#ifndef EVENTTASK_H
#define EVENTTASK_H

#include <QDialog>
#include <QGraphicsOpacityEffect>
#include "mainwindow.h"

namespace Ui {
class eventTask;
}

class eventTask : public QWidget
{
    Q_OBJECT

public:
    explicit eventTask(QWidget *parent = nullptr);
    ~eventTask();
signals:
    void lineEditReturnPressed(int a);
private slots:
    void on_lineEdit_returnPressed();    
    void on_toolButton_clicked();
    void addTask(QListWidget* Window);

private:
    Ui::eventTask *ui;
    void fadeIn();
    void fadeOut();
    void recalculateHeight(QListWidget* Window, QListWidgetItem* NewEvent);
};

#endif // EVENTTASK_H
