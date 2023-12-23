#include "App.h"

int32_t main(int32_t argc, char *argv[]) {
    QApplication a(argc, argv);

    App convertor(600, 200);
    convertor.render();

    return QApplication::exec();
}
