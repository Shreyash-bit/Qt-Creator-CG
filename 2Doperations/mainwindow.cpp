#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "cmath"

QImage img(500,500,QImage::Format_RGB888);

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    DDA(0, -249, 0, 249);
    DDA(249, 0, -249, 0);
    //DDA(0, 250, 500, 250);
    //DDA(250, 0, 250, 500);
}

MainWindow::~MainWindow()
{
    delete ui;
}


void MainWindow::DDA(int x1, int y1, int x2, int y2)
{
    float dx = x2 - x1;
    float dy = y2 - y1;

    float steps = abs(dx) > abs(dy) ? abs(dx) : abs(dy);

    float xinc = dx / steps;
    float yinc = dy / steps;

    float x = x1;
    float y = y1;

    for (int i = 0; i < steps; i++)
    {
        img.setPixel((x+250),(-y+250),qRgb(0,255,0));
        x += xinc;
        y += yinc;
    }
}

void MainWindow::multiply(float a[2][3], float b[3][3])
{
    float m3[10][10];

    for (int i=0; i < 2; i++)
    {
        for (int j=0; j < 3; j++)
        {
            m3[i][j] = 0;
        }
    }

    for (int i=0; i < 2; i++)
    {
        for (int j=0; j < 3; j++)
        {
            for (int k=0; k < 3; k++)
            {
                m3[i][j] += a[i][k]*b[k][j];
            }
        }
    }

    DDA(m3[0][0],m3[0][1],m3[1][0],m3[1][1]);
    //DDA(m3[0][0]+250,m3[0][1]+250,m3[1][0]+250,m3[1][1]+250);


}

void MainWindow::translate(float tx, float ty, float x1, float y1, float x2, float y2)
{
    float m1[2][3] = {{x1, y1, 1},{x2, y2, 1}};
    float m2[3][3] = {{1, 0, 0},{0, 1, 0},{tx, ty, 1}};
    multiply(m1, m2);
}

void MainWindow::scale(float sx, float sy, float x1, float y1, float x2, float y2)
{
    float m1[2][3] = {{x1, y1, 1},{x2, y2, 1}};
    float m2[3][3] = {{sx, 0, 0},{0, sy, 0},{0, 0, 1}};
    multiply(m1, m2);
}

void MainWindow::rotate(float theta, float x1, float y1, float x2, float y2)
{
    float cs1, sn1, cs2, sn2;
    cs1 = cos(theta);sn1 = -sin(theta);cs2 = cos(theta);sn2 = sin(theta);
    float m1[2][3] = {{x1, y1, 1},{x2, y2, 1}};
    float m2[3][3] = {{cs1, sn1, 0},{sn2, cs2, 0},{0, 0, 1}};
    multiply(m1, m2);
}

void MainWindow::rotateAboutArbitary(float theta, float tx, float ty, float x1, float y1, float x2, float y2)
{
    float m1[3][3] = {{x1, y1, 1},{x2, y2, 1}};
    float m2[3][3] = {{1, 0, 0},{0, 1, 0},{-tx, -ty, 1}};
    float cs1, sn1, cs2, sn2;
    cs1 = cos(theta);sn1 = -sin(theta);cs2 = cos(theta);sn2 = sin(theta);
    float m4[3][3] = {{cs1, sn1, 0},{sn2, cs2, 0},{0, 0, 1}};
    float m5[3][3] = {{1, 0, 0},{0, 1, 0},{tx, ty, 1}};

    float m6[3][3];
    float m7[3][3];

    for (int i=0; i < 3; i++)
    {
        for (int j=0; j < 3; j++)
        {
            m6[i][j] = 0;
        }
    }

    for (int i=0; i < 3; i++)
    {
        for (int j=0; j < 3; j++)
        {
            for (int k=0; k < 3; k++)
            {
                m6[i][j] += m2[i][k]*m4[k][j];
            }
        }
    }

    for (int i=0; i < 3; i++)
    {
        for (int j=0; j < 3; j++)
        {
            m7[i][j] = 0;
        }
    }

    for (int i=0; i < 3; i++)
    {
        for (int j=0; j < 3; j++)
        {
            for (int k=0; k < 3; k++)
            {
                m7[i][j] += m6[i][k]*m5[k][j];
            }
        }
    }

    multiply(m1, m7);

}


void MainWindow::on_pushButton_clicked()
{
    int x1, y1, x2, y2;
    x1 = ui->textEdit->toPlainText().toInt();
    y1 = ui->textEdit_2->toPlainText().toInt();
    x2 = ui->textEdit_3->toPlainText().toInt();
    y2 = ui->textEdit_4->toPlainText().toInt();

    //DDA(x1+250,y1+250,x2+250,y2+250);
    DDA(x1,y1,x2,y2);


    ui->label->setPixmap(QPixmap::fromImage(img));
}

void MainWindow::on_pushButton_2_clicked()
{
    float x1, y1, x2, y2;
    x1 = ui->textEdit->toPlainText().toInt();
    y1 = ui->textEdit_2->toPlainText().toInt();
    x2 = ui->textEdit_3->toPlainText().toInt();
    y2 = ui->textEdit_4->toPlainText().toInt();

    float tx, ty;
    tx = ui->textEdit_5->toPlainText().toInt();
    ty = ui->textEdit_6->toPlainText().toInt();

    translate(tx, ty, x1, y1, x2, y2);

    ui->label->setPixmap(QPixmap::fromImage(img));
}

void MainWindow::on_pushButton_3_clicked()
{
    float x1, y1, x2, y2;
    x1 = ui->textEdit->toPlainText().toInt();
    y1 = ui->textEdit_2->toPlainText().toInt();
    x2 = ui->textEdit_3->toPlainText().toInt();
    y2 = ui->textEdit_4->toPlainText().toInt();

    float sx, sy;
    sx = ui->textEdit_7->toPlainText().toInt();
    sy = ui->textEdit_8->toPlainText().toInt();

    scale(sx, sy, x1, y1, x2, y2);

    ui->label->setPixmap(QPixmap::fromImage(img));
}

void MainWindow::on_pushButton_4_clicked()
{
    float x1, y1, x2, y2;
    x1 = ui->textEdit->toPlainText().toInt();
    y1 = ui->textEdit_2->toPlainText().toInt();
    x2 = ui->textEdit_3->toPlainText().toInt();
    y2 = ui->textEdit_4->toPlainText().toInt();

    float theta;
    float theta_pi;
    theta = ui->textEdit_9->toPlainText().toInt();
    theta_pi = theta*(3.14)/180;

    rotate(theta_pi, x1, y1, x2, y2);

    ui->label->setPixmap(QPixmap::fromImage(img));
}

void MainWindow::on_pushButton_5_clicked()
{
    float x1, y1, x2, y2;
    x1 = ui->textEdit->toPlainText().toInt();
    y1 = ui->textEdit_2->toPlainText().toInt();
    x2 = ui->textEdit_3->toPlainText().toInt();
    y2 = ui->textEdit_4->toPlainText().toInt();

    float px, py;
    px = ui->textEdit_5->toPlainText().toInt();
    py = ui->textEdit_6->toPlainText().toInt();

    float theta;
    theta = ui->textEdit_9->toPlainText().toInt();
    float theta_pi;
    theta_pi = theta*(3.14)/180;

    rotateAboutArbitary(theta_pi, px, py, x1, y1, x2, y2);

    ui->label->setPixmap(QPixmap::fromImage(img));
}
