#include<bits/stdc++.h>
#define MAX 6
using namespace std;

char input[26][10];
int starting_input[MAX];
bool found = true;
int no_of_epsilon = 0, last_pos = -1;

void First(char s)
{
    int pos = s-'A';
    last_pos = pos;
    char production[10];
    strcpy(production, input[pos]);
    int length = strlen(production);

    for(int i = 0; i < length; i++){
        if(production[i] >= 'A' && production[i] <= 'Z'){
            if(found){ //epsilon is found, proceed
                First(production[i]);
            }
        } else if(production[i] >= 'a' && production[i] <= 'z'){
            cout<<production[i]<<",";
            found = false;
        } else if(production[i] == '|'){
            continue;
        } else if(production[i] == '#'){
            found = true;
            if(i+1 == length){ //if the production ends
                no_of_epsilon++;
            }
            else{
                First(i+1);
            }
        }
    }

}

int getPos(char s){
    for(int i = 0; i < MAX; i++){
        if(starting_input[i] == s-'A'){
            return i;
        }
    }
}

bool isPresent(char arr[], char s){
    int len = strlen(arr);
    for(int i = 0; i < len; i++){
        if(arr[i] == s)
            return true;
    }
    return false;
}

void Follow(char s)
{
    int pos = getPos(s);
    char production[10], temp_prod[10];
    if(pos == 0 || s=='E'){
        cout<<"$";
    }
    for(int i = 0; i < MAX; i++){
        if(isPresent(input[starting_input[i]], s) == true){
            strcpy(production, input[starting_input[i]]);
            int len = strlen(production);
            int current_pos;
            for(int j = 0; j < len; j++){
                if(s == production[j]){
                    current_pos = j;
                    break;
                }
            }
            bool epsilon_found;
            for(int j = current_pos; j < len; j++){
                epsilon_found = false;
                strcpy(temp_prod, input[getPos(production[j])]);
                int temp_len = strlen(temp_prod);
                for(int k = 0; k < temp_len; k++){
                    if(temp_prod[k] >= 'a' && temp_prod[k] <= 'z'){
                        cout<<temp_prod[k]<<",";
                    } else if(temp_prod[k] == '|'){
                        continue;
                    } else if(temp_prod[k] == '#'){
                        epsilon_found = true;
                    }
                }
                if(epsilon_found==false){
                    break;
                }
                else if(production[j]=='D') {
                    Follow('S');
                }
            }
        }
    }


}

int main()
{
    char temp;
    int pos = 0, i, j;
    cout<<"Enter 0 to break\n\n";
    while(1){
        cout<<"Enter starting symbol: ";
        cin>>temp;
        if(temp-'0' == 0){
            break;
        }
        starting_input[pos] = temp-'A';
        cout<<"Enter the production: ";
        cin>>input[starting_input[pos]];
        pos++;
    }
    cout<<endl<<endl;

    char starting_char, temp_production[10];
    int temp_len;
    for(i = 0; i < MAX; i++){
        no_of_epsilon = 0; last_pos = -1;
        starting_char = char(starting_input[i] + 'A');
        cout<<"First of ("<<starting_char<<")->{";
        First(starting_char);

        strcpy(temp_production, input[last_pos]);
        temp_len = strlen(temp_production);

        for(j = 0; j < temp_len; j++){
            if(temp_production[j] == '#'){
                cout<<"#";
                break;
            }
        }
        cout<<"}"<<endl;
    }
cout<<endl;


    for(i = 0; i < MAX; i++){
        starting_char = char(starting_input[i] + 'A');
        cout<<"Follow of ("<<starting_char<<")->{";
        Follow(starting_char);

        cout<<"}"<<endl;
    }
cout<<endl;

    return 0;
}

/*
S
ABCDE
A
a|#
B
b|#
C
c
D
d|#
E
e|#
0
*/
