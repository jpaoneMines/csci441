/** @file SimpleShader.hpp
 * @brief Sets up a default Gouraud Shader with vertex position and color inputs
 * @author Dr. Jeffrey Paone
 *
 * @copyright MIT License Copyright (c) 2020 Dr. Jeffrey Paone
 *
 *	These functions, classes, and constants help minimize common
 *	code that needs to be written.
 *
 *	@warning NOTE: This header file will only work with OpenGL 4.1
 *	@warning NOTE: This header file depends upon glm
 *	@warning NOTE: This header file depends upon GLAD (or alternatively GLEW)
 */

#ifndef CSCI441_SIMPLE_SHADER_HPP
#define CSCI441_SIMPLE_SHADER_HPP

#include "ShaderUtils.hpp"
#include "objects.hpp"

#ifdef CSCI441_USE_GLEW
    #include <GL/glew.h>
#else
    #include <glad/gl.h>
#endif

#include <glm/glm.hpp>
#include <glm/gtc/type_ptr.hpp>

#include <map>
#include <string>
#include <vector>

//**********************************************************************************

namespace CSCI441 {

    /**
     * @namespace SimpleShader2
     * @brief Abstracts the process of working with a 2D shader program
     */
    namespace SimpleShader2 {
        /**
         * @brief turns on Flat Shading
         * @warning must call prior to setupSimpleShader
         */
        [[maybe_unused]] void enableFlatShading();
        /**
         * @brief turns on Smooth Shading
         * @warning must call prior to setupSimpleShader
         */
        [[maybe_unused]] void enableSmoothShading();

        /**
         * @brief Registers a simple Gouraud shader for 2-Dimensional drawing
         */
        [[maybe_unused]] void setupSimpleShader();

        /**
         * @brief registers the associated vertex locations and colors with the GPU
         * @param VERTEX_POINTS vector of vertex (x,y) locations
         * @param VERTEX_COLORS vector of vertex (r,g,b) colors
         * @returns generated Vertex Array Object Descriptor (vaod)
         * @note will pad colors with alpha channel = 1.0f
         */
        [[maybe_unused]] GLuint registerVertexArray(const std::vector<glm::vec2>& VERTEX_POINTS, const std::vector<glm::vec3>& VERTEX_COLORS);

        /**
         * @brief registers the associated vertex locations and colors with the GPU
         * @param VERTEX_POINTS vector of vertex (x,y) locations
         * @param VERTEX_COLORS vector of vertex (r,g,b,a) colors
         * @returns generated Vertex Array Object Descriptor (vaod)
         */
        [[maybe_unused]] GLuint registerVertexArray(const std::vector<glm::vec2>& VERTEX_POINTS, const std::vector<glm::vec4>& VERTEX_COLORS);
        /**
         * @brief Updates GL_ARRAY_BUFFER for the corresponding VAO
         * @brief Copies the data for the vertex positions and colors from CPU RAM to the GPU for the already registered
         * VAO.  The data is copied in to the GL_ARRAY_BUFFER VBO for this VAO.  When function completes, the passed
         * VAO is currently bound.
         * @warning Requires that the same number of vertex points, or less, are passed as when the VAO was registered
         * @param VAOD Vertex Array Object Descriptor
         * @param VERTEX_POINTS vector of vertex (x,y) locations
         * @param VERTEX_COLORS vector of vertex (r,g,b) colors
         * @note will pad colors with alpha channel = 1.0f
         */
        [[maybe_unused]] void updateVertexArray(GLuint VAOD, const std::vector<glm::vec2>& VERTEX_POINTS, const std::vector<glm::vec3>& VERTEX_COLORS);
        /**
         * @brief Updates GL_ARRAY_BUFFER for the corresponding VAO
         * @brief Copies the data for the vertex positions and colors from CPU RAM to the GPU for the already registered
         * VAO.  The data is copied in to the GL_ARRAY_BUFFER VBO for this VAO.  When function completes, the passed
         * VAO is currently bound.
         * @warning Requires that the same number of vertex points, or less, are passed as when the VAO was registered
         * @param VAOD Vertex Array Object Descriptor
         * @param VERTEX_POINTS vector of vertex (x,y) locations
         * @param VERTEX_COLORS vector of vertex (r,g,b,a) colors
         */
        [[maybe_unused]] void updateVertexArray(GLuint VAOD, const std::vector<glm::vec2>& VERTEX_POINTS, const std::vector<glm::vec4>& VERTEX_COLORS);

        /**
         * @brief registers the associated vertex locations and colors with the GPU
         * @param NUM_POINTS number of points in each array
         * @param VERTEX_POINTS array of vertex (x,y) locations
         * @param VERTEX_COLORS array of vertex (r,g,b) colors
         * @returns generated Vertex Array Object Descriptor (vaod)
         */
        [[maybe_unused]] GLuint registerVertexArray(GLuint NUM_POINTS, const glm::vec2 VERTEX_POINTS[], const glm::vec3 VERTEX_COLORS[]);
        /**
         * @brief registers the associated vertex locations and colors with the GPU
         * @param NUM_POINTS number of points in each array
         * @param VERTEX_POINTS array of vertex (x,y) locations
         * @param VERTEX_COLORS array of vertex (r,g,b,a) colors
         * @returns generated Vertex Array Object Descriptor (vaod)
         */
        [[maybe_unused]] GLuint registerVertexArray(GLuint NUM_POINTS, const glm::vec2 VERTEX_POINTS[], const glm::vec4 VERTEX_COLORS[]);
        /**
         * @brief Updates GL_ARRAY_BUFFER for the corresponding VAO
         * @brief Copies the data for the vertex positions and colors from CPU RAM to the GPU for the already registered
         * VAO.  The data is copied in to the GL_ARRAY_BUFFER VBO for this VAO.  When function completes, the passed
         * VAO is currently bound.
         * @warning Requires that the same number of vertex points, or less, are passed as when the VAO was registered
         * @param VAOD Vertex Array Object Descriptor
         * @param NUM_POINTS number of points in each array
         * @param VERTEX_POINTS vector of vertex (x,y) locations
         * @param VERTEX_COLORS vector of vertex (r,g,b) colors
         */
        [[maybe_unused]] void updateVertexArray(GLuint VAOD, GLuint NUM_POINTS, const glm::vec2 VERTEX_POINTS[], const glm::vec3 VERTEX_COLORS[]);
        /**
         * @brief Updates GL_ARRAY_BUFFER for the corresponding VAO
         * @brief Copies the data for the vertex positions and colors from CPU RAM to the GPU for the already registered
         * VAO.  The data is copied in to the GL_ARRAY_BUFFER VBO for this VAO.  When function completes, the passed
         * VAO is currently bound.
         * @warning Requires that the same number of vertex points, or less, are passed as when the VAO was registered
         * @param VAOD Vertex Array Object Descriptor
         * @param NUM_POINTS number of points in each array
         * @param VERTEX_POINTS vector of vertex (x,y) locations
         * @param VERTEX_COLORS vector of vertex (r,g,b,a) colors
         */
        [[maybe_unused]] void updateVertexArray(GLuint VAOD, GLuint NUM_POINTS, const glm::vec2 VERTEX_POINTS[], const glm::vec4 VERTEX_COLORS[]);

