/**
 * @file OrthographicCamera.hpp
 * @brief Abstract Class to represent an orthographic camera.  Stores box clip planes
 * @author Dr. Jeffrey Paone
 *
 * @copyright MIT License Copyright (c) 2024 Dr. Jeffrey Paone
 *
 * These functions, classes, and constants help minimize common
 * code that needs to be written.
 */

#ifndef CSCI441_ORTHOGRAPHIC_CAMERA_HPP
#define CSCI441_ORTHOGRAPHIC_CAMERA_HPP

#include "Camera.hpp"

namespace CSCI441 {

    /**
     * @brief Abstract Class to represent an orthographic camera.  Stores box clip planes
     */
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
        explicit OrthographicCamera(GLfloat minX = -1.0f, GLfloat maxX = 1.0f, GLfloat minY = -1.0f, GLfloat maxY = 1.0f, GLfloat minZ = -1.0f, GLfloat maxZ = 1.0f);

    protected:
        /**
         * @brief construct a copy an existing camera
         */
        OrthographicCamera(const OrthographicCamera&) = default;
        /**
         * @brief assign a copy of an existing camera
         * @return our newly assigned camera
         */
        OrthographicCamera& operator=(const OrthographicCamera&) = default;

        /**
         * @brief construct a camera by moving ane existing camera object
         */
        OrthographicCamera(OrthographicCamera&&) = default;
        /**
         * @brief reassign an existing camera to ourselves
         * @return our newly assigned camera
         */
        OrthographicCamera& operator=(OrthographicCamera&&) = default;

        /**
         * @brief properly destroy concrete children
         */
        ~OrthographicCamera() override = default;

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

inline CSCI441::OrthographicCamera::OrthographicCamera(
        const GLfloat minX,
        const GLfloat maxX,
        const GLfloat minY,
        const GLfloat maxY,
        const GLfloat minZ,
        const GLfloat maxZ
) : _minX(minX), _maxX(maxX), _minY(minY), _maxY(maxY), _minZ(minZ), _maxZ(maxZ) {
    _updateProjectionMatrix();
}

inline void CSCI441::OrthographicCamera::_updateProjectionMatrix() {
    mProjectionMatrix = glm::ortho( _minX, _maxX, _minY, _maxY, _minZ, _maxZ );
}

#endif//CSCI441_ORTHOGRAPHIC_CAMERA_HPP