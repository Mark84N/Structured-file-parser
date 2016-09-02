#ifndef NODE_H
#define NODE_H

#include "resources.h"

namespace Pr
{
    class Node
    {
    private:

        std::vector<sharedNodePtr> _children;
        std::vector<sharedVariablePtr> _dataVariables;
        weakNodePtr _parent;
        std::pair<int, int> _bodyPosition;
        std::string _listName;
        int _nesting;
        int _id;
        Type _nodeType;

    public:

        Node();
        Node(const weakNodePtr &parent,
             const std::pair<int, int> &bodyPosition,
             const std::string &listName,
             int nesting,
             int id,
             Type nodeType);

        std::vector<sharedNodePtr> getChildren()const;
        std::pair<int, int> getBodyPosition()const;
        weakNodePtr getParent()const;
        int getNesting()const;
        Type getNodeType()const;
        std::string getListName()const;
        std::vector<sharedVariablePtr> getVariables()const;
        int getId()const;

        void setBodyPosition(const std::pair<int, int> &positions);
        void setParent(const weakNodePtr &parent);
        void setNesting(int value);
        void setNodeType(Type t);
        void addChild(const sharedNodePtr &child,
                      const weakNodePtr &parent);
        void addVariable(const sharedVariablePtr &var);
        void setListName(const std::string str);
        void setId(int id);
    };
}

#endif // NODE_H
