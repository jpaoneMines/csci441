/**
 * @file teapot.hpp
 * @brief Helper functions to draw teapot with OpenGL 3.0+
 *
 * @warning NOTE: This header file will only work with OpenGL 3.0+
 *
 * From the OpenGL Programming wikibook: http://en.wikibooks.org/wiki/OpenGL_Programming
 * This file is in the public domain.
 * https://gitlab.com/wikibooks-opengl/modern-tutorials/blob/master/bezier_teapot/teapot.cpp
 * Contributors: Sylvain Beucler
 *
 * Modified by Dr. Jeffrey Paone to work in Colorado School of Mines CSCI441 course context.
 *
 * @warning This header file depends upon GLEW
 */

#ifndef CSCI441_TEAPOT_HPP
#define CSCI441_TEAPOT_HPP

#include <cstdio>
#include <cstdlib>
#include <cmath>

#include <GL/glew.h>

namespace CSCI441_INTERNAL {

    // Draws the Utah teapot as a static collection of Bezier surfaces with position, normal, and texture vertex data
    // GLfloat unused (kept for legacy consistency)
    // GLint vertex position attribute location within shader program
    // GLint vertex normal attribute location within shader program (defaults to -1 and unused)
    // GLint vertex texture coordinate attribute location within shader program (defaults to -1 and unused)
    [[maybe_unused]] void teapot( GLfloat size, GLint positionLocation, GLint normalLocation = -1, GLint texCoordLocation = -1);

    // Enables VBO attribute array locations
    // GLint vertex position attribute location within shader program
    // GLint vertex normal attribute location within shader program (defaults to -1 and unused)
    // GLint vertex texture coordinate attribute location within shader program (defaults to -1 and unused)
    void setTeapotAttributeLocations(GLint positionLocation, GLint normalLocation = -1, GLint texCoordLocation = -1);

    // Draws the Utah teapot as a static collection of Bezier surfaces with position, normal, and
    // texture vertex data
    // setTeapotAttributeLocations() must be called first
    void teapot();

    //************************************************************************************************
    //************************************************************************************************

#define TEAPOT_NUMBER_PATCHES 28
#define TEAPOT_PATCH_DIMENSION 3
#define TEAPOT_RES_U 10
#define TEAPOT_RES_V 10

    inline GLuint teapot_vao;
    inline GLuint teapot_vbo, teapot_ibo;

