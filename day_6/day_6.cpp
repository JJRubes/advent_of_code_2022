#include<fstream>
#include<iostream>

char circular_buffer[3];
bool copy(char c) {
  for(int i = 0; i < 3; i++) {
    for(int j = i + 1; j < 3; j++) {
      // std::cout << "[" << i << "] ?= [" << j << "] : " << circular_buffer[i] << " ?= " << circular_buffer[j] << std::endl;
      if(circular_buffer[i] == circular_buffer[j]) {
        return true;
      }
    }
    // std::cout << "c ?= [" << i << "] : " << c << " ?= " << circular_buffer[i] << std::endl;
    if(circular_buffer[i] == c) {
      return true;
    }
  }
  return false;
}

int main(int argc, char* argv[]) {
  if(argc != 2) {
    std::cout << "Usage: ./day_6.out inputfilename" << std::endl;
    return 0;
  }

  std::ifstream input(argv[1]);
  if(!input.good()) {
    std::cerr << "Failed to open file " << argv[1] << std::endl;
    exit(1);
  }

  circular_buffer[0] = input.get();
  circular_buffer[1] = input.get();
  circular_buffer[2] = input.get();
  int read = 3;
  bool cont = true;
  while(input && cont) {
    char c = input.get();
    // std::cout << "read " << c << " at " << read << std::endl;
    cont = copy(c);
    circular_buffer[read % 3] = c;
    read++;
  }
  if(!cont) {
    std::cout << "Started at " << read << std::endl;
  } else {
    std::cout << "No start" << std::endl;
  }
}
