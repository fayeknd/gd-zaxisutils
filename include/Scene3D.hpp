#pragma once
#include <Geode/Geode.hpp>
#include "Camera3D.hpp"

using namespace geode::prelude;

namespace zaxis {
    
    class GDScene3D : public CCNode {
    protected:

        CCRenderTexture* m_renderTexture = nullptr;
        CCSprite* m_sprite = nullptr;
        bool m_renderingToFB = false;
        
    public:

        static void registerDevTools();
        Camera3D m_camera;
        bool init(CCSize size = CCSizeZero);
        void visit() override;
        static GDScene3D* create(CCSize size = CCSizeZero);
        unsigned int m_clearCol[4] = {50, 0, 50, 255};
        CCTexture2D* getOutputTexture();

    };
}

