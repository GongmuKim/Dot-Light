
#ifdef GL_ES
precision mediump float;
#endif
//#include <cmath>
//#include <GL/glut.h>
//texture 0
//uniform sampler2D u_texture;

uniform float off;
uniform float r_angle,r_angle2;
uniform float width;

//our screen resolution, set from Java whenever the display is resized
uniform vec2 resolution;
uniform vec2 pos;
uniform vec2 sprite_start;
uniform vec2 pos1;
uniform vec2 pos2;
uniform vec2 pos3;

//in attributes from our vertex shader
varying vec2 v_texCoord;
varying vec4 v_fragmentColor;



float get_dist(vec2 h_pos, vec2 pos1, vec2 pos2, float angles)
{
    float a,b=1.0,c,a_div_b,c_div_b,dist=1.0;
    
    a_div_b=(pos2.y-pos1.y)/(pos2.x-pos1.x);
    a_div_b=a_div_b-a_div_b-a_div_b;
    c_div_b=(pos1.y+a_div_b*pos1.x);
    c_div_b=c_div_b-c_div_b-c_div_b;
    a=a_div_b,c=c_div_b;
    float aabb=a*a+b*b;
    dist=abs(a*h_pos.x+b*h_pos.y+c)/sqrt(aabb);
    float a2=1.0/a,b2=1.0,c2;
    c2=h_pos.y-(h_pos.x*a2);

    


    vec2 res;
    res.x=(c+c2)/(a2+a);
    res.x=res.x-res.x-res.x;
    res.y=a*res.x;
    res.y=res.y-res.y-res.y;
    res.y=res.y-c;


    if((angles>=88.5&&angles<=91.5)||(angles>=268.5&&angles<=271.5)){
       if(pos1.x>h_pos.x)dist=pos1.x-h_pos.x;
       else dist=h_pos.x-pos1.x;
       res.x=pos1.x;
       res.y=h_pos.y;
    }

    else if((angles>=179.0&&angles<=181.0)||(angles>=0.0&&angles<=1.0)|| (angles>=359.0&&angles<=360.0)){
       if(pos1.y>h_pos.y)dist=pos1.y-h_pos.y;
       else dist=h_pos.y-pos1.y;
       res.x=h_pos.x;
       res.y=pos1.y;
    }
 
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

float sqrts(float value, int cnt)
{
   for(int i=1;i<=cnt;i++)
   {
      value=sqrt(value);
   }
   return value;
}

void main() {
    //sample our texture



    vec4 texColor = texture2D(CC_Texture0, v_texCoord).rgba;
/*
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


*/
    float len=1.0;
    vec2 h_pos=v_texCoord.xy;
    h_pos.x*=resolution.x;
    h_pos.y=1.0-h_pos.y;
    h_pos.y*=resolution.y;
    h_pos.x+=sprite_start.x,h_pos.y+=sprite_start.y;
    
    float dist=get_dist(h_pos,pos1,pos2,r_angle);
    float dist2=get_dist(h_pos,pos2,pos3,r_angle2);
    //float dist=1.0,dist2=1.0;
    
    
    if(dist>dist2) dist=dist2;
    len=sqrts(dist,2)/sqrts(width,2);
    //show our length for debugging
    //len*=off;
    float gg = dot(texColor.rgb, vec3(1.0-len, 1.0-len, 1.0-len));
    if(off<0.5) gl_FragColor=texColor;
    else gl_FragColor = vec4(gg, gg, gg,1.0);//1.0으로고치기
    //gl_FragColor = vec4(texColor*vec3(1.0-len) ,1.0);


    // vec4 color = texture2D(CC_Texture0, v_texCoord).rgba;
      //  float grey = dot(color.rgb, vec3(0.1, 0.1, 0.1));
      //  gl_FragColor = vec4(grey, grey, grey,color.a);



}



/*
#ifdef GL_ES
        precision mediump float;
        #endif
        varying vec2 v_texCoord; 
        varying vec4 v_fragmentColor;
        void main(void)
        {
        // Convert to greyscale using NTSC weightings
        vec4 color = texture2D(CC_Texture0, v_texCoord).rgba;
        float grey = dot(color.rgb, vec3(0.1, 0.1, 0.1));
        gl_FragColor = vec4(grey, grey, grey,color.a);
        }
	*/