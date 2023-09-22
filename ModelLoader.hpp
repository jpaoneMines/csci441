/** @file ModelLoader.hpp
  * @brief Loads OBJ+MTL, OFF, PLY, STL object files into a VAO
  * @author Dr. Jeffrey Paone
  *
  * @copyright MIT License Copyright (c) 2017 Dr. Jeffrey Paone
  *
  *	This class will load and render object files.  Currently supports:
  *		.obj + .mtl
  *		.off
  *     .ply
  *		.stl
  *
  *	@warning NOTE: This header file will only work with OpenGL 3.0+
  *	@warning NOTE: This header file depends upon GLEW, glm, stb_image
*/

#ifndef CSCI441_MODEL_LOADER_HPP
#define CSCI441_MODEL_LOADER_HPP

#include "modelMaterial.hpp"

#include <GL/glew.h>
#include <glm/glm.hpp>
#include <stb_image.h>

#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <ctime>
#include <fstream>
#include <sstream>
#include <map>
#include <string>
#include <vector>

////////////////////////////////////////////////////////////////////////////////////

namespace CSCI441 {

	/**
	 * @class ModelLoader
     * @brief Loads object models from file and renders using VBOs/VAOs
     */
	class [[maybe_unused]] ModelLoader final {
	public:
		/**
		 * @brief Creates an empty model
         */
		ModelLoader();
		/**
		 * @brief Loads a model from the given file
         * @param filename file to load model from
         */
		[[maybe_unused]] explicit ModelLoader( const char* filename );
		/**
		 * @brief Frees memory associated with model on both CPU and GPU
		 */
		~ModelLoader();

        /**
         * @brief do not allow models to be copied
         */
        ModelLoader(const ModelLoader&) = delete;
        /**
         * @brief do not allow models to be copied
         */
        ModelLoader& operator=(const ModelLoader&) = delete;

		/**
		 * @brief Loads a model from the given file
         * @param filename file to load model from
         * @param INFO flag to control if informational messages should be displayed
         * @param ERRORS flag to control if error messages should be displayed
         * @return true if load succeeded, false otherwise
         */
		bool loadModelFile( const char* filename, bool INFO = true, bool ERRORS = true );

		/**
		 * @brief Enables VBO attribute array locations
		 * @param positionLocation attribute location of vertex position
         * @param normalLocation attribute location of vertex normal
         * @param texCoordLocation attribute location of vertex texture coordinate
		 */
        [[maybe_unused]] void setAttributeLocations(GLint positionLocation, GLint normalLocation = -1, GLint texCoordLocation = -1) const;

        /**
         * @brief Renders a model
         * @param shaderProgramHandle shader program handle that
         * @param matDiffLocation uniform location of material diffuse component
         * @param matSpecLocation uniform location of material specular component
         * @param matShinLocation uniform location of material shininess component
         * @param matAmbLocation uniform location of material ambient component
         * @param diffuseTexture texture number to bind diffuse texture map to
         * @return true if draw succeeded, false otherwise
         */
        [[maybe_unused]] [[nodiscard]] bool draw( GLuint shaderProgramHandle,
                   GLint matDiffLocation = -1, GLint matSpecLocation = -1, GLint matShinLocation = -1, GLint matAmbLocation = -1,
                   GLenum diffuseTexture = GL_TEXTURE0 ) const;

        /**
         * @brief Return the number of vertices the model is made up of.  This value corresponds to the size of the Vertices, TexCoords, and Normals arrays.
         * @return the number of vertices within the model
         */
        [[maybe_unused]] [[nodiscard]] GLuint getNumberOfVertices() const;
		/**
		 * @brief Return the vertex array that makes up the model mesh.
		 * @return pointer to vertex array
		 * @note For use with VBOs
		 */
        [[maybe_unused]] [[nodiscard]] GLfloat* getVertices() const;
		/**
		 * @brief Return the texture coordinates array that corresponds to the model mesh.
		 * @return pointer to texture coordinate array
		 * @note For use with VBOs
		 */
        [[maybe_unused]] [[nodiscard]] GLfloat* getTexCoords() const;
		/**
		 * @brief Return the normal array that corresponds to the model mesh.
		 * @return pointer to the normal array
		 * @note For use with VBOs
		 */
        [[maybe_unused]] [[nodiscard]] GLfloat* getNormals() const;
        /**
         * @brief Return the number of indices to draw the model.  This value corresponds to the size of the Indices array.
         * @return the number of indices when drawing the model
         */
        [[maybe_unused]] [[nodiscard]] GLuint getNumberOfIndices() const;
		/**
		 * @brief Return the index array that dictates the order to draw the model mesh.
		 * @return pointer to the index array
		 * @note For use with IBOs
		 */
        [[maybe_unused]] [[nodiscard]] GLuint* getIndices() const;

		/**
		 * @brief Enable auto-generation of vertex normals
         * @warning Must be called prior to loading in a model from file
         * @note If an object model does not contain vertex normal data, then normals will be computed based on the cross product of vertex winding order.
         * @note No normals are generated by default
         * @note To disable, call disableAutoGenerateNormals
         */
		[[maybe_unused]] static void enableAutoGenerateNormals();
		/**
		 * @brief Disable auto-generation of vertex normals
         * @warning Must be called prior to loading in a model from file
         * @note No normals are generated by default
         * @note To enable, call enableAutoGenerateNormals
         */
		[[maybe_unused]] static void disableAutoGenerateNormals();

	private:
		void _init();
		bool _loadMTLFile( const char *mtlFilename, bool INFO, bool ERRORS );
		bool _loadOBJFile( bool INFO, bool ERRORS );
		bool _loadOFFFile( bool INFO, bool ERRORS );
		bool _loadPLYFile( bool INFO, bool ERRORS );
		bool _loadSTLFile( bool INFO, bool ERRORS );
		static std::vector<std::string> _tokenizeString( std::string input, const std::string& delimiters );

		char* _filename;
		CSCI441_INTERNAL::MODEL_TYPE _modelType;

		GLuint _vaod;
		GLuint _vbods[2];

		GLfloat* _vertices;
		GLfloat* _texCoords;
		GLfloat* _normals;
		GLuint* _indices;
		GLuint _uniqueIndex;
		GLuint _numIndices;

		std::map< std::string, CSCI441_INTERNAL::ModelMaterial* > _materials;
		std::map< std::string, std::vector< std::pair< GLuint, GLuint > > > _materialIndexStartStop;

		bool _hasVertexTexCoords;
		bool _hasVertexNormals;

        static bool _AUTO_GEN_NORMALS;
	};
}

////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////

namespace CSCI441_INTERNAL {
	unsigned char* createTransparentTexture( const unsigned char *imageData, const unsigned char *imageMask, int texWidth, int texHeight, int texChannels, int maskChannels );
	[[maybe_unused]] void flipImageY( int texWidth, int texHeight, int textureChannels, unsigned char *textureData );
}

inline bool CSCI441::ModelLoader::_AUTO_GEN_NORMALS = false;

inline CSCI441::ModelLoader::ModelLoader() {
	_init();
}

[[maybe_unused]]
inline CSCI441::ModelLoader::ModelLoader( const char* filename ) {
	_init();
	loadModelFile( filename );
}

inline CSCI441::ModelLoader::~ModelLoader() {
	if( _vertices ) 			free( _vertices );
	if( _texCoords ) 			free( _texCoords );
	if( _normals ) 				free( _normals );
	if( _indices ) 				free( _indices );

	glDeleteBuffers( 2, _vbods );
    glDeleteVertexArrays( 1, &_vaod );
}

inline void CSCI441::ModelLoader::_init() {
	_hasVertexTexCoords = false;
	_hasVertexNormals = false;

	_vertices = nullptr;
	_texCoords = nullptr;
	_normals = nullptr;
	_indices = nullptr;

	glGenVertexArrays( 1, &_vaod );
	glGenBuffers( 2, _vbods );
}

inline bool CSCI441::ModelLoader::loadModelFile( const char* filename, bool INFO, bool ERRORS ) {
	bool result = true;
	_filename = (char*)malloc(sizeof(char)*strlen(filename));
	strcpy( _filename, filename );
	if( strstr( _filename, ".obj" ) != NULL ) {
		result = _loadOBJFile( INFO, ERRORS );
		_modelType = CSCI441_INTERNAL::OBJ;
	}
	else if( strstr( _filename, ".off" ) != NULL ) {
		result = _loadOFFFile( INFO, ERRORS );
		_modelType = CSCI441_INTERNAL::OFF;
	}
	else if( strstr( _filename, ".ply" ) != NULL ) {
		result = _loadPLYFile( INFO, ERRORS );
		_modelType = CSCI441_INTERNAL::PLY;
	}
	else if( strstr( _filename, ".stl" ) != NULL ) {
		result = _loadSTLFile( INFO, ERRORS );
		_modelType = CSCI441_INTERNAL::STL;
	}
	else {
		result = false;
		if (ERRORS) fprintf( stderr, "[ERROR]:  Unsupported file format for file: %s\n", _filename );
	}

	return result;
}

[[maybe_unused]]
inline void CSCI441::ModelLoader::setAttributeLocations(GLint positionLocation, GLint normalLocation, GLint texCoordLocation) const {
    glBindVertexArray( _vaod );
    glBindBuffer( GL_ARRAY_BUFFER, _vbods[0] );

    glEnableVertexAttribArray( positionLocation );
    glVertexAttribPointer( positionLocation, 3, GL_FLOAT, GL_FALSE, 0, (void*)0 );

    glEnableVertexAttribArray( normalLocation );
    glVertexAttribPointer( normalLocation, 3, GL_FLOAT, GL_FALSE, 0, (void*)(sizeof(GLfloat) * _uniqueIndex * 3) );

    glEnableVertexAttribArray( texCoordLocation );
    glVertexAttribPointer( texCoordLocation, 2, GL_FLOAT, GL_FALSE, 0, (void*)(sizeof(GLfloat) * _uniqueIndex * 6) );
}

[[maybe_unused]]
inline bool CSCI441::ModelLoader::draw( GLuint shaderProgramHandle,
                                        GLint matDiffLocation, GLint matSpecLocation, GLint matShinLocation, GLint matAmbLocation,
                                        GLenum diffuseTexture ) const {
    glBindVertexArray( _vaod );

    bool result = true;
	if( _modelType == CSCI441_INTERNAL::OBJ ) {
		for(const auto & materialIter : _materialIndexStartStop) {
			std::string materialName = materialIter.first;
			std::vector< std::pair< GLuint, GLuint > > indexStartStop = materialIter.second;

			CSCI441_INTERNAL::ModelMaterial* material = nullptr;
			if( _materials.find( materialName ) != _materials.end() )
				material = _materials.find( materialName )->second;

			for(auto & idxIter : indexStartStop) {
				GLuint start = idxIter.first;
				GLuint end = idxIter.second;
				GLuint length = end - start + 1;

//				printf( "rendering material %s (%u, %u) = %u\n", materialName.c_str(), start, end, length );

				if( material != nullptr ) {
					glProgramUniform4fv( shaderProgramHandle, matAmbLocation, 1, material->ambient );
					glProgramUniform4fv( shaderProgramHandle, matDiffLocation, 1, material->diffuse );
					glProgramUniform4fv( shaderProgramHandle, matSpecLocation, 1, material->specular );
					glProgramUniform1f( shaderProgramHandle, matShinLocation, material->shininess );

					if( material->map_Kd != -1 ) {
						glActiveTexture( diffuseTexture );
						glBindTexture( GL_TEXTURE_2D, material->map_Kd );
					}
				}

				glDrawElements( GL_TRIANGLES, length, GL_UNSIGNED_INT, (void*)(sizeof(GLuint)*start) );
			}
		}
	} else {
		glDrawElements( GL_TRIANGLES, _numIndices, GL_UNSIGNED_INT, (void*)0 );
	}

	return result;
}

