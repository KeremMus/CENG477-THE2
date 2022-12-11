#include "Rotation.h"
#include <iostream>
#include <iomanip>
#include "Helpers.h"
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
    Vec3 v;
    Vec3 u = Vec3(this->ux, this->uy, this->uz, -1);
    u = normalizeVec3(u);
    if (u.x < u.y && u.x < u.z) {
        v = Vec3(0, u.z, -u.y, -1);
    } else if (u.y < u.x && u.y < u.z) {
        v = Vec3(-u.z, 0, u.x, -1);
    } else {
        v = Vec3(u.y, -u.x, 0, -1);
    }
    v = normalizeVec3(v);
    Vec3 w = crossProductVec3(u, v);
    w = normalizeVec3(w);
    Matrix4 M = getIdentityMatrix();
    M.val[0][0] = u.x;
    M.val[0][1] = u.y;
    M.val[0][2] = u.z;
    M.val[1][0] = v.x;
    M.val[1][1] = v.y;
    M.val[1][2] = v.z;
    M.val[2][0] = w.x;
    M.val[2][1] = w.y;
    M.val[2][2] = w.z;

    Matrix4 M_inverse = getIdentityMatrix();
    M_inverse.val[0][0] = u.x;
    M_inverse.val[0][1] = v.x;
    M_inverse.val[0][2] = w.x;
    M_inverse.val[1][0] = u.y;
    M_inverse.val[1][1] = v.y;
    M_inverse.val[1][2] = w.y;
    M_inverse.val[2][0] = u.z;
    M_inverse.val[2][1] = v.z;
    M_inverse.val[2][2] = w.z;

    Matrix4 R = getIdentityMatrix();
    R.val[1][1] = cos(this->angle);
    R.val[1][2] = -sin(this->angle);
    R.val[2][1] = sin(this->angle);
    R.val[2][2] = cos(this->angle);

    Matrix4 temp = multiplyMatrixWithMatrix(M_inverse, R);
    Matrix4 result = multiplyMatrixWithMatrix(temp, M);
    return result;

}

ostream &operator<<(ostream &os, const Rotation &r)
{
    os << fixed << setprecision(3) << "Rotation " << r.rotationId << " => [angle=" << r.angle << ", " << r.ux << ", " << r.uy << ", " << r.uz << "]";

    return os;
}