#ifndef _TRIANGLE_H_
#define _TRIANGLE_H_

#include "RigidBodyBase.h"
//#include "EntityManager/BodyManager/Vertex.h"

class Triangle :
    public RigidBodyBase
{
public:
    Triangle();
    ~Triangle();

    void makeTriangle();
};

#endif // _TRIANGLE_H_