/** @file ShaderProgram.hpp
 * @brief Class to work with OpenGL 3.0+ Shaders
 * @author Dr. Jeffrey Paone
 *
 * @copyright MIT License Copyright (c) 2017 Dr. Jeffrey Paone
 *
 *	These functions, classes, and constants help minimize common
 *	code that needs to be written.
 *
 *	@warning NOTE: This header file depends upon glm
 */

#ifndef CSCI441_SHADER_PROGRAM_HPP
#define CSCI441_SHADER_PROGRAM_HPP

#include "ShaderUtils.hpp"

#include <glm/glm.hpp>

#include <cstdlib>
#include <fstream>
#include <map>
#include <string>
#include <vector>

////////////////////////////////////////////////////////////////////////////////

namespace CSCI441 {

    /**
     * @class ShaderProgram
     * @brief Handles registration and compilation of Shaders
     */
    class ShaderProgram {
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
         * @brief Creates a Shader Program using a Vertex Shader and Fragment Shader
         * @param vertexShaderFilename name of the file corresponding to the vertex shader
         * @param fragmentShaderFilename name of the file corresponding to the fragment shader
         */
        ShaderProgram( const char *vertexShaderFilename,
                       const char *fragmentShaderFilename );

        /**
         * @brief Creates a Shader Program using a Vertex Shader and Fragment Shader
         * @param vertexShaderFilename name of the file corresponding to the vertex shader
         * @param fragmentShaderFilename name of the file corresponding to the fragment shader
         * @param isSeparable if program is separable
         */
        [[maybe_unused]]
        ShaderProgram( const char *vertexShaderFilename,
                       const char *fragmentShaderFilename,
                       bool isSeparable );

        /** @brief Creates a Shader Program using a Vertex Shader, Tesselation Shader, Geometry Shader, and Fragment Shader
              *
              * @param const char* vertexShaderFilename - name of the file corresponding to the vertex shader
              * @param const char* tesselationControlShaderFilename - name of the file corresponding to the tesselation control shader
              * @param const char* tesselationEvaluationShaderFilename - name of the file corresponding to the tesselation evaluation shader
              * @param const char* geometryShaderFilename - name of the file corresponding to the geometry shader
              * @param const char* fragmentShaderFilename - name of the file corresponding to the fragment shader
              */
        ShaderProgram( const char *vertexShaderFilename,
                       const char *tesselationControlShaderFilename,
                       const char *tesselationEvaluationShaderFilename,
                       const char *geometryShaderFilename,
                       const char *fragmentShaderFilename );

        /** @brief Creates a Shader Program using a Vertex Shader, Tesselation Shader, Geometry Shader, and Fragment Shader
              *
              * @param const char* vertexShaderFilename - name of the file corresponding to the vertex shader
              * @param const char* tesselationControlShaderFilename - name of the file corresponding to the tesselation control shader
              * @param const char* tesselationEvaluationShaderFilename - name of the file corresponding to the tesselation evaluation shader
              * @param const char* geometryShaderFilename - name of the file corresponding to the geometry shader
              * @param const char* fragmentShaderFilename - name of the file corresponding to the fragment shader
         * @param const bool isSeparable - if program is separable
              */
        ShaderProgram( const char *vertexShaderFilename,
                       const char *tesselationControlShaderFilename,
                       const char *tesselationEvaluationShaderFilename,
                       const char *geometryShaderFilename,
                       const char *fragmentShaderFilename,
                       const bool isSeparable );

        /** @brief Creates a Shader Program using a Vertex Shader, Tesselation Shader, and Fragment Shader
             *
             * @param const char* vertexShaderFilename - name of the file corresponding to the vertex shader
             * @param const char* tesselationControlShaderFilename - name of the file corresponding to the tesselation control shader
             * @param const char* tesselationEvaluationShaderFilename - name of the file corresponding to the tesselation evaluation shader
             * @param const char* fragmentShaderFilename - name of the file corresponding to the fragment shader
             */
        ShaderProgram( const char *vertexShaderFilename,
                       const char *tesselationControlShaderFilename,
                       const char *tesselationEvaluationShaderFilename,
                       const char *fragmentShaderFilename );

        /** @brief Creates a Shader Program using a Vertex Shader, Tesselation Shader, and Fragment Shader
             *
             * @param const char* vertexShaderFilename - name of the file corresponding to the vertex shader
             * @param const char* tesselationControlShaderFilename - name of the file corresponding to the tesselation control shader
             * @param const char* tesselationEvaluationShaderFilename - name of the file corresponding to the tesselation evaluation shader
             * @param const char* fragmentShaderFilename - name of the file corresponding to the fragment shader
             * @param const bool isSeparable - if program is separable
             */
        ShaderProgram( const char *vertexShaderFilename,
                       const char *tesselationControlShaderFilename,
                       const char *tesselationEvaluationShaderFilename,
                       const char *fragmentShaderFilename,
                       const bool isSeparable);

        /** @brief Creates a Shader Program using a Vertex Shader, Geometry Shader, and Fragment Shader
          *
            * @param const char* vertexShaderFilename - name of the file corresponding to the vertex shader
            * @param const char* geometryShaderFilename - name of the file corresponding to the geometry shader
            * @param const char* fragmentShaderFilename - name of the file corresponding to the fragment shader
            */
        ShaderProgram( const char *vertexShaderFilename,
                       const char *geometryShaderFilename,
                       const char *fragmentShaderFilename );

        /** @brief Creates a Shader Program using a Vertex Shader, Geometry Shader, and Fragment Shader
          *
            * @param const char* vertexShaderFilename - name of the file corresponding to the vertex shader
            * @param const char* geometryShaderFilename - name of the file corresponding to the geometry shader
            * @param const char* fragmentShaderFilename - name of the file corresponding to the fragment shader
             * @param const bool isSeparable - if program is separable
            */
        ShaderProgram( const char *vertexShaderFilename,
                       const char *geometryShaderFilename,
                       const char *fragmentShaderFilename,
                       const bool isSeparable );

        /** @brief Creates a Shader Program using any combination of shaders.  Intended to be used to create separable programs
         * but can be used as an alternative to the above overloaded constructors to explicitly state which shaders are present.
         *
         * @param const char **shaderFilenames - an array of filenames corresponding to all the shaders.  size must be equal to
         * the sum of true shaders present, with two for the tessellation shader
         *
         * @param const bool vertexPresent - if vertex shader is present
         * @param const bool tessellationPresent - if tessellation shader is present
         * @param const bool geometryPresent - if geometry shader is present
         * @param const bool fragmentPresent - if fragment shader is present
         * @param const bool isSeparable - if program is separable
         */
        ShaderProgram( const char **shaderFilenames,
                       const bool vertexPresent, const bool tessellationPresent, const bool geometryPresent, const bool fragmentPresent,
                       const bool isSeparable );

        /** @brief Clean up memory associated with the Shader Program
             */
        ~ShaderProgram();

        bool writeShaderProgramBinaryToFile(const char* BINARY_FILE_NAME);

        static ShaderProgram* loadShaderProgramFromBinaryFile(const char* BINARY_FILE_NAME, GLenum format);

        /** @brief Returns the location of the given uniform in this shader program
          * @note Prints an error message to standard error stream if the uniform is not found
            * @param const char* uniformName - name of the uniform to get the location for
          * @return GLint - location of the given uniform in this shader program
          */
        GLint getUniformLocation( const char *uniformName ) const;

        /** @brief Returns the index of the given uniform block in this shader program
          * @note Prints an error message to standard error stream if the uniform block is not found
            * @param const char* uniformBlockName - name of the uniform block to get the index for
          * @return GLint - index of the given uniform block in this shader program
          */
        GLint getUniformBlockIndex( const char *uniformBlockName ) const;
        /** @brief Returns the size of the given uniform block in this shader program
          * @note Prints an error message to standard error stream if the uniform block is not found
            * @param const char* uniformBlockName - name of the uniform block to get the size for
          * @return GLint - size of the given uniform block in this shader program
          */
        GLint getUniformBlockSize( const char *uniformBlockName ) const;
        /** @brief Returns an allocated buffer for the given uniform block in this shader program
          * @note Prints an error message to standard error stream if the uniform block is not found
            * @param const char* uniformBlockName - name of the uniform block to allocate a buffer for
          * @return GLubyte* - allocated buffer for the given uniform block in this shader program
          */
        GLubyte* getUniformBlockBuffer( const char *uniformBlockName ) const;
        /** @brief Returns an array of offsets into the buffer for the given uniform block in this shader program
          * @note Prints an error message to standard error stream if the uniform block is not found
            * @param const char* uniformBlockName - name of the uniform block to return offsets for
          * @return GLint* - array of offsets for the given uniform block in this shader program
          */
        GLint* getUniformBlockOffsets( const char *uniformBlockName ) const;
        /** @brief Returns an array of offsets into the buffer for the given uniform block and names in this shader program
          * @note Prints an error message to standard error stream if the uniform block is not found
            * @param const char* uniformBlockName - name of the uniform block to return offsets for
            * @param const char* names[] - names of the uniform block components to get offsets for
          * @return GLint* - array of offsets for the given uniform block in this shader program
          */
        GLint* getUniformBlockOffsets( const char *uniformBlockName, const char *names[] ) const;
        /** @brief Set the binding point for the given uniform block in this shader program
          * @note Prints an error message to standard error stream if the uniform block is not found
            * @param const char* uniformBlockName - name of the uniform block to bind
            * @param GLuint binding               - binding point for this uniform block
          */
        void setUniformBlockBinding( const char *uniformBlockName, GLuint binding ) const;

        /** @brief Returns the location of the given attribute in this shader program
          * @note Prints an error message to standard error stream if the attribute is not found
          * @param const char* attributeName - name of the attribute to get the location for
          * @return GLint - location of the given attribute in this shader program
          */
        GLint getAttributeLocation( const char *attributeName ) const;

