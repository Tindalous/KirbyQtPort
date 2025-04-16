#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QDebug>
#include <chrono>

#ifdef __cplusplus
extern "C" {
#endif

    #include "mainOG.h"

#ifdef __cplusplus
}
#endif


QImage* DrawBuffer() {
    QImage* ret = new QImage(128, 64, QImage::Format_RGB32);
    QColor* col = new QColor(0,0,0);
    ret->fill(Qt::gray);
    for (int y = 0; y < 8; y++) {
        for (int x = 0; x < 128; x++) {
            byte temp = getBuffer(x,y);

            byte mask = 0x01;
            for (int y2 = 0; y2 < 8; y2++) {
                if ((temp & mask) != 0) {
                    ret->setPixelColor(x,y*8+y2,*col);
                }
                mask = mask << 1;
            }
        }
    }
    return ret;
}

void MainWindow::keyPressEvent(QKeyEvent* event) {
    switch (event->key()) {
    case 65:
        inputButtons[0] = 1;
        break;
    case 68:
        inputButtons[1] = 1;
        break;
    case 74:
        inputButtons[2] = 1;
        break;
    case 75:
        inputButtons[3] = 1;
        break;
    }


}

void MainWindow::keyReleaseEvent(QKeyEvent* event) {
    switch (event->key()) {
    case 65:
        inputButtons[0] = 0;
        break;
    case 68:
        inputButtons[1] = 0;
        break;
    case 74:
        inputButtons[2] = 0;
        break;
    case 75:
        inputButtons[3] = 0;
        break;
    }
}

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    initFrame();

    scene = new QGraphicsScene(this);
    ui->graphicsView->setScene(scene);
    QPixmap* pix = new QPixmap();
    QImage* rets = DrawBuffer();
    *pix = pix->fromImage(rets->scaledToWidth(128*4));
    scene->addPixmap(*pix);

    frameTimer = new QTimer();
    frameTimer->setInterval(1000);
    frameTimer->start();
    connect(frameTimer,SIGNAL(timeout()),this,SLOT(ProcessInitGame()));

}

void MainWindow::ProcessInitGame() {
    frameTimer->stop();
    initGame();
    frameTimer = new QTimer();
    frameTimer->setInterval(33);
    frameTimer->start();
    connect(frameTimer,SIGNAL(timeout()),this,SLOT(ProcessNewFrame()));
}

void MainWindow::ProcessNewFrame() {
    //auto start = std::chrono::system_clock::now();
    frame(inputButtons[0],inputButtons[1],inputButtons[2],inputButtons[3]);



    QPixmap* pix = new QPixmap();
    QImage* rets = DrawBuffer();
    *pix = pix->fromImage(rets->scaledToWidth(128*4));
    scene->removeItem(scene->items()[0]);
    scene->addPixmap(*pix);

    //auto end = std::chrono::system_clock::now();
    //std::chrono::duration<float,std::milli> duration = end - start;
    //qDebug() << duration.count();

    frameTimer->setInterval(33);
}


MainWindow::~MainWindow()
{
    delete ui;
}
