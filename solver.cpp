#include <iostream>
#include <fstream>
#include <string>
#include <set>
#include <deque>

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
std::deque <std::string> parsed_input_deq;

// Global variables declarations
bool yes_cfg = true;

bool skip;
bool only_moves;
bool table;

std::string last_input = "...";

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

char flip_lor_build(char chr) { // No dependencies
    switch (chr) {
    case 'O':
        return 'G';
    case 'G':
        return 'R';
    case 'R':
        return 'O';
    }

    return 'R'; // Unreachable; I want the parser to stfu
}

char flip_lor_search(char chr) { // No dependencies
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

std::string flipper_lor_build(std::string str, int selection) { // 1 dependency: flip_lor_build
    switch (selection) {
    case 1:
        str[0] = flip_lor_build(str[0]);
        str[1] = flip_lor_build(str[1]);
        str[3] = flip_lor_build(str[3]);
        break;
    case 2:
        str[0] = flip_lor_build(str[0]);
        str[1] = flip_lor_build(str[1]);
        str[2] = flip_lor_build(str[2]);
        str[4] = flip_lor_build(str[4]);
        break;
    case 3:
        str[1] = flip_lor_build(str[1]);
        str[2] = flip_lor_build(str[2]);
        str[5] = flip_lor_build(str[5]);
        break;
    case 4:
        str[0] = flip_lor_build(str[0]);
        str[3] = flip_lor_build(str[3]);
        str[6] = flip_lor_build(str[6]);
        str[4] = flip_lor_build(str[4]);
        break;
    case 5:
        str[1] = flip_lor_build(str[1]);
        str[5] = flip_lor_build(str[5]);
        str[3] = flip_lor_build(str[3]);
        str[7] = flip_lor_build(str[7]);
        str[4] = flip_lor_build(str[4]);
        break;
    case 6:
        str[5] = flip_lor_build(str[5]);
        str[8] = flip_lor_build(str[8]);
        str[2] = flip_lor_build(str[2]);
        str[4] = flip_lor_build(str[4]);
        break;
    case 7:
        str[3] = flip_lor_build(str[3]);
        str[6] = flip_lor_build(str[6]);
        str[7] = flip_lor_build(str[7]);
        break;
    case 8:
        str[6] = flip_lor_build(str[6]);
        str[7] = flip_lor_build(str[7]);
        str[8] = flip_lor_build(str[8]);
        str[4] = flip_lor_build(str[4]);
        break;
    case 9:
        str[5] = flip_lor_build(str[5]);
        str[7] = flip_lor_build(str[7]);
        str[8] = flip_lor_build(str[8]);
        break;
    }

    return str;
}

std::string flipper_lor_search(std::string str, int selection) { // 1 dependency: flip_lor_search
    switch (selection) {
    case 1:
        str[0] = flip_lor_search(str[0]);
        str[1] = flip_lor_search(str[1]);
        str[3] = flip_lor_search(str[3]);
        break;
    case 2:
        str[0] = flip_lor_search(str[0]);
        str[1] = flip_lor_search(str[1]);
        str[2] = flip_lor_search(str[2]);
        str[4] = flip_lor_search(str[4]);
        break;
    case 3:
        str[1] = flip_lor_search(str[1]);
        str[2] = flip_lor_search(str[2]);
        str[5] = flip_lor_search(str[5]);
        break;
    case 4:
        str[0] = flip_lor_search(str[0]);
        str[3] = flip_lor_search(str[3]);
        str[6] = flip_lor_search(str[6]);
        str[4] = flip_lor_search(str[4]);
        break;
    case 5:
        str[1] = flip_lor_search(str[1]);
        str[5] = flip_lor_search(str[5]);
        str[3] = flip_lor_search(str[3]);
        str[7] = flip_lor_search(str[7]);
        str[4] = flip_lor_search(str[4]);
        break;
    case 6:
        str[5] = flip_lor_search(str[5]);
        str[8] = flip_lor_search(str[8]);
        str[2] = flip_lor_search(str[2]);
        str[4] = flip_lor_search(str[4]);
        break;
    case 7:
        str[3] = flip_lor_search(str[3]);
        str[6] = flip_lor_search(str[6]);
        str[7] = flip_lor_search(str[7]);
        break;
    case 8:
        str[6] = flip_lor_search(str[6]);
        str[7] = flip_lor_search(str[7]);
        str[8] = flip_lor_search(str[8]);
        str[4] = flip_lor_search(str[4]);
        break;
    case 9:
        str[5] = flip_lor_search(str[5]);
        str[7] = flip_lor_search(str[7]);
        str[8] = flip_lor_search(str[8]);
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
    
    if (lim == 0) printf("Stage ");
    for (int i = 1; i <= 9; i++) {
        build_lo(flipper_lo(str, i), lim + 1, i);
        if (lim == 0) printf("%d/9 ", i);
    }
    
    if (lim == 0) printf("\n");
    return;
}

void build_lor(std::string str, int lim, int last_step) { // 2 dependencies: hash_check_lor; flipper_lor_build | Recursive
    set_lor.insert(str);
    if (lim > DEPTH_LOR) return;

    State* cur_state = hash_check_lor(str);
    if (cur_state -> layer <= lim) return;
    cur_state -> layer = lim;
    cur_state -> last_step = last_step;
    
    if (lim == 0) printf("Stage ");
    for (int i = 1; i <= 9; i++) {
        build_lor(flipper_lor_build(str, i), lim + 1, i);
        if (lim == 0) printf("%d/9 ", i);
    }
    
    if (lim == 0) printf("\n");
    return;
}

// Extra functions
void parse(std::string unparsed_input) { // No dependencies
    parsed_input_deq.clear();
    std::string temp_str = "";
    unparsed_input += ' ';
    for (char i : unparsed_input) {
        if (i != ' ') temp_str += i;
        else {
            if (temp_str != "") parsed_input_deq.push_back(temp_str);
            temp_str = "";
        }
    }

    return;
}

std::string input_next() { // 1 dependency: parse | Recursive
    std::string next;
    if (parsed_input_deq.size()) {
        next = parsed_input_deq.front();
        parsed_input_deq.pop_front();
    } else {
        std::string raw_input;
        std::getline(std::cin, raw_input);
        parse(raw_input);
        if (parsed_input_deq.empty()) return "";
        return input_next();
    }
    last_input = next;
    return next;
}

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

void config_init() { // No dependencies
    printf("Initializing config...\n");
    std::fstream in("lo.cfg");
    try {
        if (!in) throw(1);
    }
    catch (...) {
        printf("Can't locate lo.cfg\nMake sure the file exists in the right directory. (Tip: use config_reset from the main process to reset the file)\n\nPress ENTER to close.");
        getch();
        exit(0);
    }
    in >> skip >> only_moves >> table;
    try {
        if (!in) throw(1);
    }
    catch (...) {
        printf("Can't access lo.cfg\nMake sure the file's contents are valid. (Tip: use config_reset from the main process to reset the file)\n\nPress ENTER to close.");
        getch();
        exit(0);
    }
    in.close();

    printf("Config initialized.\n\n");
    return;
}

void config() { // 1 dependency: input_next
    std::cout << "\nAvailable settings:\nskip\nonly_moves\ntable\n\nOutput a state list:\nlist\n\n[" << last_input << "] >>> ";
    std::string input = input_next();
    bool* cur_setting;
    try {
        if (input == "skip") {
            cur_setting = &skip;
        } else if (input == "only_moves") {
            cur_setting = &only_moves;
        } else if (input == "table") {
            cur_setting = &table;
        } else if (input == "list") {
            printf("\nList of all config states:\nskip - %s\nonly_moves - %s\ntable - %s\n\n", skip ? "true" : "false", only_moves ? "true" : "false", table ? "true" : "false");
            return;
        } else throw(input);
    }
    catch (std::string e) {
        printf("\nUnknown setting: ");
        std::cout << e;
        printf("\nReturning...\n\n");
        return;
    }
    printf("\nCurrent state for ");
    std::cout << input << ": " << (*cur_setting ? "true" : "false") << ".\nInput new state (true/false)\n\n[" << last_input << "] >>> ";
    //printf(": %s.\nInput new state (true/false)\n\n>>> ", *cur_setting ? "true" : "false");
    std::string change = input_next();
    try {
        if (change == "true") {
            *cur_setting = true;
        } else if (change == "false") {
            *cur_setting = false;
        } else throw(change);
    }
    catch (std::string e) {
        std::cout << '\n' << e;
        printf(" is not a valid state.\nReturning...\n\n");
        return;
    }
    
    printf("\nSuccessfully updated config.\n\n");
}

void search_parse(std::string &str) { // No dependencies
    for (int i = 0; i < str.size(); i++) switch (str[i]) {
    case 'x':
        str[i] = 'X';
        break;
    case 'o':
        str[i] = 'O';
        break;
    case 'r':
        str[i] = 'R';
        break;
    case 'g':
        str[i] = 'G';
        break;
    }

    return;
}

// Search functions
void search_lo() { // 4 dependencies - input_next; search_parse; hash_check_lo; flipper_lo; scout
    std::string row1, row2, row3, input = "";
    printf("LO solver mode.\nInput 3 rows:\nRow 1 | ");
    row1 = input_next();
    printf("Row 2 | ");
    row2 = input_next();
    printf("Row 3 | ");
    row3 = input_next();
    input.append(row1).append(row2).append(row3);
    search_parse(input);
    try {
        if (!set_lo.contains(input)) throw (1);
    }
    catch (...) {
        printf("Wrong input format. See README.md in the repository for help.\n\n");
        return;
    }

    State* cur_state = hash_check_lo(input);
    int total_steps = cur_state -> layer;
    if (!only_moves && !table) printf("\nFound a solution in %u step(s).\n\nSteps to solve:\nInitial position:\n", total_steps);
    else printf("\nFound a solution in %u step(s).\n\nSteps to solve:\n", total_steps);

    int step_table[9];
    if (table) std::fill(step_table, step_table + 9, 0);

    for (; cur_state -> layer != 0; cur_state = hash_check_lo(flipper_lo(cur_state -> str, cur_state -> last_step))) {
        if (!table) {
            if (!only_moves) scout(cur_state -> str);
            if (!skip) {
                printf("Press ENTER to proceed to the next step.\n\n");
                getch();
            }
            printf("Step %d/%d:\n", total_steps - cur_state -> layer + 1, total_steps);
            step_to_text(cur_state -> last_step);
            if (!only_moves) printf("Result:\n");
        } else step_table[cur_state -> last_step - 1]++;
    }

    if (table) {
        for (int i = 0; i < 9; i++) {
            printf("%d" , step_table[i]);
            if (i == 2 || i == 5 || i == 8) printf("\n");
        }
        printf("\nSolved!\n\n");
        return;
    }

    if (!only_moves) scout(cur_state -> str);
    
    printf("Solved!\n\n");
    return;
}

void search_lor() { // 4 dependencies - input_next; search_parse; hash_check_lor; flipper_lor_search; scout
    std::string row1, row2, row3, input = "";
    printf("LOR solver mode.\nInput 3 rows:\nRow 1 | ");
    row1 = input_next();
    printf("Row 2 | ");
    row2 = input_next();
    printf("Row 3 | ");
    row3 = input_next();
    input.append(row1).append(row2).append(row3);
    search_parse(input);
    try {
        if (!set_lor.contains(input)) throw (1);
    }
    catch (...) {
        printf("Wrong input format. See README.md in the repository for help.\n\n");
        return;
    }

    State* cur_state = hash_check_lor(input);
    int total_steps = cur_state -> layer;
    if (!only_moves && !table) printf("\nFound a solution in %u step(s).\n\nSteps to solve:\nInitial position:\n", total_steps);
    else printf("\nFound a solution in %u step(s).\n\nSteps to solve:\n", total_steps);

    int step_table[9];
    if (table) std::fill(step_table, step_table + 9, 0);

    for (; cur_state -> layer != 0; cur_state = hash_check_lor(flipper_lor_search(cur_state -> str, cur_state -> last_step))) {
        if (!table) {
            if (!only_moves) scout(cur_state -> str);
            if (!skip) {
                printf("Press ENTER to proceed to the next step.\n\n");
                getch();
            }
            printf("Step %d/%d:\n", total_steps - cur_state -> layer + 1, total_steps);
            step_to_text(cur_state -> last_step);
            if (!only_moves) printf("Result:\n");
        } else step_table[cur_state -> last_step - 1]++;
    }

    if (table) {
        for (int i = 0; i < 9; i++) {
            printf("%d" , step_table[i]);
            if (i == 2 || i == 5 || i == 8) printf("\n");
        }
        printf("\nSolved!\n\n");
        return;
    }

    if (!only_moves) scout(cur_state -> str);
    
    printf("Solved!\n\n");
    return;
}

// Main

int main(int argc, char* argv[]) {
    if (argc > 1 && std::string(argv[1]) == "no-cfg") yes_cfg = false;
    if (yes_cfg) config_init();
    else {
        skip = false; // Set default values
        only_moves = false;
        table = false;
        printf("no-cfg flag detected. Initializing with default config.\n\n");
    }

    std::fill(hash_table_lo, hash_table_lo + NTABLE_LO, nullptr);
    printf("LO initialized...\n");
    build_lo("OOOOOOOOO", 0, 10);
    try {
        if (set_lo.size() != 512) {
            throw set_lo.size();
        }
    }
    catch (unsigned long long e) {
        printf("Unexpected error occurred: expected 512 iterations; found %d. Please report this issue via the repository's Issues tab.\n\nPress ENTER to close.", e);
        getch();
        exit(0);
    }
    printf("LO hash table successfully built.\n");

    std::fill(hash_table_lor, hash_table_lor + NTABLE_LO, nullptr);
    printf("\nLOR initialized...\n");
    build_lor("OOOOOOOOO", 0, 10);
    try {
        if (set_lor.size() != 19683) {
            throw set_lor.size();
        }
    }
    catch (unsigned long long e) {
        printf("Unexpected error occurred: expected 19683 iterations; found %d. Please report this issue via the repository's Issues tab.\n\nPress ENTER to close.", e);
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
    bool no_guide = false;
    while (!breaker) {
        if (no_guide) std::cout << "\n[" << last_input << "] >>> ";
        else std::cout << "Input a command (lo, lor, config, exit)\n[" << last_input << "] >>> ";;

        no_guide = false;
        std::string input = input_next();

        if (input == "exit") {
            breaker = true;
        } else if (input == "lo") {
            search_lo();
        } else if (input == "lor") {
            search_lor();
        } else if (input == "config") {
            config();
        } else no_guide = true;
    }

    if (yes_cfg) {
        printf("\nSaving config settings...\n");
        std::ofstream out("lo.cfg");
        out << skip << '\n' << only_moves << '\n' << table;
        out.close();
        printf("Settings successfully saved.\n");
    }

    printf("\nDeallocating used memory...\n"); // i'm not memory leaking y'alls asses dw
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
    getch();
    return 0;
}