#include "../../include/Scene3D.hpp"
#include <geode.devtools/include/API.hpp>

using namespace zaxis;

bool GDScene3D::init(CCSize size) {
    if (!CCNode::init()) return false;
    CCSize glViewSize = CCDirector::sharedDirector()->getWinSize();
    if (size == CCSizeZero) {
        size = CCEGLView::get()->getFrameSize();
    }
    this->setContentSize(glViewSize);

    m_renderTexture = CCRenderTexture::create(
        size.width,
        size.height,
        cocos2d::kCCTexture2DPixelFormat_RGBA8888,
        GL_DEPTH24_STENCIL8
    );
    m_renderTexture->retain(); 
    m_sprite = CCSprite::createWithTexture(this->getOutputTexture());
    m_sprite->setID("output-screen"_spr);

    m_sprite->setScaleX(glViewSize.width / size.width);
    m_sprite->setScaleY(glViewSize.height / size.height);
    
    this->addChildAtPosition(m_sprite, geode::Anchor::Center, CCPointZero);
    return true;
}

void GDScene3D::visit() {
    if (m_renderingToFB) {
        CCNode::visit();
        return;
    }
    if (!m_renderTexture || !m_sprite) return;
    m_renderTexture->beginWithClear(m_clearCol[0] / 255.0f, m_clearCol[1] / 255.0f, m_clearCol[2] / 255.0f, m_clearCol[3] / 255.0f, 1, 0);
    m_renderingToFB = true;

    if (m_pChildren && m_pChildren->count() > 0) {
        this->sortAllChildren();
        for (auto obj : CCArrayExt(m_pChildren)) {
            auto child = static_cast<CCNode*>(obj);
            if (child && child != m_sprite) {
                child->visit();
            }
        }
    }

    m_renderingToFB = false;
    m_renderTexture->end();
    m_sprite->visit();
}

GDScene3D* GDScene3D::create(CCSize size) {
    GDScene3D* ret = new GDScene3D();
    if (ret && ret->init(size)) {
        ret->autorelease();
        return ret;
    }
    delete ret;
    return nullptr;
}

CCTexture2D* GDScene3D::getOutputTexture() {
    return m_renderTexture->getSprite()->getTexture();
}

void GDScene3D::registerDevTools() {
    devtools::registerNode<GDScene3D>([](GDScene3D* node) {
        kmVec3 pos = node->m_camera.getPosition();
        kmVec3 rot = node->m_camera.getRotation();
        float fov = node->m_camera.getFOV();
        float nearClip = node->m_camera.getNearClip();
        float farClip = node->m_camera.getFarClip();
        CameraProjectionMode cpm = node->m_camera.getProjectionMode();

        devtools::label("GDScene3D Properties");
        devtools::label("Camera Transform");
        if (devtools::property("Cam X Position", pos.x)) { node->m_camera.setPositionX(pos.x); }
        if (devtools::property("Cam Y Position", pos.y)) { node->m_camera.setPositionY(pos.y); }
        if (devtools::property("Cam Z Position", pos.z)) { node->m_camera.setPositionZ(pos.z); }

        if (devtools::property("Cam X Rotation", rot.x)) { node->m_camera.setRotationX(rot.x); }
        if (devtools::property("Cam Y Rotation", rot.y)) { node->m_camera.setRotationY(rot.y); }
        if (devtools::property("Cam Z Rotation", rot.z)) { node->m_camera.setRotationZ(rot.z); }

        devtools::label("Clear Colour (0-255)");
        devtools::property("Clear Colour R", node->m_clearCol[0]);
        devtools::property("Clear Colour G", node->m_clearCol[1]);
        devtools::property("Clear Colour B", node->m_clearCol[2]);
        devtools::property("Clear Colour A", node->m_clearCol[3]);

        devtools::label("Camera Perspective");
        if (devtools::property("Cam FOV", fov)) { node->m_camera.setFOV(fov); }
        if (devtools::property("Cam nearClip", nearClip)) { node->m_camera.setNearClip(nearClip); }
        if (devtools::property("Cam farClip", farClip)) { node->m_camera.setFarClip(farClip); }

        if (devtools::enumerable("Cam Projection Mode", cpm, { 
            { CameraProjectionMode::Orthographic, "Orthographic" },
            { CameraProjectionMode::Perspective, "Perspective" } })
        ) { node->m_camera.setProjectionMode(cpm); }


    });
}

$on_mod(Loaded) {
    devtools::waitForDevTools([] {
        GDScene3D::registerDevTools();
    });
}