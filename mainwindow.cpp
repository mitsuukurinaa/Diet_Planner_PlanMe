#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "QDebug"
#include "QMessageBox"
#include "QSettings"
#include "QFile"
#include "QMap"
#include "QtWidgets"
#include "QPrinter"
#include "calculator.h"
#include "addnewitem.h"
#include "QPixmap"
#include "QTextCodec"
#include "windows.h"


MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    on_actionLoad_triggered(); //Load data base

    //Style
    QMainWindow::setWindowTitle("PlanMe 1.2");
    QPixmap background(":/images/background.png");
    background = background.scaled(this->size(), Qt::IgnoreAspectRatio);
    QPalette palette;
    palette.setBrush(QPalette::Background, background);
    this->setPalette(palette);

    //Set start tab
    ui->tabWidget->setCurrentIndex(0);
;
}

MainWindow::~MainWindow()
{
    delete ui;
}

//Create and add a new item
void MainWindow::on_addItemButton_clicked()
{
    //Error dialog
    if (ui->newItemName->text() == "")
        {
            QMessageBox::warning(this,"Błąd!", "Uzupełnij wszystkie pola!", QMessageBox::Ok);
            return;
        }

            //Insert a new item variables to the vectors
            ItemName.push_back(ui->newItemName->text());
            ItemKcals.push_back(ui->newItemKcals->value());
            ItemProteins.push_back(ui->newItemProteins->value());
            ItemFats.push_back(ui->newItemFats->value());
            ItemCarbons.push_back(ui->newItemCarbons->value());

            //Assigment item category
            on_addItemCategory_activated(ItemCategory);
            ItemCategory = ui->newItemCategory->currentIndex();

            //Move item to right category
            switch(ItemCategory)
            {
                case 0:
                ui->mealOneLeft->addItem(ui->newItemName->text());
                ui->mealTwoLeft->addItem(ui->newItemName->text());
                break;

                case 1:
                ui->mealThreeLeft->addItem(ui->newItemName->text());
                ui->mealFourLeft->addItem(ui->newItemName->text());
                break;

                case 2:
                ui->mealFiveLeft->addItem(ui->newItemName->text());
                break;

                default:
                break;
            }

            //Add a new item to Item Map
            ItemMap.insert(ui->newItemName->text(), ItemMap.size());

            //Success dialog
            QMessageBox::information(this,"Sukces!", "Pomyślnie dodałeś produkt!", QMessageBox::Ok);

            //Return to main tab
            ui->tabWidget->setCurrentIndex(1);

}

