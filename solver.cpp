#include <iostream>
#include <set>
#include <string>

// Constant declarations
const unsigned int DEPTH_LO = 8; // 8 is minimal depth, 7 doesn't reach 1 iteration
const unsigned int DEPTH_LOR = 17; // 17 is minimal depth, 16 doesn't reach 1 iteration
const unsigned int BASE = 5;
const unsigned int NTABLE_LO = 521;
const unsigned int NTABLE_LOR = 19687;

// Custom structures declarations
struct State {
    std::string str;
    unsigned int layer = 4294967295;
    int last_step = 80085;
    State* next = nullptr;
};

// Global data structures declarations
std::set <std::string> set_lo;
std::set <std::string> set_lor;
State* hash_table_lo[NTABLE_LO];
State* hash_table_lor[NTABLE_LOR];

// Global variables declarations
bool step_skip = false;

// Flipping functions
char flip_lo(char chr) { // No dependencies
    switch (chr) {
    case 'O':
        return 'X';
    case 'X':
        return 'O';
    }

    return 'X'; // Unreachable; I want the parser to stfu
}

char flip_lor(char chr) { // No dependencies
    switch (chr) {
    case 'O':
        return 'R';
    case 'R':
        return 'G';
    case 'G':
        return 'O';
    }

    return 'R'; // Unreachable; I want the parser to stfu
}

std::string flipper_lo(std::string str, int selection) { // 1 dependency: flip_lo
    switch (selection) {
    case 1:
        str[0] = flip_lo(str[0]);
        str[1] = flip_lo(str[1]);
        str[3] = flip_lo(str[3]);
        break;
    case 2:
        str[0] = flip_lo(str[0]);
        str[1] = flip_lo(str[1]);
        str[2] = flip_lo(str[2]);
        str[4] = flip_lo(str[4]);
        break;
    case 3:
        str[1] = flip_lo(str[1]);
        str[2] = flip_lo(str[2]);
        str[5] = flip_lo(str[5]);
        break;
    case 4:
        str[0] = flip_lo(str[0]);
        str[3] = flip_lo(str[3]);
        str[6] = flip_lo(str[6]);
        str[4] = flip_lo(str[4]);
        break;
    case 5:
        str[1] = flip_lo(str[1]);
        str[5] = flip_lo(str[5]);
        str[3] = flip_lo(str[3]);
        str[7] = flip_lo(str[7]);
        str[4] = flip_lo(str[4]);
        break;
    case 6:
        str[5] = flip_lo(str[5]);
        str[8] = flip_lo(str[8]);
        str[2] = flip_lo(str[2]);
        str[4] = flip_lo(str[4]);
        break;
    case 7:
        str[3] = flip_lo(str[3]);
        str[6] = flip_lo(str[6]);
        str[7] = flip_lo(str[7]);
        break;
    case 8:
        str[6] = flip_lo(str[6]);
        str[7] = flip_lo(str[7]);
        str[8] = flip_lo(str[8]);
        str[4] = flip_lo(str[4]);
        break;
    case 9:
        str[5] = flip_lo(str[5]);
        str[7] = flip_lo(str[7]);
        str[8] = flip_lo(str[8]);
        break;
    }

    return str;
}

