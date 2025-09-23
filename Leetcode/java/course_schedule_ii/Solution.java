package course_schedule_ii;

import java.util.ArrayDeque;

class Solution {

	private static void initDim(int[][] prerequisites, int[] dim) {
		for (int[] prerequisite : prerequisites) {
			++dim[prerequisite[0]];
		}
	}

	private static void find0Dim(int numCourses, int[] dim, ArrayDeque<Integer> queue) {
		for (int i = 0; i < numCourses; ++i) {
			if (dim[i] == 0) {
				queue.offer(i);
			}
		}
	}

	private static void decreaseDim(int[][] prerequisites, int preCourse, int[] dim) {
		for (int[] prerequisite : prerequisites) {
			if (prerequisite[1] == preCourse) {
				--dim[prerequisite[0]];
			}
		}
	}

	public int[] findOrder(int numCourses, int[][] prerequisites) {
		ArrayDeque<Integer> queue = new ArrayDeque<>();
		int[] ans = new int[numCourses];
		int[] dim = new int[numCourses];
		boolean[] visit = new boolean[numCourses];
		ArrayDeque<Integer> visited = new ArrayDeque<>();

		initDim(prerequisites, dim);
		find0Dim(numCourses, dim, queue);

		while (!queue.isEmpty()) {
			int preCourse = queue.pollFirst();
			if (visit[preCourse]) {
				continue;
			}
			System.out.println("preCourse: " + preCourse);
			visit[preCourse] = true;
			visited.offer(preCourse);
			dim[preCourse] = -1;
			decreaseDim(prerequisites, preCourse, dim);
			find0Dim(prerequisites.length, dim, queue);
		}

		if (visited.size() == numCourses) {
			for (int i = 0; i < numCourses; ++i) {
				ans[i] = visited.pollFirst();
			}
			return ans;
		}
		return new int[0];
	}
}