#include "gui.h"

GxEPD2_DISPLAY_CLASS<GxEPD2_DRIVER_CLASS, MAX_HEIGHT(GxEPD2_DRIVER_CLASS)> display(GxEPD2_DRIVER_CLASS(/*CS=5*/ EPD_CS, /*DC=*/ 17, /*RST=*/ 16, /*BUSY=*/ 4)); // my suggested wiring and proto board

// initialize display
void init_gui(){
  display.init(115200, true, 2, false); // USE THIS for Waveshare boards with "clever" reset circuit, 2ms reset pulse
  display.setRotation(1);
  display.setFont(&FreeMonoBold9pt7b);
  display.setTextColor(GxEPD_BLACK);
  gui_main_menu();
  display.hibernate();
}

// test display
void gui_main_menu()
{
  const char main_menu_txt[] = "E-ink Pomodoro Timer";
  int16_t tbx, tby; uint16_t tbw, tbh;
  display.getTextBounds(main_menu_txt, 0, 0, &tbx, &tby, &tbw, &tbh);

  // center top
  uint16_t x = ((display.width() - tbw) / 2) - tbx;
  uint16_t y = tbh; 

  display.setPartialWindow(0, 0, display.width(), display.height());
  display.firstPage();
  do
  {
    display.fillScreen(GxEPD_WHITE);
    display.setCursor(x, y);
    display.print(main_menu_txt);
  }
  while (display.nextPage());
}

void gui_time(int seconds){ //TODO: This function can be very optimized 

  int minutes = (seconds/60) % 60;
  int hours = seconds/3600;
  /*  
  int remaining = seconds % 60; //for seconds display
  */

  std::ostringstream oss;
  oss << std::setw(2) << std::setfill('0') << hours << ":" << std::setw(2) << std::setfill('0') << minutes; //  << ":"  << std::setfill('0') << remaining; 
  std::string formattedTime = oss.str();
  Serial.println(formattedTime.c_str());
  
  // TODO: make these MACROS!
  int16_t tbx, tby; uint16_t tbw, tbh;
  display.getTextBounds(String(formattedTime.c_str()), 0, 0, &tbx, &tby, &tbw, &tbh);
  uint16_t x = ((display.width() - tbw) / 2) - tbx;
  uint16_t y = ((display.height() - tbh) / 2) - tby;
  display.setPartialWindow(x,y-tbh/2,tbw+3,tbh);
  do
  { 
    display.fillScreen(GxEPD_WHITE);
    display.setCursor(x, y);
    display.print(String(formattedTime.c_str()));
  }
  while (display.nextPage());

}

void goodbye(){
  const char main_menu_txt[] = "E-ink Pomodoro Timer";
  int16_t tbx, tby; uint16_t tbw, tbh;
  display.getTextBounds(main_menu_txt, 0, 0, &tbx, &tby, &tbw, &tbh);
  // center the bounding box by transposition of the origin:
  uint16_t x = ((display.width() - tbw) / 2) - tbx;
  uint16_t y = ((display.height() - tbh) / 2) - tby;
  const char Goodbye[] = "Goodbye!";
  display.setPartialWindow(x,y-tbh/2,tbw+1,tbh);
  do
  { 
    display.setCursor(x, y);
    display.print(Goodbye);
  }
  while (display.nextPage());
  Serial.println("End of Goodbye");
}