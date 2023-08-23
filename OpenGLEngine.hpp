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

#include "OpenGLUtils.hpp"

#include <GL/glew.h>
#include <GLFW/glfw3.h>

#include <cstdio>
#include <cstring>

namespace CSCI441 {

    /// Abstract Class to run an OpenGL application.  The following methods
    /// must be overridden:<br>
    ///  - run()<br>
    ///  - mSetupOpenGL()<br>
    class OpenGLEngine {
    public:
        /// Initialize everything needed for OpenGL Rendering.  This includes
        /// in order: GLFW, GLEW, OpenGL, Shader Programs, Buffer Objects, Textures,
        /// and any Scene information
        /// \warning If this method is overridden, then the parent implementation must
        /// be called first as part of the derived implementation
        virtual void initialize();
        /// Initiate the draw loop
        virtual void run() = 0;
        /// Cleanup everything needed for OpenGL Rendering.  This includes
        /// freeing memory for data used in: any Scene information, Textures, Buffer Objects,
        /// Shader Programs, OpenGL, GLEW, GLFW
        /// \warning If this method is overridden, then the parent implementation must
        /// be called last as part of the derived implementation
        virtual void shutdown();

        /// Enable logging to command line
        void turnDebuggingOn() noexcept { DEBUG = true; }
        /// Disable logging to command line
        void turnDebuggingOff() noexcept { DEBUG = false; }
        /// Returns if logging is enable
        bool isDebuggingEnabled() noexcept { return DEBUG; }

        /// Set the new window size
        /// \param WINDOW_WIDTH width of the new window
        /// \param WINDOW_HEIGHT height of the new window
        /// \warning This function does not cause the window to be resized, rather after the window
        /// has been resized this function is used to update the data members storing the current
        /// window size.
        void setCurrentWindowSize(const int WINDOW_WIDTH, const int WINDOW_HEIGHT) { mWindowWidth = WINDOW_WIDTH; mWindowHeight = WINDOW_HEIGHT; }
        /// Return the height of the window
        int getWindowHeight() const noexcept { return mWindowHeight; }
        /// Return the width of the window
        int getWindowWidth() const noexcept { return mWindowWidth; }
        /// Return the window object
        GLFWwindow* getWindow() const noexcept { return mpWindow; }

        /// Tell our engine's window to close
        void setWindowShouldClose() { glfwSetWindowShouldClose(mpWindow, GLFW_TRUE); }

        /// Return current value of error code and clear the error code
        [[nodiscard]] unsigned int getError() noexcept {
            unsigned int storedErrorCode = mErrorCode;  // store current error code
            mErrorCode = OPENGL_ENGINE_ERROR_NO_ERROR;  // reset error code
            return storedErrorCode;                     // return previously stored error code
        }

        static const unsigned int OPENGL_ENGINE_ERROR_NO_ERROR      = 0;
        static const unsigned int OPENGL_ENGINE_ERROR_GLFW_INIT     = 1;
        static const unsigned int OPENGL_ENGINE_ERROR_GLFW_WINDOW   = 2;
        static const unsigned int OPENGL_ENGINE_ERROR_GLEW_INIT     = 3;
        static const unsigned int OPENGL_ENGINE_ERROR_UNKNOWN       = 4;
        static const unsigned int OPENGL_ENGINE_ERROR_LAST          = OPENGL_ENGINE_ERROR_UNKNOWN;

    protected:
        OpenGLEngine(const int OPENGL_MAJOR_VERSION, const int OPENGL_MINOR_VERSION, const int WINDOW_WIDTH, const int WINDOW_HEIGHT, const char* WINDOW_TITLE, const int WINDOW_RESIZABLE = GLFW_FALSE);
        ~OpenGLEngine();

        bool DEBUG;

        unsigned int mErrorCode;

        int mOpenGLMajorVersion;
        int mOpenGLMinorVersion;
        int mWindowWidth;
        int mWindowHeight;
        int mWindowResizable;
        char* mWindowTitle;
        GLFWwindow *mpWindow;

        /// We will register this function as GLFW's error callback.
        ///	When an error within GLFW occurs, GLFW will tell us by calling
        ///	this function.  We can then print this info to the terminal to
        ///	alert the user.
        static void mErrorCallback(int error, const char* DESCRIPTION) { fprintf(stderr, "[ERROR]: %d\n\t%s\n", error, DESCRIPTION ); }

        static void mWindowResizeCallback(GLFWwindow* window, int width, int height);

        /// Used to setup everything GLFW related.  This includes the OpenGL context
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
        virtual void mSetupGLFW();
        void mSetupGLEW();
        virtual void mSetupOpenGL() = 0;
        virtual void mSetupShaders() {};
        virtual void mSetupBuffers() {};
        virtual void mSetupTextures() {}
        virtual void mSetupScene() {};

        virtual void mCleanupGLFW();
        void mCleanupGLEW() {} // nothing to be done at this time
        virtual void mCleanupOpenGL() {};
        virtual void mCleanupShaders() {};
        virtual void mCleanupBuffers() {};
        virtual void mCleanupTextures() {}
        virtual void mCleanupScene() {};

    private:
        bool _isInitialized;
        bool _isCleanedUp;
    };
}

