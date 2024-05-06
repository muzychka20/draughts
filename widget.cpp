#include "widget.h"
#include "AdditionalFunctions.h"
#include "board.h"
#include "style.h"
#include "ui_widget.h"
#include <QDebug>
#include <QTableView>

Widget::Widget(QWidget *parent) : QWidget(parent), ui(new Ui::Widget) {
  ui->setupUi(this);
  board.FillMap();
  SetInterface();
  FillModel();
  connect(changeParametersButton, &QPushButton::clicked, this,
          &Widget::clickChangeParametersButton);
  connect(saveGameButton, &QPushButton::clicked, this, &Widget::SaveGame);
  connect(clearHistoryOfGameButton, &QPushButton::clicked, this,
          &Widget::clearHistoryOfGame);
  connect(setDrawButton, &QPushButton::clicked, this, &Widget::MessageOfDraw);
  connect(giveUpButton, &QPushButton::clicked, this, &Widget::MessageOfVictory);
}

Widget::~Widget() { delete ui; }

void Widget::SetInterface() {

  QWidget::setWindowTitle("Draughts");

  windowLayout = new QVBoxLayout(this);
  this->setLayout(windowLayout);
  mainLayout = new QBoxLayout(QBoxLayout::LeftToRight);

  windowLayout->addLayout(mainLayout);
  windowLayout->setSpacing(0);

  windowLayout->setContentsMargins(0, 0, 0, 0);

  checkerboardLayout = new QGridLayout(this);
  for (int i = 0; i < board.mapSize; i++) {
    QList<QPushButton *> buttonsOnLine;
    for (int j = 0; j < board.mapSize; j++) {
      button = new QPushButton(this);
      button->setSizePolicy(QSizePolicy::Preferred, QSizePolicy::Preferred);
      button->setStyleSheet(Style::GetWhiteCellStyle());
      if (i % 2) {
        if (!(j % 2)) {
          button->setStyleSheet(Style::GetBlackCellStyle());
          button->setFixedSize(board.cellSize, board.cellSize);
        }
      }
      if (!(i % 2)) {
        if (j % 2) {
          button->setStyleSheet(Style::GetBlackCellStyle());
          button->setFixedSize(board.cellSize, board.cellSize);
        }
      }
      connect(button, &QPushButton::clicked, this, &Widget::Move);
      buttonsOnLine.append(button);
      checkerboardLayout->addWidget(button, i, j);
    }
    board.buttonsOnBoard.push_back(buttonsOnLine);
  }
  checkerboardLayout->setContentsMargins(0, 0, 0, 0);
  checkerboardLayout->setHorizontalSpacing(0);
  checkerboardLayout->setVerticalSpacing(0);
  checkerboardLayout->columnStretch(0);
  checkerboardLayout->rowStretch(0);

  menuLayout = new QBoxLayout(QBoxLayout::TopToBottom);

  navGameLayout = new QBoxLayout(QBoxLayout::TopToBottom);

  currentPlayerLabel = new QLabel(this);
  currentPlayerLabel->setText("Current player: White");
  currentPlayerLabel->setMaximumHeight(20);

  historyEdit = new QTableView(this);
  historyEdit->setSizePolicy(QSizePolicy::Preferred, QSizePolicy::Preferred);

  navButtonsLayout = new QBoxLayout(QBoxLayout::LeftToRight);

  saveGameButton = new QPushButton(tr("Save"), this);
  clearHistoryOfGameButton = new QPushButton(tr("Clear"), this);

  saveGameButton->setSizePolicy(QSizePolicy::Preferred, QSizePolicy::Preferred);
  saveGameButton->setStyleSheet(
      Style::GetStyleSaveGame(saveGameButton, board.cellSize));

  clearHistoryOfGameButton->setSizePolicy(QSizePolicy::Preferred,
                                          QSizePolicy::Preferred);
  clearHistoryOfGameButton->setStyleSheet(
      Style::GetStyleClearHistory(clearHistoryOfGameButton, board.cellSize));

  navButtonsLayout->addWidget(saveGameButton);
  navButtonsLayout->addWidget(clearHistoryOfGameButton);
  navGameLayout->addWidget(currentPlayerLabel);
  navGameLayout->addWidget(historyEdit);

  navGameLayout->addLayout(navButtonsLayout);

  chooseGameLayout = new QBoxLayout(QBoxLayout::TopToBottom);

  giveUpButton = new QPushButton(tr("Give Up"), this);
  setDrawButton = new QPushButton(tr("Draw"), this);
  changeParametersButton = new QPushButton(tr("Preferences"), this);

  giveUpButton->setSizePolicy(QSizePolicy::Preferred, QSizePolicy::Preferred);
  setDrawButton->setSizePolicy(QSizePolicy::Preferred, QSizePolicy::Preferred);
  changeParametersButton->setSizePolicy(QSizePolicy::Preferred,
                                        QSizePolicy::Preferred);

  giveUpButton->setStyleSheet(Style::GetStyleStandardButton());
  setDrawButton->setStyleSheet(Style::GetStyleStandardButton());
  changeParametersButton->setStyleSheet(Style::GetStyleStandardButton());

  chooseGameLayout->addWidget(giveUpButton);
  chooseGameLayout->addWidget(setDrawButton);
  chooseGameLayout->addWidget(changeParametersButton);

  menuLayout->addLayout(navGameLayout, 6);
  menuLayout->addLayout(chooseGameLayout, 2);
  menuLayout->setContentsMargins(10, 10, 10, 10);

  mainLayout->setSpacing(10);
  mainLayout->addLayout(checkerboardLayout, Qt::AlignLeft);
  mainLayout->addLayout(menuLayout, Qt::AlignRight);

  mainLayout->setContentsMargins(0, 0, 0, 0);
  setFixedHeight(board.cellSize * board.mapSize);
  setFixedWidth(board.cellSize * board.mapSize + board.cellSize * 4);
  board.SetFiguresOnBoard();
}

