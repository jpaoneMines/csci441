/** @file objects.hpp
 * @brief Helper functions to draw 3D OpenGL 3.0+ objects
 * @author Dr. Jeffrey Paone
 * @date Last Edit: 02 Oct 2020
 * @version 2.0
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

#ifndef __CSCI441_OBJECTS_HPP__
#define __CSCI441_OBJECTS_HPP__

#include <GL/glew.h>

#include <assert.h>   					// for assert()
#include <math.h>						// for cos(), sin()

#include "teapot.hpp"                   // for teapot()

#include <map>							// for map

////////////////////////////////////////////////////////////////////////////////////

/** @namespace CSCI441
 * @brief CSCI441 Helper Functions for OpenGL
 */
namespace CSCI441 {
    /**	@brief Sets the attribute locations for vertex positions, normals, and texture coordinates
        *
        *	Needs to be called after a shader program is being used and before drawing geometry
        *
        * @param GLint positionLocation	- location of the vertex position attribute
        * @param GLint normalLocation		- location of the vertex normal attribute
        * @param GLint texCoordLocation	- location of the vertex texture coordinate attribute
        */
    void setVertexAttributeLocations( GLint positionLocation, GLint normalLocation = -1, GLint texCoordLocation = -1 );

    /** @brief deletes the VAOs stored for all object types
     *
     */
    void deleteObjectVAOs();

    /** @brief deletes the VBOs stored for all object types
     *
     */
    void deleteObjectVBOs();

    /**	@brief Draws a solid cone
      *
        *	Cone is oriented along the y-axis with the origin along the base of the cone
        *
        * @param GLfloat base		- radius of the base of the cone
        * @param GLfloat height	- height of the cone from the base to the tip
        * @param GLint stacks			- resolution of the number of steps rotated around the central axis of the cone
        * @param GLint slices			- resolution of the number of steps to take along the height
        * @pre base must be greater than zero
        * @pre height must be greater than zero
        * @pre stacks must be greater than zero
        * @pre slices must be greater than two
      */
    void drawSolidCone( GLfloat base, GLfloat height, GLint stacks, GLint slices );
    /**	@brief Draws a wireframe cone
      *
        *	Cone is oriented along the y-axis with the origin along the base of the cone
        *
        * @param GLfloat base		- radius of the base of the cone
        * @param GLfloat height	- height of the cone from the base to the tip
        * @param GLint stacks			- resolution of the number of steps rotated around the central axis of the cone
        * @param GLint slices			- resolution of the number of steps to take along the height
        * @pre base must be greater than zero
        * @pre height must be greater than zero
        * @pre stacks must be greater than zero
        * @pre slices must be greater than two
      */
    void drawWireCone( GLfloat base, GLfloat height, GLint stacks, GLint slices );

    /** @brief Calls through to drawSolidCubeIndexed()
        *
        * @param GLfloat sideLength - length of the edge of the cube
        * @pre sideLength must be greater than zero
        */
    void drawSolidCube( GLfloat sideLength );
    /** @brief Draws a solid cube with normals aligned with cube face
  *
    *	The origin is at the cube's center of mass.  Cube is oriented with our XYZ axes
    *
    * @param GLfloat sideLength - length of the edge of the cube
    * @pre sideLength must be greater than zero
    */
    void drawSolidCubeFlat( GLfloat sideLength );
    /** @brief Draws a solid cube
		  *
			*	The origin is at the cube's center of mass.  Cube is oriented with our XYZ axes
			*
			* @param GLfloat sideLength - length of the edge of the cube
			* @pre sideLength must be greater than zero
			*/
    void drawSolidCubeIndexed( GLfloat sideLength );
    /** @brief Draws a solid textured cube.  Calls through to drawSolidCubeFlat()
		  *
			*	The origin is at the cube's center of mass.  Cube is oriented with our XYZ axes
			*
			* @param GLfloat sideLength - length of the edge of the cube
			* @pre sideLength must be greater than zero
			*/
    void drawSolidCubeTextured( GLfloat sideLength );
    /** @brief Draws a wireframe cube
      *
        *	The origin is at the cube's center of mass.  Cube is oriented with our XYZ axes
        *
        * @param GLfloat sideLength - length of the edge of the cube
        * @pre sideLength must be greater than zero
        */
    void drawWireCube( GLfloat sideLength );

    /**	@brief Draws a solid open ended cylinder
      *
        *	Cylinder is oriented along the y-axis with the origin along the base
        *
        * @param GLfloat base		- radius of the base of the cylinder
        * @param GLfloat top			- radius of the top of the cylinder
        * @param GLfloat height	- height of the cylinder from the base to the top
        * @param GLint stacks			- resolution of the number of steps rotated around the central axis of the cylinder
        * @param GLint slices			- resolution of the number of steps to take along the height
        * @pre either: (1) base is greater than zero and top is greater than or equal to zero or (2) base is greater than or equal to zero and top is greater than zero
        * @pre height must be greater than zero
        * @pre stacks must be greater than zero
        * @pre slices must be greater than two
      */
    void drawSolidCylinder( GLfloat base, GLfloat top, GLfloat height, GLint stacks, GLint slices );
    /**	@brief Draws a wireframe open ended cylinder
      *
        *	Cylinder is oriented along the y-axis with the origin along the base
        *
        * @param GLfloat base		- radius of the base of the cylinder
        * @param GLfloat top			- radius of the top of the cylinder
        * @param GLfloat height	- height of the cylinder from the base to the top
        * @param GLint stacks			- resolution of the number of steps rotated around the central axis of the cylinder
        * @param GLint slices			- resolution of the number of steps to take along the height
        * @pre either: (1) base is greater than zero and top is greater than or equal to zero or (2) base is greater than or equal to zero and top is greater than zero
        * @pre height must be greater than zero
        * @pre stacks must be greater than zero
        * @pre slices must be greater than two
      */
    void drawWireCylinder( GLfloat base, GLfloat top, GLfloat height, GLint stacks, GLint slices );

    /** @brief Draws a solid disk
      *
        *	Disk is drawn in the XY plane with the origin at its center
        *
        *	@param GLfloat inner		- equivalent to the width of the disk
        *	@param GLfloat outer		- radius from the center of the disk to the center of the ring
        * @param GLint slices			- resolution of the number of steps rotated along the disk
        * @param GLint rings			- resolution of the number of steps to take along the disk width
        * @pre inner is greater than or equal to zero
        * @pre outer is greater than zero
        * @pre outer is greater than inner
        * @pre slices is greater than two
        * @pre rings is greater than zero
        */
    void drawSolidDisk( GLfloat inner, GLfloat outer, GLint slices, GLint rings );
    /** @brief Draws a wireframe disk
      *
        *	Disk is drawn in the XY plane with the origin at its center
        *
        *	@param GLfloat inner		- equivalent to the width of the disk
        *	@param GLfloat outer		- radius from the center of the disk to the center of the ring
        * @param GLint slices			- resolution of the number of steps rotated along the disk
        * @param GLint rings			- resolution of the number of steps to take along the disk width
        * @pre inner is greater than or equal to zero
        * @pre outer is greater than zero
        * @pre outer is greater than inner
        * @pre slices is greater than two
        * @pre rings is greater than zero
        */
    void drawWireDisk( GLfloat inner, GLfloat outer, GLint slices, GLint rings );

