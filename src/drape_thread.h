#pragma once

//------------------------------------------------------------------------------
// includes.
//------------------------------------------------------------------------------

#include <QThread>
#include <QWaitCondition>
#include <QMutex>

//------------------------------------------------------------------------------
// class declaration.
//------------------------------------------------------------------------------

class DrapeThread : public QThread
{
    Q_OBJECT

public:

    DrapeThread();
    ~DrapeThread();

signals:

protected:

    /**
     * The contents of the run() method are what runs on a separate thread and
     * it shares resources defined in the QThread class.
     */
    void run();

private:
};
