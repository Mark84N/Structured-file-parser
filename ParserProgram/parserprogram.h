#ifndef PARSER_H
#define PARSER_H

#include "node.h"
#include "variablenode.h"
#include "nodetree.h"
#include "parseengine.h"
#include "xmltreewriter.h"

namespace Pr
{
class ParserProgram
{
public:

    ParserProgram(std::ifstream & readStr, ITreeWriter *treeWriter);
    ParserProgram(const std::string & filename, ITreeWriter *treeWriter);

    SharedTreePtr   getTree()const;
    std::string     getSourceString()const;

    void writeToFile(const std::string &filename);
    void writeToStream(std::ostream &outStream);

private:

    std::string             _sourceString;
    SharedTreePtr           _tree;
    SharedParseEnginePtr    _parseEngine;
    SharedTreeWriter        _treeWriter;

    std::string             readFromStream(std::ifstream &readStr);
};
}

#endif // PARSER_H

