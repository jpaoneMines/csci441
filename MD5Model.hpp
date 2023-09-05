#ifndef CSCI441_MD5_MODEL_HPP
#define CSCI441_MD5_MODEL_HPP

/*
 * md5mesh model loader + animation
 * last modification: 01 september 2023 (Dr. Jeffrey Paone)
 * encapsulated into a class
 * supports texturing
 *
 * Doom3's md5mesh viewer with animation.  Mesh and Animation declaration
 * Dependencies: md5mesh.cpp, md5anim.cpp
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

#include <GL/glew.h>
#include <glm/exponential.hpp>
#include <stb_image.h>

#include <cassert>
#include <cmath>
#include <cstdio>
#include <cstdlib>
#include <cstring>

namespace CSCI441 {
    // Vectors
    typedef GLfloat vector2_t[2];
    typedef GLfloat vector3_t[3];

    // Quaternion (x, y, z, w)
    typedef GLfloat quaternion4_t[4];

    enum { X, Y, Z, W };

    // Quaternion prototypes
    void quaternion_compute_w(quaternion4_t q);
    void quaternion_normalize(quaternion4_t q);
    void quaternion_multiply_quaternion(const quaternion4_t QA, const quaternion4_t QB, quaternion4_t out);
    void quaternion_multiply_vector(const quaternion4_t Q, const vector3_t V, quaternion4_t out);
    void quaternion_rotate_point(const quaternion4_t Q, const vector3_t IN, vector3_t out);
    GLfloat quaternion_dot_product(const quaternion4_t QA, const quaternion4_t QB);
    void quaternion_slerp(const quaternion4_t QA, const quaternion4_t QB, GLfloat T, quaternion4_t out);

    class MD5Model {
    protected:
        // Joint
        struct MD5Joint {
            static const GLint NULL_JOINT = -1;

            char name[256] = "";
            GLint parent = NULL_JOINT;

            vector3_t position = {0.0f, 0.0f, 0.0f};
            quaternion4_t orientation = {0.0f, 0.0f, 0.0f, 0.0f};
        };

        // Joint info
        struct MD5JointInfo {
            char name[256] = "";
            GLint parent = MD5Joint::NULL_JOINT;
            GLuint flags = 0;
            GLint startIndex = 0;
        };

        // Base frame joint
        struct MD5BaseFrameJoint {
            vector3_t position = {0.0f, 0.0f, 0.0f};
            quaternion4_t orientation = {0.0f, 0.0f, 0.0f, 0.0f};
        };

        // Vertex
        struct MD5Vertex {
            vector2_t st = {0.0f, 0.0f};

            GLint start = 0; // start weight
            GLint count = 0; // weight count
        };

        // Triangle
        struct MD5Triangle {
            GLint index[3] = {0};
        };

        // Weight
        struct MD5Weight {
            GLint joint = 0;
            GLfloat bias = 0.f;

            vector3_t position = {0.0f, 0.0f, 0.0f};
        };

        // Texture Handles
        struct MD5Texture {
            GLuint texHandle = 0;
            char filename[512] = "";
        };

        // Bounding box
        struct MD5BoundingBox {
            vector3_t min = {0.0f, 0.0f, 0.0f};
            vector3_t max = {0.0f, 0.0f, 0.0f};
        };

        // MD5 mesh
        struct MD5Mesh {
            MD5Vertex *vertices = nullptr;
            MD5Triangle *triangles = nullptr;
            MD5Weight *weights = nullptr;
            MD5Texture textures[4];

            GLint numVertices = 0;
            GLint numTriangles = 0;
            GLint numWeights = 0;

            char shader[512] = "";
        };

        // Animation data
        struct MD5Animation {
            GLint numFrames = 0;
            GLint numJoints = 0;
            GLint frameRate = 0;

            MD5Joint **skeletonFrames = nullptr;
            MD5BoundingBox *boundingBoxes = nullptr;
        };

        // Animation info
        struct MD5AnimationInfo {
            GLint currFrame = 0;
            GLint nextFrame = 0;

            GLdouble lastTime = 0.0;
            GLdouble maxTime = 0.0;
        };

    public:
        /**
         * initializes an empty MD5 Model
         * @note need to call loadMD5Model() or readMD5Model() after construction to actually load in a mesh file
         */
        MD5Model();
        /**
         * deallocates any used memory on the CPU and GPU
         */
        ~MD5Model();

        /**
         * @brief loads a corresponding md5mesh and md5anim file to the object
         * @param MD5_MESH_FILE name of file to load mesh from
         * @param MD5_ANIM_FILE name of file to load animation from
         */
        bool loadMD5Model(const char* MD5_MESH_FILE, const char* MD5_ANIM_FILE = "");

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
        void allocVertexArrays(GLuint vPosAttribLoc, GLuint vColorAttribLoc, GLuint vTexCoordAttribLoc);
        /**
         * @brief draws all the meshes that make up the model
         */
        void draw() const;
        /**
         * @brief draws the skeleton joints (as points) and bones (as lines)
         */
        void drawSkeleton() const;

        // md5anim prototypes
        /**
         * reads in an animation sequence from an external file
         * @param filename *.md5anim file to open
         * @returns true iff mesh and animation are compatible
         */
        [[nodiscard]] bool readMD5Anim(const char* filename);
        /**
         * advances the model forward in its animation sequence the corresponding amount of time based on frame rate
         * @param dt delta time since last frame
         */
        void animate(GLdouble dt);

    private:
        MD5Joint* _baseSkeleton;
        MD5Mesh* _meshes;

        GLint _numJoints;
        GLint _numMeshes;

        // vertex array related stuff
        GLint _maxVertices;
        GLint _maxTriangles;

        vector3_t* _vertexArray;
        vector2_t* _texelArray;
        GLuint* _vertexIndicesArray;

        GLuint _vao;
        GLuint* _vbo;

        GLuint _skeletonVAO;
        GLuint _skeletonVBO;

        /**
         * @brief the MD5 animation sequence
         */
        MD5Animation _animation;
        /**
         * @brief the MD5 skeletal bone/joint data
         */
        MD5Joint* _skeleton;
        /**
         * @brief the MD5 animation frames
         */
        MD5AnimationInfo _animationInfo;
        /**
         * @brief flag stating if the loaded MD5 model has a corresponding animation or not
         */
        bool _isAnimated;

        void _prepareMesh(const MD5Mesh* pMESH) const;
        void _drawMesh(const MD5Mesh* pMESH) const;
        [[nodiscard]] bool _checkAnimValidity() const;
        static void _buildFrameSkeleton(const MD5JointInfo* pJOINT_INFOS,
                                        const MD5BaseFrameJoint* pBASE_FRAME,
                                        const GLfloat* pANIM_FRAME_DATA,
                                        MD5Joint* pSkeletonFrame,
                                        GLint NUM_JOINTS);
        void _interpolateSkeletons(GLdouble interp);
        void _freeModel();
        void _freeVertexArrays();
        void _freeAnim();
    };
}

