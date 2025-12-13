#ifndef CSCI441_FONT_UTILITY_HPP
#define CSCI441_FONT_UTILITY_HPP

#include "constants.h"
#include "Font.hpp"
#include "ShaderProgram.hpp"

#ifdef CSCI441_USE_GLEW
    #include <GL/glew.h>
#else
    #include <glad/gl.h>
#endif

#include <glm/vec3.hpp>
#include <glm/vec4.hpp>

#include <cstdlib>
#include <string>

//************************************************
// Outward Facing Utilities

namespace CSCI441 {
    /**
     * @brief Utility class to render text overlays on screen\n\n
     * Usage:\n
     * (1) During setup, call loadFont() to load a ttf font file\n
     * (2) Immediately prior to rendering, call bindFont() to load font context\n
     * (3) Subsequently call renderText() for every string to be rendered to screen\n
     * (4) During cleanup, call releaseFont() to deallocate font memory
     */
    namespace FontUtility {
        bool loadFont(const char* filename);
        void releaseFont();

        /**
         * @pre MUST call CSCI441::FontUtility::loadFont(const char*) prior to this call
         */
        void bindFont();
        void setColor(glm::vec3 color);
        void setColor(glm::vec4 color);
        void setFontSize(GLfloat scaleX, GLfloat scaleY);

        /**
         *
         * @param str
         * @param x
         * @param y
         * @pre MUST call CSCI441::FontUtility::bindFont() prior to this call
         */
        void renderText(const char* str, GLfloat x, GLfloat y);
    }
}

//************************************************
// Inward Facing Utilities

namespace CSCI441_INTERNAL {
    namespace FontUtility {
        static CSCI441::Font* currentFont = nullptr;
        static GLuint fontShader = 0;
        static GLint colorUniformLocation = -1;
        static bool loadFontShader();
    }
}

//************************************************
// Outward Facing Definitions

inline bool CSCI441::FontUtility::loadFont(const char * const filename) {
    if (CSCI441_INTERNAL::FontUtility::currentFont != nullptr) {
        delete CSCI441_INTERNAL::FontUtility::currentFont;
        CSCI441_INTERNAL::FontUtility::currentFont = nullptr;
    }

    bool success = true;

    if (CSCI441_INTERNAL::FontUtility::fontShader == 0) {
        success &= CSCI441_INTERNAL::FontUtility::loadFontShader();
    }

    CSCI441_INTERNAL::FontUtility::currentFont = new CSCI441::Font(filename);

    return success && CSCI441_INTERNAL::FontUtility::currentFont->isLoaded();;
}

inline void CSCI441::FontUtility::releaseFont() {
    glDeleteProgram(CSCI441_INTERNAL::FontUtility::fontShader);
    CSCI441_INTERNAL::FontUtility::fontShader = 0;

    delete CSCI441_INTERNAL::FontUtility::currentFont;
    CSCI441_INTERNAL::FontUtility::currentFont = nullptr;
}

inline void CSCI441::FontUtility::bindFont() {
    if (CSCI441_INTERNAL::FontUtility::fontShader != 0 && CSCI441_INTERNAL::FontUtility::currentFont != nullptr) {
        glUseProgram( CSCI441_INTERNAL::FontUtility::fontShader );
        CSCI441_INTERNAL::FontUtility::currentFont->bind();
    } else {
        fprintf(stderr, "[FontUtil | ERROR]: bindFont() called without loading a font.  Call loadFont() first\n");
    }
}

inline void CSCI441::FontUtility::setColor(const glm::vec3 color) {
    glm::vec4 colorA = glm::vec4(color, 1.0f);
    glProgramUniform4fv(CSCI441_INTERNAL::FontUtility::fontShader, CSCI441_INTERNAL::FontUtility::colorUniformLocation, 1, glm::value_ptr(colorA));
}

inline void CSCI441::FontUtility::setColor(const glm::vec4 color) {
    glProgramUniform4fv(CSCI441_INTERNAL::FontUtility::fontShader, CSCI441_INTERNAL::FontUtility::colorUniformLocation, 1, glm::value_ptr(color));
}

inline void CSCI441::FontUtility::setFontSize(const GLfloat scaleX, const GLfloat scaleY) {
    if (CSCI441_INTERNAL::FontUtility::currentFont != nullptr) {
        CSCI441_INTERNAL::FontUtility::currentFont->setScale(scaleX, scaleY);
    } else {
        fprintf(stderr, "[FontUtil | ERROR]: setFontSize() called without loading a font.  Call loadFont() first\n");
    }
}

inline void CSCI441::FontUtility::renderText(const char* str, const GLfloat x, const GLfloat y) {
    if (CSCI441_INTERNAL::FontUtility::currentFont != nullptr) {
        CSCI441_INTERNAL::FontUtility::currentFont->draw(str, x, y);
    } else {
        fprintf(stderr, "[FontUtil | ERROR]: renderText() called without loading a font.  Call loadFont() first and then bindFont()\n");
    }
}

//************************************************
// Inward Facing Definitions

inline bool CSCI441_INTERNAL::FontUtility::loadFontShader() {
    const std::string vertex_shader_src =
R"_(#version 410 core

layout(location = 0) in vec4 coord;

out vec2 vTexCoord;

void main() {
    gl_Position = vec4( coord.xy, 0.0f, 1.0f );
    vTexCoord = coord.zw;
})_";

    const std::string fragment_shader_src =
R"_(#version 410 core

uniform sampler2D tex;
uniform vec4 color;

in vec2 vTexCoord;

out vec4 fragColorOut;

void main() {
    fragColorOut = vec4(1.0, 1.0, 1.0, texture(tex, vTexCoord).r) * color;
}
)_";

    const char* vertexShaders[1] = { vertex_shader_src.c_str() };
    const char* fragmentShaders[1] = { fragment_shader_src.c_str() };

    fprintf(stdout, "[INFO]: /--------------------------------------------------------\\\n" );

    const GLuint vertexShaderHandle = glCreateShader( GL_VERTEX_SHADER );
    glShaderSource(vertexShaderHandle, 1, vertexShaders, nullptr);
    glCompileShader(vertexShaderHandle);
    ShaderUtils::printShaderLog(vertexShaderHandle);

    const GLuint fragmentShaderHandle = glCreateShader( GL_FRAGMENT_SHADER );
    glShaderSource(fragmentShaderHandle, 1, fragmentShaders, nullptr);
    glCompileShader(fragmentShaderHandle);
    ShaderUtils::printShaderLog(fragmentShaderHandle);

    fontShader = glCreateProgram();
    glAttachShader(fontShader, vertexShaderHandle);
    glAttachShader(fontShader, fragmentShaderHandle);
    glLinkProgram(fontShader);
    ShaderUtils::printProgramLog(fontShader);

    glDetachShader(fontShader, vertexShaderHandle);
    glDeleteShader(vertexShaderHandle);

    glDetachShader(fontShader, fragmentShaderHandle);
    glDeleteShader(fragmentShaderHandle);

    ShaderUtils::printShaderProgramInfo(fontShader, true, false, false, false, true, false, true);

    const GLint texUniformLocation = glGetUniformLocation(fontShader, "tex");
    colorUniformLocation     = glGetUniformLocation(fontShader, "color");

    glProgramUniform1i(fontShader, texUniformLocation, 0);
    constexpr glm::vec4 white(1.0f, 1.0f, 1.0f, 1.0f);
    glProgramUniform4fv(fontShader, colorUniformLocation, 1, glm::value_ptr(white));

    return fontShader != 0;

}

#endif//CSCI441_FONT_UTILITY_HPP