[[maybe_unused]] inline GLuint CSCI441::ModelLoader::getNumberOfVertices() const { return _uniqueIndex; }
[[maybe_unused]] inline GLfloat* CSCI441::ModelLoader::getVertices() const { return _vertices; }
[[maybe_unused]] inline GLfloat* CSCI441::ModelLoader::getTexCoords() const { return _texCoords; }
[[maybe_unused]] inline GLfloat* CSCI441::ModelLoader::getNormals() const { return _normals; }
[[maybe_unused]] inline GLuint CSCI441::ModelLoader::getNumberOfIndices() const { return _numIndices; }
[[maybe_unused]] inline GLuint* CSCI441::ModelLoader::getIndices() const { return _indices; }

// Read in a WaveFront *.obj File
inline bool CSCI441::ModelLoader::_loadOBJFile( bool INFO, bool ERRORS ) {
	bool result = true;

	if ( INFO ) fprintf( stdout, "[.obj]: -=-=-=-=-=-=-=- BEGIN %s Info -=-=-=-=-=-=-=- \n", _filename );

	time_t start, end;
	time(&start);

	std::ifstream in( _filename );
	if( !in.is_open() ) {
		if (ERRORS) fprintf( stderr, "[.obj]: [ERROR]: Could not open \"%s\"\n", _filename );
		if ( INFO ) fprintf( stdout, "[.obj]: -=-=-=-=-=-=-=-  END %s Info  -=-=-=-=-=-=-=- \n", _filename );
		return false;
	}

	GLuint numObjects = 0, numGroups = 0;
	GLuint numVertices = 0, numTexCoords = 0, numNormals = 0;
	GLuint numFaces = 0, numTriangles = 0;
	GLfloat minX = 999999.0f, maxX = -999999.0f, minY = 999999.0f, maxY = -999999.0f, minZ = 999999.0f, maxZ = -999999.0f;
	std::string line;

	std::map<std::string, GLuint> uniqueCounts;
	_uniqueIndex = 0;

	int progressCounter = 0;

	while( getline( in, line ) ) {
		if( line.length() > 1 && line.at(0) == '\t' )
			line = line.substr( 1 );
		line.erase( line.find_last_not_of( " \n\r\t" ) + 1 );

		std::vector< std::string > tokens = _tokenizeString( line, " \t" );
		if( tokens.empty() ) continue;

		//the line should have a single character that lets us know if it's a...
		if( tokens[0] == "#"  || tokens[0].find_first_of("#") == 0 ) {								// comment ignore
		} else if( tokens[0] == "o" ) {						// object name ignore
			numObjects++;
		} else if( tokens[0] == "g" ) {						// polygon group name ignore
			numGroups++;
		} else if( tokens[0] == "mtllib" ) {					// material library
			_loadMTLFile( tokens[1].c_str(), INFO, ERRORS );
		} else if( tokens[0] == "v" ) {						//vertex
			numVertices++;

			auto x = (GLfloat) atof( tokens[1].c_str() ),
                 y = (GLfloat) atof( tokens[2].c_str() ),
                 z = (GLfloat) atof( tokens[3].c_str() );

			if( x < minX ) minX = x;
			if( x > maxX ) maxX = x;
			if( y < minY ) minY = y;
			if( y > maxY ) maxY = y;
			if( z < minZ ) minZ = z;
			if( z > maxZ ) maxZ = z;
		} else if( tokens[0] == "vn" ) {                    //vertex normal
			numNormals++;
		} else if( tokens[0] == "vt" ) {                    //vertex tex coord
			numTexCoords++;
		} else if( tokens[0] == "f" ) {                     //face!

			//now, faces can be either quads or triangles (or maybe more?)
			//split the string on spaces to get the number of verts+attrs.
			std::vector<std::string> faceTokens = _tokenizeString(line, " ");

			for(GLuint i = 1; i < faceTokens.size(); i++) {
				//need to use both the tokens and number of slashes to determine what info is there.
				std::vector<std::string> groupTokens = _tokenizeString(faceTokens[i], "/");
				int numSlashes = 0;
				for(char j : faceTokens[i]) {
					if(j == '/') numSlashes++;
				}

                std::stringstream currentFaceTokenStream;
                int v = atoi(groupTokens[0].c_str());
                if(v < 0)
                    v = numVertices + v + 1;
                currentFaceTokenStream << v;

				//based on combination of number of tokens and slashes, we can determine what we have.
				if(groupTokens.size() == 2 && numSlashes == 1) {
					_hasVertexTexCoords = true;

                    int vt = atoi(groupTokens[1].c_str());
                    if(vt < 0)
                        vt = numTexCoords + vt + 1;
                    currentFaceTokenStream << "/" << vt;
				} else if(groupTokens.size() == 2 && numSlashes == 2) {
					_hasVertexNormals = true;

                    int vn = atoi(groupTokens[1].c_str());
                    if(vn < 0)
                        vn = numNormals + vn + 1;
                    currentFaceTokenStream << "//" << vn;
				} else if(groupTokens.size() == 3) {
					_hasVertexTexCoords = true;
					_hasVertexNormals = true;

                    int vt = atoi(groupTokens[1].c_str());
                    if(vt < 0)
                        vt = numTexCoords + vt + 1;
                    int vn = atoi(groupTokens[2].c_str());
                    if(vn < 0)
                        vn = numNormals + vn + 1;
                    currentFaceTokenStream << "/" << vt << "/" << vn;
				} else if(groupTokens.size() != 1) {
					if (ERRORS) fprintf(stderr, "[.obj]: [ERROR]: Malformed OBJ file, %s.\n", _filename);
					return false;
				}

                std::string processedFaceToken = currentFaceTokenStream.str();
                if( uniqueCounts.find( processedFaceToken ) == uniqueCounts.end() ) {
                    uniqueCounts.insert( std::pair<std::string,long int>(processedFaceToken,_uniqueIndex) );
                    _uniqueIndex++;
                }
			}

			numTriangles += (faceTokens.size() - 1 - 3 + 1);

			numFaces++;
		} else {

		}

		if (INFO) {
			progressCounter++;
			if( progressCounter % 5000 == 0 ) {
				printf("\33[2K\r");
				switch( progressCounter ) {
					case 5000:	printf("[.obj]: scanning %s...\\", _filename);	break;
					case 10000:	printf("[.obj]: scanning %s...|", _filename);	break;
					case 15000:	printf("[.obj]: scanning %s.../", _filename);	break;
					case 20000:	printf("[.obj]: scanning %s...-", _filename);	break;
                    default: break;
				}
				fflush(stdout);
			}
			if( progressCounter == 20000 )
				progressCounter = 0;
		}
	}
	in.close();

	if (INFO) {
		printf( "\33[2K\r" );
		printf( "[.obj]: scanning %s...done!\n", _filename );
		printf( "[.obj]: ------------\n" );
		printf( "[.obj]: Model Stats:\n" );
		printf( "[.obj]: Vertices:  \t%u\tNormals:  \t%u\tTex Coords:\t%u\n", numVertices, numNormals, numTexCoords );
		printf( "[.obj]: Unique Verts:\t%u\n", _uniqueIndex );
		printf( "[.obj]: Faces:     \t%u\tTriangles:\t%u\n", numFaces, numTriangles );
		printf( "[.obj]: Objects:   \t%u\tGroups:   \t%u\n", numObjects, numGroups );
		printf( "[.obj]: Dimensions:\t(%f, %f, %f)\n", (maxX - minX), (maxY - minY), (maxZ - minZ) );
	}

	if( _hasVertexNormals || !_AUTO_GEN_NORMALS ) {
		if (INFO && !_hasVertexNormals)
			printf( "[.obj]: [WARN]: No vertex normals exist on model.  To autogenerate vertex\n\tnormals, call CSCI441::ModelLoader::enableAutoGenerateNormals()\n\tprior to loading the model file.\n" );
		_vertices = (GLfloat*)malloc(sizeof(GLfloat) * _uniqueIndex * 3);
		_texCoords = (GLfloat*)malloc(sizeof(GLfloat) * _uniqueIndex * 2);
		_normals = (GLfloat*)malloc(sizeof(GLfloat) * _uniqueIndex * 3);
		_indices = (GLuint*)malloc(sizeof(GLuint) * numTriangles * 3);
	} else {
		if (INFO) printf( "[.obj]: No vertex normals exist on model, vertex normals will be autogenerated\n" );
		_vertices = (GLfloat*)malloc(sizeof(GLfloat) * numTriangles * 3 * 3);
		_texCoords = (GLfloat*)malloc(sizeof(GLfloat) * numTriangles * 3 * 2);
		_normals = (GLfloat*)malloc(sizeof(GLfloat) * numTriangles * 3 * 3);
		_indices = (GLuint*)malloc(sizeof(GLuint) * numTriangles * 3);
	}

	auto v  = (GLfloat*)malloc(sizeof(GLfloat) * numVertices * 3);
	auto vt = (GLfloat*)malloc(sizeof(GLfloat) * numTexCoords * 2);
	auto vn = (GLfloat*)malloc(sizeof(GLfloat) * numNormals * 3);

	std::vector<GLfloat> vertsTemp;
	std::vector<GLfloat> texCoordsTemp;

	printf( "[.obj]: ------------\n" );

	uniqueCounts.clear();
	_uniqueIndex = 0;
	_numIndices = 0;

	in.open( _filename );

	GLuint vSeen = 0, vtSeen = 0, vnSeen = 0, indicesSeen = 0;
	GLuint uniqueV = 0;

	std::string currentMaterial = "default";
	_materialIndexStartStop.insert( std::pair< std::string, std::vector< std::pair< GLuint, GLuint > > >( currentMaterial, std::vector< std::pair< GLuint, GLuint > >(1) ) );
	_materialIndexStartStop.find( currentMaterial )->second.back().first = indicesSeen;

	while( getline( in, line ) ) {
		if( line.length() > 1 && line.at(0) == '\t' )
			line = line.substr( 1 );
		line.erase( line.find_last_not_of( " \n\r\t" ) + 1 );

		std::vector< std::string > tokens = _tokenizeString( line, " \t" );
		if( tokens.empty() ) continue;

		//the line should have a single character that lets us know if it's a...
		if( tokens[0] == "#" || tokens[0].find_first_of("#") == 0 ) {								// comment ignore

		} else if( tokens[0] == "o" ) {						// object name ignore

		} else if( tokens[0] == "g" ) {						// polygon group name ignore

		} else if( tokens[0] == "mtllib" ) {					// material library

		} else if( tokens[0] == "usemtl" ) {					// use material library
			if( currentMaterial == "default" && indicesSeen == 0 ) {
				_materialIndexStartStop.clear();
			} else {
				_materialIndexStartStop.find( currentMaterial )->second.back().second = indicesSeen - 1;
			}
			currentMaterial = tokens[1];
			if( _materialIndexStartStop.find( currentMaterial ) == _materialIndexStartStop.end() ) {
				_materialIndexStartStop.insert( std::pair< std::string, std::vector< std::pair< GLuint, GLuint > > >( currentMaterial, std::vector< std::pair< GLuint, GLuint > >(1) ) );
				_materialIndexStartStop.find( currentMaterial )->second.back().first = indicesSeen;
			} else {
				_materialIndexStartStop.find( currentMaterial )->second.push_back( std::pair< GLuint, GLuint >( indicesSeen, -1 ) );
			}
		} else if( tokens[0] == "s" ) {						// smooth shading

		} else if( tokens[0] == "v" ) {						//vertex
			auto x = (GLfloat) atof( tokens[1].c_str() ),
				     y = (GLfloat) atof( tokens[2].c_str() ),
				     z = (GLfloat) atof( tokens[3].c_str() );

			v[vSeen*3 + 0] = x;
			v[vSeen*3 + 1] = y;
			v[vSeen*3 + 2] = z;

			vSeen++;
		} else if( tokens[0] == "vn" ) {                    //vertex normal
			auto x = (GLfloat) atof( tokens[1].c_str() ),
				     y = (GLfloat) atof( tokens[2].c_str() ),
				     z = (GLfloat) atof( tokens[3].c_str() );

			vn[vnSeen*3 + 0] = x;
			vn[vnSeen*3 + 1] = y;
			vn[vnSeen*3 + 2] = z;

			vnSeen++;
		} else if( tokens[0] == "vt" ) {                    //vertex tex coord
			auto s = (GLfloat) atof( tokens[1].c_str() ),
						 t = (GLfloat) atof( tokens[2].c_str() );

		  vt[vtSeen*2 + 0] = s;
			vt[vtSeen*2 + 1] = t;

			vtSeen++;
		} else if( tokens[0] == "f" ) {                     //face!

			//now, faces can be either quads or triangles (or maybe more?)
			//split the string on spaces to get the number of verts+attrs.
			std::vector<std::string> faceTokens = _tokenizeString(line, " ");
            std::vector<std::string> processedFaceTokens;

			for(GLuint i = 1; i < faceTokens.size(); i++) {
                //need to use both the tokens and number of slashes to determine what info is there.
                std::vector<std::string> groupTokens = _tokenizeString(faceTokens[i], "/");
                int numSlashes = 0;
                for(char j : faceTokens[i]) {
                    if(j == '/') numSlashes++;
                }

                std::stringstream currentFaceTokenStream;
                int vx = atoi(groupTokens[0].c_str());
                if(vx < 0)
                    vx = vSeen + vx + 1;
                currentFaceTokenStream << vx;

                //based on combination of number of tokens and slashes, we can determine what we have.
                if(groupTokens.size() == 2 && numSlashes == 1) {
                    _hasVertexTexCoords = true;

                    int vtx = atoi(groupTokens[1].c_str());
                    if(vtx < 0)
                        vtx = vtSeen + vtx + 1;
                    currentFaceTokenStream << "/" << vtx;
                } else if(groupTokens.size() == 2 && numSlashes == 2) {
                    _hasVertexNormals = true;

                    int vnx = atoi(groupTokens[1].c_str());
                    if(vnx < 0)
                        vnx = vnSeen + vnx + 1;
                    currentFaceTokenStream << "//" << vnx;
                } else if(groupTokens.size() == 3) {
                    _hasVertexTexCoords = true;
                    _hasVertexNormals = true;

                    int vtx = atoi(groupTokens[1].c_str());
                    if(vtx < 0)
                        vtx = vtSeen + vtx + 1;
                    int vnx = atoi(groupTokens[2].c_str());
                    if(vnx < 0)
                        vnx = vnSeen + vnx + 1;
                    currentFaceTokenStream << "/" << vtx << "/" << vnx;
                } else if(groupTokens.size() != 1) {
                    if (ERRORS) fprintf(stderr, "[.obj]: [ERROR]: Malformed OBJ file, %s.\n", _filename);
                    return false;
                }

                std::string processedFaceToken = currentFaceTokenStream.str();
                processedFaceTokens.push_back(processedFaceToken);

				if( uniqueCounts.find( processedFaceToken ) == uniqueCounts.end() ) {
					uniqueCounts.insert( std::pair<std::string,unsigned long int>(processedFaceToken,uniqueV) );

					//need to use both the tokens and number of slashes to determine what info is there.
					std::vector<std::string> groupTokens = _tokenizeString(processedFaceToken, "/");
					int numSlashes = 0;
					for(char j : processedFaceToken) {
						if(j == '/') numSlashes++;
					}

					if( _hasVertexNormals || !_AUTO_GEN_NORMALS ) {
						//regardless, we always get a vertex index.
						int vI = atoi(groupTokens[0].c_str());
						if( vI < 0 )
							vI = vSeen + vI + 1;

						_vertices[ _uniqueIndex*3 + 0 ] = v[ ((vI - 1) * 3) + 0 ];
						_vertices[ _uniqueIndex*3 + 1 ] = v[ ((vI - 1) * 3) + 1 ];
						_vertices[ _uniqueIndex*3 + 2 ] = v[ ((vI - 1) * 3) + 2 ];

						//based on combination of number of tokens and slashes, we can determine what we have.
						if(groupTokens.size() == 2 && numSlashes == 1) {
							int vtI = atoi(groupTokens[1].c_str());
							if( vtI < 0 )
								vtI = vtSeen + vtI + 1;

							_texCoords[ _uniqueIndex*2 + 0 ] = vt[ ((vtI - 1) * 2) + 0 ];
							_texCoords[ _uniqueIndex*2 + 1 ] = vt[ ((vtI - 1) * 2) + 1 ];
						} else if(groupTokens.size() == 2 && numSlashes == 2) {
							int vnI = atoi(groupTokens[1].c_str());
							if( vnI < 0 )
								vnI = vnSeen + vnI + 1;

							_normals[ _uniqueIndex*3 + 0 ] = vn[ ((vnI - 1) * 3) + 0 ];
							_normals[ _uniqueIndex*3 + 1 ] = vn[ ((vnI - 1) * 3) + 1 ];
							_normals[ _uniqueIndex*3 + 2 ] = vn[ ((vnI - 1) * 3) + 2 ];
						} else if(groupTokens.size() == 3) {
							int vtI = atoi(groupTokens[1].c_str());
							if( vtI < 0 )
								vtI = vtSeen + vtI + 1;

							_texCoords[ _uniqueIndex*2 + 0 ] = vt[ ((vtI - 1) * 2) + 0 ];
							_texCoords[ _uniqueIndex*2 + 1 ] = vt[ ((vtI - 1) * 2) + 1 ];

							int vnI = atoi(groupTokens[2].c_str());
							if( vnI < 0 )
								vnI = vnSeen + vnI + 1;

							_normals[ _uniqueIndex*3 + 0 ] = vn[ ((vnI - 1) * 3) + 0 ];
							_normals[ _uniqueIndex*3 + 1 ] = vn[ ((vnI - 1) * 3) + 1 ];
							_normals[ _uniqueIndex*3 + 2 ] = vn[ ((vnI - 1) * 3) + 2 ];
						}

						_uniqueIndex++;
					} else {
						//regardless, we always get a vertex index.
						int vI = atoi(groupTokens[0].c_str());
						if( vI < 0 )
							vI = vSeen + vI + 1;

						vertsTemp.push_back( v[ ((vI - 1) * 3) + 0 ] );
						vertsTemp.push_back( v[ ((vI - 1) * 3) + 1 ] );
						vertsTemp.push_back( v[ ((vI - 1) * 3) + 2 ] );

						//based on combination of number of tokens and slashes, we can determine what we have.
						if(groupTokens.size() == 2 && numSlashes == 1) {
							int vtI = atoi(groupTokens[1].c_str());
							if( vtI < 0 )
								vtI = vtSeen + vtI + 1;

							texCoordsTemp.push_back( vt[ ((vtI - 1) * 2) + 0 ] );
							texCoordsTemp.push_back( vt[ ((vtI - 1) * 2) + 1 ] );
						} else if(groupTokens.size() == 2 && numSlashes == 2) {
							// should not occur if no normals
							if (ERRORS) fprintf( stderr, "[.obj]: [WARN]: no vertex normals were specified, should not be trying to access values\n" );
						} else if(groupTokens.size() == 3) {
							int vtI = atoi(groupTokens[1].c_str());
							if( vtI < 0 )
								vtI = vtSeen + vtI + 1;

							texCoordsTemp.push_back( vt[ ((vtI - 1) * 2) + 0 ] );
							texCoordsTemp.push_back( vt[ ((vtI - 1) * 2) + 1 ] );

							// should not occur if no normals
							if (ERRORS) fprintf( stderr, "[.obj]: [WARN]: no vertex normals were specified, should not be trying to access values\n" );
						}
					}
					uniqueV++;
				}
			}

			for(GLuint i = 1; i < processedFaceTokens.size()-1; i++) {
				if( _hasVertexNormals || !_AUTO_GEN_NORMALS ) {
					_indices[ indicesSeen++ ] = uniqueCounts.find( processedFaceTokens[0]   )->second;
					_indices[ indicesSeen++ ] = uniqueCounts.find( processedFaceTokens[i]   )->second;
					_indices[ indicesSeen++ ] = uniqueCounts.find( processedFaceTokens[i+1] )->second;

					_numIndices += 3;
				} else {
					GLuint aI = uniqueCounts.find( processedFaceTokens[0]   )->second;
					GLuint bI = uniqueCounts.find( processedFaceTokens[i]   )->second;
					GLuint cI = uniqueCounts.find( processedFaceTokens[i+1] )->second;

					glm::vec3 a( vertsTemp[aI*3 + 0], vertsTemp[aI*3 + 1], vertsTemp[aI*3 + 2] );
					glm::vec3 b( vertsTemp[bI*3 + 0], vertsTemp[bI*3 + 1], vertsTemp[bI*3 + 2] );
					glm::vec3 c( vertsTemp[cI*3 + 0], vertsTemp[cI*3 + 1], vertsTemp[cI*3 + 2] );

					glm::vec3 ab = b - a;	glm::vec3 ac = c - a;
					glm::vec3 ba = a - b; glm::vec3 bc = c - b;
					glm::vec3 ca = a - c; glm::vec3 cb = b - c;

					glm::vec3 aN = glm::normalize( glm::cross( ab, ac ) );
					glm::vec3 bN = glm::normalize( glm::cross( bc, ba ) );
					glm::vec3 cN = glm::normalize( glm::cross( ca, cb ) );

					_vertices[ _uniqueIndex*3 + 0 ] = a.x;
					_vertices[ _uniqueIndex*3 + 1 ] = a.y;
					_vertices[ _uniqueIndex*3 + 2 ] = a.z;

					_normals[ _uniqueIndex*3 + 0 ] = aN.x;
					_normals[ _uniqueIndex*3 + 1 ] = aN.y;
					_normals[ _uniqueIndex*3 + 2 ] = aN.z;

					if( _hasVertexTexCoords ) {
						_texCoords[ _uniqueIndex*2 + 0 ] = texCoordsTemp[ aI*2 + 0 ];
						_texCoords[ _uniqueIndex*2 + 1 ] = texCoordsTemp[ aI*2 + 1 ];
					}

					_indices[ _numIndices++ ] = _uniqueIndex++;
					indicesSeen++;

					_vertices[ _uniqueIndex*3 + 0 ] = b.x;
					_vertices[ _uniqueIndex*3 + 1 ] = b.y;
					_vertices[ _uniqueIndex*3 + 2 ] = b.z;

					_normals[ _uniqueIndex*3 + 0 ] = bN.x;
					_normals[ _uniqueIndex*3 + 1 ] = bN.y;
					_normals[ _uniqueIndex*3 + 2 ] = bN.z;

					if( _hasVertexTexCoords ) {
						_texCoords[ _uniqueIndex*2 + 0 ] = texCoordsTemp[ bI*2 + 0 ];
						_texCoords[ _uniqueIndex*2 + 1 ] = texCoordsTemp[ bI*2 + 1 ];
					}

					_indices[ _numIndices++ ] = _uniqueIndex++;
					indicesSeen++;

					_vertices[ _uniqueIndex*3 + 0 ] = c.x;
					_vertices[ _uniqueIndex*3 + 1 ] = c.y;
					_vertices[ _uniqueIndex*3 + 2 ] = c.z;

					_normals[ _uniqueIndex*3 + 0 ] = cN.x;
					_normals[ _uniqueIndex*3 + 1 ] = cN.y;
					_normals[ _uniqueIndex*3 + 2 ] = cN.z;

					if( _hasVertexTexCoords ) {
						_texCoords[ _uniqueIndex*2 + 0 ] = texCoordsTemp[ cI*2 + 0 ];
						_texCoords[ _uniqueIndex*2 + 1 ] = texCoordsTemp[ cI*2 + 1 ];
					}

					_indices[ _numIndices++ ] = _uniqueIndex++;
					indicesSeen++;
				}
			}

		} else {
			if (INFO) printf( "[.obj]: ignoring line: %s\n", line.c_str() );
		}

		if (INFO) {
			progressCounter++;
			if( progressCounter % 5000 == 0 ) {
				printf("\33[2K\r");
				switch( progressCounter ) {
					case 5000:	printf("[.obj]: parsing %s...\\", _filename);	break;
					case 10000:	printf("[.obj]: parsing %s...|", _filename);	break;
					case 15000:	printf("[.obj]: parsing %s.../", _filename);	break;
					case 20000:	printf("[.obj]: parsing %s...-", _filename);	break;
                    default: break;
				}
				fflush(stdout);
			}
			if( progressCounter == 20000 )
				progressCounter = 0;
		}
	}

	in.close();

	if (INFO) {
		printf( "\33[2K\r" );
		printf( "[.obj]: parsing %s...done!\n", _filename );
	}

	_materialIndexStartStop.find( currentMaterial )->second.back().second = indicesSeen - 1;

	glBindVertexArray( _vaod );
	glBindBuffer( GL_ARRAY_BUFFER, _vbods[0] );
	glBufferData( GL_ARRAY_BUFFER, sizeof(GLfloat) * _uniqueIndex * 8, nullptr, GL_STATIC_DRAW );
	glBufferSubData( GL_ARRAY_BUFFER, 0, 																  sizeof(GLfloat) * _uniqueIndex * 3, _vertices );
	glBufferSubData( GL_ARRAY_BUFFER, sizeof(GLfloat) * _uniqueIndex * 3, sizeof(GLfloat) * _uniqueIndex * 3, _normals );
	glBufferSubData( GL_ARRAY_BUFFER, sizeof(GLfloat) * _uniqueIndex * 6, sizeof(GLfloat) * _uniqueIndex * 2, _texCoords );

	glBindBuffer( GL_ELEMENT_ARRAY_BUFFER, _vbods[1] );
	glBufferData( GL_ELEMENT_ARRAY_BUFFER, sizeof(GLuint) * indicesSeen, _indices, GL_STATIC_DRAW );

	time(&end);
	double seconds = difftime( end, start );

	if (INFO) {
		printf( "[.obj]: Completed in %.3fs\n", seconds );
		printf( "[.obj]: -=-=-=-=-=-=-=-  END %s Info  -=-=-=-=-=-=-=- \n\n", _filename );
	}

	return result;
}

