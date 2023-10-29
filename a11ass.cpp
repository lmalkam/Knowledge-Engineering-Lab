#include <bits/stdc++.h>
#include <fstream>
using namespace std;
bool customcomp(pair<string, double> a, pair<string, double> b){
    return abs(a.second)>abs(b.second);
}
double calcor(vector<double> a, vector<double> b){
    double suma =0.0, sumb = 0.0, sumab = 0.0;
    double sumsa =0.0 , sumsb = 0.0;

    int n = a.size();
    for(int i=0; i<n; i++){
        suma += a[i];
        sumb += b[i];
        sumab += a[i]*b[i];
        sumsa += a[i]*a[i];
        sumsb += b[i]*b[i];
    } 

    double num = n * sumab - suma*sumb;
    double denom = sqrt((n*sumsa- suma*suma) * (n * sumsb - sumb*sumb));
    if(denom==0.0){
        return 0.0;
    }
    return num/denom;
}
double chisqval(vector<double> observed , vector<double> expected){
    int n = observed.size();
    double alpha = 0.0;
    for(int i=0; i<n; i++){
        if(expected[i]!= 0.0){
            double diff = observed[i]- expected[i];
            alpha+= (diff*diff)/expected[i];
        }
    }
    return alpha;
}
int main(){
    ifstream file("data1.txt");
    map<string, vector<double>> data;
    string line;
    string head;
    vector<string> header;
    if (getline(file, head))
    {
        string s = "";
        for (int i = 0; i < head.length(); i++)
        {
            if (head[i] == ' ')
            {
                data[s] = vector<double>();
                header.push_back(s);
                s = "";
                while(head[i]==' '){
                    i++;
                }
                i--;
            }
            else
            {
                s += head[i];
            }
        }
        data[s] = vector<double>();
        header.push_back(s);
    }
    while (getline(file, line))
    {
        cout<<line<<endl;
        int k = 0;
        string s = "";
        for (int i = 0; i < line.length(); i++)
        {
            if (line[i] == ' ')
            {
                double x = stod(s);
                data[header[k]].push_back(x);
                k++;
                s = "";
                while (line[i] == ' ')
                {
                    i++;
                }
                i--;
            }
            else
            {
                s += line[i];
            }
        }
        double x = stod(s);
        data[header[k]].push_back(x);
    }
    cout<<endl<<endl;
    cout<<"The dataset : \n";
    for(auto it : data){
        cout<<it.first<<" : ";
        for(auto it1 : it.second){
            cout<<it1<<" ";
        }
        cout<<endl;
    }
    cout<<"--------------------------------------------------------------\n";
    vector<pair<string, double>> correlations;
    string alpha;
    cout<<"Enter the target attribute:\n";
    cin>>alpha;
    vector<double> &target = data[alpha];
    for(auto it : data){
        if(it.first!=alpha){
             double correlation = calcor(it.second, target);
             correlations.push_back(make_pair(it.first, correlation));
        }
    }
    sort(correlations.begin(), correlations.end(), customcomp);
    int k;
    cout<<"Enter the desired number of attributes:\n";
    cin>>k;
    cout<<"The top "<<k<<" most relevant attributes are as follows using correlation method :\n";
    for(int i=0; i<k && i<correlations.size(); i++){
        cout<<correlations[i].first<<" : "<< correlations[i].second<<endl;
    }

    cout<<"---------------------------------------------------------\n";
    cout<<"Starting chi-square method:\n";
    vector<double> target1;
    cout<<"Enter the expected frequencies:\n";
    int n = data[alpha].size();
    for(int i=0; i<n; i++){
        double x;
        cin>>x;
        target1.push_back(x);
    }
    vector<pair<string, double>> chisq;
    for(auto it : data){
        vector<double> &observed = it.second;
        double val = chisqval(observed, target1);
        chisq.push_back(make_pair(it.first, val));
    }

    sort(chisq.begin(), chisq.end(), customcomp);
    cout<<"The top "<<k<<" attributes with highes chi-squared values are :\n";
    for(int i=0; i<k && i<chisq.size(); i++){
        cout<<chisq[i].first<<" : "<<chisq[i].second<<endl;
    }
    cout<<"-----------------------------------------------------------------\n";
}