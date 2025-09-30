/**
 * @file MD5Model.hpp
 * @brief Doom3 MD5 Model + Animation implementations
 * @author Dr. Jeffrey Paone
 *
 * @copyright MIT License Copyright (c) 2023 Dr. Jeffrey Paone
 *
 *	These functions, classes, and constants help minimize common
 *	code that needs to be written.
 */

#ifndef CSCI441_MD5_MODEL_HPP
#define CSCI441_MD5_MODEL_HPP

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

#include "TextureUtils.hpp"

#ifdef CSCI441_USE_GLEW
    #include <GL/glew.h>
#else
    #include <glad/gl.h>
#endif

#include <glm/exponential.hpp>
#include <glm/ext/quaternion_common.hpp>
#include <glm/ext/quaternion_float.hpp>

#define GLM_ENABLE_EXPERIMENTAL
#include <glm/gtx/quaternion.hpp>

#include <cassert>
#include <cmath>
#include <cstdio>
#include <cstdlib>
#include <cstring>

namespace CSCI441 {

    /**
     * @class MD5Model
     * @brief stores a Doom3 MD5 Mesh + Animation
     */
    class [[maybe_unused]] MD5Model {
    protected:
        // md5mesh types
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

            MD5Joint(const MD5Joint &OTHER) {
                _copyFromSrc(OTHER);
            }
            MD5Joint& operator=(const MD5Joint &OTHER) {
                if (this != &OTHER) {
                    _copyFromSrc(OTHER);
                }
                return *this;
            }
            MD5Joint(MD5Joint&& src) noexcept {
                _moveFromSrc(src);
            }
            MD5Joint& operator=(MD5Joint&& src) noexcept {
                if (this != &src) {
                    _moveFromSrc(src);
                }
                return *this;
            }
        private:
            void _copyFromSrc(const MD5Joint& src) {
                strncpy(this->name, src.name, MAX_NAME_LENGTH);
                this->parent = src.parent;
                this->position = src.position;
                this->orientation = src.orientation;
            }
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

            MD5Vertex(const MD5Vertex &OTHER) {
                _copyFromSrc(OTHER);
            }
            MD5Vertex& operator=(const MD5Vertex &OTHER) {
                if (this != &OTHER) {
                    _copyFromSrc(OTHER);
                }
                return *this;
            }
            MD5Vertex(MD5Vertex&& src) noexcept {
                _moveFromSrc(src);
            }
            MD5Vertex& operator=(MD5Vertex&& src) noexcept {
                if (this != &src) {
                    _moveFromSrc(src);
                }
                return *this;
            }
        private:
            void _copyFromSrc(const MD5Vertex &src) {
                this->texCoord = src.texCoord;
                this->start = src.start;
                this->count = src.count;
            }
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
             * @brief vertex indices that make up triangle
             */
            GLint index[3] = {0};

            MD5Triangle(const MD5Triangle &OTHER) {
                _copyFromSrc(OTHER);
            }
            MD5Triangle& operator=(const MD5Triangle &OTHER) {
                if (this != &OTHER) {
                    _copyFromSrc(OTHER);
                }
                return *this;
            }
            MD5Triangle(MD5Triangle&& src) noexcept {
                _moveFromSrc(src);
            }
            MD5Triangle& operator=(MD5Triangle&& src) noexcept {
                if (this != &src) {
                    _moveFromSrc(src);
                }
                return *this;
            }
        private:
            void _copyFromSrc(const MD5Triangle &src) {
                this->index[0] = src.index[0];
                this->index[1] = src.index[1];
                this->index[2] = src.index[2];
            }
            void _moveFromSrc(MD5Triangle &src) {
                _copyFromSrc(src);

                src.index[0] = 0;
                src.index[1] = 0;
                src.index[2] = 0;
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

            MD5Weight(const MD5Weight &OTHER) {
                _copyFromSrc(OTHER);
            }
            MD5Weight& operator=(const MD5Weight &OTHER) {
                if (this != &OTHER) {
                    _copyFromSrc(OTHER);
                }
                return *this;
            }
            MD5Weight(MD5Weight&& src) noexcept {
                _moveFromSrc(src);
            }
            MD5Weight& operator=(MD5Weight&& src) noexcept {
                if (this != &src) {
                    _moveFromSrc(src);
                }
                return *this;
            }
        private:
            void _copyFromSrc(const MD5Weight &src) {
                this->joint = src.joint;
                this->bias = src.bias;
                this->position = src.position;
            }
            void _moveFromSrc(MD5Weight &src) {
                _copyFromSrc(src);

                src.joint = MD5Joint::NULL_JOINT;
                src.bias = 0.0f;
                src.position = glm::vec3(0.0f, 0.0f, 0.0f);
            }
        };

        /**
         * @brief texture handle for the model
         */
        struct MD5Texture {
            /**
             * @brief max length of joint name string
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

            MD5Texture(const MD5Texture &OTHER) {
                _copyFromSrc(OTHER);
            }
            MD5Texture& operator=(const MD5Texture &OTHER) {
                if (this != &OTHER) {
                    _copyFromSrc(OTHER);
                }
                return *this;
            }
            MD5Texture(MD5Texture&& src) noexcept {
                _moveFromSrc(src);
            }
            MD5Texture& operator=(MD5Texture&& src) noexcept {
                if (this != &src) {
                    _moveFromSrc(src);
                }
                return *this;
            }
        private:
            void _copyFromSrc(const MD5Texture &src) {
                this->texHandle = src.texHandle;
                strncpy(this->filename, src.filename, MAX_NAME_LENGTH);
            }
            void _moveFromSrc(MD5Texture& src) {
                _copyFromSrc(src);

                src.texHandle = 0;
                strncpy(src.filename, "", MAX_NAME_LENGTH);
            }
        };

        /**
         * @brief mesh that comprises the model's skin
         */
        struct MD5Mesh {
            /**
             * @brief array of vertices comprising the mesh
             */
            MD5Vertex *vertices = nullptr;
            /**
             * @brief array triangles comprising the mesh
             */
            MD5Triangle *triangles = nullptr;
            /**
             * @brief array of weights to determine vertex position based on joint positions
             */
            MD5Weight *weights = nullptr;
            /**
             * @brief texture map array
             */
            MD5Texture textures[4];
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
             * @brief base filename for all textures applied to mesh
             */
            char shader[512] = "";
        };

