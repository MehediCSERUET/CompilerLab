#include<stdio.h>
#include<bits/stdc++.h>
using namespace std;

long long int StringToNumber(string a){
    long long int length = a.length();
    long long int num = 0, base = 1;
    for(long long int i = length - 1; i >= 0; i--){
        num = num + (a.at(i) - '0') * base;
        base = base * 10;
    }
    return num;

}

int main(){
    char input[1000], function_name[1000];
    int i, n, j=0, starting_pos, end_pos, count = 0, temp_count = 0, param_ending[100];
    bool starting_name = false, ending_name = false;
    printf("Enter a function definition: ");
    gets(input);
    n = strlen(input);
    //printf("%d\n", n);

    for(i = 0; i < n; i++){
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
        for(i = 0; i < n; i++){
                if(input[i-1] == '('){
                    cout<<"optparams)\n";
                    cout<<"optparams->@";
                    break;
                }
            printf("%c", input[i]);
        }
    } else {
         for(i = 0; i < n; i++){
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
        long long int ans = 0;
        string num = "";
        cout<<"param->";
        for(i = end_pos + 1; i < n; i++){
            if(input[i] >= '0' && input[i] <= '9'){
                printf("%c", input[i]);
                num += input[i];
            } else{
                if(num.length() != 0){
                    ans += StringToNumber(num);
                    num = "";
                }
                if(input[i] == ','){
                    cout<<"\nparam->";
                }
            }
        }

        printf("\n%lld", ans);
    }

    return 0;
}
