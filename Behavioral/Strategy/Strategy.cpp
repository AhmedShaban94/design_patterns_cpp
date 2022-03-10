#include <iostream>
#include <memory>

enum class MailServiceType
{
    Gmail,
    Hotmail,
    Webmail
};

struct IMailService
{
    virtual void Send() = 0;
};

struct GmailService : IMailService
{
    void Send() override
    {
        std::cout << "Sending from Gmail.\n";
    }
};

struct HotmailService : IMailService
{
    void Send() override
    {
        std::cout << "Sending from Hotmail.\n";
    }
};

struct Webmail : IMailService
{
    void Send() override
    {
        std::cout << "Sending from Webmail.\n";
    }
};

struct Notification
{
private:
    std::unique_ptr<IMailService> mailService_{};

public:
    Notification() = default;
    Notification(std::unique_ptr<IMailService> mailService)
        : mailService_{ mailService.release() }
    {
    }

    void Send()
    {
        mailService_->Send();
    }

    void SetNotificationStrategy(std::unique_ptr<IMailService> mailService)
    {
        mailService_ = std::move(mailService);
    }
};

void Client(MailServiceType type)
{
    Notification notification{};
    switch (type)
    {
    case MailServiceType::Gmail:
        notification.SetNotificationStrategy(std::make_unique<GmailService>());
        break;

    case MailServiceType::Hotmail:
        notification.SetNotificationStrategy(
            std::make_unique<HotmailService>());
        break;

    case MailServiceType::Webmail:
        notification.SetNotificationStrategy(std::make_unique<Webmail>());
        break;
    }
    notification.Send();
}

int main()
{
    Client(MailServiceType::Gmail);
    Client(MailServiceType::Hotmail);
    Client(MailServiceType::Webmail);
    return EXIT_SUCCESS;
}