#ifndef CHANGEPARAMETERS_H
#define CHANGEPARAMETERS_H

#include <QBoxLayout>
#include <QColorDialog>
#include <QFile>
#include <QSlider>

namespace Ui {
class ChangeParameters;
}

class ChangeParameters : public QWidget {
  Q_OBJECT

public:
  explicit ChangeParameters(QWidget *parent = nullptr);
  ~ChangeParameters();

private slots:
  void clickChangeSizeOfWindow();
  void clickChangeColorOfWhiteCell();
  void clickChangeColorOfBlackCell();

private:
  void SetInterface();
  Ui::ChangeParameters *ui;
  QBoxLayout *mainLayout;
  QSlider *sliderForSizeOfWindow;
  QPushButton *changeColorOfWhiteCell;
  QPushButton *changeColorOfBlackCell;
  QPushButton *changeSizeOfWindow;
  std::vector<std::vector<int>> size;

signals:
  void signalSize(int);
  void signalColorOfWhiteCell(QColor);
  void signalColorOfBlackCell(QColor);
};

#endif // CHANGEPARAMETERS_H
