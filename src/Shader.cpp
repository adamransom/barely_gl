 //
// Shader.cpp
// Copyright (c) 2015 Adam Ransom
//

#include <fstream>
#include <sstream>
#include <vector>

#include "Shader.h"
#include "Exception.h"
#include <OpenGL/gl3.h>

namespace GL {
Shader::Shader(const std::string& file_path, const GLenum shader_type)
  : shader_type_(shader_type)
  , file_path_(file_path)
{
  create();
  load();
  compile();
}

Shader::~Shader()
{
  destroy();
}

//
// =============================
//        Private Methods
// =============================
//

void Shader::create()
{
  id_ = glCreateShader(shader_type_);

  if (id_ == 0) throw Exception("Could not create shader");
}

/*
 * Opens the `file_path_` and reads into `shader_string_`
 */
void Shader::load()
{
  std::ifstream file {file_path_};

  if (file.is_open())
  {
    std::stringstream buffer;

    buffer << file.rdbuf();
    shader_string_ = buffer.str();
    file.close();
  }
  else
  {
    throw Exception("Could not open file: '" + file_path_ + "'");
  }
}

/*
 * Sets the shader source from `shader_string_` and compiles it. If it fails,
 * an execption is raised containing the shader info log
 */
void Shader::compile()
{

  GLchar const* string_ptr = shader_string_.c_str();

  glShaderSource(id_,         // ID of shader object
                 1,           // number of elements in string array
                 &string_ptr, // array of strings
                 nullptr      // array of string lengths (nullptr implies null-terminated strings)
                );

  glCompileShader(id_);

  GLint status;
  glGetShaderiv(id_, GL_COMPILE_STATUS, &status);

  if (status == GL_FALSE)
  {
    GLint info_length;
    glGetShaderiv(id_, GL_INFO_LOG_LENGTH, &info_length);

    std::string info_log;
    info_log.resize(info_length);
    glGetShaderInfoLog(id_, info_length, NULL, &info_log[0]);

    throw Exception("Shader compilation failed (" + file_path_ + "): " + info_log);
  }
}

void Shader::destroy()
{
  if (id_ != 0)
  {
    glDeleteShader(id_);
  }
}
}
