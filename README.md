This library is intended to be used with OpenGL for CSCI441 at the Colorado
School of Mines.

When building, the library must be compiled and linked against OpenGL, GLEW, and glm.  

Copyright (c) 2021 Dr. Jeffrey Paone

Permission is hereby granted, free of charge, to any person obtaining a copy
of this software and associated documentation files (the "Software"), to deal
in the Software without restriction, including without limitation the rights
to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
copies of the Software, and to permit persons to whom the Software is
furnished to do so, subject to the following conditions:

The above copyright notice and this permission notice shall be included in all
copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
SOFTWARE.

TODO Items
  > Handle vertex and face colors in OFF files

Revision History

v 3.1.0 - 21 May 2021
  > Removed all ShaderProgram::setUniform().  Use ShaderProgram::setProgramUniform() instead.

v 3.0.0 - 21 May 2021
  > Reworked ModelLoader.hpp to first set attribute locations then specify the shader handle.  This allows for the model to be used with separable programs and shader pipelines.

  > Renamed modelLoader.hpp to ModelLoader.hpp to reflect it stores a class

  > Created abstract OpenGLEngine and abstract OpenGL3DEngine classes to provide framework for a class engine style framework.

  > ShaderProgram class caches attribute locations for quicker repeated lookups instead of doing program introspection each time.

  > Added ability to load a texture to a cube map face via TextureUtils

  > ShaderProgram::setProgramUniform() now supports glm::ivec and glm::uvec

  > Marked functions as deprecated that will be removed in v4

  > Cleaned up console output for ShaderPrograms

  > Various fixes to ShaderProgramPipelines

v 2.10.0 - 23 Feb 2021
  > Added wrapper class for ComputeShaderProgram

  > Added support to ShaderProgram to return Shader Storage Buffer Block bindings

  > Added support to ShaderProgram to return Atomic Counter bindings

  > Updated ShaderProgram info output to include SSBO and ABO info

v 2.8.1 - 28 Jan 2021
  > Added wrappers to ShaderProgram to set a uniform by name or location

v 2.8.0 - 28 Jan 2021
  > Created Shader Program Pipeline class to wrap Pipeline Objects.  Interfaces with the ShaderProgram class.

v 2.7.2 - 10 Dec 2020
  > Added getters to vertex data for ModelLoader class

v 2.7.0 - 13 Nov 2020
  > Added texture coordinates to Teapot

v 2.6.0 - 27 Oct 2020
  > Added predefined Material properties for reuse

v 2.3.0 - 12 Oct 2020
  > Allow multicompilation for objects.hpp with shaders.  Now depends upon C++17

v 2.2.0 - 12 Oct 2020
  > Allow multicompilation for ShaderProgram.hpp.  Now depends upon C++17

v 2.1.0 - 02 Oct 2020
  > Fixed memory leak in objects.hpp cylinder, sphere, disk, torus caching\n

  > Added method for objects.hpp to delete the used VAOs/VBOs from GPU memory\n

  > Delete compiled shaders from GPU after Shader Program is linked to free up memory sooner

v.2.0.2 - 25 Sep 2020
  > Removed invalid enum error when querying max number of lights in OpenGL 3+

v2.0.0  - 25 Sep 2020
  > Only single version of library files to work with OpenGL 4.1\n

  > Removed dependency upon SOIL and replaced with stb_image\n

  > Fixed bug of spheres not being spheres due to precision error

v1.8.3	- 04 Dec 2017
  > Marked modelLoader3.hpp function implementations as inline to prevent redefinition errors

v1.8	- 16 Nov 2017
  > Added support for MTL files for Phong Shading and diffuse maps

v1.7	- 16 Nov 2017
  > Added loadBMP() support to TextureUtils.hpp\n

  > Added support for ASCII STL files to modelLoader3.hpp\n

  > Added support for OFF files to modelLoader3.hpp\n

  > Fixed reallocation error if model did not load properly\n

  > Added support for ASCII PLY files to modelLoader3.hpp (as long as first three vertex properties are x/y/z location)\n

  > If PLY file does not contain normal information (we're currently not checking for it), can autogenerate vertex normals\n

  > If OFF file does not contain normal information, can autogenerate vertex normals\n

  > If OBJ file does not contain normal information, can autogenerate vertex normals

v1.6	- 15 Nov 2017
  > Added FramebufferUtils3.hpp to print Framebuffer info\n

  > Fixed off by 1 error for normals/texcoords in modelLoader3.hpp\n

  > Fixed overflow error for modelLoader3.hpp when reading in models with more than 65535 vertices

v1.5.1	- 10 Nov 2017
  > Fixed redefinition errors in teapot3.hpp and objects3.hpp\n

  > Fixed bug in ShaderUtils3.hpp to check if OpenGL is version 4.0+ before querying subroutine uniforms

v1.5	- 06 Nov 2017
  > Added loadTGA method to TextureUtils.hpp\n

  > Commenting added to TextureUtils.hpp\n

  > Converted OpenGLUtils from static non-implementable class to namespace\n

  > Added commenting to ShaderProgram3.hpp

v1.4.1	- 05 Nov 2017
  > Fixed bug in objects3.hpp of internally passing torus parameters in incorrect order

v1.4	- 03 Nov 2017
  > Created ShaderUtils3.hpp and ShaderProgram3.hpp to make working with Shaders easier

v.1.3.1	- 28 Oct 2017
  > Matched internal data types to prevent c++11 narrowing warnings on lab machines

v1.3 	- 26 Oct 2017
  > Modified texture coordinates for cylinder to linear step from 0 to 1 in s instead of following cosine\n

  > Modified texture coordinates for sphere to linear step form 0 to 1 in s & t instead of following sine and cosine\n

  > Fixed bug when disk was not being displayed if consisting of 1 ring\n

  > Fixed bug with Partial Disk not starting at current angle\n

  > Fixed bug with normals on Sphere stacks\n

  > Added modelLoader3.hpp to handle loading and drawing OBJ files\n

  > Added objects3.hpp that allow for solid primitives to be drawn with OpenGL 3.0\n

  > Notes for teapot - the teapot cannot be textured and it is a pure teapot with no bottom\n

  > For a textured teapot, look into using an object model

v1.2	- 25 Sep 2017
  > Fixed error in draw*Disk not completing final slice step\n

  > Added TextureUtils to load in a PPM\n

  > Added MaterialStruct structure to group together Phong properties\n

  > Fixed error in drawSolidDisk() not allowing inner radius to be zero

v1.1.1	- 22 Sep 2017
  > Removed GL_MAX_COLOR_ATTACHMENTS to comply with lab machines

v1.1    - 21 Sep 2017
  > Added OpenGLUtils class to store commonly used helper functions

v1.0.1  - 19 Sep 2017
  > Added documentation\n

  > Added inline definition to functions to prevent duplicate linking errors

v1.0    - 01 Sep 2017
  > Initial release of all OpenGL 3D objects
