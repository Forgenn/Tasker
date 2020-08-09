#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "eventtask.h"


QListWidget * MainWindow::pListWidget = nullptr;

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{

    ui->setupUi(this);
    pListWidget = ui->listWidget;
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
    eventTask eventTaskWindow;
    eventTaskWindow.setModal(true);
    eventTaskWindow.exec();
}

void MainWindow::on_listWidget_itemClicked(QListWidgetItem *item)
{
    item->~QListWidgetItem();
}
