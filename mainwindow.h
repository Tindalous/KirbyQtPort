#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

#include <QGraphicsView>

#include <QGraphicsPixmapItem>

#include <QTimer>

#include <QKeyEvent>

QT_BEGIN_NAMESPACE
namespace Ui {
class MainWindow;
}
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

public slots:
    void ProcessNewFrame();
    void ProcessInitGame();

private:
    Ui::MainWindow *ui;

    QGraphicsScene* scene;
    QTimer* frameTimer;
    QKeyEvent* keyEvent;

    int inputButtons[4];
    int screenSize = 4;

    int partOfTutorial = 0; //-1 Cuando termina el tutorial
    void advanceTutorial(int input);
    void resizeTutorial();
    void SetWindowItem(QPixmap* pix);

protected:
    void keyPressEvent(QKeyEvent* event) override;
    void keyReleaseEvent(QKeyEvent* event) override;
};
#endif // MAINWINDOW_H
