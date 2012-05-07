uniform mat4 Modelview;
uniform mat4 Projection;

attribute vec4 Position;
attribute vec2 TexCoord0;

varying vec2 TexcoordVar;

void main(void) {

    gl_Position = Projection * Modelview * Position;
    TexcoordVar = TexCoord0;
    
}