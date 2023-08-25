/**
 * @file OpenGLEngine.hpp
 * @brief Abstract class engine class to setup window, register callbacks, vaos, textures, and shaders, draw, update
 * @author Dr. Jeffrey Paone
 *
 * @copyright MIT License Copyright (c) 2021 Dr. Jeffrey Paone
 *
 *	These functions, classes, and constants help minimize common
 *	code that needs to be written.
 */

#ifndef CSCI441_OPENGL_ENGINE_HPP
#define CSCI441_OPENGL_ENGINE_HPP

#include "OpenGLUtils.hpp"

#include <GL/glew.h>
#include <GLFW/glfw3.h>

#include <cstdio>
#include <cstring>

namespace CSCI441 {

    /**
     * @brief Abstract Class to run an OpenGL application.  The following methods
     * must be overridden:<br>
     *  - mSetupOpenGL()<br>
     *  - run()<br>
     */
    class OpenGLEngine {
    public:
        /**
         * @brief Initialize everything needed for OpenGL Rendering.  This includes
         * in order: GLFW, GLEW, OpenGL, Shader Programs, Buffer Objects, Textures,
         * and any Scene information
         * @warning If this method is overridden, then the parent implementation must
         * be called first as part of the derived implementation
         */
        virtual void initialize();
        /**
         * @brief Initiate the draw loop
         */
        virtual void run() = 0;
        /**
         * @brief Cleanup everything needed for OpenGL Rendering.  This includes
         * freeing memory for data used in: any Scene information, Textures, Buffer Objects,
         * Shader Programs, OpenGL, GLEW, GLFW
         * @warning If this method is overridden, then the parent implementation must
         * be called last as part of the derived implementation
         */
        virtual void shutdown();

        /**
         * @brief Enable logging to command line
         * @note Enabled by default
         */
        [[maybe_unused]] void turnDebuggingOn() noexcept { DEBUG = true; }
        /**
         * @brief Disable logging to command line
         * @note Enabled by default
         */
        void turnDebuggingOff() noexcept { DEBUG = false; }
        /**
         * @brief Returns if logging is enabled
         */
        [[maybe_unused]] [[nodiscard]] bool isDebuggingEnabled() const noexcept { return DEBUG; }

        /**
         * @brief Set the new window size
         * @param WINDOW_WIDTH width of the new window
         * @param WINDOW_HEIGHT height of the new window
         * @warning This function does not cause the window to be resized, rather after the window
         * has been resized this function is used to update the data members storing the current
         * window size.
         */
        void setCurrentWindowSize(const int WINDOW_WIDTH, const int WINDOW_HEIGHT) { mWindowWidth = WINDOW_WIDTH; mWindowHeight = WINDOW_HEIGHT; }
        /**
         * @brief Return the height of the window
         */
        [[maybe_unused]] [[nodiscard]] int getWindowHeight() const noexcept { return mWindowHeight; }
        /**
         * @brief Return the width of the window
         */
        [[maybe_unused]] [[nodiscard]] int getWindowWidth() const noexcept { return mWindowWidth; }
        /**
         * @brief Return the window object
         */
        [[maybe_unused]] [[nodiscard]] GLFWwindow* getWindow() const noexcept { return mpWindow; }

        /**
         * @brief Tell our engine's window to close
         */
        [[maybe_unused]] void setWindowShouldClose() { glfwSetWindowShouldClose(mpWindow, GLFW_TRUE); }

        /**
         * @brief Return current value of error code and clear the error code back to no error
         */
        [[nodiscard]] unsigned short getError() noexcept {
            unsigned short storedErrorCode = mErrorCode;  // store current error code
            mErrorCode = OPENGL_ENGINE_ERROR_NO_ERROR;  // reset error code
            return storedErrorCode;                     // return previously stored error code
        }

        /**
         * @brief no error is present, everything is currently working
         */
        static const unsigned short OPENGL_ENGINE_ERROR_NO_ERROR      = 0;
        /**
         * @brief an error occurred while initializing GLFW
         */
        static const unsigned short OPENGL_ENGINE_ERROR_GLFW_INIT     = 1;
        /**
         * @brief an error occurred while creating the GLFW window
         */
        static const unsigned short OPENGL_ENGINE_ERROR_GLFW_WINDOW   = 2;
        /**
         * @brief an error occurred while initializing GLEW
         */
        static const unsigned short OPENGL_ENGINE_ERROR_GLEW_INIT     = 3;
        /**
         * @brief a new error that does not correspond to a predefined scenario has occurred
         */
        static const unsigned short OPENGL_ENGINE_ERROR_UNKNOWN       = 4;
        // note to developers: if more error codes are added, need to update LAST accordingly or
        // update UNKNOWN to the last value and shift
        /**
         * @brief stores the error code number of the last possible error, this corresponds to the
         * max error code value.
         */
        static const unsigned short OPENGL_ENGINE_ERROR_LAST          = OPENGL_ENGINE_ERROR_UNKNOWN;
        /**
         * @brief stores the number of unique error codes that can be generated
         */
        [[maybe_unused]] static const unsigned short OPENGL_ENGINE_ERROR_SIZE          = OPENGL_ENGINE_ERROR_LAST + 1;

