#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "QMouseEvent"

QImage img1(500, 500, QImage::Format_RGB888);
QImage img2(500, 500, QImage::Format_RGB888);


MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    ver = 0;
    start = true;
    outputlabel(wxmin, wymin, wxmax, wymin,  qRgb(255,255,255));
    outputlabel(wxmin, wymin, wxmin, wymax,  qRgb(255,255,255));
    outputlabel(wxmin, wymax, wxmax, wymax,  qRgb(255,255,255));
    outputlabel(wxmax, wymin, wxmax, wymax,  qRgb(255,255,255));
    DDA(wxmin, wymin, wxmax, wymin,  qRgb(255,255,255));
    DDA(wxmin, wymin, wxmin, wymax,  qRgb(255,255,255));
    DDA(wxmin, wymax, wxmax, wymax,  qRgb(255,255,255));
    DDA(wxmax, wymin, wxmax, wymax,  qRgb(255,255,255));
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
        img1.setPixel(x, y, color);
        x += xinc;
        y += yinc;
    }

    ui->label->setPixmap(QPixmap::fromImage(img1));

}

void MainWindow::outputlabel(int xo1, int yo1, int xo2, int yo2, QRgb color)
{

    float dx = xo2 - xo1;
    float dy = yo2 - yo1;

    float steps = abs(dx) > abs(dy) ? abs(dx) : abs(dy);

    float xinc = dx / steps;
    float yinc = dy / steps;

    float x = xo1;
    float y = yo1;

    for(int i=0; i < steps; i++)
    {
        img2.setPixel(x, y, color);
        x += xinc;
        y += yinc;
    }

    ui->label_2->setPixmap(QPixmap::fromImage(img2));

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
            start = false;
        }

        else
        {
            if(ver % 2 == 1)
            {
                DDA(a[ver], b[ver], a[ver-1], b[ver-1], qRgb(255,255,255));//start = false;
            }

        }
        ver++;
    }
}

int MainWindow::check_region(double x, double y)
{
    int rcode = INSIDE;

    if(x < wxmin) rcode |= LEFT;

    else if(x > wxmax) rcode |= RIGHT;

    if(y < wymin) rcode |= BOTTOM;

    else if(y > wymax) rcode |= TOP;

    return rcode;
}

void MainWindow::on_pushButton_clicked()
{
    for (int i=1;i < ver-1;i++,i++)
    {
        int x1 = a[i];
        int y1 = b[i];
        int x2 = a[i-1];
        int y2 = b[i-1];

        int code1 = check_region(x1, y1);
        int code2 = check_region(x2, y2);

        bool accept = false;

        while(true)
        {
            if((code1 == 0) && (code2 == 0)){
                accept = true;
                break;
            }
            else if(code1 & code2){
                break;
            }

            else
            {
                int code_out;
                double x, y;

                if(code1 != 0) code_out = code1;
                else code_out = code2;

                if(code_out & TOP){
                    x = x1 + (x2 - x1) * (wymax - y1) / (y2 - y1);
                    y = wymax;
                }

                else if(code_out & BOTTOM){
                    x = x1 + (x2 - x1) * (wymin - y1) / (y2 - y1);
                    y = wymin;
                }

                else if (code_out & RIGHT) {
                    y = y1 + (y2 - y1) * (wxmax - x1) / (x2 - x1);
                    x = wxmax;
                }

                else if (code_out & LEFT) {
                    y = y1 + (y2 - y1) * (wxmin - x1) / (x2 - x1);
                    x = wxmin;
                }

                if(code_out == code1){
                    x1 = x;
                    y1 = y;
                    code1 = check_region(x1, y1);
                }

                else{
                    x2 = x;
                    y2 = y;
                    code2 = check_region(x2, y2);
                }
            }

        }
        if(accept){
            outputlabel(x1, y1, x2, y2 , qRgb(0, 255, 0));
        }

    }

}
