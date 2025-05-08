#include <iostream>
#include <string>
#include <ctime>
#include <iomanip>
using namespace std;

class HealthProfile {
private:
    string fname, lname, gender;
    int day, month, year;
    double height, weight;
    static int currentYear;

    static void initCurrentYear() {
        time_t t = time(0);
        tm* now = localtime(&t);
        currentYear = now->tm_year + 1900;
    }

    int calculateMaxDays() const {
        int maxDays[] = {0, 31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};
        if (month == 2 && ((year % 4 == 0 && year % 100 != 0) || year % 400 == 0)) {
            maxDays[2] = 29;
        }
        return maxDays[month];
    }

public:
    HealthProfile(string fn, string ln, string g, int d, int m, int y, double h, double w)
        : fname(fn), lname(ln), gender(g), day(d), month(m), year(y), height(h), weight(w) {
        initCurrentYear();
        setDate(d, m, y);
    }

    static int getCurrentYear() {
        initCurrentYear();
        return currentYear;
    }

    int getMaxHR() { return 220 - getAge(); }
    string getFname() const { return fname; }
    string getLname() const { return lname; }
    string getGender() const { return gender; }
    int getDay() const { return day; }
    int getMonth() const { return month; }
    int getYear() const { return year; }
    double getHeight() const { return height; }
    double getWeight() const { return weight; }

    void setFname(const string& fn) { fname = fn; }
    void setLname(const string& ln) { lname = ln; }
    void setGender(const string& g) { gender = g; }
    bool setDay(int d) {
        int max = calculateMaxDays();
        if (d < 1 || d > max) return false;
        day = d;
        return true;
    }
    bool setMonth(int m) {
        if (m < 1 || m > 12) return false;
        month = m;
        return setDay(day);
    }
    bool setYear(int y) {
        if (y < 1900 || y > currentYear) return false;
        year = y;
        return setDay(day);
    }
    bool setDate(int d, int m, int y) {
        if (!setYear(y)) return false;
        if (!setMonth(m)) return false;
        if (!setDay(d)) return false;
        return true;
    }
    bool setHeight(double h) {
        if (h <= 0 || h > 3) return false;
        height = h;
        return true;
    }
    bool setWeight(double w) {
        if (w <= 0 || w > 500) return false;
        weight = w;
        return true;
    }

    int getAge() {
        time_t t = time(0);
        tm* now = localtime(&t);
        int current_month = now->tm_mon + 1;
        int current_day = now->tm_mday;
        int age = getCurrentYear() - year;
        if (current_month < month || (current_month == month && current_day < day)) age--;
        return age;
    }

    double getBMI() { return weight / (height * height); }
    string getBMIClass() {
        double bmi = getBMI();
        return bmi < 18.5 ? "Underweight" : bmi < 25 ? "Normal" : bmi < 30 ? "Overweight" : "Obese";
    }
    void getTargetHR(double& low, double& high) {
        low = getMaxHR() * 0.5;
        high = getMaxHR() * 0.85;
    }

    int getMaxDays() const {
        return calculateMaxDays();
    }

    void display() {
        double low, high;
        getTargetHR(low, high);
        cout << fixed << setprecision(2);
        cout << "\nProfile: " << lname << " " << fname 
             << "\nGender: " << gender 
             << "\nDate of Birth: " << day << "/" << month << "/" << year << " (Age: " << getAge() << ")"
             << "\nHeight: " << height << "m, Weight: " << weight << "kg"
             << "\nBMI: " << getBMI() << " (" << getBMIClass() << ")"
             << "\nMax Heart Rate: " << getMaxHR() << " bpm"
             << "\nTarget Heart Rate: " << low << " - " << high << " bpm"
             << "\n\nBMI Values:\nUnderweight: < 18.5\nNormal: 18.5 - 24.9\nOverweight: 25 - 29.9\nObese: >= 30\n";
    }
};

int HealthProfile::currentYear = 0;

int main() {
    string fname, lname, gender;
    int day, month, year;
    double height, weight;

    cout << "First name: "; getline(cin, fname);
    cout << "Last name: "; getline(cin, lname);
    cout << "Gender: "; getline(cin, gender);

    HealthProfile person(fname, lname, gender, 1, 1, 1900, 1.0, 50.0);

    int currentYear = HealthProfile::getCurrentYear();

    cout << "Day (1-31): ";
    while (!(cin >> day) || day < 1 || day > 31) {
        cout << "Error: Day must be between 1 and 31. Try again: ";
        cin.clear();
        cin.ignore(10000, '\n');
    }

    cout << "Month (1-12): ";
    while (!(cin >> month) || month < 1 || month > 12) {
        cout << "Error: Month must be between 1 and 12. Try again: ";
        cin.clear();
        cin.ignore(10000, '\n');
    }

    cout << "Year (1900-" << currentYear << "): ";
    while (!(cin >> year) || year < 1900 || year > currentYear) {
        cout << "Error: Year must be between 1900 and " << currentYear << ". Try again: ";
        cin.clear();
        cin.ignore(10000, '\n');
    }

    while (!person.setDate(day, month, year)) {
        cout << "Error: Invalid date. Please re-enter:\n";
        if (year < 1900 || year > currentYear) {
            cout << "Error: Year must be between 1900 and " << currentYear << ".\n";
        } else if (month < 1 || month > 12) {
            cout << "Error: Month must be between 1 and 12.\n";
        } else {
            cout << "Error: Day must be between 1 and " << person.getMaxDays() << " for month " << month << " of year " << year << ".\n";
        }

        cout << "Day (1-31): ";
        while (!(cin >> day) || day < 1 || day > 31) {
            cout << "Error: Day must be between 1 and 31. Try again: ";
            cin.clear();
            cin.ignore(10000, '\n');
        }

        cout << "Month (1-12): ";
        while (!(cin >> month) || month < 1 || month > 12) {
            cout << "Error: Month must be between 1 and 12. Try again: ";
            cin.clear();
            cin.ignore(10000, '\n');
        }

        cout << "Year (1900-" << currentYear << "): ";
        while (!(cin >> year) || year < 1900 || year > currentYear) {
            cout << "Error: Year must be between 1900 and " << currentYear << ". Try again: ";
            cin.clear();
            cin.ignore(10000, '\n');
        }
    }

    cout << "Height (m, 0-3): ";
    while (!(cin >> height) || !person.setHeight(height)) {
        cout << "Error: Height must be between 0 and 3 meters. Enter again: ";
        cin.clear();
        cin.ignore(10000, '\n');
    }

    cout << "Weight (kg, 0-500): ";
    while (!(cin >> weight) || !person.setWeight(weight)) {
        cout << "Error: Weight must be between 0 and 500 kg. Enter again: ";
        cin.clear();
        cin.ignore(10000, '\n');
    }

    person.display();
    return 0;
}