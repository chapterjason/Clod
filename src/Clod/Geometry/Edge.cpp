#include <Clod/Geometry/Edge.hpp>
#include <algorithm>

#include "Clod/Geometry/Position.hpp"

namespace Clod
{
    Edge::Edge(const sf::Vector2f &a, const sf::Vector2f &b): a(a), b(b) {}

    bool Edge::operator==(const Edge &other) const {
        return (this->a == other.a && this->b == other.b) || (this->a == other.b && this->b == other.a);
    }

    bool Edge::contains(const sf::Vector2f &point) const
    {
        return this->a == point || this->b == point;
    }

    bool Edge::isInsideVector(const std::vector<Edge> &edges) const {
        return std::any_of(edges.begin(), edges.end(), [this](const Edge &edge)
        {
            return edge == *this;
        });
    }

    float Edge::length() const
    {
        return distance(this->a, this->b);
    }

    sf::Angle Edge::angle() const
    {
        return Clod::angle(this->a, this->b);
    }

    sf::Vector2f Edge::midpoint() const
    {
        return (this->a + this->b) / 2.f;
    }
}