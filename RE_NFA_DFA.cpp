// Rahul Jauhari 2020A7PS0106H
#include <bits/stdc++.h>
#define col 5
#define _s 30
using namespace std;

int init[20],fin[20],a=0,b=0;
string start_trans[_s],final_trans[_s];
int _a = 0, _b = 0;

string convert_regex(string s){
    char x[5000];   
    for(int i = 0;i<s.length();i++)
    {
        if(s[i] == 'a'||s[i] == 'b')
        {
            // remove character before and after expression[i]
            s.erase(i-1,1);
            s.erase(i,1);
        }
    }
    s.erase(0, 1);
    s.erase(s.length() - 1, 1);
    int l=s.length();
    int j=0;
    x[j]='(';
    j += 1;
    for(int i=0;i<l;i++){
            x[j]=s[i];
            j += 1;
        if((s[i]=='a'||s[i]=='b')&&(s[i+1]=='a'||s[i+1]=='b')){
            x[j]='.';
            j += 1;
        }else if(s[i]==')'&&s[i+1]=='('){
            x[j]='.';
            j += 1;
        }else if((s[i]=='a'||s[i]=='b')&&s[i+1]=='('){
            x[j]='.';
            j += 1;
        }else if(s[i]==')'&&(s[i+1]=='a'||s[i+1]=='b')){
            x[j]='.';
            j += 1;
        }else if(s[i]=='*'&&(s[i+1]=='(' || (s[i+1]=='a'||s[i+1]=='b'))){
            x[j]='.';
            j += 1;
        }
        else if(s[i]=='+'&&(s[i+1]=='(' || (s[i+1]=='a'||s[i+1]=='b'))){
            x[j]='.';
            j += 1;
        }
    }
    x[j] = ')';
    j += 1;
    string regex_final;
    for(int i=0;i<j;i++)
       regex_final += x[i];
    
    return regex_final;
}

string postfix(string s){
    int l=s.length();
    char a[5000];
    stack <char> ch;
    int j=0;
    for(int i=0;i<l;i++){
         char x = s[i];
         switch(x){
            case 'a':   a[j]='a';
                        j += 1;
                        break;
            case 'b':   a[j]='b';
                        j+=1;
                        break;
            case '(':   ch.push('(');
                        break;
            case ')':   while(!ch.empty()){
                            if(ch.top()=='('){
                                ch.pop();
                                break;
                            }else{
                                a[j]=ch.top();
                                    ch.pop();
                                    j += 1;
                            }
                        }
                        break;
            case '.':   if(ch.empty()){
                            ch.push('.');
                        }else {
                            char temp = ch.top();
                            if(temp=='('||temp == '|')
                                ch.push('.');
                            else if(temp=='*'||temp=='+'){
                                a[j]=ch.top();
                                ch.pop();
                                j += 1;
                                if(ch.top()== '.'){
                                    a[j] = '.';
                                    j += 1;
                                }else{
                                    ch.push('.');
                                }
                            }
                            else if(temp=='.'){
                                a[j]=ch.top();
                                ch.pop();
                                j += 1;
                                ch.push('.');
                        }
                        }
                        break;
            case '|':   if(ch.empty()){
                            ch.push('|');
                        }else{
                            char temp = ch.top();
                            if(temp == '(')
                                ch.push('|');
                            else if(temp == '*'||temp == '+'||temp == '.'){
                                a[j] = ch.top();
                                ch.pop();
                                j += 1;
                                ch.push('|');
                            }
                        }
                            break;
            case '*':   if(ch.empty()){
                            ch.push('*');
                        }else{
                            char temp = ch.top();
                            if(temp == '(' || temp == '.' || temp == '|' )
                            {    ch.push('*');}
                            
                            else{
                                a[j] = ch.top();
                                ch.pop();
                                j += 1;
                                ch.push('*');
                            }
                        }
                        break;
            case '+':   if(ch.empty()){
                            ch.push('+');
                        }else{
                            char temp = ch.top();
                            if(temp == '(' || temp == '.' || temp == '|' )
                                ch.push('+');
                            else{
                                a[j] = ch.top();
                                ch.pop();
                                j += 1;
                                ch.push('+');
                            }
                        }
                        break;
         }
    }
    string postfix_final;
    for(int i=0;i<j;i++)
        postfix_final += a[i];
    
    return postfix_final;
}

