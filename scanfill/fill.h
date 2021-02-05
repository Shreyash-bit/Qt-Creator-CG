#ifndef FILL_H
#define FILL_H
#include <QMainWindow>
#include "qmainwindow.h"
#include "mainwindow.h"
#include "ui_mainwindow.h"

class fill : public MainWindow
{
    Q_OBJECT

public:
    fill(QWidget *parent = nullptr);
    ~fill();
};

#endif // FILL_H
