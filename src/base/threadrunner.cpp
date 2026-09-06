#include "threadrunner.h"

#include <QDebug>

ThreadRunner::ThreadRunner(QObject *parent) : QObject(parent) {
    this->JobDone = true;
}

void ThreadRunner::runInThread(std::function<void()> func) {
    if(!this->JobDone) {
        qDebug() << "Faild to start new job in worker (" << this << "). Worker still didn't finish the job!";
        return;
    }

    this->JobDone = false;
    QThread *thread = QThread::create([=]() {
        func();
        this->JobDone = true;
        emit jobFinished();
    });
    thread->start();
}
