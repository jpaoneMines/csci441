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
         * @note must create camera object from parameterized constructor
         */
        MD5Camera() = delete;

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
        explicit MD5Camera(const char* MD5CAMERA_FILE, GLfloat fovy = 45.0f, GLfloat aspectRatio = 1.0f, GLfloat nearClipPlane = 0.001f, GLfloat farClipPlane = 1000.0f, GLboolean INFO = true, GLboolean ERRORS = true);

        ~MD5Camera() final;

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
    _farClipPlane(farClipPlane),
    _frameRate(60),
    _numFrames(0),
    _numCuts(0),
    _cutPositions(nullptr),
    _frames(nullptr),
    _currentFrameIndex(0),
    _currentCutIndex(0)
{
    _currentFrameIndex = 0;
    _currentCutIndex = 0;
    mProjectionMatrix = glm::perspective(_fovy, _aspectRatio, _nearClipPlane, _farClipPlane);

    _loadMD5CameraFromFile(MD5CAMERA_FILE, INFO, ERRORS);
}

inline CSCI441::MD5Camera::~MD5Camera() {
    free( _frames );
    free( _cutPositions );
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

    std::string sectionLabel, commandLineStr, brace;
    int md5version;
    Frame frame = { glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(0.0f, 0.0f, 0.0f), 45.0f };

    // MD5Version 10
    md5CameraFile >> sectionLabel >> md5version;
    if(sectionLabel != "MD5Version" || md5version != 10) {
        if (ERRORS) fprintf (stderr, "[.md5camera]: [ERROR]: improper MD5Camera version found \"%s %d\"\n", sectionLabel.c_str(), md5version );
        if ( INFO ) fprintf( stdout, "[.md5camera]: -=-=-=-=-=-=-=-  END  %s Info -=-=-=-=-=-=-=- \n", MD5CAMERA_FILE );
        return false;
    }

    // commandline "string"
    md5CameraFile >> sectionLabel;
    getline(md5CameraFile, commandLineStr);

    for(unsigned short i = 0; i < 5; i++) {
        md5CameraFile >> sectionLabel;
        if(sectionLabel == "numFrames") {
             // numFrames <integer>
             md5CameraFile >> _numFrames;
            _frames = (Frame*)malloc(sizeof(Frame) * _numFrames);
        } else if(sectionLabel == "frameRate") {
            // frameRate <integer>
            md5CameraFile >> sectionLabel >> _frameRate;
        } else if(sectionLabel == "numCuts") {
            // numCuts <integer>
            md5CameraFile >> sectionLabel >> _numCuts;
            _cutPositions = (GLuint*)malloc(sizeof(GLuint) * _numCuts);
        } else if(sectionLabel == "cuts") {
            // cuts {
            //   [frameNumber]
            //   [frameNumber]
            // }
            md5CameraFile >> brace;
            for(unsigned int cutNumber = 0; cutNumber < _numCuts; cutNumber++) {
                md5CameraFile >> _cutPositions[cutNumber];
            }
            md5CameraFile >> brace;
            _currentFrameIndex = _cutPositions[_currentCutIndex];
        } else if(sectionLabel == "camera") {
            // camera {
            //   ( [x] [y] [z] ) ( [orientation] ) [FOV]
            // }
            md5CameraFile >> brace;
            for(unsigned int frameNumber = 0; frameNumber < _numFrames; frameNumber++) {
                md5CameraFile >> brace >> frame.cameraPosition.x >> frame.cameraPosition.y >> frame.cameraPosition.z >> brace;
                md5CameraFile >> brace >> frame.cameraQuaternion.x >> frame.cameraQuaternion.y >> frame.cameraQuaternion.z >> brace;
                md5CameraFile >> frame.fieldOfView;
            }
            md5CameraFile >> brace;
        } else {
            if (ERRORS) fprintf( stderr, "[.md5camera]: [ERROR]: unknown section label found \"%s\"\n", sectionLabel.c_str() );
            if ( INFO ) fprintf( stdout, "[.md5camera]: -=-=-=-=-=-=-=-  END  %s Info -=-=-=-=-=-=-=- \n", MD5CAMERA_FILE );
            return false;
        }
    }

    if (INFO) {
        printf( "[.md5camera]: Camera Stats:\n" );
        printf( "[.md5camera]: Num Frames:\t%u\tFrame Rate:\t%u\tNum Cuts:  \t%u\n", _numFrames, _frameRate, _numCuts );
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
    // TODO clamp to current cut ? loop ? unadvance ?
    _updateCameraAttributesForCurrentFrame();
}

inline void CSCI441::MD5Camera::_updateCameraAttributesForCurrentFrame() {
    // get and set camera position for current frame
    mCameraPosition = _frames[_currentFrameIndex].cameraPosition;

    // get and set camera orientation for current frame
    // compute W of quaternion
    glm::vec4 q(_frames[_currentFrameIndex].cameraQuaternion, 0.0f);
    GLfloat t = 1.0f - (q.x * q.x) - (q.y * q.y) - (q.z * q.z);
    if (t < 0.0f)
        q.w = 0.0f;
    else
        q.w = -glm::sqrt(t);

    // set direction and look at point
    glm::vec3 defaultCameraDirection(0.0f, 0.0f, -1.0f);
    glm::vec4 inverse(-q.x, -q.y, -q.z, q.w);
    glm::normalize(inverse);

    glm::vec4 tmp( (q.w * defaultCameraDirection.x) + (q.y * defaultCameraDirection.z) - (q.z * defaultCameraDirection.y),
                   (q.w * defaultCameraDirection.y) + (q.z * defaultCameraDirection.x) - (q.x * defaultCameraDirection.z),
                   (q.w * defaultCameraDirection.z) + (q.x * defaultCameraDirection.y) - (q.y * defaultCameraDirection.x),
                   -(q.w * defaultCameraDirection.x) - (q.y * defaultCameraDirection.y) - (q.z * defaultCameraDirection.z) );
    glm::vec4 rotatedCameraDirection( (tmp.x * inverse.w) + (tmp.w * inverse.x) + (tmp.y * inverse.z) - (tmp.z * inverse.y),
                                      (tmp.y * inverse.w) + (tmp.w * inverse.y) + (tmp.z * inverse.x) - (tmp.x * inverse.z),
                                      (tmp.z * inverse.w) + (tmp.w * inverse.z) + (tmp.x * inverse.y) - (tmp.y * inverse.x),
                                      (tmp.w * inverse.w) - (tmp.x * inverse.x) - (tmp.y * inverse.y) - (tmp.z * inverse.z) );
    mCameraDirection = glm::vec3( rotatedCameraDirection.x, rotatedCameraDirection.y, rotatedCameraDirection.z );
    mCameraLookAtPoint = mCameraPosition + mCameraDirection;

    // set up vector
    glm::vec3 defaultCameraUpVector(0.0f, 1.0f, 0.0f);
    glm::vec4 tmp2( (q.w * defaultCameraUpVector.x) + (q.y * defaultCameraUpVector.z) - (q.z * defaultCameraUpVector.y),
                    (q.w * defaultCameraUpVector.y) + (q.z * defaultCameraUpVector.x) - (q.x * defaultCameraUpVector.z),
                    (q.w * defaultCameraUpVector.z) + (q.x * defaultCameraUpVector.y) - (q.y * defaultCameraUpVector.x),
                    -(q.w * defaultCameraUpVector.x) - (q.y * defaultCameraUpVector.y) - (q.z * defaultCameraUpVector.z) );
    glm::vec4 rotatedCameraUpVector(  (tmp.x * inverse.w) + (tmp.w * inverse.x) + (tmp.y * inverse.z) - (tmp.z * inverse.y),
                                      (tmp.y * inverse.w) + (tmp.w * inverse.y) + (tmp.z * inverse.x) - (tmp.x * inverse.z),
                                      (tmp.z * inverse.w) + (tmp.w * inverse.z) + (tmp.x * inverse.y) - (tmp.y * inverse.x),
                                      (tmp.w * inverse.w) - (tmp.x * inverse.x) - (tmp.y * inverse.y) - (tmp.z * inverse.z) );
    mCameraUpVector = glm::vec3(rotatedCameraUpVector.x, rotatedCameraUpVector.y, rotatedCameraUpVector.z);

    // compute and set view matrix
    computeViewMatrix();

    // get and set field of view for perspective projection matrix
    _fovy = _frames[_currentFrameIndex].fieldOfView;
    mProjectionMatrix = glm::perspective(_fovy, _aspectRatio, _nearClipPlane, _farClipPlane);
}

#endif//CSCI441_MD5_CAMERA_HPP