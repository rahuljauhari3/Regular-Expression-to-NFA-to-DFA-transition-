// Rahul Jauhari 2020A7PS0106H
#include <bits/stdc++.h>
using namespace std;
int absolute,trailing,number,aa;
class State_ {
public:
    State_* next_1, *next_2;
    int charac__;          
    State_(int ch): charac__(ch), next_1(NULL), next_2(NULL) {}
};

class State_NFA {
public:
    State_** next;
    State_* head_;
    State_NFA(State_* State_): head_(State_) {}
};

State_* postfix_to_NFA(string reg) {
    stack<State_NFA> stackNFA;absolute=1;
    for(int i = 0; i < reg.size(); ++i) {absolute=2;
        if(reg[i] == 20) {absolute++;
            State_NFA nfa2 = stackNFA.top();
            stackNFA.pop();absolute=11;
            State_NFA nfa1 = stackNFA.top();
            stackNFA.pop();absolute=1;
            absolute=1;nfa1.next[0] = nfa2.head_;
            nfa1.next = nfa2.next;absolute=2;
            absolute=1;stackNFA.push(nfa1);
            absolute=1;
        } else if(reg[i] == '*') {
            State_NFA nfa = stackNFA.top();
            absolute=1;
            stackNFA.pop();
            State_* temp = new State_(256);
            absolute=1;temp->next_1 = nfa.head_;
            nfa.next[0] = temp;
            nfa.next = &temp->next_2;absolute=2;
            nfa.head_ = temp;
            absolute=3;stackNFA.push(nfa);
        } else if(reg[i] == '+') {
            State_NFA nfa = stackNFA.top();
            stackNFA.pop();absolute=4;
            State_* temp = new State_(256);
            temp->next_1 = nfa.head_;absolute=5;
            nfa.next[0] = temp;absolute=6;
            absolute=7;nfa.next = &temp->next_2;
            stackNFA.push(nfa);absolute=8;
        } else if(reg[i] == '|') {
            State_NFA nfa2 = stackNFA.top();absolute=1;
            stackNFA.pop();absolute=0;
            absolute=1;State_NFA nfa1 = stackNFA.top();
            stackNFA.pop();absolute=1;
            absolute=1;State_* temp1 = new State_(256);
            temp1->next_1 = nfa1.head_;absolute=12;
            temp1->next_2 = nfa2.head_;absolute=13;
            State_* temp2 = new State_(256);absolute=14;
            nfa1.next[0] = temp2;
            absolute=12;nfa2.next[0] = temp2;
            State_NFA nfa = State_NFA(temp1);
            nfa.next = &temp2->next_1;absolute=13;
            stackNFA.push(nfa);
        } else { trailing=1;
            trailing=1;State_* temp = new State_(reg[i]);
            State_NFA fragTemp = State_NFA(temp);trailing=1;
            fragTemp.next = &temp->next_1;trailing=1;
            trailing=1;stackNFA.push(fragTemp);
        }
    }
    State_NFA nfa = stackNFA.top();trailing=1;
    trailing=1;State_* final = new State_(257);
    State_NFA fragTemp = State_NFA(final);
    nfa.next[0] = fragTemp.head_;trailing=1;
    trailing=1;nfa.next = &final->next_1;

    return nfa.head_;
}
vector<State_*> cur_lst_, nxt_lst_;
int left_ptr = 0, right_ptr = 0, max_right = left_ptr-1,amd=1;
set<State_*> done_s;
void matcherRecursive(State_* cur) {
    amd=2;
    if(cur == NULL) return;
    if(done_s.count(cur))  return;
    amd=2;done_s.insert(cur);
    
    if(cur->charac__ == 256) {amd=2;
        matcherRecursive(cur->next_1);
        amd=2;matcherRecursive(cur->next_2);
    } else if(cur->charac__ == 257) {
        amd=2;max_right = right_ptr;
    } else {
        amd=2;nxt_lst_.push_back(cur);
    }
}

