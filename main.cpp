#include <iostream>
#include <vector>

using std::vector;

struct point
{
    point(size_t xval, size_t yval) : x(xval), y (yval) {}
    int x;
    int y;

    void print() {
        std::cout << "(" << x << "," << y << ")";
    }
};

size_t distance(const point & p1, const point & p2)
{
    return abs(p1.x-p2.x)+abs(p1.y-p2.y);
}

class solution
{
  public:
    size_t bestMeetingPoint(const vector<vector<int>> & grid) {
        vector<point> starting;
        vector<vector<int>> visited;
        for (size_t i = 0; i < grid.size(); i++) {
            vector<int> temp;
            for (size_t j = 0; j < grid[0].size(); j++) {
                if (grid[i][j] != 0)
                    starting.push_back(point(i,j));
                temp.push_back(0);
            }
            visited.push_back(temp);
        }

        for (size_t i = 0; i < starting.size()-1; i++) {
            for (size_t j = i+1; j < starting.size(); j++) {
                std::cout << "From ";
                starting[i].print();
                std::cout << " to ";
                starting[j].print();
                std::cout << ":"  << std::endl;
                auto cpy = visited;
                auto paths = shortestPaths(grid, starting[i], starting[j], cpy);
                for (auto path : paths) {
                    for (auto pt : path)
                        pt.print();
                    std::cout << std::endl;
                }
            }
        }
        return 0;
    }

  private:
    vector<point> getNext(const vector<vector<int>> & grid, const point & curr, vector<vector<int>> & visited)
    {
        vector<point> next;
        size_t nrows = grid.size(), ncols = grid[0].size();
        if (curr.x > 0 && !visited[curr.x-1][curr.y])
            next.push_back(point(curr.x-1, curr.y));
        if ( curr.x < nrows-1 && !visited[curr.x+1][curr.y])
            next.push_back(point(curr.x+1, curr.y));
        if (curr.y > 0 && !visited[curr.x][curr.y-1])
            next.push_back(point(curr.x, curr.y-1));
        if (curr.y < ncols-1 && !visited[curr.x][curr.y+1])
            next.push_back(point(curr.x, curr.y+1));
        
        return next;
    }

    vector<vector<point>> shortestPaths(const vector<vector<int>> & grid, const point & from, const point & to, vector<vector<int>> & visited)
    {
        visited[from.x][from.y] = 1;
        vector<vector<point>> paths;
        if (distance(from, to) == 0)
        {
            vector<point> temp;
            temp.push_back(from);
            paths.push_back(temp);
        }
        else {
            vector<point> next = getNext(grid, from, visited);
            vector<vector<point>> cands;
            for (auto pt : next) {
                auto cpy = visited;
                auto temp = shortestPaths(grid, pt, to, cpy);
                for (auto pth : temp) {
                    pth.insert(pth.begin(), from);
                    cands.push_back(pth);
                }
            }
            if (!cands.empty())
            {
                size_t shortest = cands[0].size();
                for (size_t i = 1; i < cands.size(); i++)
                    if (cands[i].size() < shortest)
                        shortest = cands[i].size();

                for (size_t i = 0; i < cands.size(); i++) {
                    if (cands[i].size() == shortest) {
                        paths.push_back(cands[i]);
                        // for (auto pt : cands[i])
                        //     pt.print();
                        // std::cout << std::endl;
                    }
                }
            }
        }
        return paths;
    }
};

int main()
{
    vector<vector<int>> grid
    {
        {1,0,0,0,1},
        {0,0,0,0,0},
        {0,0,1,0,0}
    };

    solution soln;
    size_t dist = soln.bestMeetingPoint(grid);

    return 0;
}
