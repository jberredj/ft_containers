#ifndef MYCLASS_HPP
# define MYCLASS_HPP
# include <ostream>
class MyClass {
public:
    int x;
    int y;

    MyClass();
    MyClass(int _x, int _y);
    ~MyClass();

    // Define the less-than operator for sorting in the map
    bool operator<(const MyClass& other) const;
    bool operator>(const MyClass& other) const;
    bool operator<=(const MyClass& other) const;
    
	bool operator==(const MyClass& other) const;

    bool operator!=(const MyClass& other) const;
};

std::ostream& operator<<(std::ostream& os, const MyClass& obj);
#endif