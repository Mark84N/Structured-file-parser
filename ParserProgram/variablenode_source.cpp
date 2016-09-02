#include "node.h"
#include "variablenode.h"

// [1]
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
// [1]

// [2]
Pr::VariableNode::VariableNode(const std::string &name,
                               const weakNodePtr &parent,
                               int id):
    _variableName(name),
    _variableValue(),
    _parent(parent),
    _id(id),
    _varType(Pr::Type::DATA)
{ }
// [2]

// [3]
Pr::VariableNode::VariableNode():
    _variableName(),
    _variableValue(),
    _parent(),
    _id(0),
    _varType(Pr::Type::DATA)
{ }
// [3]

// [4]
std::string Pr::VariableNode::getVariableName()const{
    return _variableName;
}
// [4]

// [5]
std::string Pr::VariableNode::getVariableValue()const{
    return _variableValue;
}
// [5]

// [6]
Pr::weakNodePtr Pr::VariableNode::getParent()const{
    return _parent;
}
// [6]

// [7]
void Pr::VariableNode::setVariableName(const std::string name){

    if (!name.empty()){
        _variableName = name;
    }
}
// [7]

// [8]
void Pr::VariableNode::setParent(const weakNodePtr &parent){

    if (parent.lock()){
        _parent = parent;
    }
}
// [8]

// [9]
int Pr::VariableNode::getId()const{
    return _id;
}
// [9]
