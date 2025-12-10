
#include <iostream>

void cinGetlineBug() {
  double pi;
  double tao;
  std::string name;
  std::cin >> pi;
  std::getline(std::cin, name);
  // std::cin >> name;
  std::cin >> tao;
  std::cout << "my name is : " << name << " tao is : " << tao
            << " pi is : " << pi << '\n';
}

int main() {
    // std::cout << "test" << std::endl;
    // int i;
    // std::cin >> i;
    // std::cout << i << std::endl;
    cinGetlineBug();
    return 0;
}