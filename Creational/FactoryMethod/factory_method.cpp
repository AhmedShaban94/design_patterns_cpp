#include <iostream>
#include <memory>

struct Product
{
    Product()          = default;
    virtual ~Product() = default;

    virtual void operation() = 0;
};

struct ConcreteProduct1 : public Product
{
    ConcreteProduct1()  = default;
    ~ConcreteProduct1() = default;

    void operation() override
    {
        std::cout << "Creating ConcreteProduct1\n";
    }
};

struct ConcreteProduct2 : public Product
{
    ConcreteProduct2()  = default;
    ~ConcreteProduct2() = default;

    void operation() override
    {
        std::cout << "Creating ConcreteProduct2\n";
    }
};

struct Factory
{
public:
    Factory()          = default;
    virtual ~Factory() = default;

    virtual std::unique_ptr<Product> createProduct() = 0;
};

struct ConcreteFactory1 : public Factory
{
    std::unique_ptr<Product> createProduct() override
    {
        return std::make_unique<ConcreteProduct1>();
    }
};

struct ConcreteFactory2 : public Factory
{
    std::unique_ptr<Product> createProduct() override
    {
        return std::make_unique<ConcreteProduct2>();
    }
};

int main()
{
    ConcreteFactory1 factory1{};
    ConcreteFactory2 factory2{};

    const auto product1 = factory1.createProduct();
    const auto product2 = factory2.createProduct();

    product1->operation();
    product2->operation();
    return EXIT_SUCCESS;
}