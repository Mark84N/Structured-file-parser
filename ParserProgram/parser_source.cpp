#include "parser.h"

// [1]
Pr::ParserProgram::ParserProgram(std::ifstream &readStr):
    _sourceString(""),
    _tree(nullptr)
{

    readFromStream(readStr);
    releaseTheKraken();
}
// [1]

// [2]
Pr::ParserProgram::ParserProgram(const std::string &filename):
    _sourceString(""),
    _tree(nullptr)
{

    std::ifstream readStr;
    readStr.open(filename);

    if (!readStr.is_open()){

        throw std::runtime_error("Unable to open file \"" + filename + "\"!");
    }
    else {

        readFromStream(readStr);
    }
    releaseTheKraken();
}
// [2]

// [3]
void Pr::ParserProgram::readFromStream(std::ifstream &readStr){

    std::string temp;

    while (readStr){

        std::getline(readStr, temp);
        _sourceString += temp + ' ';
        temp.clear();
    }
}
// [3]

// [4]
int Pr::ParserProgram::calculateNodeNesting(int position,
                                      const std::vector<std::pair<int, int> > &vector){

    std::pair<int, int> coord = vector[position];
    int nesting = 0;

    /* calculates nesting based on qty of '}' before current node */
    /* подсчитывается вложенность на основании кол-ва '}' впереди рассматриваемого узла */
    for (int i = position; i >= 0; i--){

        if (coord.first < vector[i].second){
            nesting++;
        }

    }
    return nesting;
}
// [4]

// [5]
std::vector<Pr::Node> Pr::ParserProgram::getNodesWithNesting
                (const std::vector<std::pair<int, int> > &positions){

    std::vector<Pr::Node> nodes;

    for (int i = 0; i < positions.size(); i++) {

        Pr::Node _node;

        _node.setNodeType(Pr::Type::LIST);
        _node.setNesting(calculateNodeNesting(i,positions));
        _node.setBodyPosition((positions[i]));

        nodes.push_back(_node);
    }

    return nodes;
}
// [5]

// [6]
std::vector<std::pair<int, int> > Pr::ParserProgram::getStructuresPositions(){

    std::vector<int>beginnings;
    std::vector<std::pair<int, int>> positions;

    int braceAssert = 0;

    for (int i = 0; i < _sourceString.length(); i++){

        if (_sourceString[i] == '{'){

           beginnings.push_back(i);
           braceAssert++;
        }
        if (_sourceString[i] == '}'){
            braceAssert--;
        }
    }

    if (0 != braceAssert){

        throw std::invalid_argument("Entry data structure error! Braces mismatch!");
    }

    /* get pairs of positions '{', '}' */
    /* получить пары расположений '{', '}' */
    for (int it = 0; it < beginnings.size(); it++){

        int count = 0;

        for (int i = beginnings[it]; i < _sourceString.length(); i++){

            if (_sourceString[i] == '{'){
                count += 1;
            }
            if (_sourceString[i] == '}'){
                count -=1;
            }
            if (count == 0 && _sourceString[i] == '}'){

                positions.push_back(std::make_pair(beginnings[it], i+1));
                break;
            }
        }
    }

    return positions;
}
// [6]

// [7]
void Pr::ParserProgram::releaseTheKraken(){

    /* get hierarchy vector of nodes based on the positions of { } */
    /* получить иерархический вектор узлов на основании позиций их { } */
    auto nodesVector =
            getNodesWithNesting(getStructuresPositions());

    _tree = std::make_shared<Pr::NodeTree>(Pr::NodeTree(nodesVector,
                                                              this->_sourceString));
}
// [7]

// [8]
std::string Pr::ParserProgram::getSourceString()const{
    return _sourceString;
}
// [8]

// [9]
Pr::sharedTreePtr Pr::ParserProgram::getTree()const{
    return _tree;
}
// [9]

// [10]
void Pr::ParserProgram::writeToFile(const std::string &filename){

    std::ofstream fs;

    fs.open(filename);

    if (!fs.is_open()){

        throw std::runtime_error("Failed open \"" + filename + "\" for writing!");
    }

    _tree->printOut(fs);

    fs.close();
}
// [10]

// [11]
void Pr::ParserProgram::printTreeStructure(){

    _tree->printOut(std::cout);
}

// [11]
