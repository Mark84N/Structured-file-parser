#include "xmltreewriter.h"
using namespace Pr;

void XMLTreeWriter::writeToStream(std::ostream &outStream, const SharedTreePtr &tree)
{
    outStream << "<?xml version=\"1.0\" encoding=\"UTF-8\">" << "\n\n";
    outStream << "<tree>" << "\n\n";
    writeNextNode(tree->getRoot(), outStream);
    outStream << "</tree>" << "\n";
}

void XMLTreeWriter::writeNextNode(const SharedNodePtr &node, std::ostream &outStream)
{
    const std::vector<SharedNodePtr> children =
            node->getChildren();

    auto variables = node->getVariables();
    std::string name = node->getNodeName();
    int nest = node->getNesting();
    int id = node->getId();

    provideOffset(outStream, nest, "\t");

    outStream << "<node name=\"" << name << "\""
       << " id=\"" << id << "\""
       << " level=\"" << nest << "\">" << "\n\n";

    if (!variables.empty())
    {
        provideOffset(outStream, nest+1, "\t");

        for (auto tempVar:variables)
        {
            outStream << "<variable name=\"" << tempVar->getVariableName() << "\""
               << " id=\"" << tempVar->getId() << "\""
               << " level=\"" << nest+1 << "\"> " << tempVar->getVariableValue()
               << " </variable>" << "\n";

            provideOffset(outStream, nest+1, "\t");
        }
        outStream << "\n";
    }
    if (!children.empty())
    {
        for (auto nodeChild:children)
            writeNextNode(nodeChild, outStream);
    }

    provideOffset(outStream, nest, "\t");
    outStream << "</node>" << "\n\n";
}

void XMLTreeWriter::provideOffset(std::ostream &outStream, int nestingLevel, const char *ch)
{
    for (int i = nestingLevel; i > 0; i--)
        outStream << ch;
}
