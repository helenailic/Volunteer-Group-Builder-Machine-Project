#include "group.hpp"

#include <cstdlib>
#include <fstream>
#include <iostream>

#include "constants.hpp"
#include "volunteer.hpp"

// 2/ finish group class and member functions

// class that stores and evaluates combos of volunteers

void Group::AddVolunteer(const Volunteer& vol) {
  // adds volunteer passed into the function to the group
  group_.push_back(vol);
}

double Group::GetAvgBuildingExp() const {
  int sum = 0;
  double avg = 0;
  for (unsigned int i = 0; i < group_.size(); ++i) {
    sum += group_.at(i).GetBuildingExperience();
  }
  if (group_.empty()) {
    return 0;
  }
  avg = (double)sum / (double)group_.size();
  return avg;
}

double Group::GetAvgStamina() const {
  int sum = 0;
  double avg = 0;
  for (unsigned int i = 0; i < group_.size(); ++i) {
    sum += group_.at(i).GetPhysicalStamina();
  }
  if (group_.empty()) {
    return 0;
  }
  avg = (double)sum / (double)group_.size();
  return avg;
}

int Group::GetReturningMembers() const {
  int count = 0;
  for (unsigned int i = 0; i < group_.size(); ++i) {
    if (group_.at(i).IsReturning()) {
      count++;
    }
  }
  return count;
}

Volunteer& Group::GetRandomVolunteer() {
  // returns random volunteer from group
  // requires at least 1 member in group
  // note below on randomness
  return group_.at(rand() % group_.size());  // in range 0 to 4
}

std::vector<Volunteer> Group::GetGroup() const { return group_; }

std::ostream& operator<<(std::ostream& os, const Group& g_in) {
  // prints a group to the ostream passed in
  os << "Group:" << '\n';
  // how do I access the vector inside g_in? do I make a getter

  for (unsigned int i = 0; i < g_in.GetGroup().size(); ++i) {
    os << g_in.GetGroup().at(i).GetName() << '\n';
  }
  return os;
}