    struct Teapot_Vertex { GLfloat x, y, z; };
    inline Teapot_Vertex teapot_cp_vertices[] = {
            // 1
            {  1.4f   ,   0.0f   ,  2.4f     },
            {  1.4f   ,  -0.784f ,  2.4f     },
            {  0.784f ,  -1.4f   ,  2.4f     },
            {  0.0f   ,  -1.4f   ,  2.4f     },
            {  1.3375f,   0.0f   ,  2.53125f },
            {  1.3375f,  -0.749f ,  2.53125f },
            {  0.749f ,  -1.3375f,  2.53125f },
            {  0.0f   ,  -1.3375f,  2.53125f },
            {  1.4375f,    0.0f  ,  2.53125f },
            {  1.4375f,  -0.805f ,  2.53125f },
            // 11
            {  0.805f ,  -1.4375f,  2.53125f },
            {  0.0f   ,  -1.4375f,  2.53125f },
            {  1.5f   ,   0.0f   ,  2.4f     },
            {  1.5f   ,  -0.84f  ,  2.4f     },
            {  0.84f  ,  -1.5f   ,  2.4f     },
            {  0.0f   ,  -1.5f   ,  2.4f     },
            { -0.784f ,  -1.4f   ,  2.4f     },
            { -1.4f   ,  -0.784f ,  2.4f     },
            { -1.4f   ,   0.0f   ,  2.4f     },
            { -0.749f ,  -1.3375f,  2.53125f },
            // 21
            { -1.3375f,  -0.749f ,  2.53125f },
            { -1.3375f,   0.0f   ,  2.53125f },
            { -0.805f ,  -1.4375f,  2.53125f },
            { -1.4375f,  -0.805f ,  2.53125f },
            { -1.4375f,   0.0f   ,  2.53125f },
            { -0.84f  ,  -1.5f   ,  2.4f     },
            { -1.5f   ,  -0.84f  ,  2.4f     },
            { -1.5f   ,   0.0f   ,  2.4f     },
            { -1.4f   ,   0.784f ,  2.4f     },
            { -0.784f ,   1.4f   ,  2.4f     },
            // 31
            {  0.0f   ,   1.4f   ,  2.4f     },
            { -1.3375f,   0.749f ,  2.53125f },
            { -0.749f ,   1.3375f,  2.53125f },
            {  0.0f   ,   1.3375f,  2.53125f },
            { -1.4375f,   0.805f ,  2.53125f },
            { -0.805f ,   1.4375f,  2.53125f },
            {  0.0f   ,   1.4375f,  2.53125f },
            { -1.5f   ,   0.84f  ,  2.4f     },
            { -0.84f  ,   1.5f   ,  2.4f     },
            {  0.0f   ,   1.5f   ,  2.4f     },
            // 41
            {  0.784f ,   1.4f   ,  2.4f     },
            {  1.4f   ,   0.784f ,  2.4f     },
            {  0.749f ,   1.3375f,  2.53125f },
            {  1.3375f,   0.749f ,  2.53125f },
            {  0.805f ,   1.4375f,  2.53125f },
            {  1.4375f,   0.805f ,  2.53125f },
            {  0.84f  ,   1.5f   ,  2.4f     },
            {  1.5f   ,   0.84f  ,  2.4f     },
            {  1.75f  ,   0.0f   ,  1.875f   },
            {  1.75f  ,  -0.98f  ,  1.875f   },
            // 51
            {  0.98f  ,  -1.75f  ,  1.875f   },
            {  0.0f   ,  -1.75f  ,  1.875f   },
            {  2.0f   ,   0.0f   ,  1.35f    },
            {  2.0f   ,  -1.12f  ,  1.35f    },
            {  1.12f  ,  -2.0f   ,  1.35f    },
            {  0.0f   ,  -2.0f   ,  1.35f    },
            {  2.0f   ,   0.0f   ,  0.9f     },
            {  2.0f   ,  -1.12f  ,  0.9f     },
            {  1.12f  ,  -2.0f   ,  0.9f     },
            {  0.0f   ,  -2.0f   ,  0.9f     },
            // 61
            { -0.98f  ,  -1.75f  ,  1.875f   },
            { -1.75f  ,  -0.98f  ,  1.875f   },
            { -1.75f  ,   0.0f   ,  1.875f   },
            { -1.12f  ,  -2.0f   ,  1.35f    },
            { -2.0f   ,  -1.12f  ,  1.35f    },
            { -2.0f   ,   0.0f   ,  1.35f    },
            { -1.12f  ,  -2.0f   ,  0.9f     },
            { -2.0f   ,  -1.12f  ,  0.9f     },
            { -2.0f   ,   0.0f   ,  0.9f     },
            { -1.75f  ,   0.98f  ,  1.875f   },
            // 71
            { -0.98f  ,   1.75f  ,  1.875f   },
            {  0.0f   ,   1.75f  ,  1.875f   },
            { -2.0f   ,   1.12f  ,  1.35f    },
            { -1.12f  ,   2.0f   ,  1.35f    },
            {  0.0f   ,   2.0f   ,  1.35f    },
            { -2.0f   ,   1.12f  ,  0.9f     },
            { -1.12f  ,   2.0f   ,  0.9f     },
            {  0.0f   ,   2.0f   ,  0.9f     },
            {  0.98f  ,   1.75f  ,  1.875f   },
            {  1.75f  ,   0.98f  ,  1.875f   },
            // 81
            {  1.12f  ,   2.0f   ,  1.35f    },
            {  2.0f   ,   1.12f  ,  1.35f    },
            {  1.12f  ,   2.0f   ,  0.9f     },
            {  2.0f   ,   1.12f  ,  0.9f     },
            {  2.0f   ,   0.0f   ,  0.45f    },
            {  2.0f   ,  -1.12f  ,  0.45f    },
            {  1.12f  ,  -2.0f   ,  0.45f    },
            {  0.0f   ,  -2.0f   ,  0.45f    },
            {  1.5f   ,   0.0f   ,  0.225f   },
            {  1.5f   ,  -0.84f  ,  0.225f   },
            // 91
            {  0.84f  ,  -1.5f   ,  0.225f   },
            {  0.0f   ,  -1.5f   ,  0.225f   },
            {  1.5f   ,   0.0f   ,  0.15f    },
            {  1.5f   ,  -0.84f  ,  0.15f    },
            {  0.84f  ,  -1.5f   ,  0.15f    },
            {  0.0f   ,  -1.5f   ,  0.15f    },
            { -1.12f  ,  -2.0f   ,  0.45f    },
            { -2.0f   ,  -1.12f  ,  0.45f    },
            { -2.0f   ,   0.0f   ,  0.45f    },
            { -0.84f  ,  -1.5f   ,  0.225f   },
            // 101
            { -1.5f   ,  -0.84f  ,  0.225f   },
            { -1.5f   ,   0.0f   ,  0.225f   },
            { -0.84f  ,  -1.5f   ,  0.15f    },
            { -1.5f   ,  -0.84f  ,  0.15f    },
            { -1.5f   ,   0.0f   ,  0.15f    },
            { -2.0f   ,   1.12f  ,  0.45f    },
            { -1.12f  ,   2.0f   ,  0.45f    },
            {  0.0f   ,   2.0f   ,  0.45f    },
            { -1.5f   ,   0.84f  ,  0.225f   },
            { -0.84f  ,   1.5f   ,  0.225f   },
            // 111
            {  0.0f   ,   1.5f   ,  0.225f   },
            { -1.5f   ,   0.84f  ,  0.15f    },
            { -0.84f  ,   1.5f   ,  0.15f    },
            {  0.0f   ,   1.5f   ,  0.15f    },
            {  1.12f  ,   2.0f   ,  0.45f    },
            {  2.0f   ,   1.12f  ,  0.45f    },
            {  0.84f  ,   1.5f   ,  0.225f   },
            {  1.5f   ,   0.84f  ,  0.225f   },
            {  0.84f  ,   1.5f   ,  0.15f    },
            {  1.5f   ,   0.84f  ,  0.15f    },
            // 121
            { -1.6f   ,   0.0f   ,  2.025f   },
            { -1.6f   ,  -0.3f   ,  2.025f   },
            { -1.5f   ,  -0.3f   ,  2.25f    },
            { -1.5f   ,   0.0f   ,  2.25f    },
            { -2.3f   ,   0.0f   ,  2.025f   },
            { -2.3f   ,  -0.3f   ,  2.025f   },
            { -2.5f   ,  -0.3f   ,  2.25f    },
            { -2.5f   ,   0.0f   ,  2.25f    },
            { -2.7f   ,   0.0f   ,  2.025f   },
            { -2.7f   ,  -0.3f   ,  2.025f   },
            // 131
            { -3.0f   ,  -0.3f   ,  2.25f    },
            { -3.0f   ,   0.0f   ,  2.25f    },
            { -2.7f   ,   0.0f   ,  1.8f     },
            { -2.7f   ,  -0.3f   ,  1.8f     },
            { -3.0f   ,  -0.3f   ,  1.8f     },
            { -3.0f   ,   0.0f   ,  1.8f     },
            { -1.5f   ,   0.3f   ,  2.25f    },
            { -1.6f   ,   0.3f   ,  2.025f   },
            { -2.5f   ,   0.3f   ,  2.25f    },
            { -2.3f   ,   0.3f   ,  2.025f   },
            // 141
            { -3.0f   ,   0.3f   ,  2.25f    },
            { -2.7f   ,   0.3f   ,  2.025f   },
            { -3.0f   ,   0.3f   ,  1.8f     },
            { -2.7f   ,   0.3f   ,  1.8f     },
            { -2.7f   ,   0.0f   ,  1.575f   },
            { -2.7f   ,  -0.3f   ,  1.575f   },
            { -3.0f   ,  -0.3f   ,  1.35f    },
            { -3.0f   ,   0.0f   ,  1.35f    },
            { -2.5f   ,   0.0f   ,  1.125f   },
            { -2.5f   ,  -0.3f   ,  1.125f   },
            // 151
            { -2.65f  ,  -0.3f   ,  0.9375f  },
            { -2.65f  ,   0.0f   ,  0.9375f  },
            { -2.0f   ,  -0.3f   ,  0.9f     },
            { -1.9f   ,  -0.3f   ,  0.6f     },
            { -1.9f   ,   0.0f   ,  0.6f     },
            { -3.0f   ,   0.3f   ,  1.35f    },
            { -2.7f   ,   0.3f   ,  1.575f   },
            { -2.65f  ,   0.3f   ,  0.9375f  },
            { -2.5f   ,   0.3f   ,  1.1255f  },
            { -1.9f   ,   0.3f   ,  0.6f     },
            // 161
            { -2.0f   ,   0.3f   ,  0.9f     },
            {  1.7f   ,   0.0f   ,  1.425f   },
            {  1.7f   ,  -0.66f  ,  1.425f   },
            {  1.7f   ,  -0.66f  ,  0.6f     },
            {  1.7f   ,   0.0f   ,  0.6f     },
            {  2.6f   ,   0.0f   ,  1.425f   },
            {  2.6f   ,  -0.66f  ,  1.425f   },
            {  3.1f   ,  -0.66f  ,  0.825f   },
            {  3.1f   ,   0.0f   ,  0.825f   },
            {  2.3f   ,   0.0f   ,  2.1f     },
            // 171
            {  2.3f   ,  -0.25f  ,  2.1f     },
            {  2.4f   ,  -0.25f  ,  2.025f   },
            {  2.4f   ,   0.0f   ,  2.025f   },
            {  2.7f   ,   0.0f   ,  2.4f     },
            {  2.7f   ,  -0.25f  ,  2.4f     },
            {  3.3f   ,  -0.25f  ,  2.4f     },
            {  3.3f   ,   0.0f   ,  2.4f     },
            {  1.7f   ,   0.66f  ,  0.6f     },
            {  1.7f   ,   0.66f  ,  1.425f   },
            {  3.1f   ,   0.66f  ,  0.825f   },
            // 181
            {  2.6f   ,   0.66f  ,  1.425f   },
            {  2.4f   ,   0.25f  ,  2.025f   },
            {  2.3f   ,   0.25f  ,  2.1f     },
            {  3.3f   ,   0.25f  ,  2.4f     },
            {  2.7f   ,   0.25f  ,  2.4f     },
            {  2.8f   ,   0.0f   ,  2.475f   },
            {  2.8f   ,  -0.25f  ,  2.475f   },
            {  3.525f ,  -0.25f  ,  2.49375f },
            {  3.525f ,   0.0f   ,  2.49375f },
            {  2.9f   ,   0.0f   ,  2.475f   },
            // 191
            {  2.9f   ,  -0.15f  ,  2.475f   },
            {  3.45f  ,  -0.15f  ,  2.5125f  },
            {  3.45f  ,   0.0f   ,  2.5125f  },
            {  2.8f   ,   0.0f   ,  2.4f     },
            {  2.8f   ,  -0.15f  ,  2.4f     },
            {  3.2f   ,  -0.15f  ,  2.4f     },
            {  3.2f   ,   0.0f   ,  2.4f     },
            {  3.525f ,   0.25f  ,  2.49375f },
            {  2.8f   ,   0.25f  ,  2.475f   },
            {  3.45f  ,   0.15f  ,  2.5125f  },
            // 201
            {  2.9f   ,   0.15f  ,  2.475f   },
            {  3.2f   ,   0.15f  ,  2.4f     },
            {  2.8f   ,   0.15f  ,  2.4f     },
            {  0.0f   ,   0.0f   ,  3.15f    },
            {  0.0f   ,  -0.002f ,  3.15f    },
            {  0.002f ,   0.0f   ,  3.15f    },
            {  0.8f   ,   0.0f   ,  3.15f    },
            {  0.8f   ,  -0.45f  ,  3.15f    },
            {  0.45f  ,  -0.8f   ,  3.15f    },
            {  0.0f   ,  -0.8f   ,  3.15f    },
            // 211
            {  0.0f   ,   0.0f   ,  2.85f    },
            {  0.2f   ,   0.0f   ,  2.7f     },
            {  0.2f   ,  -0.112f ,  2.7f     },
            {  0.112f ,  -0.2f   ,  2.7f     },
            {  0.0f   ,  -0.2f   ,  2.7f     },
            { -0.002f ,   0.0f   ,  3.15f    },
            { -0.45f  ,  -0.8f   ,  3.15f    },
            { -0.8f   ,  -0.45f  ,  3.15f    },
            { -0.8f   ,   0.0f   ,  3.15f    },
            { -0.112f ,  -0.2f   ,  2.7f     },
            // 221
            { -0.2f   ,  -0.112f ,  2.7f     },
            { -0.2f   ,   0.0f   ,  2.7f     },
            {  0.0f   ,   0.002f ,  3.15f    },
            { -0.8f   ,   0.45f  ,  3.15f    },
            { -0.45f  ,   0.8f   ,  3.15f    },
            {  0.0f   ,   0.8f   ,  3.15f    },
            { -0.2f   ,   0.112f ,  2.7f     },
            { -0.112f ,   0.2f   ,  2.7f     },
            {  0.0f   ,   0.2f   ,  2.7f     },
            {  0.45f  ,   0.8f   ,  3.15f    },
            // 231
            {  0.8f   ,   0.45f  ,  3.15f    },
            {  0.112f ,   0.2f   ,  2.7f     },
            {  0.2f   ,   0.112f ,  2.7f     },
            {  0.4f   ,   0.0f   ,  2.55f    },
            {  0.4f   ,  -0.224f ,  2.55f    },
            {  0.224f ,  -0.4f   ,  2.55f    },
            {  0.0f   ,  -0.4f   ,  2.55f    },
            {  1.3f   ,   0.0f   ,  2.55f    },
            {  1.3f   ,  -0.728f ,  2.55f    },
            {  0.728f ,  -1.3f   ,  2.55f    },
            // 241
            {  0.0f   ,  -1.3f   ,  2.55f    },
            {  1.3f   ,   0.0f   ,  2.4f     },
            {  1.3f   ,  -0.728f ,  2.4f     },
            {  0.728f ,  -1.3f   ,  2.4f     },
            {  0.0f   ,  -1.3f   ,  2.4f     },
            { -0.224f ,  -0.4f   ,  2.55f    },
            { -0.4f   ,  -0.224f ,  2.55f    },
            { -0.4f   ,   0.0f   ,  2.55f    },
            { -0.728f ,  -1.3f   ,  2.55f    },
            { -1.3f   ,  -0.728f ,  2.55f    },
            // 251
            { -1.3f   ,   0.0f   ,  2.55f    },
            { -0.728f ,  -1.3f   ,  2.4f     },
            { -1.3f   ,  -0.728f ,  2.4f     },
            { -1.3f   ,   0.0f   ,  2.4f     },
            { -0.4f   ,   0.224f ,  2.55f    },
            { -0.224f ,   0.4f   ,  2.55f    },
            {  0.0f   ,   0.4f   ,  2.55f    },
            { -1.3f   ,   0.728f ,  2.55f    },
            { -0.728f ,   1.3f   ,  2.55f    },
            {  0.0f   ,   1.3f   ,  2.55f    },
            // 261
            { -1.3f   ,   0.728f ,  2.4f     },
            { -0.728f ,   1.3f   ,  2.4f     },
            {  0.0f   ,   1.3f   ,  2.4f     },
            {  0.224f ,   0.4f   ,  2.55f    },
            {  0.4f   ,   0.224f ,  2.55f    },
            {  0.728f ,   1.3f   ,  2.55f    },
            {  1.3f   ,   0.728f ,  2.55f    },
            {  0.728f ,   1.3f   ,  2.4f     },
            {  1.3f   ,   0.728f ,  2.4f     },
    };

