/**
 * @file MD5Model_types.hpp
 * @brief Doom3 MD5 Model + Animation type implementations
 * @author Dr. Jeffrey Paone
 *
 * @copyright MIT License Copyright (c) 2025 Dr. Jeffrey Paone
 *
 *	These functions, classes, and constants help minimize common
 *	code that needs to be written.
 */

#ifndef CSCI441_MD5_MODEL_TYPES_HPP
#define CSCI441_MD5_MODEL_TYPES_HPP

/*
 * md5mesh model loader + animation
 * last modification: Dr. Jeffrey Paone
 * encapsulated into a class
 * supports texturing
 *
 * Doom3's md5mesh viewer with animation.  Mesh and Animation declaration
 * See http://tfc.duke.free.fr/coding/md5-specs-en.html for more details
 *
 * Copyright (c) 2005-2007 David HENRY
 *
 * Permission is hereby granted, free of charge, to any person
 * obtaining a copy of this software and associated documentation
 * files (the "Software"), to deal in the Software without
 * restriction, including without limitation the rights to use,
 * copy, modify, merge, publish, distribute, sublicense, and/or
 * sell copies of the Software, and to permit persons to whom the
 * Software is furnished to do so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be
 * included in all copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND,
 * EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF
 * MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT.
 *
 * IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR
 * ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF
 * CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION
 * WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.
 *
 */

#ifdef CSCI441_USE_GLEW
    #include <GL/glew.h>
#else
    #include <glad/gl.h>
#endif

#include <glm/ext/quaternion_float.hpp>

#include <cstring>
#include <stdexcept>

namespace CSCI441_INTERNAL {

    ///////////////////////////////////////////////////////////////////////////////////////////////////
    // md5mtr types
    ///////////////////////////////////////////////////////////////////////////////////////////////////
    /**
     * @brief texture handle for the model
     */
    struct MD5Texture {
        /**
         * @brief max length of texture name string
         */
        static constexpr GLshort MAX_NAME_LENGTH = 512;
        /**
         * @brief handle of texture stored on the GPU
         */
        GLuint texHandle = 0;
        /**
         * @brief filename texture was loaded from
         */
        char filename[MAX_NAME_LENGTH] = "";

        /**
         * @brief constructs a default texture object
         */
        MD5Texture() = default;
        /**
         * @brief construct a texture object by copying an existing object
         * @param OTHER texture object to copy
         */
        MD5Texture(const MD5Texture &OTHER) {
            _copyFromSrc(OTHER);
        }
        /**
         * @brief reassign texture object by copying an existing object
         * @param OTHER existing object to copy
         * @return now modified texture object
         */
        MD5Texture& operator=(const MD5Texture &OTHER) {
            if (this != &OTHER) {
                _copyFromSrc(OTHER);
            }
            return *this;
        }
        /**
         * @brief construct a texture object by moving an existing object
         * @param src existing object to move
         */
        MD5Texture(MD5Texture&& src) noexcept {
            _moveFromSrc(src);
        }
        /**
         * @brief reassign texture object by moving an existing object
         * @param src existing object to move
         * @return now modified texture object
         */
        MD5Texture& operator=(MD5Texture&& src) noexcept {
            if (this != &src) {
                _moveFromSrc(src);
            }
            return *this;
        }
    private:
        /**
         * @brief deep copy data members from an existing object
         * @param src object to copy
         */
        void _copyFromSrc(const MD5Texture &src) {
            this->texHandle = src.texHandle;
            strncpy(this->filename, src.filename, MAX_NAME_LENGTH);
        }
        /**
         * @brief move data members and return existing object to default state
         * @param src object to move
         */
        void _moveFromSrc(MD5Texture& src) {
            _copyFromSrc(src);

            src.texHandle = 0;
            strncpy(src.filename, "", MAX_NAME_LENGTH);
        }
    };

