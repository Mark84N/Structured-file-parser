#include "parserprogram.h"
using namespace Pr;

ParserProgram::ParserProgram(std::ifstream &readStr, ITreeWriter *treeWriter)
    :
      _sourceString(""),
      _tree(new NodeTree()),
      _treeWriter(treeWriter)
{
    _sourceString = readFromStream(readStr);

    _parseEngine = std::make_shared<ParseEngine>(ParseEngine(_sourceString));
    _parseEngine->fillTree(_tree);
}

ParserProgram::ParserProgram(const std::string &filename, ITreeWriter *treeWriter):
    _sourceString(""),
    _tree(new NodeTree()),
    _treeWriter(treeWriter)
{

    std::ifstream readStr;
    readStr.open(filename, std::ios_base::in);

    if (!readStr.is_open())
    {
        throw std::runtime_error("Unable to open file \"" + filename + "\"!");
    }
    else
    {
        _sourceString = readFromStream(readStr);
    }

    _parseEngine = std::make_shared<ParseEngine>(ParseEngine(_sourceString));
    _parseEngine->fillTree(_tree);
}

std::string ParserProgram::readFromStream(std::ifstream &readStr)
{
    std::string temp;
    std::string source;

    while (readStr)
    {
        std::getline(readStr, temp);
        source += temp + ' ';
        temp.clear();
    }

    return source;
}

std::string ParserProgram::getSourceString()const
{
    return _sourceString;
}

void ParserProgram::writeToFile(const std::string &filename)
{
    _treeWriter->writeToFile(filename, _tree);
}

void ParserProgram::writeToStream(std::ostream &outStream)
{
    _treeWriter->writeToStream(outStream, _tree);
}

SharedTreePtr ParserProgram::getTree()const
{
    return _tree;
}
