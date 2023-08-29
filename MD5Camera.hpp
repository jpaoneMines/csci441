#ifndef CSCI441_MD5_CAMERA_HPP
#define CSCI441_MD5_CAMERA_HPP

#include "Camera.hpp"

namespace CSCI441 {

    class MD5Camera final : public CSCI441::Camera {
    public:
        MD5Camera(const char* MD5CAMERA_FILE);

        void recomputeOrientation() final {}
        void moveForward(GLfloat unused) final;
        void moveBackward(GLfloat unused) final;

    private:
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

        void _updateCameraPositionForCurrentFrame();
    };
}

inline CSCI441::MD5Camera::MD5Camera(const char *MD5CAMERA_FILE) {
    _currentFrameIndex = 0;
    _currentCutIndex = 0;
}

inline void CSCI441::MD5Camera::moveForward(const GLfloat unused) {
    // advance to next frame
    _currentFrameIndex++;
    // TODO clamp to current cut ? loop ? advance ?
    _updateCameraPositionForCurrentFrame();
}

inline void CSCI441::MD5Camera::moveBackward(const GLfloat unused) {
    // go to prior frame
    _currentFrameIndex--;
    // TODO clamp to current cut ?
    _updateCameraPositionForCurrentFrame();
}

inline void CSCI441::MD5Camera::_updateCameraPositionForCurrentFrame() {
    setPosition( _frames[_currentFrameIndex].cameraPosition );
    // TODO set look at point
    // TODO set up vector
}

#endif//CSCI441_MD5_CAMERA_HPP