//Add Buttons (from left side to the right side)
void MainWindow::on_addItemOne_clicked() //Meal One
{
    //Error dialog
    if(!ui->mealOneLeft->currentItem())
    {
      QMessageBox::warning(this,"Błąd!", "Zaznacz produkt!", QMessageBox::Ok);
      return;
    }

    //Move item to right side
     ui->mealOneRight->addItem(ui->mealOneLeft->currentItem()->text());

    //To show item variables in right labels
    SelectMeal =0;

    //Add
    Kcals[0]+=ItemKcals.at(ItemMap[ui->mealOneLeft->currentItem()->text()]);
    Proteins[0]+=ItemProteins.at(ItemMap[ui->mealOneLeft->currentItem()->text()]);
    Fats[0]+=ItemFats.at(ItemMap[ui->mealOneLeft->currentItem()->text()]);
    Carbons[0]+=ItemCarbons.at(ItemMap[ui->mealOneLeft->currentItem()->text()]);

    //Show results
    ShowTotalResults(SelectMeal);
}
void MainWindow::on_addItemTwo_clicked() //Meal Two
{
    //Error message
    if(!ui->mealTwoLeft->currentItem())
    {
      QMessageBox::warning(this,"Błąd!", "Zaznacz produkt!", QMessageBox::Ok);
      return;
    }

    //Move item to right side
     ui->mealTwoRight->addItem(ui->mealTwoLeft->currentItem()->text());

    //To show item variables in right labels
    SelectMeal =1;

    //Add
    Kcals[1]+=ItemKcals.at(ItemMap[ui->mealTwoLeft->currentItem()->text()]);
    Proteins[1]+=ItemProteins.at(ItemMap[ui->mealTwoLeft->currentItem()->text()]);
    Fats[1]+=ItemFats.at(ItemMap[ui->mealTwoLeft->currentItem()->text()]);
    Carbons[1]+=ItemCarbons.at(ItemMap[ui->mealTwoLeft->currentItem()->text()]);

    //Show results
    ShowTotalResults(SelectMeal);
}
void MainWindow::on_addItemThree_clicked() //Meal Three
{
    //Error messsage
    if(!ui->mealThreeLeft->currentItem())
    {
      QMessageBox::warning(this,"Błąd!", "Zaznacz produkt!", QMessageBox::Ok);
      return;
    }

    //Move item to right side
     ui->mealThreeRight->addItem(ui->mealThreeLeft->currentItem()->text());

    //To show item variables in right labels
    SelectMeal =2;

    //Add
    Kcals[2]+=ItemKcals.at(ItemMap[ui->mealThreeLeft->currentItem()->text()]);
    Proteins[2]+=ItemProteins.at(ItemMap[ui->mealThreeLeft->currentItem()->text()]);
    Fats[2]+=ItemFats.at(ItemMap[ui->mealThreeLeft->currentItem()->text()]);
    Carbons[2]+=ItemCarbons.at(ItemMap[ui->mealThreeLeft->currentItem()->text()]);

    //Show results
    ShowTotalResults(SelectMeal);
}
void MainWindow::on_addItemFour_clicked() //Meal four
{
    //Error mesage
    if(!ui->mealFourLeft->currentItem())
    {
      QMessageBox::warning(this,"Błąd!", "Zaznacz produkt!", QMessageBox::Ok);
      return;
    }

    //Move item to right side
     ui->mealFourRight->addItem(ui->mealFourLeft->currentItem()->text());

    //To show item variables in right labels
    SelectMeal =3;

    //Add
    Kcals[3]+=ItemKcals.at(ItemMap[ui->mealFourLeft->currentItem()->text()]);
    Proteins[3]+=ItemProteins.at(ItemMap[ui->mealFourLeft->currentItem()->text()]);
    Fats[3]+=ItemFats.at(ItemMap[ui->mealFourLeft->currentItem()->text()]);
    Carbons[3]+=ItemCarbons.at(ItemMap[ui->mealFourLeft->currentItem()->text()]);

    //Show results
    ShowTotalResults(SelectMeal);
}
void MainWindow::on_addItemFive_clicked() //Meal five
{
    //Error message
    if(!ui->mealFiveLeft->currentItem())
    {
      QMessageBox::warning(this,"Błąd!", "Zaznacz produkt!", QMessageBox::Ok);
      return;
    }

    //Move item to right side
     ui->mealFiveRight->addItem(ui->mealFiveLeft->currentItem()->text());

    //To show item variables in right labels
    SelectMeal =4;

    //Add
    Kcals[4]+=ItemKcals.at(ItemMap[ui->mealFiveLeft->currentItem()->text()]);
    Proteins[4]+=ItemProteins.at(ItemMap[ui->mealFiveLeft->currentItem()->text()]);
    Fats[4]+=ItemFats.at(ItemMap[ui->mealFiveLeft->currentItem()->text()]);
    Carbons[4]+=ItemCarbons.at(ItemMap[ui->mealFiveLeft->currentItem()->text()]);

    //Show results
    ShowTotalResults(SelectMeal);
}

