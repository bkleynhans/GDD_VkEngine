#include "EntityManager.h"

EntityManager::EntityManager()
{
    this->pBodyManager = new BodyManager();
    this->buildBodies();
}

void EntityManager::buildBodies()
{
    this->populateVertices("triangle", this->pBodyManager->getPTriangle());
    this->populateVertices("square", this->pBodyManager->getPSquare());
}

BodyManager* EntityManager::getPBodyManager()
{
    return this->pBodyManager;
}

const std::vector<Vertex>* EntityManager::getPVertex(std::string idx)
{
    return this->vertices[idx];
}

const std::vector<uint16_t>* EntityManager::getPIndex(std::string idx)
{
    return this->indices[idx];
}

std::map<std::string, const std::vector<Vertex>*>* EntityManager::getPVertices()
{
    return this->pVertices;
}

std::map<std::string, const std::vector<uint16_t>*>* EntityManager::getPIndices()
{
    return this->pIndices;
}

// Populates the object vertex arrays by shape
void EntityManager::populateVertices(std::string shape, RigidBodyBase* obj)
{
    this->vertices.insert(this->makeVertexPair(shape, obj));

    this->populateIndices(shape, obj);
}

// Populates the vertex array indices by shape
void EntityManager::populateIndices(std::string shape, RigidBodyBase* obj)
{
    this->indices.insert(this->makeIndexPair(shape, obj));
}

// Build the string/vertex map
std::pair<std::string, const std::vector<Vertex>*> EntityManager::makeVertexPair(std::string shape, RigidBodyBase* obj)
{
    return std::pair<std::string, const std::vector<Vertex>*>(shape, obj->getPVertices());
}

// Build the string/uint16_t map
std::pair<std::string, const std::vector<uint16_t>*> EntityManager::makeIndexPair(std::string shape, RigidBodyBase* obj)
{
    return std::pair<std::string, const std::vector<uint16_t>*>(shape, obj->getPIndices());
}

EntityManager::~EntityManager()
{

}