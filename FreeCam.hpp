/**
 * @file FreeCam.hpp
 * @brief Free Cam Implementation
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
    /// A camera that implements a FreeCam camera model.
    /// \note camera direction is controlled by setting theta & phi and rotating the camera
    class FreeCam : public CSCI441::Camera {
    public:
        /// converts spherical theta & phi to cartesian x,y,z direction vector
        /// \note sets the camera's direction vector to point outward from a sphere centered
        /// at the camera's position and updates the camera's look at point to be a point
        /// on the sphere offset from the camera's position.  internally sets the
        /// camera's view matrix
        void recomputeOrientation() final;

        /// updates the camera's position by the adding the camera's direction to the
        /// camera's position
        /// \param movementFactor distance factor to scale the movement step
        /// \note internally sets the camera's view matrix
        void moveForward(GLfloat movementFactor) final;

        /// updates the camera's position by the adding the camera's negative direction to the
        /// camera's position
        /// \param movementFactor distance factor to scale the movement step
        /// \note internally sets the camera's view matrix
        void moveBackward(GLfloat movementFactor) final;

    private:
        // updates the look at point and recalculates the view matrix
        void _updateFreeCameraViewMatrix();
    };
}

inline void CSCI441::FreeCam::recomputeOrientation() {
    // compute direction vector based on spherical to cartesian conversion
    _direction.x =  glm::sin( _theta )*glm::sin( _phi );
    _direction.y = -glm::cos( _phi );
    _direction.z = -glm::cos( _theta )*glm::sin( _phi );

    // and normalize this directional vector!
    _direction = glm::normalize( _direction );

    _updateFreeCameraViewMatrix();
}

inline void CSCI441::FreeCam::moveForward(GLfloat movementFactor) {
    _position += _direction * movementFactor;
    _updateFreeCameraViewMatrix();
}

inline void CSCI441::FreeCam::moveBackward(GLfloat movementFactor) {
    _position -= _direction * movementFactor;
    _updateFreeCameraViewMatrix();
}

inline void CSCI441::FreeCam::_updateFreeCameraViewMatrix() {
    setLookAtPoint( _position + _direction );
    computeViewMatrix();
}

#endif // CSCI441_FREE_CAM_HPP