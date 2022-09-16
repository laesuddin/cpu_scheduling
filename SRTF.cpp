#include <iostream>
#include <algorithm>
#include <string.h>
using namespace std;

struct process {
    int SL,AT,BT,ST,CT,TT,WT,RT;
    char Name;
}p[20];

int main() {

    int n;
    float ATT;
    float AWT;
    float ART;
    int total_TT = 0;
    int total_WT = 0;
    int total_RT = 0;
    int is_completed[100];
    memset(is_completed,0,sizeof(is_completed));



    cout<<"Input: n=";
    cin>>n;

    for(int i = 0; i < n; i++) {
        cin>>p[i].SL;
        cin>>p[i].Name;
        cin>>p[i].AT;
        cin>>p[i].BT;

    }

    int completion_time = 0;
    int completed = 0;
    int start = 0;

    while(completed != n) {
        int id = -1;
        int minimum = 100;
        for(int i = 0; i < n; i++){  //finding the minimum burst time process
            if(p[i].AT <= completion_time && is_completed[i] == 0) {
                if(p[i].BT < minimum) {
                    minimum = p[i].BT;
                    id = i;
                }
                if(p[i].BT == minimum) { // if two process burst time equal compare which process Arrival time less
                    if(p[i].AT < p[id].AT) {
                        minimum = p[i].BT;
                        id = i;
                    }
                }
            }
        }

        if(id != -1) {
            p[id].ST = completion_time;
            p[id].CT = p[id].ST + p[id].BT;
            p[id].TT = p[id].CT - p[id].AT;
            p[id].WT = p[id].TT - p[id].BT;
            p[id].RT = p[id].ST - p[id].AT;

            total_TT += p[id].TT;
            total_WT += p[id].WT;
            total_RT += p[id].RT;

            is_completed[id] = 1;
            completed++;
            completion_time = p[id].CT;
            start = completion_time;
        }
        else {
            completion_time++;
        }

}



    ATT = (float) total_TT / n;
    AWT = (float) total_WT / n;
    ART = (float) total_RT / n;

    cout<<endl;
    cout<<"SL\t"<<"Name\t"<<"AT\t"<<"BT\t"<<"TAT\t"<<"\n"<<endl;

    for(int i = 0; i < n; i++) {
        cout<<p[i].SL<<"\t"<<p[i].Name<<"\t"<<p[i].AT<<"\t"<<p[i].BT<<"\t"<<p[i].TT<<"\t"<<"\n"<<endl;
    }
    cout<<"ATT = "<<ATT<<endl;
    cout<<"AWT = "<<AWT<<endl;
    cout<<"ART = "<<ART<<endl;

}
