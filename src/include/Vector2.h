#ifndef VECTOR2_H
#define VECTOR2_H

#include <cmath>
#include <ostream>
class Vector2 {
public:
    inline Vector2(float x, float y) : x(x), y(y) {};
    inline Vector2() : x(0), y(0) {};
    Vector2(const Vector2 &v) :
			x(v.getX()), y(v.getY()) {
	};

	Vector2(Vector2 &&v) :
			x(v.getX()), y(v.getY()) {
	}

	Vector2(const Vector2 *v) :
			x(v->getX()), y(v->getY()) {
	}

    inline Vector2& operator=(const Vector2 &v) {
		x = v.x;
		y = v.y;
		return *this;
	}

	// move assignment - not really needed
	inline Vector2& operator=(const Vector2 &&v) {
		x = v.x;
		y = v.y;
		return *this;
	}


    inline float getX() const {return x;};
    inline float getY() const {return y;};
    // length of the vector
	inline float magnitude() const {
		return sqrtf(powf(x, 2) + powf(y, 2));
	}

	// vector in the same direction of length 1
	inline Vector2 normalize() const {
		return *this / magnitude();
	}

	// counter clockwise rotation in a normal coordinate system, and
	// it is clockwise rotation if we work with a coordinate system
	// in which the vertical axe is flipped (it is like a mirror over
	// the horizontal axe)-- which the case when working with the SDL.
	//
	Vector2 rotate(float degrees) const;

	// Computes the angle between 'this' and 'v'. The result is
	// between -180 and 180, and is such that the following holds:
	//
	//   this->rotate(angle).normalize() == v.normalize()
	//
	float angle(const Vector2 &v) const;

	// vector subtraction
	inline Vector2 operator-(const Vector2 &v) const {
		return Vector2(x - v.x, y - v.y);
	}

	// vector addition
	inline Vector2 operator+(const Vector2 &v) const {
		return Vector2(x + v.x, y + v.y);
	}

	// multiplication by constant (scaling)
	inline Vector2 operator*(float d) const {
		return Vector2(x * d, y * d);
	}

	// division by constant (scaling)
	inline Vector2 operator/(float d) const {
		return Vector2(x / d, y / d);
	}

	// scalar multiplication
	inline float operator *(const Vector2 &d) const {
		return d.x * x + d.y * y;
	}
    float x;
    float y;
};

std::ostream& operator<<(std::ostream &os, const Vector2 &v);
#endif
