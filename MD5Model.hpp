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

#include "constants.h"
#include "MD5Model_types.hpp"
#include "TextureUtils.hpp"

#ifdef CSCI441_USE_GLEW
    #include <GL/glew.h>
#else
    #include <glad/gl.h>
#endif

#include <glm/exponential.hpp>
#include <glm/ext/quaternion_common.hpp>

#define GLM_ENABLE_EXPERIMENTAL
#include <glm/gtx/quaternion.hpp>

#include <cassert>
#include <cmath>
#include <cstdio>
#include <cstdlib>
#include <map>

namespace CSCI441 {

    /**
     * @class MD5Model
     * @brief stores a Doom3 MD5 Mesh + Animation
     */
    class [[maybe_unused]] MD5Model {
    public:
        /**
         * @brief initializes an empty MD5 Model
         * @note need to call loadMD5Model() or readMD5Model() after construction to actually load in a mesh file
         */
        MD5Model() {
            // allocate space for one animation by default
            _numAnimations = 1;
            // create the initial animation
            _animations = new CSCI441_INTERNAL::MD5Animation*[_numAnimations];
            _animations[0] = new CSCI441_INTERNAL::MD5Animation();
            // and the associated animation state information
            _animationInfos = new CSCI441_INTERNAL::MD5AnimationState[_numAnimations];
        }
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
        MD5Model(MD5Model&& src) noexcept {
            _moveFromSrc(src);
        }
        /**
         * @brief do not allow MD5 models to be moved
         */
        MD5Model& operator=(MD5Model&& src) noexcept {
            if (this != &src) {
                _moveFromSrc(src);
            }
            return *this;
        }

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
         * @param vNormalAttribLoc location of vertex normal attribute (defaults to 0 to disable usage)
         * @param vTangentAttribLoc location of vertex tangent attribute (defaults to 0 to disable usage)
         * @note color attribute used when drawing the skeleton
         * @note texCoord attribute used when drawing the mesh
         * @note vertex position attribute must not be zero, if any other attribute is zero it disables it
         */
        [[maybe_unused]] void allocVertexArrays(GLuint vPosAttribLoc, GLuint vColorAttribLoc, GLuint vTexCoordAttribLoc, GLuint vNormalAttribLoc = 0, GLuint vTangentAttribLoc = 0);

        /**
         * @brief specify which texture targets each texture map should be bound to when rendering
         * @param diffuseMapActiveTexture active texture to bind the diffuse map to (default GL_TEXTURE0)
         * @param specularMapActiveTexture active texture to bind the specular map to (default GL_TEXTURE1)
         * @param normalMapActiveTexture active texture to bind the normal map to (default GL_TEXTURE2)
         * @param heightMapActiveTexture active texture to bind the height map to (default GL_TEXTURE3)
         */
        [[maybe_unused]] void setActiveTextures(GLint diffuseMapActiveTexture, GLint specularMapActiveTexture, GLint normalMapActiveTexture, GLint heightMapActiveTexture);

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
         * @param targetAnimationIndex animation index sequence to read into (defaults to first)
         * @returns true iff mesh and animation are compatible
         */
        [[nodiscard]] bool readMD5Anim(const char* filename, GLushort targetAnimationIndex = 0);
        /**
         * @brief adds another MD5 Animation sequence to the model's set of animation
         * @param filename *.md5anim file to open add to animation list
         * @return true iff mesh and animation are compatible
         */
        [[nodiscard]] bool addMD5Anim(const char* filename);
        /**
         * @brief returns the number of animations that were successfully loaded against the model
         * @return number of animations loaded against the mesh
         * @note if model is not animated, will return 0
         * @note calling addMD5Anim() increments this number when successfully loaded
         */
        [[nodiscard]] GLushort getNumberOfAnimations() const {
            // one slot is always allocated, but if model is not allocated then return 0
            if (!_isAnimated) return 0;
            // model is animated, return number of animations that were successfully loaded
            return _numAnimations;
        }
        /**
         * @brief update current animation to be running through
         * @param targetAnimationIndex animation index to animate model through
         * @note targetAnimationIndex must be within the range [0, getNumberOfAnimations()]
         */
        void useTargetAnimationIndex(GLushort targetAnimationIndex);
        /**
         * @brief advances the model forward in its animation sequence the corresponding amount of time based on frame rate
         * @param dt delta time since last frame
         */
        void animate(GLfloat dt);

        // md5material prototypes
        /**
         * @brief loads textures corresponding to MD5 Shaders
         * @param FILENAME *.mtr file to open and load textures from
         * @note registers textures on GPU
         */
        static void readMD5Material(const char* FILENAME);
        /**
         * @brief deletes textures from GPU that were registered during parsing of *.mtr file
         */
        static void releaseMD5Materials();

    private:
        /**
         * @brief array of joints making up model skeleton
         * @note allocated size is tracked in _numJoints
         */
        CSCI441_INTERNAL::MD5Joint* _baseSkeleton = nullptr;
        /**
         * @brief array of meshes making up model
         * @note allocated size is tracked in _numMeshes
         */
        CSCI441_INTERNAL::MD5Mesh* _meshes = nullptr;
        /**
         * @brief number of joints in model
         * @note corresponds to size of _baseSkeleton
         */
        GLint _numJoints = 0;
        /**
         * @brief number of meshes in model
         * @note corresponds to size of _meshes
         */
        GLint _numMeshes = 0;

        // vertex array related stuff
        /**
         * @brief max number of vertices amongst all meshes
         * @note corresponds to size of _vertexArray and _texelArray
         */
        GLint _maxVertices = 0;
        /**
         * @brief max number of triangles amongst all meshes
         * @note corresponds to size of _vertexIndicesArray
         */
        GLint _maxTriangles = 0;
        /**
         * @brief array of vertex positions for a single mesh
         * @note allocated size is tracked in _maxVertices
         */
        glm::vec3* _vertexArray = nullptr;
        /**
         * @brief array of vertex normals for a single mesh
         * @note allocated size is tracked in _maxVertices
         */
        glm::vec3* _normalArray = nullptr;
        /**
         * @brief array of vertex tangents for a single mesh
         * @note allocated size is tracked in _maxVertices
         * @note w-coordinate stores handedness
         */
        glm::vec4* _tangentArray = nullptr;
        /**
         * @brief array of texel coordinates for a single mesh
         * @note allocated size is tracked in _maxVertices
         */
        glm::vec2* _texelArray = nullptr;
        /**
         * @brief array of indices to render a single mesh
         * @note allocated size is tracked in _maxTriangles * 3
         */
        GLuint* _vertexIndicesArray = nullptr;
        /**
         * @brief VAO for the full model rendering
         */
        GLuint _vao = 0;
        /**
         * @brief VBO array for the full model rendering
         * @note position [0] bind to GL_ARRAY_BUFFER (vbo)
         * @note position [1] bind to GL_ELEMENT_ARRAY_BUFFER (ibo)
         */
        GLuint _vbo[2] = {0, 0};

        // skeleton related stuff
        /**
         * @brief VAO for the skeleton rendering
         */
        GLuint _skeletonVAO = 0;
        /**
         * @brief VBO for the skeleton rendering
         */
        GLuint _skeletonVBO = 0;
        /**
         * @brief the MD5 skeletal joint data
         */
        CSCI441_INTERNAL::MD5Joint* _skeleton = nullptr;

        // animation related stuff
        /**
         * @brief the MD5 animation frame sequences
         */
        CSCI441_INTERNAL::MD5Animation** _animations = nullptr;
        /**
         * @brief number of animations loaded against the model
         */
        GLushort _numAnimations = 0;
        /**
         * @brief index of current animation being applied
         */
        GLushort _currentAnimationIndex = 0;
        /**
         * @brief flag stating if the loaded MD5 model has a corresponding animation or not
         */
        bool _isAnimated = false;
        /**
         * @brief animation frame states
         */
        CSCI441_INTERNAL::MD5AnimationState* _animationInfos = nullptr;

