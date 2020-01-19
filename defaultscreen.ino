#include <SoftwareSerial.h>
#include "PWM.hpp"
#include <Nextion.h>

SoftwareSerial sf(27,17);  //RX,TX
int rpm_pin1 = 2;
int rpm_pin2 = A1;
int rpm_pin3 = 8;
int coolant_pin = 6;
int battery_pin = A1;
int rpm_level = 1;

//PWM my_pwm(6);

int pin1 = 2;
int pin2 = 6;
int pin3 = 8;
int pin4 = 10;
int pin6 = 1;
int pin7 = 0;
int pin8 = 13;
int pin9 = 12;
int pin5 = A1;

NexPage page1 = NexPage(1, 0, "page1");
NexPage page2 = NexPage(2, 0, "page2");

unsigned long instance_millis,time0,highTime,newTime,time1,time_initial,prevTime;
int interval = 500;
int i,k;
int pwm_value;
int a,b,c,page = 1;
//Gear pins : 1 - 43,39,37,47,45,32

NexTouch *nex_listen_list[] = {
  &page1, &page2, NULL
};

void page1PopCallback(void *ptr){
  Serial.println("page 2");
  sf.write("page page2");
  sf.write(0xff);
  sf.write(0xff);
  sf.write(0xff);
  page = 2;
} 

void page2PopCallback(void *ptr){
  sf.write("page page1");
  sf.write(0xff);
  sf.write(0xff);
  sf.write(0xff);
  page = 1;
} 

void setup() {
  // put your setup code here, to run once:
  sf.begin(9600);
  Serial.begin(115200);
//  my_pwm.begin(true);
  pinMode(43, INPUT_PULLUP);
  pinMode(39, INPUT_PULLUP);
  pinMode(37, INPUT_PULLUP);
  pinMode(31, INPUT_PULLUP);
  pinMode(45, INPUT_PULLUP);
  pinMode(32, INPUT_PULLUP);
  pinMode(rpm_pin1, INPUT_PULLUP);
  pinMode(rpm_pin2, INPUT_PULLUP);
  pinMode(rpm_pin3, INPUT_PULLUP);
  pinMode(coolant_pin, INPUT);
  pinMode(battery_pin, INPUT);

  pinMode(pin1,INPUT_PULLUP);
  //pinMode(pin2,INPUT_PULLUP);
  pinMode(pin3,INPUT_PULLUP);
  pinMode(pin4,INPUT_PULLUP);
  pinMode(pin6,INPUT_PULLUP);
  pinMode(pin7,INPUT_PULLUP);
  pinMode(pin8,INPUT_PULLUP);
  pinMode(pin9,INPUT_PULLUP);
  pinMode(pin5,INPUT_PULLUP);

  page1.attachPop(page1PopCallback);
  page2.attachPop(page2PopCallback);

  //page2_boot();

  time_initial = millis();

  sf.write("dims=100");
  sf.write(0xff);
  sf.write(0xff);
  sf.write(0xff);

  for(k = 0; k < 101; k++){
    sf.write("j0.val=");
    sf.write(k);
    sf.write(0xff); 
    sf.write(0xff);
    sf.write(0xff);
    delay(20);
  }

  sf.write("page page1");
  sf.write(0xff);
  sf.write(0xff);
  sf.write(0xff);
}

//Gear pins : 1 - 43(3),39(5),37(1),31(4),45(6),32(2)

//8,9,10,11.12,13,15,14

void loop() {
  // put your main code here, to run repeatedly:
//  pwm_value = pulseIn(3, HIGH);
//  Serial.println(pwm_value);

//  if() {
//    if(page == 1) {
//      sf.write("page page2");
//      sf.write(0xff);
//      sf.write(0xff);
//      sf.write(0xff);
//      page = 2;
//    } else if(page == 2) {
//      sf.write("page page1");
//      sf.write(0xff);
//      sf.write(0xff);
//      sf.write(0xff);
//      page = 1;
//    }
//  }

  if(page == 1){
    rpmlvl_fn();
    gear_fn();
    coolant_fn();
  } else if(page == 2){
//    noisetest();
  }
  nexLoop(nex_listen_list);
  
  //Serial.println(digitalRead(coolant_pin));
//  if(digitalRead(battery_pin) == HIGH){
//    sf.write("p6.pic=23");
//    sf.write(0xff); 
//    sf.write(0xff);
//    sf.write(0xff);
//  } else{
//    sf.write("p6.pic=25");
//    sf.write(0xff);
//    sf.write(0xff);
//    sf.write(0xff);
//  }
  
}

