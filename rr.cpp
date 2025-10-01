#include <iostream>
#include <vector>
#include <queue>
#include <algorithm>

using namespace std;

struct Process {
    int id;
    int arrival;
    int burst;
    int remaining;
    int start_time;
    int completion_time;
    int waiting;
    int turnaround;
};

void print_gantt_chart(const vector<pair<int, int>>& timeline) {
    // timeline is pairs of (process_id, end_time) segments
    cout << "\nGantt Chart:\n|";
    for (const auto& segment : timeline) {
        if (segment.first == -1) {
            cout << " Idle |";
        } else {
            cout << " P" << segment.first << " |";
        }
    }
    cout << "\n";
    for (const auto& segment : timeline) {
        cout << segment.second << "    ";
    }
    cout << "\n";
}

void round_robin(vector<Process>& processes, int quantum) {
    int n = processes.size();
    queue<int> q;
    vector<bool> in_queue(n, false);
    int current_time = 0;
    int completed = 0;

    vector<pair<int, int>> timeline; // Stores process id and time when segment ends

    // Sort processes by arrival
    sort(processes.begin(), processes.end(), [](const Process& a, const Process& b){
        return a.arrival < b.arrival;
    });

    int idx = 0; // index to track processes arrived
    q.push(processes[0].id);
    in_queue[0] = true;
    current_time = processes[0].arrival;

    while(completed < n) {
        if(q.empty()) {
            timeline.push_back({-1, current_time}); // Idle
            if(idx < n && processes[idx].arrival > current_time) {
                current_time = processes[idx].arrival;
            } else {
                break;
            }
            continue;
        }

        int pid = q.front();
        q.pop();
        Process &p = processes[pid-1];

        if(p.remaining == p.burst) {
            p.start_time = max(current_time, p.arrival);
            if(current_time < p.arrival) {
                timeline.push_back({-1, p.arrival}); // Idle
                current_time = p.arrival;
            }
        }

        int exec_time = min(quantum, p.remaining);

        timeline.push_back({pid, current_time + exec_time});
        p.remaining -= exec_time;
        current_time += exec_time;

        // Check arrival of new processes
        while(idx < n && processes[idx].arrival <= current_time) {
            if(!in_queue[idx] && processes[idx].remaining > 0) {
                q.push(processes[idx].id);
                in_queue[idx] = true;
            }
            idx++;
        }

        if(p.remaining > 0) {
            q.push(pid);
        } else {
            p.completion_time = current_time;
            p.turnaround = p.completion_time - p.arrival;
            p.waiting = p.turnaround - p.burst;
            completed++;
        }

    }

    print_gantt_chart(timeline);

    cout << "\nProcess ID | Arrival Time | Burst Time | Waiting Time | Turnaround Time\n";
    double total_waiting = 0, total_turnaround = 0;
    for(const auto& p : processes) {
        cout << "     " << p.id << "     |      " << p.arrival << "      |     " << p.burst << "     |     " << p.waiting << "     |      " << p.turnaround << "\n";
        total_waiting += p.waiting;
        total_turnaround += p.turnaround;
    }

    cout << "\nAverage Waiting Time    : " << (total_waiting / n) << "\n";
    cout << "Average Turnaround Time : " << (total_turnaround / n) << "\n";
}

int main() {
    int n, quantum;
    cout << "Enter number of processes: ";
    cin >> n;
    vector<Process> processes(n);

    for(int i=0; i<n; i++) {
        processes[i].id = i+1;
        cout << "Enter arrival time for process " << i+1 << ": ";
        cin >> processes[i].arrival;
        cout << "Enter burst time for process " << i+1 << ": ";
        cin >> processes[i].burst;
        processes[i].remaining = processes[i].burst;
    }

    cout << "Enter time quantum: ";
    cin >> quantum;

    round_robin(processes, quantum);

    return 0;
}
