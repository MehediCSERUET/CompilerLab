#include<stdio.h>
#include<bits/stdc++.h>
using namespace std;

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

        cout<<"param->";
        for(i = end_pos + 1; i < n; i++){
            if(isalpha(input[i])){
                printf("%c", input[i]);
            } else if(input[i] == ','){
                cout<<"\nparam->";
            }
        }
    }
    return 0;
}