void noisetest() {
  a = digitalRead(rpm_pin1);
  b = analogRead(rpm_pin2);
  c = digitalRead(rpm_pin3);
  if(a == LOW && b == LOW && c == LOW) {
    bg_black();
    noise_lvl1_high();
    noise_lvl2_low();
    noise_lvl3_low();
    noise_lvl4_low();
    noise_lvl5_low();
    noise_lvl6_low();
    noise_lvl7_low();
    noise_lvl8_low();
  } else if(a == LOW && b == LOW && c == HIGH) {
    bg_black();
    noise_lvl1_high();
    noise_lvl2_high();
    noise_lvl3_low();
    noise_lvl4_low();
    noise_lvl5_low();
    noise_lvl6_low();
    noise_lvl7_low();
    noise_lvl8_low();
  } else if(a == LOW && b == HIGH && c == LOW) {
    bg_black();
    noise_lvl1_high();
    noise_lvl2_high();
    noise_lvl3_high();
    noise_lvl4_low();
    noise_lvl5_low();
    noise_lvl6_low();
    noise_lvl7_low();
    noise_lvl8_low();
  } else if(a == LOW && b == HIGH && c == HIGH) {
    bg_green();
    noise_lvl1_high();
    noise_lvl2_high();
    noise_lvl3_high();
    noise_lvl4_high();
    noise_lvl5_low();
    noise_lvl6_low();
    noise_lvl7_low();
    noise_lvl8_low();
  } else if(a == HIGH && b == LOW && c == LOW) {
    bg_green();
    noise_lvl1_high();
    noise_lvl2_high();
    noise_lvl3_high();
    noise_lvl4_high();
    noise_lvl5_high();
    noise_lvl6_low();
    noise_lvl7_low();
    noise_lvl8_low();
  } else if(a == HIGH && b == LOW && c == HIGH) {
    bg_black();
    noise_lvl1_high();
    noise_lvl2_high();
    noise_lvl3_high();
    noise_lvl4_high();
    noise_lvl5_high();
    noise_lvl6_high();
    noise_lvl7_low();
    noise_lvl8_low();
  } else if(a == HIGH && b == HIGH && c == LOW) {
    bg_black();
    noise_lvl1_high();
    noise_lvl2_high();
    noise_lvl3_high();
    noise_lvl4_high();
    noise_lvl5_high();
    noise_lvl6_high();
    noise_lvl7_high();
    noise_lvl8_low();
  } else if(a == HIGH && b == HIGH && c == HIGH) {
    bg_black();
    noise_lvl1_high();
    noise_lvl2_high();
    noise_lvl3_high();
    noise_lvl4_high();
    noise_lvl5_high();
    noise_lvl6_high();
    noise_lvl7_high();
    noise_lvl8_high();
  }
}

void bg_green() {
  sf.write("page2.bco=2016");
  sf.write(0xff);
  sf.write(0xff);
  sf.write(0xff);
}

void bg_black() {
  sf.write("page2.bco=1");
  sf.write(0xff);
  sf.write(0xff);
  sf.write(0xff);
}

void noise_lvl1_high() {
  sf.write("p0.pic=34");
  sf.write(0xff); 
  sf.write(0xff);
  sf.write(0xff);
}

void noise_lvl2_high() {
  sf.write("p1.pic=35");
  sf.write(0xff); 
  sf.write(0xff);
  sf.write(0xff);
}

void noise_lvl3_high() {
  sf.write("p2.pic=36");
  sf.write(0xff); 
  sf.write(0xff);
  sf.write(0xff);
}

