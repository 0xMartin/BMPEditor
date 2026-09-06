#include "threadrunner.h"

#include <QDebug>

ThreadRunner::ThreadRunner(QObject *parent) : QObject(parent) {
    this->JobDone = true;
}

void ThreadRunner::runInThread(std::function<void()> func) {
    if(!this->JobDone) {
        qDebug() << "Failed to start new job in worker (" << this << "). Worker still didn't finish the job!";
        emit jobRejected();
        return;
    }

    this->JobDone = false;
    QThread *thread = QThread::create([=]() {
        func();
        this->JobDone = true;
        emit jobFinished();
    });
    // vlakno se po dokonceni sameuvolni (jinak by kazde spusteni operace unikalo pamet)
    connect(thread, &QThread::finished, thread, &QThread::deleteLater);
    thread->start();
}
