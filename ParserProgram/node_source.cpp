#include "node.h"
#include "variablenode.h"

Pr::Node::Node():
    _children(),
    _dataVariables(),
    _parent(),
    _bodyPosition(),
    _listName(),
    _nesting(0),
    _id(0),
    _nodeType(Pr::Type::LIST)

{ }

Pr::Node::Node(const std::weak_ptr<Pr::Node> &parent,
               const std::pair<int, int> &bodyPosition,
               const std::string &listName,
               int nesting,
               int id,
               Type nodeType):

    _children(),
    _dataVariables(),
    _parent(parent),
    _bodyPosition(bodyPosition),
    _listName(listName),
    _nesting(nesting),
    _id(id),
    _nodeType(nodeType)
{ }

std::vector<Pr::sharedNodePtr> Pr::Node::getChildren() const
{
    return _children;
}

std::pair<int, int> Pr::Node::getBodyPosition()const
{
    return _bodyPosition;
}

Pr::weakNodePtr Pr::Node::getParent()const
{
    return _parent;
}

int Pr::Node::getNesting() const
{
    return _nesting;
}

Pr::Type Pr::Node::getNodeType()const
{
    return _nodeType;
}

void Pr::Node::setBodyPosition
(const std::pair<int, int> &positions)
{
    _bodyPosition = positions;
}

void Pr::Node::setParent(const weakNodePtr &parent)
{
    _parent = parent;
}

void Pr::Node::setNesting(int value)
{
    _nesting = value;
}

void Pr::Node::setNodeType(Pr::Type t)
{
    _nodeType = t;
}

void Pr::Node::addChild(const sharedNodePtr &child,
                        const std::weak_ptr<Pr::Node> &parent){
    if (child)
    {
        auto newNode = child;
        newNode->setParent(parent);
        _children.push_back(newNode);
    }
}

void Pr::Node::addVariable(const sharedVariablePtr &var)
{
    if (var)
        _dataVariables.push_back(var);

}

void Pr::Node::setListName(const std::string str)
{
    if (!str.empty())
        _listName = str;
}

std::string Pr::Node::getListName()const
{
    return _listName;
}

std::vector<Pr::sharedVariablePtr> Pr::Node::getVariables()const
{
    return _dataVariables;
}

void Pr::Node::setId(int id){

    _id = id > 0? id : 0;
}

int Pr::Node::getId()const{
    return _id;
}