//----------------------------------------------------------------------------------------------------

// Basic quaternion operations.
inline void
CSCI441::quaternion_compute_w(
        quaternion4_t q
) {
    GLfloat t = 1.0f - (q[X] * q[X]) - (q[Y] * q[Y]) - (q[Z] * q[Z]);

    if( t < 0.0f )  q[W] = 0.0f;
    else            q[W] = -glm::sqrt(t);
}

inline void
CSCI441::quaternion_normalize(
        quaternion4_t q
) {
    // compute magnitude of the quaternion
    GLfloat mag = glm::sqrt( (q[X] * q[X]) + (q[Y] * q[Y]) + (q[Z] * q[Z]) + (q[W] * q[W]) );

    // check for bogus length, to protect against divide by zero
    if( mag > 0.0f ) {
        // normalize it
        GLfloat oneOverMag = 1.0f / mag;

        q[X] *= oneOverMag;
        q[Y] *= oneOverMag;
        q[Z] *= oneOverMag;
        q[W] *= oneOverMag;
    }
}

inline void
CSCI441::quaternion_multiply_quaternion(
        const quaternion4_t QA,
        const quaternion4_t QB,
        quaternion4_t out
) {
    out[W] = (QA[W] * QB[W]) - (QA[X] * QB[X]) - (QA[Y] * QB[Y]) - (QA[Z] * QB[Z]);
    out[X] = (QA[X] * QB[W]) + (QA[W] * QB[X]) + (QA[Y] * QB[Z]) - (QA[Z] * QB[Y]);
    out[Y] = (QA[Y] * QB[W]) + (QA[W] * QB[Y]) + (QA[Z] * QB[X]) - (QA[X] * QB[Z]);
    out[Z] = (QA[Z] * QB[W]) + (QA[W] * QB[Z]) + (QA[X] * QB[Y]) - (QA[Y] * QB[X]);
}

