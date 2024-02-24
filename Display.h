#ifndef Display_h
#define Display_h

#include <Button.h>
#include <Arduino.h>
#include <Menu.h>
#include <SPI.h>
#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>



class Display {
public:
    Display(uint8_t upPin, uint8_t downPin, uint8_t enterPin);
    void init();

    void displayMenu(Menu* menu);
    void displayMenu(Menu* menu, bool dynamic);

    void displaySensorReading();
    void displayPID();
    void displayMotorSpeed();
    void displayBinValue();
    void displayRawValue();
    void setDisplay() ;

    

    void navigate(Menu* currentMenu);

    Menu* currentMenu = &root;
    Button up;
    Button down; 
    Button enter; 

private:
   
   

    Menu root = Menu("MainMenu");

    Menu subMenu1 = Menu("Sensor", &root);
    Menu subMenu2 = Menu("PID", &root);
    Menu subMenu3 = Menu("Motor", &root);
    Menu subMenu4 = Menu("Sonar", &root);

    Menu subMenu11 = Menu("Calibration", &subMenu1); 
    Menu subMenu12 = Menu("RawValue", &subMenu1, true); //dynamic
    Menu subMenu13 = Menu("BinValue", &subMenu1, true); //dynamic
    Menu submenu14 = Menu("Threshold", &subMenu1, true); //dynamic

    Menu subMenu21 = Menu("Kp", &subMenu2, true); //dynamic
    Menu subMenu22 = Menu("Kd", &subMenu2, true); //dynamic
    Menu subMenu31 = Menu("Motor Speed", &subMenu3, true); //dynamic
    Menu subMenu32 = Menu("Live Speed", &subMenu3, true); //dynamic
    
    Menu subMenu41 = Menu("Test", &subMenu4, true); //dynamic
    Menu subMenu42 = Menu("Live Distances", &subMenu4, true); //dynamic

    Menu subMenu111 = Menu("Calibration Value", &subMenu11, true); //dynamic
    Menu subMenu112 = Menu("Calibrate", &subMenu11); 
    Menu subMenu113 = Menu("Save Calibration", &subMenu11); 

    //Menu KpTune = Menu("KpTune", &subMenu21, true); //dynamic
    //Menu KdTune = Menu("KdTune", &subMenu22, true); //dynamic
    //Menu MotorSpeedTune = Menu("MotorSpeedTune", &subMenu31, true); //dynamic
    //Menu ThresholdTune = Menu("ThresholdTune", &submenu14, true); //dynamic



    static const int8_t numOfMenu = 17;
    Menu* arr[numOfMenu] = {&root, &subMenu1, &subMenu2, &subMenu3, 
                    &subMenu4, &subMenu11, &subMenu12, &subMenu13, 
                    &subMenu21, &subMenu22, &subMenu31, &subMenu32, 
                    &subMenu41, &subMenu42, &subMenu111, &subMenu112};
    
    // Menu* tune[4] = {&KpTune, &KdTune, &MotorSpeedTune, &ThresholdTune};

    String tuneContent[4] = {
        "Increase",
        "Decrease",
        "Save",
        "Back"
    };

    //uint8_t const OLED_RESET = 4;
};


#endif