    /** @brief Draws part of a solid disk
      *
        *	Disk is drawn in the XY plane with the origin at its center
        *
        *	@param GLfloat inner		- equivalent to the width of the disk
        *	@param GLfloat outer		- radius from the center of the disk to the center of the ring
        * @param GLint stacks			- resolution of the number of steps rotated along the disk
        * @param GLint rings			- resolution of the number of steps to take along the disk width
        *	@param GLfloat start		- angle in degrees to start the disk at
        *	@param GLfloat sweep		- distance in degrees to rotate through
        * @pre inner is greater than or equal to zero
        * @pre outer is greater than zero
        * @pre outer is greater than inner
        * @pre slices is greater than two
        * @pre rings is greater than zero
        * @pre start is between [0, 360]
        * @pre sweep is between [0, 360]
        */
    void drawSolidPartialDisk( GLfloat inner, GLfloat outer, GLint slices, GLint rings, GLfloat start, GLfloat sweep );
    /** @brief Draws part of a wireframe disk
      *
        *	Disk is drawn in the XY plane with the origin at its center
        *
        *	@param GLfloat inner		- equivalent to the width of the disk
        *	@param GLfloat outer		- radius from the center of the disk to the center of the ring
        * @param GLint stacks			- resolution of the number of steps rotated along the disk
        * @param GLint rings			- resolution of the number of steps to take along the disk width
        *	@param GLfloat start		- angle in degrees to start the disk at
        *	@param GLfloat sweep		- distance in degrees to rotate through
        * @pre inner is greater than or equal to zero
        * @pre outer is greater than zero
        * @pre outer is greater than inner
        * @pre slices is greater than two
        * @pre rings is greater than zero
        * @pre start is between [0, 360]
        * @pre sweep is between [0, 360]
        */
    void drawWirePartialDisk( GLfloat inner, GLfloat outer, GLint slices, GLint rings, GLfloat start, GLfloat sweep );

    /** @brief Draws a solid sphere
      *
        *	Origin is at the center of the sphere
        *
        *	@param GLfloat radius	- radius of the sphere
        * @param GLint stacks			- resolution of the number of steps to take along theta (rotate around Y-axis)
        * @param GLint slices			- resolution of the number of steps to take along phi (rotate around X- or Z-axis)
        *	@pre radius must be greater than 0
        * @pre stacks must be greater than 2
        * @pre slices must be greater than 2
        */
    void drawSolidSphere( GLfloat radius, GLint stacks, GLint slices );
    /** @brief Draws a wireframe sphere
      *
        *	Origin is at the center of the sphere
        *
        *	@param GLfloat radius	- radius of the sphere
        * @param GLint stacks			- resolution of the number of steps to take along theta (rotate around Y-axis)
        * @param GLint slices			- resolution of the number of steps to take along phi (rotate around X- or Z-axis)
        *	@pre radius must be greater than 0
        * @pre stacks must be greater than 2
        * @pre slices must be greater than 2
        */
    void drawWireSphere( GLfloat radius, GLint stacks, GLint slices );

    /** @brief Draws a solid teapot
      *
        *	Oriented with spout and handle running along X-axis, cap and bottom along Y-axis.  Origin is at the
        *	center of the teapot
        *
        *	@param GLfloat size	- scale of the teapot
        *	@pre size must be greater than zero
        */
    void drawSolidTeapot( GLfloat size );
    /** @brief Draws a wireframe teapot
      *
        *	Oriented with spout and handle running along X-axis, cap and bottom along Y-axis.  Origin is at the
        *	center of the teapot
        *
        *	@param GLfloat size	- scale of the teapot
        *	@pre size must be greater than zero
        */
    void drawWireTeapot( GLfloat size );

    /** @brief Draws a solid torus
      *
        * Torus is oriented in the XY-plane with the origin at its center
        *
        * @param innerRadius 	- equivalent to the width of the torus ring
        * @param outerRadius	- radius from the center of the torus to the center of the ring
        * @param sides				- resolution of steps to take around the band of the ring
        * @param rings				- resolution of steps to take around the torus
        * @pre innerRadius must be greater than zero
        * @pre outerRadius must be greater than zero
        * @pre sides must be greater than two
        * @pre rings must be greater than two
        */
    void drawSolidTorus( GLfloat innerRadius, GLfloat outerRadius, GLint sides, GLint rings );
    /** @brief Draws a wireframe torus
      *
        * Torus is oriented in the XY-plane with the origin at its center
        *
        * @param innerRadius 	- equivalent to the width of the torus ring
        * @param outerRadius	- radius from the center of the torus to the center of the ring
        * @param sides				- resolution of steps to take around the band of the ring
        * @param rings				- resolution of steps to take around the torus
        * @pre innerRadius must be greater than zero
        * @pre outerRadius must be greater than zero
        * @pre sides must be greater than two
        * @pre rings must be greater than two
        */
    void drawWireTorus( GLfloat innerRadius, GLfloat outerRadius, GLint sides, GLint rings );
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
    void drawCylinder( GLfloat base, GLfloat top, GLfloat height, GLint stacks, GLint slices, GLenum renderMode );
    void drawPartialDisk( GLfloat inner, GLfloat outer, GLint slices, GLint rings, GLfloat start, GLfloat sweep, GLenum renderMode );
    void drawSphere( GLfloat radius, GLint stacks, GLint slices, GLenum renderMode );
    void drawTorus( GLfloat innerRadius, GLfloat outerRadius, GLint sides, GLint rings, GLenum renderMode );

    static GLint _positionLocation = -1;
    static GLint _normalLocation = -1;
    static GLint _texCoordLocation = -1;

    void generateCubeVAOFlat( GLfloat sideLength );
    void generateCubeVAOIndexed( GLfloat sideLength );
    static std::map< GLfloat, GLuint > _cubeVAO;
    static std::map< GLfloat, GLuint > _cubeVBO;
    static std::map< GLfloat, GLuint > _cubeVAOIndexed;
    static std::map< GLfloat, GLuint > _cubeVBOIndexed;

    struct CylinderData {
        GLfloat b, t, h;
        GLint st, sl;
        bool operator<( const CylinderData rhs ) const {
            bool result = b < rhs.b;
            if( !result ) result = t < rhs.t;
            if( !result ) result = h < rhs.h;
            if( !result ) result = st < rhs.st;
            if( !result ) result = sl < rhs.sl;
            return result;
        }
    };
    void generateCylinderVAO( CylinderData cylData );
    static std::map< CylinderData, GLuint > _cylinderVAO;
    static std::map< CylinderData, GLuint > _cylinderVBO;

    struct DiskData {
        GLfloat i, o, st, sw;
        GLint sl, r;
        bool operator<( const DiskData rhs ) const {
            bool result = i < rhs.i;
            if( !result ) result = o < rhs.o;
            if( !result ) result = sl < rhs.sl;
            if( !result ) result = r < rhs.r;
            if( !result ) result = st < rhs.st;
            if( !result ) result = sw < rhs.sw;
            return result;
        }
    };
    void generateDiskVAO( DiskData diskData );
    static std::map< DiskData, GLuint > _diskVAO;
    static std::map< DiskData, GLuint > _diskVBO;

    struct SphereData {
        GLfloat r;
        GLint st, sl;
        bool operator<( const SphereData rhs ) const {
            bool result = r < rhs.r;
            if( !result ) result = st < rhs.st;
            if( !result ) result = sl < rhs.sl;
            return result;
        }
    };
    void generateSphereVAO( SphereData sphereData );
    static std::map< SphereData, GLuint > _sphereVAO;
    static std::map< SphereData, GLuint > _sphereVBO;

