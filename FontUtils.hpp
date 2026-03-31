#ifndef CSCI441_FONT_UTILS_HPP
#define CSCI441_FONT_UTILS_HPP

#include "constants.h"
#include "Font.hpp"
#include "ShaderProgram.hpp"

#ifdef CSCI441_USE_GLEW
    #include <GL/glew.h>
#else
    #include <glad/gl.h>
#endif

#include <glm/vec2.hpp>
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
     * (4) During cleanup, call releaseFont() to deallocate font memory\n\n
     * To make placement of text within window easier, such that the (x, y) coordinate corresponds
     * to the pixel location, call setWindowSize() after loading the font (and anytime the window
     * size changes)..
     */
    namespace FontUtils {
        /**
         * @brief registers a TrueTypeFont file with a shader program to render text to screen
         * @param filename ttf font file to load
         * @return true if font file was successfully loaded AND internal font shader program successfully compiled
         */
        bool loadFont(const char* filename);
        /**
         * @brief deallocates CPU and GPU memory related to text rendering
         */
        void releaseFont();

        /**
         * @brief sets all necessary font contexts
         * @note binds VertexArray and GL_ARRAY_BUFFER
         * @note binds GL_TEXTURE_2D to GL_TEXTURE0
         * @note uses shader program
         * @pre MUST call CSCI441::FontUtility::loadFont(const char*) prior to this call
         */
        void bindFont();

        /**
         * @brief specify the color to render the text
         * @param color text color
         * @note sets alpha channel to 1.0
         */
        void setColor(glm::vec3 color);

        /**
         * @brief specify the color to render the text
         * @param color text color
         */
        void setColor(glm::vec4 color);

        /**
         * @brief store the size of the window
         * @param width window width
         * @param height window height
         * @note this allows CSCI441::FontUtils::renderText() to specify the (x, y) coordinate
         * in screen space.  The (x, y) coordinate then corresponds to the top left pixel to
         * begin drawing at.
         */
        void setWindowSize(GLint width, GLint height);
        /**
         * @brief store the size of the window
         * @param width window width
         * @param height window height
         * @note this allows CSCI441::FontUtils::renderText() to specify the (x, y) coordinate
         * in screen space.  The (x, y) coordinate then corresponds to the top left pixel to
         * begin drawing at.
         */
        void setWindowSize(GLfloat width, GLfloat height);

        /**
         * @brief set the amount to scale font when drawing
         * @param scaleX amount to scale font horizontally
         * @param scaleY amount to scale font vertically
         * @note values typically refer to inverse screen size, e.g. the size of each pixel
         */
        void setFontSize(GLfloat scaleX, GLfloat scaleY);

        /**
         * @brief draws the given text starting at the top left (x, y) coordinate specified
         * @param str text to render to screen
         * @param x x coordinate in screen space to place text within window (corresponds to left edge of text)
         * @param y y coordinate in screen space to place text within window (corresponds to top edge of text)
         * @pre MUST call CSCI441::FontUtility::bindFont() prior to this call
         * @note see CSCI441::FontUtils::setWindowSize() for help in specifying the
         * (x, y) coordinate
         * @note see CSCI441::FontUtility::setColor()  to change the displayed color
         */
        void renderText(const char* str, GLfloat x, GLfloat y);
    }
}

//************************************************
// Inward Facing Utilities

namespace CSCI441_INTERNAL {
    namespace FontUtils {
        bool loadFontShader();
        inline CSCI441::Font* currentFont = nullptr;
        inline GLuint fontShaderHandle = 0;
        inline GLint fontColorUniformLocation = -1;
        inline glm::vec2 windowSize = glm::vec2(0.0f);
        inline glm::vec2 fontSize = glm::vec2(1.0f);
    }
}

//************************************************
// Outward Facing Definitions

inline bool CSCI441::FontUtils::loadFont(const char * const filename) {
    if (CSCI441_INTERNAL::FontUtils::currentFont != nullptr) {
        delete CSCI441_INTERNAL::FontUtils::currentFont;
        CSCI441_INTERNAL::FontUtils::currentFont = nullptr;
    }

    bool success = true;

    if (CSCI441_INTERNAL::FontUtils::fontShaderHandle == 0) {
        success &= CSCI441_INTERNAL::FontUtils::loadFontShader();
    }

    CSCI441_INTERNAL::FontUtils::currentFont = new CSCI441::Font(filename);
    CSCI441_INTERNAL::FontUtils::currentFont->setScale(CSCI441_INTERNAL::FontUtils::fontSize.x, CSCI441_INTERNAL::FontUtils::fontSize.y);

    return success && CSCI441_INTERNAL::FontUtils::currentFont->isLoaded();;
}

