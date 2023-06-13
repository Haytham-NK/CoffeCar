#include <iostream>
#include <string>
#include <vector>
#include <regex>
#include <algorithm>
#include <Windows.h>

using namespace std;

// ������� ����� "����"
class Coffee {
protected:
    double volume;
    double cost;
    string name;

public:
    Coffee(string name, double volume, double cost) : name(name), volume(volume), cost(cost) {}

    virtual ~Coffee() {}

    double getVolume() const {
        return volume;
    }

    double getCost() const {
        return cost;
    }

    string getName() const {
        return name;
    }
    virtual void printDetails() const = 0;
};

// ����� "���� ��������"
class CoffeeBeans : public Coffee {
public:
    CoffeeBeans(string name, double volume, double cost) : Coffee(name, volume, cost) {}

    void printDetails() const override {
        cout << name << " ���� � �����: ����� = " << volume << " ��������� = " << cost << endl;
    }
};

// ����� "���� �������"
class GroundCoffee : public Coffee {
public:
    GroundCoffee(string name, double volume, double cost) : Coffee(name, volume, cost) {}

    void printDetails() const override {
        cout << name << " ������� ����: ����� = " << volume << " ��������� = " << cost << endl;
    }
};

// ����� "���� ����������� � ������"
class InstantCoffeeInJars : public Coffee {
public:
    InstantCoffeeInJars(string name, double volume, double cost) : Coffee(name, volume, cost) {}

    void printDetails() const override {
        cout << name << " ���� ����������� � ������ ����� = " << volume << " ��������� = " << cost << endl;
    }
};

// ����� "���� � ���������"
class InstantCoffeeInPackets : public Coffee {
public:
    InstantCoffeeInPackets(string name, double volume, double cost) : Coffee(name, volume, cost) {}

    void printDetails() const override {
        cout << " ���� � ���������: ����� = " << volume << " ��������� = " << cost << endl;
    }
};

// ����� "������"
class CoffeeTruck {
private:
    vector<Coffee*> coffees;

public:
    void addCoffee(Coffee* coffee) {
        coffees.push_back(coffee);
    }

    void removeCoffee(int index) {
        if (index >= 0 && index < coffees.size())
        {
            delete coffees[index];
            coffees.erase(coffees.begin() + index);
        }
    }

    double calculateTotalVolume() const {
        double totalVolume = 0.0;
        for (const auto& coffee : coffees) {
            totalVolume += coffee->getVolume();
        }
        return totalVolume;
    }

    void sortCoffeesByCost() {
        sort(coffees.begin(), coffees.end(), [](const Coffee* firstCoffe, const Coffee* secondCoffe) {
            return firstCoffe->getCost() < secondCoffe->getCost();
            });
    }

    vector<Coffee*> findCoffeesInPriceRange(double minCost, double maxCost) const {
        vector<Coffee*> result;
        for (const auto& coffee : coffees) {
            if (coffee->getCost() >= minCost && coffee->getCost() <= maxCost) {
                result.push_back(coffee);
            }
        }
        return result;
    }

    int getTotalCoffeCount()
    {
        return coffees.size();
    }

    void printCoffeeList() const {
        for (const auto& coffee : coffees) {
            coffee->printDetails();
        }
    }

    ~CoffeeTruck() {
        for (const auto& coffee : coffees) {
            delete coffee;
        }
    }
};

// ������� ��� ����������� ���� � �������������� � �������������
void displayMenu() {
    cout << "����:" << endl;
    cout << "1. ���������� ������ ����" << endl;
    cout << "2. �������� ����" << endl;
    cout << "3. ������� ����" << endl;
    cout << "4. ���������� ����� ����� ����" << endl;
    cout << "5. ������������� ���� �� ����" << endl;
    cout << "6. ����� ���� �� ��������� ����" << endl;
    cout << "7. �����" << endl;
    cout << "������� ����� ��������: ";
}

