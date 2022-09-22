#include <iostream>
#include <algorithm>
#include <string.h>
#include <queue>
using namespace std;

struct process {
    int SL,AT,BT,ST,CT,TT,WT,RT;
    char Name;
}p[100];

bool sortBy_ArrivalTime(process p1, process p2)
{
    return p1.AT < p2.AT;
}

bool sortby_SerialNumber(process p1, process p2)
{
    return p1.SL < p2.SL;
}

int main() {

    int n, tq ,id, BT[100];
    int total_TT = 0;
    int total_WT = 0;
    int total_RT = 0;

    float ATT,AWT,ART;

    cout<<"Time quantum: ";
    cin>>tq;
    cout<<"Number of process: ";
    cin>>n;

    for(int i = 0; i < n; i++) {
        cin>>p[i].SL;
        cin>>p[i].Name;
        cin>>p[i].AT;
        cin>>p[i].BT;
        BT[i] = p[i].BT;
    }

    sort(p,p+n,sortBy_ArrivalTime);

    queue<int> q;
    int current_time = 0;
    q.push(0);
    int completed = 0;
    int is_completed[100];
    memset(is_completed,0,sizeof(is_completed));
    is_completed[0] = 1;

    while(completed != n) {
        id = q.front();
        q.pop();

        if(BT[id] == p[id].BT) {
            p[id].ST = max(current_time,p[id].AT);
            current_time = p[id].ST;
        }

        if(BT[id]-tq > 0) {
            BT[id] -= tq;
            current_time += tq;
        }
        else {
            current_time += BT[id];
            BT[id] = 0;
            completed++;

            p[id].CT = current_time;
            p[id].TT = p[id].CT - p[id].AT;
            p[id].WT = p[id].TT - p[id].BT;
            p[id].RT = p[id].ST - p[id].AT;

            total_TT += p[id].TT;
            total_WT += p[id].WT;
            total_RT += p[id].RT;
        }
        for(int i = 1; i < n; i++) {
            if(BT[i] > 0 && p[i].AT <= current_time && is_completed[i] == 0) {
                q.push(i);
                is_completed[i] = 1;
            }
        }
        if(BT[id] > 0) {
            q.push(id);
        }
        if(q.empty()) {
            for(int i = 1; i < n; i++) {
                if(BT[i] > 0) {
                    q.push(i);
                    is_completed[i] = 1;
                    break;
                }
            }
        }
    }

    ATT = (float) total_TT / n;
    AWT = (float) total_WT / n;
    ART = (float) total_RT / n;

    sort(p,p+n,sortby_SerialNumber);

    cout<<endl;
    cout<<"SL\t"<<"Name\t"<<"AT\t"<<"BT\t"<<"TAT\t"<<"\n"<<endl;

    for(int i = 0; i < n; i++) {
        cout<<p[i].SL<<"\t"<<p[i].Name<<"\t"<<p[i].AT<<"\t"<<p[i].BT<<"\t"<<p[i].TT<<"\t"<<"\n"<<endl;
    }
    cout<<"ATT = "<<ATT<<endl;
    cout<<"AWT = "<<AWT<<endl;
    cout<<"ART = "<<ART<<endl;


}
