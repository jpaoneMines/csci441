/** @file objects_impl.hpp
 * @brief Helper functions to draw 3D OpenGL 3.0+ objects
 * @author Dr. Jeffrey Paone
 *
 * @copyright MIT License Copyright (c) 2017 Dr. Jeffrey Paone
 *
 *	These functions draw solid (or wireframe) 3D closed OpenGL
 *	objects.  All objects are constructed using triangles that
 *	have normals and texture coordinates properly set.
 *
 *	@warning NOTE: This header file will only work with OpenGL 3.0+
 *	@warning NOTE: This header file depends upon GLAD (or alternatively GLEW)
 */

#ifndef CSCI441_OBJECTS_IMPL_HPP
#define CSCI441_OBJECTS_IMPL_HPP

#include "OpenGLUtils.hpp"
#include "teapot.hpp"

#ifdef CSCI441_USE_GLEW
    #include <GL/glew.h>
#else
    #include <glad/gl.h>
#endif

#include <glm/trigonometric.hpp>

#include <map>							// for map

////////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////
// Internal rendering implementations to stay consistent with solid and wire modes
//
// Cone is drawn with a cylinder
// Disk is drawn with a partial disk

/**
 * @namespace CSCI441_INTERNAL
 * @brief implementations of public facing methods
 */
namespace CSCI441_INTERNAL {
    /**
     * @brief delete all the VAOs from the GPU
     */
    void deleteObjectVAOs();
    /**
     * @brief delete all the VBOs from the GPU
     */
    void deleteObjectVBOs();

    /**
     * @brief draws an indexed cube where vertex normals are the sum of the three faces
     * @param sideLength side length
     * @param renderMode filled polygon (GL_FILL) or line edges (GL_LINES)
     */
    void drawCube( GLfloat sideLength, GLenum renderMode );
    /**
     * @brief draws an indexed cube where vertex normals are the sum of the three faces
     * @param sideLength side length
     * @param renderMode filled polygon (GL_FILL) or line edges (GL_LINES)
     */
    void drawCubeIndexed( GLfloat sideLength, GLenum renderMode );
    /**
     * @brief draws a flat cube where vertex normals are aligned with the face of the cube
     * @param sideLength side length
     * @param renderMode filled polygon (GL_FILL) or line edges (GL_LINES)
     */
    void drawCubeFlat( GLfloat sideLength, GLenum renderMode );
    /**
     * @brief draws a cylinder
     * @note iff one of the base or top is zero and the other is non-zero, then a cone can be drawn
     * @param base radius of the base of the cylinder
     * @param top radius of the top of the cylinder
     * @param height height of the cylinder
     * @param stacks resolution of the number of steps rotated around the central axis of the cylinder
     * @param slices resolution of the number of steps to take along the height
     * @param renderMode filled polygon (GL_FILL) or line edges (GL_LINES)
     */
    void drawCylinder( GLfloat base, GLfloat top, GLfloat height, GLuint stacks, GLuint slices, GLenum renderMode );
    /**
     * @brief Draws a disk
     * @param innerRadius equivalent to the width of the disk
     * @param outerRadius radius from the center of the disk to the center of the ring
     * @param slices resolution of the number of steps rotated along the disk
     * @param rings resolution of the number of steps to take along the disk width
     * @param startAngle angle in degrees to start the disk at
     * @param sweepAngle distance in degrees to rotate through
     * @param renderMode filled polygon (GL_FILL) or line edges (GL_LINES)
     */
    void drawPartialDisk(GLfloat innerRadius, GLfloat outerRadius, GLuint slices, GLuint rings, GLfloat startAngle, GLfloat sweepAngle, GLenum renderMode );
    /**
     * @brief Draws a sphere
     * @param radius radius of the sphere
     * @param stacks resolution of the number of steps to take along theta (rotate around Y-axis)
     * @param slices resolution of the number of steps to take along phi (rotate around X- or Z-axis)
     * @param renderMode filled polygon (GL_FILL) or line edges (GL_LINES)
     */
    void drawSphere( GLfloat radius, GLuint stacks, GLuint slices, GLenum renderMode );
    /**
     * @brief Draws a half sphere with a bottom
     * @param radius radius of the sphere
     * @param stacks resolution of the number of steps to take along theta (rotate around Y-axis)
     * @param slices resolution of the number of steps to take along phi (rotate around X- or Z-axis)
     * @param renderMode filled polygon (GL_FILL) or line edges (GL_LINES)
     */
    void drawHalfSphere( GLfloat radius, GLuint stacks, GLuint slices, GLenum renderMode );
    /**
     * @brief Draws a dome
     * @param radius radius of the dome
     * @param stacks resolution of the number of steps to take along theta (rotate around Y-axis)
     * @param slices resolution of the number of steps to take along phi (rotate around X- or Z-axis)
     * @param renderMode filled polygon (GL_FILL) or line edges (GL_LINES)
     */
    void drawDome( GLfloat radius, GLuint stacks, GLuint slices, GLenum renderMode );
    /**
     * @brief Draws a torus
     * @param innerRadius equivalent to the width of the torus ring
     * @param outerRadius radius from the center of the torus to the center of the ring
     * @param sides resolution of steps to take around the band of the ring
     * @param rings resolution of steps to take around the torus
     * @param renderMode filled polygon (GL_FILL) or line edges (GL_LINES)
     */
    void drawTorus( GLfloat innerRadius, GLfloat outerRadius, GLuint sides, GLuint rings, GLenum renderMode );
    /**
     * @brief draws the Utah Teapot
     * @param renderMode filled polygon (GL_FILL) or line edges (GL_LINES)
     */
    void drawTeapot( GLenum renderMode );

    /**
     * @brief location of the vertex position attribute within the shader being rendered with
     */
    inline GLint _positionAttributeLocation = -1;
    /**
     * @brief location of the vertex normal attribute within the shader being rendered with
     */
    inline GLint _normalAttributeLocation = -1;
    /**
     * @brief location of the vertex texture coordinate attribute within the shader being rendered with
     */
    inline GLint _texCoordAttributeLocation = -1;
    /**
     * @brief location of the vertex tangent coordinate attribute within the shader being rendered with
     */
    inline GLint _tangentAttributeLocation = -1;

    /**
     * @brief creates the VAO + VBO using 36 vertices
     * @param sideLength
     */
    void generateCubeVAOFlat( GLfloat sideLength );

    /**
     * @brief creates the VAO + VBO + IBO using 8 vertices
     * @param sideLength
     */
    void generateCubeVAOIndexed( GLfloat sideLength );
    /**
     * @brief caches the VAO for a given side length
     */
    inline std::map< GLfloat, GLuint > _cubeVAO;
    /**
     * @brief caches the VBO for a given side length
     */
    inline std::map< GLfloat, GLuint > _cubeVBO;
    /**
     * @brief caches the VAO for a given side length
     */
    inline std::map< GLfloat, GLuint > _cubeVAOIndexed;
    /**
     * @brief caches the VBO for a given side length
     */
    inline std::map< GLfloat, GLuint > _cubeVBOIndexed;
    /**
     * @brief caches the IBO for a given side length
     */
    inline std::map< GLfloat, GLuint > _cubeIBOIndexed;

    /// \desc stores data necessary to specify a unique cylinder
    struct CylinderData {
        /// \desc radius of the base
        GLfloat radiusBase;
        /// \desc radius of the top
        GLfloat radiusTop;
        /// \desc height
        GLfloat height;
        /// \desc number of stacks
        GLuint stacks;
        /// \desc number of slices
        GLuint slices;
        /// \desc compute number of vertices
        [[nodiscard]] GLuint64 numVertices() const { return stacks * (slices + 1) * 2; }
        /// \desc less than comparison operator used to sort
        bool operator<( const CylinderData rhs ) const {
            if( radiusBase < rhs.radiusBase ) {
                return true;
            } else if( fabs(radiusBase - rhs.radiusBase) <= 0.000001 ) {
                if( radiusTop < rhs.radiusTop ) {
                    return true;
                } else if( fabs(radiusTop - rhs.radiusTop) <= 0.000001 ) {
                    if( height < rhs.height ) {
                        return true;
                    } else if( fabs(height - rhs.height) <= 0.000001 ) {
                        if( stacks < rhs.stacks ) {
                            return true;
                        } else if( stacks == rhs.stacks ) {
                            if( slices < rhs.slices ) {
                                return true;
                            }
                        }
                    }
                }
            }
            return false;
        }
    };
    void generateCylinderVAO( const CylinderData& cylData );
    inline std::map< CylinderData, GLuint > _cylinderVAO;
    inline std::map< CylinderData, GLuint > _cylinderVBO;

    struct DiskData {
        GLfloat innerRadius, outerRadius, startAngle, sweepAngle;
        GLuint slices, rings;
        [[nodiscard]] GLuint64 numVertices() const { return rings * (slices + 1) * 2; }
        bool operator<( const DiskData rhs ) const {
            if( innerRadius < rhs.innerRadius ) {
                return true;
            } else if( fabs(innerRadius - rhs.innerRadius) <= 0.000001 ) {
                if( outerRadius < rhs.outerRadius ) {
                    return true;
                } else if( fabs(outerRadius - rhs.outerRadius) <= 0.000001 ) {
                    if( startAngle < rhs.startAngle ) {
                        return true;
                    } else if( fabs(startAngle - rhs.startAngle) <= 0.000001 ) {
                        if( sweepAngle < rhs.sweepAngle ) {
                            return true;
                        } else if( fabs(sweepAngle - rhs.sweepAngle) <= 0.000001 ) {
                            if( slices < rhs.slices ) {
                                return true;
                            } else if( slices == rhs.slices ) {
                                if(rings < rhs.rings ) {
                                    return true;
                                }
                            }
                        }
                    }
                }
            }
            return false;
        }
    };
    void generateDiskVAO( const DiskData& diskData );
    inline std::map< DiskData, GLuint > _diskVAO;
    inline std::map< DiskData, GLuint > _diskVBO;

