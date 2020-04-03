#include "EntityManager.h"

EntityManager::EntityManager()
{
    this->pBodyManager = new BodyManager();
}

BodyManager* EntityManager::getPBodyManager()
{
    return this->pBodyManager;
}

EntityManager::~EntityManager()
{

}