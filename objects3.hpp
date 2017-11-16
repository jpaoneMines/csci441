/** @file objects3.hpp
  * @brief Helper functions to draw 3D OpenGL 3.0+ objects
	* @author Dr. Jeffrey Paone
	* @date Last Edit: 26 Oct 2017
	* @version 1.3
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

#ifdef __CSCI441_OBJECTS_HPP__
	#error cannot include both CSCI441/objects.h and CSCI441/objects3.h
#else

#ifndef __CSCI441_OBJECTS_3_HPP__
#define __CSCI441_OBJECTS_3_HPP__

#include <GL/glew.h>

#include <assert.h>   					// for assert()
#include <math.h>								// for cos(), sin()

#include <CSCI441/teapot3.hpp> 	// for teapot()

#include <map>									// for map

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

		/**	@brief Draws a solid cone
		  *
			*	Cone is oriented along the y-axis with the origin along the base of the cone
			*
			* @param GLdouble base		- radius of the base of the cone
			* @param GLdouble height	- height of the cone from the base to the tip
			* @param GLint stacks			- resolution of the number of steps rotated around the central axis of the cone
			* @param GLint slices			- resolution of the number of steps to take along the height
			* @pre base must be greater than zero
			* @pre height must be greater than zero
			* @pre stacks must be greater than zero
			* @pre slices must be greater than two
		  */
		void drawSolidCone( GLdouble base, GLdouble height, GLint stacks, GLint slices );
		/**	@brief Draws a wireframe cone
		  *
			*	Cone is oriented along the y-axis with the origin along the base of the cone
			*
			* @param GLdouble base		- radius of the base of the cone
			* @param GLdouble height	- height of the cone from the base to the tip
			* @param GLint stacks			- resolution of the number of steps rotated around the central axis of the cone
			* @param GLint slices			- resolution of the number of steps to take along the height
			* @pre base must be greater than zero
			* @pre height must be greater than zero
			* @pre stacks must be greater than zero
			* @pre slices must be greater than two
		  */
		void drawWireCone( GLdouble base, GLdouble height, GLint stacks, GLint slices );

		/** @brief Draws a solid cube
		  *
			*	The origin is at the cube's center of mass.  Cube is oriented with our XYZ axes
			*
			* @param GLdouble sideLength - length of the edge of the cube
			* @pre sideLength must be greater than zero
			*/
			void drawSolidCube( GLdouble sideLength );
		/** @brief Draws a wireframe cube
		  *
			*	The origin is at the cube's center of mass.  Cube is oriented with our XYZ axes
			*
			* @param GLdouble sideLength - length of the edge of the cube
			* @pre sideLength must be greater than zero
			*/
		void drawWireCube( GLdouble sideLength );

		/**	@brief Draws a solid open ended cylinder
		  *
			*	Cylinder is oriented along the y-axis with the origin along the base
			*
			* @param GLdouble base		- radius of the base of the cylinder
			* @param GLdouble top			- radius of the top of the cylinder
			* @param GLdouble height	- height of the cylinder from the base to the top
			* @param GLint stacks			- resolution of the number of steps rotated around the central axis of the cylinder
			* @param GLint slices			- resolution of the number of steps to take along the height
			* @pre either: (1) base is greater than zero and top is greater than or equal to zero or (2) base is greater than or equal to zero and top is greater than zero
			* @pre height must be greater than zero
			* @pre stacks must be greater than zero
			* @pre slices must be greater than two
		  */
		void drawSolidCylinder( GLdouble base, GLdouble top, GLdouble height, GLint stacks, GLint slices );
		/**	@brief Draws a wireframe open ended cylinder
		  *
			*	Cylinder is oriented along the y-axis with the origin along the base
			*
			* @param GLdouble base		- radius of the base of the cylinder
			* @param GLdouble top			- radius of the top of the cylinder
			* @param GLdouble height	- height of the cylinder from the base to the top
			* @param GLint stacks			- resolution of the number of steps rotated around the central axis of the cylinder
			* @param GLint slices			- resolution of the number of steps to take along the height
			* @pre either: (1) base is greater than zero and top is greater than or equal to zero or (2) base is greater than or equal to zero and top is greater than zero
			* @pre height must be greater than zero
			* @pre stacks must be greater than zero
			* @pre slices must be greater than two
		  */
		void drawWireCylinder( GLdouble base, GLdouble top, GLdouble height, GLint stacks, GLint slices );

		/** @brief Draws a solid disk
		  *
			*	Disk is drawn in the XY plane with the origin at its center
			*
			*	@param GLdouble inner		- equivalent to the width of the disk
			*	@param GLdouble outer		- radius from the center of the disk to the center of the ring
			* @param GLint slices			- resolution of the number of steps rotated along the disk
			* @param GLint rings			- resolution of the number of steps to take along the disk width
			* @pre inner is greater than or equal to zero
			* @pre outer is greater than zero
			* @pre outer is greater than inner
			* @pre slices is greater than two
			* @pre rings is greater than zero
			*/
		void drawSolidDisk( GLdouble inner, GLdouble outer, GLint slices, GLint rings );
		/** @brief Draws a wireframe disk
		  *
			*	Disk is drawn in the XY plane with the origin at its center
			*
			*	@param GLdouble inner		- equivalent to the width of the disk
			*	@param GLdouble outer		- radius from the center of the disk to the center of the ring
			* @param GLint slices			- resolution of the number of steps rotated along the disk
			* @param GLint rings			- resolution of the number of steps to take along the disk width
			* @pre inner is greater than or equal to zero
			* @pre outer is greater than zero
			* @pre outer is greater than inner
			* @pre slices is greater than two
			* @pre rings is greater than zero
			*/
		void drawWireDisk( GLdouble inner, GLdouble outer, GLint slices, GLint rings );

		/** @brief Draws part of a solid disk
		  *
			*	Disk is drawn in the XY plane with the origin at its center
			*
			*	@param GLdouble inner		- equivalent to the width of the disk
			*	@param GLdouble outer		- radius from the center of the disk to the center of the ring
			* @param GLint stacks			- resolution of the number of steps rotated along the disk
			* @param GLint rings			- resolution of the number of steps to take along the disk width
			*	@param GLdouble start		- angle in degrees to start the disk at
			*	@param GLdouble sweep		- distance in degrees to rotate through
			* @pre inner is greater than or equal to zero
			* @pre outer is greater than zero
			* @pre outer is greater than inner
			* @pre slices is greater than two
			* @pre rings is greater than zero
			* @pre start is between [0, 360]
			* @pre sweep is between [0, 360]
			*/
		void drawSolidPartialDisk( GLdouble inner, GLdouble outer, GLint slices, GLint rings, GLdouble start, GLdouble sweep );
		/** @brief Draws part of a wireframe disk
		  *
			*	Disk is drawn in the XY plane with the origin at its center
			*
			*	@param GLdouble inner		- equivalent to the width of the disk
			*	@param GLdouble outer		- radius from the center of the disk to the center of the ring
			* @param GLint stacks			- resolution of the number of steps rotated along the disk
			* @param GLint rings			- resolution of the number of steps to take along the disk width
			*	@param GLdouble start		- angle in degrees to start the disk at
			*	@param GLdouble sweep		- distance in degrees to rotate through
			* @pre inner is greater than or equal to zero
			* @pre outer is greater than zero
			* @pre outer is greater than inner
			* @pre slices is greater than two
			* @pre rings is greater than zero
			* @pre start is between [0, 360]
			* @pre sweep is between [0, 360]
			*/
		void drawWirePartialDisk( GLdouble inner, GLdouble outer, GLint slices, GLint rings, GLdouble start, GLdouble sweep );

		/** @brief Draws a solid sphere
		  *
			*	Origin is at the center of the sphere
			*
			*	@param GLdouble radius	- radius of the sphere
			* @param GLint stacks			- resolution of the number of steps to take along theta (rotate around Y-axis)
			* @param GLint slices			- resolution of the number of steps to take along phi (rotate around X- or Z-axis)
			*	@pre radius must be greater than 0
			* @pre stacks must be greater than 2
			* @pre slices must be greater than 2
			*/
		void drawSolidSphere( GLdouble radius, GLint stacks, GLint slices );
		/** @brief Draws a wireframe sphere
		  *
			*	Origin is at the center of the sphere
			*
			*	@param GLdouble radius	- radius of the sphere
			* @param GLint stacks			- resolution of the number of steps to take along theta (rotate around Y-axis)
			* @param GLint slices			- resolution of the number of steps to take along phi (rotate around X- or Z-axis)
			*	@pre radius must be greater than 0
			* @pre stacks must be greater than 2
			* @pre slices must be greater than 2
			*/
		void drawWireSphere( GLdouble radius, GLint stacks, GLint slices );

		/** @brief Draws a solid teapot
		  *
			*	Oriented with spout and handle running along X-axis, cap and bottom along Y-axis.  Origin is at the
			*	center of the teapot
			*
			*	@param GLdouble size	- scale of the teapot
			*	@pre size must be greater than zero
			*/
		void drawSolidTeapot( GLdouble size );
		/** @brief Draws a wireframe teapot
		  *
			*	Oriented with spout and handle running along X-axis, cap and bottom along Y-axis.  Origin is at the
			*	center of the teapot
			*
			*	@param GLdouble size	- scale of the teapot
			*	@pre size must be greater than zero
			*/
		void drawWireTeapot( GLdouble size );

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
		void drawSolidTorus( GLdouble innerRadius, GLdouble outerRadius, GLint sides, GLint rings );
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
		void drawWireTorus( GLdouble innerRadius, GLdouble outerRadius, GLint sides, GLint rings );
}

