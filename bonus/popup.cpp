#include "mainwindow.h"
#include "popup.h"
#include <qwidget.h>
#include <QVBoxLayout>
#include <QPushButton>

Popup::Popup(QWidget *parent) : QWidget(parent)
{

}

Popup::~Popup()
{

}

void Popup::show_it()
{
    this->show();
}

void Popup::set_ui_obj()
{
    qDebug("lourde queu");
    QWidget *window = this->window();
      QOpenGLWindow *QtWPreview = new QOpenGLWindow();
      QPushButton *button2 = new QPushButton("Two");
      QPushButton *button3 = new QPushButton("Three");
      QPushButton *button4 = new QPushButton("Four");
      QPushButton *button5 = new QPushButton("Five");

      QHBoxLayout *layout = new QHBoxLayout;
      layout->addWidget(button2);
      layout->addWidget(button3);
      layout->addWidget(button4);
      layout->addWidget(button5);

      window->setLayout(layout);
      window->show();
}
