# CSCI 441 Computer Graphics OpenGL Library

[CSCI441 OpenGL Library GitHub Repo](https://github.com/jpaoneMines/csci441)

[CSCI441 Library Documentation](https://jpaonemines.github.io/csci441/)

This library is intended to be used with OpenGL for CSCI441 at the Colorado
School of Mines but can be used with any OpenGL application.

## When building your application: 

### This library must be compiled against: 
- [OpenGL v3.3+](https://www.opengl.org/) (Features up through OpenGL 4.3 are supported, but library is backwards compatible with earlier versions)
- [GLFW v3.4](https://www.glfw.org/)
- [glad2](https://github.com/Dav1dde/glad)
- [glm v1.0.1](https://github.com/g-truc/glm)
- [stb_image](https://github.com/nothings/stb)

The corresponding header files are included with this distribution for proper compilation.

### This library must be linked against: 
- [OpenGL v3.3+](https://www.opengl.org/)
- [GLFW v3.4](https://www.glfw.org/)
- [glad2](https://github.com/Dav1dde/glad)

The OpenGL, GLFW, and glad libraries must be previously built and installed on your machine.  Proper linking is left to the user to ensure success.

## Example Programs:
To build, run 

`make examples`

then run one of the following programs:
- `./bin/hudcamera`: user can select which of the CSCI441 3D Objects to display using SimpleShader3 for diffuse illumination and OpenGL3DEngine for an Arcball camera.  The currently selected object shape is displayed in the lower corner via a Heads-Up Display Camera
- `./bin/simpleobjects3`: user can select which of the CSCI441 3D Objects to display using SimpleShader3 for diffuse illumination and OpenGL3DEngine for an Arcball camera
- `./bin/simpletri2`: displays a rotating triforce on the screen using SimpleShader2 and OpenGLEngine