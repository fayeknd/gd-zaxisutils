#pragma once
// #define FPS_CAM_TEST
#ifdef FPS_CAM_TEST

#include <Geode/Geode.hpp>
#include <Geode/modify/MenuGameLayer.hpp>
#include <Geode/modify/CCLayer.hpp>
#include <Geode/modify/CCKeyboardDispatcher.hpp>

#include "../../../include/Scene3D.hpp"
#include "../../../include/3DAPI.h"
#include "../../../include/MeshInstance3D.hpp"



using namespace geode::prelude;

namespace zaxis {

    class $modify(MenuGameLayerHook, MenuGameLayer) {
        bool init();
        void update(float delta); 
    };
}
#endif