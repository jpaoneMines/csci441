#ifndef CSCI441_FONT_HPP
#define CSCI441_FONT_HPP

#ifdef CSCI441_USE_GLEW
    #include <GL/glew.h>
#else
    #include <glad/gl.h>
#endif

#include <ft2build.h>
#include FT_FREETYPE_H

#include <cstdlib>

namespace CSCI441 {
    /**
     * @brief Stores character glyphs corresponding to a ttf file and draws text to the screen
     */
    class Font {
    public:
        /**
         * @brief do not allow default Font objects to be constructed
         * @note see CSCI441::Font::Font(const char*) for proper creation
         */
        Font() = delete;
        /**
         * @brief Create a Font object containing the glyphs from a given ttf file
         * @param filename ttf file to load glyphs from
         */
        explicit Font(const char* filename);
        /**
         * @brief cleanup CPU and GPU memory
         */
        ~Font();

        /**
         * @brief tracks if font file was loaded successfully
         * @return true iff font file was successfully loaded
         */
        [[nodiscard]] GLboolean isLoaded() const { return _loaded; }

        /**
         * @brief set the amount to scale each glyph when drawing
         * @param scaleX amount to scale glyph horizontally
         * @param scaleY amount to scale glyph vertically
         * @note values typically refer to inverse screen size, e.g. the size of each pixel
         */
        void setScale(GLfloat scaleX, GLfloat scaleY);

        /**
         * @brief make this font active, binding its VAO, VBO, and 2D texture to GL_TEXTURE0
         * @note must be called immediately before CSCI441::Font::draw()
         */
        void bind() const;

        /**
         * @brief draws a text string at a given (x,y) window coordinate with the currently set scale
         * @param str string to display
         * @param x window X-coordinate to draw text at
         * @param y window Y-coordinate to draw text at
         * @pre MUST call CSCI441::Font::bind() prior to this call
         * @note see CSCI441::Font::setScale()
         */
        void draw(const char* str, GLfloat x, GLfloat y) const;
    private:
        /**
         * @brief tracks if font file was loaded successfully
         */
        GLboolean _loaded;

        /**
         * @brief VAO descriptor used to draw characters
         */
        GLuint _vao;
        /**
         * @brief VBO descriptor used to store current characters to draw
         */
        GLuint _vbo;
        /**
         * @brief texture handle corresponding to glyph set
         */
        GLuint _texHandle;

        /**
         * @brief amount to scale glyphs horizontally
         */
        GLfloat _scaleX;
        /**
         * @brief amount to scale glyphs vertically
         */
        GLfloat _scaleY;

        /**
         * @brief FreeType library
         */
        FT_Library _ftLibrary;
        /**
         * @brief FreeType font
         */
        FT_Face _fontFace;
        /**
         * @brief width of the entire glyph set texture
         */
        GLint _atlasWidth;
        /**
         * @brief height of the entire glyph set texture
         */
        GLint _atlasHeight;

        /**
         * @brief texture data and size information for each character in the font set
         * @note only stores ASCII characters [32-127]
         */
        struct CharacterInfo {
            /**
             * @brief number of pixels to advance x (affects kerning)
             */
            GLfloat ax = 0.f;
            /**
             * @brief number of pixels to advance y (affects line height)
             */
            GLfloat ay = 0.f;

            /**
             * @brief width of bitmap
             */
            GLfloat bw = 0.f;
            /**
             * @brief height of bitmap
             */
            GLfloat bh = 0.f;

            /**
             * @brief left offset of bitmap
             */
            GLfloat bl = 0.f;
            /**
             * @brief top offset of bitmap
             */
            GLfloat bt = 0.f;

            /**
             * @brief x offset of glyph in texture coordinates
             */
            GLfloat tx = 0.f;
        } _fontCharacters[128];
    };
}

