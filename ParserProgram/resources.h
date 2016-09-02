#ifndef RESOURCES_H
#define RESOURCES_H

#include <string>
#include <iterator>
#include <vector>
#include <fstream>
#include <iostream>
#include <memory>
#include <algorithm>
#include <regex>
#include <exception>

namespace Pr
{S
class Node;
class VariableNode;
class NodeTree;

using sharedNodePtr = std::shared_ptr<Pr::Node>;
using sharedVariablePtr = std::shared_ptr<Pr::VariableNode>;
using weakNodePtr = std::weak_ptr<Pr::Node>;
using sharedTreePtr = std::shared_ptr<Pr::NodeTree>;

enum class Type{LIST, DATA};

}

#endif // RESOURCES_H
