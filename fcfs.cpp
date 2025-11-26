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

    sort(p.begin(), p.end(), [](const Process& a, const Process& b) {
        return a.at < b.at;
    });

    for(int i=0; i<n; i++){

        // CPU waits if process arrives later
        if (time < p[i].at) time = p[i].at;

        // Process executes
        time += p[i].bt;
        p[i].ct = time;
        p[i].tt = p[i].ct - p[i].at;
        p[i].wt = p[i].tt - p[i].bt;
        p[i].done=true;
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
0 8 5
1 6 3
2 1 7
3 5 2
4 0 5
*/