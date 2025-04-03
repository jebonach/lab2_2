#include "ui.h"
#include <iostream>
#include <vector>
#include <stdexcept>
#include "errors.h"

#include "ArraySequence.h"
#include "ListSequence.h"
#include "ImmutableArraySequence.h"
#include "ImmutableListSequence.h"

#include "sequence_ops.h"

static void handleCreate(std::vector<Sequence<int>*>& seqs);
static void handleAppend(std::vector<Sequence<int>*>& seqs);
static void handlePrint(const std::vector<Sequence<int>*>& seqs);
static void handleSubsequence(std::vector<Sequence<int>*>& seqs);
static void handleConcat(std::vector<Sequence<int>*>& seqs);
static void handleZip(std::vector<Sequence<int>*>& seqs);
static void handleUnzip(std::vector<Sequence<int>*>& seqs);

void runUI() {
    std::vector<Sequence<int>*> seqs;
    bool running = true;
    while (running) {
        std::cout << "\n==== MENU ====\n"
                  << "1) Create sequence\n"
                  << "2) Append\n"
                  << "3) Print\n"
                  << "4) Subsequence\n"
                  << "5) Concat\n"
                  << "6) Zip\n"
                  << "7) Unzip\n"
                  << "0) Exit\n"
                  << "Choose: ";
        int cmd;
        std::cin.clear();
        std::cin >> cmd;
        if (!std::cin) {
            std::cin.clear();
            std::cin.ignore(10000,'\n');
            std::cerr << "[Error] Invalid input, try again)\n";
            continue;
        }

        switch (cmd) {
        case 1:
            try {
                handleCreate(seqs); 
            } 
            catch (const std::exception &e) {
                handleException(e); 
            }
            break;
        case 2:
            try {
                handleAppend(seqs);
            } catch (const std::exception &e) {
                handleException(e);
            }
            break;
        case 3:
            try {
                handlePrint(seqs);
            } catch (const std::exception &e) {
                handleException(e);
            }
            continue;;
        case 4:
            try {
                handleSubsequence(seqs);
            } catch (const std::exception &e) {
                handleException(e);
            }
            break;
        case 5:
            try {
                handleConcat(seqs);
            } catch (const std::exception &e) {
                handleException(e);
            }
            break;
        case 6:
            try {
                handleZip(seqs);
            } catch (const std::exception &e) {
                handleException(e);
            }
            break;
        case 7:
            try {
                handleUnzip(seqs);
            } catch (const std::exception &e) {
                handleException(e);
            }
            break;
        case 0:
            running = false;
            break;
        default:
            std::cout << "Unknown command.\n";
        }
    }

    for (auto *ptr : seqs) {
        delete ptr;
    }
    seqs.clear();
    std::cout << "Program finished.\n";
}

static void handleCreate(std::vector<Sequence<int>*>& seqs) {
    std::cout << "Choose type:\n"
              << " 1) ArraySequence\n"
              << " 2) ListSequence\n"
              << " 3) ImmutableArraySequence\n"
              << " 4) ImmutableListSequence\n"
              << "Enter: ";
    int choice;
    std::cin >> choice;
    if (!std::cin) {
        throw std::invalid_argument("handleCreate: invalid input");
    }
    Sequence<int>* newSeq = nullptr;
    switch (choice) {
    case 1:
        newSeq = new ArraySequence<int>();
        std::cout << "[OK] Created ArraySequence, ID=" << seqs.size() << "\n";
        break;
    case 2:
        newSeq = new ListSequence<int>();
        std::cout << "[OK] Created ListSequence, ID=" << seqs.size() << "\n";
        break;
    case 3:
        newSeq = new ImmutableArraySequence<int>();
        std::cout << "[OK] Created ImmutableArraySequence, ID=" << seqs.size() << "\n";
        break;
    case 4:
        newSeq = new ImmutableListSequence<int>();
        std::cout << "[OK] Created ImmutableListSequence, ID=" << seqs.size() << "\n";
        break;
    default:
        throw std::out_of_range("Unknown sequence type choice");
    }
    seqs.push_back(newSeq);
}

