// SPDX-License-Identifier: GPL-3.0-only
/*
 *  Calcite Launcher - Minecraft Launcher
 *  Based on Prism Launcher (GPL-3.0-only)
 */
#include "CalciteTheme.h"

#include <QDir>
#include <QImage>
#include <QObject>
#include <QPainter>
#include <QStandardPaths>

namespace {

struct Tokens {
    QString bg, card, card2, card3, border, text, muted, accent, accentH, accentP, green;
};

Tokens tokens(bool light)
{
    if (light) {
        return { "#f2f2f7", "#ffffff", "#e9e9ee", "#d8d8de", "#d1d1d6", "#000000", "#6c6c70", "#0a84ff", "#409cff", "#0060df", "#30d158" };
    }
    return { "#000000", "#1c1c1e", "#2c2c2e", "#3a3a3c", "#38383a", "#ffffff", "#8e8e93", "#0a84ff", "#409cff", "#0060df", "#30d158" };
}

// Draws one iOS-like switch and saves it as PNG (plus @2x for HiDPI); returns the 1x file path
QString makeSwitch(const QString& dir, const QString& name, const QColor& track, bool on)
{
    auto render = [&](int scale) {
        QImage img(44 * scale, 26 * scale, QImage::Format_ARGB32_Premultiplied);
        img.fill(Qt::transparent);
        QPainter p(&img);
        p.setRenderHint(QPainter::Antialiasing, true);
        p.setPen(Qt::NoPen);
        p.setBrush(track);
        p.drawRoundedRect(QRectF(0, 0, 44 * scale, 26 * scale), 13 * scale, 13 * scale);
        p.setBrush(Qt::white);
        const qreal d = 22 * scale;
        const qreal x = on ? (44 - 2 - 22) * scale : 2 * scale;
        p.drawEllipse(QRectF(x, 2 * scale, d, d));
        return img;
    };
    const QString path1 = QDir(dir).filePath(name + ".png");
    const QString path2 = QDir(dir).filePath(name + "@2x.png");
    render(1).save(path1, "PNG");
    render(2).save(path2, "PNG");
    return path1;
}

}  // namespace

QString CalciteTheme::id()
{
    return m_light ? "calcite-light" : "calcite";
}

QString CalciteTheme::name()
{
    return m_light ? QObject::tr("Calcite Light") : QObject::tr("Calcite Dark");
}

QPalette CalciteTheme::colorScheme()
{
    const Tokens t = tokens(m_light);
    QPalette p;
    p.setColor(QPalette::Window, QColor(t.bg));
    p.setColor(QPalette::WindowText, QColor(t.text));
    p.setColor(QPalette::Base, QColor(t.card));
    p.setColor(QPalette::AlternateBase, QColor(t.card2));
    p.setColor(QPalette::ToolTipBase, QColor(t.card));
    p.setColor(QPalette::ToolTipText, QColor(t.text));
    p.setColor(QPalette::Text, QColor(t.text));
    p.setColor(QPalette::Button, QColor(t.card2));
    p.setColor(QPalette::ButtonText, QColor(t.text));
    p.setColor(QPalette::BrightText, Qt::red);
    p.setColor(QPalette::Link, QColor(t.accent));
    p.setColor(QPalette::Highlight, QColor(t.accent));
    p.setColor(QPalette::HighlightedText, Qt::white);
    p.setColor(QPalette::PlaceholderText, QColor(t.muted));
    return fadeInactive(p, fadeAmount(), fadeColor());
}

double CalciteTheme::fadeAmount()
{
    return 0.5;
}

QColor CalciteTheme::fadeColor()
{
    return QColor(tokens(m_light).bg);
}

bool CalciteTheme::hasStyleSheet()
{
    return true;
}

