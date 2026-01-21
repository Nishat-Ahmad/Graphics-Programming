#version 330 core
layout (location = 0) in vec3 aPos;
layout (location = 1) in vec2 aTexCoord;

out vec2 TexCoord;

// This is the matrix we will send from C++
uniform mat4 transform;

void main()
{
    // Apply the transformation matrix to the position
    // Note: Read from Right to Left (Transform * Position)
    gl_Position = transform * vec4(aPos, 1.0);
    TexCoord = aTexCoord;
}