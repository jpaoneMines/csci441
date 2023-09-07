//
// Created by Jeffrey Paone on 5/20/21.
//

#ifndef CSCI441_OPENGL3D_ENGINE_HPP
#define CSCI441_OPENGL3D_ENGINE_HPP

#include "ArcballCam.hpp"
#include "OpenGLEngine.hpp"

#include <glm/glm.hpp>

#ifndef M_PI
#define M_PI 3.141529
#endif

namespace CSCI441 {

    /**
     * @class OpenGL3DEngine
     * @brief Abstract Class to run an OpenGL application with a 3D environment.<br>
     * <br>
     * Creates and contains a default ArcballCam implementation, tracks the status of the left mouse button, shift key, and mouse position.<br>
     * <br>
     * The following methods must be overridden:<br>
     *  - mSetupOpenGL()<br>
     *  - run()<br>
     */
    class OpenGL3DEngine : public OpenGLEngine {
    public:
        /**
         * @brief do not allow engines to be copied
         */
        OpenGL3DEngine(const OpenGL3DEngine&) = delete;
        /**
        * @brief do not allow engines to be copied
        */
        OpenGL3DEngine& operator=(const OpenGL3DEngine&) = delete;

        /**
         * @brief the status of the left mouse button being down
         * @return true if left mouse button is currently being pressed, false otherwise
         */
        [[maybe_unused]] [[nodiscard]] GLboolean isLeftMouseDown() const noexcept { return mIsLeftMouseDown; }
        /**
         * @brief set the status of the left mouse button being down
         * @param isDown set to true if the left mouse button is currently being pressed, false otherwise
         */
        [[maybe_unused]] void setLeftMouseDown(GLboolean isDown) { mIsLeftMouseDown = isDown; }

        /**
         * @brief the status of either shift key being down
         * @return true if either shift key is currently being pressed, false otherwise
         */
        [[maybe_unused]] [[nodiscard]] GLboolean isShiftDown() const noexcept { return mIsShiftDown; }
        /**
         * @brief set the status of the shift keys being down
         * @param isDown set to true if either shift key is currently being pressed, false otherwise
         */
        [[maybe_unused]] void setShiftDown(GLboolean isDown) { mIsShiftDown = isDown; }

        /**
         * @brief the location of the mouse within the window
         * @return (x, y) coordinate in screen space of the mouse
         */
        [[maybe_unused]] [[nodiscard]] glm::vec2 getMousePosition() const noexcept { return mMousePosition; }
        /**
         * @brief set the location of the mouse within the window
         * @param mousePos (x, y) coordinate in screen space of the mouse
         */
        [[maybe_unused]] void setMousePosition(glm::vec2 mousePos) { mMousePosition = mousePos; }

        /**
         * @brief sets the object space position of the arcball camera in spherical world coordinates
         * @param angles (theta, phi, radius) spherical object space coordinate
         */
        [[maybe_unused]] void setArcballCameraAngles( glm::vec3 angles ) {
            mpArcballCamera->setTheta(angles[0] );
            mpArcballCamera->setPhi(angles[1] );
            mpArcballCamera->setRadius(angles[2] );
        }

        /**
         * @brief the world space position the arcball camera is located at
         * @return (x, y, z) world space position of the arcball camera
         */
        [[maybe_unused]] [[nodiscard]] glm::vec3 getArcballCameraEyePoint() const noexcept { return mpArcballCamera->getPosition(); }

        /**
         * @brief the world space position the arcball camera is looking at and thus centered around
         * @return (x, y, z) world space position the arcball is looking at and centered around
         */
        [[maybe_unused]] [[nodiscard]] glm::vec3 getArcballCameraLookAtPoint() const noexcept { return mpArcballCamera->getLookAtPoint(); }
        /**
         * @brief set the world space position the arcball camera is looking at and thus centered around
         * @param lookAtPoint (x, y, z) world space position the arcball is looking at and centered around
         */
        [[maybe_unused]] void setArcballCameraLookAtPoint( glm::vec3 lookAtPoint ) { mpArcballCamera->setLookAtPoint(lookAtPoint); }

