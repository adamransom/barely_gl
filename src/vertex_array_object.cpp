//
// vertex_array_object.cpp
// Copyright (c) 2015 Adam Ransom
//

#include <OpenGL/gl3.h>
#include "vertex_array_object.h"
#include "vertex_buffer_object.h"
#include "index_buffer_object.h"
#include "exception.h"

namespace BarelyGL {
VertexArrayObject::VertexArrayObject()
{
  generate_array();
}

VertexArrayObject::VertexArrayObject(const VertexAttributeArray& attributes,
                                     const VertexBufferObject* vertex_buffer,
                                     const IndexBufferObject* index_buffer)
  : vertex_buffer_(vertex_buffer)
  , index_buffer_(index_buffer)

{
  generate_array();
  set_attributes(attributes);
}

VertexArrayObject::~VertexArrayObject()
{
  destroy();
}

void VertexArrayObject::bind() const
{
  glBindVertexArray(id_);
}

void VertexArrayObject::set_attributes(const VertexAttributeArray& attributes)
{
  vertex_size_ = attributes.size();
}

void VertexArrayObject::set_vertex_buffer(const VertexBufferObject* buffer)
{
  vertex_buffer_ = buffer;
}

void VertexArrayObject::set_index_buffer(const IndexBufferObject* buffer)
{
  index_buffer_ = buffer;
}

void VertexArrayObject::draw(const GLenum mode, const IndexBufferObject* indices) const
{
  if (indices == nullptr)
  {
    draw_arrays(mode, static_cast<GLsizei>(vertex_buffer_->size() / vertex_size_));
  }
  else
  {
    index_buffer_->bind();
    draw_elements(mode);
    index_buffer_->unbind();
  }
}

void VertexArrayObject::unbind() const
{
  glBindVertexArray(0);
}

//
// =============================
//        Private Methods
// =============================
//

void VertexArrayObject::generate_array()
{
  glGenVertexArrays(1, &id_);

  if (id_ == 0) throw Exception("Could not generate vertex array");
}

void VertexArrayObject::draw_arrays(const GLenum mode, const GLsizei count) const
{
  glDrawArrays(mode, 0, count);
}

void VertexArrayObject::draw_elements(const GLenum mode) const
{
  glDrawElements(mode, static_cast<GLsizei>(index_buffer_->size()), GL_UNSIGNED_INT, 0);
}

void VertexArrayObject::destroy()
{
  if (id_ != 0)
  {
    glDeleteVertexArrays(1, &id_);
  }
}
} // end of namespace BarelyGL
