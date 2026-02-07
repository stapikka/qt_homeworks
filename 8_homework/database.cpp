#include "database.h"

DataBase::DataBase(QObject *parent)
    : QObject{parent}
{

    dataBase = new QSqlDatabase();


}

DataBase::~DataBase()
{
    delete dataBase;
}

/*!
 * \brief Метод добавляет БД к экземпляру класса QSqlDataBase
 * \param driver драйвер БД
 * \param nameDB имя БД (Если отсутствует Qt задает имя по умолчанию)
 */
void DataBase::AddDataBase(QString driver, QString nameDB)
{

    *dataBase = QSqlDatabase::addDatabase(driver, nameDB);

}

/*!
 * \brief Метод подключается к БД
 * \param для удобства передаем контейнер с данными необходимыми для подключения
 * \return возвращает тип ошибки
 */
void DataBase::ConnectToDataBase(QVector<QString> data)
{

    dataBase->setHostName(data[hostName]);
    dataBase->setDatabaseName(data[dbName]);
    dataBase->setUserName(data[login]);
    dataBase->setPassword(data[pass]);
    dataBase->setPort(data[port].toInt());


    ///Тут должен быть код ДЗ


    bool status;
    status = dataBase->open( );
    emit sig_SendStatusConnection(status);

}
/*!
 * \brief Метод производит отключение от БД
 * \param Имя БД
 */
void DataBase::DisconnectFromDataBase(QString nameDb)
{

    *dataBase = QSqlDatabase::database(nameDb);
    dataBase->close();

}
/*!
 * \brief Метод формирует запрос к БД.
 * \param request - SQL запрос
 * \return
 */
void DataBase::RequestToDB(QString request)
{

    if (request == "ALL")
    {
        QSqlTableModel *model = new QSqlTableModel(nullptr, *dataBase);

        model->setTable("film");

        // Заголовки столбцов
        model->setHeaderData(1, Qt::Horizontal, "Название фильма");
        model->setHeaderData(2, Qt::Horizontal, "Описание фильма");

        model->select();

        emit sig_SendDataFromDB(
            reinterpret_cast<QTableWidget*>(model),
            requestAllFilms
            );
    }

    else
    {
        QSqlQueryModel *model = new QSqlQueryModel();

        model->setQuery(request, *dataBase);

        model->setHeaderData(0, Qt::Horizontal, "Название фильма");
        model->setHeaderData(1, Qt::Horizontal, "Описание фильма");

        emit sig_SendDataFromDB(
            reinterpret_cast<QTableWidget*>(model),
            requestComedy
            );
    }

}

/*!
 * @brief Метод возвращает последнюю ошибку БД
 */
QSqlError DataBase::GetLastError()
{
    return dataBase->lastError();
}