        /**
         * @brief the world space vector the arcball camera is oriented upwards along
         * @return &lt;x, y, z&gt; world space vector the arcball is oriented upwards along
         */
        [[maybe_unused]] [[nodiscard]] glm::vec3 getArcballCameraUpVector() const noexcept { return mpArcballCamera->getUpVector(); }
        /**
         * @brief sets the world space vector the arcball camera is oriented upwards along
         * @param upVector &lt;x, y, z&gt; world space vector the arcball is oriented upwards along
         */
        [[maybe_unused]] void setArcballCameraUpVector( glm::vec3 upVector ) { mpArcballCamera->setUpVector(upVector); }

        /**
         * @brief moves the arcball spherical object space coordinate by the associated amounts
         * @param angleAdditions (theta, phi, radius) to add to existing spherical object space coordinate
         */
        [[maybe_unused]] void addToArcballCameraAngles( glm::vec3 angleAdditions ) {
            mpArcballCamera->setTheta(mpArcballCamera->getTheta() + angleAdditions[0] );
            mpArcballCamera->setPhi(mpArcballCamera->getPhi() + angleAdditions[1] );
            mpArcballCamera->moveBackward(angleAdditions[2] );
        }

        /**
         * @brief recomputes the arcball camera's world space position
         */
        [[maybe_unused]] void updateArcballCameraDirection() {
            mpArcballCamera->recomputeOrientation();
        }

    protected:
        /**
         * @brief creates OpenGLEngine for given context and window state as well as creating a default arcball camera
         * and setting the shift + left mouse button to be up
         * @param OPENGL_MAJOR_VERSION OpenGL Major version to request context of (for example 4.X)
         * @param OPENGL_MINOR_VERSION OpenGL Minor version to request context of (for example X.1)
         * @param WINDOW_WIDTH width of window to request creation of
         * @param WINDOW_HEIGHT height of window to request creation of
         * @param WINDOW_TITLE title to place on window bar
         * @param WINDOW_RESIZABLE if window should be resizable or not (defaults to false)
         * @note does not actually create the context nor the window at this time.  To do so, call the
         * initialize() method after the object has been created
         */
        OpenGL3DEngine(int OPENGL_MAJOR_VERSION, int OPENGL_MINOR_VERSION, int WINDOW_WIDTH, int WINDOW_HEIGHT, const char* WINDOW_TITLE, bool WINDOW_RESIZABLE = GLFW_FALSE);
        /**
         * @brief cleans up OpenGL 3D Engine by deleting arcball camera object
         */
        ~OpenGL3DEngine() override;

        /**
         * @brief pointer to the ArcballCam object
         */
        CSCI441::ArcballCam* mpArcballCamera;

        /**
         * @brief if the shift key was pressed when the mouse was pressed
         */
        GLboolean mIsShiftDown;
        /**
         * @brief if the mouse left button is currently pressed
         */
        GLboolean mIsLeftMouseDown;
        /**
         * @brief current mouse position
         */
        glm::vec2 mMousePosition;
    };

}

//*****************************************************************************************

inline CSCI441::OpenGL3DEngine::OpenGL3DEngine(const int OPENGL_MAJOR_VERSION, const int OPENGL_MINOR_VERSION, const int WINDOW_WIDTH, const int WINDOW_HEIGHT, const char* WINDOW_TITLE, const bool WINDOW_RESIZABLE)
        : OpenGLEngine(OPENGL_MAJOR_VERSION, OPENGL_MINOR_VERSION, WINDOW_WIDTH, WINDOW_HEIGHT, WINDOW_TITLE, WINDOW_RESIZABLE),
          mpArcballCamera( new CSCI441::ArcballCam() ),
          mIsShiftDown( GL_FALSE ),
          mIsLeftMouseDown( GL_FALSE ),
          mMousePosition( glm::vec2(0.0f, 0.0f) ) {

}

inline CSCI441::OpenGL3DEngine::~OpenGL3DEngine() {
    delete mpArcballCamera;
}

#endif // CSCI441_OPENGL3D_ENGINE_HPP
