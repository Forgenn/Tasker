#ifndef MAINWINDOW_H
#define MAINWINDOW_H
#include <QtSql>
#include <QtDebug>
#include <QListWidget>
#include <QMainWindow>
#include "ui_mainwindow.h"

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    static QTreeWidget * getListWidgetPtr();
    ~MainWindow();
    static QSqlDatabase getDB(){return mydb;};


signals:
    void oldEventsAdd(QTreeWidgetItem *item);

private slots:
    void on_pushButton_clicked();

    void ReturnPressed(int a);

    void on_treeWidget_itemClicked(QTreeWidgetItem *item, int column);

private:
    Ui::MainWindow *ui;
    static QTreeWidget * pListWidget;
    static QSqlDatabase mydb;
    void loadDatabase();
    //List for inactive events
    QListWidget * OldEvents;
    void newItemWidgetList(QVariant Event, QVariant Date, QListWidget * Window);
};
#endif // MAINWINDOW_H
