/**
 * @file OpenGLUtils.hpp
 * @brief Helper functions to work with OpenGL 3.0+
 * @author Dr. Jeffrey Paone
 *
 * @copyright MIT License Copyright (c) 2017 Dr. Jeffrey Paone
 *
 * These functions, classes, and constants help minimize common
 * code that needs to be written.
 *
 * @warning NOTE: This header file depends upon GLEW
 * @warning NOTE: This header file depends upon glm
 */

#ifndef CSCI441_OPENGL_UTILS_H
#define CSCI441_OPENGL_UTILS_H

#include <GL/glew.h>
#include <glm/glm.hpp>
#include <cstdio>      // for printf()
#include <cstdlib>     // for atoi()

//**********************************************************************************

/// \namespace CSCI441
/// \desc CSCI441 Helper Functions for OpenGL
namespace CSCI441 {
    /// \desc constant for positive X_AXIS
    static const glm::vec3 X_AXIS( 1.0f, 0.0f, 0.0f );
    /// \desc constant for positive Y_AXIS
    static const glm::vec3 Y_AXIS( 0.0f, 1.0f, 0.0f );
    /// \desc constant for positive Z_AXIS
    static const glm::vec3 Z_AXIS( 0.0f, 0.0f, 1.0f );
    /// \desc alias for constant for positive X_AXIS
    static const glm::vec3 X_AXIS_POS = X_AXIS;
    /// \desc alias for constant for positive Y_AXIS
    static const glm::vec3 Y_AXIS_POS = Y_AXIS;
    /// \desc alias for constant for positive Z_AXIS
    static const glm::vec3 Z_AXIS_POS = Z_AXIS;
    /// \desc constant for negative X_AXIS
    static const glm::vec3 X_AXIS_NEG( -1.0f,  0.0f,  0.0f );
    /// \desc constant for negative Y_AXIS
    static const glm::vec3 Y_AXIS_NEG(  0.0f, -1.0f,  0.0f );
    /// \desc constant for negative Z_AXIS
    static const glm::vec3 Z_AXIS_NEG(  0.0f,  0.0f, -1.0f );

    /// \namespace OpenGLUtils
    /// \desc contains OpenGL Utility functions
    namespace OpenGLUtils {
        /// \desc Prints information about our OpenGL context
        void printOpenGLInfo();
  	};

}

//**********************************************************************************
//**********************************************************************************
// Internal definitions

namespace CSCI441_INTERNAL {
  void printOpenGLParamHeader(int MAJOR, int MINOR );
  void printOpenGLParamIndexed(const char *FORMAT, GLenum name, GLuint index );
  void printOpenGLParam(const char *FORMAT, GLenum name );
  void printOpenGLParam2(const char *FORMAT, GLenum name );
  void printOpenGLParam3(const char *FORMAT, GLenum name );
  void printOpenGLParam4(const char *FORMAT, GLenum name );
}

//**********************************************************************************
//**********************************************************************************
// Outward facing function implementations

