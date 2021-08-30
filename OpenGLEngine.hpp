/**
 * @file OpenGLEngine.hpp
 * @brief Abstract class
 * @author Dr. Jeffrey Paone
 *
 * @copyright MIT License Copyright (c) 2021 Dr. Jeffrey Paone
 *
 *	These functions, classes, and constants help minimize common
 *	code that needs to be written.
 */

#ifndef CSCI441_OPENGLENGINE_HPP
#define CSCI441_OPENGLENGINE_HPP

#include <GL/glew.h>
#include <GLFW/glfw3.h>

#include "OpenGLUtils.hpp"

#include <cstdio>
#include <cstring>

/// \namespace CSCI441
/// \desc CSCI441 Helper Functions for OpenGL
namespace CSCI441 {

    /// \desc Abstract Class to run an OpenGL application.  The following methods
    /// must be overridden:<br>
    ///  - run()<br>
    ///  - _setupOpenGL()<br>
    class OpenGLEngine {
    public:
        /// \desc Initialize everything needed for OpenGL Rendering.  This includes
        /// in order: GLFW, GLEW, OpenGL, Shader Programs, Buffer Objects, Textures,
        /// and any Scene information
        /// \warning If this method is overridden, then the parent implementation must
        /// be called first as part of the derived implementation
        virtual void initialize();
        virtual void run() = 0;
        /// \desc Cleanup everything needed for OpenGL Rendering.  This includes
        /// freeing memory for data used in: any Scene information, Textures, Buffer Objects,
        /// Shader Programs, OpenGL, GLEW, GLFW
        /// \warning If this method is overridden, then the parent implementation must
        /// be called last as part of the derived implementation
        virtual void shutdown();

        /// \desc Enable logging to command line
        void turnDebuggingOn() noexcept { DEBUG = true; }
        /// \desc Disable logging to command line
        void turnDebuggingOff() noexcept { DEBUG = false; }
        /// \desc Returns if logging is enable
        bool isDebuggingEnabled() noexcept { return DEBUG; }

        /// \desc Set the new window size
        /// \param WINDOW_WIDTH width of the new window
        /// \param WINDOW_HEIGHT height of the new window
        /// \warning This function does not cause the window to be resized, rather after the window
        /// has been resized this function is used to update the data members storing the current
        /// window size.
        void setCurrentWindowSize(const int WINDOW_WIDTH, const int WINDOW_HEIGHT) { _windowWidth = WINDOW_WIDTH; _windowHeight = WINDOW_HEIGHT; }
        /// \desc Return the height of the window
        int getWindowHeight() const noexcept { return _windowHeight; }
        /// \desc Return the width of the window
        int getWindowWidth() const noexcept { return _windowWidth; }
        /// \desc Return the window object
        GLFWwindow* getWindow() const noexcept { return _window; }

        /// \desc Tell our engine's window to close
        void setWindowShouldClose() { glfwSetWindowShouldClose(_window, GLFW_TRUE); }

        /// \desc Return current value of error code and clear the error code
        [[nodiscard]] unsigned int getError() noexcept {
            unsigned int storedErrorCode = _errorCode;  // store current error code
            _errorCode = OPENGL_ENGINE_ERROR_NO_ERROR;  // reset error code
            return storedErrorCode;                     // return previously stored error code
        }

        static const unsigned int OPENGL_ENGINE_ERROR_NO_ERROR      = 0;
        static const unsigned int OPENGL_ENGINE_ERROR_GLFW_INIT     = 1;
        static const unsigned int OPENGL_ENGINE_ERROR_GLFW_WINDOW   = 2;
        static const unsigned int OPENGL_ENGINE_ERROR_GLEW_INIT     = 3;

