#ifndef GLWIDGET_H
#define GLWIDGET_H

#include <QGLWidget>
#include <QTimer>
#include <QTime>

class GLWidget : public QGLWidget
{
    Q_OBJECT
public:
    explicit GLWidget(QWidget *parent = 0);

    //void drawRect(GLdouble xRight, GLdouble yTop, GLdouble width, GLdouble height);
    //void drawFilledCircle(GLfloat x, GLfloat y, GLfloat radius);
    //void drawBird();
    //void drawPole();
    void initializeGL();
    void paintGL();
    void resizeGL(int w, int h );

    signals:
        bool outOfBound(double x);

private:
    QTimer timer;
};

#endif // GLWIDGET_H
