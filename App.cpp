#include "solve.h"
#include "App.h"

App::App(int width, int height) {
    number_ = "";

    window_ = new QMainWindow();
    window_->setFixedSize(width, height);
    window_->setStyleSheet("QMainWindow {"
                           "background: #fadcea }");

    num_edit_ = new QLineEdit(window_);
    num_edit_->resize(550, 30);
    num_edit_->move(25, 15);
    num_edit_->setStyleSheet("QLineEdit { background: #f6afd1;"
                             "color: #555555;"
                             "border-radius: 5px;"
                             "opacity: 1; }");
    num_edit_->setPlaceholderText("Number");

    converted_num_ = new QLabel(window_);
    converted_num_->resize(550, 30);
    converted_num_->move(25, 65);
    converted_num_->setStyleSheet("QLabel { background: #62213f;"
                                  "color: #f1f0f1;"
                                  "border-radius: 5px;"
                                  "padding-left: 0.5px; }");
    converted_num_->setText("Converted number");

    base_edit_ = new QLineEdit(window_);
    base_edit_->resize(150, 30);
    base_edit_->move(25, 115);
    base_edit_->setStyleSheet("QLineEdit { background: #e77b9e;"
                              "color: #555555;"
                              "border-radius: 5px; }");
    base_edit_->setPlaceholderText("Source system");

    target_base_edit_ = new QLineEdit(window_);
    target_base_edit_->resize(150, 30);
    target_base_edit_->move(200, 115);
    target_base_edit_->setStyleSheet("QLineEdit { background: #facee3;"
                                     "color: #555555;"
                                     "border-radius: 5px; }");
    target_base_edit_->setPlaceholderText("Target system");

    convert_ = new QPushButton(window_);
    convert_->resize(200, 40);
    convert_->move(375, 110);
    convert_->setStyleSheet("QPushButton { color: #ffffff;"
                            "background: #404040;"
                            "border-radius: 5px; }");
    convert_->setText("Convert");
    connect(convert_, SIGNAL (released()), this, SLOT (convertNumber()));

    save_button_ = new QPushButton(window_);
    save_button_->move(25, 150);
    save_button_->resize(100, 40);
    save_button_->setStyleSheet("QPushButton { color: #ffffff;"
                                "background: #404040;"
                                "border-radius: 5px; }");
    save_button_->setText("Save to");
    connect(save_button_, SIGNAL (released()), this, SLOT (saveToFile()));

    load_button_ = new QPushButton(window_);
    load_button_->move(140, 150);
    load_button_->resize(100, 40);
    load_button_->setStyleSheet("QPushButton { color: #ffffff;"
                                "background: #404040;"
                                "border-radius: 5px; }");
    load_button_->setText("Download from");
    connect(load_button_, SIGNAL (released()), this, SLOT (loadFromFile()));
}

App::~App() {
    delete load_button_;
    delete save_button_;
    delete window_;
    delete base_edit_;
    delete target_base_edit_;
    delete num_edit_;
    delete convert_;
    delete header_container_;
}

int toNum(const std::string& str) {
    int n = 0;
    for (char c : str) {
        n = n * 10 + c - '0';
    }
    return n;
}

int toNum(char c) {
    if (c <= '9') {
        return c - '0';
    }

    return c - 'a' + 10;
}

bool isGood(const std::string& number, int base) {
    std::string let;
    bool bracket = false;
    for (char c : number) {
        if (c == '.' || c == '(' || c == ')' || c == ',') continue;
        if (c == '[') {
            bracket = true;
            continue;
        }
        if (c == ']') {
            bracket = false;
            int num = toNum(let);
            let.clear();
            if (num >= base) {
                return false;
            }
            continue;
        }
        if (bracket) {
            let.push_back(c);
        } else if (toNum(c) >= base) {
            return false;
        }
    }
    return true;
}

void App::convertNumber() {
    std::string number = num_edit_->text().toStdString();
    int base = base_edit_->text().toInt();
    int target = target_base_edit_->text().toInt();
    if (!isGood(number, base) || base > 255 || target > 255 ||
    base < 2 || target < 2){
        converted_num_->setText(QString::fromStdString("Uncorrected number"));
        return;
    }
    std::string a, b, c;
    int i = 0;
    for (; i < number.size(); ++i) {
        if (number[i] == '.') {
            break;
        }
        a.push_back(number[i]);
    }
    ++i;
    for (; i < number.size(); ++i) {
        if (number[i] == '(') {
            break;
        }
        b.push_back(number[i]);
    }
    ++i;
    for (; i < number.size(); ++i) {
        if (number[i] == ')') {
            break;
        }
        c.push_back(number[i]);
    }
    number_ = solve(a, b, c, base, target);
    converted_num_->setText(QString::fromStdString(number_));
}

void App::saveToFile() {
    QString file = QFileDialog::getSaveFileName(nullptr, "Save to", "", "*.txt");
    QFile outFile(file);
    if (!outFile.open(QIODevice::WriteOnly)) return;
    QTextStream ostream(&outFile);
    ostream << QString::fromStdString(number_);
    outFile.close();
}

void App::loadFromFile() {
    num_edit_->clear();
    QString file = QFileDialog::getOpenFileName(nullptr, "Choose txt file", "", "*.txt");
    QFile in(file);
    if (!in.open(QIODevice::ReadOnly)) return;
    QString data = in.readLine();
    in.close();
    if (data.isEmpty()) return;
    num_edit_->setText(data);
}