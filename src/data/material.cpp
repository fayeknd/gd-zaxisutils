#include "../../include/data/material.hpp"
#include "../../include/3DAPI.h"

using namespace zaxis;

bool Material::hasAlbedoTx() {
    return (m_albedoTx != nullptr);
}
bool Material::hasRoughnessTx() {
    return (m_roughnessTx != nullptr);
}
bool Material::hasMetallixTx() {
    return (m_metallicTx != nullptr);
}

void Material::updateExtraUniforms(CCGLProgram* shader) {
    m_hasAlbedoTx =    hasAlbedoTx();
    m_hasRoughnessTx = hasRoughnessTx();
    m_hasMetallicTx =  hasMetallixTx();
    
    if (m_hasAlbedoTx) {
        glActiveTexture(GL_TEXTURE1);
        //ccGLBindTexture2D(m_albedoTx->getName());
        glBindTexture(GL_TEXTURE_2D, m_albedoTx->getName());
    }
    if (m_hasRoughnessTx) {
        glActiveTexture(GL_TEXTURE2);
        ccGLBindTexture2D(m_roughnessTx->getName());
    }
    if (m_hasMetallicTx) {
        glActiveTexture(GL_TEXTURE3);
        ccGLBindTexture2D(m_metallicTx->getName());
    }

    glUniform3fv(glGetUniformLocation(shader->getProgram(), ZAxisAPIUniform_AlbedoBase),   1, &m_albedoBase.x);
    glUniform1f (glGetUniformLocation(shader->getProgram(), ZAxisAPIUniform_RoughnessBase),   m_roughnessBase);
    glUniform1f (glGetUniformLocation(shader->getProgram(), ZAxisAPIUniform_MetallicBase),    m_metallicBase);
    glUniform1f (glGetUniformLocation(shader->getProgram(), ZAxisAPIUniform_AOBase),          m_aoBase);

    glUniform1i (glGetUniformLocation(shader->getProgram(), ZAxisAPIUniform_HasAlbedoTex),    m_hasAlbedoTx);
    glUniform1i (glGetUniformLocation(shader->getProgram(), ZAxisAPIUniform_HasRoughnessTex), m_hasRoughnessTx);
    glUniform1i (glGetUniformLocation(shader->getProgram(), ZAxisAPIUniform_HasMetallicTex),  m_hasMetallicTx);
}

std::string Material::getMaterialKey() {
    return m_materialKey;
}

// materials did not get disposed of when all mesh instances were destroyed,
// like the total instance count was still 1 and i don't really know why
// afaik that shouldn't happen with shared_ptr or maybe it does shrug
// the same might happen with meshes themselves because they're cached in a
// set of shared_ptrs unlike materials. idk. ill look at it some time

std::shared_ptr<Material> MaterialCache::getOrCreateMaterial(std::string key) {
    auto matIter = m_cache.find(key);
    if (matIter != m_cache.end()) {
        auto sharedMat = matIter->second.lock();
        if (sharedMat) return sharedMat; 
    }
    auto newMat = std::make_shared<Material>();
    m_cache[key] = newMat;
    geode::log::info("Creating new material with key {}", key);
    newMat->m_materialKey = key;
    return newMat;
} 

void MaterialCache::_cleanupExpiredRefs() {
    for (auto matIter = m_cache.begin(); matIter != m_cache.end();) {
        if (matIter->second.expired()) {
            matIter = m_cache.erase(matIter);
        } else {
            ++matIter;
        }
    }
}