    protected:
        /**
         * @brief initializes our OpenGL Engine by setting the OpenGL context and GLFW window parameters
         * @param OPENGL_MAJOR_VERSION OpenGL Major version to request context of (for example 4.X)
         * @param OPENGL_MINOR_VERSION OpenGL Minor version to request context of (for example X.1)
         * @param WINDOW_WIDTH width of window to request creation of
         * @param WINDOW_HEIGHT height of window to request creation of
         * @param WINDOW_TITLE title to place on window bar
         * @param WINDOW_RESIZABLE if window should be resizable or not (defaults to false)
         * @note does not actually create the context nor the window at this time.  To do so, call the
         * initialize() method after the object has been created
         */
        OpenGLEngine(int OPENGL_MAJOR_VERSION, int OPENGL_MINOR_VERSION, int WINDOW_WIDTH, int WINDOW_HEIGHT, const char* WINDOW_TITLE, bool WINDOW_RESIZABLE = GLFW_FALSE);
        /**
         * @brief cleans up our OpenGL Engine by destroying the OpenGL context, GLFW window, and cleaning up
         * all GPU resources
         */
        virtual ~OpenGLEngine();

        /**
         * @brief if information should be printed to console while running
         * @note defaults to true
         */
        bool DEBUG;

        /**
         * @brief tracks the current status of the OpenGL engine via error codes
         */
        unsigned int mErrorCode;

        /**
         * @brief the major version of the requested OpenGL context
         * @note may not correspond to the actual OpenGL context created
         */
        int mOpenGLMajorVersion;
        /**
         * @brief the minor version of the requested OpenGL context
         * @note may not correspond to the actual OpenGL context created
         */
        int mOpenGLMinorVersion;
        /**
         * @brief the window width of the requested GLFW window
         * @note may not correspond to the actual GLFW window created
         */
        int mWindowWidth;
        /**
         * @brief the window height of the requested GLFW window
         * @note may not correspond to the actual GLFW window created
         */
        int mWindowHeight;
        /**
         * @brief if the GLFW window can be resized while open
         * @note by default false
         */
        bool mWindowResizable;
        /**
         * @brief the title of the GLFW window
         */
        char* mWindowTitle;
        /**
         * @brief pointer to the GLFW window object
         */
        GLFWwindow *mpWindow;

        /**
         * @brief We will register this function as GLFW's error callback.
         *	When an error within OpenGL occurs, GLFW will tell us by calling
         *	this function.  We can then print this info to the terminal to
         *	alert the user.
         */
        static void mErrorCallback(int error, const char* DESCRIPTION) { fprintf(stderr, "[ERROR]: %d\n\t%s\n", error, DESCRIPTION ); }

        /**
         * callback called when GLFW pWindow is resized.  internally updated mWindowWidth and
         * mWindowHeight to new values
         * @param pWindow pointer to the window that was resized
         * @param width new width of the window
         * @param height new height of the window
         */
        static void mWindowResizeCallback(GLFWwindow* pWindow, int width, int height);

