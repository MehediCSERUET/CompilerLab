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
    //This function takes in a string (which is a number) and returns that number
    long long int length = a.length();
    long long int num = 0, base = 1;
    for(long long int i = length - 1; i >= 0; i--){
        num = num + (a.at(i) - '0') * base;
        base = base * 10;
    }
    return num;

}

double StringToDouble(char input[])
{
    //This unction takes in a string and returns the double number of that string
    char *p;
    return strtod(input, &p); //strtod -> string to double function takes string and a pointer and returns the double value
}


void MainWindow::on_pushButton_clicked()
{
    ui->Output->clear(); //clear the screen
    QString text = ui->Editor->toPlainText();  //get the input from editor
    unsigned char* input = new unsigned char[text.length()]; //create an unsigned char same size of the input string

    for(int i = 0; i < text.length(); i++){
        input[i] = static_cast<char>(text.at(i).toLatin1());  //copy the string into the unsigned char
    }
    QString output = "";  //output string initally nothing

    int i, n, starting_pos, end_pos, count = 0, pos, j=0, k=0;
    bool semicolon = false, left_bracket = false, arg_float = false, right_bracket=false, parameter = false, starting_name = false, ending_name = false, error = false;
    char return_type[100], function_name[1000], single[50];
    double nums[100];

    n = text.length();  //size of the input

    //scanning return type
    for(i = 0, j=0; i < n; i++){
        if(input[i] != ' '){
            return_type[j++] = input[i];
        } else {
            pos = i+1;
            return_type[j] = '\0';
            break;
        }
    }
    j=0;

    //extracting function name
    for(i = pos; i < n; i++){
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
//collecting function name
    for(i = starting_pos; i <= end_pos; i++){
        function_name[j++] = input[i];
    }
    function_name[j] = '\0';

//collecting info for error detection
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
        } else if(input[i] == '.'){
            arg_float = true;
        }
    }
    if(count == 0 && parameter == false){ //for no parameter function  call
        for(i = starting_pos; i < n; i++){
                if(input[i-1]== '('){
                    output.append("optparams)\n");
                    output.append("optparams->@");
                    break;
                }
            output.append(input[i]);
        }
    } else if(count > 0 && parameter == true) { //if params exist
         for(i = starting_pos; i < n; i++){
                if(input[i-1] == '('){
                    output.append("optparams)\n");
                    output.append("optparams -> params\n");
                    break;
                }
            output.append(input[i]);
        }

         //print this till the no of params required
        output.append("params -> params, param\n");
        while(count--){
                if(count > 0){
                    output.append("params->params, param\n");
                } else {
                    output.append("params -> param\n");
                }
        }
//if return type is integer
        if(strcmp(return_type, "int") == 0){
            if(arg_float == true){ //but argument supplied contains floating point
                 ui->Output->append("Type Mismatch!");
                 error = true;
            } else { //if arguments are int too
            long long int ans = 0;
            std::string num = "";
            output.append("param->");
            for(i = end_pos + 1; i < n; i++){
                if(input[i] >= '0' && input[i] <= '9'){
                    output.append(input[i]);  //now showing the actual argument supplied by the user
                    num += input[i]; //getting the full arguments in case of multi digit arg
                } else{ //after the argument being found fully
                    if(num.length() != 0){ //if the argument is not empty
                        ans += StringToNumber(num); //add this argument into ans variablke, if i subtract, agrument will subtract from the first one
                        num = ""; //setting the string empty to get the next argument
                    }
                    if(input[i] == ','){
                        output.append("\nparam->"); //if a comma is found print this
                    }
                }
            }

            output.append("\n");
            output.append(QString::number(ans)); //append the ans at last
            }
        } else if(strcmp(return_type, "double") == 0 || strcmp(return_type, "float") == 0){ //if the returen type is double or float
            double ans = 0;
            for(i = end_pos + 1, j = 0; i < n; i++){
                if(input[i] == ',' || input[i] == ')'){ //when input is finished
                    single[k] = '\0'; //close the input
                    nums[j++] = StringToDouble(single); //convert it into double value
                    k = 0; //start from fresh to scan next arg
                } else if(input[i] >= '0' && input[i] <= '9' || input[i] == '.'){ //if arg scanning is not finished
                    single[k++] = input[i];
                }
            }
//add all the arguments that has been found and show this into production
            for(i = 0; i < j; i++){
                output.append("\nparam->");
                output.append(QString::number(nums[i]));
                ans += nums[i];
            }
            output.append("\n");
            output.append(QString::number(ans));  //add the ans at the end of the productions

        } else { //if the return type  if not int or fload/double
            ui->Output->append("Invalid Return Type for add function");
            error = true;
        }

    }
    if(semicolon && left_bracket && right_bracket && !error){
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