    struct SphereData {
        GLfloat radius;
        GLuint stacks, slices;
        [[nodiscard]] GLuint64 numVertices() const { return ((slices + 2) * 2) + (((stacks - 2) * (slices+1)) * 2); }
        bool operator<( const SphereData rhs ) const {
            if( radius < rhs.radius ) {
                return true;
            } else if( fabs(radius - rhs.radius) <= 0.000001 ) {
                if( stacks < rhs.stacks ) {
                    return true;
                } else if( stacks == rhs.stacks ) {
                    if( slices < rhs.slices ) {
                        return true;
                    }
                }
            }
            return false;
        }
    };
    void generateSphereVAO( const SphereData& sphereData );
    inline std::map< SphereData, GLuint > _sphereVAO;
    inline std::map< SphereData, GLuint > _sphereVBO;

    struct TorusData {
        GLfloat innerRadius, outerRadius;
        GLuint sides, rings;
        [[nodiscard]] GLuint64 numVertices() const { return sides * 4 * rings; }
        bool operator<( const TorusData rhs ) const {
            if( innerRadius < rhs.innerRadius ) {
                return true;
            } else if( fabs(innerRadius - rhs.innerRadius) <= 0.000001 ) {
                if( outerRadius < rhs.outerRadius ) {
                    return true;
                } else if( fabs(outerRadius - rhs.outerRadius) <= 0.000001 ) {
                    if( sides < rhs.sides ) {
                        return true;
                    } else if( sides == rhs.sides ) {
                        if( rings < rhs.rings ) {
                            return true;
                        }
                    }
                }
            }
            return false;
        }
    };
    void generateTorusVAO( const TorusData& torusData );
    inline std::map< TorusData, GLuint > _torusVAO;
    inline std::map< TorusData, GLuint > _torusVBO;
}

////////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////
// Internal function rendering implementations

inline void CSCI441_INTERNAL::deleteObjectVAOs() {
    for(auto &[sideLength, vaod] : _cubeVAO) {
        glDeleteVertexArrays(1, &vaod);
    }
    _cubeVAO.clear();

    for(auto &[sideLength, vaod] : _cubeVAOIndexed) {
        glDeleteVertexArrays(1, &vaod);
    }
    _cubeVAOIndexed.clear();

    for(auto &[cylData, vaod] : _cylinderVAO) {
        glDeleteVertexArrays(1, &vaod);
    }
    _cylinderVAO.clear();

    for(auto &[diskData, vaod] : _diskVAO) {
        glDeleteVertexArrays(1, &vaod);
    }
    _diskVAO.clear();

    for(auto &[sphereData, vaod] : _sphereVAO) {
        glDeleteVertexArrays(1, &vaod);
    }
    _sphereVAO.clear();

    for(auto &[torusData, vaod] : _torusVAO) {
        glDeleteVertexArrays(1, &vaod);
    }
    _torusVAO.clear();
}

inline void CSCI441_INTERNAL::deleteObjectVBOs() {
    for(auto &[sideLength, vbod] : _cubeVBO) {
        glDeleteBuffers(1, &vbod);
    }
    _cubeVBO.clear();

    for(auto &[sideLength, vbod] : _cubeVBOIndexed) {
        glDeleteBuffers(1, &vbod);
    }
    _cubeVBOIndexed.clear();

    for(auto &[sideLength, vbod] : _cubeIBOIndexed) {
        glDeleteBuffers(1, &vbod);
    }
    _cubeIBOIndexed.clear();

    for(auto &[cylData, vbod] : _cylinderVBO) {
        glDeleteBuffers(1, &vbod);
    }
    _cylinderVBO.clear();

    for(auto &[diskData, vbod] : _diskVBO) {
        glDeleteBuffers(1, &vbod);
    }
    _diskVBO.clear();

    for(auto &[sphereData, vbod] : _sphereVBO) {
        glDeleteBuffers(1, &vbod);
    }
    _sphereVBO.clear();

    for(auto &[torusData, vbod] : _torusVBO) {
        glDeleteBuffers(1, &vbod);
    }
    _torusVBO.clear();
}

inline void CSCI441_INTERNAL::drawCube( const GLfloat sideLength, const GLenum renderMode ) {
    drawCubeIndexed(sideLength, renderMode);
}

inline void CSCI441_INTERNAL::drawCubeFlat( const GLfloat sideLength, const GLenum renderMode ) {
    if( _cubeVAO.count( sideLength ) == 0 ) {
        generateCubeVAOFlat( sideLength );
    }

    constexpr GLuint64 NUM_VERTICES = 36;

    GLint currentPolygonMode[2];
    glGetIntegerv(GL_POLYGON_MODE, currentPolygonMode);

    glPolygonMode( GL_FRONT_AND_BACK, renderMode );
    glBindVertexArray( _cubeVAO.find( sideLength )->second );
    glBindBuffer( GL_ARRAY_BUFFER, _cubeVBO.find( sideLength )->second );
    if(_positionAttributeLocation != -1) {
        glEnableVertexAttribArray( _positionAttributeLocation );
        glVertexAttribPointer( _positionAttributeLocation, 3, GL_FLOAT, GL_FALSE, 0, nullptr );
    }
    if(_normalAttributeLocation != -1) {
        glEnableVertexAttribArray( _normalAttributeLocation );
        glVertexAttribPointer( _normalAttributeLocation, 3, GL_FLOAT, GL_FALSE, 0, reinterpret_cast<void *>(sizeof(glm::vec3) * NUM_VERTICES) );
    }
    if(_texCoordAttributeLocation != -1) {
        glEnableVertexAttribArray( _texCoordAttributeLocation );
        glVertexAttribPointer( _texCoordAttributeLocation, 2, GL_FLOAT, GL_FALSE, 0, reinterpret_cast<void *>(sizeof(glm::vec3) * NUM_VERTICES * 2) );
    }
    if (_tangentAttributeLocation != -1) {
        glEnableVertexAttribArray( _tangentAttributeLocation );
        glVertexAttribPointer( _tangentAttributeLocation, 4, GL_FLOAT, GL_FALSE, 0, reinterpret_cast<void *>(sizeof(glm::vec3) * NUM_VERTICES * 2 + sizeof(glm::vec2) * NUM_VERTICES) );
    }

    glDrawArrays( GL_TRIANGLES, 0, 36 );

    glPolygonMode( GL_FRONT_AND_BACK, currentPolygonMode[0] );
}

inline void CSCI441_INTERNAL::drawCubeIndexed( const GLfloat sideLength, const GLenum renderMode ) {
    if( _cubeVAOIndexed.count( sideLength ) == 0 ) {
        generateCubeVAOIndexed( sideLength );
    }

    constexpr GLuint64 NUM_VERTICES = 8;

    GLint currentPolygonMode[2];
    glGetIntegerv(GL_POLYGON_MODE, currentPolygonMode);

    glPolygonMode( GL_FRONT_AND_BACK, renderMode );
    glBindVertexArray( _cubeVAOIndexed.find( sideLength )->second );
    glBindBuffer( GL_ARRAY_BUFFER, _cubeVBOIndexed.find( sideLength )->second );
    if(_positionAttributeLocation != -1) {
        glEnableVertexAttribArray( _positionAttributeLocation );
        glVertexAttribPointer( _positionAttributeLocation, 3, GL_FLOAT, GL_FALSE, 0, nullptr );
    }
    if(_normalAttributeLocation != -1) {
        glEnableVertexAttribArray( _normalAttributeLocation );
        glVertexAttribPointer( _normalAttributeLocation, 3, GL_FLOAT, GL_FALSE, 0, reinterpret_cast<void *>(sizeof(glm::vec3) * NUM_VERTICES) );
    }
    if(_texCoordAttributeLocation != -1) {
        glEnableVertexAttribArray( _texCoordAttributeLocation );
        glVertexAttribPointer( _texCoordAttributeLocation, 3, GL_FLOAT, GL_FALSE, 0, reinterpret_cast<void *>(sizeof(glm::vec3) * NUM_VERTICES * 2) );
    }
    if (_tangentAttributeLocation != -1) {
        glEnableVertexAttribArray( _tangentAttributeLocation );
        glVertexAttribPointer( _tangentAttributeLocation, 4, GL_FLOAT, GL_FALSE, 0, reinterpret_cast<void *>(sizeof(glm::vec3) * NUM_VERTICES * 2 + sizeof(glm::vec2) * NUM_VERTICES) );
    }

    glDrawElements(GL_TRIANGLES, 36, GL_UNSIGNED_SHORT, nullptr);

    glPolygonMode( GL_FRONT_AND_BACK, currentPolygonMode[0] );
}

