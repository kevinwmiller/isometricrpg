#ifndef VECTOROVERLOADS_H
#define VECTOROVERLOADS_H

struct VectorCompare
{

    bool operator() (sf::Vector2f left, sf::Vector2f right) const
    {
        return left.x + left.y < right.x + right.y;
    }
};

#endif