        /** @brief Returns the index of the given subroutine for a shader stage in this shader program
          * @note Prints an error message to standard error stream if the subroutine is not found
            * @param GLenum shaderStage         - stage of the shader program to get the subroutine for.
            *   Allowable values: GL_VERTEX_SHADER, GL_TESS_CONTROL_SHADER, GL_TESS_EVALUATION_SHADER, GL_GEOMETRY_SHADER, GL_FRAGMENT_SHADER
            * @param const char* subroutineName - name of the subroutine to get the location for
          * @return GLuint - index of the given subroutine for the shader stage in this shader program
          */
        GLuint getSubroutineIndex( GLenum shaderStage, const char *subroutineName ) const;

        /**
         * @brief Returns the binding point for the corresponding image uniform
         * @param imageName
         * @return
         */
        GLint getImageBinding(const char* imageName) const;

        /**
         * @brief Returns the binding point for the corresponding shader storage block
         * @param ssboName
         * @return
         */
        GLint getShaderStorageBlockBinding(const char* ssboName) const;

        /**
         * @brief Returns the binding point for the corresponding atomic counter buffer
         * @param atomicName
         * @return
         */
        GLint getAtomicCounterBufferBinding(const char* atomicName) const;
        /**
         * @brief Returns the offset into the buffer for the corresponding atomic counter buffer
         * @param atomicName
         * @return
         */
        GLint getAtomicCounterBufferOffset(const char* atomicName) const;
        /**
         * @brief Returns the full buffer size for the corresponding atomic counter buffer
         * @param atomicName
         * @return
         */
        GLint getAtomicCounterBufferSize(const char* atomicName) const;

        /** @brief Returns the number of active uniforms in this shader program
          * @return GLuint - number of active uniforms in this shader program
          */
        [[nodiscard]] GLuint getNumUniforms() const;
        /** @brief Returns the number of active uniform blocks in this shader program
          * @return GLuint - number of active uniform blocks in this shader program
          */
        [[nodiscard]] GLuint getNumUniformBlocks() const;
        /** @brief Returns the number of active attributes in this shader program
          * @return GLuint - number of active attributes in this shader program
          */
        [[nodiscard]] GLuint getNumAttributes() const;

        /** @brief Returns the handle for this shader program
          * @return GLuint - handle for this shader program
          */
        [[nodiscard]] GLuint getShaderProgramHandle() const;

        /** @brief Sets the Shader Program to be active
          */
        void useProgram() const;

        /**
         * @brief sets the program uniform consisting of one float
         * @param uniformName name of the uniform as a string
         * @param v0 value to set
         */
        void setProgramUniform(const char* uniformName, GLfloat v0) const;
        /**
         * @brief sets the program uniform consisting of two floats
         * @param uniformName name of the uniform as a string
         * @param v0 value to set
         * @param v1 value to set
         */
        void setProgramUniform(const char* uniformName, GLfloat v0, GLfloat v1) const;
        /**
         * @brief sets the program uniform consisting of two floats
         * @param uniformName name of the uniform as a string
         * @param value value to set
         */
        void setProgramUniform(const char* uniformName, glm::vec2 value) const;
        /**
         * @brief sets the program uniform consisting of three floats
         * @param uniformName name of the uniform as a string
         * @param v0 value to set
         * @param v1 value to set
         * @param v2 value to set
         */
        void setProgramUniform(const char* uniformName, GLfloat v0, GLfloat v1, GLfloat v2) const;
        /**
         * @brief sets the program uniform consisting of three floats
         * @param uniformName name of the uniform as a string
         * @param value value to set
         */
        void setProgramUniform(const char* uniformName, glm::vec3 value) const;
        /**
         * @brief sets the program uniform consisting of four floats
         * @param uniformName name of the uniform as a string
         * @param v0 value to set
         * @param v1 value to set
         * @param v2 value to set
         * @param v3 value to set
         */
        void setProgramUniform(const char* uniformName, GLfloat v0, GLfloat v1, GLfloat v2, GLfloat v3) const;
        /**
         * @brief sets the program uniform consisting of four floats
         * @param uniformName name of the uniform as a string
         * @param value value to set
         */
        void setProgramUniform(const char* uniformName, glm::vec4 value) const;
        /**
         * @brief sets the program uniform consisting of floats
         * @param uniformName name of the uniform as a string
         * @param dim dimension (number of components) for each value
         * @param count number of values in array
         * @param value array of values (array size is equal to dim*count)
         */
        void setProgramUniform(const char* uniformName, GLuint dim, GLsizei count, const GLfloat *value) const;
        void setProgramUniform(const char* uniformName, GLint v0) const;
        void setProgramUniform(const char* uniformName, GLint v0, GLint v1) const;
        void setProgramUniform(const char* uniformName, glm::ivec2 value) const;
        void setProgramUniform(const char* uniformName, GLint v0, GLint v1, GLint v2) const;
        void setProgramUniform(const char* uniformName, glm::ivec3 value) const;
        void setProgramUniform(const char* uniformName, GLint v0, GLint v1, GLint v2, GLint v3) const;
        void setProgramUniform(const char* uniformName, glm::ivec4 value) const;
        void setProgramUniform(const char* uniformName, GLuint dim, GLsizei count, const GLint *value) const;
        void setProgramUniform(const char* uniformName, GLuint v0) const;
        void setProgramUniform(const char* uniformName, GLuint v0, GLuint v1) const;
        void setProgramUniform(const char* uniformName, glm::uvec2 value) const;
        void setProgramUniform(const char* uniformName, GLuint v0, GLuint v1, GLuint v2) const;
        void setProgramUniform(const char* uniformName, glm::uvec3 value) const;
        void setProgramUniform(const char* uniformName, GLuint v0, GLuint v1, GLuint v2, GLuint v3) const;
        void setProgramUniform(const char* uniformName, glm::uvec4 value) const;
        void setProgramUniform(const char* uniformName, GLuint dim, GLsizei count, const GLuint *value) const;
        void setProgramUniform(const char* uniformName, glm::mat2 mtx) const;
        void setProgramUniform(const char* uniformName, glm::mat3 mtx) const;
        void setProgramUniform(const char* uniformName, glm::mat4 mtx) const;
        void setProgramUniform(const char* uniformName, glm::mat2x3 mtx) const;
        void setProgramUniform(const char* uniformName, glm::mat3x2 mtx) const;
        void setProgramUniform(const char* uniformName, glm::mat2x4 mtx) const;
        void setProgramUniform(const char* uniformName, glm::mat4x2 mtx) const;
        void setProgramUniform(const char* uniformName, glm::mat3x4 mtx) const;
        void setProgramUniform(const char* uniformName, glm::mat4x3 mtx) const;

        void setProgramUniform(GLint uniformLocation, GLfloat v0) const;
        void setProgramUniform(GLint uniformLocation, GLfloat v0, GLfloat v1) const;
        void setProgramUniform(GLint uniformLocation, glm::vec2 value) const;
        void setProgramUniform(GLint uniformLocation, GLfloat v0, GLfloat v1, GLfloat v2) const;
        void setProgramUniform(GLint uniformLocation, glm::vec3 value) const;
        void setProgramUniform(GLint uniformLocation, GLfloat v0, GLfloat v1, GLfloat v2, GLfloat v3) const;
        void setProgramUniform(GLint uniformLocation, glm::vec4 value) const;
        void setProgramUniform(GLint uniformLocation, GLuint dim, GLsizei count, const GLfloat *value) const;
        void setProgramUniform(GLint uniformLocation, GLint v0) const;
        void setProgramUniform(GLint uniformLocation, GLint v0, GLint v1) const;
        void setProgramUniform(GLint uniformLocation, glm::ivec2 value) const;
        void setProgramUniform(GLint uniformLocation, GLint v0, GLint v1, GLint v2) const;
        void setProgramUniform(GLint uniformLocation, glm::ivec3 value) const;
        void setProgramUniform(GLint uniformLocation, GLint v0, GLint v1, GLint v2, GLint v3) const;
        void setProgramUniform(GLint uniformLocation, glm::ivec4 value) const;
        void setProgramUniform(GLint uniformLocation, GLuint dim, GLsizei count, const GLint *value) const;
        void setProgramUniform(GLint uniformLocation, GLuint v0) const;
        void setProgramUniform(GLint uniformLocation, GLuint v0, GLuint v1) const;
        void setProgramUniform(GLint uniformLocation, glm::uvec2 value) const;
        void setProgramUniform(GLint uniformLocation, GLuint v0, GLuint v1, GLuint v2) const;
        void setProgramUniform(GLint uniformLocation, glm::uvec3 value) const;
        void setProgramUniform(GLint uniformLocation, GLuint v0, GLuint v1, GLuint v2, GLuint v3) const;
        void setProgramUniform(GLint uniformLocation, glm::uvec4 value) const;
        void setProgramUniform(GLint uniformLocation, GLuint dim, GLsizei count, const GLuint *value) const;
        void setProgramUniform(GLint uniformLocation, glm::mat2 mtx) const;
        void setProgramUniform(GLint uniformLocation, glm::mat3 mtx) const;
        void setProgramUniform(GLint uniformLocation, glm::mat4 mtx) const;
        void setProgramUniform(GLint uniformLocation, glm::mat2x3 mtx) const;
        void setProgramUniform(GLint uniformLocation, glm::mat3x2 mtx) const;
        void setProgramUniform(GLint uniformLocation, glm::mat2x4 mtx) const;
        void setProgramUniform(GLint uniformLocation, glm::mat4x2 mtx) const;
        void setProgramUniform(GLint uniformLocation, glm::mat3x4 mtx) const;
        void setProgramUniform(GLint uniformLocation, glm::mat4x3 mtx) const;

    protected:
        ShaderProgram();

        static bool sDEBUG;

        GLuint mVertexShaderHandle;
        GLuint mTesselationControlShaderHandle;
        GLuint mTesselationEvaluationShaderHandle;
        GLuint mGeometryShaderHandle;
        GLuint mFragmentShaderHandle;

        GLuint mShaderProgramHandle;

        std::map<std::string, GLint> *mpUniformLocationsMap;
        std::map<std::string, GLint> *mpAttributeLocationsMap;

