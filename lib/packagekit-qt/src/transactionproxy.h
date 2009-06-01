/*
 * This file was generated by dbusxml2cpp version 0.6
 * Command line was: dbusxml2cpp -c TransactionProxy -p transactionproxy.h /home/madcat/code/PackageKit/src/org.freedesktop.PackageKit.Transaction.xml org.freedesktop.PackageKit.Transaction
 *
 * dbusxml2cpp is Copyright (C) 2008 Nokia Corporation and/or its subsidiary(-ies).
 *
 * This is an auto-generated file.
 * Do not edit! All changes made to it will be lost.
 */

#ifndef TRANSACTIONPROXY_H_1228504363
#define TRANSACTIONPROXY_H_1228504363

#include <QtCore/QObject>
#include <QtCore/QByteArray>
#include <QtCore/QList>
#include <QtCore/QMap>
#include <QtCore/QString>
#include <QtCore/QStringList>
#include <QtCore/QVariant>
#include <QtDBus/QtDBus>

namespace PackageKit {

/*
 * Proxy class for interface org.freedesktop.PackageKit.Transaction
 */
class TransactionProxy: public QDBusAbstractInterface
{
    Q_OBJECT
public:
    static inline const char *staticInterfaceName()
    { return "org.freedesktop.PackageKit.Transaction"; }

public:
    TransactionProxy(const QString &service, const QString &path, const QDBusConnection &connection, QObject *parent = 0);

    ~TransactionProxy();

public Q_SLOTS: // METHODS
    inline QDBusReply<void> AcceptEula(const QString &eula_id)
    {
        QList<QVariant> argumentList;
        argumentList << qVariantFromValue(eula_id);
        return callWithArgumentList(QDBus::Block, QLatin1String("AcceptEula"), argumentList);
    }

    inline QDBusReply<void> Cancel()
    {
        QList<QVariant> argumentList;
        return callWithArgumentList(QDBus::Block, QLatin1String("Cancel"), argumentList);
    }

    inline QDBusReply<void> DownloadPackages(const QStringList &package_ids)
    {
        QList<QVariant> argumentList;
        argumentList << qVariantFromValue(package_ids);
        return callWithArgumentList(QDBus::Block, QLatin1String("DownloadPackages"), argumentList);
    }

    inline QDBusReply<bool> GetAllowCancel()
    {
        QList<QVariant> argumentList;
        return callWithArgumentList(QDBus::Block, QLatin1String("GetAllowCancel"), argumentList);
    }

    inline QDBusReply<void> GetCategories()
    {
        QList<QVariant> argumentList;
        return callWithArgumentList(QDBus::Block, QLatin1String("GetCategories"), argumentList);
    }

    inline QDBusReply<void> GetDepends(const QString &filter, const QStringList &package_ids, bool recursive)
    {
        QList<QVariant> argumentList;
        argumentList << qVariantFromValue(filter) << qVariantFromValue(package_ids) << qVariantFromValue(recursive);
        return callWithArgumentList(QDBus::Block, QLatin1String("GetDepends"), argumentList);
    }

    inline QDBusReply<void> GetDetails(const QStringList &package_ids)
    {
        QList<QVariant> argumentList;
        argumentList << qVariantFromValue(package_ids);
        return callWithArgumentList(QDBus::Block, QLatin1String("GetDetails"), argumentList);
    }

    inline QDBusReply<void> GetDistroUpgrades()
    {
        QList<QVariant> argumentList;
        return callWithArgumentList(QDBus::Block, QLatin1String("GetDistroUpgrades"), argumentList);
    }

    inline QDBusReply<void> GetFiles(const QStringList &package_ids)
    {
        QList<QVariant> argumentList;
        argumentList << qVariantFromValue(package_ids);
        return callWithArgumentList(QDBus::Block, QLatin1String("GetFiles"), argumentList);
    }

    inline QDBusReply<void> GetOldTransactions(uint number)
    {
        QList<QVariant> argumentList;
        argumentList << qVariantFromValue(number);
        return callWithArgumentList(QDBus::Block, QLatin1String("GetOldTransactions"), argumentList);
    }

    inline QDBusReply<QString> GetPackageLast()
    {
        QList<QVariant> argumentList;
        return callWithArgumentList(QDBus::Block, QLatin1String("GetPackageLast"), argumentList);
    }

    inline QDBusReply<void> GetPackages(const QString &filter)
    {
        QList<QVariant> argumentList;
        argumentList << qVariantFromValue(filter);
        return callWithArgumentList(QDBus::Block, QLatin1String("GetPackages"), argumentList);
    }

