#ifndef VARIABLENODE_H
#define VARIABLENODE_H

#include "resources.h"

namespace Pr{

    class VariableNode{

    private:

        std::string _variableName;
        std::string _variableValue;
        weakNodePtr _parent;
        int _id;
        Pr::Type _varType;

    public:

        VariableNode(const std::string &name,
                     const weakNodePtr &parent,
                     int id);
        VariableNode(const std::string &name,
                     const std::string &value,
                     weakNodePtr &parent,
                     int id,
                     Pr::Type varType);
        VariableNode();

        std::string getVariableName()const;
        std::string getVariableValue()const;
        weakNodePtr getParent()const;
        int getId()const;

        void setVariableName(const std::string name);
        void setParent(const weakNodePtr &parent);
    };

}
#endif // VARIABLENODE_H
