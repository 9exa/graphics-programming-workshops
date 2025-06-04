#version 450 core

layout (location = 0) in vec3 aPos;
layout (location = 1) in vec3 aCol;

uniform float time;

out vec3 col;
void main()
{
   gl_Position = vec4(
           aPos.x + aPos.x * sin(aPos.y * aPos.y * time), 
           aPos.y + aPos.y * cos(time), 
           aPos.z, 
           1.0
    );

   col = aCol; 
}