std::string flipper_lor(std::string str, int selection) { // 1 dependency: flip_lor
    switch (selection) {
    case 1:
        str[0] = flip_lor(str[0]);
        str[1] = flip_lor(str[1]);
        str[3] = flip_lor(str[3]);
        break;
    case 2:
        str[0] = flip_lor(str[0]);
        str[1] = flip_lor(str[1]);
        str[2] = flip_lor(str[2]);
        str[4] = flip_lor(str[4]);
        break;
    case 3:
        str[1] = flip_lor(str[1]);
        str[2] = flip_lor(str[2]);
        str[5] = flip_lor(str[5]);
        break;
    case 4:
        str[0] = flip_lor(str[0]);
        str[3] = flip_lor(str[3]);
        str[6] = flip_lor(str[6]);
        str[4] = flip_lor(str[4]);
        break;
    case 5:
        str[1] = flip_lor(str[1]);
        str[5] = flip_lor(str[5]);
        str[3] = flip_lor(str[3]);
        str[7] = flip_lor(str[7]);
        str[4] = flip_lor(str[4]);
        break;
    case 6:
        str[5] = flip_lor(str[5]);
        str[8] = flip_lor(str[8]);
        str[2] = flip_lor(str[2]);
        str[4] = flip_lor(str[4]);
        break;
    case 7:
        str[3] = flip_lor(str[3]);
        str[6] = flip_lor(str[6]);
        str[7] = flip_lor(str[7]);
        break;
    case 8:
        str[6] = flip_lor(str[6]);
        str[7] = flip_lor(str[7]);
        str[8] = flip_lor(str[8]);
        str[4] = flip_lor(str[4]);
        break;
    case 9:
        str[5] = flip_lor(str[5]);
        str[7] = flip_lor(str[7]);
        str[8] = flip_lor(str[8]);
        break;
    }

    return str;
}

// Hash functions
unsigned int hash_lo(std::string str) { // No dependencies
    unsigned int sum = 0;
    unsigned int factor = 1;
    for (char i : str) {
        sum += int(i) * factor;
        factor *= BASE;
    }
    return sum % NTABLE_LO;
}

unsigned int hash_lor(std::string str) { // No dependencies
    unsigned int sum = 0;
    unsigned int factor = 1;
    for (char i : str) {
        sum += int(i) * factor;
        factor *= BASE;
    }
    return sum % NTABLE_LOR;
}

State* hash_check_lo(std::string str) { // 1 dependency: hash_lo
    int hashed_str = hash_lo(str);
    for (State* i = hash_table_lo[hashed_str]; i != nullptr; i = i -> next) if (i -> str == str) return i;

    State* old_st = hash_table_lo[hashed_str];
    State* new_st = new State;
    new_st -> next = old_st;
    new_st -> str = str;
    hash_table_lo[hashed_str] = new_st;
    return new_st;
}

State* hash_check_lor(std::string str) { // 1 dependency: hash_lor
    int hashed_str = hash_lor(str);
    for (State* i = hash_table_lor[hashed_str]; i != nullptr; i = i -> next) if (i -> str == str) return i;

    State* old_st = hash_table_lor[hashed_str];
    State* new_st = new State;
    new_st -> next = old_st;
    new_st -> str = str;
    hash_table_lor[hashed_str] = new_st;
    return new_st;
}

// Build functions
void build_lo(std::string str, int lim, int last_step) { // 2 dependencies: hash_check_lo; flipper_lo | Recursive
    set_lo.insert(str);
    if (lim > DEPTH_LO) return;

    State* cur_state = hash_check_lo(str);
    if (cur_state -> layer <= lim) return;
    cur_state -> layer = lim;
    cur_state -> last_step = last_step;
    
    build_lo(flipper_lo(str, 1), lim + 1, 1);
    if (lim == 0) printf("Stage 1/9 passed\n");

    build_lo(flipper_lo(str, 2), lim + 1, 2);
    if (lim == 0) printf("Stage 2/9 passed\n");

    build_lo(flipper_lo(str, 3), lim + 1, 3);
    if (lim == 0) printf("Stage 3/9 passed\n");

    build_lo(flipper_lo(str, 4), lim + 1, 4);
    if (lim == 0) printf("Stage 4/9 passed\n");

    build_lo(flipper_lo(str, 5), lim + 1, 5);
    if (lim == 0) printf("Stage 5/9 passed\n");

    build_lo(flipper_lo(str, 6), lim + 1, 6);
    if (lim == 0) printf("Stage 6/9 passed\n");

    build_lo(flipper_lo(str, 7), lim + 1, 7);
    if (lim == 0) printf("Stage 7/9 passed\n");

    build_lo(flipper_lo(str, 8), lim + 1, 8);
    if (lim == 0) printf("Stage 8/9 passed\n");

    build_lo(flipper_lo(str, 9), lim + 1, 9);
    if (lim == 0) printf("Stage 9/9 passed\n");
    
    return;
}

