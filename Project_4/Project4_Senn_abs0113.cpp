/**
* File Name: project4_Senn_abs0113.cpp
* Author: Blake Senn (abs0113)
*
* Compiled with MinGW GCC C++ compiler.
*
* Description: A trivia quiz game using a linked list to store questions.
* Includes both a production version and a unit testing version via
* conditional compilation.
*/

#include <iostream>
#include <string>
#include <stdlib.h>
#include <assert.h>

// Macro to toggle between Production and Debugging versions
// Uncomment '#define UNIT_TESTING' to run the test driver.
// Comment it out to run the regular game.
//#define UNIT_TESTING

// Structure for the Linked List Node
struct TriviaNode {
    std::string question;
    std::string answer;
    int value;
    TriviaNode *next;

    // Constructor to initialize a node easily
    TriviaNode(std::string question_in, std::string answer_in, int value_in) {
        question = question_in;
        answer = answer_in;
        value = value_in;
        next = nullptr;
    }
};

// Class to manage the Trivia Linked List
class TriviaList {
public:
    TriviaNode *first;
    TriviaNode *last;
    int size;
    int current_score;

    TriviaList() {
        first = nullptr;
        last = nullptr;
        size = 0;
        current_score = 0;
    }

    // Adds a new question to the end of the list
    void add(std::string question_in, std::string answer_in, int value_in) {
        TriviaNode* new_node = new TriviaNode(question_in, answer_in, value_in);
        if (size == 0) {
            first = new_node;
        } else {
            last->next = new_node;
        }
        last = new_node;
        size++;
    }

    // Step 3: Initialize the list with hard-coded questions
    void initial_questions(int version) {
        // Clear list if needed, but for this project we just append
        if (size == 0) {
            // Trivia 1
            add("How long was the shortest war on record? (Hint: how many minutes)", "38", 100);
            // Trivia 2
            add("What was Bank of America's original name? (Hint: Bank of Italy or Bank of Germany)", "Bank of Italy", 50);
            // Trivia 3
            add("What is the best-selling video game of all time? (Hint: Call of Duty or Wii Sports)?", "Wii Sports", 20);
        }
    }

    // Step 4: Add a question via user input
    void add_question_from_user() {
        std::string new_q, new_a, val_str;
        int new_val;

        std::cout << "\nEnter a question: ";
        std::getline(std::cin, new_q);
        
        std::cout << "Enter an answer: ";
        std::getline(std::cin, new_a);
        
        std::cout << "Enter award points: ";
        std::getline(std::cin, val_str);
        // Simple conversion; assumes valid integer input
        new_val = std::stoi(val_str);

        add(new_q, new_a, new_val);
    }

    // Step 5: Ask questions
    // Returns 0 for success, 1 for warning/failure
    int ask_question(int num_ask) {
        if (num_ask < 1) {
            std::cout << "Warning - the number of trivia to be asked must equal to or be larger than 1." << std::endl;
            return 1;
        }
        if (size < num_ask) {
            std::cout << "Warning - there is only " << size << " trivia question(s) in the list." << std::endl;
            return 1;
        }

        current_score = 0;
        TriviaNode* current = first;
        int count = 0;

        while (current != nullptr && count < num_ask) {
            std::cout << "\nQuestion: " << current->question << std::endl;
            std::cout << "Answer: ";
            
            std::string user_answer;
            std::getline(std::cin, user_answer);

            if (user_answer == current->answer) {
                std::cout << "Your answer is correct. You receive " << current->value << " points." << std::endl;
                current_score += current->value;
            } else {
                std::cout << "Your answer is wrong. The correct answer is: " << current->answer << std::endl;
            }
            std::cout << "Your total points: " << current_score << std::endl;

            current = current->next;
            count++;
        }
        return 0; // Success
    }
};

// Global test driver function (Step 6)
#ifdef UNIT_TESTING
void test_driver() {
    std::cout << "*** This is a debugging version ***" << std::endl;
    
    TriviaList game;
    // We must populate the list for testing
    game.initial_questions(1); 

    // Case 1: Ask 0 questions
    std::cout << "Unit Test Case 1: Ask no question. The program should give a warning message." << std::endl;
    int result = game.ask_question(0);
    assert(result == 1); // Expect failure/warning return code
    std::cout << "Case 1 Passed\n" << std::endl;

    // Case 2.1: Ask 1 question (Incorrect answer)
    // Note: User must manually enter wrong answer for this test to "pass" visually, 
    // but the function call itself should return 0 (success) as the process worked.
    std::cout << "Unit Test Case 2.1: Ask 1 question in the linked list. The tester enters an incorrect answer." << std::endl;
    result = game.ask_question(1);
    assert(result == 0); 
    // We can't assert the score here easily without mocking input, 
    // but the logic flow is tested.
    std::cout << "Case 2.1 passed\n" << std::endl;

    // Case 2.2: Ask 1 question (Correct answer)
    std::cout << "Unit Test Case 2.2: Ask 1 question in the linked list. The tester enters a correct answer." << std::endl;
    result = game.ask_question(1);
    assert(result == 0);
    std::cout << "Case 2.2 passed\n" << std::endl;

    // Case 3: Ask all questions
    std::cout << "Unit Test Case 3: Ask all the questions in the linked list." << std::endl;
    result = game.ask_question(3);
    assert(result == 0);
    std::cout << "Case 3 passed\n" << std::endl;

    // Case 4: Ask too many questions
    std::cout << "Unit Test Case 4: Ask 5 questions in the linked list." << std::endl;
    result = game.ask_question(5);
    assert(result == 1); // Expect warning
    std::cout << "Case 4 passed\n" << std::endl;

    std::cout << "*** End of the Debugging Version ***" << std::endl;
}
#endif

// Main Function (Step 7)
int main() {
#ifdef UNIT_TESTING
    test_driver();
#else
    TriviaList game;
    
    std::cout << "*** Welcome to Blake's trivia quiz game ***" << std::endl;

    // 1. Create hard-coded trivia (Step 3 call)
    // REQUIRED FIX: This must run before asking user for more input
    game.initial_questions(1);

    // 2. Create more questions from keyboard (Step 4 call)
    bool add_more = false;
    do {
        game.add_question_from_user();
        
        std::string response;
        while (true) {
            std::cout << "Continue? (Yes/No): ";
            std::getline(std::cin, response);
            if (response.empty()) continue;
            
            char c = tolower(response[0]);
            if (c == 'y') {
                add_more = true;
                break;
            } else if (c == 'n') {
                add_more = false;
                break;
            }
        }
    } while (add_more);

    // 3. Play the game (Step 5 call)
    std::cout << "\n\n*** The Trivia Game ***" << std::endl;
    game.ask_question(game.size);

    std::cout << "\n*** Thank you for playing the trivia quiz game. Goodbye! ***" << std::endl;
#endif

    return 0;
}