//Show all results
void MainWindow::ShowTotalResults(int arg)
{
    arg = SelectMeal;
    switch (arg)
    {
    case 0: //Meal 1
        ui->showKcalsOne->setText(QString::number(Kcals[0]) + " kcals");
        ui->showProteinsOne->setText(QString::number(Proteins[0]) + " g");
        ui->showFatsOne->setText(QString::number(Fats[0]) + " g");
        ui->showCarbonsOne->setText(QString::number(Carbons[0]) + " g");
        break;
    case 1: //Meal 2
        ui->showKcalsTwo->setText(QString::number(Kcals[1]) + " kcals");
        ui->showProteinsTwo->setText(QString::number(Proteins[1]) + " g");
        ui->showFatsTwo->setText(QString::number(Fats[1]) + " g");
        ui->showCarbonsTwo->setText(QString::number(Carbons[1]) + " g");
        break;
    case 2: //Meal 3
        ui->showKcalsThree->setText(QString::number(Kcals[2]) + " kcals");
        ui->showProteinsThree->setText(QString::number(Proteins[2]) + " g");
        ui->showFatsThree->setText(QString::number(Fats[2]) + " g");
        ui->showCarbonsThree->setText(QString::number(Carbons[2]) + " g");
        break;
    case 3: //Meal 4
        ui->showKcalsFour->setText(QString::number(Kcals[3]) + " kcals");
        ui->showProteinsFour->setText(QString::number(Proteins[3]) + " g");
        ui->showFatsFour->setText(QString::number(Fats[3]) + " g");
        ui->showCarbonsFour->setText(QString::number(Carbons[3]) + " g");
        break;
    case 4: //Meal 5
        ui->showKcalsFive->setText(QString::number(Kcals[4]) + " kcals");
        ui->showProteinsFive->setText(QString::number(Proteins[4]) + " g");
        ui->showFatsFive->setText(QString::number(Fats[4]) + " g");
        ui->showCarbonsFive->setText(QString::number(Carbons[4]) + " g");
        break;
    }

    //Total Results (all meals)
    ui->showTotalKcals->setText(QString::number(Kcals[0] + Kcals[1] + Kcals[2] + Kcals[3] + Kcals[4]) + " kcals");
    ui->showTotalProteins->setText(QString::number(Proteins[0] + Proteins[1] + Proteins[2] + Proteins[3] + Proteins[4]) + " g");
    ui->showTotalFats->setText(QString::number(Fats[0] + Fats[1] + Fats[2] + Fats[3] + Fats[4]) + " g");
    ui->showTotalCarbons->setText(QString::number(Carbons[0] + Carbons[1] + Carbons[2] + Carbons[3] + Carbons[4]) + " g");
}