        // md5anim types
        /**
         * @brief information pertaining to each animation joint
         */
        struct MD5JointInfo {
            /**
             * @brief joint identifier
             */
            char name[256] = "";
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

            MD5BaseFrameJoint(const MD5BaseFrameJoint& OTHER) {
                _copyFromSrc(OTHER);
            }
            MD5BaseFrameJoint& operator=(const MD5BaseFrameJoint &OTHER) {
                if (this != &OTHER) {
                    _copyFromSrc(OTHER);
                }
                return *this;
            }
            MD5BaseFrameJoint(MD5BaseFrameJoint&& src) noexcept {
                _moveFromSrc(src);
            }
            MD5BaseFrameJoint& operator=(MD5BaseFrameJoint &src) noexcept {
                if (this != &src) {
                    _moveFromSrc(src);
                }
                return *this;
            }
        private:
            void _copyFromSrc(const MD5BaseFrameJoint &src) {
                this->position = src.position;
                this->orientation = src.orientation;
            }
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
        };

        /**
         * @brief stores an entire animation sequence for a given MD5 Model
         */
        struct MD5Animation {
            /**
             * @brief number of frames in the animation
             */
            GLint numFrames = 0;
            /**
             * @brief number of joints of the frame skeletons
             * @note must be the same as the number of joints on the model the animation is applied to
             */
            GLint numJoints = 0;
            /**
             * @brief number of frames per second to draw for the animation
             * @note duration of a frame can be computed by inverting the frame rate
             */
            GLint frameRate = 0;

            /**
             * @brief skeletal pose for each frame
             */
            MD5Joint **skeletonFrames = nullptr;
            /**
             * @brief bounding box for each frame
             */
            MD5BoundingBox *boundingBoxes = nullptr;
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
        };

    public:
        /**
         * @brief initializes an empty MD5 Model
         * @note need to call loadMD5Model() or readMD5Model() after construction to actually load in a mesh file
         */
        MD5Model();
        /**
         * @brief deallocates any used memory on the CPU and GPU
         */
        ~MD5Model();

        /**
         * @brief do not allow MD5 models to be copied
         */
        MD5Model(const MD5Model&) = delete;
        /**
         * @brief do not allow MD5 models to be copied
         */
        MD5Model& operator=(const MD5Model&) = delete;

        /**
         * @brief do not allow MD5 models to be moved
         */
        MD5Model(MD5Model&&) = delete;
        /**
         * @brief do not allow MD5 models to be moved
         */
        MD5Model& operator=(MD5Model&&) = delete;

        /**
         * @brief loads a corresponding md5mesh and md5anim file to the object
         * @param MD5_MESH_FILE name of file to load mesh from
         * @param MD5_ANIM_FILE name of file to load animation from
         * @returns true if both mesh and animation loaded successfully and are compatible
         */
        [[maybe_unused]] bool loadMD5Model(const char* MD5_MESH_FILE, const char* MD5_ANIM_FILE = "");

        /**
         * @brief returns if the MD5 Model has an accompanying animation
         * @returns true if animation exists for model
         */
        [[nodiscard]] bool isAnimated() const { return _isAnimated; }

        // md5mesh prototypes
        /**
         * @brief parses md5mesh file and allocates corresponding mesh data
         * @param FILENAME *.md5mesh file to load
         * @returns true if file parsed successfully
         */
        [[nodiscard]] bool readMD5Model(const char* FILENAME);
        /**
         * @brief binds model VBOs to attribute pointer locations
         * @param vPosAttribLoc location of vertex position attribute
         * @param vColorAttribLoc location of vertex color attribute
         * @param vTexCoordAttribLoc location of vertex texture coordinate attribute
         * @note color attribute used when drawing the skeleton
         * @note texCoord attribute used when drawing the mesh
         */
        [[maybe_unused]]void allocVertexArrays(GLuint vPosAttribLoc, GLuint vColorAttribLoc, GLuint vTexCoordAttribLoc);
        /**
         * @brief draws all the meshes that make up the model
         */
        [[maybe_unused]] void draw() const;
        /**
         * @brief draws the skeleton joints (as points) and bones (as lines)
         */
        [[maybe_unused]] void drawSkeleton() const;

        // md5anim prototypes
        /**
         * @brief reads in an animation sequence from an external file
         * @param filename *.md5anim file to open
         * @returns true iff mesh and animation are compatible
         */
        [[nodiscard]] bool readMD5Anim(const char* filename);
        /**
         * @brief advances the model forward in its animation sequence the corresponding amount of time based on frame rate
         * @param dt delta time since last frame
         */
        void animate(GLfloat dt);

    private:
        MD5Joint* _baseSkeleton;
        MD5Mesh* _meshes;

        GLint _numJoints;
        GLint _numMeshes;

        // vertex array related stuff
        GLint _maxVertices;
        GLint _maxTriangles;

        glm::vec3* _vertexArray;
        glm::vec2* _texelArray;
        GLuint* _vertexIndicesArray;

        GLuint _vao;
        GLuint _vbo[2];

        GLuint _skeletonVAO;
        GLuint _skeletonVBO;

        /**
         * @brief the MD5 skeletal joint data
         */
        MD5Joint* _skeleton;
        /**
         * @brief the MD5 animation frame sequence
         */
        MD5Animation _animation;
        /**
         * @brief flag stating if the loaded MD5 model has a corresponding animation or not
         */
        bool _isAnimated;
        /**
         * @brief current animation frame state
         */
        MD5AnimationState _animationInfo;

