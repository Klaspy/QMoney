#ifndef MONEY_H
#define MONEY_H

#include <QRegExp>
#include <QStringList>
#include <QObject>

class QMoney
{
public:
    explicit QMoney();
    QMoney(const QMoney &other);
    QMoney(const QString &moneyStr);
    QMoney(const char *moneyStr);
    QMoney(int money);
    QMoney(double money);

    qint64 money() const {return sign() * (qint64)m_money;}

    QMoney &operator =(const QMoney &m1);
    QMoney &operator =(const QString &m1);

    QMoney operator +(const QMoney &m1);
    QMoney operator +=(const QMoney &m1);

    QMoney operator -(const QMoney &m1);
    QMoney operator -=(const QMoney &m1);

    operator QByteArray() const;

    QMoney operator -() {QMoney newM(*this); newM.m_sign = !newM.m_sign; return newM;}

    bool operator >(const int &m1) const  {return this->inSingleNumber()  > m1;}
    bool operator <(const int &m1) const  {return this->inSingleNumber()  < m1;}
    bool operator ==(const int &m1) const {return this->inSingleNumber() == m1;}
    bool operator !=(const int &m1) const {return this->inSingleNumber() != m1;}

    bool operator >(const QMoney &m1)  const {return this->inSingleNumber()  > m1.inSingleNumber();}
    bool operator <(const QMoney &m1)  const {return this->inSingleNumber()  < m1.inSingleNumber();}
    bool operator ==(const QMoney &m1) const {return this->inSingleNumber() == m1.inSingleNumber();}
    bool operator !=(const QMoney &m1) const {return this->inSingleNumber() != m1.inSingleNumber();}


private:

    uint m_money {0};
    quint16 m_percent {0};
    bool m_sign {true};
    int sign() const {return m_sign ? 1 : -1;}

    qint64 inSingleNumber() const {return sign() * ((qint64)m_money * 10000 + m_percent);}
    void fromSingleNumber(qint64 number);

    void fromString(QString moneyStr);
    void summ(const QMoney &m1);
    void substract(const QMoney &m1);
};

Q_DECLARE_METATYPE(QMoney)

#endif // MONEY_H
