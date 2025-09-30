/**
 * @file OpenGL3DEngine.hpp
 * @brief Abstract class engine class to setup a 3D world with an arcball camera, storage for left button state and cursor position
 * @author Dr. Jeffrey Paone
 *
 * @copyright MIT License Copyright (c) 2021 Dr. Jeffrey Paone
 *
 *	These functions, classes, and constants help minimize common
 *	code that needs to be written.
 */

#ifndef CSCI441_OPENGL3D_ENGINE_HPP
#define CSCI441_OPENGL3D_ENGINE_HPP

#include "ArcballCam.hpp"
#include "OpenGLEngine.hpp"

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
         * @brief construct a new engine by moving an existing one
         */
        OpenGL3DEngine(OpenGL3DEngine&&) noexcept;
        /**
         * @brief reassign our engine by moving an existing one
         * @return our newly assigned engine
         */
        OpenGL3DEngine& operator=(OpenGL3DEngine&&) noexcept;

        /**
         * @brief the status of the left mouse button being down
         * @return true if left mouse button is currently being pressed, false otherwise
         */
        [[maybe_unused]] [[nodiscard]] virtual GLboolean isLeftMouseDown() const noexcept final { return mIsLeftMouseDown; }
        /**
         * @brief set the status of the left mouse button being down
         * @param isDown set to true if the left mouse button is currently being pressed, false otherwise
         */
        [[maybe_unused]] virtual void setLeftMouseDown(const GLboolean isDown) final { mIsLeftMouseDown = isDown; }

        /**
         * @brief the status of either shift key being down
         * @return true if either shift key is currently being pressed, false otherwise
         */
        [[maybe_unused]] [[nodiscard]] virtual GLboolean isShiftDown() const noexcept final { return mIsShiftDown; }
        /**
         * @brief set the status of the shift keys being down
         * @param isDown set to true if either shift key is currently being pressed, false otherwise
         */
        [[maybe_unused]] virtual void setShiftDown(const GLboolean isDown) final { mIsShiftDown = isDown; }

        /**
         * @brief the location of the mouse within the window
         * @return (x, y) coordinate in screen space of the mouse
         */
        [[maybe_unused]] [[nodiscard]] virtual glm::vec2 getMousePosition() const noexcept final { return mMousePosition; }
        /**
         * @brief set the location of the mouse within the window
         * @param mousePos (x, y) coordinate in screen space of the mouse
         */
        [[maybe_unused]] virtual void setMousePosition(const glm::vec2 mousePos) final { mMousePosition = mousePos; }

        /**
         * @brief sets the object space position of the arcball camera in spherical world coordinates
         * @param angles (theta, phi, radius) spherical object space coordinate
         */
        [[maybe_unused]] virtual void setArcballCameraAngles( const glm::vec3 angles ) final {
            mpArcballCamera->setTheta(angles[0] );
            mpArcballCamera->setPhi(angles[1] );
            mpArcballCamera->setRadius(angles[2] );
        }

        /**
         * @brief the world space position the arcball camera is located at
         * @return (x, y, z) world space position of the arcball camera
         */
        [[maybe_unused]] [[nodiscard]] virtual glm::vec3 getArcballCameraEyePoint() const noexcept final { return mpArcballCamera->getPosition(); }

        /**
         * @brief the world space position the arcball camera is looking at and thus centered around
         * @return (x, y, z) world space position the arcball is looking at and centered around
         */
        [[maybe_unused]] [[nodiscard]] virtual glm::vec3 getArcballCameraLookAtPoint() const noexcept final { return mpArcballCamera->getLookAtPoint(); }
        /**
         * @brief set the world space position the arcball camera is looking at and thus centered around
         * @param lookAtPoint (x, y, z) world space position the arcball is looking at and centered around
         */
        [[maybe_unused]] virtual void setArcballCameraLookAtPoint(const glm::vec3 lookAtPoint ) final { mpArcballCamera->setLookAtPoint(lookAtPoint); }

        /**
         * @brief the world space vector the arcball camera is oriented upwards along
         * @return &lt;x, y, z&gt; world space vector the arcball is oriented upwards along
         */
        [[maybe_unused]] [[nodiscard]] virtual glm::vec3 getArcballCameraUpVector() const noexcept final { return mpArcballCamera->getUpVector(); }
        /**
         * @brief sets the world space vector the arcball camera is oriented upwards along
         * @param upVector &lt;x, y, z&gt; world space vector the arcball is oriented upwards along
         */
        [[maybe_unused]] virtual void setArcballCameraUpVector( const glm::vec3 upVector ) final { mpArcballCamera->setUpVector(upVector); }

        /**
         * @brief returns the current projection matrix for the arcball camera
         * @return homogeneous projection matrix
         */
        [[maybe_unused]] [[nodiscard]] virtual glm::mat4 getArcballProjectionMatrix() const final { return mpArcballCamera->getProjectionMatrix(); }

        /**
         * @brief returns the current view matrix for the arcball camera
         * @return homogeneous view matrix
         */
        [[maybe_unused]] [[nodiscard]] virtual glm::mat4 getArcballViewMatrix() const final { return mpArcballCamera->getViewMatrix(); }

        /**
         * @brief moves the arcball spherical object space coordinate by the associated amounts
         * @param angleAdditions (theta, phi, radius) to add to existing spherical object space coordinate
         */
        [[maybe_unused]] virtual void addToArcballCameraAngles( const glm::vec3 angleAdditions ) final {
            mpArcballCamera->setTheta(mpArcballCamera->getTheta() + angleAdditions[0] );
            mpArcballCamera->setPhi(mpArcballCamera->getPhi() + angleAdditions[1] );
            mpArcballCamera->moveBackward(angleAdditions[2] );
        }

        /**
         * @brief recomputes the arcball camera's world space position
         */
        [[maybe_unused]] virtual void updateArcballCameraDirection() final {
            mpArcballCamera->recomputeOrientation();
        }

        /**
         * @brief moves camera for active cursor movement
         * @param x current cursor x coordinate in screen space
         * @param y current cursor y coordinate in screen space
         */
        [[maybe_unused]] virtual void handleCameraCursorPosEvent(const double x, const double y) final {
            const glm::vec2 currMousePos(x, getWindowHeight() - y);

            if( mIsLeftMouseDown ) {
                if( !mIsShiftDown ) {
                    // rotate the camera by the distance the mouse moved
                    mpArcballCamera->rotate((currMousePos.x - mMousePosition.x) * 0.005f,
                                              (mMousePosition.y - currMousePos.y) * 0.005f);
                } else {
                    // otherwise, update our camera angles theta & phi
                    const GLfloat totChgSq = (currMousePos.x - mMousePosition.x) + (currMousePos.y - mMousePosition.y);
                    mpArcballCamera->moveForward( totChgSq * 0.05f );
                }
            }

            setMousePosition(currMousePos);
        }

        /**
         * @brief tracks if either shift key is currently being pressed
         * @param key key that triggered event
         * @param scancode unused
         * @param action action for corresponding key (pressed, released, repeat)
         * @param mods unused
         */
        [[maybe_unused]] virtual void handleCameraKeyEvent(const int key, const int scancode, const int action, const int mods) final {
            if( key == GLFW_KEY_LEFT_SHIFT ) {
                _isLeftShiftDown = (action == GLFW_PRESS || action == GLFW_REPEAT);
            } else if( key == GLFW_KEY_RIGHT_SHIFT ) {
                _isRightShiftDown = (action == GLFW_PRESS || action == GLFW_REPEAT);
            }
            mIsShiftDown = _isLeftShiftDown || _isRightShiftDown;
        }

        /**
         * @brief tracks left mouse button state
         * @param button mouse button that triggered event
         * @param action action for corresponding mouse button (pressed or released)
         * @param mods unused
         */
        [[maybe_unused]] virtual void handleCameraMouseButtonEvent(const int button, const int action, const int mods) final {
            if( button == GLFW_MOUSE_BUTTON_LEFT ) {
                mIsLeftMouseDown = (action == GLFW_PRESS);
            }
        }

        /**
         * @brief zooms camera inward/outward based on scroll direction
         * @param xOffset unused
         * @param yOffset vertical amount scrolled
         */
        [[maybe_unused]] virtual void handleCameraScrollEvent(const double xOffset, const double yOffset) {
            mpArcballCamera->moveForward(static_cast<GLfloat>(yOffset) * 0.2f );
        }

        /**
         * @brief resizes camera aspect ratio
         * @param width new camera frame width
         * @param height new camera frame height
         */
        [[maybe_unused]] void handleCameraAspectRatioEvent(const int width, const int height) {
            mpArcballCamera->setAspectRatio( static_cast<GLfloat>(width) / static_cast<GLfloat>(height) );
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
        CSCI441::Camera* mpArcballCamera;

        /**
         * @brief if either shift key (left or right) is currently pressed
         */
        GLboolean mIsShiftDown;
        /**
         * @brief if the mouse left button is currently pressed
         */
        GLboolean mIsLeftMouseDown;
        /**
         * @brief current mouse position in screen space
         */
        glm::vec2 mMousePosition;

    private:
        /**
         * @brief true if left shift key is currently pressed
         */
        GLboolean _isLeftShiftDown;
        /**
         * @brief true if right shift key is currently pressed
         */
        GLboolean _isRightShiftDown;

        void _cleanupChildSelf();
        void _moveFromSource(OpenGL3DEngine& src);
    };
}

