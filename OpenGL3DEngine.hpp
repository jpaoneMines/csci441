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
        [[nodiscard]] GLboolean isLeftMouseDown() const noexcept { return mIsLeftMouseDown; }
        void setLeftMouseDown(GLboolean isDown) { mIsLeftMouseDown = isDown; }

        [[nodiscard]] GLboolean isShiftDown() const noexcept { return mIsShiftDown; }
        void setShiftDown(GLboolean isDown) { mIsShiftDown = isDown; }

        [[nodiscard]] glm::vec2 getMousePosition() const noexcept { return mMousePosition; }
        void setMousePosition(glm::vec2 mousePos) { mMousePosition = mousePos; }

        void setArcballCameraAngles( glm::vec3 angles ) {
            mpArcballCamera->setTheta(angles[0] );
            mpArcballCamera->setPhi(angles[1] );
            mpArcballCamera->setRadius(angles[2] );
        }

        [[nodiscard]] glm::vec3 getArcballCameraEyePoint() const noexcept { return mpArcballCamera->getPosition(); }

        [[nodiscard]] glm::vec3 getArcballCameraLookAtPoint() const noexcept { return mpArcballCamera->getLookAtPoint(); }
        void setArcballCameraLookAtPoint( glm::vec3 lookAtPoint ) { mpArcballCamera->setLookAtPoint(lookAtPoint); }

        [[nodiscard]] glm::vec3 getArcballCameraUpVector() const noexcept { return mpArcballCamera->getUpVector(); }
        void setArcballCameraUpVector( glm::vec3 upVector ) { mpArcballCamera->setUpVector(upVector); }

        void addToArcballCameraAngles( glm::vec3 angleAdditions ) {
            mpArcballCamera->setTheta(mpArcballCamera->getTheta() + angleAdditions[0] );
            mpArcballCamera->setPhi(mpArcballCamera->getPhi() + angleAdditions[1] );
            mpArcballCamera->moveBackward(angleAdditions[2] );
        }

        void updateArcballCameraDirection() {
            mpArcballCamera->recomputeOrientation();
        }

    protected:
        OpenGL3DEngine(const int OPENGL_MAJOR_VERSION, const int OPENGL_MINOR_VERSION, const int WINDOW_WIDTH, const int WINDOW_HEIGHT, const char* WINDOW_TITLE, const int WINDOW_RESIZABLE = GLFW_FALSE)
            : OpenGLEngine(OPENGL_MAJOR_VERSION, OPENGL_MINOR_VERSION, WINDOW_WIDTH, WINDOW_HEIGHT, WINDOW_TITLE, WINDOW_RESIZABLE),
              mpArcballCamera(new CSCI441::ArcballCam() ),
              mIsShiftDown(GL_FALSE), mIsLeftMouseDown(GL_FALSE),
              mMousePosition(glm::vec2(0.0f, 0.0f)) {}
        ~OpenGL3DEngine() { delete mpArcballCamera; }

        CSCI441::ArcballCam* mpArcballCamera;

        GLboolean mIsShiftDown;                          // if the shift key was pressed when the mouse was pressed
        GLboolean mIsLeftMouseDown;                      // if the mouse left button is currently pressed
        glm::vec2 mMousePosition;                        // current mouse position
    };

}

#endif // CSCI441_OPENGL3D_ENGINE_HPP