    inline QDBusReply<uint> GetProgress(uint &subpercentage, uint &elapsed, uint &remaining)
    {
        QList<QVariant> argumentList;
        QDBusMessage reply = callWithArgumentList(QDBus::Block, QLatin1String("GetProgress"), argumentList);
        if (reply.type() == QDBusMessage::ReplyMessage && reply.arguments().count() == 4) {
            subpercentage = qdbus_cast<uint>(reply.arguments().at(1));
            elapsed = qdbus_cast<uint>(reply.arguments().at(2));
            remaining = qdbus_cast<uint>(reply.arguments().at(3));
        }
        return reply;
    }

    inline QDBusReply<void> GetRepoList(const QString &filter)
    {
        QList<QVariant> argumentList;
        argumentList << qVariantFromValue(filter);
        return callWithArgumentList(QDBus::Block, QLatin1String("GetRepoList"), argumentList);
    }

    inline QDBusReply<void> GetRequires(const QString &filter, const QStringList &package_ids, bool recursive)
    {
        QList<QVariant> argumentList;
        argumentList << qVariantFromValue(filter) << qVariantFromValue(package_ids) << qVariantFromValue(recursive);
        return callWithArgumentList(QDBus::Block, QLatin1String("GetRequires"), argumentList);
    }

    inline QDBusReply<QString> GetRole(QString &text)
    {
        QList<QVariant> argumentList;
        QDBusMessage reply = callWithArgumentList(QDBus::Block, QLatin1String("GetRole"), argumentList);
        if (reply.type() == QDBusMessage::ReplyMessage && reply.arguments().count() == 2) {
            text = qdbus_cast<QString>(reply.arguments().at(1));
        }
        return reply;
    }

    inline QDBusReply<QString> GetStatus()
    {
        QList<QVariant> argumentList;
        return callWithArgumentList(QDBus::Block, QLatin1String("GetStatus"), argumentList);
    }

    inline QDBusReply<void> GetUpdateDetail(const QStringList &package_ids)
    {
        QList<QVariant> argumentList;
        argumentList << qVariantFromValue(package_ids);
        return callWithArgumentList(QDBus::Block, QLatin1String("GetUpdateDetail"), argumentList);
    }

    inline QDBusReply<void> GetUpdates(const QString &filter)
    {
        QList<QVariant> argumentList;
        argumentList << qVariantFromValue(filter);
        return callWithArgumentList(QDBus::Block, QLatin1String("GetUpdates"), argumentList);
    }

    inline QDBusReply<void> InstallFiles(bool only_trusted, const QStringList &full_paths)
    {
        QList<QVariant> argumentList;
        argumentList << qVariantFromValue(only_trusted) << qVariantFromValue(full_paths);
        return callWithArgumentList(QDBus::Block, QLatin1String("InstallFiles"), argumentList);
    }

    inline QDBusReply<void> InstallPackages(const QStringList &package_ids)
    {
        QList<QVariant> argumentList;
        argumentList << qVariantFromValue(package_ids);
        return callWithArgumentList(QDBus::Block, QLatin1String("InstallPackages"), argumentList);
    }

    inline QDBusReply<void> InstallSignature(const QString &sig_type, const QString &key_id, const QString &package_id)
    {
        QList<QVariant> argumentList;
        argumentList << qVariantFromValue(sig_type) << qVariantFromValue(key_id) << qVariantFromValue(package_id);
        return callWithArgumentList(QDBus::Block, QLatin1String("InstallSignature"), argumentList);
    }

    inline QDBusReply<bool> IsCallerActive()
    {
        QList<QVariant> argumentList;
        return callWithArgumentList(QDBus::Block, QLatin1String("IsCallerActive"), argumentList);
    }

    inline QDBusReply<void> RefreshCache(bool force)
    {
        QList<QVariant> argumentList;
        argumentList << qVariantFromValue(force);
        return callWithArgumentList(QDBus::Block, QLatin1String("RefreshCache"), argumentList);
    }

    inline QDBusReply<void> RemovePackages(const QStringList &package_ids, bool allow_deps, bool autoremove)
    {
        QList<QVariant> argumentList;
        argumentList << qVariantFromValue(package_ids) << qVariantFromValue(allow_deps) << qVariantFromValue(autoremove);
        return callWithArgumentList(QDBus::Block, QLatin1String("RemovePackages"), argumentList);
    }

    inline QDBusReply<void> RepoEnable(const QString &repo_id, bool enabled)
    {
        QList<QVariant> argumentList;
        argumentList << qVariantFromValue(repo_id) << qVariantFromValue(enabled);
        return callWithArgumentList(QDBus::Block, QLatin1String("RepoEnable"), argumentList);
    }

    inline QDBusReply<void> RepoSetData(const QString &repo_id, const QString &parameter, const QString &value)
    {
        QList<QVariant> argumentList;
        argumentList << qVariantFromValue(repo_id) << qVariantFromValue(parameter) << qVariantFromValue(value);
        return callWithArgumentList(QDBus::Block, QLatin1String("RepoSetData"), argumentList);
    }

