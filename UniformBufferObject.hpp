//
// Created by Jeffrey Paone on 2/11/21.
//

#ifndef __CSCI441_UNIFORMBUFFEROBJECT_H__
#define __CSCI441_UNIFORMBUFFEROBJECT_H__

#include <GL/glew.h>

#include <string>

////////////////////////////////////////////////////////////////////////////////

/** @namespace CSCI441
  * @brief CSCI441 Helper Functions for OpenGL
	*/
namespace CSCI441 {
    /** @struct UniformBufferObject
        * @desc Storage of UBO related data
        */
    class UniformBufferObject {
    public:
        /**
         * @desc Initializes the UniformBufferObject object
         * @param UNIFORM_BLOCK_NAME name of the uniform block
         * @param uniformNamesList list of names that makeup the uniform block components
         */
        UniformBufferObject(const char* UNIFORM_BLOCK_NAME, std::initializer_list<const char*> uniformNamesList) {
            _blockName = (char*)UNIFORM_BLOCK_NAME;

            _numUniforms = uniformNamesList.size();

            _uniformNames = (char**)malloc(_numUniforms * sizeof(char*));

            int currPos = 0;
            std::initializer_list<char*>::iterator iter;
            for(const auto &uniformName : uniformNamesList ) {
                _uniformNames[currPos] = (char*)malloc(strlen(uniformName) * sizeof(char));
                strcpy(_uniformNames[currPos++], uniformName);
            }

            _uniformIndices = (GLuint*)malloc(_numUniforms * sizeof(GLuint));
            _uniformOffsets = (GLint*)malloc(_numUniforms * sizeof(GLint));
        }
        /**
         * @desc Deletes the UBO from the GPU and frees all memory on the CPU
         */
        ~UniformBufferObject() {
            glDeleteBuffers(1, &_ubod);

            for(GLuint i = 0; i < _numUniforms; i++) {
                free(_uniformNames[i]);
            }
            free(_uniformNames);
            free(_uniformIndices);
            free(_uniformOffsets);
            free(_buffer);
        }

        /**
         * @desc creates the UBO and allocates memory on both the CPU & GPU.  binds the UBO and the
         * uniform block for the provided ShaderProgram to the same binding point.
         * @param shaderProgram ShaderProgram object that utilizes the uniformBlock
         * @param bindingPoint Binding point to bind the UBO and ShaderProgram Uniform Block to
         */
        void setupWithShaderProgram( ShaderProgram *shaderProgram, GLuint bindingPoint ) {
            _blockSize = shaderProgram->getUniformBlockSize( _blockName );
            _buffer = (GLubyte*)malloc( _blockSize );

            glGetUniformIndices(shaderProgram->getShaderProgramHandle(), _numUniforms, _uniformNames, _uniformIndices);
            glGetActiveUniformsiv(shaderProgram->getShaderProgramHandle(), _numUniforms, _uniformIndices, GL_UNIFORM_OFFSET, _uniformOffsets);

            glGenBuffers(1, &_ubod);
            bindBuffer();
            glBufferData(GL_UNIFORM_BUFFER, _blockSize, nullptr, GL_DYNAMIC_DRAW);

            _bindingPoint = bindingPoint;
            glBindBufferBase(GL_UNIFORM_BUFFER, _bindingPoint, _ubod);
            shaderProgram->setUniformBlockBinding(_blockName, _bindingPoint);
        }

        void copyToOffset( unsigned int offset, void* addr, size_t len ) {
            memcpy( _buffer + _uniformOffsets[offset], addr, len );
        }

        void bindBuffer() {
            glBindBuffer(GL_UNIFORM_BUFFER, _ubod);
        }

        void bufferSubData() {
            glBufferSubData(GL_UNIFORM_BUFFER, 0, _blockSize, _buffer);
        }

    private:
        char* _blockName;
        char** _uniformNames;
        GLint _blockSize;
        GLubyte* _buffer;
        GLuint _numUniforms;
        GLuint* _uniformIndices;
        GLint* _uniformOffsets;
        GLuint _ubod;
        GLuint _bindingPoint;
    };
}

#endif //__CSCI441_UNIFORMBUFFEROBJECT_H__
