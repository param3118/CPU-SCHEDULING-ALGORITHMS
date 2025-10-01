#include <iostream>
#include <vector>
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

void srt(vector<Process>& processes) {
    int n = processes.size();
    int completed = 0, current_time = 0, prev = -1;
    double total_waiting = 0, total_turnaround = 0;

    for (auto& p : processes) {
        p.remaining = p.burst;
        p.start_time = -1;
    }

    vector<pair<int, int>> timeline;

    while (completed < n) {
        int idx = -1;
        int min_remaining = 1e9;
        for (int i = 0; i < n; i++) {
            if (processes[i].arrival <= current_time && processes[i].remaining > 0 && processes[i].remaining < min_remaining) {
                min_remaining = processes[i].remaining;
                idx = i;
            }
        }

        if (idx == -1) { // No process ready
            if(prev != -1) {
                timeline.push_back({-1, current_time});
                prev = -1;
            }
            current_time++;
            continue;
        }

        Process& p = processes[idx];

        if (p.start_time == -1) {
            p.start_time = current_time;
        }

        if (prev != p.id) {
            timeline.push_back({p.id, current_time + 1});
        } else {
            timeline.back().second = current_time + 1;
        }

        prev = p.id;

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

    print_gantt_chart(timeline);

    cout << "\nProcess ID | Arrival Time | Burst Time | Waiting Time | Turnaround Time\n";
    for (const auto& p : processes) {
        cout << "     " << p.id << "     |      " << p.arrival << "      |     " << p.burst << "     |     " << p.waiting << "     |      " << p.turnaround << "\n";
    }

    cout << "\nAverage Waiting Time    : " << (total_waiting / n) << "\n";
    cout << "Average Turnaround Time : " << (total_turnaround / n) << "\n";
}

int main() {
    int n;
    cout << "Enter number of processes: ";
    cin >> n;
    vector<Process> processes(n);

    for (int i = 0; i < n; ++i) {
        processes[i].id = i + 1;
        cout << "Enter arrival time for process " << i + 1 << ": ";
        cin >> processes[i].arrival;
        cout << "Enter burst time for process " << i + 1 << ": ";
        cin >> processes[i].burst;
    }

    srt(processes);
    return 0;
}
