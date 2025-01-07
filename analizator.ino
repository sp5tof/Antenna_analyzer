

#include <Adafruit_GFX.h>    
#include <Adafruit_ST7735.h> 
#include <SPI.h>

#define W_CLK 6       // Pin 8 - connect to AD9850 module word load clock pin (CLK)
#define FQ_UD 3       // Pin 9 - connect to freq update pin (FQ)
#define DATA 4       // Pin 10 - connect to serial data load pin (DATA)
#define RESET 5      // Pin 11 - connect to reset pin (RST).
 
#define pulseHigh(pin) {digitalWrite(pin, HIGH); digitalWrite(pin, LOW); }

#define TFT_CS     10
#define TFT_RST    9  
#define TFT_DC     8

#define TFT_SCLK 13   
#define TFT_MOSI 11   

Adafruit_ST7735 tft = Adafruit_ST7735(TFT_CS,  TFT_DC, TFT_RST);

// Color definitions
#define BLACK           0x0000
#define BLUE            0x001F
#define RED             0xF800
#define GREEN           0x07E0
#define CYAN            0x07FF
#define MAGENTA         0xF81F
#define YELLOW          0xFFE0 
 
#define WHITE           0xFFFF
// end of color definitions

//antenna image array
const unsigned char PROGMEM logo16_glcd_bmp []  = {
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x02, 0x00, 0x00, 0x00, 0x00, 0x07, 0x00, 0x00, 0x00, 0x00, 
0x06, 0x00, 0x00, 0x00, 0x00, 0x0c, 0x00, 0x00, 0x00, 0x00, 0x18, 0x06, 0x00, 0x00, 0x00, 0x30, 
0x0e, 0x00, 0x00, 0x00, 0x60, 0x1c, 0x00, 0x00, 0x00, 0xe0, 0x38, 0x70, 0x00, 0x01, 0xc0, 0x70, 
0xe1, 0x00, 0x03, 0x80, 0xe1, 0xc3, 0x00, 0x03, 0xe1, 0xc3, 0x87, 0x02, 0x06, 0xfb, 0x87, 0x0e, 
0x06, 0x0c, 0x3f, 0x0e, 0x3c, 0x0c, 0x18, 0x0f, 0xd8, 0x78, 0x38, 0x30, 0x0d, 0xf8, 0xf0, 0x70, 
0x60, 0x38, 0x7f, 0xc0, 0xe0, 0xe0, 0x30, 0xff, 0xc1, 0x80, 0xc0, 0xe1, 0x9f, 0xe7, 0x00, 0x00, 
0xc7, 0x1f, 0xfe, 0x00, 0x01, 0x8e, 0x3d, 0x3c, 0x00, 0x00, 0x0c, 0x7b, 0x3c, 0x00, 0x00, 0x00, 
0xfb, 0xe0, 0x00, 0x00, 0x01, 0xdb, 0xc0, 0x00, 0x00, 0x01, 0x8b, 0x00, 0x00, 0x00, 0x00, 0x1e, 
0x00, 0x00, 0x00, 0x00, 0x1e, 0x00, 0x00, 0x00, 0x00, 0x1e, 0x00, 0x00, 0x00, 0x00, 0x1a, 0x00, 
0x00, 0x00, 0x00, 0x1a, 0x00, 0x00, 0x00, 0x00, 0x0a, 0x00, 0x00, 0x00, 0x00, 0x02, 0x00, 0x00, 

};

