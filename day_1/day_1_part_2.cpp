#include<iostream>
#include<fstream>
#include<string>
#include<array>

template<uint N>
void updateMax(std::array<int, N> &maxes, int value) {
  for(int max : maxes) {
    if(max < value) {
      max = value;
      value = max;
    }
  }
}

template<uint N>
int sum(const std::array<int, N> &maxes) {
  int acc = 0;
  for(int max : maxes) {
    acc += max;
  }
  return acc;
}

void day_1_part_2(std::ifstream &input) {
  std::array<int, 3> maxes;
  maxes.fill(0); // redundant but I wanted to know
  int currentCalories = 0;

  std::string line;
  while(getline(input, line)) {
    if(line.size() == 0) {
      updateMax<3>(maxes, currentCalories);
      currentCalories = 0;
    } else {
      currentCalories += std::stoi(line);
    }
  }
  updateMax<3>(maxes, currentCalories);
  std::cout << sum(maxes) << std::endl;
}

int main(int argc, char* argv[]) {
  if(argc != 2) {
    std::cout << "Usage: ./day_1_part_2.out inputfilename" << std::endl;
    return 0;
  }

  std::ifstream input(argv[1]);
  if(input.good()) {
    day_1_part_2(input);
  }
  input.close();
}