        // material related stuff
        static std::map< std::string, CSCI441_INTERNAL::MD5MaterialShader* > _materials;
        static std::map< std::string, GLuint > _textureMap;

        /**
         * @brief active texture diffuse map should be bound to
         */
        GLint _diffuseActiveTexture  = GL_TEXTURE0;
        /**
         * @brief active texture specular map should be bound to
         */
        GLint _specularActiveTexture = GL_TEXTURE1;
        /**
         * @brief active texture normal map should be bound to
         */
        GLint _normalActiveTexture   = GL_TEXTURE2;
        /**
         * @brief active texture height map should be bound to
         */
        GLint _heightActiveTexture   = GL_TEXTURE3;

        // helper functions
        /**
         * @brief Prepare a mesh for drawing.  Compute mesh's final vertex positions
         * given a skeleton.  Put the vertices in vertex arrays.
         * @param pMESH mesh to load into vertex arrays
         */
        void _prepareMesh(const CSCI441_INTERNAL::MD5Mesh* pMESH) const;
        /**
         * @brief bind mesh's texture and vao, then call glDraw
         * @param pMESH mesh to draw
         */
        auto _drawMesh(const CSCI441_INTERNAL::MD5Mesh* pMESH) const -> void;
        /**
         * @brief Check if an animation can be used for a given model.  Model's
         * skeleton and animation's skeleton must match.
         * @param targetAnimationIndex index of animations array to test validity of
         * @return true if animation can be used
         */
        [[nodiscard]] bool _checkAnimValidity(GLushort targetAnimationIndex) const;
        /**
         * @brief Build _skeleton for a given frame data.
         * @param pJOINT_INFOS array of joint infos
         * @param pBASE_FRAME array of base frames
         * @param pANIM_FRAME_DATA array of animation data
         * @param pSkeletonFrame skeleton array
         * @param NUM_JOINTS number of joints in each array
         */
        static void _buildFrameSkeleton(const CSCI441_INTERNAL::MD5JointInfo* pJOINT_INFOS,
                                        const CSCI441_INTERNAL::MD5BaseFrameJoint* pBASE_FRAME,
                                        const GLfloat* pANIM_FRAME_DATA,
                                        const CSCI441_INTERNAL::MD5Joint* pSkeletonFrame,
                                        GLint NUM_JOINTS);
        /**
         * @brief Smoothly interpolate two skeletons
         * @param interp amount to interpolate
         */
        void _interpolateSkeletons(GLfloat interp);
        /**
         * @brief Free resources allocated for the model.
         */
        void _freeModel();
        /**
         * @brief free vertex data and clear VAO/VBO from GPU
         */
        void _freeVertexArrays();
        /**
         * @brief Free resources allocated for the animation.
         */
        void _freeAnim();

        /**
         * @brief move data members and reset object to default state
         * @param src object to move
         */
        void _moveFromSrc(MD5Model &src);

        /**
         * @brief trims whitespace from beginning and end of string
         * @param out string with whitespace trimmed
         * @param len length of original string
         * @param str original string
         * @return size of trimmed string
         * @note out needs to be allocated prior to function call
         */
        static size_t _trim(char* out, size_t len, const char* str);

        /**
         * @brief registers the texture handle for a given texture filename
         * @param texture texture object to register
         * @return true iff a new texture object was registered on the GPU
         * @note MD5Texture::filename needs to be assigned before calling this method
         * @note upon completion, MD5Texture::texHandle will be overwritten with GPU texture handle
         */
        static bool _registerShaderTexture( CSCI441_INTERNAL::MD5Texture* texture );
    };
}

//----------------------------------------------------------------------------------------------------

inline
CSCI441::MD5Model::~MD5Model()
{
    _freeModel();
    _freeVertexArrays();
    _freeAnim();
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
    char buff[512];
    GLint version = 0;
    GLint currentMesh = 0;

    GLint totalVertices = 0;
    GLint totalWeights = 0;
    GLint totalTriangles = 0;

    GLfloat minX =  999999, minY =  999999, minZ =  999999;
    GLfloat maxX = -999999, maxY = -999999, maxZ = -999999;

    fprintf(stdout, "[.md5mesh]: about to read %s\n", FILENAME );

    FILE *fp = fopen(FILENAME, "rb" );
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
                _baseSkeleton = new CSCI441_INTERNAL::MD5Joint[_numJoints];
            }
        } else if( sscanf(buff, " numMeshes %d", &_numMeshes) == 1 ) {
            if( _numMeshes > 0 ) {
                // Allocate memory for meshes
                _meshes = new CSCI441_INTERNAL::MD5Mesh[_numMeshes];
            }
        } else if( strncmp(buff, "joints {", 8) == 0 ) {
            // Read each joint
            for(GLint i = 0; i < _numJoints; ++i) {
                CSCI441_INTERNAL::MD5Joint *joint = &_baseSkeleton[i];

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
            CSCI441_INTERNAL::MD5Mesh *mesh = &_meshes[currentMesh];
            GLint vert_index = 0;
            GLint tri_index = 0;
            GLint weight_index = 0;
            GLfloat floatData[4];
            GLint intData[3];

            while( buff[0] != '}' && !feof(fp) ) {
                // Read whole line
                fgets( buff, sizeof(buff), fp );

                if( strstr( buff, "shader ") ) {
                    GLint quote = 0, j = 0;

                    char shaderName[512] = "";

                    // Copy the shader name without the quote marks
                    for(unsigned long uli = 0; uli < sizeof(buff) && (quote < 2); ++uli) {
                        if( buff[uli] == '\"' )
                            quote++;

                        if( (quote == 1) && (buff[uli] != '\"') ) {
                            shaderName[j] = buff[uli];
                            j++;
                        }
                    }
                    // there was a shader name
                    if( j > 0 ) {
                        auto materialIter = _materials.find(shaderName);
                        if (materialIter != _materials.end()) {
                            mesh->shader = materialIter->second;
                        } else {
                            fprintf(stderr, "[.md5mesh | ERROR]: Could not find material shader \"%s\"\n", shaderName);
                        }
                    }
                } else if( sscanf(buff, " numverts %d", &mesh->numVertices) == 1 ) {
                    if( mesh->numVertices > 0 ) {
                        // Allocate memory for vertices
                        mesh->vertices = new CSCI441_INTERNAL::MD5Vertex[mesh->numVertices];
                    }

                    if( mesh->numVertices > _maxVertices )
                        _maxVertices = mesh->numVertices;

                    totalVertices += mesh->numVertices;
                } else if( sscanf(buff, " numtris %d", &mesh->numTriangles) == 1 ) {
                    if( mesh->numTriangles > 0 ) {
                        // Allocate memory for triangles
                        mesh->triangles = new CSCI441_INTERNAL::MD5Triangle[mesh->numTriangles];
                    }

                    if( mesh->numTriangles > _maxTriangles )
                        _maxTriangles = mesh->numTriangles;

                    totalTriangles += mesh->numTriangles;
                } else if( sscanf(buff, " numweights %d", &mesh->numWeights) == 1 ) {
                    if( mesh->numWeights > 0 ) {
                        // Allocate memory for vertex weights
                        mesh->weights = new CSCI441_INTERNAL::MD5Weight[mesh->numWeights];
                    }

                    totalWeights += mesh->numWeights;
                } else if( sscanf(buff, " vert %d ( %f %f ) %d %d",
                                  &vert_index,
                                  &floatData[0], &floatData[1],
                                  &intData[0], &intData[1]) == 5
                        ) {
                    // Copy vertex data
                    mesh->vertices[vert_index].texCoord.s = floatData[0];
                    mesh->vertices[vert_index].texCoord.t = floatData[1];
                    mesh->vertices[vert_index].start = intData[0];
                    mesh->vertices[vert_index].count = intData[1];
                } else if( sscanf(buff, " tri %d %d %d %d",
                                  &tri_index,
                                  &intData[0], &intData[1], &intData[2]) == 4
                        ) {
                    // Copy triangle data
                    mesh->triangles[tri_index ].index[0] = intData[0];
                    mesh->triangles[tri_index ].index[1] = intData[1];
                    mesh->triangles[tri_index ].index[2] = intData[2];
                } else if( sscanf(buff, " weight %d %d %f ( %f %f %f )",
                                  &weight_index, &intData[0], &floatData[3],
                                  &floatData[0], &floatData[1], &floatData[2]) == 6
                        ) {
                    // Copy vertex data
                    mesh->weights[weight_index].joint  = intData[0];
                    mesh->weights[weight_index].bias   = floatData[3];
                    mesh->weights[weight_index].position[0] = floatData[0];
                    mesh->weights[weight_index].position[1] = floatData[1];
                    mesh->weights[weight_index].position[2] = floatData[2];

                    if( floatData[0] < minX ) { minX = floatData[0]; }
                    if( floatData[0] > maxX ) { maxX = floatData[0]; }
                    if( floatData[1] < minY ) { minY = floatData[1]; }
                    if( floatData[1] > maxY ) { maxY = floatData[1]; }
                    if( floatData[2] < minZ ) { minZ = floatData[2]; }
                    if( floatData[2] > maxZ ) { maxZ = floatData[2]; }
                }
            }

            currentMesh++;
        }
    }

    fclose(fp);

    _skeleton = _baseSkeleton;

    fprintf(stdout, "[.md5mesh]: finished reading %s\n", FILENAME );
    fprintf(stdout, "[.md5mesh]: read in %d meshes, %d joints, %d vertices, %d weights, and %d triangles\n", _numMeshes, _numJoints, totalVertices, totalWeights, totalTriangles );
    fprintf(stdout, "[.md5mesh]: base pose %f units across in X, %f units across in Y, %f units across in Z\n", (maxX - minX), (maxY-minY), (maxZ - minZ) );
    fprintf(stdout, "\n" );

    return true;
}

