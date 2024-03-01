#pragma once

#include <vector>

#include <SFML/System.hpp>
#include <box2d/box2d.h>

namespace Clod
{
    struct Vertex
    {
        float x{}, y{};

        explicit Vertex(float x = 0.f, float y = 0.f);

        explicit Vertex(int x, int y);

        explicit Vertex(unsigned x, unsigned y);

        explicit Vertex(const sf::Vector2f &vector);

        explicit Vertex(const sf::Vector2i &vector);

        explicit Vertex(const sf::Vector2u &vector);

        explicit Vertex(const b2Vec2 &vector);

        Vertex(const Vertex &vertex);

        bool operator==(const Vertex &other) const;

        bool operator!=(const Vertex &other) const;

        Vertex operator+(const Vertex &other) const;

        Vertex operator+(const sf::Vector2f &other) const;

        Vertex operator-(const Vertex &other) const;

        Vertex operator-(const sf::Vector2f &other) const;

        Vertex operator*(float value) const;

        Vertex operator/(float value) const;

        Vertex &operator+=(const Vertex &other);

        Vertex &operator+=(const sf::Vector2f &other);

        Vertex &operator-=(const Vertex &other);

        Vertex &operator-=(const sf::Vector2f &other);

        Vertex &operator*=(float value);

        Vertex &operator/=(float value);

        operator sf::Vector2f() const;

        operator b2Vec2() const;

        [[nodiscard]] float distance(const Vertex &other) const;

        [[nodiscard]] float squaredDistance(const Vertex &other) const;

        [[nodiscard]] float cross(const Vertex &other) const;

        [[nodiscard]] float cross(const Vertex &otherA, const Vertex &otherB) const;

        [[nodiscard]] float perpendicularDistance(const Vertex &otherA, const Vertex &otherB) const;

        [[nodiscard]] float dot(const Vertex &other) const;

        [[nodiscard]] int crossSign(const Vertex& otherB, const Vertex& otherC) const;

        [[nodiscard]] sf::Angle angle(const Vertex &other) const;

        [[nodiscard]] sf::Vector2f toSFML() const;

        [[nodiscard]] b2Vec2 toBox2D() const;

        [[nodiscard]] Vertex toMeter() const;

        [[nodiscard]] Vertex toPixel() const;
    };
}
