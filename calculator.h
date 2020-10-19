#ifndef CALCULATOR_H
#define CALCULATOR_H

#include <QDialog>

namespace Ui {
class Calculator;
}

class Calculator : public QDialog
{
    Q_OBJECT

public:
    explicit Calculator(QWidget *parent = nullptr);
    ~Calculator();

private slots:

    //Set Gender
    void on_maleButton_clicked();
    void on_femaleButton_clicked();

    //Set Pal
    void on_activBox_activated(int index);

    //Ask buttons
    void on_BmiAsk_clicked();
    void on_PpmAsk_clicked();
    void on_CpmAsk_clicked();
    void on_Ask1_clicked();
    void on_Ask2_clicked();

    //Accept button
    void on_AcceptButton_accepted();

private:
    Ui::Calculator *ui;

    //Variables
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
    double Gain;

};

#endif // CALCULATOR_H