        void _prepareMesh(const MD5Mesh* pMESH) const;
        void _drawMesh(const MD5Mesh* pMESH) const;
        [[nodiscard]] bool _checkAnimValidity() const;
        static void _buildFrameSkeleton(const MD5JointInfo* pJOINT_INFOS,
                                        const MD5BaseFrameJoint* pBASE_FRAME,
                                        const GLfloat* pANIM_FRAME_DATA,
                                        MD5Joint* pSkeletonFrame,
                                        GLint NUM_JOINTS);
        void _interpolateSkeletons(GLfloat interp);
        void _freeModel();
        void _freeVertexArrays();
        void _freeAnim();
    };
}

//----------------------------------------------------------------------------------------------------

inline CSCI441::MD5Model::MD5Model()
{
    _baseSkeleton = nullptr;
    _meshes = nullptr;
    _numJoints = 0;
    _numMeshes = 0;
    _maxVertices = 0;
    _maxTriangles = 0;
    _vertexArray = nullptr;
    _texelArray = nullptr;
    _vertexIndicesArray = nullptr;
    _vao = 0;
    _vbo[0] = 0;
    _vbo[1] = 0;
    _skeletonVAO = 0;
    _skeletonVBO = 0;
    _animation = MD5Animation();
    _skeleton = nullptr;
    _animationInfo = MD5AnimationState();
    _isAnimated = false;
}

inline CSCI441::MD5Model::~MD5Model()
{
    _freeVertexArrays();
    _freeAnim();
    _freeModel();
}

// load our MD5 model
[[maybe_unused]]
inline bool
CSCI441::MD5Model::loadMD5Model(
        const char* MD5_MESH_FILE,
        const char* MD5_ANIM_FILE
) {
    // Load MD5 _model file
    if( readMD5Model(MD5_MESH_FILE) ) {
        // if MD5 animation file name provided
        if(strcmp(MD5_ANIM_FILE, "") != 0 ) {
            // Load MD5 animation file
            if( !readMD5Anim(MD5_ANIM_FILE) ) {
                return false;
            }
        }
        if( !isAnimated() ) {
            printf ("[.MD5_ANIM_FILE]: no animation loaded.\n");
        }
    } else {
        return false;
    }
    return true;
}

// Load an MD5 model from file.
inline bool
CSCI441::MD5Model::readMD5Model(
        const char* FILENAME
) {
    FILE *fp;
    char buff[512];
    GLint version;
    GLint currentMesh = 0;
    GLint i;
    unsigned long uli;

    GLint totalVertices = 0;
    GLint totalWeights = 0;
    GLint totalTriangles = 0;

    GLfloat minX =  999999, minY =  999999, minZ =  999999;
    GLfloat maxX = -999999, maxY = -999999, maxZ = -999999;

    printf("[.md5mesh]: about to read %s\n", FILENAME );

    fp = fopen(FILENAME, "rb" );
    if( !fp ) {
        fprintf (stderr, "[.md5mesh]: Error: couldn't open \"%s\"!\n", FILENAME);
        return false;
    }

    while( !feof(fp) ) {
        // Read whole line
        fgets( buff, sizeof(buff), fp );

        if( sscanf(buff, " MD5Version %d", &version) == 1 ) {
            if( version != 10 ) {
                // Bad version
                fprintf (stderr, "[.md5mesh]: Error: bad model version\n");
                fclose (fp);
                return false;
            }
        } else if( sscanf(buff, " numJoints %d", &_numJoints) == 1 ) {
            if( _numJoints > 0 ) {
                // Allocate memory for base skeleton joints
                _baseSkeleton = new MD5Joint[_numJoints];
            }
        } else if( sscanf(buff, " numMeshes %d", &_numMeshes) == 1 ) {
            if( _numMeshes > 0 ) {
                // Allocate memory for meshes
                _meshes = new MD5Mesh[_numMeshes];
            }
        } else if( strncmp(buff, "joints {", 8) == 0 ) {
            // Read each joint
            for(i = 0; i < _numJoints; ++i) {
                MD5Joint *joint = &_baseSkeleton[i];

                // Read whole line
                fgets( buff, sizeof(buff), fp );

                if( sscanf(buff, "%s %d ( %f %f %f ) ( %f %f %f )",
                           joint->name, &joint->parent,
                           &joint->position[0], &joint->position[1], &joint->position[2],
                           &joint->orientation[0],&joint->orientation[1], &joint->orientation[2]) == 8
                        ) {
                    // Compute the w component
                    joint->orientation.w = glm::extractRealComponent(joint->orientation);
                }
            }
        } else if( strncmp(buff, "mesh {", 6) == 0 ) {
            MD5Mesh *mesh = &_meshes[currentMesh];
            GLint vert_index = 0;
            GLint tri_index = 0;
            GLint weight_index = 0;
            GLfloat fdata[4];
            GLint idata[3];

            while( buff[0] != '}' && !feof(fp) ) {
                // Read whole line
                fgets( buff, sizeof(buff), fp );

                if( strstr( buff, "shader ") ) {
                    GLint quote = 0, j = 0;

                    // Copy the shader name without the quote marks
                    for(uli = 0; uli < sizeof(buff) && (quote < 2); ++uli) {
                        if( buff[uli] == '\"' )
                            quote++;

                        if( (quote == 1) && (buff[uli] != '\"') ) {
                            mesh->shader[j] = buff[uli];
                            j++;
                        }
                    }
                    // there was a shader name
                    if( j > 0 ) {
                        // diffuse map
                        strcpy(mesh->textures[MD5Mesh::TextureMap::DIFFUSE].filename, mesh->shader);
                        strcat(mesh->textures[MD5Mesh::TextureMap::DIFFUSE].filename, ".tga");
                        mesh->textures[MD5Mesh::TextureMap::DIFFUSE].texHandle = CSCI441::TextureUtils::loadAndRegisterTexture( mesh->textures[MD5Mesh::TextureMap::DIFFUSE].filename, GL_LINEAR, GL_LINEAR_MIPMAP_LINEAR, GL_REPEAT, GL_REPEAT, GL_FALSE, GL_FALSE);
                        if( mesh->textures[MD5Mesh::TextureMap::DIFFUSE].texHandle == 0 ) {
                            strcpy(mesh->textures[MD5Mesh::TextureMap::DIFFUSE].filename, mesh->shader);
                            strcat(mesh->textures[MD5Mesh::TextureMap::DIFFUSE].filename, "_d.tga");
                            mesh->textures[MD5Mesh::TextureMap::DIFFUSE].texHandle = CSCI441::TextureUtils::loadAndRegisterTexture( mesh->textures[MD5Mesh::TextureMap::DIFFUSE].filename, GL_LINEAR, GL_LINEAR_MIPMAP_LINEAR, GL_REPEAT, GL_REPEAT, GL_FALSE, GL_FALSE );
                            if( mesh->textures[MD5Mesh::TextureMap::DIFFUSE].texHandle == 0 ) {
                                strcpy(mesh->textures[MD5Mesh::TextureMap::DIFFUSE].filename, mesh->shader);
                                strcat(mesh->textures[MD5Mesh::TextureMap::DIFFUSE].filename, ".png");
                                mesh->textures[MD5Mesh::TextureMap::DIFFUSE].texHandle = CSCI441::TextureUtils::loadAndRegisterTexture(mesh->textures[MD5Mesh::TextureMap::DIFFUSE].filename, GL_LINEAR, GL_LINEAR_MIPMAP_LINEAR, GL_REPEAT, GL_REPEAT, GL_FALSE, GL_FALSE );
                                if( mesh->textures[MD5Mesh::TextureMap::DIFFUSE].texHandle == 0 ) {
                                    printf("[.md5mesh | ERROR]: Could not load diffuse map %s\n", mesh->shader);
                                }
                            }
                        }

                        // specular map
                        strcpy(mesh->textures[MD5Mesh::TextureMap::SPECULAR].filename, mesh->shader);
                        strcat(mesh->textures[MD5Mesh::TextureMap::SPECULAR].filename, "_s.tga");
                        mesh->textures[MD5Mesh::TextureMap::SPECULAR].texHandle = CSCI441::TextureUtils::loadAndRegisterTexture( mesh->textures[MD5Mesh::TextureMap::SPECULAR].filename, GL_LINEAR, GL_LINEAR_MIPMAP_LINEAR, GL_REPEAT, GL_REPEAT, GL_FALSE, GL_FALSE );
                        if( mesh->textures[MD5Mesh::TextureMap::SPECULAR].texHandle == 0 ) {
                            strcpy(mesh->textures[MD5Mesh::TextureMap::SPECULAR].filename, mesh->shader);
                            strcat(mesh->textures[MD5Mesh::TextureMap::SPECULAR].filename, "_s.png");
                            mesh->textures[MD5Mesh::TextureMap::SPECULAR].texHandle = CSCI441::TextureUtils::loadAndRegisterTexture( mesh->textures[MD5Mesh::TextureMap::SPECULAR].filename, GL_LINEAR, GL_LINEAR_MIPMAP_LINEAR, GL_REPEAT, GL_REPEAT, GL_FALSE, GL_FALSE );
                            if( mesh->textures[MD5Mesh::TextureMap::DIFFUSE].texHandle == 0 ) {
                                printf("[.md5mesh | ERROR]: Could not load specular map %s\n", mesh->shader);
                            }
                        }

                        // normal map
                        strcpy(mesh->textures[MD5Mesh::TextureMap::NORMAL].filename, mesh->shader);
                        strcat(mesh->textures[MD5Mesh::TextureMap::NORMAL].filename, "_local.tga");
                        mesh->textures[MD5Mesh::TextureMap::NORMAL].texHandle = CSCI441::TextureUtils::loadAndRegisterTexture( mesh->textures[MD5Mesh::TextureMap::NORMAL].filename, GL_LINEAR, GL_LINEAR_MIPMAP_LINEAR, GL_REPEAT, GL_REPEAT, GL_FALSE, GL_FALSE );
                        if( mesh->textures[MD5Mesh::TextureMap::NORMAL].texHandle == 0 ) {
                            strcpy(mesh->textures[MD5Mesh::TextureMap::NORMAL].filename, mesh->shader);
                            strcat(mesh->textures[MD5Mesh::TextureMap::NORMAL].filename, "_local.png");
                            mesh->textures[MD5Mesh::TextureMap::NORMAL].texHandle = CSCI441::TextureUtils::loadAndRegisterTexture( mesh->textures[MD5Mesh::TextureMap::NORMAL].filename, GL_LINEAR, GL_LINEAR_MIPMAP_LINEAR, GL_REPEAT, GL_REPEAT, GL_FALSE, GL_FALSE );
                            if( mesh->textures[MD5Mesh::TextureMap::DIFFUSE].texHandle == 0 ) {
                                printf("[.md5mesh | ERROR]: Could not load normal map %s\n", mesh->shader);
                            }
                        }

                        // height map
                        strcpy(mesh->textures[MD5Mesh::TextureMap::HEIGHT].filename, mesh->shader);
                        strcat(mesh->textures[MD5Mesh::TextureMap::HEIGHT].filename, "_h.tga");
                        mesh->textures[MD5Mesh::TextureMap::HEIGHT].texHandle = CSCI441::TextureUtils::loadAndRegisterTexture( mesh->textures[MD5Mesh::TextureMap::HEIGHT].filename, GL_LINEAR, GL_LINEAR_MIPMAP_LINEAR, GL_REPEAT, GL_REPEAT, GL_FALSE, GL_FALSE );
                        if( mesh->textures[MD5Mesh::TextureMap::HEIGHT].texHandle == 0 ) {
                            strcpy(mesh->textures[MD5Mesh::TextureMap::HEIGHT].filename, mesh->shader);
                            strcat(mesh->textures[MD5Mesh::TextureMap::HEIGHT].filename, "_h.png");
                            mesh->textures[MD5Mesh::TextureMap::HEIGHT].texHandle = CSCI441::TextureUtils::loadAndRegisterTexture( mesh->textures[MD5Mesh::TextureMap::HEIGHT].filename, GL_LINEAR, GL_LINEAR_MIPMAP_LINEAR, GL_REPEAT, GL_REPEAT, GL_FALSE, GL_FALSE );
                            if( mesh->textures[MD5Mesh::TextureMap::DIFFUSE].texHandle == 0 ) {
                                printf("[.md5mesh | ERROR]: Could not load height map %s\n", mesh->shader);
                            }
                        }
                    }
                } else if( sscanf(buff, " numverts %d", &mesh->numVertices) == 1 ) {
                    if( mesh->numVertices > 0 ) {
                        // Allocate memory for vertices
                        mesh->vertices = new MD5Vertex[mesh->numVertices];
                    }

                    if( mesh->numVertices > _maxVertices )
                        _maxVertices = mesh->numVertices;

                    totalVertices += mesh->numVertices;
                } else if( sscanf(buff, " numtris %d", &mesh->numTriangles) == 1 ) {
                    if( mesh->numTriangles > 0 ) {
                        // Allocate memory for triangles
                        mesh->triangles = new MD5Triangle[mesh->numTriangles];
                    }

                    if( mesh->numTriangles > _maxTriangles )
                        _maxTriangles = mesh->numTriangles;

                    totalTriangles += mesh->numTriangles;
                } else if( sscanf(buff, " numweights %d", &mesh->numWeights) == 1 ) {
                    if( mesh->numWeights > 0 ) {
                        // Allocate memory for vertex weights
                        mesh->weights = new MD5Weight[mesh->numWeights];
                    }

                    totalWeights += mesh->numWeights;
                } else if( sscanf(buff, " vert %d ( %f %f ) %d %d",
                                  &vert_index,
                                  &fdata[0], &fdata[1],
                                  &idata[0], &idata[1]) == 5
                        ) {
                    // Copy vertex data
                    mesh->vertices[vert_index].texCoord.s = fdata[0];
                    mesh->vertices[vert_index].texCoord.t = fdata[1];
                    mesh->vertices[vert_index].start = idata[0];
                    mesh->vertices[vert_index].count = idata[1];
                } else if( sscanf(buff, " tri %d %d %d %d",
                                  &tri_index,
                                  &idata[0], &idata[1], &idata[2]) == 4
                        ) {
                    // Copy triangle data
                    mesh->triangles[tri_index ].index[0] = idata[0];
                    mesh->triangles[tri_index ].index[1] = idata[1];
                    mesh->triangles[tri_index ].index[2] = idata[2];
                } else if( sscanf(buff, " weight %d %d %f ( %f %f %f )",
                                  &weight_index, &idata[0], &fdata[3],
                                  &fdata[0], &fdata[1], &fdata[2]) == 6
                        ) {
                    // Copy vertex data
                    mesh->weights[weight_index].joint  = idata[0];
                    mesh->weights[weight_index].bias   = fdata[3];
                    mesh->weights[weight_index].position[0] = fdata[0];
                    mesh->weights[weight_index].position[1] = fdata[1];
                    mesh->weights[weight_index].position[2] = fdata[2];

                    if( fdata[0] < minX ) { minX = fdata[0]; }
                    if( fdata[0] > maxX ) { maxX = fdata[0]; }
                    if( fdata[1] < minY ) { minY = fdata[1]; }
                    if( fdata[1] > maxY ) { maxY = fdata[1]; }
                    if( fdata[2] < minZ ) { minZ = fdata[2]; }
                    if( fdata[2] > maxZ ) { maxZ = fdata[2]; }
                }
            }

            currentMesh++;
        }
    }

    fclose(fp);

    _skeleton = _baseSkeleton;

    printf("[.md5mesh]: finished reading %s\n", FILENAME );
    printf("[.md5mesh]: read in %d meshes, %d joints, %d vertices, %d weights, and %d triangles\n", _numMeshes, _numJoints, totalVertices, totalWeights, totalTriangles );
    printf( "[.md5mesh]: base pose %f units across in X, %f units across in Y, %f units across in Z\n", (maxX - minX), (maxY-minY), (maxZ - minZ) );
    printf( "\n" );

    return true;
}

//Free resources allocated for the model.
inline void
CSCI441::MD5Model::_freeModel()
{
    delete _baseSkeleton;
    _baseSkeleton = nullptr;

    // Free mesh data
    for(GLint i = 0; i < _numMeshes; ++i) {
        delete _meshes[i].vertices;
        _meshes[i].vertices = nullptr;

        delete _meshes[i].triangles;
        _meshes[i].triangles = nullptr;

        delete _meshes[i].weights;
        _meshes[i].weights = nullptr;
    }

    delete _meshes;
    _meshes = nullptr;
}

[[maybe_unused]]
inline void
CSCI441::MD5Model::draw() const
{
    // Draw each mesh of the model
    for(GLint i = 0; i < _numMeshes; ++i) {
        MD5Mesh mesh = _meshes[i];                  // get the mesh
        _prepareMesh(&mesh);                // do some preprocessing on it
        _drawMesh(&mesh);
    }
}

// Prepare a mesh for drawing.  Compute mesh's final vertex positions
// given a skeleton.  Put the vertices in vertex arrays.
inline void
CSCI441::MD5Model::_prepareMesh(
        const MD5Mesh *pMESH
) const {
    GLint i, j, k;

    // Setup vertex indices
    for(k = 0, i = 0; i < pMESH->numTriangles; ++i) {
        for(j = 0; j < 3; ++j, ++k)
            _vertexIndicesArray[k] = pMESH->triangles[i].index[j];
    }

    // Setup vertices
    for(i = 0; i < pMESH->numVertices; ++i) {
        glm::vec3 finalVertex = {0.0f, 0.0f, 0.0f };

        // Calculate final vertex to draw with weights
        for(j = 0; j < pMESH->vertices[i].count; ++j) {
            const MD5Weight *weight = &pMESH->weights[pMESH->vertices[i].start + j];
            const MD5Joint  *joint  = &_skeleton[weight->joint];

            // Calculate transformed vertex for this weight
            glm::vec3 weightedVertex;
            weightedVertex = glm::rotate(joint->orientation, glm::vec4(weight->position, 0.0f));

            // The sum of all weight->bias should be 1.0
            finalVertex.x += (joint->position.x + weightedVertex.x) * weight->bias;
            finalVertex.y += (joint->position.y + weightedVertex.y) * weight->bias;
            finalVertex.z += (joint->position.z + weightedVertex.z) * weight->bias;
        }

        _vertexArray[i].x = finalVertex.x;
        _vertexArray[i].y = finalVertex.y;
        _vertexArray[i].z = finalVertex.z;

        _texelArray[i].s = pMESH->vertices[i].texCoord.s;
        _texelArray[i].t = pMESH->vertices[i].texCoord.t;
    }

    glBindVertexArray(_vao );
    glBindBuffer(GL_ARRAY_BUFFER, _vbo[0] );
    glBufferSubData(GL_ARRAY_BUFFER, 0, sizeof(glm::vec3) * pMESH->numVertices, &_vertexArray[0] );
    glBufferSubData(GL_ARRAY_BUFFER, sizeof(glm::vec3) * _maxVertices, sizeof(glm::vec2) * pMESH->numVertices, &_texelArray[0] );
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, _vbo[1] );
    glBufferSubData(GL_ELEMENT_ARRAY_BUFFER, 0, sizeof(GLuint) * pMESH->numTriangles * 3, _vertexIndicesArray );
}

