#include "nodetree.h"
using namespace Pr;

NodeTree::NodeTree()
    :
      _root(nullptr),
      _latestNode(nullptr)
{
}

void NodeTree::addNewNode(const Node &node, int Id)
{
    auto newNode = std::make_shared<Node>(node);
    newNode->setId(Id);

    int newNodeNest = node.getNesting();

    /* if no root present yet*/
    /* если корня еще нет */
    if (!_root)
    {
        _root = newNode;
        _latestNode = newNode;
        return;
    }

    int currentNest = _latestNode->getNesting();

    /* if nested below */
    /* если уровень вложенности нового узла больше нынешнего */
    if (newNodeNest > currentNest)
    {
        /* case: current is 1 level below the latestNode */
        /* случай: если вложено сразу под последним узлом */
        if (currentNest == newNodeNest - 1)
        {
            _latestNode->addChild(newNode);
            _latestNode = newNode;
        }
    }
    /* case: new node is the same level as the latestNode */
    /* случай: одинаковая вложенность с последним узлом */
    else if (newNodeNest == currentNest)
    {
        Node* commonParent = _latestNode->getParent();
        commonParent->addChild(newNode);

        _latestNode = newNode;
    }
    /* case: parent is somewhere upper */
    /* случай: вложеность - меньше чем у последнего узла, родитель где-то выше  */
    else
    {
        auto nodeUpperOneLevel = _latestNode->getParent();

        int parentNest = nodeUpperOneLevel->getNesting();

        while (parentNest < newNodeNest)
        {
            nodeUpperOneLevel = nodeUpperOneLevel->getParent();
            parentNest = nodeUpperOneLevel->getNesting();
        }
        /* once we're on the right level, then: */
        /* подняться до необходимого уровня, и: */

        auto commonParent = nodeUpperOneLevel->getParent();

        commonParent->addChild(newNode);
        _latestNode = newNode;
    }
}

SharedNodePtr NodeTree::getRoot()
{
    return _root;
}

SharedNodePtr NodeTree::getLatestNode()
{
    return _latestNode;
}
