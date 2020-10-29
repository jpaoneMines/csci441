/** @file materials.hpp
 * @brief Predefined material properties
 * @author Dr. Jeffrey Paone
 * @date Last Edit: 27 Oct 2020
 * @version 2.6.1
 *
 * @copyright MIT License Copyright (c) 2020 Dr. Jeffrey Paone
 *
 */

#ifndef __CSCI441_MATERIALS_HPP__
#define __CSCI441_MATERIALS_HPP__

/** @namespace CSCI441
 * @brief CSCI441 Helper Functions for OpenGL
 */
namespace CSCI441 {
    /** @namespace Materials
     * @brief Material Helpers for OpenGL
	 */
    namespace Materials {

        struct Material {
            float diffuse[4];
            float specular[4];
            float shininess;
            float ambient[4];
        };

        const Material BRASS            = { {0.780392f, 0.568627f,  0.113725f,  1.0f}, {0.992157f,  0.941176f,  0.807843f,  1.0f},27.8974f, {0.329412f, 0.223529f,  0.027451f,  1.0f} };
        const Material BLACK_PLASTIC    = { {0.01f,     0.01f,      0.01f,      1.0f}, {0.50f,      0.50f,      0.50f,      1.0f},32.0f,    {0.0f,      0.0f,       0.0f,       1.0f} };
        const Material BLACK_RUBBER     = { {0.01f,     0.01f,      0.01f,      1.0f}, {0.4f,       0.4f,       0.4f,       1.0f},10.0f,    {0.02f,     0.02f,      0.02f,      1.0f} };
        const Material BRONZE           = { {0.714f,    0.4284f,    0.18144f,   1.0f}, {0.393548f,  0.271906f,  0.166721f,  1.0f},25.6f,    {0.2125f,   0.1275f,    0.054f,     1.0f} };
        const Material BRONZE_POLISHED  = { {0.4f,      0.2368f,    0.1036f,    1.0f}, {0.774597f,  0.458561f,  0.200621f,  1.0f},76.8f,    {0.25f,     0.148f,     0.06475f,   1.0f} };
        const Material CHROME           = { {0.4f,      0.4f,       0.4f,       1.0f}, {0.774597f,  0.774597f,  0.774597f,  1.0f},76.8f,    {0.25f,     0.25f,      0.25f,      1.0f} };
        const Material COPPER           = { {0.7038f,   0.27048f,   0.0828f,    1.0f}, {0.256777f,  0.137622f,  0.086014f,  1.0f},12.8f,    {0.19125f,  0.0735f,    0.0225f,    1.0f} };
        const Material COPPER_POLISHED  = { {0.5508f,   0.2118f,    0.066f,     1.0f}, {0.580594f,  0.223257f,  0.0695701f, 1.0f},51.2f,    {0.2295f,   0.08825f,   0.0275f,    1.0f} };
        const Material CYAN_PLASTIC     = { {0.0f,      0.50980392f,0.50980392f,1.0f}, {0.50196078f,0.50196078f,0.50196078f,1.0f},32.0f,    {0.0f,      0.1f,       0.06f ,     1.0f} };
        const Material CYAN_RUBBER      = { {0.4f,      0.5f,       0.5f,       1.0f}, {0.04f,      0.7f,       0.7f,       1.0f},10.0f,    {0.0f,      0.05f,      0.05f,      1.0f} };
        const Material EMERALD          = { {0.07568f,  0.61424f,   0.07568f,   1.0f}, {0.633f,     0.727811f,  0.633f,     1.0f},76.8f,    {0.0215f,   0.1745f,    0.0215f,    1.0f} };
        const Material GOLD             = { {0.75164f,  0.60648f,   0.22648f,   1.0f}, {0.628281f,  0.555802f,  0.366065f,  1.0f},51.2f,    {0.24725f,  0.1995f,    0.0745f,    1.0f} };
        const Material GOLD_POLISHED    = { {0.34615f,  0.3143f,    0.0903f,    1.0f}, {0.797357f,  0.723991f,  0.208006f,  1.0f},83.2f,    {0.24725f,  0.2245f,    0.0645f,    1.0f} };
        const Material GREEN_PLASTIC    = { {0.1f,      0.35f,      0.1f,       1.0f}, {0.45f,      0.55f,      0.45f,      1.0f},32.0f,    {0.0f,      0.0f,       0.0f,       1.0f} };
        const Material GREEN_RUBBER     = { {0.4f,      0.5f,       0.4f,       1.0f}, {0.04f,      0.7f,       0.04f,      1.0f},10.0f,    {0.0f,      0.05f,      0.0f,       1.0f} };
        const Material JADE             = { {0.54f,     0.89f,      0.63f,      1.0f}, {0.316228f,  0.316228f,  0.316228f,  1.0f},12.8f,    {0.135f,    0.2225f,    0.1575f,    1.0f} };
        const Material OBSIDIAN         = { {0.18275f,  0.17f,      0.22525f,   1.0f}, {0.331741f,  0.328634f,  0.346435f,  1.0f},38.4f,    {0.05365f,  0.05f,      0.06625f,   1.0f} };
        const Material PEARL            = { {1.0f,      0.829f,     0.829f,     1.0f}, {0.296648f,  0.296648f,  0.296648f,  1.0f},11.264f,  {0.25f,     0.20725f,   0.20725f,   1.0f} };
        const Material PEWTER           = { {0.427451f, 0.470588f,  0.541176f,  1.0f}, {0.333333f,  0.333333f,  0.521569f,  1.0f},9.84615f, {0.105882f, 0.058824f,  0.113725f,  1.0f} };
        const Material RED_PLASTIC      = { {0.5f,      0.0f,       0.0f,       1.0f}, {0.7f,       0.6f,       0.6f,       1.0f},32.0f,    {0.0f,      0.0f,       0.0f,       1.0f} };
        const Material REB_RUBBER       = { {0.5f,      0.4f,       0.4f,       1.0f}, {0.7f,       0.04f,      0.04f,      1.0f},10.0f,    {0.05f,     0.0f,       0.0f,       1.0f} };
        const Material RUBY             = { {0.61424f,  0.04136f,   0.04136f,   1.0f}, {0.727811f,  0.626959f,  0.626959f,  1.0f},76.8f,    {0.1745f,   0.01175f,   0.01175f,   1.0f} };
        const Material SILVER           = { {0.50754f,  0.50754f,   0.50754f,   1.0f}, {0.508273f,  0.508273f,  0.508273f,  1.0f},51.2f,    {0.19225f,  0.19225f,   0.19225f,   1.0f} };
        const Material SILVER_POLISHED  = { {0.2775f,   0.2775f,    0.2775f,    1.0f}, {0.773911f,  0.773911f,  0.773911f,  1.0f},89.6f,    {0.23125f,  0.23125f,   0.23125f,   1.0f} };
        const Material TIN              = { {0.427451f, 0.470588f,  0.541176f,  1.0f}, {0.333333f,  0.333333f,  0.521569f,  1.0f},9.84615f, {0.105882f, 0.058824f,  0.113725f,  1.0f} };
        const Material TURQUOISE        = { {0.396f,    0.74151f,   0.69102f,   1.0f}, {0.297254f,  0.30829f,   0.306678f,  1.0f},12.8f,    {0.1f,      0.18725f,   0.1745f,    1.0f} };
        const Material WHITE_PLASTIC    = { {0.55f,     0.55f,      0.55f,      1.0f}, {0.70f,      0.70f,      0.70f,      1.0f},32.0f,    {0.0f,      0.0f,       0.0f,       1.0f} };
        const Material WHITE_RUBBER     = { {0.5f,      0.5f,       0.5f,       1.0f}, {0.7f,       0.7f,       0.7f,       1.0f},10.0f,    {0.05f,     0.05f,      0.05f,      1.0f} };
        const Material YELLOW_PLASTIC   = { {0.5f,      0.5f,       0.0f,       1.0f}, {0.60f,      0.60f,      0.50f,      1.0f},32.0f,    {0.0f,      0.0f,       0.0f,       1.0f} };
        const Material YELLOW_RUBBER    = { {0.5f,      0.5f,       0.4f,       1.0f}, {0.7f,       0.7f,       0.04f,      1.0f},10.0f,    {0.05f,     0.05f,      0.0f,       1.0f} };
    }
}

#endif // __CSCI441_MATERIALS_HPP__