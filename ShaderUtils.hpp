/** @file ShaderUtils3.hpp
 * @brief Helper functions to work with OpenGL Shaders
 * @author Dr. Jeffrey Paone
 *
 * @copyright MIT License Copyright (c) 2017 Dr. Jeffrey Paone
 *
 *	These functions, classes, and constants help minimize common
 *	code that needs to be written.
 *
 *	@warning NOTE: This header file depends upon GLEW
 */

#ifndef __CSCI441_SHADEREUTILS_H__
#define __CSCI441_SHADEREUTILS_H__

#include <GL/glew.h>

#include <stdio.h>
#include <string.h>

#include <fstream>
#include <string>

////////////////////////////////////////////////////////////////////////////////

namespace CSCI441_INTERNAL {
	namespace ShaderUtils {
		static bool sDEBUG = true;

		void enableDebugMessages();
		void disableDebugMessages();

		const char* GLSL_type_to_string( GLenum type );
		const char* GL_shader_type_to_string( GLenum type );
		const char* GL_primitive_type_to_string( GLenum type );

		bool readTextFromFile( const char* filename, char* &output );
		GLuint compileShader( const char *filename, GLenum shaderType );

		void printLog( GLuint handle );
		void printShaderLog( GLuint shaderHandle );
		void printProgramLog( GLuint programHandle );
		void printProgramPipelineLog( GLuint pipelineHandle );
		
		GLboolean printSubroutineInfo( GLuint handle, GLenum shaderStage, GLboolean printHeader );
		void printShaderProgramInfo( GLuint handle );
        void printShaderProgramInfo( GLuint handle, GLboolean hasVertexShader, GLboolean hasTessControlShader, GLboolean hasTessEvalShader, GLboolean hasGeometryShader, GLboolean hasFragmentShader, GLboolean useLastNewLine );
        void printShaderProgramInfo( GLuint handle, GLboolean hasVertexShader, GLboolean hasTessControlShader, GLboolean hasTessEvalShader, GLboolean hasGeometryShader, GLboolean hasFragmentShader, GLboolean hasComputeShader, GLboolean useLastNewLine );
	}
}

////////////////////////////////////////////////////////////////////////////////

inline void CSCI441_INTERNAL::ShaderUtils::enableDebugMessages() {
	sDEBUG = true;
}

inline void CSCI441_INTERNAL::ShaderUtils::disableDebugMessages() {
	sDEBUG = false;
}

// readTextFromFile() //////////////////////////////////////////////////////////////
//
//  Reads in a text file as a single string. Used to aid in shader loading.
//
////////////////////////////////////////////////////////////////////////////////
inline bool CSCI441_INTERNAL::ShaderUtils::readTextFromFile(const char *filename, char* &output){
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
	
	output = new char[buf.length()+1];
	strncpy(output, buf.c_str(), buf.length());
	output[buf.length()] = '\0';
	
    in.close();
	
	return true;
}

