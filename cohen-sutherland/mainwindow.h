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

private slots:
    void on_pushButton_clicked();
    void mousePressEvent(QMouseEvent *ev);
    void DDA(int x1, int y1, int x2, int y2, QRgb color);
    void outputlabel(int x1, int y1, int x2, int y2, QRgb color);
    int check_region(double x, double y);

private:
    Ui::MainWindow *ui;
    int ver, a[20], b[20];
    int INSIDE=0, LEFT=1, RIGHT=2, BOTTOM=4, TOP=8;
    bool start;
    int wxmin=100, wymin=150, wxmax=350, wymax=450;
};
#endif // MAINWINDOW_H
