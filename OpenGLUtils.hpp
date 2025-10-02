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
 * @warning NOTE: This header file depends upon GLAD (or alternatively GLEW)
 * @warning NOTE: This header file depends upon glm
 */

#ifndef CSCI441_OPENGL_UTILS_H
#define CSCI441_OPENGL_UTILS_H

#include "constants.h"

#ifdef CSCI441_USE_GLEW
    #include <GL/glew.h>
#else
    #include <glad/gl.h>
#endif

#include <glm/glm.hpp>

#include <cstdio>      // for printf()
#include <cstdlib>     // for atoi()

//**********************************************************************************

/**
 * @namespace CSCI441
 * @brief CSCI441 Helper Functions for OpenGL
 */
namespace CSCI441 {
    /**
      * @brief constant for positive X_AXIS
      */
    static const glm::vec3 X_AXIS( 1.0f, 0.0f, 0.0f );
    /**
     * @brief constant for positive Y_AXIS
     */
    static const glm::vec3 Y_AXIS( 0.0f, 1.0f, 0.0f );
    /**
     * @brief constant for positive Z_AXIS
     */
    static const glm::vec3 Z_AXIS( 0.0f, 0.0f, 1.0f );
    /**
     * @brief alias for constant for positive X_AXIS
     */
    [[maybe_unused]] static const glm::vec3 X_AXIS_POS = X_AXIS;
    /**
     * @brief alias for constant for positive Y_AXIS
     */
    [[maybe_unused]] static const glm::vec3 Y_AXIS_POS = Y_AXIS;
    /**
     * @brief alias for constant for positive Z_AXIS
     */
    [[maybe_unused]] static const glm::vec3 Z_AXIS_POS = Z_AXIS;
    /**
     * @brief constant for negative X_AXIS
     */
    [[maybe_unused]] static const glm::vec3 X_AXIS_NEG( -1.0f,  0.0f,  0.0f );
    /**
     * @brief constant for negative Y_AXIS
     */
    [[maybe_unused]] static const glm::vec3 Y_AXIS_NEG(  0.0f, -1.0f,  0.0f );
    /**
     * @brief constant for negative Z_AXIS
     */
    [[maybe_unused]] static const glm::vec3 Z_AXIS_NEG(  0.0f,  0.0f, -1.0f );

    /**
     * @namespace OpenGLUtils
     * @brief contains OpenGL Utility functions
     */
    namespace OpenGLUtils {
        /**
         * @brief Prints information about our OpenGL context
         */
        void printOpenGLInfo();
        /**
         * @brief Prints the list of available extensions
         */
        [[maybe_unused]] void printOpenGLExtensions();
        /**
         * @brief Checks if there are any OpenGL errors, printing them if so,
         * and clearing the error flag.
         */
        [[maybe_unused]] void checkOpenGLErrors();

        /**
         * @brief Converts error value to string representation
         * @param err OpenGL error code
         * @return name of error
         */
        [[maybe_unused]] const char* openGLErrorMessage(GLenum err);