    inline GLushort teapot_patches[TEAPOT_NUMBER_PATCHES][TEAPOT_PATCH_DIMENSION + 1][TEAPOT_PATCH_DIMENSION + 1] = {
            // rim
            { {   1,   2,   3,   4 }, {   5,   6,   7,   8 }, {   9,  10,  11,  12 }, {  13,  14,  15,  16, } },
            { {   4,  17,  18,  19 }, {   8,  20,  21,  22 }, {  12,  23,  24,  25 }, {  16,  26,  27,  28, } },
            { {  19,  29,  30,  31 }, {  22,  32,  33,  34 }, {  25,  35,  36,  37 }, {  28,  38,  39,  40, } },
            { {  31,  41,  42,   1 }, {  34,  43,  44,   5 }, {  37,  45,  46,   9 }, {  40,  47,  48,  13, } },
            // body
            { {  13,  14,  15,  16 }, {  49,  50,  51,  52 }, {  53,  54,  55,  56 }, {  57,  58,  59,  60, } },
            { {  16,  26,  27,  28 }, {  52,  61,  62,  63 }, {  56,  64,  65,  66 }, {  60,  67,  68,  69, } },
            { {  28,  38,  39,  40 }, {  63,  70,  71,  72 }, {  66,  73,  74,  75 }, {  69,  76,  77,  78, } },
            { {  40,  47,  48,  13 }, {  72,  79,  80,  49 }, {  75,  81,  82,  53 }, {  78,  83,  84,  57, } },
            { {  57,  58,  59,  60 }, {  85,  86,  87,  88 }, {  89,  90,  91,  92 }, {  93,  94,  95,  96, } },
            { {  60,  67,  68,  69 }, {  88,  97,  98,  99 }, {  92, 100, 101, 102 }, {  96, 103, 104, 105, } },
            { {  69,  76,  77,  78 }, {  99, 106, 107, 108 }, { 102, 109, 110, 111 }, { 105, 112, 113, 114, } },
            { {  78,  83,  84,  57 }, { 108, 115, 116,  85 }, { 111, 117, 118,  89 }, { 114, 119, 120,  93, } },
            // handle
            { { 121, 122, 123, 124 }, { 125, 126, 127, 128 }, { 129, 130, 131, 132 }, { 133, 134, 135, 136, } },
            { { 124, 137, 138, 121 }, { 128, 139, 140, 125 }, { 132, 141, 142, 129 }, { 136, 143, 144, 133, } },
            { { 133, 134, 135, 136 }, { 145, 146, 147, 148 }, { 149, 150, 151, 152 }, {  69, 153, 154, 155, } },
            { { 136, 143, 144, 133 }, { 148, 156, 157, 145 }, { 152, 158, 159, 149 }, { 155, 160, 161,  69, } },
            // spout
            { { 162, 163, 164, 165 }, { 166, 167, 168, 169 }, { 170, 171, 172, 173 }, { 174, 175, 176, 177, } },
            { { 165, 178, 179, 162 }, { 169, 180, 181, 166 }, { 173, 182, 183, 170 }, { 177, 184, 185, 174, } },
            { { 174, 175, 176, 177 }, { 186, 187, 188, 189 }, { 190, 191, 192, 193 }, { 194, 195, 196, 197, } },
            { { 177, 184, 185, 174 }, { 189, 198, 199, 186 }, { 193, 200, 201, 190 }, { 197, 202, 203, 194, } },
            // lid
            { { 204, 204, 204, 204 }, { 207, 208, 209, 210 }, { 211, 211, 211, 211 }, { 212, 213, 214, 215, } },
            { { 204, 204, 204, 204 }, { 210, 217, 218, 219 }, { 211, 211, 211, 211 }, { 215, 220, 221, 222, } },
            { { 204, 204, 204, 204 }, { 219, 224, 225, 226 }, { 211, 211, 211, 211 }, { 222, 227, 228, 229, } },
            { { 204, 204, 204, 204 }, { 226, 230, 231, 207 }, { 211, 211, 211, 211 }, { 229, 232, 233, 212, } },
            { { 212, 213, 214, 215 }, { 234, 235, 236, 237 }, { 238, 239, 240, 241 }, { 242, 243, 244, 245, } },
            { { 215, 220, 221, 222 }, { 237, 246, 247, 248 }, { 241, 249, 250, 251 }, { 245, 252, 253, 254, } },
            { { 222, 227, 228, 229 }, { 248, 255, 256, 257 }, { 251, 258, 259, 260 }, { 254, 261, 262, 263, } },
            { { 229, 232, 233, 212 }, { 257, 264, 265, 234 }, { 260, 266, 267, 238 }, { 263, 268, 269, 242, } },
            // no bottom!
    };

