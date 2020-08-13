#include "eventtask.h"
#include "ui_eventtask.h"

eventTask::eventTask(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::eventTask)
{
    ui->setupUi(this);
    ui->calendarWidget->hide();

    if(!this->isHidden())
        this->show();
    fadeIn();

}

eventTask::~eventTask()
{
    delete ui;
}

void eventTask::on_lineEdit_returnPressed()
{
    QListWidget* Window = MainWindow::getListWidgetPtr();
    addTask(Window);
}

void eventTask::on_toolButton_clicked()
{
    if(ui->calendarWidget->isHidden()){
        ui->toolButton->setArrowType(Qt::UpArrow);
        ui->calendarWidget->show();
    } else {
        ui->toolButton->setArrowType(Qt::DownArrow);
        ui->calendarWidget->hide();
    }
}

void eventTask::fadeIn(){
    QGraphicsOpacityEffect *eff = new QGraphicsOpacityEffect(this);
    setGraphicsEffect(eff);
    QPropertyAnimation *a = new QPropertyAnimation(eff,"opacity");
    a->setDuration(350);
    a->setStartValue(0);
    a->setEndValue(1);
    a->setEasingCurve(QEasingCurve::InBack);
    a->start(QPropertyAnimation::DeleteWhenStopped);
}

void eventTask::fadeOut(){
    QGraphicsOpacityEffect *eff = new QGraphicsOpacityEffect(this);
    setGraphicsEffect(eff);
    QPropertyAnimation *a = new QPropertyAnimation(eff,"opacity");
    a->setDuration(350);
    a->setStartValue(1);
    a->setEndValue(0);
    a->setEasingCurve(QEasingCurve::OutBack);
    a->start(QPropertyAnimation::DeleteWhenStopped);
}
void eventTask::addTask(QListWidget* Window){

    QString Date = ui->calendarWidget->selectedDate().toString(Qt::RFC2822Date);
    QString Event = ui->lineEdit->text();
    QListWidgetItem* NewEvent;

    QSqlDatabase mydb = MainWindow::getDB();
    QSqlQuery query;
    query.prepare("INSERT INTO CurrentEvent(EventName, EventDate, IsDone) values(:EventName,:EventDate,:IsDone)");

    if(ui->calendarWidget->isHidden()){
        NewEvent = new QListWidgetItem(ui->lineEdit->text(), Window);
        Date.clear();
    } else {
        NewEvent = new QListWidgetItem(ui->lineEdit->text() + " | " + Date, Window);
    }

    query.prepare("INSERT INTO CurrentEvent(EventName, EventDate, IsDone) values(:EventName,:EventDate,:IsDone)");
    query.bindValue(":EventName",Event);
    query.bindValue(":EventDate",Date);
    query.bindValue(":IsDone",1);

    NewEvent->setFlags(NewEvent->flags() | Qt::ItemIsUserCheckable);
    NewEvent->setCheckState(Qt::Unchecked);

    this->hide();
    fadeOut();
}
