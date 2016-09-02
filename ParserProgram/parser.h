#ifndef PARSER_H
#define PARSER_H

#include "node.h"
#include "variablenode.h"
#include "nodetree.h"

namespace Pr{

    class ParserProgram{

    private:

        std::string _sourceString;
        sharedTreePtr _tree;

        void readFromStream(std::ifstream &readStr);
        int calculateNodeNesting(int position,
                                 const std::vector<std::pair<int, int>> &vector);
        std::vector<Node> getNodesWithNesting(const std::vector<std::pair<int, int>> &positions);
        std::vector<std::pair<int, int>> getStructuresPositions();
        void releaseTheKraken();

    public:

        ParserProgram(std::ifstream & readStr);
        ParserProgram(const std::string & filename);

        sharedTreePtr getTree()const;
        std::string getSourceString()const;

        void writeToFile(const std::string &filename);
        void printTreeStructure();
    };
}

#endif // PARSER_H

