#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "eventtask.h"
#include "Section.h"

#include <QBoxLayout>
#include <QLabel>
#include <QPushButton>

//Pointer to Main list widget, so eventtask can write to it
QTreeWidget * MainWindow::pListWidget = nullptr;

//Database initializacion for the static getter
const QString DRIVER("QSQLITE");
QSqlDatabase MainWindow::mydb = QSqlDatabase::addDatabase(DRIVER);

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{

    ui->setupUi(this);

    pListWidget = ui->treeWidget;

    ui->gridStackedWidget->setContentsMargins(0,0,0,0);

    //Create a spoiler-like widget containing a list
    Section* section = new Section("Completed", 500, ui->widget);
    section->setStyleSheet("color: rgb(163, 154, 88)");
    ui->spoilerLayout->addWidget(section);

    auto* anyLayout = new QVBoxLayout();
    OldEvents = new QListWidget();
    OldEvents->setStyleSheet("border : none");
    anyLayout->addWidget(OldEvents);
    section->setContentLayout(*anyLayout);

    connect(OldEvents, &QListWidget::itemClicked, this , &MainWindow::listWidget_itemClicked);
    loadDatabase();
    ui->treeWidget->setColumnCount(1);

}


MainWindow::~MainWindow()
{
    delete ui;
}

QTreeWidget * MainWindow::getListWidgetPtr()
{
    return pListWidget;
}



void MainWindow::loadDatabase(){

    QDir dir("C:/Tasker/");

    if (!dir.exists())
        dir.mkdir("C:/Tasker/");

    mydb.setConnectOptions("QSQLITE_OPEN_URI");
    mydb.setDatabaseName("C:/Tasker/events.db");


    if(!mydb.open()){
        qDebug()<<"Failed to open database";
        return;
    }

    QSqlQuery InitialQuery("CREATE TABLE IF NOT EXISTS CurrentEvent (EventId INTEGER NOT NULL UNIQUE PRIMARY KEY AUTOINCREMENT, EventName TEXT NOT NULL, EventDate TEXT, IsDone INTEGER NOT NULL DEFAULT 1);", mydb);
    InitialQuery.exec();
    qDebug() << InitialQuery.lastError() << "Inital" ;

    QSqlQuery query("SELECT [EventName], [EventDate], [isDone] FROM CurrentEvent", mydb);
    query.exec();

    qDebug() << query.lastError() << "QUEERY";
        //Dont want to do it like this, root will be date and children will be events in that day.
        while (query.next()) {
            if (query.value(2).toInt() == 1){
                newItemWidgetTree(query.value(0), query.value(1), ui->treeWidget);
            } else {
                newItemWidgetList(query.value(0), query.value(1), OldEvents);

            }
        }
}

void MainWindow::newItemWidgetList(QVariant Event, QVariant Date, QListWidget * Window){
    QListWidgetItem* OldEventItem = new QListWidgetItem(Window);
    OldEventItem->setText(Event.toString());
    OldEventItem->setData(Qt::UserRole, Date);
    qDebug() << "newitemwidgetlist" << Date;
}


void MainWindow::ReturnPressed(int a){
    ui->gridStackedWidget->setCurrentIndex(a);
    ui->pushButton->show();
}


void MainWindow::on_pushButton_clicked()
{
    eventTask * eventTaskWindow = new eventTask();
    connect(eventTaskWindow, &eventTask::lineEditReturnPressed, this, &MainWindow::ReturnPressed);

    int a = ui->gridStackedWidget->addWidget(eventTaskWindow);
    ui->gridStackedWidget->setCurrentIndex(a);
    ui->pushButton->hide();

}

void MainWindow::on_treeWidget_itemClicked(QTreeWidgetItem *item, int column)
{
    if (item->parent()){
        qDebug() << "ontreewidgetclicked"<< item->text(0) << item->parent()->data(0, Qt::UserRole);
        newItemWidgetList(item->text(0), item->parent()->data(0, Qt::UserRole), OldEvents);
        //OldEvents->addItem(item->text(0));
        QSqlQuery query(mydb);
        query.setForwardOnly(true);

        query.prepare("UPDATE CurrentEvent SET isDone=:Done WHERE Eventname=:EventName AND EventDate=:EventDate");
        query.bindValue(":EventName",item->text(0));
        query.bindValue(":Done",0);
        query.bindValue(":EventDate", item->parent()->data(0, Qt::UserRole).toString());

        query.exec();
         qDebug() << query.lastError();

        item->~QTreeWidgetItem();

    }
}

void MainWindow::listWidget_itemClicked(QListWidgetItem *item){
    //qDebug <<
    QSqlQuery query(mydb);
    query.setForwardOnly(true);

    query.prepare("UPDATE CurrentEvent SET isDone=:Done WHERE Eventname=:EventName AND EventDate=:EventDate");
    query.bindValue(":EventName",item->text());
    query.bindValue(":Done",1);
    query.bindValue(":EventDate", item->data(Qt::UserRole).toString());
    query.exec();

    QVariant Event(item->text());
    QVariant Date(item->data(Qt::UserRole));
    qDebug() << "listwidgetitemclicked" << item->data(Qt::UserRole) << item->text();
    newItemWidgetTree(Event, Date, pListWidget);
    item->~QListWidgetItem();
}
