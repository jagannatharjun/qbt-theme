#include "iconsview.hpp"

#include <QApplication>
#include <QDebug>
#include <QDir>
#include <QDirIterator>
#include <QListWidget>
#include <QThreadPool>

#include <filesystem>

std::string tempStr() {
  std::string s;
  const int l = 4 + rand() % 20;
  for (int i = 0; i < l; i++)
    s += 'A' + (rand() % 26);
  return s;
}

std::filesystem::path getTempDir() {
  std::filesystem::path dir;
  do {
    dir = std::filesystem::temp_directory_path() / std::tmpnam(nullptr);
  } while (std::filesystem::exists(dir));
  std::filesystem::create_directory(dir);
  return dir;
}

QByteArray readAll(const QString &filePath) {
  QFile f(filePath);
  if (!f.open(QIODevice::ReadOnly | QIODevice::Text)) {
    qDebug() << "failed to open for readAll()" << filePath;
    return {};
  }
  return f.readAll();
}

void save(const QString &filePath, const QByteArray data) {
  QFile f(filePath);
  if (!f.open(QIODevice::WriteOnly | QIODevice::Text)) {
    qDebug() << "failed to open file for save()" << filePath;
    return;
  }
  f.write(data);
}

void Worker::doWork(QVector<ColorPair> colorPairs, QString destDir,
                    QString dir) {
  if (!dir.isEmpty()) {
    qDebug() << "worker temp path" << destDir;
    std::error_code ec;
    std::filesystem::copy(dir.toStdWString(), destDir.toStdWString(), ec);
    if (ec) {
      qDebug() << "error while copying files" << ec.message().c_str();
    }
  }

  for (const auto &file :
       std::filesystem::recursive_directory_iterator(destDir.toStdWString())) {
    const auto path = file.path();
    if (path.extension() != ".svg" && path.extension() != ".png")
      continue;

    if (path.extension() == ".svg") {
      auto content = readAll(path.string().c_str());
      for (const auto &cp : colorPairs) {
        qDebug() << cp.oldColor.name().toUtf8() << cp.newColor.name().toUtf8();
        content.replace(cp.oldColor.name().toUtf8(),
                        cp.newColor.name().toUtf8());
      }
      save(path.string().c_str(), content);
    }

    QListWidgetItem *item = new QListWidgetItem();
    item->setIcon(QIcon(QPixmap::fromImage(QImage(path.string().c_str()))));
    item->setText(path.filename().string().c_str());
    item->setToolTip(path.string().c_str());
    emit newItem(item);
  }

  emit completed();
}

IconsView::IconsView(QWidget *parent) : QListWidget(parent) {
  qRegisterMetaType<QVector<ColorPair>>("QVector<ColorPair>");

  Worker *worker = new Worker();
  worker->moveToThread(&m_workerThread);
  connect(this, &IconsView::startLoading, worker, &Worker::doWork);
  connect(worker, &Worker::newItem, this,
          [this](QListWidgetItem *item) { addItem(item); });
  connect(worker, &Worker::completed, this, [this]() {
    assert(m_loading);
    m_loading = false;
    emit loadingChanged();
  });
  m_workerThread.start();

  setResizeMode(QListView::Adjust);
  setMovement(QListView::Static);
  setViewMode(QListWidget::ViewMode::IconMode);
  setGridSize(QSize(96, 96));
  setIconsDir(
      R"(C:\Users\Prince\Desktop\Projects\qbt-theme\Builds\icons\nowshed)");
}

IconsView::~IconsView() {
  m_workerThread.quit();
  m_workerThread.wait();

  if (std::filesystem::exists(m_tempPath.toStdWString()))
    std::filesystem::remove_all(m_tempPath.toStdWString());
}

QVector<IconsSet> IconsView::availableIconsSet() const {
  return {
      IconsSet{
          R"(C:\Users\Prince\Desktop\Projects\qbt-theme\Builds\icons\nowshed)",
          {QColor("#f25022"), QColor("#4285f4"), QColor("#6cc24a")}},
      IconsSet{
          R"(C:\Users\Prince\Desktop\Projects\qbt-theme\Builds\icons\originals)",
          {QColor("#427337"), QColor("#375273")}}};
}

QString IconsView::iconsDir() const { return m_iconsDir; }

void IconsView::setIconsDir(const QString &newIconsDir) {
  if (newIconsDir == iconsDir())
    return;

  assert(!m_loading);
  m_iconsDir = newIconsDir;

  loadIcons();
}

void IconsView::loadIcons() {
  m_loading = true;
  clear();

  if (std::filesystem::exists(m_tempPath.toStdWString()))
    std::filesystem::remove_all(m_tempPath.toStdWString());
  m_tempPath = getTempDir().string().c_str();
  std::filesystem::create_directory(m_tempPath.toStdWString());

  emit loadingChanged();
  emit startLoading(m_colorPairs, m_tempPath, m_iconsDir);
}

bool IconsView::loading() const { return m_loading; }

QVector<ColorPair> IconsView::colorPairs() const { return m_colorPairs; }

void IconsView::setColorPairs(const QVector<ColorPair> &colorPairs) {
  m_colorPairs = colorPairs;
  loadIcons();
}

QString IconsView::currentFilePath() const {
  return currentItem() ? currentItem()->toolTip() : QString{};
}
