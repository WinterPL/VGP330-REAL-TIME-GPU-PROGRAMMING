#if 0
//
// Generated by Microsoft (R) D3D Shader Disassembler
//
//
// Input signature:
//
// Name                 Index   Mask Register SysValue  Format   Used
// -------------------- ----- ------ -------- -------- ------- ------
// SV_POSITION              0   xyzw        0      POS   float       
// COLOR                    0   xyzw        1     NONE   float   xyzw
// TEXCOORD                 0   xy          2     NONE   float       
// TEXCOORD                 1   xyz         3     NONE   float       
// TEXCOORD                 2   xyz         4     NONE   float       
// TEXCOORD                 3   xyz         5     NONE   float       
// TEXCOORD                 4   xyzw        6     NONE   float       
// TEXCOORD                 5   xyz         7     NONE   float       
//
//
// Output signature:
//
// Name                 Index   Mask Register SysValue  Format   Used
// -------------------- ----- ------ -------- -------- ------- ------
// SV_Target                0   xyzw        0   TARGET   float   xyzw
//
//
// Level9 shader bytecode:
//
    ps_2_0
    dcl t0  // pixel<4,5,6,7>

#line 79 "C:\Users\LCV2132501\source\VGP330-REAL-TIME-GPU-PROGRAMMING\Workspace\WNTRengine\External\DirectXTK\src\Shaders\DGSLUnlit.hlsl"
    mov oC0, t0  // ::main<0,1,2,3>

// approximately 1 instruction slot used
ps_4_0
dcl_input_ps linear v1.xyzw
dcl_output o0.xyzw
mov o0.xyzw, v1.xyzw
ret 
// Approximately 0 instruction slots used
#endif