void build_lor(std::string str, int lim, int last_step) { // 2 dependencies: hash_check_lor; flipper_lor | Recursive
    set_lor.insert(str);
    if (lim > DEPTH_LOR) return;

    State* cur_state = hash_check_lor(str);
    if (cur_state -> layer <= lim) return;
    cur_state -> layer = lim;
    cur_state -> last_step = last_step;
    
    build_lor(flipper_lor(str, 1), lim + 1, 1);
    if (lim == 0) printf("Stage 1/9 passed\n");

    build_lor(flipper_lor(str, 2), lim + 1, 2);
    if (lim == 0) printf("Stage 2/9 passed\n");

    build_lor(flipper_lor(str, 3), lim + 1, 3);
    if (lim == 0) printf("Stage 3/9 passed\n");

    build_lor(flipper_lor(str, 4), lim + 1, 4);
    if (lim == 0) printf("Stage 4/9 passed\n");

    build_lor(flipper_lor(str, 5), lim + 1, 5);
    if (lim == 0) printf("Stage 5/9 passed\n");

    build_lor(flipper_lor(str, 6), lim + 1, 6);
    if (lim == 0) printf("Stage 6/9 passed\n");

    build_lor(flipper_lor(str, 7), lim + 1, 7);
    if (lim == 0) printf("Stage 7/9 passed\n");

    build_lor(flipper_lor(str, 8), lim + 1, 8);
    if (lim == 0) printf("Stage 8/9 passed\n");

    build_lor(flipper_lor(str, 9), lim + 1, 9);
    if (lim == 0) printf("Stage 9/9 passed\n");
    
    return;
}

// Extra functions
void scout(std::string str) { // No dependencies
    for (int i = 0; i < 9; i++) {
        printf("%c", str[i]);
        if (i == 2 || i == 5 || i == 8) printf("\n");
    }
    printf("\n");

    return;
}

void step_to_text(int step) { // 1 dependency: scout
    switch (step) {
    case 1:
        scout("x........");
        break;
    case 2:
        scout(".x.......");
        break;
    case 3:
        scout("..x......");
        break;
    case 4:
        scout("...x.....");
        break;
    case 5:
        scout("....x....");
        break;
    case 6:
        scout(".....x...");
        break;
    case 7:
        scout("......x..");
        break;
    case 8:
        scout(".......x.");
        break;
    case 9:
        scout("........x");
        break;
    default:
        printf("FUCK YOU");
        exit(0);
    }

    return;
}

void getch() { // No dependencies
    while (std::getchar() != 10) {}
    return;
}

// Search functions
void search_lo() { // 3 dependencies - hash_check_lo; flipper_lo; scout
    std::string row1, row2, row3, input = "";
    printf("LO solver mode.\nInput 3 rows:\nRow 1 | ");
    std::cin >> row1;
    printf("Row 2 | ");
    std::cin >> row2;
    printf("Row 3 | ");
    std::cin >> row3;
    input.append(row1).append(row2).append(row3);
    if (!set_lo.contains(input)) {
        printf("Wrong input format. See README.md in the repository for help.\n\n");
        return;
    }

    State* cur_state = hash_check_lo(input);
    int total_steps = cur_state -> layer;
    printf("\nFound a solution in %u step(s).\n\nSteps to solve:\nInitial position:\n", total_steps);
    getch(); // Void a newline

    for (cur_state; cur_state -> layer != 0; cur_state = hash_check_lo(flipper_lo(cur_state -> str, cur_state -> last_step))) {
        scout(cur_state -> str);
        printf("Press ENTER to proceed to the next step.\n\n");
        getch();
        printf("Step %d/%d:\n", total_steps - cur_state -> layer + 1, total_steps);
        step_to_text(cur_state -> last_step);
        printf("Result:\n");
    }
    scout(cur_state -> str);
    
    printf("Solved!\n\n");
    return;
}