inline void CSCI441_INTERNAL::drawCylinder( const GLfloat base, const GLfloat top, const GLfloat height, const GLuint stacks, const GLuint slices, const GLenum renderMode ) {
    const CylinderData cylData = { base, top, height, stacks, slices };
    if( _cylinderVAO.count( cylData ) == 0 ) {
        generateCylinderVAO( cylData );
    }

    const GLuint64 NUM_VERTICES = cylData.numVertices();

    GLint currentPolygonMode[2];
    glGetIntegerv(GL_POLYGON_MODE, currentPolygonMode);

    glPolygonMode( GL_FRONT_AND_BACK, renderMode );
    glBindVertexArray( _cylinderVAO.find( cylData )->second );
    glBindBuffer( GL_ARRAY_BUFFER, _cylinderVBO.find( cylData )->second );
    if(_positionAttributeLocation != -1) {
        glEnableVertexAttribArray( _positionAttributeLocation );
        glVertexAttribPointer( _positionAttributeLocation, 3, GL_FLOAT, GL_FALSE, 0, nullptr );
    }
    if(_normalAttributeLocation != -1) {
        glEnableVertexAttribArray( _normalAttributeLocation );
        glVertexAttribPointer( _normalAttributeLocation, 3, GL_FLOAT, GL_FALSE, 0, reinterpret_cast<void *>(sizeof(glm::vec3) * NUM_VERTICES) );
    }
    if(_texCoordAttributeLocation != -1) {
        glEnableVertexAttribArray( _texCoordAttributeLocation );
        glVertexAttribPointer( _texCoordAttributeLocation, 2, GL_FLOAT, GL_FALSE, 0, reinterpret_cast<void *>(sizeof(glm::vec3) * NUM_VERTICES * 2) );
    }
    if (_tangentAttributeLocation != -1) {
        glEnableVertexAttribArray( _tangentAttributeLocation );
        glVertexAttribPointer( _tangentAttributeLocation, 4, GL_FLOAT, GL_FALSE, 0, reinterpret_cast<void *>(sizeof(glm::vec3) * NUM_VERTICES * 2 + sizeof(glm::vec2) * NUM_VERTICES) );
    }

    for(GLuint stackNum = 0; stackNum < stacks; stackNum++) {
        glDrawArrays( GL_TRIANGLE_STRIP, static_cast<GLint>((slices+1)*2*stackNum), static_cast<GLint>((slices+1)*2) );
    }

    glPolygonMode( GL_FRONT_AND_BACK, currentPolygonMode[0] );
}

inline void CSCI441_INTERNAL::drawPartialDisk(const GLfloat innerRadius, const GLfloat outerRadius, const GLuint slices, const GLuint rings, const GLfloat startAngle, const GLfloat sweepAngle, const GLenum renderMode ) {
    const DiskData diskData = {innerRadius, outerRadius, startAngle, sweepAngle, slices, rings };
    if( _diskVAO.count( diskData ) == 0 ) {
        generateDiskVAO( diskData );
    }

    const GLuint64 NUM_VERTICES = diskData.numVertices();

    GLint currentPolygonMode[2];
    glGetIntegerv(GL_POLYGON_MODE, currentPolygonMode);

    glPolygonMode( GL_FRONT_AND_BACK, renderMode );
    glBindVertexArray( _diskVAO.find( diskData )->second );
    glBindBuffer( GL_ARRAY_BUFFER, _diskVBO.find( diskData )->second );
    if(_positionAttributeLocation != -1) {
        glEnableVertexAttribArray( _positionAttributeLocation );
        glVertexAttribPointer( _positionAttributeLocation, 3, GL_FLOAT, GL_FALSE, 0, nullptr );
    }
    if(_normalAttributeLocation != -1) {
        glEnableVertexAttribArray( _normalAttributeLocation );
        glVertexAttribPointer( _normalAttributeLocation, 3, GL_FLOAT, GL_FALSE, 0, reinterpret_cast<void *>(sizeof(glm::vec3) * NUM_VERTICES) );
    }
    if(_texCoordAttributeLocation != -1) {
        glEnableVertexAttribArray( _texCoordAttributeLocation );
        glVertexAttribPointer( _texCoordAttributeLocation, 2, GL_FLOAT, GL_FALSE, 0, reinterpret_cast<void *>(sizeof(glm::vec3) * NUM_VERTICES * 2) );
    }
    if (_tangentAttributeLocation != -1) {
        glEnableVertexAttribArray( _tangentAttributeLocation );
        glVertexAttribPointer( _tangentAttributeLocation, 4, GL_FLOAT, GL_FALSE, 0, reinterpret_cast<void *>(sizeof(glm::vec3) * NUM_VERTICES * 2 + sizeof(glm::vec2) * NUM_VERTICES) );
    }

    for(GLuint ringNum = 0; ringNum < rings; ringNum++) {
        glDrawArrays( GL_TRIANGLE_STRIP, static_cast<GLint>((slices+1)*2*ringNum), static_cast<GLint>((slices+1)*2) );
    }

    glPolygonMode( GL_FRONT_AND_BACK, currentPolygonMode[0] );
}

inline void CSCI441_INTERNAL::drawSphere( const GLfloat radius, const GLuint stacks, const GLuint slices, const GLenum renderMode ) {
    const SphereData sphereData = { radius, stacks, slices };
    if( _sphereVAO.count( sphereData ) == 0 ) {
        generateSphereVAO( sphereData );
    }

    const GLuint64 NUM_VERTICES = sphereData.numVertices();

    GLint currentPolygonMode[2];
    glGetIntegerv(GL_POLYGON_MODE, currentPolygonMode);

    glPolygonMode( GL_FRONT_AND_BACK, renderMode );
    glBindVertexArray( _sphereVAO.find( sphereData )->second );
    glBindBuffer( GL_ARRAY_BUFFER, _sphereVBO.find( sphereData )->second );
    if(_positionAttributeLocation != -1) {
        glEnableVertexAttribArray( _positionAttributeLocation );
        glVertexAttribPointer( _positionAttributeLocation, 3, GL_FLOAT, GL_FALSE, 0, nullptr );
    }
    if(_normalAttributeLocation != -1) {
        glEnableVertexAttribArray( _normalAttributeLocation );
        glVertexAttribPointer( _normalAttributeLocation, 3, GL_FLOAT, GL_FALSE, 0, reinterpret_cast<void *>(sizeof(glm::vec3) * NUM_VERTICES) );
    }
    if(_texCoordAttributeLocation != -1) {
        glEnableVertexAttribArray( _texCoordAttributeLocation );
        glVertexAttribPointer( _texCoordAttributeLocation, 2, GL_FLOAT, GL_FALSE, 0, reinterpret_cast<void *>(sizeof(glm::vec3) * NUM_VERTICES * 2) );
    }
    if (_tangentAttributeLocation != -1) {
        glEnableVertexAttribArray( _tangentAttributeLocation );
        glVertexAttribPointer( _tangentAttributeLocation, 4, GL_FLOAT, GL_FALSE, 0, reinterpret_cast<void *>(sizeof(glm::vec3) * NUM_VERTICES * 2 + sizeof(glm::vec2) * NUM_VERTICES) );
    }

    glDrawArrays( GL_TRIANGLE_FAN, 0, static_cast<GLint>(slices+2) );

    for(GLuint stackNum = 1; stackNum < stacks-1; stackNum++) {
        glDrawArrays( GL_TRIANGLE_STRIP, static_cast<GLint>((slices+2) + (stackNum-1)*((slices+1)*2)), static_cast<GLint>((slices+1)*2) );
    }

    glDrawArrays( GL_TRIANGLE_FAN, static_cast<GLint>((slices+2) + (stacks-2)*(slices+1)*2), static_cast<GLint>(slices+2) );

    glPolygonMode( GL_FRONT_AND_BACK, currentPolygonMode[0] );
}

inline void CSCI441_INTERNAL::drawHalfSphere( const GLfloat radius, const GLuint stacks, const GLuint slices, const GLenum renderMode ) {
    const SphereData sphereData = { radius, stacks, slices };
    if( _sphereVAO.count( sphereData ) == 0 ) {
        generateSphereVAO( sphereData );
    }

    const GLuint64 NUM_VERTICES = sphereData.numVertices();

    GLint currentPolygonMode[2];
    glGetIntegerv(GL_POLYGON_MODE, currentPolygonMode);

    glPolygonMode( GL_FRONT_AND_BACK, renderMode );
    glBindVertexArray( _sphereVAO.find( sphereData )->second );
    glBindBuffer( GL_ARRAY_BUFFER, _sphereVBO.find( sphereData )->second );
    if(_positionAttributeLocation != -1) {
        glEnableVertexAttribArray( _positionAttributeLocation );
        glVertexAttribPointer( _positionAttributeLocation, 3, GL_FLOAT, GL_FALSE, 0, nullptr );
    }
    if(_normalAttributeLocation != -1) {
        glEnableVertexAttribArray( _normalAttributeLocation );
        glVertexAttribPointer( _normalAttributeLocation, 3, GL_FLOAT, GL_FALSE, 0, reinterpret_cast<void *>(sizeof(glm::vec3) * NUM_VERTICES) );
    }
    if(_texCoordAttributeLocation != -1) {
        glEnableVertexAttribArray( _texCoordAttributeLocation );
        glVertexAttribPointer( _texCoordAttributeLocation, 2, GL_FLOAT, GL_FALSE, 0, reinterpret_cast<void *>(sizeof(glm::vec3) * NUM_VERTICES * 2) );
    }
    if (_tangentAttributeLocation != -1) {
        glEnableVertexAttribArray( _tangentAttributeLocation );
        glVertexAttribPointer( _tangentAttributeLocation, 4, GL_FLOAT, GL_FALSE, 0, reinterpret_cast<void *>(sizeof(glm::vec3) * NUM_VERTICES * 2 + sizeof(glm::vec2) * NUM_VERTICES) );
    }

    glDrawArrays( GL_TRIANGLE_FAN, static_cast<GLint>((slices+2)/2), static_cast<GLint>((slices+2)/2) );

    for(GLuint stackNum = 1; stackNum < stacks-1; stackNum++) {
        glDrawArrays( GL_TRIANGLE_STRIP, static_cast<GLint>((slices+2) + (stackNum-1)*((slices+1)*2)), static_cast<GLint>(slices+2) );
    }

    glDrawArrays( GL_TRIANGLE_FAN, static_cast<GLint>((slices+2) + (stacks-2)*(slices+1)*2), static_cast<GLint>((slices+2)/2) );

    glPolygonMode( GL_FRONT_AND_BACK, currentPolygonMode[0] );

    drawPartialDisk(0.0f, radius, slices, stacks, 0.0f, glm::two_pi<GLfloat>(), renderMode);
}

