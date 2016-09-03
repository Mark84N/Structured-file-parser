#ifndef NODETREE_H
#define NODETREE_H

#include "resources.h"
#include "node.h"
#include "variablenode.h"

namespace Pr
{
class NodeTree
{
public:

    NodeTree();
    SharedNodePtr   getRoot();
    SharedNodePtr   getLatestNode();
    void            addNewNode(const Node &node, int Id);

private:

    SharedNodePtr _root;
    SharedNodePtr _latestNode;
};
}
#endif // NODETREE_H
