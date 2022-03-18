#pragma once
#include "includes.h"
#include "loginwindow.h"
#include "threattype.h"
#include "accountwindow.h"
#include "license.h"
#include "statsmanager.h"

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
    void setLicenseType(license::t_licenses license);
    std::string getUsername();
    std::string getPassword();
    license::t_licenses getLicenseType();
    void update();

private slots:
    void on_treeView_activated(const QModelIndex &index);

    void on_gui_startScan_clicked();

    void on_actionEdit_Details_triggered();

    void closeEvent(QCloseEvent *event);

private:
    Ui::MainWindow *ui;
    std::string m_username;
    std::string m_password;
    license::t_licenses m_license;
    QFileSystemModel* model;
    QPointer<accountWindow> w_account;
    std::string m_searchPath;
    std::vector<threats::threat> threatList;
    QStandardItemModel* threatListModel;
    int threatCount = 0;
    ScannedFrequency* scanFreq;
    ThreatLevelSum* threatSum;
};

