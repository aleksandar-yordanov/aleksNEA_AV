#pragma once
#include "includes.h"
#include "loginwindow.h"

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; class loginWindow;}
QT_END_NAMESPACE

class loginTransfer;

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

public:
    void setUsername(std::string username);
    void setPassword(std::string password);
    std::string getUsername();
    std::string getPassword();
    void update();

private slots:
    void on_treeView_activated(const QModelIndex &index);

private:
    Ui::MainWindow *ui;
    std::string m_username;
    std::string m_password;
    QFileSystemModel* model;
    std::string m_searchPath;
};