    protected:
        OpenGLEngine(const int OPENGL_MAJOR_VERSION, const int OPENGL_MINOR_VERSION, const int WINDOW_WIDTH, const int WINDOW_HEIGHT, const char* WINDOW_TITLE, const int WINDOW_RESIZABLE = GLFW_FALSE)
            : _majorVersion(OPENGL_MAJOR_VERSION), _minorVersion(OPENGL_MINOR_VERSION), _windowWidth(WINDOW_WIDTH), _windowHeight(WINDOW_HEIGHT), _windowResizable(WINDOW_RESIZABLE) {

            _windowTitle = (char*)malloc(sizeof(char) * strlen(WINDOW_TITLE));
            strcpy(_windowTitle, WINDOW_TITLE);

            _window = nullptr;

            _isInitialized = _isCleanedUp = false;
            DEBUG = true;
            _errorCode = OPENGL_ENGINE_ERROR_NO_ERROR;
        }
        ~OpenGLEngine() {
            shutdown();
            free(_windowTitle);
        }

        bool DEBUG;

        unsigned int _errorCode;

        int _majorVersion;
        int _minorVersion;
        int _windowWidth;
        int _windowHeight;
        int _windowResizable;
        char* _windowTitle;
        GLFWwindow *_window;

        /// \desc
        ///     We will register this function as GLFW's error callback.
        ///	When an error within GLFW occurs, GLFW will tell us by calling
        ///	this function.  We can then print this info to the terminal to
        ///	alert the user.
        static void _errorCallback(int error, const char* DESCRIPTION) { fprintf( stderr, "[ERROR]: %d\n\t%s\n", error, DESCRIPTION ); }

        static void _windowResizeCallback(GLFWwindow* window, int width, int height);

        /// \desc Used to setup everything GLFW related.  This includes the OpenGL context
        /// and our window.<br><br>
        /// By default, completes the following steps in order:<br>
        ///  - sets error callback<br>
        ///  - initializes GLFW<br>
        ///  - sets window hints for OpenGL MAJOR.minor<br>
        ///  - requests Core Profile<br>
        ///  - requests double buffering<br>
        ///  - marks window as resizable or not based on constructor creation<br>
        ///  - creates a window<br>
        ///  - makes the window the current context<br>
        ///  - sets the swap interval to 1
        /// \note This method should be overridden if any additional callbacks need to be registered.
        /// When registering additional callbacks, the parent implementation must be called first and
        /// then the additional callbacks may be registered as desired.
        virtual void _setupGLFW();
        void _setupGLEW();
        virtual void _setupOpenGL() = 0;
        virtual void _setupShaders() {};
        virtual void _setupBuffers() {};
        virtual void _setupTextures() {}
        virtual void _setupScene() {};

        virtual void _cleanupGLFW();
        void _cleanupGLEW() { /* nothing to be done at this time */ }
        virtual void _cleanupOpenGL() {};
        virtual void _cleanupShaders() {};
        virtual void _cleanupBuffers() {};
        virtual void _cleanupTextures() {}
        virtual void _cleanupScene() {};

    private:
        bool _isInitialized;
        bool _isCleanedUp;
    };
}

inline void CSCI441::OpenGLEngine::initialize() {
    if( !_isInitialized ) {
        _setupGLFW();
        _setupGLEW();
        _setupOpenGL();

        if (DEBUG) CSCI441::OpenGLUtils::printOpenGLInfo();

        _setupShaders();
        _setupBuffers();
        _setupTextures();
        _setupScene();

        _isInitialized = true;
        if (DEBUG) fprintf(stdout, "\n[INFO]: Setup complete\n");
    }
}

