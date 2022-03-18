#include "httprequest.h"

using namespace std::chrono_literals;
using namespace net;

std::vector<char> vBuffer(1024*20);
HTTPRequest::HTTPRequest()
{
    this->idleWork = std::make_unique<asio::io_context::work>(this->context);
    this->threadContext = std::thread([&](){context.run();});
    this->socket = std::make_unique<asio::ip::tcp::socket>(this->context);
}

HTTPRequest::~HTTPRequest()
{
    this->context.stop();
    if(this->threadContext.joinable()) this->threadContext.join();
}

void HTTPRequest::initialiseEndpoint(StringRequest req, std::string service)
{
    asio::ip::tcp::resolver resolver(this->context);
    asio::ip::tcp::resolver::query query(req.returnIpAddress(),service);
    asio::ip::tcp::resolver::iterator iter = resolver.resolve(query);

    this->socketEndpoint = iter->endpoint();
}

void HTTPRequest::initialiseEndpoint(std::string ipAddress, std::string service)
{
    asio::ip::tcp::resolver resolver(this->context);
    asio::ip::tcp::resolver::query query(ipAddress,service);
    asio::ip::tcp::resolver::iterator iter = resolver.resolve(query);

    this->socketEndpoint = iter->endpoint();
}

void Session::grabdata()
{
    this->socket->async_read_some(asio::buffer(vBuffer.data(),vBuffer.size()),
        [&](std::error_code ec, std::size_t length)
        {
            if(!ec){
                std::cout << "\nRead " << length << " bytes\n";
                for(int i = 0; i < static_cast<int>(length); i++){
                    //std::cout << vBuffer[i];
                    this->response.push_back(vBuffer[i]);
                }
                grabdata();
            }
        }
    );
}

void Session::connectAndSend(StringRequest req)
{
    if(this->socket == nullptr)
    {
        std::cout << "nullptr:socket";
    }
    this->socket->connect(this->socketEndpoint,this->ec);
    if(!this->ec)
    {
        std::cout<<"service resolved" << '\n';
    }
    else if(this->ec)
    {
        std::cout << this->ec.message() << '\n';
        socket->close();
        return;
    }
    if(this->socket->is_open())
    {
        std::cout << "socket open" << '\n';
        this->grabdata();

        std::string sReq = std::string(req);
        this->socket->write_some(asio::buffer(sReq.data(),sReq.size()),this->ec);

        this->socket->wait(this->socket->wait_read,this->ec);
        size_t bytes = this->socket->available();
        std::cout << "bytes available: " << bytes << '\n';
        if(bytes > 0)
        {
            std::vector<char> vBuffer(bytes);
            this->socket->read_some(asio::buffer(vBuffer.data(),vBuffer.size()),this->ec);
            for(auto c : vBuffer)
            {
                std::cout << c;
            }
        }

        this->context.stop();

        if(this->threadContext.joinable()) this->threadContext.join();
    }
    else if(this->socket->is_open() == false)
    {
        std::cout << "socket closed" << std::endl;
    }
}

std::string Session::returnResponse()
{
    return this->response;
}

void Session::closeConnection()
{
    this->socket->close(this->ec);
}

HTTPRegisterResponses net::createMapIntToEnum(int value)
{
    switch(value)
    {
        case 0:
            return net::HTTPRegisterResponses::registerFailure;
            break;
        case 1:
            return net::HTTPRegisterResponses::registerSuccess;
            break;
        case 2:
            return net::HTTPRegisterResponses::invalidPasswordLength;
            break;
        case 3:
            return net::HTTPRegisterResponses::emailRegistered;
            break;
        case 4:
            return net::HTTPRegisterResponses::invalidEmail;
            break;
        default:
            return net::HTTPRegisterResponses::registerFailure;
            break;
    }
}

HTTPResponses net::mapIntToEnum(int value)
{
    switch(value)
    {
        case 0:
            return net::HTTPResponses::loginFailure;
            break;
        case 1:
            return net::HTTPResponses::loginSuccess;
            break;
        case 2:
            return net::HTTPResponses::databaseDown;
            break;
        case 3:
            return net::HTTPResponses::unknownResponse;
            break;
        default:
            return net::HTTPResponses::unknownResponse;
            break;
    }
}

HTTPResetResponses net::resetMapIntToEnum(int value)
{
    switch(value)
    {
        case 0:
            return net::HTTPResetResponses::databaseDown;
            break;
        case 1:
            return net::HTTPResetResponses::resetSuccess;
            break;
        case 2:
            return net::HTTPResetResponses::invalidPasswordLength;
            break;
        case 3:
            return net::HTTPResetResponses::usernameNotFound;
            break;
        case 4:
            return net::HTTPResetResponses::wrongPassword;
            break;
        default:
            return net::HTTPResetResponses::databaseDown;
            break;
    }
}

HTTPLicenseResponse net::licenseMapIntToEnum(int value)
{
    switch(value)
    {
    case 0:
        return net::HTTPLicenseResponse::databaseDown;
        break;
    case 1:
        return net::HTTPLicenseResponse::license_none;
        break;
    case 2:
        return net::HTTPLicenseResponse::license_standard;
        break;
    case 3:
        return net::HTTPLicenseResponse::license_premium;
        break;
    default:
        return net::HTTPLicenseResponse::databaseDown;
        break;
    }
}

int net::parseResponse(std::string inputStr)
{
    int initPos = inputStr.find("$");
    std::string curStr = "";
    if(initPos != static_cast<int>(std::string::npos))
    {
        for(unsigned long i = 1; i < (inputStr.length()-1)-initPos;i++)
        {
            if(inputStr[initPos+i] == '?'){
                break;
            }
            else{
                curStr += inputStr[initPos+i];
            }
        }
    }
    try {
        return std::stoi(curStr);
    } catch (std::invalid_argument) {
        return std::stoi("3");
    }
}
