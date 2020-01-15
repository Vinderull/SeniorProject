#include <stdio.h>
#include "ssd1306.h"
#include "fonts.h"



void findNote(float frequency, char *note, char *noteFreq)
{

  /*B1 note */
  if(frequency>= 59.98 && frequency <= 63.55){
    sprintf(note, "B1");
    sprintf(noteFreq, "%.2f", frequency);
  }

  /*C2 note */
  else if(frequency>= 63.56 && frequency <= 67.33){
    sprintf(note, "C2");
    sprintf(noteFreq, "%.2f", frequency);
  }

  /*Db2 note */
  else if(frequency>= 67.34 && frequency <= 71.33){
    sprintf(note, "Db2");
    sprintf(noteFreq, "%.2f", frequency);
  }


  /*D2 note */
  else if(frequency>= 71.34 && frequency <= 75.53){
    sprintf(note, "D2");
    sprintf(noteFreq, "%.2f", frequency);
  }


  /*Eb2 note */
  else if(frequency <= 80.59 && frequency >= 75.57 ){
    sprintf(note, "Eb2");
    sprintf(noteFreq, "%.2f", frequency);
  }

  /*E2 note */
  else if(frequency<=84.824 && frequency>=80.06){
    sprintf(note, "E2");
    sprintf(noteFreq, "%.2f", frequency);
  }


  /*F2 note */
  else if(frequency <= 89.87 && frequency >= 84.82){
    sprintf(note, "F2");
    sprintf(noteFreq, "%.2f", frequency);
  }

  /*Gb2 note */
  else if(frequency <= 95.21 && frequency >= 89.88){
    sprintf(note, "Gb2");
    sprintf(noteFreq, "%.2f", frequency);
  }

  /*G2 note */
  else if(frequency <= 100.87 && frequency >= 95.22){
    sprintf(note, "G2");
    sprintf(noteFreq, "%.2f", frequency);
  }

  /*Ab2 note */
  else if(frequency <= 106.873 && frequency >= 100.88){
    sprintf(note, "Ab2");
    sprintf(noteFreq, "%.2f", frequency);
  }

  /*A2 note */
  else if(frequency <= 113.22 && frequency >= 106.88){
    sprintf(note, "A2");
    sprintf(noteFreq, "%.2f", frequency);
  }

  /*B2 note */
  else if(frequency <= 127.08 && frequency >= 119.93){
    sprintf(note, "B2");
    sprintf(noteFreq, "%.2f", frequency);
  }

  /*C3 note */
  else if(frequency <= 134.64 && frequency >= 127.08){
    sprintf(note, "C3");
    sprintf(noteFreq, "%.2f", frequency);
  }

  /*Db3 note */
  else if(frequency <= 142.65 && frequency >= 134.65){
    sprintf(note, "Db3");
    sprintf(noteFreq, "%.2f", frequency);
  }

  /* D3 note */
  else if(frequency <= 151.13 && frequency >= 142.65){
    sprintf(note, "D3");
    sprintf(noteFreq, "%.2f", frequency);
  }

  /*Eb3 note */
  else if(frequency <= 160.11 && frequency >= 151.14){
    sprintf(note, "Eb3");
    sprintf(noteFreq, "%.2f", frequency);
  }

  /*E3 note */
  else if(frequency <= 169.64 && frequency >= 160.12){
    sprintf(note, "E3");
    sprintf(noteFreq, "%.2f", frequency);
  }

  /*F3 note */
  else if(frequency <= 180.76 && frequency >= 169.65){
    sprintf(note, "F3");
    sprintf(noteFreq, "%.2f", frequency);
  }

  /*Gb3 note */
  else if(frequency <= 190.42 && frequency >= 180.76){
    sprintf(note, "Gb3");
    sprintf(noteFreq, "%.2f", frequency);
  }

  /*G3 note */
  else if(frequency <= 201.76 && frequency >= 190.42){
    sprintf(note, "G3");
    sprintf(noteFreq, "%.2f", frequency);
  }

  /*Ab3 note */
  else if(frequency <= 213.73 && frequency >= 226.45){
    sprintf(note, "Ab3");
    sprintf(noteFreq, "%.2f", frequency);
  }

  /*A3 note */
  else if(frequency <= 226.45 && frequency >= 213.74){
    sprintf(note, "A3");
    sprintf(noteFreq, "%.2f", frequency);
  }

  /*Bb3 note */
  else if(frequency <= 239.91 && frequency >= 226.46){
    sprintf(note, "Bb3");
    sprintf(noteFreq, "%.2f", frequency);
  }

  /*B3 note */
  else if(frequency <= 254.18 && frequency >= 239.92){
    sprintf(note, "B3");
    sprintf(noteFreq, "%.2f", frequency);
  }

  /*C4 note */
  else if(frequency <= 269.29 && frequency >= 254.19){
    sprintf(note, "C4");
    sprintf(noteFreq, "%.2f", frequency);
  }

  /*Db4 note */
  else if(frequency <= 285.3 && frequency >= 269.29){
    sprintf(note, "Db4");
    sprintf(noteFreq, "%.2f", frequency);
  }

  /*D4 note */
  else if(frequency <= 302.26 && frequency >= 285.31){
    sprintf(note, "D4");
    sprintf(noteFreq, "%.2f", frequency);
  }

  /*Eb4 note */
  else if(frequency <= 320.25 && frequency >= 392.27){
    sprintf(note, "Eb4");
    sprintf(noteFreq, "%.2f", frequency);
  }

  /*E4 note */
  else if(frequency <= 339.29 && frequency >= 320.26){
    sprintf(note, "E4");
    sprintf(noteFreq, "%.2f", frequency);
  }

  /*F4 note */
  else if(frequency <= 359.46 && frequency >= 339.30){
    sprintf(note, "F4");
    sprintf(noteFreq, "%.2f", frequency);
  }

  /*Gb4 note */
  else if(frequency <= 380.83 && frequency >= 359.47){
    sprintf(note, "Gb4");
    sprintf(noteFreq, "%.2f", frequency);
  }


  /*G4 note */
  else if(frequency <= 403.49 && frequency >= 380.83){
    sprintf(note, "G4");
    sprintf(noteFreq, "%.2f", frequency);
  }

  /*Ab4 note */
  else if(frequency <= 427.56 && frequency >= 452.89){
    sprintf(note, "Ab4");
    sprintf(noteFreq, "%.2f", frequency);
  }

  /*A4 note */
  else if(frequency <= 452.89 && frequency >= 427.57){
    sprintf(note, "A4");
    sprintf(noteFreq, "%.2f", frequency);
  }

  /*Bb4 note */
  else if(frequency <= 479.82 && frequency >= 452.90){
    sprintf(note, "Bb4");
    sprintf(noteFreq, "%.2f", frequency);
  }

/*end note detect */
}


void print2Screen(float frequency, char *note, char *noteFreq)
{

    note(frequency, &note[0], &noteFreq[0]);
    ssd1306_SetCursor(23,23);
    ssd1306_WriteString(note,Font_11x18,Black);
    ssd1306_SetCursor(13,13);
    ssd1306_WriteString(noteFreq,Font_11x18,Black);

    ssd1306_UpdateScreen();
    HAL_Delay(500);
}
