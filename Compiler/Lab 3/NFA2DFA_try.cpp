#include<bits/stdc++.h>
#define MAX 10
using namespace std;

struct Edges{
    int total;
    int ending_state[MAX]; //starting node will be the index of the edges
    char input_symbol[MAX];
}e[MAX];

void eclosure(int j){
    cout<<j<<endl;
    int total = e[j].total;
    //epsilon closure of starting node
    for(int i = 0; i <= total; i++){
        if(e[j].input_symbol[i] == 'e'){
            cout<<e[j].ending_state[i];
            eclosure(e[j].ending_state[i]);
        }
    }
}


int main()
{
    int no_of_states, no_of_input_symbol, i, j, starting_node, ending_node, previous;
    cout<<"No of states: ";
    cin>>no_of_states; //states are assumed to be starting from 0 to no_of_states - 1, 0 be the starting node


    cout<<"No of input symbol: ";
    cin>>no_of_input_symbol;

    char input_symbol[no_of_input_symbol], input_symbol_temp;

    cout<<"Enter the input symbols"<<endl;
    for(i = 0; i < no_of_input_symbol; i++){
        cin>>input_symbol[i];
    }

    ///FORMAT OF EDGE
    /// STARTING_NODE ENDING_NODE INPUT_SYMBOL
    cout<<"Enter the transitions"<<endl;
    i = 0;
    previous = 0;
    while(1){
        scanf("%d %d %c", &starting_node, &ending_node, &input_symbol_temp);
        if(starting_node == -1){
            break; //last line will be -1 to indicate break;
        }
        if(starting_node == i) {
            e[starting_node].ending_state[previous] = ending_node; //set the destination node for more than one entry
            e[starting_node].input_symbol[previous] = input_symbol_temp; //setting the label;
            previous++;
            e[starting_node].total = previous;        //total no of edge under same starting node

        } else {
            //new starting node
            i = starting_node; //pointing the currently read tarting node
            previous = 0; //starting from zero fro new entry
            e[starting_node].ending_state[previous] = ending_node; //set the destination node
            e[starting_node].input_symbol[previous] = input_symbol_temp; //setting the label;
            previous++;
        }
    }


    int max_node_of_edge = i;
    for(i = 0; i <= max_node_of_edge; i++){
        for(j = 0; j < e[i].total; j++){
            cout<<"Starting State: "<<i<<" Ending State: "<<e[i].ending_state[j]<<" Input Symbol: "<<e[i].input_symbol[j]<<endl;
        }
    }
    cout<<"Eclosure"<<endl;
    eclosure(0);


    return 0;
}
/*
4
2
a b
0 0 a
0 0 b
0 1 a
1 1 a
1 1 b
1 2 a
2 2 a
2 2 b
2 3 b
2 0 e
-1 -1 x
*/
/*
11
2
a b
0 1 e
0 7 e
1 2 e
1 4 e
2 3 a
3 6 e
4 5 b
5 6 e
6 1 e
6 7 e
7 8 a
8 9 b
9 10 b
-1 -1 z
*/



/*
cout<<"MOVE i a"<<endl;
    for(i=0; i< MAX;i++){
        if(epsilon_closure[i]==true){
            Move(i, 'a');
        }
    }
    cout<<"Move i b"<<endl;
    for(i=0; i< MAX;i++){
        if(epsilon_closure[i]==true){
            Move(i, 'b');
        }
    }

        Move(0, 'a');
    Move(1, 'a');
    Move(2, 'a');
    Move(4, 'a');
    Move(7, 'a');

    Move(0, 'b');
    Move(1, 'b');
    Move(2, 'b');
    Move(4, 'b');
    Move(7, 'b');
    */
