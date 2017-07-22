#ifndef CUSTOMBITS_H_
#define CUSTOMBITS_H_

/* This file was generated 2017-07-22 */

/* Bit definitions for Amiga custom chips */

#define INTB_SETCLR             15
#define INTB_INTEN              14
#define INTB_ALL                 0
#define INTB_EXTER              13
#define INTB_DSKSYNC            12
#define INTB_RBF                11
#define INTB_AUD3               10
#define INTB_AUD2                9
#define INTB_AUD1                8
#define INTB_AUD0                7
#define INTB_BLIT                6
#define INTB_VERTB               5
#define INTB_COPER               4
#define INTB_PORTS               3
#define INTB_SOFTINT             2
#define INTB_DSKBLK              1
#define INTB_TBE                 0
#define INTF_SETCLR             0x8000
#define INTF_INTEN              0x4000
#define INTF_ALL                0x3FFF
#define INTF_EXTER              0x2000
#define INTF_DSKSYNC            0x1000
#define INTF_RBF                0x0800
#define INTF_AUD3               0x0400
#define INTF_AUD2               0x0200
#define INTF_AUD1               0x0100
#define INTF_AUD0               0x0080
#define INTF_BLIT               0x0040
#define INTF_VERTB              0x0020
#define INTF_COPER              0x0010
#define INTF_PORTS              0x0008
#define INTF_SOFTINT            0x0004
#define INTF_DSKBLK             0x0002
#define INTF_TBE                0x0001

#define DMAB_SETCLR             15
#define DMAB_BLTDONE            14
#define DMAB_BLTNZERO           13
#define DMAB_BLITHOG            10
#define DMAB_MASTER              9
#define DMAB_ALL                 0
#define DMAB_RASTER              8
#define DMAB_COPPER              7
#define DMAB_BLITTER             6
#define DMAB_SPRITE              5
#define DMAB_DISK                4
#define DMAB_AUDIO               0
#define DMAB_AUD3                3
#define DMAB_AUD2                2
#define DMAB_AUD1                1
#define DMAB_AUD0                0
#define DMAF_SETCLR             0x8000
#define DMAF_BLTDONE            0x4000
#define DMAF_BLTNZERO           0x2000
#define DMAF_BLITHOG            0x0400
#define DMAF_MASTER             0x0200
#define DMAF_ALL                0x01FF
#define DMAF_RASTER             0x0100
#define DMAF_COPPER             0x0080
#define DMAF_BLITTER            0x0040
#define DMAF_SPRITE             0x0020
#define DMAF_DISK               0x0010
#define DMAF_AUDIO              0x000F
#define DMAF_AUD3               0x0008
#define DMAF_AUD2               0x0004
#define DMAF_AUD1               0x0002
#define DMAF_AUD0               0x0001

#define VPOSB_LOF               15
#define VPOSB_V8                 0
#define VPOSF_LOF               0x8000
#define VPOSF_V8                0x0001

#define VHPOSB_V                 8
#define VHPOSB_H                 0
#define VHPOSF_V                0xFF00
#define VHPOSF_H                0x00FF

#define BPLCON0B_HIRES          15
#define BPLCON0B_BPU            12
#define BPLCON0B_BPU2           14
#define BPLCON0B_BPU1           13
#define BPLCON0B_BPU0           12
#define BPLCON0B_HOMOD          11
#define BPLCON0B_DBLPF          10
#define BPLCON0B_COLOR           9
#define BPLCON0B_GAUD            8
#define BPLCON0B_LPEN            3
#define BPLCON0B_LACE            2
#define BPLCON0B_ERSY            1
#define BPLCON0F_HIRES          0x8000
#define BPLCON0F_BPU            0x7000
#define BPLCON0F_BPU2           0x4000
#define BPLCON0F_BPU1           0x2000
#define BPLCON0F_BPU0           0x1000
#define BPLCON0F_HOMOD          0x0800
#define BPLCON0F_DBLPF          0x0400
#define BPLCON0F_COLOR          0x0200
#define BPLCON0F_GAUD           0x0100
#define BPLCON0F_LPEN           0x0008
#define BPLCON0F_LACE           0x0004
#define BPLCON0F_ERSY           0x0002