const unsigned char PROGMEM logo16_glcd_bmp2 [] = {
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
0x00, 0x00, 0x00, 0x00, 0x04, 0x00, 0x10, 0x00, 0x00, 0x04, 0x00, 0x10, 0x00, 0x00, 0x18, 0x00, 
0x1c, 0x00, 0x00, 0x11, 0x00, 0x44, 0x00, 0x00, 0x77, 0x41, 0x64, 0x00, 0x00, 0x44, 0x81, 0x14, 
0x00, 0x00, 0x4d, 0x39, 0xd6, 0x00, 0x00, 0x49, 0x78, 0x53, 0x00, 0x00, 0x59, 0x7c, 0x53, 0x00, 
0x00, 0x5b, 0x7c, 0x51, 0x00, 0x00, 0x59, 0x7e, 0x53, 0x00, 0x00, 0x49, 0x7c, 0x53, 0x00, 0x00, 
0x4d, 0xbd, 0xd6, 0x00, 0x00, 0x44, 0xd1, 0x34, 0x00, 0x00, 0x77, 0x71, 0x64, 0x00, 0x00, 0x11, 
0x30, 0xc4, 0x00, 0x00, 0x1d, 0x79, 0x9c, 0x00, 0x00, 0x04, 0x78, 0x10, 0x00, 0x00, 0x06, 0x7c, 
0x70, 0x00, 0x00, 0x00, 0x7c, 0x00, 0x00, 0x00, 0x00, 0x7c, 0x00, 0x00, 0x00, 0x00, 0x64, 0x00, 
0x00, 0x00, 0x00, 0xe6, 0x00, 0x00, 0x00, 0x00, 0xde, 0x00, 0x00, 0x00, 0x01, 0xff, 0x00, 0x00, 
0x00, 0x01, 0xc3, 0x00, 0x00, 0x00, 0x03, 0xc3, 0x00, 0x00, 0x00, 0x03, 0xff, 0x80, 0x00, 0x00, 
0x07, 0xff, 0xc0, 0x00, 0x00, 0x07, 0x00, 0xc0, 0x00, 0x00, 0x1f, 0xff, 0xf0, 0x00, 0x00, 0x1f, 
0xff, 0xf0, 0x00, 0x00, 0x7f, 0xff, 0xfc, 0x00, 0x00, 0x70, 0x00, 0x1c, 0x00, 0x00, 0xf0, 0x00, 
0x1f, 0x00, 0x00, 0x40, 0x00, 0x06, 0x00, 0x00, 0x40, 0x00, 0x04, 0x00, 0x00, 0x00, 0x00, 0x00, 
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
};



double Start_Freq = 7.1e6; //13.4e6;//  20.5e6;//6.4e6; //start Freq; in Mhz  20.5e6;//  3.6e6;//
double End_Freq =  7.2e6; //14.5e6;// 22.5e6;//7.8e6; //End Scan Freq; in Mhz 22.5e6;// 4.5e6;//
double Step_Freq = 5e3; //Step  Freq; in KHz 25000;// 25e3;// 
double VSWRLim = 2;
double current_freq;
int FwdOffSet;
int RevOffSet;
int FwdSCVal = 30;// initialially set to 1; then set to reading found when antenna leg of bridge is shorted; Diode sensitivity compensation
int RevSCVal = 40;// initialially set to 1; then set to reading found when antenna leg of bridge is shorted; Diode sensitivity compensation
int FwdOpAmpGain;
int RevOpAmpGain;

double LastVSWR = 999;
bool VSWRtrendUP = false;
bool Incrmnt = true;
bool RunCurve = true;
char buf [32]; // used to concatenate strings & numerical data for display
double SweepData[8];
int state = 3;
// Small signal correction table [array] 
int CrtdVal[] = {
  0, 0, 2, 4, 7, 9, 12, 14, 16, 19, 22, 25, 28, 31, 33, 35,36, 37, 39, 40, 41, 42, 43, 44, 44, 46, 47, 49, 50, 52, 53, 54, 55, 57, 58, 
  59, 60, 62, 63, 64, 65, 66, 67, 68, 69, 70, 71, 72, 73, 74, 75, 76, 77, 78, 79, 79, 81, 82, 83, 84, 85, 86, 87, 88, 89, 90, 91, 92, 93, 94, 95, 96, 97,
  98, 99, 100, 101, 102, 103, 104, 105, 105, 106, 107, 108, 109, 110, 111, 111, 112, 113, 114, 114, 115, 116, 117, 117, 118, 119, 120, 120, 121, 122, 122,
  123, 124, 124, 125, 126, 126, 127, 128, 129, 130, 131, 132, 133, 133, 134, 135, 136, 137, 138, 139, 139, 140, 141, 142, 143, 143, 144, 145, 146, 147, 147,
  148, 149, 150, 151, 151, 152, 153, 154, 154, 155, 156, 157, 157, 158, 159, 160, 160, 161, 162, 162, 163, 164, 164, 165, 166, 166, 167, 168, 168, 169, 170,
  171, 172, 172, 173, 174, 175, 176, 176, 177, 178, 179, 179, 180, 181, 182, 182, 183, 184, 185, 185, 186, 187, 187, 188, 189, 190, 190, 191, 192, 193, 193,
  194, 195, 196, 196, 197, 198, 198, 199, 200, 200, 201, 202, 203, 203, 204, 205, 205, 206, 207, 207, 208, 209, 209, 210, 211, 211, 212, 213, 213, 214, 215,
  215, 216, 216, 217, 218, 218, 219, 220, 220, 221, 221, 222, 223, 223, 224, 225, 225, 226, 226, 227, 228, 228, 229, 229, 230, 230, 231, 232, 232, 233, 233,
  234, 234, 235, 235
  };

 // transfers a byte, a bit at a time, LSB first to the 9850 via serial DATA line
