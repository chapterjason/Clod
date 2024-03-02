#include <Clod/Geometry/Edge.hpp>
#include <algorithm>

#include "Clod/Geometry/Position.hpp"
#include "Clod/Geometry/Vertex.hpp"

namespace Clod
{
    Edge::Edge(const Vertex &a, const Vertex &b)
        : a(a), b(b) {}

    bool Edge::operator==(const Edge &other) const
    {
        // Check if the edges are the same, ignoring the order of vertices
        if ((this->a == other.a && this->b == other.b) ||
            (this->a == other.b && this->b == other.a))
        {
            return true;
        }

        // If none of the above conditions are met, the edges are not equal
        return false;
    }

    bool Edge::operator!=(const Edge &other) const
    {
        return !(*this == other);
    }

    bool Edge::contains(const Vertex &vertex) const
    {
        return this->a == vertex || this->b == vertex;
    }

    bool Edge::isInsideVector(const std::vector<Edge> &edges) const
    {
        return std::any_of(edges.begin(), edges.end(), [this](const Edge &edge)
        {
            return edge == *this;
        });
    }

    float Edge::length() const
    {
        return this->a.distance(this->b);
    }

    sf::Angle Edge::direction() const
    {
        return this->a.angle(this->b);
    }

    std::optional<sf::Angle> Edge::angle(const Edge &other) const
    {
        // p is the common vertex
        // a is the vertex of this edge which is not p
        // b is the vertex of the other edge which is not p
        Vertex a, b, p;

        if (this->a == other.a)
        {
            p = this->a;
            a = this->b;
            b = other.b;
        }
        else if (this->a == other.b)
        {
            p = this->a;
            a = this->b;
            b = other.a;
        }
        else if (this->b == other.a)
        {
            p = this->b;
            a = this->a;
            b = other.b;
        }
        else if (this->b == other.b)
        {
            p = this->b;
            a = this->a;
            b = other.a;
        }
        else
        {
            return std::nullopt;
        }

        // calculate the angle
        return p.angle(a) - p.angle(b);
    }

    Vertex Edge::midpoint() const
    {
        return (this->a + this->b) / 2.f;
    }

    std::string Edge::toString() const
    {
        return "Edge(" + std::to_string(this->a.x) + ", " + std::to_string(this->a.y) + ") -> (" +
               std::to_string(this->b.x) + ", " + std::to_string(this->b.y) + ")";
    }
}
