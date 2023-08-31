#ifndef CSCI441_MD5_CAMERA_HPP
#define CSCI441_MD5_CAMERA_HPP

#include "Camera.hpp"

#include <ctime>
#include <fstream>
#include <string>

namespace CSCI441 {

    /**
     * @brief A camera that implements the MD5Camera specification
     * @note camera direction is controlled by file contents
     */
    class MD5Camera final : public CSCI441::Camera {
    public:
        /**
         * creates a MD5Camera object with the specified initial perspective projection
         * @param MD5CAMERA_FILE filename of .md5camera file to load
         * @param fovy vertical field of view (defaults to 45.0f)
         * @param aspectRatio aspect ratio of view plane (defaults to 1.0f)
         * @param nearClipPlane near z clip plane (defaults to 0.001f)
         * @param farClipPlane far z clip plane (defaults to 1000.0f)
         * @param INFO if file loading information should be printed to standard out (defaults to true)
         * @param ERRORS if file loading errors should be printed to standard error (defaults to true)
         * @note field of view specified in degrees
         */
        MD5Camera(const char* MD5CAMERA_FILE, GLfloat fovy = 45.0f, GLfloat aspectRatio = 1.0f, GLfloat nearClipPlane = 0.001f, GLfloat farClipPlane = 1000.0f, GLboolean INFO = true, GLboolean ERRORS = true);

        void recomputeOrientation() final {}
        void moveForward(GLfloat unused) final;
        void moveBackward(GLfloat unused) final;

    private:
        bool _loadMD5CameraFromFile(const char * MD5CAMERA_FILE, GLboolean INFO = true, GLboolean ERRORS = true);

        struct Frame {
            glm::vec3 cameraPosition;
            glm::vec3 cameraQuaternion;
            GLfloat fieldOfView;
        };

        GLuint _frameRate;
        GLuint _numFrames;
        GLuint _numCuts;
        GLuint* _cutPositions;
        Frame* _frames;
        GLuint _currentFrameIndex;
        GLuint _currentCutIndex;

        void _updateCameraAttributesForCurrentFrame();

        // vertical field of view stored in degrees
        GLfloat _fovy;
        GLfloat _aspectRatio;
        GLfloat _nearClipPlane;
        GLfloat _farClipPlane;
    };
}

inline CSCI441::MD5Camera::MD5Camera(
        const char * const MD5CAMERA_FILE,
        const GLfloat fovy,
        const GLfloat aspectRatio,
        const GLfloat nearClipPlane,
        const GLfloat farClipPlane,
        const GLboolean INFO,
        const GLboolean ERRORS
) : _fovy(fovy),
    _aspectRatio(aspectRatio),
    _nearClipPlane(nearClipPlane),
    _farClipPlane(farClipPlane)
{
    _currentFrameIndex = 0;
    _currentCutIndex = 0;
    mProjectionMatrix = glm::perspective(_fovy, _aspectRatio, _nearClipPlane, _farClipPlane);

    _loadMD5CameraFromFile(MD5CAMERA_FILE, INFO, ERRORS);
}

inline bool CSCI441::MD5Camera::_loadMD5CameraFromFile(
        const char * const MD5CAMERA_FILE,
        const GLboolean INFO,
        const GLboolean ERRORS
) {
    if ( INFO ) fprintf( stdout, "[.md5camera]: -=-=-=-=-=-=-=- BEGIN %s Info -=-=-=-=-=-=-=- \n", MD5CAMERA_FILE );

    time_t start, end;
    time(&start);

    std::ifstream md5CameraFile(MD5CAMERA_FILE);
    if( !md5CameraFile.is_open() ) {
        if (ERRORS) fprintf( stderr, "[.md5camera]: [ERROR]: Could not open \"%s\"\n", MD5CAMERA_FILE );
        if ( INFO ) fprintf( stdout, "[.md5camera]: -=-=-=-=-=-=-=-  END  %s Info -=-=-=-=-=-=-=- \n", MD5CAMERA_FILE );
        return false;
    }

    std::string sectionLabel, commandLineStr;

    // MD5Version 10
    int md5version;
    md5CameraFile >> sectionLabel >> md5version;
    if(sectionLabel != "MD5Version" || md5version != 10) {
        if (ERRORS) fprintf(stderr, "[.md5camera]: [ERROR]: improper MD5Camera version found \"%s %d\"\n", sectionLabel.c_str(), md5version );
        if ( INFO ) fprintf( stdout, "[.md5camera]: -=-=-=-=-=-=-=-  END  %s Info -=-=-=-=-=-=-=- \n", MD5CAMERA_FILE );
        return false;
    }

    // commandline "string"
    md5CameraFile >> sectionLabel;
    getline(md5CameraFile, commandLineStr);

    // numFrames <integer>
    md5CameraFile >> sectionLabel >> _numFrames;
    // frameRate <integer>
    md5CameraFile >> sectionLabel >> _frameRate;
    // numCuts <integer>
    md5CameraFile >> sectionLabel >> _numCuts;

    // TODO sections
    // cuts {
    //   [frameNumber]
    //   [frameNumber]
    // }

    // camera {
    //   ( [x] [y] [z] ) ( [orientation] ) [FOV]
    // }

    if (INFO) {
        printf( "[.md5camera]: Camera Stats:\n" );
        printf( "[.md5camera]: Num Frames:\t%u\n", _numFrames );
        printf( "[.md5camera]: Frame Rate:\t%u\n", _frameRate );
        printf( "[.md5camera]: Num Cuts:  \t%u\n", _numCuts );
    }

    time(&end);
    double seconds = difftime( end, start );

    if (INFO) {
        printf( "[.md5camera]: Completed in %.3fs\n", seconds );
        printf( "[.md5camera]: -=-=-=-=-=-=-=-  END %s Info  -=-=-=-=-=-=-=- \n\n", MD5CAMERA_FILE );
    }

    return true;
}

inline void CSCI441::MD5Camera::moveForward(const GLfloat unused) {
    // advance to next frame
    _currentFrameIndex++;
    // TODO clamp to current cut ? loop ? advance ?
    _updateCameraAttributesForCurrentFrame();
}

inline void CSCI441::MD5Camera::moveBackward(const GLfloat unused) {
    // go to prior frame
    _currentFrameIndex--;
    // TODO clamp to current cut ?
    _updateCameraAttributesForCurrentFrame();
}

inline void CSCI441::MD5Camera::_updateCameraAttributesForCurrentFrame() {
    // get and set camera position for current frame
    setPosition( _frames[_currentFrameIndex].cameraPosition );

    // get and set camera orientation for current frame
    // TODO compute W of quarternion
    // TODO set look at point
    // TODO set up vector

    // get and set field of view for perspective projection matrix
    _fovy = _frames[_currentFrameIndex].fieldOfView;
    mProjectionMatrix = glm::perspective(_fovy, _aspectRatio, _nearClipPlane, _farClipPlane);
}

#endif//CSCI441_MD5_CAMERA_HPP