    // md5material types
    struct MD5MaterialShader {
        /**
         * @brief max length of shader name string
         */
        static constexpr GLshort MAX_NAME_LENGTH = 512;
        /**
         * @brief number of textures applied to mesh
         */
        static constexpr GLshort NUM_TEXTURES = 4;
        /**
         * @brief base filename for all textures applied to mesh
         */
        char name[MAX_NAME_LENGTH] = "";
        /**
         * @brief texture map array
         */
        MD5Texture textures[NUM_TEXTURES];
        /**
         * @brief scale factor to apply height map against normal map
         */
        GLuint displacementScale = 1;
        /**
         * @brief named entities for different texture maps applied to the model
         */
        enum TextureMap {
            /**
             * @brief diffuse map
             */
            DIFFUSE,
            /**
             * @brief specular map
             */
            SPECULAR,
            /**
             * @brief normal map
             */
            NORMAL,
            /**
             * @brief height map
             */
            HEIGHT
        };
        MD5MaterialShader() = default;
        MD5MaterialShader(const MD5MaterialShader &OTHER) {
            _copyFromSrc(OTHER);
        }
        MD5MaterialShader& operator=(const MD5MaterialShader &OTHER) {
            if (this != &OTHER) {
                _copyFromSrc(OTHER);
            }
            return *this;
        }
        MD5MaterialShader(MD5MaterialShader&& src) noexcept {
            _moveFromSrc(src);
        }
        MD5MaterialShader& operator=(MD5MaterialShader&& src) noexcept {
            if (this != &src) {
                _moveFromSrc(src);
            }
            return *this;
        }
    private:
        void _copyFromSrc(const MD5MaterialShader &src) {
            for (GLshort i = 0; i < NUM_TEXTURES; i++) {
                this->textures[i] = src.textures[i];
            }
            strncpy(this->name, src.name, MAX_NAME_LENGTH);
        }
        void _moveFromSrc(MD5MaterialShader &src) {
            for (GLshort i = 0; i < NUM_TEXTURES; i++) {
                this->textures[i] = std::move( src.textures[i] );
            }
            strncpy(this->name, src.name, MAX_NAME_LENGTH);
            strncpy(src.name, "", MAX_NAME_LENGTH);
        }
    };

    ///////////////////////////////////////////////////////////////////////////////////////////////////
    // md5mesh types
    ///////////////////////////////////////////////////////////////////////////////////////////////////
    /**
     * @brief a joint of the MD5 Skeleton
     */
    struct MD5Joint {
        /**
         * @brief a non-existent joint.  used to identify joints at the root of a skeleton
         */
        static constexpr GLint NULL_JOINT = -1;
        /**
         * @brief max length of joint name string
         */
        static constexpr GLshort MAX_NAME_LENGTH = 256;
        /**
         * @brief joint identifier
         */
        char name[MAX_NAME_LENGTH] = "";
        /**
         * @brief index of the parent joint on skeletal tree
         */
        GLint parent = NULL_JOINT;
        /**
         * @brief position of the joint in object space
         */
        glm::vec3 position = {0.0f, 0.0f, 0.0f};
        /**
         * @brief joint orientation expressed as a quaternion in object space
         */
        glm::quat orientation = {0.0f, 0.0f, 0.0f, 0.0f};

        /**
         * @brief construct a default joint object
         */
        MD5Joint() = default;
        /**
         * @brief construct a joint object by copying an existing joint
         * @param OTHER existing joint object
         */
        MD5Joint(const MD5Joint &OTHER) {
            _copyFromSrc(OTHER);
        }
        /**
         * @brief reassign an existing joint object by copying another joint object
         * @param OTHER existing joint object to copy
         * @return the now modified joint object
         */
        MD5Joint& operator=(const MD5Joint &OTHER) {
            if (this != &OTHER) {
                _copyFromSrc(OTHER);
            }
            return *this;
        }
        /**
         * @brief construct a joint object by moving an existing object
         * @param src existing joint object to move
         */
        MD5Joint(MD5Joint&& src) noexcept {
            _moveFromSrc(src);
        }
        /**
         * @brief reassign an existing joint object by moving another joint object
         * @param src existing joint object to move
         * @return the now modified joint object
         */
        MD5Joint& operator=(MD5Joint&& src) noexcept {
            if (this != &src) {
                _moveFromSrc(src);
            }
            return *this;
        }
    private:
        /**
         * @brief deep copies all the data members from another joint object
         * @param src existing joint object to copy
         */
        void _copyFromSrc(const MD5Joint& src) {
            strncpy(this->name, src.name, MAX_NAME_LENGTH);
            this->parent = src.parent;
            this->position = src.position;
            this->orientation = src.orientation;
        }
        /**
         * @brief moves data members from another joint object, resetting the other joint object
         * back to its default state
         * @param src existing joint object to move
         */
        void _moveFromSrc(MD5Joint& src) {
            // copy values from source
            _copyFromSrc(src);
            // reset source
            strncpy(src.name, "", MAX_NAME_LENGTH);
            src.parent = NULL_JOINT;
            src.position = glm::vec3(0.0f, 0.0f, 0.0f);
            src.orientation = glm::quat(0.0f, 0.0f, 0.0f, 0.0f);
        }
    };

