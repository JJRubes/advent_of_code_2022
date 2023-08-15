#include<iostream>
#include<fstream>
#include<string>
#include<set>

int priority(char item) {
  if(item >= 'a' && item <= 'z') {
    return item - 'a' + 1;
  }
  if(item >= 'A' && item <= 'Z') {
    return item - 'A' + 27;
  }
  return -1;
}

void day_3_part_2(std::ifstream &input) {
  int total = 0;
  std::set<char> items;
  std::set<char> consistentItems;
  std::string rucksack1, rucksack2, rucksack3;
  while(getline(input, rucksack1) && getline(input, rucksack2) && getline(input, rucksack3)) {
    items.clear();
    consistentItems.clear();
    for(char i : rucksack1) {
      items.insert(i);
    }
    for(char i : rucksack2) {
      if(items.find(i) != items.end()) {
        consistentItems.insert(i);
      }
    }
    for(char i : rucksack3) {
      if(consistentItems.find(i) != consistentItems.end()) {
        total += priority(i);
        break;
      }
    }
  }
  std::cout << "Sum of priorities: " << total << std::endl;
}

int main(int argc, char* argv[]) {
  if(argc != 2) {
    std::cout << "Usage: ./day_3_part_2.out inputfilename" << std::endl;
    return 0;
  }

  std::ifstream input(argv[1]);
  if(input.good()) {
    day_3_part_2(input);
  }
  input.close();
}
