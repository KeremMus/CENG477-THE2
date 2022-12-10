#include <iostream>
#include <iomanip>
#include <cstdlib>
#include <cstring>
#include <fstream>
#include <cmath>

#include "Scene.h"
#include "Camera.h"
#include "Color.h"
#include "Mesh.h"
#include "Rotation.h"
#include "Scaling.h"
#include "Translation.h"
#include "Triangle.h"
#include "Vec3.h"
#include "tinyxml2.h"

using namespace tinyxml2;
using namespace std;


Matrix4 Scene::getResultingTransformationMatrix(Mesh mesh, Vec4 v){
    Matrix4 result = getIdentityMatrix();
    for (int i = 0; i < mesh.transformationTypes.size() ; i++){
        if (mesh.transformationTypes[i] == 't'){
            Translation translation = *this->translations[mesh.transformationIds[i]];
            result = multiplyMatrixWithMatrix(translation.getTranslationMatrix(), result);
        }
        if (mesh.transformationTypes[i] == 's'){
            Scaling scaling = *this->scalings[mesh.transformationIds[i]];
            result = multiplyMatrixWithMatrix(scaling.getScalingMatrix(v), result);
        }
        if (mesh.transformationTypes[i] == 'r'){
            Rotation rotation = *this->rotations[mesh.transformationIds[i]];
            result = multiplyMatrixWithMatrix(rotation.getRotationMatrix(), result);
        }
    }
    return result;
}

Vec3 Scene::getBarycentricCoordinates(Vec3 point, Vec3 firstVertex, Vec3 secondVertex, Vec3 thirdVertex) {
    Vec3 result;
    double alphaNom = (point.x*(secondVertex.y-thirdVertex.y)+ point.y*(thirdVertex.x- secondVertex.x)+(secondVertex.x*thirdVertex.y)-(secondVertex.y*thirdVertex.x));
    double alphaDenom = (firstVertex.x*(secondVertex.y-thirdVertex.y)+ firstVertex.y*(thirdVertex.x- secondVertex.x)+(secondVertex.x*thirdVertex.y)-(secondVertex.y*thirdVertex.x));
    double alpha = alphaNom/alphaDenom;
    double betaNom = (point.x*(thirdVertex.y-firstVertex.y)+ point.y*(firstVertex.x- thirdVertex.x)+(thirdVertex.x*firstVertex.y)-(thirdVertex.y*firstVertex.x));
    double betaDenom = (secondVertex.x*(thirdVertex.y-firstVertex.y)+ secondVertex.y*(firstVertex.x- thirdVertex.x)+(thirdVertex.x*firstVertex.y)-(thirdVertex.y*firstVertex.x));
    double beta = betaNom/betaDenom;
    double gamma = 1 - alpha - beta;
    result.x = alpha;
    result.y = beta;
    result.z = gamma;
    return result;
}
/*
	Transformations, clipping, culling, rasterization are done here.
	You may define helper functions.
*/

