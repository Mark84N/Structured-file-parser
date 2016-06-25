#include "node.h"
#include "variablenode.h"

// [1]
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
// [1]

// [2]
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

// [2]

// [3]
std::vector<Pr::sharedNodePtr> Pr::Node::getChildren() const{
    return _children;
}
// [3]

// [4]
std::pair<int, int> Pr::Node::getBodyPosition()const{
    return _bodyPosition;
}
// [4]

// [5]
Pr::weakNodePtr Pr::Node::getParent()const{
    return _parent;
}
// [5]

// [6]
int Pr::Node::getNesting() const{
    return _nesting;
}
// [6]

// [7]
Pr::Type Pr::Node::getNodeType()const{
    return _nodeType;
}
// [7]

// [8]
void Pr::Node::setBodyPosition
                (const std::pair<int, int> &positions){
    _bodyPosition = positions;
}
// [8]

// [9]
void Pr::Node::setParent(const weakNodePtr &parent){
    _parent = parent;
}
// [9]

// [10]
void Pr::Node::setNesting(int value){
    _nesting = value;
}
// [10]

// [11]
void Pr::Node::setNodeType(Pr::Type t){
    _nodeType = t;
}
// [11]

// [12]
void Pr::Node::addChild(const sharedNodePtr &child,
                        const std::weak_ptr<Pr::Node> &parent){

    if (child){
        auto newNode = child;
        newNode->setParent(parent);
        _children.push_back(newNode);
    }else{

    }
}
// [12]

// [13]
void Pr::Node::addVariable(const sharedVariablePtr &var){

    if (var){
        _dataVariables.push_back(var);
    }
}
// [13]

// [14]
void Pr::Node::setListName(const std::string str){

    if (!str.empty()){
        _listName = str;
    }
}

// [14]

// [15]
std::string Pr::Node::getListName()const{
    return _listName;
}
// [15]

// [16]
std::vector<Pr::sharedVariablePtr> Pr::Node::getVariables()const{
    return _dataVariables;
}
// [16]

// [17]
void Pr::Node::setId(int id){

    _id = id > 0? id : 0;
}
// [17]

// [18]
int Pr::Node::getId()const{
    return _id;
}
// [18]