inline void
CSCI441::MD5Model::_freeModel()
{
    delete[] _baseSkeleton;
    if (_baseSkeleton == _skeleton) _skeleton = nullptr;    // if there is no animation, prevent double delete
    _baseSkeleton = nullptr;

    delete[] _meshes;
    _meshes = nullptr;
}

[[maybe_unused]]
inline void
CSCI441::MD5Model::draw() const
{
    // Draw each mesh of the model
    for(GLint i = 0; i < _numMeshes; ++i) {
        CSCI441_INTERNAL::MD5Mesh& mesh = _meshes[i];    // get the mesh
        _prepareMesh(&mesh);                             // do some preprocessing on it
        _drawMesh(&mesh);                                // draw it
    }
}

inline void
CSCI441::MD5Model::_prepareMesh(
    const CSCI441_INTERNAL::MD5Mesh *pMESH
) const {
    GLint i, j, k;

    // Setup vertex indices
    for(k = 0, i = 0; i < pMESH->numTriangles; ++i) {
        for(j = 0; j < 3; ++j, ++k)
            _vertexIndicesArray[k] = pMESH->triangles[i].index[j];
    }

    // Setup vertices
    auto normalAccum    = new glm::vec3[pMESH->numVertices];
    auto tangentAccum   = new glm::vec3[pMESH->numVertices];
    auto bitangentAccum = new glm::vec3[pMESH->numVertices];

    for(i = 0; i < pMESH->numVertices; ++i) {
        normalAccum[i] = glm::vec3(0.0f);
        tangentAccum[i] = glm::vec3(0.0f);
        bitangentAccum[i] = glm::vec3(0.0f);

        glm::vec3 finalVertex = {0.0f, 0.0f, 0.0f };

        // Calculate final vertex to draw with weights
        for(j = 0; j < pMESH->vertices[i].count; ++j) {
            const CSCI441_INTERNAL::MD5Weight *weight = &pMESH->weights[pMESH->vertices[i].start + j];
            const CSCI441_INTERNAL::MD5Joint  *joint  = &_skeleton[weight->joint];

            // Calculate transformed vertex for this weight
            const glm::vec3 weightedVertex = glm::rotate(joint->orientation, glm::vec4(weight->position, 0.0f));

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

    for(i = 0; i < pMESH->numTriangles; ++i) {
        GLint idx0 = pMESH->triangles[i].index[0];
        GLint idx1 = pMESH->triangles[i].index[1];
        GLint idx2 = pMESH->triangles[i].index[2];

        glm::vec3 v0 = _vertexArray[ idx0 ];
        glm::vec3 v1 = _vertexArray[ idx1 ];
        glm::vec3 v2 = _vertexArray[ idx2 ];

        glm::vec2 uv0 = _texelArray[ idx0 ];
        glm::vec2 uv1 = _texelArray[ idx1 ];
        glm::vec2 uv2 = _texelArray[ idx2 ];

        glm::vec3 edge1 = v1 - v0;
        glm::vec3 edge2 = v2 - v0;
        glm::vec2 deltaUV1 = uv1 - uv0;
        glm::vec2 deltaUV2 = uv2 - uv0;

        GLfloat f = 1.0f / (deltaUV1.x * deltaUV2.y - deltaUV2.x * deltaUV1.y);

        glm::vec3 normal    = cross(edge1, edge2);
        glm::vec3 tangent   = f * (deltaUV2.y * edge1 - deltaUV1.y * edge2);
        glm::vec3 bitangent = f * (deltaUV2.x * edge1 - deltaUV1.x * edge2);

        normalAccum[ idx0 ] += normal;  tangentAccum[ idx0 ] += tangent;    bitangentAccum[ idx0 ] += bitangent;
        normalAccum[ idx1 ] += normal;  tangentAccum[ idx1 ] += tangent;    bitangentAccum[ idx1 ] += bitangent;
        normalAccum[ idx2 ] += normal;  tangentAccum[ idx2 ] += tangent;    bitangentAccum[ idx2 ] += bitangent;
    }

    for(i = 0; i < pMESH->numVertices; ++i) {
        glm::vec3& n = normalAccum[i];
        glm::vec3& t = tangentAccum[i];
        glm::vec3& b = bitangentAccum[i];

        glm::vec3 normal  = glm::normalize( n );
        // Gram-Schmidt Orthogonalization
        glm::vec3 tangent = glm::normalize( t - (glm::dot(normal, t) * normal) );
        glm::vec3 bitangent = glm::normalize( b );

        _normalArray[ i ] = normal;

        _tangentArray[ i ] = glm::vec4(tangent, 0.0f);
        // store handedness in w
        _tangentArray[ i ].w = (glm::dot( glm::cross(normal, tangent), bitangent) < 0.0f) ? -1.0f : 1.0f;
    }

    delete[] normalAccum;
    delete[] tangentAccum;
    delete[] bitangentAccum;

    glBindVertexArray(_vao );

    glBindBuffer(GL_ARRAY_BUFFER, _vbo[0] );
    glBufferSubData(GL_ARRAY_BUFFER, 0, static_cast<GLsizeiptr>(sizeof(glm::vec3)) * pMESH->numVertices, &_vertexArray[0] );
    glBufferSubData(GL_ARRAY_BUFFER, static_cast<GLsizeiptr>(sizeof(glm::vec3)) * _maxVertices * 1, static_cast<GLsizeiptr>(sizeof(glm::vec3)) * pMESH->numVertices, &_normalArray[0] );
    glBufferSubData(GL_ARRAY_BUFFER, static_cast<GLsizeiptr>(sizeof(glm::vec3)) * _maxVertices * 2, static_cast<GLsizeiptr>(sizeof(glm::vec4)) * pMESH->numVertices, &_tangentArray[0] );
    glBufferSubData(GL_ARRAY_BUFFER, static_cast<GLsizeiptr>(sizeof(glm::vec3)) * _maxVertices * 2 + static_cast<GLsizeiptr>(sizeof(glm::vec4)) * _maxVertices, static_cast<GLsizeiptr>(sizeof(glm::vec2)) * pMESH->numVertices, &_texelArray[0] );

    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, _vbo[1] );
    glBufferSubData(GL_ELEMENT_ARRAY_BUFFER, 0, static_cast<GLsizeiptr>(sizeof(GLuint)) * pMESH->numTriangles * 3, _vertexIndicesArray );
}

inline void
CSCI441::MD5Model::_drawMesh(
    const CSCI441_INTERNAL::MD5Mesh *pMESH
) const {
    if (pMESH->shader != nullptr) {
        // fprintf(stdout, "applying shader %s\n", pMESH->shader->name);
        if (pMESH->shader->textures[CSCI441_INTERNAL::MD5MaterialShader::SPECULAR].texHandle != 0) {
            // Bind Specular Map if exists
            glActiveTexture(_specularActiveTexture);
            glBindTexture(GL_TEXTURE_2D, pMESH->shader->textures[CSCI441_INTERNAL::MD5MaterialShader::SPECULAR].texHandle );
            // fprintf(stdout, "bound specular texture %u to %d (%d)\n", pMESH->shader->textures[CSCI441_INTERNAL::MD5MaterialShader::SPECULAR].texHandle, _specularActiveTexture, GL_TEXTURE0);
        }
        if (pMESH->shader->textures[CSCI441_INTERNAL::MD5MaterialShader::NORMAL].texHandle != 0) {
            // Bind Normal Map if exists
            glActiveTexture(_normalActiveTexture);
            glBindTexture(GL_TEXTURE_2D, pMESH->shader->textures[CSCI441_INTERNAL::MD5MaterialShader::NORMAL].texHandle );
        }
        if (pMESH->shader->textures[CSCI441_INTERNAL::MD5MaterialShader::HEIGHT].texHandle != 0) {
            // Bind Height Map if exists
            glActiveTexture(_heightActiveTexture);
            glBindTexture(GL_TEXTURE_2D, pMESH->shader->textures[CSCI441_INTERNAL::MD5MaterialShader::HEIGHT].texHandle );
        }
        // bind diffuse last because ideally it is texture 0 and will remain for future renderings
        if (pMESH->shader->textures[CSCI441_INTERNAL::MD5MaterialShader::DIFFUSE].texHandle != 0) {
            // Bind Diffuse Map if exists
            glActiveTexture(_diffuseActiveTexture);
            glBindTexture(GL_TEXTURE_2D, pMESH->shader->textures[CSCI441_INTERNAL::MD5MaterialShader::DIFFUSE].texHandle );
            // fprintf(stdout, "bound diffuse texture %u to %d (%d)\n", pMESH->shader->textures[CSCI441_INTERNAL::MD5MaterialShader::DIFFUSE].texHandle, _diffuseActiveTexture, GL_TEXTURE0);
        }
        if (_diffuseActiveTexture != GL_TEXTURE0) {
            // reset back to active texture being zero
            glActiveTexture(GL_TEXTURE0);
        }
    }

    glBindVertexArray(_vao );
    glDrawElements(GL_TRIANGLES, pMESH->numTriangles * 3, GL_UNSIGNED_INT, (void*)nullptr );
}

[[maybe_unused]]
inline void
CSCI441::MD5Model::allocVertexArrays(
    const GLuint vPosAttribLoc,
    const GLuint vColorAttribLoc,
    const GLuint vTexCoordAttribLoc,
    const GLuint vNormalAttribLoc,
    const GLuint vTangentAttribLoc
) {
    // layout
    // position normal tangent texCoord

    _vertexArray    = new glm::vec3[_maxVertices];
    _normalArray    = new glm::vec3[_maxVertices];
    _tangentArray   = new glm::vec4[_maxVertices];
    _texelArray     = new glm::vec2[_maxVertices];
    _vertexIndicesArray = new GLuint[_maxTriangles * 3];

    glGenVertexArrays( 1, &_vao );
    glBindVertexArray(_vao );

    glGenBuffers(2, _vbo );
    glBindBuffer(GL_ARRAY_BUFFER, _vbo[0] );
    glBufferData(GL_ARRAY_BUFFER, static_cast<GLsizeiptr>(sizeof(glm::vec3)) * _maxVertices * 2 + static_cast<GLsizeiptr>(sizeof(glm::vec4)) * _maxVertices + static_cast<GLsizeiptr>(sizeof(glm::vec2)) * _maxVertices, nullptr, GL_DYNAMIC_DRAW );

    glEnableVertexAttribArray( vPosAttribLoc );
    glVertexAttribPointer( vPosAttribLoc, 3, GL_FLOAT, GL_FALSE, 0, static_cast<void *>(nullptr) );

    if (vNormalAttribLoc != 0) {
        glEnableVertexAttribArray( vNormalAttribLoc );
        glVertexAttribPointer( vNormalAttribLoc, 3, GL_FLOAT, GL_FALSE, 0, reinterpret_cast<void *>(sizeof(glm::vec3) * _maxVertices * 1) );
    }

    if (vTangentAttribLoc != 0) {
        glEnableVertexAttribArray( vTangentAttribLoc );
        glVertexAttribPointer( vTangentAttribLoc, 4, GL_FLOAT, GL_FALSE, 0, reinterpret_cast<void *>(sizeof(glm::vec3) * _maxVertices * 2) );
    }

    if (vTexCoordAttribLoc != 0) {
        glEnableVertexAttribArray( vTexCoordAttribLoc );
        glVertexAttribPointer( vTexCoordAttribLoc, 2, GL_FLOAT, GL_FALSE, 0, reinterpret_cast<void *>(sizeof(glm::vec3) * _maxVertices * 2 + sizeof(glm::vec4) * _maxVertices) );
    }

    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, _vbo[1] );
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, static_cast<GLsizeiptr>(sizeof(GLuint)) * _maxTriangles * 3, nullptr, GL_DYNAMIC_DRAW );

    printf("[.md5mesh]: Model VAO/VBO/IBO registered at %u/%u/%u\n", _vao, _vbo[0], _vbo[1] );

    glGenVertexArrays( 1, &_skeletonVAO );
    glBindVertexArray(_skeletonVAO );

    glGenBuffers( 1, &_skeletonVBO );
    glBindBuffer(GL_ARRAY_BUFFER, _skeletonVBO );
    glBufferData(GL_ARRAY_BUFFER, static_cast<GLsizeiptr>(sizeof(glm::vec3)) * _numJoints * 3 * 2, nullptr, GL_DYNAMIC_DRAW );

    glEnableVertexAttribArray( vPosAttribLoc ); // vPos
    glVertexAttribPointer( vPosAttribLoc, 3, GL_FLOAT, GL_FALSE, 0, static_cast<void *>(nullptr) );

    if (vColorAttribLoc != 0) {
        glEnableVertexAttribArray( vColorAttribLoc ); // vColor
        glVertexAttribPointer( vColorAttribLoc, 3, GL_FLOAT, GL_FALSE, 0, reinterpret_cast<void *>(sizeof(glm::vec3) * _numJoints * 3) );
    }

    printf("[.md5mesh]: Skeleton VAO/VBO registered at %u/%u\n", _skeletonVAO, _skeletonVBO );
}

