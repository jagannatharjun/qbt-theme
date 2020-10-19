#include "qbittorrentpreview.hpp"
#include "ui_qbittorrentpreview.h"

QBittorrentPreview::QBittorrentPreview(QWidget *parent) :
                                                          QWidget(parent),
                                                          ui(new Ui::QBittorrentPreview)
{
  ui->setupUi(this);
}

QBittorrentPreview::~QBittorrentPreview()
{
  delete ui;
}
