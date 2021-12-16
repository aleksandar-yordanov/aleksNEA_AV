#include "includes.h"
#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
   ui->setupUi(this);
   model = new QFileSystemModel;
   model->setRootPath(QDir::rootPath());
   model->setFilter(QDir::Dirs|QDir::Drives|QDir::NoDotAndDotDot|QDir::AllDirs);

   ui->treeView->setModel(this->model);
   ui->treeView->setColumnWidth(0,265);
   ui->treeView->setRootIndex(model->index(QDir::rootPath()));
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::setUsername(std::string username)
{
    this->m_username = username;
}

void MainWindow::setPassword(std::string password)
{
    this->m_password = password;
}

std::string MainWindow::getUsername()
{
    return this->m_username;
}

std::string MainWindow::getPassword()
{
    return this->m_password;
}

void MainWindow::update()
{
    this->ui->testUser->setText(QString::fromStdString(this->getUsername()));
    this->ui->testPass->setText(QString::fromStdString(this->getPassword()));
}

void MainWindow::on_treeView_activated(const QModelIndex &index)
{
    if(!std::regex_search((this->model->filePath(index).toStdString()),std::regex("[:*?<>|]+"))){
        this->ui->gui_searchDir->setText("Current Search Directory: " + this->model->filePath(index));
        this->m_searchPath = this->model->filePath(index).toStdString();
    }
    else
    {
        return;
    }
}
