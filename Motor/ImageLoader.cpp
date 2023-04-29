#include "ImageLoader.h"
#include "IOManager.h"
#include "Error.h"


GLTexture ImageLoader::loadPNG(string filePath)
{
    vector<unsigned char>in;
    vector<unsigned char>out;
    unsigned long width, height;

    if (!IOManager::readFiletoBuffer(filePath, in)) {
        fatalError("Could not read " + filePath);
    }

    return GLTexture();
}
