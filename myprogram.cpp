#include <iostream>
#include <string>
#include <thread>
#include <cmath>
#include <vector>
//#include <mutex>

class Swimmer {
public:
    std::string name = "unknown";
    int speed = 0;
    int meters = 0;
    int timeSec = 0;
};

std::vector <Swimmer> swimmers;
//std::mutex swimmers_access;

void Move() { 
    for (int i = 0; i < swimmers.size(); ++i) {
        //swimmers_access.lock();
        swimmers[i].meters += swimmers[i].speed;
        //swimmers_access.unlock();
    }
}

class Swim {
public:
    int timeSec = 0;
    
    void Display() {
        std::cout << "Start!\n\n";
        bool found = true;
        while (found) {
            timeSec++;
            //std::this_thread::sleep_for(std::chrono::seconds(1));
            
            std::thread moveSwimmer(Move);

            std::this_thread::sleep_for(std::chrono::seconds(1)); //нить задержки 1 сек для Вывода движений пловцов
            int count = 0;
            for (int i = 0; i < swimmers.size(); ++i) {
                //swimmers_access.lock();
                if (swimmers[i].timeSec == 0 && swimmers[i].meters >= 100) {
                    swimmers[i].timeSec = timeSec;
                    std::cout << swimmers[i].name << " Finish - 100 meters!" << '\n'; 
                } else if (swimmers[i].timeSec != 0) 
                    count++;
                else
                    std::cout << swimmers[i].name << " swam " << swimmers[i].meters << " meters\n";
                
                //swimmers_access.unlock();
            }

            moveSwimmer.join();

            std::cout << '\n'; 

            if (count == swimmers.size())
                found = false;
        } 
    }

    void Bubble() const {
        for (int s = 0; s < swimmers.size(); ++s) { 
            for (int q = 0; q < swimmers.size() - 1; ++q) {                                
                if (swimmers[q].timeSec > swimmers[q + 1].timeSec) {
                    Swimmer temp[1];
                    *temp = swimmers[q];
                    swimmers[q] = swimmers[q + 1];
                    swimmers[q + 1] = temp[0];
                }
            } 
        }
    }
};

int main() { 
    Swim swim;
    for (int i = 0; i < 6; ++i) { 
        Swimmer swimmer;
        std::cout << i + 1 << ". Enter swimmer's name: "; std::cin >> swimmer.name;
        std::cout << "And his speed: "; std::cin >> swimmer.speed;
        swimmers.push_back(swimmer);
    }
    std::cout << '\n';
    
    swim.Display();
    
    swim.Bubble();
    
    
    for (std::vector <Swimmer>::iterator it = swimmers.begin(); it != swimmers.end(); ++it)
        std::cout << "time = " << it->timeSec << ", swimmer = " << it->name << '\n';
}