#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QPainter>
#include <QMouseEvent>

void MainWindow::window_size()
{
    this->resize(1000,640);             //Задаем размеры окна
    this->setFixedSize(1000,640);        //Фиксируем размеры окна
}

void MainWindow::print_field()
{
    QPixmap jpg("D:\\morskoy_boy_2.jpg");                                                 //Установка фона
    jpg = jpg.scaled(this->size(), Qt::IgnoreAspectRatio);
    QPalette palette;
    palette.setBrush(QPalette::Background, jpg);
    this->setPalette(palette);
    ui->label->setStyleSheet("QLabel { background-color : ; color : cyan; }");              //Цвет заголовка
    ui->label_life_ikon1->setStyleSheet("QLabel { background-color : ; color : red; }");
    ui->label_life_ikon2->setStyleSheet("QLabel { background-color : ; color : red; }");
    ui->label_life1->setStyleSheet("QLabel { background-color : ; color : red; }");
    ui->label_life2->setStyleSheet("QLabel { background-color : ; color : red; }");
    ui->graphicsView->setStyleSheet("background-color: rgba(255, 255, 255, 0);");           //Прозрачное поле1
    ui->graphicsView_2->setStyleSheet("background-color: rgba(255, 255, 255, 0);");         //Прозрачное поле2
}

void MainWindow::initializing_GraphicsScenes()
{
    scene_partner = new QGraphicsScene();                                                   //Инициализируем графическую сцену
    scene_me = new QGraphicsScene();

    ui->graphicsView->setScene(scene_partner);                                              //Связываем графическую сцену(scene_partner) с графическим окном(graphicsView)
    ui->graphicsView_2->setScene(scene_me);

    scene_partner->setSceneRect(0, 0, 400,400);                                             //Область графической сцены
    scene_me->setSceneRect(0, 0, 400,400);
}

void MainWindow::print_grids()
{
    QPen pen_fields;                                                                        //Настройка кисти для разлиновки
    pen_fields.setWidth(4);                         //Задаем размер шрифта
    pen_fields.setColor(Qt::darkRed);               //Задаем цвет шрифта

    for(int i = 0; i <= 400; i += 40)                                                                         //Предварительная прорисовка поля (Разлиновка)
    {
        scene_partner->addLine(i,0,i,400,pen_fields);                                       // Аргументы addLine (x0, y0, x, y, 'Настройки кисти')
        scene_partner->addLine(0,i,400,i,pen_fields);
        scene_me->addLine(i,0,i,400,pen_fields);
        scene_me->addLine(0,i,400,i,pen_fields);
    }
}

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    window_size();
    print_field();
    initializing_GraphicsScenes();                                                  //Область графической сцены
    print_grids();
    generation_opponent_ships();                                                              //Генерация поля противника
}

MainWindow::~MainWindow()
{
    delete scene_partner;
    delete scene_me;
    delete ui;
}

