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

#include "constants.h"
#include "OpenGLUtils.hpp"

#ifdef CSCI441_USE_GLEW
    #include <GL/glew.h>
#else
    #include <glad/gl.h>
#endif

#include <GLFW/glfw3.h>

#include <cstdio>
#include <cstring>
#include <ctime>
#include <set>
#include <string>
#include <memory>

#include <stb_image_write.h>

namespace CSCI441 {

    /**
     * @class OpenGLEngine
     * @brief Abstract Class to run an OpenGL application.  The following methods
     * must be overridden:<br>
     *  - mSetupOpenGL()<br>
     *  - run()<br>
     */
    class OpenGLEngine {
    public:
        /**
         * @brief do not allow engines to be copied
         */
        OpenGLEngine(const OpenGLEngine&) = delete;
        /**
        * @brief do not allow engines to be copied
        */
        OpenGLEngine& operator=(const OpenGLEngine&) = delete;

        /**
         * @brief construct a new engine by moving an existing one
         */
        OpenGLEngine(OpenGLEngine&&) noexcept;
        /**
         * @brief assign this engine by moving an existing one
         * @return our newly assigned engine
         */
        OpenGLEngine& operator=(OpenGLEngine&&) noexcept;

        /**
         * @brief cleans up our OpenGL Engine by destroying the OpenGL context, GLFW window, and cleaning up
         * all GPU resources
         */
        virtual ~OpenGLEngine();

        /**
         * @brief Initialize everything needed for OpenGL Rendering.  This includes
         * in order: GLFW, function pointers, OpenGL, Shader Programs, Buffer Objects,
         * Textures, and any Scene information
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
         * Shader Programs, OpenGL, function pointers, GLFW
         * @warning If this method is overridden, then the parent implementation must
         * be called last as part of the derived implementation
         */
        virtual void shutdown();

        /**
         * @brief Save a PNG screenshot of the viewport
         */
        [[maybe_unused]] virtual bool saveScreenshot(const char* FILENAME = nullptr) noexcept final;

        /**
         * @brief Enable logging to command line
         * @note Enabled by default
         */
        [[maybe_unused]] virtual void turnDebuggingOn() noexcept final { DEBUG = true; }
        /**
         * @brief Disable logging to command line
         * @note Enabled by default
         */
        virtual void turnDebuggingOff() noexcept final { DEBUG = false; }
        /**
         * @brief Returns if logging is enabled
         */
        [[maybe_unused]] [[nodiscard]] virtual bool isDebuggingEnabled() const noexcept final { return DEBUG; }

        /**
         * @brief Returns if OpenGL extension exists
         * @param EXT name of extension
         * @return true if extension exists, false otherwise
         */
        [[maybe_unused]] [[nodiscard]] virtual bool isExtensionEnabled(const std::string EXT) const noexcept final { return _extensions.find(EXT) != _extensions.end(); }

        /**
         * @brief Set the new window size
         * @param WINDOW_WIDTH width of the new window
         * @param WINDOW_HEIGHT height of the new window
         * @warning This function does not cause the window to be resized, rather after the window
         * has been resized this function is used to update the data members storing the current
         * window size.
         */
        virtual void setCurrentWindowSize(const int WINDOW_WIDTH, const int WINDOW_HEIGHT) final { mWindowWidth = WINDOW_WIDTH; mWindowHeight = WINDOW_HEIGHT; }
        /**
         * @brief Return the height of the window
         */
        [[maybe_unused]] [[nodiscard]] virtual int getWindowHeight() const noexcept final { return mWindowHeight; }
        /**
         * @brief Return the width of the window
         */
        [[maybe_unused]] [[nodiscard]] virtual int getWindowWidth() const noexcept final { return mWindowWidth; }
        /**
         * @brief Return the window object
         */
        [[maybe_unused]] [[nodiscard]] virtual GLFWwindow* getWindow() const noexcept final { return mpWindow; }

        /**
         * @brief Tell our engine's window to close
         */
        [[maybe_unused]] virtual void setWindowShouldClose() final { glfwSetWindowShouldClose(mpWindow, GLFW_TRUE); }

        /**
         * @brief Return current value of error code and clear the error code back to no error
         */
        [[nodiscard]] virtual unsigned short getError() noexcept final {
            const unsigned short storedErrorCode = mErrorCode;  // store current error code
            mErrorCode = OPENGL_ENGINE_ERROR_NO_ERROR;  // reset error code
            return storedErrorCode;                     // return previously stored error code
        }

