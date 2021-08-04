#include <iostream>
#include <sstream>
#include <iomanip>
#include <map>
#include <set>
using namespace std;

class Date {
public:
    Date(string& strdate) {
        stringstream ss(strdate);
        ss >> year;
        CheckDateStr(strdate, ss);
        ss >> month;
        CheckDateStr(strdate, ss);
        ss >> day;
        if (!ss || ss.peek() != EOF) throw invalid_argument("Wrong date format: " + strdate);
        
        if (month < 1 || month > 12) throw invalid_argument("Month value is invalid: " + to_string (month));
        else if (day < 1 || day > 31) throw invalid_argument("Day value is invalid: " + to_string(day));
    }
    int GetYear() const { return year; }
    int GetMonth() const { return month; }
    int GetDay() const { return day; }
private:
    int year, month, day;
    void CheckDateStr(string& str, stringstream& ss) {
        if (!ss || ss.peek() != '-') throw invalid_argument("Wrong date format: " + str);
        else ss.ignore(1);
    }
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
    bool DeleteEvent(const Date& date, const string& event) {
        if (data[date].count(event)) {
            data[date].erase(event);
            return true;
        }
        else return false;
    }
    int DeleteDate(const Date& date) {
        int deleted = data[date].size();
        data.erase(date);
        return deleted;
    }
    void Find(const Date& date) const {
        if (data.count(date) > 0) {
            set<string> item = data.at(date);
            for (const string& i : item) {
                cout << i << endl;
            }
        }
    }
    void Print() const {
        for (const auto& item : data) {
            if (item.second.size() != 0) {
                for (const auto& str : item.second) {
                    cout << setw(4) << setfill('0') << item.first.GetYear() << '-'
                         << setw(2) << setfill('0') << item.first.GetMonth() << '-'
                         << setw(2) << setfill('0') << item.first.GetDay() << ' ' << str << endl;
                }
            }
        }
    }
private:
    map<Date, set<string>> data;
};

int main() {
    Database db;

    string command, operation, date, event;
    int count = 0;
    while (getline(cin, command)) {
        stringstream ss(command);
        try
        {
            ss >> operation;
            if (!ss) continue;
            else if (operation == "Add") {
                ss.ignore(1);
                ss >> date;
                ss.ignore(1);
                ss >> event;
                db.AddEvent(date, event);
            }
            else if (operation == "Del") {
                ss.ignore(1);
                ss >> date;
                ss.ignore(1);
                ss >> event;
                if (event.size() != 0) {
                    if (db.DeleteEvent(date, event)) cout << "Deleted successfully" << endl;
                    else cout << "Event not found" << endl;
                }
                else {
                    count = db.DeleteDate(date);
                    cout << "Deleted " << count << " events" << endl;
                }
            }
            else if (operation == "Find") {
                ss.ignore(1);
                ss >> date;
                db.Find(date);
            }
            else if (operation == "Print") {
                db.Print();
            }
            else {
                cout << "Unknown command: " << operation << endl;
                break;
            } 
            event.clear();
            date.clear();
        }
        catch (const invalid_argument& ex)
        {
            cout << ex.what() << endl;
            break;
        }
    }
    return 0;
}