#include "Square.h"

Square::Square()
{
    this->makeSquare();
}

void Square::makeSquare()
{
    this->vertices = {
        {{-0.5f, -0.5f}, {1.0f, 0.0f, 0.0f}},
        {{0.5f, -0.5f}, {0.0f, 1.0f, 0.0f}},
        {{0.5f, 0.5f}, {0.0f, 0.0f, 1.0f}},
        {{-0.5f, 0.5f}, {1.0f, 1.0f, 0.0f}},
    };

    this->indices.assign(
        {
            0, 1, 2,
            2, 3, 0
        }
    );
}

Square::~Square()
{

}