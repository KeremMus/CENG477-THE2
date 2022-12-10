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
    viewportMatrix.val[0][0] = (this->horRes) / 2;
    viewportMatrix.val[0][3] = (this->horRes - 1) / 2;
    viewportMatrix.val[1][1] = (this->verRes) / 2;
    viewportMatrix.val[1][3] = (this->verRes - 1) / 2;
    viewportMatrix.val[2][2] = 0.5;
    viewportMatrix.val[2][3] = 0.5;
    return viewportMatrix;
}


Matrix4 Camera::getProjectionTransformationMatrix(int projectionType) {
    Matrix4 projectionMatrix = getIdentityMatrix();

    projectionMatrix.val[0][0] = 2 / (this->right - this->left);
    projectionMatrix.val[0][3] = -(this->right + this->left) / (this->right - this->left);
    projectionMatrix.val[1][1] = 2 / (this->top - this->bottom);
    projectionMatrix.val[1][3] = -(this->top + this->bottom) / (this->top - this->bottom);
    projectionMatrix.val[2][2] = -(2 / (this->far - this->near));
    projectionMatrix.val[2][3] = -(this->near + this->far) / (this->far - this->near);

    if (projectionType) {
        Matrix4 pers2orth = getIdentityMatrix();
        pers2orth.val[0][0] = this->near;
        pers2orth.val[1][1] = this->near;
        pers2orth.val[2][2] = this->near + this->far;
        pers2orth.val[2][3] = this->near * this->far;
        pers2orth.val[3][2] = -1;
        pers2orth.val[3][3] = 0;
        projectionMatrix = multiplyMatrixWithMatrix(projectionMatrix, pers2orth);
    }

    return projectionMatrix;
}

Matrix4 Camera::getCameraTransformationMatrix(){

    Matrix4 cameraTransformationMatrix;

    cameraTransformationMatrix.val[0][0] = u.x;
    cameraTransformationMatrix.val[0][1] = u.y;
    cameraTransformationMatrix.val[0][2] = u.z;
    cameraTransformationMatrix.val[0][3] = -dotProductVec3(pos,u);

    cameraTransformationMatrix.val[1][0] = v.x;
    cameraTransformationMatrix.val[1][1] = v.y;
    cameraTransformationMatrix.val[1][2] = v.z;
    cameraTransformationMatrix.val[1][3] = -dotProductVec3(pos,v);

    cameraTransformationMatrix.val[2][0] = w.x;
    cameraTransformationMatrix.val[2][1] = w.y;
    cameraTransformationMatrix.val[2][2] = w.z;
    cameraTransformationMatrix.val[2][3] = -dotProductVec3(pos,w);

    cameraTransformationMatrix.val[3][0] = 0;
    cameraTransformationMatrix.val[3][1] = 0;
    cameraTransformationMatrix.val[3][2] = 0;
    cameraTransformationMatrix.val[3][3] = 1;

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