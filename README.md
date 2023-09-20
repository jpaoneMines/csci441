[CSCI441 OpenGL Library GitHub Repo](https://github.com/jpaoneMines/csci441)

This library is intended to be used with OpenGL for CSCI441/444/544 at the Colorado
School of Mines.

When building, the library must be compiled and linked against: 
- OpenGL
- GLFW
- GLEW
- glm

# Revision History

## v 4.9.1 - 20 Sep 2023
- Fixed doxygen version number

## v 4.9.0 - 20 Sep 2023
- Fixed aspect ratio calculation in OpenGL3DEngine
- Fixed MD5Model destruction if error loading model
- Removed internal references to glUniform*() and replaced with glProgramUniform*() to not change bound program state
- Cleaned up documentation

## v 4.8.0 - 14 Sep 2023
- OpenGL3DEngine can handle events that have an effect on the arcball camera movement

## v 4.7.0 - 07 Sep 2023
- Big3 implemented on classes as appropriate
- Classes and methods open/close as appropriate

## v 4.6.1 - 06 Sep 2023
- Cannot copy MD5 Models

## v 4.6.0 - 06 Sep 2023
- Created MD5Model class to load, display, and animate md5mesh + md5anim files
- Deleted copy constructor and copy assignment operator for ShaderProgram and ComputeShaderProgram to prevent shader program objects from being copied and then deallocated on the GPU
- TextureUtils::loadAndRegisterTexture() now has a trailing parameter to specify if the image should be flipped when loaded or not (defaults to flip = true)

## v 4.5.0 - 31 Aug 2023
- Camera stores projection matrix along with view matrix
  - ArcballCam, FixedCam, FreeCam operate with perspective projections
- MD5Camera class loads and steps through frames of md5camera file 
  - MD5Camera operates with perspective projection

## v 4.4.0 - 29 Aug 2023
- ShaderProgram::getProgramStages() returns GLbitfield of shader stages

## v 4.3.0 - 25 Aug 2023
- Improved and consistent web documentation using a consistent style for all public facing classes and members, methods, and namespaces
- Minor performance improvements

## v 4.2.0 - 25 Aug 2023
- setupGLEW() and cleanupGLEW() made private members of OpenGLEngine
- Improving web documentation using a consistent style

## v 4.1.1 - 24 Aug 2023
- Cleaned up order of includes
- Fixed publishing to GitHub pages

## v 4.1.0 - 24 Aug 2023
- Improving web documentation using a consistent style

## v 4.0.0 - 21 Aug 2023
- Refactored protected class member naming scheme from _xyz to mXyz
- Improving web documentation

## v 3.12.1 - 18 Aug 2023
- Improving web documentation

## v 3.12.0 - 18 Aug 2023
- Consistently use only single precision and GLfloat typedef for OS X Metal compatibility

## v 3.11.0 - 20 Apr 2023
- Fixed renaming bug in ModelLoader _AUTO_GEN_NORMALS and properly initialize to false
- Removed memory leaks in object generation of cylinder, disk, sphere, and torus

## v 3.10.2 - 26 Oct 2022
- Cleaned up Camera class warnings 
- Replaced OpenGL3DEngine internal arcball implementation with ArcballCam object

## v 3.10.1 - 09 Sep 2022
- Camera::_clampCameraPhi() explicitly checking against floats instead of double

## v 3.10.0 - 06 Aug 2022
- Added capability for ShaderProgram to write to/load from binary - if supported by driver
- ModelLoader no longer internal applies using namespace std; and qualifies all STL types

## v 3.9.0 - 05 Nov 2021
- ModelLoader can query number of vertices and indices within model
- TextureUtils load method will roll back to ppm loader if stb_image fails to load ppm
- Reversed top fan winding order for spheres 

## v 3.8.0 - 07 Oct 2021
- Resolved Issue #2 for OBJ files with negative indices.  The negative indices weren't unique and needed to offset before caching

## v 3.7.1 - 07 Oct 2021
- Fixed get polygon mode bug where it returns two values
- Objects and Teapot only enable attribute locations if they are not -1.  Prevents an invalid enum error 

## v 3.7.0 - 06 Oct 2021
- Improved encapsulation of Arcball radius modification
- Drawing objects now resets glPolygonMode to previous value instead of just forcing GL_FILL 
- When deleting a Shader Program, check the deletion status 
- Adding 3D texture coordinates to indexed cube and adding entry point to explicitly drawCubeMap()
- Corrected normals for indexed cube  
- Changed object and teapot internal variables from static to inline to support multi-compilation and single use across multiple contexts

## v 3.6.0 - 15 Sep 2021
- Created a concrete ArcBall Cam implementation

## v 3.5.0 - 13 Sep 2021
- Added full getter suite to Camera class

## v 3.4.1 - 10 Sep 2021
- Fixed bug within SimpleShader when the SimpleShader was used split across multiple class objects

## v 3.4.0 - 08 Sep 2021
- Created a concrete Fixed Camera implementation that can be positioned but doesn't move
- Fixed FreeCam being included across multiple object files 

## v 3.3.0 - 06 Sep 2021
- Created an abstract Camera class to store parameters and to make camera objects
- Created a concrete FreeCam implementation 

## v 3.2.1 - 31 Aug 2021
- Reworked SimpleShader::popTransformation() to always re-multiply the model matrix and not use the inverse calculation to avoid precision errors

## v 3.2.0 - 30 Aug 2021
- Cleaning up code style
- Removed deprecated functions in ShaderUtils
- Removed printLog() in ShaderUtils forcing explicit use of printShaderLog(), printProgramLog(), printProgramPipelineLog()
- Removed loadBMP() and loadTGA() in TextureUtils.  Use stb_image library instead
- Improved efficiency of setting VBO attribute locations for teapot 
- Sidestepped the precision error in SimpleShader2 (and therefore SimpleShader3) when popping and multiplying by the inverse by adding a resetTransformationMatrix() method which clears the stack and sets the model matrix to the identity 

## v 3.1.0 - 21 May 2021
- Removed all ShaderProgram::setUniform().  Use ShaderProgram::setProgramUniform() instead.

## v 3.0.0 - 21 May 2021
- Reworked ModelLoader.hpp to first set attribute locations then specify the shader handle.  This allows for the model to be used with separable programs and shader pipelines.
- Renamed modelLoader.hpp to ModelLoader.hpp to reflect it stores a class
- Created abstract OpenGLEngine and abstract OpenGL3DEngine classes to provide framework for a class engine style framework.
- ShaderProgram class caches attribute locations for quicker repeated lookups instead of doing program introspection each time.
- Added ability to load a texture to a cube map face via TextureUtils
- ShaderProgram::setProgramUniform() now supports glm::ivec and glm::uvec
- Marked functions as deprecated that will be removed in v4
- Cleaned up console output for ShaderPrograms
- Various fixes to ShaderProgramPipelines

## v 2.10.0 - 23 Feb 2021
- Added wrapper class for ComputeShaderProgram
- Added support to ShaderProgram to return Shader Storage Buffer Block bindings
- Added support to ShaderProgram to return Atomic Counter bindings
- Updated ShaderProgram info output to include SSBO and ABO info

## v 2.8.1 - 28 Jan 2021
- Added wrappers to ShaderProgram to set a uniform by name or location

## v 2.8.0 - 28 Jan 2021
- Created Shader Program Pipeline class to wrap Pipeline Objects.  Interfaces with the ShaderProgram class.

## v 2.7.2 - 10 Dec 2020
- Added getters to vertex data for ModelLoader class

## v 2.7.0 - 13 Nov 2020
- Added texture coordinates to Teapot

## v 2.6.0 - 27 Oct 2020
- Added predefined Material properties for reuse

## v 2.3.0 - 12 Oct 2020
- Allow multi-compilation for objects.hpp with shaders.  Now depends upon C++17

## v 2.2.0 - 12 Oct 2020
- Allow multi-compilation for ShaderProgram.hpp.  Now depends upon C++17

## v 2.1.0 - 02 Oct 2020
- Fixed memory leak in objects.hpp cylinder, sphere, disk, torus caching
- Added method for objects.hpp to delete the used VAOs/VBOs from GPU memory
- Delete compiled shaders from GPU after Shader Program is linked to free up memory sooner

## v.2.0.2 - 25 Sep 2020
- Removed invalid enum error when querying max number of lights in OpenGL 3+

## v2.0.0  - 25 Sep 2020
- Only single version of library files to work with OpenGL 4.1
- Removed dependency upon SOIL and replaced with stb_image
- Fixed bug of spheres not being spheres due to precision error

## v1.8.3	- 04 Dec 2017
- Marked modelLoader3.hpp function implementations as inline to prevent redefinition errors

## v1.8	- 16 Nov 2017
- Added support for MTL files for Phong Shading and diffuse maps

## v1.7	- 16 Nov 2017
- Added loadBMP() support to TextureUtils.hpp
- Added support for ASCII STL files to modelLoader3.hpp
- Added support for OFF files to modelLoader3.hpp
- Fixed reallocation error if model did not load properly
- Added support for ASCII PLY files to modelLoader3.hpp (as long as first three vertex properties are x/y/z location)
- If PLY file does not contain normal information (we're currently not checking for it), can autogenerate vertex normals
- If OFF file does not contain normal information, can autogenerate vertex normals
- If OBJ file does not contain normal information, can autogenerate vertex normals

## v1.6	- 15 Nov 2017
- Added FramebufferUtils3.hpp to print Framebuffer info
- Fixed off by 1 error for normals/texcoords in modelLoader3.hpp
- Fixed overflow error for modelLoader3.hpp when reading in models with more than 65535 vertices

## v1.5.1	- 10 Nov 2017
- Fixed redefinition errors in teapot3.hpp and objects3.hpp
- Fixed bug in ShaderUtils3.hpp to check if OpenGL is version 4.0+ before querying subroutine uniforms

## v1.5	- 06 Nov 2017
- Added loadTGA method to TextureUtils.hpp
- Commenting added to TextureUtils.hpp
- Converted OpenGLUtils from static non-implementable class to namespace
- Added commenting to ShaderProgram3.hpp

## v1.4.1	- 05 Nov 2017
- Fixed bug in objects3.hpp of internally passing torus parameters in incorrect order

## v1.4	- 03 Nov 2017
- Created ShaderUtils3.hpp and ShaderProgram3.hpp to make working with Shaders easier

## v.1.3.1	- 28 Oct 2017
- Matched internal data types to prevent c++11 narrowing warnings on lab machines

## v1.3 	- 26 Oct 2017
- Modified texture coordinates for cylinder to linear step from 0 to 1 in s instead of following cosine
- Modified texture coordinates for sphere to linear step form 0 to 1 in s & t instead of following sine and cosine
- Fixed bug when disk was not being displayed if consisting of 1 ring
- Fixed bug with Partial Disk not starting at current angle
- Fixed bug with normals on Sphere stacks
- Added modelLoader3.hpp to handle loading and drawing OBJ files
- Added objects3.hpp that allow for solid primitives to be drawn with OpenGL 3.0
- Notes for teapot - the teapot cannot be textured, and it is a pure teapot with no bottom
- For a textured teapot, look into using an object model

## v1.2	- 25 Sep 2017
- Fixed error in draw*Disk not completing final slice step
- Added TextureUtils to load in a PPM
- Added MaterialStruct structure to group together Phong properties
- Fixed error in drawSolidDisk() not allowing inner radius to be zero

## v1.1.1	- 22 Sep 2017
- Removed GL_MAX_COLOR_ATTACHMENTS to comply with lab machines

## v1.1    - 21 Sep 2017
- Added OpenGLUtils class to store commonly used helper functions

## v1.0.1  - 19 Sep 2017
- Added documentation
- Added inline definition to functions to prevent duplicate linking errors

## v1.0    - 01 Sep 2017
- Initial release of all OpenGL 3D objects
