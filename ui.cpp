#include <iostream>
#include <vector>
#include <stdexcept>

#include "ui.h"
#include "ListSequence.h"
#include "ArraySequence.h"

static void printMenu();
static void handleCreate(std::vector<Sequence<int>*>& sequences);
static void handleAppend(std::vector<Sequence<int>*>& sequences);
static void handlePrint(const std::vector<Sequence<int>*>& sequences);

void runUI() {
    std::vector<Sequence<int>*> sequences;

    bool running = true;
    while (running) {
        printMenu();
        
        int cmd;
        std::cin >> cmd;
        if (!std::cin) {
            std::cerr << "[Error] ты чего наделал... я ливаю\n";
            break;
        }

        switch (cmd) {
        case 1:
            handleCreate(sequences);
            break;
        case 2:
            handleAppend(sequences);
            break;
        case 3:
            handlePrint(sequences);
            break;
        case 0:
            running = false;
            break;
        default:
            std::cout << "[Warning] Unknown command.\n";
            break;
        }
    }

    for (std::size_t i = 0; i < sequences.size(); i++) {
        delete sequences[i];
    }
    sequences.clear();

    std::cout << "Program finished.\n";
}


static void printMenu() {
    std::cout << "\n==== MENU ====\n";
    std::cout << "1) Создать новую последовательность (ArraySequence или ListSequence)\n";
    std::cout << "2) Добавить значение к имеющейся последовательности\n";
    std::cout << "3) Вывод последовательностт \n";
    std::cout << "0) Выход\n";
    std::cout << "Choose: ";
}

static void handleCreate(std::vector<Sequence<int>*>& sequences) {
    std::cout << "Выбери последовательность:\n";
    std::cout << "  1) ArraySequence\n";
    std::cout << "  2) ListSequence\n";
    std::cout << "  3) ImmutableArraySequence\n";
    std::cout << "  4) ImmutableListSequence\n";
    std::cout << "Тип: ";

    int choice;
    std::cin >> choice;
    if (!std::cin) {
        std::cin.clear();
        std::cin.ignore(10000, '\n');
        std::cerr << "Неверный ввод.\n";
        return;
    }

    Sequence<int>* newSeq = nullptr;
    switch (choice) {
    case 1:
        newSeq = new ArraySequence<int>(); 
        std::cout << "[OK] Создано ArraySequence<int> (ID = " << sequences.size() << ")\n";
        break;
    case 2:
        newSeq = new ListSequence<int>();
        std::cout << "[OK] Создано ListSequence<int> (ID = " << sequences.size() << ")\n";
        break;
    case 3:
        // newSeq = new ImmutableArraySequence<int>();
        std::cout << "[НЕ OK] В разработке \n";
        return;
    case 4:
        // newSeq = new ImmutableListSequence<int>();
        std::cout << "[НЕ OK] В разработке \n";
        return;
    default:
        std::cout << "[Warning] Мне кажется такого варианта не было.\n";
        return;
    }

    sequences.push_back(newSeq);
}

static void handleAppend(std::vector<Sequence<int>*>& sequences) {
    if (sequences.empty()) {
        std::cout << "[Warning] Вы пока не создали последовательность.\n";
        return;
    }

    std::cout << "Сущетсвующие последовательности: 0 ... " << (sequences.size()-1) << "\n";
    std::cout << "Введите ID последовательности: ";
    int id;
    std::cin >> id;
    if (!std::cin) {
        std::cin.clear();
        std::cin.ignore(10000, '\n');
        std::cerr << "[Error] Мне кажется такого варианта не было..\n";
        return;
    }

    if (id < 0 || id >= static_cast<int>(sequences.size())) {
        std::cout << "[Error] ID - инвалид.\n";
        return;
    }

    std::cout << "Введите число, которое добавить: ";
    int value;
    std::cin >> value;
    if (!std::cin) {
        std::cin.clear();
        std::cin.ignore(10000, '\n');
        std::cerr << "[Error] Неверный ввод.\n";
        return;
    }

    sequences[id]->Append(value);
    std::cout << "[OK] Добавлено " << value << " к последовательности #" << id << "\n";
}

static void handlePrint(const std::vector<Sequence<int>*>& sequences) {
    if (sequences.empty()) {
        std::cout << "[Warning] Вы пока не создали последовательность.\n";
        return;
    }

    std::cout << "ущетсвующие последовательности: 0 ... " << (sequences.size()-1) << "\n";
    std::cout << "Введите ID последовательности: ";
    int id;
    std::cin >> id;
    if (!std::cin) {
        std::cin.clear();
        std::cin.ignore(10000, '\n');
        std::cerr << "[Error] Неверный ввод.\n";
        return;
    }

    if (id < 0 || id >= static_cast<int>(sequences.size())) {
        std::cout << "[Error] ID - инвалид.\n";
        return;
    }

    Sequence<int>* seq = sequences[id];
    int len = seq->GetLength();
    std::cout << "[Print] последовательность #" << id << " (длина = " << len << "): ";
    for (int i = 0; i < len; i++) {
        std::cout << seq->Get(i) << " ";
    }
    std::cout << "\n";
}
