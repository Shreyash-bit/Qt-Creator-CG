#include "fill.h"
#include "ui_mainwindow.h"
#include "mainwindow.h"

void MainWindow::on_pushButton_clicked()  //scanfill
{
    int red = ui -> r -> toPlainText().toInt();
    int green = ui -> g -> toPlainText().toInt();
    int blue = ui -> b -> toPlainText().toInt();


    a[ver] = a[0];
    b[ver] = b[0];

    for (int i=0; i < ver; i++)
    {
        dx = a[i+1] - a[i];
        dy = b[i+1] - b[i];

        if(dy == 0.0f) slope[i] = 1.0;
        if(dx == 0.0f) slope[i] = 0.0;
        if((dy != 0.0f) && (dx != 0.0f))
        {
            slope[i] = dx / dy;
        }
    }

    for (int y=0; y < 500; y++)
    {
        k = 0;
        for (i = 0; i < ver; i++)
        {
            if( ((b[i]<=y) && (b[i+1]>y)) || ((b[i]>y) && (b[i+1]<=y)) )
            {
                xi[k] = int( a[i] + ( slope[i] * (y - b[i]) ) );
                k++;
            }
        }
        for (j=0; j < k-1; j++)
        for (i=0; i < k-j-1; i++)
        {
            if(xi[i] > xi[i+1])
            {
                temp = xi[i];
                xi[i] = xi[i+1];
                xi[i+1] = temp;
            }
        }
        for (i=0; i < k; i += 2)
        {
            DDA(xi[i], y, xi[i+1]+1, y, qRgb(red, green, blue));
        }

    }
}

