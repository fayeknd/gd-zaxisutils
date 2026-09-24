
#include "../../include/data/PrimitiveGenerator.hpp"

using namespace zaxis;

// TODO : add model loading probably with assimp (big) or some lightweight fbx importer (small)
// https://learnopengl.com/Model-Loading/Assimp

// TODO : update this to be like the better material cache with keys too
// note: the shaders don't really need to be cached better, cocos already does that

// TODO : uhh test out some GL_TRIANGLE_STRIP, GL_LINE stuff like that 

size_t VertexSz = sizeof(Vertex);

void GD3DMesh::_register() {
    s_instances.insert(shared_from_this());
}

std::shared_ptr<GD3DMesh> GD3DMesh::createMeshWithData(std::vector<Vertex>* vertices, std::vector<GLushort>* indices) {

    // it genuinely took me 2 years to realise that meshes did not need to store their vertices/indices as a class member

    auto mesh = std::shared_ptr<GD3DMesh>(new GD3DMesh());
    mesh->_register(); 

    glGenBuffers(1, &mesh->m_vbo);
    glGenBuffers(1, &mesh->m_ebo);
    glGenVertexArrays(1, &mesh->m_vao);

    glBindVertexArray(mesh->m_vao);

    glBindBuffer(GL_ARRAY_BUFFER, mesh->m_vbo);
    glBufferData(GL_ARRAY_BUFFER, vertices->size() * VertexSz, vertices->data(), GL_STATIC_DRAW);

    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, mesh->m_ebo);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, indices->size() * sizeof(GLushort), indices->data(), GL_STATIC_DRAW);

    glVertexAttribPointer(cocos2d::kCCVertexAttrib_Position, 3, GL_FLOAT, GL_FALSE, VertexSz, (const GLvoid*)offsetof(Vertex, m_position));
    glEnableVertexAttribArray(cocos2d::kCCVertexAttrib_Position);

    glVertexAttribPointer(cocos2d::kCCVertexAttrib_Color,    4, GL_FLOAT, GL_FALSE, VertexSz, (const GLvoid*)offsetof(Vertex, m_col));
    glEnableVertexAttribArray(cocos2d::kCCVertexAttrib_Color);

    glVertexAttribPointer(cocos2d::kCCVertexAttrib_TexCoords,2, GL_FLOAT, GL_FALSE, VertexSz, (const GLvoid*)offsetof(Vertex, m_uv));
    glEnableVertexAttribArray(cocos2d::kCCVertexAttrib_TexCoords);

    glVertexAttribPointer(ZAxisAPIVertexAttrib_Normal,    3, GL_FLOAT, GL_FALSE, VertexSz, (const GLvoid*)offsetof(Vertex, m_normal));
    glEnableVertexAttribArray(ZAxisAPIVertexAttrib_Normal);

    glBindVertexArray(0);
    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);

    mesh->m_indexCount = indices->size(); 

    return mesh;
}

std::shared_ptr<GD3DMesh> GD3DMesh::createPrimitiveMesh(const char* mesh) {
    if (strcmp(mesh, ZAxisAPI_Plane) == 0) {
        return PrimitiveGenerator::get().getPlanePrimitive();
    }
    else if (strcmp(mesh, ZAxisAPI_Cube) == 0) {
        return PrimitiveGenerator::get().getCubePrimitive();
    }
    geode::log::error("ERROR : Primitive mesh identifier is not valid!");
    return nullptr;
}

GD3DMesh::~GD3DMesh() {
    glDeleteBuffers(1, &m_vbo);
    glDeleteBuffers(1, &m_ebo);
    glDeleteVertexArrays(1, &m_vao);
    s_instances.erase(shared_from_this());
}
