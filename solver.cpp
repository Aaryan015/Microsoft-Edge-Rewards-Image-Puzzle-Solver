#include <iostream>
#include <vector>
#include <queue>
#include <unordered_map>
#include <algorithm>
#include <string>
#include <cmath>
using namespace std;

// Define the target state of the puzzle
const vector<vector<int>> TARGET = {
    {1, 2, 3},
    {4, 5, 6},
    {7, 8, 0}
};

// Directions for moving: {row_change, col_change}
const vector<pair<int, int>> DIRECTIONS = {
    {-1, 0}, // Up
    {1, 0},  // Down
    {0, -1}, // Left
    {0, 1}   // Right
};

// Function to convert a board to a unique string representation
string boardToString(const vector<vector<int>>& board) {
    string res;
    for (const auto& row : board) {
        for (int cell : row) {
            res += to_string(cell) + ",";
        }
    }
    return res;
}

// Function to find the position of the empty tile (0)
pair<int, int> findZero(const vector<vector<int>>& board) {
    for (int i = 0; i < 3; ++i) {
        for (int j = 0; j < 3; ++j) {
            if (board[i][j] == 0) {
                return {i, j};
            }
        }
    }
    return {-1, -1};
}

// Function to calculate the Manhattan distance heuristic
int manhattanDistance(const vector<vector<int>>& board) {
    int distance = 0;
    for (int i = 0; i < 3; ++i) {
        for (int j = 0; j < 3; ++j) {
            if (board[i][j] != 0) {
                int target = board[i][j] - 1;
                int targetRow = target / 3;
                int targetCol = target % 3;
                distance += abs(i - targetRow) + abs(j - targetCol);
            }
        }
    }
    return distance;
}

// Function to solve the 8-puzzle problem using the A* algorithm
void solvePuzzle(vector<vector<int>>& board) {
    unordered_map<string, string> parent; // Map to trace steps
    unordered_map<string, string> move;  // Map to store moves
    unordered_map<string, int> cost;    // Map to store costs

    auto cmp = [&](const string& a, const string& b) {
        return cost[a] > cost[b];
    };

    priority_queue<string, vector<string>, decltype(cmp)> pq(cmp);

    string start = boardToString(board);
    string goal = boardToString(TARGET);

    pq.push(start);
    cost[start] = manhattanDistance(board);
    parent[start] = "";
    move[start] = "";

    while (!pq.empty()) {
        string curr = pq.top();
        pq.pop();

        if (curr == goal) break;

        vector<vector<int>> currBoard(3, vector<int>(3));
        int k = 0;
        for (int i = 0; i < 3; ++i) {
            for (int j = 0; j < 3; ++j) {
                currBoard[i][j] = stoi(curr.substr(k, 1));
                k += 2; // Skip ',' separator
            }
        }

        auto [zeroRow, zeroCol] = findZero(currBoard);

        for (const auto& [dr, dc] : DIRECTIONS) {
            int newRow = zeroRow + dr;
            int newCol = zeroCol + dc;

            if (newRow >= 0 && newRow < 3 && newCol >= 0 && newCol < 3) {
                swap(currBoard[zeroRow][zeroCol], currBoard[newRow][newCol]);
                string next = boardToString(currBoard);
                int newCost = manhattanDistance(currBoard);

                if (!cost.count(next) || cost[next] > cost[curr] + newCost) {
                    parent[next] = curr;
                    move[next] = "Move " + to_string(currBoard[zeroRow][zeroCol]);
                    cost[next] = cost[curr] + newCost;
                    pq.push(next);
                }

                swap(currBoard[zeroRow][zeroCol], currBoard[newRow][newCol]);
            }
        }
    }

    // Backtrack to find the solution path
    vector<string> steps;
    string curr = goal;
    while (parent[curr] != "") {
        steps.push_back(move[curr]);
        curr = parent[curr];
    }

    reverse(steps.begin(), steps.end());

    // Print the steps
    cout << "Steps to solve the puzzle:" << endl;
    for (const string& step : steps) {
        cout << step << endl;
    }

    cout << "Minimum number of moves: " << steps.size() << endl;
}

int main() {
    vector<vector<int>> board = {
        {4, 1, 2},
        {5, 0, 3},
        {7, 8, 6}
    };

    solvePuzzle(board);

    return 0;
}
