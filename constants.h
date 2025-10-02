//
// Created by Jeffrey Paone on 10/2/25.
//

#ifndef CSCI441_CONSTANTS_H
#define CSCI441_CONSTANTS_H

namespace CSCI441 {
    constexpr int VERSION_MAJOR = 5;
    constexpr int VERSION_MINOR = 15;
    constexpr int VERSION_PATCH = 1;

#ifdef CSCI441_USE_GLEW
    constexpr bool USING_GLEW = true;
    constexpr bool USING_GLAD = false;
#else
    constexpr bool USING_GLEW = false;
    constexpr bool USING_GLAD = true;
#endif
}

#endif //CSCI441_CONSTANTS_H