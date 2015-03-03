//
// Exception.h
// Copyright (c) 2015 Adam Ransom
//

#ifndef GL_EXCEPTION_H
#define GL_EXCEPTION_H

#include <exception>
#include <string>

namespace GL {
/**
 * @class Exception
 * @brief Simple exception specifically for OpenGL exceptions
 */
class Exception : public std::exception
{
public:
  Exception() throw();
  /**
   * @brief Create a new exception with a specific message
   *
   * @param description description of this exception
   */
  Exception(const std::string& description) throw()
    : description_(description) {};

  virtual const char* what() const throw() { return description_.c_str(); }

private:
  /// Description of the exception
  std::string description_;
};
}

#endif