inline CSCI441::Font::Font(const char *filename) :
    _loaded(GL_FALSE),
    _vao(0),
    _vbo(0),
    _texHandle(0),
    _scaleX(1.0f),
    _scaleY(1.0f),
    _ftLibrary(nullptr),
    _fontFace(nullptr),
    _atlasWidth(0),
    _atlasHeight(0)
{

    if(FT_Init_FreeType(&_ftLibrary)) {
        fprintf(stderr, "[font | ERROR]: Could not init freetype library\n");
        return;
    }

    if(FT_New_Face(_ftLibrary, filename, 0, &_fontFace)) {
        fprintf(stderr, "[font | ERROR]: Could not open font\n");
        return;
    }

    FT_Set_Pixel_Sizes(_fontFace, 0, 20);

    const auto g = _fontFace->glyph;
    GLint w = 0;
    GLint h = 0;

    for(int i = 32; i < 128; i++) {
      if(FT_Load_Char(_fontFace, i, FT_LOAD_RENDER)) {
        fprintf(stderr, "[font | ERROR]: Loading character %c failed!\n", i);
        continue;
      }

      w += g->bitmap.width;
      h = (h > g->bitmap.rows ? h : g->bitmap.rows);
    }

    // save this value as it is needed later on
    _atlasWidth = w;
    _atlasHeight = h;

    glEnable( GL_TEXTURE_2D );
    glActiveTexture(GL_TEXTURE0);
    glGenTextures(1, &_texHandle);
    glBindTexture(GL_TEXTURE_2D, _texHandle);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glPixelStorei(GL_UNPACK_ALIGNMENT, 1);
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RED, w, h, 0, GL_RED, GL_UNSIGNED_BYTE, 0);

    GLint x = 0;

    for(int i = 32; i < 128; i++) {
        if(FT_Load_Char(_fontFace, i, FT_LOAD_RENDER))
            continue;

        _fontCharacters[i].ax = static_cast<GLfloat>( g->advance.x >> 6 );
        _fontCharacters[i].ay = static_cast<GLfloat>( g->advance.y >> 6 );

        _fontCharacters[i].bw = static_cast<GLfloat>( g->bitmap.width );
        _fontCharacters[i].bh = static_cast<GLfloat>( g->bitmap.rows );

        _fontCharacters[i].bl = static_cast<GLfloat>( g->bitmap_left );
        _fontCharacters[i].bt = static_cast<GLfloat>( g->bitmap_top );

        _fontCharacters[i].tx = static_cast<GLfloat>(x) / static_cast<GLfloat>(w);

        glTexSubImage2D(GL_TEXTURE_2D, 0, x, 0, g->bitmap.width, g->bitmap.rows, GL_RED, GL_UNSIGNED_BYTE, g->bitmap.buffer);

        x += g->bitmap.width;
    }

    glGenVertexArrays(1, &_vao);
    glBindVertexArray(_vao);
    glGenBuffers(1, &_vbo);
    glBindBuffer(GL_ARRAY_BUFFER, _vbo);
    glEnableVertexAttribArray(0);
    glVertexAttribPointer(0, 4, GL_FLOAT, GL_FALSE, 0, nullptr);

    _loaded = GL_TRUE;
}

inline CSCI441::Font::~Font() {
    glDeleteVertexArrays(1, &_vao);
    glDeleteBuffers(1, &_vbo);
    glDeleteTextures(1, &_texHandle);
    FT_Done_Face(_fontFace);
    FT_Done_FreeType(_ftLibrary);
}

inline void CSCI441::Font::setScale(const GLfloat scaleX, const GLfloat scaleY) {
    if (_scaleX > 0 && _scaleY > 0) {
        _scaleX = scaleX;
        _scaleY = scaleY;
    }
}

inline void CSCI441::Font::bind() const {
    glBindVertexArray(_vao);
    glBindBuffer(GL_ARRAY_BUFFER, _vbo);
    glActiveTexture(GL_TEXTURE0);
    glBindTexture(GL_TEXTURE_2D, _texHandle);
}

inline void CSCI441::Font::draw(const char* str, GLfloat x, GLfloat y) const {
    struct FontPoint {
        GLfloat x;
        GLfloat y;
        GLfloat s;
        GLfloat t;
    } coords[6 * strlen(str)];

    GLint n = 0;

    for(const char *p = str; *p; p++) {
        const auto characterIndex = static_cast<int>(*p);
        const auto character = _fontCharacters[characterIndex];
        const auto x2 =  x + character.bl * _scaleX;
        const auto y2 = -y - character.bt * _scaleY;
        const auto w = character.bw * _scaleX;
        const auto h = character.bh * _scaleY;

        // Advance the cursor to the start of the next character
        x += character.ax * _scaleX;
        y += character.ay * _scaleY;

        // Skip glyphs that have no pixels
        if(!w || !h)
            continue;

        coords[n++] = (FontPoint){x2,     -y2    , character.tx,                                0};
        coords[n++] = (FontPoint){x2 + w, -y2    , character.tx + character.bw / _atlasWidth,   0};
        coords[n++] = (FontPoint){x2,     -y2 - h, character.tx,                                character.bh / _atlasHeight}; //remember: each glyph occupies a different amount of vertical space

        coords[n++] = (FontPoint){x2 + w, -y2    , character.tx + character.bw / _atlasWidth,   0};
        coords[n++] = (FontPoint){x2,     -y2 - h, character.tx,                                character.bh / _atlasHeight};
        coords[n++] = (FontPoint){x2 + w, -y2 - h, character.tx + character.bw / _atlasWidth,   character.bh / _atlasHeight};
    }
    glBufferData(GL_ARRAY_BUFFER, sizeof( coords ), coords, GL_DYNAMIC_DRAW);
    glDrawArrays(GL_TRIANGLES, 0, n);
}

#endif//CSCI441_FONT_HPP