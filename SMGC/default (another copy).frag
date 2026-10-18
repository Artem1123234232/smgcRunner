#version 460 core
out vec4 fragColor;

uniform float iTime;
uniform vec2 iMouse;
uniform vec2 iResolution;

float smin( float a, float b, float k )
{
     k *= log ( 2.0 );
     float x = (b-a)/k;
     float g = x/( 1.0 - exp (-x));
     return b - k * g; 
}
float Sphere(vec4 sphere, vec3 p)

{

    return length(p - sphere.xyz) - sphere.w;

}
float Amoeba(in vec4 amoeba, in vec3 p)
{
    vec3 q = p-amoeba.xyz;
    float h2 = Sphere(vec4(vec3(-0.75*amoeba.w,0.0,0)+amoeba.xyz,1.5*amoeba.w), q);
    float h1 = Sphere(vec4(vec3(0,0.0,0)+amoeba.xyz,1.5*amoeba.w), q);
    float h0 = Sphere(vec4(vec3(0,1.5*amoeba.w,0)+amoeba.xyz,1.5*amoeba.w),q);
    return smin(smin(h0, h1, 0.75*amoeba.w),h2, 0.75*amoeba.w);
}

float mapWater(in vec3 p)
{
    bool isamoeba = false;//Amoeba or Sphere
    float ts = 5.0;// Speed
    float displacement = sin(5.0 * p.x + iTime*ts) * sin(5.0 * p.y + iTime*ts) * sin(5.0 * p.z + iTime*ts) * 0.25 * 0.25;
    if (isamoeba)
    {
        float amoeba_0 = Amoeba(vec4(0,0,0,0.5), p);
        return amoeba_0 + displacement/2.0;
    }
    else
    {
        float sphere_0 = Sphere(vec4(0,0,0,1), p);
        return sphere_0 + displacement;
    }
}
float mapNormal(in vec3 p)
{
    float dz = sin(iTime);
    float d0 = Sphere(vec4(0,1,dz,1), p);
    return(d0);
}
vec3 WaterNormal(in vec3 p)
{
    const vec3 small_step = vec3(0.001, 0.0, 0.0);
    float gradient_x = mapWater(p + small_step.xyy) - mapWater(p - small_step.xyy);
    float gradient_y = mapWater(p + small_step.yxy) - mapWater(p - small_step.yxy);
    float gradient_z = mapWater(p + small_step.yyx) - mapWater(p - small_step.yyx);
    vec3 normal = vec3(gradient_x, gradient_y, gradient_z);
    return normalize(normal);
}
vec3 NormalNormal(in vec3 p)
{
    const vec3 small_step = vec3(0.001, 0.0, 0.0);
    float gradient_x = mapNormal(p + small_step.xyy) - mapNormal(p - small_step.xyy);
    float gradient_y = mapNormal(p + small_step.yxy) - mapNormal(p - small_step.yxy);
    float gradient_z = mapNormal(p + small_step.yyx) - mapNormal(p - small_step.yyx);
    vec3 normal = vec3(gradient_x, gradient_y, gradient_z);
    return normalize(normal);
}
vec3 ColMix(vec3 col1, vec3 col2, float val)
{
    return(col1*val+col2*(1.0-val));
}
vec3 ray_march(in vec3 ro, in vec3 rd)
{
    vec3 col = vec3(0.5,0.5,0.5);
    float total_distance_traveled = 0.0;
    bool water = false;
    for (int i = 0; i < 1000; i++)
    {
        vec3 p = ro + total_distance_traveled * rd;
        float Dist = mapNormal(p);
        float Dist2 = mapWater(p);
        if (Dist < 0.001) 
        {
            vec3 normal = NormalNormal(p);
            vec3 light_position = vec3(2.0, -5.0, 3.0);
            vec3 direction_to_light = normalize(p - light_position);
            float diffuse_intensity = max(0.0, dot(normal, direction_to_light));
            float light = (diffuse_intensity*0.5+0.5)*1.05;
            col = vec3(1,0.5,1)*light;
            break;
        }
        if (Dist2 < 0.001)
        {
            water = true;
        }
        if (total_distance_traveled > 50.0)
        {
            break;
        }
        total_distance_traveled += min(Dist, max(Dist2,0.1));
    }
    
    total_distance_traveled = 0.0;
    
    if(water)
    {
        for (int i = 0; i < 20; ++i)
        {
            vec3 current_position = ro + total_distance_traveled * rd;
            float Dist = mapWater(current_position);
            if (Dist < 0.001) 
            {
                vec3 normal = WaterNormal(current_position);
                vec3 light_position = vec3(2.0, -5.0, 3.0);
                vec3 direction_to_light = normalize(current_position - light_position);
                float diffuse_intensity = max(0.0, dot(normal, direction_to_light));
                float light = (diffuse_intensity*0.5+0.5)*1.05;//1.05 is adjusting the glare level
                col = ColMix(vec3(0,0,0),ColMix(vec3(1,1,1),ColMix(col, vec3(0.0, 0.5, 1.0)*light,0.99), max(light-1.0,0.0)),max(0.0,min(Dist*500.,0.1)));
            }
            if (total_distance_traveled > 50.0)
            {
                return col;
            }
            total_distance_traveled += Dist;
        }
    }
    return col;
}
void main()
{
    bool Rotate = false; //Rotate camera
    bool RotateWithMouse = true; //Rotate camera with mouse *IF ROTATE TRUE!*
    vec3 ro; vec3 rd; vec2 uv;
    if (Rotate)
    {
        uv = (gl_FragCoord.xy - iResolution.xy / 2.0) / min(iResolution.x, iResolution.y);
        uv.x *= -1.0;
        float r     = 5.0;
        float theta; float phi;
        if (!RotateWithMouse)
        {
            theta = iTime;//2.0*M_PI * (u_mouse.x / u_resolution.x - 0.25);
            phi   = 5.0;//0.5*M_PI * (u_mouse.y / u_resolution.y + 0.0001);
        }
        else
        {
            theta = 2.0*3.1415926 * (iMouse.x / iResolution.x - 0.25);
            phi   = 0.5*3.1415926 * (iMouse.y / iResolution.y + 0.0001)+1.5;
        }
        vec3 ta = vec3(0.0, 0.0, 0.0);
        ro = ta + r * vec3(sin(phi) * cos(theta), cos(phi), sin(phi) * sin(theta));
        vec3 ww = normalize(ta - ro);
        vec3 uu = normalize(cross(ww, vec3(0.0, 1.0, 0.0)));
        vec3 vv = normalize(cross(uu, ww));
        rd = normalize(uv.x*uu + uv.y*vv + ww);
    }
    else
    {
        uv = (gl_FragCoord.xy - iResolution.xy / 2.0) / min(iResolution.x, iResolution.y);
        ro = vec3(0.0, 0.0, -5.0);
        rd = vec3(uv, 1.0);
    }
    fragColor = vec4(ray_march(ro, rd), 1.0);
}