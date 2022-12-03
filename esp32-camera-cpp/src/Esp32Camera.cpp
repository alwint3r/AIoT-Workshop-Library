#include "Esp32Camera.h"
#include <Arduino.h>

Camera::Camera()
{
    config_.ledc_channel = LEDC_CHANNEL_0;
    config_.ledc_timer = LEDC_TIMER_0;
    config_.pin_d0 = Y2_GPIO_NUM;
    config_.pin_d1 = Y3_GPIO_NUM;
    config_.pin_d2 = Y4_GPIO_NUM;
    config_.pin_d3 = Y5_GPIO_NUM;
    config_.pin_d4 = Y6_GPIO_NUM;
    config_.pin_d5 = Y7_GPIO_NUM;
    config_.pin_d6 = Y8_GPIO_NUM;
    config_.pin_d7 = Y9_GPIO_NUM;
    config_.pin_xclk = XCLK_GPIO_NUM;
    config_.pin_pclk = PCLK_GPIO_NUM;
    config_.pin_vsync = VSYNC_GPIO_NUM;
    config_.pin_href = HREF_GPIO_NUM;
    config_.pin_sccb_sda = SIOD_GPIO_NUM;
    config_.pin_sccb_scl = SIOC_GPIO_NUM;
    config_.pin_pwdn = PWDN_GPIO_NUM;
    config_.pin_reset = RESET_GPIO_NUM;
    config_.xclk_freq_hz = 20000000;
    config_.frame_size = FRAMESIZE_UXGA;
    config_.pixel_format = PIXFORMAT_JPEG;
    config_.grab_mode = CAMERA_GRAB_LATEST;
    config_.fb_location = CAMERA_FB_IN_PSRAM;
    config_.jpeg_quality = 10;
    config_.fb_count = 2;
}

sensor_t *Camera::sensor()
{
    return esp_camera_sensor_get();
}

bool Camera::begin()
{
    esp_err_t err = esp_camera_init(&config_);
    if (err != ESP_OK)
    {
        log_e("Failed init camera. Error: %d, %s", (int)err, esp_err_to_name(err));
        return false;
    }

    sensor_t *s = esp_camera_sensor_get();
    // initial sensors are flipped vertically and colors are a bit saturated
    log_i("Camera sensor PID: %d\r\n", (int)s->id.PID);
    if (s->id.PID == OV3660_PID)
    {
        s->set_vflip(s, 1);       // flip it back
        s->set_brightness(s, 1);  // up the brightness just a bit
        s->set_saturation(s, -2); // lower the saturation
    }
    else if (s->id.PID == OV2640_PID)
    {
        s->set_vflip(s, 1);
        s->set_brightness(s, 1);
    }

    // drop down frame size for higher initial frame rate
    if (config_.pixel_format == PIXFORMAT_JPEG)
    {
        s->set_framesize(s, FRAMESIZE_QVGA);
    }

    return true;
}

camera_fb_t *Camera::capture()
{
    return esp_camera_fb_get();
}

void Camera::free(camera_fb_t *fb)
{
    esp_camera_fb_return(fb);
}
