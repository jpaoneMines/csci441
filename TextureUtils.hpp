/** @file TextureUtils.hpp
  * @brief Helper functions to work with OpenGL Textures
	* @author Dr. Jeffrey Paone
	* @date Last Edit: 03 Nov 2017
	* @version 1.5
	*
	* @copyright MIT License Copyright (c) 2017 Dr. Jeffrey Paone
	*
	*	These functions, classes, and constants help minimize common
	*	code that needs to be written.
  */

#ifndef __CSCI441_TEXTUREUTILS_H__
#define __CSCI441_TEXTUREUTILS_H__

#ifdef __APPLE__
	#include <OpenGL/gl.h>
#else
	#include <GL/gl.h>
#endif

#include <SOIL/SOIL.h>

#include <stdio.h>

#include <string>
using namespace std;

////////////////////////////////////////////////////////////////////////////////////

/** @namespace CSCI441
  * @brief CSCI441 Helper Functions for OpenGL
	*/
namespace CSCI441 {
	/** @namespace TextureUtils
	  * @brief OpenGL Texture Utility functions
	  */
	namespace TextureUtils {
		/**	@brief loads a BMP into memory
			*
			*  This function reads an ASCII BMP, returning true if the function succeeds and
			*      false if it fails. If it succeeds, the variables imageWidth and
			*      imageHeight will hold the width and height of the read image, respectively.
			*
			*  It's not terribly robust.
			*
			*  Returns the image as an unsigned character array containing
			*      imageWidth*imageHeight*3 entries (for that many bytes of storage).
			*
			*  NOTE: this function expects imageData to be UNALLOCATED, and will allocate
			*      memory itself. If the function fails (returns false), imageData
			*      will be set to NULL and any allocated memory will be automatically deallocated.
			*
			*	@param[in] const char* filename	- filename of the image to load
			* @param[out] int &imageWidth			-	will contain the image width upon successful completion
			* @param[out] int &imageHeight		- will contain the image height upon successful completion
			* @param[out] unsigned char* &imageData - will contain the RGB data upon successful completion
			* @param[in] const char* path 		- path to where file is stored.  defaults to current directory
			* @pre imageData is unallocated
			* @return bool - true if loading succeeded, false otherwise
			*/
		bool loadBMP( const char* filename, int &imageWidth, int &imageHeight, int &imageChannels, unsigned char* imageData, const char* path = "./" );

		/**	@brief loads a PPM into memory
			*
			*  This function reads an ASCII PPM, returning true if the function succeeds and
			*      false if it fails. If it succeeds, the variables imageWidth and
			*      imageHeight will hold the width and height of the read image, respectively.
			*
			*  It's not terribly robust.
			*
			*  Returns the image as an unsigned character array containing
			*      imageWidth*imageHeight*3 entries (for that many bytes of storage).
			*
			*  NOTE: this function expects imageData to be UNALLOCATED, and will allocate
			*      memory itself. If the function fails (returns false), imageData
			*      will be set to NULL and any allocated memory will be automatically deallocated.
			*
			*	@param[in] const char *filename	- filename of the image to load
			* @param[out] int &imageWidth			-	will contain the image width upon successful completion
			* @param[out] int &imageHeight		- will contain the image height upon successful completion
			* @param[out] unsigned char* &imageData - will contain the RGB data upon successful completion
			* @pre imageData is unallocated
			* @return bool - true if loading succeeded, false otherwise
			*/
		bool loadPPM( const char *filename, int &imageWidth, int &imageHeight, unsigned char* &imageData );