inline void CSCI441::FontUtils::releaseFont() {
    glDeleteProgram(CSCI441_INTERNAL::FontUtils::fontShaderHandle);
    CSCI441_INTERNAL::FontUtils::fontShaderHandle = 0;

    delete CSCI441_INTERNAL::FontUtils::currentFont;
    CSCI441_INTERNAL::FontUtils::currentFont = nullptr;
}

inline void CSCI441::FontUtils::bindFont() {
    if (CSCI441_INTERNAL::FontUtils::fontShaderHandle != 0 && CSCI441_INTERNAL::FontUtils::currentFont != nullptr) {
        glUseProgram( CSCI441_INTERNAL::FontUtils::fontShaderHandle );
        CSCI441_INTERNAL::FontUtils::currentFont->bind();
    } else {
        fprintf(stderr, "[FontUtil | ERROR]: bindFont() called without loading a font.  Call loadFont() first\n");
    }
}

inline void CSCI441::FontUtils::setColor(const glm::vec3 color) {
    const glm::vec4 colorA = glm::vec4(color, 1.0f);
    glProgramUniform4fv(CSCI441_INTERNAL::FontUtils::fontShaderHandle, CSCI441_INTERNAL::FontUtils::fontColorUniformLocation, 1, glm::value_ptr(colorA));
}

inline void CSCI441::FontUtils::setColor(const glm::vec4 color) {
    glProgramUniform4fv(CSCI441_INTERNAL::FontUtils::fontShaderHandle, CSCI441_INTERNAL::FontUtils::fontColorUniformLocation, 1, glm::value_ptr(color));
}

inline void CSCI441::FontUtils::setWindowSize(const GLint width, const GLint height) {
    setWindowSize(static_cast<GLfloat>(width), static_cast<GLfloat>(height));
}

inline void CSCI441::FontUtils::setWindowSize(const GLfloat width, const GLfloat height) {
    CSCI441_INTERNAL::FontUtils::windowSize = glm::vec2(width, height);
}

inline void CSCI441::FontUtils::setFontSize(const GLfloat scaleX, const GLfloat scaleY) {
    CSCI441_INTERNAL::FontUtils::fontSize = glm::vec2(scaleX, scaleY);
    if (CSCI441_INTERNAL::FontUtils::currentFont != nullptr) {
        CSCI441_INTERNAL::FontUtils::currentFont->setScale(scaleX, scaleY);
    }
}

inline void CSCI441::FontUtils::renderText(const char* str, const GLfloat x, const GLfloat y) {
    if (CSCI441_INTERNAL::FontUtils::currentFont != nullptr) {
        if (CSCI441_INTERNAL::FontUtils::windowSize.x == 0.0f ) {
            CSCI441_INTERNAL::FontUtils::currentFont->draw(str, x, y);
        } else {
            const GLfloat normalizedX = x / CSCI441_INTERNAL::FontUtils::windowSize.x * 2.0f - 1.0f;
            const GLfloat normalizedY = y / CSCI441_INTERNAL::FontUtils::windowSize.y * 2.0f - 1.0f;
            CSCI441_INTERNAL::FontUtils::currentFont->draw(str, normalizedX, normalizedY);
        }
    } else {
        fprintf(stderr, "[FontUtil | ERROR]: renderText() called without loading a font.  Call loadFont() first and then bindFont()\n");
    }
}

//************************************************
// Inward Facing Definitions

inline bool CSCI441_INTERNAL::FontUtils::loadFontShader() {
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

    const GLuint vertexShaderHandle = glCreateShader( GL_VERTEX_SHADER );
    glShaderSource(vertexShaderHandle, 1, vertexShaders, nullptr);
    glCompileShader(vertexShaderHandle);

    const GLuint fragmentShaderHandle = glCreateShader( GL_FRAGMENT_SHADER );
    glShaderSource(fragmentShaderHandle, 1, fragmentShaders, nullptr);
    glCompileShader(fragmentShaderHandle);

    fontShaderHandle = glCreateProgram();
    glAttachShader(fontShaderHandle, vertexShaderHandle);
    glAttachShader(fontShaderHandle, fragmentShaderHandle);
    glLinkProgram(fontShaderHandle);

    glDetachShader(fontShaderHandle, vertexShaderHandle);
    glDeleteShader(vertexShaderHandle);

    glDetachShader(fontShaderHandle, fragmentShaderHandle);
    glDeleteShader(fragmentShaderHandle);

    const GLint texUniformLocation = glGetUniformLocation(fontShaderHandle, "tex");
    fontColorUniformLocation     = glGetUniformLocation(fontShaderHandle, "color");

    glProgramUniform1i(fontShaderHandle, texUniformLocation, 0);
    constexpr glm::vec4 white(1.0f, 1.0f, 1.0f, 1.0f);
    glProgramUniform4fv(fontShaderHandle, fontColorUniformLocation, 1, glm::value_ptr(white));

    return fontShaderHandle != 0;

}

#endif//CSCI441_FONT_UTILS_HPP