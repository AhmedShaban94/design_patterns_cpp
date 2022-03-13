#include <iostream>
#include <memory>
#include <string_view>
#include <vector>

struct ISubscriber
{
    virtual void Update(std::string_view message) = 0;
};

struct ConcreteSubscriber : ISubscriber
{
    void Update(std::string_view message) override
    {
        std::cout << "MESSAGE: " << message << '\n';
    }
};

struct Publisher
{
private:
    std::vector<std::shared_ptr<ISubscriber>> subscribersList{};

public:
    void subscribe(std::shared_ptr<ISubscriber> subscriber)
    {
        subscribersList.push_back(subscriber);
    }
    void unsubscribe(std::shared_ptr<ISubscriber> subscriber)
    {
        subscribersList.erase(std::remove(subscribersList.begin(),
                                          subscribersList.end(), subscriber),
                              subscribersList.end());
    }
    void notify(std::string_view message)
    {
        for (const auto& s : subscribersList)
            s->Update(message);
    }
};

int main()
{
    Publisher publisher{};
    for (const auto& i : { 1, 2, 3, 4, 5 })
        publisher.subscribe(std::make_shared<ConcreteSubscriber>());
    publisher.notify("I have an update.\n");

    std::cout << "After new subscription.\n\n\n"; 
    std::shared_ptr<ISubscriber> sub6 = std::make_shared<ConcreteSubscriber>();
    publisher.subscribe(sub6);
    publisher.notify("Here is a new update.\n"); 

    std::cout << "After un-subsription.\n\n\n";
    publisher.unsubscribe(sub6); 
    publisher.notify("Here is another new update.\n");
    return EXIT_SUCCESS;
}