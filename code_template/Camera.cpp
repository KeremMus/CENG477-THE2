#include "Camera.h"
#include <string>
#include <iostream>
#include <iomanip>

using namespace std;

Camera::Camera() {}

Camera::Camera(int cameraId,
               int projectionType,
               Vec3 pos, Vec3 gaze,
               Vec3 u, Vec3 v, Vec3 w,
               double left, double right, double bottom, double top,
               double near, double far,
               int horRes, int verRes,
               string outputFileName)
{

    this->cameraId = cameraId;
    this->projectionType = projectionType;
    this->pos = pos;
    this->gaze = gaze;
    this->u = u;
    this->v = v;
    this->w = w;
    this->left = left;
    this->right = right;
    this->bottom = bottom;
    this->top = top;
    this->near = near;
    this->far = far;
    this->horRes = horRes;
    this->verRes = verRes;
    this->outputFileName = outputFileName;
}

Camera::Camera(const Camera &other)
{
    this->cameraId = other.cameraId;
    this->projectionType = other.projectionType;
    this->pos = other.pos;
    this->gaze = other.gaze;
    this->u = other.u;
    this->v = other.v;
    this->w = other.w;
    this->left = other.left;
    this->right = other.right;
    this->bottom = other.bottom;
    this->top = other.top;
    this->near = other.near;
    this->far = other.far;
    this->horRes = other.horRes;
    this->verRes = other.verRes;
    this->outputFileName = other.outputFileName;
}

Matrix4 Camera::getViewportTransformationMatrix() {
    Matrix4 viewportMatrix = getIdentityMatrix();
    viewportMatrix.matrix[0][0] = (this->horRes) / 2;
    viewportMatrix.matrix[0][3] = (this->horRes - 1) / 2;
    viewportMatrix.matrix[1][1] = (this->verRes) / 2;
    viewportMatrix.matrix[1][3] = (this->verRes - 1) / 2;
    viewportMatrix.matrix[2][2] = 0.5;
    viewportMatrix.matrix[2][3] = 0.5;
    return viewportMatrix;
}


Matrix4 Camera::getProjectionTransformationMatrix(int projectionType) {
    Matrix4 projectionMatrix = getIdentityMatrix();

    projectionMatrix.matrix[0][0] = 2 / (this->right - this->left);
    projectionMatrix.matrix[0][3] = -(this->right + this->left) / (this->right - this->left);
    projectionMatrix.matrix[1][1] = 2 / (this->top - this->bottom);
    projectionMatrix.matrix[1][3] = -(this->top + this->bottom) / (this->top - this->bottom);
    projectionMatrix.matrix[2][2] = -(2 / (this->far - this->near));
    projectionMatrix.matrix[2][3] = -(this->near + this->far) / (this->far - this->near);

    if (projectionType) {
        Matrix4 pers2orth = getIdentityMatrix();
        pers2orth.matrix[0][0] = this->near;
        pers2orth.matrix[1][1] = this->near;
        pers2orth.matrix[2][2] = this->near + this->far;
        pers2orth.matrix[2][3] = this->near * this->far;
        pers2orth.matrix[3][2] = -1;
        pers2orth.matrix[3][3] = 0;
        projectionMatrix = multiplyMatrixWithMatrix(projectionMatrix, pers2orth);
    }

    return projectionMatrix;
}

Matrix4 Camera::getCameraTransformationMatrix(){

    Matrix4 cameraTransformationMatrix;

    cameraTransformationMatrix[0][0] = u.x;
    cameraTransformationMatrix[0][1] = u.y;
    cameraTransformationMatrix[0][2] = u.z;
    cameraTransformationMatrix[0][3] = -pos.dot(u);

    cameraTransformationMatrix[1][0] = v.x;
    cameraTransformationMatrix[1][1] = v.y;
    cameraTransformationMatrix[1][2] = v.z;
    cameraTransformationMatrix[1][3] = -pos.dot(v);

    cameraTransformationMatrix[2][0] = w.x;
    cameraTransformationMatrix[2][1] = w.y;
    cameraTransformationMatrix[2][2] = w.z;
    cameraTransformationMatrix[2][3] = -pos.dot(w);

    cameraTransformationMatrix[3][0] = 0;
    cameraTransformationMatrix[3][1] = 0;
    cameraTransformationMatrix[3][2] = 0;
    cameraTransformationMatrix[3][3] = 1;

    return cameraTransformationMatrix;
}


ostream &operator<<(ostream &os, const Camera &c)
{
    const char *camType = c.projectionType ? "perspective" : "orthographic";

    os << fixed << setprecision(6) << "Camera " << c.cameraId << " (" << camType << ") => pos: " << c.pos << " gaze: " << c.gaze << endl
       << "\tu: " << c.u << " v: " << c.v << " w: " << c.w << endl
       << fixed << setprecision(3) << "\tleft: " << c.left << " right: " << c.right << " bottom: " << c.bottom << " top: " << c.top << endl
       << "\tnear: " << c.near << " far: " << c.far << " resolutions: " << c.horRes << "x" << c.verRes << " fileName: " << c.outputFileName;

    return os;
}