/** @file CSCI441.hpp
 * @brief Includes all CSCI 441 class helper files
 * @author Dr. Jeffrey Paone
 *
 * @copyright MIT License Copyright (c) 2017 Dr. Jeffrey Paone
 *
 *	These functions, classes, and constants help minimize common
 *	code that needs to be written.
 *
 *	@warning NOTE: This header file depends upon glm
 *	@warning NOTE: This header file depends upon GLEW
 */

#ifndef CSCI441_CSCI441_H
#define CSCI441_CSCI441_H

#include "ComputeShaderProgram.hpp" // helper class to compile and use compute shaders
#include "FramebufferUtils.hpp"     // to query common FBO information
#include "materials.hpp"            // predefined material properties
#include "modelLoader.hpp"          // to load OBJ, OFF, PLY, STL files
#include "OpenGLUtils.hpp"          // to query OpenGL features
#include "objects.hpp"              // include 3D objects (cube, cylinder, cone, torus, sphere, disk, teapot)
#include "ShaderProgram.hpp"        // helper class to compile and use shaders
#include "ShaderProgramPipeline.hpp"// helper class to compile and use shader program pipelines
#include "TextureUtils.hpp"         // helper functions for registering textures

#endif //CSCI441_CSCI441_H
