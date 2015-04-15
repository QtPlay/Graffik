#include "joystickModule.h"
#include "motionController.h"
#include <cmath>
#include <QDebug>

joystickModule::joystickModule(QObject *root, QObject *parent) :
    QObject(parent)
{
    m_pRootItem = root;
    m_maxMotorSpeed = 1;
    connect(m_pRootItem, SIGNAL(joystickMoved(int,int)), this, SLOT(joystickMoved(int,int)));
    connect(m_pRootItem, SIGNAL(sliderMoved(int)), this, SLOT(sliderMoved(int)));
    connect(m_pRootItem, SIGNAL(setStartClicked()), this, SLOT(setStartClicked()));
    connect(m_pRootItem, SIGNAL(setEndClicked()), this, SLOT(setEndClicked()));
    connect(m_pRootItem, SIGNAL(dampingChanged(qreal)), this, SLOT(dampingChanged(qreal)));
    connect(m_pRootItem, SIGNAL(maxJoystickSpeedChanged(qreal)), this, SLOT(maxJoystickSpeedChanged(qreal)));
}

void joystickModule::joystickMoved(int x, int y) {
    const float joystickRange = 64;
    unsigned maxSpeed = 4250 * m_maxMotorSpeed + 750;

    float speedX = (x / joystickRange) * maxSpeed;
    float speedY = (y / joystickRange) * maxSpeed;

    speedX = std::min(speedX, (float)maxSpeed);
    speedY = std::min(speedY, (float)maxSpeed);

    if(!controller.joystickMode()) {
        controller.setJoystickMode(true);
        controller.setWatchdogEnable(true);
    }

    controller.setContinuousSpeed(2, speedX);
    controller.setContinuousSpeed(3, speedY);

    if(qAbs(speedX) < 3 && qAbs(speedY) < 3)
        controller.setJoystickMode(false);
}

void joystickModule::sliderMoved(int x) {
    const float sliderRange = 128;
    unsigned maxSpeed = 4250 * m_maxMotorSpeed + 750;

    float speedX = (x / sliderRange) * maxSpeed;
    speedX = std::min(speedX, (float)maxSpeed);

    if(!controller.joystickMode()) {
        controller.setJoystickMode(true);
        controller.setWatchdogEnable(true);
    }

    controller.setContinuousSpeed(1, speedX);

    if(qAbs(speedX) < 3)
        controller.setJoystickMode(false);
}

void joystickModule::setStartClicked() {
    controller.setProgramStartPoint();
}

void joystickModule::setEndClicked() {
    controller.setProgramStopPoint();
}

void joystickModule::maxJoystickSpeedChanged(qreal pos) {
    m_maxMotorSpeed = pos;
}

void joystickModule::dampingChanged(qreal pos) {
    unsigned value = 29000.0 * pos + 1000;
    for(int i = 1; i <= 3; ++i)
        controller.setMotorAcceleration((unsigned char)i, (float)value);
}
