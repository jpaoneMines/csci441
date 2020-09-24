/** @file teapot.hpp
 * @brief Helper functions to draw teapot with OpenGL 3.0+
 * @date Last Edit: 24 Sep 2020
 * @warning NOTE: This header file will only work with OpenGL 3.0+
 */
// Modified by Dr. Jeffrey Paone to work in Colorado School of Mines CSCI441
// course context.

#ifndef __CSCI441_TEAPOT_HPP__
#define __CSCI441_TEAPOT_HPP__

/*
 * From the OpenGL Programming wikibook: http://en.wikibooks.org/wiki/OpenGL_Programming
 * This file is in the public domain.
 * https://gitlab.com/wikibooks-opengl/modern-tutorials/blob/master/bezier_teapot/teapot.cpp
 * Contributors: Sylvain Beucler
 */
#include <stdio.h>
#include <stdlib.h>
#include <math.h>

/* Use glew.h instead of gl.h to get all the GL prototypes declared */
#include <GL/glew.h>

namespace CSCI441_INTERNAL {

    static GLuint vao_teapot;
    static GLuint vbo_teapot_vertices, ibo_teapot_elements;

    struct vertex { GLfloat x, y, z; };
    static struct vertex teapot_cp_vertices[] = {
            // 1
            {  1.4   ,   0.0   ,  2.4     },
            {  1.4   ,  -0.784 ,  2.4     },
            {  0.784 ,  -1.4   ,  2.4     },
            {  0.0   ,  -1.4   ,  2.4     },
            {  1.3375,   0.0   ,  2.53125 },
            {  1.3375,  -0.749 ,  2.53125 },
            {  0.749 ,  -1.3375,  2.53125 },
            {  0.0   ,  -1.3375,  2.53125 },
            {  1.4375,    0.0  ,  2.53125 },
            {  1.4375,  -0.805 ,  2.53125 },
            // 11
            {  0.805 ,  -1.4375,  2.53125 },
            {  0.0   ,  -1.4375,  2.53125 },
            {  1.5   ,   0.0   ,  2.4     },
            {  1.5   ,  -0.84  ,  2.4     },
            {  0.84  ,  -1.5   ,  2.4     },
            {  0.0   ,  -1.5   ,  2.4     },
            { -0.784 ,  -1.4   ,  2.4     },
            { -1.4   ,  -0.784 ,  2.4     },
            { -1.4   ,   0.0   ,  2.4     },
            { -0.749 ,  -1.3375,  2.53125 },
            // 21
            { -1.3375,  -0.749 ,  2.53125 },
            { -1.3375,   0.0   ,  2.53125 },
            { -0.805 ,  -1.4375,  2.53125 },
            { -1.4375,  -0.805 ,  2.53125 },
            { -1.4375,   0.0   ,  2.53125 },
            { -0.84  ,  -1.5   ,  2.4     },
            { -1.5   ,  -0.84  ,  2.4     },
            { -1.5   ,   0.0   ,  2.4     },
            { -1.4   ,   0.784 ,  2.4     },
            { -0.784 ,   1.4   ,  2.4     },
            // 31
            {  0.0   ,   1.4   ,  2.4     },
            { -1.3375,   0.749 ,  2.53125 },
            { -0.749 ,   1.3375,  2.53125 },
            {  0.0   ,   1.3375,  2.53125 },
            { -1.4375,   0.805 ,  2.53125 },
            { -0.805 ,   1.4375,  2.53125 },
            {  0.0   ,   1.4375,  2.53125 },
            { -1.5   ,   0.84  ,  2.4     },
            { -0.84  ,   1.5   ,  2.4     },
            {  0.0   ,   1.5   ,  2.4     },
            // 41
            {  0.784 ,   1.4   ,  2.4     },
            {  1.4   ,   0.784 ,  2.4     },
            {  0.749 ,   1.3375,  2.53125 },
            {  1.3375,   0.749 ,  2.53125 },
            {  0.805 ,   1.4375,  2.53125 },
            {  1.4375,   0.805 ,  2.53125 },
            {  0.84  ,   1.5   ,  2.4     },
            {  1.5   ,   0.84  ,  2.4     },
            {  1.75  ,   0.0   ,  1.875   },
            {  1.75  ,  -0.98  ,  1.875   },
            // 51
            {  0.98  ,  -1.75  ,  1.875   },
            {  0.0   ,  -1.75  ,  1.875   },
            {  2.0   ,   0.0   ,  1.35    },
            {  2.0   ,  -1.12  ,  1.35    },
            {  1.12  ,  -2.0   ,  1.35    },
            {  0.0   ,  -2.0   ,  1.35    },
            {  2.0   ,   0.0   ,  0.9     },
            {  2.0   ,  -1.12  ,  0.9     },
            {  1.12  ,  -2.0   ,  0.9     },
            {  0.0   ,  -2.0   ,  0.9     },
            // 61
            { -0.98  ,  -1.75  ,  1.875   },
            { -1.75  ,  -0.98  ,  1.875   },
            { -1.75  ,   0.0   ,  1.875   },
            { -1.12  ,  -2.0   ,  1.35    },
            { -2.0   ,  -1.12  ,  1.35    },
            { -2.0   ,   0.0   ,  1.35    },
            { -1.12  ,  -2.0   ,  0.9     },
            { -2.0   ,  -1.12  ,  0.9     },
            { -2.0   ,   0.0   ,  0.9     },
            { -1.75  ,   0.98  ,  1.875   },
            // 71
            { -0.98  ,   1.75  ,  1.875   },
            {  0.0   ,   1.75  ,  1.875   },
            { -2.0   ,   1.12  ,  1.35    },
            { -1.12  ,   2.0   ,  1.35    },
            {  0.0   ,   2.0   ,  1.35    },
            { -2.0   ,   1.12  ,  0.9     },
            { -1.12  ,   2.0   ,  0.9     },
            {  0.0   ,   2.0   ,  0.9     },
            {  0.98  ,   1.75  ,  1.875   },
            {  1.75  ,   0.98  ,  1.875   },
            // 81
            {  1.12  ,   2.0   ,  1.35    },
            {  2.0   ,   1.12  ,  1.35    },
            {  1.12  ,   2.0   ,  0.9     },
            {  2.0   ,   1.12  ,  0.9     },
            {  2.0   ,   0.0   ,  0.45    },
            {  2.0   ,  -1.12  ,  0.45    },
            {  1.12  ,  -2.0   ,  0.45    },
            {  0.0   ,  -2.0   ,  0.45    },
            {  1.5   ,   0.0   ,  0.225   },
            {  1.5   ,  -0.84  ,  0.225   },
            // 91
            {  0.84  ,  -1.5   ,  0.225   },
            {  0.0   ,  -1.5   ,  0.225   },
            {  1.5   ,   0.0   ,  0.15    },
            {  1.5   ,  -0.84  ,  0.15    },
            {  0.84  ,  -1.5   ,  0.15    },
            {  0.0   ,  -1.5   ,  0.15    },
            { -1.12  ,  -2.0   ,  0.45    },
            { -2.0   ,  -1.12  ,  0.45    },
            { -2.0   ,   0.0   ,  0.45    },
            { -0.84  ,  -1.5   ,  0.225   },
            // 101
            { -1.5   ,  -0.84  ,  0.225   },
            { -1.5   ,   0.0   ,  0.225   },
            { -0.84  ,  -1.5   ,  0.15    },
            { -1.5   ,  -0.84  ,  0.15    },
            { -1.5   ,   0.0   ,  0.15    },
            { -2.0   ,   1.12  ,  0.45    },
            { -1.12  ,   2.0   ,  0.45    },
            {  0.0   ,   2.0   ,  0.45    },
            { -1.5   ,   0.84  ,  0.225   },
            { -0.84  ,   1.5   ,  0.225   },
            // 111
            {  0.0   ,   1.5   ,  0.225   },
            { -1.5   ,   0.84  ,  0.15    },
            { -0.84  ,   1.5   ,  0.15    },
            {  0.0   ,   1.5   ,  0.15    },
            {  1.12  ,   2.0   ,  0.45    },
            {  2.0   ,   1.12  ,  0.45    },
            {  0.84  ,   1.5   ,  0.225   },
            {  1.5   ,   0.84  ,  0.225   },
            {  0.84  ,   1.5   ,  0.15    },
            {  1.5   ,   0.84  ,  0.15    },
            // 121
            { -1.6   ,   0.0   ,  2.025   },
            { -1.6   ,  -0.3   ,  2.025   },
            { -1.5   ,  -0.3   ,  2.25    },
            { -1.5   ,   0.0   ,  2.25    },
            { -2.3   ,   0.0   ,  2.025   },
            { -2.3   ,  -0.3   ,  2.025   },
            { -2.5   ,  -0.3   ,  2.25    },
            { -2.5   ,   0.0   ,  2.25    },
            { -2.7   ,   0.0   ,  2.025   },
            { -2.7   ,  -0.3   ,  2.025   },
            // 131
            { -3.0   ,  -0.3   ,  2.25    },
            { -3.0   ,   0.0   ,  2.25    },
            { -2.7   ,   0.0   ,  1.8     },
            { -2.7   ,  -0.3   ,  1.8     },
            { -3.0   ,  -0.3   ,  1.8     },
            { -3.0   ,   0.0   ,  1.8     },
            { -1.5   ,   0.3   ,  2.25    },
            { -1.6   ,   0.3   ,  2.025   },
            { -2.5   ,   0.3   ,  2.25    },
            { -2.3   ,   0.3   ,  2.025   },
            // 141
            { -3.0   ,   0.3   ,  2.25    },
            { -2.7   ,   0.3   ,  2.025   },
            { -3.0   ,   0.3   ,  1.8     },
            { -2.7   ,   0.3   ,  1.8     },
            { -2.7   ,   0.0   ,  1.575   },
            { -2.7   ,  -0.3   ,  1.575   },
            { -3.0   ,  -0.3   ,  1.35    },
            { -3.0   ,   0.0   ,  1.35    },
            { -2.5   ,   0.0   ,  1.125   },
            { -2.5   ,  -0.3   ,  1.125   },
            // 151
            { -2.65  ,  -0.3   ,  0.9375  },
            { -2.65  ,   0.0   ,  0.9375  },
            { -2.0   ,  -0.3   ,  0.9     },
            { -1.9   ,  -0.3   ,  0.6     },
            { -1.9   ,   0.0   ,  0.6     },
            { -3.0   ,   0.3   ,  1.35    },
            { -2.7   ,   0.3   ,  1.575   },
            { -2.65  ,   0.3   ,  0.9375  },
            { -2.5   ,   0.3   ,  1.1255  },
            { -1.9   ,   0.3   ,  0.6     },
            // 161
            { -2.0   ,   0.3   ,  0.9     },
            {  1.7   ,   0.0   ,  1.425   },
            {  1.7   ,  -0.66  ,  1.425   },
            {  1.7   ,  -0.66  ,  0.6     },
            {  1.7   ,   0.0   ,  0.6     },
            {  2.6   ,   0.0   ,  1.425   },
            {  2.6   ,  -0.66  ,  1.425   },
            {  3.1   ,  -0.66  ,  0.825   },
            {  3.1   ,   0.0   ,  0.825   },
            {  2.3   ,   0.0   ,  2.1     },
            // 171
            {  2.3   ,  -0.25  ,  2.1     },
            {  2.4   ,  -0.25  ,  2.025   },
            {  2.4   ,   0.0   ,  2.025   },
            {  2.7   ,   0.0   ,  2.4     },
            {  2.7   ,  -0.25  ,  2.4     },
            {  3.3   ,  -0.25  ,  2.4     },
            {  3.3   ,   0.0   ,  2.4     },
            {  1.7   ,   0.66  ,  0.6     },
            {  1.7   ,   0.66  ,  1.425   },
            {  3.1   ,   0.66  ,  0.825   },
            // 181
            {  2.6   ,   0.66  ,  1.425   },
            {  2.4   ,   0.25  ,  2.025   },
            {  2.3   ,   0.25  ,  2.1     },
            {  3.3   ,   0.25  ,  2.4     },
            {  2.7   ,   0.25  ,  2.4     },
            {  2.8   ,   0.0   ,  2.475   },
            {  2.8   ,  -0.25  ,  2.475   },
            {  3.525 ,  -0.25  ,  2.49375 },
            {  3.525 ,   0.0   ,  2.49375 },
            {  2.9   ,   0.0   ,  2.475   },
            // 191
            {  2.9   ,  -0.15  ,  2.475   },
            {  3.45  ,  -0.15  ,  2.5125  },
            {  3.45  ,   0.0   ,  2.5125  },
            {  2.8   ,   0.0   ,  2.4     },
            {  2.8   ,  -0.15  ,  2.4     },
            {  3.2   ,  -0.15  ,  2.4     },
            {  3.2   ,   0.0   ,  2.4     },
            {  3.525 ,   0.25  ,  2.49375 },
            {  2.8   ,   0.25  ,  2.475   },
            {  3.45  ,   0.15  ,  2.5125  },
            // 201
            {  2.9   ,   0.15  ,  2.475   },
            {  3.2   ,   0.15  ,  2.4     },
            {  2.8   ,   0.15  ,  2.4     },
            {  0.0   ,   0.0   ,  3.15    },
            {  0.0   ,  -0.002 ,  3.15    },
            {  0.002 ,   0.0   ,  3.15    },
            {  0.8   ,   0.0   ,  3.15    },
            {  0.8   ,  -0.45  ,  3.15    },
            {  0.45  ,  -0.8   ,  3.15    },
            {  0.0   ,  -0.8   ,  3.15    },
            // 211
            {  0.0   ,   0.0   ,  2.85    },
            {  0.2   ,   0.0   ,  2.7     },
            {  0.2   ,  -0.112 ,  2.7     },
            {  0.112 ,  -0.2   ,  2.7     },
            {  0.0   ,  -0.2   ,  2.7     },
            { -0.002 ,   0.0   ,  3.15    },
            { -0.45  ,  -0.8   ,  3.15    },
            { -0.8   ,  -0.45  ,  3.15    },
            { -0.8   ,   0.0   ,  3.15    },
            { -0.112 ,  -0.2   ,  2.7     },
            // 221
            { -0.2   ,  -0.112 ,  2.7     },
            { -0.2   ,   0.0   ,  2.7     },
            {  0.0   ,   0.002 ,  3.15    },
            { -0.8   ,   0.45  ,  3.15    },
            { -0.45  ,   0.8   ,  3.15    },
            {  0.0   ,   0.8   ,  3.15    },
            { -0.2   ,   0.112 ,  2.7     },
            { -0.112 ,   0.2   ,  2.7     },
            {  0.0   ,   0.2   ,  2.7     },
            {  0.45  ,   0.8   ,  3.15    },
            // 231
            {  0.8   ,   0.45  ,  3.15    },
            {  0.112 ,   0.2   ,  2.7     },
            {  0.2   ,   0.112 ,  2.7     },
            {  0.4   ,   0.0   ,  2.55    },
            {  0.4   ,  -0.224 ,  2.55    },
            {  0.224 ,  -0.4   ,  2.55    },
            {  0.0   ,  -0.4   ,  2.55    },
            {  1.3   ,   0.0   ,  2.55    },
            {  1.3   ,  -0.728 ,  2.55    },
            {  0.728 ,  -1.3   ,  2.55    },
            // 241
            {  0.0   ,  -1.3   ,  2.55    },
            {  1.3   ,   0.0   ,  2.4     },
            {  1.3   ,  -0.728 ,  2.4     },
            {  0.728 ,  -1.3   ,  2.4     },
            {  0.0   ,  -1.3   ,  2.4     },
            { -0.224 ,  -0.4   ,  2.55    },
            { -0.4   ,  -0.224 ,  2.55    },
            { -0.4   ,   0.0   ,  2.55    },
            { -0.728 ,  -1.3   ,  2.55    },
            { -1.3   ,  -0.728 ,  2.55    },
            // 251
            { -1.3   ,   0.0   ,  2.55    },
            { -0.728 ,  -1.3   ,  2.4     },
            { -1.3   ,  -0.728 ,  2.4     },
            { -1.3   ,   0.0   ,  2.4     },
            { -0.4   ,   0.224 ,  2.55    },
            { -0.224 ,   0.4   ,  2.55    },
            {  0.0   ,   0.4   ,  2.55    },
            { -1.3   ,   0.728 ,  2.55    },
            { -0.728 ,   1.3   ,  2.55    },
            {  0.0   ,   1.3   ,  2.55    },
            // 261
            { -1.3   ,   0.728 ,  2.4     },
            { -0.728 ,   1.3   ,  2.4     },
            {  0.0   ,   1.3   ,  2.4     },
            {  0.224 ,   0.4   ,  2.55    },
            {  0.4   ,   0.224 ,  2.55    },
            {  0.728 ,   1.3   ,  2.55    },
            {  1.3   ,   0.728 ,  2.55    },
            {  0.728 ,   1.3   ,  2.4     },
            {  1.3   ,   0.728 ,  2.4     },
    };
#define TEAPOT_NB_PATCHES 28
#define ORDER 3
    static GLushort teapot_patches[TEAPOT_NB_PATCHES][ORDER+1][ORDER+1] = {
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
#define RESU 10
#define RESV 10
    static struct vertex teapot_vertices[TEAPOT_NB_PATCHES * RESU*RESV*2];
    static GLushort teapot_elements[TEAPOT_NB_PATCHES * (RESU-1)*(RESV-1) * 2*3];

    static bool teapotBuilt = false;

    void build_control_points_k(int p, struct vertex control_points_k[][ORDER+1]);
    struct vertex compute_position(struct vertex control_points_k[][ORDER+1], float u, float v);
    struct vertex compute_normal(struct vertex control_points_k[][ORDER+1], float u, float v);
    float bernstein_polynomial(int i, int n, float u);
    float binomial_coefficient(int i, int n);
    int factorial(int n);

    inline void build_teapot() {
        // Vertices
        for (int p = 0; p < TEAPOT_NB_PATCHES; p++) {
            struct vertex control_points_k[ORDER+1][ORDER+1];
            build_control_points_k(p, control_points_k);
            for (int ru = 0; ru <= RESU-1; ru++) {
                float u = 1.0 * ru / (RESU-1);
                for (int rv = 0; rv <= RESV-1; rv++) {
                    float v = 1.0 * rv / (RESV-1);
                    teapot_vertices[p*RESU*RESV + ru*RESV + rv] = compute_position(control_points_k, u, v);
                    teapot_vertices[TEAPOT_NB_PATCHES * RESU*RESV + p*RESU*RESV + ru*RESV + rv] = compute_normal(control_points_k, u, v);
                }
            }
        }

        // Elements
        int n = 0;
        for (int p = 0; p < TEAPOT_NB_PATCHES; p++)
            for (int ru = 0; ru < RESU-1; ru++)
                for (int rv = 0; rv < RESV-1; rv++) {
                    // 1 square ABCD = 2 triangles ABC + CDA
                    // ABC
                    teapot_elements[n] = p*RESU*RESV +  ru   *RESV +  rv   ; n++;
                    teapot_elements[n] = p*RESU*RESV +  ru   *RESV + (rv+1); n++;
                    teapot_elements[n] = p*RESU*RESV + (ru+1)*RESV + (rv+1); n++;
                    // CDA
                    teapot_elements[n] = p*RESU*RESV + (ru+1)*RESV + (rv+1); n++;
                    teapot_elements[n] = p*RESU*RESV + (ru+1)*RESV +  rv   ; n++;
                    teapot_elements[n] = p*RESU*RESV +  ru   *RESV +  rv   ; n++;
                }

    }

    inline void build_control_points_k(int p, struct vertex control_points_k[][ORDER+1]) {
        for (int i = 0; i <= ORDER; i++)
            for (int j = 0; j <= ORDER; j++)
                control_points_k[i][j] = teapot_cp_vertices[teapot_patches[p][i][j] - 1];
    }

    inline struct vertex compute_position(struct vertex control_points_k[][ORDER+1], float u, float v) {
        struct vertex result = { 0.0, 0.0, 0.0 };
        for (int i = 0; i <= ORDER; i++) {
            float poly_i = bernstein_polynomial(i, ORDER, u);
            for (int j = 0; j <= ORDER; j++) {
                float poly_j = bernstein_polynomial(j, ORDER, v);
                result.x += poly_i * poly_j * control_points_k[i][j].x;
                result.y += poly_i * poly_j * control_points_k[i][j].y;
                result.z += poly_i * poly_j * control_points_k[i][j].z;
            }
        }
        return result;
    }

    // TODO compute normal based on partial derivatives of surface patch
    inline struct vertex compute_normal(struct vertex control_points_k[][ORDER+1], float u, float v) {
        struct vertex result = { 0.0, 0.0, 0.0 };
        for (int i = 0; i <= ORDER; i++) {
            float poly_i = bernstein_polynomial(i, ORDER, u);
            for (int j = 0; j <= ORDER; j++) {
                float poly_j = bernstein_polynomial(j, ORDER, v);
                result.x += poly_i * poly_j * control_points_k[i][j].x;
                result.y += poly_i * poly_j * control_points_k[i][j].y;
                result.z += poly_i * poly_j * control_points_k[i][j].z;
            }
        }
        return result;
    }

    inline float bernstein_polynomial(int i, int n, float u) {
        return binomial_coefficient(i, n) * powf(u, i) * powf(1-u, n-i);
    }

    inline float binomial_coefficient(int i, int n) {
        assert(i >= 0); assert(n >= 0);
        return 1.0f * factorial(n) / (factorial(i) * factorial(n-i));
    }
    inline int factorial(int n) {
        assert(n >= 0);
        int result = 1;
        for (int i = n; i > 1; i--)
            result *= i;
        return result;
    }

    inline int init_resources() {
        build_teapot();

        glGenVertexArrays(1, &vao_teapot);
        glBindVertexArray(vao_teapot);

        glGenBuffers(1, &vbo_teapot_vertices);
        glBindBuffer(GL_ARRAY_BUFFER, vbo_teapot_vertices);
        glBufferData(GL_ARRAY_BUFFER, sizeof(teapot_vertices), teapot_vertices, GL_STATIC_DRAW);

        glGenBuffers(1, &ibo_teapot_elements);
        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ibo_teapot_elements);
        glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(teapot_elements), teapot_elements, GL_STATIC_DRAW);

