#include <stdio.h>
#include "ssd1306.h"
#include "fonts.h"


#define NOTEX 40
#define NOTEY 40
#define FREQX 40
#define FREQY 15
#define INTUNE 35


void findNote(float frequency)
{
  char note[40] = "thing\n\r";
  char noteFreq[40] = "thing\n\r";
  char dot[40] = "O";
  /*B1 note */
  if(frequency>= 59.98 && frequency <= 63.55){
    sprintf(note, "B1  ");
    sprintf(noteFreq, "%4.2f", frequency);
    ssd1306_SetCursor(NOTEX, NOTEY);
    ssd1306_WriteString(note,Font_11x18,Black);
    ssd1306_SetCursor(FREQX,FREQY);
    ssd1306_WriteString(noteFreq,Font_11x18,Black);

      /*if in tune plus/minus 10 cents */
      if(frequency>= 61.38 && frequency <= 62.09){
        ssd1306_SetCursor(NOTEX + INTUNE, NOTEY);
        ssd1306_WriteString(dot,Font_11x18,Black);

      }

      ssd1306_UpdateScreen();
      HAL_Delay(500);
  }

  /*C2 note */
  else if(frequency>= 63.56 && frequency <= 67.33){
    sprintf(note, "C2  ");
    sprintf(noteFreq, "%.2f", frequency);
    ssd1306_SetCursor(NOTEX, NOTEY);
    ssd1306_WriteString(note,Font_11x18,Black);
    ssd1306_SetCursor(FREQX,FREQY);
    ssd1306_WriteString(noteFreq,Font_11x18,Black);

    /*if in tune plus/minus 10 cents */
    if(frequency>= 65.03 && frequency <= 65.79){
      ssd1306_SetCursor(NOTEX + INTUNE, NOTEY);
      ssd1306_WriteString(dot,Font_11x18,Black);

    }

    ssd1306_UpdateScreen();
    HAL_Delay(500);
  }

  /*Db2 note */
  else if(frequency>= 67.34 && frequency <= 71.33){
    sprintf(note, "Db2  ");
    sprintf(noteFreq, "%.2f", frequency);
    ssd1306_SetCursor(NOTEX, NOTEY);
    ssd1306_WriteString(note,Font_11x18,Black);
    ssd1306_SetCursor(FREQX,FREQY);
    ssd1306_WriteString(noteFreq,Font_11x18,Black);

    /*if in tune plus/minus 10 cents */
    if(frequency>= 68.9 && frequency <= 69.7){
      ssd1306_SetCursor(NOTEX + INTUNE, NOTEY);
      ssd1306_WriteString(dot,Font_11x18,Black);

    }

    ssd1306_UpdateScreen();
    HAL_Delay(500);
  }


  /*D2 note */
  else if(frequency>= 71.34 && frequency <= 75.53){
    sprintf(note, "D2  ");
    sprintf(noteFreq, "%.2f", frequency);
    ssd1306_SetCursor(NOTEX, NOTEY);
    ssd1306_WriteString(note,Font_11x18,Black);
    ssd1306_SetCursor(FREQX,FREQY);
    ssd1306_WriteString(noteFreq,Font_11x18,Black);

    /*if in tune plus/minus 10 cents */
    if(frequency>= 68.9 && frequency <= 69.7){
      ssd1306_SetCursor(NOTEX + INTUNE, NOTEY);
      ssd1306_WriteString(dot,Font_11x18,Black);

    }

    ssd1306_UpdateScreen();
    HAL_Delay(500);
  }


  /*Eb2 note */
  else if(frequency <= 80.59 && frequency >= 75.57 ){
    sprintf(note, "Eb2  ");
    sprintf(noteFreq, "%.2f", frequency);
    ssd1306_SetCursor(NOTEX, NOTEY);
    ssd1306_WriteString(note,Font_11x18,Black);
    ssd1306_SetCursor(FREQX,FREQY);
    ssd1306_WriteString(noteFreq,Font_11x18,Black);

    /*if in tune plus/minus 10 cents */
    if(frequency>= 77.33 && frequency <= 78.23){
      ssd1306_SetCursor(NOTEX + INTUNE, NOTEY);
      ssd1306_WriteString(dot,Font_11x18,Black);

    }

    ssd1306_UpdateScreen();
    HAL_Delay(500);
  }

  /*E2 note */
  else if(frequency<=84.824 && frequency>=80.06){
    sprintf(note, "E2  ");
    sprintf(noteFreq, "%.2f", frequency);

    ssd1306_SetCursor(NOTEX, NOTEY);
    ssd1306_WriteString(note,Font_11x18,Black);
    ssd1306_SetCursor(FREQX,FREQY);
    ssd1306_WriteString(noteFreq,Font_11x18,Black);

    /*if in tune plus/minus 10 cents */
    if(frequency>= 81.93 && frequency <= 82.89){
      ssd1306_SetCursor(NOTEX + INTUNE, NOTEY);
      ssd1306_WriteString(dot,Font_11x18,Black);

    }

    ssd1306_UpdateScreen();
    HAL_Delay(500);
  }


  /*F2 note */
  else if(frequency <= 89.87 && frequency >= 84.82){
    sprintf(note, "F2  ");
    sprintf(noteFreq, "%.2f", frequency);

    ssd1306_SetCursor(NOTEX, NOTEY);
    ssd1306_WriteString(note,Font_11x18,Black);
    ssd1306_SetCursor(FREQX,FREQY);
    ssd1306_WriteString(noteFreq,Font_11x18,Black);

    /*if in tune plus/minus 10 cents */
    if(frequency>= 86.81 && frequency <= 87.81){
      ssd1306_SetCursor(NOTEX + INTUNE, NOTEY);
      ssd1306_WriteString(dot,Font_11x18,Black);

    }

    ssd1306_UpdateScreen();
    HAL_Delay(500);
  }

  /*Gb2 note */
  else if(frequency <= 95.21 && frequency >= 89.88){
    sprintf(note, "Gb2  ");
    sprintf(noteFreq, "%.2f", frequency);

    ssd1306_SetCursor(NOTEX, NOTEY);
    ssd1306_WriteString(note,Font_11x18,Black);
    ssd1306_SetCursor(FREQX,FREQY);
    ssd1306_WriteString(noteFreq,Font_11x18,Black);

    /*if in tune plus/minus 10 cents */
    if(frequency>= 91.96 && frequency <= 93.03){
      ssd1306_SetCursor(NOTEX + INTUNE, NOTEY);
      ssd1306_WriteString(dot,Font_11x18,Black);

    }

    ssd1306_UpdateScreen();
    HAL_Delay(500);
  }

  /*G2 note */
  else if(frequency <= 100.87 && frequency >= 95.22){
    sprintf(note, "G2  ");
    sprintf(noteFreq, "%.2f", frequency);

    ssd1306_SetCursor(NOTEX, NOTEY);
    ssd1306_WriteString(note,Font_11x18,Black);
    ssd1306_SetCursor(FREQX,FREQY);
    ssd1306_WriteString(noteFreq,Font_11x18,Black);

    /*if in tune plus/minus 10 cents */
    if(frequency>= 97.435 && frequency <= 98.57){
      ssd1306_SetCursor(NOTEX + INTUNE, NOTEY);
      ssd1306_WriteString(dot,Font_11x18,Black);

    }

    ssd1306_UpdateScreen();
    HAL_Delay(500);
  }

  /*Ab2 note */
  else if(frequency <= 106.873 && frequency >= 100.88){
    sprintf(note, "Ab2  ");
    sprintf(noteFreq, "%.2f", frequency);

    ssd1306_SetCursor(NOTEX, NOTEY);
    ssd1306_WriteString(note,Font_11x18,Black);
    ssd1306_SetCursor(FREQX,FREQY);
    ssd1306_WriteString(noteFreq,Font_11x18,Black);

    /*if in tune plus/minus 10 cents */
    if(frequency>= 103.23 && frequency <= 104.43){
      ssd1306_SetCursor(NOTEX + INTUNE, NOTEY);
      ssd1306_WriteString(dot,Font_11x18,Black);

    }

    ssd1306_UpdateScreen();
    HAL_Delay(500);
  }

  /*A2 note */
  else if(frequency <= 113.22 && frequency >= 106.88){
    sprintf(note, "A2  ");
    sprintf(noteFreq, "%.2f", frequency);

    ssd1306_SetCursor(NOTEX, NOTEY);
    ssd1306_WriteString(note,Font_11x18,Black);
    ssd1306_SetCursor(FREQX,FREQY);
    ssd1306_WriteString(noteFreq,Font_11x18,Black);

    /*if in tune plus/minus 10 cents */
    if(frequency>= 109.36 && frequency <= 110.64){
      ssd1306_SetCursor(NOTEX + INTUNE, NOTEY);
      ssd1306_WriteString(dot,Font_11x18,Black);

    }

    ssd1306_UpdateScreen();
    HAL_Delay(500);
  }

  /*Bb2 note */
  else if(frequency <= 119.929 && frequency >= 106.9){
    sprintf(note, "Bb2  ");
    sprintf(noteFreq, "%.2f", frequency);

    ssd1306_SetCursor(NOTEX, NOTEY);
    ssd1306_WriteString(note,Font_11x18,Black);
    ssd1306_SetCursor(FREQX,FREQY);
    ssd1306_WriteString(noteFreq,Font_11x18,Black);

    /*if in tune plus/minus 10 cents */
    if(frequency>= 115.85 && frequency <= 117.19){
      ssd1306_SetCursor(NOTEX + INTUNE, NOTEY);
      ssd1306_WriteString(dot,Font_11x18,Black);

    }

    ssd1306_UpdateScreen();
    HAL_Delay(500);
  }


  /*B2 note */
  else if(frequency <= 127.08 && frequency >= 119.93){
    sprintf(note, "B2  ");
    sprintf(noteFreq, "%.2f", frequency);

    ssd1306_SetCursor(NOTEX, NOTEY);
    ssd1306_WriteString(note,Font_11x18,Black);
    ssd1306_SetCursor(FREQX,FREQY);
    ssd1306_WriteString(noteFreq,Font_11x18,Black);

    /*if in tune plus/minus 10 cents */
    if(frequency>= 122.76 && frequency <= 124.19){
      ssd1306_SetCursor(NOTEX + INTUNE, NOTEY);
      ssd1306_WriteString(dot,Font_11x18,Black);

    }

    ssd1306_UpdateScreen();
    HAL_Delay(500);
  }

  /*C3 note */
  else if(frequency <= 134.64 && frequency >= 127.08){
    sprintf(note, "C3  ");
    sprintf(noteFreq, "%.2f", frequency);

    ssd1306_SetCursor(NOTEX, NOTEY);
    ssd1306_WriteString(note,Font_11x18,Black);
    ssd1306_SetCursor(FREQX,FREQY);
    ssd1306_WriteString(noteFreq,Font_11x18,Black);

    /*if in tune plus/minus 10 cents */
    if(frequency>= 130.05 && frequency <= 131.57){
      ssd1306_SetCursor(NOTEX + INTUNE, NOTEY);
      ssd1306_WriteString(dot,Font_11x18,Black);

    }

    ssd1306_UpdateScreen();
    HAL_Delay(500);
  }

  /*Db3 note */
  else if(frequency <= 142.65 && frequency >= 134.65){
    sprintf(note, "Db3  ");
    sprintf(noteFreq, "%.2f", frequency);

    ssd1306_SetCursor(NOTEX, NOTEY);
    ssd1306_WriteString(note,Font_11x18,Black);
    ssd1306_SetCursor(FREQX,FREQY);
    ssd1306_WriteString(noteFreq,Font_11x18,Black);

    /*if in tune plus/minus 10 cents */
    if(frequency>= 137.79 && frequency <= 139.39){
      ssd1306_SetCursor(NOTEX + INTUNE, NOTEY);
      ssd1306_WriteString(dot,Font_11x18,Black);

    }

    ssd1306_UpdateScreen();
    HAL_Delay(500);
  }

  /* D3 note */
  else if(frequency <= 151.13 && frequency >= 142.65){
    sprintf(note, "D3  ");
    sprintf(noteFreq, "%.2f", frequency);

    ssd1306_SetCursor(NOTEX, NOTEY);
    ssd1306_WriteString(note,Font_11x18,Black);
    ssd1306_SetCursor(FREQX,FREQY);
    ssd1306_WriteString(noteFreq,Font_11x18,Black);

    /*if in tune plus/minus 10 cents */
    if(frequency>= 145.98 && frequency <= 147.68){
      ssd1306_SetCursor(NOTEX + INTUNE, NOTEY);
      ssd1306_WriteString(dot,Font_11x18,Black);

    }



    ssd1306_UpdateScreen();
    HAL_Delay(500);
  }

  /*Eb3 note */
  else if(frequency <= 160.11 && frequency >= 151.14){
    sprintf(note, "Eb3  ");
    sprintf(noteFreq, "%.2f", frequency);

    ssd1306_SetCursor(NOTEX, NOTEY);
    ssd1306_WriteString(note,Font_11x18,Black);
    ssd1306_SetCursor(FREQX,FREQY);
    ssd1306_WriteString(noteFreq,Font_11x18,Black);

    /*if in tune plus/minus 10 cents */
    if(frequency>= 154.66 && frequency <= 156.46){
      ssd1306_SetCursor(NOTEX + INTUNE, NOTEY);
      ssd1306_WriteString(dot,Font_11x18,Black);

    }

    ssd1306_UpdateScreen();
    HAL_Delay(500);
  }

  /*E3 note */
  else if(frequency <= 169.64 && frequency >= 160.12){
    sprintf(note, "E3  ");
    sprintf(noteFreq, "%.2f", frequency);

    ssd1306_SetCursor(NOTEX, NOTEY);
    ssd1306_WriteString(note,Font_11x18,Black);
    ssd1306_SetCursor(FREQX,FREQY);
    ssd1306_WriteString(noteFreq,Font_11x18,Black);

    /*if in tune plus/minus 10 cents */
    if(frequency>= 163.86 && frequency <= 165.76){
      ssd1306_SetCursor(NOTEX + INTUNE, NOTEY);
      ssd1306_WriteString(dot,Font_11x18,Black);

    }

    ssd1306_UpdateScreen();
    HAL_Delay(500);
  }

  /*F3 note */
  else if(frequency <= 180.76 && frequency >= 169.65){
    sprintf(note, "F3  ");
    sprintf(noteFreq, "%.2f", frequency);

    ssd1306_SetCursor(NOTEX, NOTEY);
    ssd1306_WriteString(note,Font_11x18,Black);
    ssd1306_SetCursor(FREQX,FREQY);
    ssd1306_WriteString(noteFreq,Font_11x18,Black);

    /*if in tune plus/minus 10 cents */
    if(frequency>= 174.59 && frequency <= 176.63){
      ssd1306_SetCursor(NOTEX + INTUNE, NOTEY);
      ssd1306_WriteString(dot,Font_11x18,Black);

    }

    ssd1306_UpdateScreen();
    HAL_Delay(500);
  }

  /*Gb3 note */
  else if(frequency <= 190.42 && frequency >= 180.76){
    sprintf(note, "Gb3  ");
    sprintf(noteFreq, "%.2f", frequency);

    ssd1306_SetCursor(NOTEX, NOTEY);
    ssd1306_WriteString(note,Font_11x18,Black);
    ssd1306_SetCursor(FREQX,FREQY);
    ssd1306_WriteString(noteFreq,Font_11x18,Black);

    /*if in tune plus/minus 10 cents */
    if(frequency>= 183.93 && frequency <= 186.07){
      ssd1306_SetCursor(NOTEX + INTUNE, NOTEY);
      ssd1306_WriteString(dot,Font_11x18,Black);

    }

    ssd1306_UpdateScreen();
    HAL_Delay(500);
  }

  /*G3 note */
  else if(frequency <= 201.76 && frequency >= 190.42){
    sprintf(note, "G3  ");
    sprintf(noteFreq, "%.2f", frequency);

    ssd1306_SetCursor(NOTEX, NOTEY);
    ssd1306_WriteString(note,Font_11x18,Black);
    ssd1306_SetCursor(FREQX,FREQY);
    ssd1306_WriteString(noteFreq,Font_11x18,Black);

    /*if in tune plus/minus 10 cents */
    if(frequency>= 194.87 && frequency <= 197.14){
      ssd1306_SetCursor(NOTEX + INTUNE, NOTEY);
      ssd1306_WriteString(dot,Font_11x18,Black);

    }

    ssd1306_UpdateScreen();
    HAL_Delay(500);
  }

  /*Ab3 note */
  else if(frequency <= 213.73 && frequency >= 226.45){
    sprintf(note, "Ab3  ");
    sprintf(noteFreq, "%.2f", frequency);

    ssd1306_SetCursor(NOTEX, NOTEY);
    ssd1306_WriteString(note,Font_11x18,Black);
    ssd1306_SetCursor(FREQX,FREQY);
    ssd1306_WriteString(noteFreq,Font_11x18,Black);

    /*if in tune plus/minus 10 cents */
    if(frequency>= 206.45 && frequency <= 208.85){
      ssd1306_SetCursor(NOTEX + INTUNE, NOTEY);
      ssd1306_WriteString(dot,Font_11x18,Black);

    }

    ssd1306_UpdateScreen();
    HAL_Delay(500);
  }

  /*A3 note */
  else if(frequency <= 226.45 && frequency >= 213.74){
    sprintf(note, "A3  ");
    sprintf(noteFreq, "%.2f", frequency);

    ssd1306_SetCursor(NOTEX, NOTEY);
    ssd1306_WriteString(note,Font_11x18,Black);
    ssd1306_SetCursor(FREQX,FREQY);
    ssd1306_WriteString(noteFreq,Font_11x18,Black);

    /*if in tune plus/minus 10 cents */
    if(frequency>= 218.73 && frequency <= 221.27){
      ssd1306_SetCursor(NOTEX + INTUNE, NOTEY);
      ssd1306_WriteString(dot,Font_11x18,Black);

    }

    ssd1306_UpdateScreen();
    HAL_Delay(500);
  }

  /*Bb3 note */
  else if(frequency <= 239.91 && frequency >= 226.46){
    sprintf(note, "Bb3  ");
    sprintf(noteFreq, "%.2f", frequency);

    ssd1306_SetCursor(NOTEX, NOTEY);
    ssd1306_WriteString(note,Font_11x18,Black);
    ssd1306_SetCursor(FREQX,FREQY);
    ssd1306_WriteString(noteFreq,Font_11x18,Black);

    /*if in tune plus/minus 10 cents */
    if(frequency>= 231.73 && frequency <= 234.43){
      ssd1306_SetCursor(NOTEX + INTUNE, NOTEY);
      ssd1306_WriteString(dot,Font_11x18,Black);

    }

    ssd1306_UpdateScreen();
    HAL_Delay(500);
  }

  /*B3 note */
  else if(frequency <= 254.18 && frequency >= 239.92){
    sprintf(note, "B3  ");
    sprintf(noteFreq, "%.2f", frequency);

    ssd1306_SetCursor(NOTEX, NOTEY);
    ssd1306_WriteString(note,Font_11x18,Black);
    ssd1306_SetCursor(FREQX,FREQY);
    ssd1306_WriteString(noteFreq,Font_11x18,Black);

    /*if in tune plus/minus 10 cents */
    if(frequency>= 245.52 && frequency <= 248.37){
      ssd1306_SetCursor(NOTEX + INTUNE, NOTEY);
      ssd1306_WriteString(dot,Font_11x18,Black);

    }

    ssd1306_UpdateScreen();
    HAL_Delay(500);
  }

  /*C4 note */
  else if(frequency <= 269.29 && frequency >= 254.19){
    sprintf(note, "C4  ");
    sprintf(noteFreq, "%.2f", frequency);

    ssd1306_SetCursor(NOTEX, NOTEY);
    ssd1306_WriteString(note,Font_11x18,Black);
    ssd1306_SetCursor(FREQX,FREQY);
    ssd1306_WriteString(noteFreq,Font_11x18,Black);

    /*if in tune plus/minus 10 cents */
    if(frequency>= 260.12 && frequency <= 263.15){
      ssd1306_SetCursor(NOTEX + INTUNE, NOTEY);
      ssd1306_WriteString(dot,Font_11x18,Black);

    }

    ssd1306_UpdateScreen();
    HAL_Delay(500);
  }

  /*Db4 note */
  else if(frequency <= 285.3 && frequency >= 269.29){
    sprintf(note, "Db4  ");
    sprintf(noteFreq, "%.2f", frequency);

    ssd1306_SetCursor(NOTEX, NOTEY);
    ssd1306_WriteString(note,Font_11x18,Black);
    ssd1306_SetCursor(FREQX,FREQY);
    ssd1306_WriteString(noteFreq,Font_11x18,Black);

    /*if in tune plus/minus 10 cents */
    if(frequency>= 275.59 && frequency <= 278.78){
      ssd1306_SetCursor(NOTEX + INTUNE, NOTEY);
      ssd1306_WriteString(dot,Font_11x18,Black);

    }

    ssd1306_UpdateScreen();
    HAL_Delay(500);
  }

  /*D4 note */
  else if(frequency <= 302.26 && frequency >= 285.31){
    sprintf(note, "D4  ");
    sprintf(noteFreq, "%.2f", frequency);

    ssd1306_SetCursor(NOTEX, NOTEY);
    ssd1306_WriteString(note,Font_11x18,Black);
    ssd1306_SetCursor(FREQX,FREQY);
    ssd1306_WriteString(noteFreq,Font_11x18,Black);

    /*if in tune plus/minus 10 cents */
    if(frequency>= 291.97 && frequency <= 295.36){
      ssd1306_SetCursor(NOTEX + INTUNE, NOTEY);
      ssd1306_WriteString(dot,Font_11x18,Black);

    }

    ssd1306_UpdateScreen();
    HAL_Delay(500);
  }

  /*Eb4 note */
  else if(frequency <= 320.25 && frequency >= 392.27){
    sprintf(note, "Eb4  ");
    sprintf(noteFreq, "%.2f", frequency);

    ssd1306_SetCursor(NOTEX, NOTEY);
    ssd1306_WriteString(note,Font_11x18,Black);
    ssd1306_SetCursor(FREQX,FREQY);
    ssd1306_WriteString(noteFreq,Font_11x18,Black);

    /*if in tune plus/minus 10 cents */
    if(frequency>= 309.34 && frequency <= 312.93){
      ssd1306_SetCursor(NOTEX + INTUNE, NOTEY);
      ssd1306_WriteString(dot,Font_11x18,Black);

    }

    ssd1306_UpdateScreen();
    HAL_Delay(500);
  }

  /*E4 note */
  else if(frequency <= 339.29 && frequency >= 320.26){
    sprintf(note, "E4  ");
    sprintf(noteFreq, "%.2f", frequency);

    ssd1306_SetCursor(NOTEX, NOTEY);
    ssd1306_WriteString(note,Font_11x18,Black);
    ssd1306_SetCursor(FREQX,FREQY);
    ssd1306_WriteString(noteFreq,Font_11x18,Black);

    /*if in tune plus/minus 10 cents */
    if(frequency>= 327.73 && frequency <= 331.54){
      ssd1306_SetCursor(NOTEX + INTUNE, NOTEY);
      ssd1306_WriteString(dot,Font_11x18,Black);

    }

    ssd1306_UpdateScreen();
    HAL_Delay(500);
  }

  /*F4 note */
  else if(frequency <= 359.46 && frequency >= 339.30){
    sprintf(note, "F4  ");
    sprintf(noteFreq, "%.2f", frequency);

    ssd1306_SetCursor(NOTEX, NOTEY);
    ssd1306_WriteString(note,Font_11x18,Black);
    ssd1306_SetCursor(FREQX,FREQY);
    ssd1306_WriteString(noteFreq,Font_11x18,Black);

    /*if in tune plus/minus 10 cents */
    if(frequency>= 347.22 && frequency <= 351.25){
      ssd1306_SetCursor(NOTEX + INTUNE, NOTEY);
      ssd1306_WriteString(dot,Font_11x18,Black);

    }

    ssd1306_UpdateScreen();
    HAL_Delay(500);
  }

  /*Gb4 note */
  else if(frequency <= 380.83 && frequency >= 359.47){
    sprintf(note, "Gb4  ");
    sprintf(noteFreq, "%.2f", frequency);

    ssd1306_SetCursor(NOTEX, NOTEY);
    ssd1306_WriteString(note,Font_11x18,Black);
    ssd1306_SetCursor(FREQX,FREQY);
    ssd1306_WriteString(noteFreq,Font_11x18,Black);

    /*if in tune plus/minus 10 cents */
    if(frequency>= 367.86 && frequency <= 372.13){
      ssd1306_SetCursor(NOTEX + INTUNE, NOTEY);
      ssd1306_WriteString(dot,Font_11x18,Black);

    }

    ssd1306_UpdateScreen();
    HAL_Delay(500);
  }


  /*G4 note */
  else if(frequency <= 403.49 && frequency >= 380.83){
    sprintf(note, "G4  ");
    sprintf(noteFreq, "%4.2f", frequency);

    ssd1306_SetCursor(NOTEX, NOTEY);
    ssd1306_WriteString(note,Font_11x18,Black);
    ssd1306_SetCursor(FREQX,FREQY);
    ssd1306_WriteString(noteFreq,Font_11x18,Black);

    /*if in tune plus/minus 10 cents */
    if(frequency>= 389.74 && frequency <= 394.27){
      ssd1306_SetCursor(NOTEX + INTUNE, NOTEY);
      ssd1306_WriteString(dot,Font_11x18,Black);

    }

    ssd1306_UpdateScreen();
    HAL_Delay(500);
  }




  /*Ab4 note */
  else if(frequency >= 403.50 && frequency <= 427.56){
    sprintf(note, "Ab4  ");
    sprintf(noteFreq, "%.2f", frequency);

    ssd1306_SetCursor(NOTEX, NOTEY);
    ssd1306_WriteString(note,Font_11x18,Black);
    ssd1306_SetCursor(FREQX,FREQY);
    ssd1306_WriteString(noteFreq,Font_11x18,Black);

    /*if in tune plus/minus 10 cents */
    if(frequency>= 412.99 && frequency <= 417.79){
      ssd1306_SetCursor(NOTEX + INTUNE, NOTEY);
      ssd1306_WriteString(dot,Font_11x18,Black);

    }

    ssd1306_UpdateScreen();
    HAL_Delay(500);
  }

  /*A4 note */
  else if(frequency <= 452.89 && frequency >= 427.57){
    sprintf(note, "A4  ");
    sprintf(noteFreq, "%.2f", frequency);

    ssd1306_SetCursor(NOTEX, NOTEY);
    ssd1306_WriteString(note,Font_11x18,Black);
    ssd1306_SetCursor(FREQX,FREQY);
    ssd1306_WriteString(noteFreq,Font_11x18,Black);

    /*if in tune plus/minus 10 cents */
    if(frequency>= 437.47 && frequency <= 442.55){
      ssd1306_SetCursor(NOTEX + INTUNE, NOTEY);
      ssd1306_WriteString(dot,Font_11x18,Black);

    }

    ssd1306_UpdateScreen();
    HAL_Delay(500);
  }

  /*Bb4 note */
  else if(frequency <= 479.82 && frequency >= 452.90){
    sprintf(note, "Bb4  ");
    sprintf(noteFreq, "%.2f", frequency);

    ssd1306_SetCursor(NOTEX, NOTEY);
    ssd1306_WriteString(note,Font_11x18,Black);
    ssd1306_SetCursor(FREQX,FREQY);
    ssd1306_WriteString(noteFreq,Font_11x18,Black);

    /*if in tune plus/minus 10 cents */
    if(frequency>= 463.48 && frequency <= 468.86){
      ssd1306_SetCursor(NOTEX + INTUNE, NOTEY);
      ssd1306_WriteString(dot,Font_11x18,Black);

    }

    ssd1306_UpdateScreen();
    HAL_Delay(500);
  }

  else{
    sprintf(note, "NULL");
    sprintf(noteFreq, "%.2f", frequency);

    ssd1306_SetCursor(NOTEX, NOTEY);
    ssd1306_WriteString(note,Font_11x18,Black);
    ssd1306_SetCursor(FREQX,FREQY);
    ssd1306_WriteString(noteFreq,Font_11x18,Black);

    ssd1306_UpdateScreen();
    HAL_Delay(500);

  }
/*end note detect */
}


void print2Screen(float frequency, char *note, char *noteFreq)
{

    findNote(frequency);
    ssd1306_SetCursor(FREQX,FREQY);
    ssd1306_WriteString(note,Font_11x18,Black);
    ssd1306_SetCursor(NOTEX,NOTEY);
    ssd1306_WriteString(noteFreq,Font_11x18,Black);

    ssd1306_UpdateScreen();
    HAL_Delay(500);
}
