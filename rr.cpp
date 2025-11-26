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
        this->rbt = bt;  
        wt = 0;
        tt = 0;
        ct = 0;
        done = false;
    }
};

int main(){
    int n,id,at,bt,tq;
    int time = 0;
    vector <Process> p;

    cin >> n;
    cin >> tq;  // Time Quantum

    for (int i=0; i<n; i++){
        cin>>id;
        cin>>at;
        cin>>bt;
        p.push_back(Process(at,bt,id));
    }

    queue<int> readyQueue;
    int completed = 0;
    vector<bool> inQueue(n, false);
    
    // Add processes that have arrived at time 0
    for(int i = 0; i < n; i++) {
        if(p[i].at <= time) {
            readyQueue.push(i);
            inQueue[i] = true;
        }
    }
    
    while(completed < n) {
        if(readyQueue.empty()) {
            // No process in queue, advance time to next arrival
            time++;
            for(int i = 0; i < n; i++) {
                if(!p[i].done && !inQueue[i] && p[i].at <= time) {
                    readyQueue.push(i);
                    inQueue[i] = true;
                }
            }
            continue;
        }
        
        int idx = readyQueue.front();
        readyQueue.pop();
        
        // Execute for time quantum or remaining burst time, whichever is smaller
        int execTime = min(tq, p[idx].rbt);
        p[idx].rbt -= execTime;
        time += execTime;
        
        // Add newly arrived processes to queue
        for(int i = 0; i < n; i++) {
            if(!p[i].done && !inQueue[i] && p[i].at <= time) {
                readyQueue.push(i);
                inQueue[i] = true;
            }
        }
        
        // If process completes
        if(p[idx].rbt == 0) {
            p[idx].ct = time;
            p[idx].tt = p[idx].ct - p[idx].at;
            p[idx].wt = p[idx].tt - p[idx].bt;
            p[idx].done = true;
            completed++;
        } else {
            // Process not complete, add back to queue
            readyQueue.push(idx);
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