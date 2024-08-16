/**
 * @file HUDCamera.hpp
 * @brief Concrete Heads Up Display Camera implementation with 2D Orthographic Projection
 * @author Dr. Jeffrey Paone
 *
 * @copyright MIT License Copyright (c) 2023 Dr. Jeffrey Paone
 *
 *	These functions, classes, and constants help minimize common
 *	code that needs to be written.
 */

#ifndef CSCI441_HUD_CAMERA_HPP
#define CSCI441_HUD_CAMERA_HPP

#include "OrthographicCamera.hpp"

namespace CSCI441 {

    /**
     * @brief creates a 2D Orthographic projection camera used for Heads Up Display overlays
     * @note Once created, camera cannot be moved/modified
     */
    class [[maybe_unused]] HUDCamera final : public CSCI441::OrthographicCamera {
    public:
        HUDCamera() = delete;

        /**
         * @brief initializes the HUDCamera
         * @param minX left clipping plane
         * @param maxX right clipping plane
         * @param minY bottom clipping plane
         * @param maxY top clipping plane
         */
        [[maybe_unused]] explicit HUDCamera(GLfloat minX, GLfloat maxX, GLfloat minY, GLfloat maxY);

        /**
         * @brief does nothing
         */
        void recomputeOrientation() final {};
        /**
         * @brief does nothing
         * @param unused does nothing
         */
        void moveForward(const GLfloat unused) final {};
        /**
         * @brief does nothing
         * @param unused does nothing
         */
        void moveBackward(const GLfloat unused) final {};
    private:

    };
}

[[maybe_unused]]
inline CSCI441::HUDCamera::HUDCamera(
    GLfloat minX,
    GLfloat maxX,
    GLfloat minY,
    GLfloat maxY
) : OrthographicCamera(minX, maxX, minY, maxY) {

}

#endif//CSCI441_HUD_CAMERA_HPP