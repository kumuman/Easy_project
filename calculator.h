#pragma once

#include <QtWidgets/QMainWindow>
#include "ui_calculator.h"
#include <vector>

class Calculator : public QMainWindow
{
    Q_OBJECT

public:
    Calculator(QWidget* parent = nullptr);
    ~Calculator();

public slots:
    void onButtonClicked();

private:
    Ui::CalculatorClass ui;

    // Declare buttons in a more organized way
    QPushButton* pushButtonRemain;
    QPushButton* pushButtonClear;
    QPushButton* pushButtonDel;
    QPushButton* pushButtonAdd;
    QPushButton* pushButton7;
    QPushButton* pushButton8;
    QPushButton* pushButton9;
    QPushButton* pushButtonSub;
    QPushButton* pushButton4;
    QPushButton* pushButton5;
    QPushButton* pushButton6;
    QPushButton* pushButtonMul;
    QPushButton* pushButton1;
    QPushButton* pushButton2;
    QPushButton* pushButton3;
    QPushButton* pushButtonDiv;
    QPushButton* pushButtonPow;
    QPushButton* pushButton0;
    QPushButton* pushButtonPoint;
    QPushButton* pushButtonEqual;

    // Use a more descriptive name for the vectors
    std::vector<double> operandVector1 = { 0 };
    std::vector<double> operandVector2 = { 0 };
    std::vector<QString> operators;
    std::vector<QString> operands;

    bool isInputtingNumber; // Use a more descriptive name
    int decimalCount;

    // Refactored method for showing a message box
    void initializeButtons();
    void connectButtons();
    void showMessageBox();

};
