#pragma once
#include <cocos2d.h>

namespace zaxis {
    struct Vertex {
        kmVec3 m_position;
        cocos2d::ccColor4F m_col;
        cocos2d::CCPoint m_uv;
        kmVec3 m_normal;
    };
}