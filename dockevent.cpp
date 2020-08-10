#include "dockevent.h"
#include "ui_dockevent.h"

DockEvent::DockEvent(QWidget *parent) :
    QDockWidget(parent),
    ui(new Ui::DockEvent)
{
    ui->setupUi(this);
    this->setFeatures(QDockWidget::NoDockWidgetFeatures);
    this->setTitleBarWidget(new QWidget);
}

DockEvent::~DockEvent()
{
    delete ui;
}