inline void CSCI441_INTERNAL::drawDome( const GLfloat radius, const GLuint stacks, const GLuint slices, const GLenum renderMode ) {
    SphereData sphereData = { radius, stacks, slices };
    if( _sphereVAO.count( sphereData ) == 0 ) {
        generateSphereVAO( sphereData );
    }

    const GLuint64 NUM_VERTICES = sphereData.numVertices();

    GLint currentPolygonMode[2];
    glGetIntegerv(GL_POLYGON_MODE, currentPolygonMode);

    glPolygonMode( GL_FRONT_AND_BACK, renderMode );
    glBindVertexArray( _sphereVAO.find( sphereData )->second );
    glBindBuffer( GL_ARRAY_BUFFER, _sphereVBO.find( sphereData )->second );
    if(_positionAttributeLocation != -1) {
        glEnableVertexAttribArray( _positionAttributeLocation );
        glVertexAttribPointer( _positionAttributeLocation, 3, GL_FLOAT, GL_FALSE, 0, nullptr );
    }
    if(_normalAttributeLocation != -1) {
        glEnableVertexAttribArray( _normalAttributeLocation );
        glVertexAttribPointer( _normalAttributeLocation, 3, GL_FLOAT, GL_FALSE, 0, reinterpret_cast<void *>(sizeof(glm::vec3) * NUM_VERTICES) );
    }
    if(_texCoordAttributeLocation != -1) {
        glEnableVertexAttribArray( _texCoordAttributeLocation );
        glVertexAttribPointer( _texCoordAttributeLocation, 2, GL_FLOAT, GL_FALSE, 0, reinterpret_cast<void *>(sizeof(glm::vec3) * NUM_VERTICES * 2) );
    }
    if (_tangentAttributeLocation != -1) {
        glEnableVertexAttribArray( _tangentAttributeLocation );
        glVertexAttribPointer( _tangentAttributeLocation, 4, GL_FLOAT, GL_FALSE, 0, reinterpret_cast<void *>(sizeof(glm::vec3) * NUM_VERTICES * 2 + sizeof(glm::vec2) * NUM_VERTICES) );
    }

    glDrawArrays( GL_TRIANGLE_FAN, 0, static_cast<GLint>(slices+2) );

    for(GLuint stackNum = (stacks-1)/2; stackNum < stacks-1; stackNum++) {
        glDrawArrays( GL_TRIANGLE_STRIP, static_cast<GLint>((slices+2) + (stackNum-1)*((slices+1)*2)), static_cast<GLint>((slices+1)*2) );
    }

    glPolygonMode( GL_FRONT_AND_BACK, currentPolygonMode[0] );
}

inline void CSCI441_INTERNAL::drawTorus( const GLfloat innerRadius, const GLfloat outerRadius, const GLuint sides, const GLuint rings, const GLenum renderMode ) {
    const TorusData torusData = { innerRadius, outerRadius, sides, rings };
    if( _torusVAO.count( torusData ) == 0 ) {
        generateTorusVAO( torusData );
    }

    const GLuint64 NUM_VERTICES = torusData.numVertices();

    GLint currentPolygonMode[2];
    glGetIntegerv(GL_POLYGON_MODE, currentPolygonMode);

    glPolygonMode( GL_FRONT_AND_BACK, renderMode );
    glBindVertexArray( _torusVAO.find( torusData )->second );
    glBindBuffer( GL_ARRAY_BUFFER, _torusVBO.find( torusData )->second );
    if(_positionAttributeLocation != -1) {
        glEnableVertexAttribArray( _positionAttributeLocation );
        glVertexAttribPointer( _positionAttributeLocation, 3, GL_FLOAT, GL_FALSE, 0, nullptr );
    }
    if(_normalAttributeLocation != -1) {
        glEnableVertexAttribArray( _normalAttributeLocation );
        glVertexAttribPointer( _normalAttributeLocation, 3, GL_FLOAT, GL_FALSE, 0, reinterpret_cast<void *>(sizeof(glm::vec3) * NUM_VERTICES) );
    }
    if(_texCoordAttributeLocation != -1) {
        glEnableVertexAttribArray( _texCoordAttributeLocation );
        glVertexAttribPointer( _texCoordAttributeLocation, 2, GL_FLOAT, GL_FALSE, 0, reinterpret_cast<void *>(sizeof(glm::vec3) * NUM_VERTICES * 2) );
    }
    if (_tangentAttributeLocation != -1) {
        glEnableVertexAttribArray( _tangentAttributeLocation );
        glVertexAttribPointer( _tangentAttributeLocation, 4, GL_FLOAT, GL_FALSE, 0, reinterpret_cast<void *>(sizeof(glm::vec3) * NUM_VERTICES * 2 + sizeof(glm::vec2) * NUM_VERTICES) );
    }

    for(GLuint ringNum = 0; ringNum < rings; ringNum++) {
        glDrawArrays( GL_TRIANGLE_STRIP, static_cast<GLint>(ringNum*sides*4), static_cast<GLint>(sides*4) );
    }

    glPolygonMode( GL_FRONT_AND_BACK, currentPolygonMode[0] );
}

inline void CSCI441_INTERNAL::drawTeapot( const GLenum renderMode ) {
    GLint currentPolygonMode[2];
    glGetIntegerv(GL_POLYGON_MODE, currentPolygonMode);

    glPolygonMode( GL_FRONT_AND_BACK, renderMode );
    teapot();
    glPolygonMode( GL_FRONT_AND_BACK, currentPolygonMode[0] );
}

