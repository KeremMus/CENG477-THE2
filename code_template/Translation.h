#ifndef __TRANSLATION_H__
#define __TRANSLATION_H__

#include <iostream>

using namespace std;

class Translation
{
public:
    int translationId;
    double tx, ty, tz;

    Translation();
    Translation(int translationId, double tx, double ty, double tz);
    Matrix4 getTranslationMatrix();
    Vec4 applyTranslation(Vec4 v);
    friend ostream &operator<<(ostream &os, const Translation &t);
};

#endif