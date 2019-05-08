/* COMP2215: Task 02---MODEL ANSWER */
/* For La Fortuna board.            */


#include <avr/io.h>
#include "lcd.h"
#include <stdio.h>
#include <avr/interrupt.h>
#include "ruota.h"
#include <stdlib.h>



#define BUFFSIZE 256

void check_switches();


void init(void);
int msec = 0;
int sec = 0;
int min = 0;
int hour = 0;
int change = 1;
int run = 0;
int ypos = 42;
int update = 1;
int count = 1;
int prevtime;


void main(void) {
    init();
   	os_init();
   	os_add_task(check_switches, 100, 0);

    clear_top();
    display_string("00:00:00:00");
    clear_bottom();
   	do{
   		check_switches();
   		// Every ms the count increases, if flows over seconds or minuties then updates
   		while(run == 1){
   			my_delay_ms(10);
	   		check_switches();
	   		change = 0;
	   		msec += 1;
   			display.y = 0;
	   		display.x = (display.width / 2) - 32;
		    if(msec == 100){
		    	msec = 0;
		    	sec += 1;
		    	change = 1;
			    if(sec == 60){
			    	sec = 0;
			    	min += 1;
			    	change = 2;
			    	if(min == 60){
			    		min = 0;
			    		hour += 1;
			    		change = 3;
			    	}
			    }
			}
			// checks if it should be updating the display
			if(update == 1){
			// only updates what is necessary on the display
		    switch (change)
		    {
		    	case 0:
		    		display.x += 54;
		    		print(msec);
		    		break;
		    	case 1:
		    		display.x += 36;
		    		print(sec);
		    		display_string(":");
		    		print(msec);
		    		break;

		    	case 2:
		    		display.x += 18;
		    		print(min);
		    		display_string(":");
		    		print(sec);
		    		display_string(":");
		    		print(msec);
		    		break;

		    	case 3:
		    		print(hour);
		    		display_string(":");
				    print(min);
				    display_string(":");
				    print(sec);
				    display_string(":");
		    		print(msec);
				    break;
		    }
		}
		    
	    }
	    
	}while(1 == 1);

  
   	
   	    
}

// Checks if a button has been pressed and acts accordingly
void check_switches() {

    if (get_switch_press(_BV(SWN))) {
    	if(run == 0){
    		msec = 0;
        	sec = 0;
        	min = 0;
        	hour = 0;
        	clear_top();
        	display_string("00:00:00:00");
        	clear_bottom();
        	update = 1;
        	run = 0;
        	ypos = 42;
        	count = 1;

    	}else if (update == 1){
    		update = 0;
    	} else if (update == 0){
    		update = 1;
    		display.y = 0;
	   		display.x = (display.width / 2) - 32;
	   		print(hour);
		    display_string(":");
			print(min);
			display_string(":");
			print(sec);
			display_string(":");
		    print(msec);
    	}
       
      
    }

    if (get_switch_press(_BV(SWE))) {
      
    }

    if (get_switch_press(_BV(SWS))) {
    	if(ypos > 220)
        {
            clear_bottom();
            ypos = 42;
        }
        display.y = ypos;
        if(count < 10){
       	 	display.x = (display.width / 2) - 82; 
   	 	}else{
   	 		display.x = (display.width / 2) - 86; 
   	 	}
   	 	print(count);
        display.x = (display.width / 2) - 32; 
        print(hour);
		display_string(":");
		print(min);
		display_string(":");
		print(sec);
		display_string(":");
		print(msec);
		if(count == 1){

		}else{
		display.x = (display.width / 2) + 42;
		int differnace;
		int current;
		div_t output;
		current = ((((((hour * 60) + min) * 60) + sec) * 60) + msec);
		differnace = current - prevtime;
		int splith, splitm, splits, splitms;
		output = div(differnace, 216000);
		splith = output.quot;
		differnace = output.rem;
		output = div(differnace, 3600);
		splitm = output.quot;
		differnace = output.rem;
		output = div(differnace, 60);
		splits = output.quot;
		splitms = output.rem;

		display_string("+");
		print(splith);
		display_string(":");
		print(splitm);
		display_string(":");
		print(splits);
		display_string(":");
		print(splitms);
		}
		prevtime = ((((((hour * 60) + min) * 60) + sec) * 60) + msec);
    	ypos += 16;
        rectangle l ={0, display.width-1, ypos, ypos};
    	fill_rectangle(l, WHITE);
    	ypos += 4;
    	count += 1;

    }

    if (get_switch_press(_BV(SWW))) {
            }

    if (get_switch_press(_BV(SWC))) {
        if(run == 0){
        	run = 1;
        	update = 1;
        }else{
        	run = 0;
        }
    }
}



