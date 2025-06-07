#ifndef INPUT_H
#define INPUT_H

#include "config.h"

// Forward declaration
struct AppState;

// Input initialization
void initButtons();

// Button handling functions
void handleButtons(AppState* state);
void handleUp(AppState* state);
void handleDown(AppState* state);
void handleLeft(AppState* state);
void handleRight(AppState* state);
void handleCenter(AppState* state);
void handleKeyboardInput(AppState* state);

#endif