#include "includes.h"
#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
   ui->setupUi(this);
   QPixmap item(QPixmap("/Users/aleks/Downloads/test.png"));
   ui->gui_ads->setPixmap(item);
   this->threatList.reserve(10);

   model = new QFileSystemModel(this);
   model->setRootPath(QDir::rootPath());
   model->setReadOnly(true);
   model->setFilter(QDir::Drives|QDir::NoDotAndDotDot|QDir::AllDirs);
   ui->treeView->setModel(this->model);
   ui->treeView->setColumnWidth(0,265);
   ui->treeView->setRootIndex(model->index(QDir::rootPath()));

   threatListModel = new QStandardItemModel(0,2,this);
   threatListModel->setHorizontalHeaderLabels({"Name","Type","Hash","Severity"});
   ui->gui_ThreatTable->setEditTriggers(QAbstractItemView::NoEditTriggers);
   ui->gui_ThreatTable->setModel(threatListModel);
   ui->gui_ThreatTable->setColumnWidth(0,350);
   ui->gui_ThreatTable->setColumnWidth(1,110);

   this->scanFreq = new ScannedFrequency();
   this->scanFreq->loadData();
   this->scanFreq->setData();
   this->threatSum = new ThreatLevelSum();
   this->threatSum->loadData();
   this->threatSum->setData();
   ui->gui_scanDangerousAverage->setChart(this->threatSum->Chart);
   ui->gui_scanAverage->setChart(this->scanFreq->Chart);

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

void MainWindow::setLicenseType(license::t_licenses license)
{
    this->m_license = license;
}

std::string MainWindow::getUsername()
{
    return this->m_username;
}

std::string MainWindow::getPassword()
{
    return this->m_password;
}

license::t_licenses MainWindow::getLicenseType()
{
    return this->m_license;
}

void MainWindow::update()
{
    if(this->m_license == license::t_licenses::license_none || this->m_license == license::t_licenses::license_standard)
    {
        ui->gui_ads->show();
    }
    else
    {
        ui->gui_ads->hide();
    }
}

void MainWindow::on_treeView_activated(const QModelIndex &index)
{
    if(!std::regex_search((this->model->filePath(index).toStdString()),std::regex("[:*?<>|]+|(.app)+"))){
        this->ui->gui_searchDir->setText("Current Search Directory: " + this->model->filePath(index));
        this->m_searchPath = this->model->filePath(index).toStdString();
    }
    else
    {
        return;
    }
}

void MainWindow::on_gui_startScan_clicked()
{
    threats::threat testThreat("C:/test",threats::threatType::Type_Unknown,"",3142);
    testThreat.calculateFileHash();
    this->threatList.push_back(testThreat);
    this->threatListModel->setRowCount(threatList.size());
    this->threatCount += 1;
    for(unsigned int row = 0; row < this->threatList.size();row++)
    {
        for(int col = 0; col < threatListModel->columnCount(); col++)
        {
            QModelIndex index = threatListModel->index(row,col,QModelIndex());
            if(col == 0)
            {
                threatListModel->setData(index, QString::fromStdString(threatList[row].returnFileLocation()));
            }
            else if(col == 1)
            {
                threatListModel->setData(index, QString::fromStdString(threats::threat::mapThreatTypeToStr(threatList[row].returnThreatType())));
            }
            else if(col == 2)
            {
                threatListModel->setData(index,QString::fromStdString(threatList[row].returnFileHash()));
            }
            else
            {
                threatListModel->setData(index,QString::fromStdString(utils::intToStr(threatList[row].returnSeverity())));
            }
        }
    }
}

void MainWindow::closeEvent(QCloseEvent *event)
{
    this->scanFreq->addData(this->threatCount);
    this->scanFreq->saveData();
}

void MainWindow::on_actionEdit_Details_triggered()
{
    this->w_account = new accountWindow(nullptr,this->getUsername()); //guarded pointer
    this->w_account->show();
}
