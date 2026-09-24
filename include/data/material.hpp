#pragma once
#include <Geode/Geode.hpp>

using namespace geode::prelude;

namespace zaxis {

    class Material {
    protected:
        
        bool m_hasAlbedoTx = false;
        bool m_hasRoughnessTx = false;
        bool m_hasMetallicTx = false;
        std::string m_materialKey;

    public:
        kmVec3 m_albedoBase {1, 1, 1};

        float m_roughnessBase = 1;
        float m_metallicBase = 0.5f; 
        float m_aoBase = 1.0f;

        CCTexture2D* m_albedoTx = nullptr;
        CCTexture2D* m_roughnessTx = nullptr;
        CCTexture2D* m_metallicTx = nullptr;

        bool hasAlbedoTx();
        bool hasRoughnessTx();
        bool hasMetallixTx();

        void updateExtraUniforms(CCGLProgram* shader);
        std::string getMaterialKey();

        friend class MaterialCache;
    };

    class MaterialCache {
    protected:

        std::unordered_map<std::string, std::weak_ptr<Material>> m_cache;

        void _cleanupExpiredRefs();
    public:

        static MaterialCache& get() {
            static MaterialCache instance;
            return instance;
        }
        std::shared_ptr<Material> getOrCreateMaterial(std::string key);
    };
}