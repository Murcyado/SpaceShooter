#ifndef CSPACESHOOTER_H
#define CSPACESHOOTER_H

#include "components.h"

#include <QPointer>
#include <QGraphicsView>
#include <QKeyEvent>
#include <QTimer>

class CSpaceShooter : public QGraphicsView
{
    Q_OBJECT
public:
    CSpaceShooter(QSize oScreenSize, QWidget* pParent = nullptr);

    void Run();
    void CheckPoints();

protected:
    void keyPressEvent(QKeyEvent* pEvent) override;

public slots:
    void onCreateEnemy();
    void onIncreaseScore();
    void onDecreaseScore();
    void onDecreaseHealth();
    void onGameOver();

private:
    CCannon* m_pCannon = nullptr;
    CPoints* m_pPoints = nullptr;
    QSize m_oScreenSize;
};

#endif // CSPACESHOOTER_H
