#pragma once
//Platform specific includes
#ifdef __APPLE__
#include <unistd.h>
#include <sys/types.h>
#include <sys/kernel.h>
#include <pwd.h>
#elif _WIN32
#inclide <windows.h>
#include <tlhelp32.h>
#include <shlobj.h>
#include <psapi.h>
#include <platform.h>
#include <winsvc.h>
#endif

//Standard Library includes
#include <fstream>
#include <vector>
#include <iostream>
#include <regex>
#include <mutex>
#include <math.h>
#include <algorithm>
#include <thread>
#include <memory>
#include <thread>
#include <mutex>
#include <deque>
#include <optional>
#include <algorithm>
#include <chrono>
#include <cstdint>
#include <string>
#include <cstring>

//QT related includes
#include <QWidget>
#include <QGraphicsScene>
#include <QPixmap>
#include <QtCharts>
#include <QBitmap>
#include <QPointer>
#include <QMainWindow>
#include <QApplication>
#include <QString>
#include <QDialog>
#include <QStandardItemModel>
#include <QCommandLineParser>
#include <QCommandLineOption>
#include <QFileSystemModel>
#include <QTableView>
#include <qtimer.h>

//Other includes
#define ASIO_STANDALONE
#include <asio.hpp>
#include <asio/ts/buffer.hpp>
#include <asio/ts/internet.hpp>
#include "common.h"
#include "nlohmann/json.hpp"
#include "errorbox.h"

//Non-include or import related expressions
using json = nlohmann::json;
