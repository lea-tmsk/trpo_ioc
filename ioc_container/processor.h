#ifndef PROCESSOR_H
#define PROCESSOR_H
#include "IOC_Contaner.h"
#include <QString>
#include <QMetaEnum>

enum ProcessorType {
    x86,
    x64
};

QString getProcessorType(ProcessorType type) {
    switch (type) {
        case ProcessorType::x64:
            return "x64";
        break;

        case ProcessorType::x86:
            return "x86";
            break;
    }
    return "";
};


class IProcessor {
public:
    virtual ~IProcessor() {};
    virtual QString getProcessorInfo() = 0;
    virtual void setProcessor(double speed, ProcessorType type, QString version) = 0;
};

class AMDProcessor : public IProcessor {
public:
    AMDProcessor() {};

    void setProcessor(double speed, ProcessorType type, QString version) override {
        m_speed = speed;
        m_type = type;
        m_version = version;
    }

    QString getProcessorInfo() override {
        return "AMD " + getProcessorType(m_type) + " processor "
                + m_version + " with clock rate of " + QString::number(m_speed) + " GHz";
    }

private:
    double m_speed;
    ProcessorType m_type;
    QString m_version;
};

class IntelProcessor : public IProcessor {
public:
    IntelProcessor() {};

    void setProcessor(double speed, ProcessorType type, QString version) override {
        m_speed = speed;
        m_type = type;
        m_version = version;
    }

    QString getProcessorInfo() override {
        return "Intel " + getProcessorType(m_type) + " processor "
                + m_version + " with clock rate of " + QString::number(m_speed) + " GHz";
    }

private:
    double m_speed;
    ProcessorType m_type;
    QString m_version;
};

class Computer {
public:
    Computer() {};
    Computer(std::shared_ptr<IProcessor> processor) {
        m_processor = processor;
    }

    void setProcessor(std::shared_ptr<IProcessor> processor) {
        m_processor = processor;
    }

    QString getInfo() {
        if (m_processor != nullptr) {
            return m_processor->getProcessorInfo();
        } else {
            return "No processor";
        }
    }

private:
    std::shared_ptr<IProcessor> m_processor;
};

#endif // PROCESSOR_H
