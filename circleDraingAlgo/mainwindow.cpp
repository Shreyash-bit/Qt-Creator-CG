#include "mainwindow.h"
#include "ui_mainwindow.h"
QImage img(400,400,QImage::Format_RGB888);

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
    int xc, yc, r;
    xc = ui->xc->toPlainText().toInt();
    yc = ui->yc->toPlainText().toInt();
    r = ui->r->toPlainText().toInt();
    Bcircle(xc,yc,r);
    ui->label->setPixmap(QPixmap::fromImage(img));

}

void MainWindow::Bcircle(int xc,int yc, int r)
{
    float x = 0;
    float y = r;

    float D = 3 - 2*r;

    while (x <= y)
    {
        img.setPixel( y+xc, x+yc,qRgb(0,255,0));
        img.setPixel( x+xc, y+yc,qRgb(0,255,0));
        img.setPixel(-x+xc, y+yc,qRgb(0,255,0));
        img.setPixel(-y+xc, x+yc,qRgb(0,255,0));
        img.setPixel(-y+xc,-x+yc,qRgb(0,255,0));
        img.setPixel(-x+xc,-y+yc,qRgb(0,255,0));
        img.setPixel( x+xc,-y+yc,qRgb(0,255,0));
        img.setPixel( y+xc,-x+yc,qRgb(0,255,0));

        if(D < 0)
        {
            D += 4*x + 6;
        }
        else
        {
            D += 4*(x - y) + 10;
            y -= 1;
        }
        x += 1;
    }
}

void MainWindow::MIDcircle(int xc, int yc, int r)
{
    float x = r, y = 0;

    img.setPixel(x+xc, y+yc, qRgb(0,0,255));

    if(r > 0)
    {
        img.setPixel( x+xc,-y+yc, qRgb(0,0,255));
        img.setPixel( y+xc, x+yc, qRgb(0,0,255));
        img.setPixel(-y+xc, x+yc, qRgb(0,0,255));
    }

    float P = 1 - r;
    while(x > y)
    {
        y++;

        if(P <= 0)
        {
            P += 2*y + 1;
        }
        else
        {
            x--;
            P += 2*y - 2*x +1;

        }

        if(x < y)
        {
            break;
        }

        img.setPixel( x+xc, y+yc, qRgb(0,0,255));
        img.setPixel(-x+xc, y+yc, qRgb(0,0,255));
        img.setPixel( x+xc,-y+yc, qRgb(0,0,255));
        img.setPixel(-x+xc,-y+yc, qRgb(0,0,255));

        if(x != y)
        {
            img.setPixel( y+xc, x+yc, qRgb(0,0,255));
            img.setPixel(-y+xc, x+yc, qRgb(0,0,255));
            img.setPixel( y+xc,-x+yc, qRgb(0,0,255));
            img.setPixel(-y+xc,-x+yc, qRgb(0,0,255));
        }
    }
}

void MainWindow::on_pushButton_2_clicked()
{
    int xc, yc, r;
    xc = ui->xc_2->toPlainText().toInt();
    yc = ui->yc_2->toPlainText().toInt();
    r = ui->r_2->toPlainText().toInt();
    MIDcircle(xc,yc,r);
    ui->label->setPixmap(QPixmap::fromImage(img));

}