void Scene::forwardRenderingPipeline(Camera *camera)
{
    Matrix4 viewportMatrix = camera->getViewportTransformationMatrix();

    Matrix4 cameraTransformationMatrix = camera->getCameraTransformationMatrix();
    Matrix4 perspectiveMatrix = camera->getProjectionTransformationMatrix(camera->projectionType);
    Matrix4 projectionMatrix = multiplyMatrixWithMatrix(viewportMatrix, perspectiveMatrix);
    projectionMatrix = multiplyMatrixWithMatrix(projectionMatrix, cameraTransformationMatrix);

    // Viewport x_min?, rotation

    for (int i = 0; i < this->meshes.size(); i++)
    {
        Mesh mesh = *this->meshes[i];


        for (int j = 0; j < mesh.numberOfTriangles; j++){
            Triangle triangle = mesh.triangles[j];
            Vec4 firstVertex = Vec4(this->vertices[triangle.getFirstVertexId()]->x, this->vertices[triangle.getFirstVertexId()]->y, this->vertices[triangle.getFirstVertexId()]->z, 1);
            Vec4 secondVertex = Vec4(this->vertices[triangle.getSecondVertexId()]->x, this->vertices[triangle.getSecondVertexId()]->y, this->vertices[triangle.getSecondVertexId()]->z, 1);
            Vec4 thirdVertex = Vec4(this->vertices[triangle.getThirdVertexId()]->x, this->vertices[triangle.getThirdVertexId()]->y, this->vertices[triangle.getThirdVertexId()]->z, 1);

            Matrix4 transformMatrixV1 = getResultingTransformationMatrix(mesh, firstVertex);
            transformMatrixV1 = multiplyMatrixWithMatrix(projectionMatrix, transformMatrixV1);

            Matrix4 transformMatrixV2 = getResultingTransformationMatrix(mesh, secondVertex);
            transformMatrixV2 = multiplyMatrixWithMatrix(projectionMatrix, transformMatrixV2);

            Matrix4 transformMatrixV3 = getResultingTransformationMatrix(mesh, thirdVertex);
            transformMatrixV3 = multiplyMatrixWithMatrix(projectionMatrix, transformMatrixV3);

            Vec4 v1 = multiplyMatrixWithVec4(transformMatrixV1, firstVertex);
            Vec4 v2 = multiplyMatrixWithVec4(transformMatrixV2, secondVertex);
            Vec4 v3 = multiplyMatrixWithVec4(transformMatrixV3, thirdVertex);


            // Clipping
//            if (v1.x < -1 || v1.x > 1 || v1.y < -1 || v1.y > 1 || v1.z < -1 || v1.z > 1 ||
//                v2.x < -1 || v2.x > 1 || v2.y < -1 || v2.y > 1 || v2.z < -1 || v2.z > 1 ||
//                v3.x < -1 || v3.x > 1 || v3.y < -1 || v3.y > 1 || v3.z < -1 || v3.z > 1){
//                continue;
//            }
//
//            // Culling
//            if (this->cullingEnabled){
//                Vec3 normal = getNormalOfTriangle(triangle);
//                Vec3 cameraPosition = camera->position;
//                Vec3 cameraToTriangle = Vec3(v1.x, v1.y, v1.z) - cameraPosition;
//                if (dotProduct(normal, cameraToTriangle) < 0){
//                    continue;
//                }
//            }

            // Rasterization
//            int minX = min(v1.x, min(v2.x, v3.x));
//            int maxX = max(v1.x, max(v2.x, v3.x));
//            int minY = min(v1.y, min(v2.y, v3.y));
//            int maxY = max(v1.y, max(v2.y, v3.y));
//
//            for (int x = minX; x <= maxX; x++){
//                for (int y = minY; y <= maxY; y++){
//                    Vec3 barycentricCoordinates = getBarycentricCoordinates(Vec3(x, y, 0), Vec3(v1.x, v1.y, v1.z), Vec3(v2.x, v2.y, v2.z), Vec3(v3.x, v3.y, v3.z));
//                    if (barycentricCoordinates.x >= 0 && barycentricCoordinates.y >= 0 && barycentricCoordinates.z >= 0){
//                        this->image[x][y] = mesh.triangles[j].color;
//                    }
//                }
//            }
        }
    }
}

