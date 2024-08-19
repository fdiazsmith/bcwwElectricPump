#pragma once

#if BOARD_DFROBOT

const int PIN_HALL_SENSOR1 = 25;
const int PIN_HALL_SENSOR2 = 26;
const int PIN_MOTOR_DIR = 13;
const int PIN_MOTOR_STEP = 14;

#elif BOARD_FERN

const int PIN_HALL_SENSOR1 = 39; // NFC_MISO
const int PIN_HALL_SENSOR2 = 40; // NFC_MOSI
const int PIN_MOTOR_DIR = 18;
const int PIN_MOTOR_STEP = 8;
const int PIN_BUTTON = 12;

#endif