int reg_nfa(string s,int nfa_trans[][col]){
    int l = s.length();
    int states = 1;
    int m,n,j,counter;
    
    for (int i=0; i<10;i++) 
    for(int i=0;i<l;i++){
        char x = s[i];
        switch(x){
            case 'a': nfa_trans[states][0] = states;
                        init[a] = states;
                         a += 1;
                            states += 1;
                      nfa_trans[states-1][1] = states;
                        fin[b] = states;
                        b += 1;
                      nfa_trans[states][0] = states;
                            states +=1;
                      break;
            case 'b': nfa_trans[states][0] = states;
                        init[a] = states;
                         a += 1;
                            states += 1;
                      nfa_trans[states-1][2] = states;
                          fin[b] = states;
                          b += 1;
                      nfa_trans[states][0] = states;
                            states +=1;
                      break;
            case '.': m = fin[b-2];
                      n = init[a-1];
                      nfa_trans[m][3]=n;
                      for(int i=b-2; i<b-1; i++)
                        fin[i] = fin[i+1];
                    b -= 1;   //reduces final state
                    a -= 1;           //reduces initial states
                    break;
            case '|': for(j=a-1,counter=0;counter<2;counter++){
                        m = init[j-counter];
                        nfa_trans[states][3+counter]=m;
                      }
                      a=a-2;
                      init[a]=states;
                      a += 1;
                      nfa_trans[states][0] = states;
                      states += 1;
                      for(j=b-1,counter=0;counter<2;counter++){
                        m = fin[j-counter];
                        nfa_trans[m][3]=states;
                      }
                      b=b-2;
                      fin[b]=states;
                      b += 1;
                      nfa_trans[states][0] = states;
                      states += 1;
                      break;
            case '*': m = init[a-1];
                      nfa_trans[states][3] = m;
                      nfa_trans[states][0] = states;
                      init[a-1] = states;

                      states += 1;
                      n = fin[b-1];
                      nfa_trans[n][3]=m;
                      nfa_trans[n][4]=states;
                      nfa_trans[states-1][4]=states;
                      fin[b-1]=states;
                      nfa_trans[states][0]=states;
                      states += 1;
                        break;
            case '+': m = init[a-1];
                      nfa_trans[states][3] = m;
                      nfa_trans[states][0] = states;
                      init[a-1] = states;
    
                      states += 1;
                      n = fin[b-1];
                      nfa_trans[n][3]=m;
                      nfa_trans[n][4]=states;
                      nfa_trans[states-1][4]=states;
                      fin[b-1]=states;
                      nfa_trans[states][0]=states;
                      states += 1;
                        break;
        }
    }
  return states;
}
vector <int> eclosure(int nfa_trans[][col], int x){
    stack <int> s;
    map <int, int> m;
    vector <int> v;
    int y;
    s.push(x);
    m[x] = 1;
    while(!s.empty()){
        y = s.top();
            s.pop();
        if(nfa_trans[y][3] == -1)
            continue;
        else{
            s.push(nfa_trans[y][3]);
            m[nfa_trans[y][3]] = 1;
            if(nfa_trans[y][4] == -1)
                continue;
            else{
                s.push(nfa_trans[y][4]);
                m[nfa_trans[y][4]] = -1;
            }
        }
    }

    map <int, int> ::iterator itr;
    itr = m.begin();

    while(itr != m.end()){
        v.push_back(itr->first);
        itr++;
    }
    return v;
}
string transition_(int i){
    char s = 'q';
    string p ;
    p += s;
    if(i==0){
            p += '0';
        return p;
    }
   int a[100];
   int j=0;
    while(i>0){
        int x = i%10;
        a[j]=x;
        j += 1;
        i = i/10;
    }
    for(int i=j-1;i>=0;i--){
            int x = a[i];
        switch(x){
            case 0: p += '0';
                    break;
            case 1: p += '1';
                    break;
            case 2: p += '2';
                    break;
            case 3: p += '3';
                    break;
            case 4: p += '4';
                    break;
            case 5: p += '5';
                    break;
            case 6: p += '6';
                    break;
            case 7: p += '7';
                    break;
            case 8: p += '8';
                    break;
            case 9: p += '9';
                    break;

        }
    }
    
    return p;
}

void check_(vector <int> v, string s){
    for(int i=0;i<v.size();i++){
        if(v[i] == init[0]){
            start_trans[_a] = s;
            _a += 1;
        }
    }

    for(int i=0;i<v.size();i++){
        if(v[i] == fin[0]){
            final_trans[_b] = s;
            _b += 1;
        }
    }
}

