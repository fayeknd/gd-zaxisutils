#pragma once

namespace zaxis {

    enum CameraProjectionMode {
        Perspective,
        Orthographic
    };

    class Camera3D {
    protected:

        kmVec3 m_position;
        kmVec3 m_rotation;

        kmVec3 m_forward;
        kmVec3 m_up;
        kmVec3 m_right;

        const kmVec3 m_defaultForward {0, 0, -1};
        const kmVec3 m_defaultUp {0, 1, 0};
        const kmVec3 m_defaultRight {1, 0, 0};

        float m_fov = 75;
        float m_nearClip = 0.1f;
        float m_farClip = 1000.0f;

        kmMat4 m_projMat4;
        kmMat4 m_viewMat4;
        bool m_projectionDirty = true;
        bool m_viewDirty = true;
        CameraProjectionMode m_projectionMode = CameraProjectionMode::Perspective;

    public:

        kmVec3 getPosition();
        kmVec3 getRotation();
        kmVec3 getForward();
        kmVec3 getUp();
        kmVec3 getRight();

        float getPositionX();
        float getPositionY();
        float getPositionZ();

        float getRotationX();
        float getRotationY();
        float getRotationZ();

        float getForwardX();
        float getForwardY();
        float getForwardZ();

        float getUpX();
        float getUpY();
        float getUpZ();

        float getRightX();
        float getRightY();
        float getRightZ();

        void setPosition(kmVec3 pos);
        void setRotation(kmVec3 rot);

        void setPositionX(float x);
        void setPositionY(float y);
        void setPositionZ(float z);

        void setRotationX(float x);
        void setRotationY(float y);
        void setRotationZ(float z);

        float getFOV();
        void setFOV(float fov);

        float getNearClip();
        void setNearClip(float nearClip);

        float getFarClip();
        void setFarClip(float farClip);

        CameraProjectionMode getProjectionMode();
        void setProjectionMode(CameraProjectionMode cpm);

        kmMat4 getProjectionMat4(); 
        kmMat4 getViewMat4(); 

    };
}