    inline Teapot_Vertex teapot_vertices[TEAPOT_NUMBER_PATCHES * TEAPOT_RES_U * TEAPOT_RES_V * 3];
    inline GLushort teapot_elements[TEAPOT_NUMBER_PATCHES * (TEAPOT_RES_U - 1) * (TEAPOT_RES_V - 1) * 2 * 3];

    inline bool teapot_built = false;
    inline GLint teapot_pos_attr_loc = -1;
    inline GLint teapot_norm_attr_loc = -1;
    inline GLint teapot_tex_attr_loc = -1;

    void teapot_build_control_points_k(int p, Teapot_Vertex** control_points_k);
    Teapot_Vertex teapot_compute_position(Teapot_Vertex** control_points_k, GLfloat u, GLfloat v);
    Teapot_Vertex teapot_compute_normal(Teapot_Vertex** control_points_k, GLfloat u, GLfloat v);
    Teapot_Vertex teapot_compute_texture(Teapot_Vertex position);
    GLfloat teapot_bernstein_polynomial(int i, int n, GLfloat u);
    GLfloat teapot_binomial_coefficient(int i, int n);
    int teapot_factorial(int n);

    inline void teapot_build_teapot() {
        // Vertices
        for (int p = 0; p < TEAPOT_NUMBER_PATCHES; p++) {
            auto control_points_k = (Teapot_Vertex**)malloc(sizeof(Teapot_Vertex*) * (TEAPOT_PATCH_DIMENSION + 1));
            for(int i = 0; i < TEAPOT_PATCH_DIMENSION + 1; i++)
                control_points_k[i] = (Teapot_Vertex*)malloc(sizeof(Teapot_Vertex) * (TEAPOT_PATCH_DIMENSION + 1));

            teapot_build_control_points_k(p, control_points_k);

            for (int ru = 0; ru <= TEAPOT_RES_U - 1; ru++) {
                GLfloat u = 1.0f * (GLfloat) ru / (TEAPOT_RES_U - 1);
                for (int rv = 0; rv <= TEAPOT_RES_V - 1; rv++) {
                    GLfloat v = 1.0f * (GLfloat) rv / (TEAPOT_RES_V - 1);
                    teapot_vertices[                    p * TEAPOT_RES_U * TEAPOT_RES_V                                       + ru * TEAPOT_RES_V + rv ] = teapot_compute_position(control_points_k, u, v);
                    teapot_vertices[TEAPOT_NUMBER_PATCHES * TEAPOT_RES_U * TEAPOT_RES_V     + p * TEAPOT_RES_U * TEAPOT_RES_V + ru * TEAPOT_RES_V + rv ] = teapot_compute_normal(control_points_k, u, v);
                    teapot_vertices[TEAPOT_NUMBER_PATCHES * TEAPOT_RES_U * TEAPOT_RES_V * 2 + p * TEAPOT_RES_U * TEAPOT_RES_V + ru * TEAPOT_RES_V + rv ] = teapot_compute_texture(teapot_vertices[p * TEAPOT_RES_U * TEAPOT_RES_V + ru * TEAPOT_RES_V + rv]);
                }
            }
        }

        // Elements
        int n = 0;
        for (int p = 0; p < TEAPOT_NUMBER_PATCHES; p++)
            for (int ru = 0; ru < TEAPOT_RES_U - 1; ru++)
                for (int rv = 0; rv < TEAPOT_RES_V - 1; rv++) {
                    // 1 square ABCD = 2 triangles ABC + CDA
                    GLushort a = p * TEAPOT_RES_U * TEAPOT_RES_V + ru * TEAPOT_RES_V + rv      ;
                    GLushort b = p * TEAPOT_RES_U * TEAPOT_RES_V + ru * TEAPOT_RES_V + (rv + 1);
                    GLushort c = p * TEAPOT_RES_U * TEAPOT_RES_V + (ru + 1) * TEAPOT_RES_V + (rv + 1);
                    GLushort d = p * TEAPOT_RES_U * TEAPOT_RES_V + (ru + 1) * TEAPOT_RES_V + rv      ;
                    // ABC
                    teapot_elements[n++] = a;
                    teapot_elements[n++] = b;
                    teapot_elements[n++] = c;
                    // CDA
                    teapot_elements[n++] = c;
                    teapot_elements[n++] = d;
                    teapot_elements[n++] = a;
                }

    }

