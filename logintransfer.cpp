#include "logintransfer.h"
#include "includes.h"
#include "httprequest.h"
#include "stringrequest.h"

loginTransfer::loginTransfer(MainWindow *mainref, loginWindow *loginref, resetWindow* resetref)
{
    this->main = mainref;
    this->login = loginref;
    this->reset = resetref;
}
/*dont make destructor function, QT has its own window and memory management stuff,
 it will delete windows on when the stack unwinds

 */

void loginTransfer::setChildWindows(MainWindow *mainref, loginWindow *loginref, resetWindow* resetref)
{
    this->main = mainref;
    this->login = loginref;
    this->reset = resetref;
    this->login->show();
}

net::HTTPResponses loginTransfer::doLogin()
{
    json loginVars;
    loginVars["Username"] = m_username;
    loginVars["Password"] = m_password;
    //std::cout << loginVars.dump();
    net::StringRequest sReq(0,"aleks/test.php","51.38.80.233",loginVars.dump());
    //std::cout << std::string(sReq) << std::endl;
    net::Session s1;
    s1.initialiseEndpoint("51.38.80.233", "http");
    s1.connectAndSend(sReq);
    int loginState = net::parseResponse(s1.returnResponse());
    return net::mapIntToEnum(loginState);
}

void loginTransfer::transfer(){
    this->login->hide();
    this->main->setUsername(this->login->getUsername());
    this->main->setPassword(this->login->getPassword());
    this->main->update();
    this->main->show();
}

void loginTransfer::resetWindowTransfer()
{
    //execution flow from this function onwards will remove main and login window, user must restart program after
    //setting password
    this->login->hide();
    delete this->main;
    delete this->login;
    this->reset->show();
    this->reset->update();
    //DO NOT TRY ACCESSING MAIN AND LOGIN AFTER FUNCTION HAS BEEN RUN, WILL RESULT IN SEG FAULT
    //THIS IS DEFINED BEHAVIOUR.
}

//getters and setters

std::string loginTransfer::getPassword(){return this->m_password;}
std::string loginTransfer::getUsername(){return this->m_username;}
void loginTransfer::setPassword(std::string password){this->m_password=password;}
void loginTransfer::setUsername(std::string username){this->m_username=username;}
void loginTransfer::dodgyLoginTextSetter(std::string message){this->login->setLoginMessage(message);}
