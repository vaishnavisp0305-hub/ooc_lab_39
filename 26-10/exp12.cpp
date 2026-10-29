#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <string>
using namespace std;

// 1. Class and 2. Encapsulation
class Student {
private:
    int id;
    string name;
    float marks;

public:
    // 3. Constructor
    Student(int i = 0, string n = "", float m = 0)
        : id(i), name(n), marks(m) {}

    int getId() const {
        return id;
    }

    string getName() const {
        return name;
    }

    float getMarks() const {
        return marks;
    }

    // 5. Polymorphism: Function overloading
    virtual void display() const {
        cout << "ID: " << id
             << ", Name: " << name
             << ", Marks: " << marks << endl;
    }

    void display(string heading) const {
        cout << heading << endl;
        display();
    }
};

// 4. Inheritance
class Result : public Student {
public:
    Result(int i = 0, string n = "", float m = 0)
        : Student(i, n, m) {}

    void display() const override {
        Student::display();
        cout << "Grade: ";

        if (getMarks() >= 90)
            cout << "A";
        else if (getMarks() >= 75)
            cout << "B";
        else if (getMarks() >= 50)
            cout << "C";
        else
            cout << "Fail";

        cout << endl;
    }
};

// 6. File Handling
void saveRecords(const vector<Result>& students) {
    ofstream file("students.txt");

    for (const Result& s : students) {
        file << s.getId() << "|"
             << s.getName() << "|"
             << s.getMarks() << endl;
    }

    file.close();
    cout << "Records saved successfully!\n";
}

void loadRecords(vector<Result>& students) {
    ifstream file("students.txt");
    string line;

    while (getline(file, line)) {
        stringstream ss(line);
        string id, name, marks;

        if (getline(ss, id, '|') &&
            getline(ss, name, '|') &&
            getline(ss, marks)) {
            students.emplace_back(
                stoi(id), name, stof(marks));
        }
    }

    file.close();
}

int main() {
    vector<Result> students;
    loadRecords(students);

    int choice;

    do {
        cout << "\n--- STUDENT MANAGEMENT SYSTEM ---\n";
        cout << "1. Add Student\n";
        cout << "2. Display All Students\n";
        cout << "3. Search Student\n";
        cout << "4. Calculate Result\n";
        cout << "5. Save Records\n";
        cout << "6. Exit\n";
        cout << "Enter choice: ";
        cin >> choice;

        if (choice == 1) {
            int id;
            string name;
            float marks;

            cout << "Enter student ID: ";
            cin >> id;

            bool exists = false;
            for (const Result& s : students) {
                if (s.getId() == id) {
                    exists = true;
                    break;
                }
            }

            if (exists) {
                cout << "Student ID already exists!\n";
                continue;
            }

            cout << "Enter student name: ";
            getline(cin >> ws, name);

            cout << "Enter marks (0-100): ";
            cin >> marks;

            if (cin.fail() || marks < 0 || marks > 100) {
                cout << "Invalid marks!\n";
                cin.clear();
                cin.ignore(10000, '\n');
                continue;
            }

            students.emplace_back(id, name, marks);
            cout << "Student added successfully!\n";
            saveRecords(students);
        }

        else if (choice == 2) {
            if (students.empty()) {
                cout << "No student records found.\n";
            } else {
                for (const Result& s : students)
                    s.display();
            }
        }

        else if (choice == 3) {
            int id;
            cout << "Enter student ID to search: ";
            cin >> id;

            bool found = false;

            for (const Result& s : students) {
                if (s.getId() == id) {
                    s.display("Student Found:");
                    found = true;
                    break;
                }
            }

            if (!found)
                cout << "Student not found.\n";
        }

        else if (choice == 4) {
            for (const Result& s : students)
                s.display();
        }

        else if (choice == 5) {
            saveRecords(students);
        }

        else if (choice == 6) {
            saveRecords(students);
            cout << "Exiting program. Goodbye!\n";
        }

        else {
            cout << "Invalid choice!\n";
        }

    } while (choice != 6);

    return 0;
}