        /**
         * @brief Deletes the Vertex Array Object and corresponding Vertex Buffer Object
         * @param VAOD Vertex Array Object Descriptor
         */
        [[maybe_unused]] void deleteVertexArray(GLuint VAOD);

        /**
         * @brief Sets the Projection Matrix
         * @param PROJECTION_MATRIX homogeneous projection matrix to set
         */
        [[maybe_unused]] void setProjectionMatrix(const glm::mat4& PROJECTION_MATRIX);

        /**
         * @brief Pushes a transformation to the stack and updates our model matrix
         * @param TRANSFORMATION_MATRIX homogeneous transformation to stack on model matrix
         */
        [[maybe_unused]] void pushTransformation(const glm::mat4& TRANSFORMATION_MATRIX);

        /**
         * @brief Pops the last transformation off the stack and updates our model matrix
         * by the inverse of the last transformation
         */
        [[maybe_unused]] void popTransformation();

        /**
         * @brief Sets the model matrix back to the identity matrix and clears the
         * transformation stack
         */
        [[maybe_unused]] void resetTransformationMatrix();

        /**
         * @brief loads associated VAO, drawing given primitive made up of corresponding number of vertices
         * @param PRIMITIVE_TYPE primitive type to use
         * @param VAOD VAO to load
         * @param VERTEX_COUNT number of vertices to draw
         */
        [[maybe_unused]] void draw(GLint PRIMITIVE_TYPE, GLuint VAOD, GLuint VERTEX_COUNT);
    }

    /**
     * @namespace SimpleShader3
     * @brief Abstracts the process of working with a 3D shader program
     */
    namespace SimpleShader3 {
        /**
         * @brief turns on Flat Shading
         * @warning must call prior to setupSimpleShader
         */
        [[maybe_unused]] void enableFlatShading();
        /**
         * @brief turns on Smooth Shading
         * @warning must call prior to setupSimpleShader
         */
        [[maybe_unused]] void enableSmoothShading();

        /**
         * @brief Registers a simple Gouraud Shader with Lambertian Illumination for 3-Dimensional drawing
         */
        [[maybe_unused]] void setupSimpleShader();

        /**
         * @brief registers the associated vertex locations and colors with the GPU
         * @param VERTEX_POINTS vector of vertex (x,y,z) locations in object space
         * @param VERTEX_NORMALS vector of vertex (x,y,z) normals in object space
         * @return generated Vertex Array Object Descriptor (vaod)
         */
        [[maybe_unused]] GLuint registerVertexArray(const std::vector<glm::vec3>& VERTEX_POINTS, const std::vector<glm::vec3>& VERTEX_NORMALS);

        /**
         * @brief Updates GL_ARRAY_BUFFER for the corresponding VAO
         * @brief Copies the data for the vertex positions and colors from CPU RAM to the GPU for the already registered
         * VAO.  The data is copied in to the GL_ARRAY_BUFFER VBO for this VAO.  When function completes, the passed
         * VAO is currently bound.
         * @warning Requires that the same number of vertex points, or less, are passed as when the VAO was registered
         * @param VAOD Vertex Array Object Descriptor
         * @param VERTEX_POINTS vector of vertex (x,y,z) locations in object space
         * @param VERTEX_NORMALS vector of vertex (x,y,z) normals in object space
         */
        [[maybe_unused]] void updateVertexArray(GLuint VAOD, const std::vector<glm::vec3>& VERTEX_POINTS, const std::vector<glm::vec3>& VERTEX_NORMALS);

        /**
         * @brief registers the associated vertex locations and colors with the GPU
         * @param NUM_POINTS number of points in each array
         * @param VERTEX_POINTS array of vertex (x,y,z) locations in object space
         * @param VERTEX_NORMALS array of vertex (x,y,z) normals in object space
         * @return generated Vertex Array Object Descriptor (vaod)
         */
        [[maybe_unused]] GLuint registerVertexArray(GLuint NUM_POINTS, const glm::vec3 VERTEX_POINTS[], const glm::vec3 VERTEX_NORMALS[]);
        /**
         * @brief Updates GL_ARRAY_BUFFER for the corresponding VAO
         * @brief Copies the data for the vertex positions and colors from CPU RAM to the GPU for the already registered
         * VAO.  The data is copied in to the GL_ARRAY_BUFFER VBO for this VAO.  When function completes, the passed
         * VAO is currently bound.
         * @warning Requires that the same number of vertex points, or less, are passed as when the VAO was registered
         * @param VAOD Vertex Array Object Descriptor
         * @param NUM_POINTS number of points in each array
         * @param VERTEX_POINTS array of vertex (x,y,z) locations in object space
         * @param VERTEX_NORMALS array of vertex (x,y,z) normals in object space
         */
        [[maybe_unused]] void updateVertexArray(GLuint VAOD, GLuint NUM_POINTS, const glm::vec3 VERTEX_POINTS[], const glm::vec3 VERTEX_NORMALS[]);

        /**
         * @brief Deletes the Vertex Array Object and corresponding Vertex Buffer Object
         * @param VAOD Vertex Array Object Descriptor
         */
        [[maybe_unused]] void deleteVertexArray(GLuint VAOD);

        /**
         * @brief Sets the Projection Matrix
         * @param PROJECTION_MATRIX homogeneous projection matrix to set
         */
        [[maybe_unused]] void setProjectionMatrix(const glm::mat4& PROJECTION_MATRIX);
        /**
         * @brief Sets the View Matrix
         * @param VIEW_MATRIX homogeneous view matrix to set
         */
        [[maybe_unused]] void setViewMatrix(const glm::mat4& VIEW_MATRIX);

