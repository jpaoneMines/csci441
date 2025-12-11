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
 *	@warning NOTE: This header file depends upon GLAD (or alternatively GLEW)
 */

#ifndef CSCI441_OBJECTS_HPP
#define CSCI441_OBJECTS_HPP

#include "constants.h"
#include "objects_impl.hpp"
#include "teapot.hpp"                   // for teapot()

#ifdef CSCI441_USE_GLEW
    #include <GL/glew.h>
#else
    #include <glad/gl.h>
#endif

#include <glm/gtc/constants.hpp>

#include <cassert>   					// for assert()

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
     * @param tangentLocation location of the vertex tangent attribute
     * @note Needs to be called after a shader program is being used and before drawing geometry
     */
    void setVertexAttributeLocations( GLint positionLocation, GLint normalLocation = -1, GLint texCoordLocation = -1, GLint tangentLocation = -1 );

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
     * @brief Draws a solid open-ended cylinder
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
     * @brief Draws a wireframe open-ended cylinder
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
     * @brief Draws a solid half sphere with a bottom
     * @param radius radius of the sphere
     * @param stacks resolution of the number of steps to take along theta (rotate around Y-axis)
     * @param slices resolution of the number of steps to take along phi (rotate around X- or Z-axis)
     * @pre radius must be greater than 0
     * @pre stacks must be greater than 2
     * @pre slices must be greater than 2
     * @note Origin is at the center of the sphere
     */
    [[maybe_unused]] void drawSolidHalfSphere( GLfloat radius, GLint stacks, GLint slices );
    /**
     * @brief Draws a wireframe half sphere with a bottom
     * @param radius radius of the sphere
     * @param stacks resolution of the number of steps to take along theta (rotate around Y-axis)
     * @param slices resolution of the number of steps to take along phi (rotate around X- or Z-axis)
     * @pre radius must be greater than 0
     * @pre stacks must be greater than 2
     * @pre slices must be greater than 2
     * @note Origin is at the center of the sphere
     */
    [[maybe_unused]] void drawWireHalfSphere( GLfloat radius, GLint stacks, GLint slices );

    /**
     * @brief Draws a solid dome
     * @param radius radius of the dome
     * @param stacks resolution of the number of steps to take along theta (rotate around Y-axis)
     * @param slices resolution of the number of steps to take along phi (rotate around X- or Z-axis)
     * @pre radius must be greater than 0
     * @pre stacks must be greater than 2
     * @pre slices must be greater than 2
     * @note Origin is at the center of the dome
     */
    [[maybe_unused]] void drawSolidDome( GLfloat radius, GLint stacks, GLint slices );
    /**
     * @brief Draws a wireframe dome
     * @param radius radius of the dome
     * @param stacks resolution of the number of steps to take along theta (rotate around Y-axis)
     * @param slices resolution of the number of steps to take along phi (rotate around X- or Z-axis)
     * @pre radius must be greater than 0
     * @pre stacks must be greater than 2
     * @pre slices must be greater than 2
     * @note Origin is at the center of the dome
     */
    [[maybe_unused]] void drawWireDome( GLfloat radius, GLint stacks, GLint slices );

    /**
     * @brief Draws a solid teapot
     * @param unused present for historical compatability
     * @pre size must be greater than zero
     * @note Oriented with spout and handle running along X-axis, cap and bottom along Y-axis.  Origin is at the center of the teapot
     */
    [[maybe_unused]] void drawSolidTeapot( GLfloat unused = 0.0f );
    /**
     * @brief Draws a wireframe teapot
     * @param unused present for historical compatability
     * @pre size must be greater than zero
     * @note Oriented with spout and handle running along X-axis, cap and bottom along Y-axis.  Origin is at the center of the teapot
     */
    [[maybe_unused]] void drawWireTeapot( GLfloat unused = 0.0f );

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
// Outward facing function implementations

