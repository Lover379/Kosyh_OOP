#include "labirint.h"
#include <fstream>
#include <iostream>
#include <queue>
#include <cmath>

using namespace std;

Labyrinth::Labyrinth() : locationsFound(false) {
    start = { -1, -1 };
    finish = { -1, -1 };
}

bool Labyrinth::loadBMP(const string& filename) {
    ifstream file(filename, ios::binary);
    if (!file.is_open()) {
        cerr << "Ошибка: Не удалось открыть файл " << filename << endl;
        return false;
    }

    file.read(reinterpret_cast<char*>(&header), sizeof(header));
    file.read(reinterpret_cast<char*>(&infoHeader), sizeof(infoHeader));

    if (header.type != 0x4D42 || infoHeader.bitCount != 24) {
        cerr << "Ошибка: Поддерживаются только 24-битные BMP файлы." << endl;
        return false;
    }

    int width = infoHeader.width;
    int height = abs(infoHeader.height);
    pixels.resize(height, vector<RGB>(width));

    int padding = (4 - (width * 3) % 4) % 4;

    file.seekg(header.offset, ios::beg);

    if (infoHeader.height > 0) {
        for (int y = height - 1; y >= 0; --y) {
            file.read(reinterpret_cast<char*>(pixels[y].data()), width * 3);
            file.seekg(padding, ios::cur);
        }
    }
    else {
        for (int y = 0; y < height; ++y) {
            file.read(reinterpret_cast<char*>(pixels[y].data()), width * 3);
            file.seekg(padding, ios::cur);
        }
    }

    file.close();
    locatePoints();
    return true;
}

void Labyrinth::locatePoints() {
    int height = pixels.size();
    int width = pixels[0].size();

    long long sumStartX = 0, sumStartY = 0, countStart = 0;
    long long sumFinishX = 0, sumFinishY = 0, countFinish = 0;

    for (int y = 0; y < height; ++y) {
        for (int x = 0; x < width; ++x) {
            RGB p = pixels[y][x];

            if (p.g > 100 && p.r < 100 && p.b < 100) {
                sumStartX += x;
                sumStartY += y;
                countStart++;
            }

            if (p.r > 100 && p.g < 100 && p.b < 100) {
                sumFinishX += x;
                sumFinishY += y;
                countFinish++;
            }
        }
    }

    if (countStart > 0 && countFinish > 0) {
        start = { static_cast<int>(sumStartX / countStart), static_cast<int>(sumStartY / countStart) };
        finish = { static_cast<int>(sumFinishX / countFinish), static_cast<int>(sumFinishY / countFinish) };
        locationsFound = true;
        
    }
    else {
        if (countStart == 0) cerr << "Ошибка: Зеленая точка (старт) не найдена!" << endl;
        if (countFinish == 0) cerr << "Ошибка: Красная точка (финиш) не найдена!" << endl;
    }
}

bool Labyrinth::solve() {
    if (!locationsFound) return false;

    int height = pixels.size();
    int width = pixels[0].size();

    vector<vector<int>> dist(height, vector<int>(width, -1));
    vector<vector<Point>> parent(height, vector<Point>(width, { -1, -1 }));
    queue<Point> q;

    q.push(start);
    dist[start.y][start.x] = 0;

    int dx[] = { 0, 0, -1, 1 };
    int dy[] = { -1, 1, 0, 0 };
    bool found = false;

    while (!q.empty()) {
        Point curr = q.front();
        q.pop();

        if (curr.x == finish.x && curr.y == finish.y) {
            found = true;
            break;
        }

        for (int i = 0; i < 4; ++i) {
            int nx = curr.x + dx[i];
            int ny = curr.y + dy[i];

            if (nx >= 0 && nx < width && ny >= 0 && ny < height) {
                if (dist[ny][nx] == -1) {
                    RGB p = pixels[ny][nx];

              
                    bool isWall = (p.r < 80 && p.g < 80 && p.b < 80);

                    if (!isWall) {
                        dist[ny][nx] = dist[curr.y][curr.x] + 1;
                        parent[ny][nx] = curr;
                        q.push({ nx, ny });
                    }
                }
            }
        }
    }

    if (!found) {
        cerr << "Критическая ошибка: Путь между точками не найден даже через мягкий фильтр." << endl;
        return false;
    }


    Point curr = parent[finish.y][finish.x];
    while (!(curr == start) && curr.x != -1) {
        pixels[curr.y][curr.x] = { 255, 0, 0 };
        curr = parent[curr.y][curr.x];
    }

    return true;
}

bool Labyrinth::saveBMP(const string& filename) {
    ofstream file(filename, ios::binary);
    if (!file.is_open()) return false;

    file.write(reinterpret_cast<char*>(&header), sizeof(header));
    file.write(reinterpret_cast<char*>(&infoHeader), sizeof(infoHeader));

    int width = infoHeader.width;
    int height = pixels.size();
    int padding = (4 - (width * 3) % 4) % 4;
    char padBytes[3] = { 0, 0, 0 };

    if (infoHeader.height > 0) {
        for (int y = height - 1; y >= 0; --y) {
            file.write(reinterpret_cast<char*>(pixels[y].data()), width * 3);
            if (padding > 0) file.write(padBytes, padding);
        }
    }
    else {
        for (int y = 0; y < height; ++y) {
            file.write(reinterpret_cast<char*>(pixels[y].data()), width * 3);
            if (padding > 0) file.write(padBytes, padding);
        }
    }

    file.close();
    return true;
}