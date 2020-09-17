#include <iostream>
#include "headerFile/getchInLinux.h"
using namespace std;

class GameSnake {
  int AxisX_;
  int AxisY_;
  int SnakeDirectionX_;
  int SnakeDirectionY_;
  int SnakeLocationX_;
  int SnakeLocationY_;
  int SnakeFoodLocationX_;
  int SnakeFoodLocationY_;
  int GameScore_;
  int SnakeLength_;
  int SnakeTailInfo[2][100]; //
  string UserName_;

public:
  GameSnake();
  void DiplayBorder();
  void DiplayScore();
  bool GenerateSnakeFood();
  bool BoundryCollisionCheck();
  bool SnakeDirectcionHandle(int input_key);
  bool SnakeFoodCheck();
  void SnakeLengthIncrease();
  int GetEnteredKey();
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
  SnakeLength_ = 0;
  SnakeLocationX_ = AxisX_ - (AxisX_ / 4);
  SnakeLocationY_ = AxisY_ / 2;
}

int GameSnake::GetEnteredKey() {
  char c;
  c = getchInLinux();
  if (c == 27 || c == 91) {// this is just for scan code
    c = getchInLinux();
    if (c == 27 || c == 91) // also for scan code
      c = getchInLinux();
  }
  return c;
}

void GameSnake::DiplayScore() { cout << "Game score: " << GameScore_ << endl << endl; }

/*
  @ DiplayBorder()
    Displays the area required for snake game.
*/
void GameSnake::DiplayBorder() {
  cout << "\n\n       **** SNAKE GAME ****    ";
  cout << "\n\nUser Name: " << UserName_ << endl;
  system("clear");  // if we do not clear, we see it infinite loop
  DiplayScore();
  for (int y = 1; y <= AxisY_; y++) {
    for (int x = 1; x <= AxisX_; x++) {
      if ((y == 1 || y == AxisY_) || (x == 1 || x == AxisX_)) {
        cout << ".";
      } else if (x == SnakeFoodLocationX_ && y == SnakeFoodLocationY_) {
        cout << "*"; // Starting game keep snake food right side of game area.
      } else if (x == SnakeLocationX_ && y == SnakeLocationY_) {
        cout << "^";
      } else if (SnakeFoodCheck()) {
        GenerateSnakeFood();
      } else {
        int temp = 0;
        for (int k = 1; k <= SnakeLength_; k++)
          if (x == SnakeTailInfo[0][k] && y == SnakeTailInfo[1][k]) {
            cout << "o";
            temp = 1;
        }
        if (!temp)
          cout << " ";
      }
    }
    cout << endl;
  }
}

bool GameSnake::GenerateSnakeFood() {
  while (1) {
    SnakeFoodLocationX_ = rand() % (AxisX_);
    SnakeFoodLocationY_ = rand() % (AxisY_);
    if (SnakeFoodLocationX_ > 1 && SnakeFoodLocationY_ > 1)
      break;
  }
  SnakeLength_++;
}

bool GameSnake::BoundryCollisionCheck() {
  if (SnakeDirectionX_ <= 1 || SnakeDirectionX_ >= AxisX_ ||
      SnakeDirectionY_ <= 1 || SnakeDirectionY_ >= AxisY_) {
    cout << "\n *** Game Over ***";
    exit(0);
  }
  return false;
}

bool GameSnake::SnakeFoodCheck() {
  if (SnakeFoodLocationX_ == SnakeDirectionX_ &&
      SnakeFoodLocationY_ == SnakeDirectionY_)
    return true;
  return false;
}

void GameSnake::SnakeLengthIncrease() {
  // idea is that , each snake segments will follow its front  snake.
  // i.e
  // first segment will follow snake's HEAD
  // 2nd segment "       "     1st segment
  // 3rd segment "       "     2nd segment

  int prev1X = SnakeTailInfo[0][0];
  int prev1Y = SnakeTailInfo[1][0];

  int current1X;
  int current1Y;

  SnakeTailInfo[0][0] = SnakeDirectionX_;
  SnakeTailInfo[1][0] = SnakeDirectionY_;

  for (int i = 1; i < SnakeLength_; i++) {
    current1X = SnakeTailInfo[0][i];
    current1Y = SnakeTailInfo[1][i];

    SnakeTailInfo[0][i] = prev1X;
    SnakeTailInfo[1][i] = prev1Y;

    prev1X = current1X;
    prev1Y = current1Y;
  }
}


/*
  @ SnakeDirectcionHandle()
  - It controls the direction of snake based on input key.
  - 65: ASCII value of arrow up.
    66: ASCII value of arrow down.
    67: ASCII value of arrow right.
    68: ASCII value of arrow left.
    113: ASCII value of 'q'.
*/
bool GameSnake::SnakeDirectcionHandle(int input_key) {
  switch (input_key) {
  case 81: // 'Q'
  case 113: // 'q'
    cout << "End of Game" << endl;
    cout << "Press 'Enter' to quit the game" << endl;
    input_key = GetEnteredKey();
    exit(0);
  case 65:
    SnakeDirectionY_--;
    break;
  case 66:
    SnakeDirectionY_++;
    break;
  case 67:
    SnakeDirectionX_++;
    break;
  case 68:
    SnakeDirectionX_--;
    break;
  default:
    return false;
  }
  return true;
}

int main() {
  GameSnake GameSnakeInstance;
  GameSnakeInstance.GenerateSnakeFood();
  GameSnakeInstance.DiplayBorder();
  int input_key = GameSnakeInstance.GetEnteredKey();
  
  while (1) {
    GameSnakeInstance.DiplayBorder();
    GameSnakeInstance.SnakeDirectcionHandle(input_key);
  }

  return 0;
}