#include "nodetree.h"
#include "node.h"
#include "variablenode.h"

Pr::NodeTree::NodeTree(const std::vector<Pr::Node> &nodes,
                       const std::string &source):
    _root(nullptr),
    _latestNode(nullptr)
{
    if (source.empty())
    {
        throw std::invalid_argument("Source string is empty!");
    }

    _sourceString = source;
    initTreeWithNodes(nodes);
    initNodesWithRawData(source);
}

void Pr::NodeTree::addNewNode(const Pr::Node &node)
{
    auto newNode =
            std::make_shared<Pr::Node>(node);
    newNode->setId(_currentId++);

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
    /* случай: вложеность - выше чем у последнего узла, родитель где-то выше  */
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

void Pr::NodeTree::initTreeWithNodes(const std::vector<Pr::Node> &nodes)
{
    for (auto x:nodes)
        this->addNewNode(x);
}

void Pr::NodeTree::initNodesWithRawData(const std::string &source)
{
    insertHere(this->_root, source);
}

void Pr::NodeTree::insertHere(const sharedNodePtr &node,
                const std::string &source)
{
        /* for root node */
        /* для корневого узла */
        //if (!node->getParent().lock())
        if (!node->getParent())
        {
            /* get raw string to parse then */
            /* получить необработанную строку для парсинга */

            std::string rawData;
            std::copy(source.begin(),
                      source.begin() + node->getBodyPosition().second,
                      std::back_inserter<std::string>(rawData));

            retrieveListNameAndVariables(rawData, node);
        }
        else
        {
            Node* parent =  node->getParent();
            auto siblings = parent->getChildren();

            int startOffset = parent->getBodyPosition().first;
            int tempOldOffset = startOffset;
            int endOffset = startOffset;

            /* parse either from the parent's opening brace '{' */
            /* or from the previous sibling's brace '}' */

            /* парсить от начала тела родителя '{' */
            /* или от конца тела брата '}' */
            if (!siblings.empty())
            {
                for (int i = 0; i < siblings.size(); i++)
                {
                    if ((siblings.size() == 1) ||
                           (node == siblings[siblings.size()-1]))
                    {
                        endOffset = parent->getBodyPosition().second;
                    }
                    if (node == siblings[i] && i >= 1)
                    {
                        auto pos = siblings[i-1]->getBodyPosition();
                        startOffset = pos.second;
                    }
                }
            }

            /* get raw string to parse then */
            /* получить необработанную строку для парсинга */

            std::string rawData;

            if (tempOldOffset != endOffset)
            {
                std::copy(source.begin() + startOffset,
                          source.begin() + endOffset,
                          std::back_inserter<std::string>(rawData));
            }
            else
            {
                std::copy(source.begin() + startOffset,
                          source.begin() + node->getBodyPosition().second,
                          std::back_inserter<std::string>(rawData));
            }

            retrieveListNameAndVariables(rawData, node);
        }

        /* get done with the children of the current node */
        /* продолжить на дочерних узлах */
        auto children = node->getChildren();

        if (!children.empty())
        {
            for (auto nextChild:children)
                insertHere(nextChild, source);
        }
    }

void Pr::NodeTree::retrieveListNameAndVariables(const std::string &s,
                                                const sharedNodePtr &node){
    std::smatch sm;
    std::string name;
    std::string prefix;
    std::string suffix;
    std::regex listRegexp("([^\\}\\s\\{][\\w_\\d]*) = \\{");
    std::regex variableRegexp("([^\\d\\s][_a-zA-Z0-9]*) = \"([^\"]+)\"");

    /* get the name of the current node (list) */
    /* получить имя узла (списка) */
    if (std::regex_search(s, sm, listRegexp))
    {
        name = sm[1].str();

        std::regex leftDigitAssert("([\\d]+)(.+)");

        if (std::regex_search(name, leftDigitAssert))
        {
            throw std::invalid_argument("Bad namings: list's name can't start from digit (" +
                                        name + ")");
        }

        prefix = sm.prefix();
        suffix = sm.suffix();
    }

    node->setListName(name);

    Node* parent = node->getParent();

    /* if prefix contains variables - they belong to parent */
    /* если в префиксе найдены переменные - присвоить их родителю */

    if (prefix.length() > 2) // don't consider the garbage: spaces or brace '{'
    {
        parsePrefix(prefix, variableRegexp, parent);
    }

    /* collect variables, that current node owns */
    /* собрать переменные принадлежащие текущему узлу (списку) */
    if (!suffix.empty())
    {
        parseSuffix(suffix, variableRegexp, listRegexp, node);
    }
}

Pr::sharedNodePtr Pr::NodeTree::getRoot()
{
    return _root;
}

void Pr::NodeTree::showChildren(const Pr::sharedNodePtr &node,
                                std::ostream &os)
{
    const std::vector<Pr::sharedNodePtr> children =
        node->getChildren();

    auto vars = node->getVariables();
    int nest = node->getNesting();
    int id = node->getId();

    showOffset(os, nest, "---");

    if (node != _root)
    {
        int parentId = //node->getParent().lock()->getId();
        node->getParent()->getId();
        os << "Id: " << id << ", ";
        os << "Parent id: " << parentId << ", ";
        os << "Name: " << node->getListName() << "\n";

    }
    else
    {
        os << "Id: " << id << ", ";
        os << "Parent id: " << "not available (root)" << ", ";
        os << "Name: " << node->getListName() << "\n";
    }
    if (!vars.empty())
    {
        showOffset(os, nest, "   ");
        os << "Variables:\n";

        for (auto tempVar:vars)
        {
            showOffset(os, nest, "   ");
            os << "Variable id: " << tempVar->getId() << ", ";
            os << "Parent id: " << tempVar->getParent()->getId();//.lock()->getId() << ", ";
            os << "Name: " << tempVar->getVariableName() << ", ";
            os << "Value: "<< tempVar->getVariableValue() << "\n";
        }
    }
    if (!children.empty())
    {
        for (auto nodeChild:children)
            showChildren(nodeChild, os);
    }
}

int Pr::NodeTree::_currentId = 1;

void Pr::NodeTree::parsePrefix(const std::string &prefix,
                               const std::regex &variableRegexp,
                               Node *parent){

    for(std::sregex_iterator it =
        std::sregex_iterator(prefix.begin(),prefix.end(), variableRegexp);
        it != std::sregex_iterator ();
        it++)
    {
        std::smatch s = *it;
        auto data = std::make_shared<Pr::VariableNode>
                            (Pr::VariableNode(s[1].str(),
                                              s[2].str(),
                                              parent,
                                              this->_currentId++,
                                              Pr::Type::DATA));
        parent->addVariable(data);
    }
}

void Pr::NodeTree::parseSuffix(const std::string &suffix,
                               const std::regex &variableRegexp,
                               const std::regex &listRegexp,
                               const Pr::sharedNodePtr &node)
{
    std::smatch sm;

    if (!std::regex_search(suffix, sm, listRegexp)){

        auto listBodyEnd = suffix.find_first_of('}');

        if (listBodyEnd != std::string::npos)
        {
            for(std::sregex_iterator it =
                std::sregex_iterator(suffix.begin(), suffix.end(), variableRegexp);
                it != std::sregex_iterator();
                it++)
            {

                std::smatch s = *it;
                Node *parentNode = node.get();
                auto data = std::make_shared<Pr::VariableNode>
                                    (Pr::VariableNode(s[1].str(),
                                                      s[2].str(),
                                                      parentNode,
                                                      _currentId++,
                                                      Pr::Type::DATA));

               if (s.position(0) < listBodyEnd)
               {
                    node->addVariable(data);
                    data->setParent(parentNode);
               }
            }
        }
    }
    /* collect trailing variables, that parent owns */
    /* собрать переменные за текущим узлом. они принадлежат родителю,
     * и только родитель попадает в этот else*/
    else
    {
        auto children = node->getChildren();
        Pr::sharedNodePtr last = *children.rbegin();

        int childEnd = last->getBodyPosition().second;
        int currentNodeEnd = node->getBodyPosition().second;

        for(std::sregex_iterator it =
            std::sregex_iterator(this->_sourceString.begin() + childEnd,
                             this->_sourceString.begin() + currentNodeEnd,
                             variableRegexp);
        it != std::sregex_iterator();
        it++)
        {

            std::smatch s = *it;
            Node *currentNode = node.get();
            auto data = std::make_shared<Pr::VariableNode>
                                (Pr::VariableNode(s[1].str(),
                                              s[2].str(),
                                              currentNode,
                                              _currentId++,
                                              Pr::Type::DATA));
            node->addVariable(data);
        }
    }
}

void Pr::NodeTree::printOut(std::ostream &os)
{
    showChildren(this->_root, os);
}

void Pr::NodeTree::showOffset(std::ostream &os, int n, const char* ch)
{
    for (int i = n; i > 0; i--)
        os << ch;

}
