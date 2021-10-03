#version 330 core

in vec2 pixel_position;

out vec4 fragment_color;

uniform float rounded;

float Length(vec2 vec, float e);

void main()
{
    if(pixel_position.y < 0.0f || Length(pixel_position, rounded) > 1.0f || Length(pixel_position, rounded) < 0.95f)
    {
        discard;
    }
    
    fragment_color = vec4(1.0f, 0.0f, 0.0f, 1.0f);
}

float Length(vec2 vec, float e)
{
    return vec.x * vec.x + (1.0f - e) * vec.t * (1.0f - e) * vec.y;
}
