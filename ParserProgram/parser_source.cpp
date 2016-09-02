#include "parser.h"
using namespace Pr;

ParserProgram::ParserProgram(std::ifstream &readStr):
    _sourceString(""),
    _tree(nullptr)
{

    readFromStream(readStr);
    releaseTheKraken();
}

ParserProgram::ParserProgram(const std::string &filename):
    _sourceString(""),
    _tree(nullptr)
{

    std::ifstream readStr;
    readStr.open(filename, std::ios_base::in);

    if (!readStr.is_open())
    {
        throw std::runtime_error("Unable to open file \"" + filename + "\"!");
    }
    else
    {
        readFromStream(readStr);
    }
    releaseTheKraken();
}

void ParserProgram::readFromStream(std::ifstream &readStr)
{
    std::string temp;

    while (readStr)
    {
        std::getline(readStr, temp);
        _sourceString += temp + ' ';
        temp.clear();
    }
}

int ParserProgram::calculateNodeNesting(int position,
                                            const std::vector<std::pair<int, int> > &vector)
{
    std::pair<int, int> coord = vector[position];
    int nesting = 0;

    /* calculates nesting based on qty of '}' before current node */
    /* подсчитывается вложенность на основании кол-ва '}' впереди рассматриваемого узла */
    for (int i = position; i >= 0; i--)
    {
        if (coord.first < vector[i].second)
            nesting++;
    }
    return nesting;
}

std::vector<Node> ParserProgram::getNodesWithNesting
(const std::vector<std::pair<int, int> > &positions)
{
    std::vector<Node> nodes;

    for (int i = 0; i < positions.size(); i++)
    {
        Node _node;

        _node.setNodeType(Type::LIST);
        _node.setNesting(calculateNodeNesting(i,positions));
        _node.setBodyPosition((positions[i]));

        nodes.push_back(_node);
    }

    return nodes;
}

std::vector<std::pair<int, int> > ParserProgram::getStructuresPositions()
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

void ParserProgram::releaseTheKraken()
{
    /* get hierarchy vector of nodes based on the positions of { } */
    /* получить иерархический вектор узлов на основании позиций их { } */
    auto nodesVector =
            getNodesWithNesting(getStructuresPositions());

    _tree = std::make_shared<NodeTree>(NodeTree(nodesVector,
                                                        this->_sourceString));
}

std::string ParserProgram::getSourceString()const
{
    return _sourceString;
}

sharedTreePtr ParserProgram::getTree()const
{
    return _tree;
}

void ParserProgram::writeToFile(const std::string &filename)
{
    std::ofstream fs;

    fs.open(filename);

    if (!fs.is_open())
        throw std::runtime_error("Failed open \"" + filename + "\" for writing!");

    _tree->printOut(fs);

    fs.close();
}

void ParserProgram::printTreeStructure()
{
    _tree->printOut(std::cout);
}
