/**
 * @file FixedCam.hpp
 * @brief Concrete Fixed Camera implementation that can be position, oriented, and never moved
 * @author Dr. Jeffrey Paone
 *
 * @copyright MIT License Copyright (c) 2021 Dr. Jeffrey Paone
 *
 * These functions, classes, and constants help minimize common
 * code that needs to be written.
 */

#ifndef CSCI441_FIXED_CAM_HPP
#define CSCI441_FIXED_CAM_HPP

#include "Camera.hpp"

namespace CSCI441 {

    /**
     * @brief A camera that can be positioned and oriented but never moved or rotated
     * @note Must position via setPosition()
     * @note Must orient via setLookAtPoint()
     */
    class FixedCam final : public CSCI441::Camera {
    public:
        /**
         * @brief does nothing
         */
        void recomputeOrientation() final {};
        /**
         * @brief does nothing
         * @param unused does nothing
         */
        void moveForward(const GLfloat unused) final {};
        /**
         * @brief does nothing
         * @param unused does nothing
         */
        void moveBackward(const GLfloat unused) final {};
    };
}

#endif // CSCI441_FIXED_CAM_HPP