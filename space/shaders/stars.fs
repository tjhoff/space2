uniform sampler2D tex;

varying vec2 f_texcoord;

void main(){
	
	vec4 color = texture2D(tex, f_texcoord);
	gl_FragColor = color;
}
