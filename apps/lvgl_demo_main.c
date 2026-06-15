/**
 * @file lvgl_demo_main.c
 *
 * LVGL demo application entry point.
 * Usage:
 *   bazel run //:lvgl_demo              -- run default demo (widgets)
 *   bazel run //:lvgl_demo -- widgets   -- widgets demo
 *   bazel run //:lvgl_demo -- music     -- music player demo
 *   bazel run //:lvgl_demo -- stress    -- stress test
 *   bazel run //:lvgl_demo -- benchmark -- rendering benchmark
 *   bazel run //:lvgl_demo -- keypad    -- keypad/encoder demo
 *   bazel run //:lvgl_demo -- vector    -- vector graphics demo
 *   bazel run //:lvgl_demo -- render    -- render test
 *   bazel run //:lvgl_demo -- gltf      -- 3D glTF viewer
 */

#define SDL_MAIN_HANDLED
#include "lvgl.h"
#include "demos/lv_demos.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define HOR_RES 800
#define VER_RES 480

int main(int argc, char * argv[])
{
    lv_init();

    /* Create SDL display and input devices */
    lv_display_t * disp = lv_sdl_window_create(HOR_RES, VER_RES);
    lv_sdl_window_set_title(disp, "LVGL Demo");

    lv_indev_t * mouse = lv_sdl_mouse_create();
    lv_indev_t * keyboard = lv_sdl_keyboard_create();
    lv_indev_t * mousewheel = lv_sdl_mousewheel_create();
    (void)mouse;
    (void)keyboard;
    (void)mousewheel;

    /* Select demo from command-line args, default to "widgets" */
    if(argc > 1) {
        if(strcmp(argv[1], "--help") == 0 || strcmp(argv[1], "-h") == 0) {
            lv_demos_show_help();
            lv_deinit();
            return 0;
        }
        if(!lv_demos_create(&argv[1], argc - 1)) {
            fprintf(stderr, "Unknown demo: %s\n", argv[1]);
            lv_demos_show_help();
            lv_deinit();
            return 1;
        }
    }
    else {
        char * args[] = {"widgets"};
        lv_demos_create(args, 1);
    }

    /* Main loop */
    while(1) {
        uint32_t delay = lv_timer_handler();
        if(delay < 1) delay = 1;
        lv_delay_ms(delay);
    }

    lv_deinit();
    return 0;
}
