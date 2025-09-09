#ifdef MAKE_GLEW_EXAMPLES
#define CSCI441_USE_GLEW
#endif

#include "../OpenGLEngine.hpp"
#include "../SimpleShader.hpp"

#include <glm/gtc/matrix_transform.hpp>

#include <vector>

static void simple_tri_2_engine_keyboard_callback(GLFWwindow *window, int key, int scancode, int action, int mods);

class SimpleTri2Engine final : public CSCI441::OpenGLEngine {
public:
    SimpleTri2Engine(
        const int OPENGL_MAJOR_VERSION, const int OPENGL_MINOR_VERSION,
        const int WINDOW_WIDTH, const int WINDOW_HEIGHT,
        const char* WINDOW_TITLE
    ) : CSCI441::OpenGLEngine(OPENGL_MAJOR_VERSION, OPENGL_MINOR_VERSION, WINDOW_WIDTH, WINDOW_HEIGHT, WINDOW_TITLE),
        _triangleVAO(0),
        _triforceRotationSpeed(1.0f),
        _triforceAngle(0.0f)
    {

    }

    void run() override {
        // update the projection matrix based on the window size
        // the GL_PROJECTION matrix governs properties of the view coordinates;
        // i.e. what gets seen - use an Orthographic projection that ranges
        // from [0, windowWidth] in X and [0, windowHeight] in Y. (0,0) is the lower left.
        const glm::mat4 projMtx = glm::ortho( 0.0f, static_cast<GLfloat>(mWindowWidth), 0.0f, static_cast<GLfloat>(mWindowHeight) );
        CSCI441::SimpleShader2::setProjectionMatrix(projMtx);

        // Get the size of our framebuffer.  Ideally this should be the same dimensions as our window, but
        // when using a Retina display the actual window can be larger than the requested window.  Therefore,
        // query what the actual size of the window we are rendering to is.
        GLint framebufferWidth, framebufferHeight;
        glfwGetFramebufferSize( mpWindow, &framebufferWidth, &framebufferHeight );

        // update the viewport - tell OpenGL we want to render to the whole window
        glViewport( 0, 0, framebufferWidth, framebufferHeight );

        GLdouble currTime, lastTime = glfwGetTime();

        //  This is our draw loop - all rendering is done here.  We use a loop to keep the window open
        //  until the user decides to close the window and quit the program.  Without a loop, the
        //  window will display once and then the program exits.
        while( !glfwWindowShouldClose(mpWindow) ) { // check if the window was instructed to be closed
            glClear( GL_COLOR_BUFFER_BIT );           // clear the current color contents in the window

            _renderScene();                                 // draw everything to the window

            glfwSwapBuffers(mpWindow);                      // flush the OpenGL commands and make sure they get rendered!
            glfwPollEvents();                               // check for any events and signal to redraw screen

            currTime = glfwGetTime();
            _updateScene(lastTime - currTime);          // animate scene components
            lastTime = currTime;
        }
    }

protected:
    void mSetupGLFW() override {
        CSCI441::OpenGLEngine::mSetupGLFW();
        glfwSetKeyCallback( mpWindow, simple_tri_2_engine_keyboard_callback );
    }
    void mSetupOpenGL() override {
        glClearColor( 0.0f, 0.0f, 0.0f, 1.0f );     // set the clear color to black
    }
    void mSetupShaders() override {
        CSCI441::SimpleShader2::setupSimpleShader();
    }
    void mSetupBuffers() override {
        glm::vec3 gold(0.9f, 0.8f, 0.1f);

        _trianglePoints.emplace_back( -2.5f, -2.0f );   _triangleColorsGold.emplace_back( gold );
        _trianglePoints.emplace_back(  2.5f, -2.0f );   _triangleColorsGold.emplace_back( gold );
        _trianglePoints.emplace_back(  0.0f,  2.0f );   _triangleColorsGold.emplace_back( gold );

        _triangleVAO = CSCI441::SimpleShader2::registerVertexArray( _trianglePoints, _triangleColorsGold );
    }
    void mCleanupBuffers() override {
        CSCI441::SimpleShader2::deleteVertexArray( _triangleVAO );
        _triangleVAO = 0;

        _trianglePoints.clear();
        _triangleColorsGold.clear();
    }

private:
    void _renderScene() const {
        const glm::mat4 transMtx = glm::translate( glm::mat4(1.0), glm::vec3(getWindowWidth() / 2.0f, getWindowHeight() / 2.0f, 0.0f) );
        CSCI441::SimpleShader2::pushTransformation( transMtx );
            const glm::mat4 rotMtx = glm::rotate( glm::mat4(1.0), _triforceAngle, glm::vec3(0, 0, 1) );
            CSCI441::SimpleShader2::pushTransformation( rotMtx );
                const glm::mat4 scaleMtx = glm::scale( glm::mat4(1.0), glm::vec3(10, 10, 1) );
                CSCI441::SimpleShader2::pushTransformation( scaleMtx );
                    _drawTriforce();
                CSCI441::SimpleShader2::popTransformation();
            CSCI441::SimpleShader2::popTransformation();
        CSCI441::SimpleShader2::popTransformation();
    }

