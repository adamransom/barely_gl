//
// ShaderProgram.h
// Copyright (c) 2015 Adam Ransom
//

#ifndef GL_SHADERPROGRAM_H
#define GL_SHADERPROGRAM_H

#include <OpenGL/gltypes.h>
#include <string>
#include <glm/fwd.hpp>

namespace GL {
class Shader;

/**
 * @class ShaderProgram
 * @brief Wrapper around an OpenGL shader program
 */
class ShaderProgram
{
public:
  /**
   * @brief Creates and links a new program with the provided vertex and fragment shaders
   */
  ShaderProgram(const Shader* vertex_shader, const Shader* fragment_shader);
  ~ShaderProgram();

  /**
   * @brief Start using this program for the following commands
   */
  void use() const;

  /**
   * @brief Assigns a matrix to the named uniform in the shader program
   *
   * @param name name of the uniform variable
   * @param matrix matrix to assign to the uniform
   */
  void set_uniform(const std::string& name, glm::mat4 matrix);

  /**
   * @brief Stops using this program
   */
  void unbind() const;

  /**
   * @brief The ID of the underlying OpenGL object
   */
  GLuint id() const { return id_; }

private:
  /**
   * @brief Attaches and links the shaders.
   */
  void link();

  /**
   * @brief Get the location of the named uniform variable
   *
   * @param name name of the uniform variable
   *
   * @return the location of the uniform variable
   */
  GLint get_uniform_location(const std::string& name) const;

  /**
   * @brief Destroys the program
   */
  void destroy();

  /// The ID of the underlying shader object
  GLuint id_ = 0;
  /// A pointer to the vertex shader
  const Shader* vertex_shader_;
  /// A pointer to the fragment shader
  const Shader* fragment_shader_;
};
}

#endif /* defined(GL_SHADERPROGRAM_H) */
