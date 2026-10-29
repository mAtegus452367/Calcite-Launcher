// SPDX-License-Identifier: GPL-3.0-only
/*
 *  Calcite Launcher - Minecraft Launcher
 *  Based on Prism Launcher (GPL-3.0-only)
 */
#include "CalciteTranslator.h"

#include <QHash>

namespace {
// English source text -> Russian translation
const QHash<QString, QString>& russianTable()
{
    static const QHash<QString, QString> table = {
        { QStringLiteral("Calcite Launcher's own dark blue theme"),
          QStringLiteral("Собственная тёмно-синяя тема Calcite Launcher") },
        { QStringLiteral("Add offline account"),
          QStringLiteral("Добавить офлайн-аккаунт") },
        { QStringLiteral("<html><head/><body><p><span style=\" font-size:14pt; font-weight:600;\">Add account</span></p></body></html>"),
          QStringLiteral("<html><head/><body><p><span style=\" font-size:14pt; font-weight:600;\">Добавить аккаунт</span></p></body></html>") },
        { QStringLiteral("In order to play Minecraft, you must add at least one account: either a Microsoft account or an offline account (just a nickname). You can also skip this and add one later."),
          QStringLiteral("Чтобы играть в Minecraft, нужно добавить хотя бы один аккаунт: Microsoft или офлайн (достаточно придумать ник). Этот шаг можно пропустить и добавить аккаунт позже.") },
        { QStringLiteral("In order to play Minecraft, you must add at least one account (Microsoft or offline). Would you like to open the account manager to add an account now?"),
          QStringLiteral("Чтобы играть в Minecraft, нужно добавить хотя бы один аккаунт (Microsoft или офлайн). Открыть менеджер аккаунтов и добавить аккаунт сейчас?") },
        { QStringLiteral("Cannot download Minecraft or update instances unless you have at least one account added.\nPlease add a Microsoft or offline account."),
          QStringLiteral("Нельзя скачать Minecraft или обновить экземпляры, пока не добавлен хотя бы один аккаунт.\nДобавьте аккаунт Microsoft или офлайн-аккаунт.") },
        { QStringLiteral("Unsupported Modrinth link.\n\nCalcite Launcher currently only supports modpack links such as modrinth://modpack/fabulously-optimized."),
          QStringLiteral("Неподдерживаемая ссылка Modrinth.\n\nCalcite Launcher сейчас поддерживает только ссылки на модпаки, например modrinth://modpack/fabulously-optimized.") },
        { QStringLiteral("Please select how much memory to allocate to instances and if Calcite Launcher should manage Java automatically or manually."),
          QStringLiteral("Выберите, сколько памяти выделять экземплярам и должен ли Calcite Launcher управлять Java автоматически или вручную.") },
        { QStringLiteral("Folder where Calcite Launcher stores automatically downloaded Java versions. Do NOT set this to your system Java installation."),
          QStringLiteral("Папка, в которой Calcite Launcher хранит автоматически загруженные версии Java. НЕ указывайте здесь системную установку Java.") },
        { QStringLiteral("- Calcite Launcher, Prism Launcher, PolyMC or MultiMC exported instances (ZIP)"),
          QStringLiteral("- Экземпляры, экспортированные из Calcite Launcher, Prism Launcher, PolyMC или MultiMC (ZIP)") },
        { QStringLiteral("Note: CurseForge allows creators to block access to third-party tools like Calcite Launcher. As such, you may need to manually download some mods to be able to install a modpack."),
          QStringLiteral("Примечание: CurseForge позволяет авторам блокировать доступ сторонним инструментам, таким как Calcite Launcher. Поэтому для установки некоторых модпаков моды, возможно, придётся скачать вручную.") }
    };
    return table;
}
}  // namespace

CalciteTranslator::CalciteTranslator(const QString& langCode)
{
    if (langCode.startsWith("ru")) {
        m_table = russianTable();
    }
}

bool CalciteTranslator::supports(const QString& langCode)
{
    return langCode.startsWith("ru");
}

QString CalciteTranslator::translate(const char*, const char* sourceText, const char*, int) const
{
    if (!sourceText) {
        return {};
    }
    // An empty result means "not translated here" and lets Qt ask the other translators
    return m_table.value(QString::fromUtf8(sourceText));
}

bool CalciteTranslator::isEmpty() const
{
    return m_table.isEmpty();
}
