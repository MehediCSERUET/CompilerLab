#include<bits/stdc++.h>
using namespace std;


double StringToDouble(char input[])
{
    char *p;
    return strtod(input, &p);
}

int main()
{
    char input[1000], single[1000],  function_name[1000], return_type[100];
    int i, j = 0, k = 0, n, pos, starting_pos, ending_pos;
    double nums[10];
    bool starting_name = false, ending_name = false;

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

    for(i = ending_pos + 1, j = 0; i < n; i++){
        if(input[i] == ',' || input[i] == ')'){
            nums[j++] = StringToDouble(single);
            k = 0;
        } else if(input[i] >= '0' && input[i] <= '9' || input[i] == '.'){
            single[k++] = input[i];
        }
    }

    double ans = 0;
    for(i = 0; i < j; i++){
        ans += nums[i];
    }
    cout<<ans;

    return 0;
}
