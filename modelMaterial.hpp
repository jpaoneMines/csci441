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

#include <GL/glew.h>

namespace CSCI441_INTERNAL {

  struct ModelMaterial {
      GLfloat ambient[4];
      GLfloat diffuse[4];
      GLfloat specular[4];
      GLfloat shininess;
      [[maybe_unused]] GLfloat emissive[4];

      GLint map_Kd;
      [[maybe_unused]] GLint map_d;

      ModelMaterial() {
        for( int i = 0; i < 3; i++ ) {
          ambient[i] = 0.0f;
          diffuse[i] = 0.0f;
          specular[i] = 0.0f;
          emissive[i] = 0.0f;
        }
        ambient[3] = 1.0f;
        diffuse[3] = 1.0f;
        specular[3] = 1.0f;
        emissive[3] = 1.0f;
        shininess = 0.0f;
        map_Kd = 0;
        map_d = 0;
      }
  };

  enum MODEL_TYPE {OBJ, OFF, PLY, STL};
}

#endif // CSCI441_MODEL_MATERIAL_H
