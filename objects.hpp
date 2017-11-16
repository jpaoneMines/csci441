/** @file objects.hpp
  * @brief Helper functions to draw 3D OpenGL 2.1 objects
	* @author Dr. Jeffrey Paone
	* @date Last Edit: 25 Oct 2017
	* @version 1.3
	*
	* @copyright MIT License Copyright (c) 2017 Dr. Jeffrey Paone
	*
	*	These functions draw solid (or wireframe) 3D closed OpenGL
	*	objects.  All objects are constructed using triangles that
	*	have normals and texture coordinates properly set.
	*
	*	@warning NOTE: This header file will only work with OpenGL 2.1
  */

#ifdef __CSCI441_OBJECTS_3_HPP__
#error cannot include both CSCI441/objects.h and CSCI441/objects3.h
#else

#ifndef __CSCI441_OBJECTS_HPP__
#define __CSCI441_OBJECTS_HPP__

#ifdef __APPLE__
	#include <OpenGL/gl.h>
#else
	#include <GL/gl.h>
#endif

#include <assert.h>   // for assert()
#include <math.h>			// for cos(), sin()

#include <CSCI441/teapot.hpp> // for teapot()

////////////////////////////////////////////////////////////////////////////////////

/** @namespace CSCI441
  * @brief CSCI441 Helper Functions for OpenGL
	*/
namespace CSCI441 {
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
}

////////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////
// Outward facing function implementations

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

	CSCI441_INTERNAL::teapot( 8, size, GL_FILL, false );
}

inline void CSCI441::drawWireTeapot( GLdouble size ) {
	assert( size > 0.0f );

	CSCI441_INTERNAL::teapot( 8, size, GL_LINE, false );
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
	GLdouble cornerPoint = sideLength / 2.0f;

  glPushAttrib( GL_POLYGON_BIT ); {

		glPolygonMode( GL_FRONT_AND_BACK, renderMode );

		// Left Face
	  glBegin( GL_TRIANGLE_STRIP ); {
	    glNormal3f( -1.0f, 0.0f, 0.0f );
			glTexCoord2f( 0.0f, 0.0f ); glVertex3f( -cornerPoint, -cornerPoint, -cornerPoint );
			glTexCoord2f( 1.0f, 0.0f ); glVertex3f( -cornerPoint, -cornerPoint,  cornerPoint );
			glTexCoord2f( 0.0f, 1.0f ); glVertex3f( -cornerPoint,  cornerPoint, -cornerPoint );
			glTexCoord2f( 1.0f, 1.0f ); glVertex3f( -cornerPoint,  cornerPoint,  cornerPoint );
	  }; glEnd();

		// Right Face
	  glBegin( GL_TRIANGLE_STRIP ); {
	    glNormal3f(  1.0f, 0.0f, 0.0f );
			glTexCoord2f( 0.0f, 1.0f ); glVertex3f(  cornerPoint,  cornerPoint,  cornerPoint );
			glTexCoord2f( 0.0f, 0.0f ); glVertex3f(  cornerPoint, -cornerPoint,  cornerPoint );
			glTexCoord2f( 1.0f, 1.0f ); glVertex3f(  cornerPoint,  cornerPoint, -cornerPoint );
			glTexCoord2f( 1.0f, 0.0f ); glVertex3f(  cornerPoint, -cornerPoint, -cornerPoint );
	  }; glEnd();

		// Top Face
	  glBegin( GL_TRIANGLE_STRIP ); {
	    glNormal3f(  0.0f, 1.0f, 0.0f );
			glTexCoord2f( 1.0f, 0.0f ); glVertex3f( -cornerPoint,  cornerPoint, -cornerPoint );
			glTexCoord2f( 1.0f, 1.0f ); glVertex3f( -cornerPoint,  cornerPoint,  cornerPoint );
			glTexCoord2f( 0.0f, 0.0f ); glVertex3f(  cornerPoint,  cornerPoint, -cornerPoint );
			glTexCoord2f( 0.0f, 1.0f ); glVertex3f(  cornerPoint,  cornerPoint,  cornerPoint );
	  }; glEnd();

		// Bottom Face
	  glBegin( GL_TRIANGLE_STRIP ); {
	    glNormal3f(  0.0f, -1.0f, 0.0f );
			glTexCoord2f( 1.0f, 0.0f ); glVertex3f(  cornerPoint, -cornerPoint,  cornerPoint );
			glTexCoord2f( 1.0f, 1.0f ); glVertex3f( -cornerPoint, -cornerPoint,  cornerPoint );
			glTexCoord2f( 0.0f, 0.0f ); glVertex3f(  cornerPoint, -cornerPoint, -cornerPoint );
			glTexCoord2f( 0.0f, 1.0f ); glVertex3f( -cornerPoint, -cornerPoint, -cornerPoint );
	  }; glEnd();

		// Front Face
	  glBegin( GL_TRIANGLE_STRIP ); {
	    glNormal3f(  0.0f, 0.0f, 1.0f );
			glTexCoord2f( 0.0f, 0.0f ); glVertex3f( -cornerPoint, -cornerPoint,  cornerPoint );
			glTexCoord2f( 1.0f, 0.0f ); glVertex3f(  cornerPoint, -cornerPoint,  cornerPoint );
			glTexCoord2f( 0.0f, 1.0f ); glVertex3f( -cornerPoint,  cornerPoint,  cornerPoint );
			glTexCoord2f( 1.0f, 1.0f ); glVertex3f(  cornerPoint,  cornerPoint,  cornerPoint );
	  }; glEnd();

		// Back Face
	  glBegin( GL_TRIANGLE_STRIP ); {
	    glNormal3f(  0.0f, 0.0f, -1.0f );
			glTexCoord2f( 0.0f, 1.0f ); glVertex3f(  cornerPoint,  cornerPoint, -cornerPoint );
			glTexCoord2f( 0.0f, 0.0f ); glVertex3f(  cornerPoint, -cornerPoint, -cornerPoint );
			glTexCoord2f( 1.0f, 1.0f ); glVertex3f( -cornerPoint,  cornerPoint, -cornerPoint );
			glTexCoord2f( 1.0f, 0.0f ); glVertex3f( -cornerPoint, -cornerPoint, -cornerPoint );
	  }; glEnd();

	}; glPopAttrib();
}