    /**
     * @brief a vertex on the mesh
     */
    struct MD5Vertex {
        /**
         * @brief texture coordinate for vertex
         */
        glm::vec2 texCoord = {0.0f, 0.0f};
        /**
         * @brief index of starting weight
         */
        GLint start = 0;
        /**
         * @brief number of weights that determine vertex's position
         */
        GLint count = 0;

        /**
         * @brief construct a default vertex object
         */
        MD5Vertex() = default;
        /**
         * @brief construct a vertex object by copying an existing vertex
         * @param OTHER existing vertex object to copy
         */
        MD5Vertex(const MD5Vertex &OTHER) {
            _copyFromSrc(OTHER);
        }
        /**
         * @brief reassign existing vertex object by copying an existing vertex object
         * @param OTHER existing vertex object to copy
         * @return now modified vertex object
         */
        MD5Vertex& operator=(const MD5Vertex &OTHER) {
            if (this != &OTHER) {
                _copyFromSrc(OTHER);
            }
            return *this;
        }
        /**
         * @brief construct a vertex object by moving an existing vertex
         * @param src existing vertex object to move
         */
        MD5Vertex(MD5Vertex&& src) noexcept {
            _moveFromSrc(src);
        }
        /**
         * @brief reassign existing vertex object by moving an existing vertex object
         * @param src existing vertex object move
         * @return now modified vertex object
         */
        MD5Vertex& operator=(MD5Vertex&& src) noexcept {
            if (this != &src) {
                _moveFromSrc(src);
            }
            return *this;
        }
    private:
        /**
         * @brief deep copy vertex data members
         * @param src existing vertex to copy
         */
        void _copyFromSrc(const MD5Vertex &src) {
            this->texCoord = src.texCoord;
            this->start = src.start;
            this->count = src.count;
        }
        /**
         * @brief move data members and reset existing vertex to default state
         * @param src existing vertex to move
         */
        void _moveFromSrc(MD5Vertex& src) {
            _copyFromSrc(src);

            src.texCoord = glm::vec2(0.0f, 0.0f);
            src.start = 0;
            src.count = 0;
        }
    };

    /**
     * @brief a triangle on the mesh
     */
    struct MD5Triangle {
        /**
         * @brief number of vertices that make up a triangle
         */
        static constexpr GLshort NUM_VERTICES = 3;
        /**
         * @brief vertex indices that make up triangle
         */
        GLint index[NUM_VERTICES] = {0};

        /**
         * @brief construct a default triangle object
         */
        MD5Triangle() = default;
        /**
         * @brief construct a triangle by copying an existing triangle
         * @param OTHER existing triangle object to copy
         */
        MD5Triangle(const MD5Triangle &OTHER) {
            _copyFromSrc(OTHER);
        }
        /**
         * @brief reassign triangle object by copying an existing triangle
         * @param OTHER existing triangle object to copy
         * @return now modified triangle object
         */
        MD5Triangle& operator=(const MD5Triangle &OTHER) {
            if (this != &OTHER) {
                _copyFromSrc(OTHER);
            }
            return *this;
        }
        /**
         * @brief construct a triangle object by moving an existing triangle
         * @param src existing triangle object to move
         */
        MD5Triangle(MD5Triangle&& src) noexcept {
            _moveFromSrc(src);
        }
        /**
         * @brief reassign triangle object by moving an existing triangle
         * @param src existing triangle object to move
         * @return now modified triangle object
         */
        MD5Triangle& operator=(MD5Triangle&& src) noexcept {
            if (this != &src) {
                _moveFromSrc(src);
            }
            return *this;
        }
    private:
        /**
         * @brief deep copy triangle data members
         * @param src triangle object to copy
         */
        void _copyFromSrc(const MD5Triangle &src) {
            for (GLshort i = 0; i < NUM_VERTICES; i++) {
                this->index[i] = src.index[i];
            }
        }
        /**
         * @brief move triangle object and reset existing triangle to default state
         * @param src triangle object to move
         */
        void _moveFromSrc(MD5Triangle &src) {
            _copyFromSrc(src);

            for (GLint & i : src.index) {
                i = 0;
            }
        }
    };

