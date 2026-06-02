#ifndef LOGGER_H
#define LOGGER_H

class Logger {
public:
    static void init(const char* filename);
    static void partial_log(const char* msg);
    static void log(const char* msg);
    static void log(long number);
    static void read();
private:
    Logger() = delete;

    static bool m_partial_log;
    static char* m_filename;
};


#endif // LOGGER_H