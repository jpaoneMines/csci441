//
// Created by Jeffrey Paone on 5/20/21.
//

#ifndef CSCI441_OPENGL3DENGINE_HPP
#define CSCI441_OPENGL3DENGINE_HPP

#include "OpenGLEngine.hpp"

#include <glm/glm.hpp>

#ifndef M_PI
#define M_PI 3.141529
#endif

namespace CSCI441 {

    class OpenGL3DEngine : public OpenGLEngine {
    public:
        GLboolean isLeftMouseDown() noexcept { return _isLeftMouseDown; }
        void setLeftMouseDown(GLboolean isDown) { _isLeftMouseDown = isDown; }

        GLboolean isShiftDown() noexcept { return _isShiftDown; }
        void setShiftDown(GLboolean isDown) { _isShiftDown = isDown; }

        glm::vec2 getMousePosition() noexcept { return _mousePosition; }
        void setMousePosition(glm::vec2 mousePos) { _mousePosition = mousePos; }

        void setArcballCameraAngles( glm::vec3 angles ) { _arcballCamera.cameraAngles = angles; }

        glm::vec3 getArcballCameraEyePoint() noexcept { return _arcballCamera.eyePoint; }

        glm::vec3 getArcballCameraLookAtPoint() noexcept { return _arcballCamera.lookAtPoint; }
        void setArcballCameraLookAtPoint( glm::vec3 lookAtPoint ) { _arcballCamera.lookAtPoint = lookAtPoint; }

        glm::vec3 getArcballCameraUpVector() noexcept { return _arcballCamera.upVector; }
        void setArcballCameraUpVector( glm::vec3 upVector ) { _arcballCamera.upVector = upVector; }

        void addToArcballCameraAngles( glm::vec3 angleAdditions ) {
            _arcballCamera.cameraAngles += angleAdditions;
        }

        void updateArcballCameraDirection() {
            // ensure the camera does not flip upside down at either pole
            if( _arcballCamera.cameraAngles.y < 0 )     _arcballCamera.cameraAngles.y = 0.0f + 0.001f;
            if( _arcballCamera.cameraAngles.y >= M_PI ) _arcballCamera.cameraAngles.y = M_PI - 0.001f;

            // do not let our camera get too close or too far away
            if( _arcballCamera.cameraAngles.z <= 2.0f )  _arcballCamera.cameraAngles.z = 2.0f;
            if( _arcballCamera.cameraAngles.z >= 35.0f ) _arcballCamera.cameraAngles.z = 35.0f;

            // update the new direction to the camera
            _arcballCamera.camDir.x =  sinf( _arcballCamera.cameraAngles.x ) * sinf( _arcballCamera.cameraAngles.y );
            _arcballCamera.camDir.y = -cosf( _arcballCamera.cameraAngles.y );
            _arcballCamera.camDir.z = -cosf( _arcballCamera.cameraAngles.x ) * sinf( _arcballCamera.cameraAngles.y );

            // normalize this direction
            _arcballCamera.camDir = glm::normalize(_arcballCamera.camDir);

            // update the eye point
            _arcballCamera.eyePoint = _arcballCamera.lookAtPoint + _arcballCamera.camDir * _arcballCamera.cameraAngles.z;
        }

    protected:
        OpenGL3DEngine(const int OPENGL_MAJOR_VERSION, const int OPENGL_MINOR_VERSION, const int WINDOW_WIDTH, const int WINDOW_HEIGHT, const char* WINDOW_TITLE, const int WINDOW_RESIZABLE = GLFW_FALSE)
            : OpenGLEngine(OPENGL_MAJOR_VERSION, OPENGL_MINOR_VERSION, WINDOW_WIDTH, WINDOW_HEIGHT, WINDOW_TITLE, WINDOW_RESIZABLE) {}
        ~OpenGL3DEngine() {}

        struct CameraParameters {
            glm::vec3 cameraAngles;                     // cameraAngles --> x = theta, y = phi, z = radius
            glm::vec3 camDir;                           // direction to the camera
            glm::vec3 eyePoint;                         // camera vPos
            glm::vec3 lookAtPoint;                      // location of our object of interest
            glm::vec3 upVector;                         // the upVector of our camera
        } _arcballCamera;

        GLboolean _isShiftDown;                          // if the shift key was pressed when the mouse was pressed
        GLboolean _isLeftMouseDown;                      // if the mouse left button is currently pressed
        glm::vec2 _mousePosition;                        // current mouse position
    };

}

#endif // CSCI441_OPENGL3DENGINE_HPP
