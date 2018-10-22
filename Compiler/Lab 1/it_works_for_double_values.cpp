#include<stdio.h>
#include<bits/stdc++.h>
using namespace std;

double StringToDouble(char input[])
{
    char *p;
    return strtod(input, &p);
}

int main(){
    char return_type[100], input[1000], function_name[1000], single[50];
    int pos, ending_pos, i, n, j=0, k=0, starting_pos, end_pos, count = 0, temp_count = 0, param_ending[100];
    bool starting_name = false, ending_name = false, dot_found = false;
    double nums[100], ans = 0;

    printf("Enter a function definition: ");
    gets(input);
    n = strlen(input);

    //scanning return type
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

    cout<<return_type<<endl;

    //extracting function name
    for(i = pos; i < n; i++){
        if(isalpha(input[i]) && starting_name == false){
            starting_pos = i;
            starting_name = true;
        }
        else if(isalpha(input[i]) && input[i+1] == '(' || input[i+1] == ' ' && ending_name == false){
                ending_pos = i;
                ending_name = true;
                break;
        }
    }

    for(i = starting_pos; i <= ending_pos; i++){
        function_name[j++] = input[i];
    }
    function_name[j] = '\0';
    cout<<function_name<<endl;

    //getting total argument number
    for(i = ending_pos; i < n; i++){
        if(input[i] == ','){
            count++;
        }

    }

    temp_count = count;
    if(count == 0){
        for(i = starting_pos; i < n; i++){
                if(input[i-1] == '('){
                    cout<<"optparams)\n";
                    cout<<"optparams->@";
                    break;
                }
            printf("%c", input[i]);
        }
    } else {
         for(i = starting_pos; i < n; i++){
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


        for(i = ending_pos + 1, j = 0; i < n; i++){
            if(input[i] == ',' || input[i] == ')'){
                single[k] = '\0';
                nums[j++] = StringToDouble(single);
                k = 0;
            } else if(input[i] >= '0' && input[i] <= '9' || input[i] == '.'){
                single[k++] = input[i];
            }
        }

        for(i = 0; i < j; i++){
            cout<<"param->"<<nums[i]<<endl;
            ans += nums[i];
        }
        cout<<ans<<endl;
    }

    return 0;
}