inline void
CSCI441::MD5Model::_drawMesh(
        const MD5Mesh *pMESH
) const {
    // Bind Diffuse Map
    glBindTexture(GL_TEXTURE_2D, pMESH->textures[MD5Mesh::TextureMap::DIFFUSE].texHandle );

    glBindVertexArray(_vao );
    glDrawElements(GL_TRIANGLES, pMESH->numTriangles * 3, GL_UNSIGNED_INT, (void*)nullptr );
}

[[maybe_unused]]
inline void
CSCI441::MD5Model::allocVertexArrays(
        GLuint vPosAttribLoc,
        GLuint vColorAttribLoc,
        GLuint vTexCoordAttribLoc
) {
    _vertexArray = new glm::vec3[_maxVertices];
    _texelArray = new glm::vec2[_maxVertices];
    _vertexIndicesArray = new GLuint[_maxTriangles * 3];

    glGenVertexArrays( 1, &_vao );
    glBindVertexArray(_vao );

    glGenBuffers(2, _vbo );
    glBindBuffer(GL_ARRAY_BUFFER, _vbo[0] );
    glBufferData(GL_ARRAY_BUFFER, sizeof(glm::vec3) * _maxVertices + sizeof(glm::vec2) * _maxVertices, nullptr, GL_DYNAMIC_DRAW );

    glEnableVertexAttribArray( vPosAttribLoc );
    glVertexAttribPointer( vPosAttribLoc, 3, GL_FLOAT, GL_FALSE, 0, (void*)nullptr );

    glEnableVertexAttribArray( vTexCoordAttribLoc );
    glVertexAttribPointer( vTexCoordAttribLoc, 2, GL_FLOAT, GL_FALSE, 0, (void*)(sizeof(glm::vec3) * _maxVertices) );

    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, _vbo[1] );
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(GLuint) * _maxTriangles * 3, nullptr, GL_DYNAMIC_DRAW );

    printf("[.md5mesh]: Model VAO/VBO/IBO registered at %u/%u/%u\n", _vao, _vbo[0], _vbo[1] );

    glGenVertexArrays( 1, &_skeletonVAO );
    glBindVertexArray(_skeletonVAO );

    glGenBuffers( 1, &_skeletonVBO );
    glBindBuffer(GL_ARRAY_BUFFER, _skeletonVBO );
    glBufferData(GL_ARRAY_BUFFER, sizeof(glm::vec3) * _numJoints * 3 * 2, nullptr, GL_DYNAMIC_DRAW );

    glEnableVertexAttribArray( vPosAttribLoc ); // vPos
    glVertexAttribPointer( vPosAttribLoc, 3, GL_FLOAT, GL_FALSE, 0, (void*)nullptr );

    glEnableVertexAttribArray( vColorAttribLoc ); // vColor
    glVertexAttribPointer( vColorAttribLoc, 3, GL_FLOAT, GL_FALSE, 0, (void*)(sizeof(glm::vec3) * _numJoints * 3) );

    printf("[.md5mesh]: Skeleton VAO/VBO registered at %u/%u\n", _skeletonVAO, _skeletonVBO );
}