void tfr_byte(byte data)
{
  for (int i=0; i<8; i++, data>>=1) {
    digitalWrite(DATA, data & 0x01);
    pulseHigh(W_CLK);   //after each bit sent, CLK is pulsed high
  }
}

 // frequency calc from datasheet page 8 = <sys clock> * <frequency tuning word>/2^32
void sendFrequency(double frequency) {
  int32_t freq = frequency * 4294967295/125000000;  // note 125 MHz clock on 9850
  for (int b=0; b<4; b++, freq>>=8) {
    tfr_byte(freq & 0xFF);
  }
  tfr_byte(0x000);   // Final control byte, all 0 for 9850 chip
  pulseHigh(FQ_UD);  // Done!  Should see output
}

//przyciski
#define niebieski  2
#define czerwony  7
//przyciski

void setup() {
  
  tft.initR(INITR_BLACKTAB);  // You will need to do this in every sketch
  tft.fillScreen(ST7735_BLACK);
  tft.setRotation(3); 
  
  char str_Band[4];
 // configure arduino data pins for output
  pinMode(FQ_UD, OUTPUT);
  pinMode(W_CLK, OUTPUT);
  pinMode(DATA, OUTPUT);
  pinMode(RESET, OUTPUT);
  
  //przyciski
  
  // initialize the button pin as a input:
  pinMode(niebieski, INPUT);
  pinMode(czerwony, INPUT);
  
  //strona tytulowa
tft.drawBitmap(0, 0,  logo16_glcd_bmp, 40, 32, RED);


  tft.setTextSize(2);
  tft.setCursor(27, 16);
  tft.setTextColor(BLUE);
  tft.println(" Antenna");
  tft.println("   Analyzer");
  tft.println(" ");
    tft.setTextColor(GREEN);
     tft.setTextSize(1);
  tft.println("          based on");
  tft.println("       KW4KD project");
  tft.setTextColor(RED);
  tft.println(" ");
  tft.println("         by SP5TOF");
  tft.println(" ");
  tft.println(" ");

delay(1000);

 // pomiar napiecia zasilania
 
 tft.setTextColor(MAGENTA);
  tft.setCursor(55, 110);
 tft.print("Battery : ");
  tft.setCursor(115, 110);

long millivolts = readVcc();
  tft.print(millivolts);
  tft.print(" V");
  

  if(millivolts<4400)
  {
    
    tft.setCursor(0, 115);
    tft.setTextColor(YELLOW, BLUE);
    tft.println("Battery low");
  }
  delay(3000);
 
 // show MENU

                                                 
 int wybor;
char* menu[] = {"160m",
                "80m ",
                "40m ",
                "20m ",
                "17m ",
                "15m ",
                "12m ",
                "11m ",
                "10m "};
 
  tft.fillScreen(ST7735_BLACK);
  tft.setTextSize(2);
  tft.setCursor(27, 11);
  tft.setTextColor(MAGENTA);
  tft.println(" Choose");
  tft.println("    band");
  tft.setTextSize(1);

  tft.setTextColor(BLUE);
  tft.setTextSize(2);
         
while(1)
{
  clear_choose();

    tft.print(menu[0]);

while (digitalRead(niebieski)==LOW)
    {
      if (digitalRead(czerwony)==HIGH) 
      {
            Start_Freq = 1.80e6; // Freq; in Mhz
            End_Freq =  2.0e6; // Freq; in Mhz
            sprintf (str_Band, "160"); //str_Band = "160"
            
//diodes compensations

            FwdOpAmpGain = 92;// initialially set to 1; then set to FWD reading found when Cathodes of D1 and D2 are shorted together; (Op Amp Gain loop compensation)
            RevOpAmpGain = 92;//88;// initialially set to 1; then set to REV reading found when Cathodes of D1 and D2 are shorted together; (Op Amp Gain loop compensation)

//diodes compensations
            goto next;
      }
    }

delay(400);
clear_choose();

    tft.print(menu[1]);
    
while (digitalRead(niebieski)==LOW)
    {
      if (digitalRead(czerwony)==HIGH) 
      {
    Start_Freq = 3.5e6; // Freq; in Mhz
    End_Freq =  4.0e6; // Freq; in Mhz
    sprintf (str_Band, "80"); //str_Band = "80"
    
//diodes compensations

            FwdOpAmpGain = 88;// initialially set to 1; then set to FWD reading found when Cathodes of D1 and D2 are shorted together; (Op Amp Gain loop compensation)
            RevOpAmpGain = 120;//88;// initialially set to 1; then set to REV reading found when Cathodes of D1 and D2 are shorted together; (Op Amp Gain loop compensation)

//diodes compensations

    goto next;
      }
    }
delay(400);
    clear_choose();

    tft.print(menu[2]);
 
  
   
while (digitalRead(niebieski)==LOW)
    {
      if (digitalRead(czerwony)==HIGH) 
      {
          Start_Freq = 7.0e6; // Freq; in Mhz
          End_Freq =  7.3e6; // Freq; in Mhz
          sprintf (str_Band, "40"); //str_Band = "40"

//diodes compensations

            FwdOpAmpGain = 100;// initialially set to 1; then set to FWD reading found when Cathodes of D1 and D2 are shorted together; (Op Amp Gain loop compensation)
            RevOpAmpGain = 120;//88;// initialially set to 1; then set to REV reading found when Cathodes of D1 and D2 are shorted together; (Op Amp Gain loop compensation)

//diodes compensations
          goto next;
      }
    }
delay(400);
clear_choose();

    tft.print(menu[3]);
    
   
while (digitalRead(niebieski)==LOW)
    {
      if (digitalRead(czerwony)==HIGH)
     {
    Start_Freq = 14.0e6; // Freq; in Mhz  20.5e6;//  3.6e6;//
    End_Freq =  14.4e6; // Freq; in Mhz
    sprintf (str_Band, "20"); //str_Band = "20"
    
//diodes compensations

            FwdOpAmpGain = 95;// initialially set to 1; then set to FWD reading found when Cathodes of D1 and D2 are shorted together; (Op Amp Gain loop compensation)
            RevOpAmpGain = 120;//88;// initialially set to 1; then set to REV reading found when Cathodes of D1 and D2 are shorted together; (Op Amp Gain loop compensation)

//diodes compensations
       goto next;
     }
    }
delay(400);
    clear_choose();

    tft.print(menu[4]);

while (digitalRead(niebieski)==LOW)
    {
      if (digitalRead(czerwony)==HIGH) 
      {

    Start_Freq = 18.0e6; // Freq; in Mhz
    End_Freq =  18.2e6; // Freq; in Mhz
    sprintf (str_Band, "17"); //str_Band = "17"

//diodes compensations

            FwdOpAmpGain = 74;// initialially set to 1; then set to FWD reading found when Cathodes of D1 and D2 are shorted together; (Op Amp Gain loop compensation)
            RevOpAmpGain = 132;//88;// initialially set to 1; then set to REV reading found when Cathodes of D1 and D2 are shorted together; (Op Amp Gain loop compensation)

//diodes compensations
    goto next;
      }
    }
delay(400);
    clear_choose();

    tft.print(menu[5]);

while (digitalRead(niebieski)==LOW)
    {
      if (digitalRead(czerwony)==HIGH)
     {
    Start_Freq = 21.0e6; // Freq; in Mhz
    End_Freq =  21.5e6; // Freq; in Mhz
    sprintf (str_Band, "15"); //str_Band = "15"
    
//diodes compensations

            FwdOpAmpGain = 71;// initialially set to 1; then set to FWD reading found when Cathodes of D1 and D2 are shorted together; (Op Amp Gain loop compensation)
            RevOpAmpGain = 132;//88;// initialially set to 1; then set to REV reading found when Cathodes of D1 and D2 are shorted together; (Op Amp Gain loop compensation)

//diodes compensations
    goto next;
     }
    }
delay(400);
    clear_choose();
    

    tft.print(menu[6]);


while (digitalRead(niebieski)==LOW)
    {
      if (digitalRead(czerwony)==HIGH) 
      {
    Start_Freq = 24.8e6; // Freq; in Mhz
    End_Freq =  25.0e6; // Freq; in Mhz
    sprintf (str_Band, "12"); //str_Band = "12"
    
//diodes compensations

            FwdOpAmpGain = 67;// initialially set to 1; then set to FWD reading found when Cathodes of D1 and D2 are shorted together; (Op Amp Gain loop compensation)
            RevOpAmpGain = 110;//88;// initialially set to 1; then set to REV reading found when Cathodes of D1 and D2 are shorted together; (Op Amp Gain loop compensation)

//diodes compensations
    goto next;
      }
    }
delay(400);
    clear_choose();

    tft.print(menu[7]);
  

while (digitalRead(niebieski)==LOW)
    {
      if (digitalRead(czerwony)==HIGH) 
      {
      Start_Freq = 26.9e6; // Freq; in Mhz
      End_Freq =  27.4e6; // Freq; in Mhz
      sprintf (str_Band, "11"); //str_Band = "11"

//diodes compensations

         FwdOpAmpGain = 72;//67;// initialially set to 1; then set to FWD reading found when Cathodes of D1 and D2 are shorted together; (Op Amp Gain loop compensation)
            RevOpAmpGain = 120;//88;// initialially set to 1; then set to REV reading found when Cathodes of D1 and D2 are shorted together; (Op Amp Gain loop compensation)

//diodes compensations
      goto next;
      }
    }
delay(400);
    clear_choose();

    tft.print(menu[8]);

while (digitalRead(niebieski)==LOW)
    {
      if (digitalRead(czerwony)==HIGH) 
      {
    Start_Freq = 28.0e6; // Freq; in Mhz
    End_Freq =  29.7e6; // Freq; in Mhz

    
    sprintf (str_Band, "10"); //str_Band = "10"
    
//diodes compensations

            FwdOpAmpGain = 82;// initialially set to 1; then set to FWD reading found when Cathodes of D1 and D2 are shorted together; (Op Amp Gain loop compensation)
            RevOpAmpGain = 50;//88;// initialially set to 1; then set to REV reading found when Cathodes of D1 and D2 are shorted together; (Op Amp Gain loop compensation)

//diodes compensations

    goto next;
      }
    }


delay(400);
}

                                                         //show MENU
 
next: 

//show menu scan or tune

 
  
  pulseHigh(RESET);
  pulseHigh(W_CLK);
  pulseHigh(FQ_UD);  // this pulse enables serial mode - Datasheet page 12 figure 10
  current_freq = Start_Freq;
  Serial.begin(9600);
  SweepData[1] = 999; //Lowest Recorded VSWR
  SweepData[2] = 0;
  SweepData[3] =0;
  SweepData[4] = 9999; 
  SweepData[5] = 0;
  SweepData[6] = 0;
  char buf2 [32];
  char buf3 [32];
  char buf4 [32];
  char str_StrtFq[6];
  char str_EndFq[6];
  char str_SWRLim[6];
  char str_Step[6];
  double SFqMhz = Start_Freq/1000000;
  double EFqMhz = End_Freq/1000000;
  dtostrf(SFqMhz, 4, 2, str_StrtFq);// char *dtostrf(double val, signed char width, unsigned char prec, char *s)
  dtostrf(EFqMhz, 4, 2, str_EndFq);
  dtostrf(VSWRLim, 4, 2, str_SWRLim);
  dtostrf(Step_Freq/1000, 4, 1, str_Step);
  sprintf (buf,"%s to %s MHz", str_StrtFq,str_EndFq);
  sprintf (buf2,"MAX VSWR: %s", str_SWRLim);
  sprintf (buf3,"Step: %s kHz", str_Step);
  sprintf (buf4,"%sM Ant Analyzer", str_Band);
  

delay(100);

  
  
 tft.fillScreen(ST7735_BLACK);
 //  u8g.firstPage();
       tft.setTextColor(ST7735_WHITE);
         tft.setTextSize(0);

    int row = 11; //first OLED row to print on
    
    tft.setCursor(0, row);
    tft.println(buf4);
    row = NuRow(row);
    tft.setCursor(0, row);
    tft.println(buf);
    row = NuRow(row);
    tft.setCursor(0, row);
     tft.println(buf2);
    row = NuRow(row);
    tft.setCursor(0, row);
     tft.println(buf3);
  //  u8g.setFont(u8g_font_7x13);
    row = NuRow(row);
    tft.setCursor(0, row);
    tft.println("Antenna Analyzer");

  delay(5500);
    tft.fillScreen(ST7735_BLACK);
    
      tft.fillScreen(ST7735_BLACK);
  tft.setTextSize(2);
  tft.setCursor(27, 11);
  tft.setTextColor(YELLOW);
  tft.println(" Choose");
  tft.setTextSize(1);

  tft.setTextColor(RED);
  tft.setTextSize(2);

 tft.drawRect(55,80,110,130, 0);
      tft.fillRect(55,80,110,130, 0);
          tft.setCursor(7, 65);
  tft.print("SCAN");
  tft.setTextColor(WHITE);
  tft.print(" or ");
  tft.setTextColor(BLUE);
  tft.print("TUNE");
  
while(state>1)
{
  if(digitalRead(czerwony)==HIGH)
    { state=0; }
  if (digitalRead(niebieski)==HIGH)
    { state=1;}
}
   
  }


