include(`foreach.m4')dnl
divert(`-1')
// Matching comments to GLSL comments:
changecom(`//') 

// You'll notice we "undefine" on declaration to avoid causing a loop of dependencies.
define(`importItem', `define(`$1', `dnl
undefine(`$1')dnl
$2
')')

// Import system by just defining a bunch of macros to "import".
define(`import', `dnl
divert(-1)

importItem(`inVertex', `dnl
layout (location=0) in vec4 position;
layout (location=1) in vec3 normal;
layout (location=2) in vec2 texcoord;')

importItem(`inFrag', `in vec4 vertPos;')

// PI Definition.
importItem(`pi', `#define M_PI 3.14159265358979323846')

importItem(`rand', `dnl
float rand(vec2 co){
	return fract(sin(dot(co, vec2(12.9898, 78.233))) * 43758.5453);
}')

// Perlin noise.
importItem(`noise', `dnl
pi()

// From https://gist.github.com/patriciogonzalezvivo/670c22f3966e662d2f83

rand()

float noise(vec2 p, float freq ){
	float unit = 100.0/freq;
	vec2 ij = floor(p/unit);
	vec2 xy = mod(p,unit)/unit;
	//xy = 3.*xy*xy-2.*xy*xy*xy;
	xy = .5*(1.-cos(M_PI*xy));
	float a = rand((ij+vec2(0.,0.)));
	float b = rand((ij+vec2(1.,0.)));
	float c = rand((ij+vec2(0.,1.)));
	float d = rand((ij+vec2(1.,1.)));
	float x1 = mix(a, b, xy.x);
	float x2 = mix(c, d, xy.x);
	return mix(x1, x2, xy.y);
}

float pNoise(vec2 p, int res){
	float persistance = .5;
	float n = 0.;
	float normK = 0.;
	float f = 4.;
	float amp = 1.;
	int iCount = 0;
	for (int i = 0; i<50; i++){
		n+=amp*noise(p, f);
		f*=2.;
		normK+=amp;
		amp*=persistance;
		if (iCount == res) break;
		iCount++;
	}
	float nf = n/normK;
	return nf*nf*nf*nf;
}')

// From https://learnopengl.com/Lighting/Multiple-lights
importItem(`pointLight', `dnl
struct PointLight {
	vec3 position;

	float constant;
	float linear;
	float quadratic;

	vec3 ambient;
	vec3 diffuse;
	vec3 specular;
};

vec3 CalculatePointLight(PointLight light, vec3 normal, vec3 fragPos, vec3 viewDir) {
	vec3 lightDir = normalize(light.position - fragPos);
    // diffuse shading
    float diff = max(dot(normal, lightDir), 0.0);
    // specular shading
    vec3 reflectDir = reflect(-lightDir, normal);
    float spec = pow(max(dot(viewDir, reflectDir), 0.0), material.shininess);
    // attenuation
    float distance    = length(light.position - fragPos);
    float attenuation = 1.0 / (light.constant + light.linear * distance + 
  			     light.quadratic * (distance * distance));    
    // combine results
    vec3 ambient  = light.ambient  * vec3(texture(material.diffuse, TexCoords));
    vec3 diffuse  = light.diffuse  * diff * vec3(texture(material.diffuse, TexCoords));
    vec3 specular = light.specular * spec * vec3(texture(material.specular, TexCoords));
    ambient  *= attenuation;
    diffuse  *= attenuation;
    specular *= attenuation;
    return (ambient + diffuse + specular);
}')

// And then copy our import list, to import what we want:
divert(0)dnl
foreach(`x', ($*), `x
')')
divert