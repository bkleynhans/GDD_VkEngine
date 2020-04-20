#include "Triangle.h"

Triangle::Triangle()
{
    this->makeTriangle();
}

void Triangle::makeTriangle()
{
    this->vertices = {
        {{-0.5f, -0.5f}, {1.0f, 0.0f, 0.0f}},
        {{0.5f, -0.5f}, {0.0f, 1.0f, 0.0f}},
        {{0.0f, 0.5f}, {0.0f, 0.0f, 1.0f}}
    };

    this->indices = {
        0, 1, 2
    };
}

Triangle::~Triangle()
{

}