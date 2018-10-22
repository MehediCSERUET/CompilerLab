#include<stdio.h>
#include<bits/stdc++.h>
#include<string>
using namespace std;


vector<double> extract_num(string const& input_str)
{
    vector<double> doubles;
    istringstream input(input_str);
    string number;
    while(getline(input, number, ',')){
        istringstream iss(number);
        double i;
        iss >> i;
        doubles.push_back(i);
    }
    return doubles;
}

double StringToNumber(char a[], char return_type[]){
    cout<<"Input: "<<a<<endl;
    long long int length = strlen(a);
    long long int  i, j, dot_pos = -1;
    double number=0;
    long long int num = 0, base = 1;
    bool dot_found = false;

    for(i = 0; i < length; i++){
            if(a[i] == '.'){
                dot_pos = i;
                dot_found = true;
                break;
            }
    }

    if(dot_found == false){
        for(i = length - 1; i >= 0; i--){
            number = number + (a[i] - '0') * base;
            base = base * 10;
        }
        cout<<"Number "<<number;
        return number;
    } else if(strcmp(return_type, "void")==0){
        cout<<"With void return type, nothing will be returned. "<<endl;
    } else if(strcmp(return_type, "double")==0 || strcmp(return_type, "float")==0){

    char *end;
//        for(i = 0; i < length; i++){
//            if(a.at(i) == '.'){
//                dot_pos = i;
//                break;
//            }
//        }
//        for(i = dot_pos - 1; i >= 0; i--){
//            number = number + (a.at(i) - '0') * base;
//            base = base * 10;
//        }
//        base = 1;
//        for(i = dot_pos + 1; i < length; i++){
//            number = number + ((a.at(i) - '0') / base);
//            base = base * 10;
//        }
number = strtod(a, &end);
cout<<"Number "<<number;
        return number;
    }
}

int main(){
    char input[1000], function_name[1000], return_type[100];
    int i, n, j=0, starting_pos, end_pos, count = 0, pos, temp_count = 0, param_ending[100];
    bool starting_name = false, ending_name = false;
    printf("Enter a function definition: ");
    gets(input);
    n = strlen(input);
    //printf("%d\n", n);

    for(i = 0; i < n; i++){
        if(input[i] != ' '){
            return_type[j++] = input[i];
        } else {
            pos = i+1;
            return_type[j] = '\0';
            break;
        }
    }
    j=0;

    cout<<return_type;
    cout<<endl;


    for(i = pos; i < n; i++){
        if(isalpha(input[i]) && starting_name == false){
            starting_pos = i;
            starting_name = true;
        }
        else if(isalpha(input[i]) && input[i+1] == '(' && ending_name == false){
                end_pos = i;
                ending_name = true;
                break;
        }
    }

    for(i = end_pos; i < n; i++){
        if(input[i] == ','){
            count++;
        }
        if(isalpha(input[i]) && input[i+1] == ','){
            param_ending[j++] = i;
        }
    }
    temp_count = count;
    if(count == 0){
        for(i = pos; i < n; i++){
                if(input[i-1] == '('){
                    cout<<"optparams)\n";
                    cout<<"optparams->@";
                    break;
                }
            printf("%c", input[i]);
        }
    } else {
         for(i = pos; i < n; i++){
                if(input[i-1] == '('){
                    cout<<"optparams)\n";
                    cout<<"optparams -> params\n";
                    break;
                }
            printf("%c", input[i]);
        }

        cout<<"params -> params, param\n";
        while(count--){
                if(count > 0){
                    cout<<"params->params, param\n";
                } else {
                    cout<<"params -> param\n";
                }
        }
        double ans = 0;
        char num[2000];
        int k = 0;
        cout<<"param->";
        for(i = end_pos + 1; i < n; i++){
            if(input[i] != ')'){
                printf("%c", input[i]);
                num[k++] += input[i];
            } else{
                if(strlen(num) != 0){

                        typedef vector<double> nums;
                        nums const& doubles = extract_num(num);
                        for(nums::const_iterator i = doubles.begin(), i_end = doubles.end(); i != i_end; ++i){
                            cout<<*i<<endl;
                        }

                        if(strcmp(return_type, "double") == 0 || strcmp(return_type, "float")){
                            ans += StringToNumber(num, return_type);
                        }
                        k = 0;
                }
                if(input[i] == ','){
                    cout<<"\nparam->";
                }
            }
        }

        printf("\n%g", ans);
    }

    return 0;
}
