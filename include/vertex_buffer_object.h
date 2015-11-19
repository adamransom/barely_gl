//
// vertex_buffer_object.h
// Copyright (c) 2015 Adam Ransom
//

#ifndef BGL_VERTEX_BUFFER_OBJECT_H
#define BGL_VERTEX_BUFFER_OBJECT_H

#include <vector>
#include <OpenGL/gltypes.h>
#include "vertex_attribute.h"

namespace BarelyGL {
class IndexBufferObject;

/**
 * @class VertexBufferObject
 * @brief Wrapper around an OpenGL vertex buffer object (VB0)
 */
class VertexBufferObject
{
public:
  /**
   * @brief Sets up a new VBO
   *
   * @param target type of buffer object (only supports GL_ARRAY_BUFFER for now)
   * @param usage usage pattern of the buffer (only supports GL_STATIC_DRAW for
   *              now)
   *
   * @throws GL::Exception if the object fails to be constructed
   */
  VertexBufferObject(GLenum target, GLenum usage);
  ~VertexBufferObject();

  /**
   * @brief Binds the buffer
   */
  void bind() const;

  /**
   * @brief Draws the buffer with the specified mode
   *
   * @param mode drawing mode (usually GL_TRIANGLES)
   */
  void draw(GLenum mode) const;

  /**
   * @brief Draws the buffer with the specified mode using the indices specified
   *
   * @param mode drawing mode (usually GL_TRIANGLES)
   * @param indices the index buffer object to draw the vertices with
   */
  void draw(GLenum mode, const IndexBufferObject* indices) const;

  /**
   * @brief Unbinds the buffer
   */
  void unbind() const;

  /**
   * @brief Set the vertices for the buffer
   *
   * @param vertices array of floats to be used as vertices
   */
  void set_vertices(std::vector<float> vertices);

  /**
   * @brief Set the attributes for the vertices
   *
   * @param attributes the attributes for the corresponding vertices
   */
  void set_attributes(std::vector<VertexAttribute> attributes);

private:
  /**
   * @brief Generate the buffer
   */
  void generate_buffer();

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
  void draw_elements(GLenum mode, const IndexBufferObject* indices) const;

  /**
   * @brief Destroy the buffer
   */
  void destroy();

  /// The ID of underlying vertext buffer object
  GLuint id_ = 0;
  /// The type of buffer object
  GLenum target_;
  /// The usage partter of the buffer
  GLenum usage_;
  /// The list of vertices
  std::vector<float> vertices_;
  /// The list of attributes for the vertices
  std::vector<VertexAttribute> attributes_;
  /// The amount of values per vertex
  int vertex_size_ = 0;
};
}
#endif /* defined(BGL_VERTEX_BUFFER_OBJECT_H) */
