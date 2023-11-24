#include<fstream>
#include<iostream>

#define MARKER_SIZE 14
#define BUFFER_SIZE (MARKER_SIZE - 1)

char circular_buffer[BUFFER_SIZE];
bool copy(char c) {
  for(int i = 0; i < BUFFER_SIZE; i++) {
    for(int j = i + 1; j < BUFFER_SIZE; j++) {
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

  for(int i = 0; i < BUFFER_SIZE; i++) {
    circular_buffer[i] = input.get();
  }
  int read = BUFFER_SIZE;
  bool cont = true;
  while(input && cont) {
    char c = input.get();
    // std::cout << "read " << c << " at " << read << std::endl;
    cont = copy(c);
    circular_buffer[read % BUFFER_SIZE] = c;
    read++;
  }
  if(!cont) {
    std::cout << "Started at " << read << std::endl;
  } else {
    std::cout << "No start" << std::endl;
  }
}
