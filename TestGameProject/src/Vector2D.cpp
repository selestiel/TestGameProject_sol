#include "Vector2D.h"

Vector2D::Vector2D()
{
	x = 0.0;
	y = 0.0;
}

Vector2D::Vector2D(float x, float y)
{
	this->x = x;
	this->y = y;
}

Vector2D& Vector2D::Add(const Vector2D& vector)
{
	this->x += vector.x;
	this->y += vector.y;

	return *this;
}

Vector2D& Vector2D::Subtract(const Vector2D& vector)
{
	this->x -= vector.x;
	this->y -= vector.y;
	return *this;
}

Vector2D& Vector2D::Multiply(const Vector2D& vector)
{
	this->x *= vector.x;
	this->y *= vector.y;
	return *this;
}

Vector2D& Vector2D::Divide(const Vector2D& vector)
{
	this->x /= vector.x;
	this->y /= vector.y;
	return *this;
}

Vector2D& Vector2D::operator+=(const Vector2D vect2)
{
	return this->Add(vect2);
}

Vector2D& Vector2D::operator-=(const Vector2D vect2)
{
	return this->Subtract(vect2);
}

Vector2D& Vector2D::operator*=(const Vector2D vect2)
{
	return this->Multiply(vect2);
}

Vector2D& Vector2D::operator/=(const Vector2D vect2)
{
	return this->Divide(vect2);
}

Vector2D& Vector2D::operator*(const int& i)
{
	this->x *= i;
	this->y *= i;
	return *this;
}

Vector2D& Vector2D::Zero()
{
	this->x = 0;
	this->y = 0;
	return *this;
}

Vector2D& operator+(Vector2D& vect1, const Vector2D vect2)
{
	return vect1.Add(vect2);
}
Vector2D& operator-(Vector2D & vect1, const Vector2D vect2)
{
	return vect1.Subtract(vect2);
}

Vector2D& operator*(Vector2D& vect1, const Vector2D vect2)
{
	return vect1.Multiply(vect2);
}

Vector2D& operator/(Vector2D& vect1, const Vector2D vect2)
{
	return vect1.Divide(vect2);
}

std::ostream& operator<<(std::ostream& stream, const Vector2D vect)
{
	return stream << "(" << vect.x << " , " << vect.y << ")";
	
}
