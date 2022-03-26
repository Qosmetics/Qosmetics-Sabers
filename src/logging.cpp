#include "logging.hpp"

extern ModInfo modInfo;

Logger& Qosmetics::Sabers::Logging::getLogger()
{
    static Logger* logger = new Logger(modInfo, LoggerOptions(false, true));
    return *logger;
}
