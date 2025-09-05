#ifdef MAKE_GLEW_EXAMPLES
#define CSCI441_USE_GLEW
#endif

#include "../HUDCamera.hpp"
#include "../OpenGL3DEngine.hpp"
#include "../materials.hpp"
#include "../objects.hpp"
#include "../SimpleShader.hpp"

#include <glm/gtc/matrix_transform.hpp>

static void simple_objects_3_engine_keyboard_callback(GLFWwindow *window, int key, int scancode, int action, int mods);
static void simple_objects_3_engine_cursor_callback(GLFWwindow *window, double x, double y);
static void simple_objects_3_engine_mouse_button_callback(GLFWwindow *window, int button, int action, int mods);
static void simple_objects_3_engine_scroll_callback(GLFWwindow *window, double xOffset, double yOffset);
static void simple_objects_3_engine_window_size_callback(GLFWwindow *window, int width, int height);

class SimpleObjects3Engine final : public CSCI441::OpenGL3DEngine {
public:
    SimpleObjects3Engine(int OPENGL_MAJOR_VERSION, int OPENGL_MINOR_VERSION,
                int WINDOW_WIDTH, int WINDOW_HEIGHT,
                const char* WINDOW_TITLE) : CSCI441::OpenGL3DEngine(OPENGL_MAJOR_VERSION, OPENGL_MINOR_VERSION, WINDOW_WIDTH, WINDOW_HEIGHT, WINDOW_TITLE, GL_TRUE) {
        _objectIndex = 0;
        _objectAngle = 0;
    }
    ~SimpleObjects3Engine() final = default;

    void run() final {
        //  This is our draw loop - all rendering is done here.  We use a loop to keep the window open
        //  until the user decides to close the window and quit the program.  Without a loop, the
        //  window will display once and then the program exits.
        while( !glfwWindowShouldClose(mpWindow) ) {          // check if the window was instructed to be closed
            glDrawBuffer( GL_BACK );                                        // work with our back frame buffer
            glClear( GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT );   // clear the current color contents and depth buffer in the window

            // Get the size of our framebuffer.  Ideally this should be the same dimensions as our window, but
            // when using a Retina display the actual window can be larger than the requested window.  Therefore,
            // query what the actual size of the window we are rendering to is.
            GLint framebufferWidth, framebufferHeight;
            glfwGetFramebufferSize( mpWindow, &framebufferWidth, &framebufferHeight );

            // update the viewport - tell OpenGL we want to render to the whole window
            glViewport( 0, 0, framebufferWidth, framebufferHeight );

            // draw everything to the window
            _renderScene(getArcballViewMatrix(), getArcballProjectionMatrix());

            // animate the scene
            _updateScene();

            glfwSwapBuffers(mpWindow);                       // flush the OpenGL commands and make sure they get rendered!
            glfwPollEvents();                                               // check for any events and signal to redraw screen
        }
    }

    void swapObject(GLuint object) { _objectIndex = object; }

private:
    //***************************************************************************
    // Engine Setup
    void mSetupGLFW() final {
        CSCI441::OpenGLEngine::mSetupGLFW();

        // set our callbacks
        glfwSetKeyCallback(mpWindow, simple_objects_3_engine_keyboard_callback);
        glfwSetCursorPosCallback(mpWindow, simple_objects_3_engine_cursor_callback);
        glfwSetMouseButtonCallback(mpWindow, simple_objects_3_engine_mouse_button_callback);
        glfwSetScrollCallback(mpWindow, simple_objects_3_engine_scroll_callback);
        glfwSetWindowSizeCallback(mpWindow, simple_objects_3_engine_window_size_callback);
    }

    void mSetupOpenGL() final {
        glEnable( GL_DEPTH_TEST );                                   // enable depth testing
        glDepthFunc( GL_LESS );                                      // use less than depth test

        glEnable(GL_BLEND);                                           // enable blending
        glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);  // use one minus blending equation

