#include "BodyManager.h"

BodyManager::BodyManager()
{
    this->pSquare = new Square();
    this->pTriangle = new Triangle();
}

Square* BodyManager::getPSquare()
{
    return this->pSquare;
}

Triangle* BodyManager::getPTriangle()
{
    return this->pTriangle;
}

BodyManager::~BodyManager()
{

}