    struct TorusData {
        GLfloat i, o;
        GLint s, r;
        bool operator<( const TorusData rhs ) const {
            bool result = i < rhs.i;
            if( !result ) result = o < rhs.o;
            if( !result ) result = s < rhs.s;
            if( !result ) result = r < rhs.r;
            return result;
        }
    };
    void generateTorusVAO( TorusData torusData );
    static std::map< TorusData, GLuint > _torusVAO;
    static std::map< TorusData, GLuint > _torusVBO;
}

////////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////
// Outward facing function implementations

inline void CSCI441::setVertexAttributeLocations( GLint positionLocation, GLint normalLocation, GLint texCoordLocation ) {
    CSCI441_INTERNAL::_positionLocation = positionLocation;
    CSCI441_INTERNAL::_normalLocation = normalLocation;
    CSCI441_INTERNAL::_texCoordLocation = texCoordLocation;
}

inline void CSCI441::deleteObjectVAOs() {
    CSCI441_INTERNAL::deleteObjectVAOs();
}

inline void CSCI441::deleteObjectVBOs() {
    CSCI441_INTERNAL::deleteObjectVBOs();
}

inline void CSCI441::drawSolidCone( GLfloat base, GLfloat height, GLint stacks, GLint slices ) {
    assert( base > 0.0f );
    assert( height > 0.0f );
    assert( stacks > 0 );
    assert( slices > 2 );

    CSCI441_INTERNAL::drawCylinder( base, 0.0f, height, stacks, slices, GL_FILL );
}

inline void CSCI441::drawWireCone( GLfloat base, GLfloat height, GLint stacks, GLint slices ) {
    assert( base > 0.0f );
    assert( height > 0.0f );
    assert( stacks > 0 );
    assert( slices > 2 );

    CSCI441_INTERNAL::drawCylinder( base, 0.0f, height, stacks, slices, GL_LINE );
}

inline void CSCI441::drawSolidCube( GLfloat sideLength ) {
    drawSolidCubeIndexed(sideLength);
}

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

inline void CSCI441::drawWireCube( GLfloat sideLength ) {
    assert( sideLength > 0.0f );

    CSCI441_INTERNAL::drawCube( sideLength, GL_LINE );
}

inline void CSCI441::drawSolidCylinder( GLfloat base, GLfloat top, GLfloat height, GLint stacks, GLint slices ) {
    assert( (base >= 0.0f && top > 0.0f) || (base > 0.0f && top >= 0.0f) );
    assert( height > 0.0f );
    assert( stacks > 0 );
    assert( slices > 2 );

    CSCI441_INTERNAL::drawCylinder( base, top, height, stacks, slices, GL_FILL );
}

inline void CSCI441::drawWireCylinder( GLfloat base, GLfloat top, GLfloat height, GLint stacks, GLint slices ) {
    assert( (base >= 0.0f && top > 0.0f) || (base > 0.0f && top >= 0.0f) );
    assert( height > 0.0f );
    assert( stacks > 0 );
    assert( slices > 2 );

    CSCI441_INTERNAL::drawCylinder( base, top, height, stacks, slices, GL_LINE );
}

inline void CSCI441::drawSolidDisk( GLfloat inner, GLfloat outer, GLint slices, GLint rings ) {
    assert( inner >= 0.0f );
    assert( outer > 0.0f );
    assert( outer > inner );
    assert( slices > 2 );
    assert( rings > 0 );

    CSCI441_INTERNAL::drawPartialDisk( inner, outer, slices, rings, 0, 2*M_PI, GL_FILL );
}

inline void CSCI441::drawWireDisk( GLfloat inner, GLfloat outer, GLint slices, GLint rings ) {
    assert( inner >= 0.0f );
    assert( outer > 0.0f );
    assert( outer > inner );
    assert( slices > 2 );
    assert( rings > 0 );

    CSCI441_INTERNAL::drawPartialDisk( inner, outer, slices, rings, 0, 2*M_PI, GL_LINE );
}

inline void CSCI441::drawSolidPartialDisk( GLfloat inner, GLfloat outer, GLint slices, GLint rings, GLfloat start, GLfloat sweep ) {
    assert( inner >= 0.0f );
    assert( outer > 0.0f );
    assert( outer > inner );
    assert( slices > 2 );
    assert( rings > 0 );
    assert( start >= 0.0f && start <= 360.0f );
    assert( sweep >= 0.0f && sweep <= 360.0f );

    CSCI441_INTERNAL::drawPartialDisk( inner, outer, slices, rings, start * M_PI / 180.0f, sweep * M_PI / 180.0f, GL_FILL );
}

inline void CSCI441::drawWirePartialDisk( GLfloat inner, GLfloat outer, GLint slices, GLint rings, GLfloat start, GLfloat sweep ) {
    assert( inner >= 0.0f );
    assert( outer > 0.0f );
    assert( outer > inner );
    assert( slices > 2 );
    assert( rings > 0 );
    assert( start >= 0.0f && start <= 360.0f );
    assert( sweep >= 0.0f && sweep <= 360.0f );

    CSCI441_INTERNAL::drawPartialDisk( inner, outer, slices, rings, start * M_PI / 180.0f, sweep * M_PI / 180.0f, GL_LINE );
}

inline void CSCI441::drawSolidSphere( GLfloat radius, GLint stacks, GLint slices ) {
    assert( radius > 0.0f );
    assert( stacks > 1 );
    assert( slices > 2 );

    CSCI441_INTERNAL::drawSphere( radius, stacks, slices, GL_FILL );
}

inline void CSCI441::drawWireSphere( GLfloat radius, GLint stacks, GLint slices ) {
    assert( radius > 0.0f );
    assert( stacks > 1);
    assert( slices > 2 );

    CSCI441_INTERNAL::drawSphere( radius, stacks, slices, GL_LINE );
}

inline void CSCI441::drawSolidTeapot( GLfloat size ) {
    assert( size > 0.0f );

    CSCI441_INTERNAL::teapot( size, CSCI441_INTERNAL::_positionLocation, CSCI441_INTERNAL::_normalLocation );
}

inline void CSCI441::drawWireTeapot( GLfloat size ) {
    assert( size > 0.0f );

    glPolygonMode( GL_FRONT_AND_BACK, GL_LINE );
    CSCI441_INTERNAL::teapot( size, CSCI441_INTERNAL::_positionLocation, CSCI441_INTERNAL::_normalLocation );
    glPolygonMode( GL_FRONT_AND_BACK, GL_FILL );
}

