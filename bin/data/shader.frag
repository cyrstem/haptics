#version 330
precision highp float;

#define TWO_PI 6.283185307179586476925286766559f

out vec4 outputColor;
uniform float time;
uniform sampler2DRect fboTex;
in vec4 verts;
in vec2 texCoordVarying;

/* Light positions */
const vec3 spotLight1 = normalize(vec3(0.1725, 0.1725, 1.0));

vec2 vInvert( vec2 _st ) {
    return vec2( 0.0, 1.0 ) + vec2( 1.0, -1.0 ) * _st;
}

void main(){

    /* Im not using this but you can get the pixel coords with this */
    vec2 pos = vec2(gl_FragCoord.x, gl_FragCoord.y) / 600.; // Generally divide by height and width
    pos = pos * 2.0 - 1.0; // then scale if you want
    //colors
    vec4 baseColor = texture(fboTex,texCoordVarying);


    /* Normalize verts from the vertex shader */
    vec3 normal = normalize(verts.xyz);

    /* Basic diffuse lighting */
    float diffuse1 = pow(max(0., dot(normal, spotLight1)), 2.);

    /* Output the color */
    outputColor = vec4(vec3(diffuse1 + 0.0625),1.0);
    

}