inline bool CSCI441::ModelLoader::_loadMTLFile( const char* mtlFilename, bool INFO, bool ERRORS ) {
	bool result = true;

	if (INFO) printf( "[.mtl]: -*-*-*-*-*-*-*- BEGIN %s Info -*-*-*-*-*-*-*-\n", mtlFilename );

	std::string line;
	std::string path;
	if( strstr( _filename, "/" ) != NULL ) {
	 	path = std::string( _filename ).substr( 0, std::string(_filename).find_last_of('/')+1 );
	} else {
		path = "./";
	}

	std::ifstream in;
	in.open( mtlFilename );
	if( !in.is_open() ) {
		std::string folderMtlFile = path + mtlFilename;
		in.open( folderMtlFile.c_str() );
		if( !in.is_open() ) {
			if (ERRORS) fprintf( stderr, "[.mtl]: [ERROR]: could not open material file: %s\n", mtlFilename );
			if ( INFO ) printf( "[.mtl]: -*-*-*-*-*-*-*-  END %s Info  -*-*-*-*-*-*-*-\n", mtlFilename );
			return false;
		}
	}

	CSCI441_INTERNAL::ModelMaterial* currentMaterial = nullptr;
	std::string materialName;

	unsigned char *textureData = nullptr;
	unsigned char *maskData = nullptr;
	unsigned char *fullData;
	int texWidth, texHeight, textureChannels = 1, maskChannels = 1;
	GLuint textureHandle = 0;

	std::map< std::string, GLuint > imageHandles;

	int numMaterials = 0;

	while( getline( in, line ) ) {
		if( line.length() > 1 && line.at(0) == '\t' )
			line = line.substr( 1 );
		line.erase( line.find_last_not_of( " \n\r\t" ) + 1 );

		std::vector< std::string > tokens = _tokenizeString( line, " /" );
		if( tokens.empty() ) continue;

		//the line should have a single character that lets us know if it's a...
		if( tokens[0] == "#" ) {							// comment
		} else if( tokens[0] == "newmtl" ) {				//new material
			if (INFO) printf( "[.mtl]: Parsing material %s properties\n", tokens[1].c_str() );
			currentMaterial = new CSCI441_INTERNAL::ModelMaterial();
			materialName = tokens[1];
			_materials.insert( std::pair<std::string, CSCI441_INTERNAL::ModelMaterial*>( materialName, currentMaterial ) );

			textureHandle = 0;
			textureData = nullptr;
			maskData = nullptr;
			textureChannels = 1;
			maskChannels = 1;

			numMaterials++;
		} else if( tokens[0] == "Ka" ) {					// ambient component
			currentMaterial->ambient[0] = atof( tokens[1].c_str() );
			currentMaterial->ambient[1] = atof( tokens[2].c_str() );
			currentMaterial->ambient[2] = atof( tokens[3].c_str() );
		} else if( tokens[0] == "Kd" ) {					// diffuse component
			currentMaterial->diffuse[0] = atof( tokens[1].c_str() );
			currentMaterial->diffuse[1] = atof( tokens[2].c_str() );
			currentMaterial->diffuse[2] = atof( tokens[3].c_str() );
		} else if( tokens[0] == "Ks" ) {					// specular component
			currentMaterial->specular[0] = atof( tokens[1].c_str() );
			currentMaterial->specular[1] = atof( tokens[2].c_str() );
			currentMaterial->specular[2] = atof( tokens[3].c_str() );
		} else if( tokens[0] == "Ke" ) {					// emissive component
			currentMaterial->emissive[0] = atof( tokens[1].c_str() );
			currentMaterial->emissive[1] = atof( tokens[2].c_str() );
			currentMaterial->emissive[2] = atof( tokens[3].c_str() );
		} else if( tokens[0] == "Ns" ) {					// shininess component
			currentMaterial->shininess = atof( tokens[1].c_str() );
		} else if( tokens[0] == "Tr"
					|| tokens[0] == "d" ) {					// transparency component - Tr or d can be used depending on the format
			currentMaterial->ambient[3] = atof( tokens[1].c_str() );
			currentMaterial->diffuse[3] = atof( tokens[1].c_str() );
			currentMaterial->specular[3] = atof( tokens[1].c_str() );
		} else if( tokens[0] == "illum" ) {				    // illumination type component
			// TODO ?
		} else if( tokens[0] == "map_Kd" ) {				// diffuse color texture map
			if( imageHandles.find( tokens[1] ) != imageHandles.end() ) {
				// _textureHandles->insert( pair< string, GLuint >( materialName, imageHandles.find( tokens[1] )->second ) );
				currentMaterial->map_Kd = imageHandles.find( tokens[1] )->second;
			} else {
                stbi_set_flip_vertically_on_load(true);
				textureData = stbi_load( tokens[1].c_str(), &texWidth, &texHeight, &textureChannels, 0 );
				if( !textureData ) {
					std::string folderName = path + tokens[1];
					textureData = stbi_load( folderName.c_str(), &texWidth, &texHeight, &textureChannels, 0 );
				}

				if( !textureData ) {
					if (ERRORS) fprintf( stderr, "[.mtl]: [ERROR]: File Not Found: %s\n", tokens[1].c_str() );
				} else {
					if (INFO) printf( "[.mtl]: TextureMap:\t%s\tSize: %dx%d\tColors: %d\n", tokens[1].c_str(), texWidth, texHeight, textureChannels );

					if( maskData == nullptr ) {
						if( textureHandle == 0 ) {
							glGenTextures( 1, &textureHandle );
							imageHandles.insert( std::pair<std::string, GLuint>( tokens[1], textureHandle ) );
						}

						glBindTexture( GL_TEXTURE_2D, textureHandle );

						glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
						glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

						glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
						glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);

						GLenum colorSpace = GL_RGB;
						if( textureChannels == 4 )
							colorSpace = GL_RGBA;
						glTexImage2D( GL_TEXTURE_2D, 0, colorSpace, texWidth, texHeight, 0, colorSpace, GL_UNSIGNED_BYTE, textureData );

						currentMaterial->map_Kd = textureHandle;
					} else {
						fullData = CSCI441_INTERNAL::createTransparentTexture( textureData, maskData, texWidth, texHeight, textureChannels, maskChannels );

						if( textureHandle == 0 ) {
							glGenTextures( 1, &textureHandle );
							imageHandles.insert( std::pair<std::string, GLuint>( tokens[1], textureHandle ) );
						}

						glBindTexture( GL_TEXTURE_2D, textureHandle );

						glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
						glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

						glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
						glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);

						glTexImage2D( GL_TEXTURE_2D, 0, GL_RGBA, texWidth, texHeight, 0, GL_RGBA, GL_UNSIGNED_BYTE, fullData );

						delete fullData;

						currentMaterial->map_Kd = textureHandle;
					}
				}
			}
		} else if( tokens[0] == "map_d" ) {				// alpha texture map
			if( imageHandles.find( tokens[1] ) != imageHandles.end() ) {
				// _textureHandles->insert( pair< string, GLuint >( materialName, imageHandles.find( tokens[1] )->second ) );
				currentMaterial->map_d = imageHandles.find( tokens[1] )->second;
			} else {
			    stbi_set_flip_vertically_on_load(true);
				maskData = stbi_load( tokens[1].c_str(), &texWidth, &texHeight, &textureChannels, 0 );
				if( !textureData ) {
					std::string folderName = path + tokens[1];
					maskData = stbi_load( folderName.c_str(), &texWidth, &texHeight, &textureChannels, 0 );
				}

				if( !maskData ) {
					if (ERRORS) fprintf( stderr, "[.mtl]: [ERROR]: File Not Found: %s\n", tokens[1].c_str() );
				} else {
					if (INFO) printf( "[.mtl]: AlphaMap:  \t%s\tSize: %dx%d\tColors: %d\n", tokens[1].c_str(), texWidth, texHeight, maskChannels );

					if( textureData != nullptr ) {
						fullData = CSCI441_INTERNAL::createTransparentTexture( textureData, maskData, texWidth, texHeight, textureChannels, maskChannels );

						if( textureHandle == 0 )
							glGenTextures( 1, &textureHandle );

						glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
						glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

						glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
						glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);

						glTexImage2D( GL_TEXTURE_2D, 0, GL_RGBA, texWidth, texHeight, 0, GL_RGBA, GL_UNSIGNED_BYTE, fullData );

						delete fullData;
					}
				}
			}
		} else if( tokens[0] == "map_Ka" ) {				// ambient color texture map

		} else if( tokens[0] == "map_Ks" ) {				// specular color texture map

		} else if( tokens[0] == "map_Ns" ) {				// specular highlight map (shininess map)

		} else if( tokens[0] == "Ni" ) {						// optical density / index of refraction

		} else if( tokens[0] == "Tf" ) {						// transmission filter

		} else if( tokens[0] == "bump"
					|| tokens[0] == "map_bump" ) {				// bump map

		} else {
			if (INFO) printf( "[.mtl]: ignoring line: %s\n", line.c_str() );
		}
	}

	in.close();

	if ( INFO ) {
		printf( "[.mtl]: Materials:\t%d\n", numMaterials );
		printf( "[.mtl]: -*-*-*-*-*-*-*-  END %s Info  -*-*-*-*-*-*-*-\n", mtlFilename );
	}

	return result;
}

