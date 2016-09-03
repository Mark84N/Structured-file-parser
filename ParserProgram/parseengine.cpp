#include "parseengine.h"
using namespace Pr;

int ParseEngine::ID = 1;

ParseEngine::ParseEngine(const std::string &sourceString)
    :_sourceString(sourceString)
{

}

void ParseEngine::fillTree(const SharedTreePtr &tree)
{
    auto notParsedNodesVector = getNodesWithNesting();
    initTreeWithNodes(tree, notParsedNodesVector);

    parseNextNode(tree->getRoot());
}

std::vector<Node> ParseEngine::getNodesWithNesting()
{
    std::vector<Node> nodes;
    std::vector<std::pair<int, int>> positions = getNodesStartEndPositions();

    for (int i = 0; i < positions.size(); i++)
    {
        Node node;

        node.setNesting(calculateNodeNesting(i,positions));
        node.setBodyPosition((positions[i]));

        nodes.push_back(node);
    }

    return nodes;
}

BracesIndexes ParseEngine::getNodesStartEndPositions()
{
    std::vector<int>beginnings;
    std::vector<std::pair<int, int>> positions;

    int braceAssert = 0;

    for (int i = 0; i < _sourceString.length(); i++)
    {
        if (_sourceString[i] == '{')
        {
            beginnings.push_back(i);
            braceAssert++;
        }
        if (_sourceString[i] == '}')
            braceAssert--;
    }

    if (0 != braceAssert)
    {
        throw std::invalid_argument("Entry data structure error! Braces mismatch!");
    }

    /* get pairs of positions '{', '}' */
    /* получить пары расположений '{', '}' */
    for (int it = 0; it < beginnings.size(); it++)
    {
        int count = 0;

        for (int i = beginnings[it]; i < _sourceString.length(); i++)
        {
            if (_sourceString[i] == '{')
                count += 1;

            if (_sourceString[i] == '}')
                count -=1;

            if (count == 0 && _sourceString[i] == '}')
            {
                positions.push_back(std::make_pair(beginnings[it], i+1));
                break;
            }
        }
    }

    return positions;
}

int ParseEngine::calculateNodeNesting(int position, const BracesIndexes &vector)
{
    std::pair<int, int> coord = vector[position];
    int nesting = 0;

    /* nesting += 1 if '}' of the previous node has bigger index than '{' of the current */
    /* вложенность += 1 если '}' предшествующег узла находится позади '{' текущего*/
    for (int i = position; i >= 0; i--)
    {
        if (coord.first < vector[i].second)
            nesting++;
    }
    return nesting;
}

void ParseEngine::initTreeWithNodes(SharedTreePtr treePtr, const std::vector<Node> &nodes)
{
    for (auto x:nodes)
        treePtr->addNewNode(x, ID++);
}

void ParseEngine::parseNextNode(const SharedNodePtr &node)
{
    std::string stringToParse;

    /* for root node */
    /* для корневого узла */
    if (!node->getParent())
    {
        std::copy(_sourceString.begin(),
                  _sourceString.begin() + node->getBodyPosition().second,
                  std::back_inserter<std::string>(stringToParse));
    }
    else
    {
        Node* parent =  node->getParent();
        auto siblings = parent->getChildren();

        int startOffset = parent->getBodyPosition().first;

        /* parse either from the parent's opening brace '{' */
        /* or from the previous sibling's brace '}' */

        /* парсить от начала тела родителя '{' */
        /* или от конца тела брата '}' */

        if (siblings.size() > 1)
        {
            for (int i = 1; i < siblings.size(); i++)
            {
                if (node == siblings[i])
                {
                    auto prevNodePosition = siblings[i-1]->getBodyPosition();
                    startOffset = prevNodePosition.second;
                }
            }
        }

        std::copy(_sourceString.begin() + startOffset,
                  _sourceString.begin() + node->getBodyPosition().second,
                  std::back_inserter<std::string>(stringToParse));
    }

    retrieveNodeNameAndVariables(stringToParse, node);

    /* get done with the children of the current node */
    /* продолжить на дочерних узлах */
    auto children = node->getChildren();

    if (!children.empty())
    {
        for (auto nextChild:children)
            parseNextNode(nextChild);
    }
}

