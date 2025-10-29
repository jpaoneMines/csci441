/** @file ShaderProgramPipeline.hpp
 * @brief Class to work with Shader Program Pipelines
 * @author Dr. Jeffrey Paone
 *
 * @copyright MIT License Copyright (c) 2017 Dr. Jeffrey Paone
 *
 *	These functions, classes, and constants help minimize common
 *	code that needs to be written.
 */

#ifndef CSCI441_SHADER_PROGRAM_PIPELINE_HPP
#define CSCI441_SHADER_PROGRAM_PIPELINE_HPP

#include "ShaderProgram.hpp"

#include <cstdio>

////////////////////////////////////////////////////////////////////////////////

namespace CSCI441 {

    /**
     * @class ShaderProgramPipeline
     * @brief Handles registration and compilation of Shader Program Pipelines
     */
    class [[maybe_unused]] ShaderProgramPipeline final {
    public:
        /**
         * @brief Enables debug messages from Shader Program functions
         * @note Debug messages are on by default.
         */
        [[maybe_unused]] static void enableDebugMessages();
        /**
         * @brief Disables debug messages from Shader Program functions
         * @note Debug messages are on by default.
         */
        [[maybe_unused]] static void disableDebugMessages();

        /**
         * @brief creates a shader program pipeline by generating a
         * shader program pipeline handle
         */
        ShaderProgramPipeline();
        /**
         * @brief deletes a shader program pipeline by deleting the
         * shader program pipeline handle
         */
        ~ShaderProgramPipeline();

        /**
         * @brief do not allow shader program pipelines to be copied
         */
        ShaderProgramPipeline(const ShaderProgramPipeline&) = delete;
        /**
        * @brief do not allow shader program pipelines to be copied
        */
        ShaderProgramPipeline& operator=(const ShaderProgramPipeline&) = delete;

        /**
         * @brief move construct a shader program pipeline
         */
        ShaderProgramPipeline(ShaderProgramPipeline&&) noexcept;
        /**
         * @brief move assign a shader program pipeline
         * @return the newly assigned object
         */
        ShaderProgramPipeline& operator=(ShaderProgramPipeline&&) noexcept;

        /**
         * @brief adds shader program stages to pipeline
         * @param programStages stages shader program contains
         * @param shaderProgram separable shader program to use within pipeline
         * @note ShaderProgram must be separable
         */
        [[maybe_unused]] void useProgramStages( GLbitfield programStages, const ShaderProgram *shaderProgram ) const;

        /**
         * @brief adds shader program stages to pipeline
         * @param shaderProgram separable shader program to use within pipeline
         * @note ShaderProgram must be separable
         */
        [[maybe_unused]] void useProgramStages( const ShaderProgram *shaderProgram ) const;

        /**
         * @brief bind shader program pipeline
         * @note unbinds any previously used shader programs
         */
        [[maybe_unused]] void bindPipeline() const;

        /**
         * @brief prints shader program pipeline information to console
         */
        [[maybe_unused]] void printPipelineInfo() const;

        /**
         * checks if shader program pipeline is in valid state to run
         * @return true if valid
         */
        [[maybe_unused]] [[nodiscard]] bool validatePipeline() const;

    private:
        static bool sDEBUG;

        GLuint _pipelineHandle;
    };
}

////////////////////////////////////////////////////////////////////////////////

inline bool CSCI441::ShaderProgramPipeline::sDEBUG = true;

[[maybe_unused]]
inline void CSCI441::ShaderProgramPipeline::enableDebugMessages() {
    sDEBUG = true;
}

[[maybe_unused]]
inline void CSCI441::ShaderProgramPipeline::disableDebugMessages() {
    sDEBUG = false;
}

inline CSCI441::ShaderProgramPipeline::ShaderProgramPipeline() : _pipelineHandle(0) {
    glGenProgramPipelines(1,& _pipelineHandle);
}

inline CSCI441::ShaderProgramPipeline::~ShaderProgramPipeline() {
    glDeleteProgramPipelines(1, &_pipelineHandle);
}

inline CSCI441::ShaderProgramPipeline::ShaderProgramPipeline(ShaderProgramPipeline&& src) noexcept {
    _pipelineHandle = src._pipelineHandle;
    src._pipelineHandle = 0;
}

