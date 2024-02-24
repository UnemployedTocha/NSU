#include "level.h"
#include <stdexcept>
#include <QFile>
#include <QDir>
#include <QTextStream>

FieldType Level::QCharToFieldTypeConvertion(QChar ch) {
    switch(ch.toLatin1()) {
    case '#':
        return FieldType::WALL;
    case '@'  :
        return FieldType::PLAYER;
    case '+':
        return FieldType::PLAYER_ON_GOAL;
    case 'o':
        return FieldType::BOX;
    case '*':
        return FieldType::BOX_ON_GOAL;
    case '.':
        return FieldType::GOAL;
    case ' ':
        return FieldType::EMPTY;
    default:
        throw std::invalid_argument("Invalid game field");
    }
}

QChar Level::FieldTypeToQCharConvertion(const FieldType& obj)
{
    switch(obj) {
    case FieldType::WALL:
        return '#';
    case FieldType::PLAYER:
        return '@';
    case FieldType::PLAYER_ON_GOAL:
        return '+';
    case FieldType::BOX:
        return 'o';
    case FieldType::BOX_ON_GOAL:
        return '*';
    case FieldType::GOAL:
        return '.';
    case FieldType::EMPTY:
        return ' ';
    default:
        throw std::invalid_argument("Invalid game field");
    }
}

QString Level::GetLvlPath(const QString& lvlName)
{
    QString path = "C:/Users/Pepega/Documents/Qt/PeepoSad3/Levels/";
    path += lvlName;
    path += ".txt";
    return path;
}

QString Level::GetSavePath(const QString& saveName)
{
    QString path = "C:/Users/Pepega/Documents/Qt/PeepoSad3/Saves/";
    path += saveName;
    path += ".txt";
    return path;
}

QString Level::GetUserDataSavePath(const QString& saveName)
{
    QString path = "C:/Users/Pepega/Documents/Qt/PeepoSad3/LeaderboardSaves/";
    path += saveName;
    path += ".txt";
    return path;
}

Level::Level(QString lvlNum)
{
    currentLevel = lvlNum;
    InitializeUserData();
    loadLevel(lvlNum);

}


FieldType Level::ObjAfterMoving()
{
    if(isPlayerOnGoal_) {
        isPlayerOnGoal_ = false;
        return FieldType::GOAL;
    }
    return FieldType::EMPTY;
}

void Level::MoveUp()
{

    unsigned x = playerPos_.first;
    unsigned y = playerPos_.second;

    switch(gameField_[x - 1][y]) {
    case FieldType::EMPTY:
        ++steps;
        gameField_[x][y] = ObjAfterMoving();
        gameField_[x - 1][y] = FieldType::PLAYER;
        playerPos_.first = x - 1;
        playerPos_.second = y;
        break;
    case FieldType::GOAL:
        ++steps;
        gameField_[x][y] = ObjAfterMoving();
        gameField_[x-1][y] = FieldType::PLAYER_ON_GOAL;
        isPlayerOnGoal_ = true;
        playerPos_.first = x - 1;
        playerPos_.second = y;
        break;
    case FieldType::BOX:
        switch(gameField_[x - 2][y]) {
        case FieldType::EMPTY:
            ++steps;
            gameField_[x - 2][y] = FieldType::BOX;
            gameField_[x - 1][y] = FieldType::PLAYER;
            gameField_[x][y] = ObjAfterMoving();
            playerPos_.first = x - 1;
            playerPos_.second = y;
            break;
        case FieldType::GOAL:
            ++steps;
            gameField_[x - 2][y] = FieldType::BOX_ON_GOAL;
            gameField_[x - 1][y] = FieldType::PLAYER;
            gameField_[x][y] = ObjAfterMoving();
            ++boxOnGoalNum_;
            playerPos_.first = x - 1;
            playerPos_.second = y;
            break;
        }
        break;
    case FieldType::BOX_ON_GOAL:
        switch(gameField_[x - 2][y]) {
        case FieldType::EMPTY:
            ++steps;
            gameField_[x - 2][y] = FieldType::BOX;
            gameField_[x - 1][y] = FieldType::PLAYER_ON_GOAL;
            gameField_[x][y] = ObjAfterMoving();
            --boxOnGoalNum_;
            isPlayerOnGoal_ = true;
            playerPos_.first = x - 1;
            playerPos_.second = y;
            break;
        case FieldType::GOAL:
            ++steps;
            gameField_[x - 2][y] = FieldType::BOX_ON_GOAL;
            gameField_[x - 1][y] = FieldType::PLAYER_ON_GOAL;
            gameField_[x][y] = ObjAfterMoving();
            isPlayerOnGoal_ = true;
            playerPos_.first = x - 1;
            playerPos_.second = y;
            break;
        }
        break;
    }
}


