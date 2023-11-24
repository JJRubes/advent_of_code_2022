#include<iostream>
#include<fstream>
#include<stack>
#include<string>
#include<vector>

int main(int argc, char* argv[]) {
  if(argc != 2) {
    std::cout << "Usage: ./day_5.out inputfilename" << std::endl;
    return 0;
  }

  std::ifstream input(argv[1]);
  if(!input.good()) {
    std::cerr << "Failed to open file " << argv[1] << std::endl;
    exit(1);
  }

  std::vector<std::string> start_position;
  std::string line;
  getline(input, line);
  int num_stacks = 0;
  while(!line.empty()) {
    start_position.push_back(line);
    getline(input, line);
    int n = (line.length() + 1) / 4;
    if(n > num_stacks) {
      num_stacks = n;
    }
  }

  std::vector<std::stack<char>> harbour;
  for(int i = 0; i < num_stacks; i++) {
    harbour.push_back(std::stack<char>());
  }

  for(int i = start_position.size() - 2; i >= 0; i--) {
    std::string layer = start_position[i];
    for(int j = 0; j < (layer.length() + 1) / 4; j++) {
      char c = layer[j * 4 + 1];
      if(c != ' ') {
        harbour[j].push(c);
      }
    }
  }

  while(!input.eof()) {
    int count, start, end;
    // skip move_
    input.seekg(5, std::ios_base::cur);
    input >> count;
    // skip _from_
    input.seekg(6, std::ios_base::cur);
    input >> start;
    // skip _to_
    input.seekg(4, std::ios_base::cur);
    input >> end;
    // why the hell do i need to do this???
    while(input.peek() == '\n') {
      input.get();
    }

    start--;
    end--;

    for(int i = 0; i < count; i++) {
      harbour[end].push(harbour[start].top());
      harbour[start].pop();
    }
  }
  for(int i = 0; i < harbour.size(); i++) {
    if(harbour[i].size() != 0) {
      std::cout << harbour[i].top();
    }
  }
  std::cout << std::endl;
  input.close();
}
