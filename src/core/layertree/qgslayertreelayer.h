/***************************************************************************
  qgslayertreelayer.h
  --------------------------------------
  Date                 : May 2014
  Copyright            : (C) 2014 by Martin Dobias
  Email                : wonder dot sk at gmail dot com
 ***************************************************************************
 *                                                                         *
 *   This program is free software; you can redistribute it and/or modify  *
 *   it under the terms of the GNU General Public License as published by  *
 *   the Free Software Foundation; either version 2 of the License, or     *
 *   (at your option) any later version.                                   *
 *                                                                         *
 ***************************************************************************/

#ifndef QGSLAYERTREELAYER_H
#define QGSLAYERTREELAYER_H

#include "qgis_core.h"
#include "qgis.h"
#include "qgslayertreenode.h"
#include "qgsmaplayerref.h"
#include "qgsreadwritecontext.h"

class QgsMapLayer;

/**
 * \ingroup core
 * Layer tree node points to a map layer.
 *
 * The node can exist also without a valid instance of a layer (just ID). That
 * means the referenced layer does not need to be loaded in order to use it
 * in layer tree. In such case, resolveReferences() method can be called
 * once the layer is loaded.
 *
 * A map layer is supposed to be present in one layer tree just once. It is
 * however possible that temporarily a layer exists in one tree more than just
 * once, e.g. while reordering items with drag and drop.
 *
 * \since QGIS 2.4
 */
class CORE_EXPORT QgsLayerTreeLayer : public QgsLayerTreeNode
{
    Q_OBJECT
  public:
    explicit QgsLayerTreeLayer( QgsMapLayer *layer );

#ifndef SIP_RUN
    QgsLayerTreeLayer( const QgsLayerTreeLayer &other );
#endif

    /**
     * Constructor for QgsLayerTreeLayer using weak references to layer ID, \a name, public \a source, and \a provider key.
     */
    explicit QgsLayerTreeLayer( const QString &layerId, const QString &name = QString(), const QString &source = QString(), const QString &provider = QString() );

    QString layerId() const { return mRef.layerId; }

    QgsMapLayer *layer() const { return mRef.get(); }

    /**
     * Returns the layer's name.
     * \since QGIS 3.0
     */
    QString name() const override;

    /**
     * Sets the layer's name.
     * \since QGIS 3.0
     */
    void setName( const QString &n ) override;

    /**
     * Read layer node from XML. Returns new instance.
     * Does not resolve textual references to layers. Call resolveReferences() afterwards to do it.
     */
    static QgsLayerTreeLayer *readXml( QDomElement &element, const QgsReadWriteContext &context ) SIP_FACTORY;

    /**
     * Read layer node from XML. Returns new instance.
     * Also resolves textual references to layers from the project (calls resolveReferences() internally).
     * \since QGIS 3.0
     */
    static QgsLayerTreeLayer *readXml( QDomElement &element, const QgsProject *project, const QgsReadWriteContext &context ) SIP_FACTORY;

    void writeXml( QDomElement &parentElement, const QgsReadWriteContext &context ) override;

    QString dump() const override;

    QgsLayerTreeLayer *clone() const override SIP_FACTORY;

    /**
     * Resolves reference to layer from stored layer ID (if it has not been resolved already)
     * \since QGIS 3.0
     */
    void resolveReferences( const QgsProject *project, bool looseMatching = false ) override;

  signals:

    /**
     * Emitted when a previously unavailable layer got loaded.
     */
    void layerLoaded();

    /**
     * Emitted when a previously available layer got unloaded (from layer registry).
     * \since QGIS 2.6
     */
    void layerWillBeUnloaded();

  protected:
    void attachToLayer();

    //! Weak reference to the layer (or just it's ID if the reference is not resolved yet)
    QgsMapLayerRef mRef;
    //! Layer name - only used if layer does not exist
    QString mLayerName;

  private slots:

    /**
     * Emits a nameChanged() signal if layer's name has changed
     * \since QGIS 3.0
     */
    void layerNameChanged();

    /**
     * Handles the event of deletion of the referenced layer
     * \since QGIS 3.0
     */
    void layerWillBeDeleted();

  private:

#ifdef SIP_RUN

    /**
     * Copies are not allowed
     */
    QgsLayerTreeLayer( const QgsLayerTreeLayer &other );
#endif
};



#endif // QGSLAYERTREELAYER_H