inline const char* CSCI441_INTERNAL::ShaderUtils::GLSL_type_to_string(GLenum type) {
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
        case GL_IMAGE_2D_RECT:                              return "image3D";
        case GL_IMAGE_CUBE:                                 return "imageCube";
        case GL_IMAGE_BUFFER:                               return "imageBuffer";
        case GL_IMAGE_1D_ARRAY:                             return "image1DArray";
        case GL_IMAGE_2D_ARRAY:                             return "image2DArray";
        case GL_IMAGE_2D_MULTISAMPLE:                       return "image2DMS";
        case GL_IMAGE_2D_MULTISAMPLE_ARRAY:                 return "image2DMSArray";
        case GL_INT_IMAGE_1D:                               return "iimage1D";
        case GL_INT_IMAGE_2D:                               return "iimage2D";
        case GL_INT_IMAGE_3D:                               return "iimage3D";
        case GL_INT_IMAGE_2D_RECT:                          return "iimage3D";
        case GL_INT_IMAGE_CUBE:                             return "iimageCube";
        case GL_INT_IMAGE_BUFFER:                           return "iimageBuffer";
        case GL_INT_IMAGE_1D_ARRAY:                         return "iimage1DArray";
        case GL_INT_IMAGE_2D_ARRAY:                         return "iimage2DArray";
        case GL_INT_IMAGE_2D_MULTISAMPLE:                   return "iimage2DMS";
        case GL_INT_IMAGE_2D_MULTISAMPLE_ARRAY:             return "iimage2DMSArray";
        case GL_UNSIGNED_INT_IMAGE_1D:                      return "uimage1D";
        case GL_UNSIGNED_INT_IMAGE_2D:                      return "uimage2D";
        case GL_UNSIGNED_INT_IMAGE_3D:                      return "uimage3D";
        case GL_UNSIGNED_INT_IMAGE_2D_RECT:                 return "uimage3D";
        case GL_UNSIGNED_INT_IMAGE_CUBE:                    return "uimageCube";
        case GL_UNSIGNED_INT_IMAGE_BUFFER:                  return "uimageBuffer";
        case GL_UNSIGNED_INT_IMAGE_1D_ARRAY:                return "uimage1DArray";
        case GL_UNSIGNED_INT_IMAGE_2D_ARRAY:                return "uimage2DArray";
        case GL_UNSIGNED_INT_IMAGE_2D_MULTISAMPLE:          return "uimage2DMS";
        case GL_UNSIGNED_INT_IMAGE_2D_MULTISAMPLE_ARRAY:    return "uimage2DMSArray";
        case GL_UNSIGNED_INT_ATOMIC_COUNTER:                return "atomic_uint";
        default: break;
    }
    return "other";
}

inline const char* CSCI441_INTERNAL::ShaderUtils::GL_shader_type_to_string(GLenum type) {
  switch(type) {
    case GL_VERTEX_SHADER: return "Vertex Shader";
    case GL_TESS_CONTROL_SHADER: return "Tess Ctrl Shader";
    case GL_TESS_EVALUATION_SHADER: return "Tess Eval Shader";
    case GL_GEOMETRY_SHADER: return "Geometry Shader";
    case GL_FRAGMENT_SHADER: return "Fragment Shader";
    default: break;
  }
  return "other";
}

inline const char* CSCI441_INTERNAL::ShaderUtils::GL_primitive_type_to_string(GLenum type) {
    switch(type) {
        case GL_POINTS: return "Points";
        case GL_LINES: return "Lines";
        case GL_LINE_STRIP: return "Line Strip";
        case GL_LINE_LOOP: return "Line Loop";
        case GL_LINES_ADJACENCY: return "Line Adjacency";
        case GL_TRIANGLES: return "Triangles";
        case GL_TRIANGLE_STRIP: return "Triangle Strip";
        case GL_TRIANGLES_ADJACENCY: return "Triangle Adjacency";
        case GL_PATCHES: return "Patches";
        default: break;
    }
    return "other";
}

// printLog() //////////////////////////////////////////////////////////////////
//
//  Check for errors from compiling or linking a vertex/fragment/shader program
//      Prints to terminal
//
////////////////////////////////////////////////////////////////////////////////
inline void CSCI441_INTERNAL::ShaderUtils::printLog( GLuint handle ) {
    // check if the handle is to a vertex/fragment shader
    if( glIsShader( handle ) ) {
        printShaderLog(handle);
    }
    // check if the handle is to a shader program
    else if( glIsProgram( handle ) ) {
        printProgramLog(handle);
    }
}

