/*****************************************************************************
**
**  Copyright (c) 2015 Texas Instruments Incorporated.
**
******************************************************************************
**
**  DLP Spectrum Library
**
*****************************************************************************/

// Inclusion Guard
#ifndef _DLPSPEC_TYPES_H
#define _DLPSPEC_TYPES_H

#include "dlpspec_setup.h"

/* Return error codes */
typedef enum
{
	DLPSPEC_PASS                   =   0,
	ERR_DLPSPEC_FAIL               =  -1,
    ERR_DLPSPEC_INVALID_INPUT      =  -2,
    ERR_DLPSPEC_INSUFFICIENT_MEM   =  -3,
    ERR_DLPSPEC_TPL                =  -4,
	ERR_DLPSPEC_ILLEGAL_SCAN_TYPE  =  -5,
    ERR_DLPSPEC_NULL_POINTER       =  -6
}DLPSPEC_ERR_CODE;


// Supported data blob types for serializing and deserializing
typedef enum
{
// Library blob types: 0-127 reserved for future library expansion
    SCAN_DATA_TYPE      = 0,
    CFG_TYPE            = 1,
    CALIB_TYPE          = 2,
    REF_CAL_MATRIX_TYPE = 3,
// User extended blob types: 128-255 reserved for customer expansion
}BLOB_TYPES;

#define NUM_PIXEL_NM_COEFFS PX_TO_LAMBDA_NUM_POL_COEFF
#define NUM_SHIFT_VECTOR_COEFFS PX_TO_LAMBDA_NUM_POL_COEFF

/**
 * @brief Contains calibration coefficients generated by calibrating a spectrometer.
 * 
 * Stores the polynomial coefficients used when relating pixels to wavelengths
 * and for bending patterns to correct for mechanical tolerances which cause 
 * slit image rotation on the DMD array and optical distortions which cause 
 * curvature due to the out of plane angles on the grating. These coefficients 
 * are generated during calibration and should be stored in non-volitile 
 * protected memory in each spectrometer.
 */
typedef struct
{
    double  ShiftVectorCoeffs[NUM_SHIFT_VECTOR_COEFFS];
    double 	PixelToWavelengthCoeffs[NUM_PIXEL_NM_COEFFS];
}calibCoeffs;

#define CALIB_COEFFS_FORMAT "f#f#"

/**
 * @brief Describes a multi-frame wide frame buffer in memory
 * 
 * This structure contains descriptive information relating to a display frame
 * buffer such as the start pointer, the size of the palette, and its dimensions.
 */
typedef struct
{
    uint32_t *frameBuffer; /**< pointer to start of frame buffer memory */
    uint32_t numFBs; /**< number of consecutive buffers available to be filled with patterns */
    uint32_t width; /**< number of horizontal pixels in frame memory */
    uint32_t height; /**< number of vertical pixels in frame memory */
    uint32_t bpp; /**< number of bits per pixel */
}FrameBufferDescriptor;

/** @name Reference calibration matrix
 * 
 * These values define the reference calibration matrix, which is used when 
 * interpretting a stored reference to a different scan configuration with the
 * dlpspec_scan_interpReference() function.
 */

//@{

/** Number of tested pattern widths when collecting data for ::refCalMatrix. */
#define REF_CAL_INTERP_WIDTH 19

/** Number of tested wavelengths when collecting data for ::refCalMatrix. */
#define REF_CAL_INTERP_WAVELENGTH 50

/**
 * @brief DLP Spectrometer calibration coefficients
 * 
 * Constitutes the reference calibration matrix used by 
 * dlpspec_scan_interpReference() to interpret a stored reference to a different
 * scan configuration.
 */
typedef struct
{
/** The tested pattern widths for each scan when collecting data for ::refCalMatrix. */
uint8_t		width[REF_CAL_INTERP_WIDTH];
/** The tested wavelengths for each scan when collecting data for ::refCalMatrix. */
double		wavelength[REF_CAL_INTERP_WAVELENGTH];
/** Intensities measured at each pattern width and wavelength tested. */ 
uint16_t	ref_lookup[REF_CAL_INTERP_WIDTH][REF_CAL_INTERP_WAVELENGTH];
} refCalMatrix;

/** Format string for TPL serialization of refCalMatrix(). */
#define REF_CAL_MATRIX_FORMAT "c#f#v##"

/** Size of refCalMatrix() after serialized by TPL into a data blob. */
#define REF_CAL_MATRIX_BLOB_SIZE (sizeof(refCalMatrix)+100)
//@}

#endif //_DLPSPEC_TYPES_H
