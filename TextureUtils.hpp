/** @file TextureUtils.hpp
 * @brief Helper functions to work with OpenGL Textures
 * @author Dr. Jeffrey Paone
 *
 * @copyright MIT License Copyright (c) 2017 Dr. Jeffrey Paone
 *
 *	These functions, classes, and constants help minimize common
 *	code that needs to be written.
 *
 *	@warning This header file depends upon GLAD (or alternatively GLEW)
 *	@warning This header file depends upon stb_image
 */

#ifndef CSCI441_TEXTURE_UTILS_HPP
#define CSCI441_TEXTURE_UTILS_HPP

#include "constants.h"

#ifdef CSCI441_USE_GLEW
    #include <GL/glew.h>
#else
    #include <glad/gl.h>
#endif

#include <stb_image.h>

#include <cstdio>
#include <cstring>
#include <string>

//**********************************************************************************

namespace CSCI441 {

	/**
	 * @namespace TextureUtils
	 * @brief OpenGL Texture Utility functions
	 */
	namespace TextureUtils {

        /**
		 * @brief loads a PPM into memory
		 * @brief This function reads an ASCII PPM, returning true if the function succeeds and
		 * false if it fails. If it succeeds, the variables imageWidth and
		 * imageHeight will hold the width and height of the read image, respectively.<br><br>
		 * Returns the image as an unsigned character array containing
		 * imageWidth*imageHeight*3 entries (for that many bytes of storage).
		 * @warning This function expects imageData to be UNALLOCATED, and will allocate
		 * memory itself. If the function fails (returns false), imageData
		 * will be set to NULL and any allocated memory will be automatically deallocated.
		 * @param[in] filename name of the image to load
		 * @param[out] imageWidth will contain the image width upon successful completion
		 * @param[out] imageHeight will contain the image height upon successful completion
		 * @param[out] imageData will contain the RGB data upon successful completion
		 * @pre imageData is unallocated
		 * @returns true if loading succeeded, false otherwise
         * @note it's not terribly robust
         */
		bool loadPPM( const char *filename, int &imageWidth, int &imageHeight, unsigned char* &imageData );

        /**
		 * @brief loads and registers a texture into memory returning a texture handle
         * @note Calls through to loadAndRegister2DTexture()
         * @param filename name of texture to load
         * @param minFilter minification filter to apply (default: GL_LINEAR)
         * @param magFilter magnification filter to apply (default: GL_LINEAR)
         * @param wrapS wrapping to apply to S coordinate (default: GL_REPEAT)
         * @param wrapT wrapping to apply to T coordinate (default: GL_REPEAT)
         * @param flipOnY flip the image along the vertical on load (default: GL_TRUE)
         * @param printAllMessages prints debug/error messages to terminal (default: GL_TRUE)
         * @param enableMipmaps create mipmaps for texture (default: GL_TRUE)
         * @param enableAniso enable anisotropic filtering for mipmaps (default: GL_TRUE)
         * @returns texture handle corresponding to the texture
         */
		[[maybe_unused]] GLuint loadAndRegisterTexture( const char *filename,
                                       GLint minFilter = GL_LINEAR,
                                       GLint magFilter = GL_LINEAR,
                                       GLint wrapS = GL_REPEAT,
                                       GLint wrapT = GL_REPEAT,
                                       GLboolean flipOnY = GL_TRUE,
                                       GLboolean printAllMessages = GL_TRUE,
                                       GLboolean enableMipmaps = GL_TRUE,
                                       GLboolean enableAniso = GL_TRUE);

        /**
		 * @brief loads and registers a texture into memory returning a texture handle
		 * @brief This function loads a texture into memory and registers the texture with
		 * OpenGL.  The provided minification and magnification filters are set for
		 * the texture.  The texture coordinate wrapping parameters are also set.
		 * @param filename name of texture to load
		 * @param minFilter minification filter to apply (default: GL_LINEAR)
		 * @param magFilter magnification filter to apply (default: GL_LINEAR)
		 * @param wrapS wrapping to apply to S coordinate (default: GL_REPEAT)
		 * @param wrapT wrapping to apply to T coordinate (default: GL_REPEAT)
         * @param flipOnY flip the image along the vertical on load (default: GL_TRUE)
         * @param printAllMessages prints debug/error messages to terminal (default: GL_TRUE)
         * @param enableMipmaps create mipmaps for texture (default: GL_TRUE)
         * @param enableAniso enable anisotropic filtering for mipmaps (default: GL_TRUE)
		 * @returns texture handle corresponding to the texture
         */
		GLuint loadAndRegister2DTexture( const char *filename,
                                         GLint minFilter = GL_LINEAR,
                                         GLint magFilter = GL_LINEAR,
                                         GLint wrapS = GL_REPEAT,
                                         GLint wrapT = GL_REPEAT,
                                         GLboolean flipOnY = GL_TRUE,
                                         GLboolean printAllMessages = GL_TRUE,
                                         GLboolean enableMipmaps = GL_TRUE,
                                         GLboolean enableAniso = GL_TRUE);

        /**
		 * @brief loads a texture into memory of a cube face
		 * @param cubeMapFace face of the Cube Map to load the texture to
		 * @param filename name of image to load texture from
		 * @warning Cube Map must be bound as active texture before calling
         */
        [[maybe_unused]] void loadCubeMapFaceTexture(GLint cubeMapFace, const char* filename);
	}
}

//**********************************************************************************
// Outward facing function implementations

