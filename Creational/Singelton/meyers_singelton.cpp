#include <iostream>
#include <assert.h>

// Meyer's singelton is automatically thread-safe by standard.
class Singelton
{
private:
    Singelton()  = default;
    ~Singelton() = default;

public:
    Singelton(const Singelton&) = delete;
    Singelton& operator=(const Singelton&) = delete;
    static Singelton& getInstance()
    {
        static Singelton insatance;
        return insatance;
    }
};

int main()
{
    Singelton& singleton1{ Singelton::getInstance() };
    Singelton& singleton2{ Singelton::getInstance() };

    assert(&singleton1 == &singleton2);
    std::cout << &singleton1 << '\n';
    std::cout << &singleton2 << '\n';
    return EXIT_SUCCESS;
}