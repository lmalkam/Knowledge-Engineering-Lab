#include<bits/stdc++.h>
using namespace std;
//Linesh
map<int,int>cnt;
map<int,set<pair<vector<int>,int>>>path;
struct node{
    node* ptr[100];
    int val=0;

    void put(int id,node* curr)
    {
        ptr[id] = curr;
    }
};

class fptree{
    public:
    node* root;
    public:

    fptree()
    {
        root = new node();
    }

    void insert(vector<int>tid)
    {
        node* temp = root;

        for(int i=0;i<tid.size();i++)
        {
            if(temp -> ptr[tid[i]] == NULL)
            {
                temp->put(tid[i],new node());
            }

            temp->ptr[tid[i]]->val++;

            temp = temp->ptr[tid[i]];
        }
        cout<<"INSERTED\n";
    }

    void print(node* curr)
    {

        for(int i=0;i<100;i++)
        {
            if(curr->ptr[i]!=NULL)
            {
                cout<<i<<" "<< curr->ptr[i]->val<<" | ";
                print(curr->ptr[i]);
            }
        }
    }

    void generate(node* curr,vector<int>temp = {})
    {
        for(int i=0;i<100;i++)
        {
            if(curr->ptr[i]!=NULL)
            {
                if(temp.size())
                {
                    pair<vector<int>,int>cur = {temp,curr->ptr[i]->val};
                    path[i].insert(cur);
                }
                
                temp.push_back(i);
                generate(curr->ptr[i],temp);
                temp.pop_back();
            }
        }

    }


};


vector<int> convert(vector<int>tid)
{

    priority_queue<pair<int,int>>pq;

    for(auto it:tid)
    {
        pq.push({cnt[it],-it});
    }

    vector<int>temp;

    while(!pq.empty())
    {
        if(cnt[-pq.top().second]>=3)
        {
        temp.push_back(-pq.top().second);
        cout<<-pq.top().second<<" ";
        }
        pq.pop();
    }
    cout<<endl;

    return temp;

}

void subsets(vector<int>arr,int first,int count,int i=0,vector<int>temp={})
{
    if(i==arr.size())
    {
        if(temp.size()>=1)
        {
            for(auto it:temp)cout<<it<<" ";
            cout<<first<<" ";
            cout<<"freq("<<count<<")"<<" , ";
        }
        return;
    }

    subsets(arr,first,count,i+1,temp);
    temp.push_back(arr[i]);
    subsets(arr,first,count,i+1,temp);
    temp.pop_back();
}
int main()
{

    fstream file("td.txt");
    map<int, vector<int> > map1;  // t1 a b c d
    map<int, vector<string> > map2;  // a t1 t2 t3 

    string line;
    //cout<<"Linesh"<<endl;
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
        for(; i<line.length(); i++){
            if(line[i]!=' '){
                alpha.push_back(line[i]-'0');
                cnt[line[i] - '0']++;
            }
        }
        sort(alpha.begin(), alpha.end());
        map1[s[1]-'0'] =alpha;
    }


    for(auto it : map1){
        sort(it.second.begin(), it.second.end());
    }

    cout<<"TRANSACTION \n"<<endl;

    for(auto it : map1){
        for(auto it1 : it.second){
            cout<<it1<<" ";
        }
        cout<<endl;
    }

    cout<<"\n Creation of Frequent Pattern TREE \n";

    fptree t;


    for(auto it:map1)
    {
        vector<int>temp = convert(it.second);
        t.insert(temp);
    }

    cout<<"\n TREE PREORDER\n";
    t.print(t.root);
    cout<<endl;
    t.generate(t.root);


    cout<<"\n Conditional pattern base\n";

    for(auto it:path)
    {
        cout<<it.first<<"->";
        for(auto itr:it.second)
        {
            for(auto node:itr.first)
            {
                cout<<node<<" ";
            }
            cout<<"f("<<itr.second<<")"<<" ";
            cout<<",";
        }
        
        cout<<endl;
    }

    cout<<"\n Conditional Frequent Pattern Tree\n";

    map<int,set<pair<vector<int>,int>>>pattern;
    for(auto it:path)
    {
        cout<<it.first<<" ->";
        map<int,int>mp;
        for(auto itr:it.second)
        {
            for(auto node:itr.first)
            {
                mp[node] += itr.second;
            }
        }
        for(auto itr:mp)
        {
            vector<int>temp;
            if(itr.second>=3)
            {
                cout<<itr.first<<" ";
                temp.push_back(itr.first);
            }
            pattern[it.first].insert({temp,itr.second});
        }
        cout<<endl;
    }

    cout<<"\n Frequent Pattern Generated \n"<<endl;
    for(auto it:pattern)
    {
        int first = it.first;
        cout<<first<<"->";
        set<int>temp;
        int cntt;
        for(auto itr:it.second)
        {
            if(itr.first.size() == 0)continue;
            
            for(auto node : itr.first)
            {
                temp.insert(node);
            }
            cntt = itr.second;
        }
        vector<int>arr(temp.begin(),temp.end());
        subsets(arr,first,cntt);
        cout<<endl;
    }

}