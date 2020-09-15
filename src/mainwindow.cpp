#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QFileDialog>
#include <QDebug>
#include <QColorDialog>
#include <fstream>
#include <iostream>
#include <QTimer>

#include <zmq.hpp>

MainWindow::MainWindow(QWidget* parent) : QMainWindow(parent), ui(new Ui::MainWindow) {
    ui->setupUi(this);

    QTimer *timer = new QTimer(this);
    connect(timer, &QTimer::timeout, [this]() {
        ui->mainText->appendPlainText("Timer ran out");
    });
    timer->start(1000);

    drape_thread_ = std::make_unique<DrapeThread>();
    drape_thread_->start();
}

MainWindow::~MainWindow() { delete ui; }
