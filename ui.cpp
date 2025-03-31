#include <iostream>
#include "ui.h"

#include "ListSequence.h"
#include "ArraySequence.h"

static void handlePushFront(ListSequence<int>& listSeq) {
    std::cout << "[Push Front] Enter value: ";
    int val;
    std::cin >> val;
    listSeq.Prepend(val);
    std::cout << "Value " << val << " prepended\n";
}

static void handlePushBack(ListSequence<int>& listSeq) {
    std::cout << "[Push Back] Enter value: ";
    int val;
    std::cin >> val;
    listSeq.Append(val);
    std::cout << "Value " << val << " appended\n";
}

static void handlePrintList(const ListSequence<int>& listSeq) {
    std::cout << "[Print List]: ";
    for (int i = 0; i < listSeq.GetLength(); i++) {
        std::cout << listSeq.Get(i) << " ";
    }
    std::cout << std::endl;
}

void runUI() {
    ListSequence<int> listSeq;

    bool running = true;
    while (running) {
        std::cout << "\n==== MENU ====\n";
        std::cout << "1) Push Front (ListSequence)\n";
        std::cout << "2) Push Back  (ListSequence)\n";
        std::cout << "3) Print List\n";
        std::cout << "0) Exit\n";
        std::cout << "Choose: ";

        int cmd;
        std::cin >> cmd;
        if (!std::cin) {
            std::cerr << "Error: input stream in bad state. Exiting...\n";
            break;
        }

        switch (cmd) {
        case 1:
            handlePushFront(listSeq);
            break;
        case 2:
            handlePushBack(listSeq);
            break;
        case 3:
            handlePrintList(listSeq);
            break;
        case 0:
            running = false;
            break;
        default:
            std::cout << "Unknown command. Try again.\n";
            break;
        }
    }

    std::cout << "Program finished.\n";
}
