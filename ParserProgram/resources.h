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
{
class Node;
class VariableNode;
class NodeTree;
class ParseEngine;
class ITreeWriter;
class XMLTreeWriter;

using SharedTreeWriter = std::shared_ptr<ITreeWriter>;
using SharedParseEnginePtr = std::shared_ptr<ParseEngine>;
using SharedNodePtr = std::shared_ptr<Node>;
using SharedVariablePtr = std::shared_ptr<VariableNode>;
using SharedTreePtr = std::shared_ptr<NodeTree>;
using BracesIndexes = std::vector<std::pair<int, int>>;
}

#endif // RESOURCES_H
