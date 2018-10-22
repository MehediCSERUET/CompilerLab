#include<bits/stdc++.h>
#define MAX 10
using namespace std;

struct Edges{
    int total; //total no of out edges from a node
    int ending_state[MAX]; //starting node will be the index of the edges
    char input_symbol[MAX]; //label of each node
}e[MAX];

bool epsilon_closure[MAX+1], result_move[MAX+1], temp[MAX+1];

void eclosure(int j){
    epsilon_closure[j] = true;
    cout<<j<<endl;
    int total = e[j].total;
    //epsilon closure of starting node
    for(int i = 0; i <= total; i++){
        if(e[j].input_symbol[i] == 'e'){
            eclosure(e[j].ending_state[i]);
        }
    }
}

void Move(int j, char a){
    int total = e[j].total;
    //epsilon closure of starting node
    for(int i = 0; i <= total; i++){
        if(e[j].input_symbol[i] == a){
//            cout<<e[j].ending_state[i]<<" ";
            result_move[e[j].ending_state[i]]=true;
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
    int counter = 0;
    while(1){
        scanf("%d %d %c", &starting_node, &ending_node, &input_symbol_temp);//get the transition
        if(starting_node == -1){ //if it issignaling last transition
            e[previous].total = counter; //put the total count of last node's out edge
            break; //last line will be -1 to indicate break;
        }
        if(previous!=starting_node){ //if a new starting symbol as been occurred
            e[previous].total = counter; //set the total out edge of the previous node
            counter = 0; //reset counter for current node
        }
        e[starting_node].ending_state[counter]=ending_node; //set a new out edge
        e[starting_node].input_symbol[counter]=input_symbol_temp; //and its label
        counter++; //no of out edge increases
        previous = starting_node; //set current node in previous to check if it continues or not in line 62
        i++; //increment total number of edge
    }


    int max_node_of_edge = i;
    for(i = 0; i <= max_node_of_edge; i++){
        for(j = 0; j < e[i].total; j++){
            cout<<i<<" "<<e[i].ending_state[j]<<" "<<e[i].input_symbol[j]<<endl;
        }
    }
    cout<<"Eclosure"<<endl;
    eclosure(0);
    cout<<endl<<endl;
    //saving for move(i, b)
    for(i=0; i<= MAX; i++){
        temp[i] = epsilon_closure[i];
    }

    //printing move with a
    cout<<"Move with a"<<endl;
    for(i=0; i<= MAX;i++){
        if(epsilon_closure[i]==true){
            Move(i, 'a');
        }
    }

    //restoring epsilon_closure
    for(i=0; i <= MAX; i++){
        epsilon_closure[i] = false;
        if(temp[i]==true){
            epsilon_closure[i] = true;
        }
    }

    //printing move(i, b)
    cout<<"Move with b"<<endl;
    for(i = 0; i <= MAX; i++){
        if(epsilon_closure[i]==true){
            Move(i, 'b');
        }
    }

    return 0;
}

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
