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

#include <glm/mat4x4.hpp>
#include <glm/vec3.hpp>
#include <glm/gtc/matrix_transform.hpp>

#ifndef M_PI
#define M_PI 3.14159265f
#endif

namespace CSCI441 {

    /// Abstract Class to represent a synthetic camera.  The following methods
    /// must be overridden:<br>
    ///  - recomputeOrientation()<br>
    ///  - moveForward()<br>
    ///  - moveBackward()<br>
    class Camera {
    public:
        /// properly destroy concrete children
        virtual ~Camera() = default;

        /// Uses theta, phi, & radius to update the
        /// camera's view matrix parameters.
        /// The camera orientation is controlled via spherical coordinates
        /// and this method would orient and/or position the camera in
        /// cartesian coordinates.
        virtual void recomputeOrientation() = 0;

        /// steps forward along the camera's view
        /// \param movementFactor scaling factor for distance to move
        virtual void moveForward(GLfloat movementFactor) = 0;

        /// steps backward along the camera's view
        /// \param movementFactor scaling factor for distance to move
        virtual void moveBackward(GLfloat movementFactor) = 0;

        /// rotates the camera's POV by adding to theta & phi
        /// then ensuring phi stays within the (0, pi) range and finally
        /// calls through to recomputeOrientation() to update the view
        /// parameters after the rotation
        /// \param dTheta change in rotation of theta represented in radians
        /// \param dPhi change in rotation of phi represented in radians
        /// \note There is a default implementation to update theta & phi, but
        /// the method is overridable in the event a camera should be fixed
        /// and rotation can then be disabled.
        virtual void rotate(GLfloat dTheta, GLfloat dPhi);

        /// creates the View Matrix based on the position, lookAt point, and up vector
        void computeViewMatrix() { mViewMatrix = glm::lookAt(mCameraPosition, mCameraLookAtPoint, mCameraUpVector ); }

        /// returns the current view matrix
        [[nodiscard]] glm::mat4 getViewMatrix() { return mViewMatrix; }
        /// returns the current camera position in world space
        [[nodiscard]] glm::vec3 getPosition() const { return mCameraPosition; }
        /// returns the current lookAt point in world space
        [[nodiscard]] glm::vec3 getLookAtPoint() const { return mCameraLookAtPoint; }
        /// returns the current up vector in world space
        [[nodiscard]] glm::vec3 getUpVector() const { return mCameraUpVector; }
        /// returns the current theta value in radians
        [[nodiscard]] GLfloat getTheta() const { return mCameraTheta; }
        /// returns the current phi value in radians
        [[nodiscard]] GLfloat getPhi() const { return mCameraPhi; }

        /// sets the camera's position in world space
        /// \param pos the new camera world space position
        void setPosition( glm::vec3 pos ) { mCameraPosition = pos; }
        /// sets the camera's lookAt point in world space
        /// \param lookAt the new camera world space lookAt point
        void setLookAtPoint( glm::vec3 lookAt ) { mCameraLookAtPoint = lookAt; }
        /// sets the camera's up vector in world space
        /// \param up the new camera world space up vector
        void setUpVector( glm::vec3 up ) { mCameraUpVector = up; }
        /// sets the camera's theta angle in radians
        /// \param t the new camera theta angle in radians
        void setTheta( GLfloat t ) { mCameraTheta = t; }
        /// sets the camera's phi angle in radians
        /// \param p the new camera phi angle in radians
        void setPhi( GLfloat p ) { mCameraPhi = p; }
        /// sets the camera's radius
        /// \param r the new camera radius
        void setRadius( GLfloat r ) { mCameraRadius = r; }

    protected:
        Camera();

        /// stores the View Matrix corresponding to the inverse of the Camera's Matrix
        glm::mat4 mViewMatrix;

        /// the cartesian position in world space of the camera
        glm::vec3 mCameraPosition;
        /// the cartesian direction the camera is facing in world space
        glm::vec3 mCameraDirection;
        /// the world space point in front of the camera
        glm::vec3 mCameraLookAtPoint;
        /// the up vector of the camera specified in world space
        glm::vec3 mCameraUpVector;

        /// spherical angle for yaw direction in radians
        GLfloat mCameraTheta;
        /// spherical angle for pitch direction in radians
        GLfloat mCameraPhi;
        /// spherical magnitude for direction in world space
        GLfloat mCameraRadius;

    private:
        // keeps phi within the range (0, pi) to prevent the camera from flipping over
        void _clampCameraPhi();
    };
}

inline CSCI441::Camera::Camera() :
        mViewMatrix(glm::mat4(1.0f) ),
        mCameraPosition(glm::vec3(0.0f, 0.0f, 0.0f ) ),
        mCameraDirection(glm::vec3(0.0f, 0.0f, -1.0f ) ),
        mCameraLookAtPoint(glm::vec3(0.0f, 0.0f, -1.0f ) ),
        mCameraUpVector(glm::vec3(0.0f, 1.0f, 0.0f ) ),
        mCameraTheta(0.0f ),
        mCameraPhi(M_PI / 2.0f ),
        mCameraRadius(1.0f ) {
}

inline void CSCI441::Camera::rotate(GLfloat dTheta, GLfloat dPhi) {
    mCameraTheta += dTheta;           // update theta
    mCameraPhi += dPhi;               // update phi
    _clampCameraPhi();                // bounds check phi
    recomputeOrientation();     // convert to cartesian
}

inline void CSCI441::Camera::_clampCameraPhi() {
    if(mCameraPhi <= 0.0f) mCameraPhi = 0.0f + 0.001f;
    if(mCameraPhi >= M_PI) mCameraPhi = M_PI - 0.001f;
}

#endif // CSCI441_CAMERA_HPP