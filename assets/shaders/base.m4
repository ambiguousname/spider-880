divert(-1)
// Matching comments to GLSL comments:
changecom(`//') 


// Import system by just defining a bunch of macros to "import".
define(`import', `dnl
divert(-1)

// PI Definition.
// You'll notice we "undefine" on declaration to avoid causing a loop of dependencies.
define(`pi', `undefine(`pi')dnl
#define M_PI 3.14159265358979323846')

define(`rand', `undefine(`rand')dnl
float rand(vec2 co){
	return fract(sin(dot(co, vec2(12.9898, 78.233))) * 43758.5453);
}')

// Perlin noise.
define(`noise', `dnl
undefine(`noise')dnl
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
}dnl
')

// And then copy our import list, to import what we want:
divert
$* dnl
')

divert