inline void
CSCI441::MD5Model::setActiveTextures(
    const GLint diffuseMapActiveTexture = GL_TEXTURE0,
    const GLint specularMapActiveTexture = GL_TEXTURE1,
    const GLint normalMapActiveTexture = GL_TEXTURE2,
    const GLint heightMapActiveTexture = GL_TEXTURE3
) {
    _diffuseActiveTexture = diffuseMapActiveTexture;
    _specularActiveTexture = specularMapActiveTexture;
    _normalActiveTexture = normalMapActiveTexture;
    _heightActiveTexture = heightMapActiveTexture;
}

inline void
CSCI441::MD5Model::_freeVertexArrays()
{
    delete[] _vertexArray;
    _vertexArray = nullptr;

    delete[] _normalArray;
    _normalArray = nullptr;

    delete[] _tangentArray;
    _tangentArray = nullptr;

    delete[] _vertexIndicesArray;
    _vertexIndicesArray = nullptr;

    delete[] _texelArray;
    _texelArray = nullptr;

    glDeleteVertexArrays( 1, &_vao );
    _vao = 0;

    glDeleteBuffers(2, _vbo );
    _vbo[0] = 0;
    _vbo[1] = 0;

    glDeleteVertexArrays( 1, &_skeletonVAO );
    _skeletonVAO = 0;

    glDeleteBuffers( 1, &_skeletonVBO );
    _skeletonVBO = 0;
}