void Widget::slotSize(int value) {
  int Height = 0;
  board.cellSize = value * 10;
  for (int i = 0; i < board.mapSize; i++) {
    for (int j = 0; j < board.mapSize; j++) {
      board.buttonsOnBoard[i][j]->setFixedSize(board.cellSize, board.cellSize);
    }
    Height += board.cellSize;
  }
  setFixedHeight(Height);
  setFixedWidth(Height + board.cellSize * 4);
  board.SetFiguresOnBoard();
}

void Widget::slotColorOfWhiteCell(QColor newColorOfWhiteCell) {
  QString style = "background-color: rgb(%1, %2, %3);"
                  "border: 1px solid rgb(%1, %2, %3);";
  for (int i = 0; i < board.mapSize; i++) {
    for (int j = 0; j < board.mapSize; j++) {
      if (!(i % 2)) {
        if (!(j % 2)) {
          board.buttonsOnBoard[i][j]->setStyleSheet(
              style.arg(newColorOfWhiteCell.red())
                  .arg(newColorOfWhiteCell.green())
                  .arg(newColorOfWhiteCell.blue()));
        }
      }
      if (i % 2) {
        if (j % 2) {
          board.buttonsOnBoard[i][j]->setStyleSheet(
              style.arg(newColorOfWhiteCell.red())
                  .arg(newColorOfWhiteCell.green())
                  .arg(newColorOfWhiteCell.blue()));
        }
      }
    }
  }
}

void Widget::slotColorOfBlackCell(QColor newColorOfBlackCell) {
  QString style = "background-color: rgb(%1, %2, %3);"
                  "border: 1px solid rgb(%1, %2, %3);";
  for (int i = 0; i < board.mapSize; i++) {
    for (int j = 0; j < board.mapSize; j++) {

      if (i % 2) {
        if (!(j % 2)) {
          board.buttonsOnBoard[i][j]->setStyleSheet(
              style.arg(newColorOfBlackCell.red())
                  .arg(newColorOfBlackCell.green())
                  .arg(newColorOfBlackCell.blue()));
        }
      }
      if (!(i % 2)) {
        if (j % 2) {
          board.buttonsOnBoard[i][j]->setStyleSheet(
              style.arg(newColorOfBlackCell.red())
                  .arg(newColorOfBlackCell.green())
                  .arg(newColorOfBlackCell.blue()));
        }
      }
    }
  }
}

