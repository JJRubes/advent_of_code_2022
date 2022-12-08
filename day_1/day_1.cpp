#include<iostream>
#include<fstream>
#include<string>

void day_1(std::ifstream &input) {
  int maxCalories = 0;
  int currentCalories = 0;

  std::string line;
  while(getline(input, line)) {
    if(line.size() == 0) {
      if(maxCalories < currentCalories) {
        maxCalories = currentCalories;
      }
      currentCalories = 0;
    } else {
      currentCalories += std::stoi(line);
    }
  }
  std::cout << maxCalories << std::endl;
}

int main(int argc, char* argv[]) {
  if(argc != 2) {
    std::cout << "Usage: ./day_1.out inputfilename" << std::endl;
    return 0;
  }

  std::ifstream input(argv[1]);
  if(input.good()) {
    day_1(input);
  }
  input.close();
}