void Level::MoveDown()
{

    unsigned x = playerPos_.first;
    unsigned y = playerPos_.second;

    switch(gameField_[x + 1][y]) {
    case FieldType::EMPTY:
        ++steps;
        gameField_[x][y] = ObjAfterMoving();
        gameField_[x + 1][y] = FieldType::PLAYER;
        playerPos_.first = x + 1;
        playerPos_.second = y;
        break;
    case FieldType::GOAL:
        ++steps;
        gameField_[x][y] = ObjAfterMoving();
        gameField_[x+1][y] = FieldType::PLAYER_ON_GOAL;
        isPlayerOnGoal_ = true;
        playerPos_.first = x + 1;
        playerPos_.second = y;
        break;
    case FieldType::BOX:
        switch(gameField_[x + 2][y]) {
        case FieldType::EMPTY:
            ++steps;
            gameField_[x + 2][y] = FieldType::BOX;
            gameField_[x + 1][y] = FieldType::PLAYER;
            gameField_[x][y] = ObjAfterMoving();
            playerPos_.first = x + 1;
            playerPos_.second = y;
            break;
        case FieldType::GOAL:
            ++steps;
            gameField_[x + 2][y] = FieldType::BOX_ON_GOAL;
            gameField_[x + 1][y] = FieldType::PLAYER;
            gameField_[x][y] = ObjAfterMoving();
            ++boxOnGoalNum_;
            playerPos_.first = x + 1;
            playerPos_.second = y;
            break;
        }
        break;
    case FieldType::BOX_ON_GOAL:
        switch(gameField_[x + 2][y]) {
        case FieldType::EMPTY:
            ++steps;
            gameField_[x + 2][y] = FieldType::BOX;
            gameField_[x + 1][y] = FieldType::PLAYER_ON_GOAL;
            gameField_[x][y] = ObjAfterMoving();
            --boxOnGoalNum_;
            isPlayerOnGoal_ = true;
            playerPos_.first = x + 1;
            playerPos_.second = y;
            break;
        case FieldType::GOAL:
            ++steps;
            gameField_[x + 2][y] = FieldType::BOX_ON_GOAL;
            gameField_[x + 1][y] = FieldType::PLAYER_ON_GOAL;
            gameField_[x][y] = ObjAfterMoving();
            isPlayerOnGoal_ = true;
            playerPos_.first = x + 1;
            playerPos_.second = y;
            break;
        }
        break;
    }
}

void Level::MoveLeft()
{

    unsigned x = playerPos_.first;
    unsigned y = playerPos_.second;

    switch(gameField_[x][y - 1]) {
    case FieldType::EMPTY:
        ++steps;
        gameField_[x][y] = ObjAfterMoving();
        gameField_[x][y - 1] = FieldType::PLAYER;
        playerPos_.first = x;
        playerPos_.second = y - 1;
        break;
    case FieldType::GOAL:
        ++steps;
        gameField_[x][y] = ObjAfterMoving();
        gameField_[x][y-1] = FieldType::PLAYER_ON_GOAL;
        isPlayerOnGoal_ = true;
        playerPos_.first = x;
        playerPos_.second = y - 1;
        break;
    case FieldType::BOX:
        switch(gameField_[x][y - 2]) {
        case FieldType::EMPTY:
            ++steps;
            gameField_[x][y-2] = FieldType::BOX;
            gameField_[x][y-1] = FieldType::PLAYER;
            gameField_[x][y] = ObjAfterMoving();
            playerPos_.first = x;
            playerPos_.second = y - 1;
            break;
        case FieldType::GOAL:
            ++steps;
            gameField_[x][y-2] = FieldType::BOX_ON_GOAL;
            gameField_[x][y-1] = FieldType::PLAYER;
            gameField_[x][y] = ObjAfterMoving();
            ++boxOnGoalNum_;
            playerPos_.first = x;
            playerPos_.second = y - 1;
            break;
        }
        break;
    case FieldType::BOX_ON_GOAL:
        switch(gameField_[x][y-2]) {
        case FieldType::EMPTY:
            ++steps;
            gameField_[x][y-2] = FieldType::BOX;
            gameField_[x][y-1] = FieldType::PLAYER_ON_GOAL;
            gameField_[x][y] = ObjAfterMoving();
            --boxOnGoalNum_;
            isPlayerOnGoal_ = true;
            playerPos_.first = x;
            playerPos_.second = y - 1;
            break;
        case FieldType::GOAL:
            ++steps;
            gameField_[x][y-2] = FieldType::BOX_ON_GOAL;
            gameField_[x][y-1] = FieldType::PLAYER_ON_GOAL;
            gameField_[x][y] = ObjAfterMoving();
            isPlayerOnGoal_ = true;
            playerPos_.first = x;
            playerPos_.second = y-1;
            break;
        }
        break;
    }
}

