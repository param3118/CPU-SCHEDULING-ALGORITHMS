# CPU Scheduling Algorithms in C++

A comprehensive implementation of various Operating System CPU scheduling algorithms in C++. This project provides complete, working implementations of major scheduling techniques used in operating systems.

## 📋 Table of Contents
- [Algorithms Implemented](#algorithms-implemented)
- [Features](#features)
- [Getting Started](#getting-started)
- [Usage](#usage)
- [Input Format](#input-format)
- [Sample Output](#sample-output)
- [Project Structure](#project-structure)
- [Contributing](#contributing)
- [License](#license)

## 🔧 Algorithms Implemented

### 1. **First Come First Serve (FCFS)**
- **Type**: Non-preemptive
- **File**: `fcfs.cpp`
- **Description**: Processes are executed in the order they arrive

### 2. **Shortest Job First (SJF)**
- **Type**: Non-preemptive
- **File**: `sjf.cpp`
- **Description**: Selects the process with the shortest burst time among arrived processes

### 3. **Round Robin (RR)**
- **Type**: Preemptive
- **File**: `rr.cpp`
- **Description**: Uses time quantum for fair CPU sharing among processes

### 4. **Shortest Remaining Time (SRT)**
- **Type**: Preemptive
- **File**: `srt.cpp`
- **Description**: Preemptive version of SJF, switches to process with shortest remaining time

### 5. **Priority Scheduling**
- **Type**: Non-preemptive
- **File**: `priority.cpp`
- **Description**: Executes processes based on priority (lower number = higher priority)

### 6. **Highest Response Ratio Next (HRRN)**
- **Type**: Non-preemptive
- **File**: `hrrn.cpp`
- **Description**: Selects process with highest response ratio: (waiting time + burst time) / burst time

## ✨ Features

- **Complete Implementation**: All major CPU scheduling algorithms
- **Visual Output**: Text-based Gantt charts for execution visualization
- **Performance Metrics**: Calculates average waiting time and turnaround time
- **User-Friendly**: Interactive console input for process details
- **STL Usage**: Leverages C++ Standard Template Library without std:: prefix
- **Cross-Platform**: Works on Windows (MSYS/MinGW, WSL) and Linux

## 🚀 Getting Started

### Prerequisites
- C++ compiler (g++, clang++, or equivalent)
- Make (optional)

### Installation

1. Clone the repository:

git clone https://github.com/yourusername/CPU-Scheduling-Algorithms-CPP.git
cd CPU-Scheduling-Algorithms-CPP

2. Compile any algorithm:

g++ fcfs.cpp -o fcfs
g++ sjf.cpp -o sjf
g++ rr.cpp -o rr
g++ srt.cpp -o srt
g++ priority.cpp -o priority
g++ hrrn.cpp -o hrrn

3. Run the executable:

./fcfs        # On Linux/Mac
fcfs.exe      # On Windows

## 📖 Usage

Each program follows the same input pattern:

1. **Number of processes**
2. **For each process**:
   - Arrival time
   - Burst time
   - Priority (for Priority Scheduling only)
3. **Time quantum** (for Round Robin only)

### Example Usage:

$ ./fcfs
Enter number of processes: 3
Enter arrival time for process 1: 0
Enter burst time for process 1: 5
Enter arrival time for process 2: 2
Enter burst time for process 2: 3
Enter arrival time for process 3: 4
Enter burst time for process 3: 1

## 📊 Input Format

### Standard Input (FCFS, SJF, SRT, HRRN):
Number of processes: n
Process 1: arrival_time burst_time
Process 2: arrival_time burst_time
...
Process n: arrival_time burst_time

### Priority Scheduling:
Number of processes: n
Process 1: arrival_time burst_time priority
Process 2: arrival_time burst_time priority
...
Process n: arrival_time burst_time priority

### Round Robin:
Number of processes: n
Process 1: arrival_time burst_time
Process 2: arrival_time burst_time
...
Process n: arrival_time burst_time
Time quantum: quantum_value

## 📈 Sample Output

Gantt Chart:
| P1 | P3 | P2 |
0    5    6    9

Process ID | Arrival Time | Burst Time | Waiting Time | Turnaround Time
     1     |      0      |     5     |     0     |      5
     3     |      4      |     1     |     1     |      2
     2     |      2      |     3     |     4     |      7

Average Waiting Time    : 1.67
Average Turnaround Time : 4.67

## 📁 Project Structure

CPU-Scheduling-Algorithms-CPP/
│
├── fcfs.cpp           # First Come First Serve implementation
├── sjf.cpp            # Shortest Job First implementation
├── rr.cpp             # Round Robin implementation
├── srt.cpp            # Shortest Remaining Time implementation
├── priority.cpp       # Priority Scheduling implementation
├── hrrn.cpp           # Highest Response Ratio Next implementation
├── README.md          # Project documentation
├── LICENSE            # License file
└── .gitignore         # Git ignore file

## 🤝 Contributing

Contributions are welcome! Here's how you can help:

1. Fork the repository
2. Create your feature branch (`git checkout -b feature/AmazingFeature`)
3. Commit your changes (`git commit -m 'Add some AmazingFeature'`)
4. Push to the branch (`git push origin feature/AmazingFeature`)
5. Open a Pull Request

### Future Enhancements:
- [ ] Multilevel Queue Scheduling
- [ ] Multilevel Feedback Queue
- [ ] Aging mechanism
- [ ] Preemptive Priority Scheduling
- [ ] GUI interface
- [ ] File input support
- [ ] Performance comparison tools

## 📄 License

This project is licensed under the MIT License - see the [LICENSE](LICENSE) file for details.

## 🏷️ Tags

`cpp` `operating-systems` `scheduling-algorithms` `computer-science` `algorithms` `data-structures` `system-programming` `educational`

***

**Made with ❤️ for learning Operating Systems concepts**