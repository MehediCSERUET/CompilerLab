#include<bits/stdc++.h>
using namespace std;

int lookahead_pointer = 0;
char lookahead[100];

struct Token{
    char t[100];
};

void match(char lookahead[], char input[]){
    if(strcmp(lookahead, input)==0){
        cout<<"Lookahead: "<<lookahead<<endl<<"input: "<<input<<endl;
        lookahead_pointer++;
    }
}

void optexpr(char lookahead[]){
    if(strcmp(lookahead, "expr") == 0){
        match(lookahead, "expr");
    } else {
        cout<<"Lookahead: space"<<endl<<"Optexpr: @"<<endl;
    }

}

int main()
{
    Token my[100];
    int i, j = 0, k = 0, l = 0,m = 0, length;
    char stmt[100], fun_name[100], expr[100], temp[100];
    bool fun_name_found = false, arguments_found = false;
    gets(stmt);

    length = strlen(stmt);

    for(i = 0; i < length; i++){
        if(isalpha(stmt[i]) && fun_name_found == false){
            fun_name[j++] = stmt[i];
            continue;
        }
        if(!isalpha(stmt[i]) && fun_name_found == false){
            fun_name_found = true;
            strcpy(my[k++].t, fun_name);
            i--;
            continue;
        }
        if(stmt[i] == '('){
            temp[0]  = '(';
            strcpy(my[k++].t, temp);
            continue;
        }
        if(stmt[i] == ')'){
            temp[0] = ')';
            strcpy(my[k++].t, temp);
            i++;
            while(i < length){
                expr[m++] = stmt[i++];
            }
            strcpy(my[k++].t, expr);
            continue;
        }
        if(stmt[i] == ';'){
            temp[0] = ';';
            strcpy(my[k++].t, temp);
            continue;
        }
        if(fun_name_found == true){
            while(stmt[i] != ';' || stmt[i] != ')' && i < length){
                if(stmt[i] != ' '){
                    expr[l++] = stmt[i];
                }
                if(stmt[i+1] == ';' || stmt[i+1] == ')'){
                    strcpy(my[k++].t, expr);
                    l = 0;
                    break;
                }
                i++;
            }
        }
    }



    for(i = 0; i < k; i++)
        cout<<my[i].t<<endl;

//GO:
    strcpy(lookahead, my[lookahead_pointer].t);
    if(strcmp(lookahead, "for") == 0){
        match(lookahead, "for");

        strcpy(lookahead, my[lookahead_pointer].t);
        match(lookahead, "(");

        strcpy(lookahead, my[lookahead_pointer].t);
        optexpr(lookahead);

        strcpy(lookahead, my[lookahead_pointer].t);
        match(lookahead, ";");

        strcpy(lookahead, my[lookahead_pointer].t);
        optexpr(lookahead);

        strcpy(lookahead, my[lookahead_pointer].t);
        match(lookahead, ";");

        strcpy(lookahead, my[lookahead_pointer].t);
        optexpr(lookahead);

        strcpy(lookahead, my[lookahead_pointer].t);
        match(lookahead, ")");

        strcpy(lookahead, my[lookahead_pointer].t);
        match(lookahead, "stmt");
    } else if(strcmp(lookahead, "if") == 0){
        match(lookahead, "if");

        strcpy(lookahead, my[lookahead_pointer].t);
        match(lookahead, "(");

        strcpy(lookahead, my[lookahead_pointer].t);
        match(lookahead, "expr");

        strcpy(lookahead, my[lookahead_pointer].t);
        match(lookahead, ")");

        strcpy(lookahead, my[lookahead_pointer].t);
        match(lookahead, "stmt");
    } else if(strcmp(lookahead, "expr")==0){
        match(lookahead, "expr");
        strcpy(lookahead, ";");
    } else if(strcmp(stmt, "other")==0){
        match(stmt, "other");
    } else {
        cout<<"Syntax Error"<<endl;
        return 0;
    }
    cout<<endl<<"Accepted"<<endl;

    return 0;
}
/*

if(expr)stmt

for(;expr;expr)stmt

*/
