#pragma once
#include <string>

enum Python_mode {
	PYTHON_MODE_163MUSIC,
    PYTHON_MODE_VTB,
    PYTHON_MODE_BT,
    PYTHON_MODE_COM,
    PYTHON_MODE_MOVIE,
    PYTHON_MODE_CHATGTP
};
typedef enum Python_mode Py_mode;

enum  Python_mode_Status_code {
    WEB_NOT_FIND = -4,
    FILE_NOT_FIND,
    INS_NULL,
    BILI_INS_WRONG,
    EXECUT_SEUCCESS,
    PYTHON_END
};
typedef enum Python_mode_Status_code PY_Status_code;

#define _isInsNULL_(str,post) (str.size() == post+1) ? 0 : 1

PY_Status_code Python_main(enum Python_mode, std::string Instructions);