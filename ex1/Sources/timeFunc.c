#include <hidef.h>      /* common defines and macros */
#include <math.h>
#include "derivative.h"      /* derivative-specific definitions */

#include "timers.h"
#include "timeFunc.h"


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
  
  
  switch(datatype){
    
    case 0:{
      int a = 10;
      int b = 5;
      int c;
      switch(func){
    
        case 0:{
          resetOF();
          time1 = TCNT;
          c = b + a;
          time2 = TCNT;
          time = (time2 - time1) + (overFlows * OFticks) - (overFlows * OFinterruptTicks);
          break;
        }
        
        case 1:{
          resetOF();
          time1 = TCNT;
          c = b * a;
          time2 = TCNT;
          time = (time2 - time1) + (overFlows * OFticks) - (overFlows * OFinterruptTicks);
          break;
        }
        
        case 2:{
          resetOF();
          time1 = TCNT;
          c = b / a;
          time2 = TCNT;
          time = (time2 - time1) + (overFlows * OFticks) - (overFlows * OFinterruptTicks);
          break;
        }
        
        case 3:{
          resetOF();
          time1 = TCNT;
          c = sqrt(a);
          time2 = TCNT;
          time = (time2 - time1) + (overFlows * OFticks) - (overFlows * OFinterruptTicks);
          break;
        }
        
        case 4:{
          resetOF();
          time1 = TCNT;
          c = sin(a);
          time2 = TCNT;
          time = (time2 - time1) + (overFlows * OFticks) - (overFlows * OFinterruptTicks);
          break;
        }
        
        case 5:{
          resetOF();
          time1 = TCNT;
          c = cos(a);
          time2 = TCNT;
          time = (time2 - time1) + (overFlows * OFticks) - (overFlows * OFinterruptTicks);
          break;
        }
        default:
          break;
      }
      break;
    }
    
    case 1:{
      long a, b, c;
      a = 154;
      b = 503;
      switch(func){
    
        case 0:{
          resetOF();
          time1 = TCNT;
          c = b + a;
          time2 = TCNT;
          time = (time2 - time1) + (overFlows * OFticks) - (overFlows * OFinterruptTicks);
        break;
        }
        
        case 1:{
          resetOF();
          time1 = TCNT;
          c = b * a;
          time2 = TCNT;
          time = (time2 - time1) + (overFlows * OFticks) - (overFlows * OFinterruptTicks);
        break;
        }
        
        case 2:{
          resetOF();
          time1 = TCNT;
          c = b / a;
          time2 = TCNT;
          time = (time2 - time1) + (overFlows * OFticks) - (overFlows * OFinterruptTicks);
        break;
        }
        
        case 3:{
          resetOF();
          time1 = TCNT;
          c = sqrt(a);
          time2 = TCNT;
          time = (time2 - time1) + (overFlows * OFticks) - (overFlows * OFinterruptTicks);
        break;
        }
        
        case 4:{
          resetOF();
          time1 = TCNT;
          c = sin(a);
          time2 = TCNT;
          time = (time2 - time1) + (overFlows * OFticks) - (overFlows * OFinterruptTicks);
        break;
        }
        
        case 5:{
          resetOF();
          time1 = TCNT;
          c = cos(a);
          time2 = TCNT;
          time = (time2 - time1) + (overFlows * OFticks) - (overFlows * OFinterruptTicks);
        break;
        }
        
        default:
          break;
        
      } 
    break;
    }
    
    case 2:{
      float a, b, c;
      a = 536.34;
      b = 214.52;
      switch(func){
    
        case 0:{
          resetOF();
          time1 = TCNT;
          c = b + a;
          time2 = TCNT;
          time = (time2 - time1) + (overFlows * OFticks) - (overFlows * OFinterruptTicks);
        break;
        }
        
        case 1:{
          resetOF();
          time1 = TCNT;
          c = b * a;
          time2 = TCNT;
          time = (time2 - time1) + (overFlows * OFticks) - (overFlows * OFinterruptTicks);
        break;
        }
        
        case 2:{
          resetOF();
          time1 = TCNT;
          c = b / a;
          time2 = TCNT;
          time = (time2 - time1) + (overFlows * OFticks) - (overFlows * OFinterruptTicks);
        break;
        }
        
        case 3:{
          resetOF();
          time1 = TCNT;
          c = sqrt(a);
          time2 = TCNT;
          time = (time2 - time1) + (overFlows * OFticks) - (overFlows * OFinterruptTicks);
        break;
        }
        
        case 4:{
          resetOF();
          time1 = TCNT;
          c = sin(a);
          time2 = TCNT;
          time = (time2 - time1) + (overFlows * OFticks) - (overFlows * OFinterruptTicks);
        break;
        }
        
        case 5:{
          resetOF();
          time1 = TCNT;
          c = cos(a);
          time2 = TCNT;
          time = (time2 - time1) + (overFlows * OFticks) - (overFlows * OFinterruptTicks);
        break;
        }
      }
    break;
    }
    
    case 3:{
      double a, b, c;
      a = 135.532;
      b = 63.8539;
      switch(func){
    
        case 0:{
          resetOF();
          time1 = TCNT;
          c = b + a;
          time2 = TCNT;
          time = (time2 - time1) + (overFlows * OFticks) - (overFlows * OFinterruptTicks);
        break;
        }
        
        case 1:{
          resetOF();
          time1 = TCNT;
          c = b * a;
          time2 = TCNT;
          time = (time2 - time1) + (overFlows * OFticks) - (overFlows * OFinterruptTicks);
        break;
        }
        
        case 2:{
          resetOF();
          time1 = TCNT;
          c = b / a;
          time2 = TCNT;
          time = (time2 - time1) + (overFlows * OFticks) - (overFlows * OFinterruptTicks);
        break;
        }
        
        case 3:{
          resetOF();
          time1 = TCNT;
          c = sqrt(a);
          time2 = TCNT;
          time = (time2 - time1) + (overFlows * OFticks) - (overFlows * OFinterruptTicks);
        break;
        }
        
        case 4:{
          resetOF();
          time1 = TCNT;
          c = sin(a);
          time2 = TCNT;
          time = (time2 - time1) + (overFlows * OFticks) - (overFlows * OFinterruptTicks);
        break;
        }
        
        case 5:{
          resetOF();
          time1 = TCNT;
          c = cos(a);
          time2 = TCNT;
          time = (time2 - time1) + (overFlows * OFticks) - (overFlows * OFinterruptTicks);
        break;
        }
      }
    break;
    }
  }
  
  return time;
  
}