        /**
         * @brief sets position of single global light in world space
         * @param LIGHT_POSITION position of light in world space
         */
        [[maybe_unused]] void setLightPosition(const glm::vec3& LIGHT_POSITION);
        /**
         * @brief sets color of single global light
         * @param LIGHT_COLOR light color in RGB space
         */
        [[maybe_unused]] void setLightColor(const glm::vec3& LIGHT_COLOR);
        /**
         * @brief sets current diffuse material color to apply to object
         * @param MATERIAL_COLOR diffuse material color in RGB space
         */
        [[maybe_unused]] void setMaterialColor(const glm::vec3& MATERIAL_COLOR);

        /**
         * @brief Pushes a transformation to the stack and updates our model matrix
         * @param TRANSFORMATION_MATRIX transformation to stack on model matrix
         */
        [[maybe_unused]] void pushTransformation(const glm::mat4& TRANSFORMATION_MATRIX);

        /**
         * @brief Pops the last transformation off the stack and updates our model matrix
         * by the inverse of the last transformation
         */
        [[maybe_unused]] void popTransformation();

        /**
         * @brief Sets the model matrix back to the identity matrix and clears the
         * transformation stack
         */
        [[maybe_unused]] void resetTransformationMatrix();

        /**
         * @brief turns on lighting and applies Phong Illumination to fragment
         * @warning must call after to setupSimpleShader
         */
        [[maybe_unused]] void enableLighting();
        /**
         * @brief turns off lighting and applies material color to fragment
         * @warning must call after to setupSimpleShader
         */
        [[maybe_unused]] void disableLighting();

        /**
         * @brief loads associated VAO, drawing given primitive made up of corresponding number of vertices
         * @param PRIMITIVE_TYPE primitive type to use
         * @param VAOD VAO to load
         * @param VERTEX_COUNT number of vertices to draw
         */
        [[maybe_unused]] void draw(GLint PRIMITIVE_TYPE, GLuint VAOD, GLuint VERTEX_COUNT);
    }
}

////////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////
// Internal implementations

namespace CSCI441_INTERNAL {
    namespace SimpleShader2 {
        void enableFlatShading();
        void enableSmoothShading();
        void setupSimpleShader();
        GLuint registerVertexArray(GLuint NUM_POINTS, const glm::vec2 VERTEX_POINTS[], const glm::vec4 VERTEX_COLORS[]);
        void updateVertexArray(GLuint VAOD, GLuint NUM_POINTS, const glm::vec2 VERTEX_POINTS[], const glm::vec4 VERTEX_COLORS[]);
        void deleteVertexArray(GLuint VAOD);
        void setProjectionMatrix(const glm::mat4& PROJECTION_MATRIX);
        void pushTransformation(const glm::mat4& TRANSFORMATION_MATRIX);
        void popTransformation();
        void resetTransformationMatrix();
        void draw(GLint PRIMITIVE_TYPE, GLuint VAOD, GLuint VERTEX_COUNT);

        inline GLboolean smoothShading = true;
        inline GLint shaderProgramHandle = -1;
        inline GLint modelLocation = -1;
        inline GLint viewLocation = -1;
        inline GLint projectionLocation = -1;
        inline GLint vertexLocation = -1;
        inline GLint colorLocation = -1;

        inline std::map<GLuint, GLuint> descriptorMap;
        inline std::vector<glm::mat4> transformationStack;
        inline glm::mat4 modelMatrix(1.0f);
    }

    namespace SimpleShader3 {
        void enableFlatShading();
        void enableSmoothShading();
        void setupSimpleShader();
        GLuint registerVertexArray(GLuint NUM_POINTS, const glm::vec3 VERTEX_POINTS[], const glm::vec3 VERTEX_NORMALS[]);
        void updateVertexArray(GLuint VAOD, GLuint NUM_POINTS, const glm::vec3 VERTEX_POINTS[], const glm::vec3 VERTEX_NORMALS[]);
        void deleteVertexArray(GLuint VAOD);
        void setProjectionMatrix(const glm::mat4& PROJECTION_MATRIX);
        void setViewMatrix(const glm::mat4& VIEW_MATRIX);
        void setLightPosition(const glm::vec3& LIGHT_POSITION);
        void setLightColor(const glm::vec3& LIGHT_COLOR);
        void setMaterialColor(const glm::vec3& MATERIAL_COLOR);
        void pushTransformation(const glm::mat4& TRANSFORMATION_MATRIX);
        void popTransformation();
        void resetTransformationMatrix();
        void setNormalMatrix();
        void enableLighting();
        void disableLighting();
        void draw(GLint PRIMITIVE_TYPE, GLuint VAOD, GLuint VERTEX_COUNT);

        inline GLboolean smoothShading = true;
        inline GLint shaderProgramHandle = -1;
        inline GLint modelLocation = -1;
        inline GLint viewLocation = -1;
        inline GLint projectionLocation = -1;
        inline GLint normalMtxLocation = -1;
        inline GLint lightPositionLocation = -1;
        inline GLint lightColorLocation = -1;
        inline GLint materialLocation = -1;
        inline GLint vertexLocation = -1;
        inline GLint normalLocation = -1;
        inline GLint useLightingLocation = -1;

        inline std::map<GLuint, GLuint> descriptorMap;
        inline std::vector<glm::mat4> transformationStack;
        inline glm::mat4 modelMatrix(1.0f);
        inline glm::mat4 viewMatrix(1.0f);
    }
}

////////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////
// Outward facing function implementations

[[maybe_unused]]
inline void CSCI441::SimpleShader2::enableFlatShading() {
    CSCI441_INTERNAL::SimpleShader2::enableFlatShading();
}

[[maybe_unused]]
inline void CSCI441::SimpleShader2::enableSmoothShading() {
    CSCI441_INTERNAL::SimpleShader2::enableSmoothShading();
}

[[maybe_unused]]
inline void CSCI441::SimpleShader2::setupSimpleShader() {
    CSCI441_INTERNAL::SimpleShader2::setupSimpleShader();
}

[[maybe_unused]]
inline GLuint CSCI441::SimpleShader2::registerVertexArray(const std::vector<glm::vec2>& VERTEX_POINTS, const std::vector<glm::vec3>& VERTEX_COLORS) {
    std::vector<glm::vec4> alphaColors( VERTEX_COLORS.size() );
    for (size_t i = 0; i < VERTEX_COLORS.size(); i++) {
        alphaColors.at(i) = glm::vec4( VERTEX_COLORS[i], 1.0f );
    }
    return CSCI441_INTERNAL::SimpleShader2::registerVertexArray(VERTEX_POINTS.size(), VERTEX_POINTS.data(), alphaColors.data());
}

