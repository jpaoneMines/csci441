/** @file objects.hpp
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
 *	@warning NOTE: This header file depends upon GLEW
 */

#ifndef CSCI441_OBJECTS_HPP
#define CSCI441_OBJECTS_HPP

#include "teapot.hpp"                   // for teapot()

#include <GL/glew.h>
#include <glm/gtc/constants.hpp>

#include <cassert>   					// for assert()
#include <map>							// for map

////////////////////////////////////////////////////////////////////////////////////

/**
 * @namespace CSCI441
 * @brief CSCI441 Helper Functions for OpenGL
 */
namespace CSCI441 {
    /**
     * @brief Sets the attribute locations for vertex positions, normals, and texture coordinates
     * @param positionLocation location of the vertex position attribute
     * @param normalLocation location of the vertex normal attribute
     * @param texCoordLocation location of the vertex texture coordinate attribute
     * @note Needs to be called after a shader program is being used and before drawing geometry
     */
    void setVertexAttributeLocations( GLint positionLocation, GLint normalLocation = -1, GLint texCoordLocation = -1 );

    /**
     * @brief deletes the VAOs stored for all object types
     */
    [[maybe_unused]] void deleteObjectVAOs();

    /**
     * @brief deletes the VBOs stored for all object types
     */
    [[maybe_unused]] void deleteObjectVBOs();

    /**
     * @brief Draws a solid cone
     * @param base radius of the base of the cone
     * @param height height of the cone from the base to the tip
     * @param stacks resolution of the number of steps rotated around the central axis of the cone
     * @param slices resolution of the number of steps to take along the height
     * @pre base must be greater than zero
     * @pre height must be greater than zero
     * @pre stacks must be greater than zero
     * @pre slices must be greater than two
     * @note Cone is oriented along the y-axis with the origin along the base of the cone
     */
    [[maybe_unused]] void drawSolidCone( GLfloat base, GLfloat height, GLint stacks, GLint slices );
    /**
     * @brief Draws a wireframe cone
     * @param base radius of the base of the cone
     * @param height height of the cone from the base to the tip
     * @param stacks resolution of the number of steps rotated around the central axis of the cone
     * @param slices resolution of the number of steps to take along the height
     * @pre base must be greater than zero
     * @pre height must be greater than zero
     * @pre stacks must be greater than zero
     * @pre slices must be greater than two
     * @note Cone is oriented along the y-axis with the origin along the base of the cone
     */
    [[maybe_unused]] void drawWireCone( GLfloat base, GLfloat height, GLint stacks, GLint slices );

    /**
     * @brief Calls through to drawSolidCubeIndexed()
     * @param sideLength length of the edge of the cube
     * @pre sideLength must be greater than zero
     */
    [[maybe_unused]] void drawSolidCube( GLfloat sideLength );
    /**
     * @brief Draws a solid cube with normals aligned with cube face
     * @param sideLength length of the edge of the cube
     * @pre sideLength must be greater than zero
     * @note The origin is at the cube's center of mass.  Cube is oriented with our XYZ axes
     */
    void drawSolidCubeFlat( GLfloat sideLength );
    /**
     * @brief Draws a solid cube
     * @param sideLength length of the edge of the cube
     * @pre sideLength must be greater than zero
     * @note The origin is at the cube's center of mass.  Cube is oriented with our XYZ axes
     */
    void drawSolidCubeIndexed( GLfloat sideLength );
    /**
     * @brief Draws a solid textured cube.  Calls through to drawSolidCubeFlat()
     * @param sideLength length of the edge of the cube
     * @pre sideLength must be greater than zero
     * @note The origin is at the cube's center of mass.  Cube is oriented with our XYZ axes
     */
    [[maybe_unused]] void drawSolidCubeTextured( GLfloat sideLength );
    /**
     * @brief Draws a wireframe cube
     * @param sideLength length of the edge of the cube
     * @pre sideLength must be greater than zero
     * @note The origin is at the cube's center of mass.  Cube is oriented with our XYZ axes
     */
    [[maybe_unused]] void drawWireCube( GLfloat sideLength );

    /**
     * @brief Draws a cube with 3D Texture Coordinates to map a cube map texture to it
     * @param sideLength length of the edge of the cube
     * @pre sideLength must be greater than zero
     * @note The origin is at the cube's center of mass.  Cube is oriented with our XYZ axes
     */
    [[maybe_unused]] void drawCubeMap( GLfloat sideLength );

    /**
     * @brief Draws a solid open ended cylinder
     * @param base radius of the base of the cylinder
     * @param top radius of the top of the cylinder
     * @param height height of the cylinder from the base to the top
     * @param stacks resolution of the number of steps rotated around the central axis of the cylinder
     * @param slices resolution of the number of steps to take along the height
     * @pre either: (1) base is greater than zero and top is greater than or equal to zero or (2) base is greater than or equal to zero and top is greater than zero
     * @pre height must be greater than zero
     * @pre stacks must be greater than zero
     * @pre slices must be greater than two
     * @note Cylinder is oriented along the y-axis with the origin along the base
     */
    [[maybe_unused]] void drawSolidCylinder( GLfloat base, GLfloat top, GLfloat height, GLint stacks, GLint slices );
    /**
     * @brief Draws a wireframe open ended cylinder
     * @param base radius of the base of the cylinder
     * @param top radius of the top of the cylinder
     * @param height height of the cylinder from the base to the top
     * @param stacks resolution of the number of steps rotated around the central axis of the cylinder
     * @param slices resolution of the number of steps to take along the height
     * @pre either: (1) base is greater than zero and top is greater than or equal to zero or (2) base is greater than or equal to zero and top is greater than zero
     * @pre height must be greater than zero
     * @pre stacks must be greater than zero
     * @pre slices must be greater than two
     * @note Cylinder is oriented along the y-axis with the origin along the base
     */
    [[maybe_unused]] void drawWireCylinder( GLfloat base, GLfloat top, GLfloat height, GLint stacks, GLint slices );

    /**
     * @brief Draws a solid disk
     * @param inner equivalent to the width of the disk
     * @param outer radius from the center of the disk to the center of the ring
     * @param slices resolution of the number of steps rotated along the disk
     * @param rings resolution of the number of steps to take along the disk width
     * @pre inner is greater than or equal to zero
     * @pre outer is greater than zero
     * @pre outer is greater than inner
     * @pre slices is greater than two
     * @pre rings is greater than zero
     * @note Disk is drawn in the XY plane with the origin at its center
     */
    [[maybe_unused]] void drawSolidDisk( GLfloat inner, GLfloat outer, GLint slices, GLint rings );
    /**
     * @brief Draws a wireframe disk
     * @param inner equivalent to the width of the disk
     * @param outer radius from the center of the disk to the center of the ring
     * @param slices resolution of the number of steps rotated along the disk
     * @param rings resolution of the number of steps to take along the disk width
     * @pre inner is greater than or equal to zero
     * @pre outer is greater than zero
     * @pre outer is greater than inner
     * @pre slices is greater than two
     * @pre rings is greater than zero
     * @note Disk is drawn in the XY plane with the origin at its center
     */
    [[maybe_unused]] void drawWireDisk( GLfloat inner, GLfloat outer, GLint slices, GLint rings );

    /**
     * @brief Draws part of a solid disk
     * @param inner equivalent to the width of the disk
     * @param outer radius from the center of the disk to the center of the ring
     * @param slices resolution of the number of steps rotated along the disk
     * @param rings resolution of the number of steps to take along the disk width
     * @param start angle in degrees to start the disk at
     * @param sweep distance in degrees to rotate through
     * @pre inner is greater than or equal to zero
     * @pre outer is greater than zero
     * @pre outer is greater than inner
     * @pre slices is greater than two
     * @pre rings is greater than zero
     * @pre start is between [0, 360]
     * @pre sweep is between [0, 360]
     * @note Disk is drawn in the XY plane with the origin at its center
     */
    [[maybe_unused]] void drawSolidPartialDisk( GLfloat inner, GLfloat outer, GLint slices, GLint rings, GLfloat start, GLfloat sweep );
    /**
     * @brief Draws part of a wireframe disk
     * @param inner equivalent to the width of the disk
     * @param outer radius from the center of the disk to the center of the ring
     * @param slices resolution of the number of steps rotated along the disk
     * @param rings resolution of the number of steps to take along the disk width
     * @param start angle in degrees to start the disk at
     * @param sweep distance in degrees to rotate through
     * @pre inner is greater than or equal to zero
     * @pre outer is greater than zero
     * @pre outer is greater than inner
     * @pre slices is greater than two
     * @pre rings is greater than zero
     * @pre start is between [0, 360]
     * @pre sweep is between [0, 360]
     * @note Disk is drawn in the XY plane with the origin at its center
     */
    [[maybe_unused]] void drawWirePartialDisk( GLfloat inner, GLfloat outer, GLint slices, GLint rings, GLfloat start, GLfloat sweep );

