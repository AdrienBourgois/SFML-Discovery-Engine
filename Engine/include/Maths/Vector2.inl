#pragma once

#include <cmath>

#pragma warning(push)
#pragma warning(disable : 4244)

namespace Maths
{
template<typename T>
Vector2<T>::Vector2() : x(0), y(0) {}

template<typename T>
Vector2<T>::Vector2(T _x, T _y) : x(_x), y(_y) {}

template<typename T>
Vector2<T> Vector2<T>::operator+(const Vector2& _rhs) const
{
    return Vector2(x + _rhs.x, y + _rhs.y);
}

template<typename T>
Vector2<T> Vector2<T>::operator-(const Vector2& _rhs) const
{
    return Vector2(x - _rhs.x, y - _rhs.y);
}

template<typename T>
Vector2<T> Vector2<T>::operator*(const Vector2& _rhs) const
{
    return Vector2(x * _rhs.x, y * _rhs.y);
}

template<typename T>
Vector2<T> Vector2<T>::operator/(const Vector2& _rhs) const
{
    return Vector2(x / _rhs.x, y / _rhs.y);
}

template<typename T>
Vector2<T> Vector2<T>::operator*(const T& _rhs) const
{
    return Vector2(x * _rhs, y * _rhs);
}

template<typename T>
Vector2<T> Vector2<T>::operator/(const T& _rhs) const
{
    return Vector2(x / _rhs, y / _rhs);
}

template<typename T>
Vector2<T>& Vector2<T>::operator+=(const Vector2& _rhs)
{
    x += _rhs.x;
    y += _rhs.y;
    return *this;
}

template<typename T>
Vector2<T>& Vector2<T>::operator-=(const Vector2& _rhs)
{
    x -= _rhs.x;
    y -= _rhs.y;
    return *this;
}

template<typename T>
Vector2<T>& Vector2<T>::operator*=(const Vector2& _rhs)
{
    x *= _rhs.x;
    y *= _rhs.y;
    return *this;
}

template<typename T>
Vector2<T>& Vector2<T>::operator/=(const Vector2& _rhs)
{
    x /= _rhs.x;
    y /= _rhs.y;
    return *this;
}

template<typename T>
Vector2<T>& Vector2<T>::operator*=(const T& _rhs)
{
    x *= _rhs;
    y *= _rhs;
    return *this;
}

template<typename T>
Vector2<T>& Vector2<T>::operator/=(const T& _rhs)
{
    x /= _rhs;
    y /= _rhs;
    return *this;
}

template<typename T>
float Vector2<T>::Dot(const Vector2& _rhs) const
{
    return x * _rhs.x + y * _rhs.y;
}

template<typename T>
float Vector2<T>::Cross(const Vector2& _rhs) const
{
    return x * _rhs.y - y * _rhs.x;
}

template<typename T>
float Vector2<T>::Magnitude() const
{
    return std::sqrt(x * x + y * y);
}

template<typename T>
float Vector2<T>::MagnitudeSquared() const
{
    return x * x + y * y;
}

template<typename T>
Vector2<T> Vector2<T>::Normalize() const
{
    float mag = Magnitude();
    return Vector2(x / mag, y / mag);
}

template<typename T>
float Vector2<T>::Distance(const Vector2<T>& _rhs) const
{
    return std::sqrt((x - _rhs.x) * (x - _rhs.x) + (y - _rhs.y) * (y - _rhs.y));
}

template<typename T>
float Vector2<T>::DistanceSquared(const Vector2& _rhs) const
{
    return (x - _rhs.x) * (x - _rhs.x) + (y - _rhs.y) * (y - _rhs.y);
}

template<typename T>
float Vector2<T>::Angle(const Vector2& _rhs) const
{
    return std::acos(this->Dot(_rhs) / (Magnitude() * _rhs.Magnitude()));
}

template<typename T>
Vector2<T> Vector2<T>::Rotate(const T& _angle) const
{
    return Vector2(x * std::cos(_angle) - y * std::sin(_angle), x * std::sin(_angle) + y * std::cos(_angle));
}

template<typename T>
Vector2<T> Vector2<T>::Lerp(const Vector2& _lhs, const Vector2<T>& _rhs, const T& _alpha)
{
    return Vector2(_lhs.x * (1 - _alpha) + _rhs.x * _alpha, _lhs.y * (1 - _alpha) + _rhs.y * _alpha);
}

template<typename T>
Vector2<T> Vector2<T>::Max(const Vector2& _lhs, const Vector2& _rhs)
{
    return Vector2(_lhs.x > _rhs.x ? _lhs.x : _rhs.x, _lhs.y > _rhs.y ? _lhs.y : _rhs.y);
}

template<typename T>
Vector2<T> Vector2<T>::Min(const Vector2& _lhs, const Vector2& _rhs)
{
    return Vector2(_lhs.x < _rhs.x ? _lhs.x : _rhs.x, _lhs.y < _rhs.y ? _lhs.y : _rhs.y);
}

template<typename T>
T Vector2<T>::GetX() const
{
    return x;
}

template<typename T>
T Vector2<T>::GetY() const
{
    return y;
}

template<typename T>
void Vector2<T>::SetX(const T& _new_x)
{
    x = _new_x;
}

template<typename T>
void Vector2<T>::SetY(const T& _new_y)
{
    y = _new_y;
}

template<typename T>
void Vector2<T>::Set(const T& _new_x, const T& _new_y)
{
    x = _new_x;
    y = _new_y;
}

template<typename T>
void Vector2<T>::Set(const Vector2& _rhs)
{
    x = _rhs.x;
    y = _rhs.y;
}

template<typename T>
const Vector2<T> Vector2<T>::Zero(0, 0);

template<typename T>
const Vector2<T> Vector2<T>::One(1, 1);

template<typename T>
const Vector2<T> Vector2<T>::UnitX(1, 0);

template<typename T>
const Vector2<T> Vector2<T>::UnitY(0, 1);

template<typename T>
const Vector2<T> Vector2<T>::Up(0, 1);

template<typename T>
const Vector2<T> Vector2<T>::Down(0, -1);

template<typename T>
const Vector2<T> Vector2<T>::Left(-1, 0);

template<typename T>
const Vector2<T> Vector2<T>::Right(1, 0);

}

#pragma warning(pop)