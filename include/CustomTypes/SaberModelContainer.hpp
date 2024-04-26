#pragma once

#include "SaberObjectConfig.hpp"
#include "System/IDisposable.hpp"
#include "UnityEngine/AssetBundle.hpp"
#include "UnityEngine/GameObject.hpp"
#include "UnityEngine/MonoBehaviour.hpp"
#include "custom-types/shared/coroutine.hpp"
#include "custom-types/shared/macros.hpp"


#include "qosmetics-core/shared/Data/Descriptor.hpp"
#include "qosmetics-core/shared/Data/Manifest.hpp"

DECLARE_CLASS_CODEGEN_INTERFACES(Qosmetics::Sabers, SaberModelContainer, UnityEngine::MonoBehaviour, classof(::System::IDisposable*),
                                 DECLARE_INSTANCE_METHOD(void, Start);
                                 DECLARE_OVERRIDE_METHOD_MATCH(void, Dispose, &::System::IDisposable::Dispose);
                                 DECLARE_INSTANCE_FIELD(UnityEngine::AssetBundle*, bundle);
                                 DECLARE_INSTANCE_FIELD(bool, isLoading);
                                 DECLARE_INSTANCE_FIELD(UnityEngine::GameObject*, currentSaberObject);

                                 DECLARE_CTOR(ctor);
                                 DECLARE_SIMPLE_DTOR();

                                 public
                                 :

                                 using Manifest = Qosmetics::Core::Manifest<Qosmetics::Sabers::SaberObjectConfig>;

                                 static SaberModelContainer * get_instance();
                                 bool LoadObject(const Manifest& manifest, std::function<void(SaberModelContainer*)> onFinished);
                                 bool LoadObject(const Qosmetics::Core::Descriptor& descriptor, std::function<void(SaberModelContainer*)> onFinished = nullptr);
                                 const SaberObjectConfig& GetSaberConfig();
                                 const Qosmetics::Core::Descriptor& GetDescriptor();
                                 bool Default();

                                 private
                                 :

                                 custom_types::Helpers::Coroutine LoadBundleRoutine(std::function<void(SaberModelContainer*)> onFinished);
                                 void Unload();

                                 Manifest currentManifest;

                                 static SaberModelContainer * instance;

)
