#ifndef TEXTURE_H
#define TEXTURE_H

#include <glad/glad.h>

class Texture2D
{
public:
    unsigned int ID;
    unsigned int Width, Height; // Texture image dimensions
    unsigned int Internal_Format; // Format of texture object
    unsigned int Image_Format; // Format of loaded image

    unsigned int Wrap_S; // Wrapping mode on S axis
    unsigned int Wrap_T; // Wrapping mode on T axis
    unsigned int Filter_Min; // Filtering mode if texture pixels < screen pixels
    unsigned int Filter_Max; // Filtering mode if texture pixels > screen pixels

    Texture2D();
    void Generate(unsigned int width, unsigned int height, unsigned char* data);
    void Bind() const;
};

#endif