#include "eventtask.h"
#include "ui_eventtask.h"

eventTask::eventTask(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::eventTask)
{
    ui->setupUi(this);
    ui->calendarWidget->hide();
    ui->lineEdit->setFocusPolicy(Qt::StrongFocus);
    ui->lineEdit->setFocus();
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
    QTreeWidget* Window = MainWindow::getListWidgetPtr();
    addTask(Window);
    emit lineEditReturnPressed(0);
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

void addRoot(QVariant Event, QVariant Date, QTreeWidget* Window){

     QTreeWidgetItem* NewEvent = new QTreeWidgetItem(Window);
     //NewEvent->setChildIndicatorPolicy(QTreeWidgetItem::DontShowIndicator);
     NewEvent->setExpanded(true);

     NewEvent->setText(0, Date.toDate().toString("dddd d MMMM"));
     Window->addTopLevelItem(NewEvent);

     addChild(NewEvent, Event, Date);

}
void addChild(QTreeWidgetItem * parent, QVariant Event, QVariant Date){

    QTreeWidgetItem* NewEvent = new QTreeWidgetItem();
    NewEvent->setText(0, Event.toString());

    NewEvent->setFlags(NewEvent->flags() | Qt::ItemIsUserCheckable);
    NewEvent->setCheckState(0, Qt::Unchecked);

    parent->addChild(NewEvent);
}

void newItemWidgetTree(QVariant Event, QVariant Date, QTreeWidget* Window){

    auto isDateFound = Window->findItems(Date.toDate().toString("dddd d MMMM") , Qt::MatchExactly, 0);

    if (isDateFound.isEmpty()){
        addRoot(Event, Date, Window);
    } else {
        addChild(isDateFound.first(), Event, Date);
    }

/**
    NewEvent->setData(0, 0, Event);
    NewEvent->setData(0, 1, Date);

    NewEvent->setText(0, NewEvent->data(0,0).toString().simplified());
    NewEvent->setText(1, NewEvent->data(0,1).toDate().toString());
    NewEvent->setTextAlignment(0, Qt::AlignLeft);
    NewEvent->setFlags(NewEvent->flags() | Qt::ItemIsUserCheckable);
    NewEvent->setCheckState(0, Qt::Unchecked);
    Window->addTopLevelItem(NewEvent);
*/
}


void eventTask::addTask(QTreeWidget* Window){

    QVariant Date = ui->calendarWidget->selectedDate();
    QVariant Event = ui->lineEdit->text();

    QSqlDatabase mydb = MainWindow::getDB();
    QSqlQuery query;
    query.setForwardOnly(true);
    query.prepare("INSERT INTO CurrentEvent(EventName, EventDate, IsDone) values(:EventName,:EventDate,:IsDone)");

    if(ui->calendarWidget->isHidden())
        Date.setValue(nullptr);

    newItemWidgetTree(Event, Date, Window);

    query.prepare("INSERT INTO CurrentEvent(EventName, EventDate, IsDone) values(:EventName,:EventDate,:IsDone)");
    query.bindValue(":EventName",Event);
    query.bindValue(":EventDate",Date);
    query.bindValue(":IsDone",1);
    query.exec();

    ui->lineEdit->clear();
    Date.setValue(nullptr);
}


//TODO
void eventTask::recalculateHeight(QTreeWidget* Window, QTreeWidgetItem* NewEvent){


}

void eventTask::on_pushButton_clicked()
{
    QTreeWidget* Window = MainWindow::getListWidgetPtr();
    addTask(Window);
    emit lineEditReturnPressed(0);
}
