#include "RigidBodyBase.h"

RigidBodyBase::RigidBodyBase()
{

}

const std::vector<Vertex>* RigidBodyBase::getPVertices()
{
    return this->pVertices;
}

const std::vector<uint16_t>* RigidBodyBase::getPIndices()
{
    return this->pIndices;
}

float RigidBodyBase::getSize()
{
    return sizeof(Vertex) * vertices.size();
}

RigidBodyBase::~RigidBodyBase()
{

}