uniform sampler2D Texture0;
varying lowp vec2 TexcoordVar;

void main(void) {
    
    gl_FragColor = texture2D(Texture0, TexcoordVar);
    
}