const BYTE DGSLUnlit_main[] =
{
     68,  88,  66,  67, 119, 253, 
    225,   5, 169, 224, 115, 172, 
     46,  25, 169,  93, 144, 197, 
    172, 145,   1,   0,   0,   0, 
    244,   3,   0,   0,   4,   0, 
      0,   0,  48,   0,   0,   0, 
    148,   2,   0,   0, 212,   2, 
      0,   0, 192,   3,   0,   0, 
     65, 111, 110,  57,  92,   2, 
      0,   0,  92,   2,   0,   0, 
      0,   2, 255, 255,  56,   2, 
      0,   0,  36,   0,   0,   0, 
      0,   0,  36,   0,   0,   0, 
     36,   0,   0,   0,  36,   0, 
      0,   0,  36,   0,   0,   0, 
     36,   0,   0,   2, 255, 255, 
    254, 255, 133,   0,  68,  66, 
     85,  71,  40,   0,   0,   0, 
    232,   1,   0,   0,   0,   0, 
      0,   0,   1,   0,   0,   0, 
    168,   0,   0,   0,   2,   0, 
      0,   0, 172,   0,   0,   0, 
      2,   0,   0,   0, 192,   1, 
      0,   0, 188,   0,   0,   0, 
     67,  58,  92,  85, 115, 101, 
    114, 115,  92,  76,  67,  86, 
     50,  49,  51,  50,  53,  48, 
     49,  92, 115, 111, 117, 114, 
     99, 101,  92,  86,  71,  80, 
     51,  51,  48,  45,  82,  69, 
     65,  76,  45,  84,  73,  77, 
     69,  45,  71,  80,  85,  45, 
     80,  82,  79,  71,  82,  65, 
     77,  77,  73,  78,  71,  92, 
     87, 111, 114, 107, 115, 112, 
     97,  99, 101,  92,  87,  78, 
     84,  82, 101, 110, 103, 105, 
    110, 101,  92,  69, 120, 116, 
    101, 114, 110,  97, 108,  92, 
     68, 105, 114, 101,  99, 116, 
     88,  84,  75,  92, 115, 114, 
     99,  92,  83, 104,  97, 100, 
    101, 114, 115,  92,  68,  71, 
     83,  76,  85, 110, 108, 105, 
    116,  46, 104, 108, 115, 108, 
      0, 171,  40,   0,   0,   0, 
      0,   0, 255, 255,  28,   2, 
      0,   0,  79,   0,   0,   0, 
     40,   2,   0,   0, 109,  97, 
    105, 110,   0, 102, 114,  97, 
    103, 109, 101, 110, 116,   0, 
    171, 171,   1,   0,   3,   0, 
      1,   0,   4,   0,   1,   0, 
      0,   0,   0,   0,   0,   0, 
    193,   0,   0,   0, 204,   0, 
      0,   0,   5,   0,   0,   0, 
      1,   0,   4,   0,   1,   0, 
      1,   0, 220,   0,   0,   0, 
      1,   0,   0,   0,   0,   0, 
      1,   0,   2,   0,   3,   0, 
    112, 105, 120, 101, 108,   0, 
    112, 111, 115,   0, 100, 105, 
    102, 102, 117, 115, 101,   0, 
    117, 118,   0, 171, 171, 171, 
      1,   0,   3,   0,   1,   0, 
      2,   0,   1,   0,   0,   0, 
      0,   0,   0,   0, 119, 111, 
    114, 108, 100,  78, 111, 114, 
    109,   0, 171, 171,   1,   0, 
      3,   0,   1,   0,   3,   0, 
      1,   0,   0,   0,   0,   0, 
      0,   0, 119, 111, 114, 108, 
    100,  80, 111, 115,   0, 116, 
    111,  69, 121, 101,   0, 116, 
     97, 110, 103, 101, 110, 116, 
      0, 110, 111, 114, 109,  97, 
    108,   0, 171, 171,   6,   1, 
      0,   0, 204,   0,   0,   0, 
     10,   1,   0,   0, 204,   0, 
      0,   0,  18,   1,   0,   0, 
     24,   1,   0,   0,  40,   1, 
      0,   0,  52,   1,   0,   0, 
     68,   1,   0,   0,  52,   1, 
      0,   0,  77,   1,   0,   0, 
     52,   1,   0,   0,  83,   1, 
      0,   0, 204,   0,   0,   0, 
     91,   1,   0,   0,  52,   1, 
      0,   0,   5,   0,   0,   0, 
      1,   0,  26,   0,   1,   0, 
      8,   0, 100,   1,   0,   0, 
      0,   0,   0,   0,   4,   0, 
      5,   0,   6,   0,   7,   0, 
      0,   0,   0,   0, 188,   0, 
      0,   0, 228,   0,   0,   0, 
      1,   0,   0,   0, 244,   0, 
      0,   0, 188,   0,   0,   0, 
      0,   1,   0,   0, 164,   1, 
      0,   0,   1,   0,   0,   0, 
    180,   1,   0,   0,  77, 105, 
     99, 114, 111, 115, 111, 102, 
    116,  32,  40,  82,  41,  32, 
     72,  76,  83,  76,  32,  83, 
    104,  97, 100, 101, 114,  32, 
     67, 111, 109, 112, 105, 108, 
    101, 114,  32,  49,  48,  46, 
     49,   0,  31,   0,   0,   2, 
      0,   0,   0, 128,   0,   0, 
     15, 176,   1,   0,   0,   2, 
      0,   8,  15, 128,   0,   0, 
    228, 176, 255, 255,   0,   0, 
     83,  72,  68,  82,  56,   0, 
      0,   0,  64,   0,   0,   0, 
     14,   0,   0,   0,  98,  16, 
      0,   3, 242,  16,  16,   0, 
      1,   0,   0,   0, 101,   0, 
      0,   3, 242,  32,  16,   0, 
      0,   0,   0,   0,  54,   0, 
      0,   5, 242,  32,  16,   0, 
      0,   0,   0,   0,  70,  30, 
     16,   0,   1,   0,   0,   0, 
     62,   0,   0,   1,  73,  83, 
     71,  78, 228,   0,   0,   0, 
      8,   0,   0,   0,   8,   0, 
      0,   0, 200,   0,   0,   0, 
      0,   0,   0,   0,   1,   0, 
      0,   0,   3,   0,   0,   0, 
      0,   0,   0,   0,  15,   0, 
      0,   0, 212,   0,   0,   0, 
      0,   0,   0,   0,   0,   0, 
      0,   0,   3,   0,   0,   0, 
      1,   0,   0,   0,  15,  15, 
      0,   0, 218,   0,   0,   0, 
      0,   0,   0,   0,   0,   0, 
      0,   0,   3,   0,   0,   0, 
      2,   0,   0,   0,   3,   0, 
      0,   0, 218,   0,   0,   0, 
      1,   0,   0,   0,   0,   0, 
      0,   0,   3,   0,   0,   0, 
      3,   0,   0,   0,   7,   0, 
      0,   0, 218,   0,   0,   0, 
      2,   0,   0,   0,   0,   0, 
      0,   0,   3,   0,   0,   0, 
      4,   0,   0,   0,   7,   0, 
      0,   0, 218,   0,   0,   0, 
      3,   0,   0,   0,   0,   0, 
      0,   0,   3,   0,   0,   0, 
      5,   0,   0,   0,   7,   0, 
      0,   0, 218,   0,   0,   0, 
      4,   0,   0,   0,   0,   0, 
      0,   0,   3,   0,   0,   0, 
      6,   0,   0,   0,  15,   0, 
      0,   0, 218,   0,   0,   0, 
      5,   0,   0,   0,   0,   0, 
      0,   0,   3,   0,   0,   0, 
      7,   0,   0,   0,   7,   0, 
      0,   0,  83,  86,  95,  80, 
     79,  83,  73,  84,  73,  79, 
     78,   0,  67,  79,  76,  79, 
     82,   0,  84,  69,  88,  67, 
     79,  79,  82,  68,   0, 171, 
     79,  83,  71,  78,  44,   0, 
      0,   0,   1,   0,   0,   0, 
      8,   0,   0,   0,  32,   0, 
      0,   0,   0,   0,   0,   0, 
      0,   0,   0,   0,   3,   0, 
      0,   0,   0,   0,   0,   0, 
     15,   0,   0,   0,  83,  86, 
     95,  84,  97, 114, 103, 101, 
    116,   0, 171, 171
};
