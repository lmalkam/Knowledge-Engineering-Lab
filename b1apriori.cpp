#include<bits/stdc++.h>
using namespace std;
bool checkcommon(vector<int> a, vector<int> b){
    int i=0;
    int j=0;
    int k = a.size();
    int cnt = 0;
    while(i<k){
        if(a[i]==b[j]){
            i++;
            j++;
            cnt++;
        }
        else{
            break;
        }
    }
    return cnt==k-1;
}
int findcount(map<string, vector<int>> map1, vector<int> alpha){
     int k = 0;
      int cnt = 0;
     for(auto it : map1){
        int i= 0;
        int j =0;
        if(alpha.size()>it.second.size()){
            continue;
        }
        int flag = 0;
       
        while(i<alpha.size() && j<it.second.size()){
             if(alpha[i]==it.second[j]){
                i++;
                j++;                                                                           
             }
             else if(alpha[i]<it.second[j]){
                flag = 1;
                break;
             }                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                           
             else{
                  j++;                                                                                                            
             }
        }
        if(flag==0 && i==alpha.size()){
             cnt++;
        }
     }
     return cnt;
}
int main(){
    ifstream file("data.txt");
    map<string, vector<int>> map1;
    map<int , vector<string>> map2;
    string line;
    while(getline(file, line)){
        int i=0;
        string s = "";
        cout<<line<<endl;
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
        for(; i<line.length(); i++){
            if(line[i]!=' '){
                alpha.push_back(line[i]-'0');
                map2[line[i]-'0'].push_back(s);
    
            }
        }
        sort(alpha.begin(), alpha.end());
        map1[s] =alpha;
    }
    cout<<"Printing map 1: \n\n";
    for(auto it : map1){
        cout<<it.first<<" ";
        for(auto it1 : it.second){
            cout<<it1<<" ";
        }
        cout<<endl;
    }

    cout<<endl;
    cout<<"Printing map2 :\n\n";
    for(auto it : map2){
        cout<<it.first<<" ";
        for(auto it1 : it.second){
            cout<<it1<<" ";
        }
        cout<<endl;
    }
    cout<<"-------------------------------------\n\n";

    int ntrans = map1.size();
    int nele = map2.size();
    float ms1;
    int ms;
    cin>>ms;
    vector<vector<int>> ans;
    vector<vector<int>> beta;

    for(auto it : map2){
        if(it.second.size()>=ms){
            vector<int> alpha;
            alpha.push_back(it.first);
            ans.push_back(alpha);
            beta.push_back(alpha);
        }
    }
    while(true){
        int size = beta.size();
        vector<vector<int>> beta1;
        for(int i=0; i<size; i++){
            for(int j=i+1; j<size; j++){
                if(checkcommon(beta[i], beta[j])){
                    set<int> st;
                    for(auto it : beta[i]){
                        st.insert(it);
                    }
                    for(auto it : beta[j]){
                        st.insert(it);
                    }

                    vector<int> alpha;
                    for(auto it : st){
                        alpha.push_back(it);
                    }
                    if(findcount(map1, alpha)>=ms){
                        ans.push_back(alpha);
                        beta1.push_back(alpha);
                    }
                }
            }
        }
        if(beta1.size()==0){
            break;
        }
        beta.clear();
        for(auto it : beta1){
            beta.push_back(it);
        }
    }
    cout<<endl;
    cout<<"Frequent item sets are :\n";
    for(auto it : ans){
        cout<<"{";
        for(auto it1 : it){
            cout<<it1<<" ";
        }
        cout<<"}\n";
    }
    return 0;
}