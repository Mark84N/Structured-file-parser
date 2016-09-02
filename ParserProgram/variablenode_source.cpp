#include "node.h"
#include "variablenode.h"

using namespace  Pr;

VariableNode::VariableNode(const std::string &name,
                               const std::string &value,
                               Node* parent,
                               int id,
                               Type varType):
    _variableName(name),
    _variableValue(value),
    _parent(parent),
    _id(id),
    _varType(varType)
{ }

VariableNode::VariableNode(const std::string &name,
                               Node *parent,
                               int id):
    _variableName(name),
    _variableValue(),
    _parent(parent),
    _id(id),
    _varType(Type::DATA)
{ }

VariableNode::VariableNode():
    _variableName(),
    _variableValue(),
    _parent(nullptr),
    _id(0),
    _varType(Type::DATA)
{ }

std::string VariableNode::getVariableName()const
{
    return _variableName;
}

std::string VariableNode::getVariableValue()const
{
    return _variableValue;
}

Node* VariableNode::getParent()const
{
    return _parent;
}

void VariableNode::setVariableName(const std::string name)
{
    if (!name.empty())
        _variableName = name;
}

void VariableNode::setParent(Node *parent)
{
    //if (parent.lock())
    if (parent)
        _parent = parent;
}

int VariableNode::getId()const
{
    return _id;
}
