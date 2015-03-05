//
// IndexBufferObject.cpp
// Copyright (c) 2015 Adam Ransom
//

#include "IndexBufferObject.h"
#include <OpenGL/gl3.h>
#include <iostream>
#include "Exception.h"

namespace GL {
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
void IndexBufferObject::set_indices(const std::vector<int> indices)
{
  indices_ = indices;

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
}
