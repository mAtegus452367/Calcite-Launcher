// SPDX-License-Identifier: GPL-3.0-only
/*
 *  Calcite Launcher - Minecraft Launcher
 *  Based on Prism Launcher (GPL-3.0-only)
 */
#include "CalciteTheme.h"

#include <QObject>

QString CalciteTheme::id()
{
    return "calcite";
}

QString CalciteTheme::name()
{
    return QObject::tr("Calcite");
}

QPalette CalciteTheme::colorScheme()
{
    QPalette p;
    p.setColor(QPalette::Window, QColor(17, 26, 54));
    p.setColor(QPalette::WindowText, QColor(232, 236, 255));
    p.setColor(QPalette::Base, QColor(11, 16, 32));
    p.setColor(QPalette::AlternateBase, QColor(23, 32, 66));
    p.setColor(QPalette::ToolTipBase, QColor(29, 40, 80));
    p.setColor(QPalette::ToolTipText, Qt::white);
    p.setColor(QPalette::Text, QColor(232, 236, 255));
    p.setColor(QPalette::Button, QColor(27, 39, 84));
    p.setColor(QPalette::ButtonText, QColor(232, 236, 255));
    p.setColor(QPalette::BrightText, Qt::red);
    p.setColor(QPalette::Link, QColor(122, 184, 255));
    p.setColor(QPalette::Highlight, QColor(90, 169, 255));
    p.setColor(QPalette::HighlightedText, QColor(11, 16, 32));
    p.setColor(QPalette::PlaceholderText, QColor(120, 131, 170));
    return fadeInactive(p, fadeAmount(), fadeColor());
}

double CalciteTheme::fadeAmount()
{
    return 0.5;
}

QColor CalciteTheme::fadeColor()
{
    return QColor(17, 26, 54);
}

bool CalciteTheme::hasStyleSheet()
{
    return true;
}

