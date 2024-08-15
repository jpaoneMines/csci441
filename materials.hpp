/**
 * @file materials.hpp
 * @brief Predefined material properties
 * @author Dr. Jeffrey Paone
 *
 * @copyright MIT License Copyright (c) 2020 Dr. Jeffrey Paone
 *
 */

#ifndef CSCI441_MATERIALS_HPP
#define CSCI441_MATERIALS_HPP

#include <glm/vec4.hpp>

namespace CSCI441 {

    /**
     * @namespace Materials
     * @brief Material Helpers for Phong Reflectance Model
     */
    namespace Materials {

        /**
         * @brief stores material properties used within the Phong Reflectance Model
         */
        struct Material {
            /**
             * @brief RGBA values for Diffuse (Lambertian) Reflectance
             */
            [[maybe_unused]] GLfloat diffuse[4];
            /**
             * @brief RGBA values for Diffuse Reflectance
             * @return diffuse values in glm::vec4 format
             */
            [[maybe_unused]] [[nodiscard]] glm::vec4 getDiffuse() const { return { diffuse[0], diffuse[1], diffuse[2], diffuse[3] }; }
            /**
             * @brief RGBA values for Specular Reflectance
             */
            [[maybe_unused]] GLfloat specular[4];
            /**
             * @brief RGBA values for Specular Reflectance
             * @return specular values in glm::vec4 format
             */
            [[maybe_unused]] [[nodiscard]] glm::vec4 getSpecular() const { return { specular[0], specular[1], specular[2], specular[3] }; }
            /**
             * @brief Shininess value to control exponential falloff of Specular Reflectance
             */
            [[maybe_unused]] GLfloat shininess;
            /**
             * @brief RGBA values for Ambient Illumination
             */
            [[maybe_unused]] GLfloat ambient[4];
            /**
             * @brief RGBA values for Ambient Reflectance
             * @return ambient values in glm::vec4 format
             */
            [[maybe_unused]] [[nodiscard]] glm::vec4 getAmbient() const { return { ambient[0], ambient[1], ambient[2], ambient[3] }; }
        };