    /**
     * @brief Draws a solid sphere
     * @param radius radius of the sphere
     * @param stacks resolution of the number of steps to take along theta (rotate around Y-axis)
     * @param slices resolution of the number of steps to take along phi (rotate around X- or Z-axis)
     * @pre radius must be greater than 0
     * @pre stacks must be greater than 2
     * @pre slices must be greater than 2
     * @note Origin is at the center of the sphere
     */
    [[maybe_unused]] void drawSolidSphere( GLfloat radius, GLint stacks, GLint slices );
    /**
     * @brief Draws a wireframe sphere
     * @param radius radius of the sphere
     * @param stacks resolution of the number of steps to take along theta (rotate around Y-axis)
     * @param slices resolution of the number of steps to take along phi (rotate around X- or Z-axis)
     * @pre radius must be greater than 0
     * @pre stacks must be greater than 2
     * @pre slices must be greater than 2
     * @note Origin is at the center of the sphere
     */
    [[maybe_unused]] void drawWireSphere( GLfloat radius, GLint stacks, GLint slices );

    /**
     * @brief Draws a solid teapot
     * @param unused present for historical compatability
     * @pre size must be greater than zero
     * @note Oriented with spout and handle running along X-axis, cap and bottom along Y-axis.  Origin is at the center of the teapot
     */
    [[maybe_unused]] void drawSolidTeapot( GLfloat unused = 1.0f );
    /**
     * @brief Draws a wireframe teapot
     * @param unused present for historical compatability
     * @pre size must be greater than zero
     * @note Oriented with spout and handle running along X-axis, cap and bottom along Y-axis.  Origin is at the center of the teapot
     */
    [[maybe_unused]] void drawWireTeapot( GLfloat unused = 1.0f );

    /**
     * @brief Draws a solid torus
     * @param innerRadius equivalent to the width of the torus ring
     * @param outerRadius radius from the center of the torus to the center of the ring
     * @param sides resolution of steps to take around the band of the ring
     * @param rings resolution of steps to take around the torus
     * @pre innerRadius must be greater than zero
     * @pre outerRadius must be greater than zero
     * @pre sides must be greater than two
     * @pre rings must be greater than two
     * @note Torus is oriented in the XY-plane with the origin at its center
     */
    [[maybe_unused]] void drawSolidTorus( GLfloat innerRadius, GLfloat outerRadius, GLint sides, GLint rings );
    /**
     * @brief Draws a wireframe torus
     * @param innerRadius equivalent to the width of the torus ring
     * @param outerRadius radius from the center of the torus to the center of the ring
     * @param sides resolution of steps to take around the band of the ring
     * @param rings resolution of steps to take around the torus
     * @pre innerRadius must be greater than zero
     * @pre outerRadius must be greater than zero
     * @pre sides must be greater than two
     * @pre rings must be greater than two
     * @note Torus is oriented in the XY-plane with the origin at its center
     */
    [[maybe_unused]] void drawWireTorus( GLfloat innerRadius, GLfloat outerRadius, GLint sides, GLint rings );
}

////////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////
// Internal rendering implementations to stay consistent with solid and wire modes
//
// Cone is drawn with a cylinder
// Disk is drawn with a partial disk

namespace CSCI441_INTERNAL {
    void deleteObjectVAOs();
    void deleteObjectVBOs();

    void drawCube( GLfloat sideLength, GLenum renderMode );
    void drawCubeIndexed( GLfloat sideLength, GLenum renderMode );
    void drawCubeFlat( GLfloat sideLength, GLenum renderMode );
    void drawCylinder( GLfloat base, GLfloat top, GLfloat height, GLuint stacks, GLuint slices, GLenum renderMode );
    void drawPartialDisk(GLfloat innerRadius, GLfloat outerRadius, GLuint slices, GLuint rings, GLfloat startAngle, GLfloat sweepAngle, GLenum renderMode );
    void drawSphere( GLfloat radius, GLuint stacks, GLuint slices, GLenum renderMode );
    void drawTorus( GLfloat innerRadius, GLfloat outerRadius, GLuint sides, GLuint rings, GLenum renderMode );
    void drawTeapot( GLenum renderMode );

    inline GLint _positionAttributeLocation = -1;
    inline GLint _normalAttributeLocation = -1;
    inline GLint _texCoordAttributeLocation = -1;

    void generateCubeVAOFlat( GLfloat sideLength );
    void generateCubeVAOIndexed( GLfloat sideLength );
    inline std::map< GLfloat, GLuint > _cubeVAO;
    inline std::map< GLfloat, GLuint > _cubeVBO;
    inline std::map< GLfloat, GLuint > _cubeVAOIndexed;
    inline std::map< GLfloat, GLuint > _cubeVBOIndexed;

