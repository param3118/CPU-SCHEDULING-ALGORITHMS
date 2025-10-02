#include <iostream>
#include <vector>
using namespace std;

struct Process {
    int id, arrival, burst, remaining;
    int start_time, completion_time, waiting, turnaround;
};

int main() {
    int n;
    cin >> n;
    vector<Process> processes(n);
    for (int i = 0; i < n; i++) {
        processes[i].id = i + 1;
        cin >> processes[i].arrival >> processes[i].burst;
        processes[i].remaining = processes[i].burst;
        processes[i].start_time = -1;
    }

    int completed = 0, current_time = 0;
    double total_waiting = 0, total_turnaround = 0;

    while (completed < n) {
        int idx = -1;
        int min_remaining = 1e9;
        for (int i = 0; i < n; i++) {
            if (processes[i].arrival <= current_time && processes[i].remaining > 0 && processes[i].remaining < min_remaining) {
                min_remaining = processes[i].remaining;
                idx = i;
            }
        }

        if (idx == -1) { current_time++; continue; }

        Process &p = processes[idx];
        if (p.start_time == -1) p.start_time = current_time;

        p.remaining--;
        current_time++;

        if (p.remaining == 0) {
            completed++;
            p.completion_time = current_time;
            p.turnaround = p.completion_time - p.arrival;
            p.waiting = p.turnaround - p.burst;
            total_waiting += p.waiting;
            total_turnaround += p.turnaround;
        }
    }

    // Clean JSON output
    cout << "{";
    cout << "\"processes\":[";
    for (int i = 0; i < n; i++) {
        cout << "{";
        cout << "\"id\":" << processes[i].id << ",";
        cout << "\"arrival\":" << processes[i].arrival << ",";
        cout << "\"burst\":" << processes[i].burst << ",";
        cout << "\"waiting\":" << processes[i].waiting << ",";
        cout << "\"turnaround\":" << processes[i].turnaround;
        cout << "}";
        if (i < n-1) cout << ",";
    }
    cout << "],";
    cout << "\"avg_waiting\":" << (total_waiting/n) << ",";
    cout << "\"avg_turnaround\":" << (total_turnaround/n);
    cout << "}";
    return 0;
}
