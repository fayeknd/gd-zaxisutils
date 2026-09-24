#pragma once
#include <Geode/Geode.hpp>
#include <Geode/cocos/shaders/CCGLProgram.h>
#include <Geode/cocos/shaders/CCShaderCache.h>

using namespace geode::prelude;

namespace zaxis {

    class ShaderManager {
    public:

        static ShaderManager& get() {
            static ShaderManager instance;
            return instance;
        }

        CCGLProgram* getOrCreateShaderFromFile(const char* vert, const char* frag, const char* shaderName);

    };
}