        glClearColor( 0.0f, 0.0f, 0.0f, 1.0f );     // clear the frame buffer to black
    }

    void mSetupShaders() final {
        CSCI441::SimpleShader3::setupSimpleShader();
    }

    void mSetupScene() final {
        _pHUDCamera = new CSCI441::HUDCamera(0.0f, (GLfloat)mWindowWidth, 0.0f, (GLfloat)mWindowHeight);

        _lightPositionAngle = 0.0f;

        glm::vec3 lightColor = glm::vec3(1.0f, 1.0f, 1.0f);
        CSCI441::SimpleShader3::setLightColor(lightColor);

        setArcballCameraLookAtPoint( glm::vec3(0.0f, 2.1f, 0.0f) );
        addToArcballCameraAngles( glm::vec3(M_PI / 8.0f, M_PI / 8.0f, 25.0f) );
    }

    void mCleanupScene() final {
        delete _pHUDCamera;
    }

    //***************************************************************************
    // Engine Rendering & Updating

    /// \desc draws everything to the scene from a particular point of view
    /// \param viewMtx the current view matrix for our camera
    /// \param projMtx the current projection matrix for our camera
    void _renderScene(glm::mat4 viewMtx, glm::mat4 projMtx) const {
        CSCI441::SimpleShader3::setProjectionMatrix(projMtx);
        CSCI441::SimpleShader3::setViewMatrix(viewMtx);

        CSCI441::SimpleShader3::setLightPosition(_lightPosition);

        CSCI441::SimpleShader3::setMaterialColor(_MATERIAL_WHITE_DIFFUSE);
        glm::mat4 modelMatrix = glm::translate(glm::mat4(1.0f), _lightPosition);
        CSCI441::SimpleShader3::pushTransformation(modelMatrix);
            CSCI441::SimpleShader3::disableLighting();
            CSCI441::drawSolidSphere(1.0f, 16, 16);
            CSCI441::SimpleShader3::enableLighting();
        CSCI441::SimpleShader3::popTransformation();

        CSCI441::SimpleShader3::setMaterialColor( _MATERIAL_EMERALD_DIFFUSE );
        modelMatrix = glm::scale( glm::mat4(1.0f), glm::vec3(20.0f, 0.1f, 20.0f) );
        CSCI441::SimpleShader3::pushTransformation(modelMatrix);
            CSCI441::drawSolidCubeFlat(1.0f);
        CSCI441::SimpleShader3::popTransformation();

        CSCI441::SimpleShader3::setMaterialColor( _MATERIAL_GOLD_DIFFUSE );
        modelMatrix = glm::translate(glm::mat4(1.0f), glm::vec3(0.0f, 2.1f, 0.0f));
        modelMatrix = glm::rotate( modelMatrix, _objectAngle, CSCI441::Y_AXIS );
        CSCI441::SimpleShader3::pushTransformation(modelMatrix);
            // draw all the cool stuff!
            switch( _objectIndex ) {
                case 0: CSCI441::drawSolidTeapot();                                                             break;
                case 1: CSCI441::drawSolidCubeTextured( 3.0f );                                      break;
                case 2: CSCI441::drawSolidSphere( 2.0f, 32, 32 );                          break;
                case 3: CSCI441::drawSolidTorus( 0.5f, 1.5f, 32, 32 );        break;
                case 4: CSCI441::drawSolidCone( 2.0f, 3.0f, 32, 32 );                break;
                case 5: CSCI441::drawSolidCylinder( 2.0f, 2.0f, 3.0f, 32, 32 ); break;
                case 6: CSCI441::drawSolidCubeFlat( 3.0f );                                      break;
                case 7: CSCI441::drawSolidCubeIndexed( 3.0f );                                      break;
                case 8: CSCI441::drawSolidDome(2.0f, 32, 32);                           break;
                case 9: CSCI441::drawSolidHalfSphere(2.0f, 32, 32);                     break;

                default: break;
            }
        CSCI441::SimpleShader3::popTransformation();

        CSCI441::SimpleShader3::setProjectionMatrix(_pHUDCamera->getProjectionMatrix());
        CSCI441::SimpleShader3::setViewMatrix(_pHUDCamera->getViewMatrix());
        CSCI441::SimpleShader3::disableLighting();
        CSCI441::SimpleShader3::setMaterialColor( _MATERIAL_WHITE_DIFFUSE );
        modelMatrix = glm::translate(glm::mat4(1.0f), glm::vec3(45.0f, 45.0f, 0.0f));
        modelMatrix = glm::scale(modelMatrix, glm::vec3(10.0f, 10.0f, 1.0));
        CSCI441::SimpleShader3::pushTransformation(modelMatrix);
            // draw an icon of all the cool stuff!
            switch( _objectIndex ) {
                case 0:
                    modelMatrix = glm::translate(glm::mat4(1.0f), glm::vec3(0.0f, -1.5f, 0.0f));
                    modelMatrix = glm::rotate(modelMatrix, glm::half_pi<float>(), glm::vec3(0.0f, 1.0f, 0.0f));
                    modelMatrix = glm::rotate(modelMatrix, glm::half_pi<float>(), glm::vec3(0.0f, 0.0f, 1.0f));
                    modelMatrix = glm::rotate(modelMatrix, glm::half_pi<float>(), glm::vec3(0.0f, 1.0f, 0.0f));
                    CSCI441::SimpleShader3::pushTransformation(modelMatrix);
                        CSCI441::drawSolidTeapot();
                    CSCI441::SimpleShader3::popTransformation();
                    break;

                case 2:
                    modelMatrix = glm::scale(glm::mat4(1.0f), glm::vec3(1.5f, 1.5f, 1.0f));
                    CSCI441::SimpleShader3::pushTransformation(modelMatrix);
                        CSCI441::drawSolidSphere( 1.0f, 32, 32 );
                    CSCI441::SimpleShader3::popTransformation();
                    break;

                case 3:
                    CSCI441::drawSolidTorus( 0.25f, 1.0f, 32, 32 );
                    break;

                case 4:
                    modelMatrix = glm::translate(glm::mat4(1.0f), glm::vec3(0.0f, -1.5f, 0.0f));
                    CSCI441::SimpleShader3::pushTransformation(modelMatrix);
                        CSCI441::drawSolidCone( 1.0f, 3.0f, 32, 32 );
                    CSCI441::SimpleShader3::popTransformation();
                    break;

                case 5:
                    modelMatrix = glm::translate(glm::mat4(1.0f), glm::vec3(0.0f, -1.5f, 0.0f));
                    CSCI441::SimpleShader3::pushTransformation(modelMatrix);
                        CSCI441::drawSolidCylinder( 1.0f, 1.0f, 3.0f, 32, 32 );
                    CSCI441::SimpleShader3::popTransformation();
                    break;

                case 1:
                case 6:
                case 7:
                    modelMatrix = glm::scale(glm::mat4(1.0f), glm::vec3(3.0f, 3.0f, 1.0f));
                    CSCI441::SimpleShader3::pushTransformation(modelMatrix);
                        CSCI441::drawSolidCubeIndexed( 1.0f );
                    CSCI441::SimpleShader3::popTransformation();
                    break;

                case 8:
                    CSCI441::drawSolidDome(2.0f, 32, 32);
                    break;

                case 9:
                    modelMatrix = glm::rotate(glm::mat4(1.0f), glm::half_pi<float>(), glm::vec3(0.0f, 1.0f, 0.0f));
                    modelMatrix = glm::translate(modelMatrix, glm::vec3(1.0f, 0.0f, 0.0f));
                    CSCI441::SimpleShader3::pushTransformation(modelMatrix);
                        CSCI441::drawSolidHalfSphere(2.0f, 32, 32);
                    CSCI441::SimpleShader3::popTransformation();
                    break;

                default: break;
            }
        CSCI441::SimpleShader3::popTransformation();
        CSCI441::SimpleShader3::enableLighting();
    }

    /// \desc handles moving our FreeCam as determined by keyboard input
    void _updateScene() {
        _objectAngle += ROTATION_SPEED;
        // prevent value from getting too large
        if( _objectAngle > 2.0f * M_PI ) _objectAngle -= 2.0f * M_PI;

        _lightPositionAngle += ROTATION_SPEED;
        _lightPosition = glm::vec3( glm::cos(_lightPositionAngle) * 10.0f, 10.0f, glm::sin(_lightPositionAngle) * 10.0f );
    }

    //***************************************************************************
    // VAO & Object Information

    /// \desc tracks which object we want to be viewing
    GLuint _objectIndex;
    /// \desc the current angle of rotation to display our object at
    GLfloat _objectAngle;

    CSCI441::HUDCamera* _pHUDCamera;

    glm::vec3 _lightPosition;
    GLfloat _lightPositionAngle;

    const glm::vec3 _MATERIAL_EMERALD_DIFFUSE = CSCI441::Materials::EMERALD.getDiffuse();
    const glm::vec3 _MATERIAL_GOLD_DIFFUSE = CSCI441::Materials::GOLD.getDiffuse();
    const glm::vec3 _MATERIAL_WHITE_DIFFUSE = glm::vec3(1.0f, 1.0f, 1.0f);

    /// \desc rate at which the objects rotate
    static constexpr GLfloat ROTATION_SPEED = 0.01f;
};

