# LINE LEADER - Firmware modular pentru Arduino Nano

Acest proiect separa firmware-ul intr-un fisier principal `.ino` si module `.h` / `.cpp`, pastrand arhitectura si functiile din codul furnizat.

## Continut

- `Line_Leader.ino` - `setup()` si unicul `loop()` principal.
- `Config.h` - pini, praguri, valori ESC si tuning PID.
- `RobotData.h/.cpp` - date globale si starea robotului.
- `Sensors.h/.cpp` - multiplexor, citire, calibrare, EEPROM si procesare senzori.
- `PID.h/.cpp` - calculul PID si urmarirea liniei.
- `Motors.h/.cpp` - control TB6612FNG.
- `Turbine.h/.cpp` - control ESC si rampa non-blocanta.
- `Button.h/.cpp` - buton si debounce.
- `Debug.h/.cpp` - mesaje si telemetrie Serial.

## Deschidere in Arduino IDE

1. Extrage arhiva ZIP intr-un folder.
2. Pastreaza toate fisierele impreuna in folderul `Line_Leader_Modular`.
3. Deschide `Line_Leader.ino` in Arduino IDE.
4. Selecteaza placa **Arduino Nano** si portul corect.
5. Instaleaza/verifica biblioteca **Servo** (de obicei inclusa in Arduino IDE).
6. Compileaza inainte de a incarca firmware-ul.

Nu incarca fisierele separat. Arduino IDE compileaza impreuna toate fisierele `.cpp` din folderul sketch-ului.

## Unde modifici PID-ul

Deschide `Config.h` si modifica:

```cpp
#define PID_KP 2.8f
#define PID_KI 0.0002f
#define PID_KD 1.4f
#define PID_BASE_SPEED 60
#define PID_MAX_SPEED 100
```

La pornire, aceste valori sunt copiate in variabilele `Kp`, `Ki`, `Kd`, `baseSpeed` si `maxSpeed` din `RobotData.cpp`.

## Secventa butonului

1. `IDLE` -> primul click: calibrare senzori; la succes trece in `INITIALIZATION`.
2. `INITIALIZATION` -> al doilea click: solicita `ESC_INIT_US`, apoi trece in `READY`.
3. `READY` -> al treilea click: solicita `ESC_RUN_US`, reseteaza PID si trece in `RUNNING`.
4. `RUNNING` -> al patrulea click: opreste motoarele si trimite ESC la minim, revine in `IDLE`.

## Atentie la testare

Valorile ESC de 1800 us au fost pastrate din firmware-ul furnizat; nu sunt validate aici pentru turbina/ESC-ul tau. Inainte de orice test cu turbina conectata, verifica mecanic montajul, protectia rotorului, alimentarea si compatibilitatea ESC-ului. Fa verificarea initiala fara elice/rotor montat sau cu sistemul de propulsie dezactivat, conform instructiunilor producatorului, si cere supravegherea unei persoane cu experienta.

## Nota despre pastrarea comportamentului

Structura si valorile principale au fost pastrate. Au fost facute doar schimbari de organizare si cateva ajustari de implementare pentru separarea modulelor. Testeaza compilarea si comportamentul pe banc inainte de utilizarea pe traseu.
