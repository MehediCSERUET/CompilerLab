#include "mainwindow.h"
#include "ui_mainwindow.h"
#include<bits/stdc++.h>
#include<QDebug>
#include<string>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
}

MainWindow::~MainWindow()
{
    delete ui;
}

long long int StringToNumber(std::string a){
    long long int length = a.length();
    long long int num = 0, base = 1;
    for(long long int i = length - 1; i >= 0; i--){
        num = num + (a.at(i) - '0') * base;
        base = base * 10;
    }
    return num;

}

void MainWindow::on_pushButton_clicked()
{
    ui->Output->clear();
    QString text = ui->Editor->toPlainText();
    unsigned char* input = new unsigned char[text.length()];

    for(int i = 0; i < text.length(); i++){
        input[i] = static_cast<char>(text.at(i).toLatin1());
    }
    QString output = "";

    int i, n, starting_pos, end_pos, count = 0;
    bool starting_name = false, ending_name = false, semicolon = false, left_bracket = false, right_bracket=false, parameter = false;
    n = text.length();

    for(i = 0; i < n; i++){
        if(((input[i] >= 'a' && input[i] <= 'z') || (input[i] >= 'A' && input[i] <= 'Z')) && starting_name == false){
            starting_pos = i;
            starting_name = true;
        }
        else if(((input[i] >= 'a' && input[i] <= 'z') || (input[i] >= 'A' && input[i] <= 'Z')) && (input[i+1] == '(' || input[i+1] ==' ') && ending_name == false){
                end_pos = i;
                ending_name = true;
                break;
        }
    }

    for(i = 0; i < n; i++){
        if(input[i] == ','){
            count++;
        } else if(input[i] == ';'){
            semicolon = true;
        } else if(input[i]=='('){
            left_bracket = true;
        } else if(input[i]==')'){
            right_bracket = true;
        } else if((input[i] >= 'a' && input[i] <= 'z') || (input[i] >= 'A' && input[i] <= 'Z')){
            parameter = true;
        }
    }
    if(count == 0 && parameter == false){
        for(i = 0; i < n; i++){
                if(input[i-1]== '('){
                    output.append("optparams)\n");
                    output.append("optparams->@");
                    break;
                }
            output.append(input[i]);
        }
    } else if(count > 0 && parameter == true) {
         for(i = 0; i < n; i++){
                if(input[i-1] == '('){
                    output.append("optparams)\n");
                    output.append("optparams -> params\n");
                    break;
                }
            output.append(input[i]);
        }

        output.append("params -> params, param\n");
        while(count--){
                if(count > 0){
                    output.append("params->params, param\n");
                } else {
                    output.append("params -> param\n");
                }
        }

        long long int ans = 0;
        std::string num = "";
        output.append("param->");
        for(i = end_pos + 1; i < n; i++){
            if(input[i] >= '0' && input[i] <= '9'){
                output.append(input[i]);
                num += input[i];
            } else{
                if(num.length() != 0){
                    ans += StringToNumber(num);
                    num = "";
                }
                if(input[i] == ','){
                    output.append("\nparam->");
                }
            }
        }
        output.append("\n");
        output.append(QString::number(ans));
    }
    if(semicolon && left_bracket && right_bracket){
        ui->Output->append(output);
    } else {
        if(semicolon==false)
            ui->Output->append("Missing Semicolon");
        if(left_bracket == false){
            ui->Output->append("Missing left bracket");
        }
        if(right_bracket == false){
            ui->Output->append("Missing right bracket");
        }
        if(parameter == true && count == 0){
            ui->Output->append("Missing comma");
        }
    }
}
