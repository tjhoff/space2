/* vec3 vertex;
attribute vec3 normal;
attribute vec2 texcoord;

varying vec2 f_texcoord;
varying vec4 color;

struct light{
	vec4 pos;
};

light l0 = light(
	vec4(1.0,0.0,1.0,.0)
);

void main(){
	f_texcoord = texcoord;
	
	vec3 normDir = normalize(gl_NormalMatrix * normal);
	
	vec3 lightDir;
	
	if (l0.pos.w == 0.0){
		lightDir = normalize(vec3(l0.pos.xyz));
	}
	
	vec3 diffRef = vec3(1,1,1)*max(dot(normDir, lightDir),0.0);
	
	vec4 vx_transform = (gl_ModelViewProjectionMatrix*vec4(vertex.xyz,1));
	
	color = vec4(diffRef,1.0);
	
	gl_Position = vx_transform;
}*/

attribute vec3 vertex;
attribute vec3 normal;
attribute vec2 texcoord;

varying vec4 v_pos;
varying vec3 v_norm;
varying vec2 f_texcoord;
varying vec3 v_view;

void main(){
	f_texcoord = texcoord;
	
	v_norm = normalize(gl_NormalMatrix * normal);
	
	v_pos = gl_ModelViewMatrix * vec4(vertex,1);
	
	v_view = -(v_pos.xyz + vec3(0,0,1000));
		
	vec4 vx_transform = (gl_ModelViewProjectionMatrix*vec4(vertex.xyz,1));
	
	
	gl_Position = vx_transform;
}
