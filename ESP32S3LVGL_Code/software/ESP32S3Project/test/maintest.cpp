/*Using LVGL with Arduino requires some extra steps:
 *Be sure to read the docs here: https://docs.lvgl.io/master/get-started/platforms/arduino.html  */

#include <all_data.h>

/*To use the built-in examples and demos of LVGL uncomment the includes below respectively.
 *You also need to copy `lvgl/examples` to `lvgl/src/examples`. Similarly for the demos `lvgl/demos` to `lvgl/src/demos`.
 Note that the `lv_examples` library is for LVGL v7 and you shouldn't install it for this version (since LVGL v8)
 as the examples and demos are now part of the main LVGL library. */

/*Change to your screen resolution*/
static const uint16_t screenWidth  = 320;
static const uint16_t screenHeight = 240;

static lv_disp_draw_buf_t draw_buf;
static lv_color_t buf[ screenWidth * screenHeight / 10 ];

CST816S touch(3, 18, 8, 46); // sda, scl, rst, irq
TFT_eSPI tft = TFT_eSPI(screenWidth, screenHeight); /* TFT instance */

/* Display flushing */
void my_disp_flush( lv_disp_drv_t *disp_drv, const lv_area_t *area, lv_color_t *color_p )
{
    uint32_t w = ( area->x2 - area->x1 + 1 );
    uint32_t h = ( area->y2 - area->y1 + 1 );

    tft.startWrite();
    tft.setAddrWindow( area->x1, area->y1, w, h );
    tft.pushColors( ( uint16_t * )&color_p->full, w * h, true );
    tft.endWrite();

    lv_disp_flush_ready( disp_drv );
}

// /*Read the touchpad*/
void my_touchpad_read( lv_indev_drv_t * indev_driver, lv_indev_data_t * data )
{
    if (touch.available())
    {
        data->state = LV_INDEV_STATE_PR;
        /*Set the coordinates*/
        data->point.x = 320-touch.data.y;
        data->point.y = touch.data.x;
    }
    else
    {
        data->state = LV_INDEV_STATE_REL;
    }
}


void lvgl_set_init(void)
{   
    lv_init();

    tft.begin();          /* TFT init */
    touch.begin();
    tft.setRotation(3); /* Landscape orientation, flipped */

    lv_disp_draw_buf_init( &draw_buf, buf, NULL, screenWidth * screenHeight / 10 );

    /*Initialize the display*/
    static lv_disp_drv_t disp_drv;
    lv_disp_drv_init( &disp_drv );
    /*Change the following line to your display resolution*/
    disp_drv.hor_res = screenWidth;
    disp_drv.ver_res = screenHeight;
    disp_drv.flush_cb = my_disp_flush;
    disp_drv.draw_buf = &draw_buf;
    lv_disp_drv_register( &disp_drv );

    /*Initialize the (dummy) input device driver*/
    static lv_indev_drv_t indev_drv;
    lv_indev_drv_init( &indev_drv );
    indev_drv.type = LV_INDEV_TYPE_POINTER;
    indev_drv.read_cb = my_touchpad_read;
    lv_indev_drv_register( &indev_drv );
}

void lvgl_task(void *pt);
void WiFi_task(void *pt);
void music_task(void *pt);
void setup()
{ 
    Serial.begin( 115200 ); /* prepare for possible serial debug */

    // initWiFi();
    // initmic();
    initSD();
    initmusic();
    lvgl_set_init();
         
    ui_init();
    init_clear(); 

    xTaskCreatePinnedToCore(lvgl_task, "lvgl_task", 1024*6, NULL, 2, NULL, 1);
    xTaskCreatePinnedToCore(WiFi_task, "WiFi_task", 1024*5, NULL, 1, NULL, 0);
    xTaskCreatePinnedToCore(music_task, "music_task", 1024*4, NULL, 1, NULL, 0);
}

void loop()
{
    // getmic();
    // GPTtest();
    // lv_timer_handler(); 
    // delay(5);
}

void lvgl_task(void *pt)
{
    while(1)
    {
        lv_timer_handler(); 
        vTaskDelay(5);
    }
}

void WiFi_task(void *pt)
{
    while(1)
    {
        WiFiUpdate();
        get_time_weather();
        vTaskDelay(1000);
    }
}

void music_task(void *pt)
{
    while(1)
    {
        getmusic();
        vTaskDelay(5);
    }
}