    /**
     * @brief the weight for a mesh vertex
     */
    struct MD5Weight {
        /**
         * @brief index of joint the weight depends on
         */
        GLint joint = MD5Joint::NULL_JOINT;
        /**
         * @brief contribution of the weight
         */
        GLfloat bias = 0.f;
        /**
         * @brief weight's position in object space
         */
        glm::vec3 position = {0.0f, 0.0f, 0.0f};

        /**
         * @brief construct a default weight object
         */
        MD5Weight() = default;
        /**
         * @brief construct a weight object by copying an existing weight
         * @param OTHER existing weight object to copy
         */
        MD5Weight(const MD5Weight &OTHER) {
            _copyFromSrc(OTHER);
        }
        /**
         * @brief reassign an existing weight object by copying another
         * @param OTHER existing weight object to copy
         * @return now modified weight object
         */
        MD5Weight& operator=(const MD5Weight &OTHER) {
            if (this != &OTHER) {
                _copyFromSrc(OTHER);
            }
            return *this;
        }
        /**
         * @brief construct a weight object by moving an existing object
         * @param src existing weight object to move
         */
        MD5Weight(MD5Weight&& src) noexcept {
            _moveFromSrc(src);
        }
        /**
         * @brief reassign an existing weight object by moving another
         * @param src existing weight object to move
         * @return now modified weight object
         */
        MD5Weight& operator=(MD5Weight&& src) noexcept {
            if (this != &src) {
                _moveFromSrc(src);
            }
            return *this;
        }
    private:
        /**
         * @brief deep copy data members
         * @param src weight object to copy
         */
        void _copyFromSrc(const MD5Weight &src) {
            this->joint = src.joint;
            this->bias = src.bias;
            this->position = src.position;
        }
        /**
         * @brief move data members and reset existing object to default state
         * @param src weight object to move
         */
        void _moveFromSrc(MD5Weight &src) {
            _copyFromSrc(src);

            src.joint = MD5Joint::NULL_JOINT;
            src.bias = 0.0f;
            src.position = glm::vec3(0.0f, 0.0f, 0.0f);
        }
    };

    /**
     * @brief mesh that comprises the model's skin
     */
    struct MD5Mesh {

        /**
         * @brief array of vertices comprising the mesh
         */
        MD5Vertex* vertices = nullptr;
        /**
         * @brief array triangles comprising the mesh
         */
        MD5Triangle* triangles = nullptr;
        /**
         * @brief array of weights to determine vertex position based on joint positions
         */
        MD5Weight* weights = nullptr;

        MD5MaterialShader* shader = nullptr;

        /**
         * @brief number of vertices in the mesh vertex array
         */
        GLint numVertices = 0;
        /**
         * @brief number of triangles in the mesh triangle array
         */
        GLint numTriangles = 0;
        /**
         * @brief number of weights in the mesh weight array
         */
        GLint numWeights = 0;
        /**
         * @brief construct a default mesh object
         */
         MD5Mesh() = default;
        /**
         * @brief deallocate member arrays
         */
        ~MD5Mesh() {
            delete[] vertices;
            vertices = nullptr;

            delete[] triangles;
            triangles = nullptr;

            delete[] weights;
            weights = nullptr;
        }
        /**
         * @brief do not allow meshes to be copied
         * @param OTHER unused
         */
        MD5Mesh(const MD5Mesh &OTHER) = delete;
        /**
         * @brief do not allow meshes to be copied
         * @param OTHER unused
         */
        MD5Mesh& operator=(const MD5Mesh &OTHER) = delete;

        /**
         * @brief construct a new mesh by moving an existing object
         * @param src object to move
         */
        MD5Mesh(MD5Mesh&& src) noexcept {
            _moveFromSrc(src);
        }
        /**
         * @brief reassign mesh object by moving an existing object
         * @param src object to move
         * @return now modified object
         */
        MD5Mesh& operator=(MD5Mesh&& src) noexcept {
            if (this != &src) {
                _moveFromSrc(src);
            }
            return *this;
        }
    private:
        /**
         * @brief move data members from an existing object and reset to default state
         * @param src object to move
         */
        void _moveFromSrc(MD5Mesh& src) {
            this->vertices = src.vertices;
            src.vertices = nullptr;

            this->triangles = src.triangles;
            src.triangles = nullptr;

            this->weights = src.weights;
            src.weights = nullptr;

            this->shader = src.shader;
            src.shader = nullptr;

            this->numVertices = src.numVertices;
            src.numVertices = 0;

            this->numTriangles = src.numTriangles;
            src.numTriangles = 0;

            this->numWeights = src.numWeights;
            src.numWeights = 0;
        }
    };

