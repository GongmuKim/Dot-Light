
#ifdef GL_ES
precision mediump float;
#endif
#include <cmath>
#include <GL/glut.h>
//texture 0
//uniform sampler2D u_texture;

uniform float off;

//our screen resolution, set from Java whenever the display is resized
uniform vec2 resolution,pos,sprite_start;
uniform vec2 pos1,pos2,pos3;

//"in" attributes from our vertex shader
varying vec4 vColor;
varying vec2 v_texCoord;
varying vec4 v_fragmentColor;

//RADIUS of our vignette, where 0.5 results in a circle fitting the screen
const float RADIUS = 0.75;

//softness of our vignette, between 0.0 and 1.0
const float SOFTNESS = 0.45;

//sepia colour, adjust to taste
const vec3 SEPIA = vec3(1.2, 1.0, 0.8); 

float get_dist(vec2 h_pos, vec2 pos1, vec2 pos2)
{
	float a,b=1,c,a_div_b,c_div_b;
    float dist=0;
    a_div_b=(pos2.y-pos1.y)/(pos2.x-pos1.x)*-1;
    c_div_b=(pos1.y+a_div_b*pos1.x)*-1;
    a=a_div_b,c=c_div_b;
    float aabb=a*a+b*b;
    dist=abs(a*h_pos.x+b*h_pos.y+c)/sqrt(aabb);

    float a2=1.0/a,b2=1,c2;
    c2=h_pos.y-(h_pos.x*a2);

    vec2 res;
    res.x=(c+c2)/(a2+a)*-1;
    res.y=-a*res.x-c;

    vec2 min,max;
    if(pos1.x>pos2.x) max.x=pos1.x,min.x=pos2.x;
    else  max.x=pos2.x,min.x=pos1.x;
    
    if(pos1.y>pos2.y) max.y=pos1.y,min.y=pos2.y;
    else  max.y=pos2.y,min.y=pos1.y;
    if(res.x<min.x||res.y<min.y||res.x>max.x||res.y>max.y){
        dist=length(pos1-h_pos),res=pos1;
	if(dist>length(pos2-h_pos)) dist=length(pos2-h_pos),res=pos2;
    }
    return dist;
}

void main() {
    //sample our texture
    vec4 texColor = texture2D(CC_Texture0, v_texCoord);

    pos.x=pos.x-sprite_start.x,pos.y=pos.y-sprite_start.y;

    //determine origin
    vec2 position = (v_texCoord) - vec2(pos.x/resolution.x,(resolution.y-pos.y)/resolution.y);
     //determine origin
    vec2 position2 = (v_texCoord) - vec2(0.5,0.5);

    float len3=length(position-position2),len4=length(position2-position);


    position.x *= resolution.x / resolution.y;

    //determine the vector length of the center position
    float len = length(position);

    position2.x *= resolution.x / resolution.y;

    //determine the vector length of the center position
    float len2 = length(position2);


    if(len>len2)len=len2;
    if(len<0.1) len=0;



    vec2 h_pos=v_texCoord.xy;
    h_pos.x*=resolution.x;
    h_pos.y=1.0-h_pos.y;
    h_pos.y*=resolution.y;
    h_pos.x+=sprite_start.x,h_pos.y+=sprite_start.y;
    
    float dist=get_dist(h_pos,pos1,pos2);
    float dist2=get_dist(h_pos,pos2,pos3);
    
    

    len=1.0;
    if(dist<20||dist2<20) len=0;
    //show our length for debugging
    len*=off;
    gl_FragColor = vec4(texColor*vec3(1.0-len) ,0.5);


}


/*
#ifdef GL_ES
precision mediump float;
#endif
uniform sampler2D u_texture;
varying vec2 v_texCoord;
varying vec4 v_fragmentColor;
void main(void)
{
        // Convert to greyscale using NTSC weightings
        vec4 color = texture2D(u_texture, v_texCoord).rgba;
        float grey = dot(color.rgb, vec3(0.299, 0.587, 0.114));
        gl_FragColor = vec4(grey, grey, grey, color.a);
}
*/
/*
#ifdef GL_ES
precision highp float;
#endif

//attributes from vertex shader
varying vec4 vColor;
varying vec2 v_texCoord;

//our texture samplers
//uniform sampler2D u_texture;   //diffuse map
uniform sampler2D u_normals;   //normal map

//values used for shading algorithm...
uniform vec2 Resolution=vec2(1920.0,1080.0);      //resolution of screen
uniform vec3 LightPos=vec3(100.0,100.0,100.0);        //light position, normalized
uniform vec4 LightColor=vec4(1.0,1.0,1.0,1.0);      //light RGBA -- alpha is intensity
uniform vec4 AmbientColor=vec4(1.0,1.0,1.0,1.0);    //ambient RGBA -- alpha is intensity 
uniform vec3 Falloff=vec3(1.0,1.0,1.0);         //attenuation coefficients

void main() {
    //RGBA of our diffuse color
    vec4 DiffuseColor = texture2D(CC_Texture0, v_texCoord);

    //RGB of our normal map
    vec3 NormalMap = texture2D(u_normals, v_texCoord).rgb;

    //The delta position of light
    vec3 LightDir = vec3(LightPos.xy - (gl_FragCoord.xy / Resolution.xy), LightPos.z);

    //Correct for aspect ratio
    LightDir.x *= Resolution.x / Resolution.y;

    //Determine distance (used for attenuation) BEFORE we normalize our LightDir
    float D = length(LightDir);

    //normalize our vectors
    vec3 N = normalize(NormalMap * 2.0 - 1.0);
    vec3 L = normalize(LightDir);

    //Pre-multiply light color with intensity
    //Then perform "N dot L" to determine our diffuse term
    vec3 Diffuse = (LightColor.rgb * LightColor.a) * max(dot(N, L), 0.0);

    //pre-multiply ambient color with intensity
    vec3 Ambient = AmbientColor.rgb * AmbientColor.a;

    //calculate attenuation
    float Attenuation = 1.0 / ( Falloff.x + (Falloff.y*D) + (Falloff.z*D*D) );

    //the calculation which brings it all together
    vec3 Intensity = Ambient + Diffuse * Attenuation;
    vec3 FinalColor = DiffuseColor.rgb * Intensity;
    gl_FragColor = vColor * vec4(FinalColor, DiffuseColor.a);
}*/