#include <iostream>
#include <vector>
#include "moveVisitor.hpp"
#include "point.hpp"
#include "point.cpp"
#include "moveVisitor.cpp"

// // exploratory
// class solution
// {
//   public:
//     size_t bestMeetingPoint(const vector<vector<int>> & grid) {
//         vector<point> starting;
//         vector<vector<int>> visited;
//         for (size_t i = 0; i < grid.size(); i++) {
//             vector<int> temp;
//             for (size_t j = 0; j < grid[0].size(); j++) {
//                 if (grid[i][j] != 0)
//                     starting.push_back(point(i,j));
//                 temp.push_back(0);
//             }
//             visited.push_back(temp);
//         }

//         for (size_t i = 0; i < starting.size()-1; i++) {
//             for (size_t j = i+1; j < starting.size(); j++) {
//                 std::cout << "From ";
//                 starting[i].print();
//                 std::cout << " to ";
//                 starting[j].print();
//                 std::cout << ":"  << std::endl;
//                 auto cpy = visited;
//                 auto paths = shortestPaths(grid, starting[i], starting[j], cpy);
//                 for (auto path : paths) {
//                     for (auto pt : path)
//                         pt.print();
//                     std::cout << std::endl;
//                 }
//             }
//         }

//         for (size_t i = 0; i < grid.size(); i++) {
//             for (size_t j = 0; j < grid[i].size(); j++) {
//                 int dist = 0;
//                 for (size_t k = 0; k < starting.size(); k++) {
//                     dist += distance(point(i, j), starting[k]);
//                 }
//                 std::cout << dist << " ";
//             }
//             std::cout << std::endl;
//         }
        
//         return 0;
//     }

//   private:
//     vector<point> getNext(const vector<vector<int>> & grid, const point & curr, vector<vector<int>> & visited)
//     {
//         vector<point> next;
//         size_t nrows = grid.size(), ncols = grid[0].size();
//         if (curr.x > 0 && !visited[curr.x-1][curr.y])
//             next.push_back(point(curr.x-1, curr.y));
//         if ( curr.x < nrows-1 && !visited[curr.x+1][curr.y])
//             next.push_back(point(curr.x+1, curr.y));
//         if (curr.y > 0 && !visited[curr.x][curr.y-1])
//             next.push_back(point(curr.x, curr.y-1));
//         if (curr.y < ncols-1 && !visited[curr.x][curr.y+1])
//             next.push_back(point(curr.x, curr.y+1));
        
//         return next;
//     }

//     vector<vector<point>> shortestPaths(const vector<vector<int>> & grid, const point & from, const point & to, vector<vector<int>> & visited)
//     {
//         visited[from.x][from.y] = 1;
//         vector<vector<point>> paths;
//         if (distance(from, to) == 0)
//         {
//             vector<point> temp;
//             temp.push_back(from);
//             paths.push_back(temp);
//         }
//         else {
//             vector<point> next = getNext(grid, from, visited);
//             vector<vector<point>> cands;
//             for (auto pt : next) {
//                 auto cpy = visited;
//                 auto temp = shortestPaths(grid, pt, to, cpy);
//                 for (auto pth : temp) {
//                     pth.insert(pth.begin(), from);
//                     cands.push_back(pth);
//                 }
//             }
//             if (!cands.empty())
//             {
//                 size_t shortest = cands[0].size();
//                 for (size_t i = 1; i < cands.size(); i++)
//                     if (cands[i].size() < shortest)
//                         shortest = cands[i].size();

//                 for (size_t i = 0; i < cands.size(); i++) {
//                     if (cands[i].size() == shortest) {
//                         paths.push_back(cands[i]);
//                         // for (auto pt : cands[i])
//                         //     pt.print();
//                         // std::cout << std::endl;
//                     }
//                 }
//             }
//         }
//         return paths;
//     }
// };


template<int N>
int slopeAlong(const point & curr, const vector<point> & start);

template<>
int slopeAlong<1>(const point & curr, const vector<point> & start) {
    int slope = 0;
    for (auto pt : start) {
        if (pt.x != curr.x)
            slope += (curr.x-pt.x)/abs(curr.x-pt.x);
    }
    return slope;
}

template<>
int slopeAlong<2>(const point & curr, const vector<point> & start) {
    int slope = 0;
    for (auto pt : start) {
        if (curr.y != pt.y)
            slope += (curr.y-pt.y)/abs(curr.y-pt.y);
    }
    return slope;
}

