#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "QMouseEvent"
#include "fill.h"
QImage img(500, 500, QImage::Format_RGB888);

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    ver = 0;
    start = true;
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::DDA(int x1, int y1, int x2, int y2, QRgb color)
{
    float dx = x2 - x1;
    float dy = y2 - y1;

    float steps = abs(dx) > abs(dy) ? abs(dx) : abs(dy);

    float xinc = dx / steps;
    float yinc = dy / steps;

    float x = x1;
    float y = y1;

    for(int i=0; i < steps; i++)
    {
        img.setPixel(x, y, color);
        x += xinc;
        y += yinc;
    }
    ui->label->setPixmap(QPixmap::fromImage(img));
}

void MainWindow::mousePressEvent(QMouseEvent *ev)
{
    if(start)
    {
        int p = ev->pos().x();
        int q = ev->pos().y();
        a[ver] = p;
        b[ver] = q;

        if(ev->button() == Qt::RightButton)
        {
            DDA(a[ver], b[ver], a[ver-1], b[ver-1], qRgb(255,255,255));
            DDA(a[0], b[0], a[ver], b[ver], qRgb(255,255,255));
            start = false;
        }
        else
        {
            if(ver > 0)
            {
                DDA(a[ver], b[ver], a[ver-1], b[ver-1], qRgb(255,255,255));
            }
        }
        ver++;
    }
}

void on_pushButton_clicked();