void noise_lvl4_high() {
  sf.write("p3.pic=37");
  sf.write(0xff); 
  sf.write(0xff);
  sf.write(0xff);
}

void noise_lvl5_high() {
  sf.write("p4.pic=37");
  sf.write(0xff); 
  sf.write(0xff);
  sf.write(0xff);
}

void noise_lvl6_high() {
  sf.write("p5.pic=36");
  sf.write(0xff); 
  sf.write(0xff);
  sf.write(0xff);
}

void noise_lvl7_high() {
  sf.write("p6.pic=35");
  sf.write(0xff); 
  sf.write(0xff);
  sf.write(0xff);
}

void noise_lvl8_high() {
  sf.write("p7.pic=34");
  sf.write(0xff); 
  sf.write(0xff);
  sf.write(0xff);
}

void noise_lvl1_low() {
  sf.write("p0.pic=38");
  sf.write(0xff);
  sf.write(0xff);
  sf.write(0xff);
}

void noise_lvl2_low() {
  sf.write("p1.pic=39");
  sf.write(0xff); 
  sf.write(0xff);
  sf.write(0xff);
}

void noise_lvl3_low() {
  sf.write("p2.pic=40");
  sf.write(0xff); 
  sf.write(0xff);
  sf.write(0xff);
}

void noise_lvl4_low() {
  sf.write("p3.pic=41");
  sf.write(0xff); 
  sf.write(0xff);
  sf.write(0xff);
}

void noise_lvl5_low() {
  sf.write("p4.pic=41");
  sf.write(0xff);
  sf.write(0xff);
  sf.write(0xff);
}

void noise_lvl6_low() {
  sf.write("p5.pic=40");
  sf.write(0xff);
  sf.write(0xff);
  sf.write(0xff);
}

void noise_lvl7_low() {
  sf.write("p6.pic=39");
  sf.write(0xff); 
  sf.write(0xff);
  sf.write(0xff);
}

void noise_lvl8_low() {
  sf.write("p7.pic=38");
  sf.write(0xff); 
  sf.write(0xff);
  sf.write(0xff);
}

void rpmlvl_fn() {
  a = digitalRead(rpm_pin1);
  b = analogRead(rpm_pin2);
  c = digitalRead(rpm_pin3);

  Serial.print(a);
  Serial.print(" ");
  Serial.print(b);
  Serial.print(" ");
  Serial.println(c);
  
  if(a == LOW && b < 800 && c == LOW){
    if (rpm_level == 1) {
      lvl1_high();
//      lvl2_low();
//      lvl3_low();
//      lvl4_low();
//      lvl5_low();
//      lvl6_low();
//      lvl7_low();
//      lvl8_low();
    } else {
      lvl8_low();
      lvl7_low();
      lvl6_low();
      lvl5_low();
      lvl4_low();
      lvl3_low();
      lvl2_low();
    }
    rpm_level = 1;
  }else if(a == LOW && b < 800 && c == HIGH){  // rpm_lvl2
    if (rpmlevel <= 2) {
      lvl1_high();
      lvl2_high();
//      lvl3_low();
//      lvl4_low();
//      lvl5_low();
//      lvl6_low();
//      lvl7_low();
//      lvl8_low();
    } else {
      lvl8_low();
      lvl7_low();
      lvl6_low();
      lvl5_low();
      lvl4_low();
      lvl3_low();
//      lvl1_high();
//      lvl2_high();
    }
    rpm_level = 2;
  }else if(a == LOW && b >= 800 && c == LOW){ //rpm_lvl_3
    if (rpm_level <= 3) {
      lvl1_high();
      lvl2_high();
      lvl3_high();
//      lvl4_low();
//      lvl5_low();
//      lvl6_low();
//      lvl7_low();
//      lvl8_low();
    } else {
      lvl8_low();
      lvl7_low();
      lvl6_low();
      lvl5_low();
      lvl4_low();
    }
    rpm_level = 3;
  }else if(a == LOW && b >= 800 && c == HIGH){ //rpm_lvl4
    if (rpm_level <= 4) {
      lvl1_high();
      lvl2_high();
      lvl3_high();
      lvl4_high();
//      lvl5_low();
//      lvl6_low();
//      lvl7_low();
//      lvl8_low();
    } else {
      lvl8_low();
      lvl7_low();
      lvl6_low();
      lvl5_low();
    }
    rpm_level = 4;
  }if(a == HIGH && b < 800 && c == LOW){ //rpm_lvl5
    if (rpm_level <=5) {
      lvl1_high();
      lvl2_high();
      lvl3_high();
      lvl4_high();
      lvl5_high();
//      lvl6_low();
//      lvl7_low();
//      lvl8_low();
    } else {
      lvl8_low();
      lvl7_low();
      lvl6_low();
    }
    rpm_level = 5;
  }else if(a == HIGH && b < 800 && c == HIGH){ //rpm_lvl6
    if (rpm_level <=6) {
      lvl1_high();
      lvl2_high();
      lvl3_high();
      lvl4_high();
      lvl5_high();
      lvl6_high();
//      lvl7_low();
//      lvl8_low();
    } else {
      lvl8_low();
      lvl7_low();
    }
    rpm_level = 6;
  }else if(a == HIGH && b >= 800 && c == LOW){ //rpm_lvl7
    if (rpm_level <=7) {
      lvl1_high();
      lvl2_high();
      lvl3_high();
      lvl4_high();
      lvl5_high();
      lvl6_high();
      lvl7_high();
//      lvl8_low();
    } else {
      lvl8_low();
    }
    rpm_level = 7;
  }else if(a == HIGH && b >= 800 && c == HIGH){ //rpm_lvl8
    lvl1_high();
    lvl2_high();
    lvl3_high();
    lvl4_high();
    lvl5_high();
    lvl6_high();
    lvl7_high();
    lvl8_high();
    rpm_level = 8;
  }
}

