#include <string>
#include "randomValue.hpp"
#include "MyClass.hpp"

template <>
int randomValue<int>::get() { return rand(); }

template <>
char randomValue<char>::get() { return static_cast<char>(rand()) % 256; }

template <>
size_t randomValue<char>::getIteration(void) { return static_cast<char>(rand()) % 256; }

template <>
std::string randomValue<std::string>::get() {
	std::string	charset = \
	"abcdefghijklmnopqrstuvwxyz" \
	"ABCDEFGHUJKLMNOPQRSTUVWXYZ"\
	"0123456789" \
	"~`!@#$%^&*()_+{}[]:;\"'\\|<>,.?//*";
	int length = rand() % 20 + 1;
	std::string str;
	for (int i = 0; i < length; i++) {
		str += charset[rand() % charset.length()];
	}
	return str;
}


template <>
MyClass randomValue<MyClass>::get() {
	int x = rand();
	int y = rand();
	return MyClass(x, y);
}