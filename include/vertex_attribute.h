//
// vertex_attribute.h
// Copyright (c) 2015 Adam Ransom
//

#ifndef GL_VERTEX_ATTRIBUTE_H
#define GL_VERTEX_ATTRIBUTE_H

namespace GL {
/**
 * @struct VertexAttribute
 * @brief Describes a vertex attribute (only the size for now)
 */
struct VertexAttribute
{
  /// The size of the vertex attribute (how many vertices in this attribute)
  int size;
};
}

#endif /* defined(GL_VERTEX_ATTRIBUTE_H) */
