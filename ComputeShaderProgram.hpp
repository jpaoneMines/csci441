/** @file ComputeShaderProgram.hpp
 * @brief Class to work with OpenGL Compute Shaders
 * @author Dr. Jeffrey Paone
 * @date Last Edit: 21 Feb 2021
 *
 * @copyright MIT License Copyright (c) 2021 Dr. Jeffrey Paone
 *
 *	These functions, classes, and constants help minimize common
 *	code that needs to be written.
 */

#ifndef __CSCI441_COMPUTESHADERPROGRAM_H__
#define __CSCI441_COMPUTESHADERPROGRAM_H__

#include "ShaderProgram.hpp"


////////////////////////////////////////////////////////////////////////////////

/** @namespace CSCI441
  * @brief CSCI441 Helper Functions for OpenGL
	*/
namespace CSCI441 {

    /** @class ComputeShaderProgram
        * @desc Handles registration and compilation of Compute Shaders
        */
    class ComputeShaderProgram : public ShaderProgram {
    public:
        /** @desc Creates a Compute Shader Program
          *
            * @param const char* computeShaderFilename - name of the file corresponding to the compute shader
          */
        ComputeShaderProgram( const char *computeShaderFilename );

        void dispatchWork(GLuint numGroupsX, GLuint numGroupsY, GLuint numGroupsZ);
    private:
        ComputeShaderProgram();

        GLuint _computeShaderHandle;
    };
}

////////////////////////////////////////////////////////////////////////////////

inline CSCI441::ComputeShaderProgram::ComputeShaderProgram() {}

inline CSCI441::ComputeShaderProgram::ComputeShaderProgram( const char *computeShaderFilename ) {
    GLint major, minor;
    glGetIntegerv(GL_MAJOR_VERSION, &major);
    glGetIntegerv(GL_MINOR_VERSION, &minor);

    if(major < 4 || (major == 4 && minor < 3)) {
        fprintf(stderr, "[ERROR]: Compute Shaders only supported in OpenGL 4.3+\n");
        return;
    }

    if( sDEBUG ) printf( "\n[INFO]: /--------------------------------------------------------\\\n");

    // compile each one of our shaders
    if( strcmp( computeShaderFilename, "" ) != 0 ) {
        if( sDEBUG ) printf( "[INFO]: | Compute Shader: %38s |\n", computeShaderFilename );
        _computeShaderHandle = CSCI441_INTERNAL::ShaderUtils::compileShader( computeShaderFilename, GL_COMPUTE_SHADER );
    } else {
        _computeShaderHandle = 0;
    }

    // get a handle to a shader program
    _shaderProgramHandle = glCreateProgram();

    // attach the computer fragment shader to the shader program
    if( _computeShaderHandle != 0 ) {
        glAttachShader( _shaderProgramHandle, _computeShaderHandle );
    }

    // link all the programs together on the GPU
    glLinkProgram( _shaderProgramHandle );

    if( sDEBUG ) printf( "[INFO]: | Shader Program: %41s", "|\n" );

    // check the program log
    CSCI441_INTERNAL::ShaderUtils::printLog( _shaderProgramHandle );

    // detach & delete the vertex and fragment shaders to the shader program
    if( _computeShaderHandle != 0 ) {
        glDetachShader( _shaderProgramHandle, _computeShaderHandle );
        glDeleteShader( _computeShaderHandle );
    }

    // map uniforms
    _uniformLocations = new std::map<std::string, GLint>();
    GLint numUniforms;
    glGetProgramiv( _shaderProgramHandle, GL_ACTIVE_UNIFORMS, &numUniforms);
    if( numUniforms > 0 ) {
        for(GLuint i = 0; i < numUniforms; i++) {
            char name[64];
            int max_length = 64;
            int actual_length = 0;
            int size = 0;
            GLenum type;
            glGetActiveUniform( _shaderProgramHandle, i, max_length, &actual_length, &size, &type, name );
            GLint location = -1;
            if(size > 1) {
                for(int j = 0; j < size; j++) {
                    char long_name[64];
                    sprintf(long_name, "%s[%i]", name, j);
                    location = glGetUniformLocation(_shaderProgramHandle, long_name);
                }
            } else {
                location = glGetUniformLocation(_shaderProgramHandle, name);
            }
            _uniformLocations->emplace( name, location );
        }
    }

    // print shader info for uniforms & attributes
    CSCI441_INTERNAL::ShaderUtils::printShaderProgramInfo( _shaderProgramHandle, false, false, false, false, false, _computeShaderHandle != 0, true );
}

inline void CSCI441::ComputeShaderProgram::dispatchWork(GLuint numGroupsX = 1, GLuint numGroupsY = 1, GLuint numGroupsZ = 1) {
    glDispatchCompute(numGroupsX, numGroupsY, numGroupsZ);
}

#endif // __CSCI441_COMPUTESHADERPROGRAM_H__