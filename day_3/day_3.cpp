#include<iostream>
#include<fstream>
#include<string>

int priority(char item) {
  if(item >= 'a' && item <= 'z') {
    return item - 'a' + 1;
  }
  if(item >= 'A' && item <= 'Z') {
    return item - 'A' + 27;
  }
  return -1;
}

char commonItem(std::string line) {
  for(uint i = 0; i < line.size() / 2; i++) {
    for(uint j = line.size() / 2; j < line.size(); j++) {
      if(line[i] == line[j]) {
        return line[i];
      }
    }
  }
  return '?';
}

void day_3(std::ifstream &input) {
  int total = 0;
  std::string line;
  while(getline(input, line)) {
    total += priority(commonItem(line));
  }
  std::cout << "Sum of priorities: " << total << std::endl;
}

int main(int argc, char* argv[]) {
  if(argc != 2) {
    std::cout << "Usage: ./day_3.out inputfilename" << std::endl;
    return 0;
  }

  std::ifstream input(argv[1]);
  if(input.good()) {
    day_3(input);
  }
  input.close();
}
