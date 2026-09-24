#include "../../include/ShaderManager.hpp"
#include "../../include/3DAPI.h"

using namespace zaxis;

CCGLProgram* ShaderManager::getOrCreateShaderFromFile(const char* vert, const char* frag, const char* shaderName) {
    CCGLProgram* shader = CCShaderCache::sharedShaderCache()->programForKey(shaderName);
    if (shader) return shader;
    shader = new CCGLProgram();

    std::filesystem::path vPath(vert);
    std::filesystem::path fPath(frag);
    
    unsigned long vSize = 0;
    unsigned long fSize = 0;

    unsigned char* vSrc = cocos2d::CCFileUtils::sharedFileUtils()->getFileData(vPath.string().c_str(), "r", &vSize);
    unsigned char* fSrc = cocos2d::CCFileUtils::sharedFileUtils()->getFileData(fPath.string().c_str(), "r", &fSize);

    if (!vSrc || !fSrc) {
        geode::log::error("ERROR : Shader '{}' read error! Are file names valid?", shaderName);
        delete[] vSrc;
        delete[] fSrc;
        shader->release();
        return nullptr;
    }

    std::string vStr(reinterpret_cast<char*>(vSrc), vSize);
    std::string fStr(reinterpret_cast<char*>(fSrc), fSize);

    delete[] vSrc;
    delete[] fSrc;

    if (!shader->initWithVertexShaderByteArray(vStr.c_str(), fStr.c_str())) {
        geode::log::error("ERROR : Shader '{}' failed to init! Failed to compile? Vertex input: \n{}\nFragment input: {}", shaderName, vStr, fStr);
        shader->release();
        return nullptr;
    }

    shader->addAttribute(kCCAttributeNamePosition, cocos2d::kCCVertexAttrib_Position);
    shader->addAttribute(kCCAttributeNameColor, cocos2d::kCCVertexAttrib_Color);
    shader->addAttribute(kCCAttributeNameTexCoord, cocos2d::kCCVertexAttrib_TexCoords);
    shader->addAttribute(ZAxisAPIAttribName_Normal, ZAxisAPIVertexAttrib_Normal);

    if (!shader->link()) {
        geode::log::error("ERROR : Shader '{}' failed to link!", shaderName);
        shader->release();
        return nullptr;
    }
    shader->updateUniforms();
    glUniform1i(glGetUniformLocation(shader->getProgram(), ZAxisAPIUniform_Albedo), 1);
    glUniform1i(glGetUniformLocation(shader->getProgram(), ZAxisAPIUniform_Roughness), 2);
    glUniform1i(glGetUniformLocation(shader->getProgram(), ZAxisAPIUniform_Metallic), 3);

    cocos2d::CCShaderCache::sharedShaderCache()->addProgram(shader, shaderName);
    geode::log::info("Compiled and linked Shader '{}' successfully.", shaderName);
    return shader;
}