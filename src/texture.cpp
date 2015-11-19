//
// texture.cpp
// Copyright (c) 2015 Adam Ransom
//

#include <OpenGL/gl3.h>
#include "texture.h"
#include "exception.h"

namespace BarelyGL {
Texture::Texture(const int width, const int height, GLenum format, const void* pixels)
  : width_(width)
  , height_(height)
  , format_(format)
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
  glTexImage2D(GL_TEXTURE_2D,    // target of the texture
               0,                // mipmap level
               GL_RGBA8,         // internal color format
               width_,           // width of texture
               height_,          // height of texture
               0,                // border (must be 0)
               format_,          // format of texture being uploaded
               GL_UNSIGNED_BYTE, // type of pixel data being uploaded
               data              // pixel data
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
} // end of namespace BarelyGL
