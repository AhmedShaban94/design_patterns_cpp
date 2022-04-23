#include <iostream>
#include <memory>

class PersonBuilder;

class Person
{
private:
    std::string name_{}, streetAddress_{}, postCode_{}, city_{};
    std::string companyName_{}, position_{}, annualIncome_{};

public:
    Person() = default;
    Person(std::string name) : name_{ std::move(name) }
    {
    }
    ~Person() = default;

    friend class PersonBuilder;
    friend std::ostream& operator<<(std::ostream& os, const Person& p)
    {
        os << "name: " << p.name_ << '\n'
           << "Street Address: " << p.streetAddress_ << '\n'
           << "Post Code: " << p.postCode_ << '\n'
           << "City: " << p.city_ << '\n'
           << "Company: " << p.companyName_ << '\n'
           << "Position: " << p.position_ << '\n'
           << "Annual Income: " << p.annualIncome_ << '\n';
           return os;
    }
    static std::unique_ptr<PersonBuilder> create(const std::string& name);
};

std::unique_ptr<PersonBuilder> Person::create(const std::string& name)
{
    return std::make_unique<PersonBuilder>(name);
}

class PersonBuilder
{
private:
    Person person{};

public:
    PersonBuilder() = default;
    PersonBuilder(const std::string& name) : person{ name }
    {
    }
    ~PersonBuilder() = default;

    operator Person() const
    {
        return person;
    }

    PersonBuilder& lives()
    {
        return *this;
    }
    PersonBuilder& atStreet(std::string streetAddress)
    {
        person.streetAddress_ = std::move(streetAddress);
        return *this;
    }
    PersonBuilder& postCode(std::string postCode)
    {
        person.postCode_ = std::move(postCode);
        return *this;
    }
    PersonBuilder& inCity(std::string city)
    {
        person.city_ = std::move(city);
        return *this;
    }

    PersonBuilder& works()
    {
        return *this;
    }
    PersonBuilder& companyName(std::string companyName)
    {
        person.companyName_ = std::move(companyName);
        return *this;
    }
    PersonBuilder& position(std::string position)
    {
        person.position_ = std::move(position);
        return *this;
    }
    PersonBuilder& AnnualIncome(std::string annualIncome)
    {
        person.annualIncome_ = std::move(annualIncome);
        return *this;
    }
};

int main()
{
    Person person = Person::create("John")
                      ->lives()
                      .atStreet("number 4")
                      .postCode("2245")
                      .inCity("Dubai")
                      .works()
                      .companyName("Amazon")
                      .position("Software Engineer")
                      .AnnualIncome("300k $");
    std::cout << person;
    return EXIT_SUCCESS;
}