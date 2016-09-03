#ifndef XMLTREEWRITER_H
#define XMLTREEWRITER_H

#include "resources.h"
#include "itreewriter.h"
#include "node.h"
#include "variablenode.h"

namespace Pr {

class XMLTreeWriter : public ITreeWriter
{
using ITreeWriter::writeToFile;

public:

    virtual void writeToStream(std::ostream &outStream, const SharedTreePtr &tree)override;
    ~XMLTreeWriter() {}

private:

    virtual void writeNextNode(const SharedNodePtr &node, std::ostream &os)override;
    void provideOffset(std::ostream &os, int nestingLevel, const char* ch);
};
}

#endif // XMLTREEWRITER_H
