#include <chrono>
#include <iostream>
#include <thread>

#include "timer.h"

int main() {
  auto prof = ProfileNew("my_eval");

  auto entry = ProfileEntryNew("my_layer");

  std::this_thread::sleep_for(std::chrono::milliseconds(1000));

  ProfileEntryEnd(entry);

  ProfileAddEntry(prof, entry);

  ProfileEnd(prof);

  auto str = ProfileRead(prof);

  std::cout << "profile = " << str << "\n";

  ProfileDelete(prof);
}
