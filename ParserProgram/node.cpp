#include "node.h"
using namespace Pr;

Node::Node()
    :
      _children(),
      _dataVariables(),
      _bodyPosition(),
      _nodeName(),
      _parent(nullptr),
      _nesting(0),
      _id(0)
{ }

Node::Node(Node * parent,
           const std::pair<int, int> &bodyPosition,
           const std::string &NodeName,
           int nesting,
           int id)
    :
      _children(),
      _dataVariables(),
      _bodyPosition(bodyPosition),
      _nodeName(NodeName),
      _parent(parent),
      _nesting(nesting),
      _id(id)
{ }

std::vector<SharedNodePtr> Node::getChildren() const
{
    return _children;
}

std::pair<int, int> Node::getBodyPosition()const
{
    return _bodyPosition;
}

Node* Node::getParent()const
{
    return _parent;
}

int Node::getNesting()const
{
    return _nesting;
}

void Node::setBodyPosition(const std::pair<int, int> &positions)
{
    _bodyPosition = positions;
}

void Node::setParent(Node *parent)
{
    _parent = parent;
}

void Node::setNesting(int value)
{
    _nesting = value;
}

void Node::addChild(const SharedNodePtr &child)
{
    if (child)
    {
        auto newNode = child;
        newNode->setParent(this);
        _children.push_back(newNode);
    }
}

void Node::addVariable(const SharedVariablePtr &var)
{
    if (var)
        _dataVariables.push_back(var);

}

void Node::setNodeName(const std::string str)
{
    if (!str.empty())
        _nodeName = str;
}

std::string Node::getNodeName()const
{
    return _nodeName;
}

std::vector<SharedVariablePtr> Node::getVariables()const
{
    return _dataVariables;
}

void Node::setId(int id)
{
    _id = id > 0? id : 0;
}

int Node::getId()const
{
    return _id;
}
