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
//finding if opening and closing bracket is given or not
    bool starting_bracket = false, ending_bracket = false;
    for(i = 0; i < n; i++){
        if(input[i] == '('){
            starting_bracket = true;
        } else if(input[i] == ')'){
            ending_bracket = true;
            break;
        }
    }
    if(starting_bracket && ending_bracket){
        cout<<"Bracket Correct\n";
    } else {
        if(ending_bracket == false){
            cout<<"You didn't put closing bracket\n";
        }
        if(starting_bracket == false){
            cout<<"You didn't put opening bracket\n";
        }
        exit(0);
    }


//finding the starting and ending position of the function name
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

    //finding if any missing comma
    for(i = end_pos+1 ; i < n; i++){
        if(input[i] >= '0' && input[i] <= '9' && input[i+1] == ','){

        }

    }

//finding how many parameters are given using the number of comma
    for(i = end_pos; i < n; i++){
        if(input[i] == ','){
            count++;
        }
    }
    //printing in the case of no parameters are given
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
    } else { //if more than 0 parameter(s) are given
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
                if(count > 0){ //if it is not the last parameter
                    cout<<"params->params, param\n";
                } else { //if n=only one parameter is left
                    cout<<"params -> param\n";
                }
        }
//replacing the param with actual arguments
        cout<<"param->";
        for(i = end_pos + 1; i < n; i++){ //ending_pos+1 is bracket opening
            if(isalpha(input[i])){
                printf("%c", input[i]);
            } else if(input[i] == ','){
                cout<<"\nparam->";
            }
        }


    }
    return 0;
}