        bool mRegisterShaderProgram(const char *vertexShaderFilename,
                                    const char *tesselationControlShaderFilename,
                                    const char *tesselationEvaluationShaderFilename,
                                    const char *geometryShaderFilename,
                                    const char *fragmentShaderFilename,
                                    const bool isSeparable );

        [[nodiscard]] GLint* mGetUniformBlockOffsets(GLint uniformBlockIndex ) const;
        [[nodiscard]] GLint* mGetUniformBlockOffsets(GLint uniformBlockIndex, const char *names[] ) const;

    private:
        void _initialize();
    };

}

////////////////////////////////////////////////////////////////////////////////

inline bool CSCI441::ShaderProgram::sDEBUG = true;

inline void CSCI441::ShaderProgram::enableDebugMessages() {
    sDEBUG = true;
}
inline void CSCI441::ShaderProgram::disableDebugMessages() {
    sDEBUG = false;
}

inline CSCI441::ShaderProgram::ShaderProgram( const char *vertexShaderFilename, const char *fragmentShaderFilename ) {
    _initialize();
    mRegisterShaderProgram(vertexShaderFilename, "", "", "", fragmentShaderFilename, false);
}

inline CSCI441::ShaderProgram::ShaderProgram( const char *vertexShaderFilename, const char *fragmentShaderFilename, const bool isSeparable ) {
    _initialize();
    mRegisterShaderProgram(vertexShaderFilename, "", "", "", fragmentShaderFilename, isSeparable);
}

inline CSCI441::ShaderProgram::ShaderProgram( const char *vertexShaderFilename, const char *tesselationControlShaderFilename, const char *tesselationEvaluationShaderFilename, const char *geometryShaderFilename, const char *fragmentShaderFilename ) {
    _initialize();
    mRegisterShaderProgram(vertexShaderFilename, tesselationControlShaderFilename, tesselationEvaluationShaderFilename,
                           geometryShaderFilename, fragmentShaderFilename, false);
}

inline CSCI441::ShaderProgram::ShaderProgram( const char *vertexShaderFilename, const char *tesselationControlShaderFilename, const char *tesselationEvaluationShaderFilename, const char *geometryShaderFilename, const char *fragmentShaderFilename, bool isSeparable  ) {
    _initialize();
    mRegisterShaderProgram(vertexShaderFilename, tesselationControlShaderFilename, tesselationEvaluationShaderFilename,
                           geometryShaderFilename, fragmentShaderFilename, isSeparable);
}

inline CSCI441::ShaderProgram::ShaderProgram( const char *vertexShaderFilename, const char *tesselationControlShaderFilename, const char *tesselationEvaluationShaderFilename, const char *fragmentShaderFilename ) {
    _initialize();
    mRegisterShaderProgram(vertexShaderFilename, tesselationControlShaderFilename, tesselationEvaluationShaderFilename,
                           "", fragmentShaderFilename, false);
}

inline CSCI441::ShaderProgram::ShaderProgram( const char *vertexShaderFilename, const char *tesselationControlShaderFilename, const char *tesselationEvaluationShaderFilename, const char *fragmentShaderFilename, bool isSeparable  ) {
    _initialize();
    mRegisterShaderProgram(vertexShaderFilename, tesselationControlShaderFilename, tesselationEvaluationShaderFilename,
                           "", fragmentShaderFilename, isSeparable);
}

inline CSCI441::ShaderProgram::ShaderProgram( const char *vertexShaderFilename, const char *geometryShaderFilename, const char *fragmentShaderFilename ) {
    _initialize();
    mRegisterShaderProgram(vertexShaderFilename, "", "", geometryShaderFilename, fragmentShaderFilename, false);
}

inline CSCI441::ShaderProgram::ShaderProgram( const char *vertexShaderFilename, const char *geometryShaderFilename, const char *fragmentShaderFilename, bool isSeparable  ) {
    _initialize();
    mRegisterShaderProgram(vertexShaderFilename, "", "", geometryShaderFilename, fragmentShaderFilename, isSeparable);
}

inline CSCI441::ShaderProgram::ShaderProgram( const char **shaderFilenames,
                                       const bool vertexPresent, const bool tessellationPresent, const bool geometryPresent, const bool fragmentPresent,
                                       const bool isSeparable ) {
    _initialize();
    if( vertexPresent && !tessellationPresent && !geometryPresent && !fragmentPresent ) {
        if( !isSeparable ) {
            fprintf(stderr, "[ERROR]: Fragment Shader not present.  Program must be separable.\n");
        } else {
            mRegisterShaderProgram(shaderFilenames[0], "", "", "", "", isSeparable);
        }
    } else if( vertexPresent && tessellationPresent && !geometryPresent && !fragmentPresent ) {
        if( !isSeparable ) {
            fprintf(stderr, "[ERROR]: Fragment Shader not present.  Program must be separable.\n");
        } else {
            mRegisterShaderProgram(shaderFilenames[0], shaderFilenames[1], shaderFilenames[2], "", "", isSeparable);
        }
    } else if( vertexPresent && tessellationPresent && geometryPresent && !fragmentPresent ) {
        if( !isSeparable ) {
            fprintf(stderr, "[ERROR]: Fragment Shader not present.  Program must be separable.\n");
        } else {
            mRegisterShaderProgram(shaderFilenames[0], shaderFilenames[1], shaderFilenames[2], shaderFilenames[3], "",
                                   isSeparable);
        }
    } else if( vertexPresent && tessellationPresent && geometryPresent && fragmentPresent ) {
        mRegisterShaderProgram(shaderFilenames[0], shaderFilenames[1], shaderFilenames[2], shaderFilenames[3],
                               shaderFilenames[4], isSeparable);
    } else if( vertexPresent && tessellationPresent && !geometryPresent && fragmentPresent ) {
        mRegisterShaderProgram(shaderFilenames[0], shaderFilenames[1], shaderFilenames[2], "", shaderFilenames[3],
                               isSeparable);
    } else if( vertexPresent && !tessellationPresent && geometryPresent && !fragmentPresent ) {
        if( !isSeparable ) {
            fprintf(stderr, "[ERROR]: Fragment Shader not present.  Program must be separable.\n");
        } else {
            mRegisterShaderProgram(shaderFilenames[0], "", "", shaderFilenames[1], "", isSeparable);
        }
    } else if( vertexPresent && !tessellationPresent && geometryPresent && fragmentPresent ) {
        mRegisterShaderProgram(shaderFilenames[0], "", "", shaderFilenames[1], shaderFilenames[2], isSeparable);
    } else if( vertexPresent && !tessellationPresent && !geometryPresent && fragmentPresent ) {
        mRegisterShaderProgram(shaderFilenames[0], "", "", "", shaderFilenames[1], isSeparable);
    } else if( !vertexPresent && tessellationPresent && !geometryPresent && !fragmentPresent ) {
        if( !isSeparable ) {
            fprintf(stderr, "[ERROR]: Vertex & Fragment Shaders not present.  Program must be separable.\n");
        } else {
            mRegisterShaderProgram("", shaderFilenames[0], shaderFilenames[1], "", "", isSeparable);
        }
    } else if( !vertexPresent && tessellationPresent && geometryPresent && !fragmentPresent ) {
        if( !isSeparable ) {
            fprintf(stderr, "[ERROR]: Vertex & Fragment Shaders not present.  Program must be separable.\n");
        } else {
            mRegisterShaderProgram("", shaderFilenames[0], shaderFilenames[1], shaderFilenames[2], "", isSeparable);
        }
    } else if( !vertexPresent && tessellationPresent && geometryPresent && fragmentPresent ) {
        if( !isSeparable ) {
            fprintf(stderr, "[ERROR]: Vertex Shader not present.  Program must be separable.\n");
        } else {
            mRegisterShaderProgram("", shaderFilenames[0], shaderFilenames[1], shaderFilenames[2], shaderFilenames[3],
                                   isSeparable);
        }
    } else if( !vertexPresent && tessellationPresent && !geometryPresent && fragmentPresent ) {
        if( !isSeparable ) {
            fprintf(stderr, "[ERROR]: Vertex Shader not present.  Program must be separable.\n");
        } else {
            mRegisterShaderProgram("", shaderFilenames[0], shaderFilenames[1], "", shaderFilenames[2], isSeparable);
        }
    } else if( !vertexPresent && !tessellationPresent && geometryPresent && !fragmentPresent ) {
        if( !isSeparable ) {
            fprintf(stderr, "[ERROR]: Vertex & Fragment Shaders not present.  Program must be separable.\n");
        } else {
            mRegisterShaderProgram("", "", "", shaderFilenames[0], "", isSeparable);
        }
    } else if( !vertexPresent && !tessellationPresent && geometryPresent && fragmentPresent ) {
        if( !isSeparable ) {
            fprintf(stderr, "[ERROR]: Vertex Shader not present.  Program must be separable.\n");
        } else {
            mRegisterShaderProgram("", "", "", shaderFilenames[0], shaderFilenames[1], isSeparable);
        }
    } else if( !vertexPresent && !tessellationPresent && !geometryPresent && fragmentPresent ) {
        if( !isSeparable ) {
            fprintf(stderr, "[ERROR]: Vertex Shader not present.  Program must be separable.\n");
        } else {
            mRegisterShaderProgram("", "", "", "", shaderFilenames[0], isSeparable);
        }
    } else if( !vertexPresent && !tessellationPresent && !geometryPresent && !fragmentPresent ) {
        fprintf(stderr, "[ERROR]: At least one shader must be present.\n");
    } else {
        fprintf(stderr, "[ERROR]: Unknown state.\n");
    }
}

