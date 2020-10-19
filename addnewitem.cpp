#include "addnewitem.h"
#include "ui_addnewitem.h"
#include "QMessageBox"

MainWindow *AddNewItem::mainwindow = nullptr;

AddNewItem::AddNewItem(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::AddNewItem)
{
    ui->setupUi(this);
    QDialog::setWindowTitle("Nowy produkt...");
    QPixmap background("C:/Users/Alan/Desktop/QT Projects/Planner/background.png");
   // background = background.scaled(this->size(), Qt::IgnoreAspectRatio);
    QPalette palette;
    palette.setBrush(QPalette::Background, background);
    this->setPalette(palette);


}

AddNewItem::~AddNewItem()
{
    delete ui;
}