inline void
CSCI441::quaternion_multiply_vector(
        const quaternion4_t Q,
        const vector3_t V,
        quaternion4_t out
) {
    out[W] = -(Q[X] * V[X]) - (Q[Y] * V[Y]) - (Q[Z] * V[Z]);
    out[X] =  (Q[W] * V[X]) + (Q[Y] * V[Z]) - (Q[Z] * V[Y]);
    out[Y] =  (Q[W] * V[Y]) + (Q[Z] * V[X]) - (Q[X] * V[Z]);
    out[Z] =  (Q[W] * V[Z]) + (Q[X] * V[Y]) - (Q[Y] * V[X]);
}

inline void
CSCI441::quaternion_rotate_point(
        const quaternion4_t Q,
        const vector3_t IN,
        vector3_t out
) {
    quaternion4_t tmp, inv, final;

    inv[X] = -Q[X]; inv[Y] = -Q[Y];
    inv[Z] = -Q[Z]; inv[W] =  Q[W];

    quaternion_normalize(inv);

    quaternion_multiply_vector(Q, IN, tmp);
    quaternion_multiply_quaternion(tmp, inv, final);

    out[X] = final[X];
    out[Y] = final[Y];
    out[Z] = final[Z];
}

inline GLuint
loadTexture(
        const char* FILENAME
) {
    GLint imageWidth, imageHeight, imageChannels;
    GLuint textureHandle = 0;
    stbi_set_flip_vertically_on_load(false);
    GLubyte* data = stbi_load( FILENAME, &imageWidth, &imageHeight, &imageChannels, 0);

    if( data ) {
        glGenTextures(1, &textureHandle);
        glBindTexture(GL_TEXTURE_2D, textureHandle);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);

        const GLint STORAGE_TYPE = (imageChannels == 4 ? GL_RGBA : GL_RGB);
        glTexImage2D( GL_TEXTURE_2D, 0, STORAGE_TYPE, imageWidth, imageHeight, 0, STORAGE_TYPE, GL_UNSIGNED_BYTE, data);
        glGenerateMipmap(GL_TEXTURE_2D);

        printf( "[.md5mesh]: %s texture map read in with handle %d\n", FILENAME, textureHandle);
    }

    return textureHandle;
}

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
    _vbo = nullptr;
    _skeletonVAO = 0;
    _skeletonVBO = 0;
    _animation = MD5Animation();
    _skeleton = nullptr;
    _animationInfo = MD5AnimationInfo();
    _isAnimated = false;
}

inline CSCI441::MD5Model::~MD5Model()
{
    _freeVertexArrays();
    _freeAnim();
    _freeModel();
}