inline CSCI441::OpenGLEngine::OpenGLEngine(const int OPENGL_MAJOR_VERSION, const int OPENGL_MINOR_VERSION, const int WINDOW_WIDTH, const int WINDOW_HEIGHT, const char* WINDOW_TITLE, const int WINDOW_RESIZABLE)
        : mOpenGLMajorVersion(OPENGL_MAJOR_VERSION), mOpenGLMinorVersion(OPENGL_MINOR_VERSION), mWindowWidth(WINDOW_WIDTH), mWindowHeight(WINDOW_HEIGHT), mWindowResizable(WINDOW_RESIZABLE) {

    mWindowTitle = (char*)malloc(sizeof(char) * strlen(WINDOW_TITLE));
    strcpy(mWindowTitle, WINDOW_TITLE);

    mpWindow = nullptr;

    _isInitialized = _isCleanedUp = false;
    DEBUG = true;
    mErrorCode = OPENGL_ENGINE_ERROR_NO_ERROR;
}

inline CSCI441::OpenGLEngine::~OpenGLEngine() {
    shutdown();
    free(mWindowTitle);
}

inline void CSCI441::OpenGLEngine::initialize() {
    if( !_isInitialized ) {
        mSetupGLFW();
        mSetupGLEW();
        mSetupOpenGL();

        if (DEBUG) CSCI441::OpenGLUtils::printOpenGLInfo();

        mSetupShaders();
        mSetupBuffers();
        mSetupTextures();
        mSetupScene();

        _isInitialized = true;
        if (DEBUG) fprintf(stdout, "\n[INFO]: Setup complete\n");
    }
}

inline void CSCI441::OpenGLEngine::mSetupGLFW()  {
    // set what function to use when registering errors
    // this is the ONLY GLFW function that can be called BEFORE GLFW is initialized
    // all other GLFW calls must be performed after GLFW has been initialized
    glfwSetErrorCallback(mErrorCallback);

    // initialize GLFW
    if( !glfwInit() ) {
        fprintf( stderr, "[ERROR]: Could not initialize GLFW\n" );
        mErrorCode = OPENGL_ENGINE_ERROR_GLFW_INIT;
    } else {
        if(DEBUG) fprintf( stdout, "[INFO]: GLFW %d.%d.%d initialized\n", GLFW_VERSION_MAJOR, GLFW_VERSION_MINOR, GLFW_VERSION_REVISION );

        glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, mOpenGLMajorVersion );	        // request OpenGL vX.
        glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, mOpenGLMinorVersion );	        // request OpenGL v .X
        glfwWindowHint( GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE );                       // request forward compatible OpenGL context
        glfwWindowHint( GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE );             // request OpenGL Core Profile context
        glfwWindowHint( GLFW_DOUBLEBUFFER, GLFW_TRUE );                              // request double buffering
        glfwWindowHint(GLFW_RESIZABLE, mWindowResizable );		                    // set if our window should be able to be resized

        // create a window for a given size, with a given title
        mpWindow = glfwCreateWindow(mWindowWidth, mWindowHeight, mWindowTitle, nullptr, nullptr );
        if( !mpWindow ) {						                                                // if the window could not be created, NULL is returned
            fprintf( stderr, "[ERROR]: GLFW Window could not be created\n" );
            glfwTerminate();
            mErrorCode = OPENGL_ENGINE_ERROR_GLFW_WINDOW;
        } else {
            if(DEBUG) fprintf( stdout, "[INFO]: GLFW Window created\n" );
            glfwMakeContextCurrent(mpWindow);		                                    // make the created window the current window
            glfwSwapInterval(1);				                                        // update our screen after at least 1 screen refresh

            glfwSetWindowUserPointer(mpWindow, (void*)this);
            glfwSetWindowSizeCallback(mpWindow, mWindowResizeCallback);
        }
    }
}

inline void CSCI441::OpenGLEngine::mSetupGLEW() {
    glewExperimental = GL_TRUE;
    GLenum glewResult = glewInit();                                             // initialize GLEW

    // check for an error
    if( glewResult != GLEW_OK ) {
        fprintf( stderr, "[ERROR]: Error initializing GLEW\n");
        fprintf( stderr, "[ERROR]: %s\n", glewGetErrorString(glewResult) );
        mErrorCode = OPENGL_ENGINE_ERROR_GLEW_INIT;
    } else {
        if(DEBUG) {
            fprintf(stdout, "\n[INFO]: GLEW initialized\n");
            fprintf(stdout, "[INFO]: Using GLEW %s\n", glewGetString(GLEW_VERSION));
        }
    }
}

inline void CSCI441::OpenGLEngine::mCleanupGLFW() {
    if(DEBUG) fprintf( stdout, "[INFO]: ...closing window...\n" );
    glfwDestroyWindow(mpWindow );                        // close our window
    mpWindow = nullptr;
    if(DEBUG) fprintf( stdout, "[INFO]: ...closing GLFW.....\n" );
    glfwTerminate();
}

inline void CSCI441::OpenGLEngine::shutdown() {
    if( !_isCleanedUp ) {
        if (DEBUG) fprintf(stdout, "\n[INFO]: Shutting down.......\n");
        mCleanupShaders();                                  // delete shaders from GPU
        mCleanupBuffers();                                  // delete VAOs/VBOs from GPU
        mCleanupTextures();                                 // delete textures from GPU
        mCleanupScene();                                    // delete scene info from CPU
        mCleanupOpenGL();                                   // cleanup anything OpenGL related
        mCleanupGLEW();                                     // cleanup anything GLEW related
        mCleanupGLFW();                                     // shut down GLFW to clean up our context
        if (DEBUG) fprintf(stdout, "[INFO]: ..shut down complete!\n");
        _isCleanedUp = true;
    }
}

inline void CSCI441::OpenGLEngine::mWindowResizeCallback(GLFWwindow* window, int width, int height) {
    auto engine = (OpenGLEngine*) glfwGetWindowUserPointer(window);
    engine->setCurrentWindowSize(width, height);
}

#endif //CSCI441_OPENGLENGINE_HPP