    inline void teapot_build_control_points_k(const int p, Teapot_Vertex** const control_points_k) {
        for (int i = 0; i <= TEAPOT_PATCH_DIMENSION; i++)
            for (int j = 0; j <= TEAPOT_PATCH_DIMENSION; j++)
                control_points_k[i][j] = teapot_cp_vertices[teapot_patches[p][i][j] - 1];
    }

    inline Teapot_Vertex teapot_compute_position(Teapot_Vertex** const control_points_k, const GLfloat u, const GLfloat v) {
        Teapot_Vertex position = {0.0f, 0.0f, 0.0f };
        for (int i = 0; i <= TEAPOT_PATCH_DIMENSION; i++) {
            GLfloat poly_i = teapot_bernstein_polynomial(i, TEAPOT_PATCH_DIMENSION, u);
            for (int j = 0; j <= TEAPOT_PATCH_DIMENSION; j++) {
                GLfloat poly_j = teapot_bernstein_polynomial(j, TEAPOT_PATCH_DIMENSION, v);
                position.x += poly_i * poly_j * control_points_k[i][j].x;
                position.y += poly_i * poly_j * control_points_k[i][j].y;
                position.z += poly_i * poly_j * control_points_k[i][j].z;
            }
        }
        return position;
    }

    // TODO compute normal based on partial derivatives of surface patch
    inline Teapot_Vertex teapot_compute_normal(Teapot_Vertex** const control_points_k, const GLfloat u, const GLfloat v) {
        Teapot_Vertex normal = {0.0f, 0.0f, 0.0f };
        for (int i = 0; i <= TEAPOT_PATCH_DIMENSION; i++) {
            GLfloat poly_i = teapot_bernstein_polynomial(i, TEAPOT_PATCH_DIMENSION, u);
            for (int j = 0; j <= TEAPOT_PATCH_DIMENSION; j++) {
                GLfloat poly_j = teapot_bernstein_polynomial(j, TEAPOT_PATCH_DIMENSION, v);
                normal.x += poly_i * poly_j * control_points_k[i][j].x;
                normal.y += poly_i * poly_j * control_points_k[i][j].y;
                normal.z += poly_i * poly_j * control_points_k[i][j].z;
            }
        }
        return normal;
    }

