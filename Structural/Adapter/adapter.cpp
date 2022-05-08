#include "nlohmann/json.hpp"
#include "tinyxml2.h"
#include <iostream>
#include <memory>
#include <string>
#include <vector>

class JSONWebService
{
public:
    JSONWebService()  = default;
    ~JSONWebService() = default;
    void serviceRequest(const nlohmann::json& jsonObject)
    {
        std::cout << "JSON Object from JSON WebServer: \n";
        std::cout << jsonObject.dump(4) << '\n';
    }
};

class XMLWebService
{
public:
    XMLWebService()  = default;
    ~XMLWebService() = default;
    void serviceRequest(const tinyxml2::XMLDocument& xmlObject)
    {
        std::cout << "XML Object from XML WebServer: \n";
        tinyxml2::XMLPrinter printer{};
        xmlObject.Accept(&printer);
        std::cout << printer.CStr();
    }
};

class IAdapter
{
public:
    IAdapter()                               = default;
    virtual ~IAdapter()                      = default;
    virtual void request(const std::string&) = 0;
};

class JSONRequestAdapter : public IAdapter
{
private:
    std::shared_ptr<JSONWebService> jsonWebService_
        = std::make_shared<JSONWebService>();

    [[nodiscard]] nlohmann::json stringToJSON(const std::string& str)
    {
        return nlohmann::json::parse(str);
    }

public:
    JSONRequestAdapter() = default;
    explicit JSONRequestAdapter(std::shared_ptr<JSONWebService> jsonWebService)
        : jsonWebService_{ jsonWebService }
    {
    }
    ~JSONRequestAdapter() = default;
    void request(const std::string& str) override
    {
        auto jsonObject = stringToJSON(str);
        jsonWebService_->serviceRequest(jsonObject);
    }
};

class XMLRequestAdapter : public IAdapter
{
private:
    std::shared_ptr<XMLWebService> xmlWebService_
        = std::make_shared<XMLWebService>();

    [[nodiscard]] tinyxml2::XMLDocument stringToXML(const std::string& str)
    {
        tinyxml2::XMLDocument doc;
        doc.Parse(str.c_str());
        return doc;
    }

public:
    XMLRequestAdapter() = default;
    explicit XMLRequestAdapter(std::shared_ptr<XMLWebService> xmlWebService)
        : xmlWebService_{ xmlWebService }
    {
    }
    ~XMLRequestAdapter() = default;
    void request(const std::string& str) override
    {
        const auto xmlObject = stringToXML(str);
        xmlWebService_->serviceRequest(xmlObject);
    }
};

class WebClient
{
    std::string content_{};
    std::shared_ptr<IAdapter> adapter_{};

public:
    WebClient()  = default;
    ~WebClient() = default;
    explicit WebClient(std::string str,
                       std::shared_ptr<IAdapter> adapter
                       = std::make_shared<JSONRequestAdapter>())
        : content_{ std::move(str) }, adapter_{ std::move(adapter) }
    {
    }

    void upload()
    {
        adapter_->request(this->content_);
    }

    void setAdapter(std::shared_ptr<IAdapter> adapter)
    {
        this->adapter_ = adapter;
    }

    void setContent(std::string str)
    {
        content_ = std::move(str);
    }
};

int main()
{
    // string payload to JSON
    WebClient client{ R"({"happy": true, "pi": 3.141})" };
    client.upload();

    // string payload to XML
    client.setAdapter(std::make_shared<XMLRequestAdapter>());
    client.setContent(R"(<xml>\
          <appid>appid-value111111</appid>\
          <mch_id>mch_id-value22222</mch_id>\
          <nonce_str>nonce_str-value3333333</nonce_str>\
          <transaction_id>transaction_id-value44444444</transaction_id>\
          <sign>sign-value5555555555</sign>\
        </xml>)");
    client.upload();

    return EXIT_SUCCESS;
}