// load our MD5 model
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

    GLint totalVertices = 0;
    GLint totalWeights = 0;
    GLint totalTriangles = 0;

    GLdouble minX =  999999, minY =  999999, minZ =  999999;
    GLdouble maxX = -999999, maxY = -999999, maxZ = -999999;

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
                    quaternion_compute_w(joint->orientation);
                }
            }
        } else if( strncmp(buff, "mesh {", 6) == 0 ) {
            MD5Mesh *mesh = &_meshes[currentMesh];
            GLint vert_index = 0;
            GLint tri_index = 0;
            GLint weight_index = 0;
            GLfloat fdata[4];
            GLint idata[3];

            while( (buff[0] != '}') && !feof(fp) ) {
                // Read whole line
                fgets( buff, sizeof(buff), fp );

                if( strstr( buff, "shader ") ) {
                    GLint quote = 0, j = 0;

                    // Copy the shader name without the quote marks
                    for(i = 0; i < sizeof (buff) && (quote < 2); ++i) {
                        if( buff[i] == '\"' )
                            quote++;

                        if( (quote == 1) && (buff[i] != '\"') ) {
                            mesh->shader[j] = buff[i];
                            j++;
                        }
                    }

                    // there was a shader name
                    if( j > 0 ) {
                        // diffuse map
                        strcpy(mesh->textures[0].filename, mesh->shader);
                        strcat(mesh->textures[0].filename, ".tga");
                        mesh->textures[0].texHandle = loadTexture( mesh->textures[0].filename );
                        if( mesh->textures[0].texHandle == 0 ) {
                            strcpy(mesh->textures[0].filename, mesh->shader);
                            strcat(mesh->textures[0].filename, "_d.tga");
                            mesh->textures[0].texHandle = loadTexture( mesh->textures[0].filename );
                            if( mesh->textures[0].texHandle == 0 ) {
                                strcpy(mesh->textures[0].filename, mesh->shader);
                                strcat(mesh->textures[0].filename, ".png");
                                mesh->textures[0].texHandle = loadTexture(mesh->textures[0].filename);
                            }
                        }

                        // specular map
                        strcpy(mesh->textures[1].filename, mesh->shader);
                        strcat(mesh->textures[1].filename, "_s.tga");
                        mesh->textures[1].texHandle = loadTexture( mesh->textures[1].filename );
                        if( mesh->textures[1].texHandle == 0 ) {
                            strcpy(mesh->textures[1].filename, mesh->shader);
                            strcat(mesh->textures[1].filename, "_s.png");
                            mesh->textures[1].texHandle = loadTexture( mesh->textures[1].filename );
                        }

                        // normal map
                        strcpy(mesh->textures[2].filename, mesh->shader);
                        strcat(mesh->textures[2].filename, "_local.tga");
                        mesh->textures[2].texHandle = loadTexture( mesh->textures[2].filename );
                        if( mesh->textures[2].texHandle == 0 ) {
                            strcpy(mesh->textures[2].filename, mesh->shader);
                            strcat(mesh->textures[2].filename, "_local.png");
                            mesh->textures[2].texHandle = loadTexture( mesh->textures[2].filename );
                        }

                        // height map
                        strcpy(mesh->textures[3].filename, mesh->shader);
                        strcat(mesh->textures[3].filename, "_h.tga");
                        mesh->textures[3].texHandle = loadTexture( mesh->textures[3].filename );
                        if( mesh->textures[3].texHandle == 0 ) {
                            strcpy(mesh->textures[3].filename, mesh->shader);
                            strcat(mesh->textures[3].filename, "_h.png");
                            mesh->textures[3].texHandle = loadTexture( mesh->textures[3].filename );
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
                    mesh->vertices[vert_index].st[0] = fdata[0];
                    mesh->vertices[vert_index].st[1] = fdata[1];
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
        vector3_t finalVertex = {0.0f, 0.0f, 0.0f };

        // Calculate final vertex to draw with weights
        for(j = 0; j < pMESH->vertices[i].count; ++j) {
            const MD5Weight *weight = &pMESH->weights[pMESH->vertices[i].start + j];
            const MD5Joint  *joint  = &_skeleton[weight->joint];

            // Calculate transformed vertex for this weight
            vector3_t wv;
            quaternion_rotate_point(joint->orientation, weight->position, wv);

            // The sum of all weight->bias should be 1.0
            finalVertex[0] += (joint->position[0] + wv[0]) * weight->bias;
            finalVertex[1] += (joint->position[1] + wv[1]) * weight->bias;
            finalVertex[2] += (joint->position[2] + wv[2]) * weight->bias;
        }

        _vertexArray[i][0] = finalVertex[0];
        _vertexArray[i][1] = finalVertex[1];
        _vertexArray[i][2] = finalVertex[2];

        _texelArray[i][0] = pMESH->vertices[i].st[0];
        _texelArray[i][1] = pMESH->vertices[i].st[1];
    }

    glBindVertexArray(_vao );
    glBindBuffer(GL_ARRAY_BUFFER, _vbo[0] );
    glBufferSubData(GL_ARRAY_BUFFER, 0, sizeof(vector3_t) * pMESH->numVertices, _vertexArray );
    glBufferSubData(GL_ARRAY_BUFFER, sizeof(vector3_t) * _maxVertices, sizeof(vector2_t) * pMESH->numVertices, _texelArray );
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, _vbo[1] );
    glBufferSubData(GL_ELEMENT_ARRAY_BUFFER, 0, sizeof(GLuint) * pMESH->numTriangles * 3, _vertexIndicesArray );
}

inline void
CSCI441::MD5Model::_drawMesh(
        const MD5Mesh *pMESH
) const {
    // Bind Diffuse Map
    glBindTexture(GL_TEXTURE_2D, pMESH->textures[0].texHandle );

    glBindVertexArray(_vao );
    glDrawElements(GL_TRIANGLES, pMESH->numTriangles * 3, GL_UNSIGNED_INT, (void*)nullptr );
}

inline void
CSCI441::MD5Model::allocVertexArrays(
        GLuint vPosAttribLoc,
        GLuint vColorAttribLoc,
        GLuint vTexCoordAttribLoc
) {
    _vertexArray = new vector3_t[_maxVertices];
    _texelArray = new vector2_t[_maxVertices];
    _vertexIndicesArray = new GLuint[_maxTriangles * 3];
    _vbo = new GLuint[2];

    glGenVertexArrays( 1, &_vao );
    glBindVertexArray(_vao );

    glGenBuffers(2, _vbo );
    glBindBuffer(GL_ARRAY_BUFFER, _vbo[0] );
    glBufferData(GL_ARRAY_BUFFER, sizeof(vector3_t) * _maxVertices + sizeof(vector2_t) * _maxVertices, nullptr, GL_DYNAMIC_DRAW );

    glEnableVertexAttribArray( vPosAttribLoc );
    glVertexAttribPointer( vPosAttribLoc, 3, GL_FLOAT, GL_FALSE, 0, (void*)nullptr );

    glEnableVertexAttribArray( vTexCoordAttribLoc );
    glVertexAttribPointer( vTexCoordAttribLoc, 2, GL_FLOAT, GL_FALSE, 0, (void*)(sizeof(vector3_t) * _maxVertices) );

    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, _vbo[1] );
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(GLuint) * _maxTriangles * 3, nullptr, GL_DYNAMIC_DRAW );

    printf("[.md5mesh]: Model VAO/VBO/IBO registered at %u/%u/%u\n", _vao, _vbo[0], _vbo[1] );

    glGenVertexArrays( 1, &_skeletonVAO );
    glBindVertexArray(_skeletonVAO );

    glGenBuffers( 1, &_skeletonVBO );
    glBindBuffer(GL_ARRAY_BUFFER, _skeletonVBO );
    glBufferData(GL_ARRAY_BUFFER, sizeof(vector3_t) * _numJoints * 3 * 2, nullptr, GL_DYNAMIC_DRAW );

    glEnableVertexAttribArray( vPosAttribLoc ); // vPos
    glVertexAttribPointer( vPosAttribLoc, 3, GL_FLOAT, GL_FALSE, 0, (void*)nullptr );

    glEnableVertexAttribArray( vColorAttribLoc ); // vColor
    glVertexAttribPointer( vColorAttribLoc, 3, GL_FLOAT, GL_FALSE, 0, (void*)(sizeof(vector3_t) * _numJoints * 3) );

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

    delete[] _vbo;
    _vbo = nullptr;
}

