#include "money.h"

QMoney::QMoney() {}

QMoney::QMoney(const QMoney &other)
{
    m_sign = other.m_sign;
    m_money = other.m_money;
    m_percent = other.m_percent;
}

QMoney::QMoney(const QString &moneyStr)
{
    fromString(moneyStr);
}

QMoney::QMoney(const char *moneyStr)
{
    fromString(QString(moneyStr));
}

QMoney::QMoney(int money)
{
    if (money >= 0)
    {
        this->m_money = money;
    }
    else
    {
        m_sign = false;
        this->m_money = -money;
    }
}

QMoney::QMoney(double money)
{
    fromSingleNumber(qRound64(money * 10000));
}

QMoney &QMoney::operator =(const QMoney &m1)
{
    m_sign = m1.m_sign;
    m_money = m1.m_money;
    m_percent = m1.m_percent;
    return *this;
}

QMoney &QMoney::operator =(const QString &m1)
{
    fromString(m1);
    return *this;
}

QMoney QMoney::operator +(const QMoney &m1)
{
    QMoney m(*this);
    m.summ(m1);
    return m;
}

QMoney QMoney::operator +=(const QMoney &m1)
{
    summ(m1);
    return *this;
}

QMoney QMoney::operator -=(const QMoney &m1)
{
    substract(m1);
    return *this;
}

QMoney QMoney::operator -(const QMoney &m1)
{
    QMoney m(*this);
    m.substract(m1);
    return m;
}

QMoney::operator QByteArray() const
{
    QByteArray result = (m_sign ? "" : "-") + QByteArray::number(m_money);
    if (m_percent > 0)
    {
        result.append("." + QByteArray::number(m_percent).rightJustified(4, '0'));
        while (result.endsWith('0')) result.chop(1);
    }

    return result;
}

void QMoney::fromSingleNumber(qint64 number)
{
    m_sign = number >= 0;
    if (!m_sign) number = -number;
    m_money = number / 10000;
    m_percent = number % 10000;
}

void QMoney::fromString(QString moneyStr)
{
    QRegExp moneyExp {"-?[0-9]+[.,]?[0-9]{0,4}"};
    if (moneyExp.exactMatch(moneyStr))
    {
        if (moneyStr.startsWith('-'))
        {
            m_sign = false;
            moneyStr.remove(0, 1);
        }
        if (moneyStr.contains(','))
        {
            m_money = moneyStr.split(',').first().toInt();
            m_percent = moneyStr.split(',').last().leftJustified(4, '0').toUInt();
        }
        else if (moneyStr.contains('.'))
        {
            m_money = moneyStr.split('.').first().toInt();
            m_percent = moneyStr.split('.').last().leftJustified(4, '0').toUInt();
        }
        else
        {
            m_money = moneyStr.toInt();
        }
    }
}

void QMoney::summ(const QMoney &m1)
{
    qint64 res = this->inSingleNumber() + m1.inSingleNumber();

    fromSingleNumber(res);

    // money += m1.money;
    // percent += m1.percent;
    // if (percent > 99)
    // {
    //     int addedRubles = percent / 100;
    //     money += addedRubles;
    //     percent -= addedRubles * 100;
    // }
}

void QMoney::substract(const QMoney &m1)
{
    qint64 res = this->inSingleNumber() - m1.inSingleNumber();

    fromSingleNumber(res);
}
