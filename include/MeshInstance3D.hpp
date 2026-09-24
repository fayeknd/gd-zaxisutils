#pragma once
#include "data/mesh.hpp"
#include "CCNode3D.hpp"
#include "data/material.hpp"

using namespace geode::prelude;

namespace zaxis {

    class GDMeshInstance3D : public CCNode3D {
    public:

        std::shared_ptr<Material> m_material;
        static void registerDevTools();
        static GDMeshInstance3D* create(std::string materialKey = ZAxisAPI_StandardMaterial);
        static GDMeshInstance3D* create(const char* mesh, std::string materialKey = ZAxisAPI_StandardMaterial);
        bool init() override;
        void visit() override;

        std::shared_ptr<GD3DMesh> m_mesh;

        void update(float dt) override;
    };
}