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
    class Font {
    public:
        Font() = delete;
        Font(const char* filename);
        ~Font();

        [[nodiscard]] GLboolean isLoaded() const { return _loaded; }
        void setScale(GLfloat scaleX, GLfloat scaleY);
        void bind() const;

        /**
         *
         * @param str
         * @param x
         * @param y
         * @pre MUST call CSCI441::Font::Bind() prior to this call
         */
        void draw(const char* str, GLfloat x, GLfloat y) const;
    private:
        GLboolean _loaded;

        GLuint _vao;
        GLuint _vbo;
        GLuint _texHandle;

        GLfloat _scaleX;
        GLfloat _scaleY;

        FT_Face _fontFace;
        GLint _atlasWidth;
        GLint _atlasHeight;

        struct CharacterInfo {
            GLfloat ax; // advance.x
            GLfloat ay; // advance.y

            GLfloat bw; // bitmap.width;
            GLfloat bh; // bitmap.rows;

            GLfloat bl; // bitmap_left;
            GLfloat bt; // bitmap_top;

            GLfloat tx; // x offset of glyph in texture coordinates
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
    _atlasWidth(0),
    _atlasHeight(0)
{
    FT_Library ft;

    if(FT_Init_FreeType(&ft)) {
        fprintf(stderr, "[font | ERROR]: Could not init freetype library\n");
        return;
    }

    if(FT_New_Face(ft, filename, 0, &_fontFace)) {
        fprintf(stderr, "[font | ERROR]: Could not open font\n");
        return;
    }

    FT_Set_Pixel_Sizes(_fontFace, 0, 20);

    const FT_GlyphSlot g = _fontFace->glyph;
    GLuint w = 0;
    GLuint h = 0;

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