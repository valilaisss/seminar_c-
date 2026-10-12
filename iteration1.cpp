#include <iostream>

class Fighter {
private:
    const char* name;
    int health;
    int maxHealth;
    int damage;

public:
    Fighter(const char* name, int health, int damage): name(name), health(health), maxHealth(health), damage(damage) {}
    void TakeDamage(int amount) {
        health -= amount;
        if (health < 0) {
            health = 0;
        }
    }

    void Attack(Fighter& target) const {
        target.TakeDamage(damage);
    }

    bool IsAlive() const {
        return health > 0;
    }

    void PrintStatus() const {
        std::cout << name << ": " << health << " здоровья\n";
    }
};

void PrintFighter(const Fighter& fighter) {
    fighter.PrintStatus();
}

class Game {
private:
    Fighter player;
    Fighter enemy;

public:
    Game()
        : player("Игрок", 30, 8),
          enemy("Противник", 12, 3) {
    }

    void Run() {
        while (true) {
            std::cout << "\n";
            PrintFighter(player);
            PrintFighter(enemy);
            std::cout << "\n1 - атаковать\n";
            std::cout << "0 - выйти\n";
            int command;
            std::cin >> command;

            if (command == 0) {
                break;
            }

            if (command == 1) {
                player.Attack(enemy);
                if (enemy.IsAlive()) {
                    enemy.Attack(player);
                }

                if (!enemy.IsAlive()) {
                    std::cout << "Вы победили\n";
                    break;
                }

                if (!player.IsAlive()) {
                    std::cout << "Вы проиграли\n";
                    break;
                }
            }
        }
    }
};

int main() {
    Game game;
    game.Run();

    return 0;
}