#include "eventtask.h"
#include "ui_eventtask.h"
#include "mainwindow.h"

eventTask::eventTask(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::eventTask)
{
    ui->setupUi(this);
}

eventTask::~eventTask()
{
    delete ui;
}

void eventTask::on_lineEdit_returnPressed()
{
    QListWidget* Window = MainWindow::getListWidgetPtr();
    QString Date = ui->calendarWidget->selectedDate().toString(Qt::RFC2822Date);
    Window->addItem(ui->lineEdit->text() + " | " + Date);

}
