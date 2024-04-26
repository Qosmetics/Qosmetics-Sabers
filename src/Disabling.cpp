#include "Disabling.hpp"
#include "logging.hpp"
#include <set>

bool operator<(const modloader::ModInfo& lhs, const modloader::ModInfo& rhs)
{
    if (lhs.id == rhs.id)
        return lhs.version < rhs.version;
    return lhs.id < rhs.id;
}

namespace Qosmetics::Sabers::Disabling
{
    std::list<modloader::ModInfo> disablingModInfos = {};

    void RegisterDisablingModInfo(modloader::ModInfo info)
    {
        auto disablingModInfoItr = std::find_if(
            disablingModInfos.begin(),
            disablingModInfos.end(),
            [&info](auto& v)
            {
                return v.equals(info, modloader::MatchType::kIdVersion);
            });

        if (disablingModInfoItr != disablingModInfos.end())
            INFO("Mod {} tried to register disabling mod info more than once!", info.id);
        else
            disablingModInfos.emplace_back(info);
    }

    void UnregisterDisablingModInfo(modloader::ModInfo info)
    {
        auto disablingModInfoItr = std::find_if(
            disablingModInfos.begin(),
            disablingModInfos.end(),
            [&info](auto& v)
            {
                return v.equals(info, modloader::MatchType::kIdVersion);
            });
        if (disablingModInfoItr != disablingModInfos.end())
            disablingModInfos.erase(disablingModInfoItr);
        else
            INFO("Mod {} tried to remove their disabling mod info more than once!", info.id);
    }

    bool GetAnyDisabling()
    {
        return disablingModInfos.size() > 0;
    }

}
