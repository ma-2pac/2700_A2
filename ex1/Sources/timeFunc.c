#include <hidef.h>      /* common defines and macros */
#include "derivative.h"      /* derivative-specific definitions */

#include "timers.h"

/* Takes inputs for function to run and datatype to use
  funcs:     0 = add, 1 = mult, 2 = divide, 3 = sqrt,  4 = sin, 5 = cos
  datatypes: 0 = int, 1 = long, 2 = float,  3 = double
  returns number of clock cycles elapsed (accounting for timer overflow interrupt routine overhead)
  */
  

long timeFunc(int func, int datatype){
  unsigned int time1, time2;
  long time;
  long OFticks = 65536;
  int OFinterruptTicks = 24;
  
  // switch statement for datatype
  switch(datatype){
    case 0:{
      // create volatile integers for use by math operations
      volatile int ai, bi, ci;
      ai = 10;
      bi = 5;
      // switch statement for math operatio
      switch(func){
        case 0:{
          resetOF();    // reset overflow counter
          time1 = TCNT; // save initial time
          ci = bi + ai; // run function
          time2 = TCNT; // save final time
          // compute time elapsed
          time = (time2 - time1) + (overFlows * OFticks) - (overFlows * OFinterruptTicks);
        break;
        }
        
        case 1:{
          resetOF();
          time1 = TCNT;
          ci = bi * ai;
          time2 = TCNT;
          time = (time2 - time1) + (overFlows * OFticks) - (overFlows * OFinterruptTicks);
        break;
        }
        
        case 2:{
          resetOF();
          time1 = TCNT;
          ci = bi / ai;
          time2 = TCNT;
          time = (time2 - time1) + (overFlows * OFticks) - (overFlows * OFinterruptTicks);
        break;
        }
        
        case 3:{
          resetOF();
          time1 = TCNT;
          ci = sqrt(ai);
          time2 = TCNT;
          time = (time2 - time1) + (overFlows * OFticks) - (overFlows * OFinterruptTicks);
        break;
        }
        
        case 4:{
          resetOF();
          time1 = TCNT;
          ci = sin(ai);
          time2 = TCNT;
          time = (time2 - time1) + (overFlows * OFticks) - (overFlows * OFinterruptTicks);
        break;
        }
        
        case 5:{
          resetOF();
          time1 = TCNT;
          ci = cos(ai);
          time2 = TCNT;
          time = (time2 - time1) + (overFlows * OFticks) - (overFlows * OFinterruptTicks);
        break;
        }
      }
      break;
    }
    
    case 1:{
      volatile long al, bl, cl;
      al = 154;
      bl = 503;
      switch(func){
    
        case 0:{
          resetOF();
          time1 = TCNT;
          cl = bl + al;
          time2 = TCNT;
          time = (time2 - time1) + (overFlows * OFticks) - (overFlows * OFinterruptTicks);
        break;
        }
        
        case 1:{
          resetOF();
          time1 = TCNT;
          cl = bl * al;
          time2 = TCNT;
          time = (time2 - time1) + (overFlows * OFticks) - (overFlows * OFinterruptTicks);
        break;
        }
        
        case 2:{
          resetOF();
          time1 = TCNT;
          cl = bl / al;
          time2 = TCNT;
          time = (time2 - time1) + (overFlows * OFticks) - (overFlows * OFinterruptTicks);
        break;
        }
        
        case 3:{
          resetOF();
          time1 = TCNT;
          cl = sqrt(al);
          time2 = TCNT;
          time = (time2 - time1) + (overFlows * OFticks) - (overFlows * OFinterruptTicks);
        break;
        }
        
        case 4:{
          resetOF();
          time1 = TCNT;
          cl = sin(al);
          time2 = TCNT;
          time = (time2 - time1) + (overFlows * OFticks) - (overFlows * OFinterruptTicks);
        break;
        }
        
        case 5:{
          resetOF();
          time1 = TCNT;
          cl = cos(al);
          time2 = TCNT;
          time = (time2 - time1) + (overFlows * OFticks) - (overFlows * OFinterruptTicks);
        break;
        }
      } 
    break;
    }
    
    case 2:{
      volatile float af, bf, cf;
      af = 536.34;
      bf = 214.52;
      switch(func){
    
        case 0:{
          resetOF();
          time1 = TCNT;
          cf = bf + af;
          time2 = TCNT;
          time = (time2 - time1) + (overFlows * OFticks) - (overFlows * OFinterruptTicks);
        break;
        }
        
        case 1:{
          resetOF();
          time1 = TCNT;
          cf = bf * af;
          time2 = TCNT;
          time = (time2 - time1) + (overFlows * OFticks) - (overFlows * OFinterruptTicks);
        break;
        }
        
        case 2:{
          resetOF();
          time1 = TCNT;
          cf = bf / af;
          time2 = TCNT;
          time = (time2 - time1) + (overFlows * OFticks) - (overFlows * OFinterruptTicks);
        break;
        }
        
        case 3:{
          resetOF();
          time1 = TCNT;
          cf = sqrt(af);
          time2 = TCNT;
          time = (time2 - time1) + (overFlows * OFticks) - (overFlows * OFinterruptTicks);
        break;
        }
        
        case 4:{
          resetOF();
          time1 = TCNT;
          cf = sin(af);
          time2 = TCNT;
          time = (time2 - time1) + (overFlows * OFticks) - (overFlows * OFinterruptTicks);
        break;
        }
        
        case 5:{
          resetOF();
          time1 = TCNT;
          cf = cos(af);
          time2 = TCNT;
          time = (time2 - time1) + (overFlows * OFticks) - (overFlows * OFinterruptTicks);
        break;
        }
      }
    break;
    }
    
    case 3:{
      double ad, bd, cd;
      ad = 135.532;
      bd = 63.8539;
      switch(func){
    
        case 0:{
          resetOF();
          time1 = TCNT;
          cd = bd + ad;
          time2 = TCNT;
          time = (time2 - time1) + (overFlows * OFticks) - (overFlows * OFinterruptTicks);
        break;
        }
        
        case 1:{
          resetOF();
          time1 = TCNT;
          cd = bd * ad;
          time2 = TCNT;
          time = (time2 - time1) + (overFlows * OFticks) - (overFlows * OFinterruptTicks);
        break;
        }
        
        case 2:{
          resetOF();
          time1 = TCNT;
          cd = bd / ad;
          time2 = TCNT;
          time = (time2 - time1) + (overFlows * OFticks) - (overFlows * OFinterruptTicks);
        break;
        }
        
        case 3:{
          resetOF();
          time1 = TCNT;
          cd = sqrt(ad);
          time2 = TCNT;
          time = (time2 - time1) + (overFlows * OFticks) - (overFlows * OFinterruptTicks);
        break;
        }
        
        case 4:{
          resetOF();
          time1 = TCNT;
          cd = sin(ad);
          time2 = TCNT;
          time = (time2 - time1) + (overFlows * OFticks) - (overFlows * OFinterruptTicks);
        break;
        }
        
        case 5:{
          resetOF();
          time1 = TCNT;
          cd = cos(ad);
          time2 = TCNT;
          time = (time2 - time1) + (overFlows * OFticks) - (overFlows * OFinterruptTicks);
        break;
        }
      }
    break;
    }
  }
  // return time (ticks) elapsed by function
  return time;
  
}