inline bool CSCI441::ModelLoader::_loadOFFFile( bool INFO, bool ERRORS ) {
	bool result = true;

	if (INFO ) printf( "[.off]: -=-=-=-=-=-=-=- BEGIN %s Info -=-=-=-=-=-=-=-\n", _filename );

	time_t start, end;
	time(&start);

	std::ifstream in( _filename );
	if( !in.is_open() ) {
		if (ERRORS) fprintf( stderr, "[.off]: [ERROR]: Could not open \"%s\"\n", _filename );
		if ( INFO ) printf( "[.off]: -=-=-=-=-=-=-=-  END %s Info  -=-=-=-=-=-=-=-\n\n", _filename );
		return false;
	}

	GLuint numVertices = 0, numFaces = 0, numTriangles = 0;
	GLfloat minX = 999999.0f, maxX = -999999.0f, minY = 999999.0f, maxY = -999999.0f, minZ = 999999.0f, maxZ = -999999.0f;
	std::string line;

	enum OFF_FILE_STATE { HEADER, VERTICES, FACES, DONE };

	OFF_FILE_STATE fileState = HEADER;

	GLuint vSeen = 0, fSeen = 0;

	while( getline( in, line ) ) {
		if( line.length() > 1 && line.at(0) == '\t' )
			line = line.substr( 1 );
		line.erase( line.find_last_not_of( " \n\r\t" ) + 1 );

		std::vector< std::string > tokens = _tokenizeString( line, " \t" );
		if( tokens.empty() ) continue;

		//the line should have a single character that lets us know if it's a...
		if( !tokens[0].compare( "#" ) || tokens[0].find_first_of('#') == 0 ) {								// comment ignore
		} else if( fileState == HEADER ) {
			if( !tokens[0].compare( "OFF" ) ) {					// denotes OFF File type
			} else {
				if( tokens.size() != 3 ) {
					if (ERRORS) fprintf( stderr, "[.off]: [ERROR]: Malformed OFF file.  # vertices, faces, edges not properly specified\n" );
					if ( INFO ) printf( "[.off]: -=-=-=-=-=-=-=-  END %s Info  -=-=-=-=-=-=-=-\n\n", _filename );
					in.close();
					return false;
				}
				// read in number of expected vertices, faces, and edges
				numVertices = atoi( tokens[0].c_str() );
				numFaces = atoi( tokens[1].c_str() );

				// ignore tokens[2] - number of edges -- unnecessary information
				// numEdges = atoi( tokens[2].c_str() );

				fileState = VERTICES;
			}
		} else if( fileState == VERTICES ) {
			// read in x y z vertex location
			auto x = (GLfloat) atof( tokens[0].c_str() ),
                    y = (GLfloat) atof( tokens[1].c_str() ),
                    z = (GLfloat) atof( tokens[2].c_str() );

			if( x < minX ) minX = x;
			if( x > maxX ) maxX = x;
			if( y < minY ) minY = y;
			if( y > maxY ) maxY = y;
			if( z < minZ ) minZ = z;
			if( z > maxZ ) maxZ = z;

			vSeen++;
			if( vSeen == numVertices )
				fileState = FACES;
		} else if( fileState == FACES ) {
			GLuint numberOfVerticesInFace = atoi( tokens[0].c_str() );

			numTriangles += numberOfVerticesInFace - 3 + 1;

			if( fSeen == numFaces )
				fileState = DONE;
		} else {
			if (INFO) printf( "[.off]: unknown file state: %d\n", fileState );
		}
	}
	in.close();

	if (INFO) {
		printf( "\33[2K\r" );
		printf( "[.off]: scanning %s...done!\n", _filename );
		printf( "[.off]: ------------\n" );
		printf( "[.off]: Model Stats:\n" );
		printf( "[.off]: Vertices:  \t%u\tNormals:   \t%u\tTex Coords:\t%u\n", numVertices, 0, 0 );
		printf( "[.off]: Faces:     \t%u\tTriangles: \t%u\n", numFaces, numTriangles );
		printf( "[.off]: Dimensions:\t(%f, %f, %f)\n", (maxX - minX), (maxY - minY), (maxZ - minZ) );
	}

	if( _hasVertexNormals || !_AUTO_GEN_NORMALS ) {
		if (INFO && !_hasVertexNormals)
			printf( "[.off]: [WARN]: No vertex normals exist on model.  To autogenerate vertex\n\tnormals, call CSCI441::ModelLoader::enableAutoGenerateNormals()\n\tprior to loading the model file.\n" );
		_vertices = (GLfloat*)malloc(sizeof(GLfloat) * numVertices * 3);
		_texCoords = (GLfloat*)malloc(sizeof(GLfloat) * numVertices * 2);
		_normals = (GLfloat*)malloc(sizeof(GLfloat) * numVertices * 3);
		_indices = (GLuint*)malloc(sizeof(GLuint) * numTriangles * 3);
	} else {
		if (INFO) printf( "[.off]: No vertex normals exist on model, vertex normals will be autogenerated\n" );
		_vertices = (GLfloat*)malloc(sizeof(GLfloat) * numTriangles * 3 * 3);
		_texCoords = (GLfloat*)malloc(sizeof(GLfloat) * numTriangles * 3 * 2);
		_normals = (GLfloat*)malloc(sizeof(GLfloat) * numTriangles * 3 * 3);
		_indices = (GLuint*)malloc(sizeof(GLuint) * numTriangles * 3);
	}

	std::vector<GLfloat> vertsTemp;

	if (INFO) printf( "[.off]: ------------\n" );

	in.open( _filename );

	_uniqueIndex = 0;
	_numIndices = 0;
	vSeen = 0;

	fileState = HEADER;

	int progressCounter = 0;

	while( getline( in, line ) ) {
		if( line.length() > 1 && line.at(0) == '\t' )
			line = line.substr( 1 );
		line.erase( line.find_last_not_of( " \n\r\t" ) + 1 );

		std::vector< std::string > tokens = _tokenizeString( line, " \t" );
		if( tokens.empty() ) continue;

		//the line should have a single character that lets us know if it's a...
		if( !tokens[0].compare( "#" ) || tokens[0].find_first_of('#') == 0 ) {								// comment ignore
		} else if( fileState == HEADER ) {
			if( !tokens[0].compare( "OFF" ) ) {					// denotes OFF File type
			} else {

				// end of OFF Header reached
				fileState = VERTICES;
			}
		} else if( fileState == VERTICES ) {
			// read in x y z vertex location
			auto x = (GLfloat) atof( tokens[0].c_str() ),
                    y = (GLfloat) atof( tokens[1].c_str() ),
                    z = (GLfloat) atof( tokens[2].c_str() );

			// check if RGB(A) color information is associated with vertex
			if( tokens.size() == 6 || tokens.size() == 7 ) {
				// TODO: handle RGBA color info
				// GLfloat r = (GLfloat) atof( tokens[3].c_str() ),
				// 		g = (GLfloat) atof( tokens[4].c_str() ),
				// 		b = (GLfloat) atof( tokens[5].c_str() ),
				// 		a = 1.0f;
        //
				// if( tokens.size() == 7 )
				// 	a = atof( tokens[6].c_str() );
			}

			if( _hasVertexNormals || !_AUTO_GEN_NORMALS ) {
				_vertices[ _uniqueIndex*3 + 0 ] = x;
				_vertices[ _uniqueIndex*3 + 1 ] = y;
				_vertices[ _uniqueIndex*3 + 2 ] = z;

				_uniqueIndex++;
			} else {
				vertsTemp.push_back( x );
				vertsTemp.push_back( y );
				vertsTemp.push_back( z );

				vSeen++;
			}
			// if all vertices have been read in, move on to faces
			if( _uniqueIndex == numVertices || vSeen == numVertices )
				fileState = FACES;
		} else if( fileState == FACES ) {
			GLuint numberOfVerticesInFace = atoi( tokens[0].c_str() );

			// read in each vertex index of the face
			for(GLuint i = 2; i <= numberOfVerticesInFace - 1; i++) {
				if( _hasVertexNormals || !_AUTO_GEN_NORMALS ) {
					int fanRoot = atoi( tokens[1].c_str() );
					int fanA = atoi( tokens[i].c_str() );
					int fanB = atoi( tokens[i+1].c_str() );

					if( fanRoot < 0 ) fanRoot = numVertices + fanRoot + 1;
					if( fanA < 0 ) fanA = numVertices + fanA + 1;
					if( fanB < 0 ) fanB = numVertices + fanB + 1;

					//regardless, we always get a vertex index.
					_indices[ _numIndices++ ] = fanRoot;
					_indices[ _numIndices++ ] = fanA;
					_indices[ _numIndices++ ] = fanB;
				} else {
					int aI = atoi( tokens[1].c_str() );
					int bI = atoi( tokens[i].c_str() );
					int cI = atoi( tokens[i+1].c_str() );

					if( aI < 0 ) aI = numVertices + aI + 1;
					if( bI < 0 ) bI = numVertices + bI + 1;
					if( cI < 0 ) cI = numVertices + cI + 1;

					glm::vec3 a( vertsTemp[aI*3 + 0], vertsTemp[aI*3 + 1], vertsTemp[aI*3 + 2] );
					glm::vec3 b( vertsTemp[bI*3 + 0], vertsTemp[bI*3 + 1], vertsTemp[bI*3 + 2] );
					glm::vec3 c( vertsTemp[cI*3 + 0], vertsTemp[cI*3 + 1], vertsTemp[cI*3 + 2] );

					glm::vec3 ab = b - a;	glm::vec3 ac = c - a;
					glm::vec3 ba = a - b; glm::vec3 bc = c - b;
					glm::vec3 ca = a - c; glm::vec3 cb = b - c;

					glm::vec3 aN = glm::normalize( glm::cross( ab, ac ) );
					glm::vec3 bN = glm::normalize( glm::cross( bc, ba ) );
					glm::vec3 cN = glm::normalize( glm::cross( ca, cb ) );

					_vertices[ _uniqueIndex*3 + 0 ] = a.x;
					_vertices[ _uniqueIndex*3 + 1 ] = a.y;
					_vertices[ _uniqueIndex*3 + 2 ] = a.z;

					_normals[ _uniqueIndex*3 + 0 ] = aN.x;
					_normals[ _uniqueIndex*3 + 1 ] = aN.y;
					_normals[ _uniqueIndex*3 + 2 ] = aN.z;

					_indices[ _numIndices++ ] = _uniqueIndex++;

					_vertices[ _uniqueIndex*3 + 0 ] = b.x;
					_vertices[ _uniqueIndex*3 + 1 ] = b.y;
					_vertices[ _uniqueIndex*3 + 2 ] = b.z;

					_normals[ _uniqueIndex*3 + 0 ] = bN.x;
					_normals[ _uniqueIndex*3 + 1 ] = bN.y;
					_normals[ _uniqueIndex*3 + 2 ] = bN.z;

					_indices[ _numIndices++ ] = _uniqueIndex++;

					_vertices[ _uniqueIndex*3 + 0 ] = c.x;
					_vertices[ _uniqueIndex*3 + 1 ] = c.y;
					_vertices[ _uniqueIndex*3 + 2 ] = c.z;

					_normals[ _uniqueIndex*3 + 0 ] = cN.x;
					_normals[ _uniqueIndex*3 + 1 ] = cN.y;
					_normals[ _uniqueIndex*3 + 2 ] = cN.z;

					_indices[ _numIndices++ ] = _uniqueIndex++;
				}
			}

			// check if RGB(A) color information is associated with face
			// TODO: handle color info
			//some local variables to hold the vertex+attribute indices we read in.
			//we do it this way because we'll have to split quads into triangles ourselves.
			// GLfloat color[4] = {-1,-1,-1,1};
			// if( tokens.size() == numberOfVerticesInFace + 4 || tokens.size() == numberOfVerticesInFace + 5 ) {
			// 	color[0] = atof( tokens[numberOfVerticesInFace + 1].c_str() );
			// 	color[1] = atof( tokens[numberOfVerticesInFace + 2].c_str() );
			// 	color[2] = atof( tokens[numberOfVerticesInFace + 3].c_str() );
			// 	color[3] = 1;
      //
			// 	if( tokens.size() == numberOfVerticesInFace + 5 )
			// 		color[3] = atof( tokens[numberOfVerticesInFace + 4].c_str() );
			// }

		} else {

		}

		if (INFO) {
			progressCounter++;
			if( progressCounter % 5000 == 0 ) {
				printf("\33[2K\r");
				switch( progressCounter ) {
					case 5000:	printf("[.off]: parsing %s...\\", _filename);	break;
					case 10000:	printf("[.off]: parsing %s...|", _filename);	break;
					case 15000:	printf("[.off]: parsing %s.../", _filename);	break;
					case 20000:	printf("[.off]: parsing %s...-", _filename);	break;
				}
				fflush(stdout);
			}
			if( progressCounter == 20000 )
				progressCounter = 0;
		}
	}
	in.close();

	glBindVertexArray( _vaod );
	glBindBuffer( GL_ARRAY_BUFFER, _vbods[0] );
	glBufferData( GL_ARRAY_BUFFER, sizeof(GLfloat) * _uniqueIndex * 8, nullptr, GL_STATIC_DRAW );
	glBufferSubData( GL_ARRAY_BUFFER, 0, 																  sizeof(GLfloat) * _uniqueIndex * 3, _vertices );
	glBufferSubData( GL_ARRAY_BUFFER, sizeof(GLfloat) * _uniqueIndex * 3, sizeof(GLfloat) * _uniqueIndex * 3, _normals );
	glBufferSubData( GL_ARRAY_BUFFER, sizeof(GLfloat) * _uniqueIndex * 6, sizeof(GLfloat) * _uniqueIndex * 2, _texCoords );

	glBindBuffer( GL_ELEMENT_ARRAY_BUFFER, _vbods[1] );
	glBufferData( GL_ELEMENT_ARRAY_BUFFER, sizeof(GLuint) * _numIndices, _indices, GL_STATIC_DRAW );

	time(&end);
	double seconds = difftime( end, start );

	if (INFO) {
		printf( "\33[2K\r" );
		printf( "[.off]: parsing %s...done!  (Time: %.1fs)\n", _filename, seconds );
		printf( "[.off]: -=-=-=-=-=-=-=-  END %s Info  -=-=-=-=-=-=-=-\n\n", _filename );
	}

	return result;
}

