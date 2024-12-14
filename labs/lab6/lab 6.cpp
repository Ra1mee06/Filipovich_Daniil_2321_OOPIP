#include <iostream>
#include <fstream>
#include <string>
#include <memory>
#include <mutex>

using namespace std;

class LogStream {
private:
    static shared_ptr<LogStream> instance; 
    static ofstream logFile;               
    static mutex logMutex;                 

    string prefix;                         

    LogStream(const string& prefix = "") : prefix(prefix) {}

public:
    static void set_log_file(const string& fileName) {
        lock_guard<mutex> lock(logMutex);
        if (logFile.is_open()) {
            logFile.close();
        }
        logFile.open(fileName, ios::app);
        if (!logFile) {
            throw runtime_error("Не удалось открыть файл для логирования.");
        }
    }

    static shared_ptr<LogStream> get_instance(const string& prefix = "") {
        lock_guard<mutex> lock(logMutex);
        if (!instance) {
            instance = shared_ptr<LogStream>(new LogStream(prefix));
        }
        instance->prefix = prefix;
        return instance;
    }

    template <typename T>
    LogStream& operator<<(const T& data) {
        lock_guard<mutex> lock(logMutex);
        if (logFile.is_open()) {
            logFile << prefix << data;
        }
        cout << prefix << data; 
        return *this;
    }

    LogStream& operator<<(ostream& (*endl)(ostream&)) {
        lock_guard<mutex> lock(logMutex);
        if (logFile.is_open()) {
            logFile << endl;
        }
        cout << endl; 
        return *this;
    }

    ~LogStream() {
        lock_guard<mutex> lock(logMutex);
        if (logFile.is_open() && instance.use_count() == 1) {
            logFile.close();
        }
    }
};

shared_ptr<LogStream> LogStream::instance = nullptr;
ofstream LogStream::logFile;
mutex LogStream::logMutex;

int f(int a) {
    auto log = LogStream::get_instance("f(): ");
    *log << "Вход: a = " << a << endl;
    int r = a * a;
    *log << "Выход: r = " << r << endl;
    return r;
}

int main() {
    setlocale(LC_ALL, "RUS");
    try {
        LogStream::set_log_file("test.log");
        auto log = LogStream::get_instance("main(): ");
        *log << "Начало программы" << endl;

        cout << "Введите число для обработки: ";
        int value;
        cin >> value;

        *log << "Вызываем функцию f() с аргументом " << value << endl;
        int result = f(value);

        *log << "Результат функции f(): " << result << endl;
        *log << "Завершение программы" << endl;
    }
    catch (const exception& ex) {
        cerr << "Ошибка: " << ex.what() << endl;
    }

    return 0;
}
