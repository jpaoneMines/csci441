/**
 * @file constants.h
 * @brief stores library specific constants and flags
 * @author Dr. Jeffrey Paone
 *
 * @copyright MIT License Copyright (c) 2025 Dr. Jeffrey Paone
 *
 * These functions, classes, and constants help minimize common
 * code that needs to be written.
 */

#ifndef CSCI441_CONSTANTS_H
#define CSCI441_CONSTANTS_H

namespace CSCI441 {
    /**
     * @brief library major version
     */
    inline constexpr int VERSION_MAJOR = 6;
    /**
     * @brief library minor version
     */
    inline constexpr int VERSION_MINOR = 0;
    /**
     * @brief library revision version
     */
    inline constexpr int VERSION_REVISION = 3;
    /**
     * @brief library patch version
     */
    inline constexpr int VERSION_PATCH = 0;

#ifdef CSCI441_USE_GLEW
    /**
     * @brief true if the library is dependent upon GLEW
     */
    inline constexpr bool USING_GLEW = true;
    /**
     * @brief true if the library is dependent upon GLAD
     */
    inline constexpr bool USING_GLAD = false;
#else
    /**
     * @brief true if the library is dependent upon GLEW
     */
    inline constexpr bool USING_GLEW = false;
    /**
     * @brief true if the library is dependent upon GLAD
     */
    inline constexpr bool USING_GLAD = true;
#endif
}

#endif //CSCI441_CONSTANTS_H