#include <iostream>
#include <queue>
#include <thread> // Include this for std::this_thread
#include <chrono> // Include this for std::chrono

using namespace std;

struct Process {
    int id;         // Process ID
    int burstTime;  // CPU burst time
    int priority;   // Priority level (1 = high, 2 = medium, 3 = low)
};

// Function to execute a process
void executeProcess(Process p) {
    cout << "Executing Process ID: " << p.id << " with Burst Time: " << p.burstTime << "ms" << endl;
    this_thread::sleep_for(chrono::milliseconds(p.burstTime * 100)); // Simulate execution
}

// Multiple Level Queue Scheduler
class MLFQScheduler {
private:
    queue<Process> highPriorityQueue;
    queue<Process> mediumPriorityQueue;
    queue<Process> lowPriorityQueue;

public:
    void addProcess(Process p) {
        switch (p.priority) {
            case 1:
                highPriorityQueue.push(p);
                break;
            case 2:
                mediumPriorityQueue.push(p);
                break;
            case 3:
                lowPriorityQueue.push(p);
                break;
            default:
                cout << "Invalid priority for Process ID: " << p.id << endl;
                break; // Added break for clarity
        }
    }

    void schedule() {
        // High Priority Queue
        while (!highPriorityQueue.empty()) {
            Process p = highPriorityQueue.front();
            highPriorityQueue.pop();
            executeProcess(p);
        }

        // Medium Priority Queue
        while (!mediumPriorityQueue.empty()) {
            Process p = mediumPriorityQueue.front();
            mediumPriorityQueue.pop();
            executeProcess(p);
        }

        // Low Priority Queue
        while (!lowPriorityQueue.empty()) {
            Process p = lowPriorityQueue.front();
            lowPriorityQueue.pop();
            executeProcess(p);
        }
    }
};

int main() {
    MLFQScheduler scheduler;
    int numProcesses;

    // Ask the user for the number of processes
    cout << "Enter the number of processes: ";
    cin >> numProcesses;

    // Validate user input for number of processes
    if (numProcesses <= 0) {
        cout << "Invalid number of processes. Exiting." << endl;
        return 1; // Exit with error code
    }

    for (int i = 0; i < numProcesses; ++i) {
        Process p;
        cout << "Enter details for Process " << (i + 1) << ":\n";
        
        cout << "Process ID: ";
        cin >> p.id;

        cout << "Burst Time (ms): ";
        cin >> p.burstTime;

        // Validate burst time
        while (p.burstTime <= 0) {
            cout << "Invalid Burst Time. Please enter a positive value: ";
            cin >> p.burstTime;
        }

        cout << "Priority (1 = High, 2 = Medium, 3 = Low): ";
        cin >> p.priority;

        // Validate priority
        while (p.priority < 1 || p.priority > 3) {
            cout << "Invalid Priority. Please enter a value between 1 and 3: ";
            cin >> p.priority;
        }

        // Add the process to the scheduler
        scheduler.addProcess(p);
    }

    // Start scheduling
    scheduler.schedule();

    return 0;
}
