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
    ui->treeWidget->setStyleSheet("color:white;");
    ui->pushButton->setStyleSheet("color:white;");
    ui->gridStackedWidget->setContentsMargins(0,0,0,0);
    loadDatabase();

    //Create a spoiler like widget containing a list
    Section* section = new Section("Completed", 500, ui->widget);
    ui->spoilerLayout->addWidget(section);

    auto* anyLayout = new QVBoxLayout();
    OldEvents = new QListWidget();
    OldEvents->setStyleSheet("border : none");
    anyLayout->addWidget(OldEvents);
    section->setContentLayout(*anyLayout);

    ui->treeWidget->setColumnCount(2);

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
        //Dont want to do it like this, root will be date and children will be events in that day.
        while (query.next()) {
            if (query.value(2).toInt() == 1){
                newItemWidget(query.value(0), query.value(1), ui->treeWidget);

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

void MainWindow::on_treeWidget_itemClicked(QTreeWidgetItem *item, int column)
{
    OldEvents->addItem(item->text(0));
    item->~QTreeWidgetItem();
}