inline void CSCI441::drawSolidTorus( GLfloat innerRadius, GLfloat outerRadius, GLint sides, GLint rings ) {
    assert( innerRadius > 0.0f );
    assert( outerRadius > 0.0f );
    assert( sides > 2 );
    assert( rings > 2 );

    CSCI441_INTERNAL::drawTorus( innerRadius, outerRadius, sides, rings, GL_FILL );
}

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
    for(std::map<GLfloat, GLuint>::iterator iter = _cubeVAO.begin(); iter != _cubeVAO.end(); iter++) {
        glDeleteBuffers(1, &(iter->second));
    }
    for(std::map<GLfloat, GLuint>::iterator iter = _cubeVAOIndexed.begin(); iter != _cubeVAOIndexed.end(); iter++) {
        glDeleteBuffers(1, &(iter->second));
    }
    for(std::map<CylinderData, GLuint>::iterator iter = _cylinderVAO.begin(); iter != _cylinderVAO.end(); iter++) {
        glDeleteBuffers(1, &(iter->second));
    }
    for(std::map<DiskData, GLuint>::iterator iter = _diskVAO.begin(); iter != _diskVAO.end(); iter++) {
        glDeleteBuffers(1, &(iter->second));
    }
    for(std::map<SphereData, GLuint>::iterator iter = _sphereVAO.begin(); iter != _sphereVAO.end(); iter++) {
        glDeleteBuffers(1, &(iter->second));
    }
    for(std::map<TorusData, GLuint>::iterator iter = _torusVAO.begin(); iter != _torusVAO.end(); iter++) {
        glDeleteBuffers(1, &(iter->second));
    }
}

inline void CSCI441_INTERNAL::deleteObjectVBOs() {
    for(std::map<GLfloat, GLuint>::iterator iter = _cubeVBO.begin(); iter != _cubeVBO.end(); iter++) {
        glDeleteBuffers(1, &(iter->second));
    }
    for(std::map<GLfloat, GLuint>::iterator iter = _cubeVBOIndexed.begin(); iter != _cubeVBOIndexed.end(); iter++) {
        glDeleteBuffers(1, &(iter->second));
    }
    for(std::map<CylinderData, GLuint>::iterator iter = _cylinderVBO.begin(); iter != _cylinderVBO.end(); iter++) {
        glDeleteBuffers(1, &(iter->second));
    }
    for(std::map<DiskData, GLuint>::iterator iter = _diskVBO.begin(); iter != _diskVBO.end(); iter++) {
        glDeleteBuffers(1, &(iter->second));
    }
    for(std::map<SphereData, GLuint>::iterator iter = _sphereVBO.begin(); iter != _sphereVBO.end(); iter++) {
        glDeleteBuffers(1, &(iter->second));
    }
    for(std::map<TorusData, GLuint>::iterator iter = _torusVBO.begin(); iter != _torusVBO.end(); iter++) {
        glDeleteBuffers(1, &(iter->second));
    }
}

inline void CSCI441_INTERNAL::drawCube( GLfloat sideLength, GLenum renderMode ) {
    drawCubeIndexed(sideLength, renderMode);
}

inline void CSCI441_INTERNAL::drawCubeFlat( GLfloat sideLength, GLenum renderMode ) {
    if( CSCI441_INTERNAL::_cubeVAO.count( sideLength ) == 0 ) {
        CSCI441_INTERNAL::generateCubeVAOFlat( sideLength );
    }

    glPolygonMode( GL_FRONT_AND_BACK, renderMode );
    glBindVertexArray( CSCI441_INTERNAL::_cubeVAO.find( sideLength )->second );
    glBindBuffer( GL_ARRAY_BUFFER, CSCI441_INTERNAL::_cubeVBO.find( sideLength )->second );
    glEnableVertexAttribArray( _positionLocation );
    glVertexAttribPointer( _positionLocation, 3, GL_FLOAT, GL_FALSE, 0, (void*)0 );
    glEnableVertexAttribArray( _normalLocation );
    glVertexAttribPointer( _normalLocation, 3, GL_FLOAT, GL_FALSE, 0, (void*)(sizeof(GLfloat)*36*3) );
    glEnableVertexAttribArray( _texCoordLocation );
    glVertexAttribPointer( _texCoordLocation, 2, GL_FLOAT, GL_FALSE, 0, (void*)(sizeof(GLfloat)*36*6) );
    glDrawArrays( GL_TRIANGLES, 0, 36 );

    glPolygonMode( GL_FRONT_AND_BACK, GL_FILL );
}

inline void CSCI441_INTERNAL::drawCubeIndexed( GLfloat sideLength, GLenum renderMode ) {
    if( CSCI441_INTERNAL::_cubeVAOIndexed.count( sideLength ) == 0 ) {
        CSCI441_INTERNAL::generateCubeVAOIndexed( sideLength );
    }

    glPolygonMode( GL_FRONT_AND_BACK, renderMode );
    glBindVertexArray( CSCI441_INTERNAL::_cubeVAOIndexed.find( sideLength )->second );
    glBindBuffer( GL_ARRAY_BUFFER, CSCI441_INTERNAL::_cubeVBOIndexed.find( sideLength )->second );
    glEnableVertexAttribArray( _positionLocation );
    glVertexAttribPointer( _positionLocation, 3, GL_FLOAT, GL_FALSE, 0, (void*)0 );
    glEnableVertexAttribArray( _normalLocation );
    glVertexAttribPointer( _normalLocation, 3, GL_FLOAT, GL_FALSE, 0, (void*)(sizeof(GLfloat)*8*3) );
    glDrawElements( GL_TRIANGLES, 36, GL_UNSIGNED_SHORT, (void*)0 );

    glPolygonMode( GL_FRONT_AND_BACK, GL_FILL );
}

inline void CSCI441_INTERNAL::drawCylinder( GLfloat base, GLfloat top, GLfloat height, GLint stacks, GLint slices, GLenum renderMode ) {
    CylinderData cylData = { base, top, height, stacks, slices };
    if( CSCI441_INTERNAL::_cylinderVAO.count( cylData ) == 0 ) {
        CSCI441_INTERNAL::generateCylinderVAO( cylData );
    }

    glPolygonMode( GL_FRONT_AND_BACK, renderMode );
    glBindVertexArray( CSCI441_INTERNAL::_cylinderVAO.find( cylData )->second );
    glBindBuffer( GL_ARRAY_BUFFER, CSCI441_INTERNAL::_cylinderVBO.find( cylData )->second );
    glEnableVertexAttribArray( _positionLocation );
    glVertexAttribPointer( _positionLocation, 3, GL_FLOAT, GL_FALSE, 0, (void*)0 );
    glEnableVertexAttribArray( _normalLocation );
    glVertexAttribPointer( _normalLocation, 3, GL_FLOAT, GL_FALSE, 0, (void*)(sizeof(GLfloat)*stacks * (slices+1) * 2*3) );
    glEnableVertexAttribArray( _texCoordLocation );
    glVertexAttribPointer( _texCoordLocation, 2, GL_FLOAT, GL_FALSE, 0, (void*)(sizeof(GLfloat)*stacks * (slices+1) * 2*6) );

    for( int stackNum = 0; stackNum < stacks; stackNum++ ) {
        glDrawArrays( GL_TRIANGLE_STRIP, (slices+1)*2*stackNum, (slices+1)*2 );
    }

    glPolygonMode( GL_FRONT_AND_BACK, GL_FILL );
}

