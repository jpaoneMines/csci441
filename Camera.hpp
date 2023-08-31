/**
 * @file Camera.hpp
 * @brief Abstract Camera class to be placed (position and orientation) within our scene.
 * @author Dr. Jeffrey Paone
 *
 * @copyright MIT License Copyright (c) 2021 Dr. Jeffrey Paone
 *
 *	These functions, classes, and constants help minimize common
 *	code that needs to be written.
 *
 * @warning This header file depends upon GLEW
 * @warning This header file depends upon glm
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

    /**
     * @brief Abstract Class to represent a synthetic camera.  The following methods must be overridden:<br>
     *   - recomputeOrientation()<br>
     *   - moveForward()<br>
     *   - moveBackward()
     */
    class Camera {
    public:
        /**
         * @brief properly destroy concrete children
         */
        virtual ~Camera() = default;

        /**
         * @brief Uses theta, phi, & radius to update the
         * camera's view matrix parameters. The camera orientation
         * is controlled via spherical coordinates and this method
         * would orient and/or position the camera in cartesian
         * coordinates.
         */
        virtual void recomputeOrientation() = 0;

        /**
         * @brief steps forward along the camera's view
         * @param movementFactor scaling factor for distance to move
         */
        [[maybe_unused]] virtual void moveForward(GLfloat movementFactor) = 0;

        /**
         * @brief steps backward along the camera's view
         * @param movementFactor scaling factor for distance to move
         */
        [[maybe_unused]] virtual void moveBackward(GLfloat movementFactor) = 0;

        /**
         * @brief rotates the camera's POV by adding to theta & phi then ensuring
         * phi stays within the (0, pi) range and finally calls through to
         * recomputeOrientation() to update the view parameters after the rotation
         * @param dTheta change in rotation of theta represented in radians
         * @param dPhi change in rotation of phi represented in radians
         * @note There is a default implementation to update theta & phi, but the
         * method is overridable in the event a camera should be fixed and rotation
         * can then be disabled.
         */
        [[maybe_unused]] [[maybe_unused]] virtual void rotate(GLfloat dTheta, GLfloat dPhi);

        /**
         * @brief creates the View Matrix based on the position, lookAt point, and up vector
         */
        void computeViewMatrix() { mViewMatrix = glm::lookAt(mCameraPosition, mCameraLookAtPoint, mCameraUpVector ); }

        /**
         * @brief returns the current projection matrix for the associated camera
         * @returns homogeneous projection matrix
         */
         [[maybe_unused]] [[nodiscard]] glm::mat4 getProjectionMatrix() const { return mProjectionMatrix; }
        /**
         * @brief returns the current view matrix for the associated camera
         * @returns homogeneous view matrix
         */
        [[maybe_unused]] [[nodiscard]] glm::mat4 getViewMatrix() const { return mViewMatrix; }
        /**
         * @brief returns the current camera position in world space
         * @returns homogeneous world space point
         */
        [[nodiscard]] glm::vec3 getPosition() const { return mCameraPosition; }
        /**
         * @brief returns the current lookAt point in world space
         * @returns homogeneous world space point
         */
        [[nodiscard]] glm::vec3 getLookAtPoint() const { return mCameraLookAtPoint; }
        /**
         * @brief returns the current up vector in world space
         * @returns homogeneous world space vector
         */
        [[nodiscard]] glm::vec3 getUpVector() const { return mCameraUpVector; }
        /**
         * @brief returns the current theta value in radians
         * @returns spherical theta coordinate
         */
        [[nodiscard]] GLfloat getTheta() const { return mCameraTheta; }
        /**
         * @brief returns the current phi value in radians
         * @returns spherical phi coordinate
         */
        [[nodiscard]] GLfloat getPhi() const { return mCameraPhi; }
        /**
         * @brief returns the current radius in world space
         * @returns spherical radius coordinate
         */
        [[maybe_unused]] [[nodiscard]] GLfloat getRadius() const { return mCameraRadius; }

        /**
         * @brief sets the camera's position in world space
         * @param pos the new camera world space position
         */
        void setPosition( const glm::vec3 pos ) { mCameraPosition = pos; }
        /**
         * @brief sets the camera's lookAt point in world space
         * @param lookAt the new camera world space lookAt point
         */
        void setLookAtPoint( const glm::vec3 lookAt ) { mCameraLookAtPoint = lookAt; }
        /**
         * @brief sets the camera's up vector in world space
         * @param up the new camera world space up vector
         */
        void setUpVector( const glm::vec3 up ) { mCameraUpVector = up; }
        /**
         * @brief sets the camera's theta angle in radians
         * @param t the new camera theta angle in radians
         */
        void setTheta( const GLfloat t ) { mCameraTheta = t; }
        /**
         * @brief sets the camera's phi angle in radians
         * @param p the new camera phi angle in radians
         */
        void setPhi( const GLfloat p ) { mCameraPhi = p; }
        /**
         * @brief sets the camera's radius in world space
         * @param r the new camera radius in world space
         */
        void setRadius( const GLfloat r ) { mCameraRadius = r; }

    protected:
        /**
         * @brief create a default camera at the origin, looking down the
         * negative Z axis oriented with the world coordinate system
         */
        Camera();

        /**
         * @brief stores the Projection Matrix
         */
         glm::mat4 mProjectionMatrix;

        /**
         * @brief stores the View Matrix corresponding to the inverse of the Camera's Matrix
         */
        glm::mat4 mViewMatrix;

        /**
         * @brief the cartesian position in world space of the camera
         */
        glm::vec3 mCameraPosition;
        /**
         * @brief the cartesian direction the camera is facing in world space
         */
        glm::vec3 mCameraDirection;
        /**
         * @brief the world space point in front of the camera
         */
        glm::vec3 mCameraLookAtPoint;
        /**
         * @brief the up vector of the camera specified in world space
         */
        glm::vec3 mCameraUpVector;

        /**
         * @brief spherical angle for yaw direction in radians
         */
        GLfloat mCameraTheta;
        /**
         * @brief spherical angle for pitch direction in radians
         */
        GLfloat mCameraPhi;
        /**
         * @brief spherical magnitude for direction in world space
         */
        GLfloat mCameraRadius;

    private:
        /**
         * @brief keeps phi within the range (0, pi) to prevent the camera from flipping upside down
         * @note to invert camera - alter the up vector to flip/rotate camera orientation
         */
        void _clampCameraPhi();
    };
}

