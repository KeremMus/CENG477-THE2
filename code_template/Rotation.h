#ifndef __ROTATION_H__
#define __ROTATION_H__

#include <iostream>

using namespace std;

class Rotation
{
public:
    int rotationId;
    double angle, ux, uy, uz;

    Rotation();
    Rotation(int rotationId, double angle, double x, double y, double z);
    Matrix4 getRotationMatrix();
    // apply rotation to a Vector3
    Vec3 applyRotation(Vec3 v);

    friend ostream &operator<<(ostream &os, const Rotation &r);
};

#endif