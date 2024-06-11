package gameField;

import entities.*;

import java.io.InputStream;
import java.util.HashMap;
import java.util.List;
import java.util.Scanner;
import java.util.StringTokenizer;

public class GameField {
    public enum FieldType {
        EMPTY(0),
        WALL(1),
        PORTAL(2),
        BLOCK_WITH_COINS(3),
        POWER_PELLET(4),
        FRUIT(5),
        PLAYER(6),
        BLINKY(7),
        PINKY(8),
        INKY(9),
        CLYDE(10);
        private int code;
        private HashMap<Integer, FieldType> map = new HashMap<>();

        FieldType(int i) {
            code = i;
        }

        public int GetCode() {
            return code;
        }
        static public FieldType ValueOf(int code){
            return switch (code) {
                case 0 -> EMPTY;
                case 1 -> WALL;
                case 2 -> PORTAL;
                case 3 -> BLOCK_WITH_COINS;
                case 4 -> POWER_PELLET;
                case 5 -> FRUIT;
                case 6 -> PLAYER;
                case 7 -> BLINKY;
                case 8 -> PINKY;
                case 9 -> INKY;
                case 10 -> CLYDE;
                default -> throw new RuntimeException("Unexpected fieldType: " + code);
            };

        }
    };
    private final int tileSize;

    private final int rowsNum = 31;
    private final int colsNum = 28;
    private FieldType[][] gameField = new FieldType[rowsNum][colsNum];
    private int playerCoins = 0;
    public void CollectCoin(int i, int j) {
        playerCoins++;
        gameField[i][j] = FieldType.EMPTY;
    }

    public FieldType[][] GetGameField() {
        return gameField;
    }

    public GameField(Player player, List<Ghost> ghosts, int tileSize) {
        this.tileSize = tileSize;
        LoadGame(player, ghosts);
    }
    public void LoadGame(Player player, List<Ghost> ghosts) {
        InputStream in = GameField.class.getClassLoader().getResourceAsStream("GameField.txt");
        assert in != null;
        Scanner scanner = new Scanner(in);
        int i = 0;

        while(scanner.hasNextLine()) {
            String line = scanner.nextLine();
            StringTokenizer tokens = new StringTokenizer(line, " ");
            int j = 0;
            while(tokens.hasMoreTokens()){
                String s = tokens.nextToken();
                FieldType obj = FieldType.ValueOf(Integer.parseInt(s));
                switch (obj) {
                    case PLAYER:
                        player.SetGameField(this);
                        player.SetX(j * tileSize);
                        player.SetY(i * tileSize);
                        break;
                    case BLINKY:
                        Blinky blinky = new Blinky(player, this, j * tileSize, i * tileSize, tileSize);
                        ghosts.add(blinky);
                        break;
                    case PINKY:
                        Pinky pinky = new Pinky(player, this, j * tileSize, i * tileSize, tileSize);
                        ghosts.add(pinky);
                        break;
                    case INKY:
                        Inky inky = new Inky(player, this, j * tileSize, i * tileSize, tileSize);
                        ghosts.add(inky);
                        break;
                    case CLYDE:
                        Clyde clyde = new Clyde(player, this, j * tileSize, i * tileSize, tileSize);
                        ghosts.add(clyde);
                        break;
                }
                gameField[i][j] = obj;
                ++j;
            }
            ++i;
        }
    }
    public FieldType GetEntityCell(Entity entity) {
        return gameField[entity.GetY() / tileSize][entity.GetX() / tileSize];
    }
    public int GetRowsNum() {
        return rowsNum;
    }
    public int GetColsNum() {
        return colsNum;
    }
    public void update(List<Ghost> ghosts) {
        for(Ghost g : ghosts) {
            g.UpdateSpeed(GetGameField());
            g.Update();
        }
    }
}
