#version 330 core
layout (location = 0) in vec3 aPos;
layout (location = 1) in vec2 aTexCoord;

out vec2 TexCoord;

// We now have 3 matrices instead of 1
uniform mat4 model;
uniform mat4 view;
uniform mat4 projection;

void main()
{
    // Note: Multiplication is read from Right to Left
    // 1. Transform Local to World (model)
    // 2. Transform World to View (view)
    // 3. Transform View to Clip (projection)
    gl_Position = projection * view * model * vec4(aPos, 1.0);
    TexCoord = aTexCoord;
}