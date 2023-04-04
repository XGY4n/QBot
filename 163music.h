#pragma once
#include <iostream>
#include<string>
#include "Python_main.h"
void check_music(std::string Instructions);

PY_Status_code Python_music_main(std::string musicID);

PY_Status_code Python_bt_main(std::string message);

PY_Status_code Python_com_main(std::string message);

PY_Status_code Python_movie_main(std::string message);