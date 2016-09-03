#ifndef PARSEENGINE_H
#define PARSEENGINE_H

#include "resources.h"
#include "node.h"
#include "variablenode.h"
#include "nodetree.h"

namespace Pr {

class ParseEngine
{
public:

    ParseEngine(const std::string &sourceString);
    void fillTree(const SharedTreePtr& tree);

private:

    std::string _sourceString;
    static int ID;

    std::vector<Node>   getNodesWithNesting();
    BracesIndexes       getNodesStartEndPositions();
    int                 calculateNodeNesting(int position, const BracesIndexes &vector);

    void initTreeWithNodes(SharedTreePtr treePtr, const std::vector<Node> &nodes);
    void parseNextNode(const SharedNodePtr &node);
    void retrieveNodeNameAndVariables(const std::string &s, const SharedNodePtr &node);
    void parsePrefix(const std::string &prefix, const std::regex &variableRegexp, Node *parent);
    void parseSuffix(const std::string &suffix,
                     const std::regex &variableRegexp,
                     const std::regex &listRegexp,
                     const SharedNodePtr &node);
};
}

#endif // PARSEENGINE_H
