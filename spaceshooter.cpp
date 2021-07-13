#include <QApplication>
#include "spaceshooter.h"

CSpaceShooter::CSpaceShooter(QSize oScreenSize, QWidget *pParent) : QGraphicsView(pParent), m_oScreenSize(oScreenSize)
{
    QGraphicsScene* pScene = new QGraphicsScene();
    setScene(pScene);

    pScene->setSceneRect(0, 0, m_oScreenSize.width(), m_oScreenSize.height());

    setBackgroundBrush(QBrush(QImage(":/Resources/SpaceInvadersBg.jpg")));
    setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    setCursor(Qt::PointingHandCursor);
    setStyleSheet("border-style:none");
}

void CSpaceShooter::Run()
{
    scene()->clear();
    setCursor(Qt::BlankCursor);

    m_pCannon = new CCannon(EColor::Red);
    m_pCannon->setPos(m_oScreenSize.width() / 2, m_oScreenSize.height() - gCannonSize.height());
    m_pCannon->setFlag(QGraphicsItem::ItemIsFocusable);
    m_pCannon->setFocus();
    scene()->addItem(m_pCannon);

    connect(m_pCannon, &CCannon::sigIncreaseScore, this, &CSpaceShooter::onIncreaseScore);
    connect(m_pCannon, &CCannon::sigDecreaseScore, this, &CSpaceShooter::onDecreaseScore);

    m_pPoints = new CPoints();
    scene()->addItem(m_pPoints);

    QTimer* pTimer = new QTimer(this);
    connect(pTimer, &QTimer::timeout, this, &CSpaceShooter::onCreateEnemy);
    pTimer->start(2000);
}

void CSpaceShooter::CheckPoints()
{
    if((m_pPoints->GetScore() < 0) || (m_pPoints->GetHealth() <= 0))
    {
        m_pPoints->Reset();
        onGameOver();
    }
}

void CSpaceShooter::keyPressEvent(QKeyEvent *pEvent)
{
    if (m_pCannon == nullptr)
        return;

    switch (pEvent->key())
    {
    case Qt::Key_Left:
        if(m_pCannon->pos().x() >0)
           m_pCannon->setPos(m_pCannon->x() - 20, m_pCannon->y());
        break;

    case Qt::Key_Right:
        if((m_pCannon->pos().x() + gCannonSize.width()) < m_oScreenSize.width())
            m_pCannon->setPos(m_pCannon->x() - 20, m_pCannon->y());
        break;

    case Qt::Key_Z:
    {
        int nColor = static_cast<int>(m_pCannon->GetColor());
        m_pCannon->setColor(static_cast<EColor>(++nColor));
        break;
    }

    case Qt::Key_Space:
        m_pCannon->Shoot();
        break;

    }
}

void CSpaceShooter::onCreateEnemy()
{
    int nPos = 100 + (rand() % m_oScreenSize.width() - 100);
    int nColor = rand() % 3;

    CAlien *pAlien = new CAlien(static_cast<EColor>(nColor));
    pAlien->setPos(nPos, 0);

    scene()->addItem(pAlien);

    connect(pAlien, &CAlien::sigGameOver, this, &CSpaceShooter::onGameOver);
    connect(pAlien, &CAlien::sigDecreaseHealth, this, &CSpaceShooter::onDecreaseHealth);

}

void CSpaceShooter::onIncreaseScore()
{

}

void CSpaceShooter::onDecreaseScore()
{

}

void CSpaceShooter::onDecreaseHealth()
{

}

void CSpaceShooter::onGameOver()
{

}
