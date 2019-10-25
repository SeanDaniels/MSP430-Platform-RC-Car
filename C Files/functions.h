//******************************************************************************
//
//  Description: This file contains the Function prototypes
//
//  Sean Daniels
//  Spring 2019
//  Built with IAR Embedded Workbench
//******************************************************************************
// Functions

// Initialization
void Init_Conditions(void);

// Interrupts
void enable_interrupts(void);
__interrupt void Timer0_B0_ISR(void);
__interrupt void switch_interruptTwo(void);
__interrupt void switch_interruptOne(void);

// Analog to Digital Converter

// Clocks
void Init_Clocks(void);

// LED Configurations
void Init_LEDs(void);
void IR_LED_control(char selection);
void Backlite_control(char selection);

  // LCD
void Display_Process(void);
void Display_Update(char p_L1,char p_L2,char p_L3,char p_L4);
void enable_display_update(void);
void update_string(char *string_data, int string);
void Init_LCD(void);
void lcd_clear(void);
void lcd_putc(char c);
void lcd_puts(char *s);
void update_display_function(char* string1, char* string2, char* string3, char* string4);

void lcd_power_on(void);
void lcd_write_line1(void);
void lcd_write_line2(void);
//void lcd_draw_time_page(void);
//void lcd_power_off(void);
void lcd_enter_sleep(void);
void lcd_exit_sleep(void);
//void lcd_write(unsigned char c);
//void out_lcd(unsigned char c);

void Write_LCD_Ins(char instruction);
void Write_LCD_Data(char data);
void ClrDisplay(void);
void ClrDisplay_Buffer_0(void);
void ClrDisplay_Buffer_1(void);
void ClrDisplay_Buffer_2(void);
void ClrDisplay_Buffer_3(void);

void SetPostion(char pos);
void DisplayOnOff(char data);
void lcd_BIG_mid(void);
void lcd_4line(void);
void lcd_out(char *s, char line, char position);
void lcd_rotate(char view);

//void lcd_write(char data, char command);
void lcd_write(unsigned char c);
void lcd_write_line1(void);
void lcd_write_line2(void);
void lcd_write_line3(void);

void lcd_command( char data);
void LCD_test(void);
void LCD_iot_meassage_print(int nema_index);

// Menu
void Menu_Process(void);

// Ports
void Init_Ports(int num1);
void Init_Port1(void);
void Init_Port2(void);
void Init_Port3(int num1);
void Init_Port4(void);
void Init_Port5(void);
void Init_Port6(void);

// SPI
void Init_SPI_B1(void);
void SPI_B1_write(char byte);
void spi_rs_data(void);
void spi_rs_command(void);
void spi_LCD_idle(void);
void spi_LCD_active(void);
void SPI_test(void);
void WriteIns(char instruction);
void WriteData(char data);

// Switches
void Init_Switches(void);
void switch_control(void);
void enable_switch_SW1(void);
void enable_switch_SW2(void);
void disable_switch_SW1(void);
void disable_switch_SW2(void);
void Switches_Process(void);
void Init_Switch(void);
void Switch_Process(void);
void Switch1_Process(void);
void Switch2_Process(void);
void menu_act(void);
void menu_select(void);

// Timers
void Init_Timers(void);
void Init_Timer_B0(void);
void Init_Timer_B1(void);
void Init_Timer_B2(void);
void Init_Timer_B3(void);

void usleep(unsigned int usec);
void usleep10(unsigned int usec);
void five_msec_sleep(unsigned int msec);
void measure_delay(void);
void out_control_words(void);

//shapes

void end_case(void);
void Forward_On(void);
void Forward_Off(void);
void Do_Nothing(void);
void run_figEight(void);
void wait_caseTwo(void);
void turn_sixty(void);
void run_Tri(void);
void go_straight(void);
void start_case_tri(void);

//switch interrupt function
void interrupt_switch(void);

//IR and Thumbwheel functions
void Hex_To_Binary(volatile unsigned int ValuePassedT);
void Init_ADC(void);
void Thumb_Read_Out(void);
void L_Read_Out(void);
void R_Read_Out(void);
void Read_Outs(void);


void initial_display_update(void);
void Init_IR(void);
void Total_Stop(void);
void Car_Loc(void);
void Stop_At_Line(void);
void Look_For_Line(void);
void Start_Rot_Left(void);
void Look_Right(void);
void Start_Forward(void);
void Travel_CCW(void);
void Move_And_Test(void);
void Stay_On(void);
void clock_update(void);
void LCD_UPDATE(int line, int starting_point);


//line follow functions
void display_for_calibrate(void);
void set_white_vals(void);
void prompt_user_to_reset(void);
void calibrate_white(void);
void calibrate_black(void);
void clear_display_and_prepare_for_lift_off(void);
void display_for_lift_off(void);
void display_for_prep(void);
void clear_display(void);
void setup_timer(void);
void set_black_vals(void);
void calibrate_left_transition(void);
void calibrate_left_transition(void);
void set_trans_vals(void);
void turn_in(void);
void stop_at_middle(void);


void Init_Serial_UCA0(char BAUD);
void Init_Serial_UCA1(char BAUD);
void display_one(void);
void low_baud_process(void);
void pass_message(void);
void copy_message(void);
void display_two(void);
void display_initial(void);
void high_baud_process(void);
void clear_line_one(void);
void out_character(char character);
void out_string(char* mess);
void change_baud(void);
void display_low_baud(void);
void display_high_baud(void);
void display_recieved(void);
void clear_string(void);
void tot_message_recd(void);
void transmission_process(void);
void transmission_display_update(void);
void clear_transmit_message(void);
void clear_line_four(void);
void char_by_char(void);
void iot_action(void);

//iot functions
void check_ip(void);
void display_ip(void);
void display_ssid(void);
int check_key(void);
void parse_command(void);
void direction_duration(char direction);

void move_forward(void);
void move_backwards(void);
void Start_Reverse(void);
void Reverse_On(void);
void Stop_After_Time(char duration);
void turn_left(void);


void Start_Rot_Right(void);
void Travel_CW(void);
void turn_right(void);
void calibrate_test(char test_cond);
void calibrate_pwm(void);
void setup_IOT(void);
void og_IOT_display(void);
void movement_display(void);
void PWM_display(char cond);
void display_station(char station);
void display_success(void);
void black_line_time(void);
void final_out(void);
 void line_approach_setup(void);
 void BL_display(char cond);
 void end_case_bl(void);
 void DISABLE_MOTORS(void);
 void command_handle(void);
void ir_action(void);
void BL_Pause(char time);