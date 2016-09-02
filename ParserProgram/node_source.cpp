#include "node.h"
#include "variablenode.h"

using namespace Pr;

Node::Node():
    _children(),
    _dataVariables(),
    _parent(nullptr),
    _bodyPosition(),
    _nodeName(),
    _nesting(0),
    _id(0),
    _nodeType(Type::LIST)

{ }

Node::Node(Node * parent,
               const std::pair<int, int> &bodyPosition,
               const std::string &listName,
               int nesting,
               int id,
               Type nodeType):

    _children(),
    _dataVariables(),
    _parent(parent),
    _bodyPosition(bodyPosition),
    _nodeName(listName),
    _nesting(nesting),
    _id(id),
    _nodeType(nodeType)
{ }

std::vector<sharedNodePtr> Node::getChildren() const
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

Type Node::getNodeType()const
{
    return _nodeType;
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

void Node::setNodeType(Type t)
{
    _nodeType = t;
}

void Node::addChild(const sharedNodePtr &child)
{
    if (child)
    {
        auto newNode = child;
        newNode->setParent(this);
        _children.push_back(newNode);
    }
}

void Node::addVariable(const sharedVariablePtr &var)
{
    if (var)
        _dataVariables.push_back(var);

}

void Node::setListName(const std::string str)
{
    if (!str.empty())
        _nodeName = str;
}

std::string Node::getListName()const
{
    return _nodeName;
}

std::vector<sharedVariablePtr> Node::getVariables()const
{
    return _dataVariables;
}

void Node::setId(int id){

    _id = id > 0? id : 0;
}

int Node::getId()const{
    return _id;
}
