/*!
* \file
* $HeadURL: http://visualsvn.edna.local/PD77/PD-77SENSE1/MODBUS_EXAMPLE/Modules/Modbus/CRC16.c $
* $LastChangedRevision: 3 $
*
* $Date: 2019-01-07 15:33:09 +0100 (ma, 07 jan 2019) $
* $LastChangedBy: geert $
*
* \par Company:
*	E.D.&A.\n
*
* \par Description:
*	CRC calculation ( same as Modbus/RTU CRC)\n
*/

/*-- Includes --*/
#include "emtype.h"
#include "emmacro.h"
#include "crc16.h"

/*-- Local definitions --*/
/*! \cond *//* Local definitions shouldn't be documented */


/* select algorithm */
#define M_ALGORITHM_FAST    0
#define M_ALGORITHM_SMALL   1

/*! \endcond *//* End of local definitions */

/*-- Local types --*/
/*! \cond *//* Local types shouldn't be documented */

/*! \endcond *//* End of local types */

/*-- Local data --*/


#if M_ALGORITHM_FAST

    /* CRC table 1 */
static M_ROMTYPE uint8_t aCRCTable1[256] = /* parasoft-suppress MISRA2004-8_7 "Define const data file at the top of file" */
{
    0x00U,0xc0U,0xc1U,0x01U,0xc3U,0x03U,0x02U,0xc2U,
    0xc6U,0x06U,0x07U,0xc7U,0x05U,0xc5U,0xc4U,0x04U,
    0xccU,0x0cU,0x0dU,0xcdU,0x0fU,0xcfU,0xceU,0x0eU,
    0x0aU,0xcaU,0xcbU,0x0bU,0xc9U,0x09U,0x08U,0xc8U,
    0xd8U,0x18U,0x19U,0xd9U,0x1bU,0xdbU,0xdaU,0x1aU,
    0x1eU,0xdeU,0xdfU,0x1fU,0xddU,0x1dU,0x1cU,0xdcU,
    0x14U,0xd4U,0xd5U,0x15U,0xd7U,0x17U,0x16U,0xd6U,
    0xd2U,0x12U,0x13U,0xd3U,0x11U,0xd1U,0xd0U,0x10U,
    0xf0U,0x30U,0x31U,0xf1U,0x33U,0xf3U,0xf2U,0x32U,
    0x36U,0xf6U,0xf7U,0x37U,0xf5U,0x35U,0x34U,0xf4U,
    0x3cU,0xfcU,0xfdU,0x3dU,0xffU,0x3fU,0x3eU,0xfeU,
    0xfaU,0x3aU,0x3bU,0xfbU,0x39U,0xf9U,0xf8U,0x38U,
    0x28U,0xe8U,0xe9U,0x29U,0xebU,0x2bU,0x2aU,0xeaU,
    0xeeU,0x2eU,0x2fU,0xefU,0x2dU,0xedU,0xecU,0x2cU,
    0xe4U,0x24U,0x25U,0xe5U,0x27U,0xe7U,0xe6U,0x26U,
    0x22U,0xe2U,0xe3U,0x23U,0xe1U,0x21U,0x20U,0xe0U,
    0xa0U,0x60U,0x61U,0xa1U,0x63U,0xa3U,0xa2U,0x62U,
    0x66U,0xa6U,0xa7U,0x67U,0xa5U,0x65U,0x64U,0xa4U,
    0x6cU,0xacU,0xadU,0x6dU,0xafU,0x6fU,0x6eU,0xaeU,
    0xaaU,0x6aU,0x6bU,0xabU,0x69U,0xa9U,0xa8U,0x68U,
    0x78U,0xb8U,0xb9U,0x79U,0xbbU,0x7bU,0x7aU,0xbaU,
    0xbeU,0x7eU,0x7fU,0xbfU,0x7dU,0xbdU,0xbcU,0x7cU,
    0xb4U,0x74U,0x75U,0xb5U,0x77U,0xb7U,0xb6U,0x76U,
    0x72U,0xb2U,0xb3U,0x73U,0xb1U,0x71U,0x70U,0xb0U,
    0x50U,0x90U,0x91U,0x51U,0x93U,0x53U,0x52U,0x92U,
    0x96U,0x56U,0x57U,0x97U,0x55U,0x95U,0x94U,0x54U,
    0x9cU,0x5cU,0x5dU,0x9dU,0x5fU,0x9fU,0x9eU,0x5eU,
    0x5aU,0x9aU,0x9bU,0x5bU,0x99U,0x59U,0x58U,0x98U,
    0x88U,0x48U,0x49U,0x89U,0x4bU,0x8bU,0x8aU,0x4aU,
    0x4eU,0x8eU,0x8fU,0x4fU,0x8dU,0x4dU,0x4cU,0x8cU,
    0x44U,0x84U,0x85U,0x45U,0x87U,0x47U,0x46U,0x86U,
    0x82U,0x42U,0x43U,0x83U,0x41U,0x81U,0x80U,0x40U
};

    /* CRC table 2 */
