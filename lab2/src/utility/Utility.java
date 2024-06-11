package utility;

import gameField.GameField;

import java.util.Arrays;
import java.util.LinkedList;
import java.util.Queue;

public class Utility {
    private static final int[] ROW_OFFSETS = {-1, 0, 1, 0};
    private static final int[] COL_OFFSETS = {0, 1, 0, -1};

    private static final String[] DIRECTIONS = {"UP", "RIGHT", "DOWN", "LEFT"};
    public static int[] ShortestPath(GameField.FieldType[][] matrix, int startRow, int startCol, int endRow, int endCol, int dx, int dy) {
        int rows = matrix.length;
        int cols = matrix[0].length;
        int[][] distances = new int[rows][cols];
        int[][] prevDirection = new int[rows][cols];

        for(int[] row : distances) {
            Arrays.fill(row, Integer.MAX_VALUE);
        }
        for(int[] row : prevDirection) {
            Arrays.fill(row, -1);
        }
        distances[startRow][startCol] = 0;
        Queue<int[]> queue = new LinkedList<>();
        queue.add(new int[]{startRow, startCol, -1});

        while (!queue.isEmpty()) {
            int[] cell = queue.poll();
            int row = cell[0];
            int col = cell[1];
            int dir = cell[2];
            int currDistance = distances[row][col];

            for(int i = 0; i < 4; i++) {
                int newRow = row + ROW_OFFSETS[i];
                int newCol = col + COL_OFFSETS[i];
                if (newRow >= 0 && newRow < rows && newCol >= 0 && newCol < cols &&
                    matrix[newRow][newCol] != GameField.FieldType.WALL && distances[newRow][newCol] == Integer.MAX_VALUE) {
                        distances[newRow][newCol] = currDistance + 1;
                    if (dir == -1) {
                        prevDirection[newRow][newCol] = i;
                    } else {
                        prevDirection[newRow][newCol] = prevDirection[row][col];
                    }
                    queue.add(new int[]{newRow, newCol, i});
                }
            }
        }
        int[] outputSpeed = new int[2];
        // If goal is unreachable.
        if(distances[endRow][endCol] == Integer.MAX_VALUE) {
            outputSpeed[0] = -1;
            outputSpeed[1] = -1;
            return outputSpeed;
        }
        int firstDirection = prevDirection[endRow][endCol];
        // If Entity is already no goal.
        if(firstDirection == -1) {
            return outputSpeed;
        }
        switch(DIRECTIONS[firstDirection]) {
            case "UP":
                outputSpeed[1] = Math.abs(dy + dx)*(-1);
                break;
            case "DOWN":
                outputSpeed[1] = Math.abs(dy + dx);
                break;
            case "LEFT":
                outputSpeed[0] = Math.abs(dy + dx)*(-1);
                break;
            case "RIGHT":
                outputSpeed[0] = Math.abs(dy + dx);
                break;
        }

        return outputSpeed;
    }
}