        /**
         * @brief Converts debug source value to string representation
         * @param source debug source
         * @return name of debug source
         */
        [[maybe_unused]] const char* debugSourceToString(GLenum source);
        /**
         * @brief Converts debug type value to string representation
         * @param type debug type
         * @return type of debug message
         */
        [[maybe_unused]] const char* debugTypeToString(GLenum type);
        /**
         * @brief Converts debug severity value to string representation
         * @param severity debug severity
         * @return severity of debug message
         */
        [[maybe_unused]] const char* debugSeverityToString(GLenum severity);
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
  void printOpenGLParam2f(const char *FORMAT, GLenum name );
  [[maybe_unused]] void printOpenGLParam3(const char *FORMAT, GLenum name );
  void printOpenGLParam4(const char *FORMAT, GLenum name );
}

//**********************************************************************************
//**********************************************************************************
// Outward facing function implementations

inline void CSCI441::OpenGLUtils::printOpenGLInfo() {
    GLint major = 0, minor = 0, numExtensions = 0;
    glGetIntegerv(GL_MAJOR_VERSION, &major);
    glGetIntegerv(GL_MINOR_VERSION, &minor);
    glGetIntegerv(GL_NUM_EXTENSIONS, &numExtensions);

	fprintf( stdout, "\n[INFO]: /--------------------------------------------------------\\\n" );
	fprintf( stdout, "[INFO]: | OpenGL Information                                     |\n" );
	fprintf( stdout, "[INFO]: |--------------------------------------------------------|\n" );
	fprintf( stdout, "[INFO]: |   OpenGL Version:  %35s |\n", glGetString(GL_VERSION) );
	fprintf( stdout, "[INFO]: |   OpenGL Renderer: %35s |\n", glGetString(GL_RENDERER) );
	fprintf( stdout, "[INFO]: |   OpenGL Vendor:   %35s |\n", glGetString(GL_VENDOR) );
	fprintf( stdout, "[INFO]: |   Shading Version: %35s |\n", glGetString(GL_SHADING_LANGUAGE_VERSION) );
    fprintf( stdout, "[INFO]: |   Number of Extensions: %30d |\n", numExtensions );

	if( (major >= 2 && minor >= 0) || major > 2 ) {
		CSCI441_INTERNAL::printOpenGLParamHeader( 2, 0 );
		CSCI441_INTERNAL::printOpenGLParam( "[INFO]: |   Max # Color Attachments:  %26d |\n", 			    			GL_MAX_COLOR_ATTACHMENTS );
        CSCI441_INTERNAL::printOpenGLParam2f("[INFO]: |   Point Size Range:  %24.2f %8.2f |\n", 			            GL_POINT_SIZE_RANGE );
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
		CSCI441_INTERNAL::printOpenGLParam( "[INFO]: |   Max # Tess Evaluation Inputs:  %21d |\n", 						GL_MAX_TESS_EVALUATION_INPUT_COMPONENTS );
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
		CSCI441_INTERNAL::printOpenGLParam( "[INFO]: |   Max Atomic Counter Buffer Size:  %17d |\n", 		    		GL_MAX_ATOMIC_COUNTER_BUFFER_SIZE );
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
		CSCI441_INTERNAL::printOpenGLParam( "[INFO]: |   Max # Compute Uniform Blocks:  %21d |\n", 						GL_MAX_COMPUTE_UNIFORM_BLOCKS );
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

[[maybe_unused]]
inline void CSCI441::OpenGLUtils::printOpenGLExtensions() {
    GLint numExtensions = 0;
    glGetIntegerv(GL_NUM_EXTENSIONS, &numExtensions);

    fprintf( stdout, "[INFO]: Number of Extensions: %4d\n", numExtensions );
    for (int i = 0; i < numExtensions; i++) {
        fprintf( stdout, "[INFO]: Extension #%3d: %s \n", (i+1), glGetStringi(GL_EXTENSIONS, i) );
    }
}

[[maybe_unused]]
inline void CSCI441::OpenGLUtils::checkOpenGLErrors() {
    GLenum err;
    while( (err = glGetError()) != GL_NO_ERROR ) {
        fprintf( stderr, "[ERROR]: OpenGL Error (%d): %s\n", err, CSCI441::OpenGLUtils::openGLErrorMessage(err) );
    }
}

inline const char* CSCI441::OpenGLUtils::openGLErrorMessage(GLenum err) {
    switch(err) {
        case GL_NO_ERROR:                       return "No error";
        case GL_INVALID_ENUM:                   return "Invalid enum";
        case GL_INVALID_VALUE:                  return "Invalid value";
        case GL_INVALID_OPERATION:              return "Invalid operation";
        case GL_STACK_OVERFLOW:                 return "Stack overflow";
        case GL_STACK_UNDERFLOW:                return "Stack underflow";
        case GL_OUT_OF_MEMORY:                  return "Out of memory";
        case GL_INVALID_FRAMEBUFFER_OPERATION:  return "Invalid framebuffer operation";
        case GL_CONTEXT_LOST:                   return "Context lost";
        default: return "Unknown";
    }
}

[[maybe_unused]]
inline const char* CSCI441::OpenGLUtils::debugSourceToString(GLenum source) {
    switch(source) {
        case GL_DEBUG_SOURCE_API:               return "API";
        case GL_DEBUG_SOURCE_WINDOW_SYSTEM:     return "Window System";
        case GL_DEBUG_SOURCE_SHADER_COMPILER:   return "Shader Compiler";
        case GL_DEBUG_SOURCE_THIRD_PARTY:       return "Third Party";
        case GL_DEBUG_SOURCE_APPLICATION:       return "Application";
        case GL_DEBUG_SOURCE_OTHER:             return "Other";
        default:                                return "Unknown";
    }
}

[[maybe_unused]]
inline const char* CSCI441::OpenGLUtils::debugTypeToString(GLenum type) {
    switch(type) {
        case GL_DEBUG_TYPE_ERROR:               return "Error";
        case GL_DEBUG_TYPE_DEPRECATED_BEHAVIOR: return "Deprecated Behavior";
        case GL_DEBUG_TYPE_UNDEFINED_BEHAVIOR:  return "Undefined Behavior";
        case GL_DEBUG_TYPE_PORTABILITY:         return "Portability";
        case GL_DEBUG_TYPE_PERFORMANCE:         return "Performance";
        case GL_DEBUG_TYPE_MARKER:              return "Marker";
        case GL_DEBUG_TYPE_PUSH_GROUP:          return "Push Group";
        case GL_DEBUG_TYPE_POP_GROUP:           return "Pop Group";
        case GL_DEBUG_TYPE_OTHER:               return "Other";
        default:                                return "Unknown";
    }
}

[[maybe_unused]]
inline const char* CSCI441::OpenGLUtils::debugSeverityToString(GLenum severity) {
    switch(severity) {
        case GL_DEBUG_SEVERITY_HIGH:            return "High";
        case GL_DEBUG_SEVERITY_MEDIUM:          return "Medium";
        case GL_DEBUG_SEVERITY_LOW:             return "Low";
        case GL_DEBUG_SEVERITY_NOTIFICATION:    return "Notification";
        default:                                return "Unknown";
    }
}

//**********************************************************************************
//**********************************************************************************
// Internal function implementations

inline void CSCI441_INTERNAL::printOpenGLParamHeader( const int MAJOR, const int MINOR ) {
	fprintf( stdout, "[INFO]: >--------------------------------------------------------<\n" );
	fprintf( stdout, "[INFO]: | OpenGL %d.%d Settings                                    |\n", MAJOR, MINOR );
	fprintf( stdout, "[INFO]: |--------------------------------------------------------|\n" );
}

inline void CSCI441_INTERNAL::printOpenGLParamIndexed(const char * const FORMAT, const GLenum name, const GLuint index ) {
	GLint value = 0;
	glGetIntegeri_v( name, index, &value );
	fprintf(stdout, FORMAT, value );
}

inline void CSCI441_INTERNAL::printOpenGLParam(const char * const FORMAT, const GLenum name ) {
	GLint value = 0;
	glGetIntegerv( name, &value );
	fprintf(stdout, FORMAT, value );
}

inline void CSCI441_INTERNAL::printOpenGLParam2(const char * const FORMAT, const GLenum name ) {
	GLint values[2] = {0,0};
	glGetIntegerv( name, values );
	fprintf(stdout, FORMAT, values[0], values[1] );
}

inline void CSCI441_INTERNAL::printOpenGLParam2f(const char * const FORMAT, const GLenum name ) {
	GLfloat values[2] = {0,0};
	glGetFloatv( name, values );
	fprintf(stdout, FORMAT, values[0], values[1] );
}

[[maybe_unused]]
inline void CSCI441_INTERNAL::printOpenGLParam3(const char * const FORMAT, const GLenum name ) {
	GLint values[3] = {0,0,0};
	glGetIntegerv( name, values );
	fprintf(stdout, FORMAT, values[0], values[1], values[2] );
}

inline void CSCI441_INTERNAL::printOpenGLParam4(const char * const FORMAT, const GLenum name ) {
	GLint values[4] = {0,0,0,0};
	glGetIntegerv( name, values );
	fprintf(stdout, FORMAT, values[0], values[1], values[2], values[3] );
}

#endif // CSCI441_OPENGL_UTILS_H
