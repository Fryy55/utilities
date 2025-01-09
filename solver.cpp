#include <iostream>
#include <set>
#include <conio.h>

// Constant declarations
unsigned int DEPTH_LO = 8; // 8 is minimal depth, 7 doesn't reach 1 iteration
unsigned int DEPTH_LOR = 17; // 17 is minimal depth, 16 doesn't reach 1 iteration
const unsigned int BASE = 5;
const unsigned int NTABLE_LO = 521;
const unsigned int NTABLE_LOR = 19687;

// Custom structures declarations
struct State {
    std::string str;
    unsigned int layer = 4294967295;
    State* next = nullptr;
};

// Global data structures declarations
std::set <std::string> set_lo;
std::set <std::string> set_lor;
State* hash_table_lo[NTABLE_LO];
State* hash_table_lor[NTABLE_LOR];

// Hash functions
unsigned int hash_lo(std::string str) {
    unsigned int sum = 0;
    unsigned int factor = 1;
    for (char i : str) {
        sum += int(i) * factor;
        factor *= BASE;
    }
    return sum % NTABLE_LO;
}

unsigned int hash_lor(std::string str) {
    unsigned int sum = 0;
    unsigned int factor = 1;
    for (char i : str) {
        sum += int(i) * factor;
        factor *= BASE;
    }
    return sum % NTABLE_LOR;
}

State* hash_check_lo(std::string str) {
    int hashed_str = hash_lo(str);
    for (State* i = hash_table_lo[hashed_str]; i != nullptr; i = i -> next) {
        if (i -> str == str) {
            return i;
        }
    }

    State* old_st = hash_table_lo[hashed_str];
    State* new_st = new State;
    new_st -> next = old_st;
    new_st -> str = str;
    hash_table_lo[hashed_str] = new_st;
    return new_st;
}

State* hash_check_lor(std::string str) {
    int hashed_str = hash_lor(str);
    for (State* i = hash_table_lor[hashed_str]; i != nullptr; i = i -> next) {
        if (i -> str == str) {
            return i;
        }
    }

    State* old_st = hash_table_lor[hashed_str];
    State* new_st = new State;
    new_st -> next = old_st;
    new_st -> str = str;
    hash_table_lor[hashed_str] = new_st;
    return new_st;
}

// Build functions
char flip_lo(char chr) {
    switch (chr) {
    case '0':
        return '1';
    case '1':
        return '0';
    default:
        printf("BWAAAAAAAAAAAAAAAAAAA IMPOSSIBRUUUU\n");
        exit(0);
    }
}

char flip_lor(char chr) {
    switch (chr) {
    case '0':
        return '1';
    case '1':
        return '2';
    case '2':
        return '0';
    default:
        printf("BWAAAAAAAAAAAAAAAAAAA IMPOSSIBRUUUU\n");
        exit(0);
    }
}

void build_lo(std::string a, int lim) {
    set_lo.insert(a);
    if (lim > DEPTH_LO) {
        return;
    }
    State* cur_state = hash_check_lo(a);
    if (cur_state -> layer <= lim) {
        return;
    }
    cur_state -> layer = lim;
    
    std::string a1 = a;
    a1[0] = flip_lo(a1[0]);
    a1[1] = flip_lo(a1[1]);
    a1[3] = flip_lo(a1[3]);
    build_lo(a1, lim + 1);
    if (lim == 0) {
        printf("Stage 1/9 passed\n");
    }

    std::string a2 = a;
    a2[0] = flip_lo(a2[0]);
    a2[1] = flip_lo(a2[1]);
    a2[2] = flip_lo(a2[2]);
    a2[4] = flip_lo(a2[4]);
    build_lo(a2, lim + 1);
    if (lim == 0) {
        printf("Stage 2/9 passed\n");
    }

    std::string a3 = a;
    a3[1] = flip_lo(a3[1]);
    a3[2] = flip_lo(a3[2]);
    a3[5] = flip_lo(a3[5]);
    build_lo(a3, lim + 1);
    if (lim == 0) {
        printf("Stage 3/9 passed\n");
    }

    std::string a4 = a;
    a4[0] = flip_lo(a4[0]);
    a4[3] = flip_lo(a4[3]);
    a4[6] = flip_lo(a4[6]);
    a4[4] = flip_lo(a4[4]);
    build_lo(a4, lim + 1);
    if (lim == 0) {
        printf("Stage 4/9 passed\n");
    }

    std::string a5 = a;
    a5[1] = flip_lo(a5[1]);
    a5[5] = flip_lo(a5[5]);
    a5[3] = flip_lo(a5[3]);
    a5[7] = flip_lo(a5[7]);
    a5[4] = flip_lo(a5[4]);
    build_lo(a5, lim + 1);
    if (lim == 0) {
        printf("Stage 5/9 passed\n");
    }

    std::string a6 = a;
    a6[5] = flip_lo(a6[5]);
    a6[8] = flip_lo(a6[8]);
    a6[2] = flip_lo(a6[2]);
    a6[4] = flip_lo(a6[4]);
    build_lo(a6, lim + 1);
    if (lim == 0) {
        printf("Stage 6/9 passed\n");
    }

    std::string a7 = a;
    a7[3] = flip_lo(a7[3]);
    a7[6] = flip_lo(a7[6]);
    a7[7] = flip_lo(a7[7]);
    build_lo(a7, lim + 1);
    if (lim == 0) {
        printf("Stage 7/9 passed\n");
    }

    std::string a8 = a;
    a8[6] = flip_lo(a8[6]);
    a8[7] = flip_lo(a8[7]);
    a8[8] = flip_lo(a8[8]);
    a8[4] = flip_lo(a8[4]);
    build_lo(a8, lim + 1);
    if (lim == 0) {
        printf("Stage 8/9 passed\n");
    }

    std::string a9 = a;
    a9[5] = flip_lo(a9[5]);
    a9[7] = flip_lo(a9[7]);
    a9[8] = flip_lo(a9[8]);
    build_lo(a9, lim + 1);
    if (lim == 0) {
        printf("Stage 9/9 passed\n");
    }
    
    return;
}

