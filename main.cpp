#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include "Map.h" //подключили код с картой
#include "view.h" // подключили код с камерой
#include <sstream>
#include "mission.h"
#include <iostream>

using namespace sf;
using namespace std;


// Класс игрока
class Player {
private:
    float x, y = 0;
public:
    float w, h, dx, dy, speed = 0;
    int dir, plaerScore, health; // новая переменая отвечающая за жизнь
    bool life; // переменая жизнь логическая
    String File;
    Image image;
    Texture texture;
    Sprite sprite;

    Player(String F, float X, float Y, float W, float H) {
        dx = 0;
        dy = 0;
        speed = 0;
        dir = 0;
        plaerScore = 0, health = 100;
        life = true;
        File = F;
        w = W;
        h = H;
        image.loadFromFile("images/" + File);
        image.createMaskFromColor(Color(41, 33, 59));
        texture.loadFromImage(image);
        sprite.setTexture(texture);
        x = X;
        y = Y;
        sprite.setTextureRect(IntRect(0, 0, w, h));
    }

    void update(float time) {
        switch (dir) {
            case 0:
                dx = speed;
                dy = 0;
                break;
            case 1:
                dx = -speed;
                dy = 0;
                break;
            case 2:
                dx = 0;
                dy = speed;
                break;
            case 3:
                dx = 0;
                dy = -speed;
                break;
        }

        x += dx * time;
        y += dy * time;

        speed = 0;
        sprite.setPosition(x, y);
        interactionWitchMap(); // вызываем функцию, отвечающую за взаимодействие с картой ф
        if (health <= 0) { life = false; } // если жизни меньше или равно, то ты умираешь
    }

    float getPlayerCoordinateX() { // этим методом будем забирать координату X
        return x;
    }

    float getPlayerCoordinateY() { // этим методом будем забирать координату Y
        return y;
    }

    void interactionWitchMap() { // функция взаимодейстивия с картой
        for (int i = y / 32; i < (y + h) / 32; i++)//проходимся по тайликам, контактирующим с игроком, то есть по всем квадратикам размера 32*32, которые мы окрашивали в 9 уроке. про условия читайте ниже.
            for (int j = x / 32; j < (x + w) / 32; j++)//икс делим на 32, тем самым получаем левый квадратик, с которым персонаж соприкасается. (он ведь больше размера 32*32, поэтому может одновременно стоять на нескольких квадратах). А j<(x + w) / 32 - условие ограничения координат по иксу. то есть координата самого правого квадрата, который соприкасается с персонажем. таким образом идем в цикле слева направо по иксу, проходя по от левого квадрата (соприкасающегося с героем), до правого квадрата (соприкасающегося с героем)
            {
                if (TileMap[i][j] == '0') {
                    if (dy > 0){
                        y = i * 32 - h;//то стопорим координату игрек персонажа. сначала получаем координату нашего квадратика на карте(стены) и затем вычитаем из высоты сп
                        }// если мы шли вниз,
                    if (dy < 0) {
                        y = i * 32 + 32;
                    }//аналогично с ходьбой вверх. dy<0, значит мы идем вверх (вспоминаем координаты паинта)}
                    if (dx > 0) {
                        x = j * 32 - w;
                    }//если идем вправо, то координата Х равна стена (символ 0) минус ширина персонажа}
                    if (dx < 0) {
                        x = j * 32 + 32;
                    }//аналогично идем влево}
                }

                if (TileMap[i][j] == 's') { //если символ равен 's' (камень)
                    plaerScore++; // если взял камень, то plaerScore увеличивается на 1
                    //x = 700; y = 425; //какое то действие... например телепортация героя
                    TileMap[i][j] = ' '; //убираем камень, типа взяли бонус. можем и не убирать, кстати.
                }
                if (TileMap[i][j] == 'f') {
                    health -= 40; // если вы взяли объект, который наносит урон, то у вас отнимаются 40% жизни
                    TileMap[i][j] = ' '; //если взяли объект, то он исчезает
                }
                if (TileMap[i][j] == 'h') {
                    health += 20; // если вывзяли сердечко, то у вас прибовляется 20% жизни
                    TileMap[i][j] = ' '; //если взяли объект, то он исчезает
                }
            }
    }
};