// notes on PLY format: http://paulbourke.net/dataformats/ply/
inline bool CSCI441::ModelLoader::_loadPLYFile( bool INFO, bool ERRORS ) {
	bool result = true;

	if (INFO ) printf( "[.ply]: -=-=-=-=-=-=-=- BEGIN %s Info -=-=-=-=-=-=-=-\n", _filename );

	time_t start, end;
	time(&start);

	std::ifstream in( _filename );
	if( !in.is_open() ) {
		if (ERRORS) fprintf( stderr, "[.ply]: [ERROR]: Could not open \"%s\"\n", _filename );
		if ( INFO ) printf( "[.ply]: -=-=-=-=-=-=-=-  END %s Info  -=-=-=-=-=-=-=-\n\n", _filename );
		return false;
	}

	GLuint numVertices = 0, numFaces = 0, numTriangles = 0, numMaterials = 0;
	GLfloat minX = 999999.0f, maxX = -999999.0f, minY = 999999.0f, maxY = -999999.0f, minZ = 999999.0f, maxZ = -999999.0f;
	std::string line;

	enum PLY_FILE_STATE { HEADER, VERTICES, FACES, MATERIALS };
	enum PLY_ELEMENT_TYPE { NONE, VERTEX, FACE, MATERIAL };

	PLY_FILE_STATE fileState = HEADER;
	PLY_ELEMENT_TYPE elemType = NONE;

	GLuint progressCounter = 0;
	GLuint vSeen = 0;

	while( getline( in, line ) ) {
		if( line.length() > 1 && line.at(0) == '\t' )
			line = line.substr( 1 );
		line.erase( line.find_last_not_of( " \n\r\t" ) + 1 );

		std::vector< std::string > tokens = _tokenizeString( line, " \t" );

		if( tokens.empty() ) continue;

		//the line should have a single character that lets us know if it's a...
		if( !tokens[0].compare( "comment" ) ) {								// comment ignore
		} else if( fileState == HEADER ) {
			if( !tokens[0].compare( "ply" ) ) {					// denotes ply File type
			} else if( !tokens[0].compare( "format" ) ) {
				if( tokens[1].compare( "ascii" ) ) {
					if (ERRORS) fprintf( stderr, "[.ply]: [ERROR]: File \"%s\" not ASCII format\n", _filename );
					if ( INFO ) printf( "[.ply]: -=-=-=-=-=-=-=-  END %s Info  -=-=-=-=-=-=-=-\n\n", _filename );
					in.close();
					return false;
				}
			} else if( !tokens[0].compare( "element" ) ) {		// an element (vertex, face, material)
				if( !tokens[1].compare( "vertex" ) ) {
					numVertices = atoi( tokens[2].c_str() );
					elemType = VERTEX;
				} else if( !tokens[1].compare( "face" ) ) {
					numFaces = atoi( tokens[2].c_str() );
					elemType = FACE;
				} else if( !tokens[1].compare( "edge" ) ) {

				} else if( !tokens[1].compare( "material" ) ) {
					numMaterials = atoi( tokens[2].c_str() );
					elemType = MATERIAL;
				} else {

				}
			} else if( !tokens[0].compare( "property" ) ) {
				if( elemType == VERTEX ) {

				} else if( elemType == FACE ) {

				} else if( elemType == MATERIAL ) {

				}
			} else if( !tokens[0].compare( "end_header" ) ) {	// end of the header section
				fileState = VERTICES;
			}
		} else if( fileState == VERTICES ) {
			// read in x y z vertex location
			auto x = (GLfloat) atof( tokens[0].c_str() ),
						y = (GLfloat) atof( tokens[1].c_str() ),
						z = (GLfloat) atof( tokens[2].c_str() );

			if( x < minX ) minX = x;
			if( x > maxX ) maxX = x;
			if( y < minY ) minY = y;
			if( y > maxY ) maxY = y;
			if( z < minZ ) minZ = z;
			if( z > maxZ ) maxZ = z;

			vSeen++;
			// if all vertices have been read in, move on to faces
			if( vSeen == numVertices )
				fileState = FACES;
		} else if( fileState == FACES ) {
			GLuint numberOfVerticesInFace = atoi( tokens[0].c_str() );
			numTriangles += numberOfVerticesInFace - 3 + 1;
		} else {
			if (INFO) printf( "[.ply]: unknown file state: %d\n", fileState );
		}

		if (INFO) {
			progressCounter++;
			if( progressCounter % 5000 == 0 ) {
				printf("\33[2K\r");
				switch( progressCounter ) {
					case 5000:	printf("[.ply]: scanning %s...\\", _filename);	break;
					case 10000:	printf("[.ply]: scanning %s...|", _filename);	break;
					case 15000:	printf("[.ply]: scanning %s.../", _filename);	break;
					case 20000:	printf("[.ply]: scanning %s...-", _filename);	break;
				}
				fflush(stdout);
			}
			if( progressCounter == 20000 )
				progressCounter = 0;
		}
	}
	in.close();

	if (INFO) {
		printf( "\33[2K\r" );
		printf( "[.ply]: scanning %s...done!\n", _filename );
		printf( "[.ply]: ------------\n" );
		printf( "[.ply]: Model Stats:\n" );
		printf( "[.ply]: Vertices:  \t%u\tNormals:   \t%u\tTex Coords:\t%u\n", numVertices, 0, 0 );
		printf( "[.ply]: Faces:     \t%u\tTriangles: \t%u\n", numFaces, numTriangles );
		printf( "[.ply]: Dimensions:\t(%f, %f, %f)\n", (maxX - minX), (maxY - minY), (maxZ - minZ) );
	}

	if( _hasVertexNormals || !_AUTO_GEN_NORMALS ) {
		if (INFO && !_hasVertexNormals)
			printf( "[.ply]: [WARN]: No vertex normals exist on model.  To autogenerate vertex\n\tnormals, call CSCI441::ModelLoader::enableAutoGenerateNormals()\n\tprior to loading the model file.\n" );
		_vertices = (GLfloat*)malloc(sizeof(GLfloat) * numVertices * 3);
		_texCoords = (GLfloat*)malloc(sizeof(GLfloat) * numVertices * 2);
		_normals = (GLfloat*)malloc(sizeof(GLfloat) * numVertices * 3);
		_indices = (GLuint*)malloc(sizeof(GLuint) * numTriangles * 3);
	} else {
		if (INFO) printf( "[.ply]: No vertex normals exist on model, vertex normals will be autogenerated\n" );
		_vertices = (GLfloat*)malloc(sizeof(GLfloat) * numTriangles * 3 * 3);
		_texCoords = (GLfloat*)malloc(sizeof(GLfloat) * numTriangles * 3 * 2);
		_normals = (GLfloat*)malloc(sizeof(GLfloat) * numTriangles * 3 * 3);
		_indices = (GLuint*)malloc(sizeof(GLuint) * numTriangles * 3);
	}

	if (INFO) printf( "[.ply]: ------------\n" );

	std::vector<GLfloat> vertsTemp;

	in.open( _filename );

	_uniqueIndex = 0;
	_numIndices = 0;

	fileState = HEADER;
	elemType = NONE;

	progressCounter = 0;
	vSeen = 0;

	while( getline( in, line ) ) {
		if( line.length() > 1 && line.at(0) == '\t' )
			line = line.substr( 1 );
		line.erase( line.find_last_not_of( " \n\r\t" ) + 1 );

		std::vector< std::string > tokens = _tokenizeString( line, " \t" );

		if( tokens.empty() ) continue;

		//the line should have a single character that lets us know if it's a...
		if( !tokens[0].compare( "comment" ) ) {								// comment ignore
		} else if( fileState == HEADER ) {
			if( !tokens[0].compare( "ply" ) ) {					// denotes ply File type
			} else if( !tokens[0].compare( "format" ) ) {
				if( tokens[1].compare( "ascii" ) ) {
					if (ERRORS) fprintf( stderr, "[.ply]: [ERROR]: File \"%s\" not ASCII format\n", _filename );
					if ( INFO ) printf( "[.ply]: -=-=-=-=-=-=-=-  END %s Info  -=-=-=-=-=-=-=-\n\n", _filename );
					in.close();
					return false;
				}
			} else if( !tokens[0].compare( "element" ) ) {		// an element (vertex, face, material)
				if( !tokens[1].compare( "vertex" ) ) {
					numVertices = atoi( tokens[2].c_str() );
					elemType = VERTEX;
				} else if( !tokens[1].compare( "face" ) ) {
					numFaces = atoi( tokens[2].c_str() );
					elemType = FACE;
				} else if( !tokens[1].compare( "edge" ) ) {

				} else if( !tokens[1].compare( "material" ) ) {
					numMaterials = atoi( tokens[2].c_str() );
					elemType = MATERIAL;
				} else {

				}
			} else if( !tokens[0].compare( "property" ) ) {
				if( elemType == VERTEX ) {

				} else if( elemType == FACE ) {

				} else if( elemType == MATERIAL ) {

				}
			} else if( !tokens[0].compare( "end_header" ) ) {	// end of the header section
				fileState = VERTICES;
			}
		} else if( fileState == VERTICES ) {
			// read in x y z vertex location
			auto x = (GLfloat) atof( tokens[0].c_str() ),
						y = (GLfloat) atof( tokens[1].c_str() ),
						z = (GLfloat) atof( tokens[2].c_str() );

			if( _hasVertexNormals || !_AUTO_GEN_NORMALS ) {
				_vertices[ _uniqueIndex*3 + 0 ] = x;
				_vertices[ _uniqueIndex*3 + 1 ] = y;
				_vertices[ _uniqueIndex*3 + 2 ] = z;

				_uniqueIndex++;
			} else {
				vertsTemp.push_back( x );
				vertsTemp.push_back( y );
				vertsTemp.push_back( z );

				vSeen++;
			}
			// if all vertices have been read in, move on to faces
			if( _uniqueIndex == numVertices || vSeen == numVertices )
				fileState = FACES;
		} else if( fileState == FACES ) {
			GLuint numberOfVerticesInFace = atoi( tokens[0].c_str() );

			for( GLuint i = 2; i <= numberOfVerticesInFace - 1; i++ ) {
				if( _hasVertexNormals || !_AUTO_GEN_NORMALS ) {
					_indices[ _numIndices++ ] = atoi( tokens[1].c_str() );
					_indices[ _numIndices++ ] = atoi( tokens[i].c_str() );
					_indices[ _numIndices++ ] = atoi( tokens[i+1].c_str() );
				} else {
					GLuint aI = atoi( tokens[1].c_str() );
					GLuint bI = atoi( tokens[i].c_str() );
					GLuint cI = atoi( tokens[i+1].c_str() );

					glm::vec3 a( vertsTemp[aI*3 + 0], vertsTemp[aI*3 + 1], vertsTemp[aI*3 + 2] );
					glm::vec3 b( vertsTemp[bI*3 + 0], vertsTemp[bI*3 + 1], vertsTemp[bI*3 + 2] );
					glm::vec3 c( vertsTemp[cI*3 + 0], vertsTemp[cI*3 + 1], vertsTemp[cI*3 + 2] );

					glm::vec3 ab = b - a;	glm::vec3 ac = c - a;
					glm::vec3 ba = a - b; glm::vec3 bc = c - b;
					glm::vec3 ca = a - c; glm::vec3 cb = b - c;

					glm::vec3 aN = glm::normalize( glm::cross( ab, ac ) );
					glm::vec3 bN = glm::normalize( glm::cross( bc, ba ) );
					glm::vec3 cN = glm::normalize( glm::cross( ca, cb ) );

					_vertices[ _uniqueIndex*3 + 0 ] = a.x;
					_vertices[ _uniqueIndex*3 + 1 ] = a.y;
					_vertices[ _uniqueIndex*3 + 2 ] = a.z;

					_normals[ _uniqueIndex*3 + 0 ] = aN.x;
					_normals[ _uniqueIndex*3 + 1 ] = aN.y;
					_normals[ _uniqueIndex*3 + 2 ] = aN.z;

					_indices[ _numIndices++ ] = _uniqueIndex++;

					_vertices[ _uniqueIndex*3 + 0 ] = b.x;
					_vertices[ _uniqueIndex*3 + 1 ] = b.y;
					_vertices[ _uniqueIndex*3 + 2 ] = b.z;

					_normals[ _uniqueIndex*3 + 0 ] = bN.x;
					_normals[ _uniqueIndex*3 + 1 ] = bN.y;
					_normals[ _uniqueIndex*3 + 2 ] = bN.z;

					_indices[ _numIndices++ ] = _uniqueIndex++;

					_vertices[ _uniqueIndex*3 + 0 ] = c.x;
					_vertices[ _uniqueIndex*3 + 1 ] = c.y;
					_vertices[ _uniqueIndex*3 + 2 ] = c.z;

					_normals[ _uniqueIndex*3 + 0 ] = cN.x;
					_normals[ _uniqueIndex*3 + 1 ] = cN.y;
					_normals[ _uniqueIndex*3 + 2 ] = cN.z;

					_indices[ _numIndices++ ] = _uniqueIndex++;
				}
			}
		} else {
			if (INFO) printf( "[.ply]: unknown file state: %d\n", fileState );
		}

		if (INFO) {
			progressCounter++;
			if( progressCounter % 5000 == 0 ) {
				printf("\33[2K\r");
				switch( progressCounter ) {
					case 5000:	printf("[.ply]: parsing %s...\\", _filename);	break;
					case 10000:	printf("[.ply]: parsing %s...|", _filename);	break;
					case 15000:	printf("[.ply]: parsing %s.../", _filename);	break;
					case 20000:	printf("[.ply]: parsing %s...-", _filename);	break;
				}
				fflush(stdout);
			}
			if( progressCounter == 20000 )
				progressCounter = 0;
		}
	}
	in.close();

	glBindVertexArray( _vaod );
	glBindBuffer( GL_ARRAY_BUFFER, _vbods[0] );
	glBufferData( GL_ARRAY_BUFFER, sizeof(GLfloat) * _uniqueIndex * 8, nullptr, GL_STATIC_DRAW );
	glBufferSubData( GL_ARRAY_BUFFER, 0, 																  sizeof(GLfloat) * _uniqueIndex * 3, _vertices );
	glBufferSubData( GL_ARRAY_BUFFER, sizeof(GLfloat) * _uniqueIndex * 3, sizeof(GLfloat) * _uniqueIndex * 3, _normals );
	glBufferSubData( GL_ARRAY_BUFFER, sizeof(GLfloat) * _uniqueIndex * 6, sizeof(GLfloat) * _uniqueIndex * 2, _texCoords );

	glBindBuffer( GL_ELEMENT_ARRAY_BUFFER, _vbods[1] );
	glBufferData( GL_ELEMENT_ARRAY_BUFFER, sizeof(GLuint) * _numIndices, _indices, GL_STATIC_DRAW );

	time(&end);
	double seconds = difftime( end, start );

	if (INFO) {
		printf( "\33[2K\r" );
		printf( "[.ply]: parsing %s...done!\n[.ply]: Time to complete: %.3fs\n", _filename, seconds );
		printf( "[.ply]: -=-=-=-=-=-=-=-  END %s Info  -=-=-=-=-=-=-=-\n\n", _filename );
	}

	return result;
}

