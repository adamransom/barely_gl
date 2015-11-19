//
// texture.h
// Copyright (c) 2015 Adam Ransom
//

#ifndef BGL_TEXTURE_H
#define BGL_TEXTURE_H

#include <vector>
#include <OpenGL/gltypes.h>

namespace BarelyGL {
/**
 * @class Texture
 * @brief Wrapper around OpenGL texture
 */
class Texture
{
public:
  /**
   * @brief Creates a new texture and uploads the pixel data
   *
   * @param width width of the texture
   * @param height height of the texture
   * @param format pixel format of the texture
   * @param pixels raw pixel data of the texture
   *
   * @throws GL::Exception if the object fails to be constructed
   */
  Texture(int width, int height, GLenum format, const void* pixels);
  ~Texture();

  /**
   * @brief Binds the texture for use
   */
  void bind() const;

  /**
   * @brief Sets the raw data of the texture
   */
  void set_data(const void*);

  /**
   * @brief Unbinds the texture
   */
  void unbind() const;

  /**
   * @brief Gets the width of the texture
   *
   * @return int representing the width
   */
  int width() const { return width_; }

  /**
   * @brief Gets the height of the texture
   *
   * @return int representing the height
   */
  int height() const { return height_; }

  /**
   * @brief Gets the id assigned by OpenGL for this texture
   *
   * @return GLuint representing the id
   */
  GLuint id() const { return id_; }

private:
  /**
   * @brief Generates a new texture
   */
  void generate();

  /**
   * @brief Sets the parameters for the texture
   */
  void set_parameters();

  /**
   * @brief Destroys the texture
   */
  void destroy();

  /// The ID of underlying texture object
  GLuint id_ = 0;
  /// The width of the texture
  int width_;
  /// The height of the texture
  int height_;
  /// The pixel format of the texture
  GLenum format_;
  /// The raw data of the texture
  const void* data_;
};
}

#endif /* defined(BGL_TEXTURE_H) */
