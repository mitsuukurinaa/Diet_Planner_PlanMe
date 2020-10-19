#ifndef ADDNEWITEM_H
#define ADDNEWITEM_H

#include <QDialog>
#include "QMap"

class MainWindow;


namespace Ui {
class AddNewItem;
}

class AddNewItem : public QDialog
{
    Q_OBJECT

public:
     AddNewItem(QWidget *parent = nullptr);

    ~AddNewItem();

     static MainWindow *mainwindow;

private slots:

private:
    Ui::AddNewItem *ui;

};

#endif // ADDNEWITEM_H