static void handleAppend(std::vector<Sequence<int>*>& seqs) {
    if (seqs.empty()) {
        std::cout << "[Warn] No sequences.\n";
        return;
    }
    std::cout << "Existing sequences: [0.." << (seqs.size()-1) << "]\n";
    std::cout << "Choose ID: ";
    int id;
    std::cin >> id;
    if (!std::cin || id < 0 || id >= (int)seqs.size()) {
        throw std::out_of_range("handleAppend: invalid sequence ID");
    }
    std::cout << "Value to append: ";
    int val;
    std::cin >> val;
    if (!std::cin) {
        throw std::invalid_argument("handleAppend: invalid integer");
    }
    seqs[id] = seqs[id]->Append(val);

    std::cout << "[OK] appended " << val << " to seq #" << id << "\n";
}

static void handlePrint(const std::vector<Sequence<int>*>& seqs) {
    if (seqs.empty()) {
        std::cout << "[Warn] No sequences.\n";
        return;
    }
    std::cout << "Choose ID: ";
    int id;
    std::cin >> id;
    if (!std::cin || id < 0 || id >= (int)seqs.size()) {
        std::cin.clear();
        std::cin.ignore(10000, '\n');
        throw std::invalid_argument("handlePrint: invalid sequence ID");
    }
    
    Sequence<int>* seq = seqs[id];
    int len = seq->GetLength();
    std::cout << "Seq #" << id << " len=" << len << ": ";
    for (int i = 0; i < len; i++) {
        std::cout << seq->Get(i) << " ";
    }
    std::cout << "\n";
}

static void handleSubsequence(std::vector<Sequence<int>*>& seqs) {
    if (seqs.empty()) {
        std::cout << "[Warn] No sequences.\n";
        return;
    }
    std::cout << "Enter ID, start, end: ";
    int id, st, en;
    std::cin >> id >> st >> en;
    if (!std::cin || id < 0 || id >= (int)seqs.size()) {
        throw std::out_of_range("handleSubsequence: invalid ID or input");
    }
    Sequence<int>* sub = seqs[id]->GetSubsequence(st, en);
    seqs.push_back(sub);
    std::cout << "[OK] subsequence => ID=" << (seqs.size()-1) << "\n";
}

// 5) Concat
static void handleConcat(std::vector<Sequence<int>*>& seqs) {
    if (seqs.size() < 2) {
        std::cout << "[Warn] Need at least 2 sequences.\n";
        return;
    }
    std::cout << "Existing IDs: [0.." << (seqs.size()-1) << "]\n";
    std::cout << "Enter ID1, ID2: ";
    int id1, id2;
    std::cin >> id1 >> id2;
    if (!std::cin || id1 < 0 || id1 >= (int)seqs.size() ||
        id2 < 0 || id2 >= (int)seqs.size()) {
        throw std::out_of_range("handleConcat: invalid IDs");
    }
    Sequence<int>* s1 = seqs[id1];
    Sequence<int>* s2 = seqs[id2];
    Sequence<int>* result = s1->Concat(s2);
    seqs.push_back(result);
    std::cout << "[OK] concat => new seq ID=" << (seqs.size()-1) << "\n";
}

static void handleZip(std::vector<Sequence<int>*>& seqs) {
    if (seqs.size() < 2) {
        std::cout << "[Warn] Need at least 2 sequences.\n";
        return;
    }
    std::cout << "Enter ID1, ID2 for zip: ";
    int id1, id2;
    std::cin >> id1 >> id2;
    if (!std::cin || id1 < 0 || id1 >= (int)seqs.size() ||
        id2 < 0 || id2 >= (int)seqs.size()) {
        throw std::out_of_range("handleZip: invalid IDs");
    }
    Sequence<std::pair<int,int>>* zipped = zip<int,int>(seqs[id1], seqs[id2]);
    seqs.push_back((Sequence<int>*)zipped);
    std::cout << "[OK] zip => new seq of pairs, ID=" << (seqs.size()-1) << "\n";
}

static void handleUnzip(std::vector<Sequence<int>*>& seqs) {
    if (seqs.empty()) {
        std::cout << "[Warn] No sequences.\n";
        return;
    }
    std::cout << "Enter ID for unzip (should be seq of pairs): ";
    int id;
    std::cin >> id;
    if (!std::cin || id < 0 || id >= (int)seqs.size()) {
        throw std::out_of_range("handleUnzip: invalid ID");
    }
    auto* seqPairs = (Sequence<std::pair<int,int>>*)(seqs[id]);
    auto res = unzip<int,int>(seqPairs);
    seqs.push_back(res.first);
    seqs.push_back(res.second);
    std::cout << "[OK] unzip => ID=" << (seqs.size()-2) 
              << " and ID=" << (seqs.size()-1) << "\n";
}
