#ifndef CSCI441_ORTHOGRAPHIC_CAMERA_HPP
#define CSCI441_ORTHOGRAPHIC_CAMERA_HPP

#include "Camera.hpp"

namespace CSCI441 {

    class OrthographicCamera : public CSCI441::Camera {
    public:
        /**
         * @brief initializes the OrthographicCamera
         * @param minX left clipping plane (defaults to -1.0f)
         * @param maxX right clipping plane (defaults to +1.0f)
         * @param minY bottom clipping plane (defaults to -1.0f)
         * @param maxY top clipping plane (defaults to +1.0f)
         * @param minZ near clipping plane (defaults to -1.0f)
         * @param maxZ far clipping plane (defaults to +1.0f)
         */
        [[maybe_unused]] explicit OrthographicCamera(GLfloat minX = -1.0f, GLfloat maxX = 1.0f, GLfloat minY = -1.0f, GLfloat maxY = 1.0f, GLfloat minZ = -1.0f, GLfloat maxZ = 1.0f);

    private:
        void _updateProjectionMatrix();

        GLfloat _minX;
        GLfloat _maxX;
        GLfloat _minY;
        GLfloat _maxY;
        GLfloat _minZ;
        GLfloat _maxZ;
    };

}

[[maybe_unused]]
inline CSCI441::OrthographicCamera::OrthographicCamera(
        GLfloat minX,
        GLfloat maxX,
        GLfloat minY,
        GLfloat maxY,
        GLfloat minZ,
        GLfloat maxZ
) : _minX(minX), _maxX(maxX), _minY(minY), _maxY(maxY), _minZ(minZ), _maxZ(maxZ) {
    _updateProjectionMatrix();
}

void CSCI441::OrthographicCamera::_updateProjectionMatrix() {
    mProjectionMatrix = glm::ortho( _minX, _maxX, _minY, _maxY, _minZ, _maxZ );
}

#endif//CSCI441_ORTHOGRAPHIC_CAMERA_HPP