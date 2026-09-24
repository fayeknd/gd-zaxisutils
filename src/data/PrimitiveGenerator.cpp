#include "../../include/data/PrimitiveGenerator.hpp"

using namespace zaxis;

void PrimitiveGenerator::_createPlanePrimitive() {
    std::vector<Vertex> vertices;
    std::vector<GLushort> indices;
    vertices = {
        // Position         Colour                      UV                      Normal
        {kmVec3( 1, 1, 0),  cocos2d::ccc4f(1, 1, 1, 1), cocos2d::CCPoint(1, 0), kmVec3(0, 0, -1)},
        {kmVec3( 1,-1, 0),  cocos2d::ccc4f(1, 1, 1, 1), cocos2d::CCPoint(1, 1), kmVec3(0, 0, -1)},
        {kmVec3(-1,-1, 0),  cocos2d::ccc4f(1, 1, 1, 1), cocos2d::CCPoint(0, 1), kmVec3(0, 0, -1)},
        {kmVec3(-1, 1, 0),  cocos2d::ccc4f(1, 1, 1, 1), cocos2d::CCPoint(0, 0), kmVec3(0, 0, -1)}
    };

    indices = {
        0, 1, 3,
        1, 2, 3 
    };
    m_planePrimitive = GD3DMesh::createMeshWithData(&vertices, &indices);
}

void PrimitiveGenerator::_createCubePrimitive() {
    std::vector<Vertex> vertices;
    std::vector<GLushort> indices;
    vertices = {
        // Position         Colour                      UV                      Normal
        {kmVec3(-1, -1, 1), cocos2d::ccc4f(1, 1, 1, 1), cocos2d::CCPoint(0, 0), kmVec3(0, 0, 1)},
        {kmVec3( 1, -1, 1), cocos2d::ccc4f(1, 1, 1, 1), cocos2d::CCPoint(1, 0), kmVec3(0, 0, 1)},
        {kmVec3( 1,  1, 1), cocos2d::ccc4f(1, 1, 1, 1), cocos2d::CCPoint(1, 1), kmVec3(0, 0, 1)},
        {kmVec3(-1,  1, 1), cocos2d::ccc4f(1, 1, 1, 1), cocos2d::CCPoint(0, 1), kmVec3(0, 0, 1)},

        {kmVec3( 1, -1,-1), cocos2d::ccc4f(1, 1, 1, 1), cocos2d::CCPoint(0, 0), kmVec3(0, 0, -1)},
        {kmVec3(-1, -1,-1), cocos2d::ccc4f(1, 1, 1, 1), cocos2d::CCPoint(1, 0), kmVec3(0, 0, -1)},
        {kmVec3(-1,  1,-1), cocos2d::ccc4f(1, 1, 1, 1), cocos2d::CCPoint(1, 1), kmVec3(0, 0, -1)},
        {kmVec3( 1,  1,-1), cocos2d::ccc4f(1, 1, 1, 1), cocos2d::CCPoint(0, 1), kmVec3(0, 0, -1)},

        {kmVec3(-1,  1, 1), cocos2d::ccc4f(1, 1, 1, 1), cocos2d::CCPoint(0, 0), kmVec3(0, 1, 0)},
        {kmVec3( 1,  1, 1), cocos2d::ccc4f(1, 1, 1, 1), cocos2d::CCPoint(1, 0), kmVec3(0, 1, 0)},
        {kmVec3( 1,  1,-1), cocos2d::ccc4f(1, 1, 1, 1), cocos2d::CCPoint(1, 1), kmVec3(0, 1, 0)},
        {kmVec3(-1,  1,-1), cocos2d::ccc4f(1, 1, 1, 1), cocos2d::CCPoint(0, 1), kmVec3(0, 1, 0)},

        {kmVec3(-1, -1,-1), cocos2d::ccc4f(1, 1, 1, 1), cocos2d::CCPoint(0, 0), kmVec3(0, -1, 0)},
        {kmVec3( 1, -1,-1), cocos2d::ccc4f(1, 1, 1, 1), cocos2d::CCPoint(1, 0), kmVec3(0, -1, 0)},
        {kmVec3( 1, -1, 1), cocos2d::ccc4f(1, 1, 1, 1), cocos2d::CCPoint(1, 1), kmVec3(0, -1, 0)},
        {kmVec3(-1, -1, 1), cocos2d::ccc4f(1, 1, 1, 1), cocos2d::CCPoint(0, 1), kmVec3(0, -1, 0)},

        {kmVec3( 1, -1, 1), cocos2d::ccc4f(1, 1, 1, 1), cocos2d::CCPoint(0, 0), kmVec3(1, 0, 0)},
        {kmVec3( 1, -1,-1), cocos2d::ccc4f(1, 1, 1, 1), cocos2d::CCPoint(1, 0), kmVec3(1, 0, 0)},
        {kmVec3( 1,  1,-1), cocos2d::ccc4f(1, 1, 1, 1), cocos2d::CCPoint(1, 1), kmVec3(1, 0, 0)},
        {kmVec3( 1,  1, 1), cocos2d::ccc4f(1, 1, 1, 1), cocos2d::CCPoint(0, 1), kmVec3(1, 0, 0)},

        {kmVec3(-1, -1,-1), cocos2d::ccc4f(1, 1, 1, 1), cocos2d::CCPoint(0, 0), kmVec3(-1, 0, 0)},
        {kmVec3(-1, -1, 1), cocos2d::ccc4f(1, 1, 1, 1), cocos2d::CCPoint(1, 0), kmVec3(-1, 0, 0)},
        {kmVec3(-1,  1, 1), cocos2d::ccc4f(1, 1, 1, 1), cocos2d::CCPoint(1, 1), kmVec3(-1, 0, 0)},
        {kmVec3(-1,  1,-1), cocos2d::ccc4f(1, 1, 1, 1), cocos2d::CCPoint(0, 1), kmVec3(-1, 0, 0)} 
    };

    indices = {
        0, 1, 2,  
        0, 2, 3,

        4, 5, 6, 
        4, 6, 7,
        
        8, 9, 10, 
        8, 10, 11,

        12, 13, 14,
        12, 14, 15,

        16, 17, 18,
        16, 18, 19,

        20, 21, 22,
        20, 22, 23 
    };
    m_cubePrimitive = GD3DMesh::createMeshWithData(&vertices, &indices);
}

std::shared_ptr<GD3DMesh> PrimitiveGenerator::getPlanePrimitive() {
    if (!m_planePrimitive) _createPlanePrimitive();
    return m_planePrimitive;
}

std::shared_ptr<GD3DMesh> PrimitiveGenerator::getCubePrimitive() {
    if (!m_cubePrimitive) _createCubePrimitive();
    return m_cubePrimitive;
}