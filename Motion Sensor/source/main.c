/* MotionSensor - an application for the Pololu 3pi Robot
 *
 * This application uses the Pololu AVR C/C++ Library.  For help, see:
 * -User's guide: http://www.pololu.com/docs/0J20
 * -Command reference: http://www.pololu.com/docs/0J18
 *
 * Created: 4/10/2014 7:26:40 PM
 *  Author: Ashwini
 */

#include <pololu/3pi.h>


// Introductory messages. The "PROGMEM" identifier causes the data to
// go into program space.
const char welcome_line1[] PROGMEM = " Digtal";
const char welcome_line2[] PROGMEM = " Hathi";
const char name_line1[] PROGMEM = " Power";
const char name_line2[] PROGMEM = "rpthegeek.com";

// A couple of simple tunes, stored in program space.
const char welcome[] PROGMEM = ">g32>>c32";
const char go[] PROGMEM = "L16 cdegreg4";
// Refresh the LCD display every tenth of a second.
const int display_interval_ms = 100;
#define MS_ELAPSED_IS(n) (get_ms() % n == 0)
#define TIME_TO_DISPLAY (MS_ELAPSED_IS(display_interval_ms))

#define THRESHOLD 100
#define SPEED 180

#define REVERSE_SPEED(n) (-1 * n)
int direction = 1;

void initialize()
{
// Set PC5 as an input with internal pull-up disabled
DDRC &= ~(1<< PORTC5);
PORTC &= ~(1<< PORTC5);
// Play welcome music and display a message
print_from_program_space(welcome_line1);
lcd_goto_xy(0,1);
print_from_program_space(welcome_line2);
play_from_program_space(welcome);
delay_ms(1000);
clear();
print_from_program_space(name_line1);
lcd_goto_xy(0,1);
print_from_program_space(name_line2);
delay_ms(1000);
// Display battery voltage and wait for button press
while(!button_is_pressed(BUTTON_B))
{
clear();
print_long(read_battery_millivolts());
print("mV");
lcd_goto_xy(0,1);
print("Press B");
delay_ms(100);
}
// Always wait for the button to be released so that 3pi doesn't
// start moving until your hand is away from it.
wait_for_button_release(BUTTON_B);
clear();
print("Go!");
// Play music and wait for it to finish before we start driving.
play_from_program_space(go);
while(is_playing());
}
void back_up()
{
if (TIME_TO_DISPLAY)
{
clear();
lcd_goto_xy(0,0);
print("Backing");
lcd_goto_xy(0,1);
print("Up");
}
// Back up slightly to the left
set_motors(-50,-90);
}
void turn_in_place() {
if (TIME_TO_DISPLAY) {
clear();
lcd_goto_xy(0,0);
print("Front");
lcd_goto_xy(0,1);
print("Obstacle");
}
// Turn to the right in place
set_motors(50, -50);
}

int motion_detected() {
int proximity1 = analog_read(7);
int proximity2 = analog_read(5);
//Test
return proximity1 >= proximity2 ? proximity1 : proximity2;
/*
if(proximity > THRESHOLD){
return 1;
}
return 0;*/
}

void move_robot() {
//Run
if(direction){
//direction = 0;
set_motors(SPEED, SPEED);	
}else{
//direction = 1;
set_motors(REVERSE_SPEED(SPEED), REVERSE_SPEED(SPEED));
}
}

void stop_robot() {
//stop
int deacclerate = 100;
if(direction){
direction = 0;
set_motors(140, 140);
delay_ms(deacclerate);
set_motors(100, 100);
delay_ms(deacclerate);
set_motors(50, 50);
delay_ms(deacclerate);
set_motors(0, 0);
}else{
direction = 1;
set_motors(REVERSE_SPEED(140), REVERSE_SPEED(140));
delay_ms(deacclerate);
set_motors(REVERSE_SPEED(100), REVERSE_SPEED(100));
delay_ms(deacclerate);
set_motors(REVERSE_SPEED(50), REVERSE_SPEED(50));
delay_ms(deacclerate);
set_motors(0, 0);
}
//delay_ms(5000);
}

int main()
{
// set up the 3pi
initialize();

// This is the "main loop" - it will run forever.
while(1)
{	
int motion = motion_detected(); //485
if(motion > 350){
move_robot();
delay_ms(500);
stop_robot();
}	
if (TIME_TO_DISPLAY) {
clear();
lcd_goto_xy(0,0);
print_long(motion);
}
}
// This part of the code is never reached. A robot should
// never reach the end of its program, or unpredictable behavior
// will result as random code starts getting executed. If you
// really want to stop all actions at some point, set your motors
// to 0,0 and run the following command to loop forever:
//
// while(1);
}


/*
int main()
{
play_from_program_space(PSTR(">g32>>c32"));  // Play welcoming notes.

while(1)
{
// Print battery voltage (in mV) on the LCD.
clear();
print_long(read_battery_millivolts_3pi());

red_led(1);     // Turn on the red LED.
delay_ms(200);  // Wait for 200 ms.

red_led(0);     // Turn off the red LED.
delay_ms(200);  // Wait for 200 ms.
}
} */