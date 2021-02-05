#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "cmath"

QImage img(800,800,QImage::Format_RGB888);

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
}

MainWindow::~MainWindow()
{
    delete ui;
}


void MainWindow::on_pushButton_clicked()
{
    float length;
    length = ui->textEdit_2->toPlainText().toInt();

    int level;
    level = ui->textEdit->toPlainText().toInt();

    float x1 = 10, y1 = 250;
    float x5 = 10+length, y5 = 250;

    DrawRecursion(level, x1, y1, x5, y5);

    ui->label->setPixmap(QPixmap::fromImage(img));
}

void MainWindow::display(float x1, float y1, float x2, float y2)
{
    float x, y, dx, dy, xinc, yinc;
    QRgb value;
    value = qRgb(0, 255, 255);

    dx = x2 - x1;
    dy = y2 - y1;

    float steps = abs(dx) > abs(dy) ? abs(dx) : abs(dy);

    xinc = dx/steps;
    yinc = dy/steps;

    x = x1;
    y = y1;

    for(int i=0; i < steps; i++){
        img.setPixel(x,y,value);
        x += xinc;
        y += yinc;
    }
}

void MainWindow::DrawRecursion(int order, float x1, float y1, float x5, float y5)
{
    int dx, dy, x2, y2, x3, y3, x4, y4;

    if (order == 1){
        display(x1, y1, x5, y5);
    }
    else {
        dx = x5 - x1;
        dy = y5 - y1;

        x2 = x1 + dx / 3;
        y2 = y1 + dy / 3;

        x3 = int ((x1 + x5)/2 + (sqrt(3.0) / 6) * (y1 - y5));
        y3 = int ((y1 + y5)/2 + (sqrt(3.0) / 6) * (x5 - x1));

        x4 = x1 + 2*dx / 3;
        y4 = y1 + 2*dy / 3;

        DrawRecursion(order - 1, x1, y1, x2, y2);
        DrawRecursion(order - 1, x2, y2, x3, y3);
        DrawRecursion(order - 1, x3, y3, x4, y4);
        DrawRecursion(order - 1, x4, y4, x5, y5);
    }
}


void MainWindow::on_pushButton_2_clicked()
{
    img.fill(0);
    ui->label->setPixmap(QPixmap::fromImage(img));
}

/*
length /= 3
till length > 5

n = | log length base 3 |
*/