void gear_fn() {
  if(digitalRead(37) == LOW) {
    sf.print("p14.pic=17");
    sf.write(0xff); 
    sf.write(0xff);
    sf.write(0xff);
  } else if(digitalRead(32) == LOW) {
    sf.print("p14.pic=18");
    sf.write(0xff); 
    sf.write(0xff);
    sf.write(0xff);
  }
  else if(digitalRead(43) == LOW) {
    sf.print("p14.pic=19");
    sf.write(0xff); 
    sf.write(0xff);
    sf.write(0xff);
  }
  else if(digitalRead(31) == LOW) {
    sf.print("p14.pic=20");
    sf.write(0xff); 
    sf.write(0xff);
    sf.write(0xff);
  }
  else if(digitalRead(39) == LOW) {
    sf.print("p14.pic=21");
    sf.write(0xff); 
    sf.write(0xff);
    sf.write(0xff);
  }
  else if(digitalRead(45) == LOW) {
    sf.print("p14.pic=22");
    sf.write(0xff); 
    sf.write(0xff);
    sf.write(0xff);
  }else {
    sf.print("p14.pic=16");
    sf.write(0xff); 
    sf.write(0xff);
    sf.write(0xff);
  }
}

void coolant_fn() {
  while(digitalRead(coolant_pin) == 0){
  }
  time0 = millis();
  while(digitalRead(coolant_pin) == 1){
  }
  highTime = pulseIn(6,HIGH)/1000;
  Serial.println(highTime);
//  if(highTime > newTime){
//    newTime = highTime;
//  }
  sf.print("n0.val=");
  sf.print(highTime);
  sf.write(0xff);
  sf.write(0xff);
  sf.write(0xff);
//  if(time0 - time1 > 6000) {
//    if(time_initial > 15000) {
//      if(abs(prevTime - newTime) < 5){
//        time1 = time0;
//        sf.print("n0.val=");
//        sf.print(highTime);
//        sf.write(0xff);
//        sf.write(0xff);
//        sf.write(0xff);
//        prevTime = newTime;
//        newTime = 0;
//      }
//    } else{
//      time1 = time0;
//        sf.print("n0.val=");
//        sf.print(newTime);
//        sf.write(0xff);
//        sf.write(0xff);
//        sf.write(0xff); 
//        prevTime = newTime;
//        newTime = 0;
//    }
//  }
}

