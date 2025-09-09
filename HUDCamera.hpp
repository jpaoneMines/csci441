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
         * @brief construct a copy an existing camera
         */
        HUDCamera(const HUDCamera&) = default;
        /**
         * @brief assign a copy of an existing camera
         * @return our newly assigned camera
         */
        HUDCamera& operator=(const HUDCamera&) = default;

        /**
         * @brief construct a camera by moving ane existing camera object
         */
        HUDCamera(HUDCamera&&) = default;
        /**
         * @brief reassign an existing camera to ourselves
         * @return our newly assigned camera
         */
        HUDCamera& operator=(HUDCamera&&) = default;

        /**
         * @brief properly destroy concrete children
         */
        ~HUDCamera() override = default;

        /**
         * @brief does nothing
         */
        void recomputeOrientation() override {};
        /**
         * @brief does nothing
         * @param unused does nothing
         */
        void moveForward(const GLfloat unused) override {};
        /**
         * @brief does nothing
         * @param unused does nothing
         */
        void moveBackward(const GLfloat unused) override {};
    };
}

[[maybe_unused]]
inline CSCI441::HUDCamera::HUDCamera(
    const GLfloat minX,
    const GLfloat maxX,
    const GLfloat minY,
    const GLfloat maxY
) : OrthographicCamera(minX, maxX, minY, maxY) {

}

#endif//CSCI441_HUD_CAMERA_HPP