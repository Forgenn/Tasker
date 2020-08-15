#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "eventtask.h"
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

    //Create a spoiler like widget containing a list
    Section* section = new Section("Completed", 500, ui->widget);
    ui->spoilerLayout->addWidget(section);

    auto* anyLayout = new QVBoxLayout();
    OldEvents = new QListWidget();
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
            if (query.value(2).toInt() == 1){
                QListWidgetItem* NewEvent = new QListWidgetItem(query.value(0).toString() + " " + query.value(1).toString() , ui->listWidget);
                qDebug() << query.value(2).toBool();
                NewEvent->setFlags(NewEvent->flags() | Qt::ItemIsUserCheckable);
                NewEvent->setCheckState(Qt::Unchecked);
            }
        }
}

void MainWindow::ReturnPressed(int a){
 ui->gridStackedWidget->setCurrentIndex(a);
}


void MainWindow::on_pushButton_clicked()
{
    eventTask * eventTaskWindow = new eventTask();
    connect(eventTaskWindow, &eventTask::lineEditReturnPressed, this, &MainWindow::ReturnPressed);

    int a = ui->gridStackedWidget->addWidget(eventTaskWindow);
    ui->gridStackedWidget->setCurrentIndex(a);

}


void MainWindow::on_listWidget_itemClicked(QListWidgetItem *item)
{
    OldEvents->addItem(item->text());
    item->~QListWidgetItem();
}
