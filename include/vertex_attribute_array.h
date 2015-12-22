//
// vertex_attribute_array.h
// Copyright (c) 2015 Adam Ransom
//

#ifndef BGL_VERTEX_ATTRIBUTE_ARRAY_H
#define BGL_VERTEX_ATTRIBUTE_ARRAY_H

#include <vector>

namespace BarelyGL {
/**
 * @struct VertexAttribute
 * @brief Describes a vertex attribute (only the size for now)
 */
struct VertexAttribute
{
  /// Vertex attribute describing (x, y, z)
  static const VertexAttribute Position;
  /// Vertex attribute describing (u, v)
  static const VertexAttribute UV;
  /// Vertex attribute describing (r, g, b)
  static const VertexAttribute Color;

  /// The size of the vertex attribute (how many values described by this
  /// attribute)
  uint8_t size;
};

/**
 * @class VertexAttributeArray
 * @brief Describes collection of VertexAttributes
 */
class VertexAttributeArray
{
public:
  /**
   * @brief Construct a new VertexAttributeArray
   */
  VertexAttributeArray()
    : size_(0) {};

  /**
   * @brief Construct a new VertexAttributeArray with a list of attributes
   *
   * @param attributes the vertex attributes to initialize the array with
   */
  VertexAttributeArray(std::vector<VertexAttribute> attributes);

  /**
   * @brief Returns the number of vertices described by the attribute array
   *
   * @return the number of vertices described by the attribute array
   */
  uint8_t size() const { return size_; }

  /**
   * @brief Set the attributes in the vertex attribute array
   *
   * @param attributes the list of vertex attributes to include in the array
   */
  void set_attributes(std::vector<VertexAttribute> attributes);

  /**
   * @brief Enable and set the pointers for each attribute in the array
   */
  void enable();

private:
  /// The list of vertext attributes in the array
  std::vector<VertexAttribute> attributes_;
  /// The number of vertices described by the attribute array
  uint8_t size_;
};
} // end of namespace BarelyGL

#endif // defined(BGL_VERTEX_ATTRIBUTE_ARRAY_H)
