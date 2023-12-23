#include "header.h"

class App : public QMainWindow {
Q_OBJECT

public:
    App(int width, int height);
    ~App() override;

    void render() {
        window_->show();
    }

private slots:
    void convertNumber();
    void saveToFile();
    void loadFromFile();

private:
    QWidget* window_;
    QLabel* header_container_{};
    QLineEdit* num_edit_;
    QLineEdit* base_edit_;
    QLineEdit* target_base_edit_;
    QPushButton* convert_;
    QLabel* converted_num_;
    std::string number_;
    QPushButton* load_button_;
    QPushButton* save_button_;
};