    inline Teapot_Vertex teapot_compute_texture(const Teapot_Vertex position) {
        Teapot_Vertex textureCoordinate = {0.0f, 0.0f, 0.0f};
        const GLfloat PI = 3.14159265f;
        GLfloat theta = atan2(position.y, position.x);
        textureCoordinate.x = (theta + PI) / (2.0f * PI);
        textureCoordinate.y = position.z / 3.15f;
        return textureCoordinate;
    }

    inline GLfloat teapot_bernstein_polynomial(const int i, const int n, const GLfloat u) {
        return teapot_binomial_coefficient(i, n) * powf(u, (GLfloat)i) * powf(1 - u, (GLfloat)(n - i));
    }

    inline GLfloat teapot_binomial_coefficient(const int i, const int n) {
        assert(i >= 0);
        assert(n >= 0);
        return 1.0f * (GLfloat) teapot_factorial(n) / (GLfloat)(teapot_factorial(i) * teapot_factorial(n - i));
    }
    inline int teapot_factorial(const int n) {
        assert(n >= 0);
        int result = 1;
        for (int i = n; i > 1; i--)
            result *= i;
        return result;
    }

    inline int teapot_init_resources() {
        teapot_build_teapot();

        glGenVertexArrays(1, &teapot_vao);
        glBindVertexArray(teapot_vao);

        glGenBuffers(1, &teapot_vbo);
        glBindBuffer(GL_ARRAY_BUFFER, teapot_vbo);
        glBufferData(GL_ARRAY_BUFFER, sizeof(teapot_vertices), teapot_vertices, GL_STATIC_DRAW);

        glGenBuffers(1, &teapot_ibo);
        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, teapot_ibo);
        glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(teapot_elements), teapot_elements, GL_STATIC_DRAW);

        teapot_built = true;

        return 1;
    }

    [[maybe_unused]]
    inline void teapot( const GLfloat size, const GLint positionLocation, const GLint normalLocation, const GLint texCoordLocation ) {
        if( !teapot_built ) {
            teapot_init_resources();
        }
        if( positionLocation != teapot_pos_attr_loc || normalLocation != teapot_norm_attr_loc || texCoordLocation != teapot_tex_attr_loc ) {
            setTeapotAttributeLocations(positionLocation, normalLocation, texCoordLocation);
        }
        teapot();
    }

    inline void setTeapotAttributeLocations(const GLint positionLocation, const GLint normalLocation, const GLint texCoordLocation) {
        if( !teapot_built ) {
            teapot_init_resources();
        }

        glBindVertexArray(teapot_vao );
        glBindBuffer(GL_ARRAY_BUFFER, teapot_vbo);

        if(teapot_pos_attr_loc != -1)  glDisableVertexAttribArray(teapot_pos_attr_loc);
        if(teapot_norm_attr_loc != -1) glDisableVertexAttribArray(teapot_norm_attr_loc);
        if(teapot_tex_attr_loc != -1)  glDisableVertexAttribArray(teapot_tex_attr_loc);

        teapot_pos_attr_loc = positionLocation;
        teapot_norm_attr_loc = normalLocation;
        teapot_tex_attr_loc = texCoordLocation;

        // Describe our vertices array to OpenGL (it can't guess its format automatically)
        if(teapot_pos_attr_loc != -1) {
            glEnableVertexAttribArray(teapot_pos_attr_loc);
            glVertexAttribPointer(
                    teapot_pos_attr_loc,  // attribute
                    3,                 // number of elements per vertex, here (x,y,z)
                    GL_FLOAT,          // the type of each element
                    GL_FALSE,          // take our values as-is
                    0,                 // no extra data between each position
                    nullptr            // offset of first element
            );
        }
        if(teapot_norm_attr_loc != -1) {
            glEnableVertexAttribArray(teapot_norm_attr_loc);
            glVertexAttribPointer(
                    teapot_norm_attr_loc,  // attribute
                    3,                 // number of elements per vertex, here (x,y,z)
                    GL_FLOAT,          // the type of each element
                    GL_FALSE,          // take our values as-is
                    0,                 // no extra data between each position
                    (void*)(TEAPOT_NUMBER_PATCHES * TEAPOT_RES_U * TEAPOT_RES_V * sizeof(Teapot_Vertex))                  // offset of first element
            );
        }
        if(teapot_tex_attr_loc != -1) {
            glEnableVertexAttribArray(teapot_tex_attr_loc);
            glVertexAttribPointer(
                    teapot_tex_attr_loc,  // attribute
                    2,                 // number of elements per vertex, here (s,t)
                    GL_FLOAT,          // the type of each element
                    GL_FALSE,          // take our values as-is
                    sizeof(Teapot_Vertex),                 // no extra data between each position
                    (void*)(TEAPOT_NUMBER_PATCHES * TEAPOT_RES_U * TEAPOT_RES_V * 2 * sizeof(Teapot_Vertex))                  // offset of first element
            );
        }
    }

    inline void teapot() {
        glBindVertexArray(teapot_vao );
        glBindBuffer(GL_ARRAY_BUFFER, teapot_vbo);
        glDrawElements(GL_TRIANGLES, sizeof(teapot_elements)/sizeof(teapot_elements[0]), GL_UNSIGNED_SHORT, nullptr);
    }
}


#endif // CSCI441_TEAPOT_HPP
