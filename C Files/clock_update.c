//clock update

char one=hex_to_ascii;
char ten=hex_to_ascii;
char hundred=hex_to_ascii;
void clock_update(void){
  if(last_second_count!=second_counter){
    last_second_count = second_counter;
    one++;
    if(one==HEX_TO_ASCII_CUT){
      one = HEX_TO_ASCII;
      ten++;
      if(ten==HEX_TO_ASCII_CUT){
        ten=HEX_TO_ASCII;
        hundred++;
        if(hundred==HEX_TO_ASCII_CUT){
          hundred = HEX_TO_ASCII;
        }
      }
    }
  }
  if(second_counter>TEN){
  }
  if(second_counter>ONE){
  }

}