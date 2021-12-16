#include "stringrequest.h"
using namespace net;

StringRequest::StringRequest(int method, std::string resource, std::string ipAddress, std::string json = "")
{
    std::string jLength = std::to_string(json.length());
    switch (method)
    {
        case 0:
            this->HTMLRequestString += "POST /"+resource+" HTTP/1.1\r\n";
            this->HTMLRequestString += "Host: "+ipAddress+"\r\n";
            this->HTMLRequestString += "Content-Type: application/x-www-form-urlencoded\r\n";
            this->HTMLRequestString += "Content-Length: " + jLength + "\r\n";
            this->HTMLRequestString += "Connection: close\r\n\r\n";  //NOTE THE Double line feed
            this->HTMLRequestString += json;
            break;
        case 1:
            this->HTMLRequestString += "GET /" + resource +'?'+ json + " HTTP/1.1\r\n";
            this->HTMLRequestString += "Host: " + ipAddress + "\r\n";
            this->HTMLRequestString += "Connection: close\r\n\r\n";
            this->HTMLRequestString += json;
            break;


    }
    this->ipAddress = ipAddress;
}

std::string StringRequest::returnString()
{
    return this->HTMLRequestString;
}

StringRequest::operator std::string() const
{
    return this->HTMLRequestString;
}

std::string StringRequest::returnIpAddress()
{
    return this->ipAddress;
}
