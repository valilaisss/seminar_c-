#include <iostream>

class Fighter {
private:
    const char* name;
    int health;
    int maxHealth;
    int damage;

public:
    Fighter(const char* name, int health, int damage):name(name), health(health), maxHealth(health), damage(damage) {}

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

    void Heal(int amount) {
        health += amount;

        if (health > maxHealth) {
            health = maxHealth;
        }
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
    Fighter enemies[3];
    Fighter* currentTarget;
    int medkits;

    bool TrySelectTarget(int number, Fighter*& outTarget) {
        outTarget = nullptr;
        if (number < 1 || number > 3) {
            return false;
        }

        if (!enemies[number - 1].IsAlive()) {
            return false;
        }
        outTarget = &enemies[number - 1];

        return true;
    }

    bool AllEnemiesDefeated() const {
        for (int i = 0; i < 3; ++i) {
            if (enemies[i].IsAlive()) {
                return false;
            }
        }

        return true;
    }

public:
    Game()
        : player("Игрок", 20, 8),
          enemies{
              Fighter("Противник 1", 12, 3),
              Fighter("Противник 2", 18, 4),
              Fighter("Противник 3", 24, 5)
          },
          currentTarget(nullptr),
          medkits(1) {}

    void Run() {
        while (true) {
            std::cout << "\nСостояние\n";
            PrintFighter(player);
            for (int i = 0; i < 3; ++i) {
                std::cout << i + 1 << ". ";
                PrintFighter(enemies[i]);
            }

            std::cout << "Аптечки: " << medkits << "\n";
            std::cout << "Текущая цель: ";

            if (currentTarget != nullptr) {
                currentTarget->PrintStatus();
            }
            else {
                std::cout << "не выбрана\n";
            }

            std::cout << "\nМеню:\n";
            std::cout << "1 - выбрать цель\n";
            std::cout << "2 - атаковать\n";
            std::cout << "3 - использовать аптечку\n";
            std::cout << "0 - выйти\n";
            std::cout << "Введите команду: ";

            int command;

            if (!(std::cin >> command)) {
                break;
            }

            if (command == 0) {
                break;
            }

            else if (command == 1) {
                int targetNum;
                std::cout << "Введите номер цели (1-3): ";

                if (!(std::cin >> targetNum)) {
                    break;
                }

                if (TrySelectTarget(targetNum, currentTarget)) {
                    std::cout << "Цель успешно выбрана\n";
                }
                else {
                    std::cout << "Ошибка: неверный номер или цель мертва\n";
                    currentTarget = nullptr;
                }
            }

            else if (command == 2) {
                if (currentTarget == nullptr) {
                    std::cout << "Сначала выберите живую цель\n";
                }
                else {
                    player.Attack(*currentTarget);
                    std::cout << "Игрок атакует\n";

                    if (!currentTarget->IsAlive()) {
                        std::cout << "Цель уничтожена\n";
                        currentTarget = nullptr;
                    }
                    else {
                        currentTarget->Attack(player);
                        std::cout << "Противник атакует в ответ\n";
                    }

                    if (!player.IsAlive()) {
                        std::cout << "Вы проиграли\n";
                        break;
                    }

                    if (AllEnemiesDefeated()) {
                        std::cout << "Вы победили! Все противники мертвы\n";
                        break;
                    }
                }
            }

            else if (command == 3) {
                if (currentTarget == nullptr) {
                    std::cout << "Сначала выберите живую цель\n";
                }
                else if (medkits == 0) {
                    std::cout << "Аптечек нет\n";
                }
                else {
                    player.Heal(8);
                    medkits--;
                    std::cout << "Игрок использовал аптечку\n";
                    currentTarget->Attack(player);
                    std::cout << "Противник атакует в ответ\n";

                    if (!player.IsAlive()) {
                        std::cout << "Вы проиграли\n";
                        break;
                    }
                }
            }

            else {
                std::cout << "Неверная команда\n";
            }
        }
    }
};

int main() {
    Game game;
    game.Run();

    return 0;
}