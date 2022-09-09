//
// Created by Jeffrey Paone on 5/20/21.
//

#ifndef CSCI441_OPENGL3D_ENGINE_HPP
#define CSCI441_OPENGL3D_ENGINE_HPP

#include "OpenGLEngine.hpp"
#include "ArcballCam.hpp"

#include <glm/glm.hpp>

#ifndef M_PI
#define M_PI 3.141529
#endif

namespace CSCI441 {

    class OpenGL3DEngine : public OpenGLEngine {
    public:
        [[nodiscard]] GLboolean isLeftMouseDown() const noexcept { return _isLeftMouseDown; }
        void setLeftMouseDown(GLboolean isDown) { _isLeftMouseDown = isDown; }

        [[nodiscard]] GLboolean isShiftDown() const noexcept { return _isShiftDown; }
        void setShiftDown(GLboolean isDown) { _isShiftDown = isDown; }

        [[nodiscard]] glm::vec2 getMousePosition() const noexcept { return _mousePosition; }
        void setMousePosition(glm::vec2 mousePos) { _mousePosition = mousePos; }

        void setArcballCameraAngles( glm::vec3 angles ) {
            _arcballCamera->setTheta( angles[0] );
            _arcballCamera->setPhi( angles[1] );
            _arcballCamera->setRadius( angles[2] );
        }

        [[nodiscard]] glm::vec3 getArcballCameraEyePoint() const noexcept { return _arcballCamera->getPosition(); }

        [[nodiscard]] glm::vec3 getArcballCameraLookAtPoint() const noexcept { return _arcballCamera->getLookAtPoint(); }
        void setArcballCameraLookAtPoint( glm::vec3 lookAtPoint ) { _arcballCamera->setLookAtPoint(lookAtPoint); }

        [[nodiscard]] glm::vec3 getArcballCameraUpVector() const noexcept { return _arcballCamera->getUpVector(); }
        void setArcballCameraUpVector( glm::vec3 upVector ) { _arcballCamera->setUpVector(upVector); }

        void addToArcballCameraAngles( glm::vec3 angleAdditions ) {
            _arcballCamera->setTheta( _arcballCamera->getTheta() + angleAdditions[0] );
            _arcballCamera->setPhi(_arcballCamera->getPhi() + angleAdditions[1] );
            _arcballCamera->moveBackward( angleAdditions[2] );
        }

        void updateArcballCameraDirection() {
            _arcballCamera->recomputeOrientation();
        }

    protected:
        OpenGL3DEngine(const int OPENGL_MAJOR_VERSION, const int OPENGL_MINOR_VERSION, const int WINDOW_WIDTH, const int WINDOW_HEIGHT, const char* WINDOW_TITLE, const int WINDOW_RESIZABLE = GLFW_FALSE)
            : OpenGLEngine(OPENGL_MAJOR_VERSION, OPENGL_MINOR_VERSION, WINDOW_WIDTH, WINDOW_HEIGHT, WINDOW_TITLE, WINDOW_RESIZABLE),
            _arcballCamera( new CSCI441::ArcballCam() ),
            _isShiftDown(GL_FALSE), _isLeftMouseDown(GL_FALSE),
            _mousePosition(glm::vec2(0.0f, 0.0f)) {}
        ~OpenGL3DEngine() { delete _arcballCamera; }

        CSCI441::ArcballCam* _arcballCamera;

        GLboolean _isShiftDown;                          // if the shift key was pressed when the mouse was pressed
        GLboolean _isLeftMouseDown;                      // if the mouse left button is currently pressed
        glm::vec2 _mousePosition;                        // current mouse position
    };

}

#endif // CSCI441_OPENGL3D_ENGINE_HPP
