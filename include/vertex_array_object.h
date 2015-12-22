//
// vertex_array_object.h
// Copyright (c) 2015 Adam Ransom
//

#ifndef BGL_VERTEX_ARRAY_OBJECT_H
#define BGL_VERTEX_ARRAY_OBJECT_H

#include <OpenGL/gltypes.h>
#include "vertex_attribute_array.h"

namespace BarelyGL {
class VertexBufferObject;
class IndexBufferObject;

/**
 * @class VertexArrayObject
 * @brief Wrapper around an OpenGL vertex array object (VAO)
 */
class VertexArrayObject
{
public:
  /**
   * @brief Sets up a new VAO
   *
   * @throws GL::Exception if the object fails to be constructed
   */
  VertexArrayObject();

  /**
   * @brief Sets up a new VAO with associated attributes, VBO and IBO
   *
   * @param attributes the vertex attribute array associated with the VAO
   * @param vertex_buffer the VBO associated with the VAO
   * @param index_buffer the IBO associated with the VAO
   *
   * @throws GL::Exception if the object fails to be constructed
   */
  VertexArrayObject(const VertexAttributeArray& attributes, const VertexBufferObject* vertex_buffer,
                    const IndexBufferObject* index_buffer = nullptr);
  ~VertexArrayObject();

  /**
   * @brief Binds the vertex array object
   */
  void bind() const;

  /**
   * @brief Sets the attributes associated with the VAO
   *
   * @param attributes to vertext attribute array to be associated with the VAO
   */
  void set_attributes(const VertexAttributeArray& attributes);

  /**
   * @brief Sets the VBO associated with the VAO
   *
   * @param buffer the VBO to be associated with the VAO
   */
  void set_vertex_buffer(const VertexBufferObject* buffer);

  /**
   * @brief Sets the VAO associated with the VAO
   *
   * @param buffer the IBO to be associated with the VAO
   */
  void set_index_buffer(const IndexBufferObject* buffer);

  /**
   * @brief Draws the buffer with the specified mode using the indices specified
   *
   * @param mode drawing mode (usually GL_TRIANGLES)
   * @param indices the index buffer object to draw the vertices with
   */
  void draw(GLenum mode, const IndexBufferObject* indices = nullptr) const;

  /**
   * @brief Unbinds the vertex array
   */
  void unbind() const;

private:
  /**
   * @brief Generate the vertex array
   */
  void generate_array();

  /**
   * @brief Draws the buffer using glDrawArrays
   *
   * @param mode drawing mode (usually GL_TRIANGLES)
   * @param count the number of triangles to draw
   */
  void draw_arrays(GLenum mode, GLsizei count) const;

  /**
   * @brief Draws the buffer using glElements
   *
   * @param mode drawing mode (usually GL_TRIANGLES)
   * @param indices the IBO to use as an index into the VBO
   */
  void draw_elements(GLenum mode) const;

  /**
   * @brief Destroy the vertex array
   */
  void destroy();

  /// The ID of underlying vertext array object
  GLuint id_ = 0;
  /// The VBO associated with the VAO
  const VertexBufferObject* vertex_buffer_;
  /// The IBO associated with the VAO
  const IndexBufferObject* index_buffer_;
  /// The amount of attributes per vertex
  int vertex_size_ = 0;
};
} // end of namespace BarelyGL

#endif // defined(BGL_VERTEX_ARRAY_OBJECT_H)
