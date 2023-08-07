#ifndef STYLE_H
#define STYLE_H

#include <QPushButton>

class Style {
public:
  Style();
  static QString GetBlackCellStyle();
  static QString GetWhiteCellStyle();
  static QString GetStyleCloseButton();
  static QString GetStyleLine();
  static QString GetStyleSaveGame(QPushButton *btn, int cellSize);
  static QString GetStyleClearHistory(QPushButton *btn, int cellSize);
  static QString GetStyleStandardButton();
};

#endif // STYLE_H
