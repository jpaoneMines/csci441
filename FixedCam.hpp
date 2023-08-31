/**
 * @file FixedCam.hpp
 * @brief Concrete Fixed Camera implementation with Perspective Projection that can be positioned, oriented, and never moved
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
         * creates a FixedCam object with the specified perspective projection
         * @param aspectRatio aspect ratio of view plane (defaults to 1.0f)
         * @param fovy vertical field of view (defaults to 45.0f)
         * @param nearClipPlane near z clip plane (defaults to 0.001f)
         * @param farClipPlane far z clip plane (defaults to 1000.0f)
         * @note field of view specified in degrees
         */
        explicit FixedCam(GLfloat aspectRatio = 1.0f, GLfloat fovy = 45.0f, GLfloat nearClipPlane = 0.001f, GLfloat farClipPlane = 1000.0f);

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

    private:
        // vertical field of view stored in degrees
        GLfloat _fovy;
        GLfloat _aspectRatio;
        GLfloat _nearClipPlane;
        GLfloat _farClipPlane;
    };
}

inline CSCI441::FixedCam::FixedCam(
        const GLfloat aspectRatio,
        const GLfloat fovy,
        const GLfloat nearClipPlane,
        const GLfloat farClipPlane
) : _fovy(fovy),
    _aspectRatio(aspectRatio),
    _nearClipPlane(nearClipPlane),
    _farClipPlane(farClipPlane)
{
    mProjectionMatrix = glm::perspective(_fovy, _aspectRatio, _nearClipPlane, _farClipPlane);
}

#endif // CSCI441_FIXED_CAM_HPP