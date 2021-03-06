//
// index_buffer_object.cpp
// Copyright (c) 2015 Adam Ransom
//

#include <iostream>
#include <OpenGL/gl3.h>
#include "index_buffer_object.h"
#include "exception.h"

namespace BarelyGL {
IndexBufferObject::IndexBufferObject(const GLenum target, const GLenum usage)
  : target_(target)
  , usage_(usage)
{
  generate_buffer();
}

void IndexBufferObject::bind() const
{
  glBindBuffer(target_, id_);
}

/*
 * Uploads the vertices to the buffer object
 */
void IndexBufferObject::set_indices(std::vector<int> indices)
{
  indices_ = std::move(indices);

  glBufferData(target_, indices.size() * sizeof(int), indices.data(), usage_);
}

void IndexBufferObject::unbind() const
{
  glBindBuffer(target_, 0);
}

IndexBufferObject::~IndexBufferObject()
{
  destroy();
}

//
// =============================
//        Private Methods
// =============================
//

void IndexBufferObject::generate_buffer()
{
  glGenBuffers(1, &id_);

  if (id_ == 0) throw Exception("Could not generate buffer");
}

void IndexBufferObject::destroy()
{
  if (id_ != 0)
  {
    glDeleteBuffers(1, &id_);
  }
}
} // end of namespace BarelyGL
