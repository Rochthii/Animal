#include<iostream>
#include<string>
#include<vector>
using namespace std;

class Animal {
    private:
    string type, name, bDate, gender;
    double weight, length;

    public:
    Animal(string t, string n, string b, string g, double w, double l)
    : type(t), name(n), bDate(b), gender(g), weight(w), length(l) {}

    void setName(string n) {name = n;}
    void setbDate(string  b) {bDate = b;}
    void setGender(string g) {gender = g;}
    void setWeight(double w) {weight = w;}
    void setLength(double l) {length = l;}

    string getType() const {return type;}
    string getName() const {return name;}
    string getbDate() const {return bDate;}
    string getGender() const {return gender;}
    double getWeight() const {return weight;}
    double getLength() const {return length;}

    virtual string Introduce() const = 0;
    virtual string SayHelloTo(Animal& other) const = 0;
    virtual int Speed(int seconds) const = 0;
    virtual float Distance(int seconds) const = 0;

    virtual ~Animal() {}
};

class Dog : public Animal {
    public:
    Dog(string n, string b, string g, double w, double l)
    : Animal("Dog", n, b, g, w, l) {
    }

    string Introduce() const override {
        return "Xin chao, toi la " + getName() + ", mot chu choa.";
    }

    string SayHelloTo(Animal& other) const override {
        return "Xin chao, " + other.getName() + "!";
    }
    int Speed(int t) const override {
        return (t <= 50) ? 5 : 2;
    }
    float Distance(int t) const override {
        return Speed(t) * t / 1000.0;
    }
};

class Panther : public Animal {
    public:
        Panther(string n, string b, string g, double w, double l)
            : Animal("Panther", n, b, g, w, l) {}
    
        string Introduce() const override {
            return "Xin chao, toi la " + getName() + ", mot con bao.";
        }
    
        string SayHelloTo(Animal& other) const override {
            return "Xin chao, " + other.getName() + "!";
        }
    
        int Speed(int t) const override {
            return (t <= 20) ? 17 : 15;
        }
    
        float Distance(int t) const override {
            return (Speed(t) * t) / 1000.0;
        }
    };
    
class Lion : public Animal {
public:
    Lion(string n, string b, string g, double w, double l)
        : Animal("Lion", n, b, g, w, l) {}

    string Introduce() const override {
        return "Xin chao, toi la " + getName() + ", mot su tu.";
    }

    string SayHelloTo(Animal& other) const override {
        return "Xin chao, " + other.getName() + "!";
    }

    int Speed(int t) const override {
        return (t <= 60) ? 15 : 12;
    }

    float Distance(int t) const override {
        return (Speed(t) * t) / 1000.0;
    }
};

class Tiger : public Animal {
    public:
        Tiger(string n, string b, string g, double w, double l)
            : Animal("Tiger", n, b, g, w, l) {}
    
        string Introduce() const override {
            return "Xin chao, toi la " + getName() + ", mot con ho.";
        }
    
        string SayHelloTo(Animal& other) const override {
            return "Xin chao, " + other.getName() + "!";
        }
    
        int Speed(int t) const override {
            return (t <= 60) ? 14 : 10;
        }
    
        float Distance(int t) const override {
            return (Speed(t) * t) / 1000.0;
        }
    };

class Bear : public Animal {
public:
    Bear(string n, string b, string g, double w, double l)
        : Animal("Bear", n, b, g, w, l) {}

    string Introduce() const override {
        return "Xin chao, toi la " + getName() + ", mot con gau.";
    }

    string SayHelloTo(Animal& other) const override {
        return "Xin chao, " + other.getName() + "!";
    }

    int Speed(int t) const override {
        return (t <= 60) ? 13 : 10;
    }

    float Distance(int t) const override {
        return (Speed(t) * t) / 1000.0;
    }
};

class Meeting {
    private:
        vector<Animal*> dongVat;

    public:
    void Add(Animal* a) {
        dongVat.push_back(a);  //trỏ đv vào ds
    }

    void IntroduceAll() const {
        for (Animal* a : dongVat) {
            cout << a->Introduce() << endl;  //gọi pthuc để các đv giới thiệu cho nhau
        }
    }

    void SayHelloAll() const {   // hàm này cho các đv chào nhauu
        for(size_t i = 0; i < dongVat.size(); i++) {
            for(size_t j = 0; j < dongVat.size(); j++) {
                if(i != j) {
                    cout << dongVat[i]->getName() << ": ";
                    cout << dongVat[i] ->SayHelloTo(*dongVat[j]) << endl; 
                }
            }
        }
    }

    void Race(int seconds) const {
        for(Animal* a : dongVat) {
            int speed = a->Speed(seconds);
            float dist = a->Distance(seconds);
            cout << a->getName() << ": Tốc độ: " << speed << " m/s, Quãng đường: " << dist << " km\n";
        }
    }

};

int main() {
    Meeting HoiNghi;

    Dog dog("Bobby", "01-01-2020", "Male", 10.5, 0.8);
    Panther panther("Lina", "02-02-2020", "Female", 45.3, 1.5);
    Lion lion("Leo", "03-03-2019", "Male", 120.7, 2.0);

    HoiNghi.Add(&dog);
    HoiNghi.Add(&panther);
    HoiNghi.Add(&lion);
    HoiNghi.IntroduceAll();
    HoiNghi.SayHelloAll();
    HoiNghi.Race(60);

    return 0;
}