void MainWindow::generation_opponent_ships()          //Генерация поля противника
{
    int mass[10][10];
    int massive[20][2];
    int x, y;
    int _x, _y;								//для запоминания значения; воспользуемся, если можно будет поставить корабль
                                            //вернем х и у начальные координаты(они изменяются в switch)
    int dir = 0;							// направление
    int number_of_deck;						//количество палуб
    int number_of_ships;
    int count = 0;							//общее число кораблей
    int row = 0;							//от 0 до 20 строки массива
    for (int i = 0; i < 4; i++)
    {
        number_of_ships = 0;
        number_of_deck = 4 - i;
        while (number_of_ships < (i + 1)) //расставляем корабли
        {
                //начальная позиция
                x = rand() % 10;
                y = rand() % 10;

                _x = x; _y = y;

                dir = rand() % 4;
                int flag = 1;		//для проверки возможности поставить корабль

                for(int j = 0; j < number_of_deck; j++)
                {
                    if((x<0)||(y<0)||(x>=10)||(y>=10)) //высота и ширина окна или поля?  ( x < высота && y < ширина ) ??
                    {
                        //выходит за пределы массива
                        //не можем установить корабль
                        flag = 0;
                        break;
                    }

                    if ((x == 0) || (y == 0) || (x == 9) || (y == 9)) //проверяем для точек на границах (если рассматривать как матрицу)
                    {
                        if (mass[x][y] >= 1) { flag = 0; break; }
                        if ((x == 0) && (y < 9)) { if (mass[x][y] == 1 || mass[x][y - 1] == 1 || mass[x][y + 1] == 1 || mass[x + 1][y + 1] == 1 || mass[x + 1][y] == 1 || mass[x + 1][y - 1] == 1) { flag = 0; break; } }
                        if ((x == 0) && (y < 9)) { if (mass[x][y] == 1 || mass[x][y - 1] == 1 || mass[x][y + 1] == 1 || mass[x + 1][y + 1] == 1 || mass[x + 1][y] == 1 || mass[x + 1][y - 1] == 1) { flag = 0; break; } }
                        if ((y == 0) && (x < 9)) { if (mass[x][y] == 1 || mass[x][y + 1] == 1 || mass[x + 1][y + 1] == 1 || mass[x + 1][y] == 1 || mass[x - 1][y] == 1 || mass[x - 1][y + 1] == 1) { flag = 0; break; } }
                        if ((y == 0) && (x == 0)) { if (mass[x][y] == 1 || mass[x][y + 1] == 1 || mass[x + 1][y + 1] == 1 || mass[x + 1][y] == 1) { flag = 0; break; } }
                        if ((y == 9) && (x == 9)) { if (mass[x][y] == 1 || mass[x][y - 1] == 1 || mass[x - 1][y] == 1 || mass[x - 1][y - 1] == 1) { flag = 0; break; } }
                        if ((y == 9) && (x == 0)) { if (mass[x][y] == 1 || mass[x][y - 1] == 1 || mass[x + 1][y] == 1 || mass[x + 1][y - 1] == 1) { flag = 0; break; } }
                        if ((y == 0) && (x == 9)) { if (mass[x][y] == 1 || mass[x][y + 1] == 1 || mass[x - 1][y] == 1 || mass[x - 1][y - 1] == 1) { flag = 0; break; } }
                        if ((y == 9) && (x < 9) && (x > 0)) { if (mass[x][y] == 1 || mass[x][y - 1] == 1 || mass[x + 1][y] == 1 || mass[x + 1][y - 1] == 1 || mass[x - 1][y] == 1 || mass[x - 1][y - 1] == 1) { flag = 0; break; } }
                        if ((y < 9) && (y > 0) && (x == 9)) { if (mass[x][y] == 1 || mass[x][y - 1] == 1 || mass[x][y + 1] == 1 || mass[x - 1][y] == 1 || mass[x - 1][y + 1] == 1 || mass[x - 1][y - 1] == 1) { flag = 0; break; } }
                    }

                    //если на этом месте и рядом уже есть; проверяем для точек, которые не стоят на границах  //хз, как это написать
                    if((x>0)&&(x<9)&&(y>0)&&(y<9)) { if (mass[x][y] == 1 || mass[x][y - 1] == 1 || mass[x][y + 1] == 1 || mass[x + 1][y + 1] == 1 || mass[x + 1][y] == 1 || mass[x + 1][y - 1] == 1 || mass[x - 1][y] == 1 || mass[x - 1][y + 1] == 1 || mass[x - 1][y - 1] == 1 ) { flag = 0; break; } }

                    switch(dir)
                    {
                        case(0): x++; break;
                        case(1): y++; break;
                        case(2): x--; break;
                        case(3): y--; break;
                    }
                }

                if(flag == 1)	//установка корабля
                {
                    x = _x;
                    y = _y;

                    for(int j = 0; j < number_of_deck; j++)
                    {
                        mass[x][y] = 1;
                        massive[row][0] = { x };
                        massive[row][1] = { y };
                        row++;
                        switch(dir)
                        {
                            case(0): x++; break;
                            case(1): y++; break;
                            case(2): x--; break;
                            case(3): y--; break;
                        }
                    }
                    number_of_ships++;
                    count++;
                }

        }
    }
    for(int i = 0; i < 20; i++)                                  //Отправка координат 4х-палубника в глобальный вектор
        ships_partner.push_back({massive[i][0]+1, massive[i][1]+1});
}

