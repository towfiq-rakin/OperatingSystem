#include<bits/stdc++.h>
#define endl '\n'
using namespace std;

class Process {
public:
    int pid;           
    int at;    
    int bt;
    int rbt;   // remaining burst time
    int wt;    
    int tt; 
    int ct; 
    bool done;     

    Process(int at, int bt, int id) {
        pid = id;
        this->at = at;
        this->bt = bt;
        this->rbt = bt;  // initially remaining time = burst time
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
        int minRBT = INT_MAX;
        
        // Find process with shortest remaining burst time among arrived processes
        for(int i = 0; i < n; i++) {
            if(!p[i].done && p[i].at <= time && p[i].rbt < minRBT) {
                minRBT = p[i].rbt;
                idx = i;
            }
        }
        
        if(idx == -1) {
            // No process available, CPU idle
            time++;
        } else {
            // Execute the process for 1 time unit (preemption)
            p[idx].rbt--;
            time++;
            
            // If process completes
            if(p[idx].rbt == 0) {
                p[idx].ct = time;
                p[idx].tt = p[idx].ct - p[idx].at;
                p[idx].wt = p[idx].tt - p[idx].bt;
                p[idx].done = true;
                completed++;
            }
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