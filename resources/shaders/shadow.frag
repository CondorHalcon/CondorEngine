#version 330 core

void main()
{             
    gl_FragDepth = gl_FragCoord.z; // would also work without this line
}
