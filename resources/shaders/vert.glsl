attribute vec3 a_position;
attribute vec4 a_color;
attribute vec2 a_texCoord;
attribute vec3 a_normal;

uniform mat4 ModelMatrix;

#ifdef GL_ES
varying mediump vec2 v_texCoord;
varying mediump vec3 v_normal;
varying mediump vec4 v_color;
#else
varying vec2 v_texCoord;
varying vec3 v_normal;
varying vec4 v_color;
#endif

void main() {
    gl_Position = CC_MVPMatrix * vec4(a_position, 1.0);
    v_texCoord = a_texCoord;
    v_normal = mat3(transpose(inverse(ModelMatrix))) * a_normal;
    v_color = a_color;
} 