int main() {
    RenderWindow window(VideoMode(1280, 720), "MyGame_1.4");
    view.reset(FloatRect(0, 0, 1280, 720)); // создане "вида" кмеры при создание вида камеры

    Image map_image; //объект изображения для карты
    map_image.loadFromFile("images/map_top.png"); //загружаем файл для карты
    Texture map; //текстура карты
    map.loadFromImage(map_image); //заряжаем текстуру картинкой
    Sprite s_map; //создаём спрайт для карты
    s_map.setTexture(map); //заливаем текстуру спрайтом

    Image quest_image;
    quest_image.loadFromFile("images/Mission_1.png");
    Texture quest_texture;
    quest_texture.loadFromImage(quest_image);
    Sprite s_quest;
    s_quest.setTexture(quest_texture);
    s_quest.setTextureRect(IntRect(0, 0, 900, 940));  //приведение типов, размеры картинки исходные
    s_quest.setScale(0.7f, 0.7f);//чуть уменьшили картинку, => размер стал меньше


    // делаем hp
    Font fent;
    fent.loadFromFile("MaredivRegular.ttf");
    Text txt("", fent, 25);
    txt.setColor(Color::Red);
    txt.setStyle(Text::Bold);

    //
    Font font;
    font.loadFromFile("MaredivRegular.ttf");
    Text text("", font, 20);
    text.setColor(Color::Green);
    text.setStyle(Text::Bold);

    Font fint;
    font.loadFromFile("MaredivRegular.ttf");
    Text texet("", font, 150);
    texet.setColor(Color::Red);
    texet.setStyle(Text::Bold);

    Font miss;
    miss.loadFromFile("MaredivRegular.ttf");
    Text teext("", font, 25);
    teext.setColor(Color::Red);
    teext.setStyle(Text::Bold);

    Font ft;
    ft.loadFromFile("MaredivRegular.ttf");
    Text tx("", font, 140);
    tx.setColor(Color::Yellow);
    tx.setStyle(Text::Bold);


    Player g("skrimer_P1.jpg", 1920, 1080, 1920, 1080);
    Player p("hero_and_home1.2.png", 700, 425, 96.0, 96.0);

    float CurrentFrame = 0;
    Clock clock;
    Clock gameTimeClock;
    int gameTime = 0;
    bool showMissionText = true;


    while (window.isOpen()) {

        float time = clock.getElapsedTime().asMicroseconds();
        if (p.life) gameTime = gameTimeClock.getElapsedTime().asSeconds(); else { view.move(0.8, 0); }
        clock.restart();
        time = time / 800;


        Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed)
                window.close();

            if (Keyboard::isKeyPressed(Keyboard::Escape)) {
                window.close();
            }

            if (event.type == Event::KeyPressed) // события нажатия клавиши
                if ((event.key.code == Keyboard::Tab)) { // Если зажата кнопка Tab
                    switch (showMissionText) {//переключатель, реагирующий на логическую переменную showMissionText
                        case true: {
                            ostringstream task;//строка текста миссии
                            task << getTextMission(getCurrentMission(p.getPlayerCoordinateX()));//вызывает ся функция getTextMission (она возвращает текст миссии), которая принимает в качестве аргумента функцию getCurrentMission(возвращающую номер миссии), а уже эта ф-ция принимает в качестве аргумента функцию p.getplayercoordinateX() (эта ф-ция возвращает Икс координату игрока)
                            txt.setString( "\n" + task.str());
                            showMissionText = false;//эта строка позволяет убрать все что мы вывели на экране
                            break;//выходим , чтобы не выполнить условие "false" (которое ниже)
                        }
                        case false: {
                            txt.setString("");//если не нажата клавиша таб, то весь этот текст пустой
                            showMissionText = true; //а эта строка позволяет снова нажать клавишу таб и получить вывод на экран
                            break;
                        }
                    }
                }
        }


        if (Keyboard::isKeyPressed(::Keyboard::Escape)) {
            window.close();
        }

        //Управление персонажем с анимацией
        if (p.plaerScore < 10) {
            if (p.life ) {
                if ((Keyboard::isKeyPressed(Keyboard::Left) || (Keyboard::isKeyPressed(Keyboard::A)))) {
                    p.dir = 1;
                    p.speed = 0.1;
                    CurrentFrame += 0.005 * time;
                    if (CurrentFrame > 3) CurrentFrame -= 3;
                    p.sprite.setTextureRect(IntRect(96 * int(CurrentFrame), 96, 96, 96));

                }

                if ((Keyboard::isKeyPressed(Keyboard::Right) || (Keyboard::isKeyPressed(Keyboard::D)))) {
                    p.dir = 0;
                    p.speed = 0.1;
                    CurrentFrame += 0.005 * time;
                    if (CurrentFrame > 3) CurrentFrame -= 3;
                    p.sprite.setTextureRect(IntRect(96 * int(CurrentFrame), 192, 96, 96));

                }

                if ((Keyboard::isKeyPressed(Keyboard::Up) || (Keyboard::isKeyPressed(Keyboard::W)))) {
                    p.dir = 3;
                    p.speed = 0.1;
                    CurrentFrame += 0.005 * time;
                    if (CurrentFrame > 3) CurrentFrame -= 3;
                    p.sprite.setTextureRect(IntRect(96 * int(CurrentFrame), 288, 96, 96));


                }


                if ((Keyboard::isKeyPressed(Keyboard::Down) || (Keyboard::isKeyPressed(Keyboard::S)))) {
                    p.dir = 2;
                    p.speed = 0.1;
                    CurrentFrame += 0.005 * time;
                    if (CurrentFrame > 3) CurrentFrame -= 3;
                    p.sprite.setTextureRect(IntRect(96 * int(CurrentFrame), 0, 96, 96));

                }

            }
        }

        getPlayerCoordinateForView(p.getPlayerCoordinateX(), p.getPlayerCoordinateY()); // передаём функци игрока в функции управления камерой
        p.update(time);
        window.setView(view); // оживляем камеру в окне sfml
        window.clear(Color(128, 106, 89));

        // Рисую карту
        for (int i = 0; i < HEIGHT_MAP; i++)
            for (int j = 0; j < WIDTH_MAP; j++) {

                if (TileMap[i][j] == ' ')s_map.setTextureRect(IntRect(0, 0, 32, 32));  //если встретили символ пробел, то рисуем 1й квадратик
                if (TileMap[i][j] == 's')s_map.setTextureRect(IntRect(31, 0, 32, 32)); //если встретили символ s, то рисуем 2й квадратик
                if (TileMap[i][j] == '0')s_map.setTextureRect(IntRect(64, 0, 32, 32)); //если встретили символ 0, то рисуем 3й квадратик
                if (TileMap[i][j] == 'f') s_map.setTextureRect(IntRect(98, 0, 32, 32)); // объект отвечающий за урон
                if (TileMap[i][j] == 'h')s_map.setTextureRect(IntRect(126, 0, 32, 32)); // объект отвечающий за выстоновление жизни
                s_map.setPosition(j * 32, i * 32); //по сути раскидывает квадратики, превращая в карту. то есть задает каждому из них позицию. если убрать, то вся карта нарисуется в одном квадрате 32*32 и мы увидим один квадрат
                window.draw(s_map); //рисуем квадратики на экран
            }
        // ///////////////////////////// карта работает с миссиями //////////////////////////////////////////////////////
