#include <string>
#include <vector>
#include <fstream>
#include <iostream>
#include <sstream>
#include <iomanip>
#include <algorithm>
#include <tuple>
#include <limits>
#include "Student.h"
#include "Exceptions.h"
#include "helper.h"

bool CompareStudents(Student s1, Student s2) {
    if (s1.name == s2.name){
        return s1.last_name < s2.last_name;
    }
    return s1.name < s2.name;
}

int CountWords(std::string str) {
    int count = 0;
    std::stringstream ss(str);
    std::string word;
    while(ss >> word) { ++count;}
    return count;
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

std::string ConvertDoubleToString(double d) {
    std::ostringstream oss;
    oss.precision(2);
    oss << std::fixed << d;
    return oss.str();
}

std::string PadTo(std::string str, size_t num, bool pad_right, char paddingChar)
{
    std::string str_copy = str;
    if(num > str.size())
        if (pad_right) {
            str_copy.insert(0, num - str.size(), paddingChar);
        }
        else {
            str_copy.insert(str.size(), num - str.size(), paddingChar);
        }

    return str_copy;
}

int GetRandomGrade() {
    return std::rand() % 10 + 1;
}

void GenerateRandomGrades(Student& s, int n) {
    for (int i = 0; i < n; i++) {
        s.grades.push_back(GetRandomGrade());
    }
}

void ReadInt(int& n, std::string header) {
    std::cout << header;
    std::cin >> n;

    while (std::cin.fail()) {
        std::cin.clear();
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(),
                '\n');
        std::cout << "Input is not an integer" << std::endl;
        std::cout << header;
        std::cin >> n;
    }
}

std::tuple<std::vector<Student>, std::vector<Student>> SplitStudents(std::vector<Student> students) {
    std::vector<Student> poor, smart;

    for (Student s : students) {
        if (Mean(s.grades) < 5) poor.push_back(s);
        else smart.push_back(s);
    }

    return std::make_tuple(poor, smart);
}

std::string MakeSingleLine(std::vector<Student> students) {
    double mean, median;
    std::string line = PadTo("Name", 20) + PadTo("Last name", 20) + PadTo("Final grade (mean)", 20, true) + PadTo("Final grade (median)", 25, true);
    line += '\n' + std::string(85, '-') + '\n';
    for (Student s : students) {
        mean = Mean(s.grades);
        median = Median(s.grades);
        line += PadTo(s.name, 20) + PadTo(s.last_name, 20) + PadTo(ConvertDoubleToString(mean), 20, true) + PadTo(ConvertDoubleToString(median), 25, true) + '\n';
    }
    return line;
}

void WriteStudentsResultsToFile(std::vector<Student> students, std::string file_path) {
    std::ofstream file(file_path);
    file << MakeSingleLine(students);
    file.close();
}