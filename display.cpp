#include <Display.h>
#include <Arduino.h>
#include <Menu.h>
#include <Motor.h>
#include <IR.h>
#include <Sonar.h>
#include <LFR.h>
#define SCREEN_WIDTH  128
#define SCREEN_HEIGHT  64

extern LFR lfr;
extern uint32_t position;

Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, -1);

void addContentFromChildren(Menu* M){
    for(int i=0 ; i<= M->childrenCount; i++)
    {
        M->content[i]=M->children[i]->name;
    }

    if(M->name == "MainMenu") M->content[M->childrenCount]="Run";
    else M->content[M->childrenCount]="Back";
}
Display::Display(uint8_t upPin, uint8_t downPin, uint8_t enterPin)
    : up(upPin), down(downPin), enter(enterPin)
    {
        up.init();
        down.init();
        enter.init();

        root.addChild(&subMenu1);
        root.addChild(&subMenu2);
        root.addChild(&subMenu3);

        subMenu1.addChild(&subMenu11);
        subMenu1.addChild(&subMenu12);
        subMenu1.addChild(&subMenu13);

        subMenu2.addChild(&subMenu21);
        subMenu2.addChild(&subMenu22);
        
        subMenu3.addChild(&subMenu31);
        subMenu3.addChild(&subMenu32);

        subMenu11.addChild(&subMenu111);
        subMenu11.addChild(&subMenu112);

        for (int i = 0; i < numOfMenu; i++)
        {
            addContentFromChildren(arr[i]);
        }

        for(int i= 0 ; i < 4 ; i++){
          subMenu21.addContent(tuneContent[i]);
          subMenu22.addContent(tuneContent[i]);
        
        }



     /* //additional contents i.e. varialbes

        for (int i = 0; i < lfr.ir.getSensorNumbers(); i++)
        {
            subMenu12.addVariableContent<int>(&lfr.ir.sensorAnalogueValue[i],i);
        }

        for (int i = 0; i < lfr.ir.getSensorNumbers(); i++)
        {
            subMenu13.addVariableContent<int>(&lfr.ir.sensorBinaryValue,i);
        }

        subMenu21.addVariableContent<double>(&lfr.Kp,0);
        subMenu22.addVariableContent<double>(&lfr.Kd,0);
        subMenu31.addVariableContent<uint8_t>(&lfr.speed,0);
        subMenu32.addVariableContent<uint8_t>(lfr.leftMotor.getSpeedPointer(),0);
        subMenu32.addVariableContent<uint8_t>(lfr.rightMotor.getSpeedPointer(),1);

        for (int i = 0; i < lfr.ir.getSensorNumbers(); i++)
        {
            subMenu111.addVariableContent<int>(&lfr.ir.calibrateMax[i],i);
            subMenu111.addVariableContent<int>(&lfr.ir.calibrateMin[i],i+lfr.ir.getSensorNumbers());
            
        }   
      */   

    }

void setUpState(){
    lfr.OLED.up.setState(true);
}

void setDownState(){
    lfr.OLED.down.setState(true);
}

void setEnterState(){
    lfr.OLED.enter.setState(true);
}
void Display::init(){
    if(!display.begin(SSD1306_SWITCHCAPVCC, 0x3C)) {
    Serial.println(F("SSD1306 allocation failed"));
    for(;;); // Don't proceed, loop forever
  }
    display.display();
    delay(2000);
    display.clearDisplay();

    //attach interrupt to buttons

    attachInterrupt(digitalPinToInterrupt(up.buttonPin), setUpState , RISING);
    attachInterrupt(digitalPinToInterrupt(down.buttonPin), setDownState , RISING);
    attachInterrupt(digitalPinToInterrupt(enter.buttonPin), setEnterState , RISING);
}





void Display::setDisplay() {
    display.clearDisplay();
    display.setTextSize(1);
    display.setTextColor(SSD1306_WHITE);
    display.setCursor(0,0);

}