[[maybe_unused]]
inline GLuint CSCI441::SimpleShader2::registerVertexArray(const std::vector<glm::vec2>& VERTEX_POINTS, const std::vector<glm::vec4>& VERTEX_COLORS) {
    return CSCI441_INTERNAL::SimpleShader2::registerVertexArray(VERTEX_POINTS.size(), VERTEX_POINTS.data(), VERTEX_COLORS.data());
}

[[maybe_unused]]
inline void CSCI441::SimpleShader2::updateVertexArray(const GLuint VAOD, const std::vector<glm::vec2>& VERTEX_POINTS, const std::vector<glm::vec3>& VERTEX_COLORS) {
    std::vector<glm::vec4> alphaColors( VERTEX_COLORS.size() );
    for (size_t i = 0; i < VERTEX_COLORS.size(); i++) {
        alphaColors.at(i) = glm::vec4( VERTEX_COLORS[i], 1.0f );
    }
    CSCI441_INTERNAL::SimpleShader2::updateVertexArray(VAOD, VERTEX_POINTS.size(), VERTEX_POINTS.data(), alphaColors.data());
}

[[maybe_unused]]
inline void CSCI441::SimpleShader2::updateVertexArray(const GLuint VAOD, const std::vector<glm::vec2>& VERTEX_POINTS, const std::vector<glm::vec4>& VERTEX_COLORS) {
    CSCI441_INTERNAL::SimpleShader2::updateVertexArray(VAOD, VERTEX_POINTS.size(), VERTEX_POINTS.data(), VERTEX_COLORS.data());
}

[[maybe_unused]]
inline GLuint CSCI441::SimpleShader2::registerVertexArray(const GLuint NUM_POINTS, const glm::vec2 VERTEX_POINTS[], const glm::vec3 VERTEX_COLORS[]) {
    std::vector<glm::vec4> alphaColors(NUM_POINTS);
    for (GLuint i = 0; i < NUM_POINTS; i++) {
        alphaColors.at(i) = glm::vec4( VERTEX_COLORS[i], 1.0f );
    }
    return CSCI441_INTERNAL::SimpleShader2::registerVertexArray(NUM_POINTS, VERTEX_POINTS, alphaColors.data());
}

[[maybe_unused]]
inline void CSCI441::SimpleShader2::updateVertexArray(const GLuint VAOD, const GLuint NUM_POINTS, const glm::vec2 VERTEX_POINTS[], const glm::vec3 VERTEX_COLORS[]) {
    std::vector<glm::vec4> alphaColors(NUM_POINTS);
    for (GLuint i = 0; i < NUM_POINTS; i++) {
        alphaColors.at(i) = glm::vec4( VERTEX_COLORS[i], 1.0f );
    }
    CSCI441_INTERNAL::SimpleShader2::updateVertexArray(VAOD, NUM_POINTS, VERTEX_POINTS, alphaColors.data());
}

[[maybe_unused]]
inline void CSCI441::SimpleShader2::updateVertexArray(const GLuint VAOD, const GLuint NUM_POINTS, const glm::vec2 VERTEX_POINTS[], const glm::vec4 VERTEX_COLORS[]) {
    CSCI441_INTERNAL::SimpleShader2::updateVertexArray(VAOD, NUM_POINTS, VERTEX_POINTS, VERTEX_COLORS);
}

[[maybe_unused]]
inline void CSCI441::SimpleShader2::deleteVertexArray(const GLuint VAOD) {
    CSCI441_INTERNAL::SimpleShader2::deleteVertexArray(VAOD);
}

[[maybe_unused]]
inline void CSCI441::SimpleShader2::setProjectionMatrix(const glm::mat4& PROJECTION_MATRIX) {
    CSCI441_INTERNAL::SimpleShader2::setProjectionMatrix(PROJECTION_MATRIX);
}

[[maybe_unused]]
inline void CSCI441::SimpleShader2::pushTransformation(const glm::mat4& TRANSFORMATION_MATRIX) {
    CSCI441_INTERNAL::SimpleShader2::pushTransformation(TRANSFORMATION_MATRIX);
}

[[maybe_unused]]
inline void CSCI441::SimpleShader2::popTransformation() {
    CSCI441_INTERNAL::SimpleShader2::popTransformation();
}

[[maybe_unused]]
inline void CSCI441::SimpleShader2::resetTransformationMatrix() {
    CSCI441_INTERNAL::SimpleShader2::resetTransformationMatrix();
}

[[maybe_unused]]
inline void CSCI441::SimpleShader2::draw(const GLint PRIMITIVE_TYPE, const GLuint VAOD, const GLuint VERTEX_COUNT) {
    CSCI441_INTERNAL::SimpleShader2::draw(PRIMITIVE_TYPE, VAOD, VERTEX_COUNT);
}

//---------------------------------------------------------------------------------------------------------------------

[[maybe_unused]]
inline void CSCI441::SimpleShader3::enableFlatShading() {
    CSCI441_INTERNAL::SimpleShader3::enableFlatShading();
}

[[maybe_unused]]
inline void CSCI441::SimpleShader3::enableSmoothShading() {
    CSCI441_INTERNAL::SimpleShader3::enableSmoothShading();
}

[[maybe_unused]]
inline void CSCI441::SimpleShader3::setupSimpleShader() {
    CSCI441_INTERNAL::SimpleShader3::setupSimpleShader();
}

[[maybe_unused]]
inline GLuint CSCI441::SimpleShader3::registerVertexArray(const std::vector<glm::vec3>& VERTEX_POINTS, const std::vector<glm::vec3>& VERTEX_NORMALS) {
    return CSCI441_INTERNAL::SimpleShader3::registerVertexArray(VERTEX_POINTS.size(), VERTEX_POINTS.data(), VERTEX_NORMALS.data());
}

[[maybe_unused]]
inline void CSCI441::SimpleShader3::updateVertexArray(const GLuint VAOD, const std::vector<glm::vec3>& VERTEX_POINTS, const std::vector<glm::vec3>& VERTEX_NORMALS) {
    CSCI441_INTERNAL::SimpleShader3::updateVertexArray(VAOD, VERTEX_POINTS.size(), VERTEX_POINTS.data(), VERTEX_NORMALS.data());
}

