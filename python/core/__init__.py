# -*- coding: utf-8 -*-

"""
***************************************************************************
    __init__.py
    ---------------------
    Date                 : May 2014
    Copyright            : (C) 2014 by Nathan Woodrow
    Email                : woodrow dot nathan at gmail dot com
***************************************************************************
*                                                                         *
*   This program is free software; you can redistribute it and/or modify  *
*   it under the terms of the GNU General Public License as published by  *
*   the Free Software Foundation; either version 2 of the License, or     *
*   (at your option) any later version.                                   *
*                                                                         *
***************************************************************************
"""

__author__ = 'Nathan Woodrow'
__date__ = 'May 2014'
__copyright__ = '(C) 2014, Nathan Woodrow'
# This will get replaced with a git SHA1 when you do a git archive
__revision__ = '$Format:%H$'

from qgis.PyQt.QtCore import NULL
from qgis._core import *

from .additions.edit import edit, QgsEditError
from .additions.fromfunction import fromFunction
from .additions.processing import processing_output_layer_repr, processing_source_repr
from .additions.projectdirtyblocker import ProjectDirtyBlocker
from .additions.qgsdefaultvalue import _isValid
from .additions.qgsfeature import mapping_feature
from .additions.qgsfunction import register_function, qgsfunction
from .additions.qgsgeometry import _geometryNonZero, mapping_geometry
from .additions.qgstaskwrapper import QgsTaskWrapper
from .additions.readwritecontextentercategory import ReadWriteContextEnterCategory

# Injections into classes
QgsDefaultValue.__bool__ = _isValid
QgsFeature.__geo_interface__ = property(mapping_feature)
QgsGeometry.__bool__ = _geometryNonZero
QgsGeometry.__geo_interface__ = property(mapping_geometry)
QgsGeometry.__nonzero__ = _geometryNonZero
QgsProcessingFeatureSourceDefinition.__repr__ = processing_source_repr
QgsProcessingOutputLayerDefinition.__repr__ = processing_output_layer_repr
QgsProject.blockDirtying = ProjectDirtyBlocker
QgsReadWriteContext.enterCategory = ReadWriteContextEnterCategory
QgsTask.fromFunction = fromFunction
