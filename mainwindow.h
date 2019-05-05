#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

#include <QVector>
#include <QGraphicsScene>

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow() override;
    void window_size();
    void initializing_GraphicsScenes();

    bool hit_player();
    bool hit_opponent();
    void shot_opponent();
    void defeat_opponent();

    bool check_all_positions();
    bool check_first_section_of_ship();
    bool check_diagonals();
    bool check_vertical_and_horizontal_position();

    void generation_opponent_ships();
    bool generation_player_ships();

    void print_field();
    void print_grids();
    void print_player_shot();

    void GAME_OVER();

    void update_hit_coords(QPoint p);
    void play_on_PlayerField(QPoint p, QPen pen_ship);
    void play_on_OpponentField(QPoint p, QPen pen_ship);

protected:
    void mousePressEvent(QMouseEvent *e) override;


private:
    QVector <QPoint> shots_partner;
    QVector <QPoint> ships_partner;
    QVector <QPoint> ships_my;
    int hit_x, hit_y;
    int shot_p_x, shot_p_y;
    int count = 0;                                  //Количество твои кораблей(активно при расстановке)
    Ui::MainWindow *ui;
    QGraphicsScene  *scene_partner;                     //Объявляем графическую сцену
    QGraphicsScene  *scene_me;

};

#endif // MAINWINDOW_H