inline void
CSCI441::MD5Model::_freeVertexArrays()
{
    delete[] _vertexArray;
    _vertexArray = nullptr;

    delete[] _vertexIndicesArray;
    _vertexIndicesArray = nullptr;

    delete[] _texelArray;
    _texelArray = nullptr;

    glDeleteVertexArrays( 1, &_vao );
    glDeleteBuffers(2, _vbo );
    glDeleteVertexArrays( 1, &_skeletonVAO );
    glDeleteBuffers( 1, &_skeletonVBO );
}

// Draw the skeleton as lines and points (for joints).
[[maybe_unused]]
inline void
CSCI441::MD5Model::drawSkeleton() const
{
    glBindVertexArray(_skeletonVAO );
    glBindBuffer(GL_ARRAY_BUFFER, _skeletonVBO );

    glm::vec3 jointColor = {1.0f, 1.0f, 0.0f };
    glm::vec3 boneColor = {1.0f, 0.0f, 1.0f };

    // put in points for joints
    for(GLint i = 0; i < _numJoints; ++i ) {
        glBufferSubData(GL_ARRAY_BUFFER, i * sizeof(glm::vec3), sizeof(glm::vec3), &(_skeleton[i].position) );
        glBufferSubData(GL_ARRAY_BUFFER, i * sizeof(glm::vec3) + sizeof(glm::vec3) * _numJoints * 3, sizeof(glm::vec3), &jointColor[0]);
    }

    // put in lines for bones
    GLint numBones = 0;
    for(GLint i = 0; i < _numJoints; ++i ) {
        if( _skeleton[i].parent != MD5Joint::NULL_JOINT ) {
            glBufferSubData(GL_ARRAY_BUFFER, sizeof(glm::vec3) * _numJoints + (i * 2) * sizeof(glm::vec3), sizeof(glm::vec3), &(_skeleton[_skeleton[i].parent].position) );
            glBufferSubData(GL_ARRAY_BUFFER, sizeof(glm::vec3) * _numJoints + (i * 2) * sizeof(glm::vec3) + sizeof(glm::vec3) * _numJoints * 3, sizeof(glm::vec3), &boneColor[0]);

            glBufferSubData(GL_ARRAY_BUFFER, sizeof(glm::vec3) * _numJoints + (i * 2) * sizeof(glm::vec3) + sizeof(glm::vec3), sizeof(glm::vec3), &(_skeleton[i].position) );
            glBufferSubData(GL_ARRAY_BUFFER, sizeof(glm::vec3) * _numJoints + (i * 2) * sizeof(glm::vec3) + sizeof(glm::vec3) + sizeof(glm::vec3) * _numJoints * 3, sizeof(glm::vec3), &boneColor[0]);
            numBones++;
        }
    }

    glPointSize (5.0f);
    glDrawArrays(GL_POINTS, 0, _numJoints );
    glPointSize(1.0f);

    glLineWidth( 3.0f );
    glDrawArrays(GL_LINES, _numJoints, numBones * 2 );
    glLineWidth(1.0f);
}

