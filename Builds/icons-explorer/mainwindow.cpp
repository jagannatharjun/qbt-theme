#include "mainwindow.hpp"
#include "ui_mainwindow.h"

#include <QColorDialog>
#include <QFileDialog>
#include <QLineEdit>
#include <QPainter>
#include <QPixmap>
#include <QFileSystemWatcher>

QByteArray readAll(const QString &filePath);

class StyleSheetLoader
{
public:
    void setStyleSheetFileName(const QString &fileName)
    {
        auto loadStyleSheet = [](const QString &path)
        {
            qDebug("loading style sheet");
            qApp->setStyleSheet("");
            QFile f(path);
            if (!f.open(QIODevice::ReadOnly | QIODevice::Text))
              return;
            qApp->setStyleSheet(f.readAll());

        };

        m_fileSystemWatcher.reset(new QFileSystemWatcher());
        m_fileSystemWatcher->addPath(fileName);

        QObject::connect(m_fileSystemWatcher.get(), &QFileSystemWatcher::fileChanged, qApp, loadStyleSheet);
        loadStyleSheet(fileName);
    }

private:
    std::unique_ptr<QFileSystemWatcher> m_fileSystemWatcher {};
};

class ColorEdit : public QLineEdit {
public:
  ColorEdit(QColor initialColor = {}, bool readOnly = false,
            QWidget *parent = nullptr)
      : QLineEdit(parent), m_colorPixmap(QSize(18, 18)) {
    setTextMargins(20, 1, 1, 1);
    connect(this, &QLineEdit::textChanged, this, [this](const QString text) {
      QColor color(text);
      if (!color.isValid())
        setStyleSheet("color: red");
      else
        setStyleSheet("");

      m_colorPixmap.fill(color);
    });

    setText(initialColor.name());

    if (!readOnly) {
      QAction *colorDiag =
          addAction(QIcon("://color-dropper.png"), QLineEdit::TrailingPosition);
      connect(colorDiag, &QAction::triggered, this, [this](bool) {
        QColor newColor =
            QColorDialog::getColor(QColor(text()), this, "Choose Color");
        if (newColor.isValid())
          setText(newColor.name());
      });
      setReadOnly(readOnly);
    }
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
  for (const auto &iconSet : ui->iconsView->availableIconsSet()) {
    ui->iconsDirCombo->addItem(iconSet.dir,
                               QVariant::fromValue(iconSet.colors));
  }

  auto styleSheetBrowseIcon = ui->stylesheetEdit->addAction(style()->standardIcon(QStyle::SP_DirOpenIcon), QLineEdit::TrailingPosition);
  connect(styleSheetBrowseIcon, &QAction::triggered, this, [this]() {
    const QString styleSheet = QFileDialog::getOpenFileName(this, "Open StyleSheet", {}, "*.qss");
    if (styleSheet.isEmpty())
      return;
    if (!m_styleSheetLoader)
        m_styleSheetLoader = std::make_unique<StyleSheetLoader>();
    m_styleSheetLoader->setStyleSheetFileName(styleSheet);
  });
}

MainWindow::~MainWindow() { delete ui; }

void MainWindow::on_applyColors_clicked() {
  QVector<ColorPair> colorPairs;
  for (int i = 0; i < ui->colorTable->rowCount(); i++) {
    const auto oldColor =
        dynamic_cast<ColorEdit *>(ui->colorTable->cellWidget(i, 1))->color();
    const auto newColor =
        dynamic_cast<ColorEdit *>(ui->colorTable->cellWidget(i, 0))->color();
    if (!oldColor.isValid() || !newColor.isValid())
      continue;
    colorPairs.push_back({newColor, oldColor});
  }
  ui->iconsView->setColorPairs(colorPairs);
}

void MainWindow::on_iconsView_currentItemChanged(QListWidgetItem *,
                                                 QListWidgetItem *) {
  setPreview();
}

void MainWindow::on_iconsView_loadingChanged() {
  bool loading = ui->iconsView->loading();
  ui->folderGroup->setEnabled(!loading);
  ui->colorGroup->setEnabled(!loading);
}

void MainWindow::on_showPicture_toggled(bool checked) { setPreview(); }

void MainWindow::setPreview() {
  const QFileInfo f = ui->iconsView->currentFilePath();
  if (ui->showPicture->isChecked()) {
    ui->contentView->setText(
        QString("<img src=\"%1\" alt='failure' width=128 height=128></img>")
            .arg(QUrl::fromLocalFile(ui->iconsView->currentFilePath())
                     .toString()));
    ui->previewButton->setIcon(QIcon(ui->iconsView->currentFilePath()));
    ui->previewToolButton->setIcon(QIcon(ui->iconsView->currentFilePath()));
  } else {
    ui->contentView->setText(readAll(ui->iconsView->currentFilePath()));
  }
}

void MainWindow::on_iconsDirCombo_currentIndexChanged(int index) {
  ui->iconsView->setIconsDir(ui->iconsDirCombo->currentText());
  const QVector<QColor> colors =
      ui->iconsDirCombo->currentData().value<QVector<QColor>>();

  ui->colorTable->setRowCount(0);
  for (const auto &color : colors) {
    const int row = ui->colorTable->rowCount();
    ui->colorTable->setRowCount(row + 1);
    ui->colorTable->setCellWidget(row, 0, new ColorEdit(color, true, this));
    ui->colorTable->setCellWidget(row, 1, new ColorEdit(QColor{}, false, this));
  }
}
