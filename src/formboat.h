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

#ifndef FORMBOAT_H
#define FORMBOAT_H

#include "formmain.h"
#include "sailwriter-xml.h"

class CBoatDefPanel;

/** A form allowing the user to assemble several elements into a boat.
 */
class CFormBoat : public CFormMain
{
    Q_OBJECT

public:
    CFormBoat(QWidget *parent = 0);
    void add(const QString &newfile);
    bool open(const QString &newfile);

private slots:
    void languageChange();
    void slotAdd();
    void slotUpdate(const CBoatDef& newdef);

private:
    void setDef(const CBoatDef &newdef);
    void setupMainWidget();
    void setupMenuBar();

    CBoatDef def;
    /** A panel with one tab per element in the current boat.  */
    CBoatDefPanel *defpanel;
    /** The Add menu. */
    QMenu *menuAdd;
    /** add a file */
    QAction *actionAddFile;
};

#endif