inline void CSCI441_INTERNAL::drawCylinder( GLdouble base, GLdouble top, GLdouble height, GLint stacks, GLint slices, GLenum renderMode ) {
	double sliceStep = 2.0 * M_PI / slices;
	double stackStep = height / stacks;

	glPushAttrib( GL_POLYGON_BIT ); {

		glPolygonMode( GL_FRONT_AND_BACK, renderMode );

		for( int stackNum = 0; stackNum < stacks; stackNum++ ) {
			GLdouble botRadius = base*(stacks-stackNum)/stacks + top*stackNum/stacks;
			GLdouble topRadius = base*(stacks-stackNum-1)/stacks + top*(stackNum+1)/stacks;

			glBegin( GL_TRIANGLE_STRIP ); {
				for( int sliceNum = 0; sliceNum <= slices; sliceNum++ ) {
					glNormal3f( cos( sliceNum * sliceStep ), 0.0f, sin( sliceNum * sliceStep ) );

					glTexCoord2f( (double)sliceNum / slices, (double)stackNum / stacks );
					glVertex3f( cos( sliceNum * sliceStep )*botRadius, stackNum     * stackStep, sin( sliceNum * sliceStep )*botRadius );

					glTexCoord2f( (double)sliceNum / slices, (double)(stackNum+1) / stacks );
					glVertex3f( cos( sliceNum * sliceStep )*topRadius, (stackNum+1) * stackStep, sin( sliceNum * sliceStep )*topRadius );
				}
			}; glEnd();
		}

	}; glPopAttrib();
}

