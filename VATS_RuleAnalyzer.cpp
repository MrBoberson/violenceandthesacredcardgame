// 5/20/2024
// Violence & The Sacred Card Game

#include <iostream>
#include <string>

using namespace std;

struct Card {
    string color; // "R" for red, "B" for black
    int value;    // Numerical value of the card
};

string createRule() {
    char choicePrime, choicePrime2, choiceColor, choiceCompare, choiceAction, choiceOutcome;
    string ruleDescription;

    cout << "Welcome to the Violence and the Sacred Rule Analyzer!\n\n";
    
    // Step 1: Define the primary rule based on color
    cout << "Do you want the condition of red or black? (Y or N): ";
    cin >> choicePrime;

    if (choicePrime == 'Y') {
        cout << "Which color would this rule include? (R or B): ";
        cin >> choiceColor;

        if (choiceColor == 'R') {
            ruleDescription = "If the card is red";
        } else if (choiceColor == 'B') {
            ruleDescription = "If the card is black";
        } else {
            cout << "Invalid color choice. Exiting...\n";
            return "";
        }
    } else {
        ruleDescription = "If your card";
    }

    // Step 2: Add a numerical comparison condition
    cout << "Do you want to add a numerical condition (higher or lower) to this? (Y or N): ";
    cin >> choicePrime2;

    if (choicePrime2 == 'Y') {
        cout << "Do you want the condition to be lower or higher than your card? (L or H): ";
        cin >> choiceCompare;

        if (choiceCompare == 'H') {
            ruleDescription += " is higher than mine";
        } else if (choiceCompare == 'L') {
            ruleDescription += " is lower than mine";
        } else {
            cout << "Invalid choice for numerical condition. Exiting...\n";
            return "";
        }
    } else if (choicePrime == 'N') {
        // If no color and no numerical condition, the rule is incomplete.
        cout << "No condition selected. Exiting...\n";
        return "";
    }

    // Step 3: Define the action for other players to take
    cout << "What action should other players take? (U for keep the card up, D for put the card down): ";
    cin >> choiceAction;

    if (choiceAction == 'U') {
        ruleDescription += ", then keep the card up";
    } else if (choiceAction == 'D') {
        ruleDescription += ", then put the card down";
    } else {
        cout << "Invalid action choice. Exiting...\n";
        return "";
    }

    // Step 4: Define the outcome if the player's action is correct
    cout << "What happens if the tribe member chooses the correct action? (L for live, D for die): ";
    cin >> choiceOutcome;

    if (choiceOutcome == 'L') {
        ruleDescription += ". If you are right, you live.";
    } else if (choiceOutcome == 'D') {
        ruleDescription += ". If you are right, you die.";
    } else {
        cout << "Invalid outcome choice. Exiting...\n";
        return "";
    }

    // Step 5: Display the final rule
    cout << "Final rule: " << ruleDescription << "\n";

    return ruleDescription;
}

void analyzePlayerAction(const string& rule, const Card& userCard, const Card& playerCard, char playerAction) {
    bool isConditionMet = true;

    // Check color condition
    if (rule.find("red") != string::npos && playerCard.color != "R") {
        isConditionMet = false;
    }
    if (rule.find("black") != string::npos && playerCard.color != "B") {
        isConditionMet = false;
    }

    // Check numerical condition
    if (rule.find("higher") != string::npos && playerCard.value <= userCard.value) {
        isConditionMet = false;
    }
    if (rule.find("lower") != string::npos && playerCard.value >= userCard.value) {
        isConditionMet = false;
    }

    // Determine the expected action based on the rule
    char expectedAction = (rule.find("put the card down") != string::npos) ? 'D' : 'U';

    // Compare the player's action with the expected action
    if (isConditionMet && playerAction == expectedAction) {
        cout << "You are right. " << (rule.find("you die") != string::npos ? "You die." : "You live.") << endl;
    } else {
        cout << "You are wrong." << endl;
    }
}

int main() {
    string rule = createRule();
    if (rule.empty()) {
        return 1;
    }

    Card userCard, playerCard;
    char playerAction;

    // Input for rule maker's card
    cout << "Enter the King's card color (R for red, B for black): ";
    cin >> userCard.color;
    cout << "Enter the King's card value (numeric): ";
    cin >> userCard.value;

    // Input for player's card
    cout << "Enter the tribe member's card color (R for red, B for black): ";
    cin >> playerCard.color;
    cout << "Enter the tribe member's card value (numeric): ";
    cin >> playerCard.value;

    // Input for player's action
    cout << "Enter the tribe member's action (U for keep the card up, D for put the card down): ";
    cin >> playerAction;

    // Analyze the player's action
    analyzePlayerAction(rule, userCard, playerCard, playerAction);

    return 0;
}