inline void CSCI441_INTERNAL::ShaderUtils::printShaderLog( GLuint shaderHandle ) {
	int status;
    int infologLength = 0;
    int maxLength;

    // check if the handle is to a vertex/fragment shader
    if( glIsShader( shaderHandle ) ) {
        glGetShaderiv(  shaderHandle, GL_INFO_LOG_LENGTH, &maxLength );

        // create a buffer of designated length
		char infoLog[maxLength];
		
		glGetShaderiv( shaderHandle, GL_COMPILE_STATUS, &status );
    	if( sDEBUG ) printf( "[INFO]: |   Shader  Handle %2d: Compile%-26s |\n", shaderHandle, (status == 1 ? "d Successfully" : "r Error") );

        // get the info log for the vertex/tesselation/geometry/fragment/compute shader
        glGetShaderInfoLog(  shaderHandle, maxLength, &infologLength, infoLog );

        if( infologLength > 0 ) {
			// print info to terminal
        	if( sDEBUG ) printf( "[INFO]: |   Shader Handle %d: %s\n", shaderHandle, infoLog );
        }
    } else {
		if( sDEBUG ) fprintf( stderr, "[WARN]: |  Handle %-3d is not for a Shader                        |\n", shaderHandle );
	}
}

inline void CSCI441_INTERNAL::ShaderUtils::printProgramLog( GLuint programHandle ) {
	int status;
    int infologLength = 0;
    int maxLength;

    // check if the handle is to a vertex/fragment shader
    if( glIsProgram( programHandle ) ) {
        glGetProgramiv(  programHandle, GL_INFO_LOG_LENGTH, &maxLength );

        // create a buffer of designated length
		char infoLog[maxLength];
		
		glGetProgramiv( programHandle, GL_LINK_STATUS, &status );
    	if( sDEBUG ) printf("[INFO]: |   Program Handle %2d: Linke%-28s |\n", programHandle, (status == 1 ? "d Successfully" : "r Error") );

        // get the info log for the vertex/tesselation/geometry/fragment/compute shader
        glGetProgramInfoLog(  programHandle, maxLength, &infologLength, infoLog );

        if( infologLength > 0 ) {
			// print info to terminal
        	if( sDEBUG ) printf( "[INFO]: |   Program Handle %d: %s\n", programHandle, infoLog );
        }
    } else {
		if( sDEBUG ) fprintf( stderr, "[WARN]: |  Handle %-3d is not for a Shader Program                |\n", programHandle );
	}
}
inline void CSCI441_INTERNAL::ShaderUtils::printProgramPipelineLog( GLuint pipelineHandle ) {
    int infologLength = 0;
    int maxLength;

    // check if the handle is to a vertex/fragment shader
    if( glIsProgramPipeline( pipelineHandle ) ) {
        glGetProgramPipelineiv(  pipelineHandle, GL_INFO_LOG_LENGTH, &maxLength );

        // create a buffer of designated length
		char infoLog[maxLength];
		
        // get the info log for the vertex/tesselation/geometry/fragment/compute shader
        glGetProgramPipelineInfoLog(  pipelineHandle, maxLength, &infologLength, infoLog );

        if( infologLength > 0 ) {
			// print info to terminal
        	if( sDEBUG ) printf( "[INFO]: |   Pipeline Handle %d: %s\n", pipelineHandle, infoLog );
        }
    } else {
		if( sDEBUG ) fprintf( stderr, "[WARN]: |  Handle %-3d is not for a Shader Program Pipeline       |\n", pipelineHandle );
	}
}