        /**
         * @brief no error is present, everything is currently working
         */
        static constexpr unsigned short OPENGL_ENGINE_ERROR_NO_ERROR            = 0;
        /**
         * @brief an error occurred while initializing GLFW
         */
        static constexpr unsigned short OPENGL_ENGINE_ERROR_GLFW_INIT           = 1;
        /**
         * @brief an error occurred while creating the GLFW window
         */
        static constexpr unsigned short OPENGL_ENGINE_ERROR_GLFW_WINDOW         = 2;
        /**
         * @brief an error occurred while initializing GLEW
         */
        static constexpr unsigned short OPENGL_ENGINE_ERROR_GLEW_INIT           = 3;
        /**
         * @brief an error occurred while initializing GLAD
         */
        static constexpr unsigned short OPENGL_ENGINE_ERROR_GLAD_INIT           = 4;
        /**
         * @brief an error occurred while taking a screenshot
         */
        static constexpr unsigned short OPENGL_ENGINE_ERROR_TAKE_SCREENSHOT     = 5;
        /**
         * @brief a new error that does not correspond to a predefined scenario has occurred
         */
        static constexpr unsigned short OPENGL_ENGINE_ERROR_UNKNOWN             = 6;
        // note to developers: if more error codes are added, need to update LAST accordingly or
        // update UNKNOWN to the last value and shift
        /**
         * @brief stores the error code number of the last possible error, this corresponds to the
         * max error code value.
         */
        static constexpr unsigned short OPENGL_ENGINE_ERROR_LAST                = OPENGL_ENGINE_ERROR_UNKNOWN;
        /**
         * @brief stores the number of unique error codes that can be generated
         */
        [[maybe_unused]] static constexpr unsigned short OPENGL_ENGINE_ERROR_SIZE          = OPENGL_ENGINE_ERROR_LAST + 1;

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
        GLFWwindow* mpWindow;

        /**
         * @brief We will register this function as GLFW's error callback.
         *	When an error within OpenGL occurs, GLFW will tell us by calling
         *	this function.  We can then print this info to the terminal to
         *	alert the user.
         */
        static void mErrorCallback(const int error, const char* DESCRIPTION) { fprintf(stderr, "[ERROR]: %d\n\t%s\n", error, DESCRIPTION ); }

        /**
         * @brief callback called whenever a debug message is signaled
         */
        static void APIENTRY mDebugMessageCallback(const GLenum source, const GLenum type, const GLuint id, const GLenum severity, const GLsizei length, const GLchar* message, const void* userParam) {
            fprintf( stdout, "[VERBOSE]: Debug Message (%d): source = %s, type = %s, severity = %s, message = %s\n",
                     id,
                     CSCI441::OpenGLUtils::debugSourceToString(source),
                     CSCI441::OpenGLUtils::debugTypeToString(type),
                     CSCI441::OpenGLUtils::debugSeverityToString(severity),
                     message
                     );
        }

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

        /**
         *  @brief calls mCleanupShaders() followed by mSetupShaders() to reload
         *  shader source code from file
         */
        virtual void mReloadShaders() final;

    private:
        void _setupGLFunctions();           // initialize OpenGL functions
        void _cleanupGLFunctions() {}       // nothing to be done at this time

        void _cleanupSelf();                // delete internal memory
        void _moveFromSource(OpenGLEngine&);// move members from another instance

        bool _isInitialized;                // makes initialization a singleton process
        bool _isCleanedUp;                  // makes cleanup a singleton process

        std::set< std::string > _extensions;// set of all available OpenGL extensions
    };
}

inline CSCI441::OpenGLEngine::OpenGLEngine(
    const int OPENGL_MAJOR_VERSION,
    const int OPENGL_MINOR_VERSION,
    const int WINDOW_WIDTH,
    const int WINDOW_HEIGHT,
    const char* WINDOW_TITLE,
    const bool WINDOW_RESIZABLE
) : DEBUG(true),
    mErrorCode(OPENGL_ENGINE_ERROR_NO_ERROR),
    mOpenGLMajorVersion(OPENGL_MAJOR_VERSION),
    mOpenGLMinorVersion(OPENGL_MINOR_VERSION),
    mWindowWidth(WINDOW_WIDTH),
    mWindowHeight(WINDOW_HEIGHT),
    mWindowResizable(WINDOW_RESIZABLE),
    mWindowTitle(nullptr),
    mpWindow(nullptr),
    _isInitialized(false),
    _isCleanedUp(false)
{
    mWindowTitle = new char[ strlen(WINDOW_TITLE) ];
    strcpy(mWindowTitle, WINDOW_TITLE);
}

