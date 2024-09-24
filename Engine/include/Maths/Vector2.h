#pragma once
#include <algorithm>
#include <SFML/System/Vector2.hpp>

namespace Maths
{
	template<typename T>
	class Vector2
	{
	public:
		T x;
		T y;

		/**  
		 * \brief Default constructor, set 0 to both components  
		 */
		Vector2();

		/**  
		 * \brief Constructor with explicit values for both components  
		 * \param _x X component  
		 * \param _y Y component  
		 */
		Vector2(T _x, T _y);

		/**  
		 * \brief Default destructor  
		 */
		~Vector2() = default;

		/**  
		 * \brief Explicit conversion to sf::Vector2  
		 */
		explicit operator sf::Vector2<T>() const { return sf::Vector2<T>(x, y); }

		/**  
		 * \brief Constructor from sf::Vector2  
		 * \param _value sf::Vector2 to convert from  
		 */
		explicit Vector2(sf::Vector2<T> _value) : x(_value.x), y(_value.y) {}

		/**  
		 * \brief Copy constructor  
		 */
		Vector2(const Vector2& _other) = default;

		/**  
		 * \brief Move constructor  
		 */
		Vector2(Vector2&& _other) noexcept = default;

		/**  
		 * \brief Copy assignment operator  
		 */
		Vector2& operator=(const Vector2& _other) = default;

		/**  
		 * \brief Assignment operator from sf::Vector2  
		 * \param _other sf::Vector2 to assign from  
		 * \return Reference to this  
		 */
		Vector2& operator=(const sf::Vector2<T>& _other)
		{
			x = _other.x;
			y = _other.y;
			return *this;
		}

		/**  
		 * \brief Move assignment operator  
		 */
		Vector2& operator=(Vector2&& _other) noexcept = default;

		/**  
		 * \brief Move assignment operator from sf::Vector2  
		 * \param _other sf::Vector2 to move from  
		 * \return Reference to this  
		 */
		Vector2& operator=(sf::Vector2<T>&& _other) noexcept
		{
			x = std::move(_other.x);
			y = std::move(_other.y);
			return *this;
		}

		/**  
		 * \brief Addition operator  
		 * \param _rhs Right-hand side vector  
		 * \return Result of addition  
		 */
		Vector2 operator+(const Vector2& _rhs) const;

		/**  
		 * \brief Subtraction operator  
		 * \param _rhs Right-hand side vector  
		 * \return Result of subtraction  
		 */
		Vector2 operator-(const Vector2& _rhs) const;

		/**  
		 * \brief Multiplication operator  
		 * \param _rhs Right-hand side vector  
		 * \return Result of multiplication  
		 */
		Vector2 operator*(const Vector2& _rhs) const;

		/**  
		 * \brief Division operator  
		 * \param _rhs Right-hand side vector  
		 * \return Result of division  
		 */
		Vector2 operator/(const Vector2& _rhs) const;

		/**  
		 * \brief Multiplication operator with scalar  
		 * \param _rhs Scalar value  
		 * \return Result of multiplication  
		 */
		Vector2 operator*(const T& _rhs) const;

		/**  
		 * \brief Division operator with scalar  
		 * \param _rhs Scalar value  
		 * \return Result of division  
		 */
		Vector2 operator/(const T& _rhs) const;

		/**  
		 * \brief Addition assignment operator  
		 * \param _rhs Right-hand side vector  
		 * \return Reference to this  
		 */
		Vector2& operator+=(const Vector2& _rhs);

		/**  
		 * \brief Subtraction assignment operator  
		 * \param _rhs Right-hand side vector  
		 * \return Reference to this  
		 */
		Vector2& operator-=(const Vector2& _rhs);

		/**  
		 * \brief Multiplication assignment operator  
		 * \param _rhs Right-hand side vector  
		 * \return Reference to this  
		 */
		Vector2& operator*=(const Vector2& _rhs);

		/**  
		 * \brief Division assignment operator  
		 * \param _rhs Right-hand side vector  
		 * \return Reference to this  
		 */
		Vector2& operator/=(const Vector2& _rhs);

		/**  
		 * \brief Multiplication assignment operator with scalar  
		 * \param _rhs Scalar value  
		 * \return Reference to this  
		 */
		Vector2& operator*=(const T& _rhs);

		/**  
		 * \brief Division assignment operator with scalar  
		 * \param _rhs Scalar value  
		 * \return Reference to this  
		 */
		Vector2& operator/=(const T& _rhs);

		/**  
		 * \brief Calculate the dot product  
		 * \param _rhs Right-hand side vector  
		 * \return Dot product  
		 */
		float Dot(const Vector2& _rhs) const;

