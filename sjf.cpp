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
    bool completed;
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

void sjf(vector<Process>& processes) {
    int n = processes.size();
    int completed_count = 0, current_time = 0;
    double total_waiting = 0, total_turnaround = 0;

    vector<Process> schedule_order;

    while (completed_count < n) {
        // Find process with shortest burst among arrived and not completed
        int idx = -1;
        int min_burst = 1e9;
        for (int i = 0; i < n; ++i) {
            if (!processes[i].completed && processes[i].arrival <= current_time && processes[i].burst < min_burst) {
                min_burst = processes[i].burst;
                idx = i;
            }
        }

        if (idx == -1) { // no process ready, increment time
            current_time++;
            continue;
        }

        Process& p = processes[idx];
        p.start_time = current_time;
        p.completion_time = current_time + p.burst;
        p.turnaround = p.completion_time - p.arrival;
        p.waiting = p.start_time - p.arrival;
        p.completed = true;

        current_time += p.burst;
        completed_count++;

        schedule_order.push_back(p);

        total_waiting += p.waiting;
        total_turnaround += p.turnaround;
    }

    print_gantt_chart(schedule_order);

    cout << "\nProcess ID | Arrival Time | Burst Time | Waiting Time | Turnaround Time\n";
    for (const auto& p : schedule_order) {
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
        processes[i].completed = false;
    }

    sjf(processes);

    return 0;
}
