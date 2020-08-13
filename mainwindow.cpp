#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "eventtask.h"
#include "dockevent.h"
#include "Section.h"

#include <QBoxLayout>
#include <QLabel>
#include <QPushButton>

//Pointer to Main list widget, so eventtask can write to it
QListWidget * MainWindow::pListWidget = nullptr;

//Database initializacion for the static getter
const QString DRIVER("QSQLITE");
QSqlDatabase MainWindow::mydb = QSqlDatabase::addDatabase(DRIVER);

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{

    ui->setupUi(this);
    pListWidget = ui->listWidget;
    ui->listWidget->setStyleSheet("color:white;");
    ui->pushButton->setStyleSheet("color:white;");

    loadDatabase();

    Section* section = new Section("Completed", 500, ui->widget);
    ui->spoilerLayout->addWidget(section);

    auto* anyLayout = new QVBoxLayout();
    QListWidget * OldEvents = new QListWidget();
    OldEvents->setStyleSheet("border : none");
    anyLayout->addWidget(OldEvents);

    section->setContentLayout(*anyLayout);

}


MainWindow::~MainWindow()
{
    delete ui;
}

QListWidget * MainWindow::getListWidgetPtr()
{
    return pListWidget;
}

void MainWindow::loadDatabase(){

    mydb.setDatabaseName("events.db");

    if(!mydb.open()){
        qDebug()<<"Failed to open database";
        return;
    }

    QSqlQuery InitialQuery("CREATE TABLE IF NOT EXISTS CurrentEvent (EventId INTEGER NOT NULL UNIQUE AUTOINCREASE, EventName TEXT NOT NULL, EventDate TEXT, IsDone INTEGER NOT NULL DEFAULT 1);");

    QVariant ref_id = 0;
    QSqlQuery query("SELECT [EventName], [EventDate], [isDone] FROM CurrentEvent", mydb);
    query.exec();

    qDebug() << query.lastError();

        while (query.next()) {
            qDebug() << query.value(1).toString();
            if (query.value(2).toInt() == 1){
                QListWidgetItem* NewEvent = new QListWidgetItem(query.value(0).toString() + " " + query.value(1).toString() , ui->listWidget);
                qDebug() << query.value(2).toBool();
                NewEvent->setFlags(NewEvent->flags() | Qt::ItemIsUserCheckable);
                NewEvent->setCheckState(Qt::Unchecked);
            }
        }
}


void MainWindow::on_pushButton_clicked()
{   //Add checkmark item to list
    //QListWidgetItem* item = new QListWidgetItem("item", ui->listWidget);
    //item->setFlags(item->flags() | Qt::ItemIsUserCheckable);
   // item->setCheckState(Qt::Unchecked);
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