[[maybe_unused]]
inline GLuint CSCI441::SimpleShader3::registerVertexArray(const GLuint NUM_POINTS, const glm::vec3 VERTEX_POINTS[], const glm::vec3 VERTEX_NORMALS[]) {
    return CSCI441_INTERNAL::SimpleShader3::registerVertexArray(NUM_POINTS, VERTEX_POINTS, VERTEX_NORMALS);
}

[[maybe_unused]]
inline void CSCI441::SimpleShader3::updateVertexArray(const GLuint VAOD, const GLuint NUM_POINTS, const glm::vec3 VERTEX_POINTS[], const glm::vec3 VERTEX_NORMALS[]) {
    CSCI441_INTERNAL::SimpleShader3::updateVertexArray(VAOD, NUM_POINTS, VERTEX_POINTS, VERTEX_NORMALS);
}

[[maybe_unused]]
inline void CSCI441::SimpleShader3::deleteVertexArray(const GLuint VAOD) {
    CSCI441_INTERNAL::SimpleShader3::deleteVertexArray(VAOD);
}

[[maybe_unused]]
inline void CSCI441::SimpleShader3::setProjectionMatrix(const glm::mat4& PROJECTION_MATRIX) {
    CSCI441_INTERNAL::SimpleShader3::setProjectionMatrix(PROJECTION_MATRIX);
}

[[maybe_unused]]
inline void CSCI441::SimpleShader3::setViewMatrix(const glm::mat4& VIEW_MATRIX) {
    CSCI441_INTERNAL::SimpleShader3::setViewMatrix(VIEW_MATRIX);
}

[[maybe_unused]]
inline void CSCI441::SimpleShader3::setLightPosition(const glm::vec3& LIGHT_POSITION) {
    CSCI441_INTERNAL::SimpleShader3::setLightPosition(LIGHT_POSITION);
}

[[maybe_unused]]
inline void CSCI441::SimpleShader3::setLightColor(const glm::vec3& LIGHT_COLOR) {
    CSCI441_INTERNAL::SimpleShader3::setLightColor(LIGHT_COLOR);
}

[[maybe_unused]]
inline void CSCI441::SimpleShader3::setMaterialColor(const glm::vec3& MATERIAL_COLOR) {
    CSCI441_INTERNAL::SimpleShader3::setMaterialColor(MATERIAL_COLOR);
}

[[maybe_unused]]
inline void CSCI441::SimpleShader3::pushTransformation(const glm::mat4& TRANSFORMATION_MATRIX) {
    CSCI441_INTERNAL::SimpleShader3::pushTransformation(TRANSFORMATION_MATRIX);
}

[[maybe_unused]]
inline void CSCI441::SimpleShader3::popTransformation() {
    CSCI441_INTERNAL::SimpleShader3::popTransformation();
}

[[maybe_unused]]
inline void CSCI441::SimpleShader3::resetTransformationMatrix() {
    CSCI441_INTERNAL::SimpleShader3::resetTransformationMatrix();
}

[[maybe_unused]]
inline void CSCI441::SimpleShader3::enableLighting() {
    CSCI441_INTERNAL::SimpleShader3::enableLighting();
}

[[maybe_unused]]
inline void CSCI441::SimpleShader3::disableLighting() {
    CSCI441_INTERNAL::SimpleShader3::disableLighting();
}

[[maybe_unused]]
inline void CSCI441::SimpleShader3::draw(const GLint PRIMITIVE_TYPE, const GLuint VAOD, const GLuint VERTEX_COUNT) {
    CSCI441_INTERNAL::SimpleShader3::draw(PRIMITIVE_TYPE, VAOD, VERTEX_COUNT);
}

////////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////
// Inward facing function implementations

inline void CSCI441_INTERNAL::SimpleShader2::enableFlatShading() {
    smoothShading = false;
}
inline void CSCI441_INTERNAL::SimpleShader2::enableSmoothShading() {
    smoothShading = true;
}

inline void CSCI441_INTERNAL::SimpleShader2::setupSimpleShader() {
    std::string vertex_shader_src =
R"_(
#version 410 core

uniform mat4 model;
uniform mat4 view;
uniform mat4 projection;

layout(location=0) in vec2 vPos;
layout(location=1) in vec4 vColor;

layout(location=0) )_";
    vertex_shader_src += (smoothShading ? "" : "flat ");
    vertex_shader_src += R"_(out vec4 fragColor;

void main() {
    gl_Position = projection * view * model * vec4(vPos, 0.0, 1.0);
    fragColor = vColor;
})_";
    const char* vertexShaders[1] = { vertex_shader_src.c_str() };

    std::string fragment_shader_src =
R"_(
#version 410 core

layout(location=0) )_";
    fragment_shader_src += (smoothShading ? "" : "flat ");
    fragment_shader_src += R"_( in vec4 fragColor;

layout(location=0) out vec4 fragColorOut;

void main() {
    fragColorOut = fragColor;
})_";
    const char* fragmentShaders[1] = { fragment_shader_src.c_str() };

    printf( "[INFO]: /--------------------------------------------------------\\\n" );

    const GLuint vertexShaderHandle = glCreateShader( GL_VERTEX_SHADER );
    glShaderSource(vertexShaderHandle, 1, vertexShaders, nullptr);
    glCompileShader(vertexShaderHandle);
    ShaderUtils::printShaderLog(vertexShaderHandle);

    const GLuint fragmentShaderHandle = glCreateShader( GL_FRAGMENT_SHADER );
    glShaderSource(fragmentShaderHandle, 1, fragmentShaders, nullptr);
    glCompileShader(fragmentShaderHandle);
    ShaderUtils::printShaderLog(fragmentShaderHandle);

    shaderProgramHandle = glCreateProgram();
    glAttachShader(shaderProgramHandle, vertexShaderHandle);
    glAttachShader(shaderProgramHandle, fragmentShaderHandle);
    glLinkProgram(shaderProgramHandle);
    ShaderUtils::printProgramLog(shaderProgramHandle);

    glDetachShader(shaderProgramHandle, vertexShaderHandle);
    glDeleteShader(vertexShaderHandle);

    glDetachShader(shaderProgramHandle, fragmentShaderHandle);
    glDeleteShader(fragmentShaderHandle);

    ShaderUtils::printShaderProgramInfo(shaderProgramHandle, true, false, false, false, true, false, true);

    modelLocation       = glGetUniformLocation(shaderProgramHandle, "model");
    viewLocation        = glGetUniformLocation(shaderProgramHandle, "view");
    projectionLocation  = glGetUniformLocation(shaderProgramHandle, "projection");

    vertexLocation      = glGetAttribLocation(shaderProgramHandle, "vPos");
    colorLocation       = glGetAttribLocation(shaderProgramHandle, "vColor");


    glm::mat4 identity(1.0f);
    glProgramUniformMatrix4fv(shaderProgramHandle, modelLocation, 1, GL_FALSE, glm::value_ptr(identity));
    glProgramUniformMatrix4fv(shaderProgramHandle, viewLocation, 1, GL_FALSE, glm::value_ptr(identity));
    glProgramUniformMatrix4fv(shaderProgramHandle, projectionLocation, 1, GL_FALSE, glm::value_ptr(identity));

    transformationStack.emplace_back(identity);

    glUseProgram(shaderProgramHandle);
}

