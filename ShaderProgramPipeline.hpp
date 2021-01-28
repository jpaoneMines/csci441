/** @file ShaderProgramPipeline.hpp
 * @brief Class to work with OpenGL 4.0+ Shaders
 * @author Dr. Jeffrey Paone
 * @date Last Edit: 28 Jan 2021
 * @version 2.2.0
 *
 * @copyright MIT License Copyright (c) 2017 Dr. Jeffrey Paone
 *
 *	These functions, classes, and constants help minimize common
 *	code that needs to be written.
 */

#ifndef __CSCI441_SHADERPROGRAMPIPELINE_H__
#define __CSCI441_SHADERPROGRAMPIPELINE_H__

#include "ShaderProgram.hpp"

#include <stdlib.h>
#include <map>

////////////////////////////////////////////////////////////////////////////////

/** @namespace CSCI441
  * @brief CSCI441 Helper Functions for OpenGL
	*/
namespace CSCI441 {

    /** @class ShaderProgramPipeline
        * @desc Handles registration and compilation of Shader Program Pipelines
        */
    class ShaderProgramPipeline {
    public:
        /** @desc Enables debug messages from Shader Program functions
          *
            * Enables debug messages from Shader Program functions.  Debug messages are on by default.
          */
        static void enableDebugMessages();
        /** @desc Disables debug messages from Shader Program functions
          *
            * Disables debug messages from Shader Program functions.  Debug messages are on by default.
          */
        static void disableDebugMessages();

        ShaderProgramPipeline();
        ~ShaderProgramPipeline();

        void useProgramStages( GLbitfield programStages, ShaderProgram *shaderProgram );

        void bindPipeline();

        void printPipelineInfo();

    private:
        static bool sDEBUG;

        GLuint _pipelineHandle;

        std::map< GLuint, GLbitfield > *_programs;
    };
}

////////////////////////////////////////////////////////////////////////////////

inline bool CSCI441::ShaderProgramPipeline::sDEBUG = true;

inline void CSCI441::ShaderProgramPipeline::enableDebugMessages() {
    sDEBUG = true;
}
inline void CSCI441::ShaderProgramPipeline::disableDebugMessages() {
    sDEBUG = false;
}

CSCI441::ShaderProgramPipeline::ShaderProgramPipeline() {
    glGenProgramPipelines(1,& _pipelineHandle);

    _programs = new std::map< GLuint, GLbitfield >();
}

CSCI441::ShaderProgramPipeline::~ShaderProgramPipeline() {
    delete _programs;
}

void CSCI441::ShaderProgramPipeline::useProgramStages( GLbitfield programStages, ShaderProgram *shaderProgram ) {
    glUseProgramStages( _pipelineHandle, programStages, shaderProgram->getShaderProgramHandle() );

    _programs->emplace( shaderProgram->getShaderProgramHandle(), programStages );
}

void CSCI441::ShaderProgramPipeline::bindPipeline() {
    glBindProgramPipeline( _pipelineHandle );
}

void CSCI441::ShaderProgramPipeline::printPipelineInfo() {
    if( sDEBUG ) {
        printf( "[INFO]: /========================================================\\\n");
        printf( "[INFO]: | Program Pipeline:                                      |\n");
        printf( "[INFO]: |   Pipeline Handle: %4u %32c\n", _pipelineHandle, '|' );

        for( const auto& program : *_programs ) {
            printf( "[INFO]: >========================================================<\n");
            GLuint programHandle = program.first;
            GLbitfield programStages = program.second;

            GLboolean hasVertexShader       = ((programStages & GL_VERTEX_SHADER_BIT )           == GL_VERTEX_SHADER_BIT            );
            GLboolean hasTessControlShader  = ((programStages & GL_TESS_CONTROL_SHADER_BIT )     == GL_TESS_CONTROL_SHADER_BIT      );
            GLboolean hasTessEvalShader     = ((programStages & GL_TESS_EVALUATION_SHADER_BIT )  == GL_TESS_EVALUATION_SHADER_BIT   );
            GLboolean hasGeometryShader     = ((programStages & GL_GEOMETRY_SHADER_BIT )         == GL_GEOMETRY_SHADER_BIT          );
            GLboolean hasFragmentShader     = ((programStages & GL_FRAGMENT_SHADER_BIT )         == GL_FRAGMENT_SHADER_BIT          );

            printf( "[INFO]: | Shader Program Handle: %31u |\n", programHandle );
            printf( "[INFO]: |   Uses:    %-4s %-8s %-8s %-3s %-4s   Shader(s) |\n",
                   (hasVertexShader ? "Vert" : ""),
                   (hasTessControlShader ? "TessCtrl" : ""),
                   (hasTessEvalShader ? "TessEval" : ""),
                   (hasGeometryShader ? "Geo" : ""),
                   (hasFragmentShader ? "Frag" : ""));


            CSCI441_INTERNAL::ShaderUtils::printShaderProgramInfo( programHandle,
                                                                   hasVertexShader, hasTessControlShader, hasTessEvalShader, hasGeometryShader, hasFragmentShader,
                                                                   false );
        }

        printf( "[INFO]: \\========================================================/\n");
        printf( "\n");
    }
}

#endif