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
#include <utility>
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
		bool loadModelFile( std::string filename, bool INFO = true, bool ERRORS = true );

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
         * @brief Return the normal array that corresponds to the model mesh.
         * @return pointer to the normal array
         * @note For use with VBOs
         */
        [[maybe_unused]] [[nodiscard]] GLfloat* getNormals() const;
		/**
		 * @brief Return the texture coordinates array that corresponds to the model mesh.
		 * @return pointer to texture coordinate array
		 * @note For use with VBOs
		 */
        [[maybe_unused]] [[nodiscard]] GLfloat* getTexCoords() const;
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
        void _allocateAttributeArrays(const GLuint numVertices, const GLuint numIndices);
        void _bufferData();

		std::string _filename;
		CSCI441_INTERNAL::MODEL_TYPE _modelType;

		GLuint _vaod;
		GLuint _vbods[2];

		glm::vec3* _vertices;
        glm::vec3* _normals;
        glm::vec2* _texCoords;
		GLuint* _indices;
		GLuint _uniqueIndex;
		GLuint _numIndices;

		std::map< std::string, CSCI441_INTERNAL::ModelMaterial* > _materials;
		std::map< std::string, std::vector< std::pair< GLuint, GLuint > > > _materialIndexStartStop;

		bool _hasVertexTexCoords;
		bool _hasVertexNormals;

        static bool sAUTO_GEN_NORMALS;
	};
}

////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////

namespace CSCI441_INTERNAL {
	unsigned char* createTransparentTexture( const unsigned char *imageData, const unsigned char *imageMask, int texWidth, int texHeight, int texChannels, int maskChannels );
	[[maybe_unused]] void flipImageY( int texWidth, int texHeight, int textureChannels, unsigned char *textureData );
}

inline bool CSCI441::ModelLoader::sAUTO_GEN_NORMALS = false;

inline CSCI441::ModelLoader::ModelLoader() {
	_init();
}

[[maybe_unused]]
inline CSCI441::ModelLoader::ModelLoader( const char* filename ) {
	_init();
	loadModelFile( filename );
}

inline CSCI441::ModelLoader::~ModelLoader() {
	delete[] _vertices;
    delete[] _normals;
    delete[] _texCoords;
	delete[] _indices;

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

inline bool CSCI441::ModelLoader::loadModelFile( std::string filename, bool INFO, bool ERRORS ) {
	bool result = true;
	_filename = std::move(filename);
	if( _filename.find(".obj") != std::string::npos ) {
		result = _loadOBJFile( INFO, ERRORS );
		_modelType = CSCI441_INTERNAL::OBJ;
	}
	else if( _filename.find(".off") != std::string::npos ) {
		result = _loadOFFFile( INFO, ERRORS );
		_modelType = CSCI441_INTERNAL::OFF;
	}
	else if(  _filename.find(".ply") != std::string::npos ) {
		result = _loadPLYFile( INFO, ERRORS );
		_modelType = CSCI441_INTERNAL::PLY;
	}
	else if( _filename.find(".stl") != std::string::npos ) {
		result = _loadSTLFile( INFO, ERRORS );
		_modelType = CSCI441_INTERNAL::STL;
	}
	else {
		result = false;
		if (ERRORS) fprintf( stderr, "[ERROR]:  Unsupported file format for file: %s\n", _filename.c_str() );
	}

	return result;
}

[[maybe_unused]]
inline void CSCI441::ModelLoader::setAttributeLocations(GLint positionLocation, GLint normalLocation, GLint texCoordLocation) const {
    glBindVertexArray( _vaod );
    glBindBuffer( GL_ARRAY_BUFFER, _vbods[0] );

    glEnableVertexAttribArray( positionLocation );
    glVertexAttribPointer( positionLocation, 3, GL_FLOAT, GL_FALSE, 0, (void*)nullptr );

    glEnableVertexAttribArray( normalLocation );
    glVertexAttribPointer( normalLocation, 3, GL_FLOAT, GL_FALSE, 0, (void*)(sizeof(glm::vec3) * _uniqueIndex) );

    glEnableVertexAttribArray( texCoordLocation );
    glVertexAttribPointer( texCoordLocation, 2, GL_FLOAT, GL_FALSE, 0, (void*)(sizeof(glm::vec3) * _uniqueIndex * 2) );
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
				GLsizei length = (GLsizei)(end - start) + 1;

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
		glDrawElements( GL_TRIANGLES, static_cast<GLint>(_numIndices), GL_UNSIGNED_INT, (void*)nullptr );
	}

	return result;
}

[[maybe_unused]] inline GLuint CSCI441::ModelLoader::getNumberOfVertices() const { return _uniqueIndex; }
[[maybe_unused]] inline GLfloat* CSCI441::ModelLoader::getVertices() const { return (_vertices != nullptr ? (GLfloat*)&_vertices[0] : nullptr); }
[[maybe_unused]] inline GLfloat* CSCI441::ModelLoader::getNormals() const { return (_normals != nullptr ? (GLfloat*)&_normals[0] : nullptr); }
[[maybe_unused]] inline GLfloat* CSCI441::ModelLoader::getTexCoords() const { return (_texCoords != nullptr ? (GLfloat*)&_texCoords[0] : nullptr); }
[[maybe_unused]] inline GLuint CSCI441::ModelLoader::getNumberOfIndices() const { return _numIndices; }
[[maybe_unused]] inline GLuint* CSCI441::ModelLoader::getIndices() const { return _indices; }

