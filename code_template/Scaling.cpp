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
Matrix4 Scaling::getScalingMatrix()
{
    Matrix4 result;
    result.m[0][0] = sx;
    result.m[0][1] = 0.0;
    result.m[0][2] = 0.0;
    result.m[0][3] = 0.0;
    result.m[1][0] = 0.0;
    result.m[1][1] = sy;
    result.m[1][2] = 0.0;
    result.m[1][3] = 0.0;
    result.m[2][0] = 0.0;
    result.m[2][1] = 0.0;
    result.m[2][2] = sz;
    result.m[2][3] = 0.0;
    result.m[3][0] = 0.0;
    result.m[3][1] = 0.0;
    result.m[3][2] = 0.0;
    result.m[3][3] = 1.0;
    return result;
}

ostream &operator<<(ostream &os, const Scaling &s)
{
    os << fixed << setprecision(3) << "Scaling " << s.scalingId << " => [" << s.sx << ", " << s.sy << ", " << s.sz << "]";

    return os;
}
