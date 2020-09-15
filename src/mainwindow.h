#pragma once

#include <QKeyEvent>
#include <QMainWindow>
#include <QDebug>
#include "drape_thread.h"

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow {
    Q_OBJECT

    public:
        explicit MainWindow(QWidget* parent = nullptr);
        ~MainWindow();

    public slots:
    private:
        Ui::MainWindow* ui;

        std::unique_ptr<DrapeThread> drape_thread_;
};