bool MainWindow::check_first_section_of_ship()
{
    if(count == 0 || count == 4 || count == 7 || count == 10 || count == 12 || count == 14 || count > 15)
        return true;
    else
        return false;
}

bool MainWindow::check_all_positions()
{
    for(int i = 0; i < ships_my.size(); i++)
        if((hit_x == ships_my.value(i).rx() && hit_y == ships_my.value(i).ry()) ||
           (hit_x+1 == ships_my.value(i).rx() && hit_y == ships_my.value(i).ry()) ||
           (hit_x-1 == ships_my.value(i).rx() && hit_y == ships_my.value(i).ry()) ||
           (hit_x == ships_my.value(i).rx() && hit_y+1 == ships_my.value(i).ry()) ||
           (hit_x == ships_my.value(i).rx() && hit_y-1 == ships_my.value(i).ry()) ||
           (hit_x+1 == ships_my.value(i).rx() && hit_y+1 == ships_my.value(i).ry()) ||
           (hit_x+1 == ships_my.value(i).rx() && hit_y-1 == ships_my.value(i).ry()) ||
           (hit_x-1 == ships_my.value(i).rx() && hit_y+1 == ships_my.value(i).ry()) ||
           (hit_x-1 == ships_my.value(i).rx() && hit_y-1 == ships_my.value(i).ry()))
            return true;
    return false;
}

bool MainWindow::check_diagonals()
{
    for(int i = 0; i < ships_my.size(); i++)
    {
        if(((hit_x == ships_my.value(i).rx() && hit_y == ships_my.value(i).ry()) ||     //Запрет на точку в точку и диагонали
           (hit_x+1 == ships_my.value(i).rx() && hit_y+1 == ships_my.value(i).ry()) ||
           (hit_x+1 == ships_my.value(i).rx() && hit_y-1 == ships_my.value(i).ry()) ||
           (hit_x-1 == ships_my.value(i).rx() && hit_y+1 == ships_my.value(i).ry()) ||
           (hit_x-1 == ships_my.value(i).rx() && hit_y-1 == ships_my.value(i).ry())))
            return true;
    }
    return false;
}

bool MainWindow::check_vertical_and_horizontal_position()
{
    if((hit_x-1 == ships_my.value(count-1).rx() && hit_y == ships_my.value(count-1).ry()) ||
               (hit_x+1 == ships_my.value(count-1).rx() && hit_y == ships_my.value(count-1).ry()) ||
               (hit_y-1 == ships_my.value(count-1).ry() && hit_x == ships_my.value(count-1).rx()) ||
               (hit_y+1 == ships_my.value(count-1).ry() && hit_x == ships_my.value(count-1).rx()))
                return true;
    else return false;
}

bool MainWindow::generation_player_ships()        //Проверка возможности расстановки
{
    if(check_first_section_of_ship())
        return !check_all_positions();
    else
    {
        if(check_diagonals()) return false;
        return check_vertical_and_horizontal_position();
    }
}

void MainWindow::update_hit_coords(QPoint p)
{
    int coord_x_me = (p.rx()-25)/40, coord_y_me = (p.ry()-115)/40;                          //Исправление погрешности клика
    hit_x = coord_x_me;                                                                     //Присваивание глобальным координатам - координаты клика
    hit_y = coord_y_me;
}

void MainWindow::play_on_PlayerField(QPoint p, QPen pen_ship)                  //Поле игрока (545-943, 155-545)
{
    if(545 <= p.rx() && p.rx() <= 943 && 155 <= p.ry() && p.ry() <= 545 && count < 20 && generation_player_ships() == true)   //Пиксельные размеры поля
    {
        scene_me->addLine(hit_x*40-500, hit_y*40-20, hit_x*40-500, hit_y*40-20, pen_ship);
        ships_my.push_back({hit_x, hit_y});
        ui->label_life2->setText(QVariant(ships_my.size()).toString());
        count++;
    }
}