inline CSCI441::OpenGLEngine::OpenGLEngine(
    CSCI441::OpenGLEngine&& src
) noexcept :
    DEBUG(true),
    mErrorCode(OPENGL_ENGINE_ERROR_NO_ERROR),
    mOpenGLMajorVersion(0),
    mOpenGLMinorVersion(0),
    mWindowWidth(0),
    mWindowHeight(0),
    mWindowResizable(false),
    mWindowTitle(nullptr),
    mpWindow(nullptr),
    _isInitialized(false),
    _isCleanedUp(false)
{
    _moveFromSource(src);
}

inline CSCI441::OpenGLEngine& CSCI441::OpenGLEngine::operator=(OpenGLEngine&& src) noexcept {
    if (this != &src) {
        _cleanupSelf();
        _moveFromSource(src);
    }
    return *this;
}


inline CSCI441::OpenGLEngine::~OpenGLEngine() {
    _cleanupSelf();
}

inline void CSCI441::OpenGLEngine::_cleanupSelf() {
    delete[] mWindowTitle;
    mWindowTitle = nullptr;
}

inline void CSCI441::OpenGLEngine::_moveFromSource(OpenGLEngine& src) {
    DEBUG = src.DEBUG;
    src.DEBUG = false;

    mErrorCode = src.mErrorCode;
    src.mErrorCode = OPENGL_ENGINE_ERROR_NO_ERROR;

    mOpenGLMajorVersion = src.mOpenGLMajorVersion;
    src.mOpenGLMajorVersion = 0;

    mOpenGLMinorVersion = src.mOpenGLMinorVersion;
    src.mOpenGLMinorVersion = 0;

    mWindowWidth = src.mWindowWidth;
    src.mWindowWidth = 0;

    mWindowHeight = src.mWindowHeight;
    src.mWindowHeight = 0;

    mWindowResizable = src.mWindowResizable;
    src.mWindowResizable = false;

    mWindowTitle = src.mWindowTitle;
    src.mWindowTitle = nullptr;

    mpWindow = src.mpWindow;
    src.mpWindow = nullptr;

    _isInitialized = src._isInitialized;
    src._isInitialized = false;

    _isCleanedUp = src._isCleanedUp;
    src._isCleanedUp = false;

    _extensions = std::move(src._extensions);
}

inline void CSCI441::OpenGLEngine::initialize() {
    if( !_isInitialized ) {
        if (DEBUG) {
            fprintf(stdout, "[INFO]: Using CSCI441 Library v%d.%d.%d\n", CSCI441::VERSION_MAJOR, CSCI441::VERSION_MINOR, CSCI441::VERSION_PATCH);
        }

        mSetupGLFW();                   // initialize GLFW and set up a window
        _setupGLFunctions();            // create OpenGL function pointers
        mSetupOpenGL();                 // create the OpenGL context

        // get OpenGL context information
        if( DEBUG ) {
            // if wanting debug information with Version 4.3 or higher
            if( mOpenGLMajorVersion > 4 || (mOpenGLMajorVersion == 4 && mOpenGLMinorVersion >= 3) ) {
                // check if debug context was created
                int flags; glGetIntegerv(GL_CONTEXT_FLAGS, &flags);
                if (flags & GL_CONTEXT_FLAG_DEBUG_BIT) {
                    // register callback to synchronously print any debug messages without having to call glGetError()
                    glEnable(GL_DEBUG_OUTPUT);
                    glEnable(GL_DEBUG_OUTPUT_SYNCHRONOUS);
                    glDebugMessageCallback(mDebugMessageCallback, nullptr);
                    glDebugMessageControl( GL_DONT_CARE, GL_DONT_CARE, GL_DONT_CARE, 0, nullptr, GL_TRUE );
                }
            }

            CSCI441::OpenGLUtils::printOpenGLInfo();
        }

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
        glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE );                       // request forward compatible OpenGL context
        glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE );             // request OpenGL Core Profile context
        glfwWindowHint(GLFW_DOUBLEBUFFER, GLFW_TRUE );                              // request double buffering
        glfwWindowHint(GLFW_RESIZABLE, mWindowResizable );		                    // set if our window should be able to be resized

        // if wanting debug information with Version 4.3 or higher
        if( DEBUG
            && (mOpenGLMajorVersion > 4 || (mOpenGLMajorVersion == 4 && mOpenGLMinorVersion >= 3)) ) {
            glfwWindowHint(GLFW_OPENGL_DEBUG_CONTEXT, true);                        // request a debug context
        }

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
            glfwSetInputMode(mpWindow, GLFW_LOCK_KEY_MODS, GLFW_TRUE);      // track state of Caps Lock and Num Lock keys
            glfwSetWindowUserPointer(mpWindow, (void*)this);
            glfwSetWindowSizeCallback(mpWindow, mWindowResizeCallback);
        }
    }
}

