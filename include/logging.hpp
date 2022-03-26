#pragma once
#include "beatsaber-hook/shared/utils/logging.hpp"
#include "beatsaber-hook/shared/utils/typedefs.h"
#include <string_view>

#include "paper/shared/logger.hpp"

namespace Qosmetics::Sabers
{
    class Logging
    {
    public:
        static Logger& getLogger();
    };
}
#define INFO(...) Paper::Logger::fmtLog<Paper::LogLevel::INF>(__VA_ARGS__)
#define ERROR(...) Paper::Logger::fmtLog<Paper::LogLevel::ERR>(__VA_ARGS__)
#define WARNING(...) Paper::Logger::fmtLog<Paper::LogLevel::WRN>(__VA_ARGS__)
#define CRITICAL(...) Paper::Logger::fmtLog<Paper::LogLevel::CRIT>(__VA_ARGS__)
#define DEBUG(...) Paper::Logger::fmtLog<Paper::LogLevel::DBG>(__VA_ARGS__)
//#define DEBUG(...)

template <>
struct fmt::formatter<::StringW> : formatter<std::string_view>
{
    // parse is inherited from formatter<string_view>.
    template <typename FormatContext>
    auto format(StringW s, FormatContext& ctx)
    {
        return formatter<std::string_view>::format(static_cast<std::string>(s), ctx);
    }
};

//#define DEBUG(...)