inline CSCI441::ShaderProgramPipeline &CSCI441::ShaderProgramPipeline::operator=(ShaderProgramPipeline&& src) noexcept {
    // guard against self movement
    if (this != &src) {
        // delete our existing pipeline
        glDeleteProgramPipelines(1, &_pipelineHandle);
        // move the source pipeline
        _pipelineHandle = src._pipelineHandle;
        src._pipelineHandle = 0;
    }
    // return ourselves
    return *this;
}


[[maybe_unused]]
inline void CSCI441::ShaderProgramPipeline::useProgramStages( const GLbitfield programStages, const ShaderProgram * const shaderProgram ) const {
    glUseProgramStages( _pipelineHandle, programStages, shaderProgram->getShaderProgramHandle() );
}

[[maybe_unused]]
inline void CSCI441::ShaderProgramPipeline::useProgramStages( const ShaderProgram * const shaderProgram ) const {
    glUseProgramStages( _pipelineHandle, shaderProgram->getProgramStages(), shaderProgram->getShaderProgramHandle() );
}

[[maybe_unused]]
inline void CSCI441::ShaderProgramPipeline::bindPipeline() const {
    glUseProgram(0);    // un-use any existing program that may have previously been used.  programs override pipelines
    glBindProgramPipeline( _pipelineHandle );
}

[[maybe_unused]]
inline void CSCI441::ShaderProgramPipeline::printPipelineInfo() const {
    if( sDEBUG ) {
        printf( "\n[INFO]: /--------------------------------------------------------\\\n");
        printf( "[INFO]: | Program Pipeline:                                      |\n");
        printf( "[INFO]: |   Pipeline Handle: %4u %32c\n", _pipelineHandle, '|' );
				
		CSCI441_INTERNAL::ShaderUtils::printProgramPipelineLog(_pipelineHandle);
		
		printf( "[INFO]: >--------------------------------------------------------<\n");

		GLint vs, tcs, tes, gs, fs, cs;
		glGetProgramPipelineiv( _pipelineHandle, GL_VERTEX_SHADER, &vs );
		glGetProgramPipelineiv( _pipelineHandle, GL_TESS_CONTROL_SHADER, &tcs );
		glGetProgramPipelineiv( _pipelineHandle, GL_TESS_EVALUATION_SHADER, &tes );
		glGetProgramPipelineiv( _pipelineHandle, GL_GEOMETRY_SHADER, &gs );
		glGetProgramPipelineiv( _pipelineHandle, GL_FRAGMENT_SHADER, &fs );

        GLint major, minor;
        glGetIntegerv(GL_MAJOR_VERSION, &major);
        glGetIntegerv(GL_MINOR_VERSION, &minor);

        if(major > 4 || (major == 4 && minor >= 3)) {
            glGetProgramPipelineiv( _pipelineHandle, GL_COMPUTE_SHADER, &cs );
        }
		
		if( vs != 0 )  printf( "[INFO]: |   Vertex    Shader Program Handle: %2d                  |\n", vs );
		if( tcs != 0 ) printf( "[INFO]: |   Tess Ctrl Shader Program Handle: %2d                  |\n", tcs );
		if( tes != 0 ) printf( "[INFO]: |   Tess Eval Shader Program Handle: %2d                  |\n", tes );
		if( gs != 0 )  printf( "[INFO]: |   Geometry  Shader Program Handle: %2d                  |\n", gs );
		if( fs != 0 )  printf( "[INFO]: |   Fragment  Shader Program Handle: %2d                  |\n", fs );
        if(major < 4 || (major == 4 && minor >= 3)) {
            if( cs != 0 )  printf( "[INFO]: |   Compute   Shader Program Handle: %2d                  |\n", cs );
        }

        printf( "[INFO]: \\--------------------------------------------------------/\n");
        printf( "\n");
    }
}

[[maybe_unused]]
inline bool CSCI441::ShaderProgramPipeline::validatePipeline() const {
    glValidateProgramPipeline(_pipelineHandle);
    GLint validateStatus;
    glGetProgramPipelineiv(_pipelineHandle, GL_VALIDATE_STATUS, &validateStatus);
    return (validateStatus == GL_TRUE);
}

#endif// CSCI441_SHADER_PROGRAM_PIPELINE_HPP