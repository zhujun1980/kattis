#include <iostream>
#include <string>
#include <stack>
#include <utility>

struct Cell {
    bool visited;
    char value;
};

struct Query {
    size_t r1;
    size_t c1;
    size_t r2;
    size_t c2;
    bool found;
};

/*
使用FloodFill算法，尽量的把当前r1, c1所在的区域都填充起来
然后判断所有的query中的每一对<r1,c1, r2,c2>有多少被覆盖到
就是说，在尽可能一次填充中，把所有的query结果都确定下来
*/
void FloodFillImpl(Cell **map, size_t row, size_t col, size_t r1, size_t c1) {
    map[r1][c1].visited = true;
    // north
    if(r1 > 0 && map[r1-1][c1].value == map[r1][c1].value && !map[r1-1][c1].visited) {
        FloodFillImpl(map, row, col, r1 - 1, c1);
    }
    // east
    if(c1 < col-1 && map[r1][c1+1].value == map[r1][c1].value && !map[r1][c1+1].visited) {
        FloodFillImpl(map, row, col, r1, c1 + 1);
    }
    // south
    if(r1 < row-1 && map[r1+1][c1].value == map[r1][c1].value && !map[r1+1][c1].visited) {
        FloodFillImpl(map, row, col, r1 + 1, c1);
    }
    // west
    if(c1 > 0 && map[r1][c1-1].value == map[r1][c1].value && !map[r1][c1-1].visited) {
        FloodFillImpl(map, row, col, r1, c1 - 1);
    }
}

bool FindPathImpl1(Cell **map, size_t row, size_t col, size_t r1, size_t c1, size_t r2, size_t c2, size_t& count) {
    bool ret = false;
    count++;
    // std::cout << r1 << ", " << c1 << std::endl;
    map[r1][c1].visited = true;
    if(r1 == r2 && c1 == c2) {
        return true;
    }
    // north
    if(r1 > 0 && map[r1-1][c1].value == map[r1][c1].value && !map[r1-1][c1].visited) {
        ret = FindPathImpl1(map, row, col, r1 - 1, c1, r2, c2, count);
        if(ret) return true;
    }
    // east
    if(c1 < col-1 && map[r1][c1+1].value == map[r1][c1].value && !map[r1][c1+1].visited) {
        ret = FindPathImpl1(map, row, col, r1, c1 + 1, r2, c2, count);
        if(ret) return true;
    }
    // south
    if(r1 < row-1 && map[r1+1][c1].value == map[r1][c1].value && !map[r1+1][c1].visited) {
        ret = FindPathImpl1(map, row, col, r1 + 1, c1, r2, c2, count);
        if(ret) return true;
    }
    // west
    if(c1 > 0 && map[r1][c1-1].value == map[r1][c1].value && !map[r1][c1-1].visited) {
        ret = FindPathImpl1(map, row, col, r1, c1 - 1, r2, c2, count);
        if(ret) return true;
    }
    return false;
}

bool FindPathImpl2(Cell **map, size_t row, size_t col, size_t r1, size_t c1, size_t r2, size_t c2) {
    std::stack<std::pair<size_t, size_t> > data;

    data.push(std::make_pair(r1, c1));
    while(!data.empty()) {
        size_t cr, cc;
        auto dp = data.top();
        data.pop();
        cr = dp.first;
        cc = dp.second;
        map[cr][cc].visited = true;
        if(cr == r2 && cc == c2) return true;

        // north
        if(cr > 0 && map[cr-1][cc].value == map[cr][cc].value && !map[cr-1][cc].visited) {
            data.push(std::make_pair(cr-1, cc));
        }
        // east
        if(cc < col-1 && map[cr][cc+1].value == map[cr][cc].value && !map[cr][cc+1].visited) {
            data.push(std::make_pair(cr, cc+1));
        }
        // south
        if(cr < row-1 && map[cr+1][cc].value == map[cr][cc].value && !map[cr+1][cc].visited) {
            data.push(std::make_pair(cr+1, cc));
        }
        // west
        if(cc > 0 && map[cr][cc-1].value == map[cr][cc].value && !map[cr][cc-1].visited) {
            data.push(std::make_pair(cr, cc-1));
        }
    }
    return false;
}

void FindPath(const std::string& tag, Query *query, size_t current, size_t count, Cell **map, size_t row, size_t col, size_t r1, size_t c1, size_t r2, size_t c2) {
    FloodFillImpl(map, row, col, r1, c1);
    for(size_t i = current; i < count; ++i) {
        size_t qr1, qc1, qr2, qc2;
        qr1 = query[i].r1;
        qc1 = query[i].c1;
        qr2 = query[i].r2;
        qc2 = query[i].c2;
        if(map[qr1][qc1].visited && map[qr2][qc2].visited) {
            query[i].found = true;
        }
    }
    for(size_t i = 0; i < row; ++i) {
        for(size_t j = 0; j < col; ++j) {
            map[i][j].visited = false;
        }
    }
}

int main(void) {
    std::ios::sync_with_stdio(false);

    size_t row, col;
    size_t count;
    std::cin >> row >> col;
    Cell **map = new Cell*[row];
    for(size_t i = 0; i < row; ++i) {
        map[i] = new Cell[col];
    }
    for(size_t i = 0; i < row; ++i) {
        std::string line;
        std::cin >> line;
        for(size_t j = 0; j < col; ++j) {
            map[i][j].value = line[j];
            map[i][j].visited = false;
        }
    }
    std::cin >> count;
    Query *query = new Query[count];
    for(size_t i = 0; i < count; ++i) {
        size_t r1, c1, r2, c2;
        std::cin >> r1 >> c1 >> r2 >> c2;
        r1--; c1--; r2--; c2--;
        query[i].r1 = r1;
        query[i].c1 = c1;
        query[i].r2 = r2;
        query[i].c2 = c2;
        query[i].found = false;
    }

    for(size_t i = 0; i < count; ++i) {
        size_t r1, c1, r2, c2;
        r1 = query[i].r1;
        c1 = query[i].c1;
        r2 = query[i].r2;
        c2 = query[i].c2;

        std::string tag = (map[r1][c1].value == '0') ? "binary" : "decimal";
        if(map[r1][c1].value != map[r2][c2].value) {
            std::cout << "neither" << std::endl;
        }
        else if(r1 == r2 && c1 == c2) {
            std::cout << tag << std::endl;
        }
        else {
            if(!query[i].found)
                FindPath(tag, query, i, count, map, row, col, r1, c1, r2, c2);
            if(query[i].found) {
                std::cout << tag << std::endl;
            }
            else {
                std::cout << "neither" << std::endl;
            }
        }
    }
    return 0;
}
