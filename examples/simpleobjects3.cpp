#ifdef MAKE_GLEW_EXAMPLES
#define CSCI441_USE_GLEW
#endif

#define CSCI441_OPENGL_ENGINE_IMPLEMENTATION
#include "../OpenGL3DEngine.hpp"
#include "../materials.hpp"
#include "../objects.hpp"
#include "../SimpleShader.hpp"

#include <glm/gtc/matrix_transform.hpp>

static void simple_objects_3_engine_keyboard_callback(GLFWwindow *window, int key, int scancode, int action, int mods);
static void simple_objects_3_engine_cursor_callback(GLFWwindow *window, double x, double y);
static void simple_objects_3_engine_mouse_button_callback(GLFWwindow *window, int button, int action, int mods);
static void simple_objects_3_engine_scroll_callback(GLFWwindow *window, double xOffset, double yOffset);

class SimpleObjects3Engine final : public CSCI441::OpenGL3DEngine {
public:
    SimpleObjects3Engine(
        const int OPENGL_MAJOR_VERSION, const int OPENGL_MINOR_VERSION,
        const int WINDOW_WIDTH, const int WINDOW_HEIGHT,
        const char* WINDOW_TITLE
    ) : CSCI441::OpenGL3DEngine(OPENGL_MAJOR_VERSION, OPENGL_MINOR_VERSION, WINDOW_WIDTH, WINDOW_HEIGHT, WINDOW_TITLE),
        _objectIndex(0),
        _objectAngle(0.0f),
        _wireframe(GL_FALSE),
        _lightPositionAngle(0.0f),
        _lightPosition( {glm::cos(_lightPositionAngle) * 10.0f, 10.0f, glm::sin(_lightPositionAngle) * 10.0f} ),
        _rotate(GL_FALSE),
        _useTransparency(GL_FALSE),
        _useSmoothShading(GL_TRUE)
    {

    }
    ~SimpleObjects3Engine() override = default;

    void run() override {
        printf("  0-9   : change object\n");
        printf("   W    : toggle wireframe\n");
        printf("   R    : toggle rotation\n");
        printf("   S    : toggle smooth shading\n");
        printf("   T    : toggle transparency\n");
        printf("Q / ESC : quit\n");

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

    void swapObject(const GLuint object) { _objectIndex = object; }

    void toggleRotation() { _rotate = !_rotate; }
    void toggleWireframe() { _wireframe = !_wireframe; }
    void toggleTransparency() { _useTransparency = !_useTransparency; }
    void toggleSmoothShading() {
        _useSmoothShading = !_useSmoothShading;
        if (_useSmoothShading) {
            CSCI441::SimpleShader3::enableSmoothShading();
        } else {
            CSCI441::SimpleShader3::enableFlatShading();
        }
        mReloadShaders();
    }

protected:
    //***************************************************************************
    // Engine Setup
    void mSetupGLFW() override {
        CSCI441::OpenGLEngine::mSetupGLFW();

        // set our callbacks
        glfwSetKeyCallback(mpWindow, simple_objects_3_engine_keyboard_callback);
        glfwSetCursorPosCallback(mpWindow, simple_objects_3_engine_cursor_callback);
        glfwSetMouseButtonCallback(mpWindow, simple_objects_3_engine_mouse_button_callback);
        glfwSetScrollCallback(mpWindow, simple_objects_3_engine_scroll_callback);
    }

    void mSetupOpenGL() override {
        glEnable( GL_DEPTH_TEST );                                   // enable depth testing
        glDepthFunc( GL_LESS );                                      // use less than depth test

        glEnable(GL_BLEND);                                           // enable blending
        glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);  // use one minus blending equation

        glClearColor( 0.0f, 0.0f, 0.0f, 1.0f );     // clear the frame buffer to black
    }

    void mSetupShaders() override {
        CSCI441::SimpleShader3::setupSimpleShader();
    }

    void mSetupScene() override {
        _rotate = GL_TRUE;

        _lightPositionAngle = 0.0f;

        constexpr glm::vec3 lightColor = glm::vec3(1.0f, 1.0f, 1.0f);
        CSCI441::SimpleShader3::setLightColor(lightColor);

        setArcballCameraLookAtPoint( glm::vec3(0.0f, 2.1f, 0.0f) );
        addToArcballCameraAngles( glm::vec3(M_PI / 8.0f, M_PI / 8.0f, 25.0f) );
    }

    //***************************************************************************
    // Engine Cleanup
    void mCleanupShaders() override {
        printf("[INFO]: ...deleting shaders.\n");
        CSCI441::SimpleShader3::cleanupSimpleShader();
    }

    void mCleanupBuffers() override {
        printf("[INFO]: ...deleting VAOs....\n");
        CSCI441::deleteObjectVAOs();
        CSCI441::deleteObjectVBOs();
    }

private:
    //***************************************************************************
    // Engine Rendering & Updating

