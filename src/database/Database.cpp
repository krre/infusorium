#include "Database.h"
#include "Migrater.h"
#include <QSqlQuery>
#include <QSqlError>

Database::Database(QObject* parent) : QObject(parent) {
    m_db = QSqlDatabase::addDatabase("QSQLITE", "infusorium_world");
}

Database::~Database() {
    if (m_db.isOpen()) {
        qInfo().noquote() << "Close database:" << m_db.databaseName();
        QString connectionName = m_db.connectionName();
        m_db.close();
        m_db = QSqlDatabase();
        QSqlDatabase::removeDatabase(connectionName);
    }
}

void Database::open(const QString& filePath) {
    qInfo().noquote() << "Open database:" << filePath;
    m_db.setDatabaseName(filePath);

    if (!m_db.open()) {
        throw std::runtime_error(m_db.lastError().text().toStdString());
    }

    Migrater migrater(this);
    migrater.run();
}

QString Database::filePath() const {
    return m_db.databaseName();
}

QSqlQuery Database::exec(const QString& sql, const QVariantMap& params) const {
    QSqlQuery query(m_db);
    query.prepare(sql);

    for (auto [key, value] : params.asKeyValueRange()) {
        query.bindValue(":" + key, value);
    }

    if (!query.exec()) {
        throw std::runtime_error(query.lastError().text().toStdString());
    }

    return query;
}

void Database::updateMetaValue(const QString& name, const QVariant& value) const {
    exec(QString("UPDATE meta SET %1 = :value").arg(name), { { "value", value } });
}

QVariant Database::metaValue(const QString& name) const {
    if (!m_db.tables().contains("meta")) {
        return QVariant();
    }

    QSqlQuery query = exec(QString("SELECT %1 FROM meta").arg(name));
    return query.first() ? query.value(name) : QVariant();
}
