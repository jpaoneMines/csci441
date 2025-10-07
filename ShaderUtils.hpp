/**
 * @file ShaderUtils.hpp
 * @brief Helper functions to work with OpenGL Shaders
 * @author Dr. Jeffrey Paone
 *
 * @copyright MIT License Copyright (c) 2017 Dr. Jeffrey Paone
 *
 * These functions, classes, and constants help minimize common
 * code that needs to be written.
 *
 * @warning NOTE: This header file depends upon GLAD (or alternatively GLEW)
 */

#ifndef CSCI441_SHADER_UTILS_HPP
#define CSCI441_SHADER_UTILS_HPP

#include "constants.h"

#ifdef CSCI441_USE_GLEW
    #include <GL/glew.h>
#else
    #include <glad/gl.h>
#endif

#include <cstdio>
#include <cstring>
#include <fstream>
#include <string>

//********************************************************************************************************************

namespace CSCI441_INTERNAL::ShaderUtils {
    static bool sDEBUG = true;

    // Enables console output
    [[maybe_unused]] void enableDebugMessages();

    // Disables console output
    [[maybe_unused]] void disableDebugMessages();

    // Converts a GLenum data type variable to the string name of the associated value
    // GLenum data type
    // const char* name of data type
    const char* GLSL_type_to_string( GLenum type );

    // Converts a GLenum shader type variable to the string name of the associated value
    // GLenum shader type
    // const char* name of shader type
    const char* GL_shader_type_to_string( GLenum type );

    // Converts a GLenum primitive type variable to the string name of the associated value
    // GLenum primitive type
    // const char* name of primitive type
    const char* GL_primitive_type_to_string( GLenum type );

    // Reads the contents of a text file to a character array
    // const char* filename of shader file to read in
    // char*& character array to store the contents of the file.  Will allocate memory and populate within the function
    // bool true if file was successfully opened and read.  false otherwise
    bool readTextFromFile( const char* filename, GLchar* &output );

    // Reads the contents of a text file and compiles the associated shader type
    // const char* filename of shader file to read in
    // GLenum type of shader file corresponds to
    // GLuint shader handle if compilation successful.  -1 otherwise
    GLuint compileShader( const char *filename, GLenum shaderType );

    // Prints the shader log for the associated Shader handle
    void printShaderLog( GLuint shaderHandle );

    // Prints the shader log for the associated Shader Program handle after linking
    void printProgramLog( GLuint programHandle );

	// Prints the shader log for the associated Shader Program handle
	void printProgramInfoLog( GLuint programHandle );

    // Prints the shader log for the associated Program Pipeline handle
    void printProgramPipelineLog( GLuint pipelineHandle );

    // Prints subroutine information from a Shader program
    // GLuint Shader Program handle to inspect
    // GLenum Shader Stage to inspect
    // GLboolean if opening output line should be printed to console
    GLboolean printSubroutineInfo(GLuint programHandle, GLenum shaderStage, GLboolean printHeader );

    // Uses Shader Program introspection to print contents of Shader Program
    // GLuint Shader Program handle to inspect
    // GLboolean if Shader Program contains a vertex shader
    // GLboolean if Shader Program contains a tessellation control shader
    // GLboolean if Shader Program contains a tessellation evaluation shader
    // GLboolean if Shader Program contains a geometry shader
    // GLboolean if Shader Program contains a fragment shader
    // GLboolean if Shader Program contains a compute shader
    // GLboolean if closing output line should be printed to console (defaults to true)
    void printShaderProgramInfo( GLuint programHandle,
                                 GLboolean hasVertexShader,
                                 GLboolean hasTessControlShader, GLboolean hasTessEvalShader,
                                 GLboolean hasGeometryShader,
                                 GLboolean hasFragmentShader,
                                 GLboolean hasComputeShader,
                                 GLboolean useLastNewLine );
}

//********************************************************************************************************************

[[maybe_unused]]
inline void CSCI441_INTERNAL::ShaderUtils::enableDebugMessages() {
	sDEBUG = true;
}

[[maybe_unused]]
inline void CSCI441_INTERNAL::ShaderUtils::disableDebugMessages() {
	sDEBUG = false;
}

//********************************************************************************************************************

inline bool CSCI441_INTERNAL::ShaderUtils::readTextFromFile(
        const char *filename,
        GLchar* &output
){
    std::string buf = std::string("");
    std::string line;

    std::ifstream in(filename);
    if( !in.is_open() ) {
    	fprintf( stderr, "[ERROR]: Could not open file %s\n", filename );
    	return false;
    }
    while( std::getline(in, line) ) {
        buf += line + "\n";
    }
	
	output = new GLchar[buf.length()+1];
	strncpy(output, buf.c_str(), buf.length());
	output[buf.length()] = '\0';
	
    in.close();
	
	return true;
}