void ParseEngine::retrieveNodeNameAndVariables(const std::string &source,
                                            const SharedNodePtr &node){
    std::smatch sm;
    std::string name;
    std::string prefix;
    std::string suffix;
    std::regex nodeNameRegexp("([^\\}\\s\\{][\\w_\\d]*) = \\{");
    std::regex variableRegexp("([^\\d\\s][_a-zA-Z0-9]*) = \"([^\"]+)\"");

    /* get the name of the current node (Node) */
    /* получить имя узла (списка) */
    if (std::regex_search(source, sm, nodeNameRegexp))
    {
        name = sm[1].str();

        std::regex startDigitAssert("([\\d]+)(.+)");

        if (std::regex_search(name, startDigitAssert))
        {
            throw std::invalid_argument("Bad namings: Node's name can't start from digit (" +
                                        name + ")");
        }

        prefix = sm.prefix();
        suffix = sm.suffix();
    }

    node->setNodeName(name);

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
        parseSuffix(suffix, variableRegexp, nodeNameRegexp, node);
    }
}

// здесь собираются переменные которые могут быть между '{' родительского узла
// и '{' дочернего узла -> они принадлежат родителю рассматриваемого узла из retrieveNodeNameAndVariables()
void ParseEngine::parsePrefix(const std::string &prefix,
                           const std::regex &variableRegexp,
                           Node *parent)
{
    std::sregex_iterator iter = std::sregex_iterator(prefix.begin(),prefix.end(), variableRegexp);

    for(iter; iter != std::sregex_iterator(); iter++)
    {
        std::smatch matchResults = *iter;

        auto data = std::make_shared<VariableNode>(VariableNode(matchResults[1].str(),
                                                                matchResults[2].str(),
                                                                parent,
                                                                ID++));
        parent->addVariable(data);
    }
}

void ParseEngine::parseSuffix(const std::string &suffix,
                           const std::regex &variableRegexp,
                           const std::regex &nodeNameRegexp,
                           const SharedNodePtr &node)
{
    std::smatch sm; // dummy variable, for checking purposes below

    // если в суффиксе нет объявления нового узла
    // -> собрать переменные - они принадлежат текущему узлу
    if (!std::regex_search(suffix, sm, nodeNameRegexp))
    {
        auto nodeBodyEnd = suffix.find_first_of('}'); // закрывающая скобка текущего узла '}'

        if (nodeBodyEnd != std::string::npos)
        {
            std::sregex_iterator iter = std::sregex_iterator(suffix.begin(), suffix.end(), variableRegexp);

            for(iter; iter != std::sregex_iterator(); iter++)
            {
                std::smatch matchResults = *iter;

                auto variable = std::make_shared<VariableNode>(VariableNode(matchResults[1].str(),
                                                                            matchResults[2].str(),
                                                                            node.get(),
                                                                            ID++));
                // здесь нужно не словить переменную принадлежащую родителю - она будет находится после '}'
                // текущего узла: проверить чтобы начало найденной переменной было в пределах тела { }
                if (matchResults.position(0) < nodeBodyEnd)
                    node->addVariable(variable);
            }
        }
    }
    /* collect trailing variables, that parent owns */
    /* в суффиксе есть другие вложенные узлы -> искать переменные которые
     * могут остаться между '}' последнего дочернего узла и '}' текущего узла */
    else
    {
        auto children = node->getChildren();
        SharedNodePtr lastChild = *children.rbegin();

        int lastChildEnd = lastChild->getBodyPosition().second;
        int currentNodeEnd = node->getBodyPosition().second;

        std::sregex_iterator iter = std::sregex_iterator(_sourceString.begin() + lastChildEnd,
                                                         _sourceString.begin() + currentNodeEnd,
                                                         variableRegexp);
        for(iter; iter != std::sregex_iterator(); iter++)
        {
            std::smatch matchResults = *iter;

            auto variable = std::make_shared<VariableNode>(VariableNode(matchResults[1].str(),
                                                                        matchResults[2].str(),
                                                                        node.get(),
                                                                        ID++));
            node->addVariable(variable);
        }
    }
}
