//
// Created by yudjin on 12/15/20.
//

#include "FieldCaretaker.h"
#include "Player.h"

#define fileName "Field_snapshot_"

void FieldCaretaker::backUp() {
    this->snapshots_.push_back(this->field->save());
    saveToFile();
}

void FieldCaretaker::undo() {
    if (!this->snapshots_.size()) {
        return;
    }
    Field::Snapshot *state = snapshots_.back();
    //this->snapshots_.pop_back();
    try {
        this->field->restore(state);
    }
    catch (...) {
        this->undo();
    }
}

void FieldCaretaker::history() {
    for (auto x : snapshots_) {
        std::cout << "Field snapshot at mem " << x << '\n';
    }
}

void FieldCaretaker::saveToFile() {
    Field::FieldSerialization state = this->snapshots_.back()->getState();
    try {
        std::string fn = fileName;
        std::string num = std::to_string(snapshots_.size());
        fn += num;
        std::ofstream out(fn, std::ofstream::out | std::ofstream::ate);
        int cnt = 1;
        int playerX = field->player->position.x;
        int playerY = field->player->position.y;
        for (auto it : *field) {
            if (playerX == it.x and playerY == it.y) {
                out << 'p';
            } else if (it.num == state.start)
                out << 's';
            else if (it.num == state.end)
                out << 'e';
            else if (it.is_available == 0) {
                out << "#";
            } else {
                out << int(it.item->isAlive());
            }
            if (cnt++ % (width + wallOffset) == 0) {
                out << "\n";
            }
        }
        out.close();
    }
    catch (std::runtime_error &er) {
        std::cout << "Something went wrong with " << __func__ << ": " << er.what();
    }
}

void FieldCaretaker::initFromFile() {
    Field::FieldSerialization state;
    try {
        std::string fn = fileName;
        int numBackUp = 0;
        std::cout << "Какой снэпшот?\n";
        std::cin >> numBackUp;
        fn += std::to_string(numBackUp);
        std::ifstream in(fn, std::ofstream::in);
        int row = 0;
        std::string line;
        ICreator *coinsFabric = new CoinCreator();
        while (getline(in, line)) {
            for (int i = 0; i < line.size(); i++) {
                field->_cells[row][i].item = coinsFabric->factoryMethod(row, i);
                if (line[i] == '#') {
                    field->makeWall(row, i);
                    field->_cells[row][i].item->setAlive(0);
                } else if (line[i] == '0' || line[i] == '1') {
                    field->_cells[row][i].item->setAlive(line[i]-'0');
                } else if(line[i] == 'p') {
                    field->player->position = {row, i};
                }
            }
            row++;
        }
    }
    catch (std::runtime_error &er) {
        std::cout << "Something went wrong with " << __func__ << ": " << er.what();
    }
//    start = 1, end = 66;
//    startCoords = f->coordsByNum(start);
//    endCoords = f->coordsByNum(end);
//
//    f = Field::GetInstance(start, end);
//
//    // Необходимо проверять, что это не вход и не выход
//    f->makeWall(5);

}
