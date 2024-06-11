package entities;

import gameField.GameField;

public abstract class Ghost extends Entity{
    protected boolean isEatable = false;
    protected int tileSize;

    Ghost(GameField gameField, int x, int y, int tileSize) {
        super(gameField, tileSize, tileSize);
        dx = 0;
        dy = 0;
        this.x = x;
        this.y = y;
        this.tileSize = tileSize;
    }

    public abstract void UpdateSpeed(GameField.FieldType[][] gameField);
}