inline GLuint CSCI441_INTERNAL::SimpleShader2::registerVertexArray(const GLuint NUM_POINTS, const glm::vec2 VERTEX_POINTS[], const glm::vec4 VERTEX_COLORS[]) {
    GLuint vaod;
    glGenVertexArrays(1, &vaod);
    glBindVertexArray(vaod);

    GLuint vbod;
    glGenBuffers(1, &vbod);
    glBindBuffer(GL_ARRAY_BUFFER, vbod);
    glBufferData(GL_ARRAY_BUFFER, static_cast<GLsizeiptr>(sizeof(GLfloat)*NUM_POINTS*2 + sizeof(GLfloat)*NUM_POINTS*4), nullptr, GL_STATIC_DRAW);
    glBufferSubData(GL_ARRAY_BUFFER, 0, static_cast<GLsizeiptr>(sizeof(GLfloat)*NUM_POINTS*2), VERTEX_POINTS);
    glBufferSubData(GL_ARRAY_BUFFER, static_cast<GLintptr>(sizeof(GLfloat)*NUM_POINTS*2), static_cast<GLsizeiptr>(sizeof(GLfloat)*NUM_POINTS*4), VERTEX_COLORS);

    glEnableVertexAttribArray(vertexLocation);
    glVertexAttribPointer(vertexLocation, 2, GL_FLOAT, GL_FALSE, 0, static_cast<void *>(nullptr));

    glEnableVertexAttribArray(colorLocation);
    glVertexAttribPointer(colorLocation, 4, GL_FLOAT, GL_FALSE, 0, reinterpret_cast<void *>(sizeof(GLfloat) * NUM_POINTS * 2));

    descriptorMap.insert( std::pair( vaod, vbod ) );

    return vaod;
}

inline void CSCI441_INTERNAL::SimpleShader2::updateVertexArray(const GLuint VAOD, const GLuint NUM_POINTS, const glm::vec2 VERTEX_POINTS[], const glm::vec4 VERTEX_COLORS[]) {
    const auto descriptorIter = descriptorMap.find(VAOD);
    if( descriptorIter != descriptorMap.end() ) {
        glBindVertexArray(descriptorIter->first);
        glBindBuffer(GL_ARRAY_BUFFER, descriptorIter->second);
        glBufferSubData(GL_ARRAY_BUFFER, 0, static_cast<GLsizeiptr>(sizeof(GLfloat)*NUM_POINTS*2), VERTEX_POINTS);
        glBufferSubData(GL_ARRAY_BUFFER, static_cast<GLintptr>(sizeof(GLfloat)*NUM_POINTS*2), static_cast<GLsizeiptr>(sizeof(GLfloat)*NUM_POINTS*4), VERTEX_COLORS);
    }
}

inline void CSCI441_INTERNAL::SimpleShader2::deleteVertexArray(const GLuint VAOD) {
    const auto descriptorIter = descriptorMap.find(VAOD);
    if( descriptorIter != descriptorMap.end() ) {
        glDeleteVertexArrays(1, &(descriptorIter->first));
        glDeleteBuffers(1, &(descriptorIter->second));
        descriptorMap.erase(descriptorIter);
    }
}

inline void CSCI441_INTERNAL::SimpleShader2::setProjectionMatrix(const glm::mat4& PROJECTION_MATRIX) {
    glProgramUniformMatrix4fv(shaderProgramHandle, projectionLocation, 1, GL_FALSE, glm::value_ptr(PROJECTION_MATRIX));
}

inline void CSCI441_INTERNAL::SimpleShader2::pushTransformation(const glm::mat4& TRANSFORMATION_MATRIX) {
    transformationStack.emplace_back(TRANSFORMATION_MATRIX);

    modelMatrix *= TRANSFORMATION_MATRIX;
    glProgramUniformMatrix4fv(shaderProgramHandle, modelLocation, 1, GL_FALSE, glm::value_ptr(modelMatrix));
}

inline void CSCI441_INTERNAL::SimpleShader2::popTransformation() {
    // ensure there is a transformation stack to pop off
    // never let the original identity matrix pop off
    if( transformationStack.size() > 1 ) {
        transformationStack.pop_back();

        modelMatrix = glm::mat4(1.0f);
        for( auto tMtx : transformationStack ) {
            modelMatrix *= tMtx;
        }
        glProgramUniformMatrix4fv( shaderProgramHandle, modelLocation, 1, GL_FALSE, glm::value_ptr(modelMatrix) );
    }
}

inline void CSCI441_INTERNAL::SimpleShader2::resetTransformationMatrix() {
    modelMatrix = glm::mat4(1.0f);
    transformationStack.clear();
    transformationStack.emplace_back(modelMatrix);
    glProgramUniformMatrix4fv(shaderProgramHandle, modelLocation, 1, GL_FALSE, glm::value_ptr(modelMatrix));
}

inline void CSCI441_INTERNAL::SimpleShader2::draw(const GLint PRIMITIVE_TYPE, const GLuint VAOD, const GLuint VERTEX_COUNT) {
    glUseProgram(shaderProgramHandle);
    glBindVertexArray(VAOD);
    glDrawArrays(PRIMITIVE_TYPE, 0, static_cast<GLsizei>(VERTEX_COUNT));
}

//---------------------------------------------------------------------------------------------------------------------