    inline QDBusReply<void> Resolve(const QString &filter, const QStringList &package)
    {
        QList<QVariant> argumentList;
        argumentList << qVariantFromValue(filter) << qVariantFromValue(package);
        return callWithArgumentList(QDBus::Block, QLatin1String("Resolve"), argumentList);
    }

    inline QDBusReply<void> Rollback(const QString &transaction_id)
    {
        QList<QVariant> argumentList;
        argumentList << qVariantFromValue(transaction_id);
        return callWithArgumentList(QDBus::Block, QLatin1String("Rollback"), argumentList);
    }

    inline QDBusReply<void> SearchDetails(const QString &filter, const QString &search)
    {
        QList<QVariant> argumentList;
        argumentList << qVariantFromValue(filter) << qVariantFromValue(search);
        return callWithArgumentList(QDBus::Block, QLatin1String("SearchDetails"), argumentList);
    }

    inline QDBusReply<void> SearchFile(const QString &filter, const QString &search)
    {
        QList<QVariant> argumentList;
        argumentList << qVariantFromValue(filter) << qVariantFromValue(search);
        return callWithArgumentList(QDBus::Block, QLatin1String("SearchFile"), argumentList);
    }

    inline QDBusReply<void> SearchGroup(const QString &filter, const QString &search)
    {
        QList<QVariant> argumentList;
        argumentList << qVariantFromValue(filter) << qVariantFromValue(search);
        return callWithArgumentList(QDBus::Block, QLatin1String("SearchGroup"), argumentList);
    }

    inline QDBusReply<void> SearchName(const QString &filter, const QString &search)
    {
        QList<QVariant> argumentList;
        argumentList << qVariantFromValue(filter) << qVariantFromValue(search);
        return callWithArgumentList(QDBus::Block, QLatin1String("SearchName"), argumentList);
    }

    inline QDBusReply<void> SetLocale(const QString &code)
    {
        QList<QVariant> argumentList;
        argumentList << qVariantFromValue(code);
        return callWithArgumentList(QDBus::Block, QLatin1String("SetLocale"), argumentList);
    }

    inline QDBusReply<void> UpdatePackages(const QStringList &package_ids)
    {
        QList<QVariant> argumentList;
        argumentList << qVariantFromValue(package_ids);
        return callWithArgumentList(QDBus::Block, QLatin1String("UpdatePackages"), argumentList);
    }

    inline QDBusReply<void> UpdateSystem()
    {
        QList<QVariant> argumentList;
        return callWithArgumentList(QDBus::Block, QLatin1String("UpdateSystem"), argumentList);
    }

    inline QDBusReply<void> WhatProvides(const QString &filter, const QString &type, const QString &search)
    {
        QList<QVariant> argumentList;
        argumentList << qVariantFromValue(filter) << qVariantFromValue(type) << qVariantFromValue(search);
        return callWithArgumentList(QDBus::Block, QLatin1String("WhatProvides"), argumentList);
    }

Q_SIGNALS: // SIGNALS
    void AllowCancel(bool allow_cancel);
    void CallerActiveChanged(bool is_active);
    void Category(const QString &parent_id, const QString &cat_id, const QString &name, const QString &summary, const QString &icon);
    void Destroy();
    void Details(const QString &package_id, const QString &license, const QString &group, const QString &detail, const QString &url, qulonglong size);
    void DistroUpgrade(const QString &type, const QString &name, const QString &summary);
    void ErrorCode(const QString &code, const QString &details);
    void EulaRequired(const QString &eula_id, const QString &package_id, const QString &vendor_name, const QString &license_agreement);
    void MediaChangeRequired(const QString &media_type, const QString &media_id, const QString &media_text);
    void Files(const QString &package_id, const QString &file_list);
    void Finished(const QString &exit, uint runtime);
    void Message(const QString &type, const QString &details);
    void Package(const QString &info, const QString &package_id, const QString &summary);
    void ProgressChanged(uint percentage, uint subpercentage, uint elapsed, uint remaining);
    void RepoDetail(const QString &repo_id, const QString &description, bool enabled);
    void RepoSignatureRequired(const QString &package_id, const QString &repository_name, const QString &key_url, const QString &key_userid, const QString &key_id, const QString &key_fingerprint, const QString &key_timestamp, const QString &type);
    void RequireRestart(const QString &type, const QString &details);
    void StatusChanged(const QString &status);
    void Transaction(const QString &old_tid, const QString &timespec, bool succeeded, const QString &role, uint duration, const QString &data, uint uid, const QString &cmdline);
    void UpdateDetail(const QString &package_id, const QString &updates, const QString &obsoletes, const QString &vendor_url, const QString &bugzilla_url, const QString &cve_url, const QString &restart, const QString &update_text, const QString &changelog, const QString &state, const QString &issued, const QString &updated);
};

} // End namespace PackageKit

#endif

