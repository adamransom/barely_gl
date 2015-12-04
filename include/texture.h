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
   * @param format pixel format of the data
   * @param internal_format format the texture should be stored as
   * @param unpack_alignment the unpack alignment OpenGL uses (usually 4)
   * @param pixels raw pixel data of the texture
   *
   * @throws GL::Exception if the object fails to be constructed
   */
  Texture(int width, int height, GLenum format, GLenum internal_format, uint8_t unpack_alignment,
          const void* pixels);

  /**
   * @brief Creates a new texture and uploads the pixel data
   *
   * @param width width of the texture
   * @param height height of the texture
   * @param format pixel format of the data
   * @param internal_format format the texture should be stored as
   * @param pixels raw pixel data of the texture
   *
   * @throws GL::Exception if the object fails to be constructed
   */
  Texture(int width, int height, GLenum format, GLenum internal_format, const void* pixels);

  /**
   * @brief Creates a new texture and uploads the pixel data
   *
   * @param width width of the texture
   * @param height height of the texture
   * @param format pixel format of the data
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
   * @brief Uploads raw data to part of the texture
   *
   * Note: Must call `bind()` first!
   *
   * @param x_offset the x offset into texture
   * @param y_offset the y offset into texture
   * @param width the width of the data being uploaded
   * @param width the height of the data being uploaded
   * @param data the raw pixel data to upload
   */
  void sub_data(int x_offset, int y_offset, int width, int height, const void* data);

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
   * @brief Sets the raw data of the texture
   *
   * @param internal_format the format the texture should be stored as
   * @param data the raw pixel data to upload
   */
  void set_data(GLenum internal_format, const void* data);

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
  /// The alignment used to unpack the data (usually 4)
  uint8_t unpack_alignment_;
};
}

#endif /* defined(BGL_TEXTURE_H) */
