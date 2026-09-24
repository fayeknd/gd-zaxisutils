#pragma once
#include "mesh.hpp"

namespace zaxis {

    class PrimitiveGenerator {
    private:

        void _createPlanePrimitive();
        std::shared_ptr<GD3DMesh> m_planePrimitive = nullptr;

        void _createCubePrimitive();
        std::shared_ptr<GD3DMesh> m_cubePrimitive = nullptr;
        
    public:

        static PrimitiveGenerator& get() {
            static PrimitiveGenerator instance;
            return instance;
        }

        std::shared_ptr<GD3DMesh> getPlanePrimitive();
        std::shared_ptr<GD3DMesh> getCubePrimitive();

    };
}