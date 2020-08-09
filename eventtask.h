#ifndef EVENTTASK_H
#define EVENTTASK_H

#include <QDialog>

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

private:
    Ui::eventTask *ui;
};

#endif // EVENTTASK_H
