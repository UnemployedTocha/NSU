#ifndef LEVEL_H
#define LEVEL_H

#include <vector>
#include <QString>
#include "fieldtype.h"

class Level
{
public:
    Level() = delete;
    ~Level() = default;
    Level(QString lvlNum);

    void MoveUp();
    void MoveDown();
    void MoveLeft();
    void MoveRight();

    void loadSave(QString saveName);
    void loadLevel(QString lvlNum);

    void saveGame(QString fileName = "user_save");
    void saveUserData(const QString& userName);

    void newGame();
    void restart();
    const bool CheckWin();

    const unsigned GetStepsCounter();
    const unsigned GetLevelNumb();
    const std::vector<std::vector<FieldType>> GetGameField() const;

private:
    std::vector<std::vector<FieldType>> gameField_;
    std::pair<unsigned, unsigned> playerPos_;
    unsigned lineNum_ = 0;
    unsigned maxColumnNum_= 0;
    unsigned goalNum_ = 0;
    unsigned boxOnGoalNum_ = 0;

    QString currentLevel = 0;
    unsigned steps = 0;
    QString saveCurrentLevel = 0;
    unsigned saveSteps = 0;

    std::vector<std::pair<unsigned, unsigned>> UserData_;
    bool isPlayerOnGoal_;

    void InitializeUserData();
    FieldType ObjAfterMoving();
    void IncrementFieldData(const FieldType& obj);
    FieldType QCharToFieldTypeConvertion(QChar ch);
    QChar FieldTypeToQCharConvertion(const FieldType& obj);
    QString GetLvlPath(const QString& lvlName);
    QString GetSavePath(const QString& saveName);
    QString GetUserDataSavePath(const QString& saveName);
};

#endif // LEVEL_H
