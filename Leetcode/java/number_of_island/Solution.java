package number_of_island;

import java.util.ArrayDeque;

class Solution {
	private static final int[][] DIRS = {{1, 0}, {-1, 0}, {0, 1}, {0, -1}};

	public int numIslands(char[][] grid) {
		int m = grid.length, n = grid[0].length;
		boolean[][] visited = new boolean[m][n];
		int count = 0;

		for (int r = 0; r < m; r++) {
			for (int c = 0; c < n; c++) {
				if (grid[r][c] == '1' && !visited[r][c]) {
					count++;
					ArrayDeque<int[]> q = new ArrayDeque<>();
					q.offer(new int[] {r, c});
					visited[r][c] = true;

					while (!q.isEmpty()) {
						int[] cur = q.poll();
						for (int[] d : DIRS) {
							int nr = cur[0] + d[0], nc = cur[1] + d[1];
							if (nr < 0 || nr >= m || nc < 0 || nc >= n)
								continue;
							if (grid[nr][nc] == '0' || visited[nr][nc])
								continue;
							visited[nr][nc] = true;
							q.offer(new int[] {nr, nc});
						}
					}
				}
			}
		}
		return count;
	}
}

