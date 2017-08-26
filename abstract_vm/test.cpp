

#include <iostream>
#include <vector>

enum lol { First, Second };

int   main(void) {
  int i = 0;
  while (i < 12) {
    std::cout << i << std::endl;
    i++;
  }

  std::vector<std::string> messages;
  for (int i = 0; i < 5; i++) {
    messages.push_back(std::string("hi there"));
  }
  for (std::vector<std::string>::iterator it = messages.begin(); it < messages.end(); it++) {
    std::cout << *it << std::endl;
  }
  std::cout << First << std::endl;
  std::cout << Second << std::endl;
  return (0);
};