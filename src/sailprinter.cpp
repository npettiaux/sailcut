/*
 * Copyright (C) 1993-2008 Robert & Jeremy Laine
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
 * Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA  02111-1307  USA
 */

#include "sailprinter.h"

#include <QPrinter>

#include "sailcalc.h"
#include "saildef.h"
#include "panelgroup.h"
#include "sailcalc.h"


/**
 * Print the current sail data.
 *
 * @param saildef
 * @param painter
 */
void CSailDataPrinter::print(const CSailDef &saildef, CTextPainter *painter, size_t) const
{
    QString text2=" ", text3=" ";
    painter->setFont(QFont("times", 10));

    // text of page header
    QString sailID = QString::fromStdString(saildef.sailID);
    painter->printHeader(tr("Sailcut CAD data sheet") + (( sailID.length() > 0 ) ? " - " + sailID : " "));

    // sail cut and type
    switch (saildef.sailType )
    {
    case MAINSAIL:
        text2 = tr("Mainsail");
        break;
    case JIB:
        text2 = tr("Jib");
        break;
    case WING:
        text2 = tr("Wing")+" @ " + QString::number(saildef.dihedralDeg) + tr("deg");
        break;
    }
    painter->printDataLine(tr("Sail type"), text2, " ");

    text3 = " ";
    switch ( saildef.sailCut )
    {
    case CROSS:
        text2 = tr("Cross Cut");
        break;
    case HORIZONTAL:
        text2 = tr("Horizontal Cut");
        break;
    case RADIAL:
        text2 = tr("Radial Cut");
        text3  = QString::number(saildef.nbSections) + " " + tr("sections") + ",   ";
        text3  += QString::number(saildef.nbGores) + " " + tr("head gores") + ",   ";
        text3  += QString::number(saildef.nbLuffGores) + " " + tr("luff gores") + ".";
        break;
    case TWIST:
        text2 = tr("Twist Foot Cut");
        break;
    case VERTICAL:
        text2 = tr("Vertical Cut");
        break;
    case MITRE:
        text2 = tr("Mitre Cut");
        break;
    }
    painter->printDataLine(tr("Sail layout"), text2, text3);

    // boat data
    painter->printDataSection(tr("Rig"));
    painter->printDataLine(tr("Boat LOA"), QString::number(saildef.LOA), "mm");
    painter->printDataLine(tr("Mast/Luff rake"), QString::number(saildef.rake), "mm");
    painter->printDataLine(tr("Tack position X"), QString::number(saildef.tackX), "mm");
    painter->printDataLine(tr("Tack height Y"), QString::number(saildef.tackY), "mm");
    painter->printDataLine(tr("Fore triangle hoist I"), QString::number(saildef.foreI), "mm");
    painter->printDataLine(tr("Fore triangle base J"), QString::number(saildef.foreJ), "mm");

    // sides of the sail
    painter->printDataSection(tr("Sail dimensions"));
    painter->printDataLine(tr("Luff length"), QString::number(saildef.luffL), "mm");
    painter->printDataLine(tr("Foot length"), QString::number(saildef.footL), "mm");
    painter->printDataLine(tr("Leech length"), QString::number(saildef.leechL), "mm");
    painter->printDataLine(tr("Gaff length"), QString::number(saildef.gaffL), "mm");
    painter->printDataLine(tr("Gaff angle wrt luff"), QString::number(saildef.gaffDeg), "deg");

    // shape of sides
    painter->printDataSection(tr("Shape of edges"));
    painter->printDataLine(tr("Luff round"), QString::number(saildef.luffR), "mm");
    painter->printDataLine(tr("Luff round position"), QString::number(saildef.footRP), "%");
    painter->printDataLine(tr("Foot round"), QString::number(saildef.footR), "mm");
    painter->printDataLine(tr("Foot round position"), QString::number(saildef.footRP), "%");
    painter->printDataLine(tr("Leech round"), QString::number(saildef.leechR), "mm");
    painter->printDataLine(tr("Leech round position"), QString::number(saildef.leechRP), "%");
    painter->printDataLine(tr("Gaff round"), QString::number(saildef.gaffR), "mm");
    painter->printDataLine(tr("Gaff round position"), QString::number(saildef.gaffRP), "%");

    // sail setting
    painter->printDataSection(tr("Sail settings"));
    painter->printDataLine(tr("Twist angle"), QString::number(saildef.twistDeg), "deg");
    painter->printDataLine(tr("Sheeting angle"), QString::number(saildef.sheetDeg), "deg");

    // cloth width, seam and hems width
    painter->printDataSection(tr("Cloth seams and hems"));
    painter->printDataLine(tr("Cloth width"), QString::number(saildef.clothW), "mm");
    painter->printDataLine(tr("Seams width"), QString::number(saildef.seamW), "mm");
    painter->printDataLine(tr("Leech hem width"), QString::number(saildef.leechHemW), "mm");
    painter->printDataLine(tr("Other hem width"), QString::number(saildef.hemsW), "mm");

    // sail mould
    painter->printDataSection(tr("Sail mould"));
    painter->printDataLine("", tr("Luff factor"), tr("Depth"), tr("Leech factor"));
    painter->printDataLine(
        tr("Top profile"),
        QString::number( saildef.mould.profile[2].getLuff() ),
        QString::number( saildef.mould.profile[2].getDepth()*100 )+ "%",
        QString::number( saildef.mould.profile[2].getLeech()*50));

    painter->printDataLine(
        tr("Mid profile at h = ") + QString::number( saildef.mould.vertpos ) + "%",
        QString::number( saildef.mould.profile[1].getLuff() ),
        QString::number( saildef.mould.profile[1].getDepth()*100 )+"%",
        QString::number( saildef.mould.profile[1].getLeech()*50));

    painter->printDataLine(
        tr("Bottom profile"),
        QString::number( saildef.mould.profile[0].getLuff() ),
        QString::number( saildef.mould.profile[0].getDepth()*100 )+"%",
        QString::number( saildef.mould.profile[0].getLeech()*50));
}


