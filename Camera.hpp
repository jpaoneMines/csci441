/**
 * @file Camera.hpp
 * @brief Abstract Camera class
 * @author Dr. Jeffrey Paone
 *
 * @copyright MIT License Copyright (c) 2021 Dr. Jeffrey Paone
 *
 *	These functions, classes, and constants help minimize common
 *	code that needs to be written.
 */

#ifndef CSCI441_CAMERA_HPP
#define CSCI441_CAMERA_HPP

#include <GL/glew.h>

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

#ifndef M_PI
#define M_PI 3.14159265
#endif

/// \namespace CSCI441
/// \desc CSCI441 Helper Functions for OpenGL
namespace CSCI441 {

    /// \desc Abstract Class to represent a synthetic camera.  The following methods
    /// must be overridden:<br>
    ///  - recomputeOrientation()<br>
    ///  - moveForward()<br>
    ///  - moveBackward()<br>
    class Camera {
    public:
        /// \desc Uses theta, phi, & radius to update the
        /// camera's view matrix parameters.
        /// The camera orientation is controlled via spherical coordinates
        /// and this method would orient and/or position the camera in
        /// cartesian coordinates.
        virtual void recomputeOrientation() = 0;

        /// \desc steps forward along the camera's view
        /// \param movementFactor scaling factor for distance to move
        virtual void moveForward(GLfloat movementFactor) = 0;

        /// \desc steps backward along the camera's view
        /// \param movementFactor scaling factor for distance to move
        virtual void moveBackward(GLfloat movementFactor) = 0;

        /// \desc rotates the camera's POV by adding to theta & phi
        /// then ensuring phi stays within the (0, pi) range and finally
        /// calls through to recomputeOrientation() to update the view
        /// parameters after the rotation
        /// \param dTheta change in rotation of theta represented in radians
        /// \param dPhi change in rotation of phi represented in radians
        /// \note There is a default implementation to update theta & phi, but
        /// the method is overridable in the event a camera should be fixed
        /// and rotation can then be disabled.
        virtual void rotate(GLfloat dTheta, GLfloat dPhi);

        /// \desc creates the View Matrix based on the position, lookAt point, and up vector
        void computeViewMatrix() { _viewMatrix = glm::lookAt( _position, _lookAtPoint, _upVector ); }

        /// \desc returns the current view matrix
        [[nodiscard]] glm::mat4 getViewMatrix() { return _viewMatrix; }
        /// \desc returns the current camera position in world space
        [[nodiscard]] glm::vec3 getPosition() const { return _position; }
        /// \desc returns the current lookAt point in world space
        [[nodiscard]] glm::vec3 getLookAtPoint() const { return _lookAtPoint; }
        /// \desc returns the current up vector in world space
        [[nodiscard]] glm::vec3 getUpVector() const { return _upVector; }
        /// \desc returns the current theta value in radians
        [[nodiscard]] GLfloat getTheta() const { return _theta; }
        /// \desc returns the current phi value in radians
        [[nodiscard]] GLfloat getPhi() const { return _phi; }

        /// \desc sets the camera's position in world space
        /// \param pos the new camera world space position
        void setPosition( glm::vec3 pos ) { _position = pos; }
        /// \desc sets the camera's lookAt point in world space
        /// \param lookAt the new camera world space lookAt point
        void setLookAtPoint( glm::vec3 lookAt ) { _lookAtPoint = lookAt; }
        /// \desc sets the camera's up vector in world space
        /// \param up the new camera world space up vector
        void setUpVector( glm::vec3 up ) { _upVector = up; }
        /// \desc sets the camera's theta angle in radians
        /// \param t the new camera theta angle in radians
        void setTheta( GLfloat t ) { _theta = t; }
        /// \desc sets the camera's phi angle in radians
        /// \param p the new camera phi angle in radians
        void setPhi( GLfloat p ) { _phi = p; }
        /// \desc sets the camera's radius
        /// \param r the new camera radius
        void setRadius( GLfloat r ) { _radius = r; }

    protected:
        Camera();

        /// \desc stores the View Matrix corresponding to the inverse of the Camera's Matrix
        glm::mat4 _viewMatrix;

        /// \desc the cartesian position in world space of the camera
        glm::vec3 _position;
        /// \desc the cartesian direction the camera is facing in world space
        glm::vec3 _direction;
        /// \desc the world space point in front of the camera
        glm::vec3 _lookAtPoint;
        /// \desc the up vector of the camera specified in world space
        glm::vec3 _upVector;

        /// \desc spherical angle for yaw direction in radians
        GLfloat _theta;
        /// \desc spherical angle for pitch direction in radians
        GLfloat _phi;
        /// \desc spherical magnitude for direction in world space
        GLfloat _radius;

    private:
        /// \desc keeps phi within the range (0, pi) to prevent the camera from flipping over
        void _clampPhi();
    };
}

inline CSCI441::Camera::Camera() {
    _viewMatrix = glm::mat4(1.0f);
    _position = glm::vec3(0.0f, 0.0f, 0.0f );
    _direction = glm::vec3( 0.0f, 0.0f, -1.0f );
    _lookAtPoint = glm::vec3( 0.0f, 0.0f, -1.0f );
    _upVector = glm::vec3( 0.0f, 1.0f, 0.0f );
    _theta = 0.0f;
    _phi = M_PI / 2.0f;
    _radius = 1.0f;
}

inline void CSCI441::Camera::rotate(GLfloat dTheta, GLfloat dPhi) {
    _theta += dTheta;           // update theta
    _phi += dPhi;               // update phi
    _clampPhi();                // bounds check phi
    recomputeOrientation();     // convert to cartesian
}

inline void CSCI441::Camera::_clampPhi() {
    if(_phi <= 0)       _phi = 0+0.001;
    if(_phi >= M_PI)    _phi = M_PI-0.001;
}

#endif // CSCI441_CAMERA_HPP