inline bool CSCI441::ModelLoader::_loadSTLFile( bool INFO, bool ERRORS ) {
	bool result = true;

	if (INFO) printf( "[.stl]: -=-=-=-=-=-=-=- BEGIN %s Info -=-=-=-=-=-=-=-\n", _filename );

	time_t start, end;
	time(&start);

	std::ifstream in( _filename );
	if( !in.is_open() ) {
		if (ERRORS) fprintf(stderr, "[.stl]: [ERROR]: Could not open \"%s\"\n", _filename );
		if ( INFO ) printf( "[.stl]: -=-=-=-=-=-=-=-  END %s Info  -=-=-=-=-=-=-=-\n\n", _filename );
		return false;
	}

	GLuint numVertices = 0, numNormals = 0, numFaces = 0, numTriangles = 0, numVertsInLoop = 0;
	GLfloat minX = 999999.0f, maxX = -999999.0f, minY = 999999.0f, maxY = -999999.0f, minZ = 999999.0f, maxZ = -999999.0f;
	std::string line;

	int progressCounter = 0;
	GLfloat normalVector[3] = {0,0,0};

	while( getline( in, line ) ) {
		if( line.length() > 1 && line.at(0) == '\t' )
			line = line.substr( 1 );
		line.erase( line.find_last_not_of( " \n\r\t" ) + 1 );

		std::vector< std::string > tokens = _tokenizeString( line, " \t" );

		if( tokens.empty() ) continue;

		//the line should have a single character that lets us know if it's a...
		if( !tokens[0].compare( "solid" ) ) {
		} else if( !tokens[0].compare( "facet" ) ) {
			/* read in x y z triangle normal */
			numNormals++;
		} else if( !tokens[0].compare( "outer" ) && !tokens[1].compare( "loop" ) ) {
			// begin a primitive
			numVertsInLoop = 0;
		} else if( !tokens[0].compare( "vertex" ) ) {
			auto x = (GLfloat) atof( tokens[1].c_str() ),
					y = (GLfloat) atof( tokens[2].c_str() ),
					z = (GLfloat) atof( tokens[3].c_str() );

			if( x < minX ) minX = x;
			if( x > maxX ) maxX = x;
			if( y < minY ) minY = y;
			if( y > maxY ) maxY = y;
			if( z < minZ ) minZ = z;
			if( z > maxZ ) maxZ = z;

			numVertices++;
			numVertsInLoop++;
		} else if( !tokens[0].compare( "endloop" ) ) {
			// end primitive
			numTriangles += numVertsInLoop - 3 + 1;
		} else if( !tokens[0].compare( "endfacet" ) ) {
			numFaces++;
		} else if( !tokens[0].compare( "endsolid" ) ) {

		}
		else {
			if( memchr( line.c_str(), '\0', line.length() ) != NULL ) {
				if (ERRORS) fprintf( stderr, "[.stl]: [ERROR]: Cannot read binary STL file \"%s\"\n", _filename );
				if ( INFO ) printf( "[.stl]: -=-=-=-=-=-=-=-  END %s Info  -=-=-=-=-=-=-=-\n\n", _filename );
				in.close();
				return false;
			} else if (INFO) printf( "[.stl]: unknown line: %s\n", line.c_str() );
		}

		if (INFO) {
			progressCounter++;
			if( progressCounter % 5000 == 0 ) {
				printf("\33[2K\r");
				switch( progressCounter ) {
					case 5000:	printf("[.stl]: scanning %s...\\", _filename);	break;
					case 10000:	printf("[.stl]: scanning %s...|", _filename);	break;
					case 15000:	printf("[.stl]: scanning %s.../", _filename);	break;
					case 20000:	printf("[.stl]: scanning %s...-", _filename);	break;
				}
				fflush(stdout);
			}
			if( progressCounter == 20000 )
				progressCounter = 0;
		}
	}
	in.close();

	if (INFO) {
		printf( "\33[2K\r" );
		printf( "[.stl]: scanning %s...done!\n", _filename );
		printf( "[.stl]: ------------\n" );
		printf( "[.stl]: Model Stats:\n" );
		printf( "[.stl]: Vertices:  \t%u\tNormals:   \t%u\tTex Coords:\t%u\n", numVertices, numNormals, 0 );
		printf( "[.stl]: Faces:     \t%u\tTriangles: \t%u\n", numFaces, numTriangles );
		printf( "[.stl]: Dimensions:\t(%f, %f, %f)\n", (maxX - minX), (maxY - minY), (maxZ - minZ) );
	}

	_vertices = (GLfloat*)malloc(sizeof(GLfloat) * numVertices * 3);
	_texCoords = (GLfloat*)malloc(sizeof(GLfloat) * numVertices * 2);
	_normals = (GLfloat*)malloc(sizeof(GLfloat) * numVertices * 3);
	_indices = (GLuint*)malloc(sizeof(GLuint) * numTriangles * 3);

	if (INFO) printf( "[.stl]: ------------\n" );

	in.open( _filename );

	_uniqueIndex = 0;
	_numIndices = 0;

	while( getline( in, line ) ) {
		if( line.length() > 1 && line.at(0) == '\t' )
			line = line.substr( 1 );
		line.erase( line.find_last_not_of( " \n\r\t" ) + 1 );

		std::vector< std::string > tokens = _tokenizeString( line, " \t" );

		if( tokens.empty() ) continue;

		//the line should have a single character that lets us know if it's a...
		if( !tokens[0].compare( "solid" ) ) {
		} else if( !tokens[0].compare( "facet" ) ) {
			/* read in x y z triangle normal */
			normalVector[0] = atof( tokens[2].c_str() );
			normalVector[1] = atof( tokens[3].c_str() );
			normalVector[2] = atof( tokens[4].c_str() );
		} else if( !tokens[0].compare( "outer" ) && !tokens[1].compare( "loop" ) ) {
			// begin a primitive
		} else if( !tokens[0].compare( "vertex" ) ) {
			auto x = (GLfloat) atof( tokens[1].c_str() ),
					y = (GLfloat) atof( tokens[2].c_str() ),
					z = (GLfloat) atof( tokens[3].c_str() );

			_vertices[ _uniqueIndex*3 + 0 ] = x;
			_vertices[ _uniqueIndex*3 + 1 ] = y;
			_vertices[ _uniqueIndex*3 + 2 ] = z;

			_normals[ _uniqueIndex*3 + 0 ] = normalVector[0];
			_normals[ _uniqueIndex*3 + 1 ] = normalVector[1];
			_normals[ _uniqueIndex*3 + 2 ] = normalVector[2];

			_indices[ _numIndices++ ] = _uniqueIndex++;
		} else if( !tokens[0].compare( "endloop" ) ) {
			// end primitive
		} else if( !tokens[0].compare( "endfacet" ) ) {

		} else if( !tokens[0].compare( "endsolid" ) ) {

		}
		else {

		}

		if (INFO) {
			progressCounter++;
			if( progressCounter % 5000 == 0 ) {
				printf("\33[2K\r");
				switch( progressCounter ) {
					case 5000:	printf("[.stl]: parsing %s...\\", _filename);	break;
					case 10000:	printf("[.stl]: parsing %s...|", _filename);	break;
					case 15000:	printf("[.stl]: parsing %s.../", _filename);	break;
					case 20000:	printf("[.stl]: parsing %s...-", _filename);	break;
				}
				fflush(stdout);
			}
			if( progressCounter == 20000 )
				progressCounter = 0;
		}
	}
	in.close();

	glBindVertexArray( _vaod );
	glBindBuffer( GL_ARRAY_BUFFER, _vbods[0] );
	glBufferData( GL_ARRAY_BUFFER, sizeof(GLfloat) * _uniqueIndex * 8, nullptr, GL_STATIC_DRAW );
	glBufferSubData( GL_ARRAY_BUFFER, 0, 																  sizeof(GLfloat) * _uniqueIndex * 3, _vertices );
	glBufferSubData( GL_ARRAY_BUFFER, sizeof(GLfloat) * _uniqueIndex * 3, sizeof(GLfloat) * _uniqueIndex * 3, _normals );
	glBufferSubData( GL_ARRAY_BUFFER, sizeof(GLfloat) * _uniqueIndex * 6, sizeof(GLfloat) * _uniqueIndex * 2, _texCoords );

	glBindBuffer( GL_ELEMENT_ARRAY_BUFFER, _vbods[1] );
	glBufferData( GL_ELEMENT_ARRAY_BUFFER, sizeof(GLuint) * _numIndices, _indices, GL_STATIC_DRAW );

	time(&end);
	double seconds = difftime( end, start );

	if (INFO) {
		printf("\33[2K\r");
		printf("[.stl]: parsing %s...done!\n[.stl]: Time to complete: %.3fs\n", _filename, seconds);
		printf( "[.stl]: -=-=-=-=-=-=-=-  END %s Info  -=-=-=-=-=-=-=-\n\n", _filename );
	}

	return result;
}

