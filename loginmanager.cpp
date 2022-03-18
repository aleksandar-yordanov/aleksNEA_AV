#include "loginmanager.h"
#include "includes.h"
#include "httprequest.h"
#include "stringrequest.h"

loginTransfer::loginTransfer(MainWindow *mainref, loginWindow *loginref, resetWindow* resetref)
{
    this->main = mainref;
    this->login = loginref;
    this->reset = resetref;
}

loginTransfer::loginTransfer(QPointer<MainWindow> mainref, QPointer<loginWindow> loginref, QPointer<resetWindow> resetref)
{
    this->main = mainref;
    this->login = loginref;
    this->reset = resetref;
}

void loginTransfer::setChildWindows(MainWindow *mainref, loginWindow *loginref, resetWindow* resetref)
{
    this->main = mainref;
    this->login = loginref;
    this->reset = resetref;
    this->login->show();
}

void loginTransfer::setChildWindows(QPointer<MainWindow> mainref, QPointer<loginWindow> loginref, QPointer<resetWindow> resetref)
{
    this->main = mainref;
    this->login = loginref;
    this->reset = resetref;
    this->login->show();
}

net::HTTPResponses loginTransfer::doLogin()
{
    if(m_username == "bypass" && m_password == "bypass") return net::mapIntToEnum(1); //DEBUG, REMOVE IN FINAL BUILD
    json loginVars; //crazy gaming json
    loginVars["Username"] = m_username;
    loginVars["Password"] = m_password;
    net::StringRequest sReq(net::method::METHOD_POST,"aleks/login.php","51.38.80.233",loginVars.dump());
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
    this->main->setLicenseType(license::getLicenseStatic(this->login->getUsername()));
    this->main->show();
    this->main->update();
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
    //this is defined behaviour. After any reset, program must be rerun/
}


std::string loginTransfer::getPassword()
{
    return this->m_password;
}
std::string loginTransfer::getUsername()
{
    return this->m_username;
}
void loginTransfer::setPassword(std::string password)
{
    this->m_password=password;
}
void loginTransfer::setUsername(std::string username)
{
    this->m_username=username;
}
void loginTransfer::dodgyLoginTextSetter(std::string message)
{
    this->login->setLoginMessage(message);
}
