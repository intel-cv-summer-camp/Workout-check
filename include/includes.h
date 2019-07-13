#pragma once

//сперва инклюды в угловых скобках
#include <stdint.h>
#include <iostream>
#include <opencv2/imgproc.hpp>
#include <opencv2/highgui.hpp>
#include <string>
#include <time.h>
#include <SFML/Graphics.hpp>

//затем в кавычках, иначе будут ошибки
#include "estimationbase.h"
#include "estimated.h"
#include "filter.h"
#include "detectedobject.h"
#include "timer.h"