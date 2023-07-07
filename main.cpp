#include "Logger.hpp"

int main ()
{
    Logger::Log::InitLogFile();
    Logger::Log::SetLogLevel(Logger::LogLevel::DEBUG);
    INFO("Hello");
    ERROR("ERROR");
    WARNING("WARNING");
    DEBUG("DEBUG");
    return 0;
};