void simple_objects_3_engine_keyboard_callback(GLFWwindow *window, int key, int scancode, int action, int mods) {
    auto engine = (SimpleObjects3Engine*) glfwGetWindowUserPointer(window);
    engine->handleCameraKeyEvent(key, scancode, action, mods);

    if(action == GLFW_PRESS) {
        switch(key) {
            case GLFW_KEY_ESCAPE:
            case GLFW_KEY_Q:
                engine->setWindowShouldClose();
                break;

            // toggles which shape is being drawn
            case GLFW_KEY_1:
            case GLFW_KEY_2:
            case GLFW_KEY_3:
            case GLFW_KEY_4:
            case GLFW_KEY_5:
            case GLFW_KEY_6:
            case GLFW_KEY_7:
            case GLFW_KEY_8:
            case GLFW_KEY_9:
                engine->swapObject(key - GLFW_KEY_1); // GLFW_KEY_1 is 49.  they go in sequence from there
                break;

            case GLFW_KEY_0:
                engine->swapObject(9);
                break;

            default:
                break;
        }
    }
}

void simple_objects_3_engine_cursor_callback(GLFWwindow *window, double x, double y) {
    auto engine = (SimpleObjects3Engine*) glfwGetWindowUserPointer(window);
    engine->handleCameraCursorPosEvent(x, y);
}

