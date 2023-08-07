#include "changeparameters.h"
#include "board.h"
#include "style.h"
#include "ui_changeparameters.h"

ChangeParameters::ChangeParameters(QWidget *parent)
    : QWidget(parent), ui(new Ui::ChangeParameters) {
  ui->setupUi(this);


  SetInterface();
  connect(changeSizeOfWindow, &QPushButton::clicked, this,
          &ChangeParameters::clickChangeSizeOfWindow);
  connect(changeColorOfWhiteCell, &QPushButton::clicked, this,
          &ChangeParameters::clickChangeColorOfWhiteCell);
  connect(changeColorOfBlackCell, &QPushButton::clicked, this,
          &ChangeParameters::clickChangeColorOfBlackCell);
}

void ChangeParameters::SetInterface() {

  QWidget::setWindowTitle("Preferences");

  this->setMaximumHeight(200);
  this->setMinimumHeight(200);
  this->setMinimumWidth(300);
  this->setMaximumWidth(300);

  mainLayout = new QVBoxLayout(this);
  this->setLayout(mainLayout);

  changeColorOfWhiteCell =
      new QPushButton(tr("Change Color Of White Cell"), this);
  changeColorOfBlackCell =
      new QPushButton(tr("Change Color Of Black Cell"), this);
  changeSizeOfWindow = new QPushButton(tr("Change Size Of Window"), this);

  sliderForSizeOfWindow = new QSlider(Qt::Horizontal, this);
  sliderForSizeOfWindow->setMaximum(15);
  sliderForSizeOfWindow->setMinimum(7);
  sliderForSizeOfWindow->setValue(8);

  changeColorOfWhiteCell->setSizePolicy(QSizePolicy::Preferred,
                                        QSizePolicy::Preferred);
  changeColorOfWhiteCell->setMaximumHeight(60);
  changeColorOfWhiteCell->setStyleSheet(Style::GetStyleStandardButton());

  changeColorOfBlackCell->setSizePolicy(QSizePolicy::Preferred,
                                        QSizePolicy::Preferred);
  changeColorOfBlackCell->setMaximumHeight(60);
  changeColorOfBlackCell->setStyleSheet(Style::GetStyleStandardButton());

  changeSizeOfWindow->setSizePolicy(QSizePolicy::Preferred,
                                    QSizePolicy::Preferred);
  changeSizeOfWindow->setMaximumHeight(60);
  changeSizeOfWindow->setStyleSheet(Style::GetStyleStandardButton());

  mainLayout->addWidget(changeColorOfWhiteCell);
  mainLayout->addWidget(changeColorOfBlackCell);
  mainLayout->addWidget(changeSizeOfWindow);
  mainLayout->addWidget(sliderForSizeOfWindow);
}

ChangeParameters::~ChangeParameters() { delete ui; }

void ChangeParameters::clickChangeSizeOfWindow() {
  emit signalSize(sliderForSizeOfWindow->value());
}

void ChangeParameters::clickChangeColorOfWhiteCell() {
  QColor newColorOfWhiteCell = QColorDialog::getColor("#dfc192");
  emit signalColorOfWhiteCell(newColorOfWhiteCell);
}
void ChangeParameters::clickChangeColorOfBlackCell() {
  QColor newColorOfBlackCell = QColorDialog::getColor("#b37441");
  emit signalColorOfBlackCell(newColorOfBlackCell);
}