inline void CSCI441::OpenGLEngine::_setupGLFunctions() {

#ifdef CSCI441_USE_GLEW
    glewExperimental = GL_TRUE;
    const GLenum glewResult = glewInit();                                             // initialize GLEW

    // check for an error
    if( glewResult != GLEW_OK ) {
        fprintf( stderr, "[ERROR]: Error initializing GLEW\n");
        fprintf( stderr, "[ERROR]: %s\n", reinterpret_cast<const char *>(glewGetErrorString(glewResult)) );
        mErrorCode = OPENGL_ENGINE_ERROR_GLEW_INIT;
    } else {
        if(DEBUG) {
            fprintf(stdout, "\n[INFO]: GLEW initialized\n");
            fprintf(stdout, "[INFO]: Using GLEW %s\n", reinterpret_cast<const char *>(glewGetString(GLEW_VERSION)));
        }
    }
#else
    int version = gladLoadGL(glfwGetProcAddress);
    if(version == 0) {
        fprintf(stderr, "Failed to initialize GLAD\n" );
        mErrorCode = OPENGL_ENGINE_ERROR_GLAD_INIT;
    } else {
        if(DEBUG) {
            // Successfully loaded OpenGL
            fprintf(stdout, "\n[INFO]: GLAD initialized\n");
            fprintf(stdout, "[INFO]: Loaded OpenGL %d.%d\n", GLAD_VERSION_MAJOR(version), GLAD_VERSION_MINOR(version));
        }
    }
#endif

    if(mErrorCode == OPENGL_ENGINE_ERROR_NO_ERROR) {
        GLint numExtensions = 0;
        glGetIntegerv(GL_NUM_EXTENSIONS, &numExtensions);
        for (int i = 0; i < numExtensions; i++) {
            _extensions.insert(reinterpret_cast<const char *>(glGetStringi(GL_EXTENSIONS, i)) );
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
        _cleanupGLFunctions();                              // cleanup anything function pointer related
        mCleanupGLFW();                                     // shut down GLFW to clean up our context
        if (DEBUG) fprintf(stdout, "[INFO]: ..shut down complete!\n");
        _isCleanedUp = true;
        _isInitialized = false;
    }
}

inline bool CSCI441::OpenGLEngine::saveScreenshot(const char* FILENAME) noexcept {
    try {
        // Generate a name based on current timestamp if not provided 
        const std::string filename = FILENAME == nullptr 
            ? "Screenshot_" + std::to_string(time(nullptr)) + ".png"
            : FILENAME
        ;

        // Get size
        GLint viewport[4];
        glGetIntegerv(GL_VIEWPORT, viewport);
        const GLsizei x = viewport[0], y = viewport[1], width = viewport[2], height = viewport[3];

        // Read pixel data
        const size_t CHANNELS = 4; // RGBA
        std::unique_ptr<GLubyte> bytes(new GLubyte[width*height*CHANNELS]);
        glReadPixels(x, y, width, height, GL_RGBA, GL_UNSIGNED_BYTE, bytes.get());

        stbi_flip_vertically_on_write(1);

        if(!stbi_write_png(filename.c_str(), width, height, CHANNELS, bytes.get(), width*CHANNELS)) {
            throw 1; // Jump to catch(...) without needing stdexcept
        }
        
        if(DEBUG) {
            fprintf(stdout, "[INFO]: Screenshot saved to %s\n", filename.c_str());
        }
        
        return true;
    } catch(...) {
        fprintf(stderr, "[ERROR]: Could not save screenshot\n");
        mErrorCode = OPENGL_ENGINE_ERROR_TAKE_SCREENSHOT;
        return false;
    }
}

inline void CSCI441::OpenGLEngine::mWindowResizeCallback(GLFWwindow* pWindow, const int width, const int height) {
    const auto pEngine = static_cast<OpenGLEngine *>(glfwGetWindowUserPointer(pWindow));
    pEngine->setCurrentWindowSize(width, height);
}

inline void CSCI441::OpenGLEngine::mReloadShaders() {
    if (DEBUG) fprintf(stdout, "\n[INFO]: Removing old shaders...\n");
    mCleanupShaders();
    if (DEBUG) fprintf(stdout, "\n[INFO]: Reloading shaders...\n");
    mSetupShaders();
    if (DEBUG) fprintf(stdout, "\n[INFO]: Shaders reloaded\n");
}

#endif //CSCI441_OPENGL_ENGINE_HPP