inline bool CSCI441::ShaderProgram::mRegisterShaderProgram(const char *vertexShaderFilename, const char *tesselationControlShaderFilename, const char *tesselationEvaluationShaderFilename, const char *geometryShaderFilename, const char *fragmentShaderFilename, const bool isSeparable ) {
    GLint major, minor;
    glGetIntegerv(GL_MAJOR_VERSION, &major);
    glGetIntegerv(GL_MINOR_VERSION, &minor);

    if( sDEBUG ) printf( "\n[INFO]: /--------------------------------------------------------\\\n");

    /* compile each one of our shaders */
    if( strcmp( vertexShaderFilename, "" ) != 0 ) {
        if( sDEBUG ) printf( "[INFO]: | Vertex Shader: %39s |\n", vertexShaderFilename );
        mVertexShaderHandle = CSCI441_INTERNAL::ShaderUtils::compileShader(vertexShaderFilename, GL_VERTEX_SHADER );
    } else {
        mVertexShaderHandle = 0;
    }

    if( strcmp( tesselationControlShaderFilename, "" ) != 0 ) {
        if( sDEBUG ) printf( "[INFO]: | Tess Control Shader: %33s |\n", tesselationControlShaderFilename );
        if( major < 4 ) {
            printf( "[ERROR]:|   TESSELATION SHADER NOT SUPPORTED!!  UPGRADE TO v4.0+ |\n" );
            mTesselationControlShaderHandle = 0;
        } else {
            mTesselationControlShaderHandle = CSCI441_INTERNAL::ShaderUtils::compileShader(tesselationControlShaderFilename, GL_TESS_CONTROL_SHADER );
        }
    } else {
        mTesselationControlShaderHandle = 0;
    }

    if( strcmp( tesselationEvaluationShaderFilename, "" ) != 0 ) {
        if( sDEBUG ) printf( "[INFO]: | Tess Evaluation Shader: %30s |\n", tesselationEvaluationShaderFilename );
        if( major < 4 ) {
            printf( "[ERROR]:|   TESSELATION SHADER NOT SUPPORTED!!  UPGRADE TO v4.0+ |\n" );
            mTesselationEvaluationShaderHandle = 0;
        } else {
            mTesselationEvaluationShaderHandle = CSCI441_INTERNAL::ShaderUtils::compileShader(tesselationEvaluationShaderFilename, GL_TESS_EVALUATION_SHADER );
        }
    } else {
        mTesselationEvaluationShaderHandle = 0;
    }

    if( strcmp( geometryShaderFilename, "" ) != 0 ) {
        if( sDEBUG ) printf( "[INFO]: | Geometry Shader: %37s |\n", geometryShaderFilename );
        if( major < 3 || (major == 3 && minor < 2) ) {
            printf( "[ERROR]:|   GEOMETRY SHADER NOT SUPPORTED!!!    UPGRADE TO v3.2+ |\n" );
            mGeometryShaderHandle = 0;
        } else {
            mGeometryShaderHandle = CSCI441_INTERNAL::ShaderUtils::compileShader(geometryShaderFilename, GL_GEOMETRY_SHADER );
        }
    } else {
        mGeometryShaderHandle = 0;
    }

    if( strcmp( fragmentShaderFilename, "" ) != 0 ) {
        if( sDEBUG ) printf( "[INFO]: | Fragment Shader: %37s |\n", fragmentShaderFilename );
        mFragmentShaderHandle = CSCI441_INTERNAL::ShaderUtils::compileShader(fragmentShaderFilename, GL_FRAGMENT_SHADER );
    } else {
        mFragmentShaderHandle = 0;
    }
    /* get a handle to a shader program */
    mShaderProgramHandle = glCreateProgram();

    /* if program is separable, make it so */
    if( isSeparable ) {
        glProgramParameteri(mShaderProgramHandle, GL_PROGRAM_SEPARABLE, GL_TRUE );
    }

    /* attach the vertex and fragment shaders to the shader program */
    if(mVertexShaderHandle != 0 ) {
        glAttachShader(mShaderProgramHandle, mVertexShaderHandle );
    }
    if(mTesselationControlShaderHandle != 0 ) {
        glAttachShader(mShaderProgramHandle, mTesselationControlShaderHandle );
    }
    if(mTesselationEvaluationShaderHandle != 0 ) {
        glAttachShader(mShaderProgramHandle, mTesselationEvaluationShaderHandle );
    }
    if(mGeometryShaderHandle != 0 ) {
        glAttachShader(mShaderProgramHandle, mGeometryShaderHandle );
    }
    if(mFragmentShaderHandle != 0 ) {
        glAttachShader(mShaderProgramHandle, mFragmentShaderHandle );
    }

    /* link all the programs together on the GPU */
    glLinkProgram(mShaderProgramHandle );

    if( sDEBUG ) printf( "[INFO]: | Shader Program: %41s", "|\n" );

    /* check the program log */
    CSCI441_INTERNAL::ShaderUtils::printProgramLog(mShaderProgramHandle );

    /* detach & delete the vertex and fragment shaders to the shader program */
    if(mVertexShaderHandle != 0 ) {
        glDetachShader(mShaderProgramHandle, mVertexShaderHandle );
        glDeleteShader(mVertexShaderHandle );
    }
    if(mTesselationControlShaderHandle != 0 ) {
        glDetachShader(mShaderProgramHandle, mTesselationControlShaderHandle );
        glDeleteShader(mTesselationControlShaderHandle );
    }
    if(mTesselationEvaluationShaderHandle != 0 ) {
        glDetachShader(mShaderProgramHandle, mTesselationEvaluationShaderHandle );
        glDeleteShader(mTesselationEvaluationShaderHandle );
    }
    if(mGeometryShaderHandle != 0 ) {
        glDetachShader(mShaderProgramHandle, mGeometryShaderHandle );
        glDeleteShader(mGeometryShaderHandle );
    }
    if(mFragmentShaderHandle != 0 ) {
        glDetachShader(mShaderProgramHandle, mFragmentShaderHandle );
        glDeleteShader(mFragmentShaderHandle );
    }

    // map uniforms
    mpUniformLocationsMap = new std::map<std::string, GLint>();
    GLint numUniforms;
    glGetProgramiv(mShaderProgramHandle, GL_ACTIVE_UNIFORMS, &numUniforms);
    if( numUniforms > 0 ) {
        for(GLuint i = 0; i < numUniforms; i++) {
            char name[64];
            int max_length = 64;
            int actual_length = 0;
            int size = 0;
            GLenum type;
            glGetActiveUniform(mShaderProgramHandle, i, max_length, &actual_length, &size, &type, name );
            GLint location = -1;
            if(size > 1) {
                for(int j = 0; j < size; j++) {
                    char long_name[64];
                    sprintf(long_name, "%s[%i]", name, j);
                    location = glGetUniformLocation(mShaderProgramHandle, long_name);
                }
            } else {
                location = glGetUniformLocation(mShaderProgramHandle, name);
            }
            mpUniformLocationsMap->emplace(name, location );
        }
    }

    // map attributes
    mpAttributeLocationsMap = new std::map<std::string, GLint>();
    GLint numAttributes;
    glGetProgramiv(mShaderProgramHandle, GL_ACTIVE_ATTRIBUTES, &numAttributes );
    if( numAttributes > 0 ) {
        for(GLuint i = 0; i < numAttributes; i++) {
            char name[64];
            int max_length = 64;
            int actual_length = 0;
            int size = 0;
            GLenum type;
            glGetActiveAttrib(mShaderProgramHandle, i, max_length, &actual_length, &size, &type, name );
            GLint location = -1;
            if( size > 1 ) {
                for( int j = 0; j < size; j++ ) {
                    char long_name[64];
                    sprintf( long_name, "%s[%i]", name, j );
                    location = glGetAttribLocation(mShaderProgramHandle, long_name );
                }
            } else {
                location = glGetAttribLocation(mShaderProgramHandle, name );
            }
            mpAttributeLocationsMap->emplace(name, location );
        }
    }

    GLint separable = GL_FALSE;
    glGetProgramiv(mShaderProgramHandle, GL_PROGRAM_SEPARABLE, &separable );

    if( sDEBUG ) printf( "[INFO]: | Program Separable: %35s |\n", (separable ? "Yes" : "No"));

    GLint linkStatus;
    glGetProgramiv(mShaderProgramHandle, GL_LINK_STATUS, &linkStatus );

    /* print shader info for uniforms & attributes */
    if(linkStatus == 1) {
        CSCI441_INTERNAL::ShaderUtils::printShaderProgramInfo(mShaderProgramHandle, mVertexShaderHandle != 0,
                                                              mTesselationControlShaderHandle != 0,
                                                              mTesselationEvaluationShaderHandle != 0,
                                                              mGeometryShaderHandle != 0, mFragmentShaderHandle != 0,
                                                              false, true);
    }
    /* return handle */
    return mShaderProgramHandle != 0;
}

inline GLint CSCI441::ShaderProgram::getUniformLocation( const char *uniformName ) const {
    GLint uniformLoc = glGetUniformLocation(mShaderProgramHandle, uniformName );
    if( uniformLoc == -1 )
        fprintf(stderr, "[ERROR]: Could not find uniform \"%s\" for Shader Program %u\n", uniformName, mShaderProgramHandle );
    return uniformLoc;
}

inline GLint CSCI441::ShaderProgram::getUniformBlockIndex( const char *uniformBlockName ) const {
    GLint uniformBlockLoc = glGetUniformBlockIndex(mShaderProgramHandle, uniformBlockName );
    if( uniformBlockLoc == -1 )
        fprintf(stderr, "[ERROR]: Could not find uniform block \"%s\" for Shader Program %u\n", uniformBlockName, mShaderProgramHandle );
    return uniformBlockLoc;
}

inline GLint CSCI441::ShaderProgram::getUniformBlockSize( const char *uniformBlockName ) const {
    GLint blockSize;
    glGetActiveUniformBlockiv(mShaderProgramHandle, getUniformBlockIndex(uniformBlockName), GL_UNIFORM_BLOCK_DATA_SIZE, &blockSize );
    return blockSize;
}

inline GLubyte* CSCI441::ShaderProgram::getUniformBlockBuffer( const char *uniformBlockName ) const {
    GLubyte *blockBuffer;

    GLint blockSize = getUniformBlockSize( uniformBlockName );

    blockBuffer = (GLubyte*)malloc(blockSize);

    return blockBuffer;
}

inline GLint* CSCI441::ShaderProgram::getUniformBlockOffsets( const char *uniformBlockName ) const {
    return mGetUniformBlockOffsets(getUniformBlockIndex(uniformBlockName));
}

