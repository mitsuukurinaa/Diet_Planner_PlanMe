#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "QVector"
#include "QList"
#include "QComboBox"
#include "QMap"
#include "addnewitem.h"

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();


private slots:

    //Add new item button
    void on_addItemButton_clicked();

    //Add Buttons
    void on_addItemOne_clicked();
    void on_addItemTwo_clicked();
    void on_addItemThree_clicked();
    void on_addItemFour_clicked();
    void on_addItemFive_clicked();

    //Delete Buttons
    void on_delItemOne_clicked();
    void on_delItemTwo_clicked();
    void on_delItemThree_clicked();
    void on_delItemFour_clicked();
    void on_delItemFive_clicked();

    //Show total results
    void ShowTotalResults(int arg);

    //Category ComboBox
    void on_addItemCategory_activated(int index);

    //Add a new item function
    void on_actionNewItem_triggered();

    //Open calculator function
    void on_actionCalculator_triggered();

    //Calculator functions
    void on_maleButton_clicked();
    void on_femaleButton_clicked();

    //Set Pal
    void on_activBox_activated(int index);

    //Target buttons
    void on_slimButton_clicked();
    void on_gainButton_clicked();

    //Ask buttons
    void on_BmiAsk_clicked();
    void on_PpmAsk_clicked();
    void on_CpmAsk_clicked();
    void on_Ask1_clicked();
    void on_Ask2_clicked();
//////
    //Accept button
    void on_AcceptButton_accepted();

    //Export Diet
    void on_actionExport_triggered();

    //Save and load functions
    void on_actionSave_triggered();
    void on_actionLoad_triggered();

    void on_slimButton_2_clicked();

    void on_backMainButton_clicked();

private:
    Ui::MainWindow *ui;

    //Variables for a new items
    int ItemID=1;
    QVector<QString> ItemName;
    QVector<double> ItemKcals;
    QVector<double> ItemProteins;
    QVector<double> ItemFats;
    QVector<double> ItemCarbons;
    int ItemCategory;

    //To show item variables in right labels
    int SelectMeal;

    //Item map
    QMap<QString,int> ItemMap;
    QMap<QString, QString> map;

    //Arrays for items and category
    double Kcals[5] {0,0,0,0,0};
    double Proteins[5]{0,0,0,0,0};
    double Fats[5]{0,0,0,0,0};
    double Carbons[5]{0,0,0,0,0};

    //Calculator variables
    QString PersonName;
    double Weight;
    double Height;
    double Age;
    double Pal;
    int Gender;

    //Basic calculations
    double Bmi;
    double Ppm;
    double Cpm;

    //Target
    double Slim;
    QString targetString;
    double Gain;
};
#endif // MAINWINDOW_H
