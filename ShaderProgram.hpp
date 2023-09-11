/** @file ShaderProgram.hpp
 * @brief Class to work with OpenGL 4.0+ Shaders
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

        /** @brief Creates a Shader Program using a Vertex Shader, Tessellation Shader, Geometry Shader, and Fragment Shader
         * @param vertexShaderFilename name of the file corresponding to the vertex shader
         * @param tessellationControlShaderFilename name of the file corresponding to the tessellation control shader
         * @param tessellationEvaluationShaderFilename name of the file corresponding to the tessellation evaluation shader
         * @param geometryShaderFilename name of the file corresponding to the geometry shader
         * @param fragmentShaderFilename name of the file corresponding to the fragment shader
         */
        [[maybe_unused]]
        ShaderProgram( const char *vertexShaderFilename,
                       const char *tessellationControlShaderFilename,
                       const char *tessellationEvaluationShaderFilename,
                       const char *geometryShaderFilename,
                       const char *fragmentShaderFilename );

        /**
         * @brief Creates a Shader Program using a Vertex Shader, Tessellation Shader, Geometry Shader, and Fragment Shader
         * @param vertexShaderFilename name of the file corresponding to the vertex shader
         * @param tessellationControlShaderFilename name of the file corresponding to the tessellation control shader
         * @param tessellationEvaluationShaderFilename name of the file corresponding to the tessellation evaluation shader
         * @param geometryShaderFilename name of the file corresponding to the geometry shader
         * @param fragmentShaderFilename name of the file corresponding to the fragment shader
         * @param isSeparable if program is separable
         */
        [[maybe_unused]]
        ShaderProgram( const char *vertexShaderFilename,
                       const char *tessellationControlShaderFilename,
                       const char *tessellationEvaluationShaderFilename,
                       const char *geometryShaderFilename,
                       const char *fragmentShaderFilename,
                       bool isSeparable );

        /**
         * @brief Creates a Shader Program using a Vertex Shader, Tessellation Shader, and Fragment Shader
         * @param vertexShaderFilename name of the file corresponding to the vertex shader
         * @param tessellationControlShaderFilename name of the file corresponding to the tessellation control shader
         * @param tessellationEvaluationShaderFilename name of the file corresponding to the tessellation evaluation shader
         * @param fragmentShaderFilename name of the file corresponding to the fragment shader
         */
        [[maybe_unused]]
        ShaderProgram( const char *vertexShaderFilename,
                       const char *tessellationControlShaderFilename,
                       const char *tessellationEvaluationShaderFilename,
                       const char *fragmentShaderFilename );

        /**
         * @brief Creates a Shader Program using a Vertex Shader, Tessellation Shader, and Fragment Shader
         * @param vertexShaderFilename name of the file corresponding to the vertex shader
         * @param tessellationControlShaderFilename name of the file corresponding to the tessellation control shader
         * @param tessellationEvaluationShaderFilename name of the file corresponding to the tessellation evaluation shader
         * @param fragmentShaderFilename name of the file corresponding to the fragment shader
         * @param isSeparable if program is separable
         */
        [[maybe_unused]]
        ShaderProgram( const char *vertexShaderFilename,
                       const char *tessellationControlShaderFilename,
                       const char *tessellationEvaluationShaderFilename,
                       const char *fragmentShaderFilename,
                       bool isSeparable);

        /**
         * @brief Creates a Shader Program using a Vertex Shader, Geometry Shader, and Fragment Shader
         * @param vertexShaderFilename name of the file corresponding to the vertex shader
         * @param geometryShaderFilename name of the file corresponding to the geometry shader
         * @param fragmentShaderFilename name of the file corresponding to the fragment shader
         */
        ShaderProgram( const char *vertexShaderFilename,
                       const char *geometryShaderFilename,
                       const char *fragmentShaderFilename );

        /**
         * @brief Creates a Shader Program using a Vertex Shader, Geometry Shader, and Fragment Shader
         * @param vertexShaderFilename name of the file corresponding to the vertex shader
         * @param geometryShaderFilename name of the file corresponding to the geometry shader
         * @param fragmentShaderFilename name of the file corresponding to the fragment shader
         * @param isSeparable if program is separable
         */
        [[maybe_unused]]
        ShaderProgram( const char *vertexShaderFilename,
                       const char *geometryShaderFilename,
                       const char *fragmentShaderFilename,
                       bool isSeparable );

        /**
         * @brief Creates a Shader Program using any combination of shaders.  Intended to be used to create separable programs
         * but can be used as an alternative to the above overloaded constructors to explicitly state which shaders are present.
         * @param shaderFilenames an array of filenames corresponding to all the shaders.  size must be equal to the sum of true shaders present, with two for the tessellation shader
         * @param vertexPresent if vertex shader is present
         * @param tessellationPresent if tessellation shader is present
         * @param geometryPresent if geometry shader is present
         * @param fragmentPresent if fragment shader is present
         * @param isSeparable if program is separable
         */
        [[maybe_unused]]
        ShaderProgram( const char **shaderFilenames,
                       bool vertexPresent, bool tessellationPresent, bool geometryPresent, bool fragmentPresent,
                       bool isSeparable );

        /**
         * @brief Clean up memory associated with the Shader Program
         */
        virtual ~ShaderProgram();

        /**
         * @brief do not allow shader programs to be copied
         */
        ShaderProgram(const ShaderProgram&) = delete;
        /**
         * @brief do not allow shader programs to be copied
         */
        ShaderProgram& operator=(const ShaderProgram&) = delete;

        /**
         * @brief writes precompiled shader program binary to external file
         * @param BINARY_FILE_NAME filename to write shader program binary to
         * @return true if write succeeded, false otherwise
         */
        virtual bool writeShaderProgramBinaryToFile(const char* BINARY_FILE_NAME) const final;

        /**
         * @brief loads precompiled shader program binary from external file
         * @param BINARY_FILE_NAME filename to read shader program binary from
         * @param format format of binary data
         * @return true if read succeeded, false otherwise
         */
        static ShaderProgram* loadShaderProgramFromBinaryFile(const char* BINARY_FILE_NAME, GLenum format);

        /**
         * @brief Returns the location of the given uniform in this shader program
         * @param uniformName name of the uniform to get the location for
         * @return location of the given uniform in this shader program
         * @note Prints an error message to standard error stream if the uniform is not found
         */
        virtual GLint getUniformLocation( const char *uniformName ) const final;

        /**
         * @brief Returns the index of the given uniform block in this shader program
         * @param uniformBlockName name of the uniform block to get the index for
         * @return index of the given uniform block in this shader program
         * @note Prints an error message to standard error stream if the uniform block is not found
         */
        virtual GLint getUniformBlockIndex( const char *uniformBlockName ) const final;
        /**
         * @brief Returns the size of the given uniform block in this shader program
         * @param uniformBlockName - name of the uniform block to get the size for
         * @return size of the given uniform block in this shader program
         * @note Prints an error message to standard error stream if the uniform block is not found
         */
        virtual GLint getUniformBlockSize( const char *uniformBlockName ) const final;
        /**
         * @brief Returns an allocated buffer for the given uniform block in this shader program
         * @param uniformBlockName name of the uniform block to allocate a buffer for
         * @return allocated buffer for the given uniform block in this shader program
         * @note Prints an error message to standard error stream if the uniform block is not found
         */
        [[maybe_unused]] virtual GLubyte* getUniformBlockBuffer( const char *uniformBlockName ) const final;
        /**
         * @brief Returns an array of offsets into the buffer for the given uniform block in this shader program
         * @param uniformBlockName name of the uniform block to return offsets for
         * @return array of offsets for the given uniform block in this shader program
         * @note Prints an error message to standard error stream if the uniform block is not found
         */
        [[maybe_unused]] virtual GLint* getUniformBlockOffsets( const char *uniformBlockName ) const final;
        /**
         * @brief Returns an array of offsets into the buffer for the given uniform block and names in this shader program
         * @param uniformBlockName name of the uniform block to return offsets for
         * @param names names of the uniform block components to get offsets for
         * @return array of offsets for the given uniform block in this shader program
         * @note Prints an error message to standard error stream if the uniform block is not found
         */
        [[maybe_unused]] virtual GLint* getUniformBlockOffsets( const char *uniformBlockName, const char *names[] ) const final;
        /**
         * @brief Returns an array of offsets into the buffer for the given uniform block in this shader program
         * @param uniformBlockIndex index uniform block to return offsets for
         * @return array of offsets for the given uniform block in this shader program
         * @note Prints an error message to standard error stream if the uniform block is not found
         */
        [[nodiscard]] virtual GLint* getUniformBlockOffsets(GLint uniformBlockIndex ) const final;
        /**
         * @brief Returns an array of offsets into the buffer for the given uniform block and names in this shader program
         * @param uniformBlockIndex index uniform block to return offsets for
         * @param names names of the uniform block components to get offsets for
         * @return array of offsets for the given uniform block in this shader program
         * @note Prints an error message to standard error stream if the uniform block is not found
         */
        [[nodiscard]] virtual GLint* getUniformBlockOffsets(GLint uniformBlockIndex, const char *names[] ) const final;
        /**
         * @brief Set the binding point for the given uniform block in this shader program
         * @param uniformBlockName name of the uniform block to bind
         * @param binding point for this uniform block
         * @note Prints an error message to standard error stream if the uniform block is not found
         */
        virtual void setUniformBlockBinding( const char *uniformBlockName, GLuint binding ) const final;

        /**
         * @brief Returns the location of the given attribute in this shader program
         * @param attributeName name of the attribute to get the location for
         * @return location of the given attribute in this shader program
         * @note Prints an error message to standard error stream if the attribute is not found
         */
        [[maybe_unused]] virtual GLint getAttributeLocation( const char *attributeName ) const final;

        /**
         * @brief Returns the index of the given subroutine for a shader stage in this shader program
         * @param shaderStage stage of the shader program to get the subroutine for.
         *   Allowable values: GL_VERTEX_SHADER, GL_TESS_CONTROL_SHADER, GL_TESS_EVALUATION_SHADER, GL_GEOMETRY_SHADER, GL_FRAGMENT_SHADER
         * @param subroutineName name of the subroutine to get the location for
         * @return index of the given subroutine for the shader stage in this shader program
         * @note Prints an error message to standard error stream if the subroutine is not found
         */
        [[maybe_unused]] virtual GLuint getSubroutineIndex( GLenum shaderStage, const char *subroutineName ) const final;

        /**
         * @brief Returns the binding point for the corresponding image uniform
         * @param imageName name of the image to get binding point for
         * @return binding point for image
         * @note Prints an error message to standard error stream if the image is not found
         */
        [[maybe_unused]] virtual GLint getImageBinding(const char* imageName) const final;

        /**
         * @brief Returns the binding point for the corresponding shader storage block
         * @param ssboName name of the shader storage block to get binding point for
         * @return binding point for shader storage block
         * @note Prints an error message to standard error stream if the shader storage block is not found
         */
        [[maybe_unused]] virtual GLint getShaderStorageBlockBinding(const char* ssboName) const final;

        /**
         * @brief Returns the binding point for the corresponding atomic counter buffer
         * @param atomicName name of the atomic counter buffer to get size for
         * @return binding point of atomic counter buffer
         * @note Prints an error message to standard error stream if the atomic counter is not found
         */
        [[maybe_unused]] virtual GLint getAtomicCounterBufferBinding(const char* atomicName) const final;
        /**
         * @brief Returns the offset into the buffer for the corresponding atomic counter buffer
         * @param atomicName name of the atomic counter buffer to get size for
         * @return offset of atomic counter buffer
         * @note Prints an error message to standard error stream if the atomic counter is not found
         */
        [[maybe_unused]] virtual GLint getAtomicCounterBufferOffset(const char* atomicName) const final;
        /**
         * @brief Returns the full buffer size for the corresponding atomic counter buffer
         * @param atomicName name of the atomic counter buffer to get size for
         * @return size of atomic counter buffer
         * @note Prints an error message to standard error stream if the atomic counter is not found
         */
        [[maybe_unused]] virtual GLint getAtomicCounterBufferSize(const char* atomicName) const final;

        /**
         * @brief Returns the number of active uniforms in this shader program
         * @return number of active uniforms in this shader program
         */
        [[maybe_unused]] [[nodiscard]] virtual GLuint getNumUniforms() const final;
        /**
         * @brief Returns the number of active uniform blocks in this shader program
         * @return number of active uniform blocks in this shader program
         */
        [[maybe_unused]] [[nodiscard]] virtual GLuint getNumUniformBlocks() const final;
        /**
         * @brief Returns the number of active attributes in this shader program
         * @return number of active attributes in this shader program
         */
        [[maybe_unused]] [[nodiscard]] virtual GLuint getNumAttributes() const final;

        /**
         * @brief Returns the handle for this shader program
         * @return handle for this shader program
         */
        [[nodiscard]] virtual GLuint getShaderProgramHandle() const final;

        /**
         * @brief Sets the Shader Program to be active
         */
        [[maybe_unused]] virtual void useProgram() const final;

        /**
         * @brief sets the program uniform consisting of one float
         * @param uniformName name of the uniform as a string
         * @param v0 value to set
         */
        [[maybe_unused]] virtual void setProgramUniform(const char* uniformName, GLfloat v0) const final;
        /**
         * @brief sets the program uniform consisting of one integer
         * @param uniformName name of the uniform as a string
         * @param v0 value to set
         */
        [[maybe_unused]] virtual void setProgramUniform(const char* uniformName, GLint v0) const final;
        /**
         * @brief sets the program uniform consisting of one unsigned integer
         * @param uniformName name of the uniform as a string
         * @param v0 value to set
         */
        [[maybe_unused]] virtual void setProgramUniform(const char* uniformName, GLuint v0) const final;
        /**
         * @brief sets the program uniform consisting of one 2x2 matrix
         * @param uniformName name of the uniform as a string
         * @param mtx value to set
         */
        [[maybe_unused]] virtual void setProgramUniform(const char* uniformName, glm::mat2 mtx) const final;
        /**
         * @brief sets the program uniform consisting of one 3x3 matrix
         * @param uniformName name of the uniform as a string
         * @param mtx value to set
         */
        [[maybe_unused]] virtual void setProgramUniform(const char* uniformName, glm::mat3 mtx) const final;
        /**
         * @brief sets the program uniform consisting of one 4x4 matrix
         * @param uniformName name of the uniform as a string
         * @param mtx value to set
         */
        [[maybe_unused]] virtual void setProgramUniform(const char* uniformName, glm::mat4 mtx) const final;
        /**
         * @brief sets the program uniform consisting of one 2x3 matrix
         * @param uniformName name of the uniform as a string
         * @param mtx value to set
         */
        [[maybe_unused]] virtual void setProgramUniform(const char* uniformName, glm::mat2x3 mtx) const final;
        /**
         * @brief sets the program uniform consisting of one 3x2 matrix
         * @param uniformName name of the uniform as a string
         * @param mtx value to set
         */
        [[maybe_unused]] virtual void setProgramUniform(const char* uniformName, glm::mat3x2 mtx) const final;
        /**
         * @brief sets the program uniform consisting of one 2x4 matrix
         * @param uniformName name of the uniform as a string
         * @param mtx value to set
         */
        [[maybe_unused]] virtual void setProgramUniform(const char* uniformName, glm::mat2x4 mtx) const final;
        /**
         * @brief sets the program uniform consisting of one 4x2 matrix
         * @param uniformName name of the uniform as a string
         * @param mtx value to set
         */
        [[maybe_unused]] virtual void setProgramUniform(const char* uniformName, glm::mat4x2 mtx) const final;
        /**
         * @brief sets the program uniform consisting of one 3x4 matrix
         * @param uniformName name of the uniform as a string
         * @param mtx value to set
         */
        [[maybe_unused]] virtual void setProgramUniform(const char* uniformName, glm::mat3x4 mtx) const final;
        /**
         * @brief sets the program uniform consisting of one 4x3 matrix
         * @param uniformName name of the uniform as a string
         * @param mtx value to set
         */
        [[maybe_unused]] virtual void setProgramUniform(const char* uniformName, glm::mat4x3 mtx) const final;

        /**
         * @brief sets the program uniform consisting of two floats
         * @param uniformName name of the uniform as a string
         * @param v0 value to set
         * @param v1 value to set
         */
        [[maybe_unused]] virtual void setProgramUniform(const char* uniformName, GLfloat v0, GLfloat v1) const final;
        /**
         * @brief sets the program uniform consisting of two integers
         * @param uniformName name of the uniform as a string
         * @param v0 value to set
         * @param v1 value to set
         */
        [[maybe_unused]] virtual void setProgramUniform(const char* uniformName, GLint v0, GLint v1) const final;
        /**
         * @brief sets the program uniform consisting of two unsigned integers
         * @param uniformName name of the uniform as a string
         * @param v0 value to set
         * @param v1 value to set
         */
        [[maybe_unused]] virtual void setProgramUniform(const char* uniformName, GLuint v0, GLuint v1) const final;

        /**
         * @brief sets the program uniform consisting of three floats
         * @param uniformName name of the uniform as a string
         * @param v0 value to set
         * @param v1 value to set
         * @param v2 value to set
         */
        [[maybe_unused]] virtual void setProgramUniform(const char* uniformName, GLfloat v0, GLfloat v1, GLfloat v2) const final;
        /**
         * @brief sets the program uniform consisting of three integers
         * @param uniformName name of the uniform as a string
         * @param v0 value to set
         * @param v1 value to set
         * @param v2 value to set
         */
        [[maybe_unused]] virtual void setProgramUniform(const char* uniformName, GLint v0, GLint v1, GLint v2) const final;
        /**
         * @brief sets the program uniform consisting of three unsigned integers
         * @param uniformName name of the uniform as a string
         * @param v0 value to set
         * @param v1 value to set
         * @param v2 value to set
         */
        [[maybe_unused]] virtual void setProgramUniform(const char* uniformName, GLuint v0, GLuint v1, GLuint v2) const final;

        /**
         * @brief sets the program uniform consisting of four floats
         * @param uniformName name of the uniform as a string
         * @param v0 value to set
         * @param v1 value to set
         * @param v2 value to set
         * @param v3 value to set
         */
        [[maybe_unused]] virtual void setProgramUniform(const char* uniformName, GLfloat v0, GLfloat v1, GLfloat v2, GLfloat v3) const final;
        /**
         * @brief sets the program uniform consisting of four integers
         * @param uniformName name of the uniform as a string
         * @param v0 value to set
         * @param v1 value to set
         * @param v2 value to set
         * @param v3 value to set
         */
        [[maybe_unused]] virtual void setProgramUniform(const char* uniformName, GLint v0, GLint v1, GLint v2, GLint v3) const final;
        /**
         * @brief sets the program uniform consisting of four unsigned integers
         * @param uniformName name of the uniform as a string
         * @param v0 value to set
         * @param v1 value to set
         * @param v2 value to set
         * @param v3 value to set
         */
        [[maybe_unused]] virtual void setProgramUniform(const char* uniformName, GLuint v0, GLuint v1, GLuint v2, GLuint v3) const final;

        /**
         * @brief sets the program uniform consisting of two floats
         * @param uniformName name of the uniform as a string
         * @param value value to set
         */
        [[maybe_unused]] virtual void setProgramUniform(const char* uniformName, glm::vec2 value) const final;
        /**
         * @brief sets the program uniform consisting of two integers
         * @param uniformName name of the uniform as a string
         * @param value value to set
         */
        [[maybe_unused]] virtual void setProgramUniform(const char* uniformName, glm::ivec2 value) const final;
        /**
         * @brief sets the program uniform consisting of two unsigned integers
         * @param uniformName name of the uniform as a string
         * @param value value to set
         */
        [[maybe_unused]] virtual void setProgramUniform(const char* uniformName, glm::uvec2 value) const final;

        /**
         * @brief sets the program uniform consisting of three floats
         * @param uniformName name of the uniform as a string
         * @param value value to set
         */
        [[maybe_unused]] virtual void setProgramUniform(const char* uniformName, glm::vec3 value) const final;
        /**
         * @brief sets the program uniform consisting of three integers
         * @param uniformName name of the uniform as a string
         * @param value value to set
         */
        [[maybe_unused]] virtual void setProgramUniform(const char* uniformName, glm::ivec3 value) const final;
        /**
         * @brief sets the program uniform consisting of three unsigned integers
         * @param uniformName name of the uniform as a string
         * @param value value to set
         */
        [[maybe_unused]] virtual void setProgramUniform(const char* uniformName, glm::uvec3 value) const final;

        /**
         * @brief sets the program uniform consisting of four floats
         * @param uniformName name of the uniform as a string
         * @param value value to set
         */
        [[maybe_unused]] virtual void setProgramUniform(const char* uniformName, glm::vec4 value) const final;
        /**
         * @brief sets the program uniform consisting of four integers
         * @param uniformName name of the uniform as a string
         * @param value value to set
         */
        [[maybe_unused]] virtual void setProgramUniform(const char* uniformName, glm::ivec4 value) const final;
        /**
         * @brief sets the program uniform consisting of four unsigned integers
         * @param uniformName name of the uniform as a string
         * @param value value to set
         */
        [[maybe_unused]] virtual void setProgramUniform(const char* uniformName, glm::uvec4 value) const final;

        /**
         * @brief sets the program uniform consisting of floats
         * @param uniformName name of the uniform as a string
         * @param dim dimension (number of components) for each value
         * @param count number of values in array
         * @param value array of values (array size is equal to dim*count)
         */
        [[maybe_unused]] virtual void setProgramUniform(const char* uniformName, GLuint dim, GLsizei count, const GLfloat *value) const final;
        /**
         * @brief sets the program uniform consisting of integers
         * @param uniformName name of the uniform as a string
         * @param dim dimension (number of components) for each value
         * @param count number of values in array
         * @param value array of values (array size is equal to dim*count)
         */
        [[maybe_unused]] virtual void setProgramUniform(const char* uniformName, GLuint dim, GLsizei count, const GLint *value) const final;
        /**
         * @brief sets the program uniform consisting of unsigned integers
         * @param uniformName name of the uniform as a string
         * @param dim dimension (number of components) for each value
         * @param count number of values in array
         * @param value array of values (array size is equal to dim*count)
         */
        [[maybe_unused]] virtual void setProgramUniform(const char* uniformName, GLuint dim, GLsizei count, const GLuint *value) const final;

        /**
         * @brief sets the program uniform consisting of one float
         * @param uniformLocation location of the uniform
         * @param v0 value to set
         */
        [[maybe_unused]] virtual void setProgramUniform(GLint uniformLocation, GLfloat v0) const final;
        /**
         * @brief sets the program uniform consisting of one integer
         * @param uniformLocation location of the uniform
         * @param v0 value to set
         */
        [[maybe_unused]] virtual void setProgramUniform(GLint uniformLocation, GLint v0) const final;
        /**
         * @brief sets the program uniform consisting of one unsigned integer
         * @param uniformLocation location of the uniform
         * @param v0 value to set
         */
        [[maybe_unused]] virtual void setProgramUniform(GLint uniformLocation, GLuint v0) const final;
        /**
         * @brief sets the program uniform consisting of one 2x2 matrix
         * @param uniformLocation location of the uniform
         * @param mtx value to set
         */
        [[maybe_unused]] virtual void setProgramUniform(GLint uniformLocation, glm::mat2 mtx) const final;
        /**
         * @brief sets the program uniform consisting of one 3x3 matrix
         * @param uniformLocation location of the uniform
         * @param mtx value to set
         */
        [[maybe_unused]] virtual void setProgramUniform(GLint uniformLocation, glm::mat3 mtx) const final;
        /**
         * @brief sets the program uniform consisting of one 4x4 matrix
         * @param uniformLocation location of the uniform
         * @param mtx value to set
         */
        [[maybe_unused]] virtual void setProgramUniform(GLint uniformLocation, glm::mat4 mtx) const final;
        /**
         * @brief sets the program uniform consisting of one 2x3 matrix
         * @param uniformLocation location of the uniform
         * @param mtx value to set
         */
        [[maybe_unused]] virtual void setProgramUniform(GLint uniformLocation, glm::mat2x3 mtx) const final;
        /**
         * @brief sets the program uniform consisting of one 3x2 matrix
         * @param uniformLocation location of the uniform
         * @param mtx value to set
         */
        [[maybe_unused]] virtual void setProgramUniform(GLint uniformLocation, glm::mat3x2 mtx) const final;
        /**
         * @brief sets the program uniform consisting of one 2x4 matrix
         * @param uniformLocation location of the uniform
         * @param mtx value to set
         */
        [[maybe_unused]] virtual void setProgramUniform(GLint uniformLocation, glm::mat2x4 mtx) const final;
        /**
         * @brief sets the program uniform consisting of one 4x2 matrix
         * @param uniformLocation location of the uniform
         * @param mtx value to set
         */
        [[maybe_unused]] virtual void setProgramUniform(GLint uniformLocation, glm::mat4x2 mtx) const final;
        /**
         * @brief sets the program uniform consisting of one 3x4 matrix
         * @param uniformLocation location of the uniform
         * @param mtx value to set
         */
        [[maybe_unused]] virtual void setProgramUniform(GLint uniformLocation, glm::mat3x4 mtx) const final;
        /**
         * @brief sets the program uniform consisting of one 4x3 matrix
         * @param uniformLocation location of the uniform
         * @param mtx value to set
         */
        [[maybe_unused]] virtual void setProgramUniform(GLint uniformLocation, glm::mat4x3 mtx) const final;

        /**
         * @brief sets the program uniform consisting of two floats
         * @param uniformLocation location of the uniform
         * @param v0 value to set
         * @param v1 value to set
         */
        [[maybe_unused]] virtual void setProgramUniform(GLint uniformLocation, GLfloat v0, GLfloat v1) const final;
        /**
         * @brief sets the program uniform consisting of two integers
         * @param uniformLocation location of the uniform
         * @param v0 value to set
         * @param v1 value to set
         */
        [[maybe_unused]] virtual void setProgramUniform(GLint uniformLocation, GLint v0, GLint v1) const final;
        /**
         * @brief sets the program uniform consisting of two unsigned integers
         * @param uniformLocation location of the uniform
         * @param v0 value to set
         * @param v1 value to set
         */
        [[maybe_unused]] virtual void setProgramUniform(GLint uniformLocation, GLuint v0, GLuint v1) const final;

        /**
         * @brief sets the program uniform consisting of three floats
         * @param uniformLocation location of the uniform
         * @param v0 value to set
         * @param v1 value to set
         * @param v2 value to set
         */
        [[maybe_unused]] virtual void setProgramUniform(GLint uniformLocation, GLfloat v0, GLfloat v1, GLfloat v2) const final;
        /**
         * @brief sets the program uniform consisting of three integers
         * @param uniformLocation location of the uniform
         * @param v0 value to set
         * @param v1 value to set
         * @param v2 value to set
         */
        [[maybe_unused]] virtual void setProgramUniform(GLint uniformLocation, GLint v0, GLint v1, GLint v2) const final;
        /**
         * @brief sets the program uniform consisting of three unsigned integers
         * @param uniformLocation location of the uniform
         * @param v0 value to set
         * @param v1 value to set
         * @param v2 value to set
         */
        [[maybe_unused]] virtual void setProgramUniform(GLint uniformLocation, GLuint v0, GLuint v1, GLuint v2) const final;

        /**
         * @brief sets the program uniform consisting of four floats
         * @param uniformLocation location of the uniform
         * @param v0 value to set
         * @param v1 value to set
         * @param v2 value to set
         * @param v3 value to set
         */
        [[maybe_unused]] virtual void setProgramUniform(GLint uniformLocation, GLfloat v0, GLfloat v1, GLfloat v2, GLfloat v3) const final;
        /**
         * @brief sets the program uniform consisting of four integers
         * @param uniformLocation location of the uniform
         * @param v0 value to set
         * @param v1 value to set
         * @param v2 value to set
         * @param v3 value to set
         */
        [[maybe_unused]] virtual void setProgramUniform(GLint uniformLocation, GLint v0, GLint v1, GLint v2, GLint v3) const final;
        /**
         * @brief sets the program uniform consisting of four unsigned integers
         * @param uniformLocation location of the uniform
         * @param v0 value to set
         * @param v1 value to set
         * @param v2 value to set
         * @param v3 value to set
         */
        [[maybe_unused]] virtual void setProgramUniform(GLint uniformLocation, GLuint v0, GLuint v1, GLuint v2, GLuint v3) const final;

        /**
         * @brief sets the program uniform consisting of two floats
         * @param uniformLocation location of the uniform
         * @param value value to set
         */
        [[maybe_unused]] virtual void setProgramUniform(GLint uniformLocation, glm::vec2 value) const final;
        /**
         * @brief sets the program uniform consisting of two integers
         * @param uniformLocation location of the uniform
         * @param value value to set
         */
        [[maybe_unused]] virtual void setProgramUniform(GLint uniformLocation, glm::ivec2 value) const final;
        /**
         * @brief sets the program uniform consisting of two unsigned integers
         * @param uniformLocation location of the uniform
         * @param value value to set
         */
        [[maybe_unused]] virtual void setProgramUniform(GLint uniformLocation, glm::uvec2 value) const final;

        /**
         * @brief sets the program uniform consisting of three floats
         * @param uniformLocation location of the uniform
         * @param value value to set
         */
        [[maybe_unused]] virtual void setProgramUniform(GLint uniformLocation, glm::vec3 value) const final;
        /**
         * @brief sets the program uniform consisting of three integers
         * @param uniformLocation location of the uniform
         * @param value value to set
         */
        [[maybe_unused]] virtual void setProgramUniform(GLint uniformLocation, glm::ivec3 value) const final;
        /**
         * @brief sets the program uniform consisting of three unsigned integers
         * @param uniformLocation location of the uniform
         * @param value value to set
         */
        [[maybe_unused]] virtual void setProgramUniform(GLint uniformLocation, glm::uvec3 value) const final;

        /**
         * @brief sets the program uniform consisting of four floats
         * @param uniformLocation location of the uniform
         * @param value value to set
         */
        [[maybe_unused]] virtual void setProgramUniform(GLint uniformLocation, glm::vec4 value) const final;
        /**
         * @brief sets the program uniform consisting of four integers
         * @param uniformLocation location of the uniform
         * @param value value to set
         */
        [[maybe_unused]] virtual void setProgramUniform(GLint uniformLocation, glm::ivec4 value) const final;
        /**
         * @brief sets the program uniform consisting of four unsigned integers
         * @param uniformLocation location of the uniform
         * @param value value to set
         */
        [[maybe_unused]] virtual void setProgramUniform(GLint uniformLocation, glm::uvec4 value) const final;

        /**
         * @brief sets the program uniform consisting of floats
         * @param uniformLocation location of the uniform
         * @param dim dimension (number of components) for each value
         * @param count number of values in array
         * @param value array of values (array size is equal to dim*count)
         */
        virtual void setProgramUniform(GLint uniformLocation, GLuint dim, GLsizei count, const GLfloat *value) const final;
        /**
         * @brief sets the program uniform consisting of integers
         * @param uniformLocation location of the uniform
         * @param dim dimension (number of components) for each value
         * @param count number of values in array
         * @param value array of values (array size is equal to dim*count)
         */
        virtual void setProgramUniform(GLint uniformLocation, GLuint dim, GLsizei count, const GLint *value) const final;
        /**
         * @brief sets the program uniform consisting of unsigned integers
         * @param uniformLocation location of the uniform
         * @param dim dimension (number of components) for each value
         * @param count number of values in array
         * @param value array of values (array size is equal to dim*count)
         */
        virtual void setProgramUniform(GLint uniformLocation, GLuint dim, GLsizei count, const GLuint *value) const final;

        /**
         * @brief returns a single value corresponding to which shader stages are present in this shader program
         * @return bitfield of shader stages
         */
        [[maybe_unused]] [[nodiscard]] virtual GLbitfield getProgramStages() const final;

    protected:
        /**
         * @brief creates an empty shader program object
         */
        ShaderProgram();

        /**
         * @brief if DEBUG information should be printed or not
         * @note defaults to true
         */
        static bool sDEBUG;

        /**
         * @brief handle to the vertex shader stage
         */
        GLuint mVertexShaderHandle;
        /**
         * @brief handle to the tessellation control shader stage
         */
        GLuint mTessellationControlShaderHandle;
        /**
         * @brief handle to the tessellation evaluation shader stage
         */
        GLuint mTessellationEvaluationShaderHandle;
        /**
         * @brief handle to the geometry shader stage
         */
        GLuint mGeometryShaderHandle;
        /**
         * @brief handle to the fragment shader stage
         */
        GLuint mFragmentShaderHandle;

        /**
         * @brief handle to the shader program
         */
        GLuint mShaderProgramHandle;

        /**
         * @brief caches locations of uniform names within shader program
         */
        std::map<std::string, GLint> *mpUniformLocationsMap;
        /**
         * @brief caches locations of attribute names within shader program
         */
        std::map<std::string, GLint> *mpAttributeLocationsMap;

        /**
         * @brief registers a shader program with the GPU
         * @param vertexShaderFilename vertex shader filename to load from text file
         * @param tessellationControlShaderFilename tessellation control shader filename to load from text file
         * @param tessellationEvaluationShaderFilename tessellation evaluation shader filename to load from text file
         * @param geometryShaderFilename geometry shader filename to load from text file
         * @param fragmentShaderFilename fragment shader filename to load from text file
         * @param isSeparable if shader program is separable
         * @return true if shader program handle could be created, false otherwise
         */
        virtual bool mRegisterShaderProgram(const char *vertexShaderFilename,
                                            const char *tessellationControlShaderFilename,
                                            const char *tessellationEvaluationShaderFilename,
                                            const char *geometryShaderFilename,
                                            const char *fragmentShaderFilename,
                                            bool isSeparable ) final;

    private:
        void _initialize();
    };

}