inline GLint* CSCI441::ShaderProgram::getUniformBlockOffsets( const char *uniformBlockName, const char *names[] ) const {
    return mGetUniformBlockOffsets(getUniformBlockIndex(uniformBlockName), names);
}

inline GLint* CSCI441::ShaderProgram::mGetUniformBlockOffsets(GLint uniformBlockIndex ) const {
    GLint numUniforms;
    glGetActiveUniformBlockiv(mShaderProgramHandle, uniformBlockIndex, GL_UNIFORM_BLOCK_ACTIVE_UNIFORMS, &numUniforms );

    auto indices = (GLuint*)malloc(numUniforms*sizeof(GLuint));
    glGetActiveUniformBlockiv(mShaderProgramHandle, uniformBlockIndex, GL_UNIFORM_BLOCK_ACTIVE_UNIFORM_INDICES, (GLint*)indices);

    auto offsets = (GLint*)malloc(numUniforms*sizeof(GLint));
    glGetActiveUniformsiv(mShaderProgramHandle, numUniforms, indices, GL_UNIFORM_OFFSET, offsets );
    return offsets;
}

inline GLint* CSCI441::ShaderProgram::mGetUniformBlockOffsets(GLint uniformBlockIndex, const char *names[] ) const {
    GLint numUniforms;
    glGetActiveUniformBlockiv(mShaderProgramHandle, uniformBlockIndex, GL_UNIFORM_BLOCK_ACTIVE_UNIFORMS, &numUniforms );

    auto indices = (GLuint*)malloc(numUniforms*sizeof(GLuint));
    glGetUniformIndices(mShaderProgramHandle, numUniforms, names, indices );

    auto offsets = (GLint*)malloc(numUniforms*sizeof(GLint));
    glGetActiveUniformsiv(mShaderProgramHandle, numUniforms, indices, GL_UNIFORM_OFFSET, offsets );
    return offsets;
}

inline void CSCI441::ShaderProgram::setUniformBlockBinding( const char *uniformBlockName, GLuint binding ) const {
    glUniformBlockBinding(mShaderProgramHandle, getUniformBlockIndex(uniformBlockName), binding );
}

inline GLint CSCI441::ShaderProgram::getAttributeLocation( const char *attributeName ) const {
    auto attribIter = mpAttributeLocationsMap->find(attributeName);
    if(attribIter == mpAttributeLocationsMap->end() ) {
        fprintf(stderr, "[ERROR]: Could not find attribute \"%s\" for Shader Program %u\n", attributeName, mShaderProgramHandle );
        return -1;
    }
    return attribIter->second;
}

inline GLuint CSCI441::ShaderProgram::getSubroutineIndex( GLenum shaderStage, const char *subroutineName ) const {
    GLuint subroutineIndex = glGetSubroutineIndex(mShaderProgramHandle, shaderStage, subroutineName );
    if( subroutineIndex == GL_INVALID_INDEX )
        fprintf(stderr, "[ERROR]: Could not find subroutine \"%s\" in %s for Shader Program %u\n", subroutineName, CSCI441_INTERNAL::ShaderUtils::GL_shader_type_to_string(shaderStage), mShaderProgramHandle );
    return subroutineIndex;
}

// images are opaque types that are not considered program resources
inline GLint CSCI441::ShaderProgram::getImageBinding(const char* imageName) const {
    GLuint imageLoc = getUniformLocation(imageName);

    if(imageLoc == -1) {
        fprintf(stderr, "[ERROR]: Could not find image \"%s\" for Shader Program %u\n", imageName, mShaderProgramHandle);
        return -1;
    }

    GLint bindingPoint;
    glGetUniformiv(mShaderProgramHandle, imageLoc, &bindingPoint);

    return bindingPoint;
}

inline GLint CSCI441::ShaderProgram::getShaderStorageBlockBinding(const char* ssboName) const {
    GLuint ssboIndex = glGetProgramResourceIndex(mShaderProgramHandle, GL_SHADER_STORAGE_BLOCK, ssboName);

    if(ssboIndex == -1) {
        fprintf(stderr, "[ERROR]: Could not find shader storage block \"%s\" for Shader Program %u\n", ssboName, mShaderProgramHandle);
        return -1;
    }

    const int NUM_PROPS = 1;
    GLenum props[NUM_PROPS] = {GL_BUFFER_BINDING};
    GLint results[NUM_PROPS];
    glGetProgramResourceiv(mShaderProgramHandle, GL_SHADER_STORAGE_BLOCK, ssboIndex, NUM_PROPS, props, NUM_PROPS, nullptr, results);

    return results[0];
}

inline GLint CSCI441::ShaderProgram::getAtomicCounterBufferBinding(const char* atomicName) const {
    GLuint uniformIndex = glGetProgramResourceIndex(mShaderProgramHandle, GL_UNIFORM, atomicName);

    if(uniformIndex == -1) {
        fprintf(stderr, "[ERROR]: Could not find atomic counter \"%s\" for Shader Program %u\n", atomicName, mShaderProgramHandle);
        return -1;
    }

    GLenum props = GL_ATOMIC_COUNTER_BUFFER_INDEX;
    GLint atomicIndex, binding;
    glGetProgramResourceiv(mShaderProgramHandle, GL_UNIFORM, uniformIndex, 1, &props, 1, nullptr, &atomicIndex);
    glGetActiveAtomicCounterBufferiv(mShaderProgramHandle, atomicIndex, GL_ATOMIC_COUNTER_BUFFER_BINDING, &binding);

    return binding;
}

inline GLint CSCI441::ShaderProgram::getAtomicCounterBufferOffset(const char* atomicName) const {
    GLuint uniformIndex = glGetProgramResourceIndex(mShaderProgramHandle, GL_UNIFORM, atomicName);

    if(uniformIndex == -1) {
        fprintf(stderr, "[ERROR]: Could not find atomic counter \"%s\" for Shader Program %u\n", atomicName, mShaderProgramHandle);
        return -1;
    }

    GLint offset;
    glGetActiveUniformsiv(mShaderProgramHandle, 1, &uniformIndex, GL_UNIFORM_OFFSET, &offset);
    return offset;
}

inline GLint CSCI441::ShaderProgram::getAtomicCounterBufferSize(const char* atomicName) const {
    GLuint uniformIndex = glGetProgramResourceIndex(mShaderProgramHandle, GL_UNIFORM, atomicName);

    if(uniformIndex == -1) {
        fprintf(stderr, "[ERROR]: Could not find atomic counter \"%s\" for Shader Program %u\n", atomicName, mShaderProgramHandle);
        return -1;
    }

    GLenum props = GL_ATOMIC_COUNTER_BUFFER_INDEX;
    GLint atomicIndex, bufferSize;
    glGetProgramResourceiv(mShaderProgramHandle, GL_UNIFORM, uniformIndex, 1, &props, 1, nullptr, &atomicIndex);
    glGetActiveAtomicCounterBufferiv(mShaderProgramHandle, atomicIndex, GL_ATOMIC_COUNTER_BUFFER_DATA_SIZE, &bufferSize);

    return bufferSize;
}

inline GLuint CSCI441::ShaderProgram::getNumUniforms() const {
    int numUniform = 0;
    glGetProgramiv(mShaderProgramHandle, GL_ACTIVE_UNIFORMS, &numUniform );
    return numUniform;
}

inline GLuint CSCI441::ShaderProgram::getNumUniformBlocks() const {
    int numUniformBlocks = 0;
    glGetProgramiv(mShaderProgramHandle, GL_ACTIVE_UNIFORM_BLOCKS, &numUniformBlocks );
    return numUniformBlocks;
}

inline GLuint CSCI441::ShaderProgram::getNumAttributes() const {
    int numAttr = 0;
    glGetProgramiv(mShaderProgramHandle, GL_ACTIVE_ATTRIBUTES, &numAttr );
    return numAttr;
}

inline GLuint CSCI441::ShaderProgram::getShaderProgramHandle() const {
    return mShaderProgramHandle;
}

inline void CSCI441::ShaderProgram::useProgram() const {
    glUseProgram(mShaderProgramHandle );
}

inline void CSCI441::ShaderProgram::setProgramUniform( const char *uniformName, GLfloat v0 ) const  {
    auto uniformIter = mpUniformLocationsMap->find(uniformName);
    if(uniformIter != mpUniformLocationsMap->end()) {
        glProgramUniform1f(mShaderProgramHandle, uniformIter->second, v0 );
    } else {
        fprintf(stderr, "[ERROR]: Could not find uniform \"%s\" for Shader Program %u\n", uniformName, mShaderProgramHandle);
    }
}

inline void CSCI441::ShaderProgram::setProgramUniform( const char *uniformName, GLfloat v0, GLfloat v1 ) const {
    auto uniformIter = mpUniformLocationsMap->find(uniformName);
    if(uniformIter != mpUniformLocationsMap->end()) {
        glProgramUniform2f(mShaderProgramHandle, uniformIter->second, v0, v1 );
    } else {
        fprintf(stderr, "[ERROR]: Could not find uniform \"%s\" for Shader Program %u\n", uniformName, mShaderProgramHandle);
    }
}

inline void CSCI441::ShaderProgram::setProgramUniform( const char *uniformName, glm::vec2 value ) const {
    setProgramUniform( uniformName, 2, 1, &value[0] );
}

inline void CSCI441::ShaderProgram::setProgramUniform( const char *uniformName, GLfloat v0, GLfloat v1, GLfloat v2 ) const {
    auto uniformIter = mpUniformLocationsMap->find(uniformName);
    if(uniformIter != mpUniformLocationsMap->end()) {
        glProgramUniform3f(mShaderProgramHandle, uniformIter->second, v0, v1, v2 );
    } else {
        fprintf(stderr, "[ERROR]: Could not find uniform \"%s\" for Shader Program %u\n", uniformName, mShaderProgramHandle);
    }
}

inline void CSCI441::ShaderProgram::setProgramUniform( const char *uniformName, glm::vec3 value ) const {
    setProgramUniform( uniformName, 3, 1, &value[0] );
}