//*****************************************************************************************

inline CSCI441::OpenGL3DEngine::OpenGL3DEngine(const int OPENGL_MAJOR_VERSION, const int OPENGL_MINOR_VERSION, const int WINDOW_WIDTH, const int WINDOW_HEIGHT, const char* WINDOW_TITLE, const bool WINDOW_RESIZABLE)
        : OpenGLEngine(OPENGL_MAJOR_VERSION, OPENGL_MINOR_VERSION, WINDOW_WIDTH, WINDOW_HEIGHT, WINDOW_TITLE, WINDOW_RESIZABLE),
          mpArcballCamera( new CSCI441::ArcballCam(2.0f, 30.0f, static_cast<GLfloat>(WINDOW_WIDTH) / static_cast<GLfloat>(WINDOW_HEIGHT)) ),
          mIsShiftDown( GL_FALSE ),
          mIsLeftMouseDown( GL_FALSE ),
          mMousePosition( glm::vec2(0.0f, 0.0f) ),
          _isLeftShiftDown(GL_FALSE),
          _isRightShiftDown(GL_FALSE)
{

}

inline CSCI441::OpenGL3DEngine::~OpenGL3DEngine() {
    _cleanupChildSelf();
}

inline CSCI441::OpenGL3DEngine::OpenGL3DEngine(
    CSCI441::OpenGL3DEngine&& src
) noexcept : CSCI441::OpenGLEngine( std::move(src) ),
    mpArcballCamera(nullptr),
    mIsShiftDown(GL_FALSE),
    mIsLeftMouseDown(GL_FALSE),
    mMousePosition( glm::vec2(0.0f, 0.0f) ),
    _isLeftShiftDown(GL_FALSE),
    _isRightShiftDown(GL_FALSE)
{
    _moveFromSource( src );
}

