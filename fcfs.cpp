#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

struct Process {
    int id, at, bt, st, ct, wt, tat;
};

int main() {
    int n; cin >> n;
    vector<Process> p(n);
    for (int i = 0; i < n; i++) {
        cin >> p[i].at >> p[i].bt;
        p[i].id = i + 1;
    }

    sort(p.begin(), p.end(), [](Process a, Process b){ return a.at < b.at; });

    int time = 0;
    double totalWT = 0, totalTAT = 0;

    for (int i = 0; i < n; i++) {
        if (time < p[i].at) time = p[i].at;
        p[i].st = time;
        p[i].ct = time + p[i].bt;
        p[i].tat = p[i].ct - p[i].at;
        p[i].wt = p[i].tat - p[i].bt;

        totalWT += p[i].wt;
        totalTAT += p[i].tat;
        time = p[i].ct;
    }

    //  Output JSON
    cout << "{";
    cout << "\"processes\":[";
    for (int i = 0; i < n; i++) {
        cout << "{";
        cout << "\"id\":" << p[i].id << ",";
        cout << "\"arrival\":" << p[i].at << ",";
        cout << "\"burst\":" << p[i].bt << ",";
        cout << "\"start\":" << p[i].st << ",";
        cout << "\"completion\":" << p[i].ct << ",";
        cout << "\"waiting\":" << p[i].wt << ",";
        cout << "\"turnaround\":" << p[i].tat;
        cout << "}";
        if (i < n-1) cout << ",";
    }
    cout << "],";
    cout << "\"avg_waiting\":" << (totalWT/n) << ",";
    cout << "\"avg_turnaround\":" << (totalTAT/n);
    cout << "}";
    return 0;
}
