#include <iostream>
#include <vector>
#include <string>
#include <algorithm>
#include <iomanip>

using namespace std;

class Task {
public:
    string description;
    string dueDate;
    string priority;
    bool completed;

    Task(string desc, string date, string prio)
        : description(desc), dueDate(date), priority(prio), completed(false) {}
};

class ToDoList {
private:
    vector<Task> tasks;

public:
    void addTask() {
        string description, dueDate, priority;
        cout << "Enter the task description: ";
        cin.ignore();
        getline(cin, description);
        cout << "Enter the due date (YYYY-MM-DD): ";
        getline(cin, dueDate);
        cout << "Enter the priority (Low, Medium, High): ";
        getline(cin, priority);
        tasks.push_back(Task(description, dueDate, priority));
        cout << "Task added successfully!\n";
    }

    void removeTask() {
        string description;
        cout << "Enter the description of the task to remove: ";
        cin.ignore();
        getline(cin, description);

        auto it = find_if(tasks.begin(), tasks.end(), [&](Task &task) {
            return task.description == description;
        });

        if (it != tasks.end()) {
            tasks.erase(it);
            cout << "Task removed successfully!\n";
        } else {
            cout << "Task not found.\n";
        }
    }

    void markTaskCompleted() {
        string description;
        cout << "Enter the description of the task to mark as completed: ";
        cin.ignore();
        getline(cin, description);

        auto it = find_if(tasks.begin(), tasks.end(), [&](Task &task) {
            return task.description == description;
        });

        if (it != tasks.end()) {
            it->completed = true;
            cout << "Task marked as completed!\n";
        } else {
            cout << "Task not found.\n";
        }
    }

    void displayTasks() {
        if (tasks.empty()) {
            cout << "No tasks in the list.\n";
            return;
        }
        cout << setw(40) << left << "Description"
             << setw(15) << "Due Date"
             << setw(10) << "Priority"
             << setw(10) << "Status" << endl;
        cout << string(75, '-') << endl;
        for (const auto &task : tasks) {
            cout << setw(40) << task.description
                 << setw(15) << task.dueDate
                 << setw(10) << task.priority
                 << setw(10) << (task.completed ? "Completed" : "Pending") << endl;
        }
    }

    void clearTasks() {
        tasks.clear();
        cout << "All tasks cleared.\n";
    }

    void searchTask() {
        string keyword;
        cout << "Enter the keyword to search: ";
        cin.ignore();
        getline(cin, keyword);

        bool found = false;
        for (const auto &task : tasks) {
            if (task.description.find(keyword) != string::npos) {
                if (!found) {
                    cout << "Matching tasks:\n";
                    cout << setw(40) << left << "Description"
                         << setw(15) << "Due Date"
                         << setw(10) << "Priority"
                         << setw(10) << "Status" << endl;
                    cout << string(75, '-') << endl;
                }
                cout << setw(40) << task.description
                     << setw(15) << task.dueDate
                     << setw(10) << task.priority
                     << setw(10) << (task.completed ? "Completed" : "Pending") << endl;
                found = true;
            }
        }
        if (!found) {
            cout << "No matching tasks found.\n";
        }
    }

    void sortTasksByPriority() {
        sort(tasks.begin(), tasks.end(), [](const Task &a, const Task &b) {
            if (a.priority == b.priority)
                return a.dueDate < b.dueDate;
            if (a.priority == "High")
                return true;
            if (a.priority == "Medium" && b.priority == "Low")
                return true;
            return false;
        });
        cout << "Tasks sorted by priority.\n";
    }

    void sortTasksByDueDate() {
        sort(tasks.begin(), tasks.end(), [](const Task &a, const Task &b) {
            return a.dueDate < b.dueDate;
        });
        cout << "Tasks sorted by due date.\n";
    }
};

int main() {
    ToDoList toDoList;
    bool continueProgram = true;

    while (continueProgram) {
        int choice;
        cout << "\nTo-Do List Menu:\n";
        cout << "1. Add Task\n";
        cout << "2. Remove Task\n";
        cout << "3. Mark Task as Completed\n";
        cout << "4. Display Tasks\n";
        cout << "5. Clear All Tasks\n";
        cout << "6. Search Task\n";
        cout << "7. Sort Tasks by Priority\n";
        cout << "8. Sort Tasks by Due Date\n";
        cout << "9. Exit\n";
        cout << "Enter your choice: ";
        cin >> choice;

        switch (choice) {
            case 1:
                toDoList.addTask();
                break;
            case 2:
                toDoList.removeTask();
                break;
            case 3:
                toDoList.markTaskCompleted();
                break;
            case 4:
                toDoList.displayTasks();
                break;
            case 5:
                toDoList.clearTasks();
                break;
            case 6:
                toDoList.searchTask();
                break;
            case 7:
                toDoList.sortTasksByPriority();
                break;
            case 8:
                toDoList.sortTasksByDueDate();
                break;
            case 9:
                continueProgram = false;
                break;
            default:
                cout << "Invalid choice. Please try again.\n";
                break;
        }
    }

    cout << "Thank you for using the To-Do List. Goodbye!\n";
    return 0;
}
