//
// Created by otavio on 03/05/2021.
//

#include "Image.h"
#include "AutoArray.h"

#include <cassert>

Image::Image(char *ps, int w, int h) : pixels(ps), width(w), height(h) {
}

Image::~Image() {
    delete[] pixels;
}

Image *Image::loadImage(const char *filename) {
    std::ifstream input;
    input.open(filename, std::ifstream::binary);
    assert(!input.fail() || !"Could not find file");
    char buffer[2];
    input.read(buffer, 2);
    assert(buffer[0] == 'B' && buffer[1] == 'M' || !"Not a bitmap file");
    input.ignore(8);
    int dataOffset = readInt(input);

    //Read the header
    int headerSize = readInt(input);
    int width_;
    int height_;
    switch (headerSize) {
        case 40:
            //V3
            width_ = readInt(input);
            height_ = readInt(input);
            input.ignore(2);
            assert(readShort(input) == 24 || !"Image is not 24 bits per pixel");
            assert(readShort(input) == 0 || !"Image is compressed");
            break;
        case 12:
            //OS/2 V1
            width_ = readShort(input);
            height_ = readShort(input);
            input.ignore(2);
            assert(readShort(input) == 24 || !"Image is not 24 bits per pixel");
            break;
        case 64:
            //OS/2 V2
            assert(!"Can't load OS/2 V2 bitmaps");
        case 108:
            //Windows V4
            assert(!"Can't load Windows V4 bitmaps");
        case 124:
            //Windows V5
            assert(!"Can't load Windows V5 bitmaps");
        default:
            assert(!"Unknown bitmap format");
    }

    //Read the data
    int bytesPerRow = ((width_ * 3 + 3) / 4) * 4 - (width_ * 3 % 4);
    int size = bytesPerRow * height_;
    AutoArray pixels_(new char[size]);
    input.seekg(dataOffset, std::ios_base::beg);
    input.read(pixels_.get(), size);

    //Get the data into the right format
    AutoArray pixels2(new char[width_ * height_ * 3]);
    for (int y = 0; y < height_; y++) {
        for (int x = 0; x < width_; x++) {
            for (int c = 0; c < 3; c++) {
                pixels2[3 * (width_ * y + x) + c] =
                        pixels_[bytesPerRow * y + 3 * x + (2 - c)];
            }
        }
    }

    input.close();
    return new Image(pixels2.release(), width_, height_);
}

int Image::toInt(const char *bytes) {
    return (int) (((unsigned char) bytes[3] << 24) |
                  ((unsigned char) bytes[2] << 16) |
                  ((unsigned char) bytes[1] << 8) |
                  (unsigned char) bytes[0]);
}

//Converts a two-character array to a short, using little-endian form
short Image::toShort(const char *bytes) {
    return (short) (((unsigned char) bytes[1] << 8) |
                    (unsigned char) bytes[0]);
}

//Reads the next four bytes as an integer, using little-endian form
int Image::readInt(std::ifstream &input) {
    char buffer[4];
    input.read(buffer, 4);
    return toInt(buffer);
}

//Reads the next two bytes as a short, using little-endian form
short Image::readShort(std::ifstream &input) {
    char buffer[2];
    input.read(buffer, 2);
    return toShort(buffer);
}
