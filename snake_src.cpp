#include <iostream>
using namespace std;

class GameSnake {
  int AxisX_;
  int AxisY_;
  int foodX, foodY;
  int x, y;
  int GameScore_;
  int totalSegment;
  int snakeTail[2][100]; //
  string UserName_;

public:
  GameSnake();
  void DiplayBorder();
};

/*
  @ GameSnake()
  - Constructor of class GameSnake. 
*/
GameSnake::GameSnake() {
  cout << "Enter User Name: ";
  cin >> UserName_;
  cout << "\n\t*** SNAKE GAME ***\n\n";

  cout << "GAME INSTRUCTIONS\n";
  cout << "\n1.You can move snake Up, Down, Left, Right by arrow key. ";
  cout << "\n2.You can exit the game at any time by pressing 'q'.";
  cout << "\n3.For each eaten food You will be awared a 1 point. ";
  cout << "\n\nEnter any key to start.....  : ";

  GameScore_ = 0;
  AxisX_ = 60; // X direction length.
  AxisY_ = 30; // Y direction length.
}

/*
  @ DiplayBorder()
  - Displays the area required for snake game.
*/
void GameSnake::DiplayBorder() {
  cout << "\n\n       **** SNAKE GAME ****    ";
  cout << "\n\nUser Name: " << UserName_ << endl;

  for (int i = 1; i <= AxisY_; i++) {
    for (int j = 1; j <= AxisX_; j++) {
      if ((i == 1 || i == AxisY_) || (j == 1 || j == AxisX_)) {
        cout << ".";
      } else {
        cout << " ";
      }
    }
    cout << endl;
  }
}

int main() {
  GameSnake GameSnakeInstance;
  GameSnakeInstance.DiplayBorder();

  return 0;
}