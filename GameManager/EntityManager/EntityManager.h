#ifndef _ENTITYMANAGER_H_
#define _ENTITYMANAGER_H_

#include <string>
#include <vector>
#include <map>

#include "EntityManager/BodyManager/BodyManager.h"
#include "EntityManager/BodyManager/Vertex.h"

class EntityManager
{
public:
    EntityManager();
    ~EntityManager();

    BodyManager* getPBodyManager();

    const std::vector<Vertex>* getPVertex(std::string idx);
    const std::vector<uint16_t>* getPIndex(std::string idx);

    std::map<std::string, const std::vector<Vertex>*>* getPVertices();
    std::map<std::string, const std::vector<uint16_t>*>* getPIndices();

private:
    BodyManager* pBodyManager = nullptr;

    /*BodyManager* getPBodyManager();*/
    
    void buildBodies();
    void populateVertices(std::string shape, RigidBodyBase* obj);
    void populateIndices(std::string shape, RigidBodyBase* obj);

    std::pair<std::string, const std::vector<Vertex>*> makeVertexPair(std::string, RigidBodyBase*);
    std::pair<std::string, const std::vector<uint16_t>*> makeIndexPair(std::string, RigidBodyBase*);

    std::map<std::string, const std::vector<Vertex>*> vertices;
    std::map<std::string, const std::vector<uint16_t>*> indices;
    
    std::map<std::string, const std::vector<Vertex>*>* pVertices = &vertices;
    std::map<std::string, const std::vector<uint16_t>*>* pIndices = &indices;
};

#endif // _ENTITYMANAGER_H_