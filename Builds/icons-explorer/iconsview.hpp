#pragma once

#include <QListWidget>
#include <QThread>

struct ColorPair {
  QColor oldColor, newColor;
};

struct IconsSet {
  QString dir;
  QVector<QColor> colors;
};

class Worker : public QObject {
  Q_OBJECT
public:
  using QObject::QObject;

public slots:
  void doWork(QVector<ColorPair> colorPairs, QString destDir, QString dir);

signals:
  void newItem(QListWidgetItem *item);
  void completed();
};

class IconsView : public QListWidget {
  Q_OBJECT
public:
  IconsView(QWidget *parent = nullptr);
  ~IconsView();

  QVector<IconsSet> availableIconsSet() const;

  QString iconsDir() const;
  void setIconsDir(const QString &iconsDir);

  QVector<ColorPair> colorPairs() const;
  void setColorPairs(const QVector<ColorPair> &colorPairs);

  QString currentFilePath() const;

  bool loading() const;

signals:
  void loadingChanged();

  // private
  void startLoading(QVector<ColorPair> colorPairs, QString tempPath,
                    QString dir);

private:
  void loadIcons();

  QVector<ColorPair> m_colorPairs;
  QString m_iconsDir;
  QString m_tempPath;
  bool m_loading = false;
  QThread m_workerThread;
};