void MainWindow::print_player_shot()
{
    QPen pen;                                                                                           //Настройка кисти удара
    pen.setWidth(5);
    pen.setColor(Qt::red);
    scene_partner->addLine((hit_x-1)*40,(hit_y-1)*40, hit_x*40, hit_y*40,pen);                  //Прорисовка метки удара
    scene_partner->addLine(hit_x*40,(hit_y-1)*40, (hit_x-1)*40, hit_y*40,pen);
    ui->label_life1->setText(QVariant(ships_partner.size()).toString());
}


void MainWindow::GAME_OVER()
{
    if(ships_partner.size() == 0 || ships_my.size() == 0) exit(0);
}

bool MainWindow::hit_player()                                       //Есть ли корабль под прицелом?
{
    for(int i = 0; i < ships_partner.size(); i++)
        if(hit_x == ships_partner.value(i).rx() && hit_y == ships_partner.value(i).ry())
        {
            ships_partner.remove(i);
            return true;
        }
    return false;
}

void MainWindow::shot_opponent()
{
    QPen pen_ship, pen;                      //Настройка кисти для заголовка и секций кораблей
    pen_ship.setWidth(30);
    pen_ship.setColor(Qt::red);
    pen.setWidth(5);
    pen.setColor(Qt::red);

    while(true)
    {
        shot_p_x = rand() % 10+13;
        shot_p_y = rand() % 10+1;

        if(hit_opponent())                      //Выстрел противника
        {
            scene_me->addLine((shot_p_x-1)*40-480,(shot_p_y-1)*40, shot_p_x*40-480, shot_p_y*40,pen);                  //Прорисовка метки удара
            scene_me->addLine(shot_p_x*40-480,(shot_p_y-1)*40, (shot_p_x-1)*40-480, shot_p_y*40,pen);

            defeat_opponent();                                         //Проверка на попадание противника
            break;
        }
    }
}

bool MainWindow::hit_opponent()
{
    for(int i = 0; i < shots_partner.size(); i++)
    {
        if(shot_p_x == shots_partner.value(i).rx() && shot_p_y == shots_partner.value(i).ry())
            return false;
    }
    shots_partner.push_back({shot_p_x, shot_p_y});
    return true;
}

void MainWindow::defeat_opponent()
{
    QPen pen_ship;                      //Настройка кисти для заголовка и секций кораблей
    pen_ship.setWidth(30);
    pen_ship.setColor(Qt::red);
    for(int i = 0; i < ships_my.size(); i++)
    {
        if(shot_p_x == ships_my.value(i).rx() && shot_p_y == ships_my.value(i).ry())
        {
            ships_my.remove(i);

            scene_me->addLine(shot_p_x*40-500, shot_p_y*40-20, shot_p_x*40-500, shot_p_y*40-20, pen_ship);
            ui->label_life2->setText(QVariant(ships_my.size()).toString());
            shot_opponent();
        }
    }
}

void MainWindow::play_on_OpponentField(QPoint p, QPen pen_ship)                //Поле противника (55-453, 155-545)
{
    if(55 <= p.rx() && p.rx() <= 453 && 155 <= p.ry() && p.ry() <= 545 && count == 20)          //Пиксельные размеры поля
    {
        GAME_OVER();

        if(hit_player())                                                                            //Если есть попадание
            scene_partner->addLine(hit_x*40-20, hit_y*40-20, hit_x*40-20, hit_y*40-20, pen_ship);
        else
            shot_opponent();

        print_player_shot();
    }
}

void MainWindow::mousePressEvent(QMouseEvent *e)
{
    QPoint p = e->pos();                //Возврат координат клика
    update_hit_coords(p);

    QPen pen_ship;                      //Настройка кисти для заголовка и секций кораблей
    pen_ship.setWidth(30);
    pen_ship.setColor(Qt::cyan);

    play_on_PlayerField(p, pen_ship);
    play_on_OpponentField(p, pen_ship);
    update();
}
