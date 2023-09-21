# CSCI 441 Computer Graphics OpenGL Library

[CSCI441 OpenGL Library GitHub Repo](https://github.com/jpaoneMines/csci441)

This library is intended to be used with OpenGL for CSCI441 at the Colorado
School of Mines but can be used with any OpenGL application.

When building your application, this library must be compiled and linked against: 
- [OpenGL v3.3+](https://www.opengl.org/) (Features up through OpenGL 4.3 are supported, but library is backwards compatible with earlier versions)
- [GLFW v3.3.8](https://www.glfw.org/)
- [GLEW v2.1.0](https://glew.sourceforge.net/)
- [glm v0.9.9](https://glm.g-truc.net/0.9.9/)

The OpenGL, GLFW, and GLEW libraries must be previously built and installed on your machine.  The corresponding header files are included with this distribution for proper compilation, but proper linking is left to the user to ensure success.

## Example Programs:
To build, run 

`make examples`

then run one of the following programs:
- `./bin/simpleobjects3`: user can select which of the CSCI441 3D Objects to display using SimpleShader3 for diffuse illumination and OpenGL3DEngine for an Arcball camera
- `./bin/simpletri2`: displays a rotating triforce on the screen using SimpleShader2 and OpenGLEngine