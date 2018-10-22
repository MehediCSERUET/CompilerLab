#include<bits/stdc++.h>
using namespace std;
#define pb push_back
bool visited[100];
vector<int> nfa[100];
vector<char> trans[100];
set<int> st;

void eclosure(int node)
{
    st.insert(node);

    if(nfa[node].size() == 0  || visited[node] == 1)
        return;

    visited[node] = 1;

    for(int i=0; i<nfa[node].size(); i++)
    {
        if(trans[node][i] == 'e')
        {
            eclosure(nfa[node][i]);
        }
    }
}

void transmove(int node, char c)
{
    for(int i=0; i<nfa[node].size(); i++)
    {
        if(trans[node][i] == c)
            st.insert(nfa[node][i]);
    }
}

int main()
{
    int node, symbol,i,j, a, b, k, curr, table[100][100], init, fin, edge;
    char c, symb[100];
    FILE *fp = fopen("in.txt", "r+");

    map<set<int>, char> mp;
    map<set<int>, char> :: iterator mit;
    queue<set<int> > state;
    set<int> currst, newst;
    set<int> :: iterator it;

    fscanf(fp, "%d",&node);

    //cout<<"The number of input symbol ";
    //cin>>symbol;
    fscanf(fp, "%d",&symbol);

    //cout<<"give input the symbols ";
    for(i=0; i<symbol; i++)
    {
        fscanf(fp," %c",&symb[i]);
        //printf("%c\n", symb[i]);
    }

    //cout<<"Number of transitions?\n";
    //cin>>edge;
    fscanf(fp, "%d",&edge);

    //cout<< "Give input the transition nodes(1-->2) and symbol (for epsilon give 'e')\n";

    for(i=0; i<edge; i++)
    {
        fscanf(fp, "%d %d %c",&a,&b,&c);
        nfa[a].pb(b);                       /// transition from node a to node b.
        trans[a].pb(c);                    /// transition symbol from a to b.
    }

    //cout<<"initial and final state\n";
    //cin>>init>>fin;
    fscanf(fp,"%d %d",&init,&fin);

    memset(visited, 0, sizeof visited);
    eclosure(init);                             /// epsilon transition from the starting state.
    state.push(st);                             /// initialize the queue by eclosure(init);
    mp[st] = 'A';                               /// name the new node as 'A'
    k = 1;

    while(!state.empty())
    {
        currst.clear();
        currst = state.front();                 /// the current state working with
        state.pop();                            /// remove the state from queue.
        curr = mp[currst]-'A';                  /// the name of the state working with.


        for(j=0; j<symbol; j++)
        {
            st.clear();
            for(it = currst.begin(); it!=currst.end(); it++)
            {
                node = *it;
                transmove(node, symb[j]);               /// ex: eclosure ( move(A, a) ); all the states are saved in 'st'.
            }

            newst = st;                    /// copy 'st' into 'currst'.
            st.clear();

            for(it = newst.begin(); it!=newst.end(); it++)            /// eclosure for all the states found,
            {
                memset(visited, 0, sizeof visited);
                eclosure(*it);
            }

            if(mp.find(st) == mp.end())                 /// if this is a new set of nodes i.e. new DFA node.
            {
                mp[st] = k+'A';
                k++;
                state.push(st);
            }
            table[curr][symb[j]-'a'] = mp[st];          /// creating DFA table.
        }
    }

    printf("eNFA -> DFA\n\n");
    printf("States\\Symbol");
    for(j=0; j<symbol; j++)
        printf("\t| %c |\t",symb[j]);
    printf("\n");
    for(i=0; i<20; i++)
        printf("--");
    printf("\n");
    for(i=0; i<k; i++)
    {
        printf(" %c ", i+'A');
        for(j=0; j<symbol; j++)
            printf("\t\t %c ", table[i][j]);
        printf("\n");
    }

    printf("\nHere\n");

    for(mit = mp.begin(); mit!=mp.end(); mit++)
    {
        printf("state %c = {",(*mit).second);
        for(it = (*mit).first.begin(); it!=(*mit).first.end(); it++)
            printf("%d ",*it);
        printf("}\n");
    }
    printf("\n");

    return 0;
}
