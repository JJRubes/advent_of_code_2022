#include<iostream>
#include<fstream>
#include<string>
#include<map>

enum Shape {
  ROCK = 1,
  PAPER,
  SCISCORS,
};

const Shape convertOpntShape(char s) {
  const std::map<char, Shape> converter = {
    {'A', ROCK},
    {'B', PAPER},
    {'C', SCISCORS}
  };
  return converter.at(s);
}

const Shape convertYourShape(char s) {
  const std::map<char, Shape> converter = {
    {'X', ROCK},
    {'Y', PAPER},
    {'Z', SCISCORS}
  };
  return converter.at(s);
}

const int adjudicate(Shape opnts, Shape yours) {
  // draw
  if(opnts == yours) {
    return 3;
  }

  // win
  Shape win;
  if(yours == ROCK) {
    win = SCISCORS;
  } else if(yours == PAPER) {
    win = ROCK;
  } else if(yours == SCISCORS) {
    win = PAPER;
  }
  if(opnts == win) {
    return 6;
  }

  // lose
  return 0;
}

const int evaluate(std::string input) {
  int points;

  Shape opnts = convertOpntShape(input[0]);
  Shape yours = convertYourShape(input[2]);
  points = yours; // enum lists shapes in point order

  points += adjudicate(opnts, yours);
  return points;
}

const void day_2(std::ifstream &input) {
  int totalPoints = 0;

  std::string line;
  while(getline(input, line)) {
    totalPoints += evaluate(line);
  }
  std::cout << "Total Points: " << totalPoints << std::endl;
}

int main(int argc, char* argv[]) {
  if(argc != 2) {
    std::cout << "Usage: ./day_2.out inputfilename" << std::endl;
    return 0;
  }

  std::ifstream input(argv[1]);
  if(input.good()) {
    day_2(input);
  }
  input.close();
}