		/**  
		 * \brief Calculate the cross product  
		 * \param _rhs Right-hand side vector  
		 * \return Cross product  
		 */
		float Cross(const Vector2& _rhs) const;

		/**  
		 * \brief Calculate the magnitude  
		 * \return Magnitude  
		 */
		float Magnitude() const;

		/**  
		 * \brief Calculate the squared magnitude  
		 * \return Squared magnitude  
		 */
		float MagnitudeSquared() const;

		/**  
		 * \brief Normalize the vector  
		 * \return Normalized vector  
		 */
		Vector2 Normalize() const;

		/**  
		 * \brief Calculate the distance to another vector  
		 * \param _rhs Right-hand side vector  
		 * \return Distance  
		 */
		float Distance(const Vector2& _rhs) const;

		/**  
		 * \brief Calculate the squared distance to another vector  
		 * \param _rhs Right-hand side vector  
		 * \return Squared distance  
		 */
		float DistanceSquared(const Vector2& _rhs) const;

		/**  
		 * \brief Calculate the angle between two vectors  
		 * \param _rhs Right-hand side vector  
		 * \return Angle in radians  
		 */
		float Angle(const Vector2& _rhs) const;

		/**  
		 * \brief Rotate the vector by a given angle  
		 * \param _angle Angle in radians  
		 * \return Rotated vector  
		 */
		Vector2 Rotate(const T& _angle) const;

		/**  
		 * \brief Linearly interpolate between two vectors  
		 * \param _lhs Left-hand side vector  
		 * \param _rhs Right-hand side vector  
		 * \param _alpha Interpolation factor  
		 * \return Interpolated vector  
		 */
		static Vector2 Lerp(const Vector2& _lhs, const Vector2& _rhs, const T& _alpha);

		/**  
		 * \brief Get the component-wise maximum of two vectors  
		 * \param _lhs Left-hand side vector  
		 * \param _rhs Right-hand side vector  
		 * \return Component-wise maximum vector  
		 */
		static Vector2 Max(const Vector2& _lhs, const Vector2& _rhs);

		/**  
		 * \brief Get the component-wise minimum of two vectors  
		 * \param _lhs Left-hand side vector  
		 * \param _rhs Right-hand side vector  
		 * \return Component-wise minimum vector  
		 */
		static Vector2 Min(const Vector2& _lhs, const Vector2& _rhs);

		/**  
		 * \brief Get the X component  
		 * \return X component  
		 */
		T GetX() const;

		/**  
		 * \brief Get the Y component  
		 * \return Y component  
		 */
		T GetY() const;

		/**  
		 * \brief Set the X component  
		 * \param _new_x New X component  
		 */
		void SetX(const T& _new_x);

		/**  
		 * \brief Set the Y component  
		 * \param _new_y New Y component  
		 */
		void SetY(const T& _new_y);

		/**  
		 * \brief Set both X and Y components  
		 * \param _new_x New X component  
		 * \param _new_y New Y component  
		 */
		void Set(const T& _new_x, const T& _new_y);

		/**  
		 * \brief Set both X and Y components from another vector  
		 * \param _rhs Vector to copy components from  
		 */
		void Set(const Vector2& _rhs);

		static const Vector2 Zero;
		static const Vector2 One;
		static const Vector2 UnitX;
		static const Vector2 UnitY;
		static const Vector2 Up;
		static const Vector2 Down;
		static const Vector2 Left;
		static const Vector2 Right;

		/**  
		 * \brief Equality operator  
		 * \param _lhs Left-hand side vector  
		 * \param _rhs Right-hand side vector  
		 * \return True if vectors are equal, false otherwise  
		 */
		friend bool operator==(const Vector2& _lhs, const Vector2& _rhs)
		{
			return _lhs.x == _rhs.x && _lhs.y == _rhs.y;
		}

		/**  
		 * \brief Inequality operator  
		 * \param _lhs Left-hand side vector  
		 * \param _rhs Right-hand side vector  
		 * \return True if vectors are not equal, false otherwise  
		 */
		friend bool operator!=(const Vector2& _lhs, const Vector2& _rhs)
		{
			return !(_lhs == _rhs);
		}
	};

	using Vector2i = Vector2<int>;
	using Vector2u = Vector2<unsigned int>;
	using Vector2f = Vector2<float>;
	using Vector2d = Vector2<double>;
}

template class Maths::Vector2<int>;
template class Maths::Vector2<unsigned int>;
template class Maths::Vector2<float>;
template class Maths::Vector2<double>;

#include "Maths/Vector2.inl"
