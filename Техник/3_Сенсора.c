#include <Adafruit_BMP085.h>
#include <Wire.h>
Adafruit_BMP085 sensor;


struct pin{
    const int PIN;
    bool benable;
};

struct l{
    pin LDR ;
    int light;
    int dark;
};

struct r{
    pin PIR ;
    bool bmove;
};


void vivodTemprrature(float t)
{
    Serial.print("t");
    Serial.print("=");
    Serial.println(t);
}

void vkl(pin *l){
    digitalWrite(l->PIN, 1);
    l->benable = true;
}

void vikl(pin*l){
    digitalWrite(l->PIN, 0);
    l->benable = false;
}

void vklOrVikl(l *p, r *d, pin LED, pin LED2, const int POROG){
    float t = sensor.readTemperature();
    p->light = analogRead(p->LDR.PIN);
    d->bmove = digitalRead(d->PIR.PIN) == HIGH;
    if (p->light >= p->dark && d->bmove == true){
        vkl(&LED);
        if (t > POROG){
            vkl(&LED2);
        }
        else{
            vikl(&LED2);
        }
    }else{
        vikl(&LED);
        vikl(&LED2);
    }
}



pin LED = {8, false};
pin LED2 = {9, false};
l ldr = {{A0, true}, 0, 500};
r pir = {{A1, true}, false};
const long sen = 200;
long lastRead = 0;
long lastLed = 0;
const long IZMLED = 100;
bool ready = false;
const int POROG = 30;


void setup() {
    Serial.begin(9600);
    ready = sensor.begin();
    if (!ready){
        Serial.println("TEMPERATURE SENSOR NOT FOUND");
    }
    pinMode(LED.PIN, OUTPUT);
    pinMode(LED2.PIN, OUTPUT);

}


void loop() {
    long now = millis();
    
    ldr.light = analogRead(ldr.LDR.PIN);
    pir.bmove = digitalRead(pir.PIR.PIN) == HIGH;

    if (now - lastLed >= IZMLED){
        lastLed = now;
        vklOrVikl(&ldr, &pir, LED, LED2, POROG);
    }
    if (now - lastRead >= sen){
        lastRead = now;
        vivodTemprrature(sensor.readTemperature();
    }
}