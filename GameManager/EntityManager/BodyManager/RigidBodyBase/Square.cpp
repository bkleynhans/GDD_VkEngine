#include "Square.h"

Square::Square()
{

}

const std::vector<Vertex>* Square::getPVertices()
{
    return this->pVertices;
}

const std::vector<uint16_t>* Square::getPIndices()
{
    return this->pIndices;
}

Square::~Square()
{

}