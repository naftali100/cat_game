#pragma once
#ifndef CONFIG_H
#define CONFIG_H

#define BOARD_SIZE 11

#define LEVEL_MIN 4
#define LEVEL_MAX 14

// ==============================
// settings
#define WIN_SIZE_X 850
#define WIN_SIZE_Y 700

#define FPS 60

#if defined(_WIN32) || defined(__CYGWIN__)
// windows
#define FONT_PATH "C:/Windows/Fonts/Arial.ttf"
#elif defined(__linux__)
// Linux
#define FONT_PATH "/usr/share/fonts/noto/NotoSansMono-Regular.ttf"
#endif

#endif