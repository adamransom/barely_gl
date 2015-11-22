//
// vertex_attribute.h
// Copyright (c) 2015 Adam Ransom
//

#ifndef BGL_VERTEX_ATTRIBUTE_H
#define BGL_VERTEX_ATTRIBUTE_H

#include <vector>

namespace BarelyGL {
/**
 * @struct VertexAttribute
 * @brief Describes a vertex attribute (only the size for now)
 */
struct VertexAttribute
{
  static const VertexAttribute Position;
  static const VertexAttribute UV;
  static const VertexAttribute Color;

  /// The size of the vertex attribute (how many vertices in this attribute)
  int size;
};

/// Convenience alias for a collection of vertex attributes
using VertexAttributeArray = std::vector<VertexAttribute>;
}

#endif /* defined(BGL_VERTEX_ATTRIBUTE_H) */
