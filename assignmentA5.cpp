// Chăm Rốch Thi
// Trần Gia Bình

#include <iostream>
#include <string>
#include <ctime>
#include <iomanip>
using namespace std;

// Class lưu trữ và xử lý thông tin sức khỏe
class HealthProfile {
private:
    string fname, lname, gender;
    int day, month, year;
    double height, weight;
    static int currentYear;

    // Khởi tạo năm hiện tại
    static void initCurrentYear() {
        time_t t = time(0);
        tm* now = localtime(&t);
        currentYear = now->tm_year + 1900;
    }

    // Tính số ngày tối đa của tháng
    int calculateMaxDays(int m, int y) const {
        const int maxDays[] = {0, 31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};
        if (m == 2 && ((y % 4 == 0 && y % 100 != 0) || y % 400 == 0)) {
            return 29;
        }
        return maxDays[m];
    }
    //kiểm tra nhập tên
    static bool isValidName(const string& name) {
        if (name.empty()) return false;
        for (char ch : name) {
            if (!isalpha(ch) && ch != ' ' && ch != '-') {
                return false;
            }
        }
        return true;
    }

public:
    // Constructor với kiểm tra ngày tháng
    HealthProfile(const string& fn, const string& ln, const string& g, int d, int m, int y, double h, double w)
        : fname(fn), lname(ln), gender(g), day(d), month(m), year(y), height(h), weight(w) {
        initCurrentYear();
        setDate(d, m, y);
    }

    // Getters
    static int getCurrentYear() { initCurrentYear(); return currentYear; }
    string getFname() const { return fname; }
    string getLname() const { return lname; }
    string getGender() const { return gender; }
    int getDay() const { return day; }
    int getMonth() const { return month; }
    int getYear() const { return year; }
    double getHeight() const { return height; }
    double getWeight() const { return weight; }

    // Lấy số ngày tối đa của tháng
    int getMaxDays(int m, int y) const {
        return calculateMaxDays(m, y);
    }

    // Setters với kiểm tra hợp lệ
    void setGender(const string& g) { gender = g; }

    bool setFname(const string& fn) {
        if (!isValidName(fn)) return false;
        fname = fn;
        return true;
    }
    bool setLname(const string& ln) {
        if (!isValidName(ln)) return false;
        lname = ln;
        return true;
    }  
    bool setDay(int d) {
        int max = calculateMaxDays(month, year);
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
        if (!setYear(y) || !setMonth(m) || !setDay(d)) return false;
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

    // Tính toán các chỉ số sức khỏe
    int getAge() const {     //tính tuổi dựa vào thời gian hệ thống
        time_t t = time(0);
        tm* now = localtime(&t);
        int current_month = now->tm_mon + 1;
        int current_day = now->tm_mday;
        int age = getCurrentYear() - year;
        if (current_month < month || (current_month == month && current_day < day)) age--;
        return age;
    }
    int getMaxHR() const { return 220 - getAge(); } // tính nhịp tim tối đa
    double getBMI() const { return weight / (height * height); } // tính chỉ số BMI
    void getTargetHR(double& low, double& high) const {     // tính nhịp tim mục tiêu
        low = getMaxHR() * 0.5;
        high = getMaxHR() * 0.85;
    }
    string getBMIClass() const { // so sánh chỉ số BMI
        double bmi = getBMI();
        if (bmi < 18.5) return "Underweight";
        if (bmi < 25) return "Normal";
        if (bmi < 30) return "Overweight";
        return "Obese";
    }

    // Hiển thị thông tin
    void display() const {
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

// Chuyển chuỗi thành chữ thường
string lower(string s) {
    for (char& c : s) {
        if (c >= 'A' && c <= 'Z') c += 32;
    }
    return s;
}

// Nhập và kiểm tra thông tin có hợp lệ không 
void inputInfo(HealthProfile& person) { 
    string fname, lname, gender;
    cout << "First name: ";
    getline(cin, fname);
    while (!person.setFname(fname)) {
        cout << "Error: Name must contain only letters, spaces, or hyphens." << endl << "Enter again: ";
        getline(cin, fname);
        cin.clear();
        cin.ignore(10000, '\n');
    }

    cout << "Last name: ";
    getline(cin, lname);
    while (!person.setLname(lname)) {
        cout << "Error: Name must contain only letters, spaces, or hyphens." << endl << "Enter again: ";
        getline(cin, lname);
        cin.clear();
        cin.ignore(10000, '\n');
    }
    cout << "Gender (Male/Female/Other): ";
    getline(cin, gender);
    while (lower(gender) != "male" && lower(gender) != "female" && lower(gender) != "other") {
        cout << "Error: Gender must be 'Male', 'Female', or 'Other'. Enter again: ";
        getline(cin, gender);
    }
    person.setGender(gender);
    
}

// Nhập và kiểm tra ngày tháng năm có hợp lệ không
void inputDate(HealthProfile& person, int currentYear) {
    int day, month, year;
    bool valid = false;
    
    cout << "Enter your birthday:\n";
    while (!valid) {
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

        if (person.setDate(day, month, year)) {
            valid = true;
        } else {
            int maxDays = person.getMaxDays(month, year);
            cout << "Error: Day must be between 1 and " << maxDays << " for month " << month << " of year " << year << ".\n";
            cout << "Please re-enter date:\n";
        }
    }
}

// Nhập và kiểm tra chiều cao, cân nặng có hợp lệ không
void inputHW(HealthProfile& person) {
    double height, weight;
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
}

int main() {
    int currentYear = HealthProfile::getCurrentYear();

    HealthProfile person("Temp", "Temp", "Temp", 1, 1, 1900, 1.0, 50.0);

    inputInfo(person);
    inputDate(person, currentYear);
    inputHW(person);
    person.display();

    return 0;
}