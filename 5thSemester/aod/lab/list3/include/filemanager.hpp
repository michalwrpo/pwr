#ifndef FILEMANAGER_H
#define FILEMANAGER_H

#include <string>

#include "graph.hpp"

Graph loadGraph(const std::string &filename);
std::vector<ull> loadSources(const std::string &filename);

#endif