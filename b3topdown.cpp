#include<bits/stdc++.h>
using namespace std;

int findcount(vector<int> alpha, map<string, vector<int>> map1){
    int count = 0;
    for(auto it : map1){
        if(alpha.size()>it.second.size()){
            continue;
        }
        int i =0;
        int j=0;
        int flag = 0;
        while(i<alpha.size() && j<it.second.size()){
            if(alpha[i]== it.second[j]){
                i++;
                j++;
            }
            else if(alpha[i]<it.second[j]){
                flag =1;
                break;
            }
            else{
                j++;
            }
        }
        if(flag==0 && i==alpha.size()){
            count++;
        }
    }
    return count;
}
void gensub(vector<int> alpha, set<vector<int>> &ans, vector<int> temp, int ind){
    if(ind==alpha.size()){
        if(temp.size()>0){
            vector<int> a;
            for(auto it : temp){
                a.push_back(it);
            }
            ans.insert(a);
        }
        return;
    }
    temp.push_back(alpha[ind]);
    gensub(alpha, ans, temp , ind+1);
    temp.pop_back();
    gensub(alpha, ans, temp, ind+1);
}
void topdown(set<vector<int>>&ans, vector<int> &alpha, map<string, vector<int>> map1, int ms){
    if(alpha.size()==0){
        return;
    }
    if(findcount(alpha, map1)>=ms){
          vector<int> temp;
          gensub(alpha, ans, temp, 0);
          return;
    }
    else{
        for(int i=0; i<alpha.size(); i++){
            vector<int> a1;
            for(int j=0; j<alpha.size(); j++){
                if(i!=j){
                    a1.push_back(alpha[j]);
                }
                topdown(ans, a1, map1, ms);
            }
        }
    }
}
int main(){
    ifstream file("data.txt");
    map<string, vector<int>> map1;
    string line;
    while(getline(file, line)){
        int i=0;
        string s = "";
        for(i=0; i<line.length(); i++){
             if(line[i]==' '){
                break;
             }
             else{
                s+=line[i];
             }
        }
        i++;
        vector<int> alpha;
        for( ; i<line.length(); i++){
            if(line[i]!=' '){
                 alpha.push_back(line[i]-'0');
            }
        }
        sort(alpha.begin(), alpha.end());
        map1[s] = alpha;
    }
    cout<<"Printing map1:\n";
    for(auto it : map1){
        cout<<it.first<<" ";
        for(auto it1 : it.second){
            cout<<it1<<" ";
        }
        cout<<endl;
    }
    set<int> myst;
    for(auto it : map1){
        for(auto it1 : it.second){
            myst.insert(it1);
        }
    }

    vector<int> alpha;
    for(auto it : myst){
        alpha.push_back(it);
    }
    set<vector<int>> ans;
    int ms;
    cout<<"Enter minimum support\n";
    cin>>ms;
    topdown(ans, alpha, map1, ms);

    cout<<endl;
    cout<<"Frequent itemset are:\n";
    for(auto it : ans){
        cout<<"{ ";
        for(auto it1 : it){
            cout<<it1<<" ";
        }
        cout<<"}\n";
    }
    return 0;
}