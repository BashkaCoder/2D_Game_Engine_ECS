#pragma once
#include <iostream>

class Vector2D { //x, y - float
public:
	float x;
	float y;

	Vector2D();
	Vector2D(float x, float y);


	Vector2D& Add(const Vector2D& vec);
	Vector2D& Substract(const Vector2D& vec);
	Vector2D& Multiply(const Vector2D& vec);
	Vector2D& Divide(const Vector2D& vec);
	
	friend Vector2D& operator+(Vector2D& lhs, const Vector2D& rhs);
	friend Vector2D& operator-(Vector2D& lhs, const Vector2D& rhs);
	friend Vector2D& operator*(Vector2D& lhs, const Vector2D& rhs);
	friend Vector2D& operator/(Vector2D& lhs, const Vector2D& rhs);

	Vector2D& operator+=(const Vector2D& vec);
	Vector2D& operator-=(const Vector2D& vec);
	Vector2D& operator*=(const Vector2D& vec);
	Vector2D& operator/=(const Vector2D& vec);

	Vector2D& operator*(const int& val);
	Vector2D& Zero();

	friend std::ostream& operator<<(std::ostream& out, const Vector2D& vec);
};

