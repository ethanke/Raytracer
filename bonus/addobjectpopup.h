#ifndef ADDOBJECTPOPUP_H
#define ADDOBJECTPOPUP_H

#include <QWidget>
#include <QObject>
#include <QDialog>

class addObjectPopup: public QWidget
{
public:
    addObjectPopup(QWidget *parent = NULL);
    ~addObjectPopup();
     void show_it();

public slots:


private:

};

#endif // ADDOBJECTPOPUP_H