inline void CSCI441::ShaderProgram::setProgramUniform( const char *uniformName, GLfloat v0, GLfloat v1, GLfloat v2, GLfloat v3 ) const {
    auto uniformIter = mpUniformLocationsMap->find(uniformName);
    if(uniformIter != mpUniformLocationsMap->end()) {
        glProgramUniform4f(mShaderProgramHandle, uniformIter->second, v0, v1, v2, v3 );
    } else {
        fprintf(stderr, "[ERROR]: Could not find uniform \"%s\" for Shader Program %u\n", uniformName, mShaderProgramHandle);
    }
}

inline void CSCI441::ShaderProgram::setProgramUniform( const char *uniformName, glm::vec4 value ) const {
    setProgramUniform( uniformName, 4, 1, &value[0] );
}

inline void CSCI441::ShaderProgram::setProgramUniform(const char* uniformName, GLuint dim, GLsizei count, const GLfloat *value) const {
    auto uniformIter = mpUniformLocationsMap->find(uniformName);
    if(uniformIter != mpUniformLocationsMap->end()) {
        switch(dim) {
            case 1:
                glProgramUniform1fv(mShaderProgramHandle, uniformIter->second, count, value );
                break;
            case 2:
                glProgramUniform2fv(mShaderProgramHandle, uniformIter->second, count, value );
                break;
            case 3:
                glProgramUniform3fv(mShaderProgramHandle, uniformIter->second, count, value );
                break;
            case 4:
                glProgramUniform4fv(mShaderProgramHandle, uniformIter->second, count, value );
                break;
            default:
                fprintf(stderr, "[ERROR]: invalid dimension %u for uniform %s in Shader Program %u.  Dimension must be [1,4]\n", dim, uniformName, mShaderProgramHandle);
                break;
        }
    } else {
        fprintf(stderr, "[ERROR]: Could not find uniform \"%s\" for Shader Program %u\n", uniformName, mShaderProgramHandle);
    }
}

inline void CSCI441::ShaderProgram::setProgramUniform( const char *uniformName, GLint v0 ) const {
    auto uniformIter = mpUniformLocationsMap->find(uniformName);
    if(uniformIter != mpUniformLocationsMap->end()) {
        glProgramUniform1i(mShaderProgramHandle, uniformIter->second, v0 );
    } else {
        fprintf(stderr, "[ERROR]: Could not find uniform \"%s\" for Shader Program %u\n", uniformName, mShaderProgramHandle);
    }
}

inline void CSCI441::ShaderProgram::setProgramUniform( const char *uniformName, GLint v0, GLint v1 ) const {
    auto uniformIter = mpUniformLocationsMap->find(uniformName);
    if(uniformIter != mpUniformLocationsMap->end()) {
        glProgramUniform2i(mShaderProgramHandle, uniformIter->second, v0, v1 );
    } else {
        fprintf(stderr, "[ERROR]: Could not find uniform \"%s\" for Shader Program %u\n", uniformName, mShaderProgramHandle);
    }
}

inline void CSCI441::ShaderProgram::setProgramUniform(const char* uniformName, glm::ivec2 value) const {
    auto uniformIter = mpUniformLocationsMap->find(uniformName);
    if(uniformIter != mpUniformLocationsMap->end()) {
        glProgramUniform2iv(mShaderProgramHandle, uniformIter->second, 1, &value[0] );
    } else {
        fprintf(stderr, "[ERROR]: Could not find uniform \"%s\" for Shader Program %u\n", uniformName, mShaderProgramHandle);
    }
}

inline void CSCI441::ShaderProgram::setProgramUniform( const char *uniformName, GLint v0, GLint v1, GLint v2 ) const {
    auto uniformIter = mpUniformLocationsMap->find(uniformName);
    if(uniformIter != mpUniformLocationsMap->end()) {
        glProgramUniform3i(mShaderProgramHandle, uniformIter->second, v0, v1, v2 );
    } else {
        fprintf(stderr, "[ERROR]: Could not find uniform \"%s\" for Shader Program %u\n", uniformName, mShaderProgramHandle);
    }
}

inline void CSCI441::ShaderProgram::setProgramUniform(const char* uniformName, glm::ivec3 value) const {
    auto uniformIter = mpUniformLocationsMap->find(uniformName);
    if(uniformIter != mpUniformLocationsMap->end()) {
        glProgramUniform3iv(mShaderProgramHandle, uniformIter->second, 1, &value[0] );
    } else {
        fprintf(stderr, "[ERROR]: Could not find uniform \"%s\" for Shader Program %u\n", uniformName, mShaderProgramHandle);
    }
}

inline void CSCI441::ShaderProgram::setProgramUniform( const char *uniformName, GLint v0, GLint v1, GLint v2, GLint v3 ) const {
    auto uniformIter = mpUniformLocationsMap->find(uniformName);
    if(uniformIter != mpUniformLocationsMap->end()) {
        glProgramUniform4i(mShaderProgramHandle, uniformIter->second, v0, v1, v2, v3 );
    } else {
        fprintf(stderr, "[ERROR]: Could not find uniform \"%s\" for Shader Program %u\n", uniformName, mShaderProgramHandle);
    }
}

inline void CSCI441::ShaderProgram::setProgramUniform(const char* uniformName, glm::ivec4 value) const {
    auto uniformIter = mpUniformLocationsMap->find(uniformName);
    if(uniformIter != mpUniformLocationsMap->end()) {
        glProgramUniform4iv(mShaderProgramHandle, uniformIter->second, 1, &value[0] );
    } else {
        fprintf(stderr, "[ERROR]: Could not find uniform \"%s\" for Shader Program %u\n", uniformName, mShaderProgramHandle);
    }
}

inline void CSCI441::ShaderProgram::setProgramUniform(const char* uniformName, GLuint dim, GLsizei count, const GLint *value) const {
    auto uniformIter = mpUniformLocationsMap->find(uniformName);
    if(uniformIter != mpUniformLocationsMap->end()) {
        switch(dim) {
            case 1:
                glProgramUniform1iv(mShaderProgramHandle, uniformIter->second, count, value );
                break;
            case 2:
                glProgramUniform2iv(mShaderProgramHandle, uniformIter->second, count, value );
                break;
            case 3:
                glProgramUniform3iv(mShaderProgramHandle, uniformIter->second, count, value );
                break;
            case 4:
                glProgramUniform4iv(mShaderProgramHandle, uniformIter->second, count, value );
                break;
            default:
                fprintf(stderr, "[ERROR]: invalid dimension %u for uniform %s in Shader Program %u.  Dimension must be [1,4]\n", dim, uniformName, mShaderProgramHandle);
                break;
        }
    } else {
        fprintf(stderr, "[ERROR]: Could not find uniform \"%s\" for Shader Program %u\n", uniformName, mShaderProgramHandle);
    }
}

inline void CSCI441::ShaderProgram::setProgramUniform( const char *uniformName, GLuint v0 ) const {
    auto uniformIter = mpUniformLocationsMap->find(uniformName);
    if(uniformIter != mpUniformLocationsMap->end()) {
        glProgramUniform1ui(mShaderProgramHandle, uniformIter->second, v0 );
    } else {
        fprintf(stderr, "[ERROR]: Could not find uniform \"%s\" for Shader Program %u\n", uniformName, mShaderProgramHandle);
    }
}

inline void CSCI441::ShaderProgram::setProgramUniform( const char *uniformName, GLuint v0, GLuint v1 ) const {
    auto uniformIter = mpUniformLocationsMap->find(uniformName);
    if(uniformIter != mpUniformLocationsMap->end()) {
        glProgramUniform2ui(mShaderProgramHandle, uniformIter->second, v0, v1 );
    } else {
        fprintf(stderr, "[ERROR]: Could not find uniform \"%s\" for Shader Program %u\n", uniformName, mShaderProgramHandle);
    }
}

inline void CSCI441::ShaderProgram::setProgramUniform(const char* uniformName, glm::uvec2 value) const {
    auto uniformIter = mpUniformLocationsMap->find(uniformName);
    if(uniformIter != mpUniformLocationsMap->end()) {
        glProgramUniform2uiv(mShaderProgramHandle, uniformIter->second, 1, &value[0] );
    } else {
        fprintf(stderr, "[ERROR]: Could not find uniform \"%s\" for Shader Program %u\n", uniformName, mShaderProgramHandle);
    }
}

inline void CSCI441::ShaderProgram::setProgramUniform( const char *uniformName, GLuint v0, GLuint v1, GLuint v2 ) const {
    auto uniformIter = mpUniformLocationsMap->find(uniformName);
    if(uniformIter != mpUniformLocationsMap->end()) {
        glProgramUniform3ui(mShaderProgramHandle, uniformIter->second, v0, v1, v2 );
    } else {
        fprintf(stderr, "[ERROR]: Could not find uniform \"%s\" for Shader Program %u\n", uniformName, mShaderProgramHandle);
    }
}

inline void CSCI441::ShaderProgram::setProgramUniform(const char* uniformName, glm::uvec3 value) const {
    auto uniformIter = mpUniformLocationsMap->find(uniformName);
    if(uniformIter != mpUniformLocationsMap->end()) {
        glProgramUniform3uiv(mShaderProgramHandle, uniformIter->second, 1, &value[0] );
    } else {
        fprintf(stderr, "[ERROR]: Could not find uniform \"%s\" for Shader Program %u\n", uniformName, mShaderProgramHandle);
    }
}

inline void CSCI441::ShaderProgram::setProgramUniform( const char *uniformName, GLuint v0, GLuint v1, GLuint v2, GLuint v3 ) const {
    auto uniformIter = mpUniformLocationsMap->find(uniformName);
    if(uniformIter != mpUniformLocationsMap->end()) {
        glProgramUniform4ui(mShaderProgramHandle, uniformIter->second, v0, v1, v2, v3 );
    } else {
        fprintf(stderr, "[ERROR]: Could not find uniform \"%s\" for Shader Program %u\n", uniformName, mShaderProgramHandle);
    }
}

