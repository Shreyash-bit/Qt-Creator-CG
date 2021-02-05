#include "transformations.h"
#include "ui_transformations.h"
#include "cmath"
#include "QMouseEvent"
#include "matrix.h"

QImage img(1000, 600, QImage::Format_RGB888);

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    ver = 0;
    start = true;
    DDALine(0, 300, 0, -300, qRgb(255, 0, 0));
    DDALine(-500, 0, 500, 0, qRgb(255, 0, 0));
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::mousePressEvent(QMouseEvent *event)
{
    if(start)
    {
        if(event -> button() == Qt :: RightButton)
        {
            DDALine(x[0], y[0], x[ver - 1], y[ver - 1], qRgb(255, 255, 255));

            start = false;
        } else
        {
            int p = event -> pos().x();
            int q = event -> pos().y();
            x[ver] = p - 500;
            y[ver] = -q + 300;

            if(ver > 0)
            {
                DDALine(x[ver], y[ver], x[ver - 1], y[ver - 1], qRgb(255, 255, 255));
            }
        }
        ver++;
    }
}

void MainWindow::DDALine(int x1, int y1, int x2, int y2, QRgb color)
{
    float dx = x2 - x1;
    float dy = y2 - y1;
    float steps = abs(dx) > abs(dy) ? abs(dx) : abs(dy);

    float xinc = dx / steps;
    float yinc = dy / steps;

    float x = x1;
    float y = y1;

    for(int i = 0; i < steps; i++)
    {
        img.setPixel(500 + x, 300 - y, color);
        x += xinc;
        y += yinc;
    }
    ui->window->setPixmap(QPixmap::fromImage(img));
}

void MainWindow::mult(double a[][2], int p[][1])
{
    int temp[2][1] = {{0}};

    for (int i = 0; i < 2; i++)
        for (int j = 0; j < 1; j++)
            for (int k = 0; k < 2; k++)
                temp[i][j] += (a[i][k] * p[k][j]);

    p[0][0] = temp[0][0];
    p[1][0] = temp[1][0];
}

void MainWindow::scale(double sx, double sy, int x[], int y[])
{

    matrix obj1, obj2, res;
    obj2.m2[0][0] = sx;
    obj2.m2[1][1] = sy;
    obj2.m2[2][2] = 1;

    for(int i = 0; i < ver; i++)
    {
        obj1.m1[i][0] = x[i];
        obj1.m1[i][1] = y[i];
        obj1.m1[i][2] = 1;
    }

    res = obj1 * obj2; // Operator Overloading

    for(int i = 0; i< ver; i++)
    {
        scaled_x[i] = res.m1[i][0];
        scaled_y[i] = res.m1[i][1];
    }

    for(int i = 1; i < ver - 1; i++)
    {
        DDALine(scaled_x[i], scaled_y[i], scaled_x[i - 1], scaled_y[i - 1], qRgb(255, 255, 0));
    }

    DDALine(scaled_x[ver - 2], scaled_y[ver - 2], scaled_x[0], scaled_y[0], qRgb(255, 255, 0));
}

void MainWindow::on_scale_clicked()
{
    int sx = ui->sx->toPlainText().toInt();
    int sy = ui->sy->toPlainText().toInt();
    scale(sx, sy, x, y);
}

void MainWindow::translate(int tx, int ty, int x[], int y[])
{
    matrix obj1, obj2, res;
    obj2.m2[0][0] = 1;
    obj2.m2[1][1] = 1;
    obj2.m2[2][2] = 1;
    obj2.m2[2][0] = tx;
    obj2.m2[2][1] = ty;

    for(int i = 0; i < ver; i++)
    {
        obj1.m1[i][0] = x[i];
        obj1.m1[i][1] = y[i];
        obj1.m1[i][2] = 1;
    }

    res = obj1 * obj2; // Operator Overloading

    for(int i = 0; i< ver; i++)
    {
        translated_x[i] = res.m1[i][0];
        translated_y[i] = res.m1[i][1];
    }

    for(int i = 1; i < ver - 1; i++)
    {
        DDALine(translated_x[i], translated_y[i], translated_x[i - 1], translated_y[i - 1], qRgb(0, 255, 0));
    }

    DDALine(translated_x[ver - 2], translated_y[ver - 2], translated_x[0], translated_y[0], qRgb(0, 255, 0));
}

void MainWindow::on_translate_clicked()
{
    int tx = ui->tx->toPlainText().toInt();
    int ty = ui->ty->toPlainText().toInt();
    translate(tx, ty, x, y);
}

void MainWindow::rotate(double theta, int x[], int y[])
{

    matrix obj1, obj2, res;
    obj2.m2[0][0] = cos(theta);
    obj2.m2[0][1] = -sin(theta);
    obj2.m2[1][0] = sin(theta);
    obj2.m2[1][1] = cos(theta);
    obj2.m2[2][2] = 1;

    for(int i = 0; i < ver; i++)
    {
        obj1.m1[i][0] = x[i];
        obj1.m1[i][1] = y[i];
        obj1.m1[i][2] = 1;
    }

    res = obj1 * obj2; // Operator Overloading

    for(int i = 0; i< ver; i++)
    {
        rotated_x[i] = res.m1[i][0];
        rotated_y[i] = res.m1[i][1];
    }

    for(int i = 1; i < ver - 1; i++)
    {
        DDALine(rotated_x[i], rotated_y[i], rotated_x[i - 1], rotated_y[i - 1], qRgb(0, 255, 255));
    }

    DDALine(rotated_x[ver - 2], rotated_y[ver - 2], rotated_x[0], rotated_y[0], qRgb(0, 255, 255));
}

void MainWindow::on_rotate_clicked()
{
    double theta = ui->theta->toPlainText().toInt() * 3.1416 / 180;
    rotate(theta, x, y);
}