inline const char* CSCI441_INTERNAL::ShaderUtils::GLSL_type_to_string(
        const GLenum type
) {
    switch(type) {
        case GL_FLOAT:                                      return "float";
        case GL_FLOAT_VEC2:                                 return "vec2";
        case GL_FLOAT_VEC3:                                 return "vec3";
        case GL_FLOAT_VEC4:                                 return "vec4";
        case GL_DOUBLE:                                     return "double";
        case GL_DOUBLE_VEC2:                                return "dvec2";
        case GL_DOUBLE_VEC3:                                return "dvec3";
        case GL_DOUBLE_VEC4:                                return "dvec4";
        case GL_INT:                                        return "int";
        case GL_INT_VEC2:                                   return "ivec2";
        case GL_INT_VEC3:                                   return "ivec3";
        case GL_INT_VEC4:                                   return "ivec4";
        case GL_UNSIGNED_INT:                               return "unsigned int";
        case GL_UNSIGNED_INT_VEC2:                          return "uvec2";
        case GL_UNSIGNED_INT_VEC3:                          return "uvec3";
        case GL_UNSIGNED_INT_VEC4:                          return "uvec4";
        case GL_BOOL:                                       return "bool";
        case GL_BOOL_VEC2:                                  return "bvec2";
        case GL_BOOL_VEC3:                                  return "bvec3";
        case GL_BOOL_VEC4:                                  return "bvec4";
        case GL_FLOAT_MAT2:                                 return "mat2";
        case GL_FLOAT_MAT3:                                 return "mat3";
        case GL_FLOAT_MAT4:                                 return "mat4";
        case GL_FLOAT_MAT2x3:                               return "mat2x3";
        case GL_FLOAT_MAT2x4:                           	return "mat2x4";
        case GL_FLOAT_MAT3x2:                               return "mat3x2";
        case GL_FLOAT_MAT3x4:                               return "mat3x4";
        case GL_FLOAT_MAT4x2:                               return "mat4x2";
        case GL_FLOAT_MAT4x3:                       		return "mat4x3";
        case GL_DOUBLE_MAT2:                            	return "dmat2";
        case GL_DOUBLE_MAT3:                            	return "dmat3";
        case GL_DOUBLE_MAT4:                           		return "dmat4";
        case GL_DOUBLE_MAT2x3:                              return "dmat2x3";
        case GL_DOUBLE_MAT2x4:                              return "dmat2x4";
        case GL_DOUBLE_MAT3x2:                              return "dmat3x2";
        case GL_DOUBLE_MAT3x4:                              return "dmat3x4";
        case GL_DOUBLE_MAT4x2:                              return "dmat4x2";
        case GL_DOUBLE_MAT4x3:                              return "dmat4x3";
        case GL_SAMPLER_1D:                                 return "sampler1D";
        case GL_SAMPLER_2D:                                 return "sampler2D";
        case GL_SAMPLER_3D:                                 return "sampler3D";
        case GL_SAMPLER_CUBE:                               return "samplerCube";
        case GL_SAMPLER_1D_SHADOW:                          return "sampler1DShadow";
        case GL_SAMPLER_2D_SHADOW:                          return "sampler2DShadow";
        case GL_SAMPLER_1D_ARRAY:                           return "sampler1DArray";
        case GL_SAMPLER_2D_ARRAY:                           return "sampler2DArray";
        case GL_SAMPLER_2D_MULTISAMPLE:                     return "sampler2DMS";
        case GL_SAMPLER_2D_MULTISAMPLE_ARRAY:               return "sampler2DMSArray";
        case GL_SAMPLER_CUBE_SHADOW:                        return "samplerCubeShadow";
        case GL_SAMPLER_BUFFER:                             return "samplerBuffer";
        case GL_SAMPLER_2D_RECT:                            return "sampler2DRect";
        case GL_SAMPLER_2D_RECT_SHADOW:                     return "sampler2DRectShadow";
        case GL_INT_SAMPLER_1D:                             return "isampler1D";
        case GL_INT_SAMPLER_2D:                             return "isampler2D";
        case GL_INT_SAMPLER_3D:                             return "isampler3D";
        case GL_INT_SAMPLER_CUBE:                           return "isamplerCube";
        case GL_INT_SAMPLER_1D_ARRAY:                       return "isampler1DArray";
        case GL_INT_SAMPLER_2D_ARRAY:                       return "isampler2DArray";
        case GL_INT_SAMPLER_2D_MULTISAMPLE:                 return "isampler2DMS";
        case GL_INT_SAMPLER_2D_MULTISAMPLE_ARRAY:           return "isampler2DMSArray";
        case GL_INT_SAMPLER_BUFFER:                         return "isamplerBuffer";
        case GL_INT_SAMPLER_2D_RECT:                        return "isampler2DRect";
        case GL_UNSIGNED_INT_SAMPLER_1D:                    return "usampler1D";
        case GL_UNSIGNED_INT_SAMPLER_2D:                    return "usampler2D";
        case GL_UNSIGNED_INT_SAMPLER_3D:                    return "usampler3D";
        case GL_UNSIGNED_INT_SAMPLER_CUBE:                  return "usamplerCube";
        case GL_UNSIGNED_INT_SAMPLER_1D_ARRAY:              return "usampler1DArray";
        case GL_UNSIGNED_INT_SAMPLER_2D_ARRAY:              return "usampler2DArray";
        case GL_UNSIGNED_INT_SAMPLER_2D_MULTISAMPLE:        return "usampler2DMS";
        case GL_UNSIGNED_INT_SAMPLER_2D_MULTISAMPLE_ARRAY:  return "usampler2DMSArray";
        case GL_UNSIGNED_INT_SAMPLER_BUFFER:                return "usamplerBuffer";
        case GL_UNSIGNED_INT_SAMPLER_2D_RECT:               return "usampler2DRect";
        case GL_IMAGE_1D:                                   return "image1D";
        case GL_IMAGE_2D:                                   return "image2D";
        case GL_IMAGE_3D:                                   return "image3D";
        case GL_IMAGE_2D_RECT:                              return "image2DRect";
        case GL_IMAGE_CUBE:                                 return "imageCube";
        case GL_IMAGE_BUFFER:                               return "imageBuffer";
        case GL_IMAGE_1D_ARRAY:                             return "image1DArray";
        case GL_IMAGE_2D_ARRAY:                             return "image2DArray";
        case GL_IMAGE_2D_MULTISAMPLE:                       return "image2DMS";
        case GL_IMAGE_2D_MULTISAMPLE_ARRAY:                 return "image2DMSArray";
        case GL_INT_IMAGE_1D:                               return "iimage1D";
        case GL_INT_IMAGE_2D:                               return "iimage2D";
        case GL_INT_IMAGE_3D:                               return "iimage3D";
        case GL_INT_IMAGE_2D_RECT:                          return "iimage2DRect";
        case GL_INT_IMAGE_CUBE:                             return "iimageCube";
        case GL_INT_IMAGE_BUFFER:                           return "iimageBuffer";
        case GL_INT_IMAGE_1D_ARRAY:                         return "iimage1DArray";
        case GL_INT_IMAGE_2D_ARRAY:                         return "iimage2DArray";
        case GL_INT_IMAGE_2D_MULTISAMPLE:                   return "iimage2DMS";
        case GL_INT_IMAGE_2D_MULTISAMPLE_ARRAY:             return "iimage2DMSArray";
        case GL_UNSIGNED_INT_IMAGE_1D:                      return "uimage1D";
        case GL_UNSIGNED_INT_IMAGE_2D:                      return "uimage2D";
        case GL_UNSIGNED_INT_IMAGE_3D:                      return "uimage3D";
        case GL_UNSIGNED_INT_IMAGE_2D_RECT:                 return "uimage2DRect";
        case GL_UNSIGNED_INT_IMAGE_CUBE:                    return "uimageCube";
        case GL_UNSIGNED_INT_IMAGE_BUFFER:                  return "uimageBuffer";
        case GL_UNSIGNED_INT_IMAGE_1D_ARRAY:                return "uimage1DArray";
        case GL_UNSIGNED_INT_IMAGE_2D_ARRAY:                return "uimage2DArray";
        case GL_UNSIGNED_INT_IMAGE_2D_MULTISAMPLE:          return "uimage2DMS";
        case GL_UNSIGNED_INT_IMAGE_2D_MULTISAMPLE_ARRAY:    return "uimage2DMSArray";
        case GL_UNSIGNED_INT_ATOMIC_COUNTER:                return "atomic_uint";
        default: break;
    }
    return "other data type";
}