inline void CSCI441_INTERNAL::generateCubeVAOFlat( const GLfloat sideLength ) {
    GLuint vaod;
    glGenVertexArrays( 1, &vaod );
    glBindVertexArray( vaod );

    GLuint vbod;
    glGenBuffers( 1, &vbod );
    glBindBuffer( GL_ARRAY_BUFFER, vbod );

    const GLfloat CORNER_POINT = sideLength / 2.0f;

    constexpr GLuint64 NUM_VERTICES = 36;

    const glm::vec3 vertices[NUM_VERTICES] = {
            // Left Face
            {-CORNER_POINT, -CORNER_POINT, -CORNER_POINT}, {-CORNER_POINT, -CORNER_POINT, CORNER_POINT}, {-CORNER_POINT, CORNER_POINT, -CORNER_POINT},
            {-CORNER_POINT, CORNER_POINT,  -CORNER_POINT}, {-CORNER_POINT, -CORNER_POINT, CORNER_POINT}, {-CORNER_POINT, CORNER_POINT, CORNER_POINT},
            // Right Face
            {CORNER_POINT,  CORNER_POINT,  CORNER_POINT}, {CORNER_POINT, -CORNER_POINT, CORNER_POINT}, {CORNER_POINT, CORNER_POINT, -CORNER_POINT},
            {CORNER_POINT,  CORNER_POINT,  -CORNER_POINT}, {CORNER_POINT, -CORNER_POINT, CORNER_POINT}, {CORNER_POINT, -CORNER_POINT, -CORNER_POINT},
            // Top Face
            {-CORNER_POINT, CORNER_POINT,  -CORNER_POINT}, {-CORNER_POINT, CORNER_POINT, CORNER_POINT}, {CORNER_POINT, CORNER_POINT, -CORNER_POINT},
            {CORNER_POINT,  CORNER_POINT,  -CORNER_POINT}, {-CORNER_POINT, CORNER_POINT, CORNER_POINT}, {CORNER_POINT, CORNER_POINT, CORNER_POINT},
            // Bottom Face
            {CORNER_POINT,  -CORNER_POINT, CORNER_POINT}, {-CORNER_POINT, -CORNER_POINT, CORNER_POINT}, {CORNER_POINT, -CORNER_POINT, -CORNER_POINT},
            {CORNER_POINT,  -CORNER_POINT, -CORNER_POINT}, {-CORNER_POINT, -CORNER_POINT, CORNER_POINT}, {-CORNER_POINT, -CORNER_POINT, -CORNER_POINT},
            // Back Face
            {CORNER_POINT,  CORNER_POINT,  -CORNER_POINT}, {CORNER_POINT, -CORNER_POINT, -CORNER_POINT}, {-CORNER_POINT, CORNER_POINT, -CORNER_POINT},
            {-CORNER_POINT, CORNER_POINT,  -CORNER_POINT}, {CORNER_POINT, -CORNER_POINT, -CORNER_POINT}, {-CORNER_POINT, -CORNER_POINT, -CORNER_POINT},
            // Front Face
            {-CORNER_POINT, -CORNER_POINT, CORNER_POINT}, {CORNER_POINT, -CORNER_POINT, CORNER_POINT}, {-CORNER_POINT, CORNER_POINT, CORNER_POINT},
            {-CORNER_POINT, CORNER_POINT,  CORNER_POINT}, {CORNER_POINT, -CORNER_POINT, CORNER_POINT}, {CORNER_POINT, CORNER_POINT, CORNER_POINT}
    };
    const glm::vec3 normals[NUM_VERTICES] = {
            // Left Face = -X Axis
            CSCI441::X_AXIS_NEG, CSCI441::X_AXIS_NEG, CSCI441::X_AXIS_NEG,
            CSCI441::X_AXIS_NEG, CSCI441::X_AXIS_NEG, CSCI441::X_AXIS_NEG,
            // Right Face = +X Axis
            CSCI441::X_AXIS_POS, CSCI441::X_AXIS_POS, CSCI441::X_AXIS_POS,
            CSCI441::X_AXIS_POS, CSCI441::X_AXIS_POS, CSCI441::X_AXIS_POS,
            // Top Face = +Y Axis
            CSCI441::Y_AXIS_POS, CSCI441::Y_AXIS_POS, CSCI441::Y_AXIS_POS,
            CSCI441::Y_AXIS_POS, CSCI441::Y_AXIS_POS, CSCI441::Y_AXIS_POS,
            // Bottom Face = -Y Axis
            CSCI441::Y_AXIS_NEG, CSCI441::Y_AXIS_NEG, CSCI441::Y_AXIS_NEG,
            CSCI441::Y_AXIS_NEG, CSCI441::Y_AXIS_NEG, CSCI441::Y_AXIS_NEG,
            // Back Face = -Z Axis
            CSCI441::Z_AXIS_NEG, CSCI441::Z_AXIS_NEG, CSCI441::Z_AXIS_NEG,
            CSCI441::Z_AXIS_NEG, CSCI441::Z_AXIS_NEG, CSCI441::Z_AXIS_NEG,
            // Front Face = +Z Axis
            CSCI441::Z_AXIS_POS, CSCI441::Z_AXIS_POS, CSCI441::Z_AXIS_POS,
            CSCI441::Z_AXIS_POS, CSCI441::Z_AXIS_POS, CSCI441::Z_AXIS_POS
    };
    constexpr GLfloat handedness = 1.0f;
    const glm::vec4 tangents[NUM_VERTICES] = {
            // Left Face = -Y Axis
            glm::vec4(CSCI441::Y_AXIS_NEG, handedness), glm::vec4(CSCI441::Y_AXIS_NEG, handedness), glm::vec4(CSCI441::Y_AXIS_NEG, handedness),
            glm::vec4(CSCI441::Y_AXIS_NEG, handedness), glm::vec4(CSCI441::Y_AXIS_NEG, handedness), glm::vec4(CSCI441::Y_AXIS_NEG, handedness),
            // Right Face = +Y Axis
            glm::vec4(CSCI441::Y_AXIS_POS, handedness), glm::vec4(CSCI441::Y_AXIS_POS, handedness), glm::vec4(CSCI441::Y_AXIS_POS, handedness),
            glm::vec4(CSCI441::Y_AXIS_POS, handedness), glm::vec4(CSCI441::Y_AXIS_POS, handedness), glm::vec4(CSCI441::Y_AXIS_POS, handedness),
            // Top Face = +Z Axis
            glm::vec4(CSCI441::Z_AXIS_POS, handedness), glm::vec4(CSCI441::Z_AXIS_POS, handedness), glm::vec4(CSCI441::Z_AXIS_POS, handedness),
            glm::vec4(CSCI441::Z_AXIS_POS, handedness), glm::vec4(CSCI441::Z_AXIS_POS, handedness), glm::vec4(CSCI441::Z_AXIS_POS, handedness),
            // Bottom Face = -Z Axis
            glm::vec4(CSCI441::Z_AXIS_NEG, handedness), glm::vec4(CSCI441::Z_AXIS_NEG, handedness), glm::vec4(CSCI441::Z_AXIS_NEG, handedness),
            glm::vec4(CSCI441::Z_AXIS_NEG, handedness), glm::vec4(CSCI441::Z_AXIS_NEG, handedness), glm::vec4(CSCI441::Z_AXIS_NEG, handedness),
            // Back Face = -X Axis
            glm::vec4(CSCI441::X_AXIS_NEG, handedness), glm::vec4(CSCI441::X_AXIS_NEG, handedness), glm::vec4(CSCI441::X_AXIS_NEG, handedness),
            glm::vec4(CSCI441::X_AXIS_NEG, handedness), glm::vec4(CSCI441::X_AXIS_NEG, handedness), glm::vec4(CSCI441::X_AXIS_NEG, handedness),
            // Front Face = +X Axis
            glm::vec4(CSCI441::X_AXIS_POS, handedness), glm::vec4(CSCI441::X_AXIS_POS, handedness), glm::vec4(CSCI441::X_AXIS_POS, handedness),
            glm::vec4(CSCI441::X_AXIS_POS, handedness), glm::vec4(CSCI441::X_AXIS_POS, handedness), glm::vec4(CSCI441::X_AXIS_POS, handedness)
    };
    const glm::vec2 texCoords[NUM_VERTICES] = {
            // Left Face
            {0.0f, 0.0f}, {1.0f, 0.0f}, {0.0f, 1.0f},
            {0.0f, 1.0f}, {1.0f, 0.0f}, {1.0f, 1.0f},
            // Right Face
            {0.0f, 1.0f}, {0.0f, 0.0f}, {1.0f, 1.0f},
            {1.0f, 1.0f}, {0.0f, 0.0f}, {1.0f, 0.0f},
            // Top Face
            {1.0f, 0.0f}, {1.0f, 1.0f}, {0.0f, 0.0f},
            {0.0f, 0.0f}, {1.0f, 1.0f}, {0.0f, 1.0f},
            // Bottom Face
            {1.0f, 0.0f}, {1.0f, 1.0f}, {0.0f, 0.0f},
            {0.0f, 0.0f}, {1.0f, 1.0f}, {0.0f, 1.0f},
            // Back Face
            {0.0f, 1.0f}, {0.0f, 0.0f}, {1.0f, 1.0f},
            {1.0f, 1.0f}, {0.0f, 0.0f}, {1.0f, 0.0f},
            // Front Face
            {0.0f, 0.0f}, {1.0f, 0.0f}, {0.0f, 1.0f},
            {0.0f, 1.0f}, {1.0f, 0.0f}, {1.0f, 1.0f}
    };

    glBufferData(GL_ARRAY_BUFFER, (sizeof(glm::vec3)*2 + sizeof(glm::vec2) + sizeof(glm::vec4)) * NUM_VERTICES, nullptr, GL_STATIC_DRAW );
    glBufferSubData(GL_ARRAY_BUFFER, 0, sizeof(glm::vec3) * NUM_VERTICES, vertices );
    glBufferSubData(GL_ARRAY_BUFFER, sizeof(glm::vec3) * NUM_VERTICES, sizeof(glm::vec3) * NUM_VERTICES, normals );
    glBufferSubData(GL_ARRAY_BUFFER, sizeof(glm::vec3) * NUM_VERTICES * 2, sizeof(glm::vec2) * NUM_VERTICES, texCoords );
    glBufferSubData(GL_ARRAY_BUFFER, sizeof(glm::vec3) * NUM_VERTICES * 2 + sizeof(glm::vec2) * NUM_VERTICES, sizeof(glm::vec4) * NUM_VERTICES, tangents );

    _cubeVAO.insert( std::pair( sideLength, vaod ) );
    _cubeVBO.insert( std::pair( sideLength, vbod ) );
}

inline void CSCI441_INTERNAL::generateCubeVAOIndexed( const GLfloat sideLength ) {
    const GLfloat CORNER_POINT = sideLength / 2.0f;

    constexpr GLuint64 NUM_VERTICES = 8;

    const glm::vec3 vertices[NUM_VERTICES] = {
            { -CORNER_POINT, -CORNER_POINT, -CORNER_POINT }, // 0 - bln
            {  CORNER_POINT, -CORNER_POINT, -CORNER_POINT }, // 1 - brn
            {  CORNER_POINT,  CORNER_POINT, -CORNER_POINT }, // 2 - trn
            { -CORNER_POINT,  CORNER_POINT, -CORNER_POINT }, // 3 - tln
            { -CORNER_POINT, -CORNER_POINT,  CORNER_POINT }, // 4 - blf
            {  CORNER_POINT, -CORNER_POINT,  CORNER_POINT }, // 5 - brf
            {  CORNER_POINT,  CORNER_POINT,  CORNER_POINT }, // 6 - trf
            { -CORNER_POINT,  CORNER_POINT,  CORNER_POINT }  // 7 - tlf
    };
    const glm::vec3 normals[NUM_VERTICES] = {
            {-1.0f, -1.0f, -1.0f}, // 0 bln
            { 1.0f, -1.0f, -1.0f}, // 1 brn
            { 1.0f,  1.0f, -1.0f}, // 2 trn
            {-1.0f,  1.0f, -1.0f}, // 3 tln
            {-1.0f, -1.0f,  1.0f}, // 4 blf
            { 1.0f, -1.0f,  1.0f}, // 5 brf
            { 1.0f,  1.0f,  1.0f}, // 6 trf
            {-1.0f,  1.0f,  1.0f}  // 7 tlf
    };
    constexpr GLfloat handedness = 1.0f;
    const glm::vec4 tangents[NUM_VERTICES] = {
        {-1.0f, 0.0f,  1.0f, handedness}, // 0 bln
        {-1.0f, 0.0f, -1.0f, handedness}, // 1 brn
        {-1.0f, 0.0f, -1.0f, handedness}, // 2 trn
        {-1.0f, 0.0f,  1.0f, handedness}, // 3 tln
        { 1.0f, 0.0f,  1.0f, handedness}, // 4 blf
        { 1.0f, 0.0f, -1.0f, handedness}, // 5 brf
        { 1.0f, 0.0f, -1.0f, handedness}, // 6 trf
        { 1.0f, 0.0f,  1.0f, handedness}  // 7 tlf
    };
    const glm::vec3 texCoords[NUM_VERTICES] = {
            {-1.0f, -1.0f, -1.0f}, // 0 bln
            { 1.0f, -1.0f, -1.0f}, // 1 brn
            { 1.0f,  1.0f, -1.0f}, // 2 trn
            {-1.0f,  1.0f, -1.0f}, // 3 tln
            {-1.0f, -1.0f,  1.0f}, // 4 blf
            { 1.0f, -1.0f,  1.0f}, // 5 brf
            { 1.0f,  1.0f,  1.0f}, // 6 trf
            {-1.0f,  1.0f,  1.0f}  // 7 tlf
    };
    const GLushort indices[36] = {
            0, 2, 1,   0, 3, 2, // near
            1, 2, 5,   5, 2, 6, // right
            2, 7, 6,   3, 7, 2, // top
            0, 1, 4,   1, 5, 4, // bottom
            4, 5, 6,   4, 6, 7, // back
            0, 4, 3,   4, 7, 3  // left
    };

    GLuint vaod;
    glGenVertexArrays( 1, &vaod );
    glBindVertexArray( vaod );

    GLuint vbods[2];
    glGenBuffers( 2, vbods );

    glBindBuffer( GL_ARRAY_BUFFER, vbods[0] );
    glBufferData(GL_ARRAY_BUFFER, (sizeof(glm::vec3)*2 + sizeof(glm::vec2) + sizeof(glm::vec4)) * NUM_VERTICES, nullptr, GL_STATIC_DRAW );
    glBufferSubData(GL_ARRAY_BUFFER, 0, sizeof(glm::vec3) * NUM_VERTICES, vertices );
    glBufferSubData(GL_ARRAY_BUFFER, sizeof(glm::vec3) * NUM_VERTICES, sizeof(glm::vec3) * NUM_VERTICES, normals );
    glBufferSubData(GL_ARRAY_BUFFER, sizeof(glm::vec3) * NUM_VERTICES * 2, sizeof(glm::vec2) * NUM_VERTICES, texCoords );
    glBufferSubData(GL_ARRAY_BUFFER, sizeof(glm::vec3) * NUM_VERTICES * 2 + sizeof(glm::vec2) * NUM_VERTICES, sizeof(glm::vec4) * NUM_VERTICES, tangents );

    glBindBuffer( GL_ELEMENT_ARRAY_BUFFER, vbods[1] );
    glBufferData( GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW) ;

    _cubeVAOIndexed.insert( std::pair( sideLength, vaod ) );
    _cubeVBOIndexed.insert( std::pair( sideLength, vbods[0] ) );
    _cubeIBOIndexed.insert( std::pair( sideLength, vbods[1] ) );
}

