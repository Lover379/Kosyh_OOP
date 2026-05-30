#pragma once
#ifndef LABIRINT_H
#define LABIRINT_H

#include <string>
#include <vector>

#pragma pack(push, 1)
struct BMPHeader {
    unsigned short type;
    unsigned int size;
    unsigned short reserved1;
    unsigned short reserved2;
    unsigned int offset;
};

struct BMPInfoHeader {
    unsigned int size;
    int width;
    int height;
    unsigned short planes;
    unsigned short bitCount;
    unsigned int compression;
    unsigned int sizeImage;
    int xPelsPerMeter;
    int yPelsPerMeter;
    unsigned int clrUsed;
    unsigned int clrImportant;
};
#pragma pack(pop)

struct Point {
    int x, y;
    bool operator==(const Point& other) const {
        return x == other.x && y == other.y;
    }
};

struct RGB {
    unsigned char b, g, r;
};

class Labyrinth {
private:
    BMPHeader header;
    BMPInfoHeader infoHeader;
    std::vector<std::vector<RGB>> pixels;
    Point start;
    Point finish;
    bool locationsFound;

    void locatePoints();

public:
    Labyrinth();
    bool loadBMP(const std::string& filename);
    bool solve();
    bool saveBMP(const std::string& filename);
};

#endif