void simple_objects_3_engine_mouse_button_callback(GLFWwindow *window, int button, int action, int mods) {
    auto engine = (SimpleObjects3Engine*) glfwGetWindowUserPointer(window);
    engine->handleCameraMouseButtonEvent(button, action, mods);
}

void simple_objects_3_engine_scroll_callback(GLFWwindow *window, double xOffset, double yOffset) {
    auto engine = (SimpleObjects3Engine*) glfwGetWindowUserPointer(window);
    engine->handleCameraScrollEvent(xOffset, yOffset);
}

void simple_objects_3_engine_window_size_callback(GLFWwindow *window, int width, int height) {
    auto engine = (SimpleObjects3Engine*) glfwGetWindowUserPointer(window);
    engine->handleCameraAspectRatioEvent(width, height);
}

int main() {
    auto pSimpleObjects3Engine = new SimpleObjects3Engine(4, 1, 512, 512, "HUD Display of Object Selection");
    pSimpleObjects3Engine->initialize();
    if (pSimpleObjects3Engine->getError() == CSCI441::OpenGLEngine::OPENGL_ENGINE_ERROR_NO_ERROR) {
        pSimpleObjects3Engine->run();
    }
    pSimpleObjects3Engine->shutdown();
    delete pSimpleObjects3Engine;

    return EXIT_SUCCESS;
}