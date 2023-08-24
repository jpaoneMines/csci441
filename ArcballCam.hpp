/**
 * @file ArcballCam.hpp
 * @brief Concrete Arcball Camera implementation
 * @author Dr. Jeffrey Paone
 *
 * @copyright MIT License Copyright (c) 2021 Dr. Jeffrey Paone
 *
 *	These functions, classes, and constants help minimize common
 *	code that needs to be written.
 */

#ifndef CSCI441_ARCBALL_CAM_HPP
#define CSCI441_ARCBALL_CAM_HPP

#include "Camera.hpp"

namespace CSCI441 {

    /**
     * @brief A camera that implements an ArcBall camera model.
     * @note camera direction is controlled by setting theta & phi and rotating the camera
     */
    class ArcballCam final : public CSCI441::Camera {
    public:
        /**
         * @brief initializes the Arcball Camera and sets the minimum/maximum radius the camera can zoom through
         * @param minRadius minimum radius (zoom) for camera - defaults to 2.0 world space units
         * @param maxRadius maximum radius (zoom) for camera - defaults to 30.0 world space units
         */
        explicit ArcballCam(const GLfloat minRadius = 2.0f, const GLfloat maxRadius = 30.0f) : _minRadius(minRadius), _maxRadius(maxRadius) {}

        /**
         * @brief converts spherical theta & phi to cartesian x,y,z direction vector
         * @note sets the camera's position to be on a sphere centered at the camera's
         * look at position
         * @note internally sets the camera's view matrix
         */
        void recomputeOrientation() final;

        /**
         * @brief updates the camera's position by decreasing the camera's radius
         * @param movementFactor distance factor to scale the movement step
         * @note internally sets the camera's view matrix
         */
        void moveForward(GLfloat movementFactor) final;

        /**
         * @brief updates the camera's position by increasing the camera's radius
         * @param movementFactor distance factor to scale the movement step
         * @note internally sets the camera's view matrix
         */
        void moveBackward(GLfloat movementFactor) final;

    private:
        // updates the camera position and recalculates the view matrix
        void _updateArcballCameraViewMatrix();

        // keeps the current camera radius within the range (_minRadius, _maxRadius)
        void _clampRadius();

        // minimum allowable radius of camera
        GLfloat _minRadius;
        // maximum allowable radius of camera
        GLfloat _maxRadius;
    };
}

inline void CSCI441::ArcballCam::recomputeOrientation() {
    // compute direction vector based on spherical to cartesian conversion
    mCameraDirection.x =  glm::sin(mCameraTheta ) * glm::sin(mCameraPhi ) * mCameraRadius;
    mCameraDirection.y = -glm::cos(mCameraPhi )                                  * mCameraRadius;
    mCameraDirection.z = -glm::cos(mCameraTheta ) * glm::sin(mCameraPhi ) * mCameraRadius;

    _updateArcballCameraViewMatrix();
}

inline void CSCI441::ArcballCam::moveForward(const GLfloat movementFactor) {
    mCameraRadius -= movementFactor;    // camera "moves forward" by reducing the radius to get closer to the look at point
    _clampRadius();                     // ensure camera doesn't get too close
    recomputeOrientation();             // update view matrix
}

inline void CSCI441::ArcballCam::moveBackward(const GLfloat movementFactor) {
    mCameraRadius += movementFactor;    // camera "moves backward" by increasing the radius to get further away from the look at point
    _clampRadius();                     // ensure camera doesn't get too far away
    recomputeOrientation();             // update view matrix
}

inline void CSCI441::ArcballCam::_updateArcballCameraViewMatrix() {
    setPosition(mCameraLookAtPoint + mCameraDirection );
    computeViewMatrix();
}

inline void CSCI441::ArcballCam::_clampRadius() {
    mCameraRadius = glm::clamp(mCameraRadius, _minRadius, _maxRadius);
}

#endif // CSCI441_ARCBALL_CAM_HPP