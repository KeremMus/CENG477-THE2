#ifndef __MESH_H__
#define __MESH_H__

#include <vector>
#include "Triangle.h"
#include <iostream>
#include "Vec4.h"
#include "Matrix4.h"
#include "Helpers.h"
#include "Scene.h"

using namespace std;

class Mesh
{

public:
    int meshId;
    int type; // 0 for wireframe, 1 for solid
    int numberOfTransformations;
    vector<int> transformationIds;
    vector<char> transformationTypes;
    int numberOfTriangles;
    vector<Triangle> triangles;

    Mesh();
    Mesh(int meshId, int type, int numberOfTransformations,
          vector<int> transformationIds,
          vector<char> transformationTypes,
          int numberOfTriangles,
          vector<Triangle> triangles);
    void applyTransformation(Matrix4 transformationMatrix,Scene scene);


    friend ostream &operator<<(ostream &os, const Mesh &m);
};


#endif