inline void CSCI441_INTERNAL::drawPartialDisk( GLdouble inner, GLdouble outer, GLint slices, GLint rings, GLdouble start, GLdouble sweep, GLenum renderMode ) {
	double sliceStep = sweep / slices;
	double ringStep = (outer - inner) / rings;

	glPushAttrib( GL_POLYGON_BIT ); {

		glPolygonMode( GL_FRONT_AND_BACK, renderMode );

		for( int ringNum = 0; ringNum < rings; ringNum++ ) {
			double currRadius = inner + ringNum*ringStep;
			double nextRadius = inner + (ringNum+1)*ringStep;

			glBegin( GL_TRIANGLE_STRIP ); {
				glNormal3f( 0.0f, 0.0f, 1.0f );

				double theta = start;
				for( int i = 0; i <= slices; i++, theta += sliceStep ) {
					glTexCoord2f( cos(theta)*(currRadius/outer), sin(theta)*(currRadius/outer) );
					glVertex3f( cos(theta)*currRadius, sin(theta)*currRadius, 0.0f );

					glTexCoord2f( cos(theta)*(nextRadius/outer), sin(theta)*(nextRadius/outer) );
					glVertex3f( cos(theta)*nextRadius, sin(theta)*nextRadius, 0.0f );
				}
			}; glEnd();
		}

	}; glPopAttrib();
}

inline void CSCI441_INTERNAL::drawSphere( GLdouble radius, GLint stacks, GLint slices, GLenum renderMode ) {
	double sliceStep = 2.0 * M_PI / slices;
	double stackStep = M_PI / stacks;

	glPushAttrib( GL_POLYGON_BIT ); {

		glPolygonMode( GL_FRONT_AND_BACK, renderMode );

		// sphere top
		glBegin( GL_TRIANGLE_FAN ); {
			double phi = stackStep * stacks;
			double phiNext = stackStep * (stacks-1);

			glNormal3f( 0.0f, 1.0f, 0.0f );
			glTexCoord2f( 0.5f, 1.0f );
			glVertex3f( 0.0f, -cos( phi )*radius, 0.0f );

			for( int sliceNum = 0; sliceNum <= slices; sliceNum++ ) {
				double theta = sliceStep * sliceNum;

				glNormal3f( -cos( theta )*sin( phiNext ),        -cos( phiNext ),        sin( theta )*sin( phiNext )        );
				glTexCoord2f( (stacks-1.0f) / stacks, sliceNum / slices );
				glVertex3f( -cos( theta )*sin( phiNext )*radius, -cos( phiNext )*radius, sin( theta )*sin( phiNext )*radius );
			}
		}; glEnd();

		// sphere stacks
		for( int stackNum = 1; stackNum < stacks-1; stackNum++ ) {
			double phi = stackStep * stackNum;
			double phiNext = stackStep * (stackNum + 1);

			glBegin( GL_TRIANGLE_STRIP ); {
				for( int sliceNum = slices; sliceNum >= 0; sliceNum-- ) {
					double theta = sliceStep * sliceNum;

					glNormal3f( -cos( theta )*sin( phi ),            -cos( phi ),     sin( theta )*sin( phi )            );
					glTexCoord2f( stackNum / sphereData.st,     sliceNum / sphereData.sl );
					glVertex3f( -cos( theta )*sin( phi )*radius,     -cos( phi )*radius,     sin( theta )*sin( phi )*radius     );

					glNormal3f( -cos( theta )*sin( phiNext ),        -cos( phiNext ), sin( theta )*sin( phiNext )        );
					glTexCoord2f( (stackNum+1) / sphereData.st, sliceNum / sphereData.sl );
					glVertex3f( -cos( theta )*sin( phiNext )*radius, -cos( phiNext )*radius, sin( theta )*sin( phiNext )*radius );
				}
			}; glEnd();
		}

		// sphere bottom
		glBegin( GL_TRIANGLE_FAN ); {
			double phi = 0;
			double phiNext = stackStep;

			glNormal3f( 0.0f, -1.0f, 0.0f );
			glTexCoord2f( 0.5f, 0.0f );
			glVertex3f( 0.0f, -cos( phi )*radius, 0.0f );

			for( int sliceNum = slices; sliceNum >= 0; sliceNum-- ) {
				double theta = sliceStep * sliceNum;

				glNormal3f( -cos( theta )*sin( phiNext ),        -cos( phiNext ),        sin( theta )*sin( phiNext )        );
				glTexCoord2f( 1.0f / stacks, sliceNum / slices );
				glVertex3f( -cos( theta )*sin( phiNext )*radius, -cos( phiNext )*radius, sin( theta )*sin( phiNext )*radius );
			}
		}; glEnd();

	}; glPopAttrib();
}

