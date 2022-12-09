#include "Translation.h"
#include <iostream>
#include <iomanip>

using namespace std;

Translation::Translation()
{
    this->translationId = -1;
    this->tx = 0.0;
    this->ty = 0.0;
    this->tz = 0.0;
}

Translation::Translation(int translationId, double tx, double ty, double tz)
{
    this->translationId = translationId;
    this->tx = tx;
    this->ty = ty;
    this->tz = tz;
}
Matrix4 Translation::getTranslationMatrix()
{
    Matrix4 result;
    result.m[0][0] = 1.0;
    result.m[0][1] = 0.0;
    result.m[0][2] = 0.0;
    result.m[0][3] = tx;
    result.m[1][0] = 0.0;
    result.m[1][1] = 1.0;
    result.m[1][2] = 0.0;
    result.m[1][3] = ty;
    result.m[2][0] = 0.0;
    result.m[2][1] = 0.0;
    result.m[2][2] = 1.0;
    result.m[2][3] = tz;
    result.m[3][0] = 0.0;
    result.m[3][1] = 0.0;
    result.m[3][2] = 0.0;
    result.m[3][3] = 1.0;
    return result;
}

ostream &operator<<(ostream &os, const Translation &t)
{
    os << fixed << setprecision(3) << "Translation " << t.translationId << " => [" << t.tx << ", " << t.ty << ", " << t.tz << "]";

    return os;
}