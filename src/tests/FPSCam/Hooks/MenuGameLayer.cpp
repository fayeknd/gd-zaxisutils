#include "MenuGameLayer.hpp"
#ifdef FPS_CAM_TEST
#include <winuser.h>

// this is just a test, i brute forced inputs into working
// do not look at this lol

// cgwarpmousecursorposition(_:)
using namespace zaxis;

Camera3D* cam;
float delta;

bool MenuGameLayerHook::init() {
    if (!MenuGameLayer::init()) return false;

    this->scheduleUpdate();

    GDScene3D* scene = GDScene3D::create();
    scene->setID("3d-scene"_spr);
    scene->m_camera.setFOV(60);
    addChild(scene);

    GDMeshInstance3D* node = GDMeshInstance3D::create(ZAxisAPI_Cube, ZAxisAPI_StandardMaterial);
    node->setID("doom-render-node"_spr);
    node->setPosition({5, 0, -10});
    node->setScale({3, 3, 3});
    node->addToScene(scene);

    GDMeshInstance3D* node2 = GDMeshInstance3D::create(ZAxisAPI_Cube, "new-material");
    node2->setID("doom-render-node-2"_spr);
    node2->setPosition({-5, 0, -10});
    node2->setScale({3, 3, 3});
    node2->addToScene(scene);
    node2->m_material->m_albedoTx = CCTextureCache::sharedTextureCache()->addImage((Mod::get()->getResourcesDir() / "Soggy.png").string().c_str(), false);

    if (!node) {
        geode::log::error("render node is null!");
        return false;
    }
    cam = &scene->m_camera;
    return true;
}

bool keyWDown, keyADown, keyDDown, keySDown;

void MenuGameLayerHook::update(float delta) {
    MenuGameLayer::update(delta);

    float speed = 100.0f;
    if (keyWDown) {
        kmVec3 mov {
            cam->getPositionX() + ((speed * delta) * cam->getForwardX()),
            cam->getPositionY() + ((speed * delta) * cam->getForwardY()),
            cam->getPositionZ() + ((speed * delta) * cam->getForwardZ()),
        };
        cam->setPosition(mov);
    }
    
    if (keyADown) {
        kmVec3 mov {
            cam->getPositionX() + ((speed * delta) * -cam->getRightX()),
            cam->getPositionY() + ((speed * delta) * -cam->getRightY()),
            cam->getPositionZ() + ((speed * delta) * -cam->getRightZ()),
        };
        cam->setPosition(mov);
    }

    if (keySDown) {
        kmVec3 mov {
            cam->getPositionX() + ((speed * delta) * -cam->getForwardX()),
            cam->getPositionY() + ((speed * delta) * -cam->getForwardY()),
            cam->getPositionZ() + ((speed * delta) * -cam->getForwardZ()),
        };
        cam->setPosition(mov);
    } 

    if (keyDDown) {
        kmVec3 mov {
            cam->getPositionX() + ((speed * delta) * cam->getRightX()),
            cam->getPositionY() + ((speed * delta) * cam->getRightY()),
            cam->getPositionZ() + ((speed * delta) * cam->getRightZ()),
        };
        cam->setPosition(mov);
    }
    float sensitivity = 0.45f;
    CCPoint mouseDelta = (getMousePos() - CCDirector::get()->getWinSize() / 2.0f) * sensitivity; 
    SetCursorPos(CCEGLView::get()->getFrameSize().width / 2.0f, CCEGLView::get()->getFrameSize().height / 2.0f);
    cam->setRotationY(cam->getRotationY() - mouseDelta.x);
    cam->setRotationX(cam->getRotationX() - mouseDelta.y);
}

class $modify(CCKeyboardDispatcher) {
    bool dispatchKeyboardMSG(cocos2d::enumKeyCodes key, bool isKeyDown, bool isKeyRepeat, double timestamp) {

        if (!isKeyDown && !isKeyRepeat) {
            if (key == cocos2d::enumKeyCodes::KEY_W) {
                keyWDown = false;
            }
        }
        else if (isKeyDown && !isKeyRepeat) {
            if (key == cocos2d::enumKeyCodes::KEY_W) {
                keyWDown = true;
            }
        }

        if (!isKeyDown && !isKeyRepeat) {
            if (key == cocos2d::enumKeyCodes::KEY_A) {
                keyADown = false;
            }
        }
        else if (isKeyDown && !isKeyRepeat) {
            if (key == cocos2d::enumKeyCodes::KEY_A) {
                keyADown = true;
            }
        }

        if (!isKeyDown && !isKeyRepeat) {
            if (key == cocos2d::enumKeyCodes::KEY_S) {
                keySDown = false;
            }
        }
        else if (isKeyDown && !isKeyRepeat) {
            if (key == cocos2d::enumKeyCodes::KEY_S) {
                keySDown = true;
            }
        }
        
        if (!isKeyDown && !isKeyRepeat) {
            if (key == cocos2d::enumKeyCodes::KEY_D) {
                keyDDown = false;
            }
        }
        else if (isKeyDown && !isKeyRepeat) {
            if (key == cocos2d::enumKeyCodes::KEY_D) {
                keyDDown = true;
            }
        }

        return CCKeyboardDispatcher::dispatchKeyboardMSG(key, isKeyDown, isKeyRepeat, timestamp);
    }
};

#endif