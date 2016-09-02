#ifndef NODETREE_H
#define NODETREE_H

#include "resources.h"

namespace Pr
{
    class NodeTree
    {
    private:

        sharedNodePtr _root;
        sharedNodePtr _latestNode;
        std::string _sourceString;
        static int _currentId;

        void retrieveListNameAndVariables(const std::string &s,
                                          const sharedNodePtr &node);
        void insertHere(const sharedNodePtr &node,
                        const std::string &source);
        void parsePrefix(const std::string &prefix,
                         const std::regex &variableRegexp,
                         weakNodePtr &parent);
        void parseSuffix(const std::string &suffix,
                         const std::regex &variableRegexp,
                         const std::regex &listRegexp,
                         const Pr::sharedNodePtr &node);
        void showChildren(const std::shared_ptr<Pr::Node> &node,
                          std::ostream &os);
        void showOffset(std::ostream &os, int n, const char* ch);
        void initTreeWithNodes(const std::vector<Pr::Node> &nodes);
        void initNodesWithRawData(const std::string &source);

    public:

        NodeTree(const std::vector<Pr::Node> &nodes, const std::string &source);

        void addNewNode(const Pr::Node &node);
        sharedNodePtr getRoot();
        void printOut(std::ostream &os);

    };
}
#endif // NODETREE_H