void loop() 
{

  int incomingByte = 0;   // for incoming serial data
  sendFrequency(1.0);  // set AD9850 output to 1 Hz
  delay(100);
  RevOffSet = 0.0;
  FwdOffSet = 0.0;
  for (int i=0; i<20; i++) 
       {
       RevOffSet += analogRead(A0);
       FwdOffSet += analogRead(A2);
       delay(10);
       }
     RevOffSet = RevOffSet/20.0;
     FwdOffSet = FwdOffSet/20.0;



  if (RunCurve==true and state==0)
                {
     RunCurve = PrintNextPoint(RunCurve);
                }
 else if (RunCurve==true and state==1)
              { 
                 RunCurve = tune(RunCurve);
              }

  else          {
 
    sendFrequency(1.0);  // set AD9850 output to 1 Hz
    char buf2 [32];
    char buf3 [32];
    double BestSWR = SweepData[1];
    char str_SWR[6];
    char str_Ohms[6];
    char str_LowFreq[6];
    char str_HiFreq[6];
    dtostrf(BestSWR, 3, 1, str_SWR);
    dtostrf(SweepData[4], 3, 0, str_Ohms);
    sprintf (buf2,"Best SWR:%s/%s Ohm", str_SWR, str_Ohms);

    dtostrf(SweepData[6]/1000000, 4, 2, str_LowFreq);
    dtostrf(SweepData[5]/1000000, 4, 2, str_HiFreq);
    
    sprintf (buf3,"L/H %s/%s MHz", str_LowFreq, str_HiFreq);

    if(SweepData[2]> 0 && SweepData[3] >0)
                      {
      double centerFreq = (SweepData[2]+(SweepData[3]-SweepData[2])/2);
      char str_CFq[6];
      double CFqMhz = centerFreq/1000000;
      dtostrf(CFqMhz, 5, 3, str_CFq);// char *dtostrf(double val, signed char width, unsigned char prec, char *s)
      sprintf (buf,"Freq: %sMHz", str_CFq);
                      }
          else sprintf (buf,"%s", "NO DATA AVAILABLE!");
    
 //   u8g.firstPage();
    tft.fillScreen(ST7735_BLACK);
    tft.drawBitmap(120, 40,  logo16_glcd_bmp2, 40, 78, BLUE);
     int row = 11; //first OLED row to print on
   //  u8g.setFont(u8g_font_unifont);
    tft.setCursor(0, row);
     tft.println(buf);
    // u8g.setFont(u8g_font_7x13);
     row = NuRow(row);
     tft.setCursor(0, row);
      tft.println(buf3);
   //  u8g.setFont(u8g_font_unifont);
     row = NuRow(row);
     tft.setCursor(0, row);
      tft.println(buf2);
     row = NuRow(row);
     tft.setCursor(0, row);
     tft.println("Hit Red btn");
     row = NuRow(row);
      tft.setCursor(0, row);
     tft.println("to Scan Again");
     
    delay(2000);
    
 while (digitalRead(niebieski)==LOW)
    {
      if (digitalRead(czerwony)==HIGH) 
      {
 
    asm volatile ("  jmp 0");
      }
    }   
 
  }
 
 
 }

 