// Used to print out number values from 0 - 99
void print(int value) {
	switch(value){
		case 0:
			display_string("00");
			break;
		case 1:
			display_string("01");
			break;
		case 2:
			display_string("02");
			break;
		case 3:
			display_string("03");
			break;
		case 4:
			display_string("04");
			break;
		case 5:
			display_string("05");
			break;
		case 6:
			display_string("06");
			break;
		case 7:
			display_string("07");
			break;
		case 8:
			display_string("08");
			break;
		case 9:
			display_string("09");
			break;
		case 10:
			display_string("10");
			break;
		case 11:
			display_string("11");
			break;
		case 12:
			display_string("12");
			break;
		case 13:
			display_string("13");
			break;
		case 14:
			display_string("14");
			break;
		case 15:
			display_string("15");
			break;
		case 16:
			display_string("16");
			break;
		case 17:
			display_string("17");
			break;
		case 18:
			display_string("18");
			break;
		case 19:
			display_string("19");
			break;
		case 20:
			display_string("20");
			break;
		case 21:
			display_string("21");
			break;
		case 22:
			display_string("22");
			break;
		case 23:
			display_string("23");
			break;
		case 24:
			display_string("24");
			break;
		case 25:
			display_string("25");
			break;
		case 26:
			display_string("26");
			break;
		case 27:
			display_string("27");
			break;
		case 28:
			display_string("28");
			break;
		case 29:
			display_string("29");
			break;
		case 30:
			display_string("30");
			break;
		case 31:
			display_string("31");
			break;
		case 32:
			display_string("32");
			break;
		case 33:
			display_string("33");
			break;
		case 34:
			display_string("34");
			break;
		case 35:
			display_string("35");
			break;
		case 36:
			display_string("36");
			break;
		case 37:
			display_string("37");
			break;
		case 38:
			display_string("38");
			break;
		case 39:
			display_string("39");
			break;
		case 40:
			display_string("40");
			break;
		case 41:
			display_string("41");
			break;
		case 42:
			display_string("42");
			break;
		case 43:
			display_string("43");
			break;
		case 44:
			display_string("44");
			break;
		case 45:
			display_string("45");
			break;
		case 46:
			display_string("46");
			break;
		case 47:
			display_string("47");
			break;
		case 48:
			display_string("48");
			break;
		case 49:
			display_string("49");
			break;
		case 50:
			display_string("50");
			break;
		case 51:
			display_string("51");
			break;
		case 52:
			display_string("52");
			break;
		case 53:
			display_string("53");
			break;
		case 54:
			display_string("54");
			break;
		case 55:
			display_string("55");
			break;
		case 56:
			display_string("56");
			break;
		case 57:
			display_string("57");
			break;
		case 58:
			display_string("58");
			break;
		case 59:
			display_string("59");
			break;
		case 60:
			display_string("60");
			break;
		case 61:
			display_string("61");
			break;
		case 62:
			display_string("62");
			break;
		case 63:
			display_string("63");
			break;
		case 64:
			display_string("64");
			break;
		case 65:
			display_string("65");
			break;
		case 66:
			display_string("66");
			break;
		case 67:
			display_string("67");
			break;
		case 68:
			display_string("68");
			break;
		case 69:
			display_string("69");
			break;
		case 70:
			display_string("70");
			break;
		case 71:
			display_string("71");
			break;
		case 72:
			display_string("72");
			break;
		case 73:
			display_string("73");
			break;
		case 74:
			display_string("74");
			break;
		case 75:
			display_string("75");
			break;
		case 76:
			display_string("76");
			break;
		case 77:
			display_string("77");
			break;
		case 78:
			display_string("78");
			break;
		case 79:
			display_string("79");
			break;
		case 80:
			display_string("80");
			break;
		case 81:
			display_string("81");
			break;
		case 82:
			display_string("82");
			break;
		case 83:
			display_string("83");
			break;
		case 84:
			display_string("84");
			break;
		case 85:
			display_string("85");
			break;
		case 86:
			display_string("86");
			break;
		case 87:
			display_string("87");
			break;
		case 88:
			display_string("88");
			break;
		case 89:
			display_string("89");
			break;
		case 90:
			display_string("90");
			break;
		case 91:
			display_string("91");
			break;
		case 92:
			display_string("92");
			break;
		case 93:
			display_string("93");
			break;
		case 94:
			display_string("94");
			break;
		case 95:
			display_string("95");
			break;
		case 96:
			display_string("96");
			break;
		case 97:
			display_string("97");
			break;
		case 98:
			display_string("98");
			break;
		case 99:
			display_string("99");
			break;
		

	}
}


// sets up interups and clock
void init(void) {
     /* 8MHz clock, no prescaling (DS, p. 48) */
    CLKPR = (1 << CLKPCE);
    CLKPR = 0;

    
    DDRE &= ~_BV(PE4) & ~_BV(PE5);  /* Rot. Encoder inputs */
    PORTE |= _BV(PE4) | _BV(PE5);   /* Rot. Encoder pull-ups */


    /* Timer 0 for switch scan interrupt: */

    TCCR0A = _BV(WGM01);  /* CTC Mode, DS Table 14-7 */
    TCCR0B = _BV(CS01)
           | _BV(CS00);   /* Prescaler: F_CPU / 64, DS Table 14-8 */

    /* 1 ms for manual movement of rotary encoder: */
    /* 1 ms --> 1000 Hz, Formula for CTC mode from  DS 14.6.2  */
    /* Note that the formula gives the toggle frequency, which is half the interrupt frequency. */

    OCR0A = (uint8_t)(F_CPU / (64.0 * 1000) - 1);

    TIMSK0 |= _BV(OCIE0A);  /* Enable timer interrupt, DS 14.8.6  */

    init_lcd();

    
}






