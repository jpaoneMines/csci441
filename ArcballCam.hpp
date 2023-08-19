/**
 * @file ArcballCam.hpp
 * @brief Abstract Camera class
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
    /// A camera that implements an ArcBall camera model.
    /// \note camera direction is controlled by setting theta & phi and rotating the camera
    class ArcballCam : public CSCI441::Camera {
    public:
        explicit ArcballCam(GLfloat minRadius = 2.0f, GLfloat maxRadius = 30.0f) : _minRadius(minRadius), _maxRadius(maxRadius) {}

        /// converts spherical theta & phi to cartesian x,y,z direction vector
        /// \note sets the camera's position to be on a sphere centered
        /// at the camera's look at position.  internally sets the
        /// camera's view matrix
        void recomputeOrientation() final;

        /// updates the camera's position by decreasing the camera's radius
        /// \param movementFactor distance factor to scale the movement step
        /// \note internally sets the camera's view matrix
        void moveForward(GLfloat movementFactor) final;

        /// updates the camera's position by increasing the camera's radius
        /// \param movementFactor distance factor to scale the movement step
        /// \note internally sets the camera's view matrix
        void moveBackward(GLfloat movementFactor) final;

    private:
        // updates the camera position and recalculates the view matrix
        void _updateArcballCameraViewMatrix();

        void _clampRadius();

        GLfloat _minRadius;
        GLfloat _maxRadius;
    };
}

inline void CSCI441::ArcballCam::recomputeOrientation() {
    // compute direction vector based on spherical to cartesian conversion
    _direction.x =  glm::sin( _theta )*glm::sin( _phi ) * _radius;
    _direction.y = -glm::cos( _phi ) * _radius;
    _direction.z = -glm::cos( _theta )*glm::sin( _phi ) * _radius;

    _updateArcballCameraViewMatrix();
}

inline void CSCI441::ArcballCam::moveForward(GLfloat movementFactor) {
    _radius -= movementFactor;
    _clampRadius();
    recomputeOrientation();
}

inline void CSCI441::ArcballCam::moveBackward(GLfloat movementFactor) {
    _radius += movementFactor;
    _clampRadius();
    recomputeOrientation();
}

inline void CSCI441::ArcballCam::_updateArcballCameraViewMatrix() {
    setPosition( _lookAtPoint + _direction );
    computeViewMatrix();
}

inline void CSCI441::ArcballCam::_clampRadius() {
    _radius = glm::clamp(_radius, _minRadius, _maxRadius);
}

#endif // CSCI441_ARCBALL_CAM_HPP