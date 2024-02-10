#ifndef THREADRUNNER_H
#define THREADRUNNER_H

#include <QThread>
#include <functional>

class ThreadRunner : public QObject {
    Q_OBJECT
public:
    bool JobDone;

    explicit ThreadRunner(QObject *parent = nullptr);

    void runInThread(std::function<void()> func);

signals:
    void jobFinished();
};
#endif // THREADRUNNER_H
