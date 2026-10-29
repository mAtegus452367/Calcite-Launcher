// SPDX-License-Identifier: GPL-3.0-only
/*
 *  Calcite Launcher - Minecraft Launcher
 *  Based on Prism Launcher (GPL-3.0-only)
 */
#pragma once

#include "FusionTheme.h"

// Calcite Launcher's own themes (dark "black + cards" and light), styled after modern iOS-like launchers.
class CalciteTheme : public FusionTheme {
   public:
    explicit CalciteTheme(bool light = false) : m_light(light) {}
    virtual ~CalciteTheme() {}

    QString id() override;
    QString name() override;
    QString tooltip() override;
    bool hasStyleSheet() override;
    QString appStyleSheet() override;
    QPalette colorScheme() override;
    double fadeAmount() override;
    QColor fadeColor() override;

   private:
    bool m_light;
};
