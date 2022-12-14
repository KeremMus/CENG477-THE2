#ifndef _SCENE_H_
#define _SCENE_H_

#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <iostream>
#include <string>
#include <vector>

#include "Camera.h"
#include "Color.h"
#include "Mesh.h"
#include "Rotation.h"
#include "Scaling.h"
#include "Translation.h"
#include "Triangle.h"
#include "Vec3.h"
#include "Vec4.h"

using namespace std;

class Scene
{
public:
	Color backgroundColor;
	bool cullingEnabled;
	vector< vector<Color> > image;
	vector< Camera* > cameras;
	vector< Vec3* > vertices;
	vector< Color* > colorsOfVertices;
	vector< Scaling* > scalings;
	vector< Rotation* > rotations;
	vector< Translation* > translations;
	vector< Mesh* > meshes;


	Scene(const char *xmlPath);

	void initializeImage(Camera* camera);
    Matrix4 getResultingTransformationMatrix(Mesh mesh, Vec4 v);
    bool clipper(Vec4 &v1, Vec4 &v2,Vec3 &c1, Vec3 &c2);
    void forwardRenderingPipeline(Camera* camera);
    Vec3 getBarycentricCoordinates(Vec3 point, Vec3 firstVertex, Vec3 secondVertex, Vec3 thirdVertex);
	int makeBetweenZeroAnd255(double value);
	void writeImageToPPMFile(Camera* camera);
	void convertPPMToPNG(string ppmFileName, int osType);
};

#endif
