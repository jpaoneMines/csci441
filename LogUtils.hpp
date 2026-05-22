#ifndef CSCI441_LOG_UTILS_HPP
#define CSCI441_LOG_UTILS_HPP

#include <cstdarg>
#include <cstdio>
#include <ctime>

//************************************************
// Outward Facing Utilities

namespace CSCI441 {
    namespace LogUtils {
        void setLogFilename(const char *filename);
        void resetLogFile();
        void log(const char* MSG, ...);

        void logError(const char* MSG, ...);
        void logToTerminal(const char* MSG, ...);
        void logToFile(const char* MSG, ...);
    }
}

//************************************************
// Inward Facing Utilities

namespace CSCI441_INTERNAL {
    namespace LogUtils {
        void setLogFilename(const char *filename);
        void resetLogFile();
        void logToFile(const char* MSG, const va_list& args);
        void logToStream(FILE* file, const char* MSG, const va_list& args);
    }
}

//************************************************
// Outward Facing Definitions

inline void CSCI441::LogUtils::setLogFilename(const char *filename) {
    CSCI441_INTERNAL::LogUtils::setLogFilename(filename);
}

inline void CSCI441::LogUtils::resetLogFile() {
    CSCI441_INTERNAL::LogUtils::resetLogFile();
}

inline void CSCI441::LogUtils::log(const char* MSG, ...) {
    va_list args;

    va_start(args, MSG);
    CSCI441_INTERNAL::LogUtils::logToFile(MSG, args);
    va_end(args);

    va_start(args, MSG);
    CSCI441_INTERNAL::LogUtils::logToStream(stdout, MSG, args);
    va_end(args);
}

inline void CSCI441::LogUtils::logError(const char* MSG, ...) {
    va_list args;

    va_start(args, MSG);
    CSCI441_INTERNAL::LogUtils::logToFile(MSG, args);
    va_end(args);

    va_start(args, MSG);
    CSCI441_INTERNAL::LogUtils::logToStream(stderr, MSG, args);
    va_end(args);
}

inline void CSCI441::LogUtils::logToFile(const char* MSG, ...) {
    va_list args;
    va_start(args, MSG);
    CSCI441_INTERNAL::LogUtils::logToFile(MSG, args);
    va_end(args);
}

inline void CSCI441::LogUtils::logToTerminal(const char* MSG, ...) {
    va_list args;
    va_start(args, MSG);
    CSCI441_INTERNAL::LogUtils::logToStream(stdout, MSG, args);
    va_end(args);
}

//************************************************
// Inward Facing Definitions

inline void CSCI441_INTERNAL::LogUtils::setLogFilename(const char *filename) {

}

inline void CSCI441_INTERNAL::LogUtils::resetLogFile() {
    const time_t timestamp = time(nullptr);
    const tm datetime = *localtime(&timestamp);
    char output[50];
    strftime(output, 50, "%H:%M:%S %e %b %Y\0", &datetime);
    if (FILE* file = fopen("csci441GL.log", "w"); file != nullptr) {
        fprintf(file, "CSCI441 Log Generated at %s\n", output);
        fclose(file);
    } else {
        fprintf(stderr, "[ERROR]: Could not open file \"csci441GL.log\" for logging\n");
    }
}

inline void CSCI441_INTERNAL::LogUtils::logToFile(const char* MSG, const va_list& args) {
    if (FILE* file = fopen("csci441GL.log", "a"); file != nullptr) {
        CSCI441_INTERNAL::LogUtils::logToStream(file, MSG, args);
        fclose(file);
    } else {
        fprintf(stderr, "[ERROR]: Could not open file \"csci441GL.log\" for logging\n");
    }
}

inline void CSCI441_INTERNAL::LogUtils::logToStream(FILE *file, const char *MSG, const va_list& args) {
    vfprintf(file, MSG, args);
}

#endif//CSCI441_LOG_UTILS_HPP