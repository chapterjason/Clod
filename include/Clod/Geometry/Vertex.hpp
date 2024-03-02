#pragma once

#include <SFML/System.hpp>
#include <box2d/box2d.h>

namespace Clod
{
    struct Vertex
    {
        float x{}, y{};

        Vertex(float x = 0.f, float y = 0.f); // NOLINT(*-explicit-constructor)

        Vertex(int x, int y);

        Vertex(unsigned x, unsigned y);

        Vertex(const sf::Vector2f &vector); // NOLINT(*-explicit-constructor)

        Vertex(const sf::Vector2i &vector); // NOLINT(*-explicit-constructor)

        Vertex(const sf::Vector2u &vector); // NOLINT(*-explicit-constructor)

        Vertex(const b2Vec2 &vector); // NOLINT(*-explicit-constructor)

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

        operator sf::Vector2f() const; // NOLINT(*-explicit-constructor)

        operator b2Vec2() const; // NOLINT(*-explicit-constructor)

        [[nodiscard]] float distance(const Vertex &other) const;

        [[nodiscard]] float squaredDistance(const Vertex &other) const;

        [[nodiscard]] float cross(const Vertex &other) const;

        [[nodiscard]] float cross(const Vertex &otherA, const Vertex &otherB) const;

        [[nodiscard]] float perpendicularDistance(const Vertex &otherA, const Vertex &otherB) const;

        [[nodiscard]] float dot(const Vertex &other) const;

        /**
         * - 1: counterclockwise
         * - 0: collinear
         * - -1: clockwise
         */
        [[nodiscard]] int crossSign(const Vertex& otherB, const Vertex& otherC) const;

        [[nodiscard]] sf::Angle angle(const Vertex &other) const;

        [[nodiscard]] sf::Vector2f toSFML() const;

        [[nodiscard]] b2Vec2 toBox2D() const;

        [[nodiscard]] Vertex toMeter() const;

        [[nodiscard]] Vertex toPixel() const;
    };
}
