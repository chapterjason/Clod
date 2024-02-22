#pragma once

#include <chrono>

#include "SFML/System.hpp"

namespace Clod
{
    class Time
    {
        std::chrono::nanoseconds time;

        Time()
            : time(std::chrono::high_resolution_clock::now().time_since_epoch()) {}

        explicit Time(std::chrono::nanoseconds time);

        public:
            static Time now();

            static Time milliseconds(float milliseconds);

            static Time seconds(float seconds);

            [[nodiscard]] float asNanoseconds() const;

            [[nodiscard]] float asMicroseconds() const;

            [[nodiscard]] float asMilliseconds() const;

            [[nodiscard]] float asSeconds() const;

            [[nodiscard]] sf::Time asSFMLTime() const;

            Time operator-(const Time &time) const;

            Time operator+(const Time &time) const;

            bool operator>(const Time &time) const;

            bool operator<(const Time &time) const;

            bool operator>=(const Time &time) const;

            bool operator<=(const Time &time) const;

            Time &operator+=(const Time &time);
    };
}
