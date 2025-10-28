/**
 * @file modelMaterial.hpp
 * @brief Internal material representation for *.mtl files
 * @author Dr. Jeffrey Paone
 *
 * @copyright MIT License Copyright (c) 2021 Dr. Jeffrey Paone
 *
 *	These functions, classes, and constants help minimize common
 *	code that needs to be written.
 */

#ifndef CSCI441_MODEL_MATERIAL_H
#define CSCI441_MODEL_MATERIAL_H

#include "constants.h"

#ifdef CSCI441_USE_GLEW
    #include <GL/glew.h>
#else
    #include <glad/gl.h>
#endif

#include <glm/ext/vector_float4.hpp>

namespace CSCI441_INTERNAL {

  struct ModelMaterial {
      glm::vec4 ambient;
      glm::vec4 diffuse;
      glm::vec4 specular;
      GLfloat shininess;
      [[maybe_unused]] glm::vec4 emissive;

      GLuint map_Kd;
      [[maybe_unused]] GLuint map_d;

      ModelMaterial() :
        shininess(0.0f),
        map_Kd(0),
        map_d(0) {
          for(size_t i = 0; i < 3; i++) {
              ambient[i] = diffuse[i] = specular[i] = emissive[i] = 0.0f;
          }
          ambient[3] = diffuse[3] = specular[3] = emissive[3] = 1.0f;
      }
  };

  enum class MODEL_TYPE {OBJ, OFF, PLY, STL, UNKNOWN};
}

#endif // CSCI441_MODEL_MATERIAL_H