inline CSCI441::OpenGL3DEngine& CSCI441::OpenGL3DEngine::operator=(CSCI441::OpenGL3DEngine&& src) noexcept {
    if (this != &src) {
        _cleanupChildSelf();
        _moveFromSource(src);
    }

    OpenGLEngine::operator=( std::move(src) );

    return *this;
}

inline void CSCI441::OpenGL3DEngine::_cleanupChildSelf() {
    delete mpArcballCamera;
    mpArcballCamera = nullptr;
}

inline void CSCI441::OpenGL3DEngine::_moveFromSource(OpenGL3DEngine& src) {
    mpArcballCamera = src.mpArcballCamera;
    src.mpArcballCamera = nullptr;

    mIsShiftDown = src.mIsShiftDown;
    src.mIsShiftDown = GL_FALSE;

    mIsLeftMouseDown = src.mIsLeftMouseDown;
    src.mIsLeftMouseDown = GL_FALSE;

    mMousePosition = src.mMousePosition;
    src.mMousePosition = glm::vec2(0.0f, 0.0f);

    _isLeftShiftDown = src._isLeftShiftDown;
    src._isLeftShiftDown = GL_FALSE;

    _isRightShiftDown = src._isRightShiftDown;
    src._isRightShiftDown = GL_FALSE;
}

#endif // CSCI441_OPENGL3D_ENGINE_HPP
