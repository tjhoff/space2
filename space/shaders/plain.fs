/*varying vec2 f_texcoord;
varying vec4 color;
uniform sampler2D tex;

void main(){

	vec4 txcolor = texture2D(tex, f_texcoord);
	gl_FragColor = vec4(txcolor.xyz, 1)*color;
}*/



varying vec2 f_texcoord;
varying vec4 v_pos;
varying vec3 v_norm;
varying vec3 v_view;

uniform sampler2D tex;

struct light{
	vec4 pos;
};

light l0 = light(vec4(0.0,-1.0,0.5,0.0));

void main(){

	vec3 norm_dir = v_norm;
	vec3 light_dir;

	light_dir = normalize(vec3(l0.pos));
	
	vec3 diffRef = vec3(.5,.5,.5) * max(0.0,dot(norm_dir, light_dir));

	vec3 specRef;
	
	if (dot(norm_dir, light_dir) < 0.0){
		specRef = vec3(0,0,0);
	}
	else {
		specRef= vec3(.1,.0,.1), pow(max(0.0,dot(reflect(-light_dir, norm_dir), v_view)), 12.0);
	}
	
	vec4 txcolor = texture2D(tex, f_texcoord);
	vec4 color = vec4((vec3(.1,.1,.1)+diffRef) * txcolor.xyz + specRef, 1);
	gl_FragColor = color;
}