/** Print a developed sail.
 *
 * @param flatsail
 * @param painter
 * @param page
 */
void CSailDevelPrinter::print(const CPanelGroup &flatsail, CTextPainter *painter, size_t page) const
{
    painter->setFont(QFont("times", 10));

    // calculate logical rectangle
    real zoom = 0.8;
    CRect3d flatrect = flatsail.boundingRect();
    CRect3d logicalRect = calcLRect(painter->viewRect(), flatrect, flatrect.center(), zoom);

    // set coordinate system to match the logical viewport
    painter->setWindow(logicalRect);
    painter->setFontSize(10, zoom);

    painter->draw(flatsail[page]);
    if (showLabels)
        painter->drawLabels(flatsail[page]);

    painter->drawMarkers(flatsail[page]);

    // mark corners of cloth rectangle
    QPen oldpen = painter->pen();
    painter->setPen(Qt::green);
    CRect3d rp = flatsail[page].boundingRect();
    painter->drawCross(rp.min, painter->fontMetrics().height() );
    painter->drawCoord(rp.min, PI );
    painter->setPen(oldpen);
}


/** Print the drawing of a sail.
 *
 * @param sail
 * @param painter
 */
void CSailDrawingPrinter::print(const CPanelGroup &sail, CTextPainter *painter, size_t) const
{
    painter->setFont(QFont("times", 10));

    // center the sail
    CPanelGroup printSail = sail + CVector3d( -sail.boundingRect().center() );

    // calculate logical rectangle
    real zoom = 0.8;
    CRect3d logicalRect = calcLRect(painter->viewRect(), printSail.boundingRect(), CPoint3d(0,0,0), zoom);

    // set coordinate system to match the logical viewport
    painter->setWindow(logicalRect);
    painter->setFontSize(10, zoom);

    painter->draw(printSail);
    if (showLabels)
        painter->drawLabels(printSail);
}


