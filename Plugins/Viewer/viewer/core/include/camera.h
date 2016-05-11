#ifndef CAMERA_H
#define CAMERA_H

#define _USE_MATH_DEFINES 1
#include "GL/glew.h"
#include "point.h"
#include "vector.h"
#include "box.h"
#include <QMatrix4x4>

/*!
	\class Camera
	\brief The %Camera class represents a perspective camera.
*/

class CORE_EXPORT Camera
{
public:
	/*!
	Initializes the camera parameters from a bounding box of the scene.
	The camera is placed outside the box, ensuring that the whole box fits
	within the viewing frustum. 
	Then sets the GL_MODELVIEW and GL_PROJECTION matrices.
	*/
    void init(const Box& b);


	/*!
	Returns a 4x4 matrix representing the viewing transform of the camera.
	*/
    QMatrix4x4 modelviewMatrix() const;

	/*!
	Returns a 4x4 matrix representing the projection transform of the camera.
	*/
    QMatrix4x4 projectionMatrix() const;

    /*!
	Returns the camera (eye) position.
	*/
    Point getObs() const;

	/*!
	Returns znear ( distance to the near clipping plane)
	*/
    float znear() const;

	/*!
	Returns zfar ( distance to the far clipping plane)
	*/
    float zfar() const;

	/*!
	Sets the camera aspect ratio.
	*/    
    void setAspectRatio(float ar);

	/*!
	Recomputes the near, far clipping planes according to the given bounding box.
	*/ 
    void updateClippingPlanes(const Box&);
    
	/*!
	Moves the camera away (inc>0) or towards (inc<0) the current VRP.
	*/
    void incrementDistance(float inc);

	/*!
	Sets the distance to the current VRP.
	*/
    void setDistance(float value);

	/*!
	Rotates the camera by increasing the rotation angle around X axis (pitch).
	*/
    void incrementAngleX(float inc);

	/*!
	Rotates the camera by setting the rotation angle around X axis (pitch).
	*/
    void setAngleX(float value);

	/*!
	Rotates the camera by increasing the rotation angle around Y axis (yaw).
	*/
    void incrementAngleY(float inc);

	/*!
	Rotates the camera by setting the rotation angle around Y axis (yaw).
	*/
    void setAngleY(float value);

	/*!
	Rotates the camera by setting the rotation angle around Z axis (roll).
	*/
    void setAngleZ(float value);

	/*!
	Returns v=(x,y,z) with the Euler angles of the camera. 
    Rotation part of the viewing matrix is Rotz(-v.z)*Rotx(v.x)*Roty(-v.y)
	*/
    Vector eulerAngles() const; 

	/*!
	Offsets the camera position and VRP.
	*/     
    void pan(const Vector& offset); 

private:
    Point pvrp;  // view reference point
    float pdist; // distance obs-vrp
    float pangleX, pangleY, pangleZ;  //  Euler angles
    float pfovy; // fielf of view, vertical
    float paspectRatio; // aspect ratio
    float pzNear, pzFar; // clipping planes
};

#endif

