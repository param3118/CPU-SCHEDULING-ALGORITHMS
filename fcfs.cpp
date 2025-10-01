#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

struct Process {
    int id;
    int arrival;
    int burst;
    int start_time;
    int completion_time;
    int waiting;
    int turnaround;
};

void print_gantt_chart(const vector<Process>& processes) {
    cout << "\nGantt Chart:\n";
    cout << "|";
    for (const auto& p : processes) {
        cout << " P" << p.id << " |";
    }
    cout << "\n";

    cout << processes[0].start_time;
    for (const auto& p : processes) {
        cout << "    " << p.completion_time;
    }
    cout << "\n";
}

void fcfs(vector<Process>& processes) {
    // Sort by arrival time
    sort(processes.begin(), processes.end(), [](const Process& a, const Process& b) {
        return a.arrival < b.arrival;
    });

    int current_time = 0;
    for (auto& p : processes) {
        if (current_time < p.arrival) {
            current_time = p.arrival;
        }
        p.start_time = current_time;
        p.completion_time = current_time + p.burst;
        p.turnaround = p.completion_time - p.arrival;
        p.waiting = p.start_time - p.arrival;
        current_time += p.burst;
    }

    print_gantt_chart(processes);

    double total_waiting = 0, total_turnaround = 0;
    cout << "\nProcess ID | Arrival Time | Burst Time | Waiting Time | Turnaround Time\n";
    for (const auto& p : processes) {
        cout << "     " << p.id << "     |      " << p.arrival << "      |     " << p.burst << "     |     " << p.waiting << "     |      " << p.turnaround << "\n";
        total_waiting += p.waiting;
        total_turnaround += p.turnaround;
    }

    int n = processes.size();
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

    fcfs(processes);

    return 0;
}
