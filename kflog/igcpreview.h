/***********************************************************************
**
**   igcpreview.h
**
**   This file is part of KFLog2.
**
************************************************************************
**
**   Copyright (c):  2001 by Heiner Lamprecht, Florian Ehinger
**
**   This file is distributed under the terms of the General Public
**   Licence. See the file COPYING for more information.
**
**   $Id$
**
***********************************************************************/

#ifndef IGCPREVIEW_H
#define IGCPREVIEW_H

#include <kpreviewwidgetbase.h>

#include <qlabel.h>

/**
 * Provides a file-preview in the open-file-dialog. Only the header of
 * a local igc-file is displayed. Non-local files are not used. The
 * preview displays the date, the pilotname, the glider-type and -id and
 * the name of the waypoints.
 *
 * @author Heiner Lamprecht, Florian Ehinger
 * @version $Id$
 */
class IGCPreview : public KPreviewWidgetBase
{
  Q_OBJECT

  public:
    /**
     * Creates a preview-widget.
     *
     * @param  parent  The parent widget of the preview-widget
     */
    IGCPreview(QWidget* parent);
    /**
     * Destructor
     */
    ~IGCPreview();

  public slots:
    /**
     * This slot is called every time the user selects another file in
     * the file dialog. Reimplemented from KPreviewWidgetBase.
     *
     * @param  url  The url of the selected file
     */
    virtual void showPreview(const KURL &url);
    /**
     * This is called when e.g. the selection is cleared or when multiple
     * selections exist, or the directory is changed. Reimplemented from
     * KPreviewWidgetBase.
     */
    virtual void clearPreview();

  private:
    /**
     * The text-label in which the preview will be shown.
     */
    QLabel* textLabel;
};

#endif
