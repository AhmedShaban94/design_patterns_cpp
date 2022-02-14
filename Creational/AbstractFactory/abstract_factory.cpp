#include <iostream>
#include <memory>

struct IProductA
{
    virtual ~IProductA()                     = default;
    virtual std::string doSomethingA() const = 0;
};

struct ConcreteProductA1 : IProductA
{
    ~ConcreteProductA1() override = default;
    std::string doSomethingA() const override
    {
        return "Creating Product A1\n";
    }
};

struct ConcreteProductA2 : IProductA
{
    ~ConcreteProductA2() override = default;
    std::string doSomethingA() const override
    {
        return "Creating Product A2\n";
    }
};

struct IProductB
{
    virtual ~IProductB()                     = default;
    virtual std::string doSomethingB() const = 0;
};

struct ConcreteProductB1 : IProductB
{
    ~ConcreteProductB1() override = default;
    std::string doSomethingB() const override
    {
        return "Creating Product B1\n";
    }
};

struct ConcreteProductB2 : IProductB
{
    ~ConcreteProductB2() override = default;
    std::string doSomethingB() const override
    {
        return "Creating Product B2\n";
    }
};

struct AbstarctFactory
{
    virtual ~AbstarctFactory()                                = default;
    virtual std::unique_ptr<IProductA> createProductA() const = 0;
    virtual std::unique_ptr<IProductB> createProductB() const = 0;
};

struct ConcreteFactory1 : AbstarctFactory
{
    ~ConcreteFactory1() override = default;
    std::unique_ptr<IProductA> createProductA() const override
    {
        return std::make_unique<ConcreteProductA1>();
    }
    std::unique_ptr<IProductB> createProductB() const override
    {
        return std::make_unique<ConcreteProductB1>();
    }
};

struct ConcreteFactory2 : AbstarctFactory
{
    ~ConcreteFactory2() override = default;
    std::unique_ptr<IProductA> createProductA() const override
    {
        return std::make_unique<ConcreteProductA2>();
    }
    std::unique_ptr<IProductB> createProductB() const override
    {
        return std::make_unique<ConcreteProductB2>();
    }
};

int main()
{
    std::unique_ptr<AbstarctFactory> factory1
        = std::make_unique<ConcreteFactory1>();
    std::unique_ptr<AbstarctFactory> factory2
        = std::make_unique<ConcreteFactory2>();

    auto productA1 = factory1->createProductA();
    auto productA2 = factory2->createProductA();
    std::cout << productA1->doSomethingA();
    std::cout << productA2->doSomethingA();

    auto productB1 = factory1->createProductB();
    auto productB2 = factory2->createProductB();
    std::cout << productB1->doSomethingB();
    std::cout << productB2->doSomethingB();

    return EXIT_SUCCESS;
}