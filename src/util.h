#ifndef __util_h__
#define __util_h__
#include <cstring>
#include <stdio.h>
#include <string>
#include <vector>
#include <sstream>
#include <sys/stat.h>
#include <fstream>
#include <vector>
#include "type.h"
using namespace std;

std::vector<std::string>& split(const std::string& s, char delim, std::vector<std::string>& elems);
std::vector<std::string>  split(const std::string& s, char delim);
int getFileSize(std::string fpath, uint64& fileSize);
bool fexists(const std::string& filename);
vector<string> listFilesInDir(std::string path);
int cinNumber();
string cinString();
void clearTerminal();
uint32 factorial(u32_t n);

#endif