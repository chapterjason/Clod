#pragma once

#include <box2d/box2d.h>
#include <SFML/System.hpp>

namespace Clod
{
    const float SCALE_TO_PIXEL = 64.f;
    const float SCALE_TO_METER = 1.f / SCALE_TO_PIXEL;

    b2Vec2 toMeter(const sf::Vector2f &vector);

    b2Vec2 toMeter(const sf::Vector2i &vector);

    sf::Vector2f toPixel(const b2Vec2 &vector);

    b2Vec2 toB2Vec2(const sf::Vector2f &vector);

    sf::Vector2f toVector2f(const b2Vec2 &vector);
}