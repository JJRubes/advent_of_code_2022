#include<iostream>
#include<fstream>
#include<string>

int main(int argc, char* argv[]) {
  if(argc != 2) {
    std::cout << "Usage: ./day_4_part_2.out inputfilename" << std::endl;
    return 0;
  }

  std::ifstream input(argv[1]);
  if(!input.good()) {
    std::cerr << "Failed to open file " << argv[1] << std::endl;
    exit(1);
  }

  int count = 0;
  std::string line;
  while(input) {
    int range[2][2];
    char c; // used to eat -s and ,s
    input >> range[0][0] >> c >> range[0][1] >> c >> range[1][0] >> c >> range[1][1];
    if(range[0][0] <= range[1][0] && range[0][1] >= range[1][0]) {
      count++;
    } else if(range[0][0] >= range[1][0] && range[0][0] <= range[1][1]) {
      count++;
    }
  }
  std::cout << count << std::endl;
  input.close();
}