//Delete Buttons
void MainWindow::on_delItemOne_clicked()
{
    //Error message
    if(Kcals[0]<=0)
    {
      QMessageBox::critical(this,"Błąd!", "Wartość jest już zerowa!", QMessageBox::Ok);
      return;
    }
    else if(!ui->mealOneRight->currentItem())
    {
      QMessageBox::warning(this,"Błąd!", "Zaznacz produkt! do usunięcia!", QMessageBox::Ok);
      return;
    }

    //Delete
    Kcals[0]-=ItemKcals[ItemMap[ui->mealOneRight->currentItem()->text()]];
    Proteins[0]-=ItemProteins[ItemMap[ui->mealOneRight->currentItem()->text()]];
    Fats[0]-=ItemFats[ItemMap[ui->mealOneRight->currentItem()->text()]];
    Carbons[0]-=ItemCarbons[ItemMap[ui->mealOneRight->currentItem()->text()]];

    //Show results
    SelectMeal =0;
    ShowTotalResults(SelectMeal);

    //Removing selected item
    delete ui->mealOneRight->currentItem();
}
void MainWindow::on_delItemTwo_clicked()
{
     //Error message
    if(Kcals[1]<=0)
    {
      QMessageBox::critical(this,"Błąd!", "Wartość jest już zerowa!", QMessageBox::Ok);
      return;
    }
    else if(!ui->mealTwoRight->currentItem())
    {
      QMessageBox::warning(this,"Błąd!", "Zaznacz produkt! do usunięcia!", QMessageBox::Ok);
      return;
    }


    Kcals[1]-=ItemKcals[ItemMap[ui->mealTwoRight->currentItem()->text()]];
    Proteins[1]-=ItemProteins[ItemMap[ui->mealTwoRight->currentItem()->text()]];
    Fats[1]-=ItemFats[ItemMap[ui->mealTwoRight->currentItem()->text()]];
    Carbons[1]-=ItemCarbons[ItemMap[ui->mealTwoRight->currentItem()->text()]];

    //Show results
    SelectMeal =1;
    ShowTotalResults(SelectMeal);

    //Removing selected item
    delete ui->mealTwoRight->currentItem();
}
void MainWindow::on_delItemThree_clicked()
{
     //Error message
    if(Kcals[2]<=0)
    {
      QMessageBox::critical(this,"Błąd!", "Wartość jest już zerowa!", QMessageBox::Ok);
      return;
    }
    else if(!ui->mealThreeRight->currentItem())
    {
      QMessageBox::warning(this,"Błąd!", "Zaznacz produkt! do usunięcia!", QMessageBox::Ok);
      return;
    }


    Kcals[2]-=ItemKcals[ItemMap[ui->mealThreeRight->currentItem()->text()]];
    Proteins[2]-=ItemProteins[ItemMap[ui->mealThreeRight->currentItem()->text()]];
    Fats[2]-=ItemFats[ItemMap[ui->mealThreeRight->currentItem()->text()]];
    Carbons[2]-=ItemCarbons[ItemMap[ui->mealThreeRight->currentItem()->text()]];

    //Show results
    SelectMeal =2;
    ShowTotalResults(SelectMeal);

    //Removing selected item
    delete ui->mealThreeRight->currentItem();
}
void MainWindow::on_delItemFour_clicked()
{
     //Error message
    if(Kcals[3]<=0)
    {
      QMessageBox::critical(this,"Błąd!", "Wartość jest już zerowa!", QMessageBox::Ok);
      return;
    }
    else if(!ui->mealFourRight->currentItem())
    {
      QMessageBox::warning(this,"Błąd!", "Zaznacz produkt! do usunięcia!", QMessageBox::Ok);
      return;
    }


    Kcals[3]-=ItemKcals[ItemMap[ui->mealFourRight->currentItem()->text()]];
    Proteins[3]-=ItemProteins[ItemMap[ui->mealFourRight->currentItem()->text()]];
    Fats[3]-=ItemFats[ItemMap[ui->mealFourRight->currentItem()->text()]];
    Carbons[3]-=ItemCarbons[ItemMap[ui->mealFourRight->currentItem()->text()]];

    //Show results
    SelectMeal =3;
    ShowTotalResults(SelectMeal);

    //Removing selected item
    delete ui->mealFourRight->currentItem();
}
void MainWindow::on_delItemFive_clicked()
{
     //Error message
    if(Kcals[4]<=0)
    {
      QMessageBox::critical(this,"Błąd!", "Wartość jest już zerowa!", QMessageBox::Ok);
      return;
    }
    else if(!ui->mealFiveRight->currentItem())
    {
      QMessageBox::warning(this,"Błąd!", "Zaznacz produkt! do usunięcia!", QMessageBox::Ok);
      return;
    }


    Kcals[4]-=ItemKcals[ItemMap[ui->mealFiveRight->currentItem()->text()]];
    Proteins[4]-=ItemProteins[ItemMap[ui->mealFiveRight->currentItem()->text()]];
    Fats[4]-=ItemFats[ItemMap[ui->mealFiveRight->currentItem()->text()]];
    Carbons[4]-=ItemCarbons[ItemMap[ui->mealFiveRight->currentItem()->text()]];

    //Show results
    SelectMeal =4;
    ShowTotalResults(SelectMeal);

    //Removing selected item
    delete ui->mealFiveRight->currentItem();
}

//Function for category select
void MainWindow::on_addItemCategory_activated(int index)
{
////
}

//Open a dialog to add new item
void MainWindow::on_actionNewItem_triggered()
{
     ui->tabWidget->setCurrentIndex(3);
}

//Back to main tab from adding item
void MainWindow::on_backMainButton_clicked()
{
    ui->tabWidget->setCurrentIndex(1);
}

//Open calorie calculator
void MainWindow::on_actionCalculator_triggered()
{
    ui->tabWidget->setCurrentIndex(0);
}

