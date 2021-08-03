#include <iostream>
#include <vector>
#include <map>
#include <set>
#include <string> 
#include <sstream>
using namespace std;

class Date {
public:
    Date(string& strdate) {
        stringstream ss(strdate);
        ss >> year;
        ss.ignore(1); // change
        ss >> month;
        ss.ignore(1); // change
        ss >> day;
    }
    int GetYear() const { return year; }
    int GetMonth() const { return month; }
    int GetDay() const { return day; }
private:
    int year, month, day;
};

bool operator<(const Date& lhs, const Date& rhs) {
    if (lhs.GetYear() == rhs.GetYear()) {
        if (lhs.GetMonth() == rhs.GetMonth()) {
            return lhs.GetDay() < rhs.GetDay();
        }
        return lhs.GetMonth() < rhs.GetMonth();
    }
    return lhs.GetYear() < rhs.GetYear();
}

class Database {
public:
    void AddEvent(const Date& date, const string& event) {
        data[date].insert(event);
    }
    bool DeleteEvent(const Date& date, const string& event);
    int  DeleteDate(const Date& date);
    void Find(const Date& date) const;
    void Print() const;
private:
    map<Date, set<string>> data;
};

int main() {
    Database db;

    string command, operation, date, event;
    while (getline(cin, command)) {
        stringstream ss(command);
        ss >> operation;
        if (operation == "Add") {
            ss.ignore(1);
            ss >> date;
            ss.ignore(1);
            ss >> event;
            db.AddEvent({ date }, { event });
        }
        else if (operation == "Del") {
            // choice date or event
        }
        else if (operation == "Find") {

        }
        else if (operation == "Print") {

        }
    }
    
    return 0;
}