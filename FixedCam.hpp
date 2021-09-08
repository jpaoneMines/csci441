/**
 * @file FixedCam.hpp
 * @brief Includes all CSCI 441 class helper files
 * @author Dr. Jeffrey Paone
 *
 * @copyright MIT License Copyright (c) 2021 Dr. Jeffrey Paone
 *
 * These functions, classes, and constants help minimize common
 * code that needs to be written.
 */

#ifndef CSCI441_FIXED_CAMERA_HPP
#define CSCI441_FIXED_CAMERA_HPP

#include <CSCI441/Camera.hpp>

namespace CSCI441 {
    /// \desc A camera that can be positioned and oriented but never moved or
    /// rotated.
    /// \note Must position via setPosition()
    /// \note Must orient via setLookAtPoint()
    class FixedCam : public CSCI441::Camera {
    public:
        void recomputeOrientation() final;
        void moveForward(GLfloat unused) final;
        void moveBackward(GLfloat unused) final;
    };
}

inline void CSCI441::FixedCam::recomputeOrientation() {}

inline void CSCI441::FixedCam::moveForward(GLfloat unused) {}

inline void CSCI441::FixedCam::moveBackward(GLfloat unused) {}

#endif // CSCI441_FIXED_CAMERA_HPP