inline void CSCI441::setVertexAttributeLocations(
    const GLint positionLocation,
    const GLint normalLocation,
    const GLint texCoordLocation,
    const GLint tangentLocation
) {
    CSCI441_INTERNAL::_positionAttributeLocation = positionLocation;
    CSCI441_INTERNAL::_normalAttributeLocation = normalLocation;
    CSCI441_INTERNAL::_texCoordAttributeLocation = texCoordLocation;
    CSCI441_INTERNAL::_tangentAttributeLocation = tangentLocation;
    CSCI441_INTERNAL::setTeapotAttributeLocations(positionLocation, normalLocation, texCoordLocation, tangentLocation);
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
inline void CSCI441::drawSolidCone(
    const GLfloat base,
    const GLfloat height,
    const GLint stacks,
    const GLint slices
) {
    assert( base > 0.0f );
    assert( height > 0.0f );
    assert( stacks > 0 );
    assert( slices > 2 );

    CSCI441_INTERNAL::drawCylinder( base, 0.0f, height, stacks, slices, GL_FILL );
}

[[maybe_unused]]
inline void CSCI441::drawWireCone(
    const GLfloat base,
    const GLfloat height,
    const GLint stacks,
    const GLint slices
) {
    assert( base > 0.0f );
    assert( height > 0.0f );
    assert( stacks > 0 );
    assert( slices > 2 );

    CSCI441_INTERNAL::drawCylinder( base, 0.0f, height, stacks, slices, GL_LINE );
}

[[maybe_unused]]
inline void CSCI441::drawSolidCube(
    const GLfloat sideLength
) {
    drawSolidCubeIndexed(sideLength);
}

[[maybe_unused]]
inline void CSCI441::drawSolidCubeTextured(
    const GLfloat sideLength
) {
    drawSolidCubeFlat(sideLength);
}

inline void CSCI441::drawSolidCubeIndexed(
    const GLfloat sideLength
) {
    assert( sideLength > 0.0f );

    CSCI441_INTERNAL::drawCube( sideLength, GL_FILL );
}

inline void CSCI441::drawSolidCubeFlat(
    const GLfloat sideLength
) {
    assert( sideLength > 0.0f );

    CSCI441_INTERNAL::drawCubeFlat( sideLength, GL_FILL );
}

[[maybe_unused]]
inline void CSCI441::drawWireCube(
    const GLfloat sideLength
) {
    assert( sideLength > 0.0f );

    CSCI441_INTERNAL::drawCube( sideLength, GL_LINE );
}

[[maybe_unused]]
inline void CSCI441::drawCubeMap(
    const GLfloat sideLength
) {
    assert(sideLength > 0.0f);

    CSCI441_INTERNAL::drawCube( sideLength, GL_FILL );
}

[[maybe_unused]]
inline void CSCI441::drawSolidCylinder(
    const GLfloat base,
    const GLfloat top,
    const GLfloat height,
    const GLint stacks,
    const GLint slices
) {
    assert( (base >= 0.0f && top > 0.0f) || (base > 0.0f && top >= 0.0f) );
    assert( height > 0.0f );
    assert( stacks > 0 );
    assert( slices > 2 );

    CSCI441_INTERNAL::drawCylinder( base, top, height, stacks, slices, GL_FILL );
}

[[maybe_unused]]
inline void CSCI441::drawWireCylinder(
    const GLfloat base,
    const GLfloat top,
    const GLfloat height,
    const GLint stacks,
    const GLint slices
) {
    assert( (base >= 0.0f && top > 0.0f) || (base > 0.0f && top >= 0.0f) );
    assert( height > 0.0f );
    assert( stacks > 0 );
    assert( slices > 2 );

    CSCI441_INTERNAL::drawCylinder( base, top, height, stacks, slices, GL_LINE );
}

[[maybe_unused]]
inline void CSCI441::drawSolidDisk(
    const GLfloat inner,
    const GLfloat outer,
    const GLint slices,
    const GLint rings
) {
    assert( inner >= 0.0f );
    assert( outer > 0.0f );
    assert( outer > inner );
    assert( slices > 2 );
    assert( rings > 0 );

    CSCI441_INTERNAL::drawPartialDisk( inner, outer, slices, rings, 0, glm::two_pi<GLfloat>(), GL_FILL );
}

[[maybe_unused]]
inline void CSCI441::drawWireDisk(
    const GLfloat inner,
    const GLfloat outer,
    const GLint slices,
    const GLint rings
) {
    assert( inner >= 0.0f );
    assert( outer > 0.0f );
    assert( outer > inner );
    assert( slices > 2 );
    assert( rings > 0 );

    CSCI441_INTERNAL::drawPartialDisk( inner, outer, slices, rings, 0, glm::two_pi<GLfloat>(), GL_LINE );
}

[[maybe_unused]]
inline void CSCI441::drawSolidPartialDisk(
    const GLfloat inner,
    const GLfloat outer,
    const GLint slices,
    const GLint rings,
    const GLfloat start,
    const GLfloat sweep
) {
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
inline void CSCI441::drawWirePartialDisk(
    const GLfloat inner,
    const GLfloat outer,
    const GLint slices,
    const GLint rings,
    const GLfloat start,
    const GLfloat sweep
) {
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
inline void CSCI441::drawSolidSphere(
    const GLfloat radius,
    const GLint stacks,
    const GLint slices
) {
    assert( radius > 0.0f );
    assert( stacks > 1 );
    assert( slices > 2 );

    CSCI441_INTERNAL::drawSphere( radius, stacks, slices, GL_FILL );
}

[[maybe_unused]]
inline void CSCI441::drawWireSphere(
    const GLfloat radius,
    const GLint stacks,
    const GLint slices
) {
    assert( radius > 0.0f );
    assert( stacks > 1);
    assert( slices > 2 );

    CSCI441_INTERNAL::drawSphere( radius, stacks, slices, GL_LINE );
}

[[maybe_unused]]
inline void CSCI441::drawSolidHalfSphere(
    const GLfloat radius,
    const GLint stacks,
    const GLint slices
) {
    assert( radius > 0.0f );
    assert( stacks > 1 );
    assert( slices > 2 );

    CSCI441_INTERNAL::drawHalfSphere( radius, stacks, slices, GL_FILL );
}

[[maybe_unused]]
inline void CSCI441::drawWireHalfSphere(
    const GLfloat radius,
    const GLint stacks,
    const GLint slices
) {
    assert( radius > 0.0f );
    assert( stacks > 1);
    assert( slices > 2 );

    CSCI441_INTERNAL::drawHalfSphere( radius, stacks, slices, GL_LINE );
}

[[maybe_unused]]
inline void CSCI441::drawSolidDome(
    const GLfloat radius,
    const GLint stacks,
    const GLint slices
) {
    assert( radius > 0.0f );
    assert( stacks > 1 );
    assert( slices > 2 );

    CSCI441_INTERNAL::drawDome( radius, stacks, slices, GL_FILL );
}

[[maybe_unused]]
inline void CSCI441::drawWireDome(
    const GLfloat radius,
    const GLint stacks,
    const GLint slices
) {
    assert( radius > 0.0f );
    assert( stacks > 1);
    assert( slices > 2 );

    CSCI441_INTERNAL::drawDome( radius, stacks, slices, GL_LINE );
}

[[maybe_unused]]
inline void CSCI441::drawSolidTeapot(
    [[maybe_unused]] const GLfloat unused
) {
    CSCI441_INTERNAL::drawTeapot(GL_FILL);
}

[[maybe_unused]]
inline void CSCI441::drawWireTeapot(
    [[maybe_unused]] const GLfloat unused
) {
    CSCI441_INTERNAL::drawTeapot(GL_LINE);
}

[[maybe_unused]]
inline void CSCI441::drawSolidTorus(
    const GLfloat innerRadius,
    const GLfloat outerRadius,
    const GLint sides,
    const GLint rings
) {
    assert( innerRadius > 0.0f );
    assert( outerRadius > 0.0f );
    assert( sides > 2 );
    assert( rings > 2 );

    CSCI441_INTERNAL::drawTorus( innerRadius, outerRadius, sides, rings, GL_FILL );
}

[[maybe_unused]]
inline void CSCI441::drawWireTorus(
    const GLfloat innerRadius,
    const GLfloat outerRadius,
    const GLint sides,
    const GLint rings
) {
    assert( innerRadius > 0.0f );
    assert( outerRadius > 0.0f );
    assert( sides > 2 );
    assert( rings > 2 );

    CSCI441_INTERNAL::drawTorus( innerRadius, outerRadius, sides, rings, GL_LINE );
}

#endif // __CSCI441_OBJECTS_HPP__