inline void CSCI441_INTERNAL::drawPartialDisk( GLfloat inner, GLfloat outer, GLint slices, GLint rings, GLfloat start, GLfloat sweep, GLenum renderMode ) {
    DiskData diskData = { inner, outer, start, sweep, slices, rings };
    if( CSCI441_INTERNAL::_diskVAO.count( diskData ) == 0 ) {
        CSCI441_INTERNAL::generateDiskVAO( diskData );
    }

    glPolygonMode( GL_FRONT_AND_BACK, renderMode );
    glBindVertexArray( CSCI441_INTERNAL::_diskVAO.find( diskData )->second );
    glBindBuffer( GL_ARRAY_BUFFER, CSCI441_INTERNAL::_diskVBO.find( diskData )->second );
    glEnableVertexAttribArray( _positionLocation );
    glVertexAttribPointer( _positionLocation, 3, GL_FLOAT, GL_FALSE, 0, (void*)0 );
    glEnableVertexAttribArray( _normalLocation );
    glVertexAttribPointer( _normalLocation, 3, GL_FLOAT, GL_FALSE, 0, (void*)(sizeof(GLfloat)*rings * (slices+1) * 2*3) );
    glEnableVertexAttribArray( _texCoordLocation );
    glVertexAttribPointer( _texCoordLocation, 2, GL_FLOAT, GL_FALSE, 0, (void*)(sizeof(GLfloat)*rings * (slices+1) * 2*6) );

    for( int ringNum = 0; ringNum < rings; ringNum++ ) {
        glDrawArrays( GL_TRIANGLE_STRIP, (slices+1)*2*ringNum, (slices+1)*2 );
    }

    glPolygonMode( GL_FRONT_AND_BACK, GL_FILL );
}

inline void CSCI441_INTERNAL::drawSphere( GLfloat radius, GLint stacks, GLint slices, GLenum renderMode ) {
    SphereData sphereData = { radius, stacks, slices };
    if( CSCI441_INTERNAL::_sphereVAO.count( sphereData ) == 0 ) {
        CSCI441_INTERNAL::generateSphereVAO( sphereData );
    }

    glPolygonMode( GL_FRONT_AND_BACK, renderMode );
    glBindVertexArray( CSCI441_INTERNAL::_sphereVAO.find( sphereData )->second );
    glBindBuffer( GL_ARRAY_BUFFER, CSCI441_INTERNAL::_sphereVBO.find( sphereData )->second );
    glEnableVertexAttribArray( _positionLocation );
    glVertexAttribPointer( _positionLocation, 3, GL_FLOAT, GL_FALSE, 0, (void*)0 );
    glEnableVertexAttribArray( _normalLocation );
    glVertexAttribPointer( _normalLocation, 3, GL_FLOAT, GL_FALSE, 0, (void*)(sizeof(GLfloat)*((slices + 2)*2 + ((stacks - 2)*(slices+1))*2) *3) );
    glEnableVertexAttribArray( _texCoordLocation );
    glVertexAttribPointer( _texCoordLocation, 2, GL_FLOAT, GL_FALSE, 0, (void*)(sizeof(GLfloat)*((slices + 2)*2 + ((stacks - 2)*(slices+1))*2) *6) );

    glDrawArrays( GL_TRIANGLE_FAN, 0, slices+2 );

    for( int stackNum = 1; stackNum < stacks-1; stackNum++ ) {
        glDrawArrays( GL_TRIANGLE_STRIP, (slices+2) + (stackNum-1)*((slices+1)*2), (slices+1)*2 );
    }

    glDrawArrays( GL_TRIANGLE_FAN, (slices+2) + (stacks-2)*(slices+1)*2, slices+2 );

    glPolygonMode( GL_FRONT_AND_BACK, GL_FILL );
}

inline void CSCI441_INTERNAL::drawTorus( GLfloat innerRadius, GLfloat outerRadius, GLint sides, GLint rings, GLenum renderMode ) {
    TorusData torusData = { innerRadius, outerRadius, sides, rings };
    if( CSCI441_INTERNAL::_torusVAO.count( torusData ) == 0 ) {
        CSCI441_INTERNAL::generateTorusVAO( torusData );
    }

    glPolygonMode( GL_FRONT_AND_BACK, renderMode );
    glBindVertexArray( CSCI441_INTERNAL::_torusVAO.find( torusData )->second );
    glBindBuffer( GL_ARRAY_BUFFER, CSCI441_INTERNAL::_torusVBO.find( torusData )->second );
    glEnableVertexAttribArray( _positionLocation );
    glVertexAttribPointer( _positionLocation, 3, GL_FLOAT, GL_FALSE, 0, (void*)0 );
    glEnableVertexAttribArray( _normalLocation );
    glVertexAttribPointer( _normalLocation, 3, GL_FLOAT, GL_FALSE, 0, (void*)(sizeof(GLfloat)*(sides*4*rings)*3) );
    glEnableVertexAttribArray( _texCoordLocation );
    glVertexAttribPointer( _texCoordLocation, 2, GL_FLOAT, GL_FALSE, 0, (void*)(sizeof(GLfloat)*(sides*4*rings)*6) );

    for( int ringNum = 0; ringNum < rings; ringNum++ ) {
        glDrawArrays( GL_TRIANGLE_STRIP, ringNum*sides*4, sides*4 );
    }

    glPolygonMode( GL_FRONT_AND_BACK, GL_FILL );
}

