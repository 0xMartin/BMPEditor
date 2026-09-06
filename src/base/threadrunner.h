#ifndef THREADRUNNER_H
#define THREADRUNNER_H

#include <QThread>
#include <functional>
#include <atomic>

class ThreadRunner : public QObject {
    Q_OBJECT
public:
    std::atomic<bool> JobDone;

    explicit ThreadRunner(QObject *parent = nullptr);

    void runInThread(std::function<void()> func);

signals:
    void jobFinished();
    // vyvolano pokud je pozadavek na spusteni operace zamitnut, protoze predchozi jeste bezi
    void jobRejected();
};
#endif // THREADRUNNER_H