int nfa_dfa_transition(int nfa_trans[][col],int states,string dfa_trans[][3]){
    bool flag[states];
    memset(flag,true,sizeof(flag)); //to make sure all states E-closure found
    int state = 0,j = 0;
    map <vector<int>,string> map_state;
    vector <int> v,v1,v2,v3,v4;
    v = eclosure(nfa_trans,init[0]);
    flag[init[a]] = false;

    map_state[v] = transition_(j++);
    check_(v,map_state[v]);  //to check whether current state is initial or not

    stack < vector<int> > st;
    st.push(v);
    // transition of e-closure to over input symbol a
    int counter = 0;
    while(true){
       while(!st.empty()){
        vector <int> v ;
        v  = st.top();
             st.pop();
        counter += 1;
        dfa_trans[state][0] = map_state[v];       //find transition of a state over input symbol 'a' and 'b'
        for(int i=0;i<v.size();i++){
            flag[v[i]] = false;
            int temp = nfa_trans[v[i]][1]; 
            int temp1 = nfa_trans[v[i]][2];     //over input symbol b
            if(temp>=0)
                v1.push_back(temp);
            if(temp1>=0)
                v3.push_back(temp1);
        }
        map <int,int> map_temp,map_temp1;  //to remove duplicate state
        map <int,int> ::iterator it;
        for(int i=0;i<v1.size();i++){
            v2 = eclosure(nfa_trans,v1[i]);
            for(int j=0;j<v2.size();j++)
                {map_temp[v2[j]] = 1;}
            v2.clear();
        }
        for(int i=0;i<v3.size();i++){
            v4 = eclosure(nfa_trans,v3[i]);
            for(int j=0;j<v4.size();j++)
                map_temp1[v4[j]] = 1;
            v4.clear();
        }
        for(it = map_temp.begin(); it != map_temp.end(); it++){
            v2.push_back(it->first);
            flag[it->first] = false;
        }
        for(it = map_temp1.begin(); it != map_temp1.end(); it++){
            v4.push_back(it->first);
            flag[it->first] = false;
        }
        if(v2.empty()){
            dfa_trans[state][1] = "--";
        } else {
            string t = map_state[v2];
            char flag1 = t[0];
            if( flag1 == 'q'){
                dfa_trans[state][1] = map_state[v2];   //checking v2 has already been mapped or not
            } else {
                dfa_trans[state][1] = transition_(j++);
                map_state[v2] = dfa_trans[state][1];
                check_(v2,map_state[v2]);
                st.push(v2);                //not mapped state will be pushed into stack
            }
        }
        if(v4.empty()){
            dfa_trans[state][2] = "--";
        } else {
            string t = map_state[v4];
            char flag1 = t[0];
            if( flag1 == 'q'){
                dfa_trans[state][2] = map_state[v4];
            } else {
                dfa_trans[state][2] = transition_(j++);
                map_state[v4] = dfa_trans[state][2];
                check_(v4,map_state[v4]);
                st.push(v4);
            }
        }
        v1.clear(),v2.clear(),v3.clear(),v4.clear();
        state += 1;
    }
        int k = 1;
        for(k=1;k<states;k++){
            if(flag[k]){
                v = eclosure(nfa_trans,k);
                map_state[v] = transition_(j++);
                check_(v,map_state[v]);
                st.push(v);
                break;
            }
        }
        if(k == states)
                break;
    }
    
    return state;
}
int check_if_string_is_valid(string dfa_trans[][3],string word,int state){
    int len = word.length();
    string temp = start_trans[0];
    int i=0;
    for(i=0;i<len;i++){
        if(temp == "--")
            return -1;
        else {
            int _xtate;
            int j=0;

            for(j=0;j<state;j++){  
                if(temp == dfa_trans[j][0])
                    break;
            }

            if(word[i]=='a'){
                temp = dfa_trans[j][1];
            } else if(word[i]=='b'){
                temp = dfa_trans[j][2];
            }
        }
    }

    if(i == len){
            int j=0;
        for(j=0;j<_b;j++){
            if(temp == final_trans[j])
                return 0;
        }
        if(j==_b)
            return -1;
    }
    return -1;
}
int main(){
    int nfa_trans[1000][col];
    for(int i=0;i<1000;i++){
        for(int j=0;j<col;j++)
            nfa_trans[i][j]=-1;
    }
    int states=0;
    ifstream in("input.txt");
    string regex, str; 
    getline(in, regex);
    getline(in, str); 
    in.close();
    regex=convert_regex(regex); 
    regex=postfix(regex);
    states = reg_nfa(regex,nfa_trans); 
    string dfa_trans[states][3];
    int dfa_state = 0; 
    dfa_state = nfa_dfa_transition(nfa_trans,states,dfa_trans);
    ofstream out("output.txt"); 
    int l1=0,r1=str.size()-1,a2=r1;
    string ans="";
    while(l1<=r1)
    { 
        string temp=str.substr(l1,a2-l1+1);
        int flag=check_if_string_is_valid(dfa_trans,temp,dfa_state);
        if(flag==0)
        { 
            ans+="$"+temp;
            l1=a2+1;
            a2=r1;
        }
        else if(l1==a2)
        {
            ans+="@"+temp;
            l1=a2+1;
            a2=r1;
        }
        else
            {a2--;}
            
    }   
    out<<ans;
    out<<"#";
    out.close();
 return 0;
}

