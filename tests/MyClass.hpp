#ifndef MYCLASS_HPP
# define MYCLASS_HPP
# include <ostream>
class MyClass {
public:
    int x;
    int y;

    MyClass();
    MyClass(const MyClass &src);
    MyClass(const int _x, const int _y);
    ~MyClass();

    bool operator>(const MyClass& other) const;
    bool operator<=(const MyClass& other) const;
    
	bool operator==(const MyClass& other) const;

    bool operator!=(const MyClass& other) const;
};

bool operator<(const MyClass& lhs, const MyClass& rhs);


std::ostream& operator<<(std::ostream& os, const MyClass& obj);
#endif