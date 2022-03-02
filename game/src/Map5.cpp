#include "Map5.h"
#include "WorldManager.h"
#include "Map0.h"
#include "DisplayManager.h"
#include "LogManager.h"

#include <fstream>
#include <sstream>
#include <iomanip>


Map5::Map5(int difficulty, df::Music *p_music) {
	this->difficulty = difficulty;
	this->p_music = p_music;
    start();
}

Map5::~Map5() {

}

void Map5::start() {
    std::fstream myFile;
    myFile.open("../game/easyScoreBoard.txt", std::ios::in);
    if (myFile.is_open()) {
        std::string line;
        int lineCount = 0;
        while (getline(myFile, line)) {
            float score = static_cast<float>(std::stoi(line));
            scoreListEasy[lineCount] = score/10;
            lineCount++;
        }
        myFile.close();
    } else {
        LM.writeLog("Error: Easy scoreboard not found");
    }

    myFile.open("../game/normalScoreBoard.txt", std::ios::in);
    if (myFile.is_open()) {
        std::string line;
        int lineCount = 0;
        while (getline(myFile, line)) {
            float score = static_cast<float>(std::stoi(line));
            scoreListNormal[lineCount] = score/10;
            lineCount++;
        }
        myFile.close();
    } else {
        LM.writeLog("Error: Normal scoreboard not found");
    }

    myFile.open("../game/difficultScoreBoard.txt", std::ios::in);
    if (myFile.is_open()) {
        std::string line;
        int lineCount = 0;
        while (getline(myFile, line)) {
            float score = static_cast<float>(std::stoi(line));
            scoreListDifficult[lineCount] = score/10;
            lineCount++;
        }
        myFile.close();
    } else {
        LM.writeLog("Error: Difficult scoreboard not found");
    }
}

void Map5::stop() {
	WM.markForDelete(WM.getAllObjects());
	new Map0(difficulty);
}

int Map5::draw() {

    DM.drawString(df::Vector(20, 1), "Easy Scoreboard", df::CENTER_JUSTIFIED, df::WHITE);
    DM.drawString(df::Vector(40, 1), "Normal Scoreboard", df::CENTER_JUSTIFIED, df::YELLOW);
    DM.drawString(df::Vector(60, 1), "Difficult Scoreboard", df::CENTER_JUSTIFIED, df::RED);

    for(int i=0;i<3;i++){
        std::stringstream stream;
        stream << std::fixed << std::setprecision(1) << scoreListEasy[i];
        std::string s = stream.str();
        DM.drawString(df::Vector(20, 3+2*i), s+"seconds", df::CENTER_JUSTIFIED, df::WHITE);
    }

    for(int i=0;i<3;i++){
        std::stringstream stream;
        stream << std::fixed << std::setprecision(1) << scoreListNormal[i];
        std::string s = stream.str();
        DM.drawString(df::Vector(40, 3+2*i), s+"seconds", df::CENTER_JUSTIFIED, df::YELLOW);
    }

    for(int i=0;i<3;i++){
        std::stringstream stream;
        stream << std::fixed << std::setprecision(1) << scoreListDifficult[i];
        std::string s = stream.str();
        DM.drawString(df::Vector(60, 3+2*i), s+"seconds", df::CENTER_JUSTIFIED, df::RED);
    }

	return Object::draw();
}
