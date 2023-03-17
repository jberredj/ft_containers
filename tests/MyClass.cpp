#include <ostream>
#include "MyClass.hpp"

MyClass::MyClass() : x(0), y(0) {}
MyClass::MyClass(const MyClass &src): x(src.x), y(src.y) {}
MyClass::MyClass(int _x, int _y) : x(_x), y(_y) {}
MyClass::~MyClass() {}

bool operator<(const MyClass& lhs, const MyClass& rhs) {
	if (lhs.x < rhs.x) {
		return true;
	}
	if (lhs.x > rhs.x) {
		return false;
	}
	return lhs.y < rhs.y;
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