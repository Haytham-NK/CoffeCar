#include <iostream>
#include <string>
#include <vector>
#include <regex>
#include <algorithm>
#include <Windows.h>

using namespace std;

// Базовый класс "Кофе"
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

// Класс "Кофе зерновое"
class CoffeeBeans : public Coffee {
public:
    CoffeeBeans(string name, double volume, double cost) : Coffee(name, volume, cost) {}

    void printDetails() const override {
        cout << name << " кофе в зёрнах: Объём = " << volume << " Стоимость = " << cost << endl;
    }
};

// Класс "Кофе молотое"
class GroundCoffee : public Coffee {
public:
    GroundCoffee(string name, double volume, double cost) : Coffee(name, volume, cost) {}

    void printDetails() const override {
        cout << name << " молотое кофе: Объём = " << volume << " Стоимость = " << cost << endl;
    }
};

// Класс "Кофе растворимое в банках"
class InstantCoffeeInJars : public Coffee {
public:
    InstantCoffeeInJars(string name, double volume, double cost) : Coffee(name, volume, cost) {}

    void printDetails() const override {
        cout << name << " кофе растворимое в банках Объём = " << volume << " Стоимость = " << cost << endl;
    }
};

// Класс "Кофе в пакетиках"
class InstantCoffeeInPackets : public Coffee {
public:
    InstantCoffeeInPackets(string name, double volume, double cost) : Coffee(name, volume, cost) {}

    void printDetails() const override {
        cout << " кофе в пакетиках: Объём = " << volume << " Стоимость = " << cost << endl;
    }
};

// Класс "Фургон"
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

// Функция для отображения меню и взаимодействия с пользователем
void displayMenu() {
    cout << "Меню:" << endl;
    cout << "1. Посмотреть список кофе" << endl;
    cout << "2. Добавить кофе" << endl;
    cout << "3. Удалить кофе" << endl;
    cout << "4. Подсчитать общий объём кофе" << endl;
    cout << "5. Отсортировать кофе по цене" << endl;
    cout << "6. Найти кофе по диапазону цены" << endl;
    cout << "7. Выйти" << endl;
    cout << "Введите номер операции: ";
}

int main() {

    SetConsoleCP(1251);
    SetConsoleOutputCP(1251);

    CoffeeTruck truck;
    double volumeMax, costMax, currentVolume = 0, currentCost = 0;
    
    cout << "Введите максимальный объём кофе в кг: ";
    cin >> volumeMax;
    cout << "Введите максимальную суммарную стоимость кофе: ";
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
            cout << "Список кофе:" << endl;
            truck.printCoffeeList();
            break;
        }
        case 2: {
            cout << "Добавление нового кофе:" << endl;

            string volumeCheck, costCheck;
            double volume, cost;
            bool check = false;
            string name;
            while (true) {

                cout << "Введите название кофе: ";
                cin >> name;
                cout << "Введите объём кофе с учётом упаковки в кг: ";
                cin >> volumeCheck;
                cout << "Введите суммарную стоимость кофе: ";
                cin >> costCheck;

                if (regex_match(name, nameRegex) && regex_match(volumeCheck, volumeRegex) && regex_match(costCheck, costRegex))
                {
                    volume = stoi(volumeCheck);
                    cost = stoi(costCheck);
                    break;
                }
                else
                {
                    cout << "Вы ввели неверные данные!" << endl;
                }
            }
            while (!check)
            {
                cout << "Выберите тип кофе (1 = зерновое кофе, 2 = молотое кофе, 3 = кофе в банках, 4 = кофе в пакетиках): ";
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
                    cout << "Вы ввели неверные данные!" << endl;
                    break;
                }
            }

            currentCost += cost;
            currentVolume += volume;
            cout << "Кофе успешно добавлено!" << endl;
            break;
        }
        case 3: {
            cout << "Удалить кофе:" << endl;
            cout << "Введите номер кофе, которое необходимо удалить: ";
            int index;
            cin >> index;

            if (truck.getTotalCoffeCount() - 1 >= index) {
                truck.removeCoffee(index);
                cout << "Кофе успешно удалено!" << endl;
            }
            else {
                cout << "Кофе не найдено" << endl;
            }

            break;
        }
        case 4: {
            double totalVolume = truck.calculateTotalVolume();
            cout << "Общий объём кофе: " << totalVolume << endl;
            break;
        }
        case 5: {
            cout << "Сортировка кофе по цене..." << endl;
            truck.sortCoffeesByCost();
            std::cout << "Кофе успешно отсортировано по цене" << endl;
            break;
        }
        case 6: {
            string minCostCheck, maxCostCheck;
            double minCost;
            double maxCost;

            while (true)
            {
                cout << "Найти кофе по заданному диапазону:" << endl;
                cout << "Введите минимальную стоимость: ";
                cin >> minCostCheck;
                cout << "Введите максимальную стоимость: ";
                cin >> maxCostCheck;

                if (regex_match(minCostCheck, costRegex) && regex_match(maxCostCheck, costRegex))
                {
                    minCost = stoi(minCostCheck);
                    maxCost = stoi(maxCostCheck);

                    std::vector<Coffee*> result = truck.findCoffeesInPriceRange(minCost, maxCost);
                    std::cout << "Кофе в диапазоне [" << minCost << ", " << maxCost << "]:" << endl;
                    for (const auto& coffee : result) {
                        coffee->printDetails();
                    }
                    break;
                }
                else
                {
                    cout << "Вы ввели неверные данные!" << endl;
                }
            }

            break;
        }
        case 7: {
            cout << "Выход из программы" << endl;
            return 0;
        }
        default:
            cout << "Неправильный выбор!" << endl;
            break;
        }

        std::cout << std::endl;
    }
}
