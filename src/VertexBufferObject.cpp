//
// VertexBufferObject.cpp
// Copyright (c) 2015 Adam Ransom
//

#include "VertexBufferObject.h"
#include <OpenGL/gl3.h>
#include <iostream>
#include "Exception.h"
#include "IndexBufferObject.h"

namespace GL {
VertexBufferObject::VertexBufferObject(GLenum target, GLenum usage)
  : target_(target)
  , usage_(usage)
{
  generate_buffer();
}

void VertexBufferObject::bind()
{
  glBindBuffer(target_, id_);
}

/*
 * Uploads the vertices to the buffer object
 */
void VertexBufferObject::set_vertices(const std::vector<float> vertices)
{
  vertices_ = vertices;

  glBufferData(target_, vertices.size() * sizeof(float), vertices.data(), usage_);
}

void VertexBufferObject::set_attributes(const std::vector<VertexAttribute> attributes)
{
  attributes_ = attributes;
  
  vertex_size_ = 0;

  for (auto attr : attributes_)
  {
    vertex_size_ += attr.size;
  }
}

/*
 * Draws the vertices using the supplied attributes in arrays mode
 */
void VertexBufferObject::draw(GLenum mode)
{
  draw(mode, nullptr);
}

void VertexBufferObject::draw(GLenum mode, IndexBufferObject* indices)
{
  int cur_offset = 0;
  /*
   * Each vertex contains the position for the vertex and some extra data. To
   * let the shader know which data is which you specify attributes. For
   * example, one vertex in the array might be:
   *    10, 20, 0, 1, 0 (which describes x, y, z, u, v)
   * The attribute pointer tells the shader that the first 3 values are a vec3
   * and the last 2 values are a vec2. These are then assigned to locations in
   * the shader (these positions are specified by the index `i` below) and can
   * be retrieve by using (in the shader):
   *    (location = 0) vec3 position;
   *    (location = 1) vec2 uv;
   */
  for (int i = 0; i < static_cast<int>(attributes_.size()); i++)
  {
    GLint attr_size = attributes_[i].size;
    GLsizei stride = vertex_size_ * sizeof(float);
    uintptr_t byte_offset = cur_offset * sizeof(float);

    glEnableVertexAttribArray(i);
    glVertexAttribPointer(i,            // index of the vertex attribute to be modified
                          attr_size,    // number of components per attribute
                          GL_FLOAT,     // type of data in component array
                          GL_FALSE,     // whether values should be normalized
                          stride,       // byte offset between consecutive attributes
                          (void*)byte_offset // offset to the first attribute
                         );

    cur_offset += attr_size;
  }

  if (indices == nullptr)
  {
    draw_arrays(mode, static_cast<GLsizei>(vertices_.size() / vertex_size_));
  }
  else
  {
    indices->bind();
    draw_elements(mode, indices);
    indices->unbind();
  }

  for (int i = 0; i < static_cast<int>(attributes_.size()); i++)
  {
    glDisableVertexAttribArray(i);
  }
}

void VertexBufferObject::unbind()
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

void VertexBufferObject::draw_arrays(GLenum mode, GLsizei count)
{
  glDrawArrays(mode, 0, count);
}

void VertexBufferObject::draw_elements(GLenum mode, IndexBufferObject* indices)
{
  glDrawElements(mode, static_cast<GLsizei>(indices->size()), GL_UNSIGNED_INT, 0);
}

void VertexBufferObject::destroy()
{
  if (id_ != 0)
  {
    glDeleteBuffers(1, &id_);
  }
}
}
