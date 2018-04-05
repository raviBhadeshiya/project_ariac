/**
 * @file Manager.hpp
 * @author     Ravi Bhadeshiya
 * @version    2.0
 * @brief      Class for controlling ariac order
 *
 * @copyright  BSD 3-Clause License (c) 2018 Ravi Bhadeshiya
 *
 * Redistribution and use in source and binary forms, with or without
modification, are permitted provided that the following conditions are met:

* Redistributions of source code must retain the above copyright notice, this
list of conditions and the following disclaimer.

* Redistributions in binary form must reproduce the above copyright notice, this
list of conditions and the following disclaimer in the documentation and/or
other materials provided with the distribution.

* Neither the name of the copyright holder nor the names of its contributors may
be used to endorse or promote products derived from this software without
specific prior written permission.

THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS" AND
ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED
WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE LIABLE FOR
ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES
(INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES;
LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON
ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
(INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS
SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
*/
#pragma once
#include <geometry_msgs/Pose.h>
#include <cmath>
#include <string>
namespace peoject_ariac {

struct Part {
  std::string type_;
  geometry_msgs::Pose pose_;
  bool operator==(const Part& cmp) const;
  float distance(const Part& rhs);
};

float Part::distance(const Part& rhs) {
  return std::sqrt(std::pow(pose_.position.x - rhs.pose_.position.x, 2.0) +
                   std::pow(pose_.position.y - rhs.pose_.position.y, 2.0) +
                   std::pow(pose_.position.z - rhs.pose_.position.z, 2.0));
}

bool Part::operator==(const Part& cmp) const {
  return (this->type_.compare(cmp.type_) == 0) && (this->distance(cmp) < 0.01);
}

}  // namespace peoject_ariac
