#include "Header.h"

#include <string>
#include <cstdarg>

/*(A > B)*/
#define MAX(A, B) (A > B) ? A : B

/*static member usage*/
class a
{
public:
	int *p;
	static int id;
	a() { ++id; }
};

int a::id = 0;

/*encrypt string*/
void cipher(char*&key)
{
	std::cout << "String: ";
	std::string s;
	std::cin >> s;

	std::string encrypted;
	for (int i = 0, j = 0; j < s.length(); ++i, ++j)
	{
		encrypted.push_back(s[j] ^ key[i]);
		if (i == strlen(key) - 1)
			i = -1;
	}

	std::cout << "Enrypted string: " << encrypted << std::endl;
	
	for (int i = 0, j = 0; j < s.length(); ++i, ++j)
	{
		encrypted[j] ^= s[i];
		if (i == strlen(key) - 1) 
			i = -1;
	}

	std::cout << "Key string: " << encrypted;
}

/*own printf for %s, %c, %d*/
void print(const char* string, ...)
{
	va_list ap;
	va_start(ap, string);

	for (int i = 0; i < strlen(string); ++i)
	{
		if (string[i] == '%' && i != strlen(string) - 1)
		{
			switch (string[i + 1])
			{
			case 's':
				std::cout << va_arg(ap, char*);
				break;
			case 'c':
				std::cout << va_arg(ap, char);
				break;
			case 'd':
				std::cout << va_arg(ap, int);
				break;
			default:
				std::cerr << "error";
			}
			++i;
		}
	}

	va_end(ap);
}

/*explicit usage example*/
class b
{
private:
	int x;
public:
	explicit b(int x) {}
};

void f(b) {}

/*extern usage*/
extern "C"
{
	char* strcpy(char*, const char*);
	size_t strlen(const char*);
}

int x = 3;

/*friend template class*/
template <typename T>
class bar;

//bar - дружественный для foo class несмотря на его шаблонный параметр
//bar<int>, bar<char> и т.д - все они будут друзьями foo<char>, foo<double>, ...
template<typename T>
struct foo {
	template<typename U>
	friend class bar;
};

//или так:
template <typename T>
struct foo3 {
	template <typename>
	friend class bar;
};

//bar - дружественный для foo только если foo имеет тот же параметр
//bar<int> - друг foo<int>, но не друг foo<char>
template<typename T>
struct foo2 {
	friend class bar<T>;
};

//test получит доступ к приватным полям класса T
template <typename T>
class test {
	friend T;             // note, not 'friend class T'!!!
};

int main(int argc, char* argv[])
{

	system("pause");
	return 0;
}

