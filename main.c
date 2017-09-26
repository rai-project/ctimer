#include <chrono>
#include <iostream>
#include <thread>

#include "timer.h"

int main() {
  Profile prof = ProfileNew("my_eval", "stuff");

  {
    ProfileEntry entry1 = ProfileEntryNew("my_layer1", "stuff2");

    std::this_thread::sleep_for(std::chrono::milliseconds(1000));

    ProfileEntryEnd(entry1);
    ProfileAddEntry(prof, entry1);
  }

  {
    ProfileEntry entry2 = ProfileEntryNew("my_layer2", NULL);

    std::this_thread::sleep_for(std::chrono::milliseconds(1000));

    ProfileEntryEnd(entry2);

    ProfileAddEntry(prof, entry2);
  }

  ProfileEnd(prof);

  if (false) {
    char *str = ProfileRead(prof);

    std::cout << "profile = " << str << "\n";
    free(str);

  } else {
    ProfileDump(prof);
  }

  ProfileDelete(prof);
}