////////////////////////////////////////////////////////////////////////////////

inline bool CSCI441::ShaderProgram::sDEBUG = true;

[[maybe_unused]]
inline void CSCI441::ShaderProgram::enableDebugMessages() {
    sDEBUG = true;
}

[[maybe_unused]]
inline void CSCI441::ShaderProgram::disableDebugMessages() {
    sDEBUG = false;
}

inline CSCI441::ShaderProgram::ShaderProgram( const char *vertexShaderFilename, const char *fragmentShaderFilename ) {
    _initialize();
    mRegisterShaderProgram(vertexShaderFilename, "", "", "", fragmentShaderFilename, false);
}

[[maybe_unused]]
inline CSCI441::ShaderProgram::ShaderProgram( const char *vertexShaderFilename, const char *fragmentShaderFilename, const bool isSeparable ) {
    _initialize();
    mRegisterShaderProgram(vertexShaderFilename, "", "", "", fragmentShaderFilename, isSeparable);
}

[[maybe_unused]]
inline CSCI441::ShaderProgram::ShaderProgram(const char *vertexShaderFilename, const char *tessellationControlShaderFilename, const char *tessellationEvaluationShaderFilename, const char *geometryShaderFilename, const char *fragmentShaderFilename ) {
    _initialize();
    mRegisterShaderProgram(vertexShaderFilename, tessellationControlShaderFilename, tessellationEvaluationShaderFilename,
                           geometryShaderFilename, fragmentShaderFilename, false);
}

