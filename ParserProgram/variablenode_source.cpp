#include "node.h"
#include "variablenode.h"

Pr::VariableNode::VariableNode(const std::string &name,
                               const std::string &value,
                               weakNodePtr &parent,
                               int id,
                               Type varType):
    _variableName(name),
    _variableValue(value),
    _parent(parent),
    _id(id),
    _varType(varType)
{ }

Pr::VariableNode::VariableNode(const std::string &name,
                               const weakNodePtr &parent,
                               int id):
    _variableName(name),
    _variableValue(),
    _parent(parent),
    _id(id),
    _varType(Pr::Type::DATA)
{ }

Pr::VariableNode::VariableNode():
    _variableName(),
    _variableValue(),
    _parent(),
    _id(0),
    _varType(Pr::Type::DATA)
{ }

std::string Pr::VariableNode::getVariableName()const
{
    return _variableName;
}

std::string Pr::VariableNode::getVariableValue()const
{
    return _variableValue;
}

Pr::weakNodePtr Pr::VariableNode::getParent()const
{
    return _parent;
}

void Pr::VariableNode::setVariableName(const std::string name)
{
    if (!name.empty())
        _variableName = name;
}

void Pr::VariableNode::setParent(const weakNodePtr &parent)
{
    if (parent.lock())
        _parent = parent;
}

int Pr::VariableNode::getId()const
{
    return _id;
}