#define BPLCON1B_PF2H3           7
#define BPLCON1B_PF2H2           6
#define BPLCON1B_PF2H1           5
#define BPLCON1B_PF2H0           4
#define BPLCON1B_PF2H            4
#define BPLCON1B_PF1H3           3
#define BPLCON1B_PF1H2           2
#define BPLCON1B_PF1H1           1
#define BPLCON1B_PF1H0           0
#define BPLCON1B_PF1H            0
#define BPLCON1F_PF2H3          0x0080
#define BPLCON1F_PF2H2          0x0040
#define BPLCON1F_PF2H1          0x0020
#define BPLCON1F_PF2H0          0x0010
#define BPLCON1F_PF2H           0x00F0
#define BPLCON1F_PF1H3          0x0008
#define BPLCON1F_PF1H2          0x0004
#define BPLCON1F_PF1H1          0x0002
#define BPLCON1F_PF1H0          0x0001
#define BPLCON1F_PF1H           0x000F

#define SERDATB_OVRUN           15
#define SERDATB_RBF             14
#define SERDATB_TBE             13
#define SERDATB_TRSE            12
#define SERDATB_RXD             11
#define SERDATB_STP9             9
#define SERDATB_STP8             8
#define SERDATB_DB8              8
#define SERDATB_DB               0
#define SERDATF_OVRUN           0x8000
#define SERDATF_RBF             0x4000
#define SERDATF_TBE             0x2000
#define SERDATF_TRSE            0x1000
#define SERDATF_RXD             0x0800
#define SERDATF_STP9            0x0200
#define SERDATF_STP8            0x0100
#define SERDATF_DB8             0x0100
#define SERDATF_DB              0x00FF

#define SERPERB_LONG            15
#define SERPERB_RATE             0
#define SERPERB_BAUD230400       0
#define SERPERB_BAUD38400        0
#define SERPERB_BAUD9600         0
#define SERPERF_LONG            0x8000
#define SERPERF_RATE            0x7FFF
#define SERPERF_BAUD230400      0x000E
#define SERPERF_BAUD38400       0x005C
#define SERPERF_BAUD9600        0x0174

#define COLORB_R                 8
#define COLORB_G                 4
#define COLORB_B                 0
#define COLORF_R                0x0F00
#define COLORF_G                0x00F0
#define COLORF_B                0x000F

#define BEAMCON0B_HARDDIS       14
#define BEAMCON0B_LPENDIS       13
#define BEAMCON0B_VARVBEN       12
#define BEAMCON0B_LOLDIS        11
#define BEAMCON0B_CSCBEN        10
#define BEAMCON0B_VARVSYEN       9
#define BEAMCON0B_VARHSYEN       8
#define BEAMCON0B_VARBEAMEN      7
#define BEAMCON0B_DUAL           6
#define BEAMCON0B_PAL            5
#define BEAMCON0B_VARCSYEN       4
#define BEAMCON0B_BLANKEN        3
#define BEAMCON0B_CSYTRUE        2
#define BEAMCON0B_VSYTRUE        1
#define BEAMCON0B_HSYTRUE        0
#define BEAMCON0F_HARDDIS       0x4000
#define BEAMCON0F_LPENDIS       0x2000
#define BEAMCON0F_VARVBEN       0x1000
#define BEAMCON0F_LOLDIS        0x0800
#define BEAMCON0F_CSCBEN        0x0400
#define BEAMCON0F_VARVSYEN      0x0200
#define BEAMCON0F_VARHSYEN      0x0100
#define BEAMCON0F_VARBEAMEN     0x0080
#define BEAMCON0F_DUAL          0x0040
#define BEAMCON0F_PAL           0x0020
#define BEAMCON0F_VARCSYEN      0x0010
#define BEAMCON0F_BLANKEN       0x0008
#define BEAMCON0F_CSYTRUE       0x0004
#define BEAMCON0F_VSYTRUE       0x0002
#define BEAMCON0F_HSYTRUE       0x0001

#define POTGOB_OUTRY            15
#define POTGOB_DATRY            14
#define POTGOB_OUTRX            13
#define POTGOB_DATRX            12
#define POTGOB_OUTLY            11
#define POTGOB_DATLY            10
#define POTGOB_OUTLX             9
#define POTGOB_DATLX             8
#define POTGOB_START             0
#define POTGOF_OUTRY            0x8000
#define POTGOF_DATRY            0x4000
#define POTGOF_OUTRX            0x2000
#define POTGOF_DATRX            0x1000
#define POTGOF_OUTLY            0x0800
#define POTGOF_DATLY            0x0400
#define POTGOF_OUTLX            0x0200
#define POTGOF_DATLX            0x0100
#define POTGOF_START            0x0001