[[maybe_unused]]
inline CSCI441::ShaderProgram::ShaderProgram(const char *vertexShaderFilename, const char *tessellationControlShaderFilename, const char *tessellationEvaluationShaderFilename, const char *geometryShaderFilename, const char *fragmentShaderFilename, bool isSeparable  ) {
    _initialize();
    mRegisterShaderProgram(vertexShaderFilename, tessellationControlShaderFilename, tessellationEvaluationShaderFilename,
                           geometryShaderFilename, fragmentShaderFilename, isSeparable);
}

[[maybe_unused]]
inline CSCI441::ShaderProgram::ShaderProgram(const char *vertexShaderFilename, const char *tessellationControlShaderFilename, const char *tessellationEvaluationShaderFilename, const char *fragmentShaderFilename ) {
    _initialize();
    mRegisterShaderProgram(vertexShaderFilename, tessellationControlShaderFilename, tessellationEvaluationShaderFilename,
                           "", fragmentShaderFilename, false);
}

[[maybe_unused]]
inline CSCI441::ShaderProgram::ShaderProgram(const char *vertexShaderFilename, const char *tessellationControlShaderFilename, const char *tessellationEvaluationShaderFilename, const char *fragmentShaderFilename, bool isSeparable  ) {
    _initialize();
    mRegisterShaderProgram(vertexShaderFilename, tessellationControlShaderFilename, tessellationEvaluationShaderFilename,
                           "", fragmentShaderFilename, isSeparable);
}