int main() {

    SetConsoleCP(1251);
    SetConsoleOutputCP(1251);

    CoffeeTruck truck;
    double volumeMax, costMax, currentVolume = 0, currentCost = 0;
    
    cout << "������� ������������ ����� ���� � ��: ";
    cin >> volumeMax;
    cout << "������� ������������ ��������� ��������� ����: ";
    cin >> costMax;

    regex nameRegex("[^0-9]{2,100}$");
    regex costRegex("^(100000|[0-9]{1,5})$");
    regex volumeRegex("^(100000|[0-9]{1,5})$");


    while (true) {
        displayMenu();

        int choice;
        std::cin >> choice;

        switch (choice) {
        case 1: {
            cout << "������ ����:" << endl;
            truck.printCoffeeList();
            break;
        }
        case 2: {
            cout << "���������� ������ ����:" << endl;

            string volumeCheck, costCheck;
            double volume, cost;
            bool check = false;
            string name;
            while (true) {

                cout << "������� �������� ����: ";
                cin >> name;
                cout << "������� ����� ���� � ������ �������� � ��: ";
                cin >> volumeCheck;
                cout << "������� ��������� ��������� ����: ";
                cin >> costCheck;

                if (regex_match(name, nameRegex) && regex_match(volumeCheck, volumeRegex) && regex_match(costCheck, costRegex))
                {
                    volume = stoi(volumeCheck);
                    cost = stoi(costCheck);
                    break;
                }
                else
                {
                    cout << "�� ����� �������� ������!" << endl;
                }
            }
            while (!check)
            {
                cout << "�������� ��� ���� (1 = �������� ����, 2 = ������� ����, 3 = ���� � ������, 4 = ���� � ���������): ";
                int coffeeType;
                cin >> coffeeType;
                switch (coffeeType) {
                case 1:
                    truck.addCoffee(new CoffeeBeans(name, volume, cost));
                    check = true;
                    break;
                case 2:
                    truck.addCoffee(new GroundCoffee(name, volume, cost));
                    check = true;
                    break;
                case 3:
                    truck.addCoffee(new InstantCoffeeInJars(name, volume, cost));
                    check = true;
                    break;
                case 4:
                    truck.addCoffee(new InstantCoffeeInPackets(name, volume, cost));
                    check = true;
                    break;
                default:
                    cout << "�� ����� �������� ������!" << endl;
                    break;
                }
            }

            currentCost += cost;
            currentVolume += volume;
            cout << "���� ������� ���������!" << endl;
            break;
        }
        case 3: {
            cout << "������� ����:" << endl;
            cout << "������� ����� ����, ������� ���������� �������: ";
            int index;
            cin >> index;

            if (truck.getTotalCoffeCount() - 1 >= index) {
                truck.removeCoffee(index);
                cout << "���� ������� �������!" << endl;
            }
            else {
                cout << "���� �� �������" << endl;
            }

            break;
        }
        case 4: {
            double totalVolume = truck.calculateTotalVolume();
            cout << "����� ����� ����: " << totalVolume << endl;
            break;
        }
        case 5: {
            cout << "���������� ���� �� ����..." << endl;
            truck.sortCoffeesByCost();
            std::cout << "���� ������� ������������� �� ����" << endl;
            break;
        }
        case 6: {
            string minCostCheck, maxCostCheck;
            double minCost;
            double maxCost;

            while (true)
            {
                cout << "����� ���� �� ��������� ���������:" << endl;
                cout << "������� ����������� ���������: ";
                cin >> minCostCheck;
                cout << "������� ������������ ���������: ";
                cin >> maxCostCheck;

                if (regex_match(minCostCheck, costRegex) && regex_match(maxCostCheck, costRegex))
                {
                    minCost = stoi(minCostCheck);
                    maxCost = stoi(maxCostCheck);

                    std::vector<Coffee*> result = truck.findCoffeesInPriceRange(minCost, maxCost);
                    std::cout << "���� � ��������� [" << minCost << ", " << maxCost << "]:" << endl;
                    for (const auto& coffee : result) {
                        coffee->printDetails();
                    }
                    break;
                }
                else
                {
                    cout << "�� ����� �������� ������!" << endl;
                }
            }

            break;
        }
        case 7: {
            cout << "����� �� ���������" << endl;
            return 0;
        }
        default:
            cout << "������������ �����!" << endl;
            break;
        }

        std::cout << std::endl;
    }
}
