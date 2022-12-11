#include "Scaling.h"
#include <iostream>
#include <iomanip>

using namespace std;

Scaling::Scaling() {}

Scaling::Scaling(int scalingId, double sx, double sy, double sz)
{
    this->scalingId = scalingId;
    this->sx = sx;
    this->sy = sy;
    this->sz = sz;
}
Matrix4 Scaling::getScalingMatrix(Vec4 v)
{
    Matrix4 result;
    result.val[0][0] = sx;
    result.val[0][1] = 0.0;
    result.val[0][2] = 0.0;
    result.val[0][3] = 0;
    result.val[1][0] = 0.0;
    result.val[1][1] = sy;
    result.val[1][2] = 0.0;
    result.val[1][3] = 0;
    result.val[2][0] = 0.0;
    result.val[2][1] = 0.0;
    result.val[2][2] = sz;
    result.val[2][3] = 0;
    result.val[3][0] = 0.0;
    result.val[3][1] = 0.0;
    result.val[3][2] = 0.0;
    result.val[3][3] = 1.0;
    return result;
}

ostream &operator<<(ostream &os, const Scaling &s)
{
    os << fixed << setprecision(3) << "Scaling " << s.scalingId << " => [" << s.sx << ", " << s.sy << ", " << s.sz << "]";

    return os;
}