//Export your diet plan
void MainWindow::on_actionExport_triggered()
{

   QString fileName = QFileDialog::getSaveFileName(
            this,
            tr("Save Document"),
            QDir::currentPath(),
            tr("Text files (*.txt)") );

    QFile exportDiet(fileName);
    if (exportDiet.open(QIODevice::WriteOnly | QIODevice::Text))
    {
        //Print line
        QTextStream out(&exportDiet);

        //Set codec
        out.setCodec("UTF-8");

        out <<"\n"<< ui->showName->text()  << "\n";
        out << "Cel: " << ui->showTarget->text() << "\n";
        out << "Dieta: " << ui->showTotalKcals->text() << "\n\n";

        //First meal
        out << ui->mealOneBox->title() << ":\n\n";

        for (int i = 0; i < ui->mealOneRight->count(); i++)
        {
            QListWidgetItem *item = ui->mealOneRight->item(i);
            out << item->text() <<"\n";
        }

        out <<"\n" << ui->mealTwoBox->title() << ":\n\n";

        for (int i = 0; i < ui->mealTwoRight->count(); i++)
        {
            QListWidgetItem *item = ui->mealTwoRight->item(i);
            out << item->text() <<"\n";
        }

        out <<"\n" << ui->mealThreeBox->title() << ":\n\n";

        for (int i = 0; i < ui->mealThreeRight->count(); i++)
        {
            QListWidgetItem *item = ui->mealThreeRight->item(i);
            out << item->text() <<"\n";
        }

        out <<"\n" << ui->mealFourBox->title() << ":\n\n";

        for (int i = 0; i < ui->mealFourRight->count(); i++)
        {
            QListWidgetItem *item = ui->mealFourRight->item(i);
            out << item->text() <<"\n";
        }

        out <<"\n" << ui->mealFiveBox->title() << ":\n\n";

        for (int i = 0; i < ui->mealFiveRight->count(); i++)
        {
            QListWidgetItem *item = ui->mealFiveRight->item(i);
            out << item->text() <<"\n";
        }

        out <<"\n" << ui->tipsBox->title() << ":\n\n";

        out << ui->tipsTextEdit->toPlainText() << "\n\n";

        exportDiet.close();
    }

     QMessageBox::information(this,"Sukces!", "Pomyślnie eksportowano dietę!", QMessageBox::Ok);

}

//Save products lists function
void MainWindow::on_actionSave_triggered()
{
    //Save items for meal one
    QFile file(":/save/MealOne.txt");
    if (file.open(QIODevice::WriteOnly | QIODevice::Text))
    {
        // bind it
        QTextStream stream(&file);

        for (int i = 0; i < ui->mealOneLeft->count(); i++)
        {
            QListWidgetItem *item = ui->mealOneLeft->item(i);
            stream << item->text() << '\n';
            stream << ItemKcals.at(ItemMap[item->text()]) << "\n";
            stream << ItemProteins.at(ItemMap[item->text()]) << "\n";
            stream << ItemFats.at(ItemMap[item->text()]) << "\n";
            stream << ItemCarbons.at(ItemMap[item->text()]) << "\n";
        }
    }
    //Save items for meal three
    QFile file3(":/save/MealThree.txt");
    if (file3.open(QIODevice::WriteOnly | QIODevice::Text))
    {
        // bind it
        QTextStream stream(&file3);

        for (int i = 0; i < ui->mealThreeLeft->count(); i++)
        {
            QListWidgetItem *item = ui->mealThreeLeft->item(i);
            stream << item->text() << '\n';
            stream << ItemKcals.at(ItemMap[item->text()]) << "\n";
            stream << ItemProteins.at(ItemMap[item->text()]) << "\n";
            stream << ItemFats.at(ItemMap[item->text()]) << "\n";
            stream << ItemCarbons.at(ItemMap[item->text()]) << "\n";
        }
    }

    QFile file5(":/save/MealFive.txt");
    if (file5.open(QIODevice::WriteOnly | QIODevice::Text))
    {
        // bind it
        QTextStream stream(&file5);

        for (int i = 0; i < ui->mealFiveLeft->count(); i++)
        {
            QListWidgetItem *item = ui->mealFiveLeft->item(i);
            stream << item->text() << '\n';
            stream << ItemKcals.at(ItemMap[item->text()]) << "\n";
            stream << ItemProteins.at(ItemMap[item->text()]) << "\n";
            stream << ItemFats.at(ItemMap[item->text()]) << "\n";
            stream << ItemCarbons.at(ItemMap[item->text()]) << "\n";
        }
    }
}

