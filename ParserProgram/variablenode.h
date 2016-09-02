#ifndef VARIABLENODE_H
#define VARIABLENODE_H

#include "resources.h"

namespace Pr
{
    class VariableNode
    {
    private:

        std::string _variableName;
        std::string _variableValue;
        Node* _parent;
        int _id;
        Type _varType;

    public:

        VariableNode(const std::string &name,
                     Node* parent,
                     int id);
        VariableNode(const std::string &name,
                     const std::string &value,
                     Node *parent,
                     int id,
                     Type varType);
        VariableNode();
        ~VariableNode()
        {
            std::cout << "\Variable id = " << _id << " is deleted\n";
        }


        std::string getVariableName()const;
        std::string getVariableValue()const;
        Node* getParent()const;
        int getId()const;

        void setVariableName(const std::string name);
        void setParent(Node *parent);
    };

}
#endif // VARIABLENODE_H