[[maybe_unused]]
inline void
CSCI441::MD5Model::drawSkeleton() const
{
    glBindVertexArray(_skeletonVAO );
    glBindBuffer(GL_ARRAY_BUFFER, _skeletonVBO );

    constexpr glm::vec3 jointColor = {1.0f, 1.0f, 0.0f };
    constexpr glm::vec3 boneColor = {1.0f, 0.0f, 1.0f };

    // put in points for joints
    for(GLint i = 0; i < _numJoints; ++i ) {
        glBufferSubData(GL_ARRAY_BUFFER, i * static_cast<GLsizeiptr>(sizeof(glm::vec3)), sizeof(glm::vec3), &(_skeleton[i].position) );
        glBufferSubData(GL_ARRAY_BUFFER, i * static_cast<GLsizeiptr>(sizeof(glm::vec3)) + static_cast<GLsizeiptr>(sizeof(glm::vec3)) * _numJoints * 3, sizeof(glm::vec3), &jointColor[0]);
    }

    // put in lines for bones
    GLint numBones = 0;
    for(GLint i = 0; i < _numJoints; ++i ) {
        if( _skeleton[i].parent != CSCI441_INTERNAL::MD5Joint::NULL_JOINT ) {
            glBufferSubData(
                GL_ARRAY_BUFFER,
                static_cast<GLsizeiptr>(sizeof(glm::vec3)) * _numJoints + (i * 2) * static_cast<GLsizeiptr>(sizeof(glm::vec3)),
                static_cast<GLsizeiptr>(sizeof(glm::vec3)),
                &(_skeleton[_skeleton[i].parent].position)
            );
            glBufferSubData(
                GL_ARRAY_BUFFER,
                static_cast<GLsizeiptr>(sizeof(glm::vec3)) * _numJoints + (i * 2) * static_cast<GLsizeiptr>(sizeof(glm::vec3)) + static_cast<GLsizeiptr>(sizeof(glm::vec3)) * _numJoints * 3,
                sizeof(glm::vec3),
                &boneColor[0]
            );

            glBufferSubData(
                GL_ARRAY_BUFFER,
                static_cast<GLsizeiptr>(sizeof(glm::vec3)) * _numJoints + (i * 2) * static_cast<GLsizeiptr>(sizeof(glm::vec3)) + static_cast<GLsizeiptr>(sizeof(glm::vec3)),
                static_cast<GLsizeiptr>(sizeof(glm::vec3)),
                &(_skeleton[i].position)
            );
            glBufferSubData(
                GL_ARRAY_BUFFER,
                static_cast<GLsizeiptr>(sizeof(glm::vec3)) * _numJoints + (i * 2) * static_cast<GLsizeiptr>(sizeof(glm::vec3)) + static_cast<GLsizeiptr>(sizeof(glm::vec3)) + static_cast<GLsizeiptr>(sizeof(glm::vec3)) * _numJoints * 3,
                sizeof(glm::vec3),
                &boneColor[0]
            );
            numBones++;
        }
    }

    glPointSize(5.0f);
    glDrawArrays(GL_POINTS, 0, _numJoints );
    glPointSize(1.0f);

    glLineWidth( 3.0f );
    glDrawArrays(GL_LINES, _numJoints, numBones * 2 );
    glLineWidth(1.0f);
}

inline bool
CSCI441::MD5Model::_checkAnimValidity(const GLushort targetAnimationIndex) const
{
    // md5mesh and md5anim must have the same number of joints
    if( _numJoints != _animations[targetAnimationIndex]->getNumberOfJoints() ) {
        fprintf(stderr, "[.md5anim | ERROR]: skeleton and animation do not have same number of joints.  cannot apply animation %u to skeleton\n", targetAnimationIndex);
        return false;
    }
    if (_animations[targetAnimationIndex]->getNumberOfJoints() == 0 ) {
        fprintf(stderr, "[.md5anim | ERROR]: animation has zero joints.  cannot apply animation %u to skeleton\n\n", targetAnimationIndex);
        return false;
    }

    // We just check with frame[0]
    for(GLint i = 0; i < _numJoints; ++i) {
        // Joints must have the same parent index
        if (_baseSkeleton[i].parent != _animations[targetAnimationIndex]->getSkeletonFrameJoint(0, i).parent) {
            fprintf(stderr, "[.md5anim | ERROR]: skeleton and animation joints do not have same parent index.  cannot apply animation %u to skeleton\n", targetAnimationIndex);
            return false;
        }

        // Joints must have the same name
        if (strcmp (_baseSkeleton[i].name, _animations[targetAnimationIndex]->getSkeletonFrameJoint(0, i).name) != 0) {
            fprintf(stderr, "[.md5anim | ERROR]: skeleton and animation joints do not have same name.  cannot apply animation %u to skeleton\n", targetAnimationIndex);
            return false;
        }
    }

    fprintf(stdout, "[.md5anim]: skeleton and animation match.  animation %u can be applied to skeleton\n", targetAnimationIndex);
    return true;
}

inline void
CSCI441::MD5Model::_buildFrameSkeleton(
        const CSCI441_INTERNAL::MD5JointInfo* pJOINT_INFOS,
        const CSCI441_INTERNAL::MD5BaseFrameJoint* pBASE_FRAME,
        const GLfloat* pANIM_FRAME_DATA,
        const CSCI441_INTERNAL::MD5Joint* pSkeletonFrame,
        const GLint NUM_JOINTS
) {
    if(pJOINT_INFOS == nullptr
       || pBASE_FRAME == nullptr
       || pANIM_FRAME_DATA == nullptr
       || pSkeletonFrame == nullptr) return;

    for(GLint i = 0; i < NUM_JOINTS; ++i) {
        const CSCI441_INTERNAL::MD5BaseFrameJoint *baseJoint = &pBASE_FRAME[i];
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
        const auto thisJoint = const_cast<CSCI441_INTERNAL::MD5Joint *>(&pSkeletonFrame[i]);

        const GLint parent = pJOINT_INFOS[i].parent;
        thisJoint->parent = parent;
        strcpy (thisJoint->name, pJOINT_INFOS[i].name);

        // Has parent?
        if( thisJoint->parent == CSCI441_INTERNAL::MD5Joint::NULL_JOINT ) {
            thisJoint->position = animatedPosition;
            thisJoint->orientation = animatedOrientation;
        } else {
            const CSCI441_INTERNAL::MD5Joint *parentJoint = &pSkeletonFrame[parent];
            glm::vec3 rotatedPosition = glm::rotate(parentJoint->orientation, glm::vec4(animatedPosition, 0.0f));

            // Add positions
            thisJoint->position = parentJoint->position + rotatedPosition;

            // Concatenate rotations
            thisJoint->orientation = glm::normalize( glm::cross(parentJoint->orientation, animatedOrientation) );
        }
    }
}

