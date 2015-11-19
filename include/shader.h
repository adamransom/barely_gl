//
// shader.h
// Copyright (c) 2015 Adam Ransom
//

#ifndef BGL_SHADER_H
#define BGL_SHADER_H

#include <string>
#include <OpenGL/gltypes.h>

namespace BarelyGL {
/**
 * @class Shader
 * @brief Wrapper around an OpenGL shader
 */
class Shader
{
public:
  /**
   * @brief Loads and compiles the shader
   *
   * @param file_path path to the shader
   * @param shader_type type of shader (either GL_FRAGMENT_SHADER or GL_VERTEX_SHADER)
   *
   * @throws GL::Exception if the object fails to be constructed
   */
  Shader(const std::string& file_path, GLenum shader_type);
  ~Shader();

  /**
   * @brief The ID of the underlying OpenGL object
   */
  GLuint id() const { return id_; }

private:
  /**
   * @brief Creates an empty shader object
   */
  void create();

  /**
   * @brief Loads the file and saves the output
   */
  void load();

  /**
   * @brief Compiles the shader object
   */
  void compile();

  /**
   * @brief Destroys the shader
   */
  void destroy();

  /// The ID of underlying shader object
  GLuint id_ = 0;
  /// The type of shader
  GLenum shader_type_;
  /// The path to the shader
  std::string file_path_;
  /// The contents of shader file
  std::string shader_string_;
};
}

#endif /* defined(BGL_SHADER_H) */