inline void CSCI441::OpenGLUtils::printOpenGLInfo() {
    GLint major, minor;
    glGetIntegerv(GL_MAJOR_VERSION, &major);
    glGetIntegerv(GL_MINOR_VERSION, &minor);

	fprintf( stdout, "\n[INFO]: /--------------------------------------------------------\\\n" );
	fprintf( stdout, "[INFO]: | OpenGL Information                                     |\n" );
	fprintf( stdout, "[INFO]: |--------------------------------------------------------|\n" );
	fprintf( stdout, "[INFO]: |   OpenGL Version:  %35s |\n", glGetString(GL_VERSION) );
	fprintf( stdout, "[INFO]: |   OpenGL Renderer: %35s |\n", glGetString(GL_RENDERER) );
	fprintf( stdout, "[INFO]: |   OpenGL Vendor:   %35s |\n", glGetString(GL_VENDOR) );
	fprintf( stdout, "[INFO]: |   Shading Version: %35s |\n", glGetString(GL_SHADING_LANGUAGE_VERSION) );

	if( (major >= 2 && minor >= 0) || major > 2 ) {
		CSCI441_INTERNAL::printOpenGLParamHeader( 2, 0 );
		if(major == 2) {
            CSCI441_INTERNAL::printOpenGLParam( "[INFO]: |   Max # Lights:    %35d |\n",                         GL_MAX_LIGHTS );
        }
		CSCI441_INTERNAL::printOpenGLParam( "[INFO]: |   Max # Color Attachments:  %26d |\n", 			    			GL_MAX_COLOR_ATTACHMENTS );
	}

	if( (major >= 2 && minor >= 1) || major > 2 ) {
		CSCI441_INTERNAL::printOpenGLParamHeader( 2, 1 );
		CSCI441_INTERNAL::printOpenGLParam( "[INFO]: |   Max # Vertex Attributes:  %26d |\n", 					    	GL_MAX_VERTEX_ATTRIBS );
		CSCI441_INTERNAL::printOpenGLParam( "[INFO]: |   Max # Vertex Uniforms:  %28d |\n", 							GL_MAX_VERTEX_UNIFORM_COMPONENTS );
		CSCI441_INTERNAL::printOpenGLParam( "[INFO]: |   Max # Vertex Textures:  %28d |\n", 							GL_MAX_VERTEX_TEXTURE_IMAGE_UNITS );
		CSCI441_INTERNAL::printOpenGLParam( "[INFO]: |   Max # Vertex Outputs:  %29d |\n", 						    	GL_MAX_VERTEX_OUTPUT_COMPONENTS );
		CSCI441_INTERNAL::printOpenGLParam( "[INFO]: |   Max # Fragment Inputs:  %28d |\n", 							GL_MAX_FRAGMENT_INPUT_COMPONENTS );
		CSCI441_INTERNAL::printOpenGLParam( "[INFO]: |   Max # Fragment Uniforms:  %26d |\n", 					    	GL_MAX_FRAGMENT_UNIFORM_COMPONENTS );
		CSCI441_INTERNAL::printOpenGLParam( "[INFO]: |   Max # Fragment Textures:  %26d |\n", 					    	GL_MAX_TEXTURE_IMAGE_UNITS );
		CSCI441_INTERNAL::printOpenGLParam( "[INFO]: |   Max # Draw Buffers:  %31d |\n", 								GL_MAX_DRAW_BUFFERS );
		CSCI441_INTERNAL::printOpenGLParam( "[INFO]: |   Max # Textures Combined:  %26d |\n", 					    	GL_MAX_COMBINED_TEXTURE_IMAGE_UNITS );
	}

	if( (major >= 3 && minor >= 0) || major > 3 ) {
		CSCI441_INTERNAL::printOpenGLParamHeader( 3, 0 );
		CSCI441_INTERNAL::printOpenGLParam( "[INFO]: |   Max # Transform Feedback Buffers:  %17d |\n", 			    	GL_MAX_TRANSFORM_FEEDBACK_BUFFERS );
		CSCI441_INTERNAL::printOpenGLParam( "[INFO]: |   Max # Transform Separate Attributes:  %14d |\n", 		    	GL_MAX_TRANSFORM_FEEDBACK_SEPARATE_ATTRIBS );
		CSCI441_INTERNAL::printOpenGLParam( "[INFO]: |   Max # Transform Separate Components:  %14d |\n", 		    	GL_MAX_TRANSFORM_FEEDBACK_SEPARATE_COMPONENTS );
		CSCI441_INTERNAL::printOpenGLParam( "[INFO]: |   Max # Transform Interleaved Buffers:  %14d |\n", 		    	GL_MAX_TRANSFORM_FEEDBACK_INTERLEAVED_COMPONENTS );
	}

	if( (major >= 3 && minor >= 1) || major > 3 ) {
		CSCI441_INTERNAL::printOpenGLParamHeader( 3, 1 );
		CSCI441_INTERNAL::printOpenGLParam( "[INFO]: |   Max # Fragment Uniform Blocks:  %20d |\n", 					GL_MAX_FRAGMENT_UNIFORM_BLOCKS );
		CSCI441_INTERNAL::printOpenGLParam( "[INFO]: |   Max # Vertex Uniform Blocks:  %22d |\n", 					    GL_MAX_VERTEX_UNIFORM_BLOCKS );
		CSCI441_INTERNAL::printOpenGLParam( "[INFO]: |   Max Uniform Blocks Size:  %20d bytes |\n", 					GL_MAX_UNIFORM_BLOCK_SIZE );
		CSCI441_INTERNAL::printOpenGLParam( "[INFO]: |   Max # Combined Uniform Blocks:  %20d |\n", 					GL_MAX_COMBINED_UNIFORM_BLOCKS );
		CSCI441_INTERNAL::printOpenGLParam( "[INFO]: |   Max # Uniform Bindings:  %27d |\n", 							GL_MAX_UNIFORM_BUFFER_BINDINGS );
	}

	if( (major >= 3 && minor >= 2) || major > 3 ) {
		CSCI441_INTERNAL::printOpenGLParamHeader( 3, 2 );
		CSCI441_INTERNAL::printOpenGLParam( "[INFO]: |   Max # Geometry Uniforms:  %26d |\n", 					    	GL_MAX_GEOMETRY_UNIFORM_COMPONENTS );
		CSCI441_INTERNAL::printOpenGLParam( "[INFO]: |   Max # Geometry Uniform Blocks:  %20d |\n", 					GL_MAX_GEOMETRY_UNIFORM_BLOCKS );
		CSCI441_INTERNAL::printOpenGLParam( "[INFO]: |   Max # Geometry Textures:  %26d |\n", 					    	GL_MAX_GEOMETRY_TEXTURE_IMAGE_UNITS );
		CSCI441_INTERNAL::printOpenGLParam( "[INFO]: |   Max # Geometry Inputs:  %28d |\n", 							GL_MAX_GEOMETRY_INPUT_COMPONENTS );
		CSCI441_INTERNAL::printOpenGLParam( "[INFO]: |   Max # Geometry Output Vertices:  %19d |\n", 					GL_MAX_GEOMETRY_OUTPUT_VERTICES );
		CSCI441_INTERNAL::printOpenGLParam( "[INFO]: |   Max # Geometry Total Output Components:  %11d |\n", 			GL_MAX_GEOMETRY_TOTAL_OUTPUT_COMPONENTS );
		CSCI441_INTERNAL::printOpenGLParam( "[INFO]: |   Max # Geometry Outputs:  %27d |\n", 							GL_MAX_GEOMETRY_OUTPUT_COMPONENTS );
	}

	if( (major >= 4 && minor >= 0) || major > 4 ) {
		CSCI441_INTERNAL::printOpenGLParamHeader( 4, 0 );
		CSCI441_INTERNAL::printOpenGLParam( "[INFO]: |   Max # Patch Vertices:  %29d |\n", 						    	GL_MAX_PATCH_VERTICES );
		CSCI441_INTERNAL::printOpenGLParam( "[INFO]: |   Max # Tessellation Level:  %25d |\n", 					    	GL_MAX_TESS_GEN_LEVEL );
		CSCI441_INTERNAL::printOpenGLParam4("[INFO]: |   Default Tessellation Outer Levels:  %7d %2d %2d %2d |\n",   	GL_PATCH_DEFAULT_OUTER_LEVEL );
		CSCI441_INTERNAL::printOpenGLParam2("[INFO]: |   Default Tessellation Inner Levels:  %13d %2d |\n", 			GL_PATCH_DEFAULT_INNER_LEVEL );
		CSCI441_INTERNAL::printOpenGLParam( "[INFO]: |   Max # Tess Control Inputs:  %24d |\n", 						GL_MAX_GEOMETRY_INPUT_COMPONENTS );
		CSCI441_INTERNAL::printOpenGLParam( "[INFO]: |   Max # Tess Control Uniforms:  %22d |\n", 					    GL_MAX_TESS_CONTROL_UNIFORM_COMPONENTS );
		CSCI441_INTERNAL::printOpenGLParam( "[INFO]: |   Max # Tess Control Uniform Blocks:  %16d |\n", 				GL_MAX_TESS_CONTROL_UNIFORM_BLOCKS );
		CSCI441_INTERNAL::printOpenGLParam( "[INFO]: |   Max # Tess Control Textures:  %22d |\n", 					    GL_MAX_TESS_CONTROL_TEXTURE_IMAGE_UNITS );
		CSCI441_INTERNAL::printOpenGLParam( "[INFO]: |   Max # Tess Control Outputs:  %23d |\n", 						GL_MAX_TESS_CONTROL_OUTPUT_COMPONENTS );
		CSCI441_INTERNAL::printOpenGLParam( "[INFO]: |   Max # Tess Evaluation Inputs:  %21d |\n", 					    GL_MAX_TESS_EVALUATION_INPUT_COMPONENTS );
		CSCI441_INTERNAL::printOpenGLParam( "[INFO]: |   Max # Tess Evaluation Uniforms:  %19d |\n", 					GL_MAX_TESS_EVALUATION_UNIFORM_COMPONENTS );
		CSCI441_INTERNAL::printOpenGLParam( "[INFO]: |   Max # Tess Evaluation Uniform Blocks:  %13d |\n", 		    	GL_MAX_TESS_EVALUATION_UNIFORM_BLOCKS );
		CSCI441_INTERNAL::printOpenGLParam( "[INFO]: |   Max # Tess Evaluation Textures:  %19d |\n", 					GL_MAX_TESS_EVALUATION_TEXTURE_IMAGE_UNITS );
		CSCI441_INTERNAL::printOpenGLParam( "[INFO]: |   Max # Tess Evaluation Outputs:  %20d |\n", 					GL_MAX_TESS_EVALUATION_OUTPUT_COMPONENTS );
		CSCI441_INTERNAL::printOpenGLParam( "[INFO]: |   Max # Geometry Invocations:  %23d |\n", 				    	GL_MAX_GEOMETRY_SHADER_INVOCATIONS );
		CSCI441_INTERNAL::printOpenGLParam( "[INFO]: |   Max # Vertex Streams:  %29d |\n", 						    	GL_MAX_VERTEX_STREAMS );
	}

	if( (major >= 4 && minor >= 2) || major > 4 ) {
		CSCI441_INTERNAL::printOpenGLParamHeader( 4, 2 );
		CSCI441_INTERNAL::printOpenGLParam( "[INFO]: |   Max # Vertex Atomic Counters:  %21d |\n", 				    	GL_MAX_VERTEX_ATOMIC_COUNTERS );
		CSCI441_INTERNAL::printOpenGLParam( "[INFO]: |   Max # Tess Control Atomic Counters:  %15d |\n", 				GL_MAX_TESS_CONTROL_ATOMIC_COUNTERS );
		CSCI441_INTERNAL::printOpenGLParam( "[INFO]: |   Max # Tess Evaluation Atomic Counters:  %12d |\n", 			GL_MAX_TESS_EVALUATION_ATOMIC_COUNTERS );
		CSCI441_INTERNAL::printOpenGLParam( "[INFO]: |   Max # Geometry Atomic Counters:  %19d |\n", 					GL_MAX_GEOMETRY_ATOMIC_COUNTERS );
		CSCI441_INTERNAL::printOpenGLParam( "[INFO]: |   Max # Fragment Atomic Counters:  %19d |\n", 					GL_MAX_FRAGMENT_ATOMIC_COUNTERS );
		CSCI441_INTERNAL::printOpenGLParam( "[INFO]: |   Max # Combined Atomic Counters:  %19d |\n", 					GL_MAX_COMBINED_ATOMIC_COUNTERS );
		CSCI441_INTERNAL::printOpenGLParam( "[INFO]: |   Max # Vertex Atomic Counter Buffers:  %14d |\n", 		    	GL_MAX_VERTEX_ATOMIC_COUNTER_BUFFERS );
		CSCI441_INTERNAL::printOpenGLParam( "[INFO]: |   Max # Tess Control Atomic Counter Buffers:  %8d |\n", 	    	GL_MAX_TESS_CONTROL_ATOMIC_COUNTER_BUFFERS );
		CSCI441_INTERNAL::printOpenGLParam( "[INFO]: |   Max # Tess Evaluation Atomic Counter Buffers:  %5d |\n",   	GL_MAX_TESS_EVALUATION_ATOMIC_COUNTER_BUFFERS );
		CSCI441_INTERNAL::printOpenGLParam( "[INFO]: |   Max # Geometry Atomic Counter Buffers:  %12d |\n", 			GL_MAX_GEOMETRY_ATOMIC_COUNTER_BUFFERS );
		CSCI441_INTERNAL::printOpenGLParam( "[INFO]: |   Max # Fragment Atomic Counter Buffers:  %12d |\n", 			GL_MAX_FRAGMENT_ATOMIC_COUNTER_BUFFERS );
		CSCI441_INTERNAL::printOpenGLParam( "[INFO]: |   Max # Combined Atomic Counter Buffers:  %12d |\n", 			GL_MAX_COMBINED_ATOMIC_COUNTER_BUFFERS );
		CSCI441_INTERNAL::printOpenGLParam( "[INFO]: |   Max # Atomic Counter Buffer Bindings:  %13d |\n", 		    	GL_MAX_ATOMIC_COUNTER_BUFFER_BINDINGS );
		CSCI441_INTERNAL::printOpenGLParam( "[INFO]: |   Max # Vertex Image Uniforms:  %22d |\n", 				    	GL_MAX_VERTEX_IMAGE_UNIFORMS );
		CSCI441_INTERNAL::printOpenGLParam( "[INFO]: |   Max # Tess Control Image Uniforms:  %16d |\n", 				GL_MAX_TESS_CONTROL_IMAGE_UNIFORMS );
		CSCI441_INTERNAL::printOpenGLParam( "[INFO]: |   Max # Tess Evaluation Image Uniforms:  %13d |\n", 		    	GL_MAX_TESS_EVALUATION_IMAGE_UNIFORMS );
		CSCI441_INTERNAL::printOpenGLParam( "[INFO]: |   Max # Geometry Image Uniforms:  %20d |\n", 					GL_MAX_GEOMETRY_IMAGE_UNIFORMS );
		CSCI441_INTERNAL::printOpenGLParam( "[INFO]: |   Max # Fragment Image Uniforms:  %20d |\n", 					GL_MAX_FRAGMENT_IMAGE_UNIFORMS );
		CSCI441_INTERNAL::printOpenGLParam( "[INFO]: |   Max # Combined Image Uniforms:  %20d |\n", 					GL_MAX_IMAGE_UNITS );
		CSCI441_INTERNAL::printOpenGLParam( "[INFO]: |   Max # Shader Storage Buffer Bindings:  %13d |\n", 		    	GL_MAX_SHADER_STORAGE_BUFFER_BINDINGS );
	}

	if( (major >= 4 && minor >= 3) || major > 4 ) {
		CSCI441_INTERNAL::printOpenGLParamHeader( 4, 3 );
		CSCI441_INTERNAL::printOpenGLParam( "[INFO]: |   Max # Compute Uniforms:  %27d |\n", 							GL_MAX_COMPUTE_UNIFORM_COMPONENTS );
		CSCI441_INTERNAL::printOpenGLParam( "[INFO]: |   Max # Compute Uniform Blocks:  %21d |\n", 					    GL_MAX_COMPUTE_UNIFORM_BLOCKS );
		CSCI441_INTERNAL::printOpenGLParam( "[INFO]: |   Max # Compute Textures:  %27d |\n", 							GL_MAX_COMPUTE_TEXTURE_IMAGE_UNITS );
		CSCI441_INTERNAL::printOpenGLParam( "[INFO]: |   Max # Compute Image Uniforms:  %21d |\n", 						GL_MAX_COMPUTE_IMAGE_UNIFORMS );
		CSCI441_INTERNAL::printOpenGLParam( "[INFO]: |   Max # Compute Atomic Counters:  %20d |\n", 					GL_MAX_COMPUTE_ATOMIC_COUNTERS );
		CSCI441_INTERNAL::printOpenGLParam( "[INFO]: |   Max # Compute Atomic Counter Buffers:  %13d |\n",				GL_MAX_COMPUTE_ATOMIC_COUNTER_BUFFERS );

		CSCI441_INTERNAL::printOpenGLParamIndexed("[INFO]: |   Max # Work Groups Per Dispatch: %6d", 					GL_MAX_COMPUTE_WORK_GROUP_COUNT, 0 );
		CSCI441_INTERNAL::printOpenGLParamIndexed(" %6d", 																GL_MAX_COMPUTE_WORK_GROUP_COUNT, 1 );
		CSCI441_INTERNAL::printOpenGLParamIndexed(" %6d |\n", 															GL_MAX_COMPUTE_WORK_GROUP_COUNT, 2 );

		CSCI441_INTERNAL::printOpenGLParamIndexed("[INFO]: |   Max Work Groups Size: %16d", 							GL_MAX_COMPUTE_WORK_GROUP_SIZE, 0 );
		CSCI441_INTERNAL::printOpenGLParamIndexed(" %6d", 																GL_MAX_COMPUTE_WORK_GROUP_SIZE, 1 );
		CSCI441_INTERNAL::printOpenGLParamIndexed(" %6d |\n", 															GL_MAX_COMPUTE_WORK_GROUP_SIZE, 2 );

		CSCI441_INTERNAL::printOpenGLParam( "[INFO]: |   Max # Invocations Per Work Group: %18d |\n", 					GL_MAX_COMPUTE_WORK_GROUP_INVOCATIONS );
		CSCI441_INTERNAL::printOpenGLParam( "[INFO]: |   Max Total Storage Size: %22d bytes |\n", 						GL_MAX_COMPUTE_SHARED_MEMORY_SIZE );
		CSCI441_INTERNAL::printOpenGLParam( "[INFO]: |   Max # Vertex Shader Storage Blocks:  %15d |\n", 				GL_MAX_VERTEX_SHADER_STORAGE_BLOCKS );
		CSCI441_INTERNAL::printOpenGLParam( "[INFO]: |   Max # Tess Control Shader Storage Blocks:  %9d |\n", 			GL_MAX_TESS_CONTROL_SHADER_STORAGE_BLOCKS );
		CSCI441_INTERNAL::printOpenGLParam( "[INFO]: |   Max # Tess Evaluation Shader Storage Blocks:  %6d |\n", 		GL_MAX_TESS_EVALUATION_SHADER_STORAGE_BLOCKS );
		CSCI441_INTERNAL::printOpenGLParam( "[INFO]: |   Max # Geometry Shader Storage Blocks:  %13d |\n", 				GL_MAX_GEOMETRY_SHADER_STORAGE_BLOCKS );
		CSCI441_INTERNAL::printOpenGLParam( "[INFO]: |   Max # Fragment Shader Storage Blocks:  %13d |\n", 				GL_MAX_FRAGMENT_SHADER_STORAGE_BLOCKS );
		CSCI441_INTERNAL::printOpenGLParam( "[INFO]: |   Max # Compute Shader Storage Blocks:  %14d |\n", 				GL_MAX_COMPUTE_SHADER_STORAGE_BLOCKS );
		CSCI441_INTERNAL::printOpenGLParam( "[INFO]: |   Max # Combined Shader Storage Blocks:  %13d |\n", 				GL_MAX_COMBINED_SHADER_STORAGE_BLOCKS );
		CSCI441_INTERNAL::printOpenGLParam( "[INFO]: |   Max # Combined Shader Output Resources:  %11d |\n", 			GL_MAX_COMBINED_SHADER_OUTPUT_RESOURCES );
	}

	fprintf( stdout, "[INFO]: \\--------------------------------------------------------/\n\n");
}


