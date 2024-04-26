#pragma once

#include "SabersConfig.hpp"
#include "UnityEngine/GameObject.hpp"
#include "conditional-dependencies/shared/main.hpp"
#include "scotland2/shared/loader.hpp"

#if __has_include("qosmetics-core/shared/Data/Descriptor.hpp")
#include "qosmetics-core/shared/Data/Descriptor.hpp"
#ifndef QOSMETICS_CORE
#define QOSMETICS_CORE
#endif
#endif

#define QOSMETICS_SABERS "qosmetics-sabers"

namespace Qosmetics::Sabers::API
{
    // only available if you also have qosmetics core as a dep
#ifdef QOSMETICS_CORE
    /// @brief optionally get the active saber descriptor
    /// @return std::nullopt if not installed, descriptor if installed (check name to see if it's default)
    std::optional<Qosmetics::Core::Descriptor> GetActiveDescriptor()
    {
        static auto function = CondDeps::Find<Qosmetics::Core::Descriptor>(QOSMETICS_SABERS, "GetActiveDescriptor");
        if (function)
            return function.value()();
        return std::nullopt;
    }
#endif

    /// @brief optionally get a const reference to the Qosmetics Config
    /// @return std::nullopt if not installed, const reference wrapper otherwise
    std::optional<std::reference_wrapper<const Qosmetics::Sabers::SabersConfig>> GetConfig()
    {
        static auto function = CondDeps::Find<Qosmetics::Sabers::SabersConfig*>(QOSMETICS_SABERS, "GetConfig");
        if (function)
            return *function.value()();
        return std::nullopt;
    }

    /// @brief Set the default saber as being active
    void SetDefault()
    {
        static auto function = CondDeps::Find<void>(QOSMETICS_SABERS, "SetDefault");
        if (function)
            function.value()();
    }

    /// @brief Set a specific saber as being active, by passing the path of the object
    /// @param filePath the path of the object
    /// @return std::nullopt if not installed, false if no new object got loaded, true if a new object got loaded
    std::optional<bool> SetActiveFromFilePath(std::string filePath)
    {
        static auto function = CondDeps::Find<bool, std::string>(QOSMETICS_SABERS, "SetActiveFromFilePath");
        if (function)
            return function.value()(filePath);
        return std::nullopt;
    }

    /// @brief Set a specific saber as being active, by passing the filename of the object (with extension!)
    /// @param obj the filename of the object
    /// @return std::nullopt if not installed, false if no new object got loaded, true if a new object got loaded
    std::optional<bool> SetActive(std::string fileName)
    {
        static auto function = CondDeps::Find<bool, std::string>(QOSMETICS_SABERS, "SetActive");
        if (function)
            return function.value()(fileName);
        return std::nullopt;
    }

    /// @brief checks if the current saber is a custom one or default one
    /// @return std::nullopt if not installed, false if not custom, true if custom
    std::optional<bool> GetSaberIsCustom()
    {
        static auto function = CondDeps::Find<bool>(QOSMETICS_SABERS, "GetSaberIsCustom");
        if (function)
            return function.value()();
        return std::nullopt;
    }

    /// @brief optionally get a clone of the in-use saber so that it's properly inited, only really useful if GetSaberIsCustom returns a proper value, and nothing is disabling qosmetics sabers from being used
    /// @param left true for left, false for right
    /// @return std::nullopt if not installed, nullptr if no sabers on object, if there is sabers a gameobject pointer to a cloned and initialized saber object
    std::optional<UnityEngine::GameObject*> GetInUseSaberClone(bool left)
    {
        static auto function = CondDeps::Find<UnityEngine::GameObject*, bool>(QOSMETICS_SABERS, "GetInUseSaberClone");
        if (function)
            return function.value()(left);
        return std::nullopt;
    }

    /// @brief optionally get a clone of a saber type
    /// @param left true for left, false for right
    /// @return std::nullopt if not installed, nullptr if no sabers on object, if there is sabers a gameobject pointer to a cloned saber object
    std::optional<UnityEngine::GameObject*> GetSaber(bool left)
    {
        static auto function = CondDeps::Find<UnityEngine::GameObject*, bool>(QOSMETICS_SABERS, "GetSaber");
        if (function)
            return function.value()(left);
        return std::nullopt;
    }

    /// @brief optionally get a clone of the entire prefab
    /// @return std::nullopt if not installed, nullptr if default, if there is saber object a pointer to a cloned gameobject
    std::optional<UnityEngine::GameObject*> GetPrefabClone()
    {
        static auto function = CondDeps::Find<UnityEngine::GameObject*>(QOSMETICS_SABERS, "GetPrefabClone");
        if (function)
            return function.value()();
        return std::nullopt;
    }

    /// @brief optionally get the entire prefab (Please don't edit to break things!)
    /// @return std::nullopt if not installed, nullptr if default, if there is something selected a pointer to the original object
    std::optional<UnityEngine::GameObject*> GetPrefab()
    {
        static auto function = CondDeps::Find<UnityEngine::GameObject*>(QOSMETICS_SABERS, "GetPrefab");
        if (function)
            return function.value()();
        return std::nullopt;
    }

    /// @brief checks if sabers are disabled due to a mod registering itself as disabling
    /// @return std::nullopt if not installed, false if not disabled, true if disabled
    std::optional<bool> GetSabersDisabled()
    {
        static auto function = CondDeps::Find<bool>(QOSMETICS_SABERS, "GetSabersDisabled");
        if (function)
            return function.value()();
        return std::nullopt;
    }

    /// @brief Unregister your mod as disabling Saber editing
    /// @param info your mod info
    void UnregisterSaberDisablingInfo(modloader::ModInfo info)
    {
        static auto function = CondDeps::Find<void, modloader::ModInfo>(QOSMETICS_SABERS, "UnregisterSaberDisablingInfo");
        if (function)
            function.value()(info);
    }

    /// @brief register your mod as disabling Saber editing
    /// @param info your mod info
    void RegisterSaberDisablingInfo(modloader::ModInfo info)
    {
        static auto function = CondDeps::Find<void, modloader::ModInfo>(QOSMETICS_SABERS, "RegisterSaberDisablingInfo");
        if (function)
            function.value()(info);
    }

    /// @brief get the saber folder
    /// @return std::nullopt if not installed, else folder path for saber folder
    std::optional<std::string> GetSaberFolder()
    {
        static auto function = CondDeps::Find<std::string>(QOSMETICS_SABERS, "GetSaberFolder");
        if (function)
            return function.value()();
        return std::nullopt;
    }
}

#undef QOSMETICS_SABERS
