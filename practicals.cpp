#include <iostream>
#include <string>
#include <vector>

const int NUM_DAYS = 5;   // number of weekdays
const int NUM_SLOTS = 8;  // number of time slots per day

// structure to represent a practical session
struct Practical {
  std::string subject;   // name of the subject
  int duration;          // duration of the practical in hours
  int group;             // group number of the students
};

int main() {
  // create a 2D array to represent the timetable
  std::vector<std::vector<Practical>> timetable(NUM_DAYS, std::vector<Practical>(NUM_SLOTS));

  // list of practical sessions to be scheduled
  std::vector<Practical> practicals = {
    {"Physics", 3, 1},
    {"Biology", 2, 2},
    {"Chemistry", 3, 3},
    {"Computer Science", 2, 1},
    {"Mathematics", 2, 2},
    {"Electronics", 3, 3}
  };

  // schedule the practical sessions in the timetable
  for (const Practical& p : practicals) {
    // find the first available slot for the practical
    bool scheduled = false;
    for (int d = 0; d < NUM_DAYS; d++) {
      for (int s = 0; s < NUM_SLOTS; s++) {
        if (timetable[d][s].subject.empty()) {
          // check if there are enough consecutive slots available
          bool slot_available = true;
          for (int i = s; i < s + p.duration; i++) {
            if (i >= NUM_SLOTS || !timetable[d][i].subject.empty()) {
              slot_available = false;
              break;
            }
          }
          if (slot_available) {
            // schedule the practical at the first available slot
            for (int i = s; i < s + p.duration; i++) {
              timetable[d][i] = p;
            }
            scheduled = true;
            break;
          }
        }
      }
      if (scheduled) {
        break;
      }
    }
  }

  // print the timetable
  for (int d = 0; d < NUM_DAYS; d++) {
    std::cout << "Day " << d + 1 << ": ";
    for (int s = 0; s < NUM_SLOTS; s++) {
      std::cout << timetable[d][s].subject << " ";
    }
    std::cout << std::endl;
  }

  return 0;
}