    ///////////////////////////////////////////////////////////////////////////////////////////////////
    // md5anim types
    ///////////////////////////////////////////////////////////////////////////////////////////////////
    /**
     * @brief information pertaining to each animation joint
     */
    struct MD5JointInfo {
        /**
         * @brief max length of joint identifier string
         */
        static constexpr GLshort MAX_NAME_LENGTH = 256;
        /**
         * @brief joint identifier
         */
        char name[MAX_NAME_LENGTH] = "";
        /**
         * @brief index of parent joint on skeletal tree
         */
        GLint parent = MD5Joint::NULL_JOINT;
        /**
         * @brief bit flags denoted how to compute the skeleton of a frame for this joint
         */
        GLuint flags = 0;
        /**
         * @brief index of starting parameter
         */
        GLint startIndex = 0;

        /**
         * @brief construct a default joint info object
         */
        MD5JointInfo() = default;
        /**
         * @brief construct a joint info object by copying an existing object
         * @param OTHER object to copy
         */
        MD5JointInfo(const MD5JointInfo& OTHER) {
            _copyFromSrc(OTHER);
        }
        /**
         * @brief reassign object by copying an existing object
         * @param OTHER object to copy
         * @return now modified object
         */
        MD5JointInfo& operator=(const MD5JointInfo& OTHER) {
            if (this != &OTHER) {
                _copyFromSrc(OTHER);
            }
            return *this;
        }
        /**
         * @brief construct joint info object by moving an existing object
         * @param src object to move
         */
        MD5JointInfo(MD5JointInfo&& src) noexcept {
            _moveFromSrc(src);
        }
        /**
         * @brief reassign object by moving an existing object
         * @param src object to move
         * @return now modified object
         */
        MD5JointInfo& operator=(MD5JointInfo&& src) noexcept {
            if (this != &src) {
                _moveFromSrc(src);
            }
            return *this;
        }
    private:
        /**
         * @brief deep copy data members
         * @param src object to copy
         */
        void _copyFromSrc(const MD5JointInfo &src) {
            strncpy(this->name, src.name, MAX_NAME_LENGTH);
            this->parent = src.parent;
            this->flags = src.flags;
            this->startIndex = src.startIndex;
        }
        /**
         * @brief move object and reset to default state
         * @param src object to move
         */
        void _moveFromSrc(MD5JointInfo &src) {
            _copyFromSrc(src);

            strncpy(src.name, "", MAX_NAME_LENGTH);
            src.parent = MD5Joint::NULL_JOINT;
            src.flags = 0;
            src.startIndex = 0;
        }
    };

    /**
     * @brief base frame joint
     */
    struct MD5BaseFrameJoint {
        /**
         * @brief position of the joint in object space
         */
        glm::vec3 position = {0.0f, 0.0f, 0.0f};
        /**
         * @brief joint orientation expressed as a quaternion in object space
         */
        glm::quat orientation = {0.0f, 0.0f, 0.0f, 0.0f};

        /**
         * @brief construct a default object
         */
        MD5BaseFrameJoint() = default;
        /**
         * @brief construct an object by copying an existing object
         * @param OTHER object to copy
         */
        MD5BaseFrameJoint(const MD5BaseFrameJoint& OTHER) {
            _copyFromSrc(OTHER);
        }
        /**
         * @brief reassign object by copying an existing object
         * @param OTHER object to copy
         * @return now modified object
         */
        MD5BaseFrameJoint& operator=(const MD5BaseFrameJoint &OTHER) {
            if (this != &OTHER) {
                _copyFromSrc(OTHER);
            }
            return *this;
        }
        /**
         * @brief construct object by moving an existing object
         * @param src object to move
         */
        MD5BaseFrameJoint(MD5BaseFrameJoint&& src) noexcept {
            _moveFromSrc(src);
        }
        /**
         * @brief reassign object by moving an existing object
         * @param src object to move
         * @return now modified object
         */
        MD5BaseFrameJoint& operator=(MD5BaseFrameJoint&& src) noexcept {
            if (this != &src) {
                _moveFromSrc(src);
            }
            return *this;
        }
    private:
        /**
         * @brief deep copy data members
         * @param src object to copy
         */
        void _copyFromSrc(const MD5BaseFrameJoint &src) {
            this->position = src.position;
            this->orientation = src.orientation;
        }
        /**
         * @brief move data members and reset object to default state
         * @param src object to move
         */
        void _moveFromSrc(MD5BaseFrameJoint &src) {
            _copyFromSrc(src);

            src.position = glm::vec3(0.0f, 0.0f, 0.0f);
            src.orientation = glm::quat(0.0f, 0.0f, 0.0f, 0.0f);
        }
    };

