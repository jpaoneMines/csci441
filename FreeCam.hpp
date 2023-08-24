/**
 * @file FreeCam.hpp
 * @brief Concrete Free Cam Implementation
 * @author Dr. Jeffrey Paone
 *
 * @copyright MIT License Copyright (c) 2021 Dr. Jeffrey Paone
 *
 *	These functions, classes, and constants help minimize common
 *	code that needs to be written.
 */

#ifndef CSCI441_FREE_CAM_HPP
#define CSCI441_FREE_CAM_HPP

#include "Camera.hpp"

namespace CSCI441 {

    /**
     * @brief A camera that implements a FreeCam camera model.
     * @note camera direction is controlled by setting theta & phi and rotating the camera
     */
    class FreeCam final : public CSCI441::Camera {
    public:
        /**
         * @brief converts spherical theta & phi to cartesian x,y,z direction vector
         * @note sets the camera's direction vector to point outward from a sphere centered
         * at the camera's position and updates the camera's look at point to be a point on
         * the sphere offset from the camera's position.
         * @note internally sets the camera's view matrix
         */
        void recomputeOrientation() final;

        /**
         * @brief updates the camera's position by the adding the camera's direction to the camera's position
         * @param movementFactor  distance factor to scale the movement step
         * @note internally sets the camera's view matrix
         */
        void moveForward(GLfloat movementFactor) final;

        /**
         * @brief updates the camera's position by the adding the camera's negative direction to the camera's position
         * @param movementFactor distance factor to scale the movement step
         * @note internally sets the camera's view matrix
         */
        void moveBackward(GLfloat movementFactor) final;

    private:
        // updates the look at point and recalculates the view matrix
        void _updateFreeCameraViewMatrix();
    };
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