// Check if an animation can be used for a given model.  Model's
// skeleton and animation's skeleton must match.
inline bool
CSCI441::MD5Model::_checkAnimValidity() const
{
    // md5mesh and md5anim must have the same number of joints
    if( _numJoints != _animation.numJoints ) {
        printf("\n[.md5anim]: skeleton and animation do not have same number of joints.  cannot apply animation to skeleton\n\n");
        return false;
    }

    // We just check with frame[0]
    for(GLint i = 0; i < _numJoints; ++i) {
        // Joints must have the same parent index
        if (_baseSkeleton[i].parent != _animation.skeletonFrames[0][i].parent) {
            printf("\n[.md5anim]: skeleton and animation joints do not have same parent index.  cannot apply animation to skeleton\n\n");
            return false;
        }

        // Joints must have the same name
        if (strcmp (_baseSkeleton[i].name, _animation.skeletonFrames[0][i].name) != 0) {
            printf("\n[.md5anim]: skeleton and animation joints do not have same name.  cannot apply animation to skeleton\n\n");
            return false;
        }
    }

    printf("\n[.md5anim]: skeleton and animation match.  animation can be applied to skeleton\n\n");
    return true;
}

// Build _skeleton for a given frame data.
inline void
CSCI441::MD5Model::_buildFrameSkeleton(
        const MD5JointInfo* pJOINT_INFOS,
        const MD5BaseFrameJoint* pBASE_FRAME,
        const GLfloat* pANIM_FRAME_DATA,
        MD5Joint* pSkeletonFrame,
        const GLint NUM_JOINTS
) {
    if(pJOINT_INFOS == nullptr
       || pBASE_FRAME == nullptr
       || pANIM_FRAME_DATA == nullptr
       || pSkeletonFrame == nullptr) return;

    GLint i;

    for(i = 0; i < NUM_JOINTS; ++i) {
        const MD5BaseFrameJoint *baseJoint = &pBASE_FRAME[i];
        glm::vec3 animatedPosition = baseJoint->position;
        glm::quat animatedOrientation = baseJoint->orientation;
        GLint j = 0;

        // Tx
        if(pJOINT_INFOS[i].flags & 1 ) {
            animatedPosition.x = pANIM_FRAME_DATA[pJOINT_INFOS[i].startIndex + j];
            ++j;
        }

        // Ty
        if(pJOINT_INFOS[i].flags & 2 ) {
            animatedPosition.y = pANIM_FRAME_DATA[pJOINT_INFOS[i].startIndex + j];
            ++j;
        }

        // Tz
        if(pJOINT_INFOS[i].flags & 4 ) {
            animatedPosition.z = pANIM_FRAME_DATA[pJOINT_INFOS[i].startIndex + j];
            ++j;
        }

        // Qx
        if(pJOINT_INFOS[i].flags & 8 ) {
            animatedOrientation.x = pANIM_FRAME_DATA[pJOINT_INFOS[i].startIndex + j];
            ++j;
        }

        // Qy
        if(pJOINT_INFOS[i].flags & 16 ) {
            animatedOrientation.y = pANIM_FRAME_DATA[pJOINT_INFOS[i].startIndex + j];
            ++j;
        }

        // Qz
        if(pJOINT_INFOS[i].flags & 32 ) {
            animatedOrientation.z = pANIM_FRAME_DATA[pJOINT_INFOS[i].startIndex + j];
        }

        // Compute orientation quaternion's w value
        animatedOrientation.w = glm::extractRealComponent(animatedOrientation);

        // NOTE: we assume that this joint's parent has
        // already been calculated, i.e. joint's ID should
        // never be smaller than its parent ID.
        MD5Joint *thisJoint = &pSkeletonFrame[i];

        GLint parent = pJOINT_INFOS[i].parent;
        thisJoint->parent = parent;
        strcpy (thisJoint->name, pJOINT_INFOS[i].name);

        // Has parent?
        if( thisJoint->parent == MD5Joint::NULL_JOINT ) {
            thisJoint->position = animatedPosition;
            thisJoint->orientation = animatedOrientation;
        } else {
            MD5Joint *parentJoint = &pSkeletonFrame[parent];
            glm::vec3 rotatedPosition = glm::rotate(parentJoint->orientation, glm::vec4(animatedPosition, 0.0f));

            // Add positions
            thisJoint->position = parentJoint->position + rotatedPosition;

            // Concatenate rotations
            thisJoint->orientation = glm::normalize( glm::cross(parentJoint->orientation, animatedOrientation) );
        }
    }
}