void lvl1_high(){
  sf.write("p0.pic=0");
  sf.write(0xff);
  sf.write(0xff);
  sf.write(0xff);

  sf.write("p13.pic=0");
  sf.write(0xff);
  sf.write(0xff);
  sf.write(0xff);
//  nextion_writer("p0","pic","0");
//  nextion_writer("p13","pic","0");
}

void lvl2_high(){
  sf.write("p1.pic=1");
  sf.write(0xff);
  sf.write(0xff);
  sf.write(0xff);

  sf.write("p12.pic=1");
  sf.write(0xff);
  sf.write(0xff);
  sf.write(0xff);
//  nextion_writer("p1","pic","1");
//  nextion_writer("p12","pic","1");
}

void lvl3_high(){
  sf.write("p2.pic=2");
  sf.write(0xff);
  sf.write(0xff);
  sf.write(0xff);

  sf.write("p11.pic=2");
  sf.write(0xff);
  sf.write(0xff);
  sf.write(0xff);
//  nextion_writer("p2","pic","2");
//  nextion_writer("p11","pic","2");
}

void lvl4_high(){
  sf.write("p3.pic=3");
  sf.write(0xff);
  sf.write(0xff);
  sf.write(0xff);

  sf.write("p10.pic=3");
  sf.write(0xff);
  sf.write(0xff);
  sf.write(0xff);
//  nextion_writer("p3","pic","3");
//  nextion_writer("p10","pic","3");
}

void lvl5_high(){
  sf.write("p4.pic=4");
  sf.write(0xff);
  sf.write(0xff);
  sf.write(0xff);

  sf.write("p9.pic=4");
  sf.write(0xff);
  sf.write(0xff);
  sf.write(0xff);
//  nextion_writer("p4","pic","4");
//  nextion_writer("p9","pic","4");
}

void lvl6_high(){
  sf.write("p5.pic=5");
  sf.write(0xff);
  sf.write(0xff);
  sf.write(0xff);

  sf.write("p8.pic=5");
  sf.write(0xff);
  sf.write(0xff);
  sf.write(0xff);
//  nextion_writer("p5","pic","5");
//  nextion_writer("p8","pic","5");
}

void lvl7_high(){
  sf.print("p15.pic=6");  //lvl7
  sf.write(0xff); 
  sf.write(0xff);
  sf.write(0xff);
}

void lvl8_high(){
  sf.print("p16.pic=7");  //lvl8
  sf.write(0xff); 
  sf.write(0xff);
  sf.write(0xff);
}

void lvl2_low(){
  sf.write("p1.pic=9");
  sf.write(0xff);
  sf.write(0xff);
  sf.write(0xff);

  sf.write("p12.pic=9");
  sf.write(0xff);
  sf.write(0xff);
  sf.write(0xff);
//  nextion_writer("p1","pic","9");
//  nextion_writer("p12","pic","9");
}

void lvl3_low(){
  sf.write("p2.pic=10");
  sf.write(0xff);
  sf.write(0xff);
  sf.write(0xff);

  sf.write("p11.pic=10");
  sf.write(0xff);
  sf.write(0xff);
  sf.write(0xff);
//  nextion_writer("p2","pic","10");
//  nextion_writer("p11","pic","10");
}

void lvl4_low(){
  sf.write("p3.pic=11");
  sf.write(0xff);
  sf.write(0xff);
  sf.write(0xff);

  sf.write("p10.pic=11");
  sf.write(0xff);
  sf.write(0xff);
  sf.write(0xff);
//  nextion_writer("p3","pic","11");
//  nextion_writer("p10","pic","11");
}

void lvl5_low(){
  sf.write("p4.pic=12");
  sf.write(0xff);
  sf.write(0xff);
  sf.write(0xff);

  sf.write("p9.pic=12");
  sf.write(0xff);
  sf.write(0xff);
  sf.write(0xff);
//  nextion_writer("p4","pic","12");
//  nextion_writer("p9","pic","12");
}

