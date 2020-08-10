#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "eventtask.h"
#include "dockevent.h"
#include <QtSql>
#include <QtSql>

QListWidget * MainWindow::pListWidget = nullptr;

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{

    ui->setupUi(this);
    pListWidget = ui->listWidget;
    ui->listWidget->setStyleSheet("color:white;");
    ui->pushButton->setStyleSheet("color:white;");
}

MainWindow::~MainWindow()
{
    delete ui;
}

QListWidget * MainWindow::getListWidgetPtr()
{
    return pListWidget;
}


void MainWindow::on_pushButton_clicked()
{   //Add checkmark item to list
    //QListWidgetItem* item = new QListWidgetItem("item", ui->listWidget);
    //item->setFlags(item->flags() | Qt::ItemIsUserCheckable);
    //item->setCheckState(Qt::Unchecked);
    ui->listWidget->hide();
    ui->pushButton->hide();

    DockEvent * DockMain = new DockEvent();
    eventTask eventTaskWindow;

    this->addDockWidget(Qt::RightDockWidgetArea, DockMain);
    DockMain->setWidget(&eventTaskWindow);

    eventTaskWindow.setMinimumSize(QSize(320,200));
    eventTaskWindow.baseSize();
    eventTaskWindow.exec();
    DockMain->hide();
    ui->listWidget->show();
    ui->pushButton->show();
}

void MainWindow::on_listWidget_itemClicked(QListWidgetItem *item)
{
    item->~QListWidgetItem();
}