void Display::displayMenu(Menu* menu, bool dynamic){
    display.clearDisplay();
    display.setTextSize(1);
    display.setTextColor(SSD1306_WHITE);
    display.setCursor(0,0);
   // display.println(menu->name);

   if(!dynamic){    
    for(int i = 0; i <= menu->childrenCount; i++){
        if(i == menu->selected){
            display.setTextColor(SSD1306_BLACK, SSD1306_WHITE);
        }
        else{
            display.setTextColor(SSD1306_WHITE);
        }
        
        display.println(menu->content[i]);
    } 
   }
   else{
        if(menu->name=="Calibration Value"){
        display.println("Calibration Max");
        for(int i = 0; i < lfr.ir.getSensorNumbers(); i++){
            display.print(lfr.ir.calibrateMax[i]);
            display.print(" ");
        }
        display.println();
        display.println("Calibration Min");
        for(int i = 0; i < lfr.ir.getSensorNumbers(); i++){
            display.print(lfr.ir.calibrateMin[i]);
            display.print(" ");
        }       
    }

    else if(menu->name=="RawValue"){
        display.println("Raw Value");
        for(int i = 0; i < lfr.ir.getSensorNumbers(); i++){
            display.print(lfr.ir.sensorAnalogueValue[i]);
            display.print(" ");
        }
        display.println();
        for(int i = 0; i < lfr.ir.getSensorNumbers()-1; i++){
            display.print(*lfr.ir.sensorReadingPtr[i]);
            display.print(" ");
        }
        display.println();
        //display.print("position: "); display.println(position);
    }

    else if(menu->name=="BinValue"){
        display.println("Binary Value");
        display.print(lfr.ir.sensorBinaryValue, BIN);
         display.print(" ");
        
    }

    else if(menu->name=="Kp"){
        display.println("Kp");
        display.println(lfr.Kp);
    }

    else if(menu->name=="Kd"){
        display.println("Kd");
        display.println(lfr.Kd);
    }

    else if(menu->name=="Motor Speed"){
        display.println("Motor Speed");
        display.println(lfr.speed);
    }

    else if(menu->name=="Live Speed"){
        display.println("Left Motor Speed");
        display.println(*lfr.leftMotor.getSpeedPointer());
        display.println("Right Motor Speed");
        display.println(*lfr.rightMotor.getSpeedPointer());
    }

    else if(menu->name=="Test"){
        display.println("Test");
        display.println("Test");
    }

    else if(menu->name=="Live Distances"){
        display.println("Live Distances");
        display.println("Live Distances");
    }
    
    if(menu->childrenCount>0){
        for(int i = 0; i <= menu->childrenCount; i++){
        if(i == menu->selected){
            display.setTextColor(SSD1306_BLACK, SSD1306_WHITE);
        }
        else{
            display.setTextColor(SSD1306_WHITE);
        }
        
        display.println(menu->content[i]);
    } 
    }
   }

    display.display();


}

   
void Display::navigate(Menu* currentMenu){
        if (up.pressed){
            if(currentMenu->selected>0){
                currentMenu->selected--;
            }
            else{
                currentMenu->selected = currentMenu->childrenCount;
            }
            up.setState(false);
        }

        if (down.pressed){
            if(currentMenu->selected<currentMenu->childrenCount){
                currentMenu->selected++; 
            }
            else{
                currentMenu->selected = 0;
            }
            down.setState(false);
        }

        if (enter.pressed){

            if (currentMenu->children[currentMenu->selected]->name == "Calibrate"){
                lfr.ledGreen.on();
                lfr.ledRed.on();
                lfr.ir.calibrate(5000);
                lfr.ledGreen.off();
                lfr.ledRed.off();
            }

            else if(currentMenu->selected == currentMenu->childrenCount){
                if(currentMenu->goToParent() != nullptr)
                    this->currentMenu = currentMenu->goToParent();
            }

            else if(currentMenu->goToChild(currentMenu->selected) != nullptr){
            this->currentMenu = currentMenu->goToChild(currentMenu->selected);
            }

            else if(currentMenu->content[currentMenu->selected] == "Increase" &&  currentMenu->name == "Kp"){
                
                lfr.Kp += 0.1;
            }

            else if(currentMenu->content[currentMenu->selected] == "Decrease" &&  currentMenu->name == "Kp"){
                
                lfr.Kp -= 0.1;
            }

            else if(currentMenu->content[currentMenu->selected] == "Increase" &&  currentMenu->name == "Kd"){
                
                lfr.Kd += 0.1;
            }

            else if(currentMenu->content[currentMenu->selected] == "Decrease" &&  currentMenu->name == "Kd"){
                
                lfr.Kd -= 0.1;
            }

            else if(currentMenu->content[currentMenu->selected] == "Increase" &&  currentMenu->name == "Motor Speed"){
                
                lfr.speed += 10;
            }

            else if(currentMenu->content[currentMenu->selected] == "Decrease" &&  currentMenu->name == "Motor Speed"){
                
                lfr.speed -= 10;
            }

            enter.setState(false);
        }
}

 
 