//Load products list function
void MainWindow::on_actionLoad_triggered()
{

    //Clear maps
    ItemKcals.clear();
    ItemProteins.clear();
    ItemFats.clear();
    ItemCarbons.clear();
    ItemMap.clear();

     //Load meal one and two
     QFile file(":/save/MealOne.txt");
     if (file.open(QIODevice::ReadOnly | QIODevice::Text))
     {
         QTextStream in(&file);
         in.setCodec("UTF-8");

         while(!in.atEnd())
         {
             QString line = in.readLine();
             ui->mealOneLeft->addItem(line);
             ui->mealTwoLeft->addItem(line);

             QString line2 = in.readLine();

             QString line3 = in.readLine();

             QString line4 = in.readLine();

             QString line5 = in.readLine();

             ItemMap.insert(line, ItemMap.size());
             ItemKcals.push_back(line2.toDouble());
             ItemProteins.push_back(line3.toDouble());
             ItemFats.push_back(line4.toDouble());
             ItemCarbons.push_back(line5.toDouble());
         }

         file.close();
     }

     //Load meal three and four
     QFile file2(":/save/MealThree.txt");
     if (file2.open(QIODevice::ReadOnly | QIODevice::Text))
     {
         QTextStream in(&file2);
         in.setCodec("UTF-8");

         while(!in.atEnd())
         {
             QString line = in.readLine();
             ui->mealThreeLeft->addItem(line);
             ui->mealFourLeft->addItem(line);

             QString line2 = in.readLine();

             QString line3 = in.readLine();

             QString line4 = in.readLine();

             QString line5 = in.readLine();

             ItemMap.insert(line, ItemMap.size());
             ItemKcals.push_back(line2.toDouble());
             ItemProteins.push_back(line3.toDouble());
             ItemFats.push_back(line4.toDouble());
             ItemCarbons.push_back(line5.toDouble());
         }

         file2.close();
     }

     //Load meal five
     QFile file3(":/save/MealFive.txt");
     if (file3.open(QIODevice::ReadOnly | QIODevice::Text))
     {
         QTextStream in(&file3);
         in.setCodec("UTF-8");

         while(!in.atEnd())
         {
             QString line = in.readLine();
             ui->mealFiveLeft->addItem(line);

             QString line2 = in.readLine();

             QString line3 = in.readLine();

             QString line4 = in.readLine();

             QString line5 = in.readLine();

             ItemMap.insert(line, ItemMap.size());
             ItemKcals.push_back(line2.toDouble());
             ItemProteins.push_back(line3.toDouble());
             ItemFats.push_back(line4.toDouble());
             ItemCarbons.push_back(line5.toDouble());
         }

         file3.close();
     }
}

