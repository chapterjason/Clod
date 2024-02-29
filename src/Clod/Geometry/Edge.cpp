#include <Clod/Geometry/Edge.hpp>
#include <algorithm>

Clod::Edge::Edge(const sf::Vector2f &a, const sf::Vector2f &b): a(a), b(b) {}

bool Clod::Edge::operator==(const Edge &other) const {
    return (this->a == other.a && this->b == other.b) || (this->a == other.b && this->b == other.a);
}

bool Clod::Edge::isInsideVector(const std::vector<Edge> &edges) const {
    return std::any_of(edges.begin(), edges.end(), [this](const Edge &edge)
    {
        return edge == *this;
    });
}
