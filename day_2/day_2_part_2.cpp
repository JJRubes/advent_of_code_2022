#include<iostream>
#include<fstream>
#include<string>
#include<map>

enum class Shape {
  ROCK,
  PAPER,
  SCISCORS
};

const int shapePoints(Shape shape) {
  switch(shape) {
    case Shape::ROCK:
      return 1;
    case Shape::PAPER:
      return 2;
    case Shape::SCISCORS:
      return 3;
  }
  return -1;
}

enum class Outcome {
  WIN,
  DRAW,
  LOSE
};

const int outcomePoints(Outcome outcome) {
  switch(outcome) {
    case Outcome::WIN:
      return 6;
    case Outcome::DRAW:
      return 3;
    case Outcome::LOSE:
      return 0;
  }
  return -1;
}

const Shape convertOpntShape(char s) {
  const std::map<char, Shape> converter = {
    {'A', Shape::ROCK},
    {'B', Shape::PAPER},
    {'C', Shape::SCISCORS}
  };
  return converter.at(s);
}

const Outcome intendedOutcome(char o) {
  const std::map<char, Outcome> converter = {
    {'X', Outcome::LOSE},
    {'Y', Outcome::DRAW},
    {'Z', Outcome::WIN}
  };
  return converter.at(o);
}

// returns what will loses to the opponent
const Shape loses(Shape opnts) {
  switch(opnts) {
    case Shape::ROCK:
      return Shape::SCISCORS;
    case Shape::PAPER:
      return Shape::ROCK;
    case Shape::SCISCORS:
      return Shape::PAPER;
  }
  // what would be a better way to handle
  // get rid of the no-return-value error
  return Shape::ROCK;
}

// returns what will beat the opponent
const Shape beats(Shape opnts) {
  switch(opnts) {
    case Shape::ROCK:
      return Shape::PAPER;
    case Shape::PAPER:
      return Shape::SCISCORS;
    case Shape::SCISCORS:
      return Shape::ROCK;
  }
  return Shape::ROCK;
}

const int pointsForYourMove(Shape opnts, Outcome outcome) {
  Shape yours;
  switch(outcome) {
    case Outcome::WIN:
      yours = beats(opnts);
      break;
    case Outcome::DRAW:
      yours = opnts;
      break;
    case Outcome::LOSE:
      yours = loses(opnts);
      break;
  }
  return outcomePoints(outcome) + shapePoints(yours);
}

const int evaluate(std::string input) {
  Shape opnts = convertOpntShape(input[0]);
  Outcome outcome = intendedOutcome(input[2]);

  return pointsForYourMove(opnts, outcome);
}

const void day_2_part_2(std::ifstream &input) {
  int totalPoints = 0;

  std::string line;
  while(getline(input, line)) {
    totalPoints += evaluate(line);
  }
  std::cout << "Total Points: " << totalPoints << std::endl;
}

int main(int argc, char* argv[]) {
  if(argc != 2) {
    std::cout << "Usage: ./day_2_part_2.out inputfilename" << std::endl;
    return 0;
  }

  std::ifstream input(argv[1]);
  if(input.good()) {
    day_2_part_2(input);
  }
  input.close();
}
