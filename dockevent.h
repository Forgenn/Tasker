#ifndef DOCKEVENT_H
#define DOCKEVENT_H

#include <QDockWidget>

namespace Ui {
class DockEvent;
}

class DockEvent : public QDockWidget
{
    Q_OBJECT

public:
    explicit DockEvent(QWidget *parent = nullptr);
    ~DockEvent();

private:
    Ui::DockEvent *ui;
};

#endif // DOCKEVENT_H
