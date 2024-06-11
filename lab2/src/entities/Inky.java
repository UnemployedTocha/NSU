package entities;

import gameField.GameField;
import utility.Utility;

public class Inky extends Ghost{
    Player player;
    public Inky(Player player, GameField gameField, int x, int y, int tileSize) {
        super(gameField, x, y, tileSize);
        dx = 1;
        dy = 0;
        this.player = player;
    }
    private void CalcNewWay() {
        GameField.FieldType[][] arr = gameField.GetGameField();
        int playerI = player.GetX() / tileSize;
        int playerJ = player.GetY() / tileSize;
        int ghostI = x / tileSize;
        int ghostJ = y / tileSize;


    }

    @Override
    public void UpdateSpeed(GameField.FieldType[][] gameField) {
        if(hitbox.x / tileSize == (hitbox.x + hitbox.width) / tileSize && hitbox.y / tileSize == (hitbox.y + hitbox.height) / tileSize) {
            int[] speed = Utility.ShortestPath(gameField, y / tileSize, x / tileSize, player.GetY() / tileSize, player.GetX() / tileSize, dx, dy);
            dx = speed[0];
            dy = speed[1];
        }
    }
}
