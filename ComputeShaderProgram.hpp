/**
 * @file ComputeShaderProgram.hpp
 * @brief Class to work with OpenGL Compute Shaders
 * @author Dr. Jeffrey Paone
 *
 * @copyright MIT License Copyright (c) 2021 Dr. Jeffrey Paone
 *
 *	These functions, classes, and constants help minimize common
 *	code that needs to be written.
 */

#ifndef CSCI441_COMPUTESHADERPROGRAM_HPP
#define CSCI441_COMPUTESHADERPROGRAM_HPP

#include "ShaderProgram.hpp"

////////////////////////////////////////////////////////////////////////////////

namespace CSCI441 {

    /// Handles registration and compilation of Compute Shaders
    /// \note Extends the ShaderProgram class
    class ComputeShaderProgram : public ShaderProgram {
    public:
        /// Creates a Compute Shader Program
        /// \param const char* name of the file corresponding to the compute shader
        explicit ComputeShaderProgram( const char *computeShaderFilename );

        /// dispatches work to the Compute Shader on the GPU
        /// \param GLuint number of work groups in X dimension (defaults to 1)
        /// \param GLuint number of work groups in Y dimension (defaults to 1)
        /// \param GLuint number of work groups in Z dimension (defaults to 1)
        /// \note call after calling ShaderProgram::useProgram()
        void dispatchWork(GLuint numGroupsX, GLuint numGroupsY, GLuint numGroupsZ);
    private:
        // holds shader program handle
        GLuint _computeShaderHandle;
    };
}

////////////////////////////////////////////////////////////////////////////////

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
    mShaderProgramHandle = glCreateProgram();

    // attach the computer fragment shader to the shader program
    if( _computeShaderHandle != 0 ) {
        glAttachShader(mShaderProgramHandle, _computeShaderHandle );
    }

    // link all the programs together on the GPU
    glLinkProgram(mShaderProgramHandle );

    if( sDEBUG ) printf( "[INFO]: | Shader Program: %41s", "|\n" );

    // check the program log
    CSCI441_INTERNAL::ShaderUtils::printProgramLog(mShaderProgramHandle );

    // detach & delete the vertex and fragment shaders to the shader program
    if( _computeShaderHandle != 0 ) {
        glDetachShader(mShaderProgramHandle, _computeShaderHandle );
        glDeleteShader( _computeShaderHandle );
    }

    // map uniforms
    mpUniformLocationsMap = new std::map<std::string, GLint>();
    GLint numUniforms;
    glGetProgramiv(mShaderProgramHandle, GL_ACTIVE_UNIFORMS, &numUniforms);
    if( numUniforms > 0 ) {
        for(GLuint i = 0; i < numUniforms; i++) {
            char name[64];
            int max_length = 64;
            int actual_length = 0;
            int size = 0;
            GLenum type;
            glGetActiveUniform(mShaderProgramHandle, i, max_length, &actual_length, &size, &type, name );
            GLint location = -1;
            if(size > 1) {
                for(int j = 0; j < size; j++) {
                    char long_name[64];
                    sprintf(long_name, "%s[%i]", name, j);
                    location = glGetUniformLocation(mShaderProgramHandle, long_name);
                }
            } else {
                location = glGetUniformLocation(mShaderProgramHandle, name);
            }
            mpUniformLocationsMap->emplace(name, location );
        }
    }
    GLint linkStatus;
    glGetProgramiv(mShaderProgramHandle, GL_LINK_STATUS, &linkStatus );

    /* print shader info for uniforms & attributes */
    if(linkStatus == 1) {
        // print shader info for uniforms & attributes
        CSCI441_INTERNAL::ShaderUtils::printShaderProgramInfo(mShaderProgramHandle, false, false, false, false, false,
                                                              _computeShaderHandle != 0, true);
    }
}

inline void CSCI441::ComputeShaderProgram::dispatchWork(GLuint numGroupsX = 1, GLuint numGroupsY = 1, GLuint numGroupsZ = 1) {
    glDispatchCompute(numGroupsX, numGroupsY, numGroupsZ);
}

#endif // CSCI441_COMPUTESHADERPROGRAM_HPP