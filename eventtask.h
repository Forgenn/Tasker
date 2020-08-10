#ifndef EVENTTASK_H
#define EVENTTASK_H

#include <QDialog>
#include "mainwindow.h"

namespace Ui {
class eventTask;
}

class eventTask : public QDialog
{
    Q_OBJECT

public:
    explicit eventTask(QWidget *parent = nullptr);
    ~eventTask();

private slots:
    void on_lineEdit_returnPressed();    
    void on_toolButton_clicked();
    void addTask(QListWidget* Window);

private:
    Ui::eventTask *ui;
};

#endif // EVENTTASK_H