void Level::MoveRight()
{

    unsigned x = playerPos_.first;
    unsigned y = playerPos_.second;

    switch(gameField_[x][y + 1]) {
    case FieldType::EMPTY:
        ++steps;
        gameField_[x][y] = ObjAfterMoving();
        gameField_[x][y + 1] = FieldType::PLAYER;
        playerPos_.first = x;
        playerPos_.second = y + 1;
        break;
    case FieldType::GOAL:
        ++steps;
        gameField_[x][y] = ObjAfterMoving();
        gameField_[x][y+1] = FieldType::PLAYER_ON_GOAL;
        isPlayerOnGoal_ = true;
        playerPos_.first = x;
        playerPos_.second = y + 1;
        break;
    case FieldType::BOX:
        switch(gameField_[x][y + 2]) {
        case FieldType::EMPTY:
            ++steps;
            gameField_[x][y+2] = FieldType::BOX;
            gameField_[x][y+1] = FieldType::PLAYER;
            gameField_[x][y] = ObjAfterMoving();
            playerPos_.first = x;
            playerPos_.second = y + 1;
            break;
        case FieldType::GOAL:
            ++steps;
            gameField_[x][y+2] = FieldType::BOX_ON_GOAL;
            gameField_[x][y+1] = FieldType::PLAYER;
            gameField_[x][y] = ObjAfterMoving();
            ++boxOnGoalNum_;
            playerPos_.first = x;
            playerPos_.second = y + 1;
            break;
        }
        break;
    case FieldType::BOX_ON_GOAL:
        switch(gameField_[x][y+2]) {
        case FieldType::EMPTY:
            ++steps;
            gameField_[x][y+2] = FieldType::BOX;
            gameField_[x][y+1] = FieldType::PLAYER_ON_GOAL;
            gameField_[x][y] = ObjAfterMoving();
            --boxOnGoalNum_;
            isPlayerOnGoal_ = true;
            playerPos_.first = x;
            playerPos_.second = y + 1;
            break;
        case FieldType::GOAL:
            ++steps;
            gameField_[x][y+2] = FieldType::BOX_ON_GOAL;
            gameField_[x][y+1] = FieldType::PLAYER_ON_GOAL;
            gameField_[x][y] = ObjAfterMoving();
            isPlayerOnGoal_ = true;
            playerPos_.first = x;
            playerPos_.second = y+1;
            break;
        }
        break;
    }
}

void Level::loadSave(QString saveName)
{
    lineNum_ = 0;
    maxColumnNum_= 0;
    goalNum_ = 0;
    boxOnGoalNum_ = 0;

    currentLevel = saveCurrentLevel;
    steps = saveSteps;
    gameField_.clear();
    gameField_.shrink_to_fit();

    QString path = GetSavePath(saveName);
    QFile lvlFile(path);

    if(lvlFile.open(QIODevice::ReadOnly| QIODevice::Text)) {

        QTextStream stream(&lvlFile);
        QString str = stream.readLine();
        lineNum_ = 0;
        while(!str.isNull()){
            std::vector<FieldType> tmpGameField;
            unsigned tmpMaxColumnNum = 0;
            for(size_t j = 0; j < str.size(); ++j) {
                FieldType obj = QCharToFieldTypeConvertion(str[j]);

                IncrementFieldData(obj);
                if(obj == FieldType::PLAYER || obj == FieldType::PLAYER_ON_GOAL) {
                    playerPos_.first = lineNum_;
                    playerPos_.second = j;
                }
                tmpGameField.push_back(obj);
                ++tmpMaxColumnNum;
            }
            gameField_.push_back(tmpGameField);
            if(tmpMaxColumnNum > maxColumnNum_) {
                maxColumnNum_ = tmpMaxColumnNum;
            }

            str = stream.readLine();
            ++lineNum_;
        }

        for(size_t i = 0; i < lineNum_; ++i) {
            while(gameField_[i].size() < maxColumnNum_) {
                gameField_[i].push_back(FieldType::EMPTY);
            }
        }
    }

    lvlFile.close();
}

