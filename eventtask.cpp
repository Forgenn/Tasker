#include "eventtask.h"
#include "ui_eventtask.h"

eventTask::eventTask(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::eventTask)
{
    ui->setupUi(this);
    ui->calendarWidget->hide();
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

void eventTask::addTask(QListWidget* Window){
    QString Date = ui->calendarWidget->selectedDate().toString(Qt::RFC2822Date);
    if(ui->calendarWidget->isHidden()){
        Window->addItem(ui->lineEdit->text());
    } else {
        Window->addItem(ui->lineEdit->text() + " | " + Date);
    }
    this->hide();
}
