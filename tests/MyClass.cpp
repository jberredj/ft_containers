#include <ostream>
#include "MyClass.hpp"

MyClass::MyClass() : x(0), y(0) {}
MyClass::MyClass(int _x, int _y) : x(_x), y(_y) {}
MyClass::~MyClass() {}

// Define the less-than operator for sorting in the map
bool MyClass::operator<(const MyClass& other) const {
	if (x < other.x) {
		return true;
	}
	if (x > other.x) {
		return false;
	}
	return y < other.y;
}

bool MyClass::operator>(const MyClass& other) const { return other < *this; }

bool MyClass::operator<=(const MyClass& other) const { return !(*this > other); }

bool MyClass::operator==(const MyClass& other) const { return x == other.x && y == other.y; }

bool MyClass::operator!=(const MyClass& other) const {
	return !(*this == other);
}

std::ostream& operator<<(std::ostream& os, const MyClass& obj)
{
    os << "MyClass(" << obj.x << ", " << obj.y << ")";
    return os;
}