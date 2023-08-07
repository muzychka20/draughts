#ifndef WIDGET_H
#define WIDGET_H

#include "board.h"
#include "changeParameters.h"
#include "checker.h"
#include "directionsstore.h"
#include "queen.h"
#include <QFileDialog>
#include <QHeaderView>
#include <QLabel>
#include <QMessageBox>
#include <QStandardItemModel>
#include <QTableWidgetItem>

QT_BEGIN_NAMESPACE
namespace Ui {
class Widget;
}
QT_END_NAMESPACE

class Widget : public QWidget {
  Q_OBJECT

public slots:
  void slotSize(int value);
  void slotColorOfWhiteCell(QColor newColorOfWhiteCell);
  void slotColorOfBlackCell(QColor newColorOfBlackCell);

private slots:
  void clickChangeParametersButton();

public:
  Board board;
  Checker checker;
  Checker strikeChecker;
  Queen queen;
  DirectionsStore directionsStock;

  std::pair<int, int> DefinePass(int startI, int startJ, int endI, int endJ);
  std::vector<std::pair<int, int>> pass;

  Widget(QWidget *parent = nullptr);
  ~Widget();

private:
  Ui::Widget *ui;

  int currentPLayer = 1;
  bool moveInProcess = false;
  bool strikeInProcess = false;

  ChangeParameters *changeParametersForm;
  QVBoxLayout *windowLayout;
  QBoxLayout *mainLayout;
  QBoxLayout *menuLayout;
  QBoxLayout *navButtonsLayout;
  QBoxLayout *navGameLayout;
  QBoxLayout *chooseGameLayout;
  QGridLayout *checkerboardLayout;
  QPushButton *button;
  QPushButton *clearHistoryOfGameButton;
  QPushButton *saveGameButton;
  QPushButton *giveUpButton;
  QPushButton *setDrawButton;
  QPushButton *changeParametersButton;
  QTableView *historyEdit;
  QStandardItemModel *csvModel;
  QLabel *currentPlayerLabel;

  void FillModel();
  void AddItemToModel(QString bunch);
  void SaveGame();
  void clearHistoryOfGame();
  void SetInterface();
  void Move();
  bool CheckStrike();
  void CheckCheckerTurnIntoQueen(int row, int column);
  bool CheckAllPossibleMoves();
  void ResetGame();
  void MessageOfDraw();
  void MessageOfVictory();
};
#endif // WIDGET_H
