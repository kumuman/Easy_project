
#include "calculator.h"
#include <cmath>
#include <QtWidgets>
Calculator::Calculator(QWidget* parent)
    : QMainWindow(parent)
{
    ui.setupUi(this);
    initializeButtons();
    connectButtons();
   
}

Calculator::~Calculator()
{}
void Calculator::initializeButtons() {
    pushButton0 = ui.pushButton_0;
    pushButton1 = ui.pushButton_1;
    pushButton2 = ui.pushButton_2;
    pushButton3 = ui.pushButton_3;
    pushButton4 = ui.pushButton_4;
    pushButton5 = ui.pushButton_5;
    pushButton6 = ui.pushButton_6;
    pushButton7 = ui.pushButton_7;
    pushButton8 = ui.pushButton_8;
    pushButton9 = ui.pushButton_9;
    pushButtonAdd = ui.pushButton_add;
    pushButtonClear = ui.pushButton_clear;
    pushButtonDel = ui.pushButton_del;
    pushButtonDiv = ui.pushButton_div;
    pushButtonEqual = ui.pushButton_equal;
    pushButtonMul = ui.pushButton_mul;
    pushButtonPoint = ui.pushButton_point;
    pushButtonPow = ui.pushButton_pow;
    pushButtonRemain = ui.pushButton_remain;
    pushButtonSub = ui.pushButton_sub;
}
void Calculator::connectButtons() {
    // 连接按钮的点击事件到槽函数
    bool connected = connect(pushButton0, SIGNAL(clicked()), this, SLOT(onButtonClicked()));
    connect(pushButton1, SIGNAL(clicked()), this, SLOT(onButtonClicked()));
    connect(pushButton2, SIGNAL(clicked()), this, SLOT(onButtonClicked()));
    connect(pushButton3, SIGNAL(clicked()), this, SLOT(onButtonClicked()));
    connect(pushButton4, SIGNAL(clicked()), this, SLOT(onButtonClicked()));
    connect(pushButton5, SIGNAL(clicked()), this, SLOT(onButtonClicked()));
    connect(pushButton6, SIGNAL(clicked()), this, SLOT(onButtonClicked()));
    connect(pushButton7, SIGNAL(clicked()), this, SLOT(onButtonClicked()));
    connect(pushButton8, SIGNAL(clicked()), this, SLOT(onButtonClicked()));
    connect(pushButton9, SIGNAL(clicked()), this, SLOT(onButtonClicked()));
    connect(pushButtonAdd, SIGNAL(clicked()), this, SLOT(onButtonClicked()));
    connect(pushButtonClear, SIGNAL(clicked()), this, SLOT(onButtonClicked()));
    connect(pushButtonDel, SIGNAL(clicked()), this, SLOT(onButtonClicked()));
    connect(pushButtonDiv, SIGNAL(clicked()), this, SLOT(onButtonClicked()));
    connect(pushButtonEqual, SIGNAL(clicked()), this, SLOT(onButtonClicked()));
    connect(pushButtonMul, SIGNAL(clicked()), this, SLOT(onButtonClicked()));
    connect(pushButtonPoint, SIGNAL(clicked()), this, SLOT(onButtonClicked()));
    connect(pushButtonPow, SIGNAL(clicked()), this, SLOT(onButtonClicked()));
    connect(pushButtonRemain, SIGNAL(clicked()), this, SLOT(onButtonClicked()));
    connect(pushButtonSub, SIGNAL(clicked()), this, SLOT(onButtonClicked()));
    qDebug() << "Connection status:" << connected;
}
void Calculator::onButtonClicked() {
    QPushButton* clickedButton = qobject_cast<QPushButton*>(sender());
    QString buttonText = clickedButton->text();

    
    if (buttonText.at(0).isDigit()) {
        int number = buttonText.toInt();
        isInputtingNumber = true;
        if (isInputtingVector1) {
            if (operandVector1.size() < operators.size() || operandVector1.size()==0) {
                operandVector1.push_back(number);
            }
            else {
                if (!operands.empty() && operands.back() == '.') {
                    operandVector1.at(operators.size()) += number / pow(10, decimalCount);
                    decimalCount++;
                }
                else if(!operands.empty() && operands.back() == "pow") {
                    operandVector1.at(operators.size()) = pow(operandVector1.at(operators.size()), number);
                }
                else {
                    operandVector1.at(operators.size()) = operandVector1.at(operators.size()) * 10 + number;
                }
            }
            ui.lcdNumber->display(operandVector1.at(operandVector1.size()-1));
        }
        else {
            if (operandVector2.size() < operators.size()) {
                operandVector2.push_back(number);
            }
            else {
                if (!operands.empty() && operands.back() == '.') {
                    operandVector2.at(operators.size() - 1) += number / pow(10, decimalCount);
                    decimalCount++;
                }
                else {
                    operandVector2.at(operators.size() - 1) = operandVector2.at(operators.size() - 1) * 10 + number;
                }
            }
            ui.lcdNumber->display(operandVector2.at(operators.size() - 1));
        }
        qDebug() << "Digit: " << buttonText.toInt() << endl;
    }
    else {
        
        if (buttonText == '.' || buttonText == "pow") {
            isInputtingNumber = false;
            operands.push_back(buttonText);
        }
        if (buttonText == '+' | buttonText == '-' | buttonText == '*' |
            buttonText == '/' | buttonText == '%' ) {
            isInputtingVector1 = !isInputtingVector1;
            isInputtingNumber = false;
            operators.push_back(buttonText);
            operands.clear();
            decimalCount = 1;
        }
        else if (buttonText == '=') {
            this->Mul_Div_Ops();
            this->Add_Sub_Ops();
            decimalCount = 1;
            operators.clear();
            operands.clear();
            operandVector2.clear();
            ui.lcdNumber->display(operandVector1.at(0));
        }
        else if (buttonText == "del") {
            this->DeleteLastStep();
        }
        else if (buttonText == 'C') {
            this->ClearAll();
        }

        qDebug() << "Operator: " << buttonText << endl;
    }
    //...
}
void Calculator::ClearAll() {
    decimalCount = 1;
    isInputtingVector1 = true;
    operandVector1.clear();
    operandVector2.clear();
    operators.clear();
    operands.clear();
    ui.lcdNumber->display(0);
}
void Calculator::DeleteLastStep() {
    if (isInputtingNumber) {
        if (operators.empty()) {
            if (!operands.empty()) {
                operandVector1.at(0) = (static_cast<int>(operandVector1.at(0) * 10)) / 10;
            }
            else {
                operandVector1.at(0) = (operandVector1.at(0) - (static_cast<int>(operandVector1.at(0)) % 10)) / 10;
            }
            ui.lcdNumber->display(operandVector1.at(0));
        }
        else {
            if (!operands.empty()) {
                operandVector2.at(0) = (static_cast<int>(operandVector2.at(0) * 10)) / 10;
            }
            else {
                operandVector2.at(0) = (operandVector2.at(0) - (static_cast<int>(operandVector2.at(0)) % 10)) / 10;
            }
            ui.lcdNumber->display(operandVector2.at(0));
        }

    }
    else {
        if (operands.empty())
        {
            operators.pop_back();
        }
        else {
            operands.pop_back();
        }
    }
}
void Calculator::Mul_Div_Ops() {
    for (int i = operators.size()-1; i >=0; i--) {
        if (operators[i] == '*') {
            if (i % 2 == 0) {
                operandVector1.at(i/2) *= operandVector2.at(i/2);
            }
            else {
                operandVector2.at(i/2) *= operandVector1.at(i-i/2);
            }
        }
        else if (operators[i] == '/') {
            if (operandVector2.at(i/2) == 0 || operandVector1.at(i-i/2)==0) {
                this->showMessageBox();
                this->ClearAll();
            }
            else {
                if (i % 2 == 0) {
                    operandVector1.at(i / 2) /= operandVector2.at(i / 2);
                }
                else {
                    operandVector2.at(i / 2) /= operandVector1.at(i - i / 2);
                }
            }

        }
        else if (operators[i] == '%') {
            if (i % 2 == 0) {
                if (operandVector1.at(i / 2) == static_cast<int>(operandVector1.at(i / 2)) &&
                    operandVector2.at(i / 2) == static_cast<int>(operandVector2.at(i / 2))) {
                    operandVector1.at(i / 2) = static_cast<int>(operandVector1.at(i / 2)) % static_cast<int>(operandVector2.at(i / 2));
                }
                else {
                    this->showMessageBox();
                }
            }
            else {
                if (operandVector1.at(i / 2) == static_cast<int>(operandVector1.at(i / 2)) &&
                    operandVector2.at(i / 2) == static_cast<int>(operandVector2.at(i / 2))) {
                    operandVector2.at(i / 2) = static_cast<int>(operandVector2.at(i / 2)) % static_cast<int>(operandVector1.at(i - i / 2));
                }
                else {
                    this->showMessageBox();
                }
            }
        }
    }
}
void Calculator::Add_Sub_Ops() {
    for (int i = 0; i < operators.size(); i++) {
        if (operators[i] == '+') {
            if (i % 2 == 0) {
                operandVector1.at(0) += operandVector2.at(i/2);
            }
            else {
                operandVector1.at(0) += operandVector1.at(i - i / 2);
            }

        }
        else if (operators[i] == '-') {
            if (i % 2 == 0) {
                operandVector1.at(0) -= operandVector2.at(i / 2);
            }
            else {
                operandVector1.at(0) -= operandVector1.at(i - i / 2);
            }

        }
    }
}
void Calculator::showMessageBox() {
    // 创建信息框
    QMessageBox messageBox;

    // 设置标题
    messageBox.setWindowTitle("Information");

    // 设置文本内容
    messageBox.setText("InVaild Operators.");

    // 设置图标（可选）
    messageBox.setIcon(QMessageBox::Information);

    // 添加按钮（可选）
    messageBox.addButton(QMessageBox::Ok);

    // 执行信息框，阻塞程序直到用户关闭
    messageBox.exec();
}