//*******************************************************//
bool PrintNextPoint(bool RunCurve){
   tft.fillScreen(ST7735_BLACK);
       tft.setTextColor(ST7735_WHITE);
         tft.setTextSize(0);
  float FWD;
  float REV;
  double VSWR;
  double EffOhms;
  bool GudRun = false;
  while (RunCurve){
         if (digitalRead(czerwony)==HIGH) delay(2000);
    sendFrequency(current_freq);  // freq
    delay(100);
     // Read the forward and reverse voltages
     REV = 0.0;
     FWD = 0.0;
     for (int i=0; i<70; i++) {
       REV += (analogRead(A0)-RevOffSet);
       FWD += (analogRead(A2)-FwdOffSet);
       
     }
     REV = REV/70.0;
     FWD = FWD/70.0;
    //REV = analogRead(A0)-RevOffSet;
    REV = (FwdOpAmpGain*REV)/RevOpAmpGain; // apply Op Amp Gain loop compensation
    REV = CorrectReading(REV);// now using table apply Small Signal correction value
    
    //FWD = analogRead(A1)-FwdOffSet;
    FWD = (RevSCVal*FWD)/FwdSCVal;// apply "Short Circuit" offset
    FWD = CorrectReading(FWD);// now using table apply Small Signal correction value
    if(REV>=FWD){
      // To avoid a divide by zero or negative VSWR then set to max 999
      VSWR = 999;
    }else{
      // Calculate VSWR
      
      VSWR = ((FWD+REV)/(FWD-REV));
    }
    if(FWD>=116) EffOhms = VSWR*47.0;//FWD>=94
    else  EffOhms = 47.0/VSWR;
   // u8g.firstPage();
    // Post results

      int row = 11; //first OLED row to print on
    //  u8g.setFont(u8g_font_7x13);
  // tft.fillScreen(ST7735_BLACK);
     tft.setCursor(0, row);
      tft.print("Freq: ");
      tft.drawRect(30,row,100,row+25, 0);
      tft.fillRect(30,row,100,row+25, 0);
      tft.print(int(current_freq/1000));
      tft.print(" kHz");
      if (Incrmnt) tft.print(" +");
      else tft.print(" -");
   //   u8g.setFont(u8g_font_unifont);
      row = NuRow(row);
      tft.setCursor(0, row);
      tft.print("VSWR: ");
      tft.drawRect(30,row+25,100,row+50, 0);
      tft.fillRect(30,row+25,100,row+50, 0);
      tft.print(VSWR);//LastVSWR
      if (VSWRtrendUP) tft.print(" +");
      else tft.print(" -");
      if( VSWR > VSWRLim)tft.print("!!");
       else tft.print("  ");
      row = NuRow(row);
      tft.setCursor(0, row);
      tft.print("Ohms: ");
       tft.drawRect(30,row+25,100,row+50, 0);
      tft.fillRect(30,row+25,100,row+50, 0);
      tft.print(EffOhms);
      row = NuRow(row);
      tft.setCursor(8, row);  
      tft.print("Fwd: ");
        tft.drawRect(33,row+25,100,row+50, 0);
      tft.fillRect(33,row+25,100,row+50, 0);
      tft.print(FWD);
      row = NuRow(row);
      tft.setCursor(8, row);
      tft.print("Rev: ");
      tft.drawRect(33,row+25,100,row+50, 0);
      tft.fillRect(33,row+25,100,row+50, 0);
      tft.print(REV);
   
    // Check for & Save interesting data
    if (VSWR < SweepData[1]) {
      if (Incrmnt){
        SweepData[1] = VSWR;
        SweepData[2] = current_freq;
        SweepData[4] = EffOhms;
      }
    }
    if (VSWR == SweepData[1]) {
      if (Incrmnt){
        SweepData[3] = current_freq;
      }
    }
    if (VSWR < LastVSWR-0.06){
      VSWRtrendUP = false;
       LastVSWR = VSWR;
    }

    if (VSWR > LastVSWR+0.06){
      VSWRtrendUP = true;
      LastVSWR = VSWR;
    }
    if( VSWR < VSWRLim) GudRun = true;
    if (Incrmnt && VSWR < VSWRLim ) SweepData[5] = current_freq; // capture Highest Freq that is below the VSWR limit
    if (!Incrmnt && VSWR < VSWRLim ) SweepData[6] = current_freq; // capture Lowest Freq that is below the VSWR limit 
    if (GudRun){
      if (Incrmnt && VSWRtrendUP && VSWR > VSWRLim )Incrmnt = false;
      else if (!Incrmnt && VSWRtrendUP && VSWR > VSWRLim ){
        Incrmnt = true;
        if (GudRun) RunCurve = false;
      }
    }
    if (current_freq >  End_Freq) Incrmnt = false;
    if (current_freq <  Start_Freq) RunCurve = false; // Exit The freqs of interest have been examined; But aparently a usable SWR was not found 
    if (Incrmnt) current_freq += Step_Freq;
    else current_freq -= Step_Freq;
    }// end While Loop
    
    

   
    return RunCurve;
}

