#ifdef GL_ES
precision highp float;
#endif

uniform vec3 albedo_base;
uniform float roughness_base;
uniform float metallic_base;
uniform float ao_base;

uniform int has_albedo_tex;
uniform int has_roughness_tex;
uniform int has_metallic_tex;

varying vec4 v_color;
varying vec2 v_texCoord;
varying vec3 v_normal;

uniform sampler2D albedo_texture;
uniform sampler2D roughness_texture;
uniform sampler2D metallic_texture;

vec4 albedo(vec2 uv) {
    return (has_albedo_tex ? texture2D(albedo_texture, uv) * vec4(albedo_base, 1) : vec4(albedo_base, 1)); 
}

float roughness(vec2 uv) {
    return (has_roughness_tex ? texture2D(roughness_texture, uv).r * roughness_base : roughness_base); 
}

float metallic(vec2 uv) {
    return (has_metallic_tex ? texture2D(metallic_texture, uv).r * metallic_base : metallic_base); 
}

void main() {
    vec4 texColor = albedo(v_texCoord);
    //gl_FragColor = vec4(0.5 + (v_normal * 0.5) , 1) * texColor;
    gl_FragColor = texColor;
}