inline CSCI441::ShaderProgram::ShaderProgram( const char *vertexShaderFilename, const char *geometryShaderFilename, const char *fragmentShaderFilename ) {
    _initialize();
    mRegisterShaderProgram(vertexShaderFilename, "", "", geometryShaderFilename, fragmentShaderFilename, false);
}

[[maybe_unused]]
inline CSCI441::ShaderProgram::ShaderProgram( const char *vertexShaderFilename, const char *geometryShaderFilename, const char *fragmentShaderFilename, bool isSeparable  ) {
    _initialize();
    mRegisterShaderProgram(vertexShaderFilename, "", "", geometryShaderFilename, fragmentShaderFilename, isSeparable);
}

[[maybe_unused]]
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

inline bool CSCI441::ShaderProgram::mRegisterShaderProgram(const char *vertexShaderFilename, const char *tessellationControlShaderFilename, const char *tessellationEvaluationShaderFilename, const char *geometryShaderFilename, const char *fragmentShaderFilename, const bool isSeparable ) {
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

    if(strcmp(tessellationControlShaderFilename, "" ) != 0 ) {
        if( sDEBUG ) printf("[INFO]: | Tess Control Shader: %33s |\n", tessellationControlShaderFilename );
        if( major < 4 ) {
            printf( "[ERROR]:|   TESSELLATION SHADER NOT SUPPORTED!! UPGRADE TO v4.0+ |\n" );
            mTessellationControlShaderHandle = 0;
        } else {
            mTessellationControlShaderHandle = CSCI441_INTERNAL::ShaderUtils::compileShader(tessellationControlShaderFilename, GL_TESS_CONTROL_SHADER );
        }
    } else {
        mTessellationControlShaderHandle = 0;
    }

    if(strcmp(tessellationEvaluationShaderFilename, "" ) != 0 ) {
        if( sDEBUG ) printf("[INFO]: | Tess Evaluation Shader: %30s |\n", tessellationEvaluationShaderFilename );
        if( major < 4 ) {
            printf( "[ERROR]:|   TESSELLATION SHADER NOT SUPPORTED!! UPGRADE TO v4.0+ |\n" );
            mTessellationEvaluationShaderHandle = 0;
        } else {
            mTessellationEvaluationShaderHandle = CSCI441_INTERNAL::ShaderUtils::compileShader(tessellationEvaluationShaderFilename, GL_TESS_EVALUATION_SHADER );
        }
    } else {
        mTessellationEvaluationShaderHandle = 0;
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
    if(mTessellationControlShaderHandle != 0 ) {
        glAttachShader(mShaderProgramHandle, mTessellationControlShaderHandle );
    }
    if(mTessellationEvaluationShaderHandle != 0 ) {
        glAttachShader(mShaderProgramHandle, mTessellationEvaluationShaderHandle );
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
    if(mTessellationControlShaderHandle != 0 ) {
        glDetachShader(mShaderProgramHandle, mTessellationControlShaderHandle );
        glDeleteShader(mTessellationControlShaderHandle );
    }
    if(mTessellationEvaluationShaderHandle != 0 ) {
        glDetachShader(mShaderProgramHandle, mTessellationEvaluationShaderHandle );
        glDeleteShader(mTessellationEvaluationShaderHandle );
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
                                                              mTessellationControlShaderHandle != 0,
                                                              mTessellationEvaluationShaderHandle != 0,
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

[[maybe_unused]]
inline GLubyte* CSCI441::ShaderProgram::getUniformBlockBuffer( const char *uniformBlockName ) const {
    GLubyte *blockBuffer;

    GLint blockSize = getUniformBlockSize( uniformBlockName );

    blockBuffer = (GLubyte*)malloc(blockSize);

    return blockBuffer;
}

[[maybe_unused]]
inline GLint* CSCI441::ShaderProgram::getUniformBlockOffsets( const char *uniformBlockName ) const {
    return getUniformBlockOffsets(getUniformBlockIndex(uniformBlockName));
}

[[maybe_unused]]
inline GLint* CSCI441::ShaderProgram::getUniformBlockOffsets( const char *uniformBlockName, const char *names[] ) const {
    return getUniformBlockOffsets(getUniformBlockIndex(uniformBlockName), names);
}

inline GLint* CSCI441::ShaderProgram::getUniformBlockOffsets(GLint uniformBlockIndex ) const {
    GLint numUniforms;
    glGetActiveUniformBlockiv(mShaderProgramHandle, uniformBlockIndex, GL_UNIFORM_BLOCK_ACTIVE_UNIFORMS, &numUniforms );

    auto indices = (GLuint*)malloc(numUniforms*sizeof(GLuint));
    glGetActiveUniformBlockiv(mShaderProgramHandle, uniformBlockIndex, GL_UNIFORM_BLOCK_ACTIVE_UNIFORM_INDICES, (GLint*)indices);

    auto offsets = (GLint*)malloc(numUniforms*sizeof(GLint));
    glGetActiveUniformsiv(mShaderProgramHandle, numUniforms, indices, GL_UNIFORM_OFFSET, offsets );
    return offsets;
}

inline GLint* CSCI441::ShaderProgram::getUniformBlockOffsets(GLint uniformBlockIndex, const char *names[] ) const {
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

[[maybe_unused]]
inline GLint CSCI441::ShaderProgram::getAttributeLocation( const char *attributeName ) const {
    auto attribIter = mpAttributeLocationsMap->find(attributeName);
    if(attribIter == mpAttributeLocationsMap->end() ) {
        fprintf(stderr, "[ERROR]: Could not find attribute \"%s\" for Shader Program %u\n", attributeName, mShaderProgramHandle );
        return -1;
    }
    return attribIter->second;
}

[[maybe_unused]]
inline GLuint CSCI441::ShaderProgram::getSubroutineIndex( GLenum shaderStage, const char *subroutineName ) const {
    GLuint subroutineIndex = glGetSubroutineIndex(mShaderProgramHandle, shaderStage, subroutineName );
    if( subroutineIndex == GL_INVALID_INDEX )
        fprintf(stderr, "[ERROR]: Could not find subroutine \"%s\" in %s for Shader Program %u\n", subroutineName, CSCI441_INTERNAL::ShaderUtils::GL_shader_type_to_string(shaderStage), mShaderProgramHandle );
    return subroutineIndex;
}

// images are opaque types that are not considered program resources
[[maybe_unused]]
inline GLint CSCI441::ShaderProgram::getImageBinding(const char* imageName) const {
    GLint imageLoc = getUniformLocation(imageName);

    if(imageLoc == -1) {
        fprintf(stderr, "[ERROR]: Could not find image \"%s\" for Shader Program %u\n", imageName, mShaderProgramHandle);
        return -1;
    }

    GLint bindingPoint;
    glGetUniformiv(mShaderProgramHandle, imageLoc, &bindingPoint);

    return bindingPoint;
}

[[maybe_unused]]
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

[[maybe_unused]]
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

[[maybe_unused]]
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

[[maybe_unused]]
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

[[maybe_unused]]
inline GLuint CSCI441::ShaderProgram::getNumUniforms() const {
    int numUniform = 0;
    glGetProgramiv(mShaderProgramHandle, GL_ACTIVE_UNIFORMS, &numUniform );
    return numUniform;
}

[[maybe_unused]]
inline GLuint CSCI441::ShaderProgram::getNumUniformBlocks() const {
    int numUniformBlocks = 0;
    glGetProgramiv(mShaderProgramHandle, GL_ACTIVE_UNIFORM_BLOCKS, &numUniformBlocks );
    return numUniformBlocks;
}

[[maybe_unused]]
inline GLuint CSCI441::ShaderProgram::getNumAttributes() const {
    int numAttr = 0;
    glGetProgramiv(mShaderProgramHandle, GL_ACTIVE_ATTRIBUTES, &numAttr );
    return numAttr;
}

inline GLuint CSCI441::ShaderProgram::getShaderProgramHandle() const {
    return mShaderProgramHandle;
}

[[maybe_unused]]
inline void CSCI441::ShaderProgram::useProgram() const {
    glUseProgram(mShaderProgramHandle );
}

[[maybe_unused]]
inline void CSCI441::ShaderProgram::setProgramUniform( const char *uniformName, GLfloat v0 ) const  {
    auto uniformIter = mpUniformLocationsMap->find(uniformName);
    if(uniformIter != mpUniformLocationsMap->end()) {
        glProgramUniform1f(mShaderProgramHandle, uniformIter->second, v0 );
    } else {
        fprintf(stderr, "[ERROR]: Could not find uniform \"%s\" for Shader Program %u\n", uniformName, mShaderProgramHandle);
    }
}

[[maybe_unused]]
inline void CSCI441::ShaderProgram::setProgramUniform( const char *uniformName, GLfloat v0, GLfloat v1 ) const {
    auto uniformIter = mpUniformLocationsMap->find(uniformName);
    if(uniformIter != mpUniformLocationsMap->end()) {
        glProgramUniform2f(mShaderProgramHandle, uniformIter->second, v0, v1 );
    } else {
        fprintf(stderr, "[ERROR]: Could not find uniform \"%s\" for Shader Program %u\n", uniformName, mShaderProgramHandle);
    }
}

[[maybe_unused]]
inline void CSCI441::ShaderProgram::setProgramUniform( const char *uniformName, glm::vec2 value ) const {
    setProgramUniform( uniformName, 2, 1, &value[0] );
}

[[maybe_unused]]
inline void CSCI441::ShaderProgram::setProgramUniform( const char *uniformName, GLfloat v0, GLfloat v1, GLfloat v2 ) const {
    auto uniformIter = mpUniformLocationsMap->find(uniformName);
    if(uniformIter != mpUniformLocationsMap->end()) {
        glProgramUniform3f(mShaderProgramHandle, uniformIter->second, v0, v1, v2 );
    } else {
        fprintf(stderr, "[ERROR]: Could not find uniform \"%s\" for Shader Program %u\n", uniformName, mShaderProgramHandle);
    }
}

[[maybe_unused]]
inline void CSCI441::ShaderProgram::setProgramUniform( const char *uniformName, glm::vec3 value ) const {
    setProgramUniform( uniformName, 3, 1, &value[0] );
}

[[maybe_unused]]
inline void CSCI441::ShaderProgram::setProgramUniform( const char *uniformName, GLfloat v0, GLfloat v1, GLfloat v2, GLfloat v3 ) const {
    auto uniformIter = mpUniformLocationsMap->find(uniformName);
    if(uniformIter != mpUniformLocationsMap->end()) {
        glProgramUniform4f(mShaderProgramHandle, uniformIter->second, v0, v1, v2, v3 );
    } else {
        fprintf(stderr, "[ERROR]: Could not find uniform \"%s\" for Shader Program %u\n", uniformName, mShaderProgramHandle);
    }
}

[[maybe_unused]]
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

[[maybe_unused]]
inline void CSCI441::ShaderProgram::setProgramUniform( const char *uniformName, GLint v0 ) const {
    auto uniformIter = mpUniformLocationsMap->find(uniformName);
    if(uniformIter != mpUniformLocationsMap->end()) {
        glProgramUniform1i(mShaderProgramHandle, uniformIter->second, v0 );
    } else {
        fprintf(stderr, "[ERROR]: Could not find uniform \"%s\" for Shader Program %u\n", uniformName, mShaderProgramHandle);
    }
}

[[maybe_unused]]
inline void CSCI441::ShaderProgram::setProgramUniform( const char *uniformName, GLint v0, GLint v1 ) const {
    auto uniformIter = mpUniformLocationsMap->find(uniformName);
    if(uniformIter != mpUniformLocationsMap->end()) {
        glProgramUniform2i(mShaderProgramHandle, uniformIter->second, v0, v1 );
    } else {
        fprintf(stderr, "[ERROR]: Could not find uniform \"%s\" for Shader Program %u\n", uniformName, mShaderProgramHandle);
    }
}

[[maybe_unused]]
inline void CSCI441::ShaderProgram::setProgramUniform(const char* uniformName, glm::ivec2 value) const {
    auto uniformIter = mpUniformLocationsMap->find(uniformName);
    if(uniformIter != mpUniformLocationsMap->end()) {
        glProgramUniform2iv(mShaderProgramHandle, uniformIter->second, 1, &value[0] );
    } else {
        fprintf(stderr, "[ERROR]: Could not find uniform \"%s\" for Shader Program %u\n", uniformName, mShaderProgramHandle);
    }
}

[[maybe_unused]]
inline void CSCI441::ShaderProgram::setProgramUniform( const char *uniformName, GLint v0, GLint v1, GLint v2 ) const {
    auto uniformIter = mpUniformLocationsMap->find(uniformName);
    if(uniformIter != mpUniformLocationsMap->end()) {
        glProgramUniform3i(mShaderProgramHandle, uniformIter->second, v0, v1, v2 );
    } else {
        fprintf(stderr, "[ERROR]: Could not find uniform \"%s\" for Shader Program %u\n", uniformName, mShaderProgramHandle);
    }
}

[[maybe_unused]]
inline void CSCI441::ShaderProgram::setProgramUniform(const char* uniformName, glm::ivec3 value) const {
    auto uniformIter = mpUniformLocationsMap->find(uniformName);
    if(uniformIter != mpUniformLocationsMap->end()) {
        glProgramUniform3iv(mShaderProgramHandle, uniformIter->second, 1, &value[0] );
    } else {
        fprintf(stderr, "[ERROR]: Could not find uniform \"%s\" for Shader Program %u\n", uniformName, mShaderProgramHandle);
    }
}

[[maybe_unused]]
inline void CSCI441::ShaderProgram::setProgramUniform( const char *uniformName, GLint v0, GLint v1, GLint v2, GLint v3 ) const {
    auto uniformIter = mpUniformLocationsMap->find(uniformName);
    if(uniformIter != mpUniformLocationsMap->end()) {
        glProgramUniform4i(mShaderProgramHandle, uniformIter->second, v0, v1, v2, v3 );
    } else {
        fprintf(stderr, "[ERROR]: Could not find uniform \"%s\" for Shader Program %u\n", uniformName, mShaderProgramHandle);
    }
}

[[maybe_unused]]
inline void CSCI441::ShaderProgram::setProgramUniform(const char* uniformName, glm::ivec4 value) const {
    auto uniformIter = mpUniformLocationsMap->find(uniformName);
    if(uniformIter != mpUniformLocationsMap->end()) {
        glProgramUniform4iv(mShaderProgramHandle, uniformIter->second, 1, &value[0] );
    } else {
        fprintf(stderr, "[ERROR]: Could not find uniform \"%s\" for Shader Program %u\n", uniformName, mShaderProgramHandle);
    }
}

[[maybe_unused]]
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

[[maybe_unused]]
inline void CSCI441::ShaderProgram::setProgramUniform( const char *uniformName, GLuint v0 ) const {
    auto uniformIter = mpUniformLocationsMap->find(uniformName);
    if(uniformIter != mpUniformLocationsMap->end()) {
        glProgramUniform1ui(mShaderProgramHandle, uniformIter->second, v0 );
    } else {
        fprintf(stderr, "[ERROR]: Could not find uniform \"%s\" for Shader Program %u\n", uniformName, mShaderProgramHandle);
    }
}

[[maybe_unused]]
inline void CSCI441::ShaderProgram::setProgramUniform( const char *uniformName, GLuint v0, GLuint v1 ) const {
    auto uniformIter = mpUniformLocationsMap->find(uniformName);
    if(uniformIter != mpUniformLocationsMap->end()) {
        glProgramUniform2ui(mShaderProgramHandle, uniformIter->second, v0, v1 );
    } else {
        fprintf(stderr, "[ERROR]: Could not find uniform \"%s\" for Shader Program %u\n", uniformName, mShaderProgramHandle);
    }
}

[[maybe_unused]]
inline void CSCI441::ShaderProgram::setProgramUniform(const char* uniformName, glm::uvec2 value) const {
    auto uniformIter = mpUniformLocationsMap->find(uniformName);
    if(uniformIter != mpUniformLocationsMap->end()) {
        glProgramUniform2uiv(mShaderProgramHandle, uniformIter->second, 1, &value[0] );
    } else {
        fprintf(stderr, "[ERROR]: Could not find uniform \"%s\" for Shader Program %u\n", uniformName, mShaderProgramHandle);
    }
}

[[maybe_unused]]
inline void CSCI441::ShaderProgram::setProgramUniform( const char *uniformName, GLuint v0, GLuint v1, GLuint v2 ) const {
    auto uniformIter = mpUniformLocationsMap->find(uniformName);
    if(uniformIter != mpUniformLocationsMap->end()) {
        glProgramUniform3ui(mShaderProgramHandle, uniformIter->second, v0, v1, v2 );
    } else {
        fprintf(stderr, "[ERROR]: Could not find uniform \"%s\" for Shader Program %u\n", uniformName, mShaderProgramHandle);
    }
}

[[maybe_unused]]
inline void CSCI441::ShaderProgram::setProgramUniform(const char* uniformName, glm::uvec3 value) const {
    auto uniformIter = mpUniformLocationsMap->find(uniformName);
    if(uniformIter != mpUniformLocationsMap->end()) {
        glProgramUniform3uiv(mShaderProgramHandle, uniformIter->second, 1, &value[0] );
    } else {
        fprintf(stderr, "[ERROR]: Could not find uniform \"%s\" for Shader Program %u\n", uniformName, mShaderProgramHandle);
    }
}

[[maybe_unused]]
inline void CSCI441::ShaderProgram::setProgramUniform( const char *uniformName, GLuint v0, GLuint v1, GLuint v2, GLuint v3 ) const {
    auto uniformIter = mpUniformLocationsMap->find(uniformName);
    if(uniformIter != mpUniformLocationsMap->end()) {
        glProgramUniform4ui(mShaderProgramHandle, uniformIter->second, v0, v1, v2, v3 );
    } else {
        fprintf(stderr, "[ERROR]: Could not find uniform \"%s\" for Shader Program %u\n", uniformName, mShaderProgramHandle);
    }
}

[[maybe_unused]]
inline void CSCI441::ShaderProgram::setProgramUniform(const char* uniformName, glm::uvec4 value) const {
    auto uniformIter = mpUniformLocationsMap->find(uniformName);
    if(uniformIter != mpUniformLocationsMap->end()) {
        glProgramUniform4uiv(mShaderProgramHandle, uniformIter->second, 1, &value[0] );
    } else {
        fprintf(stderr, "[ERROR]: Could not find uniform \"%s\" for Shader Program %u\n", uniformName, mShaderProgramHandle);
    }
}

[[maybe_unused]]
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

[[maybe_unused]]
inline void CSCI441::ShaderProgram::setProgramUniform( const char *uniformName, glm::mat2 mtx ) const {
    auto uniformIter = mpUniformLocationsMap->find(uniformName);
    if(uniformIter != mpUniformLocationsMap->end()) {
        glProgramUniformMatrix2fv(mShaderProgramHandle, uniformIter->second, 1, GL_FALSE, &mtx[0][0] );
    } else {
        fprintf(stderr, "[ERROR]: Could not find uniform \"%s\" for Shader Program %u\n", uniformName, mShaderProgramHandle);
    }
}

[[maybe_unused]]
inline void CSCI441::ShaderProgram::setProgramUniform( const char *uniformName, glm::mat3 mtx ) const {
    auto uniformIter = mpUniformLocationsMap->find(uniformName);
    if(uniformIter != mpUniformLocationsMap->end()) {
        glProgramUniformMatrix3fv(mShaderProgramHandle, uniformIter->second, 1, GL_FALSE, &mtx[0][0] );
    } else {
        fprintf(stderr, "[ERROR]: Could not find uniform \"%s\" for Shader Program %u\n", uniformName, mShaderProgramHandle);
    }
}

[[maybe_unused]]
inline void CSCI441::ShaderProgram::setProgramUniform( const char *uniformName, glm::mat4 mtx ) const {
    auto uniformIter = mpUniformLocationsMap->find(uniformName);
    if(uniformIter != mpUniformLocationsMap->end()) {
        glProgramUniformMatrix4fv(mShaderProgramHandle, uniformIter->second, 1, GL_FALSE, &mtx[0][0] );
    } else {
        fprintf(stderr, "[ERROR]: Could not find uniform \"%s\" for Shader Program %u\n", uniformName, mShaderProgramHandle);
    }
}

[[maybe_unused]]
inline void CSCI441::ShaderProgram::setProgramUniform( const char *uniformName, glm::mat2x3 mtx ) const {
    auto uniformIter = mpUniformLocationsMap->find(uniformName);
    if(uniformIter != mpUniformLocationsMap->end()) {
        glProgramUniformMatrix2x3fv(mShaderProgramHandle, uniformIter->second, 1, GL_FALSE, &mtx[0][0] );
    } else {
        fprintf(stderr, "[ERROR]: Could not find uniform \"%s\" for Shader Program %u\n", uniformName, mShaderProgramHandle);
    }
}

[[maybe_unused]]
inline void CSCI441::ShaderProgram::setProgramUniform( const char *uniformName, glm::mat3x2 mtx ) const {
    auto uniformIter = mpUniformLocationsMap->find(uniformName);
    if(uniformIter != mpUniformLocationsMap->end()) {
        glProgramUniformMatrix3x2fv(mShaderProgramHandle, uniformIter->second, 1, GL_FALSE, &mtx[0][0] );
    } else {
        fprintf(stderr, "[ERROR]: Could not find uniform \"%s\" for Shader Program %u\n", uniformName, mShaderProgramHandle);
    }
}

[[maybe_unused]]
inline void CSCI441::ShaderProgram::setProgramUniform( const char *uniformName, glm::mat2x4 mtx ) const {
    auto uniformIter = mpUniformLocationsMap->find(uniformName);
    if(uniformIter != mpUniformLocationsMap->end()) {
        glProgramUniformMatrix2x4fv(mShaderProgramHandle, uniformIter->second, 1, GL_FALSE, &mtx[0][0] );
    } else {
        fprintf(stderr, "[ERROR]: Could not find uniform \"%s\" for Shader Program %u\n", uniformName, mShaderProgramHandle);
    }
}

[[maybe_unused]]
inline void CSCI441::ShaderProgram::setProgramUniform( const char *uniformName, glm::mat4x2 mtx ) const {
    auto uniformIter = mpUniformLocationsMap->find(uniformName);
    if(uniformIter != mpUniformLocationsMap->end()) {
        glProgramUniformMatrix4x2fv(mShaderProgramHandle, uniformIter->second, 1, GL_FALSE, &mtx[0][0] );
    } else {
        fprintf(stderr, "[ERROR]: Could not find uniform \"%s\" for Shader Program %u\n", uniformName, mShaderProgramHandle);
    }
}

[[maybe_unused]]
inline void CSCI441::ShaderProgram::setProgramUniform( const char *uniformName, glm::mat3x4 mtx ) const {
    auto uniformIter = mpUniformLocationsMap->find(uniformName);
    if(uniformIter != mpUniformLocationsMap->end()) {
        glProgramUniformMatrix3x4fv(mShaderProgramHandle, uniformIter->second, 1, GL_FALSE, &mtx[0][0] );
    } else {
        fprintf(stderr, "[ERROR]: Could not find uniform \"%s\" for Shader Program %u\n", uniformName, mShaderProgramHandle);
    }
}

[[maybe_unused]]
inline void CSCI441::ShaderProgram::setProgramUniform( const char *uniformName, glm::mat4x3 mtx ) const {
    auto uniformIter = mpUniformLocationsMap->find(uniformName);
    if(uniformIter != mpUniformLocationsMap->end()) {
        glProgramUniformMatrix4x3fv(mShaderProgramHandle, uniformIter->second, 1, GL_FALSE, &mtx[0][0] );
    } else {
        fprintf(stderr, "[ERROR]: Could not find uniform \"%s\" for Shader Program %u\n", uniformName, mShaderProgramHandle);
    }
}

[[maybe_unused]]
inline void CSCI441::ShaderProgram::setProgramUniform( GLint uniformLocation, GLfloat v0 ) const {
    glProgramUniform1f(mShaderProgramHandle, uniformLocation, v0 );
}

[[maybe_unused]]
inline void CSCI441::ShaderProgram::setProgramUniform( GLint uniformLocation, GLfloat v0, GLfloat v1 ) const {
    glProgramUniform2f(mShaderProgramHandle, uniformLocation, v0, v1 );
}

[[maybe_unused]]
inline void CSCI441::ShaderProgram::setProgramUniform( GLint uniformLocation, glm::vec2 value ) const {
    setProgramUniform( uniformLocation, 2, 1, &value[0] );
}

[[maybe_unused]]
inline void CSCI441::ShaderProgram::setProgramUniform( GLint uniformLocation, GLfloat v0, GLfloat v1, GLfloat v2 ) const {
    glProgramUniform3f(mShaderProgramHandle, uniformLocation, v0, v1, v2 );
}

[[maybe_unused]]
inline void CSCI441::ShaderProgram::setProgramUniform( GLint uniformLocation, glm::vec3 value ) const {
    setProgramUniform( uniformLocation, 3, 1, &value[0] );
}

[[maybe_unused]]
inline void CSCI441::ShaderProgram::setProgramUniform( GLint uniformLocation, GLfloat v0, GLfloat v1, GLfloat v2, GLfloat v3 ) const {
    glProgramUniform4f(mShaderProgramHandle, uniformLocation, v0, v1, v2, v3 );
}

[[maybe_unused]]
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

[[maybe_unused]]
inline void CSCI441::ShaderProgram::setProgramUniform( GLint uniformLocation, GLint v0 ) const {
    glProgramUniform1i(mShaderProgramHandle, uniformLocation, v0 );
}

[[maybe_unused]]
inline void CSCI441::ShaderProgram::setProgramUniform( GLint uniformLocation, GLint v0, GLint v1 ) const {
    glProgramUniform2i(mShaderProgramHandle, uniformLocation, v0, v1 );
}

[[maybe_unused]]
inline void CSCI441::ShaderProgram::setProgramUniform(GLint uniformLocation, glm::ivec2 value) const {
    setProgramUniform(uniformLocation, 2, 1, &value[0]);
}

[[maybe_unused]]
inline void CSCI441::ShaderProgram::setProgramUniform( GLint uniformLocation, GLint v0, GLint v1, GLint v2 ) const {
    glProgramUniform3i(mShaderProgramHandle, uniformLocation, v0, v1, v2 );
}

[[maybe_unused]]
inline void CSCI441::ShaderProgram::setProgramUniform(GLint uniformLocation, glm::ivec3 value) const {
    setProgramUniform(uniformLocation, 3, 1, &value[0]);
}

[[maybe_unused]]
inline void CSCI441::ShaderProgram::setProgramUniform( GLint uniformLocation, GLint v0, GLint v1, GLint v2, GLint v3 ) const {
    glProgramUniform4i(mShaderProgramHandle, uniformLocation, v0, v1, v2, v3 );
}

[[maybe_unused]]
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

[[maybe_unused]]
inline void CSCI441::ShaderProgram::setProgramUniform( GLint uniformLocation, GLuint v0 ) const {
    glProgramUniform1ui(mShaderProgramHandle, uniformLocation, v0 );
}

[[maybe_unused]]
inline void CSCI441::ShaderProgram::setProgramUniform( GLint uniformLocation, GLuint v0, GLuint v1 ) const {
    glProgramUniform2ui(mShaderProgramHandle, uniformLocation, v0, v1 );
}

[[maybe_unused]]
inline void CSCI441::ShaderProgram::setProgramUniform(GLint uniformLocation, glm::uvec2 value) const {
    setProgramUniform(uniformLocation, 2, 1, &value[0]);
}

[[maybe_unused]]
inline void CSCI441::ShaderProgram::setProgramUniform( GLint uniformLocation, GLuint v0, GLuint v1, GLuint v2 ) const {
    glProgramUniform3ui(mShaderProgramHandle, uniformLocation, v0, v1, v2 );
}

[[maybe_unused]]
inline void CSCI441::ShaderProgram::setProgramUniform(GLint uniformLocation, glm::uvec3 value) const {
    setProgramUniform(uniformLocation, 3, 1, &value[0]);
}

[[maybe_unused]]
inline void CSCI441::ShaderProgram::setProgramUniform( GLint uniformLocation, GLuint v0, GLuint v1, GLuint v2, GLuint v3 ) const {
    glProgramUniform4ui(mShaderProgramHandle, uniformLocation, v0, v1, v2, v3 );
}

[[maybe_unused]]
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

[[maybe_unused]]
inline void CSCI441::ShaderProgram::setProgramUniform( GLint uniformLocation, glm::mat2 mtx ) const {
    glProgramUniformMatrix2fv(mShaderProgramHandle, uniformLocation, 1, GL_FALSE, &mtx[0][0] );
}

[[maybe_unused]]
inline void CSCI441::ShaderProgram::setProgramUniform( GLint uniformLocation, glm::mat3 mtx ) const {
    glProgramUniformMatrix3fv(mShaderProgramHandle, uniformLocation, 1, GL_FALSE, &mtx[0][0] );
}

[[maybe_unused]]
inline void CSCI441::ShaderProgram::setProgramUniform( GLint uniformLocation, glm::mat4 mtx ) const {
    glProgramUniformMatrix4fv(mShaderProgramHandle, uniformLocation, 1, GL_FALSE, &mtx[0][0] );
}

[[maybe_unused]]
inline void CSCI441::ShaderProgram::setProgramUniform( GLint uniformLocation, glm::mat2x3 mtx ) const {
    glProgramUniformMatrix2x3fv(mShaderProgramHandle, uniformLocation, 1, GL_FALSE, &mtx[0][0] );
}

[[maybe_unused]]
inline void CSCI441::ShaderProgram::setProgramUniform( GLint uniformLocation, glm::mat3x2 mtx ) const {
    glProgramUniformMatrix3x2fv(mShaderProgramHandle, uniformLocation, 1, GL_FALSE, &mtx[0][0] );
}

[[maybe_unused]]
inline void CSCI441::ShaderProgram::setProgramUniform( GLint uniformLocation, glm::mat2x4 mtx ) const {
    glProgramUniformMatrix2x4fv(mShaderProgramHandle, uniformLocation, 1, GL_FALSE, &mtx[0][0] );
}

[[maybe_unused]]
inline void CSCI441::ShaderProgram::setProgramUniform( GLint uniformLocation, glm::mat4x2 mtx ) const {
    glProgramUniformMatrix4x2fv(mShaderProgramHandle, uniformLocation, 1, GL_FALSE, &mtx[0][0] );
}

[[maybe_unused]]
inline void CSCI441::ShaderProgram::setProgramUniform( GLint uniformLocation, glm::mat3x4 mtx ) const {
    glProgramUniformMatrix3x4fv(mShaderProgramHandle, uniformLocation, 1, GL_FALSE, &mtx[0][0] );
}

[[maybe_unused]]
inline void CSCI441::ShaderProgram::setProgramUniform( GLint uniformLocation, glm::mat4x3 mtx ) const {
    glProgramUniformMatrix4x3fv(mShaderProgramHandle, uniformLocation, 1, GL_FALSE, &mtx[0][0] );
}

[[maybe_unused]]
inline GLbitfield CSCI441::ShaderProgram::getProgramStages() const {
    GLbitfield shaderBits = 0;
    if( mVertexShaderHandle != 0                 ) shaderBits |= GL_VERTEX_SHADER_BIT;
    if( mTessellationControlShaderHandle != 0    ) shaderBits |= GL_TESS_CONTROL_SHADER_BIT;
    if( mTessellationEvaluationShaderHandle != 0 ) shaderBits |= GL_TESS_EVALUATION_SHADER_BIT;
    if( mGeometryShaderHandle != 0               ) shaderBits |= GL_GEOMETRY_SHADER_BIT;
    if( mFragmentShaderHandle != 0               ) shaderBits |= GL_FRAGMENT_SHADER_BIT;
    return shaderBits;
}

inline CSCI441::ShaderProgram::ShaderProgram() {
    _initialize();
}

inline void CSCI441::ShaderProgram::_initialize() {
    mVertexShaderHandle = 0;
    mTessellationControlShaderHandle = 0;
    mTessellationEvaluationShaderHandle = 0;
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

    // get the info log for the vertex/tessellation/geometry/fragment/compute shader
    glGetProgramInfoLog(mShaderProgramHandle, maxLength, &infoLogLength, infoLog );

    if(infoLogLength > 0 ) {
        // print info to terminal
        if( sDEBUG ) printf("[INFO]: Program Handle %d Delete Status %s: %s\n", mShaderProgramHandle, (status == GL_TRUE ? "Success" : " Error"), infoLog );
    }

    delete mpUniformLocationsMap;
    delete mpAttributeLocationsMap;
}

inline bool CSCI441::ShaderProgram::writeShaderProgramBinaryToFile(const char* BINARY_FILE_NAME) const {
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
