/** @file TextureUtils.hpp
 * @brief Helper functions to work with OpenGL Textures
 * @author Dr. Jeffrey Paone
 *
 * @copyright MIT License Copyright (c) 2017 Dr. Jeffrey Paone
 *
 *	These functions, classes, and constants help minimize common
 *	code that needs to be written.
 */

#ifndef CSCI441_TEXTUREUTILS_HPP
#define CSCI441_TEXTUREUTILS_HPP

#include <GL/glew.h>

#include <stb_image.h>

#include <cstdio>

#include <string>

//**********************************************************************************

/// \namespace CSCI441
/// \desc CSCI441 Helper Functions for OpenGL
namespace CSCI441 {
	/// \namespace TextureUtils
	/// \desc OpenGL Texture Utility functions
	namespace TextureUtils {

		/// \brief loads a PPM into memory
		/// \desc This function reads an ASCII PPM, returning true if the function succeeds and
		/// false if it fails. If it succeeds, the variables imageWidth and
		/// imageHeight will hold the width and height of the read image, respectively.<br><br>
		/// It's not terribly robust.<br><br>
		/// Returns the image as an unsigned character array containing
		/// imageWidth*imageHeight*3 entries (for that many bytes of storage).
		/// \warning This function expects imageData to be UNALLOCATED, and will allocate
		/// memory itself. If the function fails (returns false), imageData
		/// will be set to NULL and any allocated memory will be automatically deallocated.
		/// \param[in] const char* filename of the image to load
		/// \param[out] int will contain the image width upon successful completion
		/// \param[out] int will contain the image height upon successful completion
		/// \param[out] unsigned char* will contain the RGB data upon successful completion
		/// \pre imageData is unallocated
		/// \return bool - true if loading succeeded, false otherwise
		bool loadPPM( const char *filename, int &imageWidth, int &imageHeight, unsigned char* &imageData );

		/// \brief loads and registers a texture into memory returning a texture handle
        /// \desc Calls through to loadAndRegister2DTexture()
        /// \param const char* name of texture to load
        /// \param GLint minification filter to apply (default: GL_LINEAR)
        /// \param GLint magnification filter to apply (default: GL_LINEAR)
        /// \param GLint wrapping to apply to S coordinate (default: GL_REPEAT)
        /// \param GLint wrapping to apply to T coordinate (default: GL_REPEAT)
        /// \return GLuint texture handle corresponding to the texture
		GLuint loadAndRegisterTexture( const char *filename,
                                       GLint minFilter = GL_LINEAR,
                                       GLint magFilter = GL_LINEAR,
                                       GLint wrapS = GL_REPEAT,
                                       GLint wrapT = GL_REPEAT );

		/// \brief loads and registers a texture into memory returning a texture handle
		/// \desc This function loads a texture into memory and registers the texture with
		/// OpenGL.  The provided minification and magnification filters are set for
		/// the texture.  The texture coordinate wrapping parameters are also set.
		/// \param const char* name of texture to load
		/// \param GLint minification filter to apply (default: GL_LINEAR)
		/// \param GLint magnification filter to apply (default: GL_LINEAR)
		/// \param GLint wrapping to apply to S coordinate (default: GL_REPEAT)
		/// \param GLint wrapping to apply to T coordinate (default: GL_REPEAT)
		/// \return GLuint texture handle corresponding to the texture
		GLuint loadAndRegister2DTexture( const char *filename,
                                         GLint minFilter = GL_LINEAR,
                                         GLint magFilter = GL_LINEAR,
                                         GLint wrapS = GL_REPEAT,
                                         GLint wrapT = GL_REPEAT );

		/// \desc loads a texture into memory of a cube face
		/// \param GLint face of the Cube Map to load the texture to
		/// \param const char* filename of image to load texture from
		/// \warning Cube Map must be bound as active texture before calling
        void loadCubeMapFaceTexture(const GLint CUBE_MAP_FACE, const char* FILENAME);
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

inline GLuint CSCI441::TextureUtils::loadAndRegisterTexture( const char *filename, GLint minFilter, GLint magFilter, GLint wrapS, GLint wrapT ) {
	return loadAndRegister2DTexture( filename, minFilter, magFilter, wrapS, wrapT );
}

inline GLuint CSCI441::TextureUtils::loadAndRegister2DTexture( const char *filename, GLint minFilter, GLint magFilter, GLint wrapS, GLint wrapT ) {
    int imageWidth, imageHeight, imageChannels;
    GLuint texHandle = 0;
    stbi_set_flip_vertically_on_load(true);
    unsigned char *data = stbi_load( filename, &imageWidth, &imageHeight, &imageChannels, 0);

	if( !data ) {
        printf( "[ERROR]: CSCI441::TextureUtils::loadAndRegister2DTexture(): Could not load texture \"%s\"\n", filename );
	} else {
        glGenTextures(1, &texHandle );
        glBindTexture(   GL_TEXTURE_2D,  texHandle );
        glTexParameteri( GL_TEXTURE_2D,  GL_TEXTURE_MIN_FILTER, minFilter );
        glTexParameteri( GL_TEXTURE_2D,  GL_TEXTURE_MAG_FILTER, magFilter );
        glTexParameteri( GL_TEXTURE_2D,  GL_TEXTURE_WRAP_S,     wrapS );
        glTexParameteri( GL_TEXTURE_2D,  GL_TEXTURE_WRAP_T,     wrapT );
        const GLint STORAGE_TYPE = (imageChannels == 4 ? GL_RGBA : GL_RGB);
        glTexImage2D( GL_TEXTURE_2D, 0, STORAGE_TYPE, imageWidth, imageHeight, 0, STORAGE_TYPE, GL_UNSIGNED_BYTE, data);
        glGenerateMipmap(GL_TEXTURE_2D);
        printf( "[INFO]: Successfully loaded texture \"%s\" with handle %d\n", filename, texHandle );
    }

	return texHandle;
}

inline void CSCI441::TextureUtils::loadCubeMapFaceTexture(const GLint CUBE_MAP_FACE, const char* FILENAME) {
    int imageWidth, imageHeight, imageChannels;
    unsigned char *data = stbi_load( FILENAME, &imageWidth, &imageHeight, &imageChannels, 0);

    if( data ) {
        const GLint STORAGE_TYPE = (imageChannels == 4 ? GL_RGBA : GL_RGB);
        glTexImage2D(CUBE_MAP_FACE, 0, STORAGE_TYPE, imageWidth, imageHeight, 0, STORAGE_TYPE, GL_UNSIGNED_BYTE, data);
        stbi_image_free(data);
    } else {
        fprintf( stderr, "[ERROR]: CSCI441::TextureUtils::loadCubeMapFaceTexture(): Could not load texture map \"%s\"\n", FILENAME );
    }
}

#endif // CSCI441_TEXTUREUTILS_HPP