class solution {
  public:
    point bestMeetingPoint(const vector<vector<int>> & grid) {        
        point prev(0,0), curr;
        vector<point> start = getStartingPoints(grid);

        for (size_t i = 0; i < grid.size(); i++) {
            for (size_t j = 0; j < grid[i].size(); j++) {
                int dist = 0;
                for (size_t k = 0; k < start.size(); k++) {
                    dist += distance(point(i, j), start[k]);
                }
                std::cout << dist << " ";
            }
            std::cout << std::endl;
        }
        std::cout << std::endl;

        // for (size_t i = 0; i < grid.size(); i++) {
        //     for (size_t j = 0; j < grid[i].size(); j++) {
        //         std::cout << slopeAlong<1>(point(i,j), start) << " ";
        //     }
        //     std::cout << std::endl;
        // }
        // std::cout << std::endl;

        // for (size_t i = 0; i < grid.size(); i++) {
        //     for (size_t j = 0; j < grid[i].size(); j++) {
        //         std::cout << slopeAlong<2>(point(i,j), start) << " ";
        //     }
        //     std::cout << std::endl;
        // }
        // std::cout << std::endl;

        moveVisitor * moveup = new moveUpVisitor(grid);
        moveVisitor * movedown = new moveDownVisitor(grid);
        moveVisitor * moveleft = new moveLeftVisitor(grid);
        moveVisitor * moveright = new moveRightVisitor(grid);
        vector<moveVisitor*> visitors{moveup, movedown, moveleft, moveright};
        
        // prev.print();
        // if (slopeX < 0)
        //     curr = prev.apply(movedown);
        // else if (slopeY < 0)
        //     curr = prev.apply(moveright);
        // while (!curr.isSame(prev)) {
        //     std::cout << " -> ";
        //     slopeX = slopeAlong<1>(curr, start);
        //     slopeY = slopeAlong<2>(curr, start);
        //     prev = curr;
        //     prev.print();
        //     if (slopeX < 0)
        //         curr = prev.apply(movedown);
        //     else if (slopeY < 0)
        //         curr = prev.apply(moveright);
        // }

        // slopeX = slopeAlong<1>(curr, start);
        // slopeY = slopeAlong<2>(curr, start);
        // prev = curr;
        // if (slopeY < 0)
        //     curr = prev.apply(moveright);
        // else if (slopeX < 0)
        //     curr = prev.apply(movedown);
        // else if (slopeX > 0)
        //     curr = prev.apply(moveup);
        // while (!curr.isSame(prev)) {
        //     std::cout << " -> ";
        //     slopeX = slopeAlong<1>(curr, start);
        //     slopeY = slopeAlong<2>(curr, start);
        //     prev = curr;
        //     prev.print();
        //     if (slopeY < 0)
        //         curr = prev.apply(moveright);
        //     else if (slopeX < 0)
        //         curr = prev.apply(movedown);
        // }
        // std::cout << std::endl;

        prev.print();
        curr = prev;
        int diff = distanceSum(curr, start)-distanceSum(prev, start);
        for (size_t i = 0; i < visitors.size(); i++) {
            auto temp = prev.apply(visitors[i]);             
            if (!prev.isSame(temp)) {
                if (distanceSum(temp, start)-distanceSum(prev, start) < diff)
                {
                    diff = distanceSum(temp, start)-distanceSum(prev, start);
                    curr = temp;
                }                
            }
        }

        while (!curr.isSame(prev)) {
            std::cout << "->";
            curr.print();
            prev = curr;
            curr = prev;
            int shortest = distanceSum(prev, start);
            for (size_t i = 0; i < visitors.size(); i++) {
                auto temp = prev.apply(visitors[i]);             
                if (!prev.isSame(temp)) {
                    if (distanceSum(temp, start) < shortest)
                    {
                        shortest = distanceSum(temp, start);
                        curr = temp;
                    }                
                }
            }
        }
        std::cout << std::endl;

        delete moveup;
        delete movedown;
        delete moveleft;
        delete moveright;
        
        return curr;
    }

  private:
    vector<point> getStartingPoints(const vector<vector<int>> & grid) {
        vector<point> start;
        for (size_t i = 0; i < grid.size(); i++) {
            for (size_t j = 0; j < grid[i].size(); j++)
                if (grid[i][j] != 0)
                    start.push_back(point(i, j));
        }
        return start;
    }
    
    int distanceSum(const point & curr, const vector<point> & start) {
        int dist = 0;
        for (size_t i = 0; i < start.size(); i++)
            dist += distance(curr, start[i]);

        return dist;
    }
};


int main()
{
    vector<vector<int>> grid
    {
        {1,0,0,0,0},
        {0,0,0,0,1},
        {0,1,0,0,0}
    };

    solution soln;
    auto bmp = soln.bestMeetingPoint(grid);

    return 0;
}
