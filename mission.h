// /////////////////////////////////НОМЕР МИССИИ//////////////////////////////////
int getCurrentMission(int x)//ф-ция номера миссия, которая меняет номер миссии, в зависимости от координаты игрока Х (сюда будем передавать эту координату)
{
    int mission = 0;
    if ((x>0) && (x<600)) { mission = 0; } //знакомим игрока с игрой
    if (x>400) { mission = 1; } //игрок на первой миссии
    if (x>1000) { mission = 2; }//2ой
    if (x>2200) { mission = 3; }//и тд

    return mission;//ф-ция возвращает номер миссии
}



// ///////////////////////////////////ТЕКСТ МИССИИ/////////////////////////////////
std::string getTextMission(int currentMission) {

    std::string missionText = "";//текст миссии и его инициализация

    switch (currentMission)//принимается номер миссии и в зависимости от него переменной missionText присваивается различный текст
    {
        case 0:
            missionText = "\nGetting Started and \nGame Instructions";
            break;
        case 1:
            missionText ="\nMission 1\n\n Here's your first\n mission, \non this level \nyou should be wary\n... blah blah blah...";
            break;
        case 2:
            missionText = "\nMission 2\n You need to solve\n a logic puzzle\n to proceed further ";
            break;
        case 3:
            missionText = "\nAnd so on \nand so on.......";
            break;
    }

    return missionText;//ф-ция возвращает текст
}