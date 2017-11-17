#ifndef __CSCI441_MODELMATERIAL_H__
#define __CSCI441_MODELMATERIAL_H__

namespace CSCI441_INTERNAL {

  struct ModelMaterial {
      GLfloat ambient[4];
      GLfloat diffuse[4];
      GLfloat specular[4];
      GLfloat shininess;
      GLfloat emissive[4];

      GLuint map_Kd;

      ModelMaterial() {
        for( int i = 0; i < 3; i++ ) {
          ambient[i] = 0;
          diffuse[i] = 0;
          specular[i] = 0;
          emissive[i] = 0;
        }
        ambient[3] = 1;
        diffuse[3] = 1;
        specular[3] = 1;
        emissive[3] = 1;
        shininess = 0;
        map_Kd = 0;
      }
  };

  enum MODEL_TYPE {OBJ, OFF, PLY, STL};
}

#endif
