//
// vertex_attribute_array.cpp
// Copyright (c) 2015 Adam Ransom
//

#include <OpenGL/gl3.h>
#include "vertex_attribute_array.h"

namespace BarelyGL {
const VertexAttribute VertexAttribute::Position{3};
const VertexAttribute VertexAttribute::UV{2};
const VertexAttribute VertexAttribute::Color{3};

VertexAttributeArray::VertexAttributeArray(std::vector<VertexAttribute> attributes)
{
  set_attributes(std::move(attributes));
}

void VertexAttributeArray::set_attributes(std::vector<VertexAttribute> attributes)
{
  attributes_ = std::move(attributes);

  for (auto& attribute : attributes_)
  {
    size_ += attribute.size;
  }
}

void VertexAttributeArray::enable()
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
  for (unsigned i = 0; i < attributes_.size(); ++i)
  {
    GLint attr_size = attributes_[i].size;
    GLsizei stride = size_ * sizeof(float);
    uintptr_t byte_offset = cur_offset * sizeof(float);

    glEnableVertexAttribArray(i);
    glVertexAttribPointer(i,                 // index of the vertex attribute to be modified
                          attr_size,         // number of components per attribute
                          GL_FLOAT,          // type of data in component array
                          GL_FALSE,          // whether values should be normalized
                          stride,            // byte offset between consecutive attributes
                          (void*)byte_offset // offset to the first attribute
                         );

    cur_offset += attr_size;
  }
}
} // end of namespace BarelyGL