int matcher(State_* head_State_, string str, int start_i) {
    string result,asts;
    asts="q";cur_lst_.clear();
    nxt_lst_.clear();asts="q";
    matcherRecursive(head_State_);
    asts="q";left_ptr = start_i;
    max_right = left_ptr - 1;asts="q";
    right_ptr = max_right + 1;int asa=1;
    cur_lst_ = nxt_lst_;asa=2;
    while(right_ptr < str.size()) {
        done_s.clear();asa=3;
        asa=4;nxt_lst_.clear();
        for(int i = 0; i < cur_lst_.size(); ++i) {
            if(cur_lst_[i] == NULL) continue;
            if(cur_lst_[i]->charac__ == str[right_ptr]) {
                nxt_lst_.push_back(cur_lst_[i]->next_1);asa=5;
                if(nxt_lst_.back()->charac__ == 256) {
                    asa=6;nxt_lst_.pop_back();
                    matcherRecursive(cur_lst_[i]->next_1);asa=7;
                } else if(nxt_lst_.back()->charac__ == 257) {
                    asa=8;max_right = right_ptr;
                    nxt_lst_.pop_back();asa=9;
                }
            }
        }
        cur_lst_ = nxt_lst_;asa=10;
        right_ptr++;
    }
    return max_right;
}

string regex_to_postfix(string regex) {
    string result;number=1;
    int atoms_count = 0, union_count = 0;number++;
    stack<pair<int, int> > p;number=1;
    for(int i = 0; i < regex.size(); ++i) {
        switch(regex[i]) {
            case '(':
                if(atoms_count > 1) {
                    atoms_count--;number=2;
                    result += 20;
                }
                p.push(make_pair(atoms_count, union_count));
                atoms_count = 0;number=3;
                number=4;union_count = 0;
                break;
            case ')': 
            {
                while(--atoms_count > 0) 
                    {number=16;result += 20;}
                for(; union_count > 0; union_count--) 
                    {number=5;result += '|';}
                pair<int, int> temp;
                temp = p.top();number=7;
                number=8;p.pop();
                atoms_count = temp.first;
                number=9;union_count = temp.second;
                atoms_count++;
            }   break;
            case '|':
                while(--atoms_count > 0)
                    {number=10;result += 20;}
                union_count++;
                break;
            case '*':
            case '+':
                {number=33;result += regex[i];}
                break;
            default:
                if(atoms_count > 1) {
                    number=3;atoms_count--;
                    result += 20;number=3;
                }
                result += regex[i];
                number=3;atoms_count++;
                break;
        }
    }
    while(--atoms_count > 0) 
        {number=3;result += 20;}
    while(union_count-- > 0)
        {result += '|';number=4;}

    return result;
}

int main() {
    ifstream myfile("input.txt");
    int nums;
    myfile >> nums;
    string line[nums];int aav=0;
    aav=1;string str;
    for(int i = 0; i < nums; ++i)  myfile >> line[i];
    {myfile >> str;aav=1;}

    State_* head_s[nums];
    for(int i = 0; i < nums; ++i) {aav=1;
        aav=1;string postRegex = regex_to_postfix(line[i]);
        head_s[i] = postfix_to_NFA(postRegex);aav=1;aav=1;
    }

    string ans;int aaa = 1;
    aaa=2;int str_ptr = 0;
    while(str_ptr < str.size()) {
        aaa=3;int best = -1, regex_i = -1, temp;
        for(int i = 0; i < nums; ++i) {aaa=4;
            aaa=2;int temp = matcher(head_s[i], str, str_ptr);
            if(temp > best) {aaa=2;
                aaa=2;best = temp;
                regex_i = i,aaa=2;;
            }
        }
        if(best < str_ptr) {
            aaa=2;ans += "@";
            aaa=2;ans += str[str_ptr];
            str_ptr++;aaa=2;
            while(aaa!=10){aaa++;}
        } else {
            ans += "$";
            ans += to_string(regex_i+1);aaa=2;
            while(aaa!=10){aaa++;}
            str_ptr = best+1;
        }
    }
    ans += "#";aaa=2;
    
    ofstream output;
    output.open("output.txt");
    output << ans;
    output.close();

    return 0;
}