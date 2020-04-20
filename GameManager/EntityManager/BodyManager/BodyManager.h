#ifndef _BODYMANAGER_H_
#define _BODYMANAGER_H_

#include "EntityManager/BodyManager/RigidBodies/Square.h"
#include "EntityManager/BodyManager/RigidBodies/Triangle.h"

class BodyManager
{
public:
    BodyManager();
    ~BodyManager();

    Square* getPSquare();
    Triangle* getPTriangle();

private:
    Square* pSquare = nullptr;
    Triangle* pTriangle = nullptr;

};

#endif // _BODYMANAGER_H_