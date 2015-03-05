//
// ShaderProgram.cpp
// Copyright (c) 2015 Adam Ransom
//

#include "ShaderProgram.h"
#include "Shader.h"
#include "Exception.h"
#include <OpenGL/gl3.h>
#include "glm/glm.hpp"
#include "glm/gtc/type_ptr.hpp"

namespace GL {

ShaderProgram::ShaderProgram(const Shader* vertex_shader, const Shader* fragment_shader)
  : vertex_shader_(vertex_shader)
  , fragment_shader_(fragment_shader)
{
  link();
}

void ShaderProgram::use() const
{
  glUseProgram(id_);
}

/*
 * Gets the location of the named uniform variable and then sets it to the
 * provided matrix
 */
void ShaderProgram::set_uniform(const std::string& name, const glm::mat4 matrix)
{
  GLint location = get_uniform_location(name);

  if (location != -1)
  {
    glUniformMatrix4fv(location,              // location of uniform variable
                       1,                     // number of matrices to be modified
                       GL_FALSE,              // whether to transpose matrix
                       glm::value_ptr(matrix) // new value for uniform variable
                      );
  }
  else
  {
    throw Exception("Could not find uniform: '" + name + "'");
  }
}

void ShaderProgram::unbind() const
{
  glUseProgram(0);
}

ShaderProgram::~ShaderProgram()
{
  destroy();
}

//
// =============================
//        Private Methods
// =============================
//

/*
 * Creates a new program, then attaches the vertex and fragment shaders and
 * then attempts to link the program. If it fails, an exception is raised
 * containing the program info log
 */
void ShaderProgram::link()
{
  id_ = glCreateProgram();

  if (id_ != 0)
  {
    glAttachShader(id_, vertex_shader_->id());
    glAttachShader(id_, fragment_shader_->id());

    glLinkProgram(id_);

    GLint status;
    glGetProgramiv(id_, GL_LINK_STATUS, &status);

    glDetachShader(id_, vertex_shader_->id());
    glDetachShader(id_, fragment_shader_->id());

    if (status == GL_FALSE)
    {
      GLint info_length;
      glGetProgramiv(id_, GL_INFO_LOG_LENGTH, &info_length);

      std::string info_log;
      info_log.resize(info_length);
      glGetProgramInfoLog(id_, info_length, NULL, &info_log[0]);

      throw Exception("Program linking failed: " + info_log);
    }
  }
  else
  {
    throw Exception("Could not create program");
  }
}

GLint ShaderProgram::get_uniform_location(const std::string& name) const
{
  return glGetUniformLocation(id_, name.c_str());
}

void ShaderProgram::destroy()
{
  if (id_ != 0)
  {
    glDeleteProgram(id_);
  }
}
}
