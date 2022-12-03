#ifndef ESP32_CAMERA_CPP_H_
#define ESP32_CAMERA_CPP_H_

#include <esp_camera.h>
#include "camera_config.h"

class Camera
{
public:
    Camera();

    bool begin();

    camera_fb_t *capture();

    void free(camera_fb_t *fb);

    sensor_t *sensor();

private:
    camera_config_t config_;
};

#endif