inline CSCI441::Camera::Camera() :
        mProjectionMatrix( glm::mat4(1.0f) ),
        mViewMatrix( glm::mat4(1.0f) ),
        mCameraPosition( glm::vec3(0.0f, 0.0f, 0.0f ) ),
        mCameraDirection( glm::vec3(0.0f, 0.0f, -1.0f ) ),
        mCameraLookAtPoint( glm::vec3(0.0f, 0.0f, -1.0f ) ),
        mCameraUpVector( glm::vec3(0.0f, 1.0f, 0.0f ) ),
        mCameraTheta( 0.0f ),
        mCameraPhi( M_PI / 2.0f ),
        mCameraRadius( 1.0f ) {
}

[[maybe_unused]]
inline void CSCI441::Camera::rotate(const GLfloat dTheta, const GLfloat dPhi) {
    mCameraTheta += dTheta;           // update theta
    mCameraPhi += dPhi;               // update phi
    _clampCameraPhi();                // bounds check phi
    recomputeOrientation();           // convert to cartesian
}

inline void CSCI441::Camera::_clampCameraPhi() {
    if(mCameraPhi <= 0.0f) mCameraPhi = 0.0f + 0.001f;
    if(mCameraPhi >= M_PI) mCameraPhi = M_PI - 0.001f;
}

#endif // CSCI441_CAMERA_HPP