		/**	@brief loads a TGA into memory
			*
			*  This function reads an ASCII TGA, returning true if the function succeeds and
			*      false if it fails. If it succeeds, the variables imageWidth and
			*      imageHeight will hold the width and height of the read image, respectively.
			*
			*  It's not terribly robust.
			*
			*  Returns the image as an unsigned character array containing
			*      imageWidth*imageHeight*3 entries (for that many bytes of storage).
			*
			*  NOTE: this function expects imageData to be UNALLOCATED, and will allocate
			*      memory itself. If the function fails (returns false), imageData
			*      will be set to NULL and any allocated memory will be automatically deallocated.
			*
			*	@param[in] const char *filename	- filename of the image to load
			* @param[out] int &imageWidth			-	will contain the image width upon successful completion
			* @param[out] int &imageHeight		- will contain the image height upon successful completion
			* @param[out] unsigned char* &imageData - will contain the RGB data upon successful completion
			* @param[out] int &imageChannels  - will contain the number of channels in the image upon successful completion
			* @pre imageData is unallocated
			* @return bool - true if loading succeeded, false otherwise
			*/
		bool loadTGA( const char *filename, int &imageWidth, int &imageHeight, unsigned char* &imageData, int &imageChannels );

		/**	@brief loads and registers a texture into memory returning a texture handle
			*
			*  Equivalent to loadAndRegister2DTexture()
			*/
		GLuint loadAndRegisterTexture( const char *filename,
																		GLenum minFilter = GL_LINEAR,
																		GLenum magFilter = GL_LINEAR,
																		GLenum wrapS = GL_REPEAT,
																		GLenum wrapT = GL_REPEAT );

		/**	@brief loads and registers a texture into memory returning a texture handle
			*
			*  This function loads a texture into memory and registers the texture with
			* OpenGL.  The provided minification and magnification filters are set for
			* the texture.  The texture coordinate wrapping parameters are also set.
			*
			*	@param const char* filename - name of texture to load
			* @param GLenum minFilter     - minification filter to apply (default: GL_LINEAR)
			* @param GLenum magFilter     - magnification filter to apply (default: GL_LINEAR)
			* @param GLenum wrapS         - wrapping to apply to S coordinate (default: GL_REPEAT)
			* @param GLenum wrapT         - wrapping to apply to T coordinate (default: GL_REPEAT)
			* @return GLuint 						  - texture handle corresponding to the texture
			*/
		GLuint loadAndRegister2DTexture( const char *filename,
														  				GLenum minFilter = GL_LINEAR,
															  			GLenum magFilter = GL_LINEAR,
																  		GLenum wrapS = GL_REPEAT,
																	  	GLenum wrapT = GL_REPEAT );
	}
}

////////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////
// Outward facing function implementations

inline bool CSCI441::TextureUtils::loadBMP( const char* filename, int &imageWidth, int &imageHeight, int &imageChannels, unsigned char* imageData, const char* path ) {
	FILE *file;
	unsigned long size;                 // size of the image in bytes.
	size_t i;							// standard counter.
	unsigned short int planes;          // number of planes in image (must be 1)
	unsigned short int bpp;             // number of bits per pixel (must be 24)
	char temp;                          // used to convert bgr to rgb color.

	// make sure the file is there.
	if ((file = fopen(filename, "rb"))==NULL) {
		string folderName = string(path) + string(filename);
		if ((file = fopen(folderName.c_str(), "rb")) == NULL ) {
			printf("[.bmp]: [ERROR]: File Not Found: %s\n",filename);
			return false;
		}
	}

	// seek through the bmp header, up to the width/height:
	fseek(file, 18, SEEK_CUR);

	// read the width
	if ((i = fread(&imageWidth, 4, 1, file)) != 1) {
		printf("[.bmp]: [ERROR]: reading width from %s.\n", filename);
		return false;
	}
	//printf("Width of %s: %lu\n", filename, image->sizeX);

	// read the height
	if ((i = fread(&imageHeight, 4, 1, file)) != 1) {
		printf("[.bmp]: [ERROR]: reading height from %s.\n", filename);
		return false;
	}
	//printf("Height of %s: %lu\n", filename, image->sizeY);

	// calculate the size (assuming 24 bits or 3 bytes per pixel).
	size = imageWidth * imageHeight * 3;

	// read the planes
	if ((fread(&planes, 2, 1, file)) != 1) {
		printf("[.bmp]: [ERROR]: reading planes from %s.\n", filename);
		return false;
	}
	if (planes != 1) {
		printf("[.bmp]: [ERROR]: Planes from %s is not 1: %u\n", filename, planes);
		return false;
	}

	// read the bpp
	if ((i = fread(&bpp, 2, 1, file)) != 1) {
		printf("[.bmp]: [ERROR]: reading bpp from %s.\n", filename);
		return false;
	}
	if (bpp != 24) {
		printf("[.bmp]: [ERROR]: Bpp from %s is not 24: %u\n", filename, bpp);
		return false;
	}

	// seek past the rest of the bitmap header.
	fseek(file, 24, SEEK_CUR);

	// read the data.
	imageData = (unsigned char *) malloc(size);
	if (imageData == NULL) {
		printf("[.bmp]: [ERROR]: allocating memory for color-corrected image data");
		return false;
	}

	if ((i = fread(imageData, size, 1, file)) != 1) {
		printf("[.bmp]: [ERROR]: reading image data from %s.\n", filename);
		return false;
	}

	for (i=0;i<size;i+=3) { // reverse all of the colors. (bgr -> rgb)
		temp = imageData[i];
		imageData[i] = imageData[i+2];
		imageData[i+2] = temp;
	}

	imageChannels = 3;

	return true;
}