////Calculator functions
void MainWindow::on_AcceptButton_accepted()
{
    if (ui->addHeight->value()== 0 || ui->addWeight->value()==0 || ui->addAge->value() == 0)
    {
        QMessageBox::warning(this,"Błąd", "Uzupełnij wszystkie dane!",QMessageBox::Ok);
    }
    else if (Gender!=1 && Gender!=2)
    {
        QMessageBox::warning(this,"Błąd", "Podaj płeć!",QMessageBox::Ok);
    }
    else if (ui->activBox->currentIndex()==0)
    {
        QMessageBox::warning(this,"Błąd", "Podaj aktywność fizyczną!",QMessageBox::Ok);
    }
    else
    {
    PersonName = ui->addPersonName->text();
    Height = ui->addHeight->value();
    Weight = ui->addWeight->value();
    Age = ui->addAge->value();

    //BMI
    Bmi = Weight / (Height /100 * Height/100);
    ui->showBmi->setNum(Bmi);

    //PPM
    if (Gender==1)
    {
    Ppm = (66.5 + (13.75 * Weight) + (5.033 * Height) - (6.755 * Age));
    }

    else if (Gender==2)
    {
    Ppm = (665.1 + (9.563 * Weight) + (1.850 * Height) - (4.676 * Age));
    }

    ui->showPpm->setNum(Ppm);

    //CPM
    Cpm = (Ppm * Pal);
    ui->showCpm->setNum(Cpm);

    //Target : slim
    Slim = (Cpm - (0.15 * Cpm));

    //Target :: gain
    Gain = (Cpm + (0.15 * Cpm));
    }

    //Show Name in Main Tab
    ui->showName->setText(PersonName);

    //Show choosed target in main tab
    if(targetString == "PRZYTYĆ")
    {
        ui->showDiet->setText(QString::number(Gain) + " kcals");
        //ui->showKcalsOne->setText(QString::number(Kcals[0]) + " kcals");
    }
    else if (targetString == "SCHUDNĄĆ")
    {
        ui->showDiet->setText(QString::number(Slim) + " kcals");
    }


}

//Return to main tab
void MainWindow::on_slimButton_2_clicked()
{
    ui->tabWidget->setCurrentIndex(1);
    ui->tabWidget->resize(1920,1080);
}

//Gender buttons
void MainWindow::on_maleButton_clicked()
{
    Gender=1;
}
void MainWindow::on_femaleButton_clicked()
{
    Gender=2;
}

//Pal
void MainWindow::on_activBox_activated(int index)
{
    if (index==1)
    {
       Pal = 1.2;
    }
    else if (index==2)
    {
       Pal = 1.25;
    }
    else if (index==3)
    {
       Pal = 1.5;
    }
    else if (index==4)
    {
       Pal = 1.75;
    }
    else if (index==5)
    {
       Pal = 2.0;
    }
}

//Target buttons
void MainWindow::on_slimButton_clicked()
{
   targetString = "SCHUDNĄĆ";
   ui->showTarget->setText("SCHUDNĄĆ");
}
void MainWindow::on_gainButton_clicked()
{
   targetString = "PRZYTYĆ";
   ui->showTarget->setText("PRZYTYĆ");
}

//Info Dialogs Buttons
void MainWindow::on_BmiAsk_clicked()
{
    QMessageBox::information(this,"BMI - Wskaźnik Masy Ciała", "Porównaj swój wynik BMI z poniższą tabelką.\nBMI < 18,5 - niedowaga\n18,5 ≤ BMI ≤ 24,9 - waga prawidłowa\n25 ≤ BMI ≤ 29,9 - nadwaga\nBMI > 30 - otyłość",
                                            QMessageBox::Ok);
}
void MainWindow::on_PpmAsk_clicked()
{
    QMessageBox::information(this,"Co to PPM?", "PPM – jest to najniższy poziom metabolizmu\nwarunkującego życie i nie obejmuje\n aktywności fizycznej.",QMessageBox::Ok);
}
void MainWindow::on_CpmAsk_clicked()
{
    QMessageBox::information(this,"Co to CPM?","CPM – całodobowe wydatki energetyczne\nczłowieka związane z jego normalnym\nfunkcjonowaniem w życiu codziennym,\nzawodowym oraz z uwzględnieniem\naktywności fizycznej.",QMessageBox::Ok);
}
void MainWindow::on_Ask1_clicked()
{
    QMessageBox::warning(this,"Uwaga!","Pamiętaj, że są to przybliżone wyniki! W celu poznania dokładnych wyników skontakuj się ze swoim dietetykiem!", QMessageBox::Ok);
}
void MainWindow::on_Ask2_clicked()
{
    QMessageBox::warning(this,"Uwaga!","Pamiętaj, że są to przybliżone wyniki! W celu poznania dokładnych wyników skontakuj się ze swoim dietetykiem!", QMessageBox::Ok);
}

