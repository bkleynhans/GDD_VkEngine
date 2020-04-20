#ifndef _SQUARE_H_
#define _SQUARE_H_

#include "RigidBodyBase.h"

class Square :
    public RigidBodyBase
{
public:
    Square();
    ~Square();

    void makeSquare();
};

#endif // _SQUARE_H_