inline void CSCI441::ShaderProgram::setProgramUniform(const char* uniformName, glm::uvec4 value) const {
    auto uniformIter = mpUniformLocationsMap->find(uniformName);
    if(uniformIter != mpUniformLocationsMap->end()) {
        glProgramUniform4uiv(mShaderProgramHandle, uniformIter->second, 1, &value[0] );
    } else {
        fprintf(stderr, "[ERROR]: Could not find uniform \"%s\" for Shader Program %u\n", uniformName, mShaderProgramHandle);
    }
}

inline void CSCI441::ShaderProgram::setProgramUniform(const char* uniformName, GLuint dim, GLsizei count, const GLuint *value) const {
    auto uniformIter = mpUniformLocationsMap->find(uniformName);
    if(uniformIter != mpUniformLocationsMap->end()) {
        switch(dim) {
            case 1:
                glProgramUniform1uiv(mShaderProgramHandle, uniformIter->second, count, value );
                break;
            case 2:
                glProgramUniform2uiv(mShaderProgramHandle, uniformIter->second, count, value );
                break;
            case 3:
                glProgramUniform3uiv(mShaderProgramHandle, uniformIter->second, count, value );
                break;
            case 4:
                glProgramUniform4uiv(mShaderProgramHandle, uniformIter->second, count, value );
                break;
            default:
                fprintf(stderr, "[ERROR]: invalid dimension %u for uniform %s in Shader Program %u.  Dimension must be [1,4]\n", dim, uniformName, mShaderProgramHandle);
                break;
        }
    } else {
        fprintf(stderr, "[ERROR]: Could not find uniform \"%s\" for Shader Program %u\n", uniformName, mShaderProgramHandle);
    }
}

inline void CSCI441::ShaderProgram::setProgramUniform( const char *uniformName, glm::mat2 mtx ) const {
    auto uniformIter = mpUniformLocationsMap->find(uniformName);
    if(uniformIter != mpUniformLocationsMap->end()) {
        glProgramUniformMatrix2fv(mShaderProgramHandle, uniformIter->second, 1, GL_FALSE, &mtx[0][0] );
    } else {
        fprintf(stderr, "[ERROR]: Could not find uniform \"%s\" for Shader Program %u\n", uniformName, mShaderProgramHandle);
    }
}

inline void CSCI441::ShaderProgram::setProgramUniform( const char *uniformName, glm::mat3 mtx ) const {
    auto uniformIter = mpUniformLocationsMap->find(uniformName);
    if(uniformIter != mpUniformLocationsMap->end()) {
        glProgramUniformMatrix3fv(mShaderProgramHandle, uniformIter->second, 1, GL_FALSE, &mtx[0][0] );
    } else {
        fprintf(stderr, "[ERROR]: Could not find uniform \"%s\" for Shader Program %u\n", uniformName, mShaderProgramHandle);
    }
}

inline void CSCI441::ShaderProgram::setProgramUniform( const char *uniformName, glm::mat4 mtx ) const {
    auto uniformIter = mpUniformLocationsMap->find(uniformName);
    if(uniformIter != mpUniformLocationsMap->end()) {
        glProgramUniformMatrix4fv(mShaderProgramHandle, uniformIter->second, 1, GL_FALSE, &mtx[0][0] );
    } else {
        fprintf(stderr, "[ERROR]: Could not find uniform \"%s\" for Shader Program %u\n", uniformName, mShaderProgramHandle);
    }
}

inline void CSCI441::ShaderProgram::setProgramUniform( const char *uniformName, glm::mat2x3 mtx ) const {
    auto uniformIter = mpUniformLocationsMap->find(uniformName);
    if(uniformIter != mpUniformLocationsMap->end()) {
        glProgramUniformMatrix2x3fv(mShaderProgramHandle, uniformIter->second, 1, GL_FALSE, &mtx[0][0] );
    } else {
        fprintf(stderr, "[ERROR]: Could not find uniform \"%s\" for Shader Program %u\n", uniformName, mShaderProgramHandle);
    }
}

inline void CSCI441::ShaderProgram::setProgramUniform( const char *uniformName, glm::mat3x2 mtx ) const {
    auto uniformIter = mpUniformLocationsMap->find(uniformName);
    if(uniformIter != mpUniformLocationsMap->end()) {
        glProgramUniformMatrix3x2fv(mShaderProgramHandle, uniformIter->second, 1, GL_FALSE, &mtx[0][0] );
    } else {
        fprintf(stderr, "[ERROR]: Could not find uniform \"%s\" for Shader Program %u\n", uniformName, mShaderProgramHandle);
    }
}

inline void CSCI441::ShaderProgram::setProgramUniform( const char *uniformName, glm::mat2x4 mtx ) const {
    auto uniformIter = mpUniformLocationsMap->find(uniformName);
    if(uniformIter != mpUniformLocationsMap->end()) {
        glProgramUniformMatrix2x4fv(mShaderProgramHandle, uniformIter->second, 1, GL_FALSE, &mtx[0][0] );
    } else {
        fprintf(stderr, "[ERROR]: Could not find uniform \"%s\" for Shader Program %u\n", uniformName, mShaderProgramHandle);
    }
}

inline void CSCI441::ShaderProgram::setProgramUniform( const char *uniformName, glm::mat4x2 mtx ) const {
    auto uniformIter = mpUniformLocationsMap->find(uniformName);
    if(uniformIter != mpUniformLocationsMap->end()) {
        glProgramUniformMatrix4x2fv(mShaderProgramHandle, uniformIter->second, 1, GL_FALSE, &mtx[0][0] );
    } else {
        fprintf(stderr, "[ERROR]: Could not find uniform \"%s\" for Shader Program %u\n", uniformName, mShaderProgramHandle);
    }
}

inline void CSCI441::ShaderProgram::setProgramUniform( const char *uniformName, glm::mat3x4 mtx ) const {
    auto uniformIter = mpUniformLocationsMap->find(uniformName);
    if(uniformIter != mpUniformLocationsMap->end()) {
        glProgramUniformMatrix3x4fv(mShaderProgramHandle, uniformIter->second, 1, GL_FALSE, &mtx[0][0] );
    } else {
        fprintf(stderr, "[ERROR]: Could not find uniform \"%s\" for Shader Program %u\n", uniformName, mShaderProgramHandle);
    }
}

inline void CSCI441::ShaderProgram::setProgramUniform( const char *uniformName, glm::mat4x3 mtx ) const {
    auto uniformIter = mpUniformLocationsMap->find(uniformName);
    if(uniformIter != mpUniformLocationsMap->end()) {
        glProgramUniformMatrix4x3fv(mShaderProgramHandle, uniformIter->second, 1, GL_FALSE, &mtx[0][0] );
    } else {
        fprintf(stderr, "[ERROR]: Could not find uniform \"%s\" for Shader Program %u\n", uniformName, mShaderProgramHandle);
    }
}

inline void CSCI441::ShaderProgram::setProgramUniform( GLint uniformLocation, GLfloat v0 ) const {
    glProgramUniform1f(mShaderProgramHandle, uniformLocation, v0 );
}

inline void CSCI441::ShaderProgram::setProgramUniform( GLint uniformLocation, GLfloat v0, GLfloat v1 ) const {
    glProgramUniform2f(mShaderProgramHandle, uniformLocation, v0, v1 );
}

inline void CSCI441::ShaderProgram::setProgramUniform( GLint uniformLocation, glm::vec2 value ) const {
    setProgramUniform( uniformLocation, 2, 1, &value[0] );
}

inline void CSCI441::ShaderProgram::setProgramUniform( GLint uniformLocation, GLfloat v0, GLfloat v1, GLfloat v2 ) const {
    glProgramUniform3f(mShaderProgramHandle, uniformLocation, v0, v1, v2 );
}

inline void CSCI441::ShaderProgram::setProgramUniform( GLint uniformLocation, glm::vec3 value ) const {
    setProgramUniform( uniformLocation, 3, 1, &value[0] );
}

inline void CSCI441::ShaderProgram::setProgramUniform( GLint uniformLocation, GLfloat v0, GLfloat v1, GLfloat v2, GLfloat v3 ) const {
    glProgramUniform4f(mShaderProgramHandle, uniformLocation, v0, v1, v2, v3 );
}

inline void CSCI441::ShaderProgram::setProgramUniform( GLint uniformLocation, glm::vec4 value ) const {
    setProgramUniform( uniformLocation, 4, 1, &value[0] );
}

inline void CSCI441::ShaderProgram::setProgramUniform(GLint uniformLocation, GLuint dim, GLsizei count, const GLfloat *value) const {
    switch(dim) {
        case 1:
            glProgramUniform1fv(mShaderProgramHandle, uniformLocation, count, value );
            break;
        case 2:
            glProgramUniform2fv(mShaderProgramHandle, uniformLocation, count, value );
            break;
        case 3:
            glProgramUniform3fv(mShaderProgramHandle, uniformLocation, count, value );
            break;
        case 4:
            glProgramUniform4fv(mShaderProgramHandle, uniformLocation, count, value );
            break;
        default:
            fprintf(stderr, "[ERROR]: invalid dimension %u for uniform %i in Shader Program %u.  Dimension must be [1,4]\n", dim, uniformLocation, mShaderProgramHandle);
            break;
    }
}

inline void CSCI441::ShaderProgram::setProgramUniform( GLint uniformLocation, GLint v0 ) const {
    glProgramUniform1i(mShaderProgramHandle, uniformLocation, v0 );
}

inline void CSCI441::ShaderProgram::setProgramUniform( GLint uniformLocation, GLint v0, GLint v1 ) const {
    glProgramUniform2i(mShaderProgramHandle, uniformLocation, v0, v1 );
}

inline void CSCI441::ShaderProgram::setProgramUniform(GLint uniformLocation, glm::ivec2 value) const {
    setProgramUniform(uniformLocation, 2, 1, &value[0]);
}

inline void CSCI441::ShaderProgram::setProgramUniform( GLint uniformLocation, GLint v0, GLint v1, GLint v2 ) const {
    glProgramUniform3i(mShaderProgramHandle, uniformLocation, v0, v1, v2 );
}

inline void CSCI441::ShaderProgram::setProgramUniform(GLint uniformLocation, glm::ivec3 value) const {
    setProgramUniform(uniformLocation, 3, 1, &value[0]);
}