/*
	Parses XML file
*/
Scene::Scene(const char *xmlPath)
{
	const char *str;
	XMLDocument xmlDoc;
	XMLElement *pElement;

	xmlDoc.LoadFile(xmlPath);

	XMLNode *pRoot = xmlDoc.FirstChild();

	// read background color
	pElement = pRoot->FirstChildElement("BackgroundColor");
	str = pElement->GetText();
	sscanf(str, "%lf %lf %lf", &backgroundColor.r, &backgroundColor.g, &backgroundColor.b);

	// read culling
	pElement = pRoot->FirstChildElement("Culling");
	if (pElement != NULL) {
		str = pElement->GetText();
		
		if (strcmp(str, "enabled") == 0) {
			cullingEnabled = true;
		}
		else {
			cullingEnabled = false;
		}
	}

	// read cameras
	pElement = pRoot->FirstChildElement("Cameras");
	XMLElement *pCamera = pElement->FirstChildElement("Camera");
	XMLElement *camElement;
	while (pCamera != NULL)
	{
		Camera *cam = new Camera();

		pCamera->QueryIntAttribute("id", &cam->cameraId);

		// read projection type
		str = pCamera->Attribute("type");

		if (strcmp(str, "orthographic") == 0) {
			cam->projectionType = 0;
		}
		else {
			cam->projectionType = 1;
		}

		camElement = pCamera->FirstChildElement("Position");
		str = camElement->GetText();
		sscanf(str, "%lf %lf %lf", &cam->pos.x, &cam->pos.y, &cam->pos.z);

		camElement = pCamera->FirstChildElement("Gaze");
		str = camElement->GetText();
		sscanf(str, "%lf %lf %lf", &cam->gaze.x, &cam->gaze.y, &cam->gaze.z);

		camElement = pCamera->FirstChildElement("Up");
		str = camElement->GetText();
		sscanf(str, "%lf %lf %lf", &cam->v.x, &cam->v.y, &cam->v.z);

		cam->gaze = normalizeVec3(cam->gaze);
		cam->u = crossProductVec3(cam->gaze, cam->v);
		cam->u = normalizeVec3(cam->u);

		cam->w = inverseVec3(cam->gaze);
		cam->v = crossProductVec3(cam->u, cam->gaze);
		cam->v = normalizeVec3(cam->v);

		camElement = pCamera->FirstChildElement("ImagePlane");
		str = camElement->GetText();
		sscanf(str, "%lf %lf %lf %lf %lf %lf %d %d",
			   &cam->left, &cam->right, &cam->bottom, &cam->top,
			   &cam->near, &cam->far, &cam->horRes, &cam->verRes);

		camElement = pCamera->FirstChildElement("OutputName");
		str = camElement->GetText();
		cam->outputFileName = string(str);

		cameras.push_back(cam);

		pCamera = pCamera->NextSiblingElement("Camera");
	}

	// read vertices
	pElement = pRoot->FirstChildElement("Vertices");
	XMLElement *pVertex = pElement->FirstChildElement("Vertex");
	int vertexId = 1;

	while (pVertex != NULL)
	{
		Vec3 *vertex = new Vec3();
		Color *color = new Color();

		vertex->colorId = vertexId;

		str = pVertex->Attribute("position");
		sscanf(str, "%lf %lf %lf", &vertex->x, &vertex->y, &vertex->z);

		str = pVertex->Attribute("color");
		sscanf(str, "%lf %lf %lf", &color->r, &color->g, &color->b);

		vertices.push_back(vertex);
		colorsOfVertices.push_back(color);

		pVertex = pVertex->NextSiblingElement("Vertex");

		vertexId++;
	}

	// read translations
	pElement = pRoot->FirstChildElement("Translations");
	XMLElement *pTranslation = pElement->FirstChildElement("Translation");
	while (pTranslation != NULL)
	{
		Translation *translation = new Translation();

		pTranslation->QueryIntAttribute("id", &translation->translationId);

		str = pTranslation->Attribute("value");
		sscanf(str, "%lf %lf %lf", &translation->tx, &translation->ty, &translation->tz);

		translations.push_back(translation);

		pTranslation = pTranslation->NextSiblingElement("Translation");
	}

	// read scalings
	pElement = pRoot->FirstChildElement("Scalings");
	XMLElement *pScaling = pElement->FirstChildElement("Scaling");
	while (pScaling != NULL)
	{
		Scaling *scaling = new Scaling();

		pScaling->QueryIntAttribute("id", &scaling->scalingId);
		str = pScaling->Attribute("value");
		sscanf(str, "%lf %lf %lf", &scaling->sx, &scaling->sy, &scaling->sz);

		scalings.push_back(scaling);

		pScaling = pScaling->NextSiblingElement("Scaling");
	}

	// read rotations
	pElement = pRoot->FirstChildElement("Rotations");
	XMLElement *pRotation = pElement->FirstChildElement("Rotation");
	while (pRotation != NULL)
	{
		Rotation *rotation = new Rotation();

		pRotation->QueryIntAttribute("id", &rotation->rotationId);
		str = pRotation->Attribute("value");
		sscanf(str, "%lf %lf %lf %lf", &rotation->angle, &rotation->ux, &rotation->uy, &rotation->uz);

		rotations.push_back(rotation);

		pRotation = pRotation->NextSiblingElement("Rotation");
	}

	// read meshes
	pElement = pRoot->FirstChildElement("Meshes");

	XMLElement *pMesh = pElement->FirstChildElement("Mesh");
	XMLElement *meshElement;
	while (pMesh != NULL)
	{
		Mesh *mesh = new Mesh();

		pMesh->QueryIntAttribute("id", &mesh->meshId);

		// read projection type
		str = pMesh->Attribute("type");

		if (strcmp(str, "wireframe") == 0) {
			mesh->type = 0;
		}
		else {
			mesh->type = 1;
		}

		// read mesh transformations
		XMLElement *pTransformations = pMesh->FirstChildElement("Transformations");
		XMLElement *pTransformation = pTransformations->FirstChildElement("Transformation");

		while (pTransformation != NULL)
		{
			char transformationType;
			int transformationId;

			str = pTransformation->GetText();
			sscanf(str, "%c %d", &transformationType, &transformationId);

			mesh->transformationTypes.push_back(transformationType);
			mesh->transformationIds.push_back(transformationId);

			pTransformation = pTransformation->NextSiblingElement("Transformation");
		}

		mesh->numberOfTransformations = mesh->transformationIds.size();

		// read mesh faces
		char *row;
		char *clone_str;
		int v1, v2, v3;
		XMLElement *pFaces = pMesh->FirstChildElement("Faces");
        str = pFaces->GetText();
		clone_str = strdup(str);

		row = strtok(clone_str, "\n");
		while (row != NULL)
		{
			int result = sscanf(row, "%d %d %d", &v1, &v2, &v3);
			
			if (result != EOF) {
				mesh->triangles.push_back(Triangle(v1, v2, v3));
			}
			row = strtok(NULL, "\n");
		}
		mesh->numberOfTriangles = mesh->triangles.size();
		meshes.push_back(mesh);

		pMesh = pMesh->NextSiblingElement("Mesh");
	}
}