inline bool
CSCI441::MD5Model::readMD5Anim(
        const char *filename,
        const GLushort targetAnimationIndex
) {
    if (targetAnimationIndex >= _numAnimations) {
        fprintf (stderr, "[.md5anim]: Error: target animation index %u is out of range for currently allocated animations (which is %u)\n", targetAnimationIndex, _numAnimations);
        fprintf (stderr, "[.md5anim]: Hey Developer, if you wish to add an animation to the sequence, use CSCI441::MD5Model::addMD5Anim(const char*)\n");
        return false;
    }

    char buff[512];
    CSCI441_INTERNAL::MD5JointInfo *jointInfos = nullptr;
    CSCI441_INTERNAL::MD5BaseFrameJoint *baseFrame = nullptr;
    GLfloat *animFrameData = nullptr;
    GLint version;
    GLint numAnimatedComponents;
    GLint frameIndex, numFrames, numJoints;
    GLint i;

    printf( "[.md5anim]: about to read %s into animation %u\n", filename, targetAnimationIndex );

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
        } else if( sscanf(buff, " numFrames %d", &numFrames) == 1 ) {
            // Allocate memory for skeleton frames and bounding boxes
            _animations[targetAnimationIndex]->setNumberOfFrames(numFrames);
        } else if( sscanf(buff, " numJoints %d", &numJoints) == 1 ) {
            if (jointInfos != nullptr) {
                fprintf( stderr, "[.md5anim]: Error: md5anim file malformed. numJoints already specified\n" );
            }
            if( numJoints > 0 ) {
                _animations[targetAnimationIndex]->setNumberOfJoints(numJoints);

                // Allocate temporary memory for building skeleton frames
                jointInfos = new CSCI441_INTERNAL::MD5JointInfo[numJoints];
                baseFrame = new CSCI441_INTERNAL::MD5BaseFrameJoint[numJoints];
            }
        } else if( sscanf(buff, " frameRate %d", &_animations[targetAnimationIndex]->frameRate) == 1 ) {

        } else if( sscanf(buff, " numAnimatedComponents %d", &numAnimatedComponents) == 1 ) {
            if (animFrameData != nullptr) {
                fprintf( stderr, "[.md5anim]: Error: md5anim file malformed. numAnimatedComponents already specified\n" );
            }
            if( numAnimatedComponents > 0 ) {
                // Allocate memory for animation frame data
                animFrameData = new GLfloat[numAnimatedComponents];
            }
        } else if( strncmp(buff, "hierarchy {", 11) == 0 ) {
            if (jointInfos == nullptr) {
                fprintf( stderr, "[.md5anim]: Error: md5anim file malformed. numJoints not specified prior to hierarchy\n" );
            } else {
                for(i = 0; i < numJoints; ++i) {
                    // Read whole line
                    fgets( buff, sizeof(buff), fp );

                    // Read joint info
                    sscanf(buff, " %s %d %d %d",
                           jointInfos[i].name, &jointInfos[i].parent,
                           &jointInfos[i].flags, &jointInfos[i].startIndex);
                }
            }
        } else if( strncmp(buff, "bounds {", 8) == 0 ) {
            if (_animations[targetAnimationIndex]->getNumberOfFrames() == 0) {
                fprintf( stderr, "[.md5anim]: Error: md5anim file malformed. numFrames not specified prior to bounds\n" );
            } else {
                for(i = 0; i < _animations[targetAnimationIndex]->getNumberOfFrames(); ++i) {
                    // Read whole line
                    fgets( buff, sizeof(buff), fp );

                    // Read bounding box
                    sscanf(buff, " ( %f %f %f ) ( %f %f %f )",
                           &_animations[targetAnimationIndex]->getBoundingBox(i).min[0], &_animations[targetAnimationIndex]->getBoundingBox(i).min[1], &_animations[targetAnimationIndex]->getBoundingBox(i).min[2],
                           &_animations[targetAnimationIndex]->getBoundingBox(i).max[0], &_animations[targetAnimationIndex]->getBoundingBox(i).max[1], &_animations[targetAnimationIndex]->getBoundingBox(i).max[2]);
                }
            }
        } else if( strncmp(buff, "baseframe {", 10) == 0 ) {
            if (baseFrame == nullptr) {
                fprintf( stderr, "[.md5anim]: Error: md5anim file malformed. numJoints not specified prior to baseframe\n" );
            } else {
                for(i = 0; i < numJoints; ++i) {
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
            }
        } else if(sscanf(buff, " frame %d", &frameIndex) == 1 ) {
            if (animFrameData == nullptr) {
                fprintf( stderr, "[.md5anim]: Error: md5anim file malformed. numAnimatedComponents not specified prior to frame\n" );
            } else if (_animations[targetAnimationIndex]->getNumberOfFrames() == 0) {
                fprintf( stderr, "[.md5anim]: Error: md5anim file malformed. numFrames not specified prior to frame\n" );
            } else if (baseFrame == nullptr) {
                fprintf( stderr, "[.md5anim]: Error: md5anim file malformed. baseframe not specified prior to frame\n" );
            } else if (jointInfos == nullptr) {
                fprintf( stderr, "[.md5anim]: Error: md5anim file malformed. numJoints not specified prior to frame\n" );
            } else {
                // Read frame data
                for(i = 0; i < numAnimatedComponents; ++i)
                    fscanf( fp, "%f", &animFrameData[i] );

                // Build frame _skeleton from the collected data
                _buildFrameSkeleton(jointInfos, baseFrame, animFrameData,
                                    _animations[targetAnimationIndex]->getSkeletonFrame(frameIndex),
                                    numJoints);
            }
        }
    }

    fclose( fp );

    printf( "[.md5anim]: finished reading %s into animation %u\n", filename, targetAnimationIndex );
    printf( "[.md5anim]: read in %d frames of %d joints with %d animated components\n", _animations[targetAnimationIndex]->getNumberOfFrames(), _animations[targetAnimationIndex]->getNumberOfJoints(), numAnimatedComponents );
    printf( "[.md5anim]: animation's frame rate is %d\n", _animations[targetAnimationIndex]->frameRate );

    // Free temporary data allocated
    delete[] animFrameData;
    delete[] baseFrame;
    delete[] jointInfos;

    // successful loading...set up animation parameters
    _animationInfos[targetAnimationIndex].currFrame = 0;
    _animationInfos[targetAnimationIndex].nextFrame = 1;

    _animationInfos[targetAnimationIndex].lastTime = 0.0f;
    _animationInfos[targetAnimationIndex].maxTime = 1.0f / static_cast<GLfloat>(_animations[targetAnimationIndex]->frameRate);

    // Allocate memory for animated _skeleton
    if (_animations[targetAnimationIndex]->getNumberOfJoints() == 0) {
        fprintf( stderr, "[.md5anim]: Error: md5anim file malformed. numJoints never specified\n" );
    } else {
        _skeleton = new CSCI441_INTERNAL::MD5Joint[_animations[targetAnimationIndex]->getNumberOfJoints()];
    }

    if( _checkAnimValidity(targetAnimationIndex) ) {
        _isAnimated = true;
        // compute initial pose
        animate(0.0);
    }

    return true;
}