// Load an MD5 animation from file.
inline bool
CSCI441::MD5Model::readMD5Anim(
        const char *filename
) {
    char buff[512];
    MD5JointInfo *jointInfos = nullptr;
    MD5BaseFrameJoint *baseFrame = nullptr;
    GLfloat *animFrameData = nullptr;
    GLint version;
    GLint numAnimatedComponents;
    GLint frameIndex;
    GLint i;

    printf( "[.md5anim]: about to read %s\n", filename );

    FILE *fp = fopen( filename, "rb" );
    if( !fp ) {
        fprintf (stderr, "[.md5anim]: Error: couldn't open \"%s\"!\n", filename);
        return false;
    }

    while( !feof(fp) ) {
        // Read whole line
        fgets( buff, sizeof(buff), fp );

        if( sscanf(buff, " MD5Version %d", &version) == 1 ) {
            if( version != 10 ) {
                // Bad version
                fprintf (stderr, "[.md5anim]: Error: bad animation version\n");
                fclose (fp);
                return false;
            }
        } else if( sscanf(buff, " numFrames %d", &_animation.numFrames) == 1 ) {
            // Allocate memory for skeleton frames and bounding boxes
            if( _animation.numFrames > 0 ) {
                _animation.skeletonFrames = new MD5Joint*[_animation.numFrames];
                _animation.boundingBoxes = new MD5BoundingBox[_animation.numFrames];
            }
        } else if( sscanf(buff, " numJoints %d", &_animation.numJoints) == 1 ) {
            if( _animation.numJoints > 0 ) {
                for(i = 0; i < _animation.numFrames; ++i) {
                    // Allocate memory for joints of each frame
                    _animation.skeletonFrames[i] = new MD5Joint[_animation.numJoints];
                }

                // Allocate temporary memory for building skeleton frames
                jointInfos = new MD5JointInfo[_animation.numJoints];

                baseFrame = new MD5BaseFrameJoint[_animation.numJoints];
            }
        } else if( sscanf(buff, " frameRate %d", &_animation.frameRate) == 1 ) {

        } else if( sscanf(buff, " numAnimatedComponents %d", &numAnimatedComponents) == 1 ) {
            if( numAnimatedComponents > 0 ) {
                // Allocate memory for animation frame data
                animFrameData = new GLfloat[numAnimatedComponents];
            }
        } else if( strncmp(buff, "hierarchy {", 11) == 0 ) {
            for(i = 0; i < _animation.numJoints; ++i) {
                // Read whole line
                fgets( buff, sizeof(buff), fp );

                // Read joint info
                sscanf(buff, " %s %d %d %d",
                       jointInfos[i].name, &jointInfos[i].parent,
                       &jointInfos[i].flags, &jointInfos[i].startIndex);
            }
        } else if( strncmp(buff, "bounds {", 8) == 0 ) {
            for(i = 0; i < _animation.numFrames; ++i) {
                // Read whole line
                fgets( buff, sizeof(buff), fp );

                // Read bounding box
                sscanf(buff, " ( %f %f %f ) ( %f %f %f )",
                       &_animation.boundingBoxes[i].min[0], &_animation.boundingBoxes[i].min[1], &_animation.boundingBoxes[i].min[2],
                       &_animation.boundingBoxes[i].max[0], &_animation.boundingBoxes[i].max[1], &_animation.boundingBoxes[i].max[2]);
            }
        } else if( strncmp(buff, "baseframe {", 10) == 0 ) {
            for(i = 0; i < _animation.numJoints; ++i) {
                // Read whole line
                fgets( buff, sizeof(buff), fp );

                // Read base frame joint
                if( sscanf(buff, " ( %f %f %f ) ( %f %f %f )",
                           &baseFrame[i].position[0], &baseFrame[i].position[1], &baseFrame[i].position[2],
                           &baseFrame[i].orientation[0], &baseFrame[i].orientation[1], &baseFrame[i].orientation[2]) == 6 ) {
                    // Compute the w component
                    baseFrame[i].orientation.w = glm::extractRealComponent(baseFrame[i].orientation);
                }
            }
        } else if(sscanf(buff, " frame %d", &frameIndex) == 1 ) {
            // Read frame data
            for(i = 0; i < numAnimatedComponents; ++i)
                fscanf( fp, "%f", &animFrameData[i] );

            // Build frame _skeleton from the collected data
            _buildFrameSkeleton(jointInfos, baseFrame, animFrameData,
                                _animation.skeletonFrames[frameIndex],
                                _animation.numJoints);
        }
    }

    fclose( fp );

    printf( "[.md5anim]: finished reading %s\n", filename );
    printf( "[.md5anim]: read in %d frames of %d joints with %d animated components\n", _animation.numFrames, _animation.numJoints, numAnimatedComponents );
    printf( "[.md5anim]: animation's frame rate is %d\n", _animation.frameRate );

    // Free temporary data allocated
    if( animFrameData )
        free( animFrameData );

    if( baseFrame )
        free( baseFrame );

    if( jointInfos )
        free( jointInfos );

    // successful loading...set up animation parameters
    _animationInfo.currFrame = 0;
    _animationInfo.nextFrame = 1;

    _animationInfo.lastTime = 0.0f;
    _animationInfo.maxTime = 1.0f / (GLfloat)_animation.frameRate;

    // Allocate memory for animated _skeleton
    _skeleton = new MD5Joint[_animation.numJoints];

    if( _checkAnimValidity() ) {
        _isAnimated = true;
        // compute initial pose
        animate(0.0);
    }

    return true;
}

