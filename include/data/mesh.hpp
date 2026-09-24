#pragma once
#include "vertex.hpp"
#include "../3DAPI.h"

namespace zaxis {

    class GD3DMesh : public std::enable_shared_from_this<GD3DMesh> {
    private:

        GLuint m_vbo;
        GLuint m_ebo;
        GLuint m_vao;
        GLsizei m_indexCount;

        static inline std::set<std::shared_ptr<GD3DMesh>> s_instances;
        void _register();

    public:

        ~GD3DMesh();
        static std::shared_ptr<GD3DMesh> createPrimitiveMesh(const char* mesh);
        static std::shared_ptr<GD3DMesh> createMeshWithData(std::vector<Vertex>* vertices, std::vector<GLushort>* indices);

        GLuint const getVBO() { return m_vbo; } 
        GLuint const getEBO() { return m_ebo; }
        GLuint const getVAO() { return m_vao; }

        friend class GDMeshInstance3D;

    };
}

