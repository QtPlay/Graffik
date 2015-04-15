#ifndef MOTORSMODULE_H
#define MOTORSMODULE_H

#include <QObject>

struct motion {
    qreal leadIn;
    qreal acceleration;
    qreal deceleration;
    qreal travelTime;

    qreal prevLeadIn;
    qreal prevAcceleration;
    qreal prevDeceleration;
    qreal prevTravelTime;
    quint8 prevMicrostep;

    motion() {
        leadIn = 0;
        acceleration = 0.333333;
        deceleration = 0.99187 - 0.658537;
        travelTime = 0.658537 - 0.333333;

        prevLeadIn = -1;
        prevAcceleration = -1;
        prevDeceleration = -1;
        prevTravelTime = -1;
        prevMicrostep = 0xFF;
    }
};

class motorsModule : public QObject
{
    Q_OBJECT
public:
    explicit motorsModule(QObject *root, QObject *parent = 0);
    motion motorMotion(unsigned char motor) const { return m_motions[motor - 1]; }

private:
    QObject *m_pRootItem;
    QList<motion> m_motions;
    unsigned char m_validatingMotor;

private slots:
    void validateProgram(int motor = -1);
    void powerSaveMode(int motor, bool enable);
    void invertDirection(int motor, bool enable);
    void stepResolution(int motor, int resolution);
    void maxStepRate(int motor, int rate);
    void easingType(int motor, int easing);
    void backlash(int motor, int value);
    void clearClicked(int motor);
    void motionChanged(int motor, qreal p1, qreal p2, qreal p3, qreal p4);
    void validateMotorFinished(const QByteArray &data);
    void validateMotorsFinished(const QByteArray &data);
};

#endif // MOTORSMODULE_H
