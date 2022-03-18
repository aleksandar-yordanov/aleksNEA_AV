#include "includes.h"
#include "loginwindow.h"
#include "ui_loginwindow.h"
#include "mainInherited.h"


loginWindow::loginWindow(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::loginWindow)
{
    ui->setupUi(this);
    this->readDetails();
    this->m_saveState = false;
    if(this->m_username.length() != 0)
    {
        ui->gui_username->setText(QString::fromStdString(this->m_username));
    }
}

loginWindow::~loginWindow()
{
    delete ui;
}

void loginWindow::on_gui_exit_clicked()
{
    this->~loginWindow();
    sendEvent(0, mainTransfer);
}

std::string loginWindow::getUsername()
{
    return this->m_username;
}

std::string loginWindow::getPassword()
{
    return this->m_password;
}

void loginWindow::on_gui_continue_clicked()
{
    sendEvent(1, mainTransfer);
    saveStateWriteDetails(this->m_saveState);
}

void loginWindow::on_gui_username_textChanged(const QString &arg1)
{
    this->m_username = ui->gui_username->text().toStdString();
    mainTransfer.setUsername(ui->gui_username->text().toStdString());
}

void loginWindow::on_gui_password_textEdited(const QString &arg1)
{
    this->m_password = ui->gui_password->text().toStdString();
    mainTransfer.setPassword(ui->gui_password->text().toStdString());
}

void loginWindow::on_gui_password_returnPressed()
{
    sendEvent(1, mainTransfer);
    saveStateWriteDetails(this->m_saveState);
}

void loginWindow::on_gui_username_returnPressed()
{
    sendEvent(1, mainTransfer);
    saveStateWriteDetails(this->m_saveState);
}

void loginWindow::readDetails() //issue, crash on file creation
{
    std::ifstream file; //random file read crap from old project, integrate later, de-hardcoding required
    file.open(this->detailsFilePath);
    if(!file.is_open())
    {
        std::ofstream o(this->detailsFilePath.c_str());
        o << '\n' << std::endl;
        o.close();
    }
    if(utils::is_empty(file))
    {
        std::ofstream writefile;
        writefile.open(this->detailsFilePath.c_str());
        writefile << '\n' << std::endl;
        writefile.close();
    }
    std::vector<std::string> returnStr;
    std::string str;
    while (std::getline(file,str))
    {
        returnStr.push_back(str);
    }
    if(returnStr.size() <= 1)
    {
        if(returnStr[0][0] == '\0') this->m_username = "";
        this->m_username = returnStr[0];
    }
    else if(returnStr.size() > 1)
    {
        if(returnStr[0][0] == '\0') this->m_username = "";
        else
        {
        this->m_username = returnStr[0];
        this->m_saveState = utils::strToBool(returnStr[1]);
        }
    }
}

void loginWindow::saveStateWriteDetails(bool state)
{
    if(this->detailsFilePath.length() == 0)
    {
        return;
    }
    std::ofstream file;
    file.open(this->detailsFilePath);
    file.clear();
    if(state == false)
    {
        file << '\0' << '\n' << this->m_saveState << std::endl;
        file.close();
        return;
    }
    file << this->m_username << '\n' << utils::boolToStr(this->m_saveState) << std::endl;
    file.close();
}

void loginWindow::on_gui_resetPassword_clicked()
{
    sendEvent(2,mainTransfer) ;
}

void loginWindow::setLoginMessage(std::string message)
{
    this->ui->gui_loginState->setText(QString::fromStdString(message));
}

void loginWindow::on_gui_rememberDetails_toggled(bool checked)
{
    this->m_saveState = checked;
}
