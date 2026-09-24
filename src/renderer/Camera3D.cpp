#include "../../include/Camera3D.hpp"

using namespace zaxis;

kmVec3 Camera3D::getPosition() {
    return m_position;
}
kmVec3 Camera3D::getRotation() {
    return m_rotation;
}
kmVec3 Camera3D::getForward() {
    return m_forward;
}
kmVec3 Camera3D::getUp() {
    return m_up;
}
kmVec3 Camera3D::getRight() {
    return m_right;
}

float Camera3D::getPositionX() {
    return m_position.x;
}
float Camera3D::getPositionY() {
    return m_position.y;
}
float Camera3D::getPositionZ() {
    return m_position.z;
}

float Camera3D::getRotationX() {
    return m_rotation.x;
}
float Camera3D::getRotationY() {
    return m_rotation.y;
}
float Camera3D::getRotationZ() {
    return m_rotation.z; 
}

float Camera3D::getForwardX() {
    return m_forward.x;
}
float Camera3D::getForwardY() {
    return m_forward.y;
}
float Camera3D::getForwardZ() {
    return m_forward.z; 
}

float Camera3D::getUpX() {
    return m_up.x;
}
float Camera3D::getUpY() {
    return m_up.y;
}
float Camera3D::getUpZ() {
    return m_up.z; 
}

float Camera3D::getRightX() {
    return m_right.x;
}
float Camera3D::getRightY() {
    return m_right.y;
}
float Camera3D::getRightZ() {
    return m_right.z; 
}

void Camera3D::setPosition(kmVec3 pos) {
    m_position = pos;
    m_viewDirty = true;
}
void Camera3D::setRotation(kmVec3 rot) {
    m_rotation = rot;
    m_viewDirty = true;
}

void Camera3D::setPositionX(float x) {
    m_position.x = x;
    m_viewDirty = true;
}
void Camera3D::setPositionY(float y) {
    m_position.y = y;
    m_viewDirty = true;
}
void Camera3D::setPositionZ(float z) {
    m_position.z = z; 
    m_viewDirty = true;
}

void Camera3D::setRotationX(float x) {
    m_rotation.x = x;
    m_viewDirty = true;
}
void Camera3D::setRotationY(float y) {
    m_rotation.y = y;
    m_viewDirty = true;
}
void Camera3D::setRotationZ(float z) {
    m_rotation.z = z;
    m_viewDirty = true;
}

float Camera3D::getFOV() {
    return m_fov;
}
void Camera3D::setFOV(float fov) {
    m_fov = fov;
    m_projectionDirty = true;
}

float Camera3D::getNearClip() {
    return m_nearClip; 
}
void Camera3D::setNearClip(float nearClip) {
    m_nearClip = nearClip;
    m_projectionDirty = true;
}

float Camera3D::getFarClip() {
    return m_farClip;
}
void Camera3D::setFarClip(float farClip) {
    m_farClip = farClip;
    m_projectionDirty = true;
}

CameraProjectionMode Camera3D::getProjectionMode() {
    return m_projectionMode;
}

void Camera3D::setProjectionMode(CameraProjectionMode cpm) {
    m_projectionMode = cpm;
    m_projectionDirty = true;
}

kmMat4 Camera3D::getProjectionMat4() {
    if (!m_projectionDirty) return m_projMat4;
    m_projectionDirty = false;

    auto winSize = cocos2d::CCDirector::sharedDirector()->getWinSize();
    float aspectRatio = winSize.width / winSize.height;
    switch (m_projectionMode) {
        case CameraProjectionMode::Orthographic:      // 16:9 centered
            kmMat4OrthographicProjection(&m_projMat4, -8, 8, -4.5f, 4.5f, m_nearClip, m_farClip);
            break;
        default:
            kmMat4PerspectiveProjection(&m_projMat4, m_fov, aspectRatio, m_nearClip, m_farClip);
            break;
    }
    return m_projMat4;
}

kmMat4 Camera3D::getViewMat4() {
    if (!m_viewDirty) return m_viewMat4;
    m_viewDirty = false;

    kmVec3 rad = {
        kmDegreesToRadians(m_rotation.x), // yaw
        kmDegreesToRadians(m_rotation.y), // pitch
        kmDegreesToRadians(m_rotation.z)  // roll
    };
    // kmMat4RotationPitchYawRoll was kinda weird and didn't work properly / i don't understand the difference with it (i miss glm)
    kmMat4 rotX, rotY, rotZ;
    kmMat4RotationAxisAngle(&rotX, &m_defaultRight, rad.x);
    kmMat4RotationAxisAngle(&rotY, &m_defaultUp, rad.y);
    kmMat4RotationAxisAngle(&rotZ, &m_defaultForward, rad.z);

    kmMat4 rot;
    kmMat4Multiply(&rot, &rotX, &rotZ);
    kmMat4Multiply(&rot, &rotY, &rot);

    kmVec3Transform(&m_forward, &m_defaultForward, &rot);
    kmVec3Transform(&m_up, &m_defaultUp, &rot);
    kmVec3Transform(&m_right, &m_defaultRight, &rot);

    kmVec3 target = {
        m_position.x + m_forward.x, 
        m_position.y + m_forward.y, 
        m_position.z + m_forward.z
    }; 

    kmMat4LookAt(&m_viewMat4, &m_position, &target, &m_up);

    return m_viewMat4;
}