inline bool
CSCI441::MD5Model::addMD5Anim(
    const char* filename
) {
    // extend animation array
    auto newAnimations = new CSCI441_INTERNAL::MD5Animation*[_numAnimations + 1];
    auto newAnimationInfos = new CSCI441_INTERNAL::MD5AnimationState[_numAnimations + 1];

    for( int i = 0; i < _numAnimations; ++i ) {
        newAnimations[i] = _animations[i];
        newAnimationInfos[i] = _animationInfos[i];
    }
    newAnimations[_numAnimations] = new CSCI441_INTERNAL::MD5Animation();

    delete[] _animations;
    delete[] _animationInfos;

    _animations = newAnimations;
    _animationInfos = newAnimationInfos;

    _numAnimations++;

    // read animation into new array position
    fprintf( stdout, "\n[.md5anim]: preparing to read %s into new animation %u\n", filename, (_numAnimations-1) );
    const bool readSuccess = readMD5Anim(filename, _numAnimations - 1);

    if (readSuccess) {
        fprintf( stdout, "[.md5anim]: successfully read %s into new animation %u\n", filename, (_numAnimations-1) );
    } else {
        fprintf( stderr, "[.md5anim]: Error: could not read %s into new animation %u\n", filename, (_numAnimations-1) );

        // undo array growth
        newAnimations = new CSCI441_INTERNAL::MD5Animation*[_numAnimations-1];
        newAnimationInfos = new CSCI441_INTERNAL::MD5AnimationState[_numAnimations-1];

        for (int i = 0; i < _numAnimations - 1; ++i) {
            newAnimations[i] = _animations[i];
            newAnimationInfos[i] = _animationInfos[i];
        }
        delete _animations[_numAnimations-1];

        delete[] _animations;
        delete[] _animationInfos;

        _animations = newAnimations;
        _animationInfos = newAnimationInfos;

        _numAnimations--;
    }

    return readSuccess;
}

inline void
CSCI441::MD5Model::useTargetAnimationIndex(
    const GLushort targetAnimationIndex
) {
    // if target index is within range
    if (targetAnimationIndex < _numAnimations) {
        // update animation to run through
        _currentAnimationIndex = targetAnimationIndex;

        // set to base animation
        _animationInfos[targetAnimationIndex].currFrame = 0;
        _animationInfos[targetAnimationIndex].nextFrame = 1;

        _animationInfos[targetAnimationIndex].lastTime = 0.0f;
        _animationInfos[targetAnimationIndex].maxTime = 1.0f / static_cast<GLfloat>(_animations[targetAnimationIndex]->frameRate);

        animate(0.f);
    }
}

inline void
CSCI441::MD5Model::_freeAnim()
{
    delete[] _skeleton;
    _skeleton = nullptr;

    for (int i = 0; i < _numAnimations; i++) {
        delete _animations[i];
    }
    delete[] _animations;
    _animations = nullptr;

    delete[] _animationInfos;
    _animationInfos = nullptr;
}

inline void CSCI441::MD5Model::_moveFromSrc(MD5Model &src) {
    this->_baseSkeleton = src._baseSkeleton;
    src._baseSkeleton = nullptr;

    this->_meshes = src._meshes;
    src._meshes = nullptr;

    this->_maxVertices = src._maxVertices;
    src._maxVertices = 0;

    this->_maxTriangles = src._maxTriangles;
    src._maxTriangles = 0;

    this->_vertexArray = src._vertexArray;
    src._vertexArray = nullptr;

    this->_normalArray = src._normalArray;
    src._normalArray = nullptr;

    this->_tangentArray = src._tangentArray;
    src._tangentArray = nullptr;

    this->_texelArray = src._texelArray;
    src._texelArray = nullptr;

    this->_vertexIndicesArray = src._vertexIndicesArray;
    src._vertexIndicesArray = nullptr;

    this->_vao = src._vao;
    src._vao = 0;

    this->_vbo[0] = src._vbo[0];
    this->_vbo[1] = src._vbo[1];
    src._vbo[0] = 0;
    src._vbo[1] = 0;

    this->_skeletonVAO = src._skeletonVAO;
    src._skeletonVAO = 0;

    this->_skeletonVBO = src._skeletonVBO;
    src._skeletonVBO = 0;

    this->_skeleton = src._skeleton;
    src._skeleton = nullptr;

    this->_animations = src._animations;
    src._animations = nullptr;

    this->_numAnimations = src._numAnimations;
    src._numAnimations = 0;

    this->_currentAnimationIndex = src._currentAnimationIndex;
    src._currentAnimationIndex = 0;

    this->_isAnimated = src._isAnimated;
    src._isAnimated = false;

    this->_animationInfos = src._animationInfos;
    src._animationInfos = nullptr;
}

inline void
CSCI441::MD5Model::_interpolateSkeletons(const GLfloat interp)
{
    const CSCI441_INTERNAL::MD5Joint *skeletonA = _animations[_currentAnimationIndex]->getSkeletonFrame(_animationInfos[_currentAnimationIndex].currFrame);
    const CSCI441_INTERNAL::MD5Joint *skeletonB = _animations[_currentAnimationIndex]->getSkeletonFrame(_animationInfos[_currentAnimationIndex].nextFrame);

    for(GLint i = 0; i < _animations[_currentAnimationIndex]->getNumberOfJoints(); ++i) {
        // Copy parent index
        _skeleton[i].parent = skeletonA[i].parent;

        // Linear interpolation for position
        _skeleton[i].position = glm::mix(skeletonA[i].position, skeletonB[i].position, interp);

        // Spherical linear interpolation for orientation
        _skeleton[i].orientation = glm::slerp(skeletonA[i].orientation, skeletonB[i].orientation, interp);
    }
}

// Perform animation related computations.  Calculate the current and
// next frames, given a delta time.
inline void
CSCI441::MD5Model::animate(const GLfloat dt)
{
    const GLint maxFrames = _animations[_currentAnimationIndex]->getNumberOfFrames() - 1;
    if (maxFrames <= 0) return;

    _animationInfos[_currentAnimationIndex].lastTime += dt;

    // move to next frame
    if( _animationInfos[_currentAnimationIndex].lastTime >= _animationInfos[_currentAnimationIndex].maxTime ) {
        _animationInfos[_currentAnimationIndex].currFrame++;
        _animationInfos[_currentAnimationIndex].nextFrame++;
        _animationInfos[_currentAnimationIndex].lastTime = 0.0;

        if( _animationInfos[_currentAnimationIndex].currFrame > maxFrames )
            _animationInfos[_currentAnimationIndex].currFrame = 0;

        if( _animationInfos[_currentAnimationIndex].nextFrame > maxFrames )
            _animationInfos[_currentAnimationIndex].nextFrame = 0;
    }

    // Interpolate skeletons between two frames
    _interpolateSkeletons( _animationInfos[_currentAnimationIndex].lastTime * static_cast<GLfloat>(_animations[_currentAnimationIndex]->frameRate) );
}

inline std::map< std::string, CSCI441_INTERNAL::MD5MaterialShader* > CSCI441::MD5Model::_materials;
inline std::map< std::string, GLuint > CSCI441::MD5Model::_textureMap;


inline size_t CSCI441::MD5Model::_trim(char* out, const size_t len, const char* str) {
    if(len == 0)
        return 0;

    // Trim leading space
    while( isspace(static_cast<unsigned char>(*str)) ) str++;

    if(*str == 0)  // All spaces?
    {
        *out = 0;
        return 1;
    }

    // Trim trailing space
    const char *end = str + strlen(str) - 1;
    while( end > str && isspace(static_cast<unsigned char>(*end)) ) end--;
    end++;

    // Set output size to minimum of trimmed string length and buffer size minus 1
    const size_t out_size = (end - str) < len - 1 ? (end - str) : len - 1;

    // Copy trimmed string and add null terminator
    memcpy(out, str, out_size);
    out[out_size] = '\0';

    return out_size;
}

