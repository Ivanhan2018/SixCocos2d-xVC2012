#include <iostream>
#include <string>
#include <list>
#include <algorithm>
using namespace std;

/*
root@iZ14rcmneyrcltZ:~/cpptest# g++ -o for_each for_each.cpp
root@iZ14rcmneyrcltZ:~/cpptest# ./for_each
pineapple
apple
carrot
pumpkin
potato
*/
void PrintIt (string& StringToPrint) {
  cout << StringToPrint << endl;
}

int main (void) {
  list<string> FruitAndVegetables;
  FruitAndVegetables.push_back("carrot");
  FruitAndVegetables.push_back("pumpkin");
  FruitAndVegetables.push_back("potato");
  FruitAndVegetables.push_front("apple");
  FruitAndVegetables.push_front("pineapple");

  for_each(FruitAndVegetables.begin(), FruitAndVegetables.end(), PrintIt);
  return 0;
}