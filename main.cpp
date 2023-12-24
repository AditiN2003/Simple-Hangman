#include <cstdio>
#include <ncurses.h>
#include <vector>
#include <string>
#include <stdlib.h>
#include <time.h> 
#include <iostream>
using namespace std; 

enum Colors {
    RED_BLACK = 1,
    GREEN_BLACK,
    YELLOW_BLACK,
    BLUE_BLACK,
    MAGENTA_BLACK,
    CYAN_BLACK,
    WHITE_BLACK
};

vector<string> animals = {
    "elephant", "giraffe", "zebra", "flamingo", "tiger",
    "monkey", "penguin", "cheetah", "kangaroo", "hippopotamus",
    "rhinoceros", "crocodile", "gorilla", "panther", "koala"
};

vector<string> food = {
    "pizza", "hamburger", "sushi", "pasta", "cheescake",
    "pancake", "burrito", "lasagna", "sandwich", "doughnut",
    "taco", "spaghetti", "popcorn", "chocolate", "cake"
};

vector<string> movies = {
    "inception", "avatar", "titanic", "jaws", "Aladdin",
    "barbie", "deadpool", "incredibles", "gladiator", "interstellar",
    "oppenheimer", "spiderman", "ratatouille", "avengers", "clueless"
};

vector<string> states = {
    "california", "texas", "florida", "iowa", "ohio",
    "arizona", "georgia", "michigan", "washington", "colorado",
    "illinois", "connecticut", "pennsylvania", "virginia", "massachusetts",
};

std::vector<std::string> hangman = {
 R"+(
 +--+     
    |     
    |      
    |        
    |        
    |       
===== )+",
R"+(
 +--+     
 |  |     
    |      
    |        
    |        
    |       
===== )+",
R"+(
 +--+     
 |  |     
 O  |      
    |        
    |        
    |       
===== )+",
R"+(
 +--+     
 |  |     
 O  |      
 |  |        
    |        
    |       
===== )+",
R"+(
 +--+
 |  |
 O  |
/|  |
    |
    |
===== )+",
 R"+(
 +--+
 |  |
 O  |
/|\ |
    |
    |
===== )+",
R"+(
 +--+
 |  |
 O  |
/|\ |
/   |
    |
===== )+",
R"+(
 +--+
 |  |
 O  |
/|\ |
/ \ |
    |
===== )+"
};

void initColors() {
    start_color();

    init_pair(RED_BLACK, COLOR_RED, COLOR_BLACK);
    init_pair(GREEN_BLACK, COLOR_GREEN, COLOR_BLACK);
    init_pair(YELLOW_BLACK, COLOR_YELLOW, COLOR_BLACK);
    init_pair(BLUE_BLACK, COLOR_BLUE, COLOR_BLACK);
    init_pair(MAGENTA_BLACK, COLOR_MAGENTA, COLOR_BLACK);
    init_pair(CYAN_BLACK, COLOR_CYAN, COLOR_BLACK);
    init_pair(WHITE_BLACK, COLOR_WHITE, COLOR_BLACK);
}

void initNcurses(void)
{
  initscr();
  raw();
  noecho();
  curs_set(0);
  keypad(stdscr, true);
  refresh();
}

void printColor(const char *text, int colorPair) {
    attron(COLOR_PAIR(colorPair));
    printw("%s", text);
    attroff(COLOR_PAIR(colorPair));
}

void display(){
    initColors();

    printColor("Welcome to Hangman!\n", YELLOW_BLACK);

    printw("  _    _\n");
    printw(" | |  | |\n");
    printw(" | |__| | __ _ _ __   __ _ _ __ ___   __ _ _ __\n");
    printw(" |  __  |/ _` | '_ \\ / _` | '_ ` _ \\ / _` | '_ \\\n");
    printw(" | |  | | (_| | | | | (_| | | | | | | (_| | | | |\n");
    printw(" |_|  |_|\\__,_|_| |_|\\__, |_| |_| |_|\\__,_|_| |_|\n");
    printw("                     __/ |\n");
    printw("                    |___/\n");

    printColor("Rules of the game: \n", WHITE_BLACK);
	printw("You have 8 lives to guess the word correctly. ");
	printw("If not, stickman will hang!!!\n");
	printw( "You will not be penalized more than once for ");
	printw("making the same mistake.\n");
    printColor("\nPress any key to start. Good luck!\n", GREEN_BLACK);
    getch();
    refresh();
    clear();
}

bool guessedAlready(vector<char> lettersGuessed, char letter){
    bool guessed = false;
    for (long unsigned int i = 0; i<lettersGuessed.size();i++){
        if (letter==lettersGuessed[i]){
            guessed = true;
            return guessed;
        }
    }
    return guessed;

}

