#include "IOManager.h"
#include <fstream>
#include "Error.h"

bool IOManager::readFiletoBuffer(string filePath, vector<unsigned char>& buffer)
{
    ifstream  file(filePath, ios::binary);
    if (file.fail()) {
        fatalError(filePath.c_str());
        return false;
    }
    file.seekg(0, ios::end);
    int fileSize = file.tellg();
    file.seekg(0, ios::beg);
    fileSize -= file.tellg();
    buffer.resize(fileSize);
    file.read((char*)&(buffer[0]), fileSize);
    file.close();
    return true;
}