inline GLboolean CSCI441_INTERNAL::ShaderUtils::printSubroutineInfo( GLuint handle, GLenum shaderStage, GLboolean printHeader ) {
	int params, params2;
	int *params3 = NULL;

	glGetProgramStageiv(handle, shaderStage, GL_ACTIVE_SUBROUTINE_UNIFORMS, &params);
	bool headerPrinted = false;
	if( params > 0 ) {
        if( printHeader ) {
            printf( "[INFO]: >--------------------------------------------------------<\n");
            headerPrinted = true;
        }
        printf("[INFO]: | GL_ACTIVE_SUBROUTINE_UNIFORMS (%-15s): %5i |\n", CSCI441_INTERNAL::ShaderUtils::GL_shader_type_to_string(shaderStage), params);
        for(int i = 0; i < params; i++ ) {
            char name[256];
            int max_length = 256;
            int actual_length = 0;

            glGetActiveSubroutineUniformName( handle, shaderStage, i, max_length, &actual_length, name );
            glGetActiveSubroutineUniformiv( handle, shaderStage, i, GL_NUM_COMPATIBLE_SUBROUTINES, &params2 );
            params3 = (int*)malloc(sizeof(int) * params2);
            glGetActiveSubroutineUniformiv( handle, shaderStage, i, GL_COMPATIBLE_SUBROUTINES, params3 );
            GLint loc = glGetSubroutineUniformLocation( handle, shaderStage, name );

            printf("[INFO]: |   %i) name: %-15s #subRoutines: %-5i loc: %2i |\n", i, name, params2, loc );

            for(int j = 0; j < params2; j++ ) {
                GLint idx = params3[j];

                char name2[64];
                int max_length2 = 64;
                int actual_length2 = 0;
                glGetActiveSubroutineName( handle, shaderStage, idx, max_length2, &actual_length2, name2 );

                printf("[INFO]: |     %i) subroutine: %-25s index: %2i |\n", j, name2, idx );
            }

            free(params3);
        }
	}
	return !headerPrinted;
}

[[deprecated("Use printShaderProgramInfo(GLuint, GLboolean, GLboolean, GLboolean, GLboolean, GLboolean, GLboolean, GLboolean)")]]
inline void CSCI441_INTERNAL::ShaderUtils::printShaderProgramInfo( GLuint handle ) {
    printShaderProgramInfo(handle, false, false, false, false, false, false, true);
}

[[deprecated("Use printShaderProgramInfo(GLuint, GLboolean, GLboolean, GLboolean, GLboolean, GLboolean, GLboolean, GLboolean)")]]
inline void CSCI441_INTERNAL::ShaderUtils::printShaderProgramInfo( GLuint handle, GLboolean hasVertexShader, GLboolean hasTessControlShader, GLboolean hasTessEvalShader, GLboolean hasGeometryShader, GLboolean hasFragmentShader, GLboolean useLastNewLine ) {
    printShaderProgramInfo(handle, hasVertexShader, hasTessControlShader, hasTessEvalShader, hasGeometryShader, hasFragmentShader, false, useLastNewLine);
}