inline void CSCI441::OpenGLEngine::_setupGLFW()  {
    // set what function to use when registering errors
    // this is the ONLY GLFW function that can be called BEFORE GLFW is initialized
    // all other GLFW calls must be performed after GLFW has been initialized
    glfwSetErrorCallback( _errorCallback );

    // initialize GLFW
    if( !glfwInit() ) {
        fprintf( stderr, "[ERROR]: Could not initialize GLFW\n" );
        _errorCode = OPENGL_ENGINE_ERROR_GLFW_INIT;
    } else {
        if(DEBUG) fprintf( stdout, "[INFO]: GLFW %d.%d.%d initialized\n", GLFW_VERSION_MAJOR, GLFW_VERSION_MINOR, GLFW_VERSION_REVISION );

        glfwWindowHint( GLFW_CONTEXT_VERSION_MAJOR, _majorVersion );	        // request OpenGL vX.
        glfwWindowHint( GLFW_CONTEXT_VERSION_MINOR, _minorVersion );	        // request OpenGL v.X
        glfwWindowHint( GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE );                  // request forward compatible OpenGL context
        glfwWindowHint( GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE );        // request OpenGL Core Profile context
        glfwWindowHint( GLFW_DOUBLEBUFFER, GLFW_TRUE );                             // request double buffering
        glfwWindowHint( GLFW_RESIZABLE, _windowResizable );		                // set if our window should be able to be resized

        // create a window for a given size, with a given title
        _window = glfwCreateWindow( _windowWidth, _windowHeight, _windowTitle, nullptr, nullptr );
        if( !_window ) {						                                // if the window could not be created, NULL is returned
            fprintf( stderr, "[ERROR]: GLFW Window could not be created\n" );
            glfwTerminate();
            _errorCode = OPENGL_ENGINE_ERROR_GLFW_WINDOW;
        } else {
            if(DEBUG) fprintf( stdout, "[INFO]: GLFW Window created\n" );
            glfwMakeContextCurrent(_window);		                                // make the created window the current window
            glfwSwapInterval(1);				                            // update our screen after at least 1 screen refresh

            glfwSetWindowUserPointer(_window, (void*)this);
            glfwSetWindowSizeCallback(_window, _windowResizeCallback);
        }
    }
}

inline void CSCI441::OpenGLEngine::_setupGLEW() {
    glewExperimental = GL_TRUE;
    GLenum glewResult = glewInit();                                             // initialize GLEW

    // check for an error
    if( glewResult != GLEW_OK ) {
        fprintf( stderr, "[ERROR]: Error initializing GLEW\n");
        fprintf( stderr, "[ERROR]: %s\n", glewGetErrorString(glewResult) );
        _errorCode = OPENGL_ENGINE_ERROR_GLEW_INIT;
    } else {
        if(DEBUG) {
            fprintf(stdout, "\n[INFO]: GLEW initialized\n");
            fprintf(stdout, "[INFO]: Using GLEW %s\n", glewGetString(GLEW_VERSION));
        }
    }
}

inline void CSCI441::OpenGLEngine::_cleanupGLFW() {
    if(DEBUG) fprintf( stdout, "[INFO]: ...closing window...\n" );
    glfwDestroyWindow( _window );                        // close our window
    _window = nullptr;
    if(DEBUG) fprintf( stdout, "[INFO]: ...closing GLFW.....\n" );
    glfwTerminate();
}

inline void CSCI441::OpenGLEngine::shutdown() {
    if( !_isCleanedUp ) {
        if (DEBUG) fprintf(stdout, "\n[INFO]: Shutting down.......\n");
        _cleanupShaders();                                  // delete shaders from GPU
        _cleanupBuffers();                                  // delete VAOs/VBOs from GPU
        _cleanupTextures();                                 // delete textures from GPU
        _cleanupScene();                                    // delete scene info from CPU
        _cleanupOpenGL();                                   // cleanup anything OpenGL related
        _cleanupGLEW();                                     // cleanup anything GLEW related
        _cleanupGLFW();                                     // shut down GLFW to clean up our context
        if (DEBUG) fprintf(stdout, "[INFO]: ..shut down complete!\n");
        _isCleanedUp = true;
    }
}

inline void CSCI441::OpenGLEngine::_windowResizeCallback(GLFWwindow* window, int width, int height) {
    auto engine = (OpenGLEngine*) glfwGetWindowUserPointer(window);
    engine->setCurrentWindowSize(width, height);
}

#endif //CSCI441_OPENGLENGINE_HPP