void search_lor() { // 3 dependencies - hash_check_lor; flipper_lor; scout
    std::string row1, row2, row3, input = "";
    printf("LOR solver mode.\nInput 3 rows:\nRow 1 | ");
    std::cin >> row1;
    printf("Row 2 | ");
    std::cin >> row2;
    printf("Row 3 | ");
    std::cin >> row3;
    input.append(row1).append(row2).append(row3);
    if (!set_lor.contains(input)) {
        printf("Wrong input format. See README.md in the repository for help.\n\n");
        return;
    }

    State* cur_state = hash_check_lor(input);
    int total_steps = cur_state -> layer;
    printf("\nFound a solution in %u step(s).\n\nSteps to solve:\nInitial position:\n", total_steps);
    getch(); // Void a newline

    for (cur_state; cur_state -> layer != 0; cur_state = hash_check_lor(flipper_lor(cur_state -> str, cur_state -> last_step))) {
        scout(cur_state -> str);
        printf("Press ENTER to proceed to the next step.\n\n");
        getch();
        printf("Step %d/%d:\n", total_steps - cur_state -> layer + 1, total_steps);
        step_to_text(cur_state -> last_step);
        printf("Result:\n");
    }
    scout(cur_state -> str);
    
    printf("Solved!\n\n");
    return;
}

// Main

int main() {
    std::fill(hash_table_lo, hash_table_lo + NTABLE_LO, nullptr);
    printf("LO initialized...\n");
    build_lo("OOOOOOOOO", 0, 10);
    if (set_lo.size() != 512) {
        printf("Unexpected error occurred: expected 512 iterations; found %lu. Please report this issue via the repository's Issues tab.\n\nPress ENTER to close.", set_lo.size());
        getch(); // Void a newline
        getch();
        exit(0);
    }
    printf("LO hash table successfully built.\n");

    std::fill(hash_table_lor, hash_table_lor + NTABLE_LO, nullptr);
    printf("\nLOR initialized...\n");
    build_lor("OOOOOOOOO", 0, 10);
    if (set_lor.size() != 19683) {
        printf("Unexpected error occurred: expected 19683 iterations; found %lu. Please report this issue via the repository's Issues tab.\n\nPress ENTER to close.", set_lor.size());
        getch(); // Void a newline
        getch();
        exit(0);
    }
    printf("LOR hash table successfully built.\n\n");
    
    // :wtf: lo hash table output??? :car:
    /* for (int i = 0; i < NTABLE_LO; i++) {
        if (hash_table_lo[i] != nullptr) {
            printf("Hash: %d\n", i);
            for (State* j = hash_table_lo[i]; j != nullptr; j = j -> next) {
                printf("String:");
                std::cout << j -> str;
                printf(";Layer:%u\n", j -> layer);
            }
        }
     } */
    // :wtf: lo hash table output??? :car:

    // :wtf: lor hash table output??? :car:
    /* for (int i = 0; i < NTABLE_LOR; i++) {
        if (hash_table_lor[i] != nullptr) {
            printf("Hash: %d\n", i);
            for (State* j = hash_table_lor[i]; j != nullptr; j = j -> next) {
                printf("String:");
                std::cout << j -> str;
                printf(";Layer:%u\n", j -> layer);
            }
        }
    } */
    // :wtf: lor hash table output??? :car:

    // Main input loop
    bool breaker = false;
    while (!breaker) {
        printf("Input a command (lo, lor, config, exit)\n>>> ");
        std::string input;
        std::cin >> input;
        if (input == "exit") {
            breaker = true;
        } else if (input == "lo") {
            search_lo();
        } else if (input == "lor") {
            search_lor();
        } else if (input == "config") {
            //config();
        }
    }

    // i'm not memory leaking y'alls asses dw
    printf("\nDeallocating used memory...\n");
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
    printf("Memory successfully deallocated.\n\nPress ENTER to close.");
    getch(); // Void a newline
    getch();
    return 0;
}