#include<bits/stdc++.h>
#define endl '\n'
using namespace std;

class Process {
public:
    int pid;           
    int at;    
    int bt;      
    int wt;    
    int tt; 
    int ct; 
    bool done;     

    Process(int at, int bt, int id) {
        pid = id;
        this->at = at;
        this->bt = bt;
        wt = 0;
        tt = 0;
        ct = 0;
        done = false;
    }
};

int main(){
    int n,id,at,bt;
    int time = 0;
    vector <Process> p;

    cin >> n;

    for (int i=0; i<n; i++){
        cin>>id;
        cin>>at;
        cin>>bt;
        p.push_back(Process(at,bt,id));
    }

    int completed = 0;
    
    while(completed < n) {
        int idx = -1;
        int minBT = INT_MAX;
        
        for(int i = 0; i < n; i++) {
            if(!p[i].done && p[i].at <= time && p[i].bt < minBT) {
                minBT = p[i].bt;
                idx = i;
            }
        }
        
        if(idx == -1) {
            time++;
        } else {
            time += p[idx].bt;
            p[idx].ct = time;
            p[idx].tt = p[idx].ct - p[idx].at;
            p[idx].wt = p[idx].tt - p[idx].bt;
            p[idx].done = true;
            completed++;
        }
    }

    int avgwt=0,avgtat=0;
    cout << endl << "PID\tAT\tBT\tCT\tTT\tWT\n";
    for(int i=0; i<n; i++){
        cout << p[i].pid << "\t" << p[i].at << "\t" << p[i].bt << "\t" << p[i].ct << "\t" << p[i].tt << "\t" << p[i].wt << "\n";
        avgwt += p[i].wt;
        avgtat += p[i].tt;
    }

    cout << "Average Waiting Time: " << (float)avgwt/n << "\n";
    cout << "Average Turnaround Time: " << (float)avgtat/n << "\n";
}

/*
5
0 2 2
1 1 5
2 4 1
3 0 6
4 2 3
*/