#define BLTCON0B_ASH            12
#define BLTCON0B_USEA           11
#define BLTCON0B_USEB           10
#define BLTCON0B_USEC            9
#define BLTCON0B_USED            8
#define BLTCON0B_LF              0
#define BLTCON0B_START          12
#define BLTCON0F_ASH            0xF000
#define BLTCON0F_USEA           0x0800
#define BLTCON0F_USEB           0x0400
#define BLTCON0F_USEC           0x0200
#define BLTCON0F_USED           0x0100
#define BLTCON0F_LF             0x00FF
#define BLTCON0F_START          0xF000

#define BLTCON1B_BSH            12
#define BLTCON1B_DOFF            7
#define BLTCON1B_EFE             4
#define BLTCON1B_IFE             3
#define BLTCON1B_FCI             2
#define BLTCON1B_DESC            1
#define BLTCON1B_LINE            0
#define BLTCON1B_TEXTURE        12
#define BLTCON1B_SIGN            6
#define BLTCON1B_SUD             4
#define BLTCON1B_SUL             3
#define BLTCON1B_AUL             2
#define BLTCON1B_SING            1
#define BLTCON1B_OCT             2
#define BLTCON1B_OCT0            2
#define BLTCON1B_OCT1            2
#define BLTCON1B_OCT2            2
#define BLTCON1B_OCT3            2
#define BLTCON1B_OCT4            2
#define BLTCON1B_OCT5            2
#define BLTCON1B_OCT6            2
#define BLTCON1B_OCT7            2
#define BLTCON1F_BSH            0xF000
#define BLTCON1F_DOFF           0x0080
#define BLTCON1F_EFE            0x0010
#define BLTCON1F_IFE            0x0008
#define BLTCON1F_FCI            0x0004
#define BLTCON1F_DESC           0x0002
#define BLTCON1F_LINE           0x0001
#define BLTCON1F_TEXTURE        0xF000
#define BLTCON1F_SIGN           0x0040
#define BLTCON1F_SUD            0x0010
#define BLTCON1F_SUL            0x0008
#define BLTCON1F_AUL            0x0004
#define BLTCON1F_SING           0x0002
#define BLTCON1F_OCT            0x001C
#define BLTCON1F_OCT0           0x0018
#define BLTCON1F_OCT1           0x0004
#define BLTCON1F_OCT2           0x000C
#define BLTCON1F_OCT3           0x001C
#define BLTCON1F_OCT4           0x0014
#define BLTCON1F_OCT5           0x0008
#define BLTCON1F_OCT6           0x0000
#define BLTCON1F_OCT7           0x0010

#define BLTSIZEB_H               6
#define BLTSIZEB_W               0
#define BLTSIZEF_H              0xFFC0
#define BLTSIZEF_W              0x003F

/* Register offsets from CUSTOMBASE */

#define BLTCON0         0x040
#define BLTCON1         0x042
#define BLTSIZE         0x058
#define DIWSTRT         0x08E
#define DIWSTOP         0x090
#define DDFSTRT         0x092
#define DDFSTOP         0x094
#define BPL1PTH         0x0E0
#define BPL1PTL         0x0E2
#define BPL2PTH         0x0E4
#define BPL2PTL         0x0E6
#define BPL3PTH         0x0E8
#define BPL3PTL         0x0EA
#define BPL4PTH         0x0EC
#define BPL4PTL         0x0EE
#define BPL5PTH         0x0F0
#define BPL5PTL         0x0F2
#define BPL6PTH         0x0F4
#define BPL6PTL         0x0F6
#define BPLCON0         0x100
#define BPLCON1         0x102
#define BPL1MOD         0x108
#define BPL2MOD         0x10A
#define COLOR00         0x180
#define COLOR01         0x182
#define COLOR02         0x184
#define COLOR03         0x186
#define COLOR04         0x188
#define COLOR05         0x18A
#define COLOR06         0x18C
#define COLOR07         0x18E
#define COLOR08         0x190
#define COLOR09         0x192
#define COLOR10         0x194
#define COLOR11         0x196
#define COLOR12         0x198
#define COLOR13         0x19A
#define COLOR14         0x19C
#define COLOR15         0x19E
#define COLOR16         0x1A0
#define COLOR17         0x1A2
#define COLOR18         0x1A4
#define COLOR19         0x1A6
#define COLOR20         0x1A8
#define COLOR21         0x1AA
#define COLOR22         0x1AC
#define COLOR23         0x1AE
#define COLOR24         0x1B0
#define COLOR25         0x1B2
#define COLOR26         0x1B4
#define COLOR27         0x1B6
#define COLOR28         0x1B8
#define COLOR29         0x1BA
#define COLOR30         0x1BC
#define COLOR31         0x1BE
#define BEAMCON0        0x1DC

#endif