        /**
         * @brief brass material from teapots.c demo SGI 1994, Mark J. Kilgard (http://devernay.free.fr/cours/opengl/materials.html)
         */
        [[maybe_unused]] constexpr Material BRASS            = { {0.780392f, 0.568627f,  0.113725f,  1.0f}, {0.992157f,  0.941176f,  0.807843f,  1.0f},27.8974f, {0.329412f, 0.223529f,  0.027451f,  1.0f} };
        /**
         * @brief plastic black material from teapots.c demo SGI 1994, Mark J. Kilgard (http://devernay.free.fr/cours/opengl/materials.html)
         */
        [[maybe_unused]] constexpr Material BLACK_PLASTIC    = { {0.01f,     0.01f,      0.01f,      1.0f}, {0.50f,      0.50f,      0.50f,      1.0f},32.0f,    {0.0f,      0.0f,       0.0f,       1.0f} };
        /**
         * @brief black rubber material from teapots.c demo SGI 1994, Mark J. Kilgard (http://devernay.free.fr/cours/opengl/materials.html)
         */
        [[maybe_unused]] constexpr Material BLACK_RUBBER     = { {0.01f,     0.01f,      0.01f,      1.0f}, {0.4f,       0.4f,       0.4f,       1.0f},10.0f,    {0.02f,     0.02f,      0.02f,      1.0f} };
        /**
         * @brief bronze material from teapots.c demo SGI 1994, Mark J. Kilgard (http://devernay.free.fr/cours/opengl/materials.html)
         */
        [[maybe_unused]] constexpr Material BRONZE           = { {0.714f,    0.4284f,    0.18144f,   1.0f}, {0.393548f,  0.271906f,  0.166721f,  1.0f},25.6f,    {0.2125f,   0.1275f,    0.054f,     1.0f} };
        /**
         * @brief polished bronze material from teapots.c demo SGI 1994, Mark J. Kilgard (http://devernay.free.fr/cours/opengl/materials.html)
         */
        [[maybe_unused]] constexpr Material BRONZE_POLISHED  = { {0.4f,      0.2368f,    0.1036f,    1.0f}, {0.774597f,  0.458561f,  0.200621f,  1.0f},76.8f,    {0.25f,     0.148f,     0.06475f,   1.0f} };
        /**
         * @brief chrome material from teapots.c demo SGI 1994, Mark J. Kilgard (http://devernay.free.fr/cours/opengl/materials.html)
         */
        [[maybe_unused]] constexpr Material CHROME           = { {0.4f,      0.4f,       0.4f,       1.0f}, {0.774597f,  0.774597f,  0.774597f,  1.0f},76.8f,    {0.25f,     0.25f,      0.25f,      1.0f} };
        /**
         * @brief copper material from teapots.c demo SGI 1994, Mark J. Kilgard (http://devernay.free.fr/cours/opengl/materials.html)
         */
        [[maybe_unused]] constexpr Material COPPER           = { {0.7038f,   0.27048f,   0.0828f,    1.0f}, {0.256777f,  0.137622f,  0.086014f,  1.0f},12.8f,    {0.19125f,  0.0735f,    0.0225f,    1.0f} };
        /**
         * @brief polished copper material from teapots.c demo SGI 1994, Mark J. Kilgard (http://devernay.free.fr/cours/opengl/materials.html)
         */
        [[maybe_unused]] constexpr Material COPPER_POLISHED  = { {0.5508f,   0.2118f,    0.066f,     1.0f}, {0.580594f,  0.223257f,  0.0695701f, 1.0f},51.2f,    {0.2295f,   0.08825f,   0.0275f,    1.0f} };
        /**
         * @brief plastic cyan material from teapots.c demo SGI 1994, Mark J. Kilgard (http://devernay.free.fr/cours/opengl/materials.html)
         */
        [[maybe_unused]] constexpr Material CYAN_PLASTIC     = { {0.0f,      0.50980392f,0.50980392f,1.0f}, {0.50196078f,0.50196078f,0.50196078f,1.0f},32.0f,    {0.0f,      0.1f,       0.06f ,     1.0f} };
        /**
         * @brief cyan rubber material from teapots.c demo SGI 1994, Mark J. Kilgard (http://devernay.free.fr/cours/opengl/materials.html)
         */
        [[maybe_unused]] constexpr Material CYAN_RUBBER      = { {0.4f,      0.5f,       0.5f,       1.0f}, {0.04f,      0.7f,       0.7f,       1.0f},10.0f,    {0.0f,      0.05f,      0.05f,      1.0f} };
        /**
         * @brief emerald material from teapots.c demo SGI 1994, Mark J. Kilgard (http://devernay.free.fr/cours/opengl/materials.html)
         */
        [[maybe_unused]] constexpr Material EMERALD          = { {0.07568f,  0.61424f,   0.07568f,   1.0f}, {0.633f,     0.727811f,  0.633f,     1.0f},76.8f,    {0.0215f,   0.1745f,    0.0215f,    1.0f} };
        /**
         * @brief gold material from teapots.c demo SGI 1994, Mark J. Kilgard (http://devernay.free.fr/cours/opengl/materials.html)
         */
        [[maybe_unused]] constexpr Material GOLD             = { {0.75164f,  0.60648f,   0.22648f,   1.0f}, {0.628281f,  0.555802f,  0.366065f,  1.0f},51.2f,    {0.24725f,  0.1995f,    0.0745f,    1.0f} };
        /**
         * @brief polished gold material from teapots.c demo SGI 1994, Mark J. Kilgard (http://devernay.free.fr/cours/opengl/materials.html)
         */
        [[maybe_unused]] constexpr Material GOLD_POLISHED    = { {0.34615f,  0.3143f,    0.0903f,    1.0f}, {0.797357f,  0.723991f,  0.208006f,  1.0f},83.2f,    {0.24725f,  0.2245f,    0.0645f,    1.0f} };
        /**
         * @brief plastic green material from teapots.c demo SGI 1994, Mark J. Kilgard (http://devernay.free.fr/cours/opengl/materials.html)
         */
        [[maybe_unused]] constexpr Material GREEN_PLASTIC    = { {0.1f,      0.35f,      0.1f,       1.0f}, {0.45f,      0.55f,      0.45f,      1.0f},32.0f,    {0.0f,      0.0f,       0.0f,       1.0f} };
        /**
         * @brief green rubber material from teapots.c demo SGI 1994, Mark J. Kilgard (http://devernay.free.fr/cours/opengl/materials.html)
         */
        [[maybe_unused]] constexpr Material GREEN_RUBBER     = { {0.4f,      0.5f,       0.4f,       1.0f}, {0.04f,      0.7f,       0.04f,      1.0f},10.0f,    {0.0f,      0.05f,      0.0f,       1.0f} };
        /**
         * @brief jade material from teapots.c demo SGI 1994, Mark J. Kilgard (http://devernay.free.fr/cours/opengl/materials.html)
         */
        [[maybe_unused]] constexpr Material JADE             = { {0.54f,     0.89f,      0.63f,      1.0f}, {0.316228f,  0.316228f,  0.316228f,  1.0f},12.8f,    {0.135f,    0.2225f,    0.1575f,    1.0f} };
        /**
         * @brief obsidian material from teapots.c demo SGI 1994, Mark J. Kilgard (http://devernay.free.fr/cours/opengl/materials.html)
         */
        [[maybe_unused]] constexpr Material OBSIDIAN         = { {0.18275f,  0.17f,      0.22525f,   1.0f}, {0.331741f,  0.328634f,  0.346435f,  1.0f},38.4f,    {0.05365f,  0.05f,      0.06625f,   1.0f} };
        /**
         * @brief pearl material from teapots.c demo SGI 1994, Mark J. Kilgard (http://devernay.free.fr/cours/opengl/materials.html)
         */
        [[maybe_unused]] constexpr Material PEARL            = { {1.0f,      0.829f,     0.829f,     1.0f}, {0.296648f,  0.296648f,  0.296648f,  1.0f},11.264f,  {0.25f,     0.20725f,   0.20725f,   1.0f} };
        /**
         * @brief pewter material from teapots.c demo SGI 1994, Mark J. Kilgard (http://devernay.free.fr/cours/opengl/materials.html)
         */
        [[maybe_unused]] constexpr Material PEWTER           = { {0.427451f, 0.470588f,  0.541176f,  1.0f}, {0.333333f,  0.333333f,  0.521569f,  1.0f},9.84615f, {0.105882f, 0.058824f,  0.113725f,  1.0f} };
        /**
         * @brief plastic red material from teapots.c demo SGI 1994, Mark J. Kilgard (http://devernay.free.fr/cours/opengl/materials.html)
         */
        [[maybe_unused]] constexpr Material RED_PLASTIC      = { {0.5f,      0.0f,       0.0f,       1.0f}, {0.7f,       0.6f,       0.6f,       1.0f},32.0f,    {0.0f,      0.0f,       0.0f,       1.0f} };
        /**
         * @brief red rubber material from teapots.c demo SGI 1994, Mark J. Kilgard (http://devernay.free.fr/cours/opengl/materials.html)
         */
        [[maybe_unused]] constexpr Material REB_RUBBER       = { {0.5f,      0.4f,       0.4f,       1.0f}, {0.7f,       0.04f,      0.04f,      1.0f},10.0f,    {0.05f,     0.0f,       0.0f,       1.0f} };
        /**
         * @brief ruby material from teapots.c demo SGI 1994, Mark J. Kilgard (http://devernay.free.fr/cours/opengl/materials.html)
         */
        [[maybe_unused]] constexpr Material RUBY             = { {0.61424f,  0.04136f,   0.04136f,   1.0f}, {0.727811f,  0.626959f,  0.626959f,  1.0f},76.8f,    {0.1745f,   0.01175f,   0.01175f,   1.0f} };
        /**
         * @brief silver material from teapots.c demo SGI 1994, Mark J. Kilgard (http://devernay.free.fr/cours/opengl/materials.html)
         */
        [[maybe_unused]] constexpr Material SILVER           = { {0.50754f,  0.50754f,   0.50754f,   1.0f}, {0.508273f,  0.508273f,  0.508273f,  1.0f},51.2f,    {0.19225f,  0.19225f,   0.19225f,   1.0f} };
        /**
         * @brief polished silver material from teapots.c demo SGI 1994, Mark J. Kilgard (http://devernay.free.fr/cours/opengl/materials.html)
         */
        [[maybe_unused]] constexpr Material SILVER_POLISHED  = { {0.2775f,   0.2775f,    0.2775f,    1.0f}, {0.773911f,  0.773911f,  0.773911f,  1.0f},89.6f,    {0.23125f,  0.23125f,   0.23125f,   1.0f} };
        /**
         * @brief tin material from teapots.c demo SGI 1994, Mark J. Kilgard (http://devernay.free.fr/cours/opengl/materials.html)
         */
        [[maybe_unused]] constexpr Material TIN              = { {0.427451f, 0.470588f,  0.541176f,  1.0f}, {0.333333f,  0.333333f,  0.521569f,  1.0f},9.84615f, {0.105882f, 0.058824f,  0.113725f,  1.0f} };
        /**
         * @brief turquoise material from teapots.c demo SGI 1994, Mark J. Kilgard (http://devernay.free.fr/cours/opengl/materials.html)
         */
        [[maybe_unused]] constexpr Material TURQUOISE        = { {0.396f,    0.74151f,   0.69102f,   1.0f}, {0.297254f,  0.30829f,   0.306678f,  1.0f},12.8f,    {0.1f,      0.18725f,   0.1745f,    1.0f} };
        /**
         * @brief plastic white material from teapots.c demo SGI 1994, Mark J. Kilgard (http://devernay.free.fr/cours/opengl/materials.html)
         */
        [[maybe_unused]] constexpr Material WHITE_PLASTIC    = { {0.55f,     0.55f,      0.55f,      1.0f}, {0.70f,      0.70f,      0.70f,      1.0f},32.0f,    {0.0f,      0.0f,       0.0f,       1.0f} };
        /**
         * @brief white rubber material from teapots.c demo SGI 1994, Mark J. Kilgard (http://devernay.free.fr/cours/opengl/materials.html)
         */
        [[maybe_unused]] constexpr Material WHITE_RUBBER     = { {0.5f,      0.5f,       0.5f,       1.0f}, {0.7f,       0.7f,       0.7f,       1.0f},10.0f,    {0.05f,     0.05f,      0.05f,      1.0f} };
        /**
         * @brief plastic yellow material from teapots.c demo SGI 1994, Mark J. Kilgard (http://devernay.free.fr/cours/opengl/materials.html)
         */
        [[maybe_unused]] constexpr Material YELLOW_PLASTIC   = { {0.5f,      0.5f,       0.0f,       1.0f}, {0.60f,      0.60f,      0.50f,      1.0f},32.0f,    {0.0f,      0.0f,       0.0f,       1.0f} };
        /**
         * @brief yellow rubber material from teapots.c demo SGI 1994, Mark J. Kilgard (http://devernay.free.fr/cours/opengl/materials.html)
         */
        [[maybe_unused]] constexpr Material YELLOW_RUBBER    = { {0.5f,      0.5f,       0.4f,       1.0f}, {0.7f,       0.7f,       0.04f,      1.0f},10.0f,    {0.05f,     0.05f,      0.0f,       1.0f} };
    }
}

#endif // CSCI441_MATERIALS_HPP