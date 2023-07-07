#pragma once
#include <iostream>
#include <string>
#include <fstream>
#include <time.h>
#include <chrono>
#include <filesystem>
#include <sys/stat.h>

using namespace std;

#define INFO(msg) Logger::Log::Info(msg, __FILE__,  __LINE__);
#define WARNING(msg) Logger::Log::Warning(msg, __FILE__,  __LINE__);
#define ERROR(msg) Logger::Log::Error(msg, __FILE__,  __LINE__);
#define DEBUG(msg) Logger::Log::Debug(msg, __FILE__,  __LINE__);

namespace Logger {

    enum class LogLevel {
        RELEASE, DEBUG
    };

    class Log {
    private:
        static ofstream out;
        static Logger::LogLevel log_level;


    public:
        static void SetLogLevel(LogLevel log_Level) {
            log_level = log_Level;
        }

        static void Write(const string& mode, const string& msg, string file = "", int line = 0) {
            chrono::time_point now = chrono::system_clock::now();
            time_t tt = chrono::system_clock::to_time_t(now);
            tm local_tm = *localtime(&tt);

            out << "[ " << (local_tm.tm_year + 1900) << "."
                << local_tm.tm_mon << "."<< local_tm.tm_mday << " "
                << local_tm.tm_hour << ":" << local_tm.tm_min << ":" << local_tm.tm_sec << " ]"
                << "[" << mode << "] " << msg << " " << (file.empty() ? "" : "File: " + file)
                << " " << (line == 0 ? "" : "Line: " + to_string(line)) << '\n';

            out.flush();
        }

        static void InitLogFile() {
            chrono::time_point now = chrono::system_clock::now();
            time_t tt = chrono::system_clock::to_time_t(now);
            tm local_tm = *localtime(&tt);

            if (!(filesystem::exists("logs")))
                filesystem::create_directory("logs");

            string filename = "logs\\log_" +
                                   to_string(local_tm.tm_year + 1900) + "-" +
                                   to_string(local_tm.tm_mon) + "-" +
                                   to_string(local_tm.tm_mday) + ".txt";

            out.open(filename, ios::app);
            Write("INIT", "Init Logger");
        }

        static void Info(const std::string& msg, string file, int line) {
            if (log_level == LogLevel::DEBUG)
                cerr << msg << std::endl;
            Write("INFO", msg, file, line);
        }

        static void Debug(const string& msg, string file, int line) {
            cerr << msg << " " << "File: " << file << " " << "Line: " << line << endl;
        }

        static void Error(const string& msg, string file, int line) {
            if (log_level == LogLevel::DEBUG) {
                cerr << msg << endl;
            }
            Write("ERROR", msg, file, line);
        }

        static void Warning(const string& msg, string file, int line) {
            if (log_level == LogLevel::DEBUG) {
                cerr << msg << endl;
            }
            Write("WARNING", msg, file, line);
        }
    };
}