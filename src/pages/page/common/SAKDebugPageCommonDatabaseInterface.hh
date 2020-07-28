﻿/*
 * Copyright 2018-2020 Qter(qsaker@qq.com). All rights reserved.
 *
 * The file is encoding with utf-8 (with BOM). It is a part of QtSwissArmyKnife
 * project(https://www.qsak.pro). The project is an open source project. You can
 * get the source of the project from: "https://github.com/qsak/QtSwissArmyKnife"
 * or "https://gitee.com/qsak/QtSwissArmyKnife". Also, you can join in the QQ
 * group which number is 952218522 to have a communication.
 */
#ifndef SAKDEBUGPAGECOMMONDATABASEMANAGER_HH
#define SAKDEBUGPAGECOMMONDATABASEMANAGER_HH

#include <QObject>
#include <QSqlQuery>
#include <QSqlDatabase>

#include "SAKDataStruct.hh"

class SAKDebugPage;
/// @brief If Qt has sql module, some parameters will be written to database
class SAKDebugPageCommonDatabaseInterface : public QObject
{
    Q_OBJECT
private:
    SAKDebugPageCommonDatabaseInterface(QObject *parent = Q_NULLPTR);
    ~SAKDebugPageCommonDatabaseInterface();
public:
    friend SAKDebugPage;
    static SAKDebugPageCommonDatabaseInterface *instance();

    /// @brief Auto response item record
    struct AutoResponseTable {
        QString tableName;
        struct Columns {
            QString id;
            QString name;
            QString referenceData;
            QString responseData;
            QString enable;
            QString referenceFormat;
            QString responseFormat;
            QString option;
        }columns;
    };

    // timing sent table context
    struct TimingSendingTable {
        QString tableName;
        struct Columns {
            const QString id = QString("ID");
            const QString interval = QString("Interval");
            const QString format = QString("Format");
            const QString description = QString("Description");
            const QString text = QString("Text");
        }columns;
    };

    // data preset table context
    struct DataPresetItemTable{
        QString tableName;
        struct Columns {
            const QString id = QString("ID");
            const QString format = QString("Format");
            const QString description = QString("Description");
            const QString text = QString("Text");
        }columns;
    };

    /**
     * @brief insertAutoResponseItem: Insert record
     * @param tableName: table name of database
     * @param item: Item that contains record info
     */
    void insertAutoResponseItem(QString tableName, SAKDataStruct::SAKStructAutoResponseItem item);

    /**
     * @brief selectAutoResponseItem: Query records
     * @param tableName: table name
     * @return records
     */
    QList<SAKDataStruct::SAKStructAutoResponseItem> selectAutoResponseItem(QString tableName);

    /**
     * @brief insertTimingSendingItem: Insert record to database
     * @param tableName: Target table name
     * @param item: Record item
     */
    void insertTimingSentItem(QString tableName, SAKDataStruct::SAKStructTimingSentItem item);

    /**
     * @brief selectTimingSendingItem: Query records
     * @param tableName: Table name
     * @return records
     */
    QList<SAKDataStruct::SAKStructTimingSentItem> selectTimingSentItem(QString tableName);

    /**
     * @brief insertDataPresetItem: Insert record to database
     * @param tableName: table name of database
     * @param item: item that contains information of record
     */
    void insertDataPresetItem(QString tableName, SAKDataStruct::SAKStructPresettingDataItem item);

    /**
     * @brief selectDataPresetItem: Select records
     * @param tableName: Table name
     * @return records
     */
    QList<SAKDataStruct::SAKStructPresettingDataItem> selectDataPresetItem(QString tableName);

    /**
     * @brief updateRecord: Update the record of table
     * @param tableName: The table name that need to be updated
     * @param columnName: The column that need to be updated
     * @param value: the new value of record
     * @param recordID: The ID of record that need to be update
     * @param valueIsString: ture-the value type is string, false-the value type is not string
     */
    void updateRecord(QString tableName, QString columnName, QVariant value, quint64 recordID, bool valueIsString);

    /**
     * @brief deleteRecord: Delete record from database
     * @param tableName: table name
     * @param recordID: id of the record that need to be delete
     */
    void deleteRecord(QString tableName, quint64 recordID);
private:
    static SAKDebugPageCommonDatabaseInterface *instancePtr;
    QSqlDatabase sakDatabase;
    QSqlQuery sakDatabaseQuery;
    QList<AutoResponseTable> autoResponseTableList;
    QList<TimingSendingTable> timingSendingTableList;
    QList<DataPresetItemTable> presettingDataTableList;
    QString databaseName;
private:
    bool isTableExist(QString tableName);
    void initDatabase();
    void createTables();
    void createAutoResponseTables();
    bool createAutoResponseTable(const AutoResponseTable &table);
    void createTimingSendingTables();
    bool createTimingSendingTable(const TimingSendingTable &table);
    void createPresettingDataTables();
    bool createPresettingDataTable(const DataPresetItemTable &table);

    AutoResponseTable tableNmaeToAutoResponseTable(QString tableName);
    TimingSendingTable tableNameToTimingSendingTable(QString tableName);
    DataPresetItemTable tableNameToPresettingDataTable(QString tableName);
};

#endif
