#include<bits/stdc++.h>
#define endl '\n'
using namespace std;

class Process {
public:
    int pid;           
    int at;    
    int bt;
    int pr;    // priority (lower value = higher priority)
    int wt;    
    int tt; 
    int ct; 
    bool done;     

    Process(int id, int at, int bt, int pr) {
        pid = id;
        this->at = at;
        this->bt = bt;
        this->pr = pr;
        wt = 0;
        tt = 0;
        ct = 0;
        done = false;
    }
};

int main(){
    int n,id,at,bt,pr;
    int time = 0;
    vector <Process> p;

    cin >> n;

    for (int i=0; i<n; i++){
        cin>>id;
        cin>>at;
        cin>>bt;
        cin>>pr;
        p.push_back(Process(id,at,bt,pr));
    }

    int completed = 0;
    
    while(completed < n) {
        int idx = -1;
        int minPr = INT_MAX;
        
        // Find process with highest priority (lowest priority number) among arrived processes
        for(int i = 0; i < n; i++) {
            if(!p[i].done && p[i].at <= time) {
                if(p[i].pr < minPr || (p[i].pr == minPr && p[i].at < p[idx].at)) {
                    minPr = p[i].pr;
                    idx = i;
                }
            }
        }
        
        if(idx == -1) {
            // No process available, CPU idle
            time++;
        } else {
            // Execute the highest priority process
            time += p[idx].bt;
            p[idx].ct = time;
            p[idx].tt = p[idx].ct - p[idx].at;
            p[idx].wt = p[idx].tt - p[idx].bt;
            p[idx].done = true;
            completed++;
        }
    }

    int avgwt=0,avgtat=0;
    cout << endl << "PID\tAT\tBT\tPR\tCT\tTT\tWT\n";
    for(int i=0; i<n; i++){
        cout << p[i].pid << "\t" << p[i].at << "\t" << p[i].bt << "\t" << p[i].pr << "\t" << p[i].ct << "\t" << p[i].tt << "\t" << p[i].wt << "\n";
        avgwt += p[i].wt;
        avgtat += p[i].tt;
    }

    cout << "Average Waiting Time: " << (float)avgwt/n << "\n";
    cout << "Average Turnaround Time: " << (float)avgtat/n << "\n";
}

/*
5
0 0 4 2
1 1 3 3
2 2 1 4
3 3 5 5
4 4 2 1
*/