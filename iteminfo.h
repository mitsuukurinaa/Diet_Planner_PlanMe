#ifndef ITEMINFO_H
#define ITEMINFO_H

#include <QDialog>

namespace Ui {
class ItemInfo;
}

class ItemInfo : public QDialog
{
    Q_OBJECT

public:
    explicit ItemInfo(QWidget *parent = nullptr);
    ~ItemInfo();

private:
    Ui::ItemInfo *ui;
};

#endif // ITEMINFO_H
