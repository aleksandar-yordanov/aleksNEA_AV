#pragma once

#include <QWidget>

namespace Ui {
class resetWindow;
}

class resetWindow : public QWidget
{
    Q_OBJECT

public:
    explicit resetWindow(QWidget *parent = nullptr);
    ~resetWindow();

private:
    Ui::resetWindow *ui;
};

