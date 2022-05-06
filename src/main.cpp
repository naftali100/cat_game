
#include <plog/Appenders/ColorConsoleAppender.h>
#include <plog/Initializers/RollingFileInitializer.h>
#include <plog/Log.h>

#include "Game.h"
//#include "../include/Game/MatrixIterator.h"
#include <SFML/Graphics.hpp>

int main() {
    // init plog
    plog::ColorConsoleAppender<plog::TxtFormatter> appiarer;
    plog::init(plog::info, &appiarer);

    Game game;
    game.run();

    return 0;
}