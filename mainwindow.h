#ifndef MAINWINDOW_H
#define MAINWINDOW_H

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
    static QListWidget * getListWidgetPtr();
    ~MainWindow();

private slots:
    void on_pushButton_clicked();

    void on_listWidget_itemClicked(QListWidgetItem *item);

private:
    Ui::MainWindow *ui;
    static QListWidget * pListWidget;
};
#endif // MAINWINDOW_H
