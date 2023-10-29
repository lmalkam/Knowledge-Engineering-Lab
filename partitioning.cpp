#include <bits/stdc++.h>
using namespace std;
bool checkcommon(vector<int> a, vector<int> b)
{
    int m = a.size();
    int c = 0;
    for (int i = 0; i < m; i++)
    {
        if (a[i] != b[i])
        {
            break;
        }
        c++;
    }
    if (c == m - 1)
    {
        return true;
    }
    return false;
}

int findcount(map<string, vector<int>> map1, vector<int> alpha)
{
    sort(alpha.begin(), alpha.end());
    int count = 0;
    for (auto it : map1)
    {
        if (it.second.size() < alpha.size())
        {
            continue;
        }

        int i = 0;
        int j = 0;
        int flag = 0;
        while (i < alpha.size() && j < it.second.size())
        {
            if (alpha[i] == it.second[j])
            {
                i++;
                j++;
            }
            else if (alpha[i] < it.second[j])
            {
                flag = 1;
                break;
            }
            else
            {
                j++;
            }
        }
        if (flag == 0 && i == alpha.size())
        {
            count++;
        }
    }
    return count;
}
void apriori(map<string, vector<int>> map1, map<int, vector<string>> map2, float ms, vector<vector<int>> &ans)
{
    vector<vector<int>> beta;
    for (auto it : map2)
    {
        if (it.second.size() >= ms)
        {
            vector<int> alpha;
            alpha.push_back(it.first);
            beta.push_back(alpha);
            ans.push_back(alpha);
        }
    }
    while (true)
    {
        int size = beta.size();
        vector<vector<int>> beta1;
        for (int i = 0; i < size; i++)
        {
            for (int j = i + 1; j < size; j++)
            {
                if (checkcommon(beta[i], beta[j]))
                {
                    set<int> st;
                    for (auto it : beta[i])
                    {
                        st.insert(it);
                    }
                    for (auto it : beta[j])
                    {
                        st.insert(it);
                    }
                    vector<int> alpha;
                    for (auto it : st)
                    {
                        alpha.push_back(it);
                    }
                    if (findcount(map1, alpha) >= ms)
                    {
                        ans.push_back(alpha);
                        beta1.push_back(alpha);
                    }
                }
            }
        }
        if (beta1.size() == 0)
        {
            break;
        }
        beta.clear();
        for (int i = 0; i < beta1.size(); i++)
        {
            beta.push_back(beta1[i]);
        }
    }
}
int main()
{
    ifstream file("data.txt");
    string line;
    cout << "Enter the number of transacions:\n";
    int ntrans;
    cin >> ntrans;
    float ms1;
    cout << "Enter Minimum support:\n";
    cin >> ms1;

    float ms = ntrans * ms1;

    vector<vector<int>> ans;
    int p;
    cout << "Enter number of partitions:\n";
    cin >> p;
    int x = ceil((float)ntrans / p);
    for (int k = 1; k <= p; k++)
    {
        float a = 0;
        map<string, vector<int>> map1; // t1 a b c d
        map<int, vector<string>> map2; // a t1 t2 t3
        while (getline(file, line) && a < x - 1)
        {
            int i = 0;
            string s = "";
            for (i = 0; i < line.length(); i++)
            {
                if (line[i] == ' ')
                {
                    break;
                }
                else
                {
                    s += line[i];
                }
            }
            i++;
            vector<int> alpha;
            for (; i < line.length(); i++)
            {
                if (line[i] != ' ')
                {
                    alpha.push_back(line[i] - '0');
                    map2[line[i] - '0'].push_back(s);
                }
            }
            sort(alpha.begin(), alpha.end());
            map1[s] = alpha;
            a++;
        }
        int i = 0;
        string s = "";
        for (i = 0; i < line.length(); i++)
        {
            if (line[i] == ' ')
            {
                break;
            }
            else
            {
                s += line[i];
            }
        }
        i++;
        vector<int> alpha;
        for (; i < line.length(); i++)
        {
            if (line[i] != ' ')
            {
                alpha.push_back(line[i] - '0');
                map2[line[i] - '0'].push_back(s);
            }
        }
        sort(alpha.begin(), alpha.end());
        map1[s] = alpha;
        cout << "Iteration number : " << k << endl;
        cout << "Printing map1:\n";
        for (auto it : map1)
        {
            cout << it.first << " ";
            for (auto it1 : it.second)
            {
                cout << it1 << " ";
            }
            cout << endl;
        }
        cout << endl;
        cout << endl;
        cout << " -------------------------------------\n";
        apriori(map1, map2, a * ms1, ans);
    }
    map<vector<int>, int> finmap;
    for(auto it : ans){
        finmap[it]++;
    }
    cout << "Frequent item sets are :\n";
    for(auto it : finmap){
        if(it.second>=ms){
            cout<<"{ ";
            for(auto it1 : it.first){
                cout<<it1<<" ";
            }
            cout<<"}\n";
        }
    }
    return 0;
}