inline void CSCI441_INTERNAL::generateCylinderVAO( const CylinderData& cylData ) {
    GLuint vaod;
    glGenVertexArrays( 1, &vaod );
    glBindVertexArray( vaod );

    GLuint vbod;
    glGenBuffers( 1, &vbod );
    glBindBuffer( GL_ARRAY_BUFFER, vbod );

    const GLuint64 NUM_VERTICES = cylData.numVertices();
    const auto RADIUS_BOTTOM = cylData.radiusBase;
    const auto RADIUS_TOP = cylData.radiusTop;
    const auto NUM_STACKS = cylData.stacks;
    const auto NUM_STACKS_GL_FLOAT = static_cast<GLfloat>(NUM_STACKS);
    const auto NUM_SLICES = cylData.slices;
    const auto NUM_SLICES_GL_FLOAT = static_cast<GLfloat>(NUM_SLICES);

    const GLfloat sliceDelta = glm::two_pi<GLfloat>() / NUM_SLICES_GL_FLOAT;
    const GLfloat stackDelta = cylData.height / NUM_STACKS_GL_FLOAT;
    constexpr GLfloat quarterPI = glm::pi<GLfloat>() / 4.0f;

    const auto vertices  = new glm::vec3[NUM_VERTICES];
    const auto normals   = new glm::vec3[NUM_VERTICES];
    const auto tangents  = new glm::vec4[NUM_VERTICES];
    const auto texCoords = new glm::vec2[NUM_VERTICES];

    constexpr GLfloat handedness = 1.0f;

    GLuint64 idx = 0;

    for(GLuint stackNum = 0; stackNum < NUM_STACKS; stackNum++ ) {
        const auto currStackNum = static_cast<GLfloat>(stackNum);
        const auto nextStackNum = static_cast<GLfloat>(stackNum + 1);
        const GLfloat currStackBotRadius = RADIUS_BOTTOM * static_cast<GLfloat>(NUM_STACKS - stackNum    ) / NUM_STACKS_GL_FLOAT + RADIUS_TOP * currStackNum / NUM_STACKS_GL_FLOAT;
        const GLfloat currStackTopRadius = RADIUS_BOTTOM * static_cast<GLfloat>(NUM_STACKS - stackNum - 1) / NUM_STACKS_GL_FLOAT + RADIUS_TOP * nextStackNum / NUM_STACKS_GL_FLOAT;

        for(GLuint sliceNum = 0; sliceNum <= NUM_SLICES; sliceNum++ ) {
            const auto currSliceNum = static_cast<GLfloat>(sliceNum);

            const auto theta = currSliceNum * sliceDelta;
            const GLfloat cosTheta = glm::cos( theta );
            const GLfloat sinTheta = glm::sin( theta );

            vertices[ idx ] = glm::vec3(
                cosTheta * currStackBotRadius,
                currStackNum * stackDelta,
                sinTheta * currStackBotRadius
            );
            normals[ idx ] = glm::vec3(
                cosTheta,
                0.0f,
                sinTheta
            );
            tangents[ idx ] = glm::vec4(
                glm::vec3(
                    glm::cos( theta + quarterPI ),
                    0.0f,
                    glm::sin( theta + quarterPI )
                ),
                handedness
            );
            texCoords[ idx ] = glm::vec2(
                1.0f - currSliceNum / NUM_SLICES_GL_FLOAT,
                       currStackNum / NUM_STACKS_GL_FLOAT
            );

            idx++;

            vertices[ idx ] = glm::vec3(
                cosTheta * currStackTopRadius,
                nextStackNum * stackDelta,
                sinTheta * currStackTopRadius
            );
            normals[ idx ] = glm::vec3(
                cosTheta,
                0.0f,
                sinTheta
            );
            tangents[ idx ] = glm::vec4(
                glm::vec3(
                    glm::cos( theta + quarterPI ),
                    0.0f,
                    glm::sin( theta + quarterPI )
                ),
                handedness
            );
            texCoords[ idx ] = glm::vec2(
                1.0f - currSliceNum / NUM_SLICES_GL_FLOAT,
                       nextStackNum / NUM_STACKS_GL_FLOAT
            );

            idx++;
        }
    }

    glBufferData(GL_ARRAY_BUFFER, (sizeof(glm::vec3)*2 + sizeof(glm::vec2) + sizeof(glm::vec4)) * NUM_VERTICES, nullptr, GL_STATIC_DRAW );
    glBufferSubData(GL_ARRAY_BUFFER, 0, static_cast<GLsizeiptr>(sizeof(glm::vec3) * NUM_VERTICES), vertices );
    glBufferSubData(GL_ARRAY_BUFFER, static_cast<GLintptr>(sizeof(glm::vec3) * NUM_VERTICES), static_cast<GLsizeiptr>(sizeof(glm::vec3) * NUM_VERTICES), normals );
    glBufferSubData(GL_ARRAY_BUFFER, static_cast<GLintptr>(sizeof(glm::vec3) * NUM_VERTICES * 2), static_cast<GLsizeiptr>(sizeof(glm::vec2) * NUM_VERTICES), texCoords );
    glBufferSubData(GL_ARRAY_BUFFER, sizeof(glm::vec3) * NUM_VERTICES * 2 + sizeof(glm::vec2) * NUM_VERTICES, sizeof(glm::vec4) * NUM_VERTICES, tangents );

    _cylinderVAO.insert( std::pair( cylData, vaod ) );
    _cylinderVBO.insert( std::pair( cylData, vbod ) );

    delete[] vertices;
    delete[] normals;
    delete[] tangents;
    delete[] texCoords;
}

inline void CSCI441_INTERNAL::generateDiskVAO( const DiskData& diskData ) {
    GLuint vaod;
    glGenVertexArrays( 1, &vaod );
    glBindVertexArray( vaod );

    GLuint vbod;
    glGenBuffers( 1, &vbod );
    glBindBuffer( GL_ARRAY_BUFFER, vbod );

    const GLuint64 NUM_VERTICES = diskData.numVertices();

    const GLfloat sliceDelta = diskData.sweepAngle / static_cast<GLfloat>(diskData.slices);
    const GLfloat ringDelta = (diskData.outerRadius - diskData.innerRadius) / static_cast<GLfloat>(diskData.rings);
    constexpr GLfloat quarterPI = glm::pi<GLfloat>() / 4.0f;

    const auto vertices  = new glm::vec3[NUM_VERTICES];
    const auto normals   = new glm::vec3[NUM_VERTICES];
    const auto tangents  = new glm::vec4[NUM_VERTICES];
    const auto texCoords = new glm::vec2[NUM_VERTICES];

    constexpr GLfloat handedness = 1.0f;

    GLuint64 idx = 0;

    for(GLuint ringNum = 0; ringNum < diskData.rings; ringNum++ ) {
        const GLfloat currRadius = diskData.innerRadius + static_cast<GLfloat>(ringNum)    * ringDelta;
        const GLfloat nextRadius = diskData.innerRadius + static_cast<GLfloat>(ringNum + 1) * ringDelta;

        GLfloat theta = diskData.startAngle;

        for(GLuint i = 0; i <= diskData.slices; i++ ) {
            const GLfloat cosTheta = glm::cos( theta );
            const GLfloat sinTheta = glm::sin( theta );

            vertices[ idx ] = glm::vec3(
                cosTheta * currRadius,
                sinTheta * currRadius,
                0.0f
            );
            normals[ idx ] = CSCI441::Z_AXIS_POS;
            tangents[ idx ] = glm::vec4(
                glm::vec3(
                    glm::cos(theta + quarterPI),
                    glm::sin(theta + quarterPI),
                    0.0f
                ),
                handedness
            );
            texCoords[ idx ] = glm::vec2(
                cosTheta * (currRadius / diskData.outerRadius),
                sinTheta * (currRadius / diskData.outerRadius)
            );

            idx++;

            vertices[ idx ] = glm::vec3(
                cosTheta * nextRadius,
                sinTheta * nextRadius,
                0.0f
            );
            normals[ idx ] = CSCI441::Z_AXIS_POS;
            tangents[ idx ] = glm::vec4(
                glm::vec3(
                    glm::cos(theta + quarterPI),
                    glm::sin(theta + quarterPI),
                    0.0f
                ),
                handedness
            );
            texCoords[ idx ] = glm::vec2(
                cosTheta * (nextRadius / diskData.outerRadius),
                sinTheta * (nextRadius / diskData.outerRadius)
            );

            idx++;
            theta += sliceDelta;
        }
    }

    glBufferData(GL_ARRAY_BUFFER, (sizeof(glm::vec3)*2 + sizeof(glm::vec2) + sizeof(glm::vec4)) * NUM_VERTICES, nullptr, GL_STATIC_DRAW );
    glBufferSubData(GL_ARRAY_BUFFER, 0, static_cast<GLsizeiptr>(sizeof(glm::vec3) * NUM_VERTICES), vertices );
    glBufferSubData(GL_ARRAY_BUFFER, static_cast<GLintptr>(sizeof(glm::vec3) * NUM_VERTICES), static_cast<GLsizeiptr>(sizeof(glm::vec3) * NUM_VERTICES), normals );
    glBufferSubData(GL_ARRAY_BUFFER, static_cast<GLintptr>(sizeof(glm::vec3) * NUM_VERTICES * 2), static_cast<GLsizeiptr>(sizeof(glm::vec2) * NUM_VERTICES), texCoords );
    glBufferSubData(GL_ARRAY_BUFFER, sizeof(glm::vec3) * NUM_VERTICES * 2 + sizeof(glm::vec2) * NUM_VERTICES, sizeof(glm::vec4) * NUM_VERTICES, tangents );

    _diskVAO.insert( std::pair( diskData, vaod ) );
    _diskVBO.insert( std::pair( diskData, vbod ) );

    delete[] vertices;
    delete[] normals;
    delete[] tangents;
    delete[] texCoords;
}