inline void CSCI441_INTERNAL::ShaderUtils::printShaderProgramInfo( GLuint handle, GLboolean hasVertexShader, GLboolean hasTessControlShader, GLboolean hasTessEvalShader, GLboolean hasGeometryShader, GLboolean hasFragmentShader, GLboolean hasComputeShader, GLboolean useLastNewLine = true ) {
    GLint major, minor;
    glGetIntegerv(GL_MAJOR_VERSION, &major);
    glGetIntegerv(GL_MINOR_VERSION, &minor);

	int params;

    GLuint shaders[6];
    int max_count = 6;
    int actual_count;
    glGetAttachedShaders( handle, max_count, &actual_count, shaders );
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
                GLint verticesOut, inputType, outputType;
                glGetProgramiv(handle, GL_GEOMETRY_VERTICES_OUT, &verticesOut);
                glGetProgramiv(handle, GL_GEOMETRY_INPUT_TYPE,   &inputType);
                glGetProgramiv(handle, GL_GEOMETRY_OUTPUT_TYPE,  &outputType);

                printf( "[INFO]: >--------------------------------------------------------<\n");
                printf( "[INFO]: | GEOMETRY SHADER PRIMITIVE I/O                          |\n");
                printf( "[INFO]: |   Input Type: %40s |\n", GL_primitive_type_to_string(inputType) );
                printf( "[INFO]: |   Output Type: %39s |\n", GL_primitive_type_to_string(outputType) );
                printf( "[INFO]: |   Max Vertices Out: %34d |\n", verticesOut );
            }
        }
    }

    if(hasVertexShader) {
        glGetProgramiv( handle, GL_ACTIVE_ATTRIBUTES, &params );
        if( params > 0 ) {
            if( sDEBUG ) printf( "[INFO]: >--------------------------------------------------------<\n");
            if( sDEBUG ) printf( "[INFO]: | GL_ACTIVE_ATTRIBUTES: %32i |\n", params );
            for( int i = 0; i < params; i++ ) {
                char name[64];
                int max_length = 64;
                int actual_length = 0;
                int size = 0;
                GLenum type;
                glGetActiveAttrib( handle, i, max_length, &actual_length, &size, &type, name );
                if( size > 1 ) {
                    for( int j = 0; j < size; j++ ) {
                        char long_name[64];
                        sprintf( long_name, "%s[%i]", name, j );
                        int location = glGetAttribLocation( handle, long_name );
                        if( sDEBUG ) printf( "[INFO]: |   %i) type: %-15s name: %-13s loc: %2i |\n", i, GLSL_type_to_string( type ), long_name, location );
                    }
                } else {
                    int location = glGetAttribLocation( handle, name );
                    if( sDEBUG ) printf( "[INFO]: |   %i) type: %-15s name: %-13s loc: %2i |\n",i, GLSL_type_to_string( type ), name, location );
                }
            }
        }
    }

    glGetProgramiv(handle, GL_ACTIVE_UNIFORMS, &params);
    if( params > 0 ) {
        if( sDEBUG ) printf( "[INFO]: >--------------------------------------------------------<\n" );
        if( sDEBUG ) printf("[INFO]: | GL_ACTIVE_UNIFORMS: %34i |\n", params);
        for(int i = 0; i < params; i++) {
            char name[64];
            int max_length = 64;
            int actual_length = 0;
            int size = 0;
            GLenum type;
            glGetActiveUniform( handle, i, max_length, &actual_length, &size, &type, name );
            if(size > 1) {
                for(int j = 0; j < size; j++) {
                    char long_name[64];
                    sprintf(long_name, "%s[%i]", name, j);
                    int location = glGetUniformLocation(handle, long_name);
                    if(location != -1) {
                        if (sDEBUG) printf("[INFO]: |  %2i) type: %-15s name: %-13s loc: %2i |\n", i, GLSL_type_to_string(type), long_name, location);
                    }
                }
            } else {
                int location = glGetUniformLocation(handle, name);
                if(location != -1) {
                    if (sDEBUG) printf("[INFO]: |  %2i) type: %-15s name: %-13s loc: %2i |\n",i, GLSL_type_to_string(type), name, location);
                }
            }
        }
    }

    int vsCount, tcsCount, tesCount, gsCount, fsCount, csCount;
    vsCount = tcsCount = tesCount = gsCount = fsCount = csCount = 0;

    glGetProgramiv(handle, GL_ACTIVE_UNIFORM_BLOCKS, &params);
    if( params > 0 ) {
        if( sDEBUG ) printf( "[INFO]: >--------------------------------------------------------<\n");
        if( sDEBUG ) printf("[INFO]: | GL_UNIFORM_BLOCK_ACTIVE_UNIFORMS: %20d |\n", params);
        for(int i = 0; i < params; i++ ) {
            int params2;
            glGetActiveUniformBlockiv(handle, i, GL_UNIFORM_BLOCK_ACTIVE_UNIFORMS, &params2 );

            int actualLen;
            glGetActiveUniformBlockiv(handle, i, GL_UNIFORM_BLOCK_NAME_LENGTH, &actualLen);
            char *name = (char *)malloc(sizeof(char) * actualLen);
            glGetActiveUniformBlockName(handle, i, actualLen, NULL, name);

            GLuint *indices = (GLuint*)malloc(params2*sizeof(GLuint));
            glGetActiveUniformBlockiv( handle, i, GL_UNIFORM_BLOCK_ACTIVE_UNIFORM_INDICES, (GLint*)indices);

            GLint *offsets = (GLint*)malloc(params2*sizeof(GLint));
            glGetActiveUniformsiv(handle, params2, indices, GL_UNIFORM_OFFSET, offsets);

            if( sDEBUG ) printf("[INFO]: | %d) %-34s   # Uniforms: %2d |\n", i, name, params2);

            GLint vs, tcs, tes, gs, fs, cs;
            glGetActiveUniformBlockiv( handle, i, GL_UNIFORM_BLOCK_REFERENCED_BY_VERTEX_SHADER, &vs);			if( vs ) vsCount++;
            glGetActiveUniformBlockiv( handle, i, GL_UNIFORM_BLOCK_REFERENCED_BY_TESS_CONTROL_SHADER, &tcs);	if( tcs) tcsCount++;
            glGetActiveUniformBlockiv( handle, i, GL_UNIFORM_BLOCK_REFERENCED_BY_TESS_EVALUATION_SHADER, &tes);	if( tes) tesCount++;
            glGetActiveUniformBlockiv( handle, i, GL_UNIFORM_BLOCK_REFERENCED_BY_GEOMETRY_SHADER, &gs);			if( gs ) gsCount++;
            glGetActiveUniformBlockiv( handle, i, GL_UNIFORM_BLOCK_REFERENCED_BY_FRAGMENT_SHADER, &fs);			if( fs ) fsCount++;
            glGetActiveUniformBlockiv( handle, i, GL_UNIFORM_BLOCK_REFERENCED_BY_COMPUTE_SHADER, &cs);			if( cs ) csCount++;
            if( sDEBUG ) printf("[INFO]: |   Used in: %-4s %-4s %-4s %-3s %-4s %-4s      Shader(s) |\n", (vs ? "Vert" : ""), (tcs ? "Ctrl" : ""), (tes ? "Eval" : ""), (gs ? "Geo" : ""), (fs ? "Frag" : ""), (cs ? "Comp" : ""));

            int maxUniLength;
            glGetProgramiv(handle, GL_ACTIVE_UNIFORM_MAX_LENGTH, &maxUniLength);
            char *name2 = (char *)malloc(sizeof(char) * maxUniLength);
            for(int j = 0; j < params2; j++) {
                GLenum type;
                int uniSize;
                glGetActiveUniform(handle, indices[j], maxUniLength, &actualLen, &uniSize, &type, name2);

                if( sDEBUG ) {
                    printf("[INFO]: |  %2d) type: %-15s name: %-21s |\n", j, GLSL_type_to_string(type), name2);
                    printf("[INFO]: |      uniform index: %3d    offset: %4d                |\n", indices[j], offsets[j]);
                }
            }
        }

        if( vsCount + tcsCount + tesCount + gsCount + fsCount + csCount > 0 ) {
            GLint maxUniBlocks = 0;
            glGetIntegerv( GL_MAX_COMBINED_UNIFORM_BLOCKS, &maxUniBlocks );
            if( sDEBUG ) printf( "[INFO]: | Shader Uniform Block Counts                     %2d/%2d  |\n", params, maxUniBlocks);
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

    if( sDEBUG ) {
        if((major == 4 && minor >= 3) || major > 4) {
            GLint params[1];
            glGetProgramInterfaceiv(handle, GL_SHADER_STORAGE_BLOCK, GL_ACTIVE_RESOURCES, params);
            if(params[0] > 0) {
                GLint maxLen;
                glGetProgramInterfaceiv(handle, GL_SHADER_STORAGE_BLOCK, GL_MAX_NAME_LENGTH, &maxLen);
                GLchar *ssboName = (GLchar*)malloc(sizeof(GLchar)*maxLen);
                GLsizei ssboNameLen;

                const int NUM_PROPS = 7;
                GLenum props[NUM_PROPS] = {GL_BUFFER_BINDING,
                                           GL_REFERENCED_BY_VERTEX_SHADER,
                                           GL_REFERENCED_BY_TESS_CONTROL_SHADER, GL_REFERENCED_BY_TESS_EVALUATION_SHADER,
                                           GL_REFERENCED_BY_GEOMETRY_SHADER,
                                           GL_REFERENCED_BY_FRAGMENT_SHADER,
                                           GL_REFERENCED_BY_COMPUTE_SHADER};
                GLsizei numWritten;
                GLint results[NUM_PROPS];

                int vSSB, teSSB, tcSSB, gSSB, fSSB, cSSB;
                vSSB = teSSB = tcSSB = gSSB = fSSB = cSSB = 0;

                printf( "[INFO]: >--------------------------------------------------------<\n");
                printf( "[INFO]: | GL_SHADER_STORAGE_BLOCK: %29d |\n", params[0] );
                for(int i = 0; i < params[0]; i++) {
                    glGetProgramResourceName(handle, GL_SHADER_STORAGE_BLOCK, i, maxLen, &ssboNameLen, ssboName);
                    GLuint ssboIndex = glGetProgramResourceIndex(handle, GL_SHADER_STORAGE_BLOCK, ssboName);
                    glGetProgramResourceiv(handle, GL_SHADER_STORAGE_BLOCK, i, NUM_PROPS, props, NUM_PROPS, &numWritten, results);

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
                printf( "[INFO]: | Shader Storage Block Counts:                   %2d/%2d   |\n", params[0], maxSSBCounters );
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
            }
        }

        if((major == 4 && minor >= 2) || major > 4) {
            GLint params[1];
            glGetProgramInterfaceiv(handle, GL_ATOMIC_COUNTER_BUFFER, GL_ACTIVE_RESOURCES, params);
            if(params[0] > 0) {
                GLint maxLen;
                glGetProgramInterfaceiv(handle, GL_ATOMIC_COUNTER_BUFFER, GL_MAX_NAME_LENGTH, &maxLen);
                GLchar *atomicName = (GLchar*)malloc(sizeof(GLchar)*maxLen);
                GLsizei atomicNameLen;

                const int NUM_PROPS = 8;
                GLenum props[NUM_PROPS] = {GL_BUFFER_BINDING,
                                           GL_REFERENCED_BY_VERTEX_SHADER,
                                           GL_REFERENCED_BY_TESS_CONTROL_SHADER,
                                           GL_REFERENCED_BY_TESS_EVALUATION_SHADER,
                                           GL_REFERENCED_BY_GEOMETRY_SHADER,
                                           GL_REFERENCED_BY_FRAGMENT_SHADER,
                                           GL_REFERENCED_BY_COMPUTE_SHADER,
                                           GL_BUFFER_DATA_SIZE};
                GLsizei numWritten;
                GLint results[NUM_PROPS];

                printf( "[INFO]: >--------------------------------------------------------<\n");
                printf( "[INFO]: | GL_ATOMIC_COUNTER_BUFFER: %28d |\n", params[0] );

                int vAC, teAC, tcAC, gAC, fAC, cAC;
                vAC = teAC = tcAC = gAC = fAC = cAC = 0;

                GLint numUniforms;
                glGetProgramiv(handle, GL_ACTIVE_UNIFORMS, &numUniforms);
                for(int j = 0; j < numUniforms; j++) {
                    int size = 0;
                    GLenum type;
                    glGetActiveUniform( handle, j, maxLen, &atomicNameLen, &size, &type, atomicName );

                    GLuint atomicIndex = glGetProgramResourceIndex(handle, GL_UNIFORM, atomicName);

                    GLenum atomicProps[1] = {GL_ATOMIC_COUNTER_BUFFER_INDEX};
                    GLint atomicResults[1];
                    glGetProgramResourceiv(handle, GL_UNIFORM, atomicIndex, 1, atomicProps, 1, nullptr, atomicResults);

                    if(atomicResults[0] != -1) {
                        glGetProgramResourceiv(handle, GL_ATOMIC_COUNTER_BUFFER, atomicResults[0], NUM_PROPS, props, NUM_PROPS, &numWritten, results);

                        GLint offset;
                        glGetActiveUniformsiv(handle, 1, &atomicIndex, GL_UNIFORM_OFFSET, &offset);

                        printf( "[INFO]: | %3d) type: %-15s name: %-21s |\n", atomicResults[0], GLSL_type_to_string(type), atomicName );
                        printf( "[INFO]: |      uniform index: %3d    atomic index: %3d           |\n", atomicIndex, atomicResults[0] );
                        printf( "[INFO]: |      binding: %3d   offset: %3d   buffer size: %4d    |\n", results[0], offset, results[7] );
                        printf( "[INFO]: |   Used in: %-4s %-4s %-4s %-3s %-4s %-4s      Shader(s) |\n", (results[1] ? "Vert" : ""), (results[2] ? "Ctrl" : ""), (results[3] ? "Eval" : ""), (results[4] ? "Geo" : ""), (results[5] ? "Frag" : ""), (results[6] ? "Comp" : ""));

                        if(results[1]) vAC++;
                        if(results[2]) teAC++;
                        if(results[3]) tcAC++;
                        if(results[4]) gAC++;
                        if(results[5]) fAC++;
                        if(results[6]) cAC++;
                    }
                }

                GLint maxAtomicCounters = 0;
                glGetIntegerv( GL_MAX_COMBINED_ATOMIC_COUNTERS, &maxAtomicCounters );
                printf( "[INFO]: | Atomic Counter Counts:                     %4d/%4d   |\n", params[0], maxAtomicCounters );
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
            if( hasVertexShader   )     printHeader = printSubroutineInfo( handle, GL_VERTEX_SHADER, printHeader );
            if( hasTessControlShader)   printHeader = printSubroutineInfo( handle, GL_TESS_CONTROL_SHADER, printHeader );
            if( hasTessEvalShader)      printHeader = printSubroutineInfo( handle, GL_TESS_EVALUATION_SHADER, printHeader );
            if( hasGeometryShader )     printHeader = printSubroutineInfo( handle, GL_GEOMETRY_SHADER, printHeader );
            if( hasFragmentShader )     printHeader = printSubroutineInfo( handle, GL_FRAGMENT_SHADER, printHeader );
            if( hasComputeShader )      printHeader = printSubroutineInfo( handle, GL_COMPUTE_SHADER, printHeader );
        }
    }

    if(useLastNewLine) printf( "[INFO]: \\--------------------------------------------------------/\n\n");
}

// compileShader() ///////////////////////////////////////////////////////////////
//
//  Compile a given shader program
//
////////////////////////////////////////////////////////////////////////////////
inline GLuint CSCI441_INTERNAL::ShaderUtils::compileShader( const char *filename, GLenum shaderType ) {
	GLuint shaderHandle = 0;
	char *shaderString;

    /* create a handle to our shader */
	shaderHandle = glCreateShader( shaderType );

    /* read in each text file and store the contents in a string */
    if( readTextFromFile( filename, shaderString ) ) {

		/* send the contents of each program to the GPU */
		glShaderSource( shaderHandle, 1, (const char**)&shaderString, NULL );

		/* we are good programmers so free up the memory used by each buffer */
		delete [] shaderString;

		/* compile each shader on the GPU */
		glCompileShader( shaderHandle );

		/* check the shader log */
		printLog( shaderHandle );

		/* return the handle of our shader */
		return shaderHandle;
	} else {
		return -1;
	}
}

#endif // __CSCI441_SHADEREUTILS_H__