inline void CSCI441_INTERNAL::drawTorus( GLdouble innerRadius, GLdouble outerRadius, GLint sides, GLint rings, GLenum renderMode ) {
	double sideStep = 2.0 * M_PI / sides;
	double ringStep = 2.0 * M_PI / rings;

	glPushAttrib( GL_POLYGON_BIT ); {

		glPolygonMode( GL_FRONT_AND_BACK, renderMode );

		for( int ringNum = 0; ringNum < rings; ringNum++ ) {
			double currTheta = ringStep * ringNum;
			double nextTheta = ringStep * (ringNum+1);

			glBegin( GL_TRIANGLE_STRIP ); {
				for( int sideNum = 0; sideNum < sides; sideNum++ ) {
					double currPhi = sideStep * sideNum;
					double nextPhi = sideStep * (sideNum+1);

					glNormal3f( cos( currPhi ) * cos( currTheta ), cos( currPhi ) * sin( currTheta ), sin( currPhi ) );
					glTexCoord2f( cos( currPhi ) * cos( currTheta ), cos( currPhi ) * sin( currTheta ) );
					glVertex3f( ( outerRadius + innerRadius * cos( currPhi ) ) * cos( currTheta ), ( outerRadius + innerRadius * cos( currPhi ) ) * sin( currTheta ), innerRadius * sin( currPhi ) );

					glNormal3f( cos( currPhi ) * cos( nextTheta ), cos( currPhi ) * sin( nextTheta ), sin( currPhi ) );
					glTexCoord2f( cos( currPhi ) * cos( nextTheta ), cos( currPhi ) * sin( nextTheta ) );
					glVertex3f( ( outerRadius + innerRadius * cos( currPhi ) ) * cos( nextTheta ), ( outerRadius + innerRadius * cos( currPhi ) ) * sin( nextTheta ), innerRadius * sin( currPhi ) );

					glNormal3f( cos( nextPhi ) * cos( currTheta ), cos( nextPhi ) * sin( currTheta ), sin( nextPhi ) );
					glTexCoord2f( cos( nextPhi ) * cos( currTheta ), cos( nextPhi ) * sin( currTheta ) );
					glVertex3f( ( outerRadius + innerRadius * cos( nextPhi ) ) * cos( currTheta ), ( outerRadius + innerRadius * cos( nextPhi ) ) * sin( currTheta ), innerRadius * sin( nextPhi ) );

					glNormal3f( cos( nextPhi ) * cos( nextTheta ), cos( nextPhi ) * sin( nextTheta ), sin( nextPhi ) );
					glTexCoord2f( cos( nextPhi ) * cos( nextTheta ), cos( nextPhi ) * sin( nextTheta ) );
					glVertex3f( ( outerRadius + innerRadius * cos( nextPhi ) ) * cos( nextTheta ), ( outerRadius + innerRadius * cos( nextPhi ) ) * sin( nextTheta ), innerRadius * sin( nextPhi ) );
				}
			}; glEnd();
		}

	}; glPopAttrib();
}

#endif // __CSCI441_OBJECTS_HPP__
#endif // #ifndef __CSCI441_OBJECTS_3_HPP__
