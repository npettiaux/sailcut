/*
 * Copyright (C) 1993-2015 Robert & Jeremy Laine
 * See AUTHORS file for a full list of contributors.
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 2 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program; if not, write to the Free Software
 * Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston, MA  02110-1301  USA
 */

#ifndef FORMMAIN_H
#define FORMMAIN_H

#include <QMainWindow>
#include <QMessageBox>
#include <QMenu>
#include <QUrl>
#include "formdocument.h"

// forward definitions
class QAction;
class QMenu;
class QMenuBar;
class QStatusBar;
class QSignalMapper;

class CSailApp;


/** The main dialog of the Sailcut application.
 */
class CFormMain : public QMainWindow
{
    Q_OBJECT

public:
    // construction, destruction
    CFormMain(QWidget *parent = 0);
    virtual bool open(const QString &filename) = 0;

protected:
    void closeEvent( QCloseEvent * e);
    void makeMenuMru();

private:
    void setupMenuBar();
    void setupMainWidget();

protected slots:
    virtual void slotAbout();
    virtual void slotAboutQt();

    virtual void slotOpen();
    virtual void slotOpenRecent();
    virtual void slotSave();
    virtual void slotSaveAs();

    virtual void slotHandbook();

    virtual void slotLanguage();
    virtual void slotUpdateDocumentMenus();

private slots:
    void languageChange();

protected:
    /** The signal mapper */
    QSignalMapper *windowMapper;

    /** The application */
    CSailApp *app;

    /** The status bar */
    QStatusBar* statusbar;

    /** The File menu */
    QMenu *menuFile;
    /** The New submenu */
    QMenu *menuFileNew;
    /** The Help menu */
    QMenu *menuHelp;
    /** The View menu */
    QMenu *menuView;
    /** The Language menu */
    QMenu *menuLanguage;

    /** The Most Recently Used files menu */
    QMenu *menuRecent;

    /** Display information about sailcut */
    QAction *actionAbout;
    /** Display information about Qt */
    QAction *actionAboutQt;

    /** Display the handbook */
    QAction *actionHandbook;

    /** Create a new boat */
    QAction *actionNewBoat;
    /** Create a new hull */
    QAction *actionNewHull;
    /** Create a new rig */
    QAction *actionNewRig;
    /** Create a new sail */
    QAction *actionNewSail;
    /** Open an existing sail definition */
    QAction *actionOpen;

    /** Save the sail definition to a file */
    QAction *actionSave;
    /** Prompt for a filename then write the sail definition to a file */
    QAction *actionSaveAs;
    /** Final separator in the 'File' menu before 'Quit' */
    QAction *actionFileSep;

    /** View the sail definition */
    QAction *actionViewDef;
    /** View the sail mould */
    QAction *actionViewMould;
    /** View the sail patches definition */
    QAction *actionViewPatch;
    /** View the sail rig */
    QAction *actionViewRig;
    /** Separator in the 'Window' menu */
    QAction *actionWindowSep;
    /** Quit */
    QAction *actionQuit;

    /** Extra actions for the file menu */
    vector<QAction*> childFileActions;
    /** Extra actions for the view menu */
    vector<QAction*> childViewActions;

    CSailViewerTabs *tabs;
    /** Extra submenus for the File menu */
    vector<QMenu*> extraFileMenus;
    /** Extra actions for the View menu */
    vector<QAction*> extraViewActions;
    /** The current filename. */
    QString filename;
};

#endif
