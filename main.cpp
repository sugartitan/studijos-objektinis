#include <string>
#include <vector>
#include <fstream>
#include <iostream>
#include <sstream>
#include <iomanip>
#include <algorithm>

struct Student {
    std::string name, last_name;
    std::vector<int> grades;
    int egzam_grade;
};

int CountWords(std::string str) {
    int count = 0;
    std::stringstream ss(str);
    std::string word;
    while(ss >> word) { ++count;}
    return count;
}

void ReadDataFromConsole(std::vector<Student>& students) {
    std::string name, last_name, str;
    int index = 1, grade, egzam_grade;
    char add_another;

    while (true) {
        Student s;
        std::cout << "Enter student's Name: ";
        std::cin >> s.name;
        std::cout << "Last name: ";
        std::cin >> s.last_name;

        std::cout << "Enter as many student's homework grades as you like. Press ENTER twice to finish." << std::endl;

        std::cin.ignore();

        while (getline(std::cin, str) and !str.empty()) {
            std::stringstream ss(str);
            while (ss >> grade)
                s.grades.push_back(grade);
        }

        std::cout << "Enter student's egzam grade: ";
        std::cin >> s.egzam_grade;

        students.push_back(s);

        std::cout << "\nDo you wish to add another student? (y/n): ";
        std::cin >> add_another;

        if (add_another == 'n') {
            break;
        }
    }
}

void ReadDataFromFile(std::vector<Student>& students, std::string filePath) {
    std::ifstream file(filePath);
    std::string my_string, token;
    int pos = 0, grade;
    
    if (file.is_open()) {
        getline(file, my_string);
        int count = CountWords(my_string);

        while (getline(file, my_string)) {
            std::stringstream ss(my_string);
            Student student;
            ss >> student.name >> student.last_name;
            for (int i = 0; i < count - 3; i++) {
                ss >> grade;
                student.grades.push_back(grade);
            }
            ss >> student.egzam_grade;

            students.push_back(student);
        }
    }
}

double Mean(std::vector<int> grades) {
    double sum = 0;
    for (int grade : grades) {
        sum += grade;
    }

    return sum / grades.size();
}

double Median(std::vector<int> grades) {
    std::vector<int> v_sorted(grades.size());
    std::partial_sort_copy(begin(grades), end(grades), begin(v_sorted), end(v_sorted));

    if (v_sorted.size() % 2 == 0) {
        return (v_sorted[v_sorted.size() / 2] + v_sorted[v_sorted.size() / 2 - 1]) / 2;
    }
    return v_sorted[v_sorted.size() / 2];
}

void PrintStudentsResults(std::vector<Student> students, bool if_mean) {
    double sum = 0, value;
    std::string func_str = "Final grade ";

    if (if_mean) { 
        func_str += "(mean)";
    }
    else {
        func_str += "(median)";
    }

    std::cout << std::left << std::setw(20) << "Name" << std::setw(20) << "Last name" << std::right << std::setw(20) << func_str << std::endl;
    std::cout << std::string(60, '-') << std::endl;

    for (Student s : students) {
        std::cout << std::left << std::setw(20) << s.name << std::setw(20) << s.last_name;

        if (if_mean) {
            value = Mean(s.grades);
        }
        else {
            value = Median(s.grades);
        }

        std::cout << std::right << std::setw(20) << std::fixed << std::setprecision(2) << value << std::endl;
        sum = 0;
    }
}

int main() {
    std::vector<Student> students;
    std::string file_path, mean_or_median;
    char read_data;

    while (true) {
        std::cout << "Read data from (enter 'c' for console or 'f' for file): ";
        std::cin >> read_data;

        if (read_data != 'c' && read_data != 'f') {
            std::cout << "Invalid input" << std::endl;
        } 
        else {
            break;
        }
    }

    if (read_data == 'c') {
        ReadDataFromConsole(students);
    }
    else {
        std::cout << "Please enter file path: ";
        std::cin >> file_path;
        ReadDataFromFile(students, file_path);
    }

    while(true) {
        std::cout << "Please choose MEAN or MEDIAN for calculation of the final grade ('mean' for MEAN and 'median' for MEDIAN): ";
        std::cin >> mean_or_median;

        if (mean_or_median == "mean") {
            PrintStudentsResults(students, true);
            break;
        }
        else if (mean_or_median == "median") {
            PrintStudentsResults(students, false);
            break;
        }
        else {
            std::cout << "Invalid input '" << mean_or_median << "'" << std::endl;
        }
    }

    return 0;
}