void Widget::clickChangeParametersButton() {
  changeParametersForm = new ChangeParameters;
  changeParametersForm->show();
  connect(changeParametersForm, &ChangeParameters::signalSize, this,
          &Widget::slotSize);
  connect(changeParametersForm, &ChangeParameters::signalColorOfWhiteCell, this,
          &Widget::slotColorOfWhiteCell);
  connect(changeParametersForm, &ChangeParameters::signalColorOfBlackCell, this,
          &Widget::slotColorOfBlackCell);
}

void Widget::Move() {
  // QIcon markPossibleMove = QIcon(":/source/img/possibleMove.png");
  QIcon markPossibleMove = QIcon(":/source/img/possibleMove_white.png");
  if (!CheckStrike()) {
    if (CheckAllPossibleMoves()) {
      MessageOfVictory();
      ResetGame();
    }
    // common move
    if (!moveInProcess) {
      QPushButton *startPositionBtn = qobject_cast<QPushButton *>(sender());
      checker.SetStartPostion(startPositionBtn->y() / board.cellSize,
                              startPositionBtn->x() / board.cellSize);
      checker.DefineType(
          board.map[checker.startPositionY][checker.startPositionX]);
      checker.fillPossibleMoves();
      if (checker.getType() == currentPLayer) {
        for (auto move : checker.possibleMoves) {
          int dx = move.second, dy = move.first;
          if (isInBoard(checker.startPositionY + dy,
                        checker.startPositionX + dx, board.mapSize) &&
              !board.map[checker.startPositionY + dy]
                        [checker.startPositionX + dx]) {
            checker.possibleMovesIndex.push_back(
                {checker.startPositionY + dy, checker.startPositionX + dx});
          }
        }
      }
      if (checker.getType() == currentPLayer + 2) {
        for (auto move : checker.possibleMoves) {
          int dx = move.second, dy = move.first, ty = checker.startPositionY,
              tx = checker.startPositionX;
          while (isInBoard(ty + dy, tx + dx, board.mapSize) &&
                 !board.map[ty + dy][tx + dx]) {
            checker.possibleMovesIndex.push_back({ty + dy, tx + dx});
            ty += dy;
            tx += dx;
          }
        }
      }
      if (checker.possibleMovesIndex.size()) {
        if (checker.getType() == currentPLayer) {
          for (auto move : checker.possibleMoves) {
            int dx = move.second, dy = move.first;
            if (isInBoard(checker.startPositionY + dy,
                          checker.startPositionX + dx, board.mapSize) &&
                !board.map[checker.startPositionY + dy]
                          [checker.startPositionX + dx]) {
              board
                  .buttonsOnBoard[checker.startPositionY + dy]
                                 [checker.startPositionX + dx]
                  ->setIcon(markPossibleMove);
            }
          }
        } else if (checker.getType() == currentPLayer + 2) {
          for (auto move : checker.possibleMoves) {
            int dx = move.second, dy = move.first, ty = checker.startPositionY,
                tx = checker.startPositionX;
            while (isInBoard(ty + dy, tx + dx, board.mapSize) &&
                   !board.map[ty + dy][tx + dx]) {
              board.buttonsOnBoard[ty + dy][tx + dx]->setIcon(markPossibleMove);
              ty += dy;
              tx += dx;
            }
          }
        }
        moveInProcess = true;
      }
    } else {
      QPushButton *endPositionBth = qobject_cast<QPushButton *>(sender());
      checker.SetEndPostion(endPositionBth->y() / board.cellSize,
                            endPositionBth->x() / board.cellSize);
      for (auto move : checker.possibleMovesIndex) {
        int i = move.first, j = move.second;
        if (i == checker.endPositionY && j == checker.endPositionX) {
          AddItemToModel("-");
          Swap(board.map, i, j, checker.startPositionY, checker.startPositionX);
          CheckCheckerTurnIntoQueen(i, j);
          TurnMove(&currentPLayer, currentPlayerLabel);
        }
      }
      board.SetFiguresOnBoard();
      moveInProcess = false;
      checker.possibleMovesIndex.clear();
    }
  } else if (!moveInProcess) // strike
  {
    board.SetFiguresOnBoard();
    QPushButton *startPositionBtn = qobject_cast<QPushButton *>(sender());
    if (strikeInProcess) {
      if (SameCell(startPositionBtn->y() / board.cellSize,
                   startPositionBtn->x() / board.cellSize,
                   strikeChecker.endPositionY, strikeChecker.endPositionX)) {
        checker.SetStartPostion(startPositionBtn->y() / board.cellSize,
                                startPositionBtn->x() / board.cellSize);
        if (checker.getType() == currentPLayer) {
          for (auto &strike : checker.strikesForOne) {
            board.buttonsOnBoard[strike.first][strike.second]->setIcon(
                QIcon(markPossibleMove));
          }
        }
        if (checker.getType() == currentPLayer + 2) {
          for (auto &strike : queen.strikesForOne) {
            board.buttonsOnBoard[strike.first][strike.second]->setIcon(
                QIcon(markPossibleMove));
          }
        }
        moveInProcess = true;
      }
    } else {
      checker.SetStartPostion(startPositionBtn->y() / board.cellSize,
                              startPositionBtn->x() / board.cellSize);
      strikeChecker.SetStartPostion(startPositionBtn->y() / board.cellSize,
                                    startPositionBtn->x() / board.cellSize);
      strikeChecker.SetEndPostion(startPositionBtn->y() / board.cellSize,
                                  startPositionBtn->x() / board.cellSize);
      checker.DefineType(
          board.map[checker.startPositionY][checker.startPositionX]);
      checker.strikesForOne.clear();
      if (checker.getType() == currentPLayer) {
        for (int i = 0; i < (int)checker.possibleStrikes.size(); i++) {
          if (checker.possibleStrikes[i][0].first == checker.startPositionY &&
              checker.startPositionX == checker.possibleStrikes[i][0].second) {
            moveInProcess = true;
            for (int j = 1; j < (int)checker.possibleStrikes[i].size(); j++) {
              board
                  .buttonsOnBoard[checker.possibleStrikes[i][j].first]
                                 [checker.possibleStrikes[i][j].second]
                  ->setIcon(QIcon(markPossibleMove));
              checker.strikesForOne.push_back(
                  {checker.possibleStrikes[i][j].first,
                   checker.possibleStrikes[i][j].second});
            }
          }
        }
      } else if (checker.getType() == currentPLayer + 2) {
        for (int i = 0; i < (int)queen.possibleStrikes.size(); i++) {
          if (queen.possibleStrikes[i][0].first == checker.startPositionY &&
              checker.startPositionX == queen.possibleStrikes[i][0].second) {
            moveInProcess = true;
            for (int j = 1; j < (int)queen.possibleStrikes[i].size(); j++) {
              board
                  .buttonsOnBoard[queen.possibleStrikes[i][j].first]
                                 [queen.possibleStrikes[i][j].second]
                  ->setIcon(QIcon(markPossibleMove));
              queen.strikesForOne.push_back(
                  {queen.possibleStrikes[i][j].first,
                   queen.possibleStrikes[i][j].second});
            }
          }
        }
      }
    }
  } else {
    QPushButton *endPositionBtn = qobject_cast<QPushButton *>(sender());
    if (checker.getType() == currentPLayer) {
      if (!NotIn(checker.strikesForOne,
                 {endPositionBtn->y() / board.cellSize,
                  endPositionBtn->x() / board.cellSize})) {
        checker.SetEndPostion(endPositionBtn->y() / board.cellSize,
                              endPositionBtn->x() / board.cellSize);
        for (auto &strike : checker.strikesForOne) {
          int i = strike.first, j = strike.second;
          if (checker.endPositionX == j && checker.endPositionY == i) {
            Swap(board.map, i, j, checker.startPositionY,
                 checker.startPositionX);
            strikeChecker.SetEndPostion(i, j);
            pass.push_back(
                {(i - checker.startPositionY) / 2 + checker.startPositionY,
                 (j - checker.startPositionX) / 2 + checker.startPositionX});
            CheckCheckerTurnIntoQueen(i, j);
            strikeInProcess = true;
            break;
          }
        }
        if (checker.getType() == currentPLayer) {
          if (!checker.CheckContinueStrike(
                  checker.endPositionY, checker.endPositionX, board.mapSize,
                  currentPLayer, board.map, pass, directionsStock.dr)) {
            AddItemToModel(":");
            directionsStock.dr = {0, 0};
            RemoveCheckers(pass, board.map);
            TurnMove(&currentPLayer, currentPlayerLabel);
            strikeInProcess = false;
          }
        } else if (checker.getType() == currentPLayer + 2) {
          if (!queen.CheckContinueStrike(
                  checker.endPositionY, checker.endPositionX, board.mapSize,
                  currentPLayer, board.map, pass, directionsStock.dr)) {
            AddItemToModel(":");
            directionsStock.dr = {0, 0};
            RemoveCheckers(pass, board.map);
            TurnMove(&currentPLayer, currentPlayerLabel);
            strikeInProcess = false;
          }
        }
      }
    } else if (checker.getType() == currentPLayer + 2) {
      if (!NotIn(queen.strikesForOne, {endPositionBtn->y() / board.cellSize,
                                       endPositionBtn->x() / board.cellSize})) {
        checker.SetEndPostion(endPositionBtn->y() / board.cellSize,
                              endPositionBtn->x() / board.cellSize);
        for (auto &strike : queen.strikesForOne) {
          int i = strike.first, j = strike.second;
          if (checker.endPositionX == j && checker.endPositionY == i) {
            Swap(board.map, i, j, checker.startPositionY,
                 checker.startPositionX);
            strikeChecker.SetEndPostion(i, j);
            directionsStock.dr =
                DefinePass(checker.startPositionY, checker.startPositionX,
                           checker.endPositionY, checker.endPositionX);
            strikeInProcess = true;
            break;
          }
        }
        if (!queen.CheckContinueStrike(
                checker.endPositionY, checker.endPositionX, board.mapSize,
                currentPLayer, board.map, pass, directionsStock.dr)) {
          AddItemToModel(":");
          directionsStock.dr = {0, 0};
          RemoveCheckers(pass, board.map);
          TurnMove(&currentPLayer, currentPlayerLabel);
          strikeInProcess = false;
        }
      }
    }
    moveInProcess = false;
    board.SetFiguresOnBoard();
  }
}

