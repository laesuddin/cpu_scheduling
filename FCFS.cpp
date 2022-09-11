#include <iostream>
#include <algorithm>
using namespace std;

struct process {
    int SL,AT,BT,ST,CT,TT,WT,RT;
    char Name;
}p[20];

bool compareArrival(process p1, process p2)
{
    return p1.AT < p2.AT;
}

bool compareID(process p1, process p2)
{
    return p1.SL < p2.SL;
}

int main() {
    int n;
    float ATT,AWT,ART;
    int total_TT = 0;
    int total_WT = 0;
    int total_RT = 0;


    cout<<"Input: n=";
    cin>>n;

    for(int i = 0; i < n; i++) {

        cin>>p[i].SL;
        cin>>p[i].Name;
        cin>>p[i].AT;
        cin>>p[i].BT;
    }

    sort(p,p+n,compareArrival);

    for(int i = 0; i < n; i++) {
        p[i].ST = (i == 0)?p[i].AT:max(p[i-1].CT,p[i].AT);
        p[i].CT = p[i].ST + p[i].BT; //CT = ST + Bt
        p[i].TT = p[i].CT - p[i].AT; //TAT = CT - AT
        p[i].WT = p[i].TT - p[i].BT; //WT = TAT - BT
        p[i].RT = p[i].ST - p[i].AT; //RT = ST - AT

        total_TT += p[i].TT;
        total_WT += p[i].WT;
        total_RT += p[i].RT;
    }

    ATT = (float) total_TT / n;
    AWT = (float) total_WT / n;
    ART = (float) total_RT / n;

    sort(p,p+n,compareID);

    cout<<endl;
    cout<<"SL\t"<<"Name\t"<<"AT\t"<<"BT\t"<<"TAT\t"<<"\n"<<endl;

    for(int i = 0; i < n; i++) {
        cout<<p[i].SL<<"\t"<<p[i].Name<<"\t"<<p[i].AT<<"\t"<<p[i].BT<<"\t"<<p[i].TT<<"\t"<<"\n"<<endl;
    }
    cout<<"ATT = "<<ATT<<endl;
    cout<<"AWT = "<<AWT<<endl;
    cout<<"ART = "<<ART<<endl;


}