    /**
     * @brief bounding box containing the model during animation
     * @note can be useful for computing AABB or OBB for frustum culling and basic collision detection
     */
    struct MD5BoundingBox {
        /**
         * @brief minimum dimension bound
         */
        glm::vec3 min = {0.0f, 0.0f, 0.0f};
        /**
         * @brief maximum dimension bound
         */
        glm::vec3 max = {0.0f, 0.0f, 0.0f};

        /**
         * @brief construct a default object
         */
        MD5BoundingBox() = default;
        /**
         * @brief construct an object by copying an existing object
         * @param OTHER object to copy
         */
        MD5BoundingBox(const MD5BoundingBox &OTHER) {
            _copyFromSrc(OTHER);
        }
        /**
         * @brief reassign object by copying an existing object
         * @param OTHER object to copy
         * @return now modified object
         */
        MD5BoundingBox& operator=(const MD5BoundingBox &OTHER) {
            if (this != &OTHER) {
                _copyFromSrc(OTHER);
            }
            return *this;
        }
        /**
         * @brief construct an object by moving an existing object
         * @param src object to move
         */
        MD5BoundingBox(MD5BoundingBox&& src) noexcept {
            _moveFromSrc(src);
        }
        /**
         * @brief reassign object by moving an existing object
         * @param src object to move
         * @return now modified object
         */
        MD5BoundingBox& operator=(MD5BoundingBox&& src) noexcept {
            if (this != &src) {
                _moveFromSrc(src);
            }
            return *this;
        }
    private:
        /**
         * @brief deep copy data members
         * @param src object to copy
         */
        void _copyFromSrc(const MD5BoundingBox& src) {
            this->min = src.min;
            this->max = src.max;
        }
        /**
         * @brief move data members and reset object to default state
         * @param src object to move
         */
        void _moveFromSrc(MD5BoundingBox& src) {
            _copyFromSrc(src);

            src.min = glm::vec3(0.0f, 0.0f, 0.0f);
            src.max = glm::vec3(0.0f, 0.0f, 0.0f);
        }
    };

    /**
     * @brief stores an entire animation sequence for a given MD5 Model
     */
    class MD5Animation {
    public:
        /**
         * @brief number of frames per second to draw for the animation
         * @note duration of a frame can be computed by inverting the frame rate
         */
        GLint frameRate = 0;

        /**
         * @brief getter to retrieve number of frames within the animation
         * @return number of frames in this animation
         */
        [[nodiscard]] GLint getNumberOfFrames() const { return _numFrames; }
        /**
         * @brief sets the number of frames and allocates skeletonFrames and boundingBoxes to the associated size
         * @param numFrames number of frames this animation is made up of
         * @note will first deallocate any memory associated with frames to prevent memory leaks
         * @note setNumberOfJoints() must be called after this method
         */
        void setNumberOfFrames(const GLint numFrames) {
            // if previously set, delete prior allocation to avoid memory leak
            if(_skeletonFrames != nullptr) {
                for (GLint i = 0; i < _numFrames; ++i) {
                    delete _skeletonFrames[i];
                }
            }
            delete[] _skeletonFrames;
            _skeletonFrames = nullptr;   // no longer exists, in event new set equals zero
            delete[] _boundingBoxes;
            _boundingBoxes = nullptr;    // no longer exists, in event new set equals zero

            _numFrames = numFrames;
            if ( _numFrames > 0 ) {
                _skeletonFrames = new MD5Joint*[_numFrames];
                for (GLint i = 0; i < _numFrames; ++i) {
                    _skeletonFrames[i] = nullptr;
                }
                _boundingBoxes = new MD5BoundingBox[_numFrames];
            }
        }

