#include <QCoreApplication>

#include "parser.h"

#include <memory>

int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);

    const QString testDir = "/data/Programs/SpellViewer/Code/muddled-manticore/";

    auto parser = std::make_unique<Java::Parser>();
    parser->parse(testDir);

    return a.exec();
}
