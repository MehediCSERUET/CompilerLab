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
            cout<<production[i];
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
        cout<<starting_char<<"->";
        First(starting_char);

        strcpy(temp_production, input[last_pos]);
        temp_len = strlen(temp_production);

        for(j = 0; j < temp_len; j++){
            if(temp_production[j] == '#'){
                cout<<"#";
                break;
            }
        }
        cout<<endl;
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
