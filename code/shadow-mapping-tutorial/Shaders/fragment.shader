#version 110

void main()
{
    gl_FragColor = vec4(vec3(depthValue), 1.0);
}