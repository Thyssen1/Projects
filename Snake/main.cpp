#include <iostream>

// Define global boolean variable
bool is_gameOver = false;

// Define map dimensions
const int width = 20;
const int height = 20;

int x;
int y;
int fruitX;
int fruitY;
int score;

enum eDirection { STOP = 0, LEFT, RIGHT, UP, DOWN};

// Store current direction of snake
eDirection dir;

void Setup()
{
    is_gameOver = false;
    dir = STOP;
    x = width / 2;
    y = height / 2;

    fruitX = rand() % width;
    fruitY = rand() % height;


}

void Draw() 
{
    // Clear the screen
    system("cls");

    for (int i = 0; i < width; i++) {
        std::cout << "#";
    }
    std::cout << std::endl;

    for (int i = 0; i < height; i++) {
        for (int j = 0; j < width; j++) {
            if (j == 0) {
                std::cout << "#";
            } else if (j == width - 1) {
                std::cout << "#";
            } else {
                std::cout << " ";
            }
        }
        std::cout << std::endl;
    }
    
}

void Input()
{

}

void Logic() 
{

}

int main()
{
    Setup();

    while(!is_gameOver) {
        Draw();
        Input();
        Logic();

    }
}