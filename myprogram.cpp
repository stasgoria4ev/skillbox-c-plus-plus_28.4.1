#include <iostream>
#include <string>
#include <thread>
#include <cmath>
#include <vector>

void Move(int speed, int* meters) { 
    std::this_thread::sleep_for(std::chrono::seconds(0)); //нить реализации движения пловца
    *meters += speed;
}

class Swimmer {
public:
    std::string name = "unknown";
    int speed = 0;
    int meters = 0;
    bool finish = false;
    int timeSec = 0;
};

class Swim {
public:
    std::vector <Swimmer> swimmers;
    std::vector <Swimmer> results;
    int timeSec = 0;

    bool SpeedComparison(int& speed) {
        bool found = false;
        for (int i = 0; i < swimmers.size(); ++i) {
            if (swimmers[i].speed == speed) 
                return true;
        }
        return found;
    }
    
    void Display() {
        std::cout << "Start!\n\n";
        while (!swimmers.empty()) {
            timeSec++;
            std::this_thread::sleep_for(std::chrono::seconds(1)); //нить задержки 1 сек для Вывода движений пловцов
            for (int i = 0; i < swimmers.size(); ++i) {
                swimmers[i].timeSec = timeSec;
                std::thread moveSwimmer(Move, swimmers[i].speed, &swimmers[i].meters);
                moveSwimmer.join();            
                if (!swimmers[i].finish && swimmers[i].meters >= 100) {
                    swimmers[i].finish = true;

                    results.push_back(swimmers[i]);

                    std::cout << swimmers[i].name << " Finish - 100 meters!" << '\n'; 
                } else if (!swimmers[i].finish) 
                    std::cout << swimmers[i].name << " swam " << swimmers[i].meters << " meters\n";
            }
            std::cout << '\n'; 

            for (int s = 0; s < swimmers.size(); ++s) {                              
                for (int q = 0; q < swimmers.size(); ++q) {                                
                    if (swimmers[q].finish) 
                        swimmers.erase(swimmers.begin() + q);
                } 
            }
        } 
    }
};

int main() { 
    Swim swim;
    for (int i = 0; i < 6; ++i) {
        Swimmer swimmer;
        bool good;
        std::cout << i + 1 << ". Enter swimmer's name: "; std::cin >> swimmer.name;
        do {
            std::cout << "And his speed: "; std::cin >> swimmer.speed;
            good = swim.SpeedComparison(swimmer.speed);
            if (good) std::cout << "Repetitive speed, please enter another value\n";
        } while (good);
        swim.swimmers.push_back(swimmer);
    }
    std::cout << '\n';
    
    swim.Display();
    
    for (std::vector <Swimmer>::iterator it = swim.results.begin(); it != swim.results.end(); ++it)
        std::cout << "time = " << it->timeSec << ", swimmer = " << it->name << '\n';
}