/*
	Initializes image with background color
*/
void Scene::initializeImage(Camera *camera)
{
	if (this->image.empty())
	{
		for (int i = 0; i < camera->horRes; i++)
		{
			vector<Color> rowOfColors;

			for (int j = 0; j < camera->verRes; j++)
			{
				rowOfColors.push_back(this->backgroundColor);
			}

			this->image.push_back(rowOfColors);
		}
	}
	else
	{
		for (int i = 0; i < camera->horRes; i++)
		{
			for (int j = 0; j < camera->verRes; j++)
			{
				this->image[i][j].r = this->backgroundColor.r;
				this->image[i][j].g = this->backgroundColor.g;
				this->image[i][j].b = this->backgroundColor.b;
			}
		}
	}
}

/*
	If given value is less than 0, converts value to 0.
	If given value is more than 255, converts value to 255.
	Otherwise returns value itself.
*/
int Scene::makeBetweenZeroAnd255(double value)
{
	if (value >= 255.0)
		return 255;
	if (value <= 0.0)
		return 0;
	return (int)(value);
}

/*
	Writes contents of image (Color**) into a PPM file.
*/
void Scene::writeImageToPPMFile(Camera *camera)
{
	ofstream fout;

	fout.open(camera->outputFileName.c_str());

	fout << "P3" << endl;
	fout << "# " << camera->outputFileName << endl;
	fout << camera->horRes << " " << camera->verRes << endl;
	fout << "255" << endl;

	for (int j = camera->verRes - 1; j >= 0; j--)
	{
		for (int i = 0; i < camera->horRes; i++)
		{
			fout << makeBetweenZeroAnd255(this->image[i][j].r) << " "
				 << makeBetweenZeroAnd255(this->image[i][j].g) << " "
				 << makeBetweenZeroAnd255(this->image[i][j].b) << " ";
		}
		fout << endl;
	}
	fout.close();
}

/*
	Converts PPM image in given path to PNG file, by calling ImageMagick's 'convert' command.
	os_type == 1 		-> Ubuntu
	os_type == 2 		-> Windows
	os_type == other	-> No conversion
*/
void Scene::convertPPMToPNG(string ppmFileName, int osType)
{
	string command;

	// call command on Ubuntu
	if (osType == 1)
	{
		command = "convert " + ppmFileName + " " + ppmFileName + ".png";
		system(command.c_str());
	}

	// call command on Windows
	else if (osType == 2)
	{
		command = "magick convert " + ppmFileName + " " + ppmFileName + ".png";
		system(command.c_str());
	}

	// default action - don't do conversion
	else
	{
	}
}