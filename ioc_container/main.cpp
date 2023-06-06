#include <QCoreApplication>
#include <iostream>
#include "processor.h"

void configureComputer(std::shared_ptr<IProcessor> processor) {
    auto computer = new Computer(processor);
    std::cout << computer->getInfo().toStdString() << std::endl;
    delete computer;
}

int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);

    IOCContainer injector;

    injector.RegisterInstance<IProcessor, AMDProcessor>();
    injector.GetObject<IProcessor>()->setProcessor(3.6, ProcessorType::x64, "Ryzen 5 3600");

    configureComputer(injector.GetObject<IProcessor>());

    injector.RegisterInstance<IProcessor, IntelProcessor>();
    injector.GetObject<IProcessor>()->setProcessor(4.7, ProcessorType::x86, "Intel Core i7 6700k");

    configureComputer(injector.GetObject<IProcessor>());

    return a.exec();
}