inline void CSCI441_INTERNAL::SimpleShader3::enableFlatShading() {
    smoothShading = false;
}
inline void CSCI441_INTERNAL::SimpleShader3::enableSmoothShading() {
    smoothShading = true;
}

inline void CSCI441_INTERNAL::SimpleShader3::setupSimpleShader() {
    std::string vertex_shader_src =
R"_(
#version 410 core

uniform mat4 model;
uniform mat4 view;
uniform mat4 projection;
uniform mat3 normalMtx;
uniform vec3 lightColor;
uniform vec3 lightPosition;
uniform vec3 materialColor;

layout(location=0) in vec3 vPos;
layout(location=2) in vec3 vNormal;

layout(location=0) )_";
    vertex_shader_src += (smoothShading ? "" : "flat ");
    vertex_shader_src += R"_(out vec4 fragColor;

void main() {
    gl_Position = projection * view * model * vec4(vPos, 1.0);

    vec3 vertexEye = (view * model * vec4(vPos, 1.0)).xyz;
    vec3 lightEye = (view * vec4(lightPosition, 1.0)).xyz;
    vec3 lightVec = normalize( lightEye - vertexEye );
    vec3 normalVec = normalize( normalMtx * vNormal );
    float sDotN = max(dot(lightVec, normalVec), 0.0);
    vec3 diffColor = lightColor * materialColor * sDotN;
    vec3 ambColor = materialColor * 0.3;
    vec3 color = diffColor + ambColor;
    fragColor = vec4(color, 1.0);
})_";
    const char* vertexShaders[1] = { vertex_shader_src.c_str() };

    std::string fragment_shader_src =
R"_(#version 410 core

uniform vec3 materialColor;
uniform int useLighting;

layout(location=0) )_";
    fragment_shader_src += (smoothShading ? "" : "flat ");
    fragment_shader_src += R"_( in vec4 fragColor;

layout(location=0) out vec4 fragColorOut;

void main() {
    if(useLighting == 1) {
        fragColorOut = fragColor;
    } else {
        fragColorOut = vec4(materialColor, 1.0f);
    }
})_";
    const char* fragmentShaders[1] = { fragment_shader_src.c_str() };

    printf( "[INFO]: /--------------------------------------------------------\\\n" );

    GLuint vertexShaderHandle = glCreateShader( GL_VERTEX_SHADER );
    glShaderSource(vertexShaderHandle, 1, vertexShaders, nullptr);
    glCompileShader(vertexShaderHandle);
    ShaderUtils::printShaderLog(vertexShaderHandle);

    GLuint fragmentShaderHandle = glCreateShader( GL_FRAGMENT_SHADER );
    glShaderSource(fragmentShaderHandle, 1, fragmentShaders, nullptr);
    glCompileShader(fragmentShaderHandle);
    ShaderUtils::printShaderLog(fragmentShaderHandle);

    shaderProgramHandle = glCreateProgram();
    glAttachShader(shaderProgramHandle, vertexShaderHandle);
    glAttachShader(shaderProgramHandle, fragmentShaderHandle);
    glLinkProgram(shaderProgramHandle);
    ShaderUtils::printProgramLog(shaderProgramHandle);

    glDetachShader(shaderProgramHandle, vertexShaderHandle);
    glDeleteShader(vertexShaderHandle);

    glDetachShader(shaderProgramHandle, fragmentShaderHandle);
    glDeleteShader(fragmentShaderHandle);

    ShaderUtils::printShaderProgramInfo(shaderProgramHandle, true, false, false, false, true, false, true);

    modelLocation       = glGetUniformLocation(shaderProgramHandle, "model");
    viewLocation        = glGetUniformLocation(shaderProgramHandle, "view");
    projectionLocation  = glGetUniformLocation(shaderProgramHandle, "projection");
    normalMtxLocation   = glGetUniformLocation(shaderProgramHandle, "normalMtx");
    lightPositionLocation=glGetUniformLocation(shaderProgramHandle, "lightPosition");
    lightColorLocation  = glGetUniformLocation(shaderProgramHandle, "lightColor");
    materialLocation    = glGetUniformLocation(shaderProgramHandle, "materialColor");
    useLightingLocation = glGetUniformLocation(shaderProgramHandle, "useLighting");

    vertexLocation      = glGetAttribLocation(shaderProgramHandle, "vPos");
    normalLocation      = glGetAttribLocation(shaderProgramHandle, "vNormal");

    glm::mat4 identity(1.0f);
    glProgramUniformMatrix4fv(shaderProgramHandle, modelLocation, 1, GL_FALSE, glm::value_ptr(identity));
    glProgramUniformMatrix4fv(shaderProgramHandle, viewLocation, 1, GL_FALSE, glm::value_ptr(identity));
    glProgramUniformMatrix4fv(shaderProgramHandle, projectionLocation, 1, GL_FALSE, glm::value_ptr(identity));

    transformationStack.emplace_back(identity);

    glm::vec3 white(1.0f, 1.0f, 1.0f);
    glProgramUniform3fv(shaderProgramHandle, lightColorLocation, 1, glm::value_ptr(white));
    glProgramUniform3fv(shaderProgramHandle, materialLocation, 1, glm::value_ptr(white));

    glm::vec3 origin(0.0f, 0.0f, 0.0f);
    glProgramUniform3fv(shaderProgramHandle, lightPositionLocation, 1, glm::value_ptr(origin));

    glProgramUniform1i(shaderProgramHandle, useLightingLocation, 1);

    glUseProgram(shaderProgramHandle);
    CSCI441::setVertexAttributeLocations(vertexLocation, normalLocation);
}

inline GLuint CSCI441_INTERNAL::SimpleShader3::registerVertexArray(const GLuint NUM_POINTS, const glm::vec3 VERTEX_POINTS[], const glm::vec3 VERTEX_NORMALS[]) {
    GLuint vaod;
    glGenVertexArrays(1, &vaod);
    glBindVertexArray(vaod);

    GLuint vbod;
    glGenBuffers(1, &vbod);
    glBindBuffer(GL_ARRAY_BUFFER, vbod);
    glBufferData(GL_ARRAY_BUFFER, static_cast<GLsizeiptr>(sizeof(GLfloat)*NUM_POINTS*3 + sizeof(GLfloat)*NUM_POINTS*3), nullptr, GL_STATIC_DRAW);
    glBufferSubData(GL_ARRAY_BUFFER, 0, static_cast<GLsizeiptr>(sizeof(GLfloat)*NUM_POINTS*3), VERTEX_POINTS);
    glBufferSubData(GL_ARRAY_BUFFER, static_cast<GLintptr>(sizeof(GLfloat)*NUM_POINTS*3), static_cast<GLsizeiptr>(sizeof(GLfloat)*NUM_POINTS*3), VERTEX_NORMALS);

    glEnableVertexAttribArray(vertexLocation);
    glVertexAttribPointer(vertexLocation, 3, GL_FLOAT, GL_FALSE, 0, (void*)nullptr);

    glEnableVertexAttribArray(normalLocation);
    glVertexAttribPointer(normalLocation, 3, GL_FLOAT, GL_FALSE, 0, (void*)(sizeof(GLfloat)*NUM_POINTS*2));

    descriptorMap.insert( std::pair<GLuint, GLuint>( vaod, vbod ) );

    return vaod;
}