inline const char* CSCI441_INTERNAL::ShaderUtils::GL_shader_type_to_string(
        const GLenum type
) {
  switch(type) {
    case GL_VERTEX_SHADER:          return "Vertex Shader";
    case GL_TESS_CONTROL_SHADER:    return "Tess Ctrl Shader";
    case GL_TESS_EVALUATION_SHADER: return "Tess Eval Shader";
    case GL_GEOMETRY_SHADER:        return "Geometry Shader";
    case GL_FRAGMENT_SHADER:        return "Fragment Shader";
    case GL_COMPUTE_SHADER:         return "Compute Shader";
    default: break;
  }
  return "other shader type";
}

inline const char* CSCI441_INTERNAL::ShaderUtils::GL_primitive_type_to_string(
        const GLenum type
) {
    switch(type) {
        case GL_POINTS:                 return "Points";
        case GL_LINES:                  return "Lines";
        case GL_LINE_STRIP:             return "Line Strip";
        case GL_LINE_LOOP:              return "Line Loop";
        case GL_LINES_ADJACENCY:        return "Line Adjacency";
        case GL_TRIANGLES:              return "Triangles";
        case GL_TRIANGLE_STRIP:         return "Triangle Strip";
        case GL_TRIANGLES_ADJACENCY:    return "Triangle Adjacency";
        case GL_PATCHES:                return "Patches";
        default: break;
    }
    return "other primitive type";
}

inline void CSCI441_INTERNAL::ShaderUtils::printShaderLog(
        const GLuint shaderHandle
) {
    // check if the handle is to a vertex/fragment shader
    if( glIsShader( shaderHandle ) ) {
		GLint maxLength = 0, status = 0, infoLogLength = 0;
        glGetShaderiv(  shaderHandle, GL_INFO_LOG_LENGTH, &maxLength );

        // create a buffer of designated length
		const auto infoLog = new GLchar[maxLength];
		
		glGetShaderiv( shaderHandle, GL_COMPILE_STATUS, &status );
    	if( sDEBUG ) printf( "[INFO]: |   Shader  Handle %2d: Compile%-26s |\n", shaderHandle, (status == 1 ? "d Successfully" : "r Error") );

        // get the info log for the vertex/tesselation/geometry/fragment/compute shader
        glGetShaderInfoLog(shaderHandle, maxLength, &infoLogLength, infoLog );

        if(infoLogLength > 0 ) {
			// print info to terminal
        	if( sDEBUG ) printf( "[INFO]: |   Shader Handle %d: %s\n", shaderHandle, infoLog );
        }

        delete[] infoLog;
    } else {
		if( sDEBUG ) fprintf( stderr, "[WARN]: |  Handle %-3d is not for a Shader                        |\n", shaderHandle );
	}
}

inline void CSCI441_INTERNAL::ShaderUtils::printProgramLog(
    const GLuint programHandle
) {
	// check if the handle is to a vertex/fragment shader
    if( glIsProgram( programHandle ) ) {
		GLint status = 0;
		glGetProgramiv( programHandle, GL_LINK_STATUS, &status );
    	if( sDEBUG ) printf("[INFO]: |   Program Handle %2d: Linke%-28s |\n", programHandle, (status == 1 ? "d Successfully" : "r Error") );

    	printProgramInfoLog(programHandle);
    } else {
		if( sDEBUG ) fprintf( stderr, "[WARN]: |  Handle %-3d is not for a Shader Program                |\n", programHandle );
	}
}

inline void CSCI441_INTERNAL::ShaderUtils::printProgramInfoLog(
	const GLuint programHandle
) {
	// check if the handle is to a vertex/fragment shader
	if( glIsProgram( programHandle ) ) {
		GLint maxLength = 0, infoLogLength = 0;
		glGetProgramiv(  programHandle, GL_INFO_LOG_LENGTH, &maxLength );

		// create a buffer of designated length
		const auto infoLog = new GLchar[maxLength];

		// get the info log for the vertex/tesselation/geometry/fragment/compute shader
		glGetProgramInfoLog(programHandle, maxLength, &infoLogLength, infoLog );

		if(infoLogLength > 0 ) {
			// print info to terminal
			if( sDEBUG ) printf( "[INFO]: |   Program Handle %d: %s\n", programHandle, infoLog );
		}

		delete[] infoLog;
	} else {
		if( sDEBUG ) fprintf( stderr, "[WARN]: |  Handle %-3d is not for a Shader Program                |\n", programHandle );
	}
}

inline void CSCI441_INTERNAL::ShaderUtils::printProgramPipelineLog(
        const GLuint pipelineHandle
) {
    // check if the handle is to a shader program pipeline
    if( glIsProgramPipeline( pipelineHandle ) ) {
        GLint maxLength = 0, infoLogLength = 0;

        glGetProgramPipelineiv(  pipelineHandle, GL_INFO_LOG_LENGTH, &maxLength );

        // create a buffer of designated length
		const auto infoLog = new GLchar[maxLength];
		
        // get the info log for the shader program pipeline
        glGetProgramPipelineInfoLog(pipelineHandle, maxLength, &infoLogLength, infoLog );

        if( infoLogLength > 0 ) {
			// print info to terminal
        	if( sDEBUG ) printf( "[INFO]: |   Pipeline Handle %d: %s\n", pipelineHandle, infoLog );
        }

        delete[] infoLog;
    } else {
		if( sDEBUG ) fprintf( stderr, "[WARN]: |  Handle %-3d is not for a Shader Program Pipeline       |\n", pipelineHandle );
	}
}