        /**
         * @brief Used to setup everything GLFW related.  This includes the OpenGL context
         * and our window.<br><br>
         * By default, completes the following steps in order:<br>
         *  - sets error callback<br>
         *  - initializes GLFW<br>
         *  - sets window hints for OpenGL MAJOR.minor<br>
         *  - requests Core Profile<br>
         *  - requests double buffering<br>
         *  - marks window as resizable or not based on constructor creation<br>
         *  - creates a window<br>
         *  - makes the window the current context<br>
         *  - sets the swap interval to 1
         * @note This method should be overridden if any additional callbacks need to be registered.
         * When registering additional callbacks, the parent implementation must be called first and
         * then the additional callbacks may be registered as desired.
         * @note If overridden, then it is likely that mCleanupGLFW should be overridden as well
         * @note Sets mErrorCode if process does not complete successfully
         */
        virtual void mSetupGLFW();
        /**
         * @brief override to enable specific OpenGL features
         * @note called after GLFW window is created and OpenGL context is created and prior to any
         * other shader, buffer, texture, or scene setup has been performed
         * @note If overridden, then it is likely that mCleanupOpenGL should be overridden as well
         */
        virtual void mSetupOpenGL() = 0;
        /**
         * @brief override to register any shaders with the GPU
         * @note called after OpenGL features are setup and prior to buffers, textures, or scene setup
         * has been performed
         * @note If overridden, then it is likely that mCleanupShaders should be overridden as well
         */
        virtual void mSetupShaders() {};
        /**
         * @brief override to register any buffer objects with the GPU
         * @note called after shaders are setup and prior to textures or scene setup has been performed
         * @note If overridden, then it is likely that mCleanupBuffers should be overridden as well
         */
        virtual void mSetupBuffers() {};
        /**
         * @brief override to register any textures with the GPU
         * @note called after buffer objects are setup and prior to scene setup has been performed
         * @note If overridden, then it is likely that mCleanupTextures should be overridden as well
         */
        virtual void mSetupTextures() {}
        /**
         * @brief override to setup any scene specific information
         * @note final setup method to be called
         * @note If overridden, then it is likely that mCleanupScene should be overridden as well
         */
        virtual void mSetupScene() {};

        /**
         * @brief override to cleanup any scene specific information
         * @note first cleanup method to be called
         */
        virtual void mCleanupScene() {};
        /**
         * @brief override to cleanup any textures from the GPU
         * @note called after scene cleanup and prior to any other cleanup processes
         */
        virtual void mCleanupTextures() {}
        /**
         * @brief override to cleanup any buffer objects from the GPU
         * @note called after textures have been cleaned up and prior to shaders, OpenGL, or GLFW being cleaned
         */
        virtual void mCleanupBuffers() {};
        /**
         * @brief override to cleanup any shaders from the GPU
         * @note called after buffer objects have been cleaned up and prior to OpenGL or GLFW being cleaned
         */
        virtual void mCleanupShaders() {};
        /**
         * @brief override to cleanup any specific OpenGL features
         * @note called after shaders have been cleaned and prior to GLFW being cleaned
         */
        virtual void mCleanupOpenGL() {};
        /**
        * @brief Destroys the associated GLFW window and terminates the GLFW instance
        * @warning If this method is overridden, then the parent implementation must
        * be called last as part of the derived implementation
        * @note final cleanup method to be called
        */
        virtual void mCleanupGLFW();

    private:
        void _setupGLEW();                  // initialize GLEW
        void _cleanupGLEW() {}              // nothing to be done at this time

        bool _isInitialized;                // makes initialization a singleton process
        bool _isCleanedUp;                  // makes cleanup a singleton process
    };
}

inline CSCI441::OpenGLEngine::OpenGLEngine(const int OPENGL_MAJOR_VERSION, const int OPENGL_MINOR_VERSION, const int WINDOW_WIDTH, const int WINDOW_HEIGHT, const char* WINDOW_TITLE, const bool WINDOW_RESIZABLE)
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
        mSetupGLFW();                   // initialize GLFW and set up a window
        _setupGLEW();                   // create OpenGL extensions
        mSetupOpenGL();                 // create the OpenGL context

        // get OpenGL context information
        if (DEBUG) CSCI441::OpenGLUtils::printOpenGLInfo();

        mSetupShaders();                // transfer, compile, link shaders on GPU
        mSetupBuffers();                // register Buffers on GPU
        mSetupTextures();               // register Textures on GPU
        mSetupScene();                  // setup any scene specific information

        _isInitialized = true;
        _isCleanedUp = false;
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

inline void CSCI441::OpenGLEngine::_setupGLEW() {
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
        _cleanupGLEW();                                     // cleanup anything GLEW related
        mCleanupGLFW();                                     // shut down GLFW to clean up our context
        if (DEBUG) fprintf(stdout, "[INFO]: ..shut down complete!\n");
        _isCleanedUp = true;
        _isInitialized = false;
    }
}

inline void CSCI441::OpenGLEngine::mWindowResizeCallback(GLFWwindow* pWindow, int width, int height) {
    auto pEngine = (OpenGLEngine*) glfwGetWindowUserPointer(pWindow);
    pEngine->setCurrentWindowSize(width, height);
}

#endif //CSCI441_OPENGL_ENGINE_HPP
