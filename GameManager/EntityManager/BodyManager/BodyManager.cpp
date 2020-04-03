#include "BodyManager.h"

BodyManager::BodyManager()
{
    this->pSquare = new Square();
}

Square* BodyManager::getPSquare()
{
    return this->pSquare;
}

BodyManager::~BodyManager()
{

}