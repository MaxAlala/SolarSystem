#ifndef TESTER_H
#define TESTER_H

#include <QObject>
#include <QThread>
class tester : public QThread
{
    Q_OBJECT
public:
    explicit tester(QObject *parent = nullptr);

signals:

public slots:
};

#endif // TESTER_H
