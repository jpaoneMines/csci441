/**
 * @file FreeCam.hpp
 * @brief Concrete Free Cam Implementation with Perspective Projection
 * @author Dr. Jeffrey Paone
 *
 * @copyright MIT License Copyright (c) 2021 Dr. Jeffrey Paone
 *
 *	These functions, classes, and constants help minimize common
 *	code that needs to be written.
 */

#ifndef CSCI441_FREE_CAM_HPP
#define CSCI441_FREE_CAM_HPP

#include "PerspectiveCamera.hpp"

namespace CSCI441 {

    /**
     * @brief A camera that implements a FreeCam camera model.
     * @note camera direction is controlled by setting theta & phi and rotating the camera
     */
    class FreeCam final : public CSCI441::PerspectiveCamera {
    public:
        /**
         * creates a FreeCam object with the specified perspective projection
         * @param aspectRatio aspect ratio of view plane (defaults to 1.0f)
         * @param fovy vertical field of view (defaults to 45.0f)
         * @param nearClipPlane near z clip plane (defaults to 0.001f)
         * @param farClipPlane far z clip plane (defaults to 1000.0f)
         * @note field of view specified in degrees
         */
        explicit FreeCam(GLfloat aspectRatio = 1.0f, GLfloat fovy = 45.0f, GLfloat nearClipPlane = 0.001f, GLfloat farClipPlane = 1000.0f);

        /**
         * @brief construct a copy an existing camera
         */
        FreeCam(const FreeCam&) = default;
        /**
         * @brief assign a copy of an existing camera
         * @return our newly assigned camera
         */
        FreeCam& operator=(const FreeCam&) = default;

        /**
         * @brief construct a camera by moving ane existing camera object
         */
        FreeCam(FreeCam&&) = default;
        /**
         * @brief reassign an existing camera to ourselves
         * @return our newly assigned camera
         */
        FreeCam& operator=(FreeCam&&) = default;

        /**
         * @brief properly destroy concrete children
         */
        ~FreeCam() override = default;

        /**
         * @brief converts spherical theta & phi to cartesian x,y,z direction vector
         * @note sets the camera's direction vector to point outward from a sphere centered
         * at the camera's position and updates the camera's look at point to be a point on
         * the sphere offset from the camera's position.
         * @note internally sets the camera's view matrix
         */
        void recomputeOrientation() override;

        /**
         * @brief updates the camera's position by the adding the camera's direction to the camera's position
         * @param movementFactor  distance factor to scale the movement step
         * @note internally sets the camera's view matrix
         */
        void moveForward(GLfloat movementFactor) override;

        /**
         * @brief updates the camera's position by the adding the camera's negative direction to the camera's position
         * @param movementFactor distance factor to scale the movement step
         * @note internally sets the camera's view matrix
         */
        void moveBackward(GLfloat movementFactor) override;

    private:
        // updates the look at point and recalculates the view matrix
        void _updateFreeCameraViewMatrix();
    };
}

inline CSCI441::FreeCam::FreeCam(
        const GLfloat aspectRatio,
        const GLfloat fovy,
        const GLfloat nearClipPlane,
        const GLfloat farClipPlane
) : PerspectiveCamera(aspectRatio, fovy, nearClipPlane, farClipPlane)
{
    recomputeOrientation();
}

inline void CSCI441::FreeCam::recomputeOrientation() {
    // compute direction vector based on spherical to cartesian conversion
    mCameraDirection.x =  glm::sin(mCameraTheta ) * glm::sin(mCameraPhi );
    mCameraDirection.y = -glm::cos(mCameraPhi );
    mCameraDirection.z = -glm::cos(mCameraTheta ) * glm::sin(mCameraPhi );

    // and normalize this directional vector!
    mCameraDirection = glm::normalize(mCameraDirection );

    _updateFreeCameraViewMatrix();
}

inline void CSCI441::FreeCam::moveForward(const GLfloat movementFactor) {
    mCameraPosition += mCameraDirection * movementFactor;
    _updateFreeCameraViewMatrix();
}

inline void CSCI441::FreeCam::moveBackward(const GLfloat movementFactor) {
    mCameraPosition -= mCameraDirection * movementFactor;
    _updateFreeCameraViewMatrix();
}

inline void CSCI441::FreeCam::_updateFreeCameraViewMatrix() {
    setLookAtPoint(mCameraPosition + mCameraDirection );
    computeViewMatrix();
}

#endif // CSCI441_FREE_CAM_HPP