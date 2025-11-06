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
        ~ComputeShaderProgram() override = default;

        /**
         * @brief do not allow shader programs to be copied
         */
        ComputeShaderProgram(const ComputeShaderProgram&) = delete;
        /**
         * @brief do not allow shader programs to be copied
         */
        ComputeShaderProgram& operator=(const ComputeShaderProgram&) = delete;

        /**
         * @brief construct a new compute shader program by moving an existing computer shader program
         * @note uses default implementation which is to call the parent CSCI441::ShaderProgram implementation
         */
        ComputeShaderProgram(ComputeShaderProgram&&) noexcept = default;
        /**
         * @brief assign this compute shader program by moving an existing computer shader program
         * @return our newly assigned computer shader program
         * @note uses default implementation which is to call the parent CSCI441::ShaderProgram implementation
         */
        ComputeShaderProgram& operator=(ComputeShaderProgram&&) noexcept = default;

        /**
         * @brief dispatches work to the Compute Shader on the GPU
         * @param numGroupsX number of work groups in X dimension (defaults to 1)
         * @param numGroupsY number of work groups in Y dimension (defaults to 1)
         * @param numGroupsZ number of work groups in Z dimension (defaults to 1)
         * @note call after calling ShaderProgram::useProgram()
         */
        [[maybe_unused]] void dispatchWork(GLuint numGroupsX, GLuint numGroupsY, GLuint numGroupsZ) const;

        /**
         * @brief returns a single value corresponding to which shader stages are present in this shader program
         * @return bitfield of shader stages
         */
        [[maybe_unused]] [[nodiscard]] GLbitfield getProgramStages() const override;

    protected:
        /**
         * @brief compute shader handle
         */
        GLuint mComputeShaderHandle;
    };

}

////////////////////////////////////////////////////////////////////////////////

inline CSCI441::ComputeShaderProgram::ComputeShaderProgram( const char *computeShaderFilename ) : mComputeShaderHandle(0) {
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
        mComputeShaderHandle = CSCI441_INTERNAL::ShaderUtils::compileShader(computeShaderFilename, GL_COMPUTE_SHADER );
    } else {
        mComputeShaderHandle = 0;
    }

    // get a handle to a shader program
    mShaderProgramHandle = glCreateProgram();

    // attach the computer fragment shader to the shader program
    if(mComputeShaderHandle != 0 ) {
        glAttachShader(mShaderProgramHandle, mComputeShaderHandle );
    }

    // link all the programs together on the GPU
    glLinkProgram(mShaderProgramHandle );

    if( sDEBUG ) printf( "[INFO]: | Shader Program: %41s", "|\n" );

    // check the program log
    CSCI441_INTERNAL::ShaderUtils::printProgramLog(mShaderProgramHandle );

    // detach & delete the vertex and fragment shaders to the shader program
    if(mComputeShaderHandle != 0 ) {
        glDetachShader(mShaderProgramHandle, mComputeShaderHandle );
        glDeleteShader(mComputeShaderHandle );
    }

    // map uniforms
    mpUniformLocationsMap = new std::map<std::string, GLint>();
    GLint numUniforms;
    glGetProgramiv(mShaderProgramHandle, GL_ACTIVE_UNIFORMS, &numUniforms);
    GLint max_uniform_name_size;
    glGetProgramiv(mShaderProgramHandle, GL_ACTIVE_UNIFORM_MAX_LENGTH, &max_uniform_name_size);
    if( numUniforms > 0 ) {
        for(GLuint i = 0; i < numUniforms; i++) {
            char* name = (char*) malloc(max_uniform_name_size * sizeof(char));
            int actual_length = 0;
            int size = 0;
            GLenum type;
            glGetActiveUniform(mShaderProgramHandle, i, max_uniform_name_size, &actual_length, &size, &type, name );
            GLint location = -1;
            if(size > 1) {
                for(int j = 0; j < size; j++) {
                    int max_array_size = actual_length + 4 + 2 + 1;
                    char* array_name = (char*) malloc(max_array_size * sizeof(char));
                    snprintf(array_name, max_array_size, "%s[%i]", name, j);
                    location = glGetUniformLocation(mShaderProgramHandle, array_name);
                    mpUniformLocationsMap->emplace(array_name, location);
                    free(array_name);
                }
            } else {
                location = glGetUniformLocation(mShaderProgramHandle, name);
                mpUniformLocationsMap->emplace(name, location);
            }
            free(name);
        }
    }
    GLint linkStatus;
    glGetProgramiv(mShaderProgramHandle, GL_LINK_STATUS, &linkStatus );

    /* print shader info for uniforms & attributes */
    if(linkStatus == 1) {
        // print shader info for uniforms & attributes
        CSCI441_INTERNAL::ShaderUtils::printShaderProgramInfo(mShaderProgramHandle, false, false, false, false, false,
                                                              mComputeShaderHandle != 0, true);
    }
}

[[maybe_unused]]
inline void CSCI441::ComputeShaderProgram::dispatchWork(const GLuint numGroupsX = 1, const GLuint numGroupsY = 1, const GLuint numGroupsZ = 1) const {
    glDispatchCompute(numGroupsX, numGroupsY, numGroupsZ);
}

[[maybe_unused]]
inline GLbitfield CSCI441::ComputeShaderProgram::getProgramStages() const {
    GLbitfield shaderBits = 0;
    if( mComputeShaderHandle != 0 ) shaderBits |= GL_COMPUTE_SHADER_BIT;
    return shaderBits;
}

#endif // CSCI441_COMPUTE_SHADER_PROGRAM_HPP