#pragma once
#include <Geode/Geode.hpp>
#include "Scene3D.hpp"

namespace zaxis {
    
    class CCNode3D : public cocos2d::CCNode {
    protected:

        // this is KIND of weird, but you also get to keep all the cool ccnode stuff like autorelease so its okay really 

        float m_fRotationZ = 0;
        float m_fScaleZ = 1;
        float m_fPositionZ = 0;
        float m_fSkewZ = 0;

        void _Mat4Skew3D(kmMat4* pOut, float x, float y, float zx, float zy);

    public:
        
        GDScene3D* m_scene;
        void addToScene(GDScene3D* scn);

        float getPositionZ();
        float getRotationZ();
        float getScaleZ();
        float getSkewZ();

        kmVec3 getPosition3D();
        kmVec3 getRotation3D();
        kmVec3 getScale3D();
        kmVec3 getSkew3D();

        void setPositionZ(float z);
        void setRotationZ(float z);
        void setScaleZ(float z);
        void setSkewZ(float z);

        void setPosition(kmVec3 v);
        void setRotation(kmVec3 v);
        void setScale(kmVec3 v);
        void setSkew(kmVec3 v);

        void transform3D();
        void endTransform3D();

    };
}

