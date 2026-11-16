//структура
struct Svetodiod {
    int pin;           // Номер пина
    bool sostoyanie;   // Включен (true) или выключен (false)
    unsigned long vremya; // Время последнего мигания
};


//массив структур
// 0 - Основной, 1 - Индикатор движения, 2 - Индикатор света
Svetodiod leds[3];


//Переменные для кнопки и логики
bool trevoga = false;        // Включена ли сигнализация (мигание)
bool na_ohrane = true;       // Система готова сработать
bool knopka_zhataya = false; // Нажата ли кнопка прямо сейчас
unsigned long vremya_nazhatiya = 0; // Когда нажали кнопку
const int blink = 500; //длительность состояния лампоччки


//Функции для работы с указателями
void vklyuchit(Svetodiod *l) {
    l->sostoyanie = true;
    digitalWrite(l->pin, HIGH);
}
void vyklyuchit(Svetodiod *l) {
    l->sostoyanie = false;
    digitalWrite(l->pin, LOW);
}


//обозначение пинов
const int BUTTON_PIN = 23;
const int PIR = A1;
const int LDR = A0;
const int LED_BLINK = 8;
const int LED_PIR = 9;
const int LED_LDR = 10;




void setup() {
    // Настройка пинов
    pinMode(BUTTON_PIN, INPUT_PULLUP); // Кнопка сброса
    pinMode(PIR, INPUT);        // Датчик движения (PIR)
    pinMode(LDR, INPUT);       // Датчик света (Фоторезистор)


    // Настройка светодиодов в массиве
    leds[0].pin = LED_BLINK; // Основной
    leds[1].pin = LED_PIR;  // Датчик движения
    leds[2].pin = LED_LDR;  // Датчик света

    for (int i = 0; i < 3; i++) {
    pinMode(leds[i].pin, OUTPUT);
    leds[i].sostoyanie = false;
    digitalWrite(leds[i].pin, LOW);
    }
}




void loop() {

    // ШАГ 1. ЧТЕНИЕ КНОПКИ (Умный сброс)

    if (digitalRead(BUTTON_PIN) == LOW) { // Если кнопка нажата
        if (knopka_zhataya == false) {
            knopka_zhataya = true;
            vremya_nazhatiya = millis(); // Запоминаем время нажатия
        }
        // Если держим кнопку 3 секунды (3000 мс)
        else if (millis() - vremya_nazhatiya > 3000) {
            trevoga = false;  // Выключаем мигание
            na_ohrane = true; // Система снова на охране
            vyklyuchit(&leds[0]);
        }
    } else { // Если кнопка отпущена
        if (knopka_zhataya == true) {
            knopka_zhataya = false;
        }
    }


    // ШАГ 2. ЧТЕНИЕ ДАТЧИКОВ

    bool est_dvizhenie = digitalRead(PIR);
    bool est_svet = false;
    if (analogRead(LDR) > 500) { // Если света достаточно (порог можно менять)
        est_svet = true;
    }


    // Индикация датчиков (каждый своим светодиодом)
    if (est_dvizhenie) { vklyuchit(&leds[1]); } else { vyklyuchit(&leds[1]); }
    if (est_svet)      { vklyuchit(&leds[2]); } else { vyklyuchit(&leds[2]); }



    // ШАГ 3. ЛОГИКА СИГНАЛИЗАЦИИ

    // Если есть движение И есть свет - включаем тревогу
    if (na_ohrane == true && est_dvizhenie == true && est_svet == true) {
        trevoga = true;
    }



    // ШАГ 4. МИГАНИЕ ОСНОВНОГО СВЕТОДИОДА

    if (trevoga == true) {
        // Мигаем каждые отрывок времени
        if (millis() - leds[0].vremya > blink) {
            leds[0].vremya = millis();
            leds[0].sostoyanie = !leds[0].sostoyanie; // Меняем состояние на противоположное
            digitalWrite(leds[0].pin, leds[0].sostoyanie);
    }
    } else {
        // Если тревоги нет, светодиод просто выключен
        vyklyuchit(&leds[0]);
    }
}