inline void CSCI441::ShaderProgram::setProgramUniform( GLint uniformLocation, GLint v0, GLint v1, GLint v2, GLint v3 ) const {
    glProgramUniform4i(mShaderProgramHandle, uniformLocation, v0, v1, v2, v3 );
}

inline void CSCI441::ShaderProgram::setProgramUniform(GLint uniformLocation, glm::ivec4 value) const {
    setProgramUniform(uniformLocation, 4, 1, &value[0]);
}

inline void CSCI441::ShaderProgram::setProgramUniform(GLint uniformLocation, GLuint dim, GLsizei count, const GLint *value) const {
    switch(dim) {
        case 1:
            glProgramUniform1iv(mShaderProgramHandle, uniformLocation, count, value );
            break;
        case 2:
            glProgramUniform2iv(mShaderProgramHandle, uniformLocation, count, value );
            break;
        case 3:
            glProgramUniform3iv(mShaderProgramHandle, uniformLocation, count, value );
            break;
        case 4:
            glProgramUniform4iv(mShaderProgramHandle, uniformLocation, count, value );
            break;
        default:
            fprintf(stderr, "[ERROR]: invalid dimension %u for uniform %i in Shader Program %u.  Dimension must be [1,4]\n", dim, uniformLocation, mShaderProgramHandle);
            break;
    }
}

inline void CSCI441::ShaderProgram::setProgramUniform( GLint uniformLocation, GLuint v0 ) const {
    glProgramUniform1ui(mShaderProgramHandle, uniformLocation, v0 );
}

inline void CSCI441::ShaderProgram::setProgramUniform( GLint uniformLocation, GLuint v0, GLuint v1 ) const {
    glProgramUniform2ui(mShaderProgramHandle, uniformLocation, v0, v1 );
}

inline void CSCI441::ShaderProgram::setProgramUniform(GLint uniformLocation, glm::uvec2 value) const {
    setProgramUniform(uniformLocation, 2, 1, &value[0]);
}

inline void CSCI441::ShaderProgram::setProgramUniform( GLint uniformLocation, GLuint v0, GLuint v1, GLuint v2 ) const {
    glProgramUniform3ui(mShaderProgramHandle, uniformLocation, v0, v1, v2 );
}

inline void CSCI441::ShaderProgram::setProgramUniform(GLint uniformLocation, glm::uvec3 value) const {
    setProgramUniform(uniformLocation, 3, 1, &value[0]);
}

inline void CSCI441::ShaderProgram::setProgramUniform( GLint uniformLocation, GLuint v0, GLuint v1, GLuint v2, GLuint v3 ) const {
    glProgramUniform4ui(mShaderProgramHandle, uniformLocation, v0, v1, v2, v3 );
}

inline void CSCI441::ShaderProgram::setProgramUniform(GLint uniformLocation, glm::uvec4 value) const {
    setProgramUniform(uniformLocation, 4, 1, &value[0]);
}

inline void CSCI441::ShaderProgram::setProgramUniform(GLint uniformLocation, GLuint dim, GLsizei count, const GLuint *value) const {
    switch(dim) {
        case 1:
            glProgramUniform1uiv(mShaderProgramHandle, uniformLocation, count, value );
            break;
        case 2:
            glProgramUniform2uiv(mShaderProgramHandle, uniformLocation, count, value );
            break;
        case 3:
            glProgramUniform3uiv(mShaderProgramHandle, uniformLocation, count, value );
            break;
        case 4:
            glProgramUniform4uiv(mShaderProgramHandle, uniformLocation, count, value );
            break;
        default:
            fprintf(stderr, "[ERROR]: invalid dimension %u for uniform %i in Shader Program %u.  Dimension must be [1,4]\n", dim, uniformLocation, mShaderProgramHandle);
            break;
    }
}

inline void CSCI441::ShaderProgram::setProgramUniform( GLint uniformLocation, glm::mat2 mtx ) const {
    glProgramUniformMatrix2fv(mShaderProgramHandle, uniformLocation, 1, GL_FALSE, &mtx[0][0] );
}

inline void CSCI441::ShaderProgram::setProgramUniform( GLint uniformLocation, glm::mat3 mtx ) const {
    glProgramUniformMatrix3fv(mShaderProgramHandle, uniformLocation, 1, GL_FALSE, &mtx[0][0] );
}

inline void CSCI441::ShaderProgram::setProgramUniform( GLint uniformLocation, glm::mat4 mtx ) const {
    glProgramUniformMatrix4fv(mShaderProgramHandle, uniformLocation, 1, GL_FALSE, &mtx[0][0] );
}

inline void CSCI441::ShaderProgram::setProgramUniform( GLint uniformLocation, glm::mat2x3 mtx ) const {
    glProgramUniformMatrix2x3fv(mShaderProgramHandle, uniformLocation, 1, GL_FALSE, &mtx[0][0] );
}

inline void CSCI441::ShaderProgram::setProgramUniform( GLint uniformLocation, glm::mat3x2 mtx ) const {
    glProgramUniformMatrix3x2fv(mShaderProgramHandle, uniformLocation, 1, GL_FALSE, &mtx[0][0] );
}

inline void CSCI441::ShaderProgram::setProgramUniform( GLint uniformLocation, glm::mat2x4 mtx ) const {
    glProgramUniformMatrix2x4fv(mShaderProgramHandle, uniformLocation, 1, GL_FALSE, &mtx[0][0] );
}

inline void CSCI441::ShaderProgram::setProgramUniform( GLint uniformLocation, glm::mat4x2 mtx ) const {
    glProgramUniformMatrix4x2fv(mShaderProgramHandle, uniformLocation, 1, GL_FALSE, &mtx[0][0] );
}

inline void CSCI441::ShaderProgram::setProgramUniform( GLint uniformLocation, glm::mat3x4 mtx ) const {
    glProgramUniformMatrix3x4fv(mShaderProgramHandle, uniformLocation, 1, GL_FALSE, &mtx[0][0] );
}

inline void CSCI441::ShaderProgram::setProgramUniform( GLint uniformLocation, glm::mat4x3 mtx ) const {
    glProgramUniformMatrix4x3fv(mShaderProgramHandle, uniformLocation, 1, GL_FALSE, &mtx[0][0] );
}

inline CSCI441::ShaderProgram::ShaderProgram() {
    _initialize();
}

inline void CSCI441::ShaderProgram::_initialize() {
    mVertexShaderHandle = 0;
    mTesselationControlShaderHandle = 0;
    mTesselationEvaluationShaderHandle = 0;
    mGeometryShaderHandle = 0;
    mFragmentShaderHandle = 0;
    mShaderProgramHandle = 0;
    mpUniformLocationsMap = nullptr;
    mpAttributeLocationsMap = nullptr;
}

inline CSCI441::ShaderProgram::~ShaderProgram() {
    int status;
    int infoLogLength = 0;
    int maxLength = 1000;

    glDeleteProgram(mShaderProgramHandle );

    // create a buffer of designated length
    char infoLog[maxLength];

    glGetProgramiv(mShaderProgramHandle, GL_DELETE_STATUS, &status );

    // get the info log for the vertex/tesselation/geometry/fragment/compute shader
    glGetProgramInfoLog(mShaderProgramHandle, maxLength, &infoLogLength, infoLog );

    if(infoLogLength > 0 ) {
        // print info to terminal
        if( sDEBUG ) printf("[INFO]: Program Handle %d Delete Status %s: %s\n", mShaderProgramHandle, (status == GL_TRUE ? "Success" : " Error"), infoLog );
    }

    delete mpUniformLocationsMap;
    delete mpAttributeLocationsMap;
}

inline bool CSCI441::ShaderProgram::writeShaderProgramBinaryToFile(const char* BINARY_FILE_NAME) {
    GLint formats = 0;
    glGetIntegerv(GL_NUM_PROGRAM_BINARY_FORMATS, &formats);
    if( formats < 1 ) {
        fprintf(stderr, "[ERROR]: Driver does not support any binary formats.\n");
        return false;
    }

    // Get the binary length
    GLint length = 0;
    glGetProgramiv(mShaderProgramHandle, GL_PROGRAM_BINARY_LENGTH, &length);

    // Retrieve the binary code
    std::vector<GLubyte> buffer(length);
    GLenum format = 0;
    glGetProgramBinary(mShaderProgramHandle, length, nullptr, &format, buffer.data());

    // Write the binary to a file.
    fprintf(stdout, "[INFO]: Writing to %s, binary format %d\n",BINARY_FILE_NAME, format);
    std::ofstream out(BINARY_FILE_NAME, std::ios::binary);
    out.write( reinterpret_cast<char *>(buffer.data()), length );
    out.close();

    return true;
}

inline CSCI441::ShaderProgram* CSCI441::ShaderProgram::loadShaderProgramFromBinaryFile(const char* BINARY_FILE_NAME, const GLenum FORMAT) {
    GLint formats = 0;
    glGetIntegerv(GL_NUM_PROGRAM_BINARY_FORMATS, &formats);
    if( formats < 1 ) {
        fprintf(stderr, "[ERROR]: Driver does not support any binary formats.\n");
        return nullptr;
    }

    GLuint program = glCreateProgram();

    // Load binary from file
    std::ifstream inputStream(BINARY_FILE_NAME, std::ios::binary);
    std::istreambuf_iterator<char> startIt(inputStream), endIt;
    std::vector<char> buffer(startIt, endIt);  // Load file
    inputStream.close();

    // Install shader binary
    glProgramBinary(program, FORMAT, buffer.data(), buffer.size() );

    // Check for success/failure
    GLint status;
    glGetProgramiv(program, GL_LINK_STATUS, &status);
    if( GL_FALSE == status ) {
        CSCI441_INTERNAL::ShaderUtils::printProgramLog(program);
        return nullptr;
    }

    auto shaderProgram = new CSCI441::ShaderProgram();
    shaderProgram->mShaderProgramHandle = program;
    return shaderProgram;
}

#endif // CSCI441_SHADER_PROGRAM_HPP