    /// \desc draws everything to the scene from a particular point of view
    /// \param viewMtx the current view matrix for our camera
    /// \param projMtx the current projection matrix for our camera
    void _renderScene(const glm::mat4& viewMtx, const glm::mat4& projMtx) const {
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

        if (_useTransparency) {
            CSCI441::SimpleShader3::setMaterialColor( _MATERIAL_GOLD_ALPHA_DIFFUSE );
        } else {
            CSCI441::SimpleShader3::setMaterialColor( _MATERIAL_GOLD_DIFFUSE );
        }
        modelMatrix = glm::translate(glm::mat4(1.0f), glm::vec3(0.0f, 2.1f, 0.0f));
        modelMatrix = glm::rotate( modelMatrix, _objectAngle, CSCI441::Y_AXIS );
        CSCI441::SimpleShader3::pushTransformation(modelMatrix);
            // draw all the cool stuff!
            if( !_wireframe ) {
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
            } else {
                switch( _objectIndex ) {
                    case 0: CSCI441::drawWireTeapot();                                                             break;
                    case 1: CSCI441::drawWireCube( 3.0f );                                      break;
                    case 2: CSCI441::drawWireSphere( 2.0f, 32, 32 );                          break;
                    case 3: CSCI441::drawWireTorus( 0.5f, 1.5f, 32, 32 );        break;
                    case 4: CSCI441::drawWireCone( 2.0f, 3.0f, 32, 32 );                break;
                    case 5: CSCI441::drawWireCylinder( 2.0f, 2.0f, 3.0f, 32, 32 ); break;
                    case 6: CSCI441::drawWireCube( 3.0f );                                      break;
                    case 7: CSCI441::drawWireCube( 3.0f );                                      break;
                    case 8: CSCI441::drawWireDome(2.0f, 32, 32);                           break;
                    case 9: CSCI441::drawWireHalfSphere(2.0f, 32, 32);                     break;

                    default: break;
                }
            }

        CSCI441::SimpleShader3::popTransformation();
    }

    /// \desc handles moving our FreeCam as determined by keyboard input
    void _updateScene() {
        if( _rotate ) {
            _objectAngle += ROTATION_SPEED;
            // prevent value from getting too large
            if( _objectAngle > 2.0f * M_PI ) _objectAngle -= 2.0f * M_PI;

            _lightPositionAngle += ROTATION_SPEED;
            _lightPosition = glm::vec3( glm::cos(_lightPositionAngle) * 10.0f, 10.0f, glm::sin(_lightPositionAngle) * 10.0f );
        }
    }

    //***************************************************************************
    // VAO & Object Information

    /// \desc tracks which object we want to be viewing
    GLuint _objectIndex;
    /// \desc the current angle of rotation to display our object at
    GLfloat _objectAngle;
    /// \desc if objects should be drawn as wireframe or solid
    GLboolean _wireframe;

    GLfloat _lightPositionAngle;
    glm::vec3 _lightPosition;

    GLboolean _rotate;
    GLboolean _useTransparency;
    GLboolean _useSmoothShading;

    const glm::vec3 _MATERIAL_EMERALD_DIFFUSE = CSCI441::Materials::EMERALD.getDiffuse();
    const glm::vec3 _MATERIAL_GOLD_DIFFUSE = CSCI441::Materials::GOLD.getDiffuse();
    const glm::vec4 _MATERIAL_GOLD_ALPHA_DIFFUSE = glm::vec4( glm::vec3(CSCI441::Materials::GOLD.getDiffuse()), 0.5f );
    static constexpr glm::vec3 _MATERIAL_WHITE_DIFFUSE = glm::vec3(1.0f, 1.0f, 1.0f);

    /// \desc rate at which the objects rotate
    static constexpr GLfloat ROTATION_SPEED = 0.01f;
};

void simple_objects_3_engine_keyboard_callback(GLFWwindow *window, const int key, const int scancode, const int action, const int mods) {
    const auto engine = static_cast<SimpleObjects3Engine *>(glfwGetWindowUserPointer(window));
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

            case GLFW_KEY_R:
                engine->toggleRotation();
                break;

            case GLFW_KEY_W:
                engine->toggleWireframe();
                break;

            case GLFW_KEY_S:
                engine->toggleSmoothShading();
                break;

            case GLFW_KEY_T:
                engine->toggleTransparency();
                break;

            default:
                break;
        }
    }
}

void simple_objects_3_engine_cursor_callback(GLFWwindow *window, const double x, const double y) {
    const auto engine = static_cast<SimpleObjects3Engine *>(glfwGetWindowUserPointer(window));
    engine->handleCameraCursorPosEvent(x, y);
}

void simple_objects_3_engine_mouse_button_callback(GLFWwindow *window, const int button, const int action, const int mods) {
    const auto engine = static_cast<SimpleObjects3Engine *>(glfwGetWindowUserPointer(window));
    engine->handleCameraMouseButtonEvent(button, action, mods);
}

void simple_objects_3_engine_scroll_callback(GLFWwindow *window, const double xOffset, const double yOffset) {
    const auto engine = static_cast<SimpleObjects3Engine *>(glfwGetWindowUserPointer(window));
    engine->handleCameraScrollEvent(xOffset, yOffset);
}

int main() {
    const auto pSimpleObjects3Engine = new SimpleObjects3Engine(4, 1, 512, 512, "SimpleShader3 Objects");
    pSimpleObjects3Engine->initialize();
    if (pSimpleObjects3Engine->getError() == CSCI441::OpenGLEngine::OPENGL_ENGINE_ERROR_NO_ERROR) {
        pSimpleObjects3Engine->run();
    }
    pSimpleObjects3Engine->shutdown();
    delete pSimpleObjects3Engine;
    return EXIT_SUCCESS;
}