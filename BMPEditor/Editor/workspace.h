#ifndef WORKSPACE_H
#define WORKSPACE_H


#include <QWidget>
#include <QMouseEvent>
#include <QScrollArea>

#include "mouseeventhelper.h"
#include "../Base/image.h"

// defaultni obnovovaci vzdalenost pro pohyb kurzoru pri meritku (100% - 1.0)
#define DEFAULT_MOUSE_HELPER_DIST 5

// minimalni scale projektu nutne pro zobrazeni pixelove mrizky
#define PIXEL_GRID_MIN_SCALE 15

/**
 * @brief Konfiguracn struktura pro workspace
 */
struct Config_Workspace_t {
    QFont font; /** Font pro texty ve workspace (meritka + pozicni informace)*/
    float mouseSensitivity; /** Citlivost mysi */
    int fps; /** Maximalni rychlost vykreslovani*/
};

/**
 * @brief Tato komponenta se stara o spravne vykreslovani (obrazku)
 */
class Workspace : public QWidget
{
    Q_OBJECT
public:
    /**
     * @brief Vytvori instanci workspac widgetu
     * @param parent - Parent widget
     */
    explicit Workspace(const Config_Workspace_t & config, QWidget *parent = nullptr);

    /**
     * @brief Navrati pointer na aktualni obrazek
     * @return
     */
    Image *getImage() const;

    /**
     * @brief Nastavy obrazek, ktery bude zobrazovat/editovan
     * @param newImage - Pointer na obrazek
     */
    void setImage(Image *newImage);

    /**
     * @brief Nastavy vhodnou velikost meritka tak aby projek byl dobre viditelny
     */
    void setDefaultScale();

    /**
     * @brief Nastavy defaultni offest workspaceu
     */
    void setDefaultOffset();

    /**
     * @brief Nastavi nove meritko pro zobrazovani obrazku
     * @param scale - Meritko
     */
    void setScale(float scale);

    /**
     * @brief Zmeni meritko o urcitou hodnotu
     * @param diff - Zmena meritka
     */
    void addScale(float diff);

    /**
     * @brief Priblizi editovany projekt o definovany krok
     */
    void zoomIN();

    /**
     * @brief Oddali editovany projekt o definovany krok
     */
    void zoomOUT();

    /**
     * @brief Navrati meritko
     * @return meritko
     */
    float getScale() const;

    // events
    virtual void mousePressEvent(QMouseEvent *event) override;
    virtual void mouseReleaseEvent(QMouseEvent *event) override;
    virtual void mouseMoveEvent(QMouseEvent *event) override;
    virtual void wheelEvent(QWheelEvent *event) override;

signals:
    /**
     * @brief Signal vyvolan ve chvili zmeny nastroje
     */
    void toolChanged();

    /**
     * @brief Signal vyvolan ve chvili zmeny konfiguracni struktury
     */
    void configChanged();

protected:
    // nastaveni workspace
    Config_Workspace_t config;

    // zobrazovany obrazek
    Image *image;

    // merito zobrazeni
    float scale;

    // globalni offset (pro pohybovani projektem)
    QPointF globalOffset;

    // aktualni pozice kurzoru (pro press a current)
    QPointF pressPos;
    QPointF currentPos;

    // helper pro mouse eventy
    MouseEventHelper mouseHelper;

    /**
     * @brief [[[ Hlavni paint event ]]]
     * @param event - QPaintEvent
     */
    void paintEvent(QPaintEvent *event) override;

private:
    // promena pro casovani
    std::chrono::steady_clock::time_point begin;

    /**
     * @brief Vypocita pozici pro eventy projektu (pozici kurzoru prevede na pozici
     * odpovidajici primo na souradnice v projektu)
     * @param pos - Aktualni pozice kurzoru
     * @param outOfRange - Vystupni parametr (bude nastaven na true pokud kurzor bude mymo kreslici oblast)
     * @return QPoint
     */
    QPointF calculateEventOffsetPosition(const QPointF &pos, bool &outOfRange) const;
};

#endif // WORKSPACE_H