void play (string word){
    char letter;
    int maxLives=8; 
    vector<char> lettersGuessed;
    vector<char> correctLetter;
    
    clear();

    int wordSize = word.size();
    int numBlanks = wordSize;
    int hangmanDrawingIndex=0;
   // printw("word %s", word.c_str());
    //printw("  %d", word.size());
    printw("%s\n",hangman[hangmanDrawingIndex].c_str());

    for (int i = 0; i<wordSize;i++){
        printw("_ ");
    }
    mvprintw( 2, 20, "Lives: %d", maxLives);
        mvprintw( 3, 20, "Letters Guessed: ");
        mvprintw( 10, 0, "Guess a letter: ");

    while(maxLives>0&&numBlanks>0 ){
        // mvprintw( 2, 20, "Lives: %d", maxLives);
        // mvprintw( 3, 20, "Letters Guessed: %d", maxLives);
        // mvprintw( 10, 0, "Guess a letter: ");
        numBlanks = wordSize;
        letter = getch();
        letter = tolower(letter);
        size_t found = word.find(letter);
        clear();

    bool oldLetter = guessedAlready(lettersGuessed, letter);

    printw("num lives left %d", maxLives);
    printw("\nnum of balnks %d", numBlanks);
    if(oldLetter==false){
        lettersGuessed.push_back(letter);
        if (found != std::string::npos) {
            correctLetter.push_back(letter);
            clear();
                printColor("Good job! You guessed correctly!", GREEN_BLACK);
            printw("%s\n",hangman[hangmanDrawingIndex].c_str());

        for (int i = 0; i < wordSize; i++) {
            bool detected = false;
            for (size_t j = 0; j < correctLetter.size(); j++) {
            if (correctLetter[j] == word[i]) {
                printw("%c ", word[i]);
                numBlanks--;
                detected = true;
                break;
            }
        }
        if (!detected) {
            printw("_ ");
        }
    }
         mvprintw( 2, 20, "Lives: %d", maxLives);
          mvprintw( 3, 20, "Letters Guessed: ");
          for (long unsigned int i = 0; i< lettersGuessed.size(); i++){
            printw("%c ", lettersGuessed[i]);
          }
         mvprintw( 10, 0, "Guess a letter: ");
      
        if(numBlanks==0){
            clear();
            printColor("Yayy! You won! Way to go!! Press any key to exit!\n", GREEN_BLACK);
        //getch();
       
    }

    } else {
        maxLives--;
        hangmanDrawingIndex++;
        clear();
        if(maxLives==0){
            printColor(("Uh Oh! You lost :( Booohoooo! You ran out of lives. The word was " + word + ". \n\nPress any key to exit!\n").c_str(), RED_BLACK);
            break;
        }
        printColor(("Oh no! " + string(1, letter) + " is not in this word. You now have " + to_string(maxLives)+ " lives. Try again!" ).c_str(), RED_BLACK);
        printw("%s\n",hangman[hangmanDrawingIndex].c_str());
        
            for (int i = 0; i < wordSize; i++) {
                bool detected = false;
                for (size_t j = 0; j < correctLetter.size(); j++) {
                    if (correctLetter[j] == word[i]) {
                        printw("%c ", word[i]);
                        detected = true;
                        break;
                    }
        }
        if (!detected) {
            printw("_ ");
        }
    }

        mvprintw( 2, 20, "Lives: %d", maxLives);
        mvprintw( 3, 20, "Letters Guessed: ");
          for (long unsigned int i = 0; i< lettersGuessed.size(); i++){
            printw("%c ", lettersGuessed[i]);
          }
         mvprintw( 10, 0, "Guess a letter: ");
    }
    }else{
        clear();
        printColor("You have guessed that letter before. Try again!", YELLOW_BLACK);

        printw("%s\n",hangman[hangmanDrawingIndex].c_str());
        
            for (int i = 0; i < wordSize; i++) {
                bool detected = false;
                for (size_t j = 0; j < correctLetter.size(); j++) {
                    if (correctLetter[j] == word[i]) {
                        printw("%c ", word[i]);
                        detected = true;
                        break;
                    }
        }
        if (!detected) {
            printw("_ ");
        }
    }
        mvprintw( 2, 20, "Lives: %d", maxLives);
        mvprintw( 3, 20, "Letters Guessed: ");
          for (long unsigned int i = 0; i< lettersGuessed.size(); i++){
            printw("%c ", lettersGuessed[i]);
          }
         mvprintw( 10, 0, "Guess a letter: ");
        
    }
    
    }
 
   // getch();
}

void chooseCategory(){
    char input; 
    string word; 
    int index = rand() % 15;

    printw("\nChoose a category:\n\n");
    printw("1. Animals\n");
    printw("2. Food \n");
    printw("3. Movies\n");
    printw("4. States\n\n");
    printw("Enter your choice (1-4): ");

    input = getch(); 
    
    while (input!='1'&&input!='2'&&input!='3'&&input!='4'){
        printw("Invalid choice. Try again. \n");
        input = getch();
    }
    if (input=='1'){
        word = animals[index];
    }else if(input=='2'){
        word = food[index];
    }else if (input=='3'){
       word = movies[index];
    }else if(input=='4'){
       word = states[index];
    }
   // printw("%s", word.c_str()); 
    play(word);

}

int main()
{
    initNcurses();

    srand(time(NULL));

    display();

    chooseCategory();

    getch();

    endwin();

    return 0;
}