inline bool CSCI441::MD5Model::_registerShaderTexture(CSCI441_INTERNAL::MD5Texture *texture) {
    if (const auto textureIter = _textureMap.find( texture->filename ); textureIter == _textureMap.end()) {
        texture->texHandle = CSCI441::TextureUtils::loadAndRegisterTexture( texture->filename, GL_LINEAR, GL_LINEAR_MIPMAP_LINEAR, GL_REPEAT, GL_REPEAT, GL_FALSE, GL_FALSE);
        if( texture->texHandle == 0 ) {
            // silently failing to avoid many unnecessary error messages
            //fprintf(stderr, "[.md5mtr | ERROR]: Could not load diffuse map %s for shader %s\n", shader->textures[MD5MaterialShader::TextureMap::DIFFUSE].filename, shader->shader);
        } else {
            // only display successes which likely refer to what we are using
            _textureMap.insert( std::pair( texture->filename, texture->texHandle) );
            return true;
        }
    } else {
        texture->texHandle = textureIter->second;
    }
    return false;
}

inline void
CSCI441::MD5Model::readMD5Material(const char *FILENAME) {
    char buff[512], buff2[512];
    GLushort numTextures = 0;

    fprintf(stdout, "\n[.md5mtr]: about to read %s\n", FILENAME );

    FILE *fp = fopen(FILENAME, "rb" );
    if( !fp ) {
        fprintf (stderr, "[.md5mtr]: Error: couldn't open \"%s\"!\n", FILENAME);
        return;
    }

    while( !feof(fp) ) {
        // Read whole line
        fgets( buff, sizeof(buff), fp );

        _trim(buff, 512, buff);

        if( sscanf(buff, "table %s", buff2) == 1 ) {
            // fprintf(stdout, "[.md5mtr]: ignoring table line\n");
        } else if ( sscanf(buff, "//%s", buff2) == 1 ) {
            // fprintf(stdout, "[.md5mtr]: ignoring comment\n");
        } else if (strnlen(buff, sizeof(buff)) == 0) {
            // fprintf(stdout, "[.md5mtr]: ignoring empty line\n");
        } else {
            // assuming this begins a shader
            auto shader = new CSCI441_INTERNAL::MD5MaterialShader();

            strncpy(shader->name, buff, sizeof(buff));
            // fprintf(stdout, "[.md5mtr]: parsing shader \"%s\"\n", shader->shader);

            unsigned short numBlocks = 0;

            // read line, fails in event of malformed file
            while ( fgets( buff, sizeof(buff), fp ) != nullptr) {
                _trim(buff, 512, buff);

                if (strchr(buff, '{') != nullptr) {
                    // found opening block
                    ++numBlocks;
                }
                else if (sscanf(buff, " diffusemap %s", buff2) == 1) {
                    // fprintf(stdout, "[.md5mtr]: attempting to read diffusemap %s\n", buff2);
                    strncpy( shader->textures[CSCI441_INTERNAL::MD5MaterialShader::TextureMap::DIFFUSE].filename, buff2, sizeof(buff2) );
                    if (_registerShaderTexture( &shader->textures[CSCI441_INTERNAL::MD5MaterialShader::TextureMap::DIFFUSE] )) {
                        ++numTextures;
                    }
                }
                else if (sscanf(buff, " specularmap %s", buff2) == 1) {
                    // fprintf(stdout, "[.md5mtr]: attempting to read specularmap %s\n", buff2);
                    strncpy( shader->textures[CSCI441_INTERNAL::MD5MaterialShader::TextureMap::SPECULAR].filename, buff2, sizeof(buff2) );
                    if (_registerShaderTexture( &shader->textures[CSCI441_INTERNAL::MD5MaterialShader::TextureMap::SPECULAR] )) {
                        ++numTextures;
                    }
                }
                // make sure getting top level shader bumpmap
                else if (numBlocks == 1 && sscanf(buff, " bumpmap %s", buff2) == 1) {
                    // fprintf(stdout, "[.md5mtr]: attempting to read bumpmap line \"%s\"\n", buff);
                    // tokenize string
                    std::vector< char* > tokens;
                    char* pch = strtok(buff, " \t(),");
                    while (pch != NULL) {
                        tokens.push_back( pch );
                        pch = strtok(NULL, " \t(),");
                    }
                    // fprintf(stdout, "[.md5mtr]: found %lu tokens\n", tokens.size());
                    // line is formatted: bumpmap normalTxtr
                    // normal map texture filename is in tokens[1]
                    if (tokens.size() == 2) {
                        strncpy( shader->textures[CSCI441_INTERNAL::MD5MaterialShader::TextureMap::NORMAL].filename, tokens[1], strlen(tokens[1]) );
                        if (_registerShaderTexture( &shader->textures[CSCI441_INTERNAL::MD5MaterialShader::TextureMap::NORMAL] )) {
                            ++numTextures;
                        }
                    }
                    // line is formatted: bumpmap heightmap(heightTxtr, scale)
                    // height map texture filename is in tokens[2]
                    // displacement scale is in tokens[3]
                    else if (tokens.size() == 4) {
                        strncpy( shader->textures[CSCI441_INTERNAL::MD5MaterialShader::TextureMap::HEIGHT].filename, tokens[2], strlen(tokens[2]) );
                        shader->displacementScale = strtol(tokens[3], NULL, 10);
                        if (_registerShaderTexture( &shader->textures[CSCI441_INTERNAL::MD5MaterialShader::TextureMap::HEIGHT] )) {
                            ++numTextures;
                        }
                    }
                    // line is formatted: bumpmap addnormals(normalTxtr, heightMap(heightTxtr, scale))
                    // normal map texture filename is in tokens[2]
                    // height map texture filename is in tokens[4]
                    // displacement scale is in tokens[5]
                    else if (tokens.size() == 6) {
                        strncpy( shader->textures[CSCI441_INTERNAL::MD5MaterialShader::TextureMap::NORMAL].filename, tokens[2], strlen(tokens[2]) );
                        if (_registerShaderTexture( &shader->textures[CSCI441_INTERNAL::MD5MaterialShader::TextureMap::NORMAL] )) {
                            ++numTextures;
                        }
                        strncpy( shader->textures[CSCI441_INTERNAL::MD5MaterialShader::TextureMap::HEIGHT].filename, tokens[4], strlen(tokens[4]) );
                        shader->displacementScale = strtol(tokens[5], NULL, 10);
                        if (_registerShaderTexture( &shader->textures[CSCI441_INTERNAL::MD5MaterialShader::TextureMap::HEIGHT] )) {
                            ++numTextures;
                        }
                    }
                }
                else if (strchr(buff, '}') != nullptr) {
                    --numBlocks;
                    // if all blocks have been closed, then we are at end of shader
                    if (numBlocks == 0) {
                        break;
                    }
                }
            }

            _materials.insert( std::pair(shader->name, shader) );
        }
    }
    fclose(fp);

    fprintf(stdout, "[.md5mtr]: finished reading %s\n", FILENAME );
    fprintf(stdout, "[.md5mtr]: read in %lu shaders and %u textures\n\n", _materials.size(), numTextures );
}

inline void
CSCI441::MD5Model::releaseMD5Materials() {
    for (auto &[name, material] : _materials) {
        glDeleteTextures(1, &material->textures[CSCI441_INTERNAL::MD5MaterialShader::TextureMap::DIFFUSE].texHandle);
        glDeleteTextures(1, &material->textures[CSCI441_INTERNAL::MD5MaterialShader::TextureMap::SPECULAR].texHandle);
        glDeleteTextures(1, &material->textures[CSCI441_INTERNAL::MD5MaterialShader::TextureMap::HEIGHT].texHandle);
        glDeleteTextures(1, &material->textures[CSCI441_INTERNAL::MD5MaterialShader::TextureMap::NORMAL].texHandle);
        delete material;
    }
}

#endif//CSCI441_MD5_MODEL_HPP
