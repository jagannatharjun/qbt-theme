#include "mainwindow.hpp"
#include "ui_mainwindow.h"

#include <QColorDialog>
#include <QFileDialog>
#include <QLineEdit>
#include <QPainter>
#include <QPixmap>

QByteArray readAll(const QString &filePath);

class ColorEdit : public QLineEdit {
public:
  ColorEdit(QWidget *parent = nullptr)
      : QLineEdit(parent), m_colorPixmap(QSize(18, 18)) {
    setTextMargins(20, 1, 1, 1);
    connect(this, &QLineEdit::textChanged, this, [this](const QString text) {
      QColor color(text);
      if (!color.isValid())
        setStyleSheet("color: red");
      else
        setPalette(QPalette());
      m_colorPixmap.fill(color);
    });

    QAction *colorDiag =
        addAction(QIcon("://color-dropper.png"), QLineEdit::TrailingPosition);
    connect(colorDiag, &QAction::triggered, this, [this](bool) {
      QColor newColor =
          QColorDialog::getColor(QColor(text()), this, "Choose Color");
      if (newColor.isValid())
        setText(newColor.name());
    });
  }

  QColor color() { return QColor(text()); }

private:
  QPixmap m_colorPixmap;

  void paintEvent(QPaintEvent *event) {
    QLineEdit::paintEvent(event);
    if (!m_colorPixmap.isNull()) {
      QPainter painter(this);
      QPixmap pxm = m_colorPixmap;

      painter.drawPixmap(3, (height() - pxm.height()) / 2, pxm);
    }
  }

  void resizeEvent(QResizeEvent *) {
    const int s = qMin(QFontMetrics(font()).height() + 8, height() - 4);
    m_colorPixmap = m_colorPixmap.scaled(s, s);
    setTextMargins(m_colorPixmap.width() + 6, 0, 0, 0);
  }
};

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent), ui(new Ui::MainWindow) {
  ui->setupUi(this);
  on_iconsView_loadingChanged();
  ui->iconsDirEdit->setText(ui->iconsView->iconsDir());
}

MainWindow::~MainWindow() { delete ui; }

void MainWindow::on_new_row_clicked() {
  const int row = ui->colorTable->rowCount();
  ui->colorTable->setRowCount(row + 1);
  ui->colorTable->setCellWidget(row, 0, new ColorEdit(this));
  ui->colorTable->setCellWidget(row, 1, new ColorEdit(this));
}

void MainWindow::on_applyColors_clicked() {
  QVector<ColorPair> colorPairs;
  for (int i = 0; i < ui->colorTable->rowCount(); i++) {
    colorPairs.push_back(
        {dynamic_cast<ColorEdit *>(ui->colorTable->cellWidget(i, 0))->color(),
         dynamic_cast<ColorEdit *>(ui->colorTable->cellWidget(i, 1))->color()});
  }
  ui->iconsView->setColorPairs(colorPairs);
}

void MainWindow::on_iconsView_currentItemChanged(QListWidgetItem *,
                                                 QListWidgetItem *) {
  ui->contentView->setText(readAll(ui->iconsView->currentFilePath()));
}

void MainWindow::on_pushButton_clicked() {
  const QString dir = QFileDialog::getExistingDirectory(
      this, "Browse Icons", ui->iconsView->iconsDir());
  if (!dir.isEmpty()) {
    ui->iconsView->setIconsDir(dir);
    ui->iconsDirEdit->setText(ui->iconsView->iconsDir());
  }
}

void MainWindow::on_iconsView_loadingChanged() {
  bool loading = ui->iconsView->loading();
  ui->folderGroup->setEnabled(!loading);
  ui->colorGroup->setEnabled(!loading);
}