QString CalciteTheme::appStyleSheet()
{
    const Tokens t = tokens(m_light);

    // Switch images live in the temp folder; QSS can only reference files/resources
    const QString dir = QDir(QStandardPaths::writableLocation(QStandardPaths::TempLocation)).filePath("calcite-theme");
    QDir().mkpath(dir);
    const QString suffix = m_light ? "light" : "dark";
    const QString swOff = makeSwitch(dir, "switch-off-" + suffix, QColor(t.card3), false);
    const QString swOn = makeSwitch(dir, "switch-on-" + suffix, QColor(t.green), true);

    QString qss = QStringLiteral(R"CALCITEQSS(
/* ===== Base ===== */
QMainWindow, QDialog, QWizard, QWizardPage { background: @BG@; color: @TEXT@; }
QWidget#centralWidget { background: transparent; }
QWidget { color: @TEXT@; selection-background-color: @ACCENT@; selection-color: #ffffff; }
QLabel { background: transparent; }
QStackedWidget, QScrollArea { background: transparent; border: none; }

/* ===== Toolbars / menus ===== */
QToolBar { background: @CARD@; border: none; spacing: 6px; padding: 6px; }
QToolBar#newsToolBar { background: transparent; }
QToolButton { background: transparent; border: none; border-radius: 12px; padding: 6px 10px; color: @TEXT@; }
QToolButton:hover { background: @CARD2@; }
QToolButton:pressed, QToolButton:checked { background: @ACCENT@; color: #ffffff; }
QToolButton::menu-indicator { image: none; }

QMenuBar { background: @BG@; color: @TEXT@; }
QMenuBar::item { background: transparent; padding: 6px 12px; border-radius: 10px; }
QMenuBar::item:selected { background: @CARD2@; }
QMenu { background: @CARD@; border: 1px solid @BORDER@; border-radius: 14px; padding: 6px; }
QMenu::item { padding: 7px 28px 7px 22px; border-radius: 9px; }
QMenu::item:selected { background: @ACCENT@; color: #ffffff; }
QMenu::item:disabled { color: @MUTED@; }
QMenu::separator { height: 1px; background: @BORDER@; margin: 5px 8px; }
QStatusBar { background: @BG@; color: @MUTED@; }

/* ===== Buttons (pills) ===== */
QPushButton { background: @CARD2@; border: none; border-radius: 15px; padding: 8px 20px; color: @TEXT@; }
QPushButton:hover { background: @CARD3@; }
QPushButton:pressed { background: @BORDER@; }
QPushButton:default { background: @ACCENT@; color: #ffffff; }
QPushButton:default:hover { background: @ACCENT_H@; }
QPushButton:default:pressed { background: @ACCENT_P@; }
QPushButton:disabled { background: @CARD@; color: @MUTED@; }
QDialogButtonBox QPushButton { min-width: 90px; }

/* ===== Inputs ===== */
QLineEdit, QPlainTextEdit, QTextEdit, QTextBrowser, QSpinBox, QDoubleSpinBox, QComboBox {
    background: @CARD2@; border: 2px solid transparent; border-radius: 13px; padding: 6px 12px; color: @TEXT@;
}
QLineEdit:focus, QPlainTextEdit:focus, QTextEdit:focus, QSpinBox:focus, QDoubleSpinBox:focus, QComboBox:focus { border: 2px solid @ACCENT@; }
QComboBox::drop-down { border: none; width: 26px; }
QComboBox QAbstractItemView { background: @CARD@; border: 1px solid @BORDER@; border-radius: 12px; selection-background-color: @ACCENT@; outline: none; padding: 4px; }
QRadioButton { background: transparent; spacing: 8px; }
QRadioButton::indicator { width: 18px; height: 18px; border-radius: 10px; border: 2px solid @MUTED@; background: transparent; }
QRadioButton::indicator:checked { border: 6px solid @ACCENT@; background: #ffffff; }

/* iOS-style switch (images are generated at startup) */
QCheckBox { background: transparent; spacing: 10px; }
QCheckBox::indicator { width: 44px; height: 26px; }
QCheckBox::indicator:unchecked { image: url("@SW_OFF@"); }
QCheckBox::indicator:checked { image: url("@SW_ON@"); }

/* ===== Lists / trees (incl. the instance view) as cards ===== */
QAbstractItemView { background: @CARD@; alternate-background-color: @CARD2@; border: none; border-radius: 18px; outline: none; color: @TEXT@; }
QAbstractItemView::item { border-radius: 10px; }
QAbstractItemView::item:hover { background: @CARD2@; }
QAbstractItemView::item:selected { background: @ACCENT@; color: #ffffff; }
QHeaderView::section { background: @CARD@; color: @MUTED@; border: none; padding: 7px 10px; }
QTableCornerButton::section { background: @CARD@; border: none; }

/* ===== Tabs / groups as cards ===== */
QTabWidget::pane { border: none; border-radius: 18px; background: @CARD@; top: -1px; }
QTabBar::tab { background: transparent; color: @MUTED@; padding: 8px 18px; border-radius: 13px; margin: 2px; }
QTabBar::tab:selected { background: @CARD2@; color: @TEXT@; }
QTabBar::tab:hover:!selected { color: @TEXT@; }
QGroupBox { background: @CARD@; border: none; border-radius: 18px; margin-top: 16px; padding: 18px 12px 12px 12px; }
QGroupBox::title { subcontrol-origin: margin; left: 16px; padding: 0 6px; color: @TEXT@; font-weight: 600; }

/* ===== Scrollbars ===== */
QScrollBar:vertical { background: transparent; width: 12px; margin: 2px; }
QScrollBar::handle:vertical { background: @CARD3@; border-radius: 4px; min-height: 30px; }
QScrollBar::handle:vertical:hover { background: @MUTED@; }
QScrollBar:horizontal { background: transparent; height: 12px; margin: 2px; }
QScrollBar::handle:horizontal { background: @CARD3@; border-radius: 4px; min-width: 30px; }
QScrollBar::handle:horizontal:hover { background: @MUTED@; }
QScrollBar::add-line, QScrollBar::sub-line { width: 0; height: 0; }
QScrollBar::add-page, QScrollBar::sub-page { background: transparent; }

/* ===== Progress / sliders ===== */
QProgressBar { background: @CARD2@; border: none; border-radius: 9px; text-align: center; color: @TEXT@; min-height: 18px; }
QProgressBar::chunk { border-radius: 9px; background: @ACCENT@; }
QSlider::groove:horizontal { height: 6px; background: @CARD2@; border-radius: 3px; }
QSlider::sub-page:horizontal { background: @ACCENT@; border-radius: 3px; }
QSlider::handle:horizontal { background: #ffffff; border: 1px solid @BORDER@; width: 22px; height: 22px; margin: -9px 0; border-radius: 11px; }
QSplitter::handle { background: transparent; }

QToolTip { color: @TEXT@; background-color: @CARD@; border: 1px solid @BORDER@; border-radius: 8px; padding: 5px; }
)CALCITEQSS");
    qss.replace("@BG@", t.bg)
        .replace("@CARD2@", t.card2)
        .replace("@CARD3@", t.card3)
        .replace("@CARD@", t.card)
        .replace("@BORDER@", t.border)
        .replace("@TEXT@", t.text)
        .replace("@MUTED@", t.muted)
        .replace("@ACCENT_H@", t.accentH)
        .replace("@ACCENT_P@", t.accentP)
        .replace("@ACCENT@", t.accent)
        .replace("@SW_OFF@", QDir::fromNativeSeparators(swOff))
        .replace("@SW_ON@", QDir::fromNativeSeparators(swOn));
    return qss;
}

QString CalciteTheme::tooltip()
{
    return m_light ? QObject::tr("Calcite Launcher's own light theme") : QObject::tr("Calcite Launcher's own dark theme");
}
