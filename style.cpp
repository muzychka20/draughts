#include "style.h"
#include <QString>

Style::Style() {}

QString Style::GetBlackCellStyle() {
  return "QPushButton{"
         "background-color: #b37441;"
         "border:1px solid #b37441;"
         "}";
}

QString Style::GetWhiteCellStyle() {
  return "QPushButton{"
         "    background-color: #dfc192;"
         "    border:1px solid #dfc192;"
         "}";
}

QString Style::GetStyleSaveGame(QPushButton *btn, int cellSize) {
  btn->setIcon(QIcon(":/source/img/save.png"));
  btn->setIconSize(QSize(cellSize / 2, cellSize / 2));
  btn->setMaximumHeight(cellSize - 20);
  return "QPushButton{"
         "    border: 1px solid #00456c;"
         "    border-radius: 10px;"
         "}"
         "QPushButton:hover"
         "{"
         "    background-color: #dad9d9;"
         "}";
}

QString Style::GetStyleClearHistory(QPushButton *btn, int cellSize) {
  btn->setIcon(QIcon(":/source/img/clear.png"));
  btn->setIconSize(QSize(cellSize / 2, cellSize / 2));
  btn->setMaximumHeight(cellSize - 20);
  return "QPushButton{"
         "    border: 1px solid #00456c;"
         "    border-radius: 10px;"
         "}"
         "QPushButton:hover"
         "{"
         "    background-color: #dad9d9;"
         "}";
}

QString Style::GetStyleStandardButton() {
  return "QPushButton{"
         "    border: 1px solid #00456c;"
         "    border-radius: 10px;"
         "}"
         "QPushButton:hover"
         "{"
         "    background-color: #dad9d9;"
         "}";
}
