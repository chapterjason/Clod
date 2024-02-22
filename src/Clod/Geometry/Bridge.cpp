#include <Clod/Geometry/Bridge.hpp>

namespace Clod
{
    b2Vec2 toMeter(const sf::Vector2f &vector)
    {
        return {vector.x * SCALE_TO_METER, vector.y * SCALE_TO_METER};
    }

    b2Vec2 toMeter(const sf::Vector2i &vector)
    {
        return {static_cast<float>(vector.x) * SCALE_TO_METER, static_cast<float>(vector.y) * SCALE_TO_METER};
    }

    sf::Vector2f toPixel(const b2Vec2 &vector)
    {
        return {vector.x * SCALE_TO_PIXEL, vector.y * SCALE_TO_PIXEL};
    }

    b2Vec2 toB2Vec2(const sf::Vector2f &vector)
    {
        return {vector.x, vector.y};
    }

    sf::Vector2f toVector2f(const b2Vec2 &vector)
    {
        return {vector.x, vector.y};
    }
}
