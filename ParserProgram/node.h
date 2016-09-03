#ifndef NODE_H
#define NODE_H

#include "resources.h"
#include "variablenode.h"

namespace Pr
{
class Node
{
public:

    Node();
    Node(Node * parent,
         const std::pair<int, int> &bodyPosition,
         const std::string &NodeName,
         int nesting,
         int id);

    std::vector<SharedNodePtr>      getChildren()const;
    std::vector<SharedVariablePtr>  getVariables()const;
    std::pair<int, int>             getBodyPosition()const;
    std::string                     getNodeName()const;
    Node *                          getParent()const;
    int                             getNesting()const;
    int                             getId()const;

    void setBodyPosition(const std::pair<int, int> &positions);
    void setParent(Node *parent);
    void setNesting(int value);
    void addChild(const SharedNodePtr &child);
    void addVariable(const SharedVariablePtr &var);
    void setNodeName(const std::string str);
    void setId(int id);

private:

    std::vector<SharedNodePtr>      _children;
    std::vector<SharedVariablePtr>  _dataVariables;
    std::pair<int, int>             _bodyPosition;
    std::string                     _nodeName;
    Node*                           _parent;
    int                             _nesting;
    int                             _id;
};
}

#endif // NODE_H