inline bool CSCI441::TextureUtils::loadPPM( const char *filename, int &imageWidth, int &imageHeight, unsigned char* &imageData ) {
    FILE *fp = fopen(filename, "r");
    int temp, maxValue;
    fscanf(fp, "P%d", &temp);
    if(temp != 3) {
        fprintf(stderr, "[ERROR]: CSCI441::TextureUtils::loadPPM(): PPM file is not of correct format! (Must be P3, is P%d.)\n", temp);
        fclose(fp);
        return false;
    }

    //got the file header right...
    fscanf(fp, "%d", &imageWidth);
    fscanf(fp, "%d", &imageHeight);
    fscanf(fp, "%d", &maxValue);

    //now that we know how big it is, allocate the buffer...
    imageData = new unsigned char[imageWidth*imageHeight*3];
    if(!imageData) {
        fprintf(stderr, "[ERROR]: CSCI441::TextureUtils::loadPPM(): couldn't allocate image memory. Dimensions: %d x %d.\n", imageWidth, imageHeight);
        fclose(fp);
        return false;
    }

    //and read the data in.
    for(int j = 0; j < imageHeight; j++) {
        for(int i = 0; i < imageWidth; i++) {
            int r, g, b;
            fscanf(fp, "%d", &r);
            fscanf(fp, "%d", &g);
            fscanf(fp, "%d", &b);

            imageData[(j*imageWidth+i)*3+0] = r;
            imageData[(j*imageWidth+i)*3+1] = g;
            imageData[(j*imageWidth+i)*3+2] = b;
        }
    }

    fclose(fp);
    return true;
}

[[maybe_unused]]
inline GLuint CSCI441::TextureUtils::loadAndRegisterTexture( const char *filename, const GLint minFilter, const GLint magFilter, const GLint wrapS, const GLint wrapT, const GLboolean flipOnY, const GLboolean printAllMessages, const GLboolean enableMipmaps, const GLboolean enableAniso ) {
	return loadAndRegister2DTexture( filename, minFilter, magFilter, wrapS, wrapT, flipOnY, printAllMessages, enableMipmaps, enableAniso );
}

inline GLuint CSCI441::TextureUtils::loadAndRegister2DTexture( const char *filename, const GLint minFilter, const GLint magFilter, const GLint wrapS, const GLint wrapT, const GLboolean flipOnY, const GLboolean printAllMessages, const GLboolean enableMipmaps, const GLboolean enableAniso ) {
    int imageWidth, imageHeight, imageChannels;
    GLuint texHandle = 0;
    stbi_set_flip_vertically_on_load(flipOnY);
    unsigned char *data = stbi_load( filename, &imageWidth, &imageHeight, &imageChannels, 0);

	if( !data ) {
        if( strstr(filename, ".ppm") != NULL ) {
            loadPPM(filename, imageWidth, imageHeight, data);
            imageChannels = 3;
        }
        if( !data ) {
            if(printAllMessages) printf( "[ERROR]: CSCI441::TextureUtils::loadAndRegister2DTexture(): Could not load texture \"%s\"\n", filename );
            return texHandle;
        }
	}

    glGenTextures(1, &texHandle );
    glBindTexture(   GL_TEXTURE_2D,  texHandle );
    glTexParameteri( GL_TEXTURE_2D,  GL_TEXTURE_MIN_FILTER, minFilter );
    glTexParameteri( GL_TEXTURE_2D,  GL_TEXTURE_MAG_FILTER, magFilter );
    glTexParameteri( GL_TEXTURE_2D,  GL_TEXTURE_WRAP_S,     wrapS );
    glTexParameteri( GL_TEXTURE_2D,  GL_TEXTURE_WRAP_T,     wrapT );
    const GLint STORAGE_TYPE = (imageChannels == 4 ? GL_RGBA : GL_RGB);
    glTexImage2D( GL_TEXTURE_2D, 0, STORAGE_TYPE, imageWidth, imageHeight, 0, STORAGE_TYPE, GL_UNSIGNED_BYTE, data);

    if(enableMipmaps) glGenerateMipmap(GL_TEXTURE_2D);

    if(enableAniso) {
        // anisotropic filtering became core in OpenGL 4.6, but was widely supported via extensions prior to then
        GLint major = 0, minor = 0;
        glGetIntegerv(GL_MAJOR_VERSION, &major);
        glGetIntegerv(GL_MINOR_VERSION, &minor);
        // check if anisotropic filtering is enabled
        if( (major > 4 || (major == 4 && minor >= 6)) || GL_EXT_texture_filter_anisotropic ) {
            GLfloat maxAniso = 1.0f;
            glGetFloatv(GL_MAX_TEXTURE_MAX_ANISOTROPY_EXT, &maxAniso);
            glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MAX_ANISOTROPY_EXT, maxAniso);
        }
    }

    printf( "[INFO]: Successfully loaded texture \"%s\" with handle %d\n", filename, texHandle );

	return texHandle;
}

[[maybe_unused]]
inline void CSCI441::TextureUtils::loadCubeMapFaceTexture(const GLint cubeMapFace, const char* FILENAME) {
    int imageWidth, imageHeight, imageChannels;
    unsigned char *data = stbi_load( FILENAME, &imageWidth, &imageHeight, &imageChannels, 0);

    if( data ) {
        const GLint STORAGE_TYPE = (imageChannels == 4 ? GL_RGBA : GL_RGB);
        glTexImage2D(cubeMapFace, 0, STORAGE_TYPE, imageWidth, imageHeight, 0, STORAGE_TYPE, GL_UNSIGNED_BYTE, data);
        stbi_image_free(data);
    } else {
        fprintf( stderr, "[ERROR]: CSCI441::TextureUtils::loadCubeMapFaceTexture(): Could not load texture map \"%s\"\n", FILENAME );
    }
}

#endif // CSCI441_TEXTURE_UTILS_HPP