void Level::loadLevel(QString lvlNum)
{
    lineNum_ = 0;
    maxColumnNum_= 0;
    goalNum_ = 0;
    boxOnGoalNum_ = 0;

    currentLevel = lvlNum;
    steps = 0;
    gameField_.clear();
    gameField_.shrink_to_fit();

    QString path = GetLvlPath(lvlNum);
    QFile lvlFile(path);

    if(lvlFile.open(QIODevice::ReadOnly| QIODevice::Text)) {

        QTextStream stream(&lvlFile);
        QString str = stream.readLine();
        lineNum_ = 0;
        while(!str.isNull()){
            std::vector<FieldType> tmpGameLine;
            unsigned tmpMaxColumnNum = 0;
            for(size_t j = 0; j < str.size(); ++j) {
                FieldType obj = QCharToFieldTypeConvertion(str[j]);

                IncrementFieldData(obj);
                if(obj == FieldType::PLAYER || obj == FieldType::PLAYER_ON_GOAL) {
                    playerPos_.first = lineNum_;
                    playerPos_.second = j;
                }
                tmpGameLine.push_back(obj);
                ++tmpMaxColumnNum;
            }
            gameField_.push_back(tmpGameLine);
            if(tmpMaxColumnNum > maxColumnNum_) {
                maxColumnNum_ = tmpMaxColumnNum;
            }

            str = stream.readLine();
            ++lineNum_;
        }

        for(size_t i = 0; i < lineNum_; ++i) {
            while(gameField_[i].size() < maxColumnNum_) {
                gameField_[i].push_back(FieldType::EMPTY);
            }
        }
    }

    lvlFile.close();
}

void Level::saveGame(QString fileName)
{
    saveCurrentLevel = currentLevel;
    saveSteps = steps;
    QString path = GetSavePath(fileName);
    QFile saveFile(path);

    if(saveFile.open(QIODevice::WriteOnly | QIODevice::Text)) {
        QTextStream s(&saveFile);
        for(auto it1 = gameField_.begin(); it1 != gameField_.end(); ++it1) {
            for(auto it2 = (*it1).begin(); it2 != (*it1).end(); ++it2) {
                s << FieldTypeToQCharConvertion(*it2);
            }
            s << '\n';
        }
    }

    saveFile.close();
}

void Level::saveUserData(const QString& userName)
{
    QDir dir("C:/Users/Pepega/Documents/Qt/PeepoSad3/LeaderboardSaves/");
    QString path = GetUserDataSavePath(QString::number(dir.count()));
    QFile leaderboardFile(path);

    if(leaderboardFile.open(QIODevice::WriteOnly | QFile::Truncate)) {
        QTextStream s(&leaderboardFile);
        int tempSum = 0;
        std::for_each(UserData_.begin(), UserData_.end(), [&tempSum](auto pair){tempSum += pair.first;});
        s << tempSum;
        s << " ";
        tempSum = 0;
        std::for_each(UserData_.begin(), UserData_.end(), [&tempSum](auto pair){tempSum += pair.second;}); // Заменимо на std::acamulate
        s << tempSum;
        s << " ";
        s << userName;
    }

}

void Level::newGame()
{
    InitializeUserData();
    steps = 0;
    loadLevel("1");
}

void Level::restart()
{
    steps = 0;
    loadLevel(currentLevel);
}

const unsigned Level::GetStepsCounter()
{
    return steps;
}

bool Level::CheckWin()
{
    if(boxOnGoalNum_ == goalNum_) {
        UserData_[currentLevel.toInt() - 1].first = 1;
        UserData_[currentLevel.toInt() - 1].second = steps;
    }
    return boxOnGoalNum_ == goalNum_;
}

void Level::InitializeUserData()
{
    UserData_.clear();

    std::pair<unsigned, unsigned> levelData;
    levelData.first = 0;
    levelData.second = 0;
    for(size_t i = 0; i < GetLevelNumb(); ++i) {
        UserData_.push_back(levelData);
    }
}

void Level::IncrementFieldData(const FieldType& obj)
{
    switch(obj) {
    case FieldType::BOX_ON_GOAL:
        ++boxOnGoalNum_;
        ++goalNum_;
        break;
    case FieldType::GOAL:
        ++goalNum_;
        break;
    case FieldType::PLAYER_ON_GOAL:
        isPlayerOnGoal_ = true;
        ++goalNum_;
        break;
    case FieldType::PLAYER:
        isPlayerOnGoal_ = false;
    }
}

const unsigned Level::GetLevelNumb()
{
    QString path = "C:/Users/Pepega/Documents/Qt/PeepoSad3/Levels";
    QDir dir(path);
    dir.setFilter( QDir::AllEntries | QDir::NoDotAndDotDot );
    unsigned levelNumber = dir.count();
    return levelNumber;
}

const std::vector<std::vector<FieldType> > Level::GetGameField() const
{
    return gameField_;
}
