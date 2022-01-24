#include <assert.h>
#include <iostream>
#include <mutex>

std::mutex m;
class Singelton
{
private:
    static Singelton* instance;

    Singelton()  = default;
    ~Singelton() = default;

public:
    Singelton(const Singelton&) = delete;
    Singelton& operator=(const Singelton&) = delete;
    static Singelton& getInstance()
    {
        if (instance == nullptr)
        {
            std::lock_guard<std::mutex> lock{ m };
            if (instance == nullptr)
                instance = new Singelton{};
        }
        return *instance;
    }
};

Singelton* Singelton::instance{ nullptr };

int main()
{
    Singelton& singleton1{ Singelton::getInstance() };
    Singelton& singleton2{ Singelton::getInstance() };

    assert(&singleton1 == &singleton2);
    std::cout << &singleton1 << '\n';
    std::cout << &singleton2 << '\n';
    return EXIT_SUCCESS;
}