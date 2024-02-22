#include <Clod/System/Time.hpp>

namespace Clod
{
    Time::Time(const std::chrono::nanoseconds time)
        : time(time) {}

    Time Time::now()
    {
        return {};
    }

    Time Time::milliseconds(const float milliseconds)
    {
        return Time(std::chrono::nanoseconds(static_cast<std::chrono::nanoseconds::rep>(milliseconds * 1000000.0f)));
    }

    Time Time::seconds(const float seconds)
    {
        return Time(std::chrono::nanoseconds(static_cast<std::chrono::nanoseconds::rep>(seconds * 1000000000.0f)));
    }

    float Time::asNanoseconds() const
    {
        const auto nanoseconds = this->time.count();

        return static_cast<float>(nanoseconds);
    }

    float Time::asMicroseconds() const
    {
        const auto nanoseconds = this->time.count();

        return static_cast<float>(nanoseconds) / 1000.0f;
    }

    float Time::asMilliseconds() const
    {
        const auto nanoseconds = this->time.count();

        return static_cast<float>(nanoseconds) / 1000000.0f;
    }

    float Time::asSeconds() const
    {
        const auto nanoseconds = this->time.count();

        return static_cast<float>(nanoseconds) / 1000000000.0f;
    }

    sf::Time Time::asSFMLTime() const
    {
        return sf::microseconds(static_cast<std::int64_t>(this->asMicroseconds()));
    }

    Time Time::operator-(const Time &time) const
    {
        return Time(this->time - time.time);
    }

    Time Time::operator+(const Time &time) const
    {
        return Time(this->time + time.time);
    }

    bool Time::operator>(const Time &time) const
    {
        return this->time > time.time;
    }

    bool Time::operator<(const Time &time) const
    {
        return this->time < time.time;
    }


    bool Time::operator>=(const Time &time) const
    {
        return this->time >= time.time;
    }

    bool Time::operator<=(const Time &time) const
    {
        return this->time <= time.time;
    }

    Time &Time::operator+=(const Time &time)
    {
        this->time += time.time;

        return *this;
    }
}