        /**
         * @brief get the number of joints in each skeleton frame
         * @return number of joints in the skeleton
         */
        [[nodiscard]] GLint getNumberOfJoints() const { return _numJoints; }
        /**
         * @brief set the number of joints in the skeleton of each animation frame and allocates each
         * frame of skeletonFrames
         * @param numJoints number of joints in the skeleton of each animation frame
         * @note will first deallocate any memory associated with the skeleton frame to prevent memory leaks
         * @note call setNumberOfFrames() first or this method will have no effect
         */
        void setNumberOfJoints(const GLint numJoints) {
            // if previously set, delete prior allocation to avoid memory leak
            if(_skeletonFrames != nullptr) {
                for (GLint i = 0; i < _numFrames; ++i) {
                    delete _skeletonFrames[i];
                    _skeletonFrames[i] = nullptr;    // no longer exists, in event new set equals zero
                }
            }

            _numJoints = numJoints;
            if (_numJoints > 0) {
                if(_skeletonFrames != nullptr) {
                    for(GLint i = 0; i < _numFrames; ++i) {
                        // Allocate memory for joints of each frame
                        _skeletonFrames[i] = new MD5Joint[_numJoints];
                    }
                }
            }
        }

        /**
         * @brief get the skeleton for a specific animation frame
         * @param frameIndex animation frame to retrieve skeleton for
         * @return pointer to skeleton
         * @throws std::out_of_range if frameIndex < 0 or >= number of frames
         * @throws std::out_of_range if skeletonFrames is null and setNumberOfFrames has not been previously called
         */
        [[nodiscard]] const MD5Joint* getSkeletonFrame(const GLint frameIndex) const {
            if ( frameIndex < 0 || frameIndex >= _numFrames ) {
                throw std::out_of_range("frameIndex out of range");
            }
            if (_skeletonFrames == nullptr) {
                throw std::out_of_range("skeleton frames are null, setNumberOfFrames() may not have been called");
            }
            return _skeletonFrames[frameIndex];
        }
        /**
         * @brief get the specific joint from a skeleton for a specific animation frame
         * @param frameIndex animation frame to retrieve skeleton for
         * @param jointIndex joint to retrieve from skeleton
         * @return pointer to joint
         * @throws std::out_of_range if frameIndex < 0 or >= number of frames
         * @throws std::out_of_range if jointIndex < 0 or >= number of joints
         * @throws std::out_of_range if skeletonFrames[frameIndex] is null and setNumberOfJoints has not been previously called
         */
        [[nodiscard]] MD5Joint& getSkeletonFrameJoint(const GLint frameIndex, const GLint jointIndex) const {
            if ( frameIndex < 0 || frameIndex >= _numFrames ) {
                throw std::out_of_range("frameIndex out of range");
            }
            if ( jointIndex < 0 || jointIndex >= _numJoints ) {
                throw std::out_of_range("jointIndex out of range");
            }
            if (_skeletonFrames == nullptr) {
                throw std::out_of_range("skeleton frames are null, setNumberOfFrames() may not have been called");
            }
            if (_skeletonFrames[frameIndex] == nullptr) {
                throw std::out_of_range("skeleton joints are null, setNumberOfJoints() may not have been called");
            }
            return _skeletonFrames[frameIndex][jointIndex];
        }

        /**
         * @brief get the specific bounding box for a target frame
         * @param frameIndex frame index to retrieve bounding box for
         * @return bounding box
         * @throws std::out_of_range if frameIndex < 0 or >= number of frames
         * @throws std::out_of_range if boundingBoxes is null and setNumberOfFrames has not been previously called
         */
        [[nodiscard]] MD5BoundingBox& getBoundingBox(const GLint frameIndex) const {
            if(frameIndex < 0 || frameIndex >= _numFrames) {
                throw std::out_of_range("frameIndex out of range");
            }
            if (_boundingBoxes == nullptr) {
                throw std::out_of_range("bounding boxes are null, setNumberOfFrames() may not have been called");
            }
            return _boundingBoxes[frameIndex];
        }

        /**
         * @brief construct a default animation object
         */
        MD5Animation() = default;
        /**
         * @brief deallocate animation arrays
         */
        ~MD5Animation() {
            if(_skeletonFrames != nullptr) {
                for (GLint i = 0; i < _numFrames; i++) {
                    delete[] _skeletonFrames[i];
                    _skeletonFrames[i] = nullptr;
                }
            }
            delete[] _skeletonFrames;
            _skeletonFrames = nullptr;

            delete[] _boundingBoxes;
            _boundingBoxes = nullptr;
        }

