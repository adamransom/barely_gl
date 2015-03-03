//
// VertexBufferObject.h
// Copyright (c) 2015 Adam Ransom
//

#ifndef GL_VERTEX_BUFFER_OBJECT_H
#define GL_VERTEX_BUFFER_OBJECT_H

#include <vector>
#include <OpenGL/gltypes.h>
#include "VertexAttribute.h"

namespace GL {
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
  void bind();

  /**
   * @brief Draws the buffer with the specified mode
   *
   * @param mode drawing mode (usually GL_TRIANGLES)
   */
  void draw(GLenum mode);

  /**
   * @brief Draws the buffer with the specified mode using the indices specified
   *
   * @param mode drawing mode (usually GL_TRIANGLES)
   * @param indices the index buffer object to draw the vertices with
   */
  void draw(GLenum mode, IndexBufferObject* indices);

  /**
   * @brief Unbinds the buffer
   */
  void unbind();

  /**
   * @brief Set the vertices for the buffer
   *
   * @param vertices array of floats to be used as vertices
   */
  void set_vertices(const std::vector<float> vertices);

  /**
   * @brief Set the attributes for the vertices
   *
   * @param attributes the attributes for the corresponding vertices
   */
  void set_attributes(const std::vector<VertexAttribute> attributes);

private:
  /**
   * @brief Generate the buffer
   */
  void generate_buffer();

  void draw_arrays(GLenum mode, GLsizei count);
  void draw_elements(GLenum mode, IndexBufferObject* indices);

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
#endif /* defined(GL_VERTEX_BUFFER_OBJECT_H) */