[[maybe_unused]]
inline void CSCI441::ModelLoader::enableAutoGenerateNormals() {
	_AUTO_GEN_NORMALS = true;
}

[[maybe_unused]]
inline void CSCI441::ModelLoader::disableAutoGenerateNormals() {
	_AUTO_GEN_NORMALS = false;
}

//
//  vector<string> tokenizeString(string input, string delimiters)
//
//      This is a helper function to break a single string into std::vector
//  of strings, based on a given set of delimiter characters.
//
inline std::vector<std::string> CSCI441::ModelLoader::_tokenizeString(std::string input, const std::string& delimiters) {
	if(input.empty())
		return {};

	std::vector<std::string> retVec = std::vector<std::string>();
	size_t oldR = 0, r = 0;

	//strip all delimiter characters from the front and end of the input string.
	std::string strippedInput;
	int lowerValidIndex = 0, upperValidIndex = input.size() - 1;
	while((GLuint)lowerValidIndex < input.size() && delimiters.find_first_of(input.at(lowerValidIndex), 0) != std::string::npos)
		lowerValidIndex++;

	while(upperValidIndex >= 0 && delimiters.find_first_of(input.at(upperValidIndex), 0) != std::string::npos)
		upperValidIndex--;

	//if the lowest valid index is higher than the highest valid index, they're all delimiters! return nothing.
	if((GLuint)lowerValidIndex >= input.size() || upperValidIndex < 0 || lowerValidIndex > upperValidIndex)
		return {};

	//remove the delimiters from the beginning and end of the string, if any.
	strippedInput = input.substr(lowerValidIndex, upperValidIndex-lowerValidIndex+1);

	//search for each instance of a delimiter character, and create a new token spanning
	//from the last valid character up to the delimiter character.
	while((r = strippedInput.find_first_of(delimiters, oldR)) != std::string::npos)
	{
		if(oldR != r)           //but watch out for multiple consecutive delimiters!
			retVec.push_back(strippedInput.substr(oldR, r-oldR));
		oldR = r+1;
	}
	if(r != 0)
		retVec.push_back(strippedInput.substr(oldR, r-oldR));

	return retVec;
}

