#include <iostream>
#include <fstream>
#include <vector>
#include <queue>
#include <string>
#include "figures.h"

using namespace std;

const int SIZE = 200;

int main() {
    string filename = "";
    string targets[] = { "input1.dat", "input2.dat", "input3.dat" };

    ifstream infile;
    for (const string& target : targets) {
        infile.open(target);
        if (infile.is_open()) {
            filename = target;
            break;
        }
    }

    if (filename.empty()) {
        cerr << "No input file found in folder!" << endl;
        return 1;
    }

    vector<vector<int>> grid(SIZE, vector<int>(SIZE, 0));
    int r = 0, c = 0;
    char ch;
    while (infile.get(ch)) {
        if (ch == '1' || ch == '0') {
            if (r < SIZE && c < SIZE) grid[r][c] = (ch == '1') ? 1 : 0;
            c++;
            if (c >= SIZE) { c = 0; r++; }
        }
    }
    infile.close();

    vector<vector<bool>> visited(SIZE, vector<bool>(SIZE, false));
    int rects = 0, circles = 0, tris = 0, noise = 0;
    double total_area = 0.0;

    for (int i = 0; i < SIZE; ++i) {
        for (int j = 0; j < SIZE; ++j) {
            if (grid[i][j] == 1 && !visited[i][j]) {
                vector<pair<int, int>> points;
                queue<pair<int, int>> q;

                q.push({ i, j });
                visited[i][j] = true;

                while (!q.empty()) {
                    auto curr = q.front();
                    q.pop();
                    points.push_back(curr);

                    int dr[] = { -1, 1, 0, 0 };
                    int dc[] = { 0, 0, -1, 1 };
                    for (int k = 0; k < 4; ++k) {
                        int nr = curr.first + dr[k];
                        int nc = curr.second + dc[k];
                        if (nr >= 0 && nr < SIZE && nc >= 0 && nc < SIZE) {
                            if (grid[nr][nc] == 1 && !visited[nr][nc]) {
                                visited[nr][nc] = true;
                                q.push({ nr, nc });
                            }
                        }
                    }
                }

                if (points.size() <= 15) continue;

                int min_x = SIZE, max_x = 0, min_y = SIZE, max_y = 0;
                for (const auto& p : points) {
                    if (p.second < min_x) min_x = p.second;
                    if (p.second > max_x) max_x = p.second;
                    if (p.first < min_y) min_y = p.first;
                    if (p.first > max_y) max_y = p.first;
                }

                double w = max_x - min_x + 1.0;
                double h = max_y - min_y + 1.0;

                int corners = 0;
                for (const auto& p : points) {
                    int y = p.first, x = p.second;
                    int neighbors = 0;
                    if (y > 0 && grid[y - 1][x]) neighbors++;
                    if (y < SIZE - 1 && grid[y + 1][x]) neighbors++;
                    if (x > 0 && grid[y][x - 1]) neighbors++;
                    if (x < SIZE - 1 && grid[y][x + 1]) neighbors++;
                    if (neighbors == 2) corners++;
                }

                if (corners == 4) {
                    rects++;
                    Rectangle s(w, h);
                    total_area += s.calc_area();
                }
                else if (corners == 3) {
                    tris++;
                    Triangle s(w);
                    total_area += (w * h) / 2.0;
                }
                else if (corners > 4) {
                    circles++;
                    Circle s((w + h) / 4.0);
                    total_area += s.calc_area();
                }
                else {
                    noise++;
                }
            }
        }
    }

    ofstream outfile("output.dat");
    if (outfile.is_open()) {
        outfile << rects << "\n" << circles << "\n" << tris << "\n" << noise << "\n";
        outfile.close();
    }

    cout << "Processed file: " << filename << endl;
    cout << "Rectangle = " << rects << "\nCircle = " << circles << "\nTriangle = " << tris << "\nNoise = " << noise << endl;
    cout << "Total Area = " << total_area << endl;

    Polygon plot("granitsy-uchastka2.txt");
    cout << "Polygon Area = " << plot.calc_area() << endl;

    return 0;
}