inline void CSCI441_INTERNAL::generateSphereVAO( const SphereData& sphereData ) {
    GLuint vaod;
    glGenVertexArrays( 1, &vaod );
    glBindVertexArray( vaod );

    GLuint vbod;
    glGenBuffers( 1, &vbod );
    glBindBuffer( GL_ARRAY_BUFFER, vbod );

    const GLuint64 NUM_VERTICES = sphereData.numVertices();

    const auto RADIUS = sphereData.radius;
    const auto NUM_SLICES = sphereData.slices;
    const auto NUM_SLICES_GL_FLOAT = static_cast<GLfloat>(NUM_SLICES);
    const auto NUM_STACKS = sphereData.stacks;
    const auto NUM_STACKS_GL_FLOAT = static_cast<GLfloat>(NUM_STACKS);
    const auto NUM_STACKS_LESS_ONE = static_cast<GLfloat>(NUM_STACKS - 1);
    const auto NUM_STACKS_LESS_TWO = static_cast<GLfloat>(NUM_STACKS - 2);

    const GLfloat sliceDelta = glm::two_pi<GLfloat>() / NUM_SLICES_GL_FLOAT;
    const GLfloat stackDelta = glm::pi<GLfloat>() / NUM_STACKS_GL_FLOAT;

    const auto vertices  = new glm::vec3[NUM_VERTICES];
    const auto normals   = new glm::vec3[NUM_VERTICES];
    const auto tangents  = new glm::vec4[NUM_VERTICES];
    const auto texCoords = new glm::vec2[NUM_VERTICES];

    constexpr GLfloat handedness = 1.0f;

    GLuint64 idx = 0;

    // sphere top
    {
        constexpr GLfloat phi = glm::pi<GLfloat>();
        const GLfloat cosPhi = glm::cos( phi );

        const GLfloat phiNext = stackDelta * NUM_STACKS_LESS_ONE;
        const GLfloat sinPhiNext = glm::sin( phiNext );
        const GLfloat cosPhiNext = glm::cos( phiNext );

        vertices[ idx ] = glm::vec3(
            0.0f,
            -cosPhi * RADIUS,
            0.0f
        );
        normals [ idx ] = CSCI441::Y_AXIS_POS;
        tangents[ idx ] = glm::vec4(
            CSCI441::Z_AXIS_POS,
            handedness
        );
        texCoords[idx ] = glm::vec2(
            0.5f,
            1.0f
        );

        idx++;

        for(GLuint sliceNum = 0; sliceNum <= NUM_SLICES; ++sliceNum ) {
            const GLfloat theta = sliceDelta * static_cast<GLfloat>(sliceNum);
            const GLfloat sinTheta = glm::sin( theta );
            const GLfloat cosTheta = glm::cos( theta );

            vertices[ idx ] = glm::vec3(
                -cosTheta * sinPhiNext * RADIUS,
                           -cosPhiNext * RADIUS,
                 sinTheta * sinPhiNext * RADIUS
            );
            normals[ idx ] = glm::normalize( vertices[idx] );
            tangents[ idx ] = glm::vec4(
                glm::normalize(glm::cross(CSCI441::Y_AXIS, normals[idx]) ),
                handedness
            );
            texCoords[ idx ] = glm::vec2(
                static_cast<GLfloat>(sliceNum) / NUM_SLICES_GL_FLOAT,
                1.0f
            );

            idx++;
        }
    }

    // sphere stacks
    for(GLuint stackNum = 1; stackNum < NUM_STACKS - 1; ++stackNum ) {
        const GLfloat phi     = stackDelta * static_cast<GLfloat>(stackNum);
        const GLfloat sinPhi = glm::sin( phi );
        const GLfloat cosPhi = glm::cos( phi );

        const GLfloat phiNext = stackDelta * static_cast<GLfloat>(stackNum + 1);
        const GLfloat sinPhiNext = glm::sin( phiNext );
        const GLfloat cosPhiNext = glm::cos( phiNext );

        for(GLuint sliceNum = NUM_SLICES; sliceNum > 0; --sliceNum ) {
            const GLfloat theta = sliceDelta * static_cast<GLfloat>(sliceNum);
            const GLfloat sinTheta = glm::sin( theta );
            const GLfloat cosTheta = glm::cos( theta );

            vertices[ idx ] = glm::vec3(
                -cosTheta * sinPhi * RADIUS,
                           -cosPhi * RADIUS,
                 sinTheta * sinPhi * RADIUS
            );
            normals[ idx ] = glm::normalize( vertices[idx] );
            tangents[ idx ] = glm::vec4(
                glm::normalize(glm::cross(CSCI441::Y_AXIS, glm::normalize(normals[idx])) ),
                handedness
            );
            texCoords[ idx ] = glm::vec2(
                static_cast<GLfloat>(sliceNum) / NUM_SLICES_GL_FLOAT,
                static_cast<GLfloat>(stackNum - 1) / NUM_STACKS_LESS_TWO
            );

            idx++;

            vertices[ idx ] = glm::vec3(
            -cosTheta * sinPhiNext * RADIUS,
                       -cosPhiNext * RADIUS,
             sinTheta * sinPhiNext * RADIUS
            );
            normals[ idx ] = glm::normalize( vertices[idx] );
            tangents[ idx ] = glm::vec4(
                glm::normalize(glm::cross(CSCI441::Y_AXIS, glm::normalize(normals[idx])) ),
                handedness
            );
            texCoords[ idx ] = glm::vec2(
                static_cast<GLfloat>(sliceNum) / NUM_SLICES_GL_FLOAT,
                static_cast<GLfloat>(stackNum) / NUM_STACKS_LESS_TWO
            );

            idx++;
        }

        vertices[ idx ] = glm::vec3(
            -sinPhi * RADIUS,
            -cosPhi * RADIUS,
            0.0f
        );
        normals[ idx ] = glm::normalize( vertices[idx] );
        tangents[ idx ] = glm::vec4(
            glm::normalize(glm::cross(CSCI441::Y_AXIS, normals[idx]) ),
            handedness
        );
        texCoords[ idx ] = glm::vec2(
            0.0f,
            static_cast<GLfloat>(stackNum - 1) / NUM_STACKS_LESS_TWO
        );

        idx++;

        vertices[ idx ] = glm::vec3(
            -sinPhiNext * RADIUS,
            -cosPhiNext * RADIUS,
            0.0f
        );
        normals[ idx ] = glm::normalize( vertices[idx] );
        tangents[ idx ] = glm::vec4(
            glm::normalize(glm::cross(CSCI441::Y_AXIS, normals[idx]) ),
            handedness
        );
        texCoords[ idx ] = glm::vec2(
            0.0f,
            static_cast<GLfloat>(stackNum) / NUM_STACKS_LESS_TWO
        );

        idx++;
    }

    // sphere bottom
    {
        constexpr GLfloat phi = 0.0f;
        const GLfloat cosPhi = glm::cos( phi );

        const GLfloat phiNext = stackDelta;
        const GLfloat sinPhiNext = glm::sin( phiNext );
        const GLfloat cosPhiNext = glm::cos( phiNext );

        vertices[ idx ] = glm::vec3(
            0.0f,
            -cosPhi * RADIUS,
            0.0f
        );
        normals[ idx ] = CSCI441::Y_AXIS_NEG;
        tangents[ idx ] = glm::vec4( CSCI441::Z_AXIS_NEG, handedness );
        texCoords[ idx ] = glm::vec2(
            0.5f,
            0.0f
        );

        idx++;

        for(GLuint sliceNum = NUM_SLICES; sliceNum > 0; --sliceNum) {
            const GLfloat theta = sliceDelta * static_cast<GLfloat>(sliceNum);
            const GLfloat sinTheta = glm::sin( theta );
            const GLfloat cosTheta = glm::cos( theta );

            vertices[ idx ] = glm::vec3(
                -cosTheta * sinPhiNext * RADIUS,
                           -cosPhiNext * RADIUS,
                 sinTheta * sinPhiNext * RADIUS
            );
            normals[ idx ] = glm::normalize( vertices[idx] );
            tangents[ idx ] = glm::vec4(
                glm::normalize(glm::cross(CSCI441::Y_AXIS, normals[idx]) ),
                handedness
            );
            texCoords[ idx ] = glm::vec2(
                static_cast<GLfloat>(sliceNum) / NUM_SLICES_GL_FLOAT,
                0.0f
            );

            idx++;
        }

        vertices[ idx ] = glm::vec3(
            -sinPhiNext * RADIUS,
            -cosPhiNext * RADIUS,
            0.0f
        );
        normals[ idx ] = glm::normalize( vertices[idx] );
        tangents[ idx ] = glm::vec4(
            glm::normalize(glm::cross(CSCI441::Y_AXIS, normals[idx]) ),
            handedness
        );
        texCoords[ idx ] = glm::vec2(
            0.0f,
            0.0f
        );
    }

    glBufferData(GL_ARRAY_BUFFER, (sizeof(glm::vec3)*2 + sizeof(glm::vec2) + sizeof(glm::vec4)) * NUM_VERTICES, nullptr, GL_STATIC_DRAW );
    glBufferSubData(GL_ARRAY_BUFFER, 0, sizeof(glm::vec3) * NUM_VERTICES, vertices );
    glBufferSubData(GL_ARRAY_BUFFER, sizeof(glm::vec3) * NUM_VERTICES, sizeof(glm::vec3) * NUM_VERTICES, normals );
    glBufferSubData(GL_ARRAY_BUFFER, sizeof(glm::vec3) * NUM_VERTICES * 2, sizeof(glm::vec2) * NUM_VERTICES, texCoords );
    glBufferSubData(GL_ARRAY_BUFFER, sizeof(glm::vec3) * NUM_VERTICES * 2 + sizeof(glm::vec2) * NUM_VERTICES, sizeof(glm::vec4) * NUM_VERTICES, tangents );

    _sphereVAO.insert( std::pair( sphereData, vaod ) );
    _sphereVBO.insert( std::pair( sphereData, vbod ) );

    delete[] vertices;
    delete[] texCoords;
    delete[] normals;
    delete[] tangents;
}

inline void CSCI441_INTERNAL::generateTorusVAO( const TorusData& torusData ) {
    GLuint vaod;
    glGenVertexArrays( 1, &vaod );
    glBindVertexArray( vaod );

    GLuint vbod;
    glGenBuffers( 1, &vbod );
    glBindBuffer( GL_ARRAY_BUFFER, vbod );

    const auto NUM_VERTICES = torusData.numVertices();
    const auto OUTER_RADIUS = torusData.outerRadius;
    const auto INNER_RADIUS = torusData.innerRadius;
    const auto NUM_SIDES = torusData.sides;
    const auto NUM_SIDES_GL_FLOAT = static_cast<GLfloat>(NUM_SIDES);
    const auto NUM_RINGS = torusData.rings;
    const auto NUM_RINGS_GL_FLOAT = static_cast<GLfloat>(NUM_RINGS);

    const auto vertices  = new glm::vec3[NUM_VERTICES];
    const auto normals   = new glm::vec3[NUM_VERTICES];
    const auto tangents  = new glm::vec4[NUM_VERTICES];
    const auto texCoords = new glm::vec2[NUM_VERTICES];

    constexpr GLfloat handedness = 1.0f;

    GLuint64 idx = 0;

    const GLfloat sideDelta = glm::two_pi<GLfloat>() / NUM_SIDES_GL_FLOAT;
    const GLfloat ringDelta = glm::two_pi<GLfloat>() / NUM_RINGS_GL_FLOAT;

    for(GLuint ringNum = 0; ringNum < NUM_RINGS; ++ringNum ) {
        const auto currRingNum = static_cast<GLfloat>(ringNum);
        const auto nextRingNum = static_cast<GLfloat>(ringNum + 1);

        const GLfloat theta = ringDelta * currRingNum;
        const GLfloat sinTheta = glm::sin( theta );
        const GLfloat cosTheta = glm::cos( theta );

        const GLfloat thetaNext = ringDelta * nextRingNum;
        const GLfloat sinThetaNext = glm::sin( thetaNext );
        const GLfloat cosThetaNext = glm::cos( thetaNext );

        for(GLuint sideNum = 0; sideNum < NUM_SIDES; ++sideNum ) {
            const auto currSideNum = static_cast<GLfloat>(sideNum);
            const auto nextSideNum = static_cast<GLfloat>(sideNum + 1);

            const GLfloat phi = sideDelta * currSideNum;
            const GLfloat sinPhi = glm::sin( phi );
            const GLfloat cosPhi = glm::cos( phi );

            const GLfloat phiNext = sideDelta * nextSideNum;
            const GLfloat sinPhiNext = glm::sin( phiNext );
            const GLfloat cosPhiNext = glm::cos( phiNext );

            vertices[ idx ] = glm::vec3(
                (OUTER_RADIUS + INNER_RADIUS * cosPhi ) * cosTheta,
                (OUTER_RADIUS + INNER_RADIUS * cosPhi ) * sinTheta,
                                INNER_RADIUS * sinPhi
            );
            normals[ idx ] = glm::vec3(
                cosPhi * cosTheta,
                cosPhi * sinTheta,
                sinPhi
            );
            tangents[ idx ] = glm::vec4(
                glm::vec3(
                    -(OUTER_RADIUS + INNER_RADIUS * cosPhi ) * sinTheta,
                     (OUTER_RADIUS + INNER_RADIUS * cosPhi ) * cosTheta,
                    0.0f
                ),
                handedness
            );
            texCoords[ idx ] = glm::vec2(
                currSideNum / NUM_SIDES_GL_FLOAT,
                currRingNum / NUM_RINGS_GL_FLOAT
            );

            idx++;

            vertices[ idx ] = glm::vec3(
                (OUTER_RADIUS + INNER_RADIUS * cosPhi ) * cosThetaNext,
                (OUTER_RADIUS + INNER_RADIUS * cosPhi ) * sinThetaNext,
                                INNER_RADIUS * sinPhi
            );
            normals[ idx ] = glm::vec3(
                cosPhi * cosThetaNext,
                cosPhi * sinThetaNext,
                sinPhi
            );
            tangents[ idx ] = glm::vec4(
                glm::vec3(
                    -(OUTER_RADIUS + INNER_RADIUS * cosPhi ) * sinThetaNext,
                     (OUTER_RADIUS + INNER_RADIUS * cosPhi ) * cosThetaNext,
                    0.0f
                ),
                handedness
            );
            texCoords[ idx ] = glm::vec2(
                currSideNum / NUM_SIDES_GL_FLOAT,
                nextRingNum / NUM_RINGS_GL_FLOAT
            );

            idx++;

            vertices[ idx ] = glm::vec3(
                (OUTER_RADIUS + INNER_RADIUS * cosPhiNext ) * cosTheta,
                (OUTER_RADIUS + INNER_RADIUS * cosPhiNext ) * sinTheta,
                                INNER_RADIUS * sinPhiNext
            );
            normals[ idx ] = glm::vec3(
                cosPhiNext * cosTheta,
                cosPhiNext * sinTheta,
                sinPhiNext
            );
            tangents[ idx ] = glm::vec4(
                glm::vec3(
                    -(OUTER_RADIUS + INNER_RADIUS * cosPhiNext ) * cosTheta,
                     (OUTER_RADIUS + INNER_RADIUS * cosPhiNext ) * sinTheta,
                    0.0f
                ),
                handedness
            );
            texCoords[ idx ] = glm::vec2(
                nextSideNum / NUM_SIDES_GL_FLOAT,
                currRingNum / NUM_RINGS_GL_FLOAT
            );

            idx++;

            vertices[ idx ] = glm::vec3(
                (OUTER_RADIUS + INNER_RADIUS * cosPhiNext ) * cosThetaNext,
                (OUTER_RADIUS + INNER_RADIUS * cosPhiNext ) * sinThetaNext,
                                INNER_RADIUS * sinPhiNext
            );
            normals[ idx ] = glm::vec3(
                cosPhiNext * cosThetaNext,
                cosPhiNext * sinThetaNext,
                sinPhiNext
            );
            tangents[ idx ] = glm::vec4(
                glm::vec3(
                    -(OUTER_RADIUS + INNER_RADIUS * cosPhiNext ) * sinThetaNext,
                     (OUTER_RADIUS + INNER_RADIUS * cosPhiNext ) * cosThetaNext,
                    0.0f
                ),
                handedness
            );
            texCoords[ idx ] = glm::vec2(
                nextSideNum / NUM_SIDES_GL_FLOAT,
                nextRingNum / NUM_RINGS_GL_FLOAT
            );

            idx++;
        }
    }

    glBufferData(GL_ARRAY_BUFFER, (sizeof(glm::vec3)*2 + sizeof(glm::vec2) + sizeof(glm::vec4)) * NUM_VERTICES, nullptr, GL_STATIC_DRAW );
    glBufferSubData(GL_ARRAY_BUFFER, 0, static_cast<GLsizeiptr>(sizeof(glm::vec3) * NUM_VERTICES), vertices );
    glBufferSubData(GL_ARRAY_BUFFER, static_cast<GLintptr>(sizeof(glm::vec3) * NUM_VERTICES), static_cast<GLsizeiptr>(sizeof(glm::vec3) * NUM_VERTICES), normals );
    glBufferSubData(GL_ARRAY_BUFFER, static_cast<GLintptr>(sizeof(glm::vec3) * NUM_VERTICES * 2), static_cast<GLsizeiptr>(sizeof(glm::vec2) * NUM_VERTICES), texCoords );
    glBufferSubData(GL_ARRAY_BUFFER, sizeof(glm::vec3) * NUM_VERTICES * 2 + sizeof(glm::vec2) * NUM_VERTICES, sizeof(glm::vec4) * NUM_VERTICES, tangents );

    _torusVAO.insert( std::pair( torusData, vaod ) );
    _torusVBO.insert( std::pair( torusData, vbod ) );

    delete[] vertices;
    delete[] normals;
    delete[] tangents;
    delete[] texCoords;
}

#endif//CSCI441_OBJECTS_IMPL_HPP