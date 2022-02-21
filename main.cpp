#include <QApplication>
#include <QSlider>
#include <QPixmap>
#include <QPainter>
#include <QPaintEvent>
#include <QVBoxLayout>

class ImageCircle : public QWidget {
Q_OBJECT
public:
    ImageCircle() = default;

    ImageCircle(QWidget *parent);

    void paintEvent(QPaintEvent *e) override;

    QSize minimumSizeHint() const override;

public slots:

    void setGreen();

    void setYellow();

    void setRed();

private:
    QPixmap mCurrentImagePixmap;
    QPixmap mImageGreenPixmap;
    QPixmap mImageYellowPixmap;
    QPixmap mImageRedPixmap;
};

ImageCircle::ImageCircle(QWidget *parent) {
    setParent(parent);
    setSizePolicy(QSizePolicy::Fixed, QSizePolicy::Fixed);
    mImageGreenPixmap = QPixmap("src\\green.png");
    mImageYellowPixmap = QPixmap("src\\yellow.png");
    mImageRedPixmap = QPixmap("src\\red.png");
    mCurrentImagePixmap = mImageGreenPixmap;
    setGeometry(mCurrentImagePixmap.rect());
}

void ImageCircle::paintEvent(QPaintEvent *e) {
    QPainter p(this);
    p.drawPixmap(e->rect(), mCurrentImagePixmap);
}

QSize ImageCircle::minimumSizeHint() const {
    return QSize(100, 100);
}

void ImageCircle::setGreen() {
    mCurrentImagePixmap = mImageGreenPixmap;
    update();
}

void ImageCircle::setYellow() {
    mCurrentImagePixmap = mImageYellowPixmap;
    update();
}

void ImageCircle::setRed() {
    mCurrentImagePixmap = mImageRedPixmap;
    update();
}

int main(int argc, char *argv[]) {
    QApplication app(argc, argv);

    QWidget *window = new QWidget;
    auto *layout = new QVBoxLayout(window);
    ImageCircle circle(window);
    circle.setFixedSize(150, 150);

    auto *slider = new QSlider(Qt::Horizontal, window);
    slider->setMinimum(0);
    slider->setMaximum(100);

    QObject::connect(slider, &QSlider::valueChanged, [&slider, &circle](int newValue) {
        if (newValue < 33) {
            circle.setGreen();
        } else if (newValue >= 33 && newValue < 66) {
            circle.setYellow();
        } else if (newValue >= 66) {
            circle.setRed();
        }

    });

    layout->addWidget(&circle);
    layout->addWidget(slider);

    window->setFixedSize(200, 250);
    window->show();
    return app.exec();
}

#include "main.moc"