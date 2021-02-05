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

    void DDALine(int x1, int y1, int x2, int y2, QRgb color);

    void mousePressEvent(QMouseEvent *event);

    void mult(double a[][2], int p[][1]);

    void scale(double sx, double sy, int x[], int y[]);

    void on_scale_clicked();

    void translate(int tx, int ty, int x[], int y[]);

    void on_translate_clicked();

    void rotate(double theta, int x[], int y[]);

    void on_rotate_clicked();

private:
    Ui::MainWindow *ui;
    int ver, scaled_x[20], scaled_y[20], translated_x[20], translated_y[20], rotated_x[20], rotated_y[20], x[20], y[20];
    bool start;

};
#endif // MAINWINDOW_H
