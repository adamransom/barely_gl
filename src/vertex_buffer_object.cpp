//
// vertex_buffer_object.cpp
// Copyright (c) 2015 Adam Ransom
//

#include <iostream>
#include <OpenGL/gl3.h>
#include "vertex_buffer_object.h"
#include "index_buffer_object.h"
#include "exception.h"

namespace BarelyGL {
VertexBufferObject::VertexBufferObject(const GLenum target, const GLenum usage)
  : target_(target)
  , usage_(usage)
{
  generate_buffer();
}

void VertexBufferObject::bind() const
{
  glBindBuffer(target_, id_);
}

void VertexBufferObject::init_buffer(const GLsizeiptr size)
{
  glBufferData(target_, size * sizeof(float), 0, usage_);
}

void VertexBufferObject::set_vertices(const std::vector<float>& vertices)
{
  vertex_count_ = vertices.size();
  glBufferData(target_, vertices.size() * sizeof(float), vertices.data(), usage_);
}

void VertexBufferObject::sub_vertices(const std::vector<float>& vertices, const GLintptr offset)
{
  vertex_count_ = vertices.size();
  glBufferSubData(target_, offset, vertices.size() * sizeof(float), vertices.data());
}

void VertexBufferObject::unbind() const
{
  glBindBuffer(target_, 0);
}

VertexBufferObject::~VertexBufferObject()
{
  destroy();
}

//
// =============================
//        Private Methods
// =============================
//

void VertexBufferObject::generate_buffer()
{
  glGenBuffers(1, &id_);

  if (id_ == 0) throw Exception("Could not generate buffer");
}

void VertexBufferObject::destroy()
{
  if (id_ != 0)
  {
    glDeleteBuffers(1, &id_);
  }
}
} // end of namespace BarelyGL
