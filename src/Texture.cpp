//
// Texture.cpp
// Copyright (c) 2015 Adam Ransom
//

#include "Texture.h"
#include <OpenGL/gl3.h>
#include "Exception.h"

namespace GL {
Texture::Texture(const int width, const int height, const void* pixels)
  : width_(width)
  , height_(height)
{
  generate();
  bind();
  set_data(pixels);
  set_parameters();
  unbind();
}

void Texture::bind() const
{
  glBindTexture(GL_TEXTURE_2D, id_);
}

/*
 * Uploads the image data to graphics card
 */
void Texture::set_data(const void* data)
{
  data_ = data;

  glTexImage2D(GL_TEXTURE_2D,    // target of the texture
               0,                // mipmap level
               GL_RGB,           // internal color format
               width_,           // width of texture
               height_,          // height of texture
               0,                // border (must be 0)
               GL_BGR,           // format of texture being uploaded
               GL_UNSIGNED_BYTE, // type of pixel data being uploaded
               data_             // pixel data
              );
}

void Texture::unbind() const
{
  glBindTexture(GL_TEXTURE_2D, 0);
}

void Texture::destroy()
{
  if (id_ != 0)
  {
    glDeleteTextures(1, &id_);
  }
}

//
// =============================
//        Private Methods
// =============================
//

void Texture::generate()
{
  glGenTextures(1, &id_);

  if (id_ == 0) throw Exception("Could not generate texture");
}

/*
 * Sets the texture paramaters. This makes sure the texture doesn't wrap and
 * uses a linear filter for resizing
 */
void Texture::set_parameters()
{
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_BORDER);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_BORDER);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
}

Texture::~Texture()
{
  destroy();
}
}
