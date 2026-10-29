// SPDX-License-Identifier: GPL-3.0-only
/*
 *  Calcite Launcher - Minecraft Launcher
 *  Based on Prism Launcher (GPL-3.0-only)
 */
#pragma once

#include "FusionTheme.h"

// Calcite Launcher's own dark theme: deep navy gradient, glass panels, accent buttons.
class CalciteTheme : public FusionTheme {
   public:
    virtual ~CalciteTheme() {}

    QString id() override;
    QString name() override;
    QString tooltip() override;
    bool hasStyleSheet() override;
    QString appStyleSheet() override;
    QPalette colorScheme() override;
    double fadeAmount() override;
    QColor fadeColor() override;
};
