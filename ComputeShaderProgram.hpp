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

#ifndef CSCI441_COMPUTE_SHADER_PROGRAM_HPP
#define CSCI441_COMPUTE_SHADER_PROGRAM_HPP

#include "ShaderProgram.hpp"

////////////////////////////////////////////////////////////////////////////////

namespace CSCI441 {

    /**
     * @brief Handles registration and compilation of Compute Shaders
     */
    class ComputeShaderProgram final : public ShaderProgram {
    public:
        /**
         * @brief Creates a Compute Shader Program
         * @param computeShaderFilename name of the file corresponding to the compute shader
         */
        explicit ComputeShaderProgram( const char *computeShaderFilename );

        /**
         * @brief Clean up memory associated with the Compute Shader Program
         */
        ~ComputeShaderProgram() final = default;

        /**
         * @brief do not allow shader programs to be copied
         */
        ComputeShaderProgram(const ComputeShaderProgram&) = delete;
        /**
         * @brief do not allow shader programs to be copied
         */
        ComputeShaderProgram& operator=(const ComputeShaderProgram&) = delete;

        /**
         * @brief dispatches work to the Compute Shader on the GPU
         * @param numGroupsX number of work groups in X dimension (defaults to 1)
         * @param numGroupsY number of work groups in Y dimension (defaults to 1)
         * @param numGroupsZ number of work groups in Z dimension (defaults to 1)
         * @note call after calling ShaderProgram::useProgram()
         */
        [[maybe_unused]] virtual void dispatchWork(GLuint numGroupsX, GLuint numGroupsY, GLuint numGroupsZ) final;
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

    // stores shader program handle
    GLuint computeShaderHandle;

    // compile each one of our shaders
    if( strcmp( computeShaderFilename, "" ) != 0 ) {
        if( sDEBUG ) printf( "[INFO]: | Compute Shader: %38s |\n", computeShaderFilename );
        computeShaderHandle = CSCI441_INTERNAL::ShaderUtils::compileShader(computeShaderFilename, GL_COMPUTE_SHADER );
    } else {
        computeShaderHandle = 0;
    }

    // get a handle to a shader program
    mShaderProgramHandle = glCreateProgram();

    // attach the computer fragment shader to the shader program
    if(computeShaderHandle != 0 ) {
        glAttachShader(mShaderProgramHandle, computeShaderHandle );
    }

    // link all the programs together on the GPU
    glLinkProgram(mShaderProgramHandle );

    if( sDEBUG ) printf( "[INFO]: | Shader Program: %41s", "|\n" );

    // check the program log
    CSCI441_INTERNAL::ShaderUtils::printProgramLog(mShaderProgramHandle );

    // detach & delete the vertex and fragment shaders to the shader program
    if(computeShaderHandle != 0 ) {
        glDetachShader(mShaderProgramHandle, computeShaderHandle );
        glDeleteShader(computeShaderHandle );
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
                                                              computeShaderHandle != 0, true);
    }
}

[[maybe_unused]]
inline void CSCI441::ComputeShaderProgram::dispatchWork(GLuint numGroupsX = 1, GLuint numGroupsY = 1, GLuint numGroupsZ = 1) {
    glDispatchCompute(numGroupsX, numGroupsY, numGroupsZ);
}

#endif // CSCI441_COMPUTE_SHADER_PROGRAM_HPP