QString CalciteTheme::appStyleSheet()
{
    return QStringLiteral(R"CALCITEQSS(
/* ---------- Base ---------- */
QMainWindow, QDialog, QWizard, QWizardPage {
    background: qlineargradient(x1:0, y1:0, x2:1, y2:1, stop:0 #0b1020, stop:0.55 #111a36, stop:1 #1a1440);
    color: #e8ecff;
}
QWidget#centralWidget { background: transparent; }
QWidget { color: #e8ecff; selection-background-color: #5aa9ff; selection-color: #0b1020; }
QLabel { background: transparent; }
QStackedWidget, QScrollArea { background: transparent; border: none; }

/* ---------- Toolbars / menus ---------- */
QToolBar {
    background: rgba(23, 32, 66, 0.82);
    border: none;
    border-bottom: 1px solid #2a3668;
    spacing: 4px;
    padding: 4px;
}
QToolBar#newsToolBar { border-top: 1px solid #2a3668; border-bottom: none; }
QToolButton {
    background: transparent;
    border: 1px solid transparent;
    border-radius: 8px;
    padding: 5px 8px;
    color: #e8ecff;
}
QToolButton:hover { background: rgba(90, 169, 255, 0.18); border: 1px solid #3d5199; }
QToolButton:pressed, QToolButton:checked { background: rgba(124, 107, 255, 0.35); border: 1px solid #7c6bff; }
QToolButton::menu-indicator { image: none; }

QMenuBar { background: rgba(11, 16, 32, 0.9); color: #e8ecff; border-bottom: 1px solid #2a3668; }
QMenuBar::item { background: transparent; padding: 5px 10px; border-radius: 6px; }
QMenuBar::item:selected { background: rgba(90, 169, 255, 0.22); }
QMenu {
    background: #141c3a;
    border: 1px solid #2a3668;
    border-radius: 8px;
    padding: 6px;
}
QMenu::item { padding: 6px 26px 6px 22px; border-radius: 6px; }
QMenu::item:selected { background: #2b4fa3; color: #ffffff; }
QMenu::item:disabled { color: #5d678f; }
QMenu::separator { height: 1px; background: #2a3668; margin: 5px 8px; }

QStatusBar { background: rgba(11, 16, 32, 0.9); color: #8d98c4; border-top: 1px solid #2a3668; }

/* ---------- Buttons ---------- */
QPushButton {
    background: qlineargradient(x1:0, y1:0, x2:0, y2:1, stop:0 #24336b, stop:1 #1b2754);
    border: 1px solid #34458a;
    border-radius: 9px;
    padding: 6px 16px;
    color: #e8ecff;
}
QPushButton:hover {
    background: qlineargradient(x1:0, y1:0, x2:0, y2:1, stop:0 #3b6fd8, stop:1 #5a52e0);
    border: 1px solid #7fb4ff;
    color: #ffffff;
}
QPushButton:pressed { background: #2b3f8f; border: 1px solid #5aa9ff; }
QPushButton:default { border: 1px solid #5aa9ff; }
QPushButton:disabled { background: #151c38; border: 1px solid #222c55; color: #5d678f; }
QDialogButtonBox QPushButton { min-width: 84px; }

/* ---------- Inputs ---------- */
QLineEdit, QPlainTextEdit, QTextEdit, QTextBrowser, QSpinBox, QDoubleSpinBox, QComboBox {
    background: rgba(11, 16, 32, 0.85);
    border: 1px solid #2f3d78;
    border-radius: 8px;
    padding: 4px 8px;
    color: #e8ecff;
}
QLineEdit:focus, QPlainTextEdit:focus, QTextEdit:focus, QSpinBox:focus, QDoubleSpinBox:focus, QComboBox:focus {
    border: 1px solid #5aa9ff;
}
QComboBox::drop-down { border: none; width: 22px; }
QComboBox QAbstractItemView {
    background: #141c3a;
    border: 1px solid #2a3668;
    selection-background-color: #2b4fa3;
    outline: none;
}
QCheckBox, QRadioButton { background: transparent; spacing: 8px; }
QCheckBox::indicator, QRadioButton::indicator { width: 16px; height: 16px; }
QCheckBox::indicator { border: 1px solid #3d5199; border-radius: 4px; background: #0b1020; }
QCheckBox::indicator:checked { background: #5aa9ff; border: 1px solid #9cc9ff; }
QRadioButton::indicator { border: 1px solid #3d5199; border-radius: 9px; background: #0b1020; }
QRadioButton::indicator:checked { background: #5aa9ff; border: 1px solid #9cc9ff; }

/* ---------- Lists, trees, tables (incl. the instance view) ---------- */
QAbstractItemView {
    background: rgba(11, 16, 32, 0.55);
    alternate-background-color: rgba(23, 32, 66, 0.55);
    border: 1px solid #2a3668;
    border-radius: 10px;
    outline: none;
    color: #e8ecff;
}
QAbstractItemView::item:hover { background: rgba(90, 169, 255, 0.15); }
QAbstractItemView::item:selected { background: rgba(90, 169, 255, 0.35); color: #ffffff; }
QHeaderView::section {
    background: #172042;
    color: #8d98c4;
    border: none;
    border-right: 1px solid #2a3668;
    border-bottom: 1px solid #2a3668;
    padding: 5px 8px;
}
QTableCornerButton::section { background: #172042; border: none; }

/* ---------- Tabs / groups ---------- */
QTabWidget::pane { border: 1px solid #2a3668; border-radius: 10px; background: rgba(23, 32, 66, 0.55); top: -1px; }
QTabBar::tab {
    background: transparent;
    color: #8d98c4;
    padding: 7px 16px;
    border: 1px solid transparent;
    border-top-left-radius: 8px;
    border-top-right-radius: 8px;
}
QTabBar::tab:selected { background: rgba(23, 32, 66, 0.95); color: #ffffff; border: 1px solid #2a3668; border-bottom: none; }
QTabBar::tab:hover:!selected { color: #cfd8ff; }
QGroupBox {
    background: rgba(23, 32, 66, 0.45);
    border: 1px solid #2a3668;
    border-radius: 10px;
    margin-top: 14px;
    padding-top: 10px;
}
QGroupBox::title { subcontrol-origin: margin; left: 12px; padding: 0 6px; color: #9cc9ff; }

/* ---------- Scrollbars ---------- */
QScrollBar:vertical { background: transparent; width: 12px; margin: 2px; }
QScrollBar::handle:vertical { background: #34458a; border-radius: 4px; min-height: 28px; }
QScrollBar::handle:vertical:hover { background: #5aa9ff; }
QScrollBar:horizontal { background: transparent; height: 12px; margin: 2px; }
QScrollBar::handle:horizontal { background: #34458a; border-radius: 4px; min-width: 28px; }
QScrollBar::handle:horizontal:hover { background: #5aa9ff; }
QScrollBar::add-line, QScrollBar::sub-line { width: 0; height: 0; }
QScrollBar::add-page, QScrollBar::sub-page { background: transparent; }

/* ---------- Progress / sliders / splitters ---------- */
QProgressBar {
    background: #0b1020;
    border: 1px solid #2f3d78;
    border-radius: 8px;
    text-align: center;
    color: #e8ecff;
}
QProgressBar::chunk {
    border-radius: 7px;
    background: qlineargradient(x1:0, y1:0, x2:1, y2:0, stop:0 #5aa9ff, stop:1 #7c6bff);
}
QSlider::groove:horizontal { height: 6px; background: #0b1020; border-radius: 3px; }
QSlider::sub-page:horizontal { background: #5aa9ff; border-radius: 3px; }
QSlider::handle:horizontal { background: #e8ecff; width: 14px; margin: -5px 0; border-radius: 7px; }
QSplitter::handle { background: #2a3668; }

QToolTip { color: #ffffff; background-color: #1d2850; border: 1px solid #5aa9ff; border-radius: 6px; padding: 4px; }
)CALCITEQSS");
}

QString CalciteTheme::tooltip()
{
    return QObject::tr("Calcite Launcher's own dark blue theme");
}
