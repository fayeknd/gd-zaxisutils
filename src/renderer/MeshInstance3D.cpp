#include "../../include/MeshInstance3D.hpp"
#include <geode.devtools/include/API.hpp>
#include "../../include/ShaderManager.hpp"

using namespace zaxis;

GDMeshInstance3D* GDMeshInstance3D::create(std::string materialKey)  {
    GDMeshInstance3D* ret = new GDMeshInstance3D();
    if (ret && ret->init()) {
        ret->m_material = MaterialCache::get().getOrCreateMaterial(materialKey);
        ret->autorelease();
        return ret;
    }
    delete ret;
    return nullptr;
}
GDMeshInstance3D* GDMeshInstance3D::create(const char* mesh, std::string materialKey) {
    GDMeshInstance3D* ret = create(materialKey);
    if (!ret) return nullptr;

    ret->m_mesh = GD3DMesh::createPrimitiveMesh(mesh);
    return ret;
}

bool GDMeshInstance3D::init() {
    if (!CCNode::init()) return false;
    //this->setShaderProgram(CCShaderCache::sharedShaderCache()->programForKey(kCCShader_PositionColor));
    this->setShaderProgram(ShaderManager::get().getOrCreateShaderFromFile("vert.glsl"_spr, "frag.glsl"_spr, ZAxisAPIDefaultShaderKey));
    this->scheduleUpdate();
    return true;

}

void GDMeshInstance3D::visit() {
    if (!this->m_bVisible || !m_mesh) return;
    if (!m_scene) {
        geode::log::error("ERROR : CCNode3D and any of it's derivatives must be assigned to a GDScene3D via node->addToScene(scene)! DO NOT add it via scene->addChild(node)!");
        return;
    }
    CCNode::visit();

    this->m_pShaderProgram->use();
    this->transform3D();
    m_material->updateExtraUniforms(this->m_pShaderProgram);
    glBindVertexArray(m_mesh->m_vao);

    glEnable(GL_DEPTH_TEST);
    glDisable(GL_BLEND);
    glDepthFunc(GL_LESS);
    glDrawElements(GL_TRIANGLES, static_cast<GLsizei>(m_mesh->m_indexCount), GL_UNSIGNED_SHORT, 0);
    glDisable(GL_DEPTH_TEST);

    glBindVertexArray(0);

    this->endTransform3D();
    
}

void GDMeshInstance3D::registerDevTools() {
    devtools::registerNode<GDMeshInstance3D>([](GDMeshInstance3D* node) {
        kmVec3 pos = node->getPosition3D();
        kmVec3 rot = node->getRotation3D();
        kmVec3 sca = node->getScale3D();
        kmVec3 skw = node->getSkew3D();
        kmVec3 alb = node->m_material->m_albedoBase;
        alb = {alb.x * 255.0f, alb.y * 255.0f, alb.z * 255.0f}; 
        float rough = node->m_material->m_roughnessBase * 100.0f;
        float metal = node->m_material->m_metallicBase * 100.0f;

        devtools::label("GDMeshInstance3D Properties");
        devtools::label("Mesh Transform");
        if (devtools::property("Position", pos.x)) { node->setPositionX(pos.x); }
        if (devtools::property("Y Position", pos.y)) { node->setPositionY(pos.y); }
        if (devtools::property("Z Position", pos.z)) { node->setPositionZ(pos.z); }

        if (devtools::property("X Rotation", rot.x)) { node->setRotationX(rot.x); }
        if (devtools::property("Y Rotation", rot.y)) { node->setRotationY(rot.y); }
        if (devtools::property("Z Rotation", rot.z)) { node->setRotationZ(rot.z); }

        if (devtools::property("X Scale", sca.x)) { node->setScaleX(sca.x); }
        if (devtools::property("Y Scale", sca.y)) { node->setScaleY(sca.y); }
        if (devtools::property("Z Scale", sca.z)) { node->setScaleZ(sca.z); }

        if (devtools::property("X Skew", skw.x)) { node->setSkewX(skw.x); }
        if (devtools::property("Y Skew", skw.y)) { node->setSkewY(skw.y); }
        if (devtools::property("Z Skew", skw.z)) { node->setSkewZ(skw.z); }

        devtools::label("Material Properties (" + node->m_material->getMaterialKey() + ")");
        devtools::label("0-255");
        if (devtools::property("Albedo Base R", alb.x)) { node->m_material->m_albedoBase.x = alb.x / 255.0f; }
        if (devtools::property("Albedo Base G", alb.y)) { node->m_material->m_albedoBase.y = alb.y / 255.0f; }
        if (devtools::property("Albedo base B", alb.z)) { node->m_material->m_albedoBase.z = alb.z / 255.0f; }
        devtools::label("0-100");
        if (devtools::property("Roughness", rough)) { node->m_material->m_roughnessBase = rough / 100.0f; }
        if (devtools::property("Metallic", metal)) { node->m_material->m_metallicBase = metal / 100.0f; }

        devtools::label("Has Albedo texture: " + ((node->m_material->hasAlbedoTx()) ? std::string("Yes") : std::string("No")));
        devtools::label("Has Roughness texture: " + ((node->m_material->hasRoughnessTx()) ? std::string("Yes") : std::string("No")));
        devtools::label("Has Metallic texture: " + ((node->m_material->hasMetallixTx()) ? std::string("Yes") : std::string("No")));
    });
}
void GDMeshInstance3D::update(float dt) {
    float currentRotY = this->getRotationY();
    
    this->setRotationY(currentRotY + 25.0f * dt);
}

$on_mod(Loaded) {
    devtools::waitForDevTools([] {
        GDMeshInstance3D::registerDevTools();
    });
}