inline GLboolean CSCI441_INTERNAL::ShaderUtils::printSubroutineInfo(
        const GLuint programHandle,
        const GLenum shaderStage,
        const GLboolean printHeader
) {
	GLint numSubroutineUniforms = 0;
	glGetProgramStageiv(programHandle, shaderStage, GL_ACTIVE_SUBROUTINE_UNIFORMS, &numSubroutineUniforms);
	bool headerPrinted = false;
	if( numSubroutineUniforms > 0 ) {
        if( printHeader ) {
            printf( "[INFO]: >--------------------------------------------------------<\n");
            headerPrinted = true;
        }
        printf("[INFO]: | GL_ACTIVE_SUBROUTINE_UNIFORMS (%-15s): %5i |\n", CSCI441_INTERNAL::ShaderUtils::GL_shader_type_to_string(shaderStage), numSubroutineUniforms);
        for(int i = 0; i < numSubroutineUniforms; i++ ) {
            GLchar subroutineName[256];
            GLint max_length = 256, actual_length = 0;
            GLint numCompatibleSubroutines = 0;

            glGetActiveSubroutineUniformName(programHandle, shaderStage, i, max_length, &actual_length, subroutineName );
            glGetActiveSubroutineUniformiv(programHandle, shaderStage, i, GL_NUM_COMPATIBLE_SUBROUTINES, &numCompatibleSubroutines );
            
			const auto compatibleSubroutines = new GLint[numCompatibleSubroutines];
            glGetActiveSubroutineUniformiv(programHandle, shaderStage, i, GL_COMPATIBLE_SUBROUTINES, compatibleSubroutines );
            
			GLint loc = glGetSubroutineUniformLocation(programHandle, shaderStage, subroutineName );

            printf("[INFO]: |   %i) name: %-15s #subRoutines: %-5i loc: %2i |\n", i, subroutineName, numCompatibleSubroutines, loc );

            for(int j = 0; j < numCompatibleSubroutines; j++ ) {
                GLint idx = compatibleSubroutines[j];

                GLchar subroutineImplName[64];
                GLint max_length2 = 64, actual_length2 = 0;
                glGetActiveSubroutineName(programHandle, shaderStage, idx, max_length2, &actual_length2, subroutineImplName );

                printf("[INFO]: |     %i) subroutine: %-25s index: %2i |\n", j, subroutineImplName, idx );
            }

            delete[] compatibleSubroutines;
        }
	}
	return !headerPrinted;
}

