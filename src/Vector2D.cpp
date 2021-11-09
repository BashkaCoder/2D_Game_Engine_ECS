#include <exception>
#include "Vector2D.h"

Vector2D::Vector2D() {
	x = y = 0.0f;
}
Vector2D::Vector2D(float x, float y) {
	this->x = x;
	this->y = y;
}

Vector2D& Vector2D::Add(const Vector2D& vec) {
	this->x += vec.x;
	this->y += vec.y;
	return *this;
}
Vector2D& Vector2D::Substract(const Vector2D& vec) {
	this->x -= vec.x;
	this->y -= vec.y;
	return *this;
}
Vector2D& Vector2D::Multiply(const Vector2D& vec) {
	this->x *= vec.x;
	this->y *= vec.y;
	return *this;
}
Vector2D& Vector2D::Divide(const Vector2D& vec) {
	if (vec.x == 0) {
		throw std::invalid_argument("Division by 0 in vector.x!");
		return *this;
	}
	else if (vec.y == 0) {
		throw std::invalid_argument("Division by 0 in vector.y!");
		return *this;
	}
	else {
		this->x /= vec.x;
		this->y /= vec.y;
		return *this;
	}
}

Vector2D& operator+(Vector2D& lhs, const Vector2D& rhs) {
	lhs.Add(rhs);
	return lhs;
}
Vector2D& operator-(Vector2D& lhs, const Vector2D& rhs) {
	lhs.Substract(rhs);
	return lhs;
}
Vector2D& operator*(Vector2D& lhs, const Vector2D& rhs) {
	lhs.Multiply(rhs);
	return lhs;
}
Vector2D& operator/(Vector2D& lhs, const Vector2D& rhs) {
	lhs.Divide(rhs);
	return lhs;
}

Vector2D& Vector2D::operator+=(const Vector2D& vec) {
	this->Add(vec);
	return *this;
}
Vector2D& Vector2D::operator-=(const Vector2D& vec) {
	this->Substract(vec);
	return *this;
}
Vector2D& Vector2D::operator*=(const Vector2D& vec) {
	this->Multiply(vec);
	return *this;
}
Vector2D& Vector2D::operator/=(const Vector2D& vec) {
	this->Divide(vec);
	return *this;
}

Vector2D& Vector2D::operator*(const int& val) {
	this->x *= val;
	this->y *= val;
	return *this;
}

Vector2D& Vector2D::Zero() {
	this->x = 0;
	this->y = 0;
	return *this;
}

std::ostream& operator<<(std::ostream& out, const Vector2D& vec) {
	out << "(" << vec.x << ", " << vec.y << ")";
	return out;
}


