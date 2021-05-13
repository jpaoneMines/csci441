/** @file ShaderProgramPipeline.hpp
 * @brief Class to work with OpenGL 4.0+ Shaders
 * @author Dr. Jeffrey Paone
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

        void useProgramStages( GLbitfield programStages, const ShaderProgram *shaderProgram );

        void bindPipeline();

        void printPipelineInfo();

    private:
        static bool sDEBUG;

        GLuint _pipelineHandle;
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

inline CSCI441::ShaderProgramPipeline::ShaderProgramPipeline() {
    glGenProgramPipelines(1,& _pipelineHandle);
}

inline CSCI441::ShaderProgramPipeline::~ShaderProgramPipeline() {
    
}

inline void CSCI441::ShaderProgramPipeline::useProgramStages( GLbitfield programStages, const ShaderProgram *shaderProgram ) {
    glUseProgramStages( _pipelineHandle, programStages, shaderProgram->getShaderProgramHandle() );
}

inline void CSCI441::ShaderProgramPipeline::bindPipeline() {
    glUseProgram(0);    // unuse any existing program that may have previously been used.  programs override pipelines
    glBindProgramPipeline( _pipelineHandle );
}

inline void CSCI441::ShaderProgramPipeline::printPipelineInfo() {
    if( sDEBUG ) {
        printf( "\n[INFO]: /--------------------------------------------------------\\\n");
        printf( "[INFO]: | Program Pipeline:                                      |\n");
        printf( "[INFO]: |   Pipeline Handle: %4u %32c\n", _pipelineHandle, '|' );
				
		CSCI441_INTERNAL::ShaderUtils::printProgramPipelineLog(_pipelineHandle);
		
		printf( "[INFO]: >--------------------------------------------------------<\n");

		GLint vs, tcs, tes, gs, fs;
		glGetProgramPipelineiv( _pipelineHandle, GL_VERTEX_SHADER, &vs );
		glGetProgramPipelineiv( _pipelineHandle, GL_TESS_CONTROL_SHADER, &tcs );
		glGetProgramPipelineiv( _pipelineHandle, GL_TESS_EVALUATION_SHADER, &tes );
		glGetProgramPipelineiv( _pipelineHandle, GL_GEOMETRY_SHADER, &gs );
		glGetProgramPipelineiv( _pipelineHandle, GL_FRAGMENT_SHADER, &fs );
		
		if( vs != 0 )  printf( "[INFO]: |   Vertex    Shader Program Handle: %2d                  |\n", vs );
		if( tcs != 0 ) printf( "[INFO]: |   Tess Ctrl Shader Program Handle: %2d                  |\n", tcs );
		if( tes != 0 ) printf( "[INFO]: |   Tess Eval Shader Program Handle: %2d                  |\n", tes );
		if( gs != 0 )  printf( "[INFO]: |   Geometry  Shader Program Handle: %2d                  |\n", gs );
		if( fs != 0 )  printf( "[INFO]: |   Fragment  Shader Program Handle: %2d                  |\n", fs );

        printf( "[INFO]: \\--------------------------------------------------------/\n");
        printf( "\n");
    }
}

#endif