inline void CSCI441_INTERNAL::ShaderUtils::printShaderProgramInfo(
        const GLuint programHandle,
        const GLboolean hasVertexShader,
        const GLboolean hasTessControlShader,
        const GLboolean hasTessEvalShader,
        const GLboolean hasGeometryShader,
        const GLboolean hasFragmentShader,
        const GLboolean hasComputeShader,
        const GLboolean useLastNewLine = true
) {
    GLint major = 0, minor = 0;
    glGetIntegerv(GL_MAJOR_VERSION, &major);
    glGetIntegerv(GL_MINOR_VERSION, &minor);

    GLuint shaders[6] = {0};
    GLint max_count = 6;
    GLint actual_count = 0;

    GLint maxAttributeNameLength = 0;
    GLint maxUniformNameLength = 0;

    // get max var name from program
    // https://registry.khronos.org/OpenGL-Refpages/gl4/html/glGetActiveAttrib.xhtml
    glGetProgramiv(programHandle, GL_ACTIVE_ATTRIBUTE_MAX_LENGTH, &maxAttributeNameLength);
    glGetProgramiv(programHandle, GL_ACTIVE_UNIFORM_MAX_LENGTH, &maxUniformNameLength);

    glGetAttachedShaders(programHandle, max_count, &actual_count, shaders );
    if(actual_count > 0) {
        if( sDEBUG ) printf( "[INFO]: >--------------------------------------------------------<\n");
        if( sDEBUG ) printf("[INFO]: | GL_ATTACHED_SHADERS: %33i |\n", actual_count);
        for(int i = 0; i < actual_count; i++ ) {
            GLint shaderType;
            glGetShaderiv( shaders[i], GL_SHADER_TYPE, &shaderType );
            if( sDEBUG ) printf("[INFO]: |   %i) %-38s Handle: %2i |\n", i, GL_shader_type_to_string(shaderType), shaders[i]);
        }
    }

    if(sDEBUG) {
        if(hasGeometryShader) {
            if( major > 3 || (major >= 3 && minor >= 2)  ) {
                GLint verticesOut = 0, inputType = 0, outputType = 0;
                glGetProgramiv(programHandle, GL_GEOMETRY_VERTICES_OUT, &verticesOut);
                glGetProgramiv(programHandle, GL_GEOMETRY_INPUT_TYPE, &inputType);
                glGetProgramiv(programHandle, GL_GEOMETRY_OUTPUT_TYPE, &outputType);

                printf( "[INFO]: >--------------------------------------------------------<\n");
                printf( "[INFO]: | GEOMETRY SHADER PRIMITIVE I/O                          |\n");
                printf( "[INFO]: |   Input Type: %40s |\n", GL_primitive_type_to_string(inputType) );
                printf( "[INFO]: |   Output Type: %39s |\n", GL_primitive_type_to_string(outputType) );
                printf( "[INFO]: |   Max Vertices Out: %34d |\n", verticesOut );
            }
        }
    }

    if(hasVertexShader) {
		GLint numActiveAttributes = 0;
        glGetProgramiv(programHandle, GL_ACTIVE_ATTRIBUTES, &numActiveAttributes );
        if( numActiveAttributes > 0 ) {
            if( sDEBUG ) printf( "[INFO]: >--------------------------------------------------------<\n");
            if( sDEBUG ) printf( "[INFO]: | GL_ACTIVE_ATTRIBUTES: %32i |\n", numActiveAttributes );
            for( int i = 0; i < numActiveAttributes; i++ ) {
                const auto name = new GLchar[maxAttributeNameLength];
                GLint actual_length = 0, size = 0;
                GLenum type = GL_NONE;
                glGetActiveAttrib(programHandle, i, maxAttributeNameLength, &actual_length, &size, &type, name );
                if( size > 1 ) {
                    for( int j = 0; j < size; j++ ) {
                        // length of string + max array value size (technically it depends on the size of GL type, but I'm not aware a way to get the size) 
                        // + array accessors + null
                        int max_array_size = actual_length + 4 + 2 + 1;
                        const auto array_name = new GLchar[max_array_size];

                        snprintf( array_name, max_array_size, "%s[%i]", name, j );
                        GLint location = glGetAttribLocation(programHandle, array_name);
                        if( sDEBUG ) printf( "[INFO]: |   %i) type: %-15s name: %-13s loc: %2i |\n", i, GLSL_type_to_string( type ), array_name, location );
                        delete[] array_name;
                    }
                } else {
                    GLint location = glGetAttribLocation(programHandle, name );
                    if( sDEBUG ) printf( "[INFO]: |   %i) type: %-15s name: %-13s loc: %2i |\n",i, GLSL_type_to_string( type ), name, location );
                }

                delete[] name;
            }
        }
    }

	GLint numActiveUniforms = 0;
    glGetProgramiv(programHandle, GL_ACTIVE_UNIFORMS, &numActiveUniforms);
    if( numActiveUniforms > 0 ) {
		constexpr int NUM_PROPS = 6;
		GLenum props[NUM_PROPS] = {GL_REFERENCED_BY_VERTEX_SHADER,
								   GL_REFERENCED_BY_TESS_CONTROL_SHADER,
								   GL_REFERENCED_BY_TESS_EVALUATION_SHADER,
								   GL_REFERENCED_BY_GEOMETRY_SHADER,
								   GL_REFERENCED_BY_FRAGMENT_SHADER,
								   GL_NONE};
								   
		if((major == 4 && minor >= 3) || major > 4) {
			props[5] = GL_REFERENCED_BY_COMPUTE_SHADER;
		}
		GLint results[NUM_PROPS] = {0};
			
        if( sDEBUG ) printf( "[INFO]: >--------------------------------------------------------<\n" );
        if( sDEBUG ) printf("[INFO]: | GL_ACTIVE_UNIFORMS: %34i |\n", numActiveUniforms);
        for(int uIdx = 0; uIdx < numActiveUniforms; uIdx++) {
            const auto name = new GLchar[maxUniformNameLength];
            GLint actual_length = 0, size = 0, location = -1;
            GLenum type = GL_NONE;
            glGetActiveUniform(programHandle, uIdx, maxUniformNameLength, &actual_length, &size, &type, name );
            if(size > 1) {
                for(int j = 0; j < size; j++) {
                    int max_array_size = actual_length + 4 + 2 + 1;
					const auto array_name = new GLchar[max_array_size];
                    snprintf(array_name, max_array_size, "%s[%i]", name, j);
                    location = glGetUniformLocation(programHandle, array_name);
                    if(location != -1) {
                        if (sDEBUG) printf("[INFO]: |  %2i) type: %-15s name: %-13s loc: %2i |\n", uIdx, GLSL_type_to_string(type), array_name, location);
                    }
                    delete[] array_name;
                }
            } else {
                location = glGetUniformLocation(programHandle, name);
                if(location != -1) {
                    if (sDEBUG) printf("[INFO]: |  %2i) type: %-15s name: %-13s loc: %2i |\n", uIdx, GLSL_type_to_string(type), name, location);
                }
            }
			
			if(((major == 4 && minor >= 3) || major > 4) && location != -1) {
				glGetProgramResourceiv(programHandle, GL_UNIFORM, uIdx, NUM_PROPS, props, NUM_PROPS, nullptr, results);
				if( sDEBUG ) printf("[INFO]: |     Used in: %-4s %-4s %-4s %-3s %-4s %-4s    Shader(s) |\n", (results[0] ? "Vert" : ""), (results[1] ? "Ctrl" : ""), (results[2] ? "Eval" : ""), (results[3] ? "Geo" : ""), (results[4] ? "Frag" : ""), (results[5] ? "Comp" : ""));
			}
			
            delete[] name;
        }
    }

	GLint numActiveUniformBlocks = 0;
    glGetProgramiv(programHandle, GL_ACTIVE_UNIFORM_BLOCKS, &numActiveUniformBlocks);
    if( numActiveUniformBlocks > 0 ) {
		int vsCount, tcsCount, tesCount, gsCount, fsCount, csCount;
		vsCount = tcsCount = tesCount = gsCount = fsCount = csCount = 0;

        if( sDEBUG ) printf( "[INFO]: >--------------------------------------------------------<\n");
        if( sDEBUG ) printf("[INFO]: | GL_UNIFORM_BLOCK_ACTIVE_UNIFORMS: %20d |\n", numActiveUniformBlocks);
        for(int i = 0; i < numActiveUniformBlocks; i++ ) {
            GLint numActiveUniformsInBlock = 0, bindingPoint = 0;
            glGetActiveUniformBlockiv(programHandle, i, GL_UNIFORM_BLOCK_ACTIVE_UNIFORMS, &numActiveUniformsInBlock );
			glGetActiveUniformBlockiv(programHandle, i, GL_UNIFORM_BLOCK_BINDING, &bindingPoint);
			
			GLint actualLen;
            glGetActiveUniformBlockiv(programHandle, i, GL_UNIFORM_BLOCK_NAME_LENGTH, &actualLen);
            const auto name = new GLchar[actualLen];
            glGetActiveUniformBlockName(programHandle, i, actualLen, nullptr, name);

            const auto indices = new GLint[numActiveUniformsInBlock];
            glGetActiveUniformBlockiv(programHandle, i, GL_UNIFORM_BLOCK_ACTIVE_UNIFORM_INDICES, indices);
			
            const auto offsets = new GLint[numActiveUniformsInBlock];
            glGetActiveUniformsiv(programHandle, numActiveUniformsInBlock, (GLuint*)indices, GL_UNIFORM_OFFSET, offsets);

            if( sDEBUG ) printf("[INFO]: | %d) %-19s     binding: %3d                |\n", i, name, bindingPoint);

            GLint vs, tcs, tes, gs, fs, cs;
            glGetActiveUniformBlockiv(programHandle, i, GL_UNIFORM_BLOCK_REFERENCED_BY_VERTEX_SHADER, &vs);				if( vs ) vsCount++;
            glGetActiveUniformBlockiv(programHandle, i, GL_UNIFORM_BLOCK_REFERENCED_BY_TESS_CONTROL_SHADER, &tcs);		if( tcs) tcsCount++;
            glGetActiveUniformBlockiv(programHandle, i, GL_UNIFORM_BLOCK_REFERENCED_BY_TESS_EVALUATION_SHADER, &tes);	if( tes) tesCount++;
            glGetActiveUniformBlockiv(programHandle, i, GL_UNIFORM_BLOCK_REFERENCED_BY_GEOMETRY_SHADER, &gs);			if( gs ) gsCount++;
            glGetActiveUniformBlockiv(programHandle, i, GL_UNIFORM_BLOCK_REFERENCED_BY_FRAGMENT_SHADER, &fs);			if( fs ) fsCount++;
			if((major == 4 && minor >= 3) || major > 4) {
				glGetActiveUniformBlockiv(programHandle, i, GL_UNIFORM_BLOCK_REFERENCED_BY_COMPUTE_SHADER, &cs);		if( cs ) csCount++;
			}
            if( sDEBUG ) printf("[INFO]: |   Used in: %-4s %-4s %-4s %-3s %-4s %-4s      Shader(s) |\n", (vs ? "Vert" : ""), (tcs ? "Ctrl" : ""), (tes ? "Eval" : ""), (gs ? "Geo" : ""), (fs ? "Frag" : ""), (cs ? "Comp" : ""));

            const auto name2 = new char[maxUniformNameLength];
            for(int j = 0; j < numActiveUniformsInBlock; j++) {
                GLenum type;
                int uniSize;
                glGetActiveUniform(programHandle, indices[j], maxUniformNameLength, &actualLen, &uniSize, &type, name2);
				
				constexpr GLsizei NUM_ATOMIC_PROPERTIES = 1;
				GLint atomicIndex[NUM_ATOMIC_PROPERTIES] = {-1};
				if((major == 4 && minor >= 3) || major > 4) {
					GLenum atomicProps[NUM_ATOMIC_PROPERTIES] = {GL_ATOMIC_COUNTER_BUFFER_INDEX};
					glGetProgramResourceiv(programHandle, GL_UNIFORM, indices[j], NUM_ATOMIC_PROPERTIES, atomicProps, NUM_ATOMIC_PROPERTIES, nullptr, atomicIndex);
				}

                if( atomicIndex[0] == -1 && sDEBUG ) {
                    printf("[INFO]: |  %2d) type: %-15s name: %-21s |\n", j, GLSL_type_to_string(type), name2);
                    printf("[INFO]: |      uniform index: %3d    offset: %4d                |\n", indices[j], offsets[j]);
                }
            }
			
			delete[] name;
			delete[] indices;
			delete[] offsets;
			delete[] name2;
        }

        if( vsCount + tcsCount + tesCount + gsCount + fsCount + csCount > 0 ) {
            GLint maxUniBlocks = 0;
            glGetIntegerv( GL_MAX_COMBINED_UNIFORM_BLOCKS, &maxUniBlocks );
            if( sDEBUG ) printf( "[INFO]: | Shader Uniform Block Counts                     %2d/%2d  |\n", numActiveUniformBlocks, maxUniBlocks);
            if( hasVertexShader ) {
                GLint maxVertexUniformBlocks = 0;
                glGetIntegerv( GL_MAX_VERTEX_UNIFORM_BLOCKS, &maxVertexUniformBlocks );

                if( sDEBUG ) printf( "[INFO]: |   Vertex Shader Uniform Blocks: %18d/%2d  |\n", vsCount, maxVertexUniformBlocks );
            }
            if( hasTessControlShader ) {
                GLint maxTessControlUniformBlocks = 0;
                glGetIntegerv( GL_MAX_TESS_CONTROL_UNIFORM_BLOCKS, &maxTessControlUniformBlocks );

                if( sDEBUG ) printf( "[INFO]: |   Tess Ctrl Shader Uniform Blocks: %15d/%2d  |\n", tcsCount, maxTessControlUniformBlocks );
            }
            if( hasTessEvalShader ) {
                GLint maxTessEvalUniformBlocks = 0;
                glGetIntegerv( GL_MAX_TESS_EVALUATION_UNIFORM_BLOCKS, &maxTessEvalUniformBlocks );

                if( sDEBUG ) printf( "[INFO]: |   Tess Eval Shader Uniform Blocks: %15d/%2d  |\n", tesCount, maxTessEvalUniformBlocks );
            }
            if( hasGeometryShader ) {
                GLint maxGeometryUniformBlocks = 0;
                glGetIntegerv( GL_MAX_GEOMETRY_UNIFORM_BLOCKS, &maxGeometryUniformBlocks );

                if( sDEBUG ) printf( "[INFO]: |   Geometry Shader Uniform Blocks: %16d/%2d  |\n", gsCount, maxGeometryUniformBlocks );
            }
            if( hasFragmentShader ) {
                GLint maxFragmentUniformBlocks = 0;
                glGetIntegerv( GL_MAX_FRAGMENT_UNIFORM_BLOCKS, &maxFragmentUniformBlocks );

                if( sDEBUG ) printf( "[INFO]: |   Fragment Shader Uniform Blocks: %16d/%2d  |\n", fsCount, maxFragmentUniformBlocks );
            }
            if( hasComputeShader ) {
                GLint maxComputeUniformBlocks = 0;
                glGetIntegerv( GL_MAX_COMPUTE_UNIFORM_BLOCKS, &maxComputeUniformBlocks );

                if( sDEBUG ) printf( "[INFO]: |   Compute Shader Uniform Blocks: %17d/%2d  |\n", csCount, maxComputeUniformBlocks );
            }
        }
    }

	if (sDEBUG) {
		if ((major == 4 && minor >=3) || major > 4) {
			GLint numFragOutputs;           //Where GL will write the number of outputs
			glGetProgramInterfaceiv(programHandle, GL_PROGRAM_OUTPUT,GL_ACTIVE_RESOURCES, &numFragOutputs);

			printf( "[INFO]: >--------------------------------------------------------<\n");
			printf( "[INFO]: | GL_PROGRAM_OUTPUT: %35d |\n", numFragOutputs);

			if(numFragOutputs > 0) {
				GLint maxLen = 0;
                glGetProgramInterfaceiv(programHandle, GL_PROGRAM_OUTPUT, GL_MAX_NAME_LENGTH, &maxLen);

				const auto outputName = new GLchar[maxLen];

				//Now you can query for the names and indices of the outputs
				for (GLint i = 0; i < numFragOutputs; i++) {
					GLsizei actualLength = 0;
					glGetProgramResourceName(programHandle, GL_PROGRAM_OUTPUT, i, maxLen, &actualLength, outputName);
					GLint location = glGetFragDataLocation(programHandle, outputName);
					GLint index = glGetFragDataIndex(programHandle, outputName);
					printf( "[INFO]: | %3d) name: %-18s location: %3d index: %3d |\n", i, outputName, location, index );
				}

				delete[] outputName;
			}
		}
	}

    if( sDEBUG ) {
        if((major == 4 && minor >= 3) || major > 4) {
            GLint numSSBO = 0;
            glGetProgramInterfaceiv(programHandle, GL_SHADER_STORAGE_BLOCK, GL_ACTIVE_RESOURCES, &numSSBO);
            if(numSSBO > 0) {
                GLint maxLen = 0;
                glGetProgramInterfaceiv(programHandle, GL_SHADER_STORAGE_BLOCK, GL_MAX_NAME_LENGTH, &maxLen);
                const auto ssboName = new GLchar[maxLen];
                GLsizei ssboNameLen = 0;

                constexpr int NUM_PROPS = 7;
                GLenum props[NUM_PROPS] = {GL_BUFFER_BINDING,
                                           GL_REFERENCED_BY_VERTEX_SHADER,
                                           GL_REFERENCED_BY_TESS_CONTROL_SHADER, GL_REFERENCED_BY_TESS_EVALUATION_SHADER,
                                           GL_REFERENCED_BY_GEOMETRY_SHADER,
                                           GL_REFERENCED_BY_FRAGMENT_SHADER,
                                           GL_REFERENCED_BY_COMPUTE_SHADER};
                GLsizei numWritten = 0;
                GLint results[NUM_PROPS] = {0};

                int vSSB, teSSB, tcSSB, gSSB, fSSB, cSSB;
                vSSB = teSSB = tcSSB = gSSB = fSSB = cSSB = 0;

                printf( "[INFO]: >--------------------------------------------------------<\n");
                printf( "[INFO]: | GL_SHADER_STORAGE_BLOCK: %29d |\n", numSSBO );
                for(int i = 0; i < numSSBO; i++) {
                    glGetProgramResourceName(programHandle, GL_SHADER_STORAGE_BLOCK, i, maxLen, &ssboNameLen, ssboName);
                    GLuint ssboIndex = glGetProgramResourceIndex(programHandle, GL_SHADER_STORAGE_BLOCK, ssboName);
                    glGetProgramResourceiv(programHandle, GL_SHADER_STORAGE_BLOCK, i, NUM_PROPS, props, NUM_PROPS, &numWritten, results);

                    printf( "[INFO]: | %3d) name: %-19s index: %3d binding: %3d |\n", i, ssboName, ssboIndex, results[0] );
                    printf( "[INFO]: |   Used in: %-4s %-4s %-4s %-3s %-4s %-4s      Shader(s) |\n", (results[1] ? "Vert" : ""), (results[2] ? "Ctrl" : ""), (results[3] ? "Eval" : ""), (results[4] ? "Geo" : ""), (results[5] ? "Frag" : ""), (results[6] ? "Comp" : ""));

                    if(results[1]) vSSB++;
                    if(results[2]) teSSB++;
                    if(results[3]) tcSSB++;
                    if(results[4]) gSSB++;
                    if(results[5]) fSSB++;
                    if(results[6]) cSSB++;
                }

                GLint maxSSBCounters = 0;
                glGetIntegerv( GL_MAX_COMBINED_SHADER_STORAGE_BLOCKS, &maxSSBCounters );
                printf( "[INFO]: | Shader Storage Block Counts:                   %2d/%2d   |\n", numSSBO, maxSSBCounters );
                if(hasVertexShader) {
                    GLint maxVertSSB = 0;
                    glGetIntegerv( GL_MAX_VERTEX_SHADER_STORAGE_BLOCKS, &maxVertSSB );
                    printf( "[INFO]: |   Vertex Shader Storage Blocks:                %2d/%2d   |\n", vSSB, maxVertSSB );
                }
                if(hasTessControlShader) {
                    GLint maxTESSB = 0;
                    glGetIntegerv( GL_MAX_TESS_CONTROL_SHADER_STORAGE_BLOCKS, &maxTESSB );
                    printf( "[INFO]: |   Tess Ctrl Shader Storage Blocks:              %2d/%2d   |\n", teSSB, maxTESSB );
                }
                if(hasTessEvalShader) {
                    GLint maxTCSSB = 0;
                    glGetIntegerv( GL_MAX_TESS_EVALUATION_SHADER_STORAGE_BLOCKS, &maxTCSSB );
                    printf( "[INFO]: |   Tess Eval Shader Storage Blocks:              %2d/%2d   |\n", tcSSB, maxTCSSB );
                }
                if(hasGeometryShader) {
                    GLint maxGeoSSB = 0;
                    glGetIntegerv( GL_MAX_GEOMETRY_SHADER_STORAGE_BLOCKS, &maxGeoSSB );
                    printf( "[INFO]: |   Geometry Shader Storage Blocks:              %2d/%2d   |\n", gSSB, maxGeoSSB );
                }
                if(hasFragmentShader) {
                    GLint maxFragSSB = 0;
                    glGetIntegerv( GL_MAX_FRAGMENT_SHADER_STORAGE_BLOCKS, &maxFragSSB );
                    printf( "[INFO]: |   Fragment Shader Storage Blocks:              %2d/%2d   |\n", fSSB, maxFragSSB );
                }
                if(hasComputeShader) {
                    GLint maxComputeSSB = 0;
                    glGetIntegerv( GL_MAX_COMPUTE_SHADER_STORAGE_BLOCKS, &maxComputeSSB );
                    printf( "[INFO]: |   Compute Shader Storage Blocks:               %2d/%2d   |\n", cSSB, maxComputeSSB );
                }
				
				delete[] ssboName;
            }
        }

        if((major == 4 && minor >= 2) || major > 4) {
            GLint numAtomicCounters = 0;
            glGetProgramInterfaceiv(programHandle, GL_ATOMIC_COUNTER_BUFFER, GL_ACTIVE_RESOURCES, &numAtomicCounters);
			
		    if(numAtomicCounters > 0) {
				constexpr int NUM_PROPS = 6;
                GLenum props[NUM_PROPS] = {GL_REFERENCED_BY_VERTEX_SHADER,
                                           GL_REFERENCED_BY_TESS_CONTROL_SHADER,
                                           GL_REFERENCED_BY_TESS_EVALUATION_SHADER,
                                           GL_REFERENCED_BY_GEOMETRY_SHADER,
                                           GL_REFERENCED_BY_FRAGMENT_SHADER,
                                           GL_NONE};
										   
				if((major == 4 && minor >= 3) || major > 4) {
					props[5] = GL_REFERENCED_BY_COMPUTE_SHADER;
				}
				
                GLsizei numWritten = 0;
                GLint results[NUM_PROPS] = {0};

                printf( "[INFO]: >--------------------------------------------------------<\n");
                printf("[INFO]: | GL_ATOMIC_COUNTER_BUFFER: %28d |\n", numAtomicCounters );

                int vAC, teAC, tcAC, gAC, fAC, cAC;
                vAC = teAC = tcAC = gAC = fAC = cAC = 0;

                for(GLint acIdx = 0; acIdx < numAtomicCounters; acIdx++) {
					GLint binding = -1, bufferSize = 0, nac = 0;
					
					glGetActiveAtomicCounterBufferiv(programHandle, acIdx, GL_ATOMIC_COUNTER_BUFFER_BINDING, &binding);
					glGetActiveAtomicCounterBufferiv(programHandle, acIdx, GL_ATOMIC_COUNTER_BUFFER_DATA_SIZE, &bufferSize);
					glGetActiveAtomicCounterBufferiv(programHandle, acIdx, GL_ATOMIC_COUNTER_BUFFER_ACTIVE_ATOMIC_COUNTERS, &nac);
					
					const auto uniformIndices = new GLint[nac];
					const auto atomicOffsets = new GLint[nac];
					const auto atomicName = new GLchar[maxUniformNameLength];
					
					glGetActiveAtomicCounterBufferiv(programHandle, acIdx, GL_ATOMIC_COUNTER_BUFFER_ACTIVE_ATOMIC_COUNTER_INDICES, uniformIndices);
					glGetActiveUniformsiv(programHandle, nac, (GLuint*)uniformIndices, GL_UNIFORM_OFFSET, atomicOffsets);
					glGetProgramResourceiv(programHandle, GL_ATOMIC_COUNTER_BUFFER, acIdx, NUM_PROPS, props, NUM_PROPS, &numWritten, results);
					
					// increment counts of which shaders have an atomic counter
					if(results[0]) vAC++;
					if(results[1]) teAC++;
					if(results[2]) tcAC++;
					if(results[3]) gAC++;
					if(results[4]) fAC++;
					if(results[5]) cAC++;
					
					printf( "[INFO]: | %d) binding: %11d    buffer size: %4d           |\n", acIdx, binding, bufferSize );
					printf( "[INFO]: |   Used in: %-4s %-4s %-4s %-3s %-4s %-4s      Shader(s) |\n", (results[0] ? "Vert" : ""), (results[1] ? "Ctrl" : ""), (results[2] ? "Eval" : ""), (results[3] ? "Geo" : ""), (results[4] ? "Frag" : ""), (results[5] ? "Comp" : ""));						
					
					GLint acCtr = 0, actualLen = 0, uniSize = 0;
					GLenum type = GL_NONE;
					for(GLint uniIdx = 0; uniIdx < nac; uniIdx++) {
						glGetActiveUniform(programHandle, uniformIndices[uniIdx], maxUniformNameLength, &actualLen, &uniSize, &type, atomicName);
						
						constexpr GLsizei NUM_ATOMIC_PROPERTIES = 1;
						GLenum atomicProps[NUM_ATOMIC_PROPERTIES] = {GL_ATOMIC_COUNTER_BUFFER_INDEX};
						GLint atomicIndex [NUM_ATOMIC_PROPERTIES] = {-1};
						glGetProgramResourceiv(programHandle, GL_UNIFORM, uniformIndices[uniIdx], NUM_ATOMIC_PROPERTIES, atomicProps, NUM_ATOMIC_PROPERTIES, nullptr, atomicIndex);
						
						if(atomicIndex[0] == acIdx) {
							printf( "[INFO]: | %3d) type: %-15s name: %-21s |\n", acCtr++, GLSL_type_to_string(type), atomicName );
							printf( "[INFO]: |      uniform index: %3d      offset: %7d           |\n", uniformIndices[uniIdx], atomicOffsets[uniIdx] );							
						}
					}
					
					delete[] uniformIndices;
					delete[] atomicOffsets;
					delete[] atomicName;
				}

                GLint maxAtomicCounters = 0;
                glGetIntegerv( GL_MAX_COMBINED_ATOMIC_COUNTERS, &maxAtomicCounters );
                printf("[INFO]: | Atomic Counter Counts:                     %4d/%4d   |\n", numAtomicCounters, maxAtomicCounters );
                if(hasVertexShader) {
                    GLint maxVertAtomicCounters = 0;
                    glGetIntegerv( GL_MAX_VERTEX_ATOMIC_COUNTERS, &maxVertAtomicCounters );
                    printf( "[INFO]: |   Vertex Atomic Counters:                  %4d/%4d   |\n", vAC, maxVertAtomicCounters );
                }
                if(hasTessControlShader) {
                    GLint maxTCAtomicCounters = 0;
                    glGetIntegerv( GL_MAX_TESS_CONTROL_ATOMIC_COUNTERS, &maxTCAtomicCounters );
                    printf( "[INFO]: |   Tess Ctrl Atomic Counters:                %4d/%4d   |\n", teAC, maxTCAtomicCounters );
                }
                if(hasTessEvalShader) {
                    GLint maxTEAtomicCounters = 0;
                    glGetIntegerv( GL_MAX_TESS_EVALUATION_ATOMIC_COUNTERS, &maxTEAtomicCounters );
                    printf( "[INFO]: |   Tess Eval Atomic Counters:                %4d/%4d   |\n", tcAC, maxTEAtomicCounters );
                }
                if(hasGeometryShader) {
                    GLint maxGeoAtomicCounters = 0;
                    glGetIntegerv( GL_MAX_GEOMETRY_ATOMIC_COUNTERS, &maxGeoAtomicCounters );
                    printf( "[INFO]: |   Geometry Atomic Counters:                  %4d/%4d   |\n", gAC, maxGeoAtomicCounters );
                }
                if(hasFragmentShader) {
                    GLint maxFragAtomicCounters = 0;
                    glGetIntegerv( GL_MAX_FRAGMENT_ATOMIC_COUNTERS, &maxFragAtomicCounters );
                    printf( "[INFO]: |   Fragment Atomic Counters:                %4d/%4d   |\n", fAC, maxFragAtomicCounters );
                }
                if(hasComputeShader) {
                    GLint maxComputeAtomicCounters = 0;
                    glGetIntegerv( GL_MAX_COMPUTE_ATOMIC_COUNTERS, &maxComputeAtomicCounters );
                    printf( "[INFO]: |   Compute Atomic Counters:                 %4d/%4d   |\n", cAC, maxComputeAtomicCounters );
                }
            }
        }

        if( major >= 4 ) {
            GLboolean printHeader = GL_TRUE;
            if( hasVertexShader   )     printHeader = printSubroutineInfo(programHandle, GL_VERTEX_SHADER, printHeader );
            if( hasTessControlShader)   printHeader = printSubroutineInfo(programHandle, GL_TESS_CONTROL_SHADER, printHeader );
            if( hasTessEvalShader)      printHeader = printSubroutineInfo(programHandle, GL_TESS_EVALUATION_SHADER, printHeader );
            if( hasGeometryShader )     printHeader = printSubroutineInfo(programHandle, GL_GEOMETRY_SHADER, printHeader );
            if( hasFragmentShader )     printHeader = printSubroutineInfo(programHandle, GL_FRAGMENT_SHADER, printHeader );
            if( hasComputeShader )      printSubroutineInfo(programHandle, GL_COMPUTE_SHADER, printHeader );
        }
    }

    if(useLastNewLine && sDEBUG) printf( "[INFO]: \\--------------------------------------------------------/\n\n");
}

inline GLuint CSCI441_INTERNAL::ShaderUtils::compileShader(
        const char *filename,
        const GLenum shaderType
) {
    // will hold contents of shader source code, loaded from file
    GLchar *shaderString;

	// read in each text file and store the contents in a string
    if( readTextFromFile( filename, shaderString ) ) {
        // generate a shader handle for the corresponding shader type
        GLuint shaderHandle = glCreateShader( shaderType );

		// send the contents of each program to the GPU
		glShaderSource( shaderHandle, 1, (const char**)&shaderString, nullptr );

		// we are good programmers so free up the memory used by each buffer
		delete [] shaderString;

		// compile each shader on the GPU
		glCompileShader( shaderHandle );

		// check the shader log
		printShaderLog( shaderHandle );

		// return the handle of our shader
		return shaderHandle;
	} else {
		return 0;
	}
}

#endif // CSCI441_SHADER_UTILS_HPP