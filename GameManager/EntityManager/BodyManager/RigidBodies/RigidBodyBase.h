#ifndef _RIGIDBODYBASE_H_
#define _RIGIDBODYBASE_H_

#include <vector>

#include "EntityManager/BodyManager/Vertex.h"

class RigidBodyBase
{
public:
    RigidBodyBase();
    ~RigidBodyBase();

    const std::vector<Vertex>* getPVertices();
    const std::vector<uint16_t>* getPIndices();

    float getSize();

protected:
    // This variable contains the vec2 vertex, and the vec3 color
    // for each vertex
    std::vector<Vertex> vertices;

    // Indices of the vertices as defined in the vertices variable above
    // this variable
    std::vector<uint16_t> indices;

private:
    const std::vector<Vertex>* pVertices = &vertices;
    const std::vector<uint16_t>* pIndices = &indices;
};

#endif // _RIGIDBODYBASE_H_