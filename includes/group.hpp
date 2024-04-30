#ifndef GROUP_HPP
#define GROUP_HPP

#include <ostream>
#include <vector>

#include "volunteer.hpp"

class Group {
public:
  void AddVolunteer(const Volunteer& vol);

  double GetAvgBuildingExp() const;

  int GetReturningMembers() const;

  double GetAvgStamina() const;

  friend std::ostream& operator<<(std::ostream& os, const Group& g_in);

  Volunteer& GetRandomVolunteer();

  std::vector<Volunteer> GetGroup() const;

private:
  // TODO create private member variable(s)
  std::vector<Volunteer> group_;
};

std::ostream& operator<<(std::ostream& os, const Group& g_in);

#endif
