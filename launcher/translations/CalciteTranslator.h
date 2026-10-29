// SPDX-License-Identifier: GPL-3.0-only
/*
 *  Calcite Launcher - Minecraft Launcher
 *  Based on Prism Launcher (GPL-3.0-only)
 */
#pragma once

#include <QTranslator>

/**
 * Calcite's own translations. Installed on top of the downloaded language files, so it wins over them.
 * Used for strings that Calcite added or changed (and strings missing in the upstream translation).
 * To add a translation, put "English source" -> "translation" into the table in CalciteTranslator.cpp.
 */
class CalciteTranslator : public QTranslator {
   public:
    explicit CalciteTranslator(const QString& langCode);

    QString translate(const char* context, const char* sourceText, const char* disambiguation = nullptr, int n = -1) const override;
    bool isEmpty() const override;

    static bool supports(const QString& langCode);

   private:
    QHash<QString, QString> m_table;
};