inline void CSCI441_INTERNAL::SimpleShader3::updateVertexArray(const GLuint VAOD, const GLuint NUM_POINTS, const glm::vec3 VERTEX_POINTS[], const glm::vec3 VERTEX_NORMALS[]) {
    const auto descriptorIter = descriptorMap.find(VAOD);
    if( descriptorIter != descriptorMap.end() ) {
        glBindVertexArray(descriptorIter->first);
        glBindBuffer(GL_ARRAY_BUFFER, descriptorIter->second);
        glBufferSubData(GL_ARRAY_BUFFER, 0, static_cast<GLsizeiptr>(sizeof(GLfloat)*NUM_POINTS*3), VERTEX_POINTS);
        glBufferSubData(GL_ARRAY_BUFFER, static_cast<GLintptr>(sizeof(GLfloat)*NUM_POINTS*3), static_cast<GLsizeiptr>(sizeof(GLfloat)*NUM_POINTS*3), VERTEX_NORMALS);
    }
}

inline void CSCI441_INTERNAL::SimpleShader3::deleteVertexArray(const GLuint VAOD) {
    const auto descriptorIter = descriptorMap.find(VAOD);
    if( descriptorIter != descriptorMap.end() ) {
        glDeleteVertexArrays(1, &(descriptorIter->first));
        glDeleteBuffers(1, &(descriptorIter->second));
        descriptorMap.erase(descriptorIter);
    }
}

inline void CSCI441_INTERNAL::SimpleShader3::setProjectionMatrix(const glm::mat4& PROJECTION_MATRIX) {
    glProgramUniformMatrix4fv(shaderProgramHandle, projectionLocation, 1, GL_FALSE, glm::value_ptr(PROJECTION_MATRIX));
}

inline void CSCI441_INTERNAL::SimpleShader3::setViewMatrix(const glm::mat4& VIEW_MATRIX) {
    glProgramUniformMatrix4fv(shaderProgramHandle, viewLocation, 1, GL_FALSE, glm::value_ptr(VIEW_MATRIX));

    viewMatrix = VIEW_MATRIX;
    setNormalMatrix();
}

inline void CSCI441_INTERNAL::SimpleShader3::setLightPosition(const glm::vec3& LIGHT_POSITION) {
    glProgramUniform3fv(shaderProgramHandle, lightPositionLocation, 1, glm::value_ptr(LIGHT_POSITION));
}

inline void CSCI441_INTERNAL::SimpleShader3::setLightColor(const glm::vec3& LIGHT_COLOR) {
    glProgramUniform3fv(shaderProgramHandle, lightColorLocation, 1, glm::value_ptr(LIGHT_COLOR));
}

inline void CSCI441_INTERNAL::SimpleShader3::setMaterialColor(const glm::vec3& MATERIAL_COLOR) {
    glProgramUniform3fv(shaderProgramHandle, materialLocation, 1, glm::value_ptr(MATERIAL_COLOR));
}

inline void CSCI441_INTERNAL::SimpleShader3::pushTransformation(const glm::mat4& TRANSFORMATION_MATRIX) {
    transformationStack.emplace_back(TRANSFORMATION_MATRIX);

    modelMatrix *= TRANSFORMATION_MATRIX;
    glProgramUniformMatrix4fv(shaderProgramHandle, modelLocation, 1, GL_FALSE, glm::value_ptr(modelMatrix));

    setNormalMatrix();
}

inline void CSCI441_INTERNAL::SimpleShader3::popTransformation() {
    // ensure there is a transformation stack to pop off
    // never let the original identity matrix pop off
    if( transformationStack.size() > 1 ) {
        transformationStack.pop_back();

        modelMatrix = glm::mat4(1.0f);
        for( auto tMtx : transformationStack ) {
            modelMatrix *= tMtx;
        }
        glProgramUniformMatrix4fv( shaderProgramHandle, modelLocation, 1, GL_FALSE, glm::value_ptr(modelMatrix) );

        setNormalMatrix();
    }
}

inline void CSCI441_INTERNAL::SimpleShader3::resetTransformationMatrix() {
    modelMatrix = glm::mat4(1.0f);
    transformationStack.clear();
    transformationStack.emplace_back(modelMatrix);
    glProgramUniformMatrix4fv(shaderProgramHandle, modelLocation, 1, GL_FALSE, glm::value_ptr(modelMatrix));
    setNormalMatrix();
}

inline void CSCI441_INTERNAL::SimpleShader3::setNormalMatrix() {
    glm::mat4 modelView = viewMatrix * modelMatrix;
    glm::mat3 normalMatrix = glm::mat3( glm::transpose( glm::inverse( modelView ) ) );
    glProgramUniformMatrix3fv(shaderProgramHandle, normalMtxLocation, 1, GL_FALSE, glm::value_ptr(normalMatrix));
}

inline void CSCI441_INTERNAL::SimpleShader3::enableLighting() {
    glProgramUniform1i(shaderProgramHandle, useLightingLocation, 1);
}

inline void CSCI441_INTERNAL::SimpleShader3::disableLighting() {
    glProgramUniform1i(shaderProgramHandle, useLightingLocation, 0);
}

inline void CSCI441_INTERNAL::SimpleShader3::draw(const GLint PRIMITIVE_TYPE, const GLuint VAOD, const GLuint VERTEX_COUNT) {
    glUseProgram(shaderProgramHandle);
    glBindVertexArray(VAOD);
    glDrawArrays(PRIMITIVE_TYPE, 0, static_cast<GLsizei>(VERTEX_COUNT));
}

#endif //__CSCI441_SIMPLE_SHADER_HPP__