inline bool CSCI441::TextureUtils::loadPPM( const char *filename, int &imageWidth, int &imageHeight, unsigned char* &imageData ) {
    FILE *fp = fopen(filename, "r");
    int temp, maxValue;
    fscanf(fp, "P%d", &temp);
    if(temp != 3) {
        fprintf(stderr, "Error: PPM file is not of correct format! (Must be P3, is P%d.)\n", temp);
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
        fprintf(stderr, "Error: couldn't allocate image memory. Dimensions: %d x %d.\n", imageWidth, imageHeight);
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

inline bool CSCI441::TextureUtils::loadTGA(const char *filename, int &imageWidth, int &imageHeight, unsigned char* &imageData, int &imageChannels ) {
	FILE *fp = fopen(filename, "rb");
	if(!fp) {
		fprintf(stderr, "Error: could not open TGA file: %s.", filename);
		imageData = NULL;
		return false;
	}

	//bunch of data fields in the file header that we read in en masse
	unsigned char idLength, colorMapType, imageType;
	unsigned short idxOfFirstColorMapEntry, countOfColorMapEntries;
	unsigned char numBitsPerColorMapEntry;
	unsigned short xCoordOfLowerLeft, yCoordOfLowerLeft;
	unsigned short width, height;
	unsigned char bytesPerPixel;
	unsigned char imageAttributeFlags;

	fread(&idLength, sizeof(unsigned char), 1, fp);
	fread(&colorMapType, sizeof(unsigned char), 1, fp);
	fread(&imageType, sizeof(unsigned char), 1, fp);
	fread(&idxOfFirstColorMapEntry, sizeof(unsigned short), 1, fp);
	fread(&countOfColorMapEntries, sizeof(unsigned short), 1, fp);
	fread(&numBitsPerColorMapEntry, sizeof(unsigned char), 1, fp);
	fread(&xCoordOfLowerLeft, sizeof(unsigned short), 1, fp);
	fread(&yCoordOfLowerLeft, sizeof(unsigned short), 1, fp);
	fread(&width, sizeof(unsigned short), 1, fp);
	fread(&height, sizeof(unsigned short), 1, fp);
	fread(&bytesPerPixel, sizeof(unsigned char), 1, fp);
	fread(&imageAttributeFlags, sizeof(unsigned char), 1, fp);

	//now check to make sure that we actually have the capability to read this file.
	if(colorMapType != 0) {
		fprintf(stderr, "Error: TGA file (%s) uses colormap instead of RGB/RGBA data; this is unsupported.\n", filename);
		imageData = NULL;
		return false;
	}

	if(imageType != 2 && imageType != 10) {
		fprintf(stderr, "Error: unspecified TGA type: %d. Only supports 2 (uncompressed RGB/A) and 10 (RLE, RGB/A).\n", imageType);
		imageData = NULL;
		return false;
	}

	if(bytesPerPixel != 24 && bytesPerPixel != 32) {
		fprintf(stderr, "Error: unsupported image depth (%d bits per pixel). Only supports 24bpp and 32bpp.\n", bytesPerPixel);
		imageData = NULL;
		return false;
	}


	//set some helpful variables based on the header information:
	bool usingRLE = (imageType == 10);              //whether the file uses run-length encoding (compression)
	imageChannels = (bytesPerPixel == 32 ? 4 : 3);                //whether the file is RGB or RGBA (RGBA = 32bpp)
	bool topLeft = (imageAttributeFlags & 32);      //whether the origin is at the top-left or bottom-left


	//this should never happen, since we should never have a color map,
	//but just in case the data is setting around in there anyway... skip it.
	if(idLength != 0) {
		fseek(fp, idLength, SEEK_CUR);
	}


	//allocate our image data before we get started.
	imageWidth = width;
	imageHeight = height;
	imageData = new unsigned char[imageWidth*imageHeight*imageChannels];

	//ok so we can assume at this point that there's no colormap, and
	//consequently that the next part of the image is the actual image data.
	if(usingRLE) {
		//ok... the data comes in in packets, but we don't know how many of these there'll be.
		int numberOfPixelsRead = 0;
		unsigned char dummy;
		while(numberOfPixelsRead < imageWidth*imageHeight) {
			//alright let's read the packet header.
			fread(&dummy, sizeof(unsigned char), 1, fp);
			bool isRLEPacket = (dummy & 0x80);

			unsigned char theOtherBitsYesThatWasAPun = (dummy & 0x7F);
			if(isRLEPacket) {
				//the other bits (+1) gives the number of times we need to
				//repeat the next real set of color values (RGB/A).
				unsigned char repeatedR, repeatedG, repeatedB, repeatedA;
				fread(&repeatedR, sizeof(unsigned char), 1, fp);
				fread(&repeatedG, sizeof(unsigned char), 1, fp);
				fread(&repeatedB, sizeof(unsigned char), 1, fp);
				if(imageChannels==4) fread(&repeatedA, sizeof(unsigned char), 1, fp);

				//and go ahead and copy those into the new image. repetitively.
				for(int i = 0; i < ((int)theOtherBitsYesThatWasAPun+1); i++) {
					int idx = numberOfPixelsRead * imageChannels;
					imageData[idx+2] = repeatedR;
					imageData[idx+1] = repeatedG;
					imageData[idx+0] = repeatedB;
					if(imageChannels==4) imageData[idx+3] = repeatedA;

					numberOfPixelsRead++;
				}
			} else {
				//the other bits (+1) gives the number of consecutive
				//pixels we get to read in from the stream willy nilly.
				for(int i = 0; i < ((int)theOtherBitsYesThatWasAPun+1); i++) {
					int idx = numberOfPixelsRead * imageChannels;
					fread(&imageData[idx+2], sizeof(unsigned char), 1, fp);
					fread(&imageData[idx+1], sizeof(unsigned char), 1, fp);
					fread(&imageData[idx+0], sizeof(unsigned char), 1, fp);
					if(imageChannels==4) fread(&imageData[idx+3], sizeof(unsigned char), 1, fp);

					numberOfPixelsRead++;
				}
			}
		}


		//and you know what? we're not going to have worried about flipping the image before
		//if its origin was in the bottom left or top left or whatever. flip it afterwards here if need be.
		if(!topLeft) {
			unsigned char *tempCopy = new unsigned char[imageWidth*imageHeight*imageChannels];
			for(int i = 0; i < imageHeight; i++) {
				for(int j = 0; j < imageWidth; j++) {
					int copyIdx = (i*imageWidth + j)*imageChannels;
					int pullIdx = ((imageHeight - i - 1)*imageWidth + j)*imageChannels;
					tempCopy[copyIdx+0] = imageData[pullIdx+0];
					tempCopy[copyIdx+1] = imageData[pullIdx+1];
					tempCopy[copyIdx+2] = imageData[pullIdx+2];
					if(imageChannels==4) tempCopy[copyIdx+3] = imageData[pullIdx+3];
				}
			}

			delete imageData;
			imageData = tempCopy;
		}

	} else {
		//uh well if we're not using run-length encoding, i guess we'll
		//just try reading bytes in straight like a normal binary file.
		unsigned char byte1, byte2, byte3, maybeEvenByte4;
		for(int i = 0; i < imageHeight; i++) {
			for(int j = 0; j < imageWidth; j++) {
				int multiplierThing = imageChannels;

				//read in the data from file...
				fread(&byte1, sizeof(unsigned char), 1, fp);
				fread(&byte2, sizeof(unsigned char), 1, fp);
				fread(&byte3, sizeof(unsigned char), 1, fp);
				if(imageChannels==4) fread(&maybeEvenByte4, sizeof(unsigned char), 1, fp);

				//flip the vertical index if the origin is in the bottom-left.
				int wutHeight = topLeft ? i : (imageHeight - 1 - i);
				int idx = (wutHeight*imageWidth+j)*multiplierThing;

				//and load that image into file. seems to be BGR instead of RGB...
				imageData[idx+2] = byte1;
				imageData[idx+1] = byte2;
				imageData[idx+0] = byte3;
				if(imageChannels==4) imageData[idx+3] = maybeEvenByte4;
			}
		}
	}

	fclose(fp);
	return true;
}

// loadAndRegisterTexture() ////////////////////////////////////////////////////
//
// Load and register a texture with OpenGL
//
////////////////////////////////////////////////////////////////////////////////
inline GLuint CSCI441::TextureUtils::loadAndRegisterTexture( const char *filename, GLenum minFilter, GLenum magFilter, GLenum wrapS, GLenum wrapT ) {
	return loadAndRegister2DTexture( filename, minFilter, magFilter, wrapS, wrapT );
}

// loadAndRegister2DTexture() ////////////////////////////////////////////////////
//
// Load and register a 2D texture with OpenGL
//
////////////////////////////////////////////////////////////////////////////////
inline GLuint CSCI441::TextureUtils::loadAndRegister2DTexture( const char *filename, GLenum minFilter, GLenum magFilter, GLenum wrapS, GLenum wrapT ) {
	GLuint texHandle = SOIL_load_OGL_texture( filename,
																					 SOIL_LOAD_AUTO,
																					 SOIL_CREATE_NEW_ID,
																					 SOIL_FLAG_MIPMAPS | SOIL_FLAG_INVERT_Y | SOIL_FLAG_NTSC_SAFE_RGB | SOIL_FLAG_COMPRESS_TO_DXT );

	if( texHandle == 0 ) {
			printf( "[ERROR]: Could not load texture \"%s\"\n[SOIL]: %s\n", filename, SOIL_last_result() );
	} else {
			printf( "[INFO]: Successfully loaded texture \"%s\"\n[SOIL]: %s\n", filename, SOIL_last_result() );
			glBindTexture(   GL_TEXTURE_2D,  texHandle );
			glTexParameteri( GL_TEXTURE_2D,  GL_TEXTURE_MIN_FILTER, minFilter );
			glTexParameteri( GL_TEXTURE_2D,  GL_TEXTURE_MAG_FILTER, magFilter );
			glTexParameteri( GL_TEXTURE_2D,  GL_TEXTURE_WRAP_S,     wrapS );
			glTexParameteri( GL_TEXTURE_2D,  GL_TEXTURE_WRAP_T,     wrapT );
	}

	return texHandle;
}

#endif // __CSCI441_TEXTUREUTILS_H__