//**********************************************************************************
//**********************************************************************************
// Internal function implementations

inline void CSCI441_INTERNAL::printOpenGLParamHeader( const int MAJOR, const int MINOR ) {
	fprintf( stdout, "[INFO]: >--------------------------------------------------------<\n" );
	fprintf( stdout, "[INFO]: | OpenGL %d.%d Settings                                    |\n", MAJOR, MINOR );
	fprintf( stdout, "[INFO]: |--------------------------------------------------------|\n" );
}

inline void CSCI441_INTERNAL::printOpenGLParamIndexed(const char *FORMAT, GLenum name, GLuint index ) {
	GLint value = 0;
	glGetIntegeri_v( name, index, &value );
	fprintf(stdout, FORMAT, value );
}

inline void CSCI441_INTERNAL::printOpenGLParam(const char *FORMAT, GLenum name ) {
	GLint value = 0;
	glGetIntegerv( name, &value );
	fprintf(stdout, FORMAT, value );
}

inline void CSCI441_INTERNAL::printOpenGLParam2(const char *FORMAT, GLenum name ) {
	GLint values[2] = {0,0};
	glGetIntegerv( name, values );
	fprintf(stdout, FORMAT, values[0], values[1] );
}

inline void CSCI441_INTERNAL::printOpenGLParam3(const char *FORMAT, GLenum name ) {
	GLint values[3] = {0,0,0};
	glGetIntegerv( name, values );
	fprintf(stdout, FORMAT, values[0], values[1], values[2] );
}

inline void CSCI441_INTERNAL::printOpenGLParam4(const char *FORMAT, GLenum name ) {
	GLint values[4] = {0,0,0,0};
	glGetIntegerv( name, values );
	fprintf(stdout, FORMAT, values[0], values[1], values[2], values[3] );
}

#endif // CSCI441_OPENGL_UTILS_H
