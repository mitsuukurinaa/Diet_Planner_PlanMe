#include "iteminfo.h"
#include "ui_iteminfo.h"

ItemInfo::ItemInfo(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::ItemInfo)
{
    ui->setupUi(this);

    //Style
    QDialog::setWindowTitle("Informacje o produkcie");
    QPixmap background("C:/Users/Alan/Desktop/QT Projects/Planner/background.png");
    QPalette palette;
    palette.setBrush(QPalette::Background, background);
    this->setPalette(palette);
}

ItemInfo::~ItemInfo()
{
    delete ui;
}
