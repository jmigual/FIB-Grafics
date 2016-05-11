#include "camera.h"
#include <cmath>
#include <QMatrix4x4>
#include <iostream>
using namespace std;

void Camera::init(const Box& box)
{
    Point center = box.center();
    float radius = box.radius();

    pvrp = center;
    pdist = 2*radius;
    pfovy = 60; // 2 * asin (radi/2*radi)
    pzNear = radius;
    pzFar = 3*radius;

    pangleX = 0;
    pangleY = 0;
    pangleZ = 0;

    GLint view[4];
    glGetIntegerv(GL_VIEWPORT, view);
    paspectRatio = float(view[2])/float(view[3]);

}

QMatrix4x4 Camera::modelviewMatrix() const
{
    QMatrix4x4 viewing;
    viewing.translate(0,0,-pdist);
    viewing.rotate(-pangleZ,0,0,1);
    viewing.rotate( pangleX,1,0,0);
    viewing.rotate(-pangleY,0,1,0);
    viewing.translate(-pvrp.x(),-pvrp.y(),-pvrp.z());
    return viewing;
}

QMatrix4x4  Camera::projectionMatrix() const
{
    QMatrix4x4 P;
    float realFovy = pfovy;
    if (paspectRatio < 1.0) 
      realFovy = 360.0/M_PI*atan(tan(pfovy*M_PI/360)/paspectRatio);
    P.perspective(realFovy, paspectRatio, pzNear, pzFar);
    return P;
}

Point Camera::getObs() const
{
    QMatrix4x4 viewing = modelviewMatrix();
    QMatrix4x4 inv = viewing.inverted(); 
    return QVector3D(inv*QVector4D(0.0, 0.0, 0.0, 1.0));
}

void Camera::setAspectRatio(float ar)
{
    paspectRatio = ar;
}

void Camera::incrementDistance(float inc)
{
    pdist += inc;
}

void Camera::incrementAngleX(float inc)
{
    pangleX += inc;
}

void Camera::incrementAngleY(float inc)
{
    pangleY += inc;
}



void Camera::setDistance(float value)
{
    pdist = value;;
}

void Camera::setAngleX(float value)
{
    pangleX =value;
}

void Camera::setAngleY(float value)
{
    pangleY =value;
}

void Camera::setAngleZ(float value)
{
    pangleZ =value;
}

Vector Camera::eulerAngles() const
{
    return Vector(pangleX, pangleY, pangleZ);
}



void Camera::pan(const Vector& offset)
{
    pvrp = pvrp + offset;
}

void Camera::updateClippingPlanes(const Box& box)
{
    Point obs = getObs();
    Vector v = pvrp - obs;
    v.normalize();
    Vector u = box.center()-obs;
    pzNear = Vector::dotProduct(u,v)-box.radius();
    if (pzNear < 0.1f) pzNear = 0.1f;
    pzFar = Vector::dotProduct(u,v)+box.radius();
}

float Camera::znear() const
{
    return pzNear;
}

float Camera::zfar() const
{
    return pzFar;
}


