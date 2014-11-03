/*
 * libgnomonic - Gnomonic projection algorithms library
 *
 * Copyright (c) 2013-2014 FOXEL SA - http://foxel.ch
 * Please read <http://foxel.ch/license> for more information.
 *
 *
 * Author(s):
 *
 *      Nils Hamel <n.hamel@foxel.ch>
 *
 * Contributor(s) :
 * 
 *      Stephane Flotron <s.flotron@foxel.ch>
 *
 * 
 * This file is part of the FOXEL project <http://foxel.ch>.
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU Affero General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU Affero General Public License for more details.
 *
 * You should have received a copy of the GNU Affero General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 *
 *
 * Additional Terms:
 *
 *      You are required to preserve legal notices and author attributions in
 *      that material or in the Appropriate Legal Notices displayed by works
 *      containing it.
 *
 *      You are required to attribute the work as explained in the "Usage and
 *      Attribution" section of <http://foxel.ch/license>.
 */

    /*! \file   gnomonic-ttg.h
     *  \author Nils Hamel <n.hamel@foxel.ch>
     *
     *  Equirectangular tile to rectilinear transformation
     */

/*
    Header - Include guard
 */

    # ifndef __LG_TTG__
    # define __LG_TTG__

/*
    Header - C/C++ compatibility
 */

    # ifdef __cplusplus
    extern "C" {
    # endif

/*
    Header - Includes
 */

    # include "gnomonic.h"
    # include "gnomonic-algebra.h"

/*
    Header - Preprocessor definitions
 */

/*
    Header - Preprocessor macros
 */

/*
    Header - Typedefs
 */

/*
    Header - Structures
 */

/*
    Header - Function prototypes
 */

    lg_Void_t lg_ttg_center(

        li_C8_t     const * const lgeBitmap,
        lg_Size_t   const         lgeWidth,
        lg_Size_t   const         lgeHeight,
        lg_Size_t   const         lgeLayers,
        li_C8_t           * const lgrBitmap,
        lg_Size_t   const         lgrWidth,
        lg_Size_t   const         lgrHeight,
        lg_Size_t   const         lgrLayers,
        lg_Size_t   const         lgmWidth,
        lg_Size_t   const         lgmHeight,
        lg_Size_t   const         lgmCornerX,
        lg_Size_t   const         lgmCornerY,
        lg_Real_t   const         lgAzim,
        lg_Real_t   const         lgElev,
        lg_Real_t   const         lgRoll,
        lg_Real_t   const         lgFocal,
        lg_Real_t   const         lgPixel,
        li_Method_t const         lgInter

    );

    lg_Void_t lg_ttg_elphel(

        li_C8_t     const * const lgeBitmap,
        lg_Size_t   const         lgeWidth,
        lg_Size_t   const         lgeHeight,
        lg_Size_t   const         lgeLayers,
        li_C8_t           * const lgrBitmap,
        lg_Size_t   const         lgrWidth,
        lg_Size_t   const         lgrHeight,
        lg_Size_t   const         lgrLayers,
        lg_Real_t   const         lgrSightX,
        lg_Real_t   const         lgrSightY,
        lg_Size_t   const         lgmWidth,
        lg_Size_t   const         lgmHeight,
        lg_Size_t   const         lgmCornerX,
        lg_Size_t   const         lgmCornerY,
        lg_Real_t   const         lgRoll,
        lg_Real_t   const         lgAzim,
        lg_Real_t   const         lgElev,
        lg_Real_t   const         lgHead,
        lg_Real_t   const         lgPixel,
        lg_Real_t   const         lgFocal,
        li_Method_t const         lgInter

    );

    /*! \brief Equirectangular tile to rectilinear fixed focal gnomonic projection
     * 
     *  This function performs a gnomonic reprojection of an equirectangular
     *  tile extracted from an entire equirectangular mapping. The obtained
     *  rectilinear image can have an arbitrary size taking into account that
     *  scaling of pixels is set through focal length and pixel length, assumed
     *  to be identical in both direction.
     *  
     *  The input equirectangular tile has to be a three or four chromatic 
     *  layers image and the output rectilinear image has to be already allocated
     *  according to its parameters and has to come with three or four chromatic
     *  layers. The bitmaps are standard bitmaps that considers byte padding in
     *  memory.
     *
     *  In order to perform the desired projection, the following 3d-frame is 
     *  attached to the entire equirectangular mapping from which the tile is 
     *  extracted : the x-axis points the left edge of the mapping at half height.
     *  The y-axis points at third fourth of the mapping width and at half of its
     *  height. The z-axis is obtained using a cross-product, inducing a direct
     *  frame.
     *
     *  The rectilinear image has its center attached to the x-axis and the image
     *  plane is orthogonal to this same x-axis. The rotation matrix is built as
     *  follows : 
     * 
     *      M = Rz(Azimut)Ry(Elevation)Rx(Roll)
     *
     *  and corresponds to the rotation that brings the rectilinear image pixels
     *  on the equirectangular mapping.
     *
     *  \param lgeBitmap      Pointer to equirectangular tile bitmap
     *  \param lgeWidth       Width, in pixels, of the equirectangular tile
     *                        bitmap
     *  \param lgeHeight      Height, in pixels, of the equirectangular tile
     *                        bitmap
     *  \param lgeLayers      Depth, in chromatic layer count, of equirectangular 
     *                        tile bitmap
     *  \param lgrBitmap      Pointer to rectilinear bitmap that recieve the 
     *                        gnomonic projection
     *  \param lgrWidth       Width, in pixels, of the rectilinear bitmap
     *  \param lgrHeight      Height, in pixels, of the rectilinear bitmap
     *  \param lgrLayers      Depth, in chromatic layer count, of rectilinear 
     *                        bitmap
     *  \param lgrSightX      Position X, in pixels on rectilinear image,of the
     *                        projection center
     *  \param lgrSightY      Position Y, in pixels on rectilinear image,of the
     *                        projection center
     *  \param lgMapWidth     Width, in pixels, of the entire equirectangular 
     *                        mapping
     *  \param lgMapHeight    Height, in pixels, of the entire equirectangular 
     *                        mapping
     *  \param lgMapCornerX   Position x, in pixels, of the equirectangular tile
     *                        top-left corner in the entire mapping
     *  \param lgMapCornerY   Position y, in pixels, of the equirectangular tile
     *                        top-left corner in the entire mapping
     *  \param lgAzim         Azimut angle, in radians
     *  \param lgElev         Elevation angle, in radians
     *  \param lgRoll         Roll angle, in radians
     *  \param lgFocal        Focal length, in mm, of the rectilinear image
     *  \param lgPixel        Length, in mm, of the pixels of the rectilinear
     *                        image virtual camera
     *  \param lgInter        Pointer to interpolation method function
     */

    lg_Void_t lg_ttg_generic(

        li_C8_t     const * const lgeBitmap,
        lg_Size_t   const         lgeWidth,
        lg_Size_t   const         lgeHeight,
        lg_Size_t   const         lgeLayers,
        li_C8_t           * const lgrBitmap,
        lg_Size_t   const         lgrWidth,
        lg_Size_t   const         lgrHeight,
        lg_Size_t   const         lgrLayers,
        lg_Real_t   const         lgrSightX,
        lg_Real_t   const         lgrSightY,
        lg_Size_t   const         lgMapWidth,
        lg_Size_t   const         lgMapHeight,
        lg_Size_t   const         lgMapCornerX,
        lg_Size_t   const         lgMapCornerY,
        lg_Real_t   const         lgAzim,
        lg_Real_t   const         lgElev,
        lg_Real_t   const         lgRoll,
        lg_Real_t   const         lgFocal,
        lg_Real_t   const         lgPixel,
        li_Method_t const         lgInter

    );

/*
    Header - C/C++ compatibility
 */

    # ifdef __cplusplus
    }
    # endif

/*
    Header - Include guard
 */

    # endif

