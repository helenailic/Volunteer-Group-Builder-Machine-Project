#include <ctime>
#include <fstream>
#include <iostream>
#include <string>

#include "constants.hpp"
#include "group.hpp"

void Read(const std::string& volunteerInputfile,
          std::vector<Group>& all_groups,
          unsigned int num_volunteers) {
  unsigned int j = -1;
  std::ifstream ifs{volunteerInputfile};
  if (!ifs.is_open()) {
    std::cout << "couldn't open input file" << std::endl;
  }
  std::string name;
  int building_experience = 0;
  int physical_stamina = 0;
  int returning_num = -1;
  bool returning = false;
  for (unsigned int i = 0; i < num_volunteers; ++i) {
    if (i % kSizeGroups == 0) {
      all_groups.push_back(Group());
      j++;
    }
    ifs >> name >> building_experience >> physical_stamina >> returning_num;
    if (returning_num == 1) {
      returning = true;
    } else if (returning_num == 0) {
      returning = false;
    }
    all_groups.at(j).AddVolunteer(
        Volunteer{name, building_experience, physical_stamina, returning});
  }
}

bool GroupConditions(std::vector<Group> all_groups) {
  for (unsigned int i = 0; i < all_groups.size(); ++i) {
    // selecting a group which is a vector<Volunteers> and checking its
    // attributes
    Group& goi = all_groups.at(i);
    if (goi.GetAvgBuildingExp() < kMinAvgBuildingExp ||
        goi.GetAvgStamina() < kMinAvgStamina ||
        goi.GetReturningMembers() < kMinReturning) {
      return false;
    }
  }
  return true;
}

void Swap(unsigned int index1,
          unsigned int index2,
          std::vector<Group>& all_groups) {
  while (index1 == index2) {
    index1 = rand() % all_groups.size();
    index2 = rand() % all_groups.size();
  }

  Group& gr1 = all_groups.at(index1);
  Group& gr2 = all_groups.at(index2);

  Volunteer& v1 = gr1.GetRandomVolunteer();
  Volunteer& v2 = gr2.GetRandomVolunteer();
  std::swap(v1, v2);
}

void Write(unsigned int swap_iterations,
           std::vector<Group>& all_groups,
           const std::string& volunteerOutputfile) {
  std::ofstream ofs{volunteerOutputfile};
  if (!ofs.is_open()) {
    std::cout << "couldn't open output file" << std::endl;
  }
  if (swap_iterations > kMaxIterations) {
    std::cout << "No groups found." << std::endl;
  } else {
    for (unsigned int i = 0; i < all_groups.size(); ++i) {
      ofs << all_groups.at(i);
    }
  }
}

int main(int argc, char* argv[]) {
  srand(time(nullptr));
  std::string volunteer_inputfile;
  unsigned int num_volunteers = 0;
  std::string volunteer_outputfile;
  for (int i = 0; i < argc; ++i) {
    if (i == 1) {
      volunteer_inputfile = argv[1];
    } else if (i == 2) {
      num_volunteers = std::stoi(argv[2]);
    } else if (i == 3) {
      volunteer_outputfile = argv[3];
    }
  }
  std::vector<Group> all_groups;

  Read(volunteer_inputfile, all_groups, num_volunteers);

  unsigned int swap_iterations = 0;
  while (!(GroupConditions(all_groups)) && (swap_iterations < kMaxIterations)) {
    unsigned int index1 = rand() % all_groups.size();
    unsigned int index2 = rand() % all_groups.size();
    Swap(index1, index2, all_groups);
    swap_iterations++;
  }
  Write(swap_iterations, all_groups, volunteer_outputfile);
  return 0;
}
