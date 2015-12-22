//
// vertex_buffer_object.h
// Copyright (c) 2015 Adam Ransom
//

#ifndef BGL_VERTEX_BUFFER_OBJECT_H
#define BGL_VERTEX_BUFFER_OBJECT_H

#include <vector>
#include <OpenGL/gltypes.h>
#include "vertex_attribute_array.h"

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
   * @param usage usage pattern of the buffer (GL_STATIC_DRAW etc)
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
   * @brief Initialize the buffer data store without uploading any data
   *
   * @param size the size of data store to allocate
   */
  void init_buffer(GLsizeiptr size);

  /**
   * @brief Set the vertices for the buffer, recreating the data store
   *
   * @param vertices array of floats to be used as vertices
   */
  void set_vertices(const std::vector<float>& vertices);

  /**
   * @brief Set the vertices for the buffer, replacing data in the store
   *
   * @param vertices array of floats to be used as vertices
   */
  void sub_vertices(const std::vector<float>& vertices, GLintptr offset = 0);

  /**
   * @brief Unbinds the buffer
   */
  void unbind() const;

  /**
   * @brief Returns the number of vertices in the buffer
   *
   * @return the number of vertices in the buffer
   */
  size_t size() const { return vertex_count_; }

private:
  /**
   * @brief Generate the buffer
   */
  void generate_buffer();

  /**
   * @brief Destroy the buffer
   */
  void destroy();

  /// The ID of underlying vertext buffer object
  GLuint id_ = 0;
  /// The type of buffer object
  GLenum target_;
  /// The usage pattern of the buffer
  GLenum usage_;
  /// The number of vertices in the buffer
  size_t vertex_count_;
};
}
#endif /* defined(BGL_VERTEX_BUFFER_OBJECT_H) */
