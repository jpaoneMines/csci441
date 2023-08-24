/** @file UniformBufferObject.hpp
 * @brief Helper functions to work with Uniform Buffer Objects
 * @author Dr. Jeffrey Paone
 *
 * @copyright MIT License Copyright (c) 2021 Dr. Jeffrey Paone
 *
 *	These functions, classes, and constants help minimize common
 *	code that needs to be written.
 */

#ifndef CSCI441_UNIFORM_BUFFER_OBJECT_HPP
#define CSCI441_UNIFORM_BUFFER_OBJECT_HPP

#include "ShaderProgram.hpp"

#include <GL/glew.h>

#include <cstdio>
#include <string>
#include <vector>

//******************************************************************************

namespace CSCI441 {

    /**
     * @class UniformBufferObject
     * @brief Storage of UBO related data
     */
    class [[maybe_unused]] UniformBufferObject final {
    public:
        /**
         * @note must use `UniformBufferObject(const char*, std::initializer_list<const char*>
         */
        UniformBufferObject() = delete;

        /**
         * @brief Initializes the UniformBufferObject object
         * @param UNIFORM_BLOCK_NAME name of the uniform block
         * @param uniformNamesList list of names that makeup the uniform block components
         */
        [[maybe_unused]] UniformBufferObject(const char* UNIFORM_BLOCK_NAME, std::initializer_list<const char*> uniformNamesList);
        /**
         * @brief Deletes the UBO from the GPU and frees all memory on the CPU
         */
        ~UniformBufferObject();

        /**
         * @brief creates the UBO and allocates memory on both the CPU & GPU.  binds the UBO and the
         * uniform block for the provided ShaderProgram to the same binding point.
         * @param shaderProgram ShaderProgram object that utilizes the uniformBlock
         * @param bindingPoint Binding point to bind the UBO and ShaderProgram Uniform Block to
         */
        [[maybe_unused]] void setupWithShaderProgram( ShaderProgram *shaderProgram, GLuint bindingPoint );

        /**
         * @brief copies the value pointed to by addr to the corresponding location within the UBO as denoted by the offset
         * @param offset UBO offset to copy value to
         * @param addr starting address of source to copy from
         * @param len length of buffer to copy
         */
        [[maybe_unused]] void copyToOffset( unsigned int offset, void* addr, size_t len );

        /**
         * @brief copies the value pointed to by addr to the corresponding location within the UBO as denoted by the uniform name
         * @param uniformName name of the uniform within the block to copy value to
         * @param addr starting address of source to copy from
         * @param len length of buffer to copy
         */
        [[maybe_unused]] void copyToBuffer( const char* UNIFORM_NAME, void* addr, size_t len );

        /**
         * @brief binds UBO object to UBO buffer
         */
        void bindBuffer() const;

        /**
         * @brief transfers UBO data to UBO buffer
         */
        [[maybe_unused]] void bufferSubData() const;

    private:
        char* _blockName;
        std::vector<char*> _uniformNames;
        GLint _blockSize;
        GLubyte* _buffer;
        GLuint _numUniforms;
        GLuint* _uniformIndices;
        GLint* _uniformOffsets;
        GLuint _ubod;
        GLuint _bindingPoint;
    };
}

//******************************************************************************

[[maybe_unused]]
inline CSCI441::UniformBufferObject::UniformBufferObject(const char* UNIFORM_BLOCK_NAME, std::initializer_list<const char*> uniformNamesList) {
    _blockName = (char*)UNIFORM_BLOCK_NAME;

    _numUniforms = uniformNamesList.size();

    for(const auto &uniformName : uniformNamesList ) {
        char* un = (char*)malloc(strlen(uniformName) * sizeof(char));
        strcpy(un, uniformName);
        _uniformNames.push_back(un);
    }

    _uniformIndices = (GLuint*)malloc(_numUniforms * sizeof(GLuint));
    _uniformOffsets = (GLint*)malloc(_numUniforms * sizeof(GLint));

    _blockSize = 0;
    _buffer = nullptr;
    _bindingPoint = 0;
    _ubod = 0;
}

inline CSCI441::UniformBufferObject::~UniformBufferObject() {
    glDeleteBuffers(1, &_ubod);

    for(GLuint i = 0; i < _numUniforms; i++) {
        free(_uniformNames[i]);
    }
    free(_uniformIndices);
    free(_uniformOffsets);
    free(_buffer);
}

[[maybe_unused]]
inline void CSCI441::UniformBufferObject::setupWithShaderProgram( ShaderProgram *shaderProgram, GLuint bindingPoint ) {
    _blockSize = shaderProgram->getUniformBlockSize( _blockName );
    _buffer = (GLubyte*)malloc( _blockSize );

    glGetUniformIndices(shaderProgram->getShaderProgramHandle(), _numUniforms, &_uniformNames[0], _uniformIndices);
    glGetActiveUniformsiv(shaderProgram->getShaderProgramHandle(), _numUniforms, _uniformIndices, GL_UNIFORM_OFFSET, _uniformOffsets);

    glGenBuffers(1, &_ubod);
    bindBuffer();
    glBufferData(GL_UNIFORM_BUFFER, _blockSize, nullptr, GL_DYNAMIC_DRAW);

    _bindingPoint = bindingPoint;
    glBindBufferBase(GL_UNIFORM_BUFFER, _bindingPoint, _ubod);
    shaderProgram->setUniformBlockBinding(_blockName, _bindingPoint);
}

[[maybe_unused]]
inline void CSCI441::UniformBufferObject::copyToOffset( unsigned int offset, void* addr, size_t len ) {
    if(offset < _numUniforms) {
        memcpy(_buffer + _uniformOffsets[offset], addr, len);
    } else {
        fprintf(stderr, "[ERROR]: Offset %d exceeds size of Uniform Block %s which is %d\n", offset, _blockName, _numUniforms);
    }
}

[[maybe_unused]]
inline void CSCI441::UniformBufferObject::copyToBuffer( const char* UNIFORM_NAME, void* addr, size_t len ) {
    bool found = false;
    for(GLuint i = 0; i < _numUniforms; i++) {
        if( strcmp(_uniformNames[i], UNIFORM_NAME) == 0 ) {
            memcpy( _buffer + _uniformOffsets[i], addr, len );
            found = true;
            break;
        }
    }
    if(!found) {
        fprintf(stderr, "[ERROR]: Uniform Name \"%s\" not found within Uniform Block \"%s\"\n", UNIFORM_NAME, _blockName);
    }
}

inline void CSCI441::UniformBufferObject::bindBuffer() const {
    glBindBuffer(GL_UNIFORM_BUFFER, _ubod);
}

[[maybe_unused]]
inline void CSCI441::UniformBufferObject::bufferSubData() const {
    glBufferSubData(GL_UNIFORM_BUFFER, 0, _blockSize, _buffer);
}

#endif //CSCI441_UNIFORM_BUFFER_OBJECT_HPP
