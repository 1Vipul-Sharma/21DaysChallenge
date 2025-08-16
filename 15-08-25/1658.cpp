//TLE
#include <iostream>
#include <vector>
#include <algorithm> // For std::max

class Solution {
public:
    // Helper function to calculate happiness for a given grid configuration.
    // It's safer to have this outside the recursive function.
    int calculate_total_happiness(int m, int n, const std::vector<std::vector<int>>& grid) {
        if (grid.empty() || grid[0].empty()) {
            return 0;
        }

        int total_happiness = 0;
        int dr[] = {-1, 1, 0, 0}; // N, S
        int dc[] = {0, 0, -1, 1}; // W, E

        for (int r = 0; r < m; ++r) {
            for (int c = 0; c < n; ++c) {
                if (grid[r][c] == 0) continue; // Skip empty cells

                int neighbor_count = 0;
                // Check neighbors
                for (int i = 0; i < 4; ++i) {
                    int nr = r + dr[i];
                    int nc = c + dc[i];
                    if (nr >= 0 && nr < m && nc >= 0 && nc < n && grid[nr][nc] != 0) {
                        neighbor_count++;
                    }
                }

                if (grid[r][c] == 120) { // Introvert
                    total_happiness += 120 - (30 * neighbor_count);
                } else if (grid[r][c] == 40) { // Extrovert
                    total_happiness += 40 + (20 * neighbor_count);
                }
            }
        }
        return total_happiness;
    }

    void solve(int r, int c, int m, int n, int intro, int extro, 
               std::vector<std::vector<int>>& grid, int& max_happiness) {
        
        // Base Case: If we have moved past the last cell, a full configuration is ready.
        if (r == m) {
            max_happiness = std::max(max_happiness, calculate_total_happiness(m, n, grid));
            return;
        }

        // --- Correct Traversal Logic ---
        int next_r = (c == n - 1) ? r + 1 : r;
        int next_c = (c == n - 1) ? 0 : c + 1;

        // --- Option 1: Place an Introvert at (r, c) ---
        if (intro > 0) {
            grid[r][c] = 120; // Choose
            solve(next_r, next_c, m, n, intro - 1, extro, grid, max_happiness); // Explore
        }

        // --- Option 2: Place an Extrovert at (r, c) ---
        if (extro > 0) {
            grid[r][c] = 40; // Choose
            solve(next_r, next_c, m, n, intro, extro - 1, grid, max_happiness); // Explore
        }

        // --- Option 3: Leave cell (r, c) empty AND Backtrack ---
        // This acts as the "un-choose" step for options 1 and 2, and as the
        // exploration path for the "leave empty" choice.
        grid[r][c] = 0; 
        solve(next_r, next_c, m, n, intro, extro, grid, max_happiness);
    }

    int getMaxGridHappiness(int m, int n, int introvertsCount, int extrovertsCount) {
        std::vector<std::vector<int>> grid(m, std::vector<int>(n, 0));
        int max_happiness = 0;
        solve(0, 0, m, n, introvertsCount, extrovertsCount, grid, max_happiness);
        return max_happiness;
    }
};

tc - O(3^(m*n));
sc - O(m*n)+O(m+n) recusrion stack space;