bool Widget::CheckAllPossibleMoves() {
  bool is = true;
  Checker ch;
  for (int i = 0; i < (int)board.mapSize; i++) {
    for (int j = 0; j < (int)board.mapSize; j++) {
      if (board.map[i][j] == currentPLayer ||
          board.map[i][j] == currentPLayer + 2) {
        ch.DefineType(board.map[i][j]);
        ch.fillPossibleMoves();
        for (auto m : ch.possibleMoves) {
          int dy = m.first, dx = m.second;
          if (isInBoard(i + dy, j + dx, board.mapSize) &&
              !board.map[i + dy][j + dx]) {
            is = false;
            break;
          }
        }
      }
    }
  }
  return is ? true : false;
}

bool Widget::CheckStrike() {
  if (!strikeInProcess) {
    checker.CheckStrikeFigure(board.mapSize, currentPLayer, board.map);
    queen.CheckStrikeFigure(board.mapSize, currentPLayer, board.map);
  } else {
    checker.CheckContinueStrike(checker.endPositionY, checker.endPositionX,
                                board.mapSize, currentPLayer, board.map, pass,
                                directionsStock.dr);
    queen.CheckContinueStrike(checker.endPositionY, checker.endPositionX,
                              board.mapSize, currentPLayer, board.map, pass,
                              directionsStock.dr);
  }
  if (!checker.possibleStrikes.empty() || !queen.possibleStrikes.empty())
    return true;
  return false;
}

