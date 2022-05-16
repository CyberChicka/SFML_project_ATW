#include <SFML/Graphics.hpp>
using namespace sf;

View view; //объявляем SFML обект вид, который и является камерой
View getPlayerCoordinateForView(float x, float y){ // функция для считывания движения игрока
    float tempX = x; float tempY = y;
    if(x < 320) tempX = 320; //убираем из вида левую сторону
    if(y < 250) tempY = 250; //убирем из вида задную сторону
    if(y > 554) tempY = 554; //убираем из вида верхную сторонуa
     view.setCenter(tempX, tempY); // Следим за игроко передавая его координаты

    return view;

}
