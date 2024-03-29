#pragma once

#include <box2d/box2d.h>
#include <SFML/System.hpp>

namespace Clod
{
 // @todo: Change b2_settings.sh by define a user config(?) to change the scale
 constexpr auto SCALE_TO_PIXEL = 30.f;
 constexpr auto SCALE_TO_METER = 1.f / SCALE_TO_PIXEL;

 /**
  * Converts SFML vector (float) to Box2D vector, scaling from pixels to meters.
  *
  * @param vector SFML vector in pixels.
  * @return Box2D vector in meters.
  */
 b2Vec2 toMeter(const sf::Vector2f &vector);

 /**
  * Converts SFML vector (integer) to Box2D vector, scaling from pixels to meters.
  */
 b2Vec2 toMeter(const sf::Vector2i &vector);

 /**
  * Converts Box2D vector to SFML vector, scaling from meters to pixels.
  */
 sf::Vector2f toPixel(const b2Vec2 &vector);

 /**
  * Converts SFML vector (float) to Box2D vector without scaling.
  * Useful for operations that don't involve conversions between units.
  */
 b2Vec2 toB2Vec2(const sf::Vector2f &vector);

 /**
  * Converts Box2D vector to SFML vector (float) without scaling.
  * Useful for operations that don't involve conversions between units.
  */
 sf::Vector2f toVector2f(const b2Vec2 &vector);
}
