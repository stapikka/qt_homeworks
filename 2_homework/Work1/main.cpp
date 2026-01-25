#include <QCoreApplication>
#include <QNetworkAccessManager>
#include <QSqlDatabase>

int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);

    QNetworkAccessManager networkManager;

    QSqlDatabase database = QSqlDatabase::addDatabase("QSQLITE");


    return 0;
}
