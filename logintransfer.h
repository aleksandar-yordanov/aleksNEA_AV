#pragma once

#include "includes.h"
#include "mainwindow.h"
#include "loginwindow.h"
#include "resetwindow.h"
#include "httprequest.h"

namespace Ui {
    class MainWindow;
    class loginWindow;
}

class loginTransfer
{
public:
    loginTransfer(MainWindow* mainref = nullptr, loginWindow* loginref = nullptr, resetWindow* resetref = nullptr);
    void setChildWindows(MainWindow* mainref, loginWindow* loginref, resetWindow* resetref);
    //~loginTransfer();

private:
    //neccessary for program function
    MainWindow* main;
    loginWindow* login;
    resetWindow* reset;
    //not neccessary for program function
    //resetWindow* reset;

public:
    void transfer();
    void resetWindowTransfer();
    net::HTTPResponses doLogin();
    std::string getPassword();
    std::string getUsername();
    void setUsername(std::string username);
    void setPassword(std::string password);
    void dodgyLoginTextSetter(std::string message);

private:
    std::string m_username;
    std::string m_password;
};

