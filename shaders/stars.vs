attribute vec3 vertex;
attribute vec2 texcoord;

varying vec2 f_texcoord;

void main(){
	f_texcoord = texcoord;
	vec4 vx_transform = (gl_ModelViewProjectionMatrix*vec4(vertex.xyz,1));
	gl_Position = vx_transform;
}
