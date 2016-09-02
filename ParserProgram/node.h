#ifndef NODE_H
#define NODE_H

#include "resources.h"

namespace Pr
{
    class Node
    {
    private:

        std::vector<sharedNodePtr>      _children;
        std::vector<sharedVariablePtr>  _dataVariables;
        std::pair<int, int>             _bodyPosition;
        std::string                     _nodeName;
        Node*                           _parent;
        int                             _nesting;
        int                             _id;

    public:

        Node();
        Node(Node * parent,
             const std::pair<int, int> &bodyPosition,
             const std::string &listName,
             int nesting,
             int id);

        ~Node()
        {
            std::cout << "\nNode id = " << _id << " is deleted\n";
        }

        std::vector<sharedNodePtr>      getChildren()const;
        std::vector<sharedVariablePtr>  getVariables()const;
        std::pair<int, int>             getBodyPosition()const;
        std::string                     getListName()const;
        Node *                          getParent()const;
        int                             getNesting()const;
        int                             getId()const;

        void setBodyPosition(const std::pair<int, int> &positions);
        void setParent(Node *parent);
        void setNesting(int value);
        void addChild(const sharedNodePtr &child);
        void addVariable(const sharedVariablePtr &var);
        void setListName(const std::string str);
        void setId(int id);
    };
}

#endif // NODE_H
