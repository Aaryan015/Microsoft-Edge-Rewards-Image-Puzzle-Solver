### I solve the puzzle everyday for fun (and for the reward points of course😉). This code shows the necessary steps required to solve it as quickly as possible✨
-----
### About: 🪄
This problem is similar to [LeetCode 773: Sliding Puzzle](https://leetcode.com/problems/sliding-puzzle/description/). The only slight difference there is the board size: 2x3. And for some test cases, the board is unsolvable. Here, the puzzle generated the Microsoft Edge is **always solvable**.
-----
### Approach:🦮
Uses:
1. Manhattan Distance: The heuristic used to estimate the cost of reaching the goal from the current state.
2. Priority Queue: Used to prioritize states with lower total cost (cost so far + heuristic).
3. Parent Map: Keeps track of the predecessor of each state for reconstructing the solution path.
4. Direction Vectors: Simplify the swapping of tiles in four possible directions.

### Setup: 🧰
1. Clone this repository:
```sh
https://github.com/Aaryan015/Microsoft-Edge-Rewards-Image-Puzzle-Solver.git
```
2. Change the input board in the main() function, based on the puzzle. Enter the respective numbers of the tiles same as on the puzzle. For example, if the puzzle is like: ![refresh](https://github.com/Aaryan015/Microsoft-Edge-Rewards-Image-Puzzle-Solver/blob/main/sample%20puzzle.png?raw=true)
Then change/enter the input in the main() function to match exactly as the puzzle:
```
{5,8,6}
{7,0,3} //0 represents the empty tile/space
{1,2,4}
```
