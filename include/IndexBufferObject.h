//
// IndexBufferObject.h
// Copyright (c) 2015 Adam Ransom
//

#ifndef GL_INDEX_BUFFER_OBJECT_H
#define GL_INDEX_BUFFER_OBJECT_H

#include <vector>
#include <OpenGL/gltypes.h>

namespace GL {
/**
 * @class IndexBufferObject
 * @brief Wrapper around an OpenGL index buffer object (IBO)
 */
class IndexBufferObject
{
public:
  /**
   * @brief Sets up a new IBO
   *
   * @param target type of buffer object (only supports GL_ELEMENT_ARRAY_BUFFER for now)
   * @param usage usage pattern of the buffer (only supports GL_STATIC_DRAW for
   *              now)
   *
   * @throws GL::Exception if the object fails to be constructed
   */
  IndexBufferObject(GLenum target, GLenum usage);
  ~IndexBufferObject();

  /**
   * @brief Binds the buffer
   */
  void bind() const;

  /**
   * @brief Unbinds the buffer
   */
  void unbind() const;

  /**
   * @brief Gets the number of indices
   *
   * @returns the number of indices
   */
  size_t size() const { return indices_.size(); }

  /**
   * @brief Set the vertices for the buffer
   *
   * @param vertices array of floats to be used as vertices
   */
  void set_indices(std::vector<int> indices);

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
  /// The usage partter of the buffer
  GLenum usage_;
  /// The list of vertices
  std::vector<int> indices_;
};
}

#endif // defined(GL_INDEX_BUFFER_OBJECT_H)
