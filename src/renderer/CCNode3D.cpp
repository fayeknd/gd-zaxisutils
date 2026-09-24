#include "../../include/CCNode3D.hpp"
#include "../../include/3DAPI.h"

using namespace zaxis;

void CCNode3D::addToScene(GDScene3D* scn) {
    scn->addChild(this);
    this->m_scene = scn;
}

void CCNode3D::_Mat4Skew3D(kmMat4* pOut, float x, float y, float zx, float zy)  {
    kmMat4Identity(pOut);
    
    pOut->mat[1] = tanf(kmDegreesToRadians(y));
    pOut->mat[4] = tanf(kmDegreesToRadians(x));
    
    pOut->mat[8] = tanf(kmDegreesToRadians(zx));
    pOut->mat[9] = tanf(kmDegreesToRadians(zy));
}

float CCNode3D::getPositionZ() {
    return m_fPositionZ;
}

float CCNode3D::getRotationZ() {
    return m_fRotationZ;
}

float CCNode3D::getScaleZ() {
    return m_fScaleZ;
}

float CCNode3D::getSkewZ() {
    return m_fSkewZ;
}


kmVec3 CCNode3D::getPosition3D() {
    return kmVec3(m_obPosition.x, m_obPosition.y, m_fPositionZ);
}

kmVec3 CCNode3D::getRotation3D() {
    return kmVec3(m_fRotationX, m_fRotationY, m_fRotationZ);
}

kmVec3 CCNode3D::getScale3D() {
    return kmVec3(m_fScaleX, m_fScaleY, m_fScaleZ);
}

kmVec3 CCNode3D::getSkew3D() {
    return kmVec3(m_fSkewX, m_fSkewY, m_fSkewZ);
}


void CCNode3D::setPositionZ(float z) {
    m_fPositionZ = z;
    m_bTransformDirty = true;
} 

void CCNode3D::setRotationZ(float z) {
    m_fRotationZ = z;
    m_bTransformDirty = true;
} 

void CCNode3D::setScaleZ(float z) {
    m_fScaleZ = z;
    m_bTransformDirty = true;
} 

void CCNode3D::setSkewZ(float z) {
    m_fSkewZ = z;
    m_bTransformDirty = true;
} 


void CCNode3D::setPosition(kmVec3 v) {
    m_obPosition.x = v.x;
    m_obPosition.y = v.y;
    m_fPositionZ   = v.z;
    m_bTransformDirty = true;
}

void CCNode3D::setRotation(kmVec3 v) {
    m_fRotationX = v.x;
    m_fRotationY = v.y;
    m_fRotationZ = v.z;
    m_bTransformDirty = true;
}

void CCNode3D::setScale(kmVec3 v) {
    m_fScaleX = v.x;
    m_fScaleY = v.y;
    m_fScaleZ = v.z;
    m_bTransformDirty = true;
}

void CCNode3D::setSkew(kmVec3 v) {
    m_fSkewX = v.x;
    m_fSkewY = v.y;
    m_fSkewZ = v.z;
    m_bTransformDirty = true;
}

void CCNode3D::transform3D() {

    kmGLMatrixMode(KM_GL_PROJECTION);
    kmGLPushMatrix();
    
    kmMat4 projMat = this->m_scene->m_camera.getProjectionMat4();
    kmGLLoadMatrix(&projMat);

    kmGLMatrixMode(KM_GL_MODELVIEW);
    kmGLPushMatrix();

    kmMat4 camViewMat = this->m_scene->m_camera.getViewMat4();
    kmMat4 viewMat;
    kmMat4Translation(&viewMat, this->m_obPosition.x, this->m_obPosition.y, this->m_fPositionZ); 
    kmMat4Multiply(&viewMat, &camViewMat, &viewMat);
    kmGLLoadMatrix(&viewMat);

    kmMat4 modelMat, rotX, rotY, rotZ, scale, skew;
    kmMat4RotationX(&rotX, kmDegreesToRadians(this->m_fRotationX));
    kmMat4RotationY(&rotY, kmDegreesToRadians(this->m_fRotationY));
    kmMat4RotationZ(&rotZ, kmDegreesToRadians(this->m_fRotationZ));

    kmMat4Multiply(&modelMat, &rotX, &rotY);
    kmMat4Multiply(&modelMat, &modelMat, &rotZ);

    _Mat4Skew3D(&skew, this->m_fSkewX, 0, this->m_fSkewZ, this->m_fSkewY);
    kmMat4Multiply(&modelMat, &modelMat, &skew);

    kmMat4Scaling(&scale, this->m_fScaleX, this->m_fScaleY, this->m_fScaleZ);
    kmMat4Multiply(&modelMat, &modelMat, &scale);

    kmGLMultMatrix(&modelMat);

    kmMat4 currentModelView, currentProjection, mvpMatrix;
    kmGLGetMatrix(KM_GL_MODELVIEW, &currentModelView);
    kmGLGetMatrix(KM_GL_PROJECTION, &currentProjection);
    kmMat4Multiply(&mvpMatrix, &currentProjection, &currentModelView);

    this->m_pShaderProgram->setUniformLocationWithMatrix4fv(this->m_pShaderProgram->getUniformLocationForName(kCCUniformMVPMatrix_s), mvpMatrix.mat, 1);
    this->m_pShaderProgram->setUniformLocationWithMatrix4fv(this->m_pShaderProgram->getUniformLocationForName(ZAxisAPIModelMatrixUniform), modelMat.mat, 1);
}

void CCNode3D::endTransform3D() {
    kmGLMatrixMode(KM_GL_PROJECTION); kmGLPopMatrix();
    kmGLMatrixMode(KM_GL_MODELVIEW); kmGLPopMatrix();
}