double CorrectReading(double ReadVal){
//  Serial.println(ReadVal);
//  if (ReadVal > 263)return ReadVal;// if (ReadVal > 0)return ReadVal;//
//  return CrtdVal[ReadVal];
 if (ReadVal > 70)return 0.8*ReadVal+57;// if (ReadVal > 0)return ReadVal;//
 if (ReadVal < 13)return 3.6*(ReadVal*ReadVal)/15;
 float CalcVal =1.1*( 8+(2.1*ReadVal)-((ReadVal*ReadVal)*10.7/1000));
 return CalcVal;
}

int NuRow(int oldrow){
   {
    int pixcnt = 25;
    oldrow += pixcnt;
    return oldrow; 
   }
}



void clear_choose()
{
 tft.drawRect(55,80,110,130, 0);
      tft.fillRect(55,80,110,130, 0);
          tft.setCursor(55, 80);

}

long readVcc() {
  // Read 1.1V reference against AVcc
  // set the reference to Vcc and the measurement to the internal 1.1V reference
  #if defined(__AVR_ATmega32U4__) || defined(__AVR_ATmega1280__) || defined(__AVR_ATmega2560__)
    ADMUX = _BV(REFS0) | _BV(MUX4) | _BV(MUX3) | _BV(MUX2) | _BV(MUX1);
  #elif defined (__AVR_ATtiny24__) || defined(__AVR_ATtiny44__) || defined(__AVR_ATtiny84__)
    ADMUX = _BV(MUX5) | _BV(MUX0);
  #elif defined (__AVR_ATtiny25__) || defined(__AVR_ATtiny45__) || defined(__AVR_ATtiny85__)
    ADMUX = _BV(MUX3) | _BV(MUX2);
  #else
    ADMUX = _BV(REFS0) | _BV(MUX3) | _BV(MUX2) | _BV(MUX1);
  #endif  

  delay(2); // Wait for Vref to settle
  ADCSRA |= _BV(ADSC); // Start conversion
  while (bit_is_set(ADCSRA,ADSC)); // measuring

  uint8_t low  = ADCL; // must read ADCL first - it then locks ADCH  
  uint8_t high = ADCH; // unlocks both

  long result = (high<<8) | low;

  result = 1125300L / result; // Calculate Vcc (in mV); 1125300 = 1.1*1023*1000
  return result; // Vcc in millivolts
}

