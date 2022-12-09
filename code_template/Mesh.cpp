#include <vector>
#include "Triangle.h"
#include "Mesh.h"
#include <iostream>
#include <iomanip>

using namespace std;

Mesh::Mesh() {}

Mesh::Mesh(int meshId, int type, int numberOfTransformations,
             vector<int> transformationIds,
             vector<char> transformationTypes,
             int numberOfTriangles,
             vector<Triangle> triangles)
{
    this->meshId = meshId;
    this->type = type;
    this->numberOfTransformations = numberOfTransformations;
    this->numberOfTriangles = numberOfTriangles;

    this->transformationIds = transformationIds;
    this->transformationTypes = transformationTypes;
    this->triangles = triangles;
}

void Mesh::applyTransformation(Matrix4 transformationMatrix,Scene scene)
{
    for (int i = 0; i < this->triangles.size(); i++)
    {
       Vec4 firstResultVertex,secondResultVertex,thirdResultVertex;
       firstResultVertex.x = scene.vertices[this->triangles[i].getFirstVertexId()]->x;
       firstResultVertex.y = scene.vertices[this->triangles[i].getFirstVertexId()]->y;
       firstResultVertex.z = scene.vertices[this->triangles[i].getFirstVertexId()]->z;

       secondResultVertex.x = scene.vertices[this->triangles[i].getSecondVertexId()]->x;
       secondResultVertex.y = scene.vertices[this->triangles[i].getSecondVertexId()]->y;
       secondResultVertex.z = scene.vertices[this->triangles[i].getSecondVertexId()]->z;

       thirdResultVertex.x = scene.vertices[this->triangles[i].getThirdVertexId()]->x;
       thirdResultVertex.y = scene.vertices[this->triangles[i].getThirdVertexId()]->y;
       thirdResultVertex.z = scene.vertices[this->triangles[i].getThirdVertexId()]->z;
    
    }

}

ostream &operator<<(ostream &os, const Mesh &m)
{
    os << "Mesh " << m.meshId;

    if (m.type == 0)
    {
        os << " wireframe(0) with ";
    }
    else
    {
        os << " solid(1) with ";
    }

    os << fixed << setprecision(3) << m.numberOfTransformations << " transformations and " << m.numberOfTriangles << " triangles"
       << endl << "\tTriangles are:" << endl << fixed << setprecision(0);

    for (int i = 0; i < m.triangles.size(); i++) {
        os << "\t\t" << m.triangles[i].vertexIds[0] << " " << m.triangles[i].vertexIds[1] << " " << m.triangles[i].vertexIds[2] << endl;
    }

    return os;
}
