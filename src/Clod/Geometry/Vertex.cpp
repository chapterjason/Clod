#include <Clod/Geometry/Vertex.hpp>

#include "Clod/Geometry/Bridge.hpp"

namespace Clod
{
    Vertex::Vertex(const float x, const float y)
        : x(x), y(y) {}

    Vertex::Vertex(const int x, const int y)
        : x(static_cast<float>(x)), y(static_cast<float>(y)) {}

    Vertex::Vertex(const unsigned x, const unsigned y)
        : x(static_cast<float>(x)), y(static_cast<float>(y)) {}

    Vertex::Vertex(const sf::Vector2f &vector)
        : x(vector.x), y(vector.y) {}

    Vertex::Vertex(const sf::Vector2i &vector)
        : x(static_cast<float>(vector.x)), y(static_cast<float>(vector.y)) {}

    Vertex::Vertex(const sf::Vector2u &vector)
        : x(static_cast<float>(vector.x)), y(static_cast<float>(vector.y)) {}

    Vertex::Vertex(const b2Vec2 &vector)
        : x(vector.x), y(vector.y) {}

    Vertex::Vertex(const Vertex &vertex) = default;

    bool Vertex::operator==(const Vertex &other) const
    {
        return this->x == other.x && this->y == other.y;
    }

    bool Vertex::operator!=(const Vertex &other) const
    {
        return !(*this == other);
    }

    Vertex Vertex::operator+(const Vertex &other) const
    {
        return Vertex(this->x + other.x, this->y + other.y);
    }

    Vertex Vertex::operator+(const sf::Vector2f &other) const
    {
        return Vertex(this->x + other.x, this->y + other.y);
    }

    Vertex Vertex::operator-(const sf::Vector2f &other) const
    {
        return Vertex(this->x - other.x, this->y - other.y);
    }

    Vertex & Vertex::operator+=(const sf::Vector2f &other)
    {
        this->x += other.x;
        this->y += other.y;

        return *this;
    }

    Vertex & Vertex::operator-=(const sf::Vector2f &other)
    {
        this->x -= other.x;
        this->y -= other.y;

        return *this;
    }

    Vertex Vertex::operator-(const Vertex &other) const
    {
        return Vertex(this->x - other.x, this->y - other.y);
    }

    Vertex Vertex::operator*(const float value) const
    {
        return Vertex(this->x * value, this->y * value);
    }

    Vertex Vertex::operator/(const float value) const
    {
        return Vertex(this->x / value, this->y / value);
    }

    Vertex &Vertex::operator+=(const Vertex &other)
    {
        this->x += other.x;
        this->y += other.y;

        return *this;
    }

    Vertex &Vertex::operator-=(const Vertex &other)
    {
        this->x -= other.x;
        this->y -= other.y;

        return *this;
    }

    Vertex &Vertex::operator*=(const float value)
    {
        this->x *= value;
        this->y *= value;

        return *this;
    }

    Vertex &Vertex::operator/=(const float value)
    {
        this->x /= value;
        this->y /= value;

        return *this;
    }

    Vertex::operator sf::Vector2f() const
    {
        return {this->x, this->y};
    }

    Vertex::operator b2Vec2() const
    {
        return {this->x, this->y};
    }

    float Vertex::distance(const Vertex &other) const
    {
        return sqrtf(powf(this->x - other.x, 2) + powf(this->y - other.y, 2));
    }

    float Vertex::squaredDistance(const Vertex &other) const
    {
        return (this->x - other.x) * (this->x - other.x) + (this->y - other.y) * (this->y - other.y);
    }

    sf::Angle Vertex::angle(const Vertex &other) const
    {
        return sf::radians(atan2f(other.y - this->y, other.x - this->x));
    }

    sf::Vector2f Vertex::toSFML() const
    {
        return {this->x, this->y};
    }

    b2Vec2 Vertex::toBox2D() const
    {
        return {this->x, this->y};
    }

    Vertex Vertex::toMeter() const
    {
        return Vertex(this->x * SCALE_TO_METER, this->y * SCALE_TO_METER);
    }

    Vertex Vertex::toPixel() const
    {
        return Vertex(this->x * SCALE_TO_PIXEL, this->y * SCALE_TO_PIXEL);
    }
}