inline void CSCI441_INTERNAL::generateCubeVAOFlat( GLfloat sideLength ) {
    GLuint vaod;
    glGenVertexArrays( 1, &vaod );
    glBindVertexArray( vaod );

    GLuint vbod;
    glGenBuffers( 1, &vbod );
    glBindBuffer( GL_ARRAY_BUFFER, vbod );

    GLfloat cornerPoint = sideLength / 2.0f;

    GLfloat vertices[36][3] = {
            // Left Face
            {-cornerPoint, -cornerPoint, -cornerPoint}, {-cornerPoint, -cornerPoint,  cornerPoint}, {-cornerPoint,  cornerPoint, -cornerPoint},
            {-cornerPoint,  cornerPoint, -cornerPoint}, {-cornerPoint, -cornerPoint,  cornerPoint}, {-cornerPoint,  cornerPoint,  cornerPoint},
            // Right Face
            { cornerPoint,  cornerPoint,  cornerPoint}, { cornerPoint, -cornerPoint,  cornerPoint}, { cornerPoint,  cornerPoint, -cornerPoint},
            { cornerPoint,  cornerPoint, -cornerPoint}, { cornerPoint, -cornerPoint,  cornerPoint}, { cornerPoint, -cornerPoint, -cornerPoint},
            // Top Face
            {-cornerPoint,  cornerPoint, -cornerPoint}, {-cornerPoint,  cornerPoint,  cornerPoint}, { cornerPoint,  cornerPoint, -cornerPoint},
            { cornerPoint,  cornerPoint, -cornerPoint}, {-cornerPoint,  cornerPoint,  cornerPoint}, { cornerPoint,  cornerPoint,  cornerPoint},
            // Bottom Face
            { cornerPoint, -cornerPoint,  cornerPoint}, {-cornerPoint, -cornerPoint,  cornerPoint}, { cornerPoint, -cornerPoint, -cornerPoint},
            { cornerPoint, -cornerPoint, -cornerPoint}, {-cornerPoint, -cornerPoint,  cornerPoint}, {-cornerPoint, -cornerPoint, -cornerPoint},
            // Back Face
            { cornerPoint,  cornerPoint, -cornerPoint}, { cornerPoint, -cornerPoint, -cornerPoint}, {-cornerPoint,  cornerPoint, -cornerPoint},
            {-cornerPoint,  cornerPoint, -cornerPoint}, { cornerPoint, -cornerPoint, -cornerPoint}, {-cornerPoint, -cornerPoint, -cornerPoint},
            // Front Face
            {-cornerPoint, -cornerPoint,  cornerPoint}, { cornerPoint, -cornerPoint,  cornerPoint}, {-cornerPoint,  cornerPoint,  cornerPoint},
            {-cornerPoint,  cornerPoint,  cornerPoint}, { cornerPoint, -cornerPoint,  cornerPoint}, { cornerPoint,  cornerPoint,  cornerPoint}
    };
    GLfloat texCoords[36][2] = {
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
    GLfloat normals[36][3] = {
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

    glBufferData( GL_ARRAY_BUFFER, sizeof(GLfloat) * 36 * 8, NULL, GL_STATIC_DRAW );
    glBufferSubData( GL_ARRAY_BUFFER, 0, sizeof(GLfloat) * 36 * 3, vertices );
    glBufferSubData( GL_ARRAY_BUFFER, sizeof(GLfloat) * 36 * 3, sizeof(GLfloat) * 36 * 3, normals );
    glBufferSubData( GL_ARRAY_BUFFER, sizeof(GLfloat) * 36 * 6, sizeof(GLfloat) * 36 * 2, texCoords );

    CSCI441_INTERNAL::_cubeVAO.insert( std::pair<GLfloat, GLuint>( sideLength, vaod ) );
    CSCI441_INTERNAL::_cubeVBO.insert( std::pair<GLfloat, GLuint>( sideLength, vbod ) );
}

inline void CSCI441_INTERNAL::generateCubeVAOIndexed( GLfloat sideLength ) {
    const GLfloat CORNER_POINT = sideLength / 2.0f;

    GLfloat vertices[8][3] = {
            { -CORNER_POINT, -CORNER_POINT, -CORNER_POINT }, // 0 - bln
            {  CORNER_POINT, -CORNER_POINT, -CORNER_POINT }, // 1 - brn
            {  CORNER_POINT,  CORNER_POINT, -CORNER_POINT }, // 2 - trn
            { -CORNER_POINT,  CORNER_POINT, -CORNER_POINT }, // 3 - tln
            { -CORNER_POINT, -CORNER_POINT,  CORNER_POINT }, // 4 - blf
            {  CORNER_POINT, -CORNER_POINT,  CORNER_POINT }, // 5 - brf
            {  CORNER_POINT,  CORNER_POINT,  CORNER_POINT }, // 6 - trf
            { -CORNER_POINT,  CORNER_POINT,  CORNER_POINT }  // 7 - tlf
    };
    GLfloat normals[8][3] = {
            {-1, -1, -1}, // 0 LBF
            {-1,  1, -1}, // 1 LTF
            { 1, -1, -1}, // 2 RBF
            { 1,  1, -1}, // 3 RTF
            {-1, -1,  1}, // 4 LBN
            {-1,  1,  1}, // 5 LTN
            { 1, -1,  1}, // 6 RBN
            { 1,  1,  1}  // 7 RTN
    };
    unsigned short indices[36] = {
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
    glBufferData( GL_ARRAY_BUFFER, sizeof(GLfloat) * 8 * 6, nullptr, GL_STATIC_DRAW );
    glBufferSubData( GL_ARRAY_BUFFER, 0, sizeof(GLfloat) * 8 * 3, vertices );
    glBufferSubData( GL_ARRAY_BUFFER, sizeof(GLfloat) * 8 * 3, sizeof(GLfloat) * 8 * 3, normals );

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

    unsigned long int numVertices = cylData.st * (cylData.sl+1) * 2;

    GLfloat sliceStep = 2.0 * M_PI / cylData.sl;
    GLfloat stackStep = (GLfloat)cylData.h / cylData.st;

    GLfloat* vertices = (GLfloat*)malloc(sizeof(GLfloat)*numVertices*3);
    GLfloat* texCoords = (GLfloat*)malloc(sizeof(GLfloat)*numVertices*2);
    GLfloat* normals = (GLfloat*)malloc(sizeof(GLfloat)*numVertices*3);

    unsigned long int idx = 0;

    for( int stackNum = 0; stackNum < cylData.st; stackNum++ ) {
        GLfloat botRadius = cylData.b*(cylData.st-stackNum)/cylData.st + cylData.t*stackNum/cylData.st;
        GLfloat topRadius = cylData.b*(cylData.st-stackNum-1)/cylData.st + cylData.t*(stackNum+1)/cylData.st;

        for( int sliceNum = 0; sliceNum <= cylData.sl; sliceNum++ ) {
            normals[ idx*3 + 0 ] = cos( sliceNum * sliceStep );
            normals[ idx*3 + 1 ] = 0.0f;
            normals[ idx*3 + 2 ] = sin( sliceNum * sliceStep );

            texCoords[ idx*2 + 0 ] = (GLfloat)sliceNum / cylData.sl;
            texCoords[ idx*2 + 1 ] = (GLfloat)stackNum / cylData.st;

            vertices[ idx*3 + 0 ] = cos( sliceNum * sliceStep )*botRadius;
            vertices[ idx*3 + 1 ] = stackNum * stackStep;
            vertices[ idx*3 + 2 ] = sin( sliceNum * sliceStep )*botRadius;

            idx++;

            normals[ idx*3 + 0 ] = cos( sliceNum * sliceStep );
            normals[ idx*3 + 1 ] = 0.0f;
            normals[ idx*3 + 2 ] = sin( sliceNum * sliceStep );

            texCoords[ idx*2 + 0 ] = (GLfloat)sliceNum / cylData.sl;
            texCoords[ idx*2 + 1 ] = (GLfloat)(stackNum+1) / cylData.st;

            vertices[ idx*3 + 0 ] = cos( sliceNum * sliceStep )*topRadius;
            vertices[ idx*3 + 1 ] = (stackNum+1) * stackStep;
            vertices[ idx*3 + 2 ] = sin( sliceNum * sliceStep )*topRadius;

            idx++;
        }
    }

    glBufferData( GL_ARRAY_BUFFER, sizeof(GLfloat) * numVertices * 8, NULL, GL_STATIC_DRAW );
    glBufferSubData( GL_ARRAY_BUFFER, 0, 																  sizeof(GLfloat) * numVertices * 3, vertices );
    glBufferSubData( GL_ARRAY_BUFFER, sizeof(GLfloat) * numVertices * 3, sizeof(GLfloat) * numVertices * 3, normals );
    glBufferSubData( GL_ARRAY_BUFFER, sizeof(GLfloat) * numVertices * 6, sizeof(GLfloat) * numVertices * 2, texCoords );

    CSCI441_INTERNAL::_cylinderVAO.insert( std::pair<CylinderData, GLuint>( cylData, vaod ) );
    CSCI441_INTERNAL::_cylinderVBO.insert( std::pair<CylinderData, GLuint>( cylData, vbod ) );
}

inline void CSCI441_INTERNAL::generateDiskVAO( DiskData diskData ) {
    GLuint vaod;
    glGenVertexArrays( 1, &vaod );
    glBindVertexArray( vaod );

    GLuint vbod;
    glGenBuffers( 1, &vbod );
    glBindBuffer( GL_ARRAY_BUFFER, vbod );

    unsigned long int numVertices = diskData.r * (diskData.sl+1) * 2;

    GLfloat sliceStep = diskData.sw / diskData.sl;
    GLfloat ringStep = (diskData.o - diskData.i) / diskData.r;

    GLfloat* vertices = (GLfloat*)malloc(sizeof(GLfloat)*numVertices*3);
    GLfloat* texCoords = (GLfloat*)malloc(sizeof(GLfloat)*numVertices*2);
    GLfloat* normals = (GLfloat*)malloc(sizeof(GLfloat)*numVertices*3);

    unsigned long int idx = 0;

    for( int ringNum = 0; ringNum < diskData.r; ringNum++ ) {
        GLfloat currRadius = diskData.i + ringNum*ringStep;
        GLfloat nextRadius = diskData.i + (ringNum+1)*ringStep;

        GLfloat theta = diskData.st;
        for( int i = 0; i <= diskData.sl; i++, theta += sliceStep ) {
            normals[ idx*3 + 0 ] = 0.0f;
            normals[ idx*3 + 1 ] = 0.0f;
            normals[ idx*3 + 2 ] = 1.0f;

            texCoords[ idx*2 + 0 ] = cos(theta)*(currRadius/diskData.o);
            texCoords[ idx*2 + 1 ] = sin(theta)*(currRadius/diskData.o);

            vertices[ idx*3 + 0 ] = cos(theta)*currRadius;
            vertices[ idx*3 + 1 ] = sin(theta)*currRadius;
            vertices[ idx*3 + 2 ] = 0.0f;

            idx++;

            normals[ idx*3 + 0 ] = 0.0f;
            normals[ idx*3 + 1 ] = 0.0f;
            normals[ idx*3 + 2 ] = 1.0f;

            texCoords[ idx*2 + 0 ] = cos(theta)*(nextRadius/diskData.o);
            texCoords[ idx*2 + 1 ] = sin(theta)*(nextRadius/diskData.o);

            vertices[ idx*3 + 0 ] = cos(theta)*nextRadius;
            vertices[ idx*3 + 1 ] = sin(theta)*nextRadius;
            vertices[ idx*3 + 2 ] = 0.0f;

            idx++;
        }
    }

    glBufferData( GL_ARRAY_BUFFER, sizeof(GLfloat) * numVertices * 8, NULL, GL_STATIC_DRAW );
    glBufferSubData( GL_ARRAY_BUFFER, 0, 																  sizeof(GLfloat) * numVertices * 3, vertices );
    glBufferSubData( GL_ARRAY_BUFFER, sizeof(GLfloat) * numVertices * 3, sizeof(GLfloat) * numVertices * 3, normals );
    glBufferSubData( GL_ARRAY_BUFFER, sizeof(GLfloat) * numVertices * 6, sizeof(GLfloat) * numVertices * 2, texCoords );

    CSCI441_INTERNAL::_diskVAO.insert( std::pair<DiskData, GLuint>( diskData, vaod ) );
    CSCI441_INTERNAL::_diskVBO.insert( std::pair<DiskData, GLuint>( diskData, vbod ) );
}

inline void CSCI441_INTERNAL::generateSphereVAO( SphereData sphereData ) {
    GLuint vaod;
    glGenVertexArrays( 1, &vaod );
    glBindVertexArray( vaod );

    GLuint vbod;
    glGenBuffers( 1, &vbod );
    glBindBuffer( GL_ARRAY_BUFFER, vbod );

    unsigned long int numVertices = (sphereData.sl + 2)*2 + ((sphereData.st - 2)*(sphereData.sl+1))*2;

    GLfloat sliceStep = 2.0 * M_PI / sphereData.sl;
    GLfloat stackStep = M_PI / sphereData.st;

    GLfloat* vertices = (GLfloat*)malloc(sizeof(GLfloat)*numVertices*3);
    GLfloat* texCoords = (GLfloat*)malloc(sizeof(GLfloat)*numVertices*2);
    GLfloat* normals = (GLfloat*)malloc(sizeof(GLfloat)*numVertices*3);

    unsigned long int idx = 0;

    // sphere top
    GLfloat phi = stackStep * sphereData.st;
    GLfloat phiNext = stackStep * (sphereData.st-1);

    normals[ idx*3 + 0 ] = 0.0f;
    normals[ idx*3 + 1 ] = 1.0f;
    normals[ idx*3 + 2 ] = 0.0f;

    texCoords[ idx*2 + 0 ] = 0.5f;
    texCoords[ idx*2 + 1 ] = 1.0f;

    vertices[ idx*3 + 0 ] = 0.0f;
    vertices[ idx*3 + 1 ] = -cos( phi )*sphereData.r;
    vertices[ idx*3 + 2 ] = 0.0f;

    idx++;

    for( int sliceNum = sphereData.sl; sliceNum >= 0; sliceNum-- ) {
        GLfloat theta = sliceStep * sliceNum;

        normals[ idx*3 + 0 ] = -cos( theta )*sin( phiNext );
        normals[ idx*3 + 1 ] = -cos( phiNext );
        normals[ idx*3 + 2 ] = sin( theta )*sin( phiNext );

        texCoords[ idx*2 + 0 ] = (sphereData.st-1.0f) / sphereData.st;
        texCoords[ idx*2 + 1 ] = sliceNum / sphereData.sl;

        vertices[ idx*3 + 0 ] = -cos( theta )*sin( phiNext )*sphereData.r;
        vertices[ idx*3 + 1 ] = -cos( phiNext )*sphereData.r;
        vertices[ idx*3 + 2 ] = sin( theta )*sin( phiNext )*sphereData.r;

        idx++;
    }

    // sphere stacks
    for( int stackNum = 1; stackNum < sphereData.st-1; stackNum++ ) {
        phi = stackStep * stackNum;
        phiNext = stackStep * (stackNum + 1);

        for( int sliceNum = sphereData.sl; sliceNum >= 0; sliceNum-- ) {
            GLfloat theta = sliceStep * sliceNum;

            normals[ idx*3 + 0 ] = -cos( theta )*sin( phi );
            normals[ idx*3 + 1 ] = -cos( phi );
            normals[ idx*3 + 2 ] =  sin( theta )*sin( phi );

            texCoords[ idx*2 + 0 ] = theta / 6.28;
            texCoords[ idx*2 + 1 ] = phi / 3.14;

            vertices[ idx*3 + 0 ] = -cos( theta )*sin( phi )*sphereData.r;
            vertices[ idx*3 + 1 ] = -cos( phi )*sphereData.r;
            vertices[ idx*3 + 2 ] = sin( theta )*sin( phi )*sphereData.r;

            idx++;

            normals[ idx*3 + 0 ] = -cos( theta )*sin( phiNext );
            normals[ idx*3 + 1 ] = -cos( phiNext );
            normals[ idx*3 + 2 ] =  sin( theta )*sin( phiNext );

            texCoords[ idx*2 + 0 ] = theta / 6.28;
            texCoords[ idx*2 + 1 ] = phiNext / 3.14;

            vertices[ idx*3 + 0 ] = -cos( theta )*sin( phiNext )*sphereData.r;
            vertices[ idx*3 + 1 ] = -cos( phiNext )*sphereData.r;
            vertices[ idx*3 + 2 ] = sin( theta )*sin( phiNext )*sphereData.r;

            idx++;
        }
    }

    // sphere bottom
    phi = 0;
    phiNext = stackStep;

    normals[ idx*3 + 0 ] =  0.0f;
    normals[ idx*3 + 1 ] = -1.0f;
    normals[ idx*3 + 2 ] =  0.0f;

    texCoords[ idx*2 + 0 ] = 0.5f;
    texCoords[ idx*2 + 1 ] = 0.0f;

    vertices[ idx*3 + 0 ] = 0.0f;
    vertices[ idx*3 + 1 ] = -cos( phi )*sphereData.r;
    vertices[ idx*3 + 2 ] = 0.0f;

    idx++;

    for( int sliceNum = sphereData.sl; sliceNum >= 0; sliceNum-- ) {
        GLfloat theta = sliceStep * sliceNum;

        normals[ idx*3 + 0 ] = -cos( theta )*sin( phiNext );
        normals[ idx*3 + 1 ] = -cos( phiNext );
        normals[ idx*3 + 2 ] = sin( theta )*sin( phiNext );

        texCoords[ idx*2 + 0 ] = 1.0f / sphereData.st;
        texCoords[ idx*2 + 1 ] = sliceNum / sphereData.sl;

        vertices[ idx*3 + 0 ] = -cos( theta )*sin( phiNext )*sphereData.r;
        vertices[ idx*3 + 1 ] = -cos( phiNext )*sphereData.r;
        vertices[ idx*3 + 2 ] = sin( theta )*sin( phiNext )*sphereData.r;

        idx++;
    }

    glBufferData( GL_ARRAY_BUFFER, sizeof(GLfloat) * numVertices * 8, NULL, GL_STATIC_DRAW );
    glBufferSubData( GL_ARRAY_BUFFER, 0, 																  sizeof(GLfloat) * numVertices * 3, vertices );
    glBufferSubData( GL_ARRAY_BUFFER, sizeof(GLfloat) * numVertices * 3, sizeof(GLfloat) * numVertices * 3, normals );
    glBufferSubData( GL_ARRAY_BUFFER, sizeof(GLfloat) * numVertices * 6, sizeof(GLfloat) * numVertices * 2, texCoords );

    CSCI441_INTERNAL::_sphereVAO.insert( std::pair<SphereData, GLuint>( sphereData, vaod ) );
    CSCI441_INTERNAL::_sphereVBO.insert( std::pair<SphereData, GLuint>( sphereData, vbod ) );
}

inline void CSCI441_INTERNAL::generateTorusVAO( TorusData torusData ) {
    GLuint vaod;
    glGenVertexArrays( 1, &vaod );
    glBindVertexArray( vaod );

    GLuint vbod;
    glGenBuffers( 1, &vbod );
    glBindBuffer( GL_ARRAY_BUFFER, vbod );

    unsigned long int numVertices = torusData.s * 4 * torusData.r;

    GLfloat* vertices = (GLfloat*)malloc(sizeof(GLfloat)*numVertices*3);
    GLfloat* texCoords = (GLfloat*)malloc(sizeof(GLfloat)*numVertices*2);
    GLfloat* normals = (GLfloat*)malloc(sizeof(GLfloat)*numVertices*3);

    unsigned long int idx = 0;

    GLfloat sideStep = 2.0 * M_PI / torusData.s;
    GLfloat ringStep = 2.0 * M_PI / torusData.r;

    for( int ringNum = 0; ringNum < torusData.r; ringNum++ ) {
        GLfloat currTheta = ringStep * ringNum;
        GLfloat nextTheta = ringStep * (ringNum+1);

        for( int sideNum = 0; sideNum < torusData.s; sideNum++ ) {
            GLfloat currPhi = sideStep * sideNum;
            GLfloat nextPhi = sideStep * (sideNum+1);

            normals[ idx*3 + 0 ] = cos( currPhi ) * cos( currTheta );
            normals[ idx*3 + 1 ] = cos( currPhi ) * sin( currTheta );
            normals[ idx*3 + 2 ] = sin( currPhi );

            texCoords[ idx*2 + 0 ] = cos( currPhi ) * cos( currTheta );
            texCoords[ idx*2 + 1 ] = cos( currPhi ) * sin( currTheta );

            vertices[ idx*3 + 0 ] = ( torusData.o + torusData.i * cos( currPhi ) ) * cos( currTheta );
            vertices[ idx*3 + 1 ] = ( torusData.o + torusData.i * cos( currPhi ) ) * sin( currTheta );
            vertices[ idx*3 + 2 ] = torusData.i * sin( currPhi );

            idx++;

            normals[ idx*3 + 0 ] = cos( currPhi ) * cos( nextTheta );
            normals[ idx*3 + 1 ] = cos( currPhi ) * sin( nextTheta );
            normals[ idx*3 + 2 ] = sin( currPhi );

            texCoords[ idx*2 + 0 ] = cos( currPhi ) * cos( nextTheta );
            texCoords[ idx*2 + 1 ] = cos( currPhi ) * sin( nextTheta );

            vertices[ idx*3 + 0 ] = ( torusData.o + torusData.i * cos( currPhi ) ) * cos( nextTheta );
            vertices[ idx*3 + 1 ] = ( torusData.o + torusData.i * cos( currPhi ) ) * sin( nextTheta );
            vertices[ idx*3 + 2 ] = torusData.i * sin( currPhi );

            idx++;

            normals[ idx*3 + 0 ] = cos( nextPhi ) * cos( currTheta );
            normals[ idx*3 + 1 ] = cos( nextPhi ) * sin( currTheta );
            normals[ idx*3 + 2 ] = sin( nextPhi );

            texCoords[ idx*2 + 0 ] = cos( nextPhi ) * cos( currTheta );
            texCoords[ idx*2 + 1 ] = cos( nextPhi ) * sin( currTheta );

            vertices[ idx*3 + 0 ] = ( torusData.o + torusData.i * cos( nextPhi ) ) * cos( currTheta );
            vertices[ idx*3 + 1 ] = ( torusData.o + torusData.i * cos( nextPhi ) ) * sin( currTheta );
            vertices[ idx*3 + 2 ] = torusData.i * sin( nextPhi );

            idx++;

            normals[ idx*3 + 0 ] = cos( nextPhi ) * cos( nextTheta );
            normals[ idx*3 + 1 ] = cos( nextPhi ) * sin( nextTheta );
            normals[ idx*3 + 2 ] = sin( nextPhi );

            texCoords[ idx*2 + 0 ] = cos( nextPhi ) * cos( nextTheta );
            texCoords[ idx*2 + 1 ] = cos( nextPhi ) * sin( nextTheta );

            vertices[ idx*3 + 0 ] = ( torusData.o + torusData.i * cos( nextPhi ) ) * cos( nextTheta );
            vertices[ idx*3 + 1 ] = ( torusData.o + torusData.i * cos( nextPhi ) ) * sin( nextTheta );
            vertices[ idx*3 + 2 ] = torusData.i * sin( nextPhi );

            idx++;
        }
    }

    glBufferData( GL_ARRAY_BUFFER, sizeof(GLfloat) * numVertices * 8, NULL, GL_STATIC_DRAW );
    glBufferSubData( GL_ARRAY_BUFFER, 0, 																  sizeof(GLfloat) * numVertices * 3, vertices );
    glBufferSubData( GL_ARRAY_BUFFER, sizeof(GLfloat) * numVertices * 3, sizeof(GLfloat) * numVertices * 3, normals );
    glBufferSubData( GL_ARRAY_BUFFER, sizeof(GLfloat) * numVertices * 6, sizeof(GLfloat) * numVertices * 2, texCoords );

    CSCI441_INTERNAL::_torusVAO.insert( std::pair<TorusData, GLuint>( torusData, vaod ) );
    CSCI441_INTERNAL::_torusVBO.insert( std::pair<TorusData, GLuint>( torusData, vbod ) );
}

#endif // __CSCI441_OBJECTS_HPP__