static M_ROMTYPE uint8_t aCRCTable2[256] = /* parasoft-suppress MISRA2004-8_7 "Define const data file at the top of file" */
{
    0x00U,0xc1U,0x81U,0x40U,0x01U,0xc0U,0x80U,0x41U,
    0x01U,0xc0U,0x80U,0x41U,0x00U,0xc1U,0x81U,0x40U,
    0x01U,0xc0U,0x80U,0x41U,0x00U,0xc1U,0x81U,0x40U,
    0x00U,0xc1U,0x81U,0x40U,0x01U,0xc0U,0x80U,0x41U,
    0x01U,0xc0U,0x80U,0x41U,0x00U,0xc1U,0x81U,0x40U,
    0x00U,0xc1U,0x81U,0x40U,0x01U,0xc0U,0x80U,0x41U,
    0x00U,0xc1U,0x81U,0x40U,0x01U,0xc0U,0x80U,0x41U,
    0x01U,0xc0U,0x80U,0x41U,0x00U,0xc1U,0x81U,0x40U,
    0x01U,0xc0U,0x80U,0x41U,0x00U,0xc1U,0x81U,0x40U,
    0x00U,0xc1U,0x81U,0x40U,0x01U,0xc0U,0x80U,0x41U,
    0x00U,0xc1U,0x81U,0x40U,0x01U,0xc0U,0x80U,0x41U,
    0x01U,0xc0U,0x80U,0x41U,0x00U,0xc1U,0x81U,0x40U,
    0x00U,0xc1U,0x81U,0x40U,0x01U,0xc0U,0x80U,0x41U,
    0x01U,0xc0U,0x80U,0x41U,0x00U,0xc1U,0x81U,0x40U,
    0x01U,0xc0U,0x80U,0x41U,0x00U,0xc1U,0x81U,0x40U,
    0x00U,0xc1U,0x81U,0x40U,0x01U,0xc0U,0x80U,0x41U,
    0x01U,0xc0U,0x80U,0x41U,0x00U,0xc1U,0x81U,0x40U,
    0x00U,0xc1U,0x81U,0x40U,0x01U,0xc0U,0x80U,0x41U,
    0x00U,0xc1U,0x81U,0x40U,0x01U,0xc0U,0x80U,0x41U,
    0x01U,0xc0U,0x80U,0x41U,0x00U,0xc1U,0x81U,0x40U,
    0x00U,0xc1U,0x81U,0x40U,0x01U,0xc0U,0x80U,0x41U,
    0x01U,0xc0U,0x80U,0x41U,0x00U,0xc1U,0x81U,0x40U,
    0x01U,0xc0U,0x80U,0x41U,0x00U,0xc1U,0x81U,0x40U,
    0x00U,0xc1U,0x81U,0x40U,0x01U,0xc0U,0x80U,0x41U,
    0x00U,0xc1U,0x81U,0x40U,0x01U,0xc0U,0x80U,0x41U,
    0x01U,0xc0U,0x80U,0x41U,0x00U,0xc1U,0x81U,0x40U,
    0x01U,0xc0U,0x80U,0x41U,0x00U,0xc1U,0x81U,0x40U,
    0x00U,0xc1U,0x81U,0x40U,0x01U,0xc0U,0x80U,0x41U,
    0x01U,0xc0U,0x80U,0x41U,0x00U,0xc1U,0x81U,0x40U,
    0x00U,0xc1U,0x81U,0x40U,0x01U,0xc0U,0x80U,0x41U,
    0x00U,0xc1U,0x81U,0x40U,0x01U,0xc0U,0x80U,0x41U,
    0x01U,0xc0U,0x80U,0x41U,0x00U,0xc1U,0x81U,0x40U
};

#endif

/*-- Private prototypes --*/

/*-- Public functions --*/


/*!
*	Calculate Modbus/RTU CRC
*
*	\param[in]		pucBuffer	Points to data buffer
*	\param[in]		Length		Number of bytes in data buffer
*	\param[out]		pusCRC		Points to variable that receives CRC when function returns
*/
#if M_ALGORITHM_FAST
 
void CalcCrc( uint8_t aBuffer[], uint32_t Length, uint16_t * pCRC)
{
    uint16_t Index;
    uint8_t  CRCh;
    uint8_t  CRCl;

    CRCh = 0xFFu;
    CRCl = 0xFFu;

    for(uint32_t CurrentByte = 0u; CurrentByte < Length ; CurrentByte++)
    {
        Index = (uint16_t)((uint16_t)aBuffer[CurrentByte] ^ (uint16_t)CRCh);
        CRCh = CRCl ^ aCRCTable2[Index];
        CRCl = aCRCTable1[Index];
    }

    *pCRC = (uint16_t)((uint16_t)CRCh << 8u) |  (uint16_t)CRCl;
}

#endif

#if M_ALGORITHM_SMALL

void CalcCrc( uint8_t aBuffer[], uint32_t Length, uint16_t* pCRC)
{
    uint32_t Index;
    uint16_t usCRC;

    usCRC = 0xFFFFu;
    
    for( Index = 0u; Index < Length; Index++)
    {
        uint8_t Carry;
        uint8_t i;

        usCRC ^= aBuffer[Index];
        for (i = 0u; i < 8u; i++)
        {
            Carry = (uint8_t)(usCRC & 0x0001u);
            usCRC >>= 1u;
            if (Carry != 0u)
            {
                usCRC ^= 0xA001u;
            }
        }
    }

    *pCRC = (usCRC << 8u) | (usCRC >> 8u);

    return;
}

#endif


/*-- Private functions --*/




