#ifndef EVENTTASK_H
#define EVENTTASK_H

#include <QDialog>
#include <QGraphicsOpacityEffect>
#include <QListWidget>
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
    void addTask(QTreeWidget* Window);

    void on_pushButton_clicked();

private:
    Ui::eventTask *ui;
    void fadeIn();
    void fadeOut();
    void recalculateHeight(QTreeWidget* Window, QTreeWidgetItem* NewEvent);
};

void newItemWidgetTree(QVariant Event, QVariant Date, QTreeWidget* Window);
void addRoot(QVariant Event, QVariant Date, QTreeWidget* Window);
void addChild(QTreeWidgetItem * parent, QVariant Event, QVariant Date);

#endif // EVENTTASK_H