        /**
         * @brief do not allow animation objects to be copied
         * @param OTHER unused
         */
        MD5Animation(const MD5Animation& OTHER) = delete;
        /**
         * @brief do not allow animation objects to be copied
         * @param OTHER unused
         */
        MD5Animation& operator=(const MD5Animation& OTHER) = delete;

        /**
         * @brief construct an animation object by moving an existing object
         * @param src object to move
         */
        MD5Animation(MD5Animation&& src) noexcept {
            _moveFromSrc(src);
        }
        /**
         * @brief reassign object by moving an existing object
         * @param src object to be moved
         * @return now modified object
         */
        MD5Animation& operator=(MD5Animation&& src) noexcept {
            if (this != &src) {
                _moveFromSrc(src);
            }
            return *this;
        }
    private:
        /**
         * @brief number of frames in the animation
         * @note corresponds to size of skeletonFrames and boundingBoxes
         */
        GLint _numFrames = 0;
        /**
         * @brief number of joints of the frame skeletons
         * @note must be the same as the number of joints on the model the animation is applied to
         */
        GLint _numJoints = 0;
        /**
         * @brief skeletal pose for each frame
         * @note size tracked in numFrames
         */
        MD5Joint** _skeletonFrames = nullptr;
        /**
         * @brief bounding box for each frame
         * @note size tracked in numFrames
         */
        MD5BoundingBox* _boundingBoxes = nullptr;

        /**
         * @brief move data members and reset object to default state
         * @param src object to move
         */
        void _moveFromSrc(MD5Animation &src) {
            this->_numFrames = src._numFrames;
            src._numFrames = 0;

            this->_numJoints = src._numJoints;
            src._numJoints = 0;

            this->frameRate = src.frameRate;
            src.frameRate = 0;

            this->_skeletonFrames = src._skeletonFrames;
            src._skeletonFrames = nullptr;

            this->_boundingBoxes = src._boundingBoxes;
            src._boundingBoxes = nullptr;
        }
    };

    /**
     * @brief stores state of current animation frame
     */
    struct MD5AnimationState {
        /**
         * @brief index of current frame model is in
         */
        GLint currFrame = 0;
        /**
         * @brief index of next frame model will move to
         */
        GLint nextFrame = 0;
        /**
         * @brief time of last frame interpolation
         */
        GLfloat lastTime = 0.0f;
        /**
         * @brief duration of a single frame
         * @note equivalent to inverse of frame rate
         */
        GLfloat maxTime = 0.0f;

        /**
         * @brief construct a default object
         */
        MD5AnimationState() = default;
        /**
         * @brief construct an object by copying an existing object
         * @param OTHER object to copy
         */
        MD5AnimationState(const MD5AnimationState &OTHER) {
            _copyFromSrc(OTHER);
        }
        /**
         * @brief reassign object by copying an existing object
         * @param OTHER object to copy
         * @return now modified object
         */
        MD5AnimationState& operator=(const MD5AnimationState &OTHER) {
            if (this != &OTHER) {
                _copyFromSrc(OTHER);
            }
            return *this;
        }
        /**
         * @brief construct an object by moving an existing object
         * @param src object to move
         */
        MD5AnimationState(MD5AnimationState&& src) noexcept {
            _moveFromSrc(src);
        }
        /**
         * @brief reassign object by moving an existing object
         * @param src object to move
         * @return now modified object
         */
        MD5AnimationState& operator=(MD5AnimationState&& src) noexcept {
            if (this != &src) {
                _moveFromSrc(src);
            }
            return *this;
        }
    private:
        /**
         * @brief deep copy data members
         * @param src object to copy
         */
        void _copyFromSrc(const MD5AnimationState &src) {
            this->currFrame = src.currFrame;
            this->nextFrame = src.nextFrame;
            this->lastTime = src.lastTime;
            this->maxTime = src.maxTime;
        }
        /**
         * @brief move data members and reset object to default state
         * @param src object to move
         */
        void _moveFromSrc(MD5AnimationState &src) {
            _copyFromSrc(src);

            src.currFrame = 0;
            src.nextFrame = 0;
            src.lastTime = 0.0f;
            src.maxTime = 0.0f;
        }
    };
}

#endif//CSCI441_MD5_MODEL_TYPES_HPP