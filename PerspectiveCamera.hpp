#ifndef CSCI441_PERSPECTIVE_CAMERA_HPP
#define CSCI441_PERSPECTIVE_CAMERA_HPP

#include "Camera.hpp"

namespace CSCI441 {

    /**
     * @brief Abstract Class to represent a perspective camera.  Stores aspect ratio and field of view
     */
    class PerspectiveCamera : public CSCI441::Camera {
    public:
        /**
         * @brief initializes the Perspective Camera
         * @param aspectRatio aspect ratio of view plane (defaults to 1.0f)
         * @param fovy vertical field of view (defaults to 45.0f)
         * @param nearClipPlane near z clip plane (defaults to 0.001f)
         * @param farClipPlane far z clip plane (defaults to 1000.0f)
         * @note field of view specified in degrees
         */
        explicit PerspectiveCamera(GLfloat aspectRatio = 1.0f, GLfloat fovy = 45.0f, GLfloat nearClipPlane = 0.001f, GLfloat farClipPlane = 1000.0f);

        /**
         * @brief properly destroy concrete children
         */
        ~PerspectiveCamera() override = default;

        /**
         * @brief updates the camera's aspect ratio
         * @param aspectRatio new aspect ratio to apply to camera
         * @note internally updates the camera's projection matrix
         */
        [[maybe_unused]] virtual void setAspectRatio(GLfloat aspectRatio) final;

        /**
         * @brief updates the camera's vertical field of view
         * @param fovy new vertical field of view to apply to camera
         * @note internally updates the camera's projection matrix
         */
        [[maybe_unused]] virtual void setVerticalFOV(GLfloat fovy) final;

        /**
         * @brief updates the camera's near clip plane
         * @param near new near clip plane to apply to camera
         * @note internally updates the camera's projection matrix
         */
        [[maybe_unused]] virtual void setNearClipPlane(GLfloat near) final;

        /**
         * @brief updates the camera's far clip plane
         * @param far new far clip plane to apply to camera
         * @note internally updates the camera's projection matrix
         */
        [[maybe_unused]] virtual void setFarClipPlane(GLfloat far) final;

    protected:
        /**
         * @brief computes the perspective projection matrix for the camera
         */
        void mUpdateProjectionMatrix();

        /**
         * @brief construct a copy an existing camera
         */
        PerspectiveCamera(const PerspectiveCamera&) = default;
        /**
         * @brief assign a copy of an existing camera
         * @return our newly assigned camera
         */
        PerspectiveCamera& operator=(const PerspectiveCamera&) = default;

        /**
         * @brief construct a camera by moving ane existing camera object
         */
        PerspectiveCamera(PerspectiveCamera&&) = default;
        /**
         * @brief reassign an existing camera to ourselves
         * @return our newly assigned camera
         */
        PerspectiveCamera& operator=(PerspectiveCamera&&) = default;

    private:
        /**
         * @brief vertical field of view
         * @note stored in degrees
         */
        GLfloat _fovy;
        /**
         * @brief aspect ratio of view plane
         */
        GLfloat _aspectRatio;
        /**
         * @brief near Z clipping plane
         */
        GLfloat _nearClipPlane;
        /**
         * @brief far Z clipping plane
         */
        GLfloat _farClipPlane;
    };

}

inline CSCI441::PerspectiveCamera::PerspectiveCamera(
        const GLfloat aspectRatio,
        const GLfloat fovy,
        const GLfloat nearClipPlane,
        const GLfloat farClipPlane
) : _fovy(fovy),
    _aspectRatio(aspectRatio),
    _nearClipPlane(nearClipPlane),
    _farClipPlane(farClipPlane)
{
    mUpdateProjectionMatrix();
}

[[maybe_unused]]
inline void CSCI441::PerspectiveCamera::setAspectRatio(const GLfloat aspectRatio) {
    _aspectRatio = aspectRatio;
    mUpdateProjectionMatrix();
}

[[maybe_unused]]
inline void CSCI441::PerspectiveCamera::setVerticalFOV(const GLfloat fovy) {
    _fovy = fovy;
    mUpdateProjectionMatrix();
}

[[maybe_unused]]
inline void CSCI441::PerspectiveCamera::setNearClipPlane(const GLfloat near) {
    _nearClipPlane = near;
    mUpdateProjectionMatrix();
}

[[maybe_unused]]
inline void CSCI441::PerspectiveCamera::setFarClipPlane(const GLfloat far) {
    _farClipPlane = far;
    mUpdateProjectionMatrix();
}

inline void CSCI441::PerspectiveCamera::mUpdateProjectionMatrix() {
    mProjectionMatrix = glm::perspective(_fovy, _aspectRatio, _nearClipPlane, _farClipPlane);
}

#endif//CSCI441_PERSPECTIVE_CAMERA_HPP