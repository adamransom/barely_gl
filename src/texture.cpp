//
// texture.cpp
// Copyright (c) 2015 Adam Ransom
//

#include <OpenGL/gl3.h>
#include "texture.h"
#include "exception.h"
#include <iostream>

namespace BarelyGL {
Texture::Texture(const int width, const int height, const GLenum format,
                 const GLenum internal_format, const uint8_t unpack_alignment, const void* pixels)
  : width_(width)
  , height_(height)
  , format_(format)
  , unpack_alignment_(unpack_alignment)
{
  generate();
  bind();
  set_data(internal_format, pixels);
  set_parameters();
  unbind();
}

// Construct and default to an unpack alignment of 4 bytes, which is the most usual
Texture::Texture(int width, int height, GLenum format, GLenum internal_format, const void* pixels)
  : Texture(width, height, format, internal_format, 4, pixels) {};

// Construct and default to an internal format of GL_RGBA8
Texture::Texture(int width, int height, GLenum format, const void* pixels)
  : Texture(width, height, format, GL_RGBA8, pixels) {};

void Texture::bind() const
{
  glBindTexture(GL_TEXTURE_2D, id_);
}

void Texture::sub_data(const int x_offset, const int y_offset, const int width, const int height,
                       const void* data)
{

  glPixelStorei(GL_UNPACK_ALIGNMENT, unpack_alignment_);
  glTexSubImage2D(GL_TEXTURE_2D,    // target of the texture
                  0,                // mipmap level
                  x_offset,         // the x offset within the texture
                  y_offset,         // the y offset within the texture
                  width,            // width of texture
                  height,           // height of texture
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

void Texture::set_data(const GLenum internal_format, const void* data)
{
  glPixelStorei(GL_UNPACK_ALIGNMENT, unpack_alignment_);
  glTexImage2D(GL_TEXTURE_2D,    // target of the texture
               0,                // mipmap level
               internal_format,  // internal color format
               width_,           // width of texture
               height_,          // height of texture
               0,                // border (must be 0)
               format_,          // format of texture being uploaded
               GL_UNSIGNED_BYTE, // type of pixel data being uploaded
               data              // pixel data
              );
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
