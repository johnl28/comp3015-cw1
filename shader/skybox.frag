#version 460 core

out vec4 FragColor;

in vec3 FragCoord;


void main()
{    
    float dist = distance(normalize(FragCoord).y, 1);

    vec4 startColor = vec4(107, 176, 255, 255) / 255;
    vec4 endColor = vec4(0, 55, 117, 255) / 255;

    FragColor = mix(endColor, startColor, dist);
}

