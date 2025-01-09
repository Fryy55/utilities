#include <iostream>
#include <set>
#include <conio.h>

unsigned int depth; // 8 is minimal depth, 7 doesn't reach 1 iteration
const unsigned int BASE = 5;
const unsigned int NTABLE = 521;

struct State {
    std::string str;
    unsigned int layer = 4294967295;
    State* next = nullptr;
};


std::set <std::string> s;
State* hash_table[NTABLE];

unsigned int hsh(std::string str) {
    unsigned int sum = 0;
    unsigned int factor = 1;
    for (char i : str) {
        sum += int(i) * factor;
        factor *= BASE;
    }
    return sum % NTABLE;
}

State* hash_check(std::string str) {
    int hashed_str = hsh(str);
    for (State* i = hash_table[hashed_str]; i != nullptr; i = i -> next) {
        if (i -> str == str) {
            return i;
        }
    }

    State* old_st = hash_table[hashed_str];
    State* new_st = new State;
    new_st -> next = old_st;
    new_st -> str = str;
    hash_table[hashed_str] = new_st;
    return new_st;
}

char flip(char chr) {
    switch (chr) {
    case '0':
        return '1';
    case '1':
        return '0';
    default:
        printf("BWAAAAAAAAAAAAAAAAAAA\n");
        exit(0);
    }
}

void rec(std::string a, int lim) {
    s.insert(a);
    if (lim > depth) {
        return;
    }
    State* cur_state = hash_check(a);
    if (cur_state -> layer <= lim) {
        return;
    }
    cur_state -> layer = lim;
    
    std::string a1 = a;
    a1[0] = flip(a1[0]);
    a1[1] = flip(a1[1]);
    a1[3] = flip(a1[3]);
    rec(a1, lim + 1);
    if (lim == 0) {
        printf("Stage 1 passed\n");
    }

    std::string a2 = a;
    a2[0] = flip(a2[0]);
    a2[1] = flip(a2[1]);
    a2[2] = flip(a2[2]);
    a2[4] = flip(a2[4]);
    rec(a2, lim + 1);
    if (lim == 0) {
        printf("Stage 2 passed\n");
    }

    std::string a3 = a;
    a3[1] = flip(a3[1]);
    a3[2] = flip(a3[2]);
    a3[5] = flip(a3[5]);
    rec(a3, lim + 1);
    if (lim == 0) {
        printf("Stage 3 passed\n");
    }

    std::string a4 = a;
    a4[0] = flip(a4[0]);
    a4[3] = flip(a4[3]);
    a4[6] = flip(a4[6]);
    a4[4] = flip(a4[4]);
    rec(a4, lim + 1);
    if (lim == 0) {
        printf("Stage 4 passed\n");
    }

    std::string a5 = a;
    a5[1] = flip(a5[1]);
    a5[5] = flip(a5[5]);
    a5[3] = flip(a5[3]);
    a5[7] = flip(a5[7]);
    a5[4] = flip(a5[4]);
    rec(a5, lim + 1);
    if (lim == 0) {
        printf("Stage 5 passed\n");
    }

    std::string a6 = a;
    a6[5] = flip(a6[5]);
    a6[8] = flip(a6[8]);
    a6[2] = flip(a6[2]);
    a6[4] = flip(a6[4]);
    rec(a6, lim + 1);
    if (lim == 0) {
        printf("Stage 6 passed\n");
    }

    std::string a7 = a;
    a7[3] = flip(a7[3]);
    a7[6] = flip(a7[6]);
    a7[7] = flip(a7[7]);
    rec(a7, lim + 1);
    if (lim == 0) {
        printf("Stage 7 passed\n");
    }

    std::string a8 = a;
    a8[6] = flip(a8[6]);
    a8[7] = flip(a8[7]);
    a8[8] = flip(a8[8]);
    a8[4] = flip(a8[4]);
    rec(a8, lim + 1);
    if (lim == 0) {
        printf("Stage 8 passed\n");
    }

    std::string a9 = a;
    a9[5] = flip(a9[5]);
    a9[7] = flip(a9[7]);
    a9[8] = flip(a9[8]);
    rec(a9, lim + 1);
    if (lim == 0) {
        printf("Stage 9 passed\n");
    }

    return;
}

int main() {
    std::fill(hash_table, hash_table + NTABLE, nullptr);

    std::string a0 = "000000000";
    printf("Depth: ");
    scanf("%i", &depth);
    printf("\nInitialized...\n");
    rec("000000000", 0);
    printf("%d iterations found, 512 to prove. Depth: %d", s.size(), depth);
    
    for (State* i : hash_table) {
        while (i != nullptr) {
            State* next_state = i -> next;
            delete i;
            i = next_state;
        }
    }

    printf("\n\npress any key plsplsplsplspls :pray:");
    getch();
    return 0;
}