#ifndef IO_H
#define IO_H

#include "library.h"
#include <string>

namespace IO {
    bool loadData(Library& lib);
    bool saveData(const Library& lib);
}

#endif 