// Draw the skeleton as lines and points (for joints).
inline void
CSCI441::MD5Model::drawSkeleton() const
{
    glBindVertexArray(_skeletonVAO );
    glBindBuffer(GL_ARRAY_BUFFER, _skeletonVBO );

    vector3_t jointColor = {1.0f, 1.0f, 0.0f };
    vector3_t boneColor = {1.0f, 0.0f, 1.0f };

    // put in points for joints
    for(GLint i = 0; i < _numJoints; ++i ) {
        glBufferSubData(GL_ARRAY_BUFFER, i * sizeof(vector3_t), sizeof(vector3_t), &(_skeleton[i].position) );
        glBufferSubData(GL_ARRAY_BUFFER, i * sizeof(vector3_t) + sizeof(vector3_t) * _numJoints * 3, sizeof(vector3_t), jointColor);
    }

    // put in lines for bones
    GLint numBones = 0;
    for(GLint i = 0; i < _numJoints; ++i ) {
        if( _skeleton[i].parent != MD5Joint::NULL_JOINT ) {
            glBufferSubData(GL_ARRAY_BUFFER, sizeof(vector3_t) * _numJoints + (i * 2) * sizeof(vector3_t), sizeof(vector3_t), &(_skeleton[_skeleton[i].parent].position) );
            glBufferSubData(GL_ARRAY_BUFFER, sizeof(vector3_t) * _numJoints + (i * 2) * sizeof(vector3_t) + sizeof(vector3_t) * _numJoints * 3, sizeof(vector3_t), boneColor);

            glBufferSubData(GL_ARRAY_BUFFER, sizeof(vector3_t) * _numJoints + (i * 2) * sizeof(vector3_t) + sizeof(vector3_t), sizeof(vector3_t), &(_skeleton[i].position) );
            glBufferSubData(GL_ARRAY_BUFFER, sizeof(vector3_t) * _numJoints + (i * 2) * sizeof(vector3_t) + sizeof(vector3_t) + sizeof(vector3_t) * _numJoints * 3, sizeof(vector3_t), boneColor);
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

// More quaternion operations for skeletal animation.

inline GLfloat
CSCI441::quaternion_dot_product(
        const quaternion4_t QA,
        const quaternion4_t QB
) {
    return ((QA[X] * QB[X]) + (QA[Y] * QB[Y]) + (QA[Z] * QB[Z]) + (QA[W] * QB[W]));
}

inline void
CSCI441::quaternion_slerp(
        const quaternion4_t QA,
        const quaternion4_t QB,
        const GLfloat T,
        quaternion4_t out
) {
    // Check for out-of range parameter and return edge points if so
    if(T <= 0.0 ) {
        memcpy(out, QA, sizeof(quaternion4_t) );
        return;
    }

    if(T >= 1.0 ) {
        memcpy(out, QB, sizeof (quaternion4_t) );
        return;
    }

    // Compute "cosine of angle between quaternions" using dot product
    GLfloat cosOmega = quaternion_dot_product(QA, QB);

    // If negative dot, use -q1.  Two quaternions q and -q
    // represent the same rotation, but may produce
    // different slerp.  We chose q or -q to rotate using
    // the acute angle.
    GLfloat q1w = QB[W];
    GLfloat q1x = QB[X];
    GLfloat q1y = QB[Y];
    GLfloat q1z = QB[Z];

    if( cosOmega < 0.0f ) {
        q1w = -q1w;
        q1x = -q1x;
        q1y = -q1y;
        q1z = -q1z;
        cosOmega = -cosOmega;
    }

    // We should have two unit quaternions, so dot should be <= 1.0
    assert( cosOmega < 1.1f );

    // Compute interpolation fraction, checking for quaternions
    // almost exactly the same
    GLfloat k0, k1;

    if( cosOmega > 0.9999f ) {
        // Very close - just use linear interpolation,
        // which will protect against a divide by zero

        k0 = 1.0f - T;
        k1 = T;
    } else {
        // Compute the sin of the angle using the
        // trig identity sin^2(omega) + cos^2(omega) = 1
        GLfloat sinOmega = sqrt (1.0f - (cosOmega * cosOmega));

        // Compute the angle from its sin and cosine
        GLfloat omega = atan2 (sinOmega, cosOmega);

        // Compute inverse of denominator, so we only have
        // to divide once
        GLfloat oneOverSinOmega = 1.0f / sinOmega;

        // Compute interpolation parameters
        k0 = sin ((1.0f - T) * omega) * oneOverSinOmega;
        k1 = sin (T * omega) * oneOverSinOmega;
    }

    // Interpolate and return new quaternion
    out[W] = (k0 * QA[3]) + (k1 * q1w);
    out[X] = (k0 * QA[0]) + (k1 * q1x);
    out[Y] = (k0 * QA[1]) + (k1 * q1y);
    out[Z] = (k0 * QA[2]) + (k1 * q1z);
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
        vector3_t animatedPosition;
        quaternion4_t animatedOrientation;
        GLint j = 0;

        memcpy(animatedPosition, baseJoint->position, sizeof(vector3_t) );
        memcpy(animatedOrientation, baseJoint->orientation, sizeof(quaternion4_t) );

        // Tx
        if(pJOINT_INFOS[i].flags & 1 ) {
            animatedPosition[0] = pANIM_FRAME_DATA[pJOINT_INFOS[i].startIndex + j];
            ++j;
        }

        // Ty
        if(pJOINT_INFOS[i].flags & 2 ) {
            animatedPosition[1] = pANIM_FRAME_DATA[pJOINT_INFOS[i].startIndex + j];
            ++j;
        }

        // Tz
        if(pJOINT_INFOS[i].flags & 4 ) {
            animatedPosition[2] = pANIM_FRAME_DATA[pJOINT_INFOS[i].startIndex + j];
            ++j;
        }

        // Qx
        if(pJOINT_INFOS[i].flags & 8 ) {
            animatedOrientation[0] = pANIM_FRAME_DATA[pJOINT_INFOS[i].startIndex + j];
            ++j;
        }

        // Qy
        if(pJOINT_INFOS[i].flags & 16 ) {
            animatedOrientation[1] = pANIM_FRAME_DATA[pJOINT_INFOS[i].startIndex + j];
            ++j;
        }

        // Qz
        if(pJOINT_INFOS[i].flags & 32 ) {
            animatedOrientation[2] = pANIM_FRAME_DATA[pJOINT_INFOS[i].startIndex + j];
        }

        // Compute orientation quaternion's w value
        quaternion_compute_w(animatedOrientation);

        // NOTE: we assume that this joint's parent has
        // already been calculated, i.e. joint's ID should
        // never be smaller than its parent ID.
        MD5Joint *thisJoint = &pSkeletonFrame[i];

        GLint parent = pJOINT_INFOS[i].parent;
        thisJoint->parent = parent;
        strcpy (thisJoint->name, pJOINT_INFOS[i].name);

        // Has parent?
        if( thisJoint->parent < 0 ) {
            memcpy (thisJoint->position, animatedPosition, sizeof (vector3_t));
            memcpy (thisJoint->orientation, animatedOrientation, sizeof (quaternion4_t));
        } else {
            MD5Joint *parentJoint = &pSkeletonFrame[parent];
            vector3_t rpos; // Rotated position

            // Add positions
            quaternion_rotate_point(parentJoint->orientation, animatedPosition, rpos);
            thisJoint->position[0] = rpos[0] + parentJoint->position[0];
            thisJoint->position[1] = rpos[1] + parentJoint->position[1];
            thisJoint->position[2] = rpos[2] + parentJoint->position[2];

            // Concatenate rotations
            quaternion_multiply_quaternion(parentJoint->orientation, animatedOrientation, thisJoint->orientation);
            quaternion_normalize(thisJoint->orientation);
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
    GLint frame_index;
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
            // Allocate memory for _skeleton frames and bounding boxes
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
                    quaternion_compute_w( baseFrame[i].orientation );
                }
            }
        } else if( sscanf(buff, " frame %d", &frame_index) == 1 ) {
            // Read frame data
            for(i = 0; i < numAnimatedComponents; ++i)
                fscanf( fp, "%f", &animFrameData[i] );

            // Build frame _skeleton from the collected data
            _buildFrameSkeleton(jointInfos, baseFrame, animFrameData,
                                _animation.skeletonFrames[frame_index],
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

    _animationInfo.lastTime = 0;
    _animationInfo.maxTime = 1.0 / _animation.frameRate;

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
CSCI441::MD5Model::_interpolateSkeletons(GLdouble interp)
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
        quaternion_slerp(skeletonA[i].orientation, skeletonB[i].orientation, interp, _skeleton[i].orientation);
    }
}

// Perform animation related computations.  Calculate the current and
// next frames, given a delta time.
inline void
CSCI441::MD5Model::animate(GLdouble dt)
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