inline unsigned char* CSCI441_INTERNAL::createTransparentTexture( const unsigned char * imageData, const unsigned char *imageMask, int texWidth, int texHeight, int texChannels, int maskChannels ) {
	//combine the 'mask' array with the image data array into an RGBA array.
	auto *fullData = new unsigned char[texWidth*texHeight*4];

	for(int j = 0; j < texHeight; j++) {
		for(int i = 0; i < texWidth; i++) {
			if( imageData ) {
				fullData[(j*texWidth+i)*4+0] = imageData[(j*texWidth+i)*texChannels+0];	// R
				fullData[(j*texWidth+i)*4+1] = imageData[(j*texWidth+i)*texChannels+1];	// G
				fullData[(j*texWidth+i)*4+2] = imageData[(j*texWidth+i)*texChannels+2];	// B
			} else {
				fullData[(j*texWidth+i)*4+0] = 1;	// R
				fullData[(j*texWidth+i)*4+1] = 1;	// G
				fullData[(j*texWidth+i)*4+2] = 1;	// B
			}

			if( imageMask ) {
				fullData[(j*texWidth+i)*4+3] = imageMask[(j*texWidth+i)*maskChannels+0];	// A
			} else {
				fullData[(j*texWidth+i)*4+3] = 1;	// A
			}
		}
	}
	return fullData;
}

[[maybe_unused]]
inline void CSCI441_INTERNAL::flipImageY( int texWidth, int texHeight, int textureChannels, unsigned char *textureData ) {
	for( int j = 0; j < texHeight / 2; j++ ) {
		for( int i = 0; i < texWidth; i++ ) {
			for( int k = 0; k < textureChannels; k++ ) {
				int top = (j*texWidth + i)*textureChannels + k;
				int bot = ((texHeight-j-1)*texWidth + i)*textureChannels + k;

				unsigned char t = textureData[top];
				textureData[top] = textureData[bot];
				textureData[bot] = t;

			}
		}
	}
}

#endif // __CSCI441_MODEL_LOADER_HPP__