    void _drawTriangle() const {
        CSCI441::SimpleShader2::draw(GL_TRIANGLES, _triangleVAO, _trianglePoints.size());
    }

    void _drawTriforce() const {
        constexpr glm::mat4 t1 = glm::translate( glm::mat4(1.0), glm::vec3( -2.5f, -2.0f, 0.0f ) );
        CSCI441::SimpleShader2::pushTransformation( t1 );
            _drawTriangle();
        CSCI441::SimpleShader2::popTransformation();

        constexpr glm::mat4 t2 = glm::translate( glm::mat4(1.0), glm::vec3( 2.5f, -2.0f, 0.0f ) );
        CSCI441::SimpleShader2::pushTransformation( t2 );
            _drawTriangle();
        CSCI441::SimpleShader2::popTransformation();

        constexpr glm::mat4 t3 = glm::translate( glm::mat4(1.0), glm::vec3( 0.0f, 2.0f, 0.0f ) );
        CSCI441::SimpleShader2::pushTransformation( t3 );
            _drawTriangle();
        CSCI441::SimpleShader2::popTransformation();
    }

    void _updateScene(const GLfloat dt) {
        _triforceAngle += _triforceRotationSpeed * dt;
        if( _triforceAngle > glm::two_pi<GLfloat>() ) _triforceAngle -= glm::two_pi<GLfloat>();
    }

    GLuint _triangleVAO;
    std::vector<glm::vec2> _trianglePoints;
    std::vector<glm::vec3> _triangleColorsGold;
    GLfloat _triforceRotationSpeed;
    GLfloat _triforceAngle;
};

void simple_tri_2_engine_keyboard_callback(GLFWwindow *window, const int key, const int scancode, const int action, const int mods) {
    const auto engine = static_cast<SimpleTri2Engine *>(glfwGetWindowUserPointer(window));
    if(action == GLFW_PRESS) {
        switch(key) {
            case GLFW_KEY_ESCAPE:
            case GLFW_KEY_Q:
                engine->setWindowShouldClose();
                break;

            default:
                break;
        }
    }
}

int main() {
    const auto pSimpleTri2Engine = new SimpleTri2Engine(4, 1, 512, 512, "SimpleShader2 Triangle");
    pSimpleTri2Engine->initialize();
    if (pSimpleTri2Engine->getError() == CSCI441::OpenGLEngine::OPENGL_ENGINE_ERROR_NO_ERROR) {
        pSimpleTri2Engine->run();
    }
    pSimpleTri2Engine->shutdown();
    delete pSimpleTri2Engine;

    return EXIT_SUCCESS;
}