void Widget::CheckCheckerTurnIntoQueen(int row, int column) {
  if (checker.getType() == 1 && row == 0) {
    board.map[row][column] = 3;
    checker.setType(3);
  }
  if (checker.getType() == 2 && row == 7) {
    board.map[row][column] = 4;
    checker.setType(4);
  }
}

std::pair<int, int> Widget::DefinePass(int startI, int startJ, int endI,
                                       int endJ) {
  int i = endI - startI;
  int j = endJ - startJ;
  std::pair<int, int> dr;
  if (i > 0 && j < 0) {
    dr = directionsStock.directions[0];
  } else if (i > 0 && j > 0) {
    dr = directionsStock.directions[1];
  } else if (i < 0 && j < 0) {
    dr = directionsStock.directions[2];
  } else {
    dr = directionsStock.directions[3];
  }
  int ti = startI, tj = startJ;
  while (isInBoard(ti, tj, board.mapSize) && !SameCell(ti, tj, endI, endJ)) {
    if (board.map[ti][tj]) {
      pass.push_back({ti, tj});
      break;
    }
    ti += dr.first;
    tj += dr.second;
  }
  dr.first *= -1;
  dr.second *= -1;
  return dr;
}

void Widget::FillModel() {
  csvModel = new QStandardItemModel(this);
  csvModel->setColumnCount(2);
  csvModel->setHorizontalHeaderLabels(QStringList() << "White"
                                                    << "Black");
  historyEdit->setModel(csvModel);
  historyEdit->horizontalHeader()->setSectionResizeMode(0,
                                                        QHeaderView::Stretch);
  historyEdit->horizontalHeader()->setSectionResizeMode(1,
                                                        QHeaderView::Stretch);
}

void Widget::AddItemToModel(QString bunch) {
  QList<QStandardItem *> standardItemsList;
  QString line;

  if (strikeInProcess) {
    line = board.mapOfSymbols[strikeChecker.startPositionY]
                             [strikeChecker.startPositionX] +
           bunch +
           board.mapOfSymbols[strikeChecker.endPositionY]
                             [strikeChecker.endPositionX];
  } else {
    line = board.mapOfSymbols[checker.startPositionY][checker.startPositionX] +
           bunch +
           board.mapOfSymbols[checker.endPositionY][checker.endPositionX];
  }

  if (currentPLayer == 1) {
    standardItemsList.push_back(new QStandardItem(line));
    csvModel->insertRow(csvModel->rowCount(), standardItemsList);
  } else {
    standardItemsList.push_back(csvModel->takeItem(csvModel->rowCount() - 1));
    standardItemsList.push_back(new QStandardItem(line));
    csvModel->removeRow(csvModel->rowCount() - 1);
    csvModel->appendRow(standardItemsList);
  }
}

void Widget::SaveGame() {
  QFile csvFile = QFileDialog::getSaveFileName(this, "Save a file", ".csv");
  if (csvFile.open(QIODevice::WriteOnly)) {
    QTextStream textStream(&csvFile);
    QStringList stringList;
    stringList << "N";
    stringList << csvModel->horizontalHeaderItem(0)->text();
    stringList << csvModel->horizontalHeaderItem(1)->text();
    textStream << stringList.join(';') + "\n";
    for (int row = 0; row < (int)csvModel->rowCount(); row++) {
      stringList.clear();
      stringList << QString::number(row + 1);
      for (int column = 0; column < (int)csvModel->columnCount(); column++) {
        if (csvModel->item(row, column))
          stringList << csvModel->item(row, column)->text();
      }
      textStream << stringList.join(';') + "\n";
    }
    csvFile.close();
  }
}

void Widget::clearHistoryOfGame() {
  csvModel->clear();
  FillModel();
}

void Widget::ResetGame() {
  board.FillMap();
  board.SetFiguresOnBoard();
  directionsStock.dr = {0, 0};
  currentPLayer = 1;
  currentPlayerLabel->setText("Current player: White");
  checker.possibleStrikes.clear();
  checker.strikesForOne.clear();
  queen.possibleStrikes.clear();
  queen.strikesForOne.clear();
  moveInProcess = false;
  strikeInProcess = false;
  pass.clear();
}

void Widget::MessageOfVictory() {
  QMessageBox msgBox;
  if (currentPLayer == 1)
    msgBox.setText("Black won");
  else
    msgBox.setText("White won");
  msgBox.setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
  msgBox.setStyleSheet("QLabel{min-width: 100px; min-height: 70px}");
  if (msgBox.exec()) {
    ResetGame();
  }
}

void Widget::MessageOfDraw() {
  QMessageBox msgBox;
  msgBox.setText("Draw");
  msgBox.setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
  msgBox.setStyleSheet("QLabel{min-width: 100px; min-height: 70px}");
  if (msgBox.exec()) {
    ResetGame();
  }
}