bool tune(bool RunCurve){
 tft.fillScreen(ST7735_BLACK);

       tft.setTextColor(ST7735_WHITE);
         tft.setTextSize(0);
  float FWD;
  float REV;
  double VSWR;
  double EffOhms;
  bool GudRun = false;

  while (RunCurve){
    sendFrequency(current_freq);  // freq
    delay(100);
     // Read the forward and reverse voltages
     REV = 0.0;
     FWD = 0.0;
     for (int i=0; i<70; i++) {
       REV += (analogRead(A0)-RevOffSet);
       FWD += (analogRead(A2)-FwdOffSet);
       
     }
     REV = REV/70.0;
     FWD = FWD/70.0;
    //REV = analogRead(A0)-RevOffSet;
    REV = (FwdOpAmpGain*REV)/RevOpAmpGain; // apply Op Amp Gain loop compensation
    REV = CorrectReading(REV);// now using table apply Small Signal correction value
    
    //FWD = analogRead(A1)-FwdOffSet;
    FWD = (RevSCVal*FWD)/FwdSCVal;// apply "Short Circuit" offset
    FWD = CorrectReading(FWD);// now using table apply Small Signal correction value
    if(REV>=FWD){
      // To avoid a divide by zero or negative VSWR then set to max 999
      VSWR = 999;
    }else{
      // Calculate VSWR
      
      VSWR = ((FWD+REV)/(FWD-REV));
    }
    if(FWD>=116) EffOhms = VSWR*47.0;//FWD>=94
    else  EffOhms = 47.0/VSWR;
   // u8g.firstPage();
    // Post results

      int row = 11; //first OLED row to print on
    //  u8g.setFont(u8g_font_7x13);
  // tft.fillScreen(ST7735_BLACK);
     tft.setCursor(0, row);
      tft.print("Freq: ");
      tft.drawRect(30,row,100,row+25, 0);
      tft.fillRect(30,row,100,row+25, 0);
      tft.print(int(current_freq/1000));
      tft.print(" kHz");
      if (Incrmnt) tft.print(" +");
      else tft.print(" -");
   //   u8g.setFont(u8g_font_unifont);
      row = NuRow(row);
      tft.setCursor(0, row);
      tft.print("VSWR: ");
      tft.drawRect(30,row+25,100,row+50, 0);
      tft.fillRect(30,row+25,100,row+50, 0);
      tft.print(VSWR);//LastVSWR
      if (VSWRtrendUP) tft.print(" +");
      else tft.print(" -");
      if( VSWR > VSWRLim)tft.print("!!");
       else tft.print("  ");
      row = NuRow(row);
      tft.setCursor(0, row);
      tft.print("Ohms: ");
       tft.drawRect(30,row+25,100,row+50, 0);
      tft.fillRect(30,row+25,100,row+50, 0);
      tft.print(EffOhms);
      row = NuRow(row);
      tft.setCursor(8, row);  
      tft.print("Fwd: ");
        tft.drawRect(33,row+25,100,row+50, 0);
      tft.fillRect(33,row+25,100,row+50, 0);
      tft.print(FWD);
      row = NuRow(row);
      tft.setCursor(8, row);
      tft.print("Rev: ");
      tft.drawRect(33,row+25,100,row+50, 0);
      tft.fillRect(33,row+25,100,row+50, 0);
      tft.print(REV);
   
 
  
    if (digitalRead(czerwony)==HIGH) current_freq -= Step_Freq;
     if (digitalRead(niebieski)==HIGH) current_freq += Step_Freq;
 
//    RunCurve = false;
    }// end While Loop
    
    

   
    return RunCurve;
}