void lvl6_low(){
  sf.write("p5.pic=13");
  sf.write(0xff);
  sf.write(0xff);
  sf.write(0xff);

  sf.write("p8.pic=13");
  sf.write(0xff);
  sf.write(0xff);
  sf.write(0xff);
//  nextion_writer("p5","pic","13");
//  nextion_writer("p8","pic","13");
}

void lvl7_low(){
  sf.print("p15.pic=15");  //lvl7
  sf.write(0xff); 
  sf.write(0xff);
  sf.write(0xff);
}

void lvl8_low(){
  sf.print("p16.pic=14");  //lvl8
  sf.write(0xff); 
  sf.write(0xff);
  sf.write(0xff);
}

  void nextion_writer(char a, char b, char c){
    sf.write(a);
    sf.write(".");
    sf.write(b);
    sf.write("=");
    sf.write(c);
    sf.write(0xff);
    sf.write(0xff);
    sf.write(0xff);
  }

  void page2_boot(){
    instance_millis = millis();
    while(millis() - instance_millis <= interval){}
  
    sf.write("p0.pic=0");
    sf.write(0xff); 
    sf.write(0xff);
    sf.write(0xff);
  
    sf.write("p13.pic=0");
    sf.write(0xff); 
    sf.write(0xff);
    sf.write(0xff);
  
    instance_millis = millis();
    while(millis() - instance_millis <= interval){}
  
    sf.print("p1.pic=1");
    sf.write(0xff); 
    sf.write(0xff);
    sf.write(0xff);
  
    sf.print("p12.pic=1");
    sf.write(0xff); 
    sf.write(0xff);
    sf.write(0xff);
  
    instance_millis = millis();
    while(millis() - instance_millis <= interval){}
  
    sf.print("p2.pic=2");
    sf.write(0xff); 
    sf.write(0xff);
    sf.write(0xff);
  
    sf.print("p11.pic=2");
    sf.write(0xff); 
    sf.write(0xff);
    sf.write(0xff);
  
    instance_millis = millis();
    while(millis() - instance_millis <= interval){}
  
    sf.print("p3.pic=3");
    sf.write(0xff); 
    sf.write(0xff);
    sf.write(0xff);
  
    sf.print("p10.pic=3");
    sf.write(0xff); 
    sf.write(0xff);
    sf.write(0xff);
  
    instance_millis = millis();
    while(millis() - instance_millis <= interval){}
  
    sf.print("p4.pic=4");
    sf.write(0xff); 
    sf.write(0xff);
    sf.write(0xff);
  
    sf.print("p9.pic=4");
    sf.write(0xff); 
    sf.write(0xff);
    sf.write(0xff);
  
    instance_millis = millis();
    while(millis() - instance_millis <= interval){}
  
    sf.print("p5.pic=5");
    sf.write(0xff); 
    sf.write(0xff);
    sf.write(0xff);
  
    sf.print("p8.pic=5");
    sf.write(0xff); 
    sf.write(0xff);
    sf.write(0xff);
  
    instance_millis = millis();
    while(millis() - instance_millis <= interval){}
  
    sf.print("p15.pic=6");
    sf.write(0xff); 
    sf.write(0xff);
    sf.write(0xff);
  
    instance_millis = millis();
    while(millis() - instance_millis <= interval){}
  
    sf.print("p16.pic=7");
    sf.write(0xff); 
    sf.write(0xff);
    sf.write(0xff);
  
    instance_millis = millis();
    while(millis() - instance_millis <= interval){}
  
    for(i = 17; i <= 22; i++){
      sf.print("p14.pic=");
      sf.print(i);
      sf.write(0xff); 
      sf.write(0xff);
      sf.write(0xff);
  
      instance_millis = millis();
      while(millis() - instance_millis <= interval){}
    }
  
    sf.print("p6.pic=34");
    sf.write(0xff);
    sf.write(0xff);
    sf.write(0xff);
  
    instance_millis = millis();
    while(millis() - instance_millis <= interval){}
  
    sf.print("p7.pic=24");
    sf.write(0xff);
    sf.write(0xff);
    sf.write(0xff);
  
    instance_millis = millis();
    while(millis() - instance_millis <= interval){}
  }