        teapotBuilt = true;

        return 1;
    }

    inline void teapot( GLfloat size, GLint positionLocation, GLint normalLocation ) {
        if( !teapotBuilt ) {
            init_resources();
        }

        glBindVertexArray( vao_teapot );
        // Describe our vertices array to OpenGL (it can't guess its format automatically)
        glBindBuffer(GL_ARRAY_BUFFER, vbo_teapot_vertices);
        glEnableVertexAttribArray(positionLocation);
        glVertexAttribPointer(
                positionLocation,  // attribute
                3,                 // number of elements per vertex, here (x,y,z)
                GL_FLOAT,          // the type of each element
                GL_FALSE,          // take our values as-is
                0,                 // no extra data between each position
                0                  // offset of first element
        );
        glEnableVertexAttribArray(normalLocation);
        glVertexAttribPointer(
                normalLocation,  // attribute
                3,                 // number of elements per vertex, here (x,y,z)
                GL_FLOAT,          // the type of each element
                GL_FALSE,          // take our values as-is
                0,                 // no extra data between each position
                (void*)(TEAPOT_NB_PATCHES * RESU*RESV)                  // offset of first element
        );

        glDrawElements(GL_TRIANGLES, sizeof(teapot_elements)/sizeof(teapot_elements[0]), GL_UNSIGNED_SHORT, 0);
    }
}


#endif // __CSCI441_TEAPOT_3_HPP__
