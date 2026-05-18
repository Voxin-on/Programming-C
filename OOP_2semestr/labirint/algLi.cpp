#include "algLi.h"
#include <queue>

void algLi::reversePath(std::vector<Cell>& cells) {
    int left = 0;
    int right = cells.size() - 1;

    while (left < right) {
        Cell temp = cells[left];
        cells[left] = cells[right];
        cells[right] = temp;
        
        left++;
        right--;
    }
}

Path algLi::unroll(const std::vector<std::vector<int>>& dist, Cell start, Cell end) {
    Path result;
    Cell curr = end;
    result.cells.push_back(curr);

    int dx[] = {0, 0, -1, 1};
    int dy[] = {-1, 1, 0, 0};

    int h = dist.size();
    int w = dist[0].size();

    // от финиша к старту
    while (curr != start) {
        for (int i = 0; i < 4; ++i) {
            int nextX = curr.x + dx[i];
            int nextY = curr.y + dy[i];

            // проверяем границы
            if (nextX >= 0 && nextX < w && nextY >= 0 && nextY < h) {
                // Ищем соседа, у которого шаг на 1 меньше текущего
                if (dist[nextY][nextX] == dist[curr.y][curr.x] - 1) {
                    curr = Cell(nextX, nextY);
                    result.cells.push_back(curr);
                    break; 
                }
            }
        }
    }

    // переворот от старта к концу
    reversePath(result.cells);

    result.length = dist[end.y][end.x];

    return result;
}

Path algLi::shortestPath(){
    int w = maze.getWidth();
    int h = maze.getHeight();
    
    Cell start = maze.getStartCell();
    Cell end = maze.getEndCell();

    std::vector<std::vector<int>> dist(h, std::vector<int>(w, -1)); // волна по умолч -1
    std::queue<Cell> q;

    dist[start.y][start.x] = 0;
    q.push(start);

    int dx[] = {0, 0, -1, 1};
    int dy[] = {-1, 1, 0, 0};

    bool found = false;

    while(!q.empty()) {
        Cell curr = q.front(); // самый первый из очереди
        q.pop(); // удаляем из очереди 

        if (curr == end) { // нашли финиш
            found = true;
            break;
        }

        for (int i = 0; i < 4; ++i) { // 4 соседние клетки
            int nextX = curr.x + dx[i];
            int nextY = curr.y + dy[i];

            if (maze.isWalkable(nextX, nextY)) { // не стена
                if (dist[nextY][nextX] == -1) { // ещё не ходили сюда
                    dist[nextY][nextX] = dist[curr.y][curr.x] + 1; // дист до клетки пред + 1
                    q.push(Cell(nextX, nextY)); // ложим в очередь
                }
            }
        }
    }
    if (!found) {
        return Path();
    }

    return unroll(dist, start, end);
}