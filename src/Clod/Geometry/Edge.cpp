#include <Clod/Geometry/Edge.hpp>
#include <algorithm>

#include "Clod/Geometry/Position.hpp"

Clod::Edge::Edge(const sf::Vector2f &a, const sf::Vector2f &b): a(a), b(b) {}

bool Clod::Edge::operator==(const Edge &other) const {
    return (this->a == other.a && this->b == other.b) || (this->a == other.b && this->b == other.a);
}

bool Clod::Edge::contains(const sf::Vector2f &point) const
{
    return this->a == point || this->b == point;
}

bool Clod::Edge::isInsideVector(const std::vector<Edge> &edges) const {
    return std::any_of(edges.begin(), edges.end(), [this](const Edge &edge)
    {
        return edge == *this;
    });
}

float Clod::Edge::length() const
{
    return distance(this->a, this->b);
}

sf::Angle Clod::Edge::angle() const
{
    return Clod::angle(this->a, this->b);
}
