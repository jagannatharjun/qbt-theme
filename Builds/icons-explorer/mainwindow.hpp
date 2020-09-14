#pragma once

#include <QMainWindow>

class QListWidgetItem;

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
  Q_OBJECT

public:
  MainWindow(QWidget *parent = nullptr);
  ~MainWindow();

private slots:
  void on_new_row_clicked();

  void on_applyColors_clicked();

  void on_iconsView_currentItemChanged(QListWidgetItem *, QListWidgetItem *);

  void on_pushButton_clicked();

  void on_iconsView_loadingChanged();

private:
  Ui::MainWindow *ui;
};
