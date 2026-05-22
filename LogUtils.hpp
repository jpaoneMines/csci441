#ifndef CSCI441_LOG_UTILS_HPP
#define CSCI441_LOG_UTILS_HPP

#include <cstdarg>
#include <cstdio>
#include <ctime>

//************************************************
// Outward Facing Utilities

namespace CSCI441 {
    /**
     * @brief Utility class to log information to the terminal and file\n\n
     * Usage:\n
     * (1) Filename defaults to 'csci441GL.log', call setLogFilename() at
     * program start to change the output file name
     * (2) At program start, call resetLogFile() to clear prior file if one
     * exists.  Otherwise, new logs will continue to be appended to
     * existing file.
     */
    namespace LogUtils {
        /**
         * @brief change the name of the log file that messages are saved to
         * @param filename name of file to write out to
         */
        void setLogFilename(const char *filename);

        /**
         * @brief clears contents of log file (if it exists) and prints
         * timestamp to file of when log was initially created
         */
        void resetLogFile();

        /**
         * @brief log a message to both the standard output stream and file
         * @param MSG formatted string to print
         * @param ... optional arguments to inject into string
         */
        void log(const char* MSG, ...);

        /**
         * @brief log a message to both the standard error stream and file
         * @param MSG formatted string to print
         * @param ... optional arguments to inject into string
         */
        void logError(const char* MSG, ...);

        /**
         * @brief log a message to the standard output stream
         * @param MSG formatted string to print
         * @param ... optional arguments to inject into string
         */
        void logToTerminal(const char* MSG, ...);

        /**
         * @brief log a message to file
         * @param MSG formatted string to print
         * @param ... optional arguments to inject into string
         */
        void logToFile(const char* MSG, ...);
    }
}

//************************************************
// Inward Facing Utilities

namespace CSCI441_INTERNAL {
    namespace LogUtils {
        /**
         * @brief name of file to open
         * @note can be changed through setLogFilename()
         */
        inline const char* logFilename = "csci441GL.log";

        /**
         * @brief change the name of the log file messages are written to
         * @param filename name of file to write to
         */
        void setLogFilename(const char *filename);

        /**
         * @brief clears contents of log file (if it exists) and prints
         * timestamp to file of when log was initially created
         */
        void resetLogFile();

        /**
         * @brief opens log file and appends message to file
         * @param MSG formatted string to print
         * @param args variadic list of arguments to inject into string
         */
        void logToFile(const char* MSG, const va_list& args);

        /**
         * @brief prints message to file stream
         * @param file pointer to already opened file stream
         * @param MSG formatted string to print
         * @param args variadic list of arguments to inject into string
         * @note file must be open prior to logging
         */
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
    CSCI441_INTERNAL::LogUtils::logFilename = filename;
}

inline void CSCI441_INTERNAL::LogUtils::resetLogFile() {
    const time_t timestamp = time(nullptr);
    const tm datetime = *localtime(&timestamp);
    char output[50];
    strftime(output, 50, "%H:%M:%S %e %b %Y\0", &datetime);
    if (FILE* file = fopen(logFilename, "w"); file != nullptr) {
        fprintf(file, "CSCI441 Log Generated at %s\n", output);
        fclose(file);
    } else {
        fprintf(stderr, "[ERROR]: Could not open file \"%s\" for logging\n", logFilename);
    }
}

inline void CSCI441_INTERNAL::LogUtils::logToFile(const char* MSG, const va_list& args) {
    if (FILE* file = fopen(logFilename, "a"); file != nullptr) {
        CSCI441_INTERNAL::LogUtils::logToStream(file, MSG, args);
        fclose(file);
    } else {
        fprintf(stderr, "[ERROR]: Could not open file \"%s\" for logging\n", logFilename);
    }
}

inline void CSCI441_INTERNAL::LogUtils::logToStream(FILE *file, const char *MSG, const va_list& args) {
    vfprintf(file, MSG, args);
}

#endif//CSCI441_LOG_UTILS_HPP