#include "QsaberConversion.hpp"
#include "SaberObjectConfig.hpp"

#include "logging.hpp"
#include "qosmetics-core/shared/Data/Descriptor.hpp"
#include "qosmetics-core/shared/Utils/BundleUtils.hpp"
#include "qosmetics-core/shared/Utils/FileUtils.hpp"
#include "static-defines.hpp"

#include "GlobalNamespace/SharedCoroutineStarter.hpp"
#include "UnityEngine/ImageConversion.hpp"
#include "UnityEngine/TextAsset.hpp"
#include "UnityEngine/Texture2D.hpp"
#include "zip/shared/zip.h"

#include "beatsaber-hook/shared/config/rapidjson-utils.hpp"

#include <algorithm>

#define coro(...) custom_types::Helpers::CoroutineHelper::New(__VA_ARGS__)

namespace Qosmetics::Sabers::QsaberConversion
{
    void ConvertOldQsabers()
    {
        GlobalNamespace::SharedCoroutineStarter::get_instance()->StartCoroutine(coro(ConvertAllFoundQsabers(GetNonConverted(GetQsaberFiles()))));
    }

    std::vector<std::string> GetQsaberFiles()
    {
        std::vector<std::string> result;

        Qosmetics::Core::FileUtils::GetFilesInFolderPath("qsaber", saber_path, result);
        Qosmetics::Core::FileUtils::GetFilesInFolderPath("qsaber", whacker_path, result);
        return result;
    }

    std::vector<std::pair<std::string, std::string>> GetNonConverted(std::vector<std::string> filePaths)
    {
        std::vector<std::pair<std::string, std::string>> toConvert;
        for (auto file : filePaths)
        {
            std::string fileName(Qosmetics::Core::FileUtils::GetFileName(file, true));
            std::replace(fileName.begin(), fileName.end(), ' ', '_');

            std::string convertedFilePath = fmt::format("{}/{}.whacker", whacker_path, fileName);

            if (!fileexists(convertedFilePath))
            {
                toConvert.emplace_back(std::make_pair(fmt::format("{}/{}", saber_path, file), convertedFilePath));
            }
        }

        return toConvert;
    }

    custom_types::Helpers::Coroutine ConvertAllFoundQsabers(std::vector<std::pair<std::string, std::string>> oldNewPathPairs)
    {
        // all pairs should be things to convert
        for (auto& pair : oldNewPathPairs)
        {
            std::string oldPath = pair.first;
            INFO("converting {}", oldPath);
            std::string newPath = pair.second;

            // if it exists anyways just skip it
            if (fileexists(newPath))
            {
                ERROR("{} Existed, continuing...", newPath);
                continue;
            }

            if (!fileexists(oldPath))
            {
                ERROR("{} did not exist, continuing...", oldPath);
            }
            UnityEngine::AssetBundle* bundle = nullptr;
            INFO("Loading bundle...");
            co_yield coro(Qosmetics::Core::BundleUtils::LoadBundleFromFileAsync(oldPath, bundle));

            if (!bundle)
            {
                ERROR("Couldn't load bundle from file, continuing...");
                continue;
            }

            std::string androidFileName(Qosmetics::Core::FileUtils::GetFileName(oldPath));
            std::replace(androidFileName.begin(), androidFileName.end(), ' ', '_');

            /// load descriptor
            UnityEngine::TextAsset* descriptorAsset = nullptr;
            INFO("Getting descriptor...");
            co_yield coro(Qosmetics::Core::BundleUtils::LoadAssetFromBundleAsync(bundle, "descriptor", descriptorAsset));
            std::string descriptorText = descriptorAsset->get_text();
            rapidjson::Document descriptorDoc;
            descriptorDoc.Parse(descriptorText);
            LegacyDescriptor legacyDescriptor(descriptorDoc);

            Qosmetics::Core::Descriptor actualDescriptor(legacyDescriptor.authorName, std::string(Qosmetics::Core::FileUtils::GetFileName(oldPath, true)), legacyDescriptor.description, newPath, "thumbnail.png");

            /// load config
            UnityEngine::TextAsset* configAsset = nullptr;
            INFO("Getting config...");
            co_yield coro(Qosmetics::Core::BundleUtils::LoadAssetFromBundleAsync(bundle, "config", configAsset));
            std::string configText = configAsset->get_text();
            rapidjson::Document configDoc;
            configDoc.Parse(configText);
            LegacyConfig legacyConfig(configDoc);
            // TODO: make this actually do proper stuff (also legacy config stuff)
            Qosmetics::Sabers::SaberObjectConfig actualConfig(legacyConfig.hasCustomTrails);

            INFO("Making package.json...");
            Qosmetics::Core::Manifest manifest(newPath, androidFileName, actualDescriptor, actualConfig);

            auto doc = manifest.ToJson();
            rapidjson::StringBuffer buffer;
            buffer.Clear();
            rapidjson::PrettyWriter<rapidjson::StringBuffer> writer(buffer);
            doc.Accept(writer);

            /// load thumbnail
            UnityEngine::Texture2D* thumbnail = nullptr;
            INFO("Getting thumbnail...");
            co_yield coro(Qosmetics::Core::BundleUtils::LoadAssetFromBundleAsync(bundle, "thumbnail", thumbnail));
            auto imageData = UnityEngine::ImageConversion::EncodeToPNG(thumbnail);

            int error = 0;
            auto zip = zip_open(newPath.data(), ZIP_CREATE, &error);
            zip_flags_t write;

            zip_error_t err;
            auto package_buffer = zip_source_buffer_create(buffer.GetString(), buffer.GetSize(), 0, &err);
            zip_file_add(zip, "package.json", package_buffer, ZIP_FL_ENC_GUESS);

            co_yield nullptr;
            std::vector<char> qsaberFile = readbytes(oldPath);
            auto qsaber_buffer = zip_source_buffer_create(qsaberFile.data(), qsaberFile.size(), 0, &err);
            zip_file_add(zip, androidFileName.c_str(), qsaber_buffer, ZIP_FL_ENC_GUESS);

            co_yield nullptr;
            auto thumbnail_buffer = zip_source_buffer_create(imageData.begin(), imageData.size(), 0, &err);
            zip_file_add(zip, "thumbnail.png", thumbnail_buffer, ZIP_FL_ENC_GUESS);

            zip_close(zip);
            bundle->Unload(true);
            co_yield nullptr;
        }

        co_return;
    }
}