#include <iostream>
#include <string>

using std::endl;
using std::cin;
using std::cout;
using std::string;

/*
data-driven
4个方向，8个item
第1第2是起始点
第3第4是行列步长，移动到下一行还是下一列（具体是行还是列要看是左右划还是上下划）
第5第6是item步长，在每一行或每一列，按照该步长，从起始点开始逐个遍历item
第7第8是每个item移动的方向，就是它要移动的下一个位置
*/
int directions[4][8] = {
    {0, 0, 1, 0,  0,  1,  0, -1}, // left
    {0, 0, 0, 1,  1,  0, -1,  0}, // up
    {0, 3, 1, 0,  0, -1,  0,  1}, // right
    {3, 0, 0, 1, -1,  0,  1,  0}, // down
};

inline bool IsValid(int X, int Y) {
    return X >= 0 && X < 4 && Y >= 0 && Y < 4;
}

void Move(int map[4][4], size_t d) {
    int beginX = directions[d][0];
    int beginY = directions[d][1];
    int stepX = directions[d][2];
    int stepY = directions[d][3];
    int nextX = directions[d][4];
    int nextY = directions[d][5];
    int moveX = directions[d][6];
    int moveY = directions[d][7];
    int currentX = beginX;
    int currentY = beginY;

    // for each lines or columns
    for(int i = 0; i < 4; ++i) {
        int first = map[currentX][currentY];
        int tileX = currentX;
        int tileY = currentY;

        // for each items
        int resultX = -1;
        int resultY = -1;
        for(int j = 0; j < 4; ++j) {
            int X = tileX;
            int Y = tileY;
            while(1) {
                if(map[X][Y] == 0) {
                    break;
                }
                if(!IsValid(X+moveX, Y+moveY)) {
                    break;
                }
                if(map[X+moveX][Y+moveY] == 0) {
                    map[X+moveX][Y+moveY] = map[X][Y];
                    map[X][Y] = 0;
                    X += moveX;
                    Y += moveY;
                    continue;
                }
                //cout << j << ":'" << map[X][Y] << "' " << resultX << " " << resultY << " " << X+moveX << " " << Y+moveY << ", ";
                if(map[X+moveX][Y+moveY] == map[X][Y] && ((X+moveX) != resultX || (Y+moveY) != resultY)) {
                    map[X+moveX][Y+moveY] *= 2;
                    map[X][Y] = 0;
                    resultX = X+moveX;
                    resultY = Y+moveY;
                }
                break;
            }
            tileX += nextX;
            tileY += nextY;
        }
        //cout << endl;
        currentX += stepX;
        currentY += stepY;
    }
}

int main(void) {
    std::ios::sync_with_stdio(false);
    size_t direction;
    int map[4][4];
    cin >> map[0][0] >> map[0][1] >> map[0][2] >> map[0][3];
    cin >> map[1][0] >> map[1][1] >> map[1][2] >> map[1][3];
    cin >> map[2][0] >> map[2][1] >> map[2][2] >> map[2][3];
    cin >> map[3][0] >> map[3][1] >> map[3][2] >> map[3][3];
    cin >> direction;
    Move(map, direction);
    for(int i = 0; i < 4; ++i) {
        cout << map[i][0] << " " << map[i][1] << " " << map[i][2] << " " << map[i][3] << endl;
    }
    return 0;
}