    // stores data necessary to specify a unique cylinder
    struct CylinderData {
        // radius of the base
        GLfloat radiusBase;
        // radius of the top
        GLfloat top;
        // height
        GLfloat height;
        // number of stacks
        GLuint stacks;
        // number of slices
        GLuint slices;
        // compute number of vertices
        [[nodiscard]] GLulong numVertices() const { return stacks * (slices + 1) * 2; }
        bool operator<( const CylinderData rhs ) const {
            if( radiusBase < rhs.radiusBase ) {
                return true;
            } else if( fabs(radiusBase - rhs.radiusBase) <= 0.000001 ) {
                if( top < rhs.top ) {
                    return true;
                } else if( fabs(top - rhs.top) <= 0.000001 ) {
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
    void generateCylinderVAO( CylinderData cylData );
    inline std::map< CylinderData, GLuint > _cylinderVAO;
    inline std::map< CylinderData, GLuint > _cylinderVBO;

    struct DiskData {
        GLfloat innerRadius, outerRadius, startAngle, sweepAngle;
        GLuint slices, rings;
        [[nodiscard]] GLulong numVertices() const { return rings * (slices + 1) * 2; }
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
    void generateDiskVAO( DiskData diskData );
    inline std::map< DiskData, GLuint > _diskVAO;
    inline std::map< DiskData, GLuint > _diskVBO;

    struct SphereData {
        GLfloat radius;
        GLuint stacks, slices;
        [[nodiscard]] GLulong numVertices() const { return ((slices + 2) * 2) + (((stacks - 2) * (slices+1)) * 2); }
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
    void generateSphereVAO( SphereData sphereData );
    inline std::map< SphereData, GLuint > _sphereVAO;
    inline std::map< SphereData, GLuint > _sphereVBO;

    struct TorusData {
        GLfloat innerRadius, outerRadius;
        GLuint sides, rings;
        [[nodiscard]] GLulong numVertices() const { return sides * 4 * rings; }
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
    void generateTorusVAO( TorusData torusData );
    inline std::map< TorusData, GLuint > _torusVAO;
    inline std::map< TorusData, GLuint > _torusVBO;
}

////////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////
// Outward facing function implementations

inline void CSCI441::setVertexAttributeLocations( GLint positionLocation, GLint normalLocation, GLint texCoordLocation ) {
    CSCI441_INTERNAL::_positionAttributeLocation = positionLocation;
    CSCI441_INTERNAL::_normalAttributeLocation = normalLocation;
    CSCI441_INTERNAL::_texCoordAttributeLocation = texCoordLocation;
    CSCI441_INTERNAL::setTeapotAttributeLocations(positionLocation, normalLocation, texCoordLocation);
}

[[maybe_unused]]
inline void CSCI441::deleteObjectVAOs() {
    CSCI441_INTERNAL::deleteObjectVAOs();
}

[[maybe_unused]]
inline void CSCI441::deleteObjectVBOs() {
    CSCI441_INTERNAL::deleteObjectVBOs();
}

[[maybe_unused]]
inline void CSCI441::drawSolidCone( GLfloat base, GLfloat height, GLint stacks, GLint slices ) {
    assert( base > 0.0f );
    assert( height > 0.0f );
    assert( stacks > 0 );
    assert( slices > 2 );

    CSCI441_INTERNAL::drawCylinder( base, 0.0f, height, stacks, slices, GL_FILL );
}

[[maybe_unused]]
inline void CSCI441::drawWireCone( GLfloat base, GLfloat height, GLint stacks, GLint slices ) {
    assert( base > 0.0f );
    assert( height > 0.0f );
    assert( stacks > 0 );
    assert( slices > 2 );

    CSCI441_INTERNAL::drawCylinder( base, 0.0f, height, stacks, slices, GL_LINE );
}

[[maybe_unused]]
inline void CSCI441::drawSolidCube( GLfloat sideLength ) {
    drawSolidCubeIndexed(sideLength);
}

[[maybe_unused]]
inline void CSCI441::drawSolidCubeTextured( GLfloat sideLength ) {
    drawSolidCubeFlat(sideLength);
}

inline void CSCI441::drawSolidCubeIndexed(GLfloat sideLength) {
    assert( sideLength > 0.0f );

    CSCI441_INTERNAL::drawCube( sideLength, GL_FILL );
}

inline void CSCI441::drawSolidCubeFlat(GLfloat sideLength) {
    assert( sideLength > 0.0f );

    CSCI441_INTERNAL::drawCubeFlat( sideLength, GL_FILL );
}

[[maybe_unused]]
inline void CSCI441::drawWireCube( GLfloat sideLength ) {
    assert( sideLength > 0.0f );

    CSCI441_INTERNAL::drawCube( sideLength, GL_LINE );
}

[[maybe_unused]]
inline void CSCI441::drawCubeMap(GLfloat sideLength) {
    assert(sideLength > 0.0f);

    CSCI441_INTERNAL::drawCube( sideLength, GL_FILL );
}

[[maybe_unused]]
inline void CSCI441::drawSolidCylinder( GLfloat base, GLfloat top, GLfloat height, GLint stacks, GLint slices ) {
    assert( (base >= 0.0f && top > 0.0f) || (base > 0.0f && top >= 0.0f) );
    assert( height > 0.0f );
    assert( stacks > 0 );
    assert( slices > 2 );

    CSCI441_INTERNAL::drawCylinder( base, top, height, stacks, slices, GL_FILL );
}

[[maybe_unused]]
inline void CSCI441::drawWireCylinder( GLfloat base, GLfloat top, GLfloat height, GLint stacks, GLint slices ) {
    assert( (base >= 0.0f && top > 0.0f) || (base > 0.0f && top >= 0.0f) );
    assert( height > 0.0f );
    assert( stacks > 0 );
    assert( slices > 2 );

    CSCI441_INTERNAL::drawCylinder( base, top, height, stacks, slices, GL_LINE );
}

[[maybe_unused]]
inline void CSCI441::drawSolidDisk( GLfloat inner, GLfloat outer, GLint slices, GLint rings ) {
    assert( inner >= 0.0f );
    assert( outer > 0.0f );
    assert( outer > inner );
    assert( slices > 2 );
    assert( rings > 0 );

    CSCI441_INTERNAL::drawPartialDisk( inner, outer, slices, rings, 0, glm::two_pi<float>(), GL_FILL );
}

[[maybe_unused]]
inline void CSCI441::drawWireDisk( GLfloat inner, GLfloat outer, GLint slices, GLint rings ) {
    assert( inner >= 0.0f );
    assert( outer > 0.0f );
    assert( outer > inner );
    assert( slices > 2 );
    assert( rings > 0 );

    CSCI441_INTERNAL::drawPartialDisk( inner, outer, slices, rings, 0, glm::two_pi<float>(), GL_LINE );
}

[[maybe_unused]]
inline void CSCI441::drawSolidPartialDisk( GLfloat inner, GLfloat outer, GLint slices, GLint rings, GLfloat start, GLfloat sweep ) {
    assert( inner >= 0.0f );
    assert( outer > 0.0f );
    assert( outer > inner );
    assert( slices > 2 );
    assert( rings > 0 );
    assert( start >= 0.0f && start <= 360.0f );
    assert( sweep >= 0.0f && sweep <= 360.0f );

    CSCI441_INTERNAL::drawPartialDisk( inner, outer, slices, rings, start * glm::pi<float>() / 180.0f, sweep * glm::pi<float>() / 180.0f, GL_FILL );
}

[[maybe_unused]]
inline void CSCI441::drawWirePartialDisk( GLfloat inner, GLfloat outer, GLint slices, GLint rings, GLfloat start, GLfloat sweep ) {
    assert( inner >= 0.0f );
    assert( outer > 0.0f );
    assert( outer > inner );
    assert( slices > 2 );
    assert( rings > 0 );
    assert( start >= 0.0f && start <= 360.0f );
    assert( sweep >= 0.0f && sweep <= 360.0f );

    CSCI441_INTERNAL::drawPartialDisk( inner, outer, slices, rings, start * glm::pi<float>() / 180.0f, sweep * glm::pi<float>() / 180.0f, GL_LINE );
}

[[maybe_unused]]
inline void CSCI441::drawSolidSphere( GLfloat radius, GLint stacks, GLint slices ) {
    assert( radius > 0.0f );
    assert( stacks > 1 );
    assert( slices > 2 );

    CSCI441_INTERNAL::drawSphere( radius, stacks, slices, GL_FILL );
}

[[maybe_unused]]
inline void CSCI441::drawWireSphere( GLfloat radius, GLint stacks, GLint slices ) {
    assert( radius > 0.0f );
    assert( stacks > 1);
    assert( slices > 2 );

    CSCI441_INTERNAL::drawSphere( radius, stacks, slices, GL_LINE );
}

[[maybe_unused]]
inline void CSCI441::drawSolidTeapot( [[maybe_unused]] GLfloat unused ) {
    CSCI441_INTERNAL::drawTeapot(GL_FILL);
}

[[maybe_unused]]
inline void CSCI441::drawWireTeapot( [[maybe_unused]] GLfloat unused ) {
    CSCI441_INTERNAL::drawTeapot(GL_LINE);
}

[[maybe_unused]]
inline void CSCI441::drawSolidTorus( GLfloat innerRadius, GLfloat outerRadius, GLint sides, GLint rings ) {
    assert( innerRadius > 0.0f );
    assert( outerRadius > 0.0f );
    assert( sides > 2 );
    assert( rings > 2 );

    CSCI441_INTERNAL::drawTorus( innerRadius, outerRadius, sides, rings, GL_FILL );
}

[[maybe_unused]]
inline void CSCI441::drawWireTorus( GLfloat innerRadius, GLfloat outerRadius, GLint sides, GLint rings ) {
    assert( innerRadius > 0.0f );
    assert( outerRadius > 0.0f );
    assert( sides > 2 );
    assert( rings > 2 );

    CSCI441_INTERNAL::drawTorus( innerRadius, outerRadius, sides, rings, GL_LINE );
}

////////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////
// Internal function rendering implementations

inline void CSCI441_INTERNAL::deleteObjectVAOs() {
    for(auto & iter : _cubeVAO) {
        glDeleteVertexArrays(1, &(iter.second));
    }
    for(auto & iter : _cubeVAOIndexed) {
        glDeleteVertexArrays(1, &(iter.second));
    }
    for(auto & iter : _cylinderVAO) {
        glDeleteVertexArrays(1, &(iter.second));
    }
    for(auto & iter : _diskVAO) {
        glDeleteVertexArrays(1, &(iter.second));
    }
    for(auto & iter : _sphereVAO) {
        glDeleteVertexArrays(1, &(iter.second));
    }
    for(auto & iter : _torusVAO) {
        glDeleteVertexArrays(1, &(iter.second));
    }
}

inline void CSCI441_INTERNAL::deleteObjectVBOs() {
    for(auto & iter : _cubeVBO) {
        glDeleteBuffers(1, &(iter.second));
    }
    for(auto & iter : _cubeVBOIndexed) {
        glDeleteBuffers(1, &(iter.second));
    }
    for(auto & iter : _cylinderVBO) {
        glDeleteBuffers(1, &(iter.second));
    }
    for(auto & iter : _diskVBO) {
        glDeleteBuffers(1, &(iter.second));
    }
    for(auto & iter : _sphereVBO) {
        glDeleteBuffers(1, &(iter.second));
    }
    for(auto & iter : _torusVBO) {
        glDeleteBuffers(1, &(iter.second));
    }
}

inline void CSCI441_INTERNAL::drawCube( GLfloat sideLength, GLenum renderMode ) {
    drawCubeIndexed(sideLength, renderMode);
}

inline void CSCI441_INTERNAL::drawCubeFlat( GLfloat sideLength, GLenum renderMode ) {
    if( CSCI441_INTERNAL::_cubeVAO.count( sideLength ) == 0 ) {
        CSCI441_INTERNAL::generateCubeVAOFlat( sideLength );
    }

    const GLulong NUM_VERTICES = 36;

    GLint currentPolygonMode[2];
    glGetIntegerv(GL_POLYGON_MODE, currentPolygonMode);

    glPolygonMode( GL_FRONT_AND_BACK, renderMode );
    glBindVertexArray( CSCI441_INTERNAL::_cubeVAO.find( sideLength )->second );
    glBindBuffer( GL_ARRAY_BUFFER, CSCI441_INTERNAL::_cubeVBO.find( sideLength )->second );
    if(CSCI441_INTERNAL::_positionAttributeLocation != -1) {
        glEnableVertexAttribArray( CSCI441_INTERNAL::_positionAttributeLocation );
        glVertexAttribPointer( CSCI441_INTERNAL::_positionAttributeLocation, 3, GL_FLOAT, GL_FALSE, 0, (void*)nullptr );
    }
    if(CSCI441_INTERNAL::_normalAttributeLocation != -1) {
        glEnableVertexAttribArray( CSCI441_INTERNAL::_normalAttributeLocation );
        glVertexAttribPointer( CSCI441_INTERNAL::_normalAttributeLocation, 3, GL_FLOAT, GL_FALSE, 0, (void*)(sizeof(glm::vec3) * NUM_VERTICES) );
    }
    if(CSCI441_INTERNAL::_texCoordAttributeLocation != -1) {
        glEnableVertexAttribArray( CSCI441_INTERNAL::_texCoordAttributeLocation );
        glVertexAttribPointer( CSCI441_INTERNAL::_texCoordAttributeLocation, 2, GL_FLOAT, GL_FALSE, 0, (void*)(sizeof(glm::vec3) * NUM_VERTICES * 2) );
    }

    glDrawArrays( GL_TRIANGLES, 0, 36 );

    glPolygonMode( GL_FRONT, currentPolygonMode[0] );
    glPolygonMode( GL_BACK, currentPolygonMode[1] );
}

inline void CSCI441_INTERNAL::drawCubeIndexed( GLfloat sideLength, GLenum renderMode ) {
    if( CSCI441_INTERNAL::_cubeVAOIndexed.count( sideLength ) == 0 ) {
        CSCI441_INTERNAL::generateCubeVAOIndexed( sideLength );
    }

    const GLulong NUM_VERTICES = 8;

    GLint currentPolygonMode[2];
    glGetIntegerv(GL_POLYGON_MODE, currentPolygonMode);

    glPolygonMode( GL_FRONT_AND_BACK, renderMode );
    glBindVertexArray( CSCI441_INTERNAL::_cubeVAOIndexed.find( sideLength )->second );
    glBindBuffer( GL_ARRAY_BUFFER, CSCI441_INTERNAL::_cubeVBOIndexed.find( sideLength )->second );
    if(CSCI441_INTERNAL::_positionAttributeLocation != -1) {
        glEnableVertexAttribArray( CSCI441_INTERNAL::_positionAttributeLocation );
        glVertexAttribPointer( CSCI441_INTERNAL::_positionAttributeLocation, 3, GL_FLOAT, GL_FALSE, 0, (void*)nullptr );
    }
    if(CSCI441_INTERNAL::_normalAttributeLocation != -1) {
        glEnableVertexAttribArray( CSCI441_INTERNAL::_normalAttributeLocation );
        glVertexAttribPointer( CSCI441_INTERNAL::_normalAttributeLocation, 3, GL_FLOAT, GL_FALSE, 0, (void*)(sizeof(glm::vec3) * NUM_VERTICES) );
    }
    if(CSCI441_INTERNAL::_texCoordAttributeLocation != -1) {
        glEnableVertexAttribArray( CSCI441_INTERNAL::_texCoordAttributeLocation );
        glVertexAttribPointer( CSCI441_INTERNAL::_texCoordAttributeLocation, 2, GL_FLOAT, GL_FALSE, 0, (void*)(sizeof(glm::vec3) * NUM_VERTICES * 2) );
    }

    glDrawElements(GL_TRIANGLES, 36, GL_UNSIGNED_SHORT, (void*)nullptr);

    glPolygonMode( GL_FRONT, currentPolygonMode[0] );
    glPolygonMode( GL_BACK, currentPolygonMode[1] );
}

inline void CSCI441_INTERNAL::drawCylinder( GLfloat base, GLfloat top, GLfloat height, GLuint stacks, GLuint slices, GLenum renderMode ) {
    CylinderData cylData = { base, top, height, stacks, slices };
    if( CSCI441_INTERNAL::_cylinderVAO.count( cylData ) == 0 ) {
        CSCI441_INTERNAL::generateCylinderVAO( cylData );
    }

    const GLulong NUM_VERTICES = cylData.numVertices();

    GLint currentPolygonMode[2];
    glGetIntegerv(GL_POLYGON_MODE, currentPolygonMode);

    glPolygonMode( GL_FRONT_AND_BACK, renderMode );
    glBindVertexArray( CSCI441_INTERNAL::_cylinderVAO.find( cylData )->second );
    glBindBuffer( GL_ARRAY_BUFFER, CSCI441_INTERNAL::_cylinderVBO.find( cylData )->second );
    if(CSCI441_INTERNAL::_positionAttributeLocation != -1) {
        glEnableVertexAttribArray( CSCI441_INTERNAL::_positionAttributeLocation );
        glVertexAttribPointer( CSCI441_INTERNAL::_positionAttributeLocation, 3, GL_FLOAT, GL_FALSE, 0, (void*)nullptr );
    }
    if(CSCI441_INTERNAL::_normalAttributeLocation != -1) {
        glEnableVertexAttribArray( CSCI441_INTERNAL::_normalAttributeLocation );
        glVertexAttribPointer( CSCI441_INTERNAL::_normalAttributeLocation, 3, GL_FLOAT, GL_FALSE, 0, (void*)(sizeof(glm::vec3) * NUM_VERTICES) );
    }
    if(CSCI441_INTERNAL::_texCoordAttributeLocation != -1) {
        glEnableVertexAttribArray( CSCI441_INTERNAL::_texCoordAttributeLocation );
        glVertexAttribPointer( CSCI441_INTERNAL::_texCoordAttributeLocation, 2, GL_FLOAT, GL_FALSE, 0, (void*)(sizeof(glm::vec3) * NUM_VERTICES * 2) );
    }

    for(GLuint stackNum = 0; stackNum < stacks; stackNum++) {
        glDrawArrays( GL_TRIANGLE_STRIP, static_cast<GLint>((slices+1)*2*stackNum), static_cast<GLint>((slices+1)*2) );
    }

    glPolygonMode( GL_FRONT, currentPolygonMode[0] );
    glPolygonMode( GL_BACK, currentPolygonMode[1] );
}

inline void CSCI441_INTERNAL::drawPartialDisk(GLfloat innerRadius, GLfloat outerRadius, GLuint slices, GLuint rings, GLfloat startAngle, GLfloat sweepAngle, GLenum renderMode ) {
    DiskData diskData = {innerRadius, outerRadius, startAngle, sweepAngle, slices, rings };
    if( CSCI441_INTERNAL::_diskVAO.count( diskData ) == 0 ) {
        CSCI441_INTERNAL::generateDiskVAO( diskData );
    }

    const GLulong NUM_VERTICES = diskData.numVertices();

    GLint currentPolygonMode[2];
    glGetIntegerv(GL_POLYGON_MODE, currentPolygonMode);

    glPolygonMode( GL_FRONT_AND_BACK, renderMode );
    glBindVertexArray( CSCI441_INTERNAL::_diskVAO.find( diskData )->second );
    glBindBuffer( GL_ARRAY_BUFFER, CSCI441_INTERNAL::_diskVBO.find( diskData )->second );
    if(CSCI441_INTERNAL::_positionAttributeLocation != -1) {
        glEnableVertexAttribArray( CSCI441_INTERNAL::_positionAttributeLocation );
        glVertexAttribPointer( CSCI441_INTERNAL::_positionAttributeLocation, 3, GL_FLOAT, GL_FALSE, 0, (void*)nullptr );
    }
    if(CSCI441_INTERNAL::_normalAttributeLocation != -1) {
        glEnableVertexAttribArray( CSCI441_INTERNAL::_normalAttributeLocation );
        glVertexAttribPointer( CSCI441_INTERNAL::_normalAttributeLocation, 3, GL_FLOAT, GL_FALSE, 0, (void*)(sizeof(glm::vec3) * NUM_VERTICES) );
    }
    if(CSCI441_INTERNAL::_texCoordAttributeLocation != -1) {
        glEnableVertexAttribArray( CSCI441_INTERNAL::_texCoordAttributeLocation );
        glVertexAttribPointer( CSCI441_INTERNAL::_texCoordAttributeLocation, 2, GL_FLOAT, GL_FALSE, 0, (void*)(sizeof(glm::vec3) * NUM_VERTICES * 2) );
    }

    for(GLuint ringNum = 0; ringNum < rings; ringNum++) {
        glDrawArrays( GL_TRIANGLE_STRIP, static_cast<GLint>((slices+1)*2*ringNum), static_cast<GLint>((slices+1)*2) );
    }

    glPolygonMode( GL_FRONT, currentPolygonMode[0] );
    glPolygonMode( GL_BACK, currentPolygonMode[1] );
}

inline void CSCI441_INTERNAL::drawSphere( GLfloat radius, GLuint stacks, GLuint slices, GLenum renderMode ) {
    SphereData sphereData = { radius, stacks, slices };
    if( CSCI441_INTERNAL::_sphereVAO.count( sphereData ) == 0 ) {
        CSCI441_INTERNAL::generateSphereVAO( sphereData );
    }

    const GLulong NUM_VERTICES = sphereData.numVertices();

    GLint currentPolygonMode[2];
    glGetIntegerv(GL_POLYGON_MODE, currentPolygonMode);

    glPolygonMode( GL_FRONT_AND_BACK, renderMode );
    glBindVertexArray( CSCI441_INTERNAL::_sphereVAO.find( sphereData )->second );
    glBindBuffer( GL_ARRAY_BUFFER, CSCI441_INTERNAL::_sphereVBO.find( sphereData )->second );
    if(CSCI441_INTERNAL::_positionAttributeLocation != -1) {
        glEnableVertexAttribArray( CSCI441_INTERNAL::_positionAttributeLocation );
        glVertexAttribPointer( CSCI441_INTERNAL::_positionAttributeLocation, 3, GL_FLOAT, GL_FALSE, 0, (void*)nullptr );
    }
    if(CSCI441_INTERNAL::_normalAttributeLocation != -1) {
        glEnableVertexAttribArray( CSCI441_INTERNAL::_normalAttributeLocation );
        glVertexAttribPointer( CSCI441_INTERNAL::_normalAttributeLocation, 3, GL_FLOAT, GL_FALSE, 0, (void*)(sizeof(glm::vec3) * NUM_VERTICES) );
    }
    if(CSCI441_INTERNAL::_texCoordAttributeLocation != -1) {
        glEnableVertexAttribArray( CSCI441_INTERNAL::_texCoordAttributeLocation );
        glVertexAttribPointer( CSCI441_INTERNAL::_texCoordAttributeLocation, 2, GL_FLOAT, GL_FALSE, 0, (void*)(sizeof(glm::vec3) * NUM_VERTICES * 2) );
    }

    glDrawArrays( GL_TRIANGLE_FAN, 0, static_cast<GLint>(slices+2) );

    for(GLuint stackNum = 1; stackNum < stacks-1; stackNum++) {
        glDrawArrays( GL_TRIANGLE_STRIP, static_cast<GLint>((slices+2) + (stackNum-1)*((slices+1)*2)), static_cast<GLint>((slices+1)*2) );
    }

    glDrawArrays( GL_TRIANGLE_FAN, static_cast<GLint>((slices+2) + (stacks-2)*(slices+1)*2), static_cast<GLint>(slices+2) );

    glPolygonMode( GL_FRONT, currentPolygonMode[0] );
    glPolygonMode( GL_BACK, currentPolygonMode[1] );
}

inline void CSCI441_INTERNAL::drawTorus( GLfloat innerRadius, GLfloat outerRadius, GLuint sides, GLuint rings, GLenum renderMode ) {
    TorusData torusData = { innerRadius, outerRadius, sides, rings };
    if( CSCI441_INTERNAL::_torusVAO.count( torusData ) == 0 ) {
        CSCI441_INTERNAL::generateTorusVAO( torusData );
    }

    const GLulong NUM_VERTICES = torusData.numVertices();

    GLint currentPolygonMode[2];
    glGetIntegerv(GL_POLYGON_MODE, currentPolygonMode);

    glPolygonMode( GL_FRONT_AND_BACK, renderMode );
    glBindVertexArray( CSCI441_INTERNAL::_torusVAO.find( torusData )->second );
    glBindBuffer( GL_ARRAY_BUFFER, CSCI441_INTERNAL::_torusVBO.find( torusData )->second );
    if(CSCI441_INTERNAL::_positionAttributeLocation != -1) {
        glEnableVertexAttribArray( CSCI441_INTERNAL::_positionAttributeLocation );
        glVertexAttribPointer( CSCI441_INTERNAL::_positionAttributeLocation, 3, GL_FLOAT, GL_FALSE, 0, (void*)nullptr );
    }
    if(CSCI441_INTERNAL::_normalAttributeLocation != -1) {
        glEnableVertexAttribArray( CSCI441_INTERNAL::_normalAttributeLocation );
        glVertexAttribPointer( CSCI441_INTERNAL::_normalAttributeLocation, 3, GL_FLOAT, GL_FALSE, 0, (void*)(sizeof(glm::vec3) * NUM_VERTICES) );
    }
    if(CSCI441_INTERNAL::_texCoordAttributeLocation != -1) {
        glEnableVertexAttribArray( CSCI441_INTERNAL::_texCoordAttributeLocation );
        glVertexAttribPointer( CSCI441_INTERNAL::_texCoordAttributeLocation, 2, GL_FLOAT, GL_FALSE, 0, (void*)(sizeof(glm::vec3) * NUM_VERTICES * 2) );
    }

    for(GLuint ringNum = 0; ringNum < rings; ringNum++) {
        glDrawArrays( GL_TRIANGLE_STRIP, static_cast<GLint>(ringNum*sides*4), static_cast<GLint>(sides*4) );
    }

    glPolygonMode( GL_FRONT, currentPolygonMode[0] );
    glPolygonMode( GL_BACK, currentPolygonMode[1] );
}

inline void CSCI441_INTERNAL::drawTeapot( GLenum renderMode ) {
    GLint currentPolygonMode[2];
    glGetIntegerv(GL_POLYGON_MODE, currentPolygonMode);

    glPolygonMode( GL_FRONT_AND_BACK, renderMode );
    CSCI441_INTERNAL::teapot();
    glPolygonMode( GL_FRONT, currentPolygonMode[0] );
    glPolygonMode( GL_BACK, currentPolygonMode[1] );
}

inline void CSCI441_INTERNAL::generateCubeVAOFlat( GLfloat sideLength ) {
    GLuint vaod;
    glGenVertexArrays( 1, &vaod );
    glBindVertexArray( vaod );

    GLuint vbod;
    glGenBuffers( 1, &vbod );
    glBindBuffer( GL_ARRAY_BUFFER, vbod );

    const GLfloat CORNER_POINT = sideLength / 2.0f;

    const GLulong NUM_VERTICES = 36;

    glm::vec3 vertices[NUM_VERTICES] = {
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
    glm::vec3 normals[NUM_VERTICES] = {
            // Left Face
            {-1.0f, 0.0f, 0.0f}, {-1.0f, 0.0f, 0.0f}, {-1.0f, 0.0f, 0.0f},
            {-1.0f, 0.0f, 0.0f}, {-1.0f, 0.0f, 0.0f}, {-1.0f, 0.0f, 0.0f},
            // Right Face
            {1.0f, 0.0f, 0.0f}, {1.0f, 0.0f, 0.0f}, {1.0f, 0.0f, 0.0f},
            {1.0f, 0.0f, 0.0f}, {1.0f, 0.0f, 0.0f}, {1.0f, 0.0f, 0.0f},
            // Top Face
            {0.0f, 1.0f, 0.0f}, {0.0f, 1.0f, 0.0f}, {0.0f, 1.0f, 0.0f},
            {0.0f, 1.0f, 0.0f}, {0.0f, 1.0f, 0.0f}, {0.0f, 1.0f, 0.0f},
            // Bottom Face
            {0.0f, -1.0f, 0.0f}, {0.0f, -1.0f, 0.0f}, {0.0f, -1.0f, 0.0f},
            {0.0f, -1.0f, 0.0f}, {0.0f, -1.0f, 0.0f}, {0.0f, -1.0f, 0.0f},
            // Back Face
            {0.0f, 0.0f, -1.0f}, {0.0f, 0.0f, -1.0f}, {0.0f, 0.0f, -1.0f},
            {0.0f, 0.0f, -1.0f}, {0.0f, 0.0f, -1.0f}, {0.0f, 0.0f, -1.0f},
            // Front Face
            {0.0f, 0.0f, 1.0f}, {0.0f, 0.0f, 1.0f}, {0.0f, 0.0f, 1.0f},
            {0.0f, 0.0f, 1.0f}, {0.0f, 0.0f, 1.0f}, {0.0f, 0.0f, 1.0f}
    };
    glm::vec2 texCoords[NUM_VERTICES] = {
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

    glBufferData(GL_ARRAY_BUFFER, (sizeof(glm::vec3)*2 + sizeof(glm::vec2)) * NUM_VERTICES, nullptr, GL_STATIC_DRAW );
    glBufferSubData(GL_ARRAY_BUFFER, 0, sizeof(glm::vec3) * NUM_VERTICES, vertices );
    glBufferSubData(GL_ARRAY_BUFFER, sizeof(glm::vec3) * NUM_VERTICES, sizeof(glm::vec3) * NUM_VERTICES, normals );
    glBufferSubData(GL_ARRAY_BUFFER, sizeof(glm::vec3) * NUM_VERTICES * 2, sizeof(glm::vec2) * NUM_VERTICES, texCoords );

    CSCI441_INTERNAL::_cubeVAO.insert( std::pair<GLfloat, GLuint>( sideLength, vaod ) );
    CSCI441_INTERNAL::_cubeVBO.insert( std::pair<GLfloat, GLuint>( sideLength, vbod ) );
}

inline void CSCI441_INTERNAL::generateCubeVAOIndexed( GLfloat sideLength ) {
    const GLfloat CORNER_POINT = sideLength / 2.0f;

    const GLulong NUM_VERTICES = 8;

    glm::vec3 vertices[NUM_VERTICES] = {
            { -CORNER_POINT, -CORNER_POINT, -CORNER_POINT }, // 0 - bln
            {  CORNER_POINT, -CORNER_POINT, -CORNER_POINT }, // 1 - brn
            {  CORNER_POINT,  CORNER_POINT, -CORNER_POINT }, // 2 - trn
            { -CORNER_POINT,  CORNER_POINT, -CORNER_POINT }, // 3 - tln
            { -CORNER_POINT, -CORNER_POINT,  CORNER_POINT }, // 4 - blf
            {  CORNER_POINT, -CORNER_POINT,  CORNER_POINT }, // 5 - brf
            {  CORNER_POINT,  CORNER_POINT,  CORNER_POINT }, // 6 - trf
            { -CORNER_POINT,  CORNER_POINT,  CORNER_POINT }  // 7 - tlf
    };
    glm::vec3 normals[NUM_VERTICES] = {
            {-1.0f, -1.0f, -1.0f}, // 0 bln
            { 1.0f, -1.0f, -1.0f}, // 1 brn
            { 1.0f,  1.0f, -1.0f}, // 2 trn
            {-1.0f,  1.0f, -1.0f}, // 3 tln
            {-1.0f, -1.0f,  1.0f}, // 4 blf
            { 1.0f, -1.0f,  1.0f}, // 5 brf
            { 1.0f,  1.0f,  1.0f}, // 6 trf
            {-1.0f,  1.0f,  1.0f}  // 7 tlf
    };
    glm::vec3 texCoords[NUM_VERTICES] = {
            {-1.0f, -1.0f, -1.0f}, // 0 bln
            { 1.0f, -1.0f, -1.0f}, // 1.0f brn
            { 1.0f,  1.0f, -1.0f}, // 2 trn
            {-1.0f,  1.0f, -1.0f}, // 3 tln
            {-1.0f, -1.0f,  1.0f}, // 4 blf
            { 1.0f, -1.0f,  1.0f}, // 5 brf
            { 1.0f,  1.0f,  1.0f}, // 6 trf
            {-1.0f,  1.0f,  1.0f}  // 7 tlf
    };
    GLushort indices[36] = {
            0, 1, 2,   0, 2, 3, // near
            1, 5, 2,   5, 6, 2, // right
            2, 6, 7,   3, 2, 7, // top
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
    glBufferData(GL_ARRAY_BUFFER, sizeof(glm::vec3) * NUM_VERTICES, nullptr, GL_STATIC_DRAW );
    glBufferSubData(GL_ARRAY_BUFFER, 0, sizeof(glm::vec3) * NUM_VERTICES, vertices  );
    glBufferSubData(GL_ARRAY_BUFFER, sizeof(glm::vec3) * NUM_VERTICES, sizeof(glm::vec3) * NUM_VERTICES, normals   );
    glBufferSubData(GL_ARRAY_BUFFER, sizeof(glm::vec3) * NUM_VERTICES * 2, sizeof(glm::vec3) * NUM_VERTICES, texCoords );

    glBindBuffer( GL_ELEMENT_ARRAY_BUFFER, vbods[1] );
    glBufferData( GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW) ;

    CSCI441_INTERNAL::_cubeVAOIndexed.insert( std::pair<GLfloat, GLuint>( sideLength, vaod ) );
    CSCI441_INTERNAL::_cubeVBOIndexed.insert( std::pair<GLfloat, GLuint>( sideLength, vbods[0] ) );
}

inline void CSCI441_INTERNAL::generateCylinderVAO( CylinderData cylData ) {
    GLuint vaod;
    glGenVertexArrays( 1, &vaod );
    glBindVertexArray( vaod );

    GLuint vbod;
    glGenBuffers( 1, &vbod );
    glBindBuffer( GL_ARRAY_BUFFER, vbod );

    const GLulong NUM_VERTICES = cylData.numVertices();

    GLfloat sliceStep = glm::two_pi<float>() / (GLfloat)cylData.slices;
    GLfloat stackStep = cylData.height / (GLfloat)cylData.stacks;

    auto vertices  = new glm::vec3[NUM_VERTICES];
    auto normals   = new glm::vec3[NUM_VERTICES];
    auto texCoords = new glm::vec2[NUM_VERTICES];

    GLulong idx = 0;

    for(GLuint stackNum = 0; stackNum < cylData.stacks; stackNum++ ) {
        GLfloat botRadius = cylData.radiusBase * (GLfloat)(cylData.stacks - stackNum) / (GLfloat)cylData.stacks + cylData.top * (GLfloat)stackNum / (GLfloat)cylData.stacks;
        GLfloat topRadius = cylData.radiusBase * (GLfloat)(cylData.stacks - stackNum - 1) / (GLfloat)cylData.stacks + cylData.top * (GLfloat)(stackNum + 1) / (GLfloat)cylData.stacks;

        for(GLuint sliceNum = 0; sliceNum <= cylData.slices; sliceNum++ ) {
            vertices[ idx ].x = glm::cos( sliceNum * sliceStep )*botRadius;
            vertices[ idx ].y = (GLfloat)stackNum * stackStep;
            vertices[ idx ].z = glm::sin( sliceNum * sliceStep )*botRadius;

            normals[ idx ].x = glm::cos( sliceNum * sliceStep );
            normals[ idx ].y = 0.0f;
            normals[ idx ].z = glm::sin( sliceNum * sliceStep );

            texCoords[ idx ].s = (GLfloat)sliceNum / (GLfloat)cylData.slices;
            texCoords[ idx ].t = (GLfloat)stackNum / (GLfloat)cylData.stacks;

            idx++;

            vertices[ idx ].x = glm::cos( sliceNum * sliceStep )*topRadius;
            vertices[ idx ].y = (GLfloat)(stackNum+1) * stackStep;
            vertices[ idx ].z = glm::sin( sliceNum * sliceStep )*topRadius;

            normals[ idx ].x = glm::cos( sliceNum * sliceStep );
            normals[ idx ].y = 0.0f;
            normals[ idx ].z = glm::sin( sliceNum * sliceStep );

            texCoords[ idx ].s = (GLfloat)sliceNum / (GLfloat)cylData.slices;
            texCoords[ idx ].t = (GLfloat)(stackNum+1) / (GLfloat)cylData.stacks;

            idx++;
        }
    }

    glBufferData(GL_ARRAY_BUFFER, (sizeof(glm::vec3)*2 + sizeof(glm::vec2)) * NUM_VERTICES, nullptr, GL_STATIC_DRAW );
    glBufferSubData(GL_ARRAY_BUFFER, 0, static_cast<GLsizeiptr>(sizeof(glm::vec3) * NUM_VERTICES), vertices );
    glBufferSubData(GL_ARRAY_BUFFER, static_cast<GLintptr>(sizeof(glm::vec3) * NUM_VERTICES), static_cast<GLsizeiptr>(sizeof(glm::vec3) * NUM_VERTICES), normals );
    glBufferSubData(GL_ARRAY_BUFFER, static_cast<GLintptr>(sizeof(glm::vec3) * NUM_VERTICES * 2), static_cast<GLsizeiptr>(sizeof(glm::vec2) * NUM_VERTICES), texCoords );

    CSCI441_INTERNAL::_cylinderVAO.insert( std::pair<CylinderData, GLuint>( cylData, vaod ) );
    CSCI441_INTERNAL::_cylinderVBO.insert( std::pair<CylinderData, GLuint>( cylData, vbod ) );

    delete[] vertices;
    delete[] texCoords;
    delete[] normals;
}

inline void CSCI441_INTERNAL::generateDiskVAO( DiskData diskData ) {
    GLuint vaod;
    glGenVertexArrays( 1, &vaod );
    glBindVertexArray( vaod );

    GLuint vbod;
    glGenBuffers( 1, &vbod );
    glBindBuffer( GL_ARRAY_BUFFER, vbod );

    const GLulong NUM_VERTICES = diskData.numVertices();

    GLfloat sliceStep = diskData.sweepAngle / (GLfloat)diskData.slices;
    GLfloat ringStep = (diskData.outerRadius - diskData.innerRadius) / (GLfloat)diskData.rings;

    auto vertices  = new glm::vec3[NUM_VERTICES];
    auto normals   = new glm::vec3[NUM_VERTICES];
    auto texCoords = new glm::vec2[NUM_VERTICES];

    GLulong idx = 0;

    for(GLuint ringNum = 0; ringNum < diskData.rings; ringNum++ ) {
        GLfloat currRadius = diskData.innerRadius + (GLfloat)ringNum * ringStep;
        GLfloat nextRadius = diskData.innerRadius + (GLfloat)(ringNum + 1) * ringStep;

        GLfloat theta = diskData.startAngle;
        for(GLuint i = 0; i <= diskData.slices; i++ ) {
            vertices[ idx ].x = glm::cos(theta)*currRadius;
            vertices[ idx ].y = glm::sin(theta)*currRadius;
            vertices[ idx ].z = 0.0f;

            normals[ idx ].x = 0.0f;
            normals[ idx ].y = 0.0f;
            normals[ idx ].z = 1.0f;

            texCoords[ idx ].s = glm::cos(theta)*(currRadius/diskData.outerRadius);
            texCoords[ idx ].t = glm::sin(theta)*(currRadius/diskData.outerRadius);

            idx++;

            vertices[ idx ].x = glm::cos(theta)*nextRadius;
            vertices[ idx ].y = glm::sin(theta)*nextRadius;
            vertices[ idx ].z = 0.0f;

            normals[ idx ].x = 0.0f;
            normals[ idx ].y = 0.0f;
            normals[ idx ].z = 1.0f;

            texCoords[ idx ].s = glm::cos(theta)*(nextRadius/diskData.outerRadius);
            texCoords[ idx ].t = glm::sin(theta)*(nextRadius/diskData.outerRadius);

            idx++;
            theta += sliceStep;
        }
    }

    glBufferData(GL_ARRAY_BUFFER, (sizeof(glm::vec3)*2 + sizeof(glm::vec2)) * NUM_VERTICES, nullptr, GL_STATIC_DRAW );
    glBufferSubData(GL_ARRAY_BUFFER, 0, sizeof(glm::vec3) * NUM_VERTICES, vertices );
    glBufferSubData(GL_ARRAY_BUFFER, sizeof(glm::vec3) * NUM_VERTICES, sizeof(glm::vec3) * NUM_VERTICES, normals );
    glBufferSubData(GL_ARRAY_BUFFER, sizeof(glm::vec3) * NUM_VERTICES * 2, sizeof(glm::vec2) * NUM_VERTICES, texCoords );

    CSCI441_INTERNAL::_diskVAO.insert( std::pair<DiskData, GLuint>( diskData, vaod ) );
    CSCI441_INTERNAL::_diskVBO.insert( std::pair<DiskData, GLuint>( diskData, vbod ) );

    delete[] vertices;
    delete[] texCoords;
    delete[] normals;
}

inline void CSCI441_INTERNAL::generateSphereVAO( SphereData sphereData ) {
    GLuint vaod;
    glGenVertexArrays( 1, &vaod );
    glBindVertexArray( vaod );

    GLuint vbod;
    glGenBuffers( 1, &vbod );
    glBindBuffer( GL_ARRAY_BUFFER, vbod );

    const GLulong NUM_VERTICES = sphereData.numVertices();

    GLfloat sliceStep = glm::two_pi<float>() / (GLfloat)sphereData.slices;
    GLfloat stackStep = glm::pi<float>() / (GLfloat)sphereData.stacks;

    auto vertices  = new glm::vec3[NUM_VERTICES];
    auto normals   = new glm::vec3[NUM_VERTICES];
    auto texCoords = new glm::vec2[NUM_VERTICES];

    GLulong idx = 0;

    // sphere top
    GLfloat phi = stackStep * (GLfloat)sphereData.stacks;
    GLfloat phiNext = stackStep * (GLfloat)(sphereData.stacks - 1);

    vertices[ idx ].x = 0.0f;
    vertices[ idx ].y = -glm::cos( phi )*sphereData.radius;
    vertices[ idx ].z = 0.0f;

    normals[ idx ].x = 0.0f;
    normals[ idx ].y = 1.0f;
    normals[ idx ].z = 0.0f;

    texCoords[ idx ].s = 0.5f;
    texCoords[ idx ].t = 1.0f;

    idx++;

    for(GLuint sliceNum = 0; sliceNum <= sphereData.slices; sliceNum++ ) {
        GLfloat theta = sliceStep * (GLfloat)sliceNum;

        vertices[ idx ].x = -glm::cos( theta )*glm::sin( phiNext )*sphereData.radius;
        vertices[ idx ].y = -glm::cos( phiNext )*sphereData.radius;
        vertices[ idx ].z =  glm::sin( theta )*glm::sin( phiNext )*sphereData.radius;

        normals[ idx ].x = -glm::cos( theta )*glm::sin( phiNext );
        normals[ idx ].y = -glm::cos( phiNext );
        normals[ idx ].z =  glm::sin( theta )*glm::sin( phiNext );

        texCoords[ idx ].s = (GLfloat)sliceNum / (GLfloat)sphereData.slices;
        texCoords[ idx ].t = 1.0f;

        idx++;
    }

    // sphere stacks
    for(GLuint stackNum = 1; stackNum < sphereData.stacks - 1; stackNum++ ) {
        phi = stackStep * (GLfloat)stackNum;
        phiNext = stackStep * (GLfloat)(stackNum + 1);

        for(GLuint sliceNum = sphereData.slices; sliceNum > 0; sliceNum-- ) {
            GLfloat theta = sliceStep * (GLfloat)sliceNum;

            vertices[ idx ].x = -glm::cos( theta )*glm::sin( phi )*sphereData.radius;
            vertices[ idx ].y = -glm::cos( phi )*sphereData.radius;
            vertices[ idx ].z =  glm::sin( theta )*glm::sin( phi )*sphereData.radius;

            normals[ idx ].x = -glm::cos( theta )*glm::sin( phi );
            normals[ idx ].y = -glm::cos( phi );
            normals[ idx ].z =  glm::sin( theta )*glm::sin( phi );

            texCoords[ idx ].s = (GLfloat)sliceNum / (GLfloat)sphereData.slices;
            texCoords[ idx ].t = (GLfloat)(stackNum-1) / (GLfloat)(sphereData.stacks - 2);

            idx++;

            vertices[ idx ].x = -glm::cos( theta )*glm::sin( phiNext )*sphereData.radius;
            vertices[ idx ].y = -glm::cos( phiNext )*sphereData.radius;
            vertices[ idx ].z =  glm::sin( theta )*glm::sin( phiNext )*sphereData.radius;

            normals[ idx ].x = -glm::cos( theta )*glm::sin( phiNext );
            normals[ idx ].y = -glm::cos( phiNext );
            normals[ idx ].z =  glm::sin( theta )*glm::sin( phiNext );

            texCoords[ idx ].s = (GLfloat)sliceNum / (GLfloat)sphereData.slices;
            texCoords[ idx ].t = (GLfloat)(stackNum) / (GLfloat)(sphereData.stacks - 2);

            idx++;
        }

        vertices[ idx ].x = -glm::sin( phi )*sphereData.radius;
        vertices[ idx ].y = -glm::cos( phi )*sphereData.radius;
        vertices[ idx ].z =  0.0f;

        normals[ idx ].x = -glm::sin( phi );
        normals[ idx ].y = -glm::cos( phi );
        normals[ idx ].z =  0.0f;

        texCoords[ idx ].s = 0.0f;
        texCoords[ idx ].t = (GLfloat)(stackNum-1) / (GLfloat)(sphereData.stacks - 2);

        idx++;

        vertices[ idx ].x = -glm::sin( phiNext )*sphereData.radius;
        vertices[ idx ].y = -glm::cos( phiNext )*sphereData.radius;
        vertices[ idx ].z =  0.0f;

        normals[ idx ].x = -glm::sin( phiNext );
        normals[ idx ].y = -glm::cos( phiNext );
        normals[ idx ].z =  0.0f;

        texCoords[ idx ].s = 0.0f;
        texCoords[ idx ].t = (GLfloat)(stackNum) / (GLfloat)(sphereData.stacks - 2);

        idx++;
    }

    // sphere bottom
    phi = 0;
    phiNext = stackStep;

    vertices[ idx ].x = 0.0f;
    vertices[ idx ].y = -glm::cos( phi )*sphereData.radius;
    vertices[ idx ].z = 0.0f;

    normals[ idx ].x =  0.0f;
    normals[ idx ].y = -1.0f;
    normals[ idx ].z =  0.0f;

    texCoords[ idx ].s = 0.5f;
    texCoords[ idx ].t = 0.0f;

    idx++;

    for(GLuint sliceNum = sphereData.slices; sliceNum > 0; sliceNum--) {
        GLfloat theta = sliceStep * (GLfloat)sliceNum;

        vertices[ idx ].x = -glm::cos( theta )*glm::sin( phiNext )*sphereData.radius;
        vertices[ idx ].y = -glm::cos( phiNext )*sphereData.radius;
        vertices[ idx ].z = glm::sin( theta )*glm::sin( phiNext )*sphereData.radius;

        normals[ idx ].x = -glm::cos( theta )*glm::sin( phiNext );
        normals[ idx ].y = -glm::cos( phiNext );
        normals[ idx ].z = glm::sin( theta )*glm::sin( phiNext );

        texCoords[ idx ].s = (GLfloat)sliceNum / (GLfloat)sphereData.slices;
        texCoords[ idx ].t = 0.0f;

        idx++;
    }

    vertices[ idx ].x = -glm::sin( phiNext )*sphereData.radius;
    vertices[ idx ].y = -glm::cos( phiNext )*sphereData.radius;
    vertices[ idx ].z =  0.0f;

    normals[ idx ].x = -glm::sin( phiNext );
    normals[ idx ].y = -glm::cos( phiNext );
    normals[ idx ].z =  0.0f;

    texCoords[ idx ].s = 0.0f;
    texCoords[ idx ].t = 0.0f;

    glBufferData(GL_ARRAY_BUFFER, (sizeof(glm::vec3)*2 + sizeof(glm::vec2)) * NUM_VERTICES, nullptr, GL_STATIC_DRAW );
    glBufferSubData(GL_ARRAY_BUFFER, 0, sizeof(glm::vec3) * NUM_VERTICES, vertices );
    glBufferSubData(GL_ARRAY_BUFFER, sizeof(glm::vec3) * NUM_VERTICES, sizeof(glm::vec3) * NUM_VERTICES, normals );
    glBufferSubData(GL_ARRAY_BUFFER, sizeof(glm::vec3) * NUM_VERTICES * 2, sizeof(glm::vec2) * NUM_VERTICES, texCoords );

    CSCI441_INTERNAL::_sphereVAO.insert( std::pair<SphereData, GLuint>( sphereData, vaod ) );
    CSCI441_INTERNAL::_sphereVBO.insert( std::pair<SphereData, GLuint>( sphereData, vbod ) );

    delete[] vertices;
    delete[] texCoords;
    delete[] normals;
}

inline void CSCI441_INTERNAL::generateTorusVAO( TorusData torusData ) {
    GLuint vaod;
    glGenVertexArrays( 1, &vaod );
    glBindVertexArray( vaod );

    GLuint vbod;
    glGenBuffers( 1, &vbod );
    glBindBuffer( GL_ARRAY_BUFFER, vbod );

    const GLulong NUM_VERTICES = torusData.numVertices();

    auto vertices  = new glm::vec3[NUM_VERTICES];
    auto normals   = new glm::vec3[NUM_VERTICES];
    auto texCoords = new glm::vec2[NUM_VERTICES];

    GLulong idx = 0;

    GLfloat sideStep = glm::two_pi<float>() / (GLfloat)torusData.sides;
    GLfloat ringStep = glm::two_pi<float>() / (GLfloat)torusData.rings;

    for(GLuint ringNum = 0; ringNum < torusData.rings; ringNum++ ) {
        GLfloat currTheta = ringStep * (GLfloat)ringNum;
        GLfloat nextTheta = ringStep * (GLfloat)(ringNum+1);

        for(GLuint sideNum = 0; sideNum < torusData.sides; sideNum++ ) {
            GLfloat currPhi = sideStep * (GLfloat)sideNum;
            GLfloat nextPhi = sideStep * (GLfloat)(sideNum+1);

            vertices[ idx ].x = (torusData.outerRadius + torusData.innerRadius * glm::cos(currPhi ) ) * glm::cos(currTheta );
            vertices[ idx ].y = (torusData.outerRadius + torusData.innerRadius * glm::cos(currPhi ) ) * glm::sin(currTheta );
            vertices[ idx ].z = torusData.innerRadius * glm::sin(currPhi );

            normals[ idx ].x = glm::cos( currPhi ) * glm::cos( currTheta );
            normals[ idx ].y = glm::cos( currPhi ) * glm::sin( currTheta );
            normals[ idx ].z = glm::sin( currPhi );

            texCoords[ idx ].s = (GLfloat)sideNum / (GLfloat)torusData.sides;
            texCoords[ idx ].t = (GLfloat)ringNum / (GLfloat)torusData.rings;

            idx++;

            vertices[ idx ].x = (torusData.outerRadius + torusData.innerRadius * glm::cos(currPhi ) ) * glm::cos(nextTheta );
            vertices[ idx ].y = (torusData.outerRadius + torusData.innerRadius * glm::cos(currPhi ) ) * glm::sin(nextTheta );
            vertices[ idx ].z = torusData.innerRadius * glm::sin(currPhi );

            normals[ idx ].x = glm::cos( currPhi ) * glm::cos( nextTheta );
            normals[ idx ].y = glm::cos( currPhi ) * glm::sin( nextTheta );
            normals[ idx ].z = glm::sin( currPhi );

            texCoords[ idx ].s = (GLfloat)sideNum / (GLfloat)torusData.sides;
            texCoords[ idx ].t = (GLfloat)(ringNum+1) / (GLfloat)torusData.rings;

            idx++;

            vertices[ idx ].x = (torusData.outerRadius + torusData.innerRadius * glm::cos(nextPhi ) ) * glm::cos(currTheta );
            vertices[ idx ].y = (torusData.outerRadius + torusData.innerRadius * glm::cos(nextPhi ) ) * glm::sin(currTheta );
            vertices[ idx ].z = torusData.innerRadius * glm::sin(nextPhi );

            normals[ idx ].x = glm::cos( nextPhi ) * glm::cos( currTheta );
            normals[ idx ].y = glm::cos( nextPhi ) * glm::sin( currTheta );
            normals[ idx ].z = glm::sin( nextPhi );

            texCoords[ idx ].s = (GLfloat)(sideNum+1) / (GLfloat)torusData.sides;
            texCoords[ idx ].t = (GLfloat)ringNum / (GLfloat)torusData.rings;

            idx++;

            vertices[ idx ].x = (torusData.outerRadius + torusData.innerRadius * glm::cos(nextPhi ) ) * glm::cos(nextTheta );
            vertices[ idx ].y = (torusData.outerRadius + torusData.innerRadius * glm::cos(nextPhi ) ) * glm::sin(nextTheta );
            vertices[ idx ].z = torusData.innerRadius * glm::sin(nextPhi );

            normals[ idx ].x = glm::cos( nextPhi ) * glm::cos( nextTheta );
            normals[ idx ].y = glm::cos( nextPhi ) * glm::sin( nextTheta );
            normals[ idx ].z = glm::sin( nextPhi );

            texCoords[ idx ].s = (GLfloat)(sideNum+1) / (GLfloat)torusData.sides;
            texCoords[ idx ].t = (GLfloat)(ringNum+1) / (GLfloat)torusData.rings;

            idx++;
        }
    }

    glBufferData(GL_ARRAY_BUFFER, (sizeof(glm::vec3)*2 + sizeof(glm::vec2)) * NUM_VERTICES, nullptr, GL_STATIC_DRAW );
    glBufferSubData(GL_ARRAY_BUFFER, 0, sizeof(glm::vec3) * NUM_VERTICES, vertices );
    glBufferSubData(GL_ARRAY_BUFFER, sizeof(glm::vec3) * NUM_VERTICES, sizeof(glm::vec3) * NUM_VERTICES, normals );
    glBufferSubData(GL_ARRAY_BUFFER, sizeof(glm::vec3) * NUM_VERTICES * 2, sizeof(glm::vec2) * NUM_VERTICES, texCoords );

    CSCI441_INTERNAL::_torusVAO.insert( std::pair<TorusData, GLuint>( torusData, vaod ) );
    CSCI441_INTERNAL::_torusVBO.insert( std::pair<TorusData, GLuint>( torusData, vbod ) );

    delete[] vertices;
    delete[] texCoords;
    delete[] normals;
}

#endif // __CSCI441_OBJECTS_HPP__
