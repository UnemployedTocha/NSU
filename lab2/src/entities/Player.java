package entities;

import collisions.EntityMovement;
import gameField.GameField;

public class Player extends Entity{
    private int inputDx;
    private int inputDy;
    private final int defaultDx = -1;
    private final int defaultDy = 0;
    private long lastInputTime = 0;
    public Player(GameField gameField, int tileSize) {
        super(gameField, tileSize, tileSize);
        this.SetSpeed(defaultDx, defaultDy);

        inputDx = dx;
        inputDy = dy;

    }
    public void SetGameField(GameField gameField) {
        this.gameField = gameField;
    }
    public void MoveUp() {
        lastInputTime = System.currentTimeMillis();
        inputDy = Math.abs(inputDy + inputDx)*(-1);
        inputDx = 0;
    }
    public void MoveDown() {
        lastInputTime = System.currentTimeMillis();
        inputDy = Math.abs(inputDy + inputDx);
        inputDx = 0;
    }
    public void MoveLeft() {
        lastInputTime = System.currentTimeMillis();
        inputDx = Math.abs(inputDy + inputDx)*(-1);
        inputDy = 0;
    }
    public void MoveRight() {
        lastInputTime = System.currentTimeMillis();
        inputDx = Math.abs(inputDy + inputDx);
        inputDy = 0;
    }
    public long GetLastInputTime() {
        return lastInputTime;
    }
    public int GetInputDx() { return inputDx; }
    public int GetInputDy() { return inputDy; }
    public void SetInputSpeedAsActual() {
        dx = inputDx;
        dy = inputDy;
    }
}
