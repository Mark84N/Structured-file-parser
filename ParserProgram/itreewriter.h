#ifndef ITREEWRITER_H
#define ITREEWRITER_H

#include <resources.h>
#include "nodetree.h"

namespace Pr {

class ITreeWriter
{
public:

    ~ITreeWriter() {}

    virtual void writeToStream(std::ostream &outStream, const SharedTreePtr &tree)=0;

    virtual void writeToFile(const std::string &filename, const SharedTreePtr &tree)
    {
        std::ofstream fs;

        fs.open(filename, std::ios_base::out);

        if (!fs.is_open())
            throw std::runtime_error("Failed open \"" + filename + "\" for writing!");

        writeToStream(fs, tree);

        fs.close();
    }

private:

    virtual void writeNextNode(const SharedNodePtr &node, std::ostream &os)=0;
};
}

#endif // ITREEWRITER_H