// Free resources allocated for the animation.
inline void
CSCI441::MD5Model::_freeAnim()
{
    GLint i;

    for(i = 0; i < _animation.numFrames; ++i) {
        delete _animation.skeletonFrames[i];
        _animation.skeletonFrames[i] = nullptr;
    }

    delete[] _animation.skeletonFrames;
    _animation.skeletonFrames = nullptr;

    delete _animation.boundingBoxes;
    _animation.boundingBoxes = nullptr;

    delete _skeleton;
    _skeleton = nullptr;
}

// Smoothly interpolate two skeletons
inline void
CSCI441::MD5Model::_interpolateSkeletons(GLfloat interp)
{
    const MD5Joint *skeletonA = _animation.skeletonFrames[_animationInfo.currFrame];
    const MD5Joint *skeletonB = _animation.skeletonFrames[_animationInfo.nextFrame];

    GLint i;

    for(i = 0; i < _animation.numJoints; ++i) {
        // Copy parent index
        _skeleton[i].parent = skeletonA[i].parent;

        // Linear interpolation for position
        _skeleton[i].position[0] = skeletonA[i].position[0] + interp * (skeletonB[i].position[0] - skeletonA[i].position[0]);
        _skeleton[i].position[1] = skeletonA[i].position[1] + interp * (skeletonB[i].position[1] - skeletonA[i].position[1]);
        _skeleton[i].position[2] = skeletonA[i].position[2] + interp * (skeletonB[i].position[2] - skeletonA[i].position[2]);

        // Spherical linear interpolation for orientation
        _skeleton[i].orientation = glm::slerp(skeletonA[i].orientation, skeletonB[i].orientation, interp);
    }
}

// Perform animation related computations.  Calculate the current and
// next frames, given a delta time.
inline void
CSCI441::MD5Model::animate(GLfloat dt)
{
    GLint maxFrames = _animation.numFrames - 1;

    _animationInfo.lastTime += dt;

    // move to next frame
    if( _animationInfo.lastTime >= _animationInfo.maxTime ) {
        _animationInfo.currFrame++;
        _animationInfo.nextFrame++;
        _animationInfo.lastTime = 0.0;

        if( _animationInfo.currFrame > maxFrames )
            _animationInfo.currFrame = 0;

        if( _animationInfo.nextFrame > maxFrames )
            _animationInfo.nextFrame = 0;
    }

    // Interpolate skeletons between two frames
    _interpolateSkeletons( _animationInfo.lastTime * _animation.frameRate );
}

#endif//CSCI441_MD5_MODEL_HPP