void build_lor(std::string a, int lim) {
    set_lor.insert(a);
    if (lim > DEPTH_LOR) {
        return;
    }
    State* cur_state = hash_check_lor(a);
    if (cur_state -> layer <= lim) {
        return;
    }
    cur_state -> layer = lim;
    
    std::string a1 = a;
    a1[0] = flip_lor(a1[0]);
    a1[1] = flip_lor(a1[1]);
    a1[3] = flip_lor(a1[3]);
    build_lor(a1, lim + 1);
    if (lim == 0) {
        printf("Stage 1/9 passed\n");
    }

    std::string a2 = a;
    a2[0] = flip_lor(a2[0]);
    a2[1] = flip_lor(a2[1]);
    a2[2] = flip_lor(a2[2]);
    a2[4] = flip_lor(a2[4]);
    build_lor(a2, lim + 1);
    if (lim == 0) {
        printf("Stage 2/9 passed\n");
    }

    std::string a3 = a;
    a3[1] = flip_lor(a3[1]);
    a3[2] = flip_lor(a3[2]);
    a3[5] = flip_lor(a3[5]);
    build_lor(a3, lim + 1);
    if (lim == 0) {
        printf("Stage 3/9 passed\n");
    }

    std::string a4 = a;
    a4[0] = flip_lor(a4[0]);
    a4[3] = flip_lor(a4[3]);
    a4[6] = flip_lor(a4[6]);
    a4[4] = flip_lor(a4[4]);
    build_lor(a4, lim + 1);
    if (lim == 0) {
        printf("Stage 4/9 passed\n");
    }

    std::string a5 = a;
    a5[1] = flip_lor(a5[1]);
    a5[5] = flip_lor(a5[5]);
    a5[3] = flip_lor(a5[3]);
    a5[7] = flip_lor(a5[7]);
    a5[4] = flip_lor(a5[4]);
    build_lor(a5, lim + 1);
    if (lim == 0) {
        printf("Stage 5/9 passed\n");
    }

    std::string a6 = a;
    a6[5] = flip_lor(a6[5]);
    a6[8] = flip_lor(a6[8]);
    a6[2] = flip_lor(a6[2]);
    a6[4] = flip_lor(a6[4]);
    build_lor(a6, lim + 1);
    if (lim == 0) {
        printf("Stage 6/9 passed\n");
    }

    std::string a7 = a;
    a7[3] = flip_lor(a7[3]);
    a7[6] = flip_lor(a7[6]);
    a7[7] = flip_lor(a7[7]);
    build_lor(a7, lim + 1);
    if (lim == 0) {
        printf("Stage 7/9 passed\n");
    }

    std::string a8 = a;
    a8[6] = flip_lor(a8[6]);
    a8[7] = flip_lor(a8[7]);
    a8[8] = flip_lor(a8[8]);
    a8[4] = flip_lor(a8[4]);
    build_lor(a8, lim + 1);
    if (lim == 0) {
        printf("Stage 8/9 passed\n");
    }

    std::string a9 = a;
    a9[5] = flip_lor(a9[5]);
    a9[7] = flip_lor(a9[7]);
    a9[8] = flip_lor(a9[8]);
    build_lor(a9, lim + 1);
    if (lim == 0) {
        printf("Stage 9/9 passed\n");
    }
    
    return;
}

int main() {
    std::fill(hash_table_lo, hash_table_lo + NTABLE_LO, nullptr);
    printf("LO initialized...\n");
    build_lo("000000000", 0);
    if (set_lo.size() != 512) {
        printf("Unexpected error occurred: expected 512 iterations; found %d. Please report this issue via the repository's Issues tab.\n\nPress any key to close.", set_lo.size());
        getch();
        exit(0);
    }
    printf("LO hash table successfully built.\n");

    std::fill(hash_table_lo, hash_table_lo + NTABLE_LO, nullptr);
    printf("\nLOR initialized...\n");
    build_lor("000000000", 0);
    if (set_lor.size() != 19683) {
        printf("Unexpected error occurred: expected 19683 iterations; found %d. Please report this issue via the repository's Issues tab.\n\nPress any key to close.", set_lor.size());
        getch();
        exit(0);
    }
    printf("LOR hash table successfully built.\n");
    
    // i'm not memory leaking y'alls asses dw
    for (State* i : hash_table_lo) {
        while (i != nullptr) {
            State* next_state = i -> next;
            delete i;
            i = next_state;
        }
    }
    for (State* i : hash_table_lor) {
        while (i != nullptr) {
            State* next_state = i -> next;
            delete i;
            i = next_state;
        }
    }
    return 0;
}