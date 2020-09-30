/** @file CSCI441.hpp
 * @brief Includes all CSCI 441 class helper files
 * @author Dr. Jeffrey Paone
 * @date Last Edit: 08 Jun 2020
 * @version 2.0
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

#include "FramebufferUtils.hpp"     // to query common FBO information
#include "modelLoader.hpp"          // to load OBJ, OFF, PLY, STL files
#include "OpenGLUtils.hpp"          // to query OpenGL features
#include "objects.hpp"              // include 3D objects (cube, cylinder, cone, torus, sphere, disk, teapot)
#include "ShaderProgram.hpp"        // helper class to compile and use shaders
#include "TextureUtils.hpp"         // helper functions for registering textures

#endif //CSCI441_CSCI441_H
