#include <iostream>
#include <string.h>
using namespace std;

struct process {
    int serial,Arribal_T,Brust_T,Piority_T,ST,CT,TT,WT,RT;
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
        p[i].Piority_T=p[i].Arribal_T-((p[i].Brust_T)*0.25);
        cin>>p[i].serial;
        cin>>p[i].Name;
        cin>>p[i].Arribal_T;
        cin>>p[i].Brust_T;

    }

    int completion_time = 0;
    int completed = 0;
    int start = 0;

    while(completed != n) {
        int id = -1;
        int mx = -1;
        for(int i = 0; i < n; i++){
            if(p[i].Arribal_T <= completion_time && is_completed[i] == 0) {
                if(p[i].Piority_T > mx) {
                    mx = p[i].Piority_T;
                    id = i;
                }
                if(p[i].Piority_T == mx) {
                    if(p[i].Arribal_T < p[id].Arribal_T) {
                        mx = p[i].Piority_T;
                        id = i;
                    }
                }
            }
        }

        if(id != -1) {
            p[id].ST = completion_time;
            p[id].CT = p[id].ST + p[id].Brust_T;
            p[id].TT = p[id].CT - p[id].Arribal_T;
            p[id].WT = p[id].TT - p[id].Brust_T;
            p[id].RT = p[id].ST - p[id].Arribal_T;

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
        cout<<p[i].serial<<"\t"<<p[i].Name<<"\t"<<p[i].Arribal_T<<"\t"<<p[i].Brust_T<<"\t"<<p[i].TT<<"\t"<<"\n"<<endl;
    }
    cout<<"ATT = "<<ATT<<endl;
    cout<<"AWT = "<<AWT<<endl;
    cout<<"ART = "<<ART<<endl;

}
