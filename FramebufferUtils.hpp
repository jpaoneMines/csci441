/**
 * @file FramebufferUtils.hpp
 * @brief Helper functions to work with OpenGL Framebuffer
 * @author Dr. Jeffrey Paone
 *
 * @copyright MIT License Copyright (c) 2020 Dr. Jeffrey Paone
 *
 * These functions, classes, and constants help minimize common
 * code that needs to be written.
 *
 * @warning This header file depends upon GLAD (or alternatively GLEW)
 */

#ifndef CSCI441_FRAMEBUFFER_UTILS_HPP
#define CSCI441_FRAMEBUFFER_UTILS_HPP

#include "constants.h"
#include "LogUtils.hpp"

#ifdef CSCI441_USE_GLEW
    #include <GL/glew.h>
#else
    #include <glad/gl.h>
#endif

#include <cstdio>

//**********************************************************************************

namespace CSCI441 {

	/**
	 * @namespace FramebufferUtils
	 * @brief OpenGL Framebuffer Utility functions
	 */
	namespace FramebufferUtils {

	    /**
	     * @brief Prints the framebuffer information for the FBO attached to the corresponding target
	     * @param target framebuffer target to bind named framebuffer to
	     * @param fbo name of a framebuffer object
	     */
        [[maybe_unused]] void printFramebufferInfo( GLenum target, GLuint fbo );

		/**
		 * @brief Prints the framebuffer status for the FBO attached to the corresponding target
		 * @param target framebuffer target to bind named framebuffer to
		 * @param fbo name of a framebuffer object
		 */
        [[maybe_unused]] void printFramebufferStatusMessage( GLenum target, GLuint fbo );

        /**
         * @brief Prints the framebuffer status for the FBO currently attached to the corresponding target
         * @param target framebuffer target to check status of bound framebuffer
         */
		void printFramebufferStatusMessage( GLenum target );
	}
}

//**********************************************************************************
//**********************************************************************************
// Outward facing function implementations

[[maybe_unused]]
inline void CSCI441::FramebufferUtils::printFramebufferInfo( const GLenum target, const GLuint fbo ) {
	int res, i = 0;
	GLint buffer;

	if(glIsFramebuffer(fbo)) {
        glBindFramebuffer( target, fbo );

        do {
            glGetIntegerv( GL_DRAW_BUFFER0 + i, &buffer );
            if( buffer != GL_NONE ) {
                CSCI441::LogUtils::log("[FBO]: Shader Output Location %d -> color attachment %d\n", i, buffer - GL_COLOR_ATTACHMENT0 );
                glGetFramebufferAttachmentParameteriv( target, buffer, GL_FRAMEBUFFER_ATTACHMENT_OBJECT_TYPE, &res );
                CSCI441::LogUtils::log("[FBO]:  \tAttachment Type: %s\n", res == GL_TEXTURE ? "Texture" : "Render Buffer" );
                glGetFramebufferAttachmentParameteriv( target, buffer, GL_FRAMEBUFFER_ATTACHMENT_OBJECT_NAME, &res );
                CSCI441::LogUtils::log("[FBO]:  \tAttachment object name: %d\n", res );
            }
            ++i;
        } while( buffer != GL_NONE );
    } else {
	    CSCI441::LogUtils::logError("[FBO]: Error: %d is not a framebuffer\n", fbo);
	}
}

[[maybe_unused]]
inline void CSCI441::FramebufferUtils::printFramebufferStatusMessage( const GLenum target, const GLuint fbo ) {
    if(glIsFramebuffer(fbo)) {
        glBindFramebuffer( target, fbo );
        printFramebufferStatusMessage(target);
    } else {
        CSCI441::LogUtils::logError("[FBO]: Error: %d is not a framebuffer\n", fbo);
    }
}

inline void CSCI441::FramebufferUtils::printFramebufferStatusMessage( const GLenum target ) {
	GLenum status = glCheckFramebufferStatus( target );
	if( status == GL_FRAMEBUFFER_COMPLETE )
		CSCI441::LogUtils::log("[FBO]: Framebuffer initialized completely!\n" );
	else {
		CSCI441::LogUtils::logError("[FBO]: Framebuffer failed to initialize completely 0x%x.\n", status );

		switch(status) {
		case GL_FRAMEBUFFER_INCOMPLETE_ATTACHMENT:
          CSCI441::LogUtils::logError("[FBO]: An attachment could not be bound to framebuffer object!\n");
		  break;

		case GL_FRAMEBUFFER_INCOMPLETE_MISSING_ATTACHMENT:
		  CSCI441::LogUtils::logError("[FBO]: Attachments are missing! At least one image (texture) must be bound to the framebuffer object!\n");
		  break;

		case GL_FRAMEBUFFER_INCOMPLETE_DIMENSIONS_EXT:
		  CSCI441::LogUtils::logError("[FBO]: The dimensions of the buffers attached to the currently used framebuffer object do not match!\n");
		  break;

		case GL_FRAMEBUFFER_INCOMPLETE_FORMATS_EXT:
		  CSCI441::LogUtils::logError("[FBO]: The formats of the currently used framebuffer object are not supported or do not fit together!\n");
		  break;

		case GL_FRAMEBUFFER_INCOMPLETE_DRAW_BUFFER:
		  CSCI441::LogUtils::logError("[FBO]: A Draw buffer is incomplete or undefined. All draw buffers must specify attachment points that have images attached.\n");
		  break;

		case GL_FRAMEBUFFER_INCOMPLETE_READ_BUFFER:
		  CSCI441::LogUtils::logError("[FBO]: A Read buffer is incomplete or undefined. All read buffers must specify attachment points that have images attached.\n");
		  break;

		case GL_FRAMEBUFFER_INCOMPLETE_MULTISAMPLE:
		  CSCI441::LogUtils::logError("[FBO]: All images must have the same number of multisample samples.\n");
		  break;

		case GL_FRAMEBUFFER_INCOMPLETE_LAYER_TARGETS :
		  CSCI441::LogUtils::logError("[FBO]: If a layered image is attached to one attachment, then all attachments must be layered attachments. The attached layers do not have to have the same number of layers, nor do the layers have to come from the same kind of texture.\n");
		  break;

		case GL_FRAMEBUFFER_UNSUPPORTED:
		  CSCI441::LogUtils::logError("[FBO]: Attempt to use an unsupported format combination!\n");
		  break;

		default:
		  CSCI441::LogUtils::logError("[FBO]: Unknown error while attempting to create framebuffer object!\n");
		  break;
		}
	}
}

#endif // CSCI441_FRAMEBUFFER_UTILS_HPP