//        if ((getCurrentMission(p.getPlayerCoordinateX())) == 0) { //Если текущая миссия 0, то рисуем карту вот так
//            for (int i = 0; i < HEIGHT_MAP; i++)
//                for (int j = 0; j < WIDTH_MAP; j++)
//                {
//                    if (TileMap[i][j] == ' ')  s_map.setTextureRect(IntRect(0, 0, 32, 32));
//                    if (TileMap[i][j] == 's')  s_map.setTextureRect(IntRect(32, 0, 32, 32));
//                    if ((TileMap[i][j] == '0')) s_map.setTextureRect(IntRect(64, 0, 32, 32));
//                    if ((TileMap[i][j] == 'f')) s_map.setTextureRect(IntRect(96, 0, 32, 32));
//                    if ((TileMap[i][j] == 'h')) s_map.setTextureRect(IntRect(128, 0, 32, 32));
//                    s_map.setPosition(j * 32, i * 32);
//
//                    window.draw(s_map);
//                }
//        }
//
//        if ((getCurrentMission(p.getPlayerCoordinateX())) >= 1) { //Если текущая миссия 1, то рисуем карту вот так
//            for (int i = 0; i < HEIGHT_MAP; i++)
//                for (int j = 0; j < WIDTH_MAP; j++)
//                {
//                    if (TileMap[i][j] == ' ')  s_map.setTextureRect(IntRect(64, 0, 32, 32));//для примера поменял местами вывод спрайта для этого символа и..
//                    if (TileMap[i][j] == 's')  s_map.setTextureRect(IntRect(32, 0, 32, 32));
//                    if ((TileMap[i][j] == '0')) s_map.setTextureRect(IntRect(0, 0, 32, 32));//и для вот этого. логически-игровой смысл их остался таким же
//                    if ((TileMap[i][j] == 'f')) s_map.setTextureRect(IntRect(96, 0, 32, 32));
//                    if ((TileMap[i][j] == 'h')) s_map.setTextureRect(IntRect(128, 0, 32, 32));
//                    s_map.setPosition(j * 32, i * 32);
//
//                    window.draw(s_map);
//
//               }
//        }


        if (!showMissionText) {
            txt.setPosition(view.getCenter().x + 300, view.getCenter().y - 50);//позиция всего этого текстового блока
            s_quest.setPosition(view.getCenter().x + 78, view.getCenter().y - 220);//позиция фона для блока
            window.draw(s_quest); window.draw(txt); //рисуем спрайт свитка (фон для текста миссии). а затем и текст. все это завязано на логическую переменную, которая меняет свое состояние от нажатия клавиши ТАБ
        }


        ostringstream playerHealthString, gameTimeString;
        playerHealthString << p.health;
        gameTimeString << gameTime;
        teext.setString("Health: " + playerHealthString.str() + "\nGames time: " + gameTimeString.str());
        teext.setPosition(view.getCenter().x - 570, view.getCenter().y - 300);
        window.draw(teext);

        ostringstream plaerScoreString; // объевляем переменую
        plaerScoreString << p.plaerScore; // занесли в неё число очков, то есть формулируем строку
        text.setString("Stones collected: " + plaerScoreString.str()); // задаём строку тексту
        text.setPosition(view.getCenter().x - 570, view.getCenter().y - 325); // задаём позицию в центор карты
        window.draw(text); // рисуем этот текст



        if (p.plaerScore == 10) {
            tx.setString("You Winner");
            tx.setPosition(view.getCenter().x - 350, view.getCenter().y - 200);
            window.draw(tx);

        }

        if (p.life == false) {
            texet.setString("You Death");
            texet.setPosition(view.getCenter().x - 350, view.getCenter().y - 200);
            window.draw(texet);

        }

        if (Keyboard::isKeyPressed(Keyboard::E)) {
            window.draw(g.sprite);
        }



        window.draw(p.sprite);
        window.display();
    }
    return 0;
}