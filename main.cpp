#include "includes.h"
#include "mainInherited.h"
#include "mainwindow.h"
#include "loginwindow.h"
#include "resetwindow.h"
#include "loginmanager.h"
#include "httprequest.h"

loginTransfer mainTransfer; //extern in mainInherited.h

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    QPointer<MainWindow> mainWindow = new MainWindow;
    QPointer<loginWindow> login = new loginWindow;
    QPointer<resetWindow> reset = new resetWindow;
    mainTransfer.setChildWindows(mainWindow, login, reset);
    return a.exec();
}

void sendEvent(int state, loginTransfer transferObj)//retarded code, doesnt respect encapsulation heirarchy
{
    if(state == 1)
    {
        net::HTTPResponses response = transferObj.doLogin();
        switch (response) //enum comparison for login
        {
        case net::HTTPResponses::loginSuccess:
            transferObj.dodgyLoginTextSetter("Login Successful");
            transferObj.transfer();
            break;
        case net::HTTPResponses::loginFailure:
            transferObj.dodgyLoginTextSetter("Invalid Details");
            break;
        case net::HTTPResponses::databaseDown:
            transferObj.dodgyLoginTextSetter("Down for maintainance");
            break;
        case net::HTTPResponses::unknownResponse:
            transferObj.dodgyLoginTextSetter("Check Connection");
            break;
        }
    }
    else if(state == 0)
    {
        transferObj.~loginTransfer();
    }
    else if(state == 2) //State to transfer to forgot password window.
    {
        transferObj.resetWindowTransfer();
    }
}
