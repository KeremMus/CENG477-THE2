#include "Rotation.h"
#include <iostream>
#include <iomanip>

using namespace std;

Rotation::Rotation() {}

Rotation::Rotation(int rotationId, double angle, double x, double y, double z)
{
    this->rotationId = rotationId;
    this->angle = angle;
    this->ux = x;
    this->uy = y;
    this->uz = z;
}
Matrix4 Rotation::getRotationMatrix() {
    Matrix4 result;
    result.val[0][0] = ux * ux * (1 - cos(angle)) + cos(angle);
    result.val[0][1] = ux * uy * (1 - cos(angle)) - uz * sin(angle);
    result.val[0][2] = ux * uz * (1 - cos(angle)) + uy * sin(angle);
    result.val[0][3] = 0.0;
    result.val[1][0] = uy * ux * (1 - cos(angle)) + uz * sin(angle);
    result.val[1][1] = uy * uy * (1 - cos(angle)) + cos(angle);
    result.val[1][2] = uy * uz * (1 - cos(angle)) - ux * sin(angle);
    result.val[1][3] = 0.0;
    result.val[2][0] = uz * ux * (1 - cos(angle)) - uy * sin(angle);
    result.val[2][1] = uz * uy * (1 - cos(angle)) + ux * sin(angle);
    result.val[2][2] = uz * uz * (1 - cos(angle)) + cos(angle);
    result.val[2][3] = 0.0;
    result.val[3][0] = 0.0;
    result.val[3][1] = 0.0;
    result.val[3][2] = 0.0;
    result.val[3][3] = 1.0;
    return result;
}


ostream &operator<<(ostream &os, const Rotation &r)
{
    os << fixed << setprecision(3) << "Rotation " << r.rotationId << " => [angle=" << r.angle << ", " << r.ux << ", " << r.uy << ", " << r.uz << "]";

    return os;
}