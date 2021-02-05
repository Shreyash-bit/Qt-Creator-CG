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
    void DDA(int x1, int y1, int x2, int y2);
    void multiply(float[2][3], float[3][3]);
    void translate(float tx, float ty, float x1, float y1, float x2, float y2);
    void scale(float sx, float sy, float x1, float y1, float x2, float y2);
    void rotate(float theta, float x1, float y1, float x2, float y2);
    void rotateAboutArbitary(float theta, float tx, float ty, float x1, float y1, float x2, float y2);

    void on_pushButton_2_clicked();

    void on_pushButton_3_clicked();

    void on_pushButton_4_clicked();

    void on_pushButton_5_clicked();

private:
    Ui::MainWindow *ui;
};
#endif // MAINWINDOW_H
