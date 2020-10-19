#pragma once

#include <QWidget>

namespace Ui {
class QBittorrentPreview;
}

class QBittorrentPreview : public QWidget
{
  Q_OBJECT

public:
  explicit QBittorrentPreview(QWidget *parent = nullptr);
  ~QBittorrentPreview();

private:
  Ui::QBittorrentPreview *ui;
};