////////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////
// Internal rendering implementations to stay consistent with solid and wire modes
//
// Cone is drawn with a cylinder
// Disk is drawn with a partial disk

namespace CSCI441_INTERNAL {
	void drawCube( GLdouble sideLength, GLenum renderMode );
	void drawCylinder( GLdouble base, GLdouble top, GLdouble height, GLint stacks, GLint slices, GLenum renderMode );
	void drawPartialDisk( GLdouble inner, GLdouble outer, GLint slices, GLint rings, GLdouble start, GLdouble sweep, GLenum renderMode );
	void drawSphere( GLdouble radius, GLint stacks, GLint slices, GLenum renderMode );
	void drawTorus( GLdouble innerRadius, GLdouble outerRadius, GLint sides, GLint rings, GLenum renderMode );

	static GLint _positionLocation = -1;
	static GLint _normalLocation = -1;
	static GLint _texCoordLocation = -1;

	void generateCubeVAO( GLdouble sideLength );
	static std::map< GLdouble, GLuint > _cubeVAO;
	static std::map< GLdouble, GLuint > _cubeVBO;

	struct CylinderData {
		GLdouble b, t, h;
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
		GLdouble i, o, st, sw;
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
		GLdouble r;
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
		GLdouble i, o;
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

inline void CSCI441::drawSolidCone( GLdouble base, GLdouble height, GLint stacks, GLint slices ) {
	assert( base > 0.0f );
	assert( height > 0.0f );
	assert( stacks > 0 );
	assert( slices > 2 );

	CSCI441_INTERNAL::drawCylinder( base, 0.0f, height, stacks, slices, GL_FILL );
}

inline void CSCI441::drawWireCone( GLdouble base, GLdouble height, GLint stacks, GLint slices ) {
	assert( base > 0.0f );
	assert( height > 0.0f );
	assert( stacks > 0 );
	assert( slices > 2 );

	CSCI441_INTERNAL::drawCylinder( base, 0.0f, height, stacks, slices, GL_LINE );
}

inline void CSCI441::drawSolidCube( GLdouble sideLength ) {
  assert( sideLength > 0.0f );

  CSCI441_INTERNAL::drawCube( sideLength, GL_FILL );
}

inline void CSCI441::drawWireCube( GLdouble sideLength ) {
  assert( sideLength > 0.0f );

  CSCI441_INTERNAL::drawCube( sideLength, GL_LINE );
}

inline void CSCI441::drawSolidCylinder( GLdouble base, GLdouble top, GLdouble height, GLint stacks, GLint slices ) {
	assert( (base >= 0.0f && top > 0.0f) || (base > 0.0f && top >= 0.0f) );
	assert( height > 0.0f );
	assert( stacks > 0 );
	assert( slices > 2 );

	CSCI441_INTERNAL::drawCylinder( base, top, height, stacks, slices, GL_FILL );
}

inline void CSCI441::drawWireCylinder( GLdouble base, GLdouble top, GLdouble height, GLint stacks, GLint slices ) {
	assert( (base >= 0.0f && top > 0.0f) || (base > 0.0f && top >= 0.0f) );
	assert( height > 0.0f );
	assert( stacks > 0 );
	assert( slices > 2 );

	CSCI441_INTERNAL::drawCylinder( base, top, height, stacks, slices, GL_LINE );
}

inline void CSCI441::drawSolidDisk( GLdouble inner, GLdouble outer, GLint slices, GLint rings ) {
	assert( inner >= 0.0f );
	assert( outer > 0.0f );
	assert( outer > inner );
	assert( slices > 2 );
	assert( rings > 0 );

	CSCI441_INTERNAL::drawPartialDisk( inner, outer, slices, rings, 0, 2*M_PI, GL_FILL );
}

inline void CSCI441::drawWireDisk( GLdouble inner, GLdouble outer, GLint slices, GLint rings ) {
	assert( inner >= 0.0f );
	assert( outer > 0.0f );
	assert( outer > inner );
	assert( slices > 2 );
	assert( rings > 0 );

	CSCI441_INTERNAL::drawPartialDisk( inner, outer, slices, rings, 0, 2*M_PI, GL_LINE );
}

inline void CSCI441::drawSolidPartialDisk( GLdouble inner, GLdouble outer, GLint slices, GLint rings, GLdouble start, GLdouble sweep ) {
	assert( inner >= 0.0f );
	assert( outer > 0.0f );
	assert( outer > inner );
	assert( slices > 2 );
	assert( rings > 0 );
	assert( start >= 0.0f && start <= 360.0f );
	assert( sweep >= 0.0f && sweep <= 360.0f );

	CSCI441_INTERNAL::drawPartialDisk( inner, outer, slices, rings, start * M_PI / 180.0f, sweep * M_PI / 180.0f, GL_FILL );
}

inline void CSCI441::drawWirePartialDisk( GLdouble inner, GLdouble outer, GLint slices, GLint rings, GLdouble start, GLdouble sweep ) {
	assert( inner >= 0.0f );
	assert( outer > 0.0f );
	assert( outer > inner );
	assert( slices > 2 );
	assert( rings > 0 );
	assert( start >= 0.0f && start <= 360.0f );
	assert( sweep >= 0.0f && sweep <= 360.0f );

	CSCI441_INTERNAL::drawPartialDisk( inner, outer, slices, rings, start * M_PI / 180.0f, sweep * M_PI / 180.0f, GL_LINE );
}

inline void CSCI441::drawSolidSphere( GLdouble radius, GLint stacks, GLint slices ) {
	assert( radius > 0.0f );
	assert( stacks > 1 );
	assert( slices > 2 );

	CSCI441_INTERNAL::drawSphere( radius, stacks, slices, GL_FILL );
}

inline void CSCI441::drawWireSphere( GLdouble radius, GLint stacks, GLint slices ) {
	assert( radius > 0.0f );
	assert( stacks > 1);
	assert( slices > 2 );

	CSCI441_INTERNAL::drawSphere( radius, stacks, slices, GL_LINE );
}

inline void CSCI441::drawSolidTeapot( GLdouble size ) {
	assert( size > 0.0f );

	CSCI441_INTERNAL::teapot( size, CSCI441_INTERNAL::_positionLocation, CSCI441_INTERNAL::_normalLocation );
}

inline void CSCI441::drawWireTeapot( GLdouble size ) {
	assert( size > 0.0f );

	glPolygonMode( GL_FRONT_AND_BACK, GL_LINE );
	CSCI441_INTERNAL::teapot( size, CSCI441_INTERNAL::_positionLocation, CSCI441_INTERNAL::_normalLocation );
	glPolygonMode( GL_FRONT_AND_BACK, GL_FILL );
}

inline void CSCI441::drawSolidTorus( GLdouble innerRadius, GLdouble outerRadius, GLint sides, GLint rings ) {
	assert( innerRadius > 0.0f );
	assert( outerRadius > 0.0f );
	assert( sides > 2 );
	assert( rings > 2 );

	CSCI441_INTERNAL::drawTorus( innerRadius, outerRadius, sides, rings, GL_FILL );
}

inline void CSCI441::drawWireTorus( GLdouble innerRadius, GLdouble outerRadius, GLint sides, GLint rings ) {
	assert( innerRadius > 0.0f );
	assert( outerRadius > 0.0f );
	assert( sides > 2 );
	assert( rings > 2 );

	CSCI441_INTERNAL::drawTorus( innerRadius, outerRadius, sides, rings, GL_LINE );
}

////////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////
// Internal function rendering implementations

inline void CSCI441_INTERNAL::drawCube( GLdouble sideLength, GLenum renderMode ) {
	if( CSCI441_INTERNAL::_cubeVAO.find( sideLength ) == CSCI441_INTERNAL::_cubeVAO.end() ) {
		CSCI441_INTERNAL::generateCubeVAO( sideLength );
	}

	glPolygonMode( GL_FRONT_AND_BACK, renderMode );
	glBindVertexArray( CSCI441_INTERNAL::_cubeVAO.find( sideLength )->second );
	glBindBuffer( GL_ARRAY_BUFFER, CSCI441_INTERNAL::_cubeVBO.find( sideLength )->second );
	glEnableVertexAttribArray( _positionLocation );
	glVertexAttribPointer( _positionLocation, 3, GL_DOUBLE, GL_FALSE, 0, (void*)0 );
	glEnableVertexAttribArray( _normalLocation );
	glVertexAttribPointer( _normalLocation, 3, GL_DOUBLE, GL_FALSE, 0, (void*)(sizeof(GLdouble)*36*3) );
	glEnableVertexAttribArray( _texCoordLocation );
	glVertexAttribPointer( _texCoordLocation, 2, GL_DOUBLE, GL_FALSE, 0, (void*)(sizeof(GLdouble)*36*6) );
	glDrawArrays( GL_TRIANGLES, 0, 36 );

	glPolygonMode( GL_FRONT_AND_BACK, GL_FILL );
}

inline void CSCI441_INTERNAL::drawCylinder( GLdouble base, GLdouble top, GLdouble height, GLint stacks, GLint slices, GLenum renderMode ) {
	CylinderData cylData = { base, top, height, stacks, slices };
	if( CSCI441_INTERNAL::_cylinderVAO.find( cylData ) == CSCI441_INTERNAL::_cylinderVAO.end() ) {
		CSCI441_INTERNAL::generateCylinderVAO( cylData );
	}

	glPolygonMode( GL_FRONT_AND_BACK, renderMode );
	glBindVertexArray( CSCI441_INTERNAL::_cylinderVAO.find( cylData )->second );
	glBindBuffer( GL_ARRAY_BUFFER, CSCI441_INTERNAL::_cylinderVBO.find( cylData )->second );
	glEnableVertexAttribArray( _positionLocation );
	glVertexAttribPointer( _positionLocation, 3, GL_DOUBLE, GL_FALSE, 0, (void*)0 );
	glEnableVertexAttribArray( _normalLocation );
	glVertexAttribPointer( _normalLocation, 3, GL_DOUBLE, GL_FALSE, 0, (void*)(sizeof(GLdouble)*stacks * (slices+1) * 2*3) );
	glEnableVertexAttribArray( _texCoordLocation );
	glVertexAttribPointer( _texCoordLocation, 2, GL_DOUBLE, GL_FALSE, 0, (void*)(sizeof(GLdouble)*stacks * (slices+1) * 2*6) );

	for( int stackNum = 0; stackNum < stacks; stackNum++ ) {
		glDrawArrays( GL_TRIANGLE_STRIP, (slices+1)*2*stackNum, (slices+1)*2 );
	}

	glPolygonMode( GL_FRONT_AND_BACK, GL_FILL );
}

inline void CSCI441_INTERNAL::drawPartialDisk( GLdouble inner, GLdouble outer, GLint slices, GLint rings, GLdouble start, GLdouble sweep, GLenum renderMode ) {
	DiskData diskData = { inner, outer, start, sweep, slices, rings };
	if( CSCI441_INTERNAL::_diskVAO.find( diskData ) == CSCI441_INTERNAL::_diskVAO.end() ) {
		CSCI441_INTERNAL::generateDiskVAO( diskData );
	}

	glPolygonMode( GL_FRONT_AND_BACK, renderMode );
	glBindVertexArray( CSCI441_INTERNAL::_diskVAO.find( diskData )->second );
	glBindBuffer( GL_ARRAY_BUFFER, CSCI441_INTERNAL::_diskVBO.find( diskData )->second );
	glEnableVertexAttribArray( _positionLocation );
	glVertexAttribPointer( _positionLocation, 3, GL_DOUBLE, GL_FALSE, 0, (void*)0 );
	glEnableVertexAttribArray( _normalLocation );
	glVertexAttribPointer( _normalLocation, 3, GL_DOUBLE, GL_FALSE, 0, (void*)(sizeof(GLdouble)*rings * (slices+1) * 2*3) );
	glEnableVertexAttribArray( _texCoordLocation );
	glVertexAttribPointer( _texCoordLocation, 2, GL_DOUBLE, GL_FALSE, 0, (void*)(sizeof(GLdouble)*rings * (slices+1) * 2*6) );

	for( int ringNum = 0; ringNum < rings; ringNum++ ) {
		glDrawArrays( GL_TRIANGLE_STRIP, (slices+1)*2*ringNum, (slices+1)*2 );
	}

	glPolygonMode( GL_FRONT_AND_BACK, GL_FILL );
}

inline void CSCI441_INTERNAL::drawSphere( GLdouble radius, GLint stacks, GLint slices, GLenum renderMode ) {
	SphereData sphereData = { radius, stacks, slices };
	if( CSCI441_INTERNAL::_sphereVAO.find( sphereData ) == CSCI441_INTERNAL::_sphereVAO.end() ) {
		CSCI441_INTERNAL::generateSphereVAO( sphereData );
	}

	glPolygonMode( GL_FRONT_AND_BACK, renderMode );
	glBindVertexArray( CSCI441_INTERNAL::_sphereVAO.find( sphereData )->second );
	glBindBuffer( GL_ARRAY_BUFFER, CSCI441_INTERNAL::_sphereVBO.find( sphereData )->second );
	glEnableVertexAttribArray( _positionLocation );
	glVertexAttribPointer( _positionLocation, 3, GL_DOUBLE, GL_FALSE, 0, (void*)0 );
	glEnableVertexAttribArray( _normalLocation );
	glVertexAttribPointer( _normalLocation, 3, GL_DOUBLE, GL_FALSE, 0, (void*)(sizeof(GLdouble)*((slices + 2)*2 + ((stacks - 2)*(slices+1))*2) *3) );
	glEnableVertexAttribArray( _texCoordLocation );
	glVertexAttribPointer( _texCoordLocation, 2, GL_DOUBLE, GL_FALSE, 0, (void*)(sizeof(GLdouble)*((slices + 2)*2 + ((stacks - 2)*(slices+1))*2) *6) );

	glDrawArrays( GL_TRIANGLE_FAN, 0, slices+2 );

	for( int stackNum = 1; stackNum < stacks-1; stackNum++ ) {
		glDrawArrays( GL_TRIANGLE_STRIP, (slices+2) + (stackNum-1)*((slices+1)*2), (slices+1)*2 );
	}

	glDrawArrays( GL_TRIANGLE_FAN, (slices+2) + (stacks-2)*(slices+1)*2, slices+2 );

	glPolygonMode( GL_FRONT_AND_BACK, GL_FILL );
}

inline void CSCI441_INTERNAL::drawTorus( GLdouble innerRadius, GLdouble outerRadius, GLint sides, GLint rings, GLenum renderMode ) {
	TorusData torusData = { innerRadius, outerRadius, sides, rings };
	if( CSCI441_INTERNAL::_torusVAO.find( torusData ) == CSCI441_INTERNAL::_torusVAO.end() ) {
		CSCI441_INTERNAL::generateTorusVAO( torusData );
	}

	glPolygonMode( GL_FRONT_AND_BACK, renderMode );
	glBindVertexArray( CSCI441_INTERNAL::_torusVAO.find( torusData )->second );
	glBindBuffer( GL_ARRAY_BUFFER, CSCI441_INTERNAL::_torusVBO.find( torusData )->second );
	glEnableVertexAttribArray( _positionLocation );
	glVertexAttribPointer( _positionLocation, 3, GL_DOUBLE, GL_FALSE, 0, (void*)0 );
	glEnableVertexAttribArray( _normalLocation );
	glVertexAttribPointer( _normalLocation, 3, GL_DOUBLE, GL_FALSE, 0, (void*)(sizeof(GLdouble)*(sides*4*rings)*3) );
	glEnableVertexAttribArray( _texCoordLocation );
	glVertexAttribPointer( _texCoordLocation, 2, GL_DOUBLE, GL_FALSE, 0, (void*)(sizeof(GLdouble)*(sides*4*rings)*6) );

	for( int ringNum = 0; ringNum < rings; ringNum++ ) {
		glDrawArrays( GL_TRIANGLE_STRIP, ringNum*sides*4, sides*4 );
	}

	glPolygonMode( GL_FRONT_AND_BACK, GL_FILL );
}

inline void CSCI441_INTERNAL::generateCubeVAO( GLdouble sideLength ) {
	GLuint vaod;
	glGenVertexArrays( 1, &vaod );
	glBindVertexArray( vaod );

	GLuint vbod;
	glGenBuffers( 1, &vbod );
	glBindBuffer( GL_ARRAY_BUFFER, vbod );

	GLdouble cornerPoint = sideLength / 2.0f;

	GLdouble vertices[36][3] = {
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
	GLdouble texCoords[36][2] = {
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
	GLdouble normals[36][3] = {
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

	glBufferData( GL_ARRAY_BUFFER, sizeof(GLdouble) * 36 * 8, NULL, GL_STATIC_DRAW );
	glBufferSubData( GL_ARRAY_BUFFER, 0, sizeof(GLdouble) * 36 * 3, vertices );
	glBufferSubData( GL_ARRAY_BUFFER, sizeof(GLdouble) * 36 * 3, sizeof(GLdouble) * 36 * 3, normals );
	glBufferSubData( GL_ARRAY_BUFFER, sizeof(GLdouble) * 36 * 6, sizeof(GLdouble) * 36 * 2, texCoords );

	CSCI441_INTERNAL::_cubeVAO.insert( std::pair<GLdouble, GLuint>( sideLength, vaod ) );
	CSCI441_INTERNAL::_cubeVBO.insert( std::pair<GLdouble, GLuint>( sideLength, vbod ) );
}

inline void CSCI441_INTERNAL::generateCylinderVAO( CylinderData cylData ) {
	GLuint vaod;
	glGenVertexArrays( 1, &vaod );
	glBindVertexArray( vaod );

	GLuint vbod;
	glGenBuffers( 1, &vbod );
	glBindBuffer( GL_ARRAY_BUFFER, vbod );

	unsigned long int numVertices = cylData.st * (cylData.sl+1) * 2;

	double sliceStep = 2.0 * M_PI / cylData.sl;
	double stackStep = (double)cylData.h / cylData.st;

	GLdouble* vertices = (GLdouble*)malloc(sizeof(GLdouble)*numVertices*3);
	GLdouble* texCoords = (GLdouble*)malloc(sizeof(GLdouble)*numVertices*2);
	GLdouble* normals = (GLdouble*)malloc(sizeof(GLdouble)*numVertices*3);

	unsigned long int idx = 0;

	for( int stackNum = 0; stackNum < cylData.st; stackNum++ ) {
		GLdouble botRadius = cylData.b*(cylData.st-stackNum)/cylData.st + cylData.t*stackNum/cylData.st;
		GLdouble topRadius = cylData.b*(cylData.st-stackNum-1)/cylData.st + cylData.t*(stackNum+1)/cylData.st;

		for( int sliceNum = 0; sliceNum <= cylData.sl; sliceNum++ ) {
			normals[ idx*3 + 0 ] = cos( sliceNum * sliceStep );
			normals[ idx*3 + 1 ] = 0.0f;
			normals[ idx*3 + 2 ] = sin( sliceNum * sliceStep );

			texCoords[ idx*2 + 0 ] = (double)sliceNum / cylData.sl;
			texCoords[ idx*2 + 1 ] = (double)stackNum / cylData.st;

			vertices[ idx*3 + 0 ] = cos( sliceNum * sliceStep )*botRadius;
			vertices[ idx*3 + 1 ] = stackNum * stackStep;
			vertices[ idx*3 + 2 ] = sin( sliceNum * sliceStep )*botRadius;

			idx++;

			normals[ idx*3 + 0 ] = cos( sliceNum * sliceStep );
			normals[ idx*3 + 1 ] = 0.0f;
			normals[ idx*3 + 2 ] = sin( sliceNum * sliceStep );

			texCoords[ idx*2 + 0 ] = (double)sliceNum / cylData.sl;
			texCoords[ idx*2 + 1 ] = (double)(stackNum+1) / cylData.st;

			vertices[ idx*3 + 0 ] = cos( sliceNum * sliceStep )*topRadius;
			vertices[ idx*3 + 1 ] = (stackNum+1) * stackStep;
			vertices[ idx*3 + 2 ] = sin( sliceNum * sliceStep )*topRadius;

			idx++;
		}
	}

	glBufferData( GL_ARRAY_BUFFER, sizeof(GLdouble) * numVertices * 8, NULL, GL_STATIC_DRAW );
	glBufferSubData( GL_ARRAY_BUFFER, 0, 																  sizeof(GLdouble) * numVertices * 3, vertices );
	glBufferSubData( GL_ARRAY_BUFFER, sizeof(GLdouble) * numVertices * 3, sizeof(GLdouble) * numVertices * 3, normals );
	glBufferSubData( GL_ARRAY_BUFFER, sizeof(GLdouble) * numVertices * 6, sizeof(GLdouble) * numVertices * 2, texCoords );

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

	double sliceStep = diskData.sw / diskData.sl;
	double ringStep = (diskData.o - diskData.i) / diskData.r;

	GLdouble* vertices = (GLdouble*)malloc(sizeof(GLdouble)*numVertices*3);
	GLdouble* texCoords = (GLdouble*)malloc(sizeof(GLdouble)*numVertices*2);
	GLdouble* normals = (GLdouble*)malloc(sizeof(GLdouble)*numVertices*3);

	unsigned long int idx = 0;

	for( int ringNum = 0; ringNum < diskData.r; ringNum++ ) {
		double currRadius = diskData.i + ringNum*ringStep;
		double nextRadius = diskData.i + (ringNum+1)*ringStep;

		double theta = diskData.st;
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

	glBufferData( GL_ARRAY_BUFFER, sizeof(GLdouble) * numVertices * 8, NULL, GL_STATIC_DRAW );
	glBufferSubData( GL_ARRAY_BUFFER, 0, 																  sizeof(GLdouble) * numVertices * 3, vertices );
	glBufferSubData( GL_ARRAY_BUFFER, sizeof(GLdouble) * numVertices * 3, sizeof(GLdouble) * numVertices * 3, normals );
	glBufferSubData( GL_ARRAY_BUFFER, sizeof(GLdouble) * numVertices * 6, sizeof(GLdouble) * numVertices * 2, texCoords );

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

	double sliceStep = 2.0 * M_PI / sphereData.sl;
	double stackStep = M_PI / sphereData.st;

	GLdouble* vertices = (GLdouble*)malloc(sizeof(GLdouble)*numVertices*3);
	GLdouble* texCoords = (GLdouble*)malloc(sizeof(GLdouble)*numVertices*2);
	GLdouble* normals = (GLdouble*)malloc(sizeof(GLdouble)*numVertices*3);

	unsigned long int idx = 0;

	// sphere top
	double phi = stackStep * sphereData.st;
	double phiNext = stackStep * (sphereData.st-1);

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
		double theta = sliceStep * sliceNum;

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
		double phi = stackStep * stackNum;
		double phiNext = stackStep * (stackNum + 1);

		for( int sliceNum = sphereData.sl; sliceNum >= 0; sliceNum-- ) {
			double theta = sliceStep * sliceNum;

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
		double theta = sliceStep * sliceNum;

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

	glBufferData( GL_ARRAY_BUFFER, sizeof(GLdouble) * numVertices * 8, NULL, GL_STATIC_DRAW );
	glBufferSubData( GL_ARRAY_BUFFER, 0, 																  sizeof(GLdouble) * numVertices * 3, vertices );
	glBufferSubData( GL_ARRAY_BUFFER, sizeof(GLdouble) * numVertices * 3, sizeof(GLdouble) * numVertices * 3, normals );
	glBufferSubData( GL_ARRAY_BUFFER, sizeof(GLdouble) * numVertices * 6, sizeof(GLdouble) * numVertices * 2, texCoords );

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

	GLdouble* vertices = (GLdouble*)malloc(sizeof(GLdouble)*numVertices*3);
	GLdouble* texCoords = (GLdouble*)malloc(sizeof(GLdouble)*numVertices*2);
	GLdouble* normals = (GLdouble*)malloc(sizeof(GLdouble)*numVertices*3);

	unsigned long int idx = 0;

	double sideStep = 2.0 * M_PI / torusData.s;
	double ringStep = 2.0 * M_PI / torusData.r;

	for( int ringNum = 0; ringNum < torusData.r; ringNum++ ) {
		double currTheta = ringStep * ringNum;
		double nextTheta = ringStep * (ringNum+1);

		for( int sideNum = 0; sideNum < torusData.s; sideNum++ ) {
			double currPhi = sideStep * sideNum;
			double nextPhi = sideStep * (sideNum+1);

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

	glBufferData( GL_ARRAY_BUFFER, sizeof(GLdouble) * numVertices * 8, NULL, GL_STATIC_DRAW );
	glBufferSubData( GL_ARRAY_BUFFER, 0, 																  sizeof(GLdouble) * numVertices * 3, vertices );
	glBufferSubData( GL_ARRAY_BUFFER, sizeof(GLdouble) * numVertices * 3, sizeof(GLdouble) * numVertices * 3, normals );
	glBufferSubData( GL_ARRAY_BUFFER, sizeof(GLdouble) * numVertices * 6, sizeof(GLdouble) * numVertices * 2, texCoords );

	CSCI441_INTERNAL::_torusVAO.insert( std::pair<TorusData, GLuint>( torusData, vaod ) );
	CSCI441_INTERNAL::_torusVBO.insert( std::pair<TorusData, GLuint>( torusData, vbod ) );
}

#endif // __CSCI441_OBJECTS_3_HPP__
#endif // #ifndef __CSCI441_OBJECTS_HPP__
