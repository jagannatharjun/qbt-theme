#pragma once

#include <QMainWindow>

class QListWidgetItem;

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class StyleSheetLoader;

class MainWindow : public QMainWindow
{
  Q_OBJECT
    Q_DISABLE_COPY_MOVE(MainWindow);

public:
  MainWindow(QWidget *parent = nullptr);
  ~MainWindow();

private slots:
  void on_applyColors_clicked();

  void on_iconsView_currentItemChanged(QListWidgetItem *, QListWidgetItem *);

  void on_iconsView_loadingChanged();

  void on_showPicture_toggled(bool checked);

  void on_iconsDirCombo_currentIndexChanged(int index);

private:
  Ui::MainWindow *ui;
  std::unique_ptr<StyleSheetLoader> m_styleSheetLoader;
  void setPreview();
};
