#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

public slots:
    void on_pushButton_clicked();
    void mousePressEvent(QMouseEvent *ev);    
    void DDA( int x1, int y1, int x2, int y2, QRgb color);

public:
    Ui::MainWindow *ui;
    int ver, a[20], b[20];
    int xi[20], temp, i, j, k;
    float dx, dy, slope[20];
    bool start;
};
#endif // MAINWINDOW_H