// Read in a WaveFront *.obj File
inline bool CSCI441::ModelLoader::_loadOBJFile( bool INFO, bool ERRORS ) {
	bool result = true;

	if ( INFO ) fprintf( stdout, "[.obj]: -=-=-=-=-=-=-=- BEGIN %s Info -=-=-=-=-=-=-=- \n", _filename.c_str() );

	time_t start, end;
	time(&start);

	std::ifstream in( _filename );
	if( !in.is_open() ) {
		if (ERRORS) fprintf( stderr, "[.obj]: [ERROR]: Could not open \"%s\"\n", _filename.c_str() );
		if ( INFO ) fprintf( stdout, "[.obj]: -=-=-=-=-=-=-=-  END %s Info  -=-=-=-=-=-=-=- \n", _filename.c_str() );
		return false;
	}

	GLuint numObjects = 0, numGroups = 0;
	GLuint numVertices = 0, numTexCoords = 0, numNormals = 0;
	GLuint numFaces = 0, numTriangles = 0;
    glm::vec3 minDimension = {999999.f, 999999.f, 999999.f};
    glm::vec3 maxDimension = { -999999.f, -999999.f, -999999.f };
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
		if( tokens[0] == "#"  || tokens[0].find_first_of('#') == 0 ) {
            // comment ignore
		} else if( tokens[0] == "o" ) {						// object name ignore
			numObjects++;
		} else if( tokens[0] == "g" ) {						// polygon group name ignore
			numGroups++;
		} else if( tokens[0] == "mtllib" ) {					// material library
			_loadMTLFile( tokens[1].c_str(), INFO, ERRORS );
		} else if( tokens[0] == "v" ) {						//vertex
			numVertices++;

			glm::vec3 pos = { strtof( tokens[1].c_str(), nullptr ),
                            strtof( tokens[2].c_str(), nullptr ),
                            strtof( tokens[3].c_str(), nullptr ) };

			if( pos.x < minDimension.x ) minDimension.x = pos.x;
			if( pos.x > maxDimension.x ) maxDimension.x = pos.x;
			if( pos.y < minDimension.y ) minDimension.y = pos.y;
			if( pos.y > maxDimension.y ) maxDimension.y = pos.y;
			if( pos.z < minDimension.z ) minDimension.z = pos.z;
			if( pos.z > maxDimension.z ) maxDimension.z = pos.z;
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

                auto sv = (GLint)strtol(groupTokens[0].c_str(), nullptr, 10);
                GLuint v = sv;
                if(sv < 0) v = numVertices + sv + 1;

                currentFaceTokenStream << v;

				//based on combination of number of tokens and slashes, we can determine what we have.
				if(groupTokens.size() == 2 && numSlashes == 1) {
					_hasVertexTexCoords = true;

                    auto svt = (GLint)strtol(groupTokens[1].c_str(), nullptr, 10);
                    GLuint vt = svt;
                    if(svt < 0) vt = numTexCoords + svt + 1;

                    currentFaceTokenStream << "/" << vt;
				} else if(groupTokens.size() == 2 && numSlashes == 2) {
					_hasVertexNormals = true;

                    auto svn = (GLint)strtol(groupTokens[1].c_str(), nullptr, 10);
                    GLuint vn = svn;
                    if(svn < 0) vn = numNormals + svn + 1;

                    currentFaceTokenStream << "//" << vn;
				} else if(groupTokens.size() == 3) {
					_hasVertexTexCoords = true;
					_hasVertexNormals = true;

                    auto svt = (GLint)strtol(groupTokens[1].c_str(), nullptr, 10);
                    GLuint vt = svt;
                    if(svt < 0) vt = numTexCoords + svt + 1;

                    auto svn = (GLint)strtol(groupTokens[2].c_str(), nullptr, 10);
                    GLuint vn = svn;
                    if(svn < 0) vn = numNormals + svn + 1;

                    currentFaceTokenStream << "/" << vt << "/" << vn;
				} else if(groupTokens.size() != 1) {
					if (ERRORS) fprintf(stderr, "[.obj]: [ERROR]: Malformed OBJ file, %s.\n", _filename.c_str());
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
            if (INFO) printf( "[.obj]: ignoring line: %s\n", line.c_str() );
		}

		if (INFO) {
			progressCounter++;
			if( progressCounter % 5000 == 0 ) {
				printf("\33[2K\r");
				switch( progressCounter ) {
					case 5000:	printf("[.obj]: scanning %s...\\", _filename.c_str());	break;
					case 10000:	printf("[.obj]: scanning %s...|", _filename.c_str());	break;
					case 15000:	printf("[.obj]: scanning %s.../", _filename.c_str());	break;
					case 20000:	printf("[.obj]: scanning %s...-", _filename.c_str());	break;
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
		printf( "[.obj]: scanning %s...done!\n", _filename.c_str() );
		printf( "[.obj]: ------------\n" );
		printf( "[.obj]: Model Stats:\n" );
		printf( "[.obj]: Vertices:  \t%u\tNormals:  \t%u\tTex Coords:\t%u\n", numVertices, numNormals, numTexCoords );
		printf( "[.obj]: Unique Verts:\t%u\n", _uniqueIndex );
		printf( "[.obj]: Faces:     \t%u\tTriangles:\t%u\n", numFaces, numTriangles );
		printf( "[.obj]: Objects:   \t%u\tGroups:   \t%u\n", numObjects, numGroups );

        glm::vec3 sizeDimensions = maxDimension - minDimension;
		printf( "[.obj]: Dimensions:\t(%f, %f, %f)\n", sizeDimensions.x, sizeDimensions.y, sizeDimensions.z );
	}

	if( _hasVertexNormals || !sAUTO_GEN_NORMALS ) {
		if (INFO && !_hasVertexNormals)
			printf( "[.obj]: [WARN]: No vertex normals exist on model.  To autogenerate vertex\n\tnormals, call CSCI441::ModelLoader::enableAutoGenerateNormals()\n\tprior to loading the model file.\n" );
        _allocateAttributeArrays(_uniqueIndex, numTriangles*3);
	} else {
		if (INFO) printf( "[.obj]: No vertex normals exist on model, vertex normals will be autogenerated\n" );
        _allocateAttributeArrays(numTriangles * 3, numTriangles*3);
	}

	auto v  = new glm::vec3[numVertices];
	auto vn = new glm::vec3[numNormals];
    auto vt = new glm::vec2[numTexCoords];

	std::vector<glm::vec3> verticesTemps;
	std::vector<glm::vec2> texCoordsTemp;

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
		if( tokens[0] == "#" || tokens[0].find_first_of('#') == 0   // comment ignore
            || tokens[0] == "o"                                         // object name ignore
            || tokens[0] == "g"                                         // polygon group name ignore
            || tokens[0] == "mtllib"                                    // material library
            || tokens[0] == "s"                                         // smooth shading
        ) {

		} else if( tokens[0] == "usemtl" ) {					        // use material library
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
				_materialIndexStartStop.find( currentMaterial )->second.emplace_back(  indicesSeen, -1 );
			}
		} else if( tokens[0] == "v" ) {						//vertex
			v[vSeen] = glm::vec3(strtof( tokens[1].c_str(), nullptr ),
                                 strtof( tokens[2].c_str(), nullptr ),
                                 strtof( tokens[3].c_str(), nullptr ) );
			vSeen++;
		} else if( tokens[0] == "vn" ) {                    //vertex normal
			vn[vnSeen] = glm::vec3(strtof( tokens[1].c_str(), nullptr ),
                                   strtof( tokens[2].c_str(), nullptr ),
                                   strtof( tokens[3].c_str(), nullptr ));
			vnSeen++;
		} else if( tokens[0] == "vt" ) {                    //vertex tex coord
		    vt[vtSeen] = glm::vec2(strtof( tokens[1].c_str(), nullptr ),
                                   strtof( tokens[2].c_str(), nullptr ));
			vtSeen++;
		} else if( tokens[0] == "f" ) {                     //face!
			//now, faces can be either quads or triangles (or maybe more?)
			//split the string on spaces to get the number of verts+attrs.
			std::vector<std::string> faceTokens = _tokenizeString(line, " ");
            std::vector<std::string> processedFaceTokens;

			for(GLuint i = 1; i < faceTokens.size(); i++) {
                //need to use both the tokens and number of slashes to determine what info is there.
                std::vector<std::string> vertexAttributeTokens = _tokenizeString(faceTokens[i], "/");
                int numAttributeSlashes = 0;
                for(char j : faceTokens[i]) {
                    if(j == '/') numAttributeSlashes++;
                }

                std::stringstream currentFaceTokenStream;
                auto svx = (GLint)strtol(vertexAttributeTokens[0].c_str(), nullptr, 10);
                GLuint vx = svx;
                if(svx < 0) vx = vSeen + svx + 1;
                currentFaceTokenStream << vx;

                //based on combination of number of tokens and slashes, we can determine what we have.
                if(vertexAttributeTokens.size() == 2 && numAttributeSlashes == 1) {
                    _hasVertexTexCoords = true;

                    auto svtx = (GLint)strtol(vertexAttributeTokens[1].c_str(), nullptr, 10);
                    GLuint vtx = svtx;
                    if(svtx < 0) vtx = vtSeen + svtx + 1;
                    currentFaceTokenStream << "/" << vtx;
                } else if(vertexAttributeTokens.size() == 2 && numAttributeSlashes == 2) {
                    _hasVertexNormals = true;

                    auto svnx = (GLint)strtol(vertexAttributeTokens[1].c_str(), nullptr, 10);
                    GLuint vnx = svnx;
                    if(svnx < 0) vnx = vnSeen + svnx + 1;
                    currentFaceTokenStream << "//" << vnx;
                } else if(vertexAttributeTokens.size() == 3) {
                    _hasVertexTexCoords = true;
                    _hasVertexNormals = true;

                    auto svtx = (GLint)strtol(vertexAttributeTokens[1].c_str(), nullptr, 10);
                    GLuint vtx = svtx;
                    if(svtx < 0) vtx = vtSeen + svtx + 1;

                    auto svnx = (GLint)strtol(vertexAttributeTokens[2].c_str(), nullptr, 10);
                    GLuint vnx = svnx;
                    if(svnx < 0) vnx = vnSeen + svnx + 1;

                    currentFaceTokenStream << "/" << vtx << "/" << vnx;
                } else if(vertexAttributeTokens.size() != 1) {
                    if (ERRORS) fprintf(stderr, "[.obj]: [ERROR]: Malformed OBJ file, %s.\n", _filename.c_str());
                    return false;
                }

                std::string processedFaceToken = currentFaceTokenStream.str();
                processedFaceTokens.push_back(processedFaceToken);

				if( uniqueCounts.find( processedFaceToken ) == uniqueCounts.end() ) {
					uniqueCounts.insert( std::pair<std::string,GLuint>(processedFaceToken,uniqueV) );

					//need to use both the tokens and number of slashes to determine what info is there.
					std::vector<std::string> groupTokens = _tokenizeString(processedFaceToken, "/");
					int numSlashes = 0;
					for(char j : processedFaceToken) {
						if(j == '/') numSlashes++;
					}

					if( _hasVertexNormals || !sAUTO_GEN_NORMALS ) {
						//regardless, we always get a vertex index.
						auto svI = (GLint)strtol(groupTokens[0].c_str(), nullptr, 10);
                        GLuint vI = svI;
						if( svI < 0 ) vI = vSeen + svI + 1;
						_vertices[ _uniqueIndex ] = v[ vI - 1 ];

						//based on combination of number of tokens and slashes, we can determine what we have.
						if(groupTokens.size() == 2 && numSlashes == 1) {
							auto svtI = (GLint)strtol(groupTokens[1].c_str(), nullptr, 10);
                            GLuint vtI = svtI;
							if( svtI < 0 ) vtI = vtSeen + svtI + 1;
							_texCoords[ _uniqueIndex ] = vt[ vtI - 1 ];
						} else if(groupTokens.size() == 2 && numSlashes == 2) {
							auto svnI = (GLint)strtol(groupTokens[1].c_str(), nullptr, 10);
                            GLuint vnI = svnI;
							if( svnI < 0 ) vnI = vnSeen + svnI + 1;
							_normals[ _uniqueIndex ] = vn[ vnI - 1 ];
						} else if(groupTokens.size() == 3) {
							auto svtI = (GLint)strtol(groupTokens[1].c_str(), nullptr, 10);
                            GLuint vtI = svtI;
							if( svtI < 0 ) vtI = vtSeen + svtI + 1;
							_texCoords[ _uniqueIndex ] = vt[ vtI - 1 ];

							auto svnI = (GLint)strtol(groupTokens[2].c_str(), nullptr, 10);
                            GLuint vnI = svnI;
							if( svnI < 0 ) vnI = vnSeen + svnI + 1;
							_normals[ _uniqueIndex ] = vn[ vnI - 1 ];
						}

						_uniqueIndex++;
					} else {
						//regardless, we always get a vertex index.
						auto svI = (GLint)strtol(groupTokens[0].c_str(), nullptr, 10);
                        GLuint vI = svI;
						if( svI < 0 ) vI = vSeen + svI + 1;
						verticesTemps.push_back( v[ vI - 1 ] );

						//based on combination of number of tokens and slashes, we can determine what we have.
						if(groupTokens.size() == 2 && numSlashes == 1) {
							auto svtI = (GLint)strtol(groupTokens[1].c_str(), nullptr, 10);
                            GLuint vtI = svtI;
							if( svtI < 0 ) vtI = vtSeen + svtI + 1;
							texCoordsTemp.push_back( vt[ vtI - 1 ] );
						} else if(groupTokens.size() == 2 && numSlashes == 2) {
							// should not occur if no normals
							if (ERRORS) fprintf( stderr, "[.obj]: [WARN]: no vertex normals were specified, should not be trying to access values\n" );
						} else if(groupTokens.size() == 3) {
							auto svtI = (GLint)strtol(groupTokens[1].c_str(), nullptr, 10);
                            GLuint vtI = svtI;
							if( svtI < 0 ) vtI = vtSeen + svtI + 1;
							texCoordsTemp.push_back( vt[ vtI - 1 ] );

							// should not occur if no normals
							if (ERRORS) fprintf( stderr, "[.obj]: [WARN]: no vertex normals were specified, should not be trying to access values\n" );
						}
					}
					uniqueV++;
				}
			}

			for(GLuint i = 1; i < processedFaceTokens.size()-1; i++) {
				if( _hasVertexNormals || !sAUTO_GEN_NORMALS ) {
					_indices[ indicesSeen++ ] = uniqueCounts.find( processedFaceTokens[0]   )->second;
					_indices[ indicesSeen++ ] = uniqueCounts.find( processedFaceTokens[i]   )->second;
					_indices[ indicesSeen++ ] = uniqueCounts.find( processedFaceTokens[i+1] )->second;

					_numIndices += 3;
				} else {
					GLuint aI = uniqueCounts.find( processedFaceTokens[0]   )->second;
					GLuint bI = uniqueCounts.find( processedFaceTokens[i]   )->second;
					GLuint cI = uniqueCounts.find( processedFaceTokens[i+1] )->second;

					glm::vec3 a = verticesTemps[aI];
					glm::vec3 b = verticesTemps[bI];
					glm::vec3 c = verticesTemps[cI];

					glm::vec3 ab = b - a; glm::vec3 ac = c - a;
					glm::vec3 ba = a - b; glm::vec3 bc = c - b;
					glm::vec3 ca = a - c; glm::vec3 cb = b - c;

					glm::vec3 aN = glm::normalize( glm::cross( ab, ac ) );
					glm::vec3 bN = glm::normalize( glm::cross( bc, ba ) );
					glm::vec3 cN = glm::normalize( glm::cross( ca, cb ) );

					_vertices[ _uniqueIndex ] = a;
					_normals[ _uniqueIndex ] = aN;
					if( _hasVertexTexCoords ) { _texCoords[ _uniqueIndex ] = texCoordsTemp[ aI ]; }
					_indices[ _numIndices++ ] = _uniqueIndex++;

					indicesSeen++;

					_vertices[ _uniqueIndex ] = b;
					_normals[ _uniqueIndex ] = bN;
					if( _hasVertexTexCoords ) { _texCoords[ _uniqueIndex ] = texCoordsTemp[ bI ]; }
					_indices[ _numIndices++ ] = _uniqueIndex++;

					indicesSeen++;

					_vertices[ _uniqueIndex ] = c;
					_normals[ _uniqueIndex ] = cN;
					if( _hasVertexTexCoords ) { _texCoords[ _uniqueIndex ] = texCoordsTemp[ cI ]; }
					_indices[ _numIndices++ ] = _uniqueIndex++;

					indicesSeen++;
				}
			}

		}

		if (INFO) {
			progressCounter++;
			if( progressCounter % 5000 == 0 ) {
				printf("\33[2K\r");
				switch( progressCounter ) {
					case 5000:	printf("[.obj]: parsing %s...\\", _filename.c_str());	break;
					case 10000:	printf("[.obj]: parsing %s...|", _filename.c_str());	break;
					case 15000:	printf("[.obj]: parsing %s.../", _filename.c_str());	break;
					case 20000:	printf("[.obj]: parsing %s...-", _filename.c_str());	break;
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
		printf( "[.obj]: parsing %s...done!\n", _filename.c_str() );
	}

	_materialIndexStartStop.find( currentMaterial )->second.back().second = indicesSeen - 1;

	_bufferData();

	time(&end);
	double seconds = difftime( end, start );

	if (INFO) {
		printf( "[.obj]: Completed in %.3fs\n", seconds );
		printf( "[.obj]: -=-=-=-=-=-=-=-  END %s Info  -=-=-=-=-=-=-=- \n\n", _filename.c_str() );
	}

	return result;
}

inline bool CSCI441::ModelLoader::_loadMTLFile( const char* mtlFilename, bool INFO, bool ERRORS ) {
	bool result = true;

	if (INFO) printf( "[.mtl]: -*-*-*-*-*-*-*- BEGIN %s Info -*-*-*-*-*-*-*-\n", mtlFilename );

	std::string line;
	std::string path;
	if( _filename.find('/') != std::string::npos ) {
	 	path = _filename.substr( 0, _filename.find_last_of('/')+1 );
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
			currentMaterial->ambient[0] = strtof( tokens[1].c_str(), nullptr );
			currentMaterial->ambient[1] = strtof( tokens[2].c_str(), nullptr );
			currentMaterial->ambient[2] = strtof( tokens[3].c_str(), nullptr );
		} else if( tokens[0] == "Kd" ) {					// diffuse component
			currentMaterial->diffuse[0] = strtof( tokens[1].c_str(), nullptr );
			currentMaterial->diffuse[1] = strtof( tokens[2].c_str(), nullptr );
			currentMaterial->diffuse[2] = strtof( tokens[3].c_str(), nullptr );
		} else if( tokens[0] == "Ks" ) {					// specular component
			currentMaterial->specular[0] = strtof( tokens[1].c_str(), nullptr );
			currentMaterial->specular[1] = strtof( tokens[2].c_str(), nullptr );
			currentMaterial->specular[2] = strtof( tokens[3].c_str(), nullptr );
		} else if( tokens[0] == "Ke" ) {					// emissive component
			currentMaterial->emissive[0] = strtof( tokens[1].c_str(), nullptr );
			currentMaterial->emissive[1] = strtof( tokens[2].c_str(), nullptr );
			currentMaterial->emissive[2] = strtof( tokens[3].c_str(), nullptr );
		} else if( tokens[0] == "Ns" ) {					// shininess component
			currentMaterial->shininess = strtof( tokens[1].c_str(), nullptr );
		} else if( tokens[0] == "Tr"
					|| tokens[0] == "d" ) {					// transparency component - Tr or d can be used depending on the format
			currentMaterial->ambient[3] = strtof( tokens[1].c_str(), nullptr );
			currentMaterial->diffuse[3] = strtof( tokens[1].c_str(), nullptr );
			currentMaterial->specular[3] = strtof( tokens[1].c_str(), nullptr );
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

						GLint colorSpace = GL_RGB;
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

	if (INFO ) printf( "[.off]: -=-=-=-=-=-=-=- BEGIN %s Info -=-=-=-=-=-=-=-\n", _filename.c_str() );

	time_t start, end;
	time(&start);

	std::ifstream in( _filename );
	if( !in.is_open() ) {
		if (ERRORS) fprintf( stderr, "[.off]: [ERROR]: Could not open \"%s\"\n", _filename.c_str() );
		if ( INFO ) printf( "[.off]: -=-=-=-=-=-=-=-  END %s Info  -=-=-=-=-=-=-=-\n\n", _filename.c_str() );
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
		if( tokens[0] == "#" || tokens[0].find_first_of('#') == 0 ) {								// comment ignore
		} else if( fileState == HEADER ) {
			if( tokens[0] == "OFF" ) {					// denotes OFF File type
			} else {
				if( tokens.size() != 3 ) {
					if (ERRORS) fprintf( stderr, "[.off]: [ERROR]: Malformed OFF file.  # vertices, faces, edges not properly specified\n" );
					if ( INFO ) printf( "[.off]: -=-=-=-=-=-=-=-  END %s Info  -=-=-=-=-=-=-=-\n\n", _filename.c_str() );
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
			GLfloat x = strtof( tokens[0].c_str(), nullptr ),
                    y = strtof( tokens[1].c_str(), nullptr ),
                    z = strtof( tokens[2].c_str(), nullptr );

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
		printf( "[.off]: scanning %s...done!\n", _filename.c_str() );
		printf( "[.off]: ------------\n" );
		printf( "[.off]: Model Stats:\n" );
		printf( "[.off]: Vertices:  \t%u\tNormals:   \t%u\tTex Coords:\t%u\n", numVertices, 0, 0 );
		printf( "[.off]: Faces:     \t%u\tTriangles: \t%u\n", numFaces, numTriangles );
		printf( "[.off]: Dimensions:\t(%f, %f, %f)\n", (maxX - minX), (maxY - minY), (maxZ - minZ) );
	}

	if( _hasVertexNormals || !sAUTO_GEN_NORMALS ) {
		if (INFO && !_hasVertexNormals)
			printf( "[.off]: [WARN]: No vertex normals exist on model.  To autogenerate vertex\n\tnormals, call CSCI441::ModelLoader::enableAutoGenerateNormals()\n\tprior to loading the model file.\n" );
        _allocateAttributeArrays(numVertices, numTriangles*3);
	} else {
		if (INFO) printf( "[.off]: No vertex normals exist on model, vertex normals will be autogenerated\n" );
        _allocateAttributeArrays(numTriangles*3, numTriangles*3);
	}

	std::vector<glm::vec3> verticesTemp;

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
		if( tokens[0] == "#"  || tokens[0].find_first_of('#') == 0 ) {								// comment ignore
		} else if( fileState == HEADER ) {
			if( tokens[0] == "OFF" ) {					// denotes OFF File type
			} else {

				// end of OFF Header reached
				fileState = VERTICES;
			}
		} else if( fileState == VERTICES ) {
			// read in x y z vertex location
			glm::vec3 pos(strtof( tokens[0].c_str(), nullptr ),
                          strtof( tokens[1].c_str(), nullptr ),
                          strtof( tokens[2].c_str(), nullptr ) );

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

			if( _hasVertexNormals || !sAUTO_GEN_NORMALS ) {
				_vertices[ _uniqueIndex ] = pos;
				_uniqueIndex++;
			} else {
				verticesTemp.push_back(pos);
				vSeen++;
			}
			// if all vertices have been read in, move on to faces
			if( _uniqueIndex == numVertices || vSeen == numVertices )
				fileState = FACES;
		} else if( fileState == FACES ) {
			GLuint numberOfVerticesInFace = atoi( tokens[0].c_str() );

			// read in each vertex index of the face
			for(GLuint i = 2; i <= numberOfVerticesInFace - 1; i++) {
				if( _hasVertexNormals || !sAUTO_GEN_NORMALS ) {
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

					glm::vec3 a = verticesTemp[aI];
					glm::vec3 b = verticesTemp[bI];
					glm::vec3 c = verticesTemp[cI];

					glm::vec3 ab = b - a; glm::vec3 ac = c - a;
					glm::vec3 ba = a - b; glm::vec3 bc = c - b;
					glm::vec3 ca = a - c; glm::vec3 cb = b - c;

					glm::vec3 aN = glm::normalize( glm::cross( ab, ac ) );
					glm::vec3 bN = glm::normalize( glm::cross( bc, ba ) );
					glm::vec3 cN = glm::normalize( glm::cross( ca, cb ) );

					_vertices[ _uniqueIndex ] = a;
					_normals[ _uniqueIndex ] = aN;
					_indices[ _numIndices++ ] = _uniqueIndex++;

					_vertices[ _uniqueIndex ] = b;
					_normals[ _uniqueIndex ] = bN;
					_indices[ _numIndices++ ] = _uniqueIndex++;

					_vertices[ _uniqueIndex ] = c;
					_normals[ _uniqueIndex ] = cN;
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
					case 5000:	printf("[.off]: parsing %s...\\", _filename.c_str());	break;
					case 10000:	printf("[.off]: parsing %s...|", _filename.c_str());	break;
					case 15000:	printf("[.off]: parsing %s.../", _filename.c_str());	break;
					case 20000:	printf("[.off]: parsing %s...-", _filename.c_str());	break;
                    default: break;
				}
				fflush(stdout);
			}
			if( progressCounter == 20000 )
				progressCounter = 0;
		}
	}
	in.close();

    _bufferData();

	time(&end);
	double seconds = difftime( end, start );

	if (INFO) {
		printf( "\33[2K\r" );
		printf( "[.off]: parsing %s...done!  (Time: %.1fs)\n", _filename.c_str(), seconds );
		printf( "[.off]: -=-=-=-=-=-=-=-  END %s Info  -=-=-=-=-=-=-=-\n\n", _filename.c_str() );
	}

	return result;
}

// notes on PLY format: http://paulbourke.net/dataformats/ply/
inline bool CSCI441::ModelLoader::_loadPLYFile( bool INFO, bool ERRORS ) {
	bool result = true;

	if (INFO ) printf( "[.ply]: -=-=-=-=-=-=-=- BEGIN %s Info -=-=-=-=-=-=-=-\n", _filename.c_str() );

	time_t start, end;
	time(&start);

	std::ifstream in( _filename );
	if( !in.is_open() ) {
		if (ERRORS) fprintf( stderr, "[.ply]: [ERROR]: Could not open \"%s\"\n", _filename.c_str() );
		if ( INFO ) printf( "[.ply]: -=-=-=-=-=-=-=-  END %s Info  -=-=-=-=-=-=-=-\n\n", _filename.c_str() );
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
		if( tokens[0] == "comment" ) {								// comment ignore
		} else if( fileState == HEADER ) {
			if( tokens[0] == "ply" ) {					// denotes ply File type
			} else if( tokens[0] == "format" ) {
				if( tokens[1] != "ascii" ) {
					if (ERRORS) fprintf( stderr, "[.ply]: [ERROR]: File \"%s\" not ASCII format\n", _filename.c_str() );
					if ( INFO ) printf( "[.ply]: -=-=-=-=-=-=-=-  END %s Info  -=-=-=-=-=-=-=-\n\n", _filename.c_str() );
					in.close();
					return false;
				}
			} else if( tokens[0] == "element" ) {		// an element (vertex, face, material)
				if( tokens[1] == "vertex" ) {
					numVertices = atoi( tokens[2].c_str() );
					elemType = VERTEX;
				} else if( tokens[1] == "face" ) {
					numFaces = atoi( tokens[2].c_str() );
					elemType = FACE;
				} else if( tokens[1] == "edge" ) {

				} else if( tokens[1] == "material" ) {
					numMaterials = atoi( tokens[2].c_str() );
					elemType = MATERIAL;
				} else {

				}
			} else if( tokens[0] == "property" ) {
				if( elemType == VERTEX ) {

				} else if( elemType == FACE ) {

				} else if( elemType == MATERIAL ) {

				}
			} else if( tokens[0] == "end_header" ) {	// end of the header section
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
					case 5000:	printf("[.ply]: scanning %s...\\", _filename.c_str());	break;
					case 10000:	printf("[.ply]: scanning %s...|", _filename.c_str());	break;
					case 15000:	printf("[.ply]: scanning %s.../", _filename.c_str());	break;
					case 20000:	printf("[.ply]: scanning %s...-", _filename.c_str());	break;
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
		printf( "[.ply]: scanning %s...done!\n", _filename.c_str() );
		printf( "[.ply]: ------------\n" );
		printf( "[.ply]: Model Stats:\n" );
		printf( "[.ply]: Vertices:  \t%u\tNormals:   \t%u\tTex Coords:\t%u\n", numVertices, 0, 0 );
		printf( "[.ply]: Faces:     \t%u\tTriangles: \t%u\n", numFaces, numTriangles );
		printf( "[.ply]: Dimensions:\t(%f, %f, %f)\n", (maxX - minX), (maxY - minY), (maxZ - minZ) );
	}

	if( _hasVertexNormals || !sAUTO_GEN_NORMALS ) {
		if (INFO && !_hasVertexNormals)
			printf( "[.ply]: [WARN]: No vertex normals exist on model.  To autogenerate vertex\n\tnormals, call CSCI441::ModelLoader::enableAutoGenerateNormals()\n\tprior to loading the model file.\n" );
        _allocateAttributeArrays(numVertices, numTriangles*3);
	} else {
		if (INFO) printf( "[.ply]: No vertex normals exist on model, vertex normals will be autogenerated\n" );
        _allocateAttributeArrays(numTriangles*3, numTriangles*3);
	}

	if (INFO) printf( "[.ply]: ------------\n" );

	std::vector<glm::vec3> verticesTemp;

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
		if( tokens[0] == "comment" ) {								// comment ignore
		} else if( fileState == HEADER ) {
			if( tokens[0] == "ply" ) {					// denotes ply File type
			} else if( tokens[0] == "format" ) {
				if( tokens[1] != "ascii" ) {
					if (ERRORS) fprintf( stderr, "[.ply]: [ERROR]: File \"%s\" not ASCII format\n", _filename.c_str() );
					if ( INFO ) printf( "[.ply]: -=-=-=-=-=-=-=-  END %s Info  -=-=-=-=-=-=-=-\n\n", _filename.c_str() );
					in.close();
					return false;
				}
			} else if( tokens[0] == "element" ) {		// an element (vertex, face, material)
				if( tokens[1] == "vertex" ) {
					numVertices = atoi( tokens[2].c_str() );
					elemType = VERTEX;
				} else if( tokens[1] == "face" ) {
					numFaces = atoi( tokens[2].c_str() );
					elemType = FACE;
				} else if( tokens[1] == "edge" ) {

				} else if( tokens[1] == "material" ) {
					numMaterials = atoi( tokens[2].c_str() );
					elemType = MATERIAL;
				} else {

				}
			} else if( tokens[0] == "property" ) {
				if( elemType == VERTEX ) {

				} else if( elemType == FACE ) {

				} else if( elemType == MATERIAL ) {

				}
			} else if( tokens[0] == "end_header" ) {	// end of the header section
				fileState = VERTICES;
			}
		} else if( fileState == VERTICES ) {
			// read in x y z vertex location
			glm::vec3 pos(strtof( tokens[0].c_str(), nullptr ),
                          strtof( tokens[1].c_str(), nullptr ),
                          strtof( tokens[2].c_str(), nullptr ) );

			if( _hasVertexNormals || !sAUTO_GEN_NORMALS ) {
				_vertices[ _uniqueIndex ] = pos;
				_uniqueIndex++;
			} else {
				verticesTemp.push_back(pos );
				vSeen++;
			}
			// if all vertices have been read in, move on to faces
			if( _uniqueIndex == numVertices || vSeen == numVertices )
				fileState = FACES;
		} else if( fileState == FACES ) {
			GLuint numberOfVerticesInFace = atoi( tokens[0].c_str() );

			for( GLuint i = 2; i <= numberOfVerticesInFace - 1; i++ ) {
				if( _hasVertexNormals || !sAUTO_GEN_NORMALS ) {
					_indices[ _numIndices++ ] = atoi( tokens[1].c_str() );
					_indices[ _numIndices++ ] = atoi( tokens[i].c_str() );
					_indices[ _numIndices++ ] = atoi( tokens[i+1].c_str() );
				} else {
					GLuint aI = atoi( tokens[1].c_str() );
					GLuint bI = atoi( tokens[i].c_str() );
					GLuint cI = atoi( tokens[i+1].c_str() );

					glm::vec3 a = verticesTemp[aI];
					glm::vec3 b = verticesTemp[bI];
					glm::vec3 c = verticesTemp[cI];

					glm::vec3 ab = b - a; glm::vec3 ac = c - a;
					glm::vec3 ba = a - b; glm::vec3 bc = c - b;
					glm::vec3 ca = a - c; glm::vec3 cb = b - c;

					glm::vec3 aN = glm::normalize( glm::cross( ab, ac ) );
					glm::vec3 bN = glm::normalize( glm::cross( bc, ba ) );
					glm::vec3 cN = glm::normalize( glm::cross( ca, cb ) );

					_vertices[ _uniqueIndex ] = a;
					_normals[ _uniqueIndex ] = aN;
					_indices[ _numIndices++ ] = _uniqueIndex++;

					_vertices[ _uniqueIndex ] = b;
					_normals[ _uniqueIndex ] = bN;
					_indices[ _numIndices++ ] = _uniqueIndex++;

					_vertices[ _uniqueIndex ] = c;
					_normals[ _uniqueIndex ] = cN;
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
					case 5000:	printf("[.ply]: parsing %s...\\", _filename.c_str());	break;
					case 10000:	printf("[.ply]: parsing %s...|", _filename.c_str());	break;
					case 15000:	printf("[.ply]: parsing %s.../", _filename.c_str());	break;
					case 20000:	printf("[.ply]: parsing %s...-", _filename.c_str());	break;
                    default: break;
				}
				fflush(stdout);
			}
			if( progressCounter == 20000 )
				progressCounter = 0;
		}
	}
	in.close();

    _bufferData();

	time(&end);
	double seconds = difftime( end, start );

	if (INFO) {
		printf( "\33[2K\r" );
		printf( "[.ply]: parsing %s...done!\n[.ply]: Time to complete: %.3fs\n", _filename.c_str(), seconds );
		printf( "[.ply]: -=-=-=-=-=-=-=-  END %s Info  -=-=-=-=-=-=-=-\n\n", _filename.c_str() );
	}

	return result;
}

inline bool CSCI441::ModelLoader::_loadSTLFile( bool INFO, bool ERRORS ) {
	bool result = true;

	if (INFO) printf( "[.stl]: -=-=-=-=-=-=-=- BEGIN %s Info -=-=-=-=-=-=-=-\n", _filename.c_str() );

	time_t start, end;
	time(&start);

	std::ifstream in( _filename );
	if( !in.is_open() ) {
		if (ERRORS) fprintf(stderr, "[.stl]: [ERROR]: Could not open \"%s\"\n", _filename.c_str() );
		if ( INFO ) printf( "[.stl]: -=-=-=-=-=-=-=-  END %s Info  -=-=-=-=-=-=-=-\n\n", _filename.c_str() );
		return false;
	}

	GLuint numVertices = 0, numNormals = 0, numFaces = 0, numTriangles = 0, numVertsInLoop = 0;
	GLfloat minX = 999999.0f, maxX = -999999.0f, minY = 999999.0f, maxY = -999999.0f, minZ = 999999.0f, maxZ = -999999.0f;
	std::string line;

	int progressCounter = 0;
	glm::vec3 normalVector = {0.f,0.f,0.f};

	while( getline( in, line ) ) {
		if( line.length() > 1 && line.at(0) == '\t' )
			line = line.substr( 1 );
		line.erase( line.find_last_not_of( " \n\r\t" ) + 1 );

		std::vector< std::string > tokens = _tokenizeString( line, " \t" );

		if( tokens.empty() ) continue;

		if( tokens[0] == "solid" ) {

		} else if( tokens[0] == "facet" ) {
			// read in x y z triangle normal
			numNormals++;
		} else if( tokens[0] == "outer" && tokens[1] == "loop" ) {
			// begin a primitive
			numVertsInLoop = 0;
		} else if( tokens[0] == "vertex" ) {
			GLfloat x = strtof( tokens[1].c_str(), nullptr ),
					y = strtof( tokens[2].c_str(), nullptr ),
					z = strtof( tokens[3].c_str(), nullptr );

			if( x < minX ) minX = x;
			if( x > maxX ) maxX = x;
			if( y < minY ) minY = y;
			if( y > maxY ) maxY = y;
			if( z < minZ ) minZ = z;
			if( z > maxZ ) maxZ = z;

			numVertices++;
			numVertsInLoop++;
		} else if( tokens[0] == "endloop" ) {
			// end primitive
			numTriangles += numVertsInLoop - 3 + 1;
		} else if( tokens[0] == "endfacet" ) {
			numFaces++;
		} else if( tokens[0] == "endsolid" ) {

		}
		else {
			if( memchr( line.c_str(), '\0', line.length() ) != NULL ) {
				if (ERRORS) fprintf( stderr, "[.stl]: [ERROR]: Cannot read binary STL file \"%s\"\n", _filename.c_str() );
				if ( INFO ) printf( "[.stl]: -=-=-=-=-=-=-=-  END %s Info  -=-=-=-=-=-=-=-\n\n", _filename.c_str() );
				in.close();
				return false;
			} else if (INFO) printf( "[.stl]: unknown line: %s\n", line.c_str() );
		}

		if (INFO) {
			progressCounter++;
			if( progressCounter % 5000 == 0 ) {
				printf("\33[2K\r");
				switch( progressCounter ) {
					case 5000:	printf("[.stl]: scanning %s...\\", _filename.c_str());	break;
					case 10000:	printf("[.stl]: scanning %s...|", _filename.c_str());	break;
					case 15000:	printf("[.stl]: scanning %s.../", _filename.c_str());	break;
					case 20000:	printf("[.stl]: scanning %s...-", _filename.c_str());	break;
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
		printf( "[.stl]: scanning %s...done!\n", _filename.c_str() );
		printf( "[.stl]: ------------\n" );
		printf( "[.stl]: Model Stats:\n" );
		printf( "[.stl]: Vertices:  \t%u\tNormals:   \t%u\tTex Coords:\t%u\n", numVertices, numNormals, 0 );
		printf( "[.stl]: Faces:     \t%u\tTriangles: \t%u\n", numFaces, numTriangles );
		printf( "[.stl]: Dimensions:\t(%f, %f, %f)\n", (maxX - minX), (maxY - minY), (maxZ - minZ) );
	}

    _allocateAttributeArrays(numVertices, numTriangles*3);

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

		if( tokens[0] == "solid" ) {

		} else if( tokens[0] == "facet" ) {
			// read in x y z triangle normal
			normalVector = glm::vec3( strtof( tokens[2].c_str(), nullptr ),
                                      strtof( tokens[3].c_str(), nullptr ),
                                      strtof( tokens[4].c_str(), nullptr ) );
		} else if( tokens[0] == "outer" && tokens[1] == "loop" ) {
			// begin a primitive
		} else if( tokens[0] == "vertex" ) {
			_vertices[ _uniqueIndex ] = glm::vec3(strtof( tokens[1].c_str(), nullptr ),
                                                  strtof( tokens[2].c_str(), nullptr ),
                                                  strtof( tokens[3].c_str(), nullptr ) );
			_normals[ _uniqueIndex ] = normalVector;
			_indices[ _numIndices++ ] = _uniqueIndex++;
		} else if( tokens[0] == "endloop" ) {
			// end primitive
		} else if( tokens[0] == "endfacet" ) {

		} else if( tokens[0] == "endsolid" ) {

		}
		else {

		}

		if (INFO) {
			progressCounter++;
			if( progressCounter % 5000 == 0 ) {
				printf("\33[2K\r");
				switch( progressCounter ) {
					case 5000:	printf("[.stl]: parsing %s...\\", _filename.c_str());	break;
					case 10000:	printf("[.stl]: parsing %s...|", _filename.c_str());	break;
					case 15000:	printf("[.stl]: parsing %s.../", _filename.c_str());	break;
					case 20000:	printf("[.stl]: parsing %s...-", _filename.c_str());	break;
                    default: break;
				}
				fflush(stdout);
			}
			if( progressCounter == 20000 )
				progressCounter = 0;
		}
	}
	in.close();

	_bufferData();

	time(&end);
	double seconds = difftime( end, start );

	if (INFO) {
		printf("\33[2K\r");
		printf("[.stl]: parsing %s...done!\n[.stl]: Time to complete: %.3fs\n", _filename.c_str(), seconds);
		printf( "[.stl]: -=-=-=-=-=-=-=-  END %s Info  -=-=-=-=-=-=-=-\n\n", _filename.c_str() );
	}

	return result;
}

[[maybe_unused]]
inline void CSCI441::ModelLoader::enableAutoGenerateNormals() {
    sAUTO_GEN_NORMALS = true;
}

[[maybe_unused]]
inline void CSCI441::ModelLoader::disableAutoGenerateNormals() {
    sAUTO_GEN_NORMALS = false;
}

inline void CSCI441::ModelLoader::_allocateAttributeArrays(const GLuint numVertices, const GLuint numIndices) {
    _vertices  = new glm::vec3[numVertices];
    _normals   = new glm::vec3[numVertices];
    _texCoords = new glm::vec2[numVertices];
    _indices   = new GLuint[numIndices];
}

inline void CSCI441::ModelLoader::_bufferData() {
    glBindVertexArray( _vaod );
    glBindBuffer( GL_ARRAY_BUFFER, _vbods[0] );
    glBufferData( GL_ARRAY_BUFFER, (sizeof(glm::vec3)*2 + sizeof(glm::vec2)) * _uniqueIndex, nullptr, GL_STATIC_DRAW );
    glBufferSubData( GL_ARRAY_BUFFER, 0, sizeof(glm::vec3) * _uniqueIndex, _vertices );
    glBufferSubData( GL_ARRAY_BUFFER, sizeof(glm::vec3) * _uniqueIndex, sizeof(glm::vec3) * _uniqueIndex, _normals );
    glBufferSubData( GL_ARRAY_BUFFER, sizeof(glm::vec3) * _uniqueIndex * 2, sizeof(glm::vec2) * _uniqueIndex, _texCoords );

    glBindBuffer( GL_ELEMENT_ARRAY_BUFFER, _vbods[1] );
    glBufferData( GL_ELEMENT_ARRAY_BUFFER, sizeof(GLuint) * _numIndices, _indices, GL_STATIC_DRAW );
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
	GLint lowerValidIndex = 0, upperValidIndex = (GLint)input.size() - 1;
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
