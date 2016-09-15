#include "tinytensor_math.h"
#include <assert.h>

//not including header because of macro definition conflicts
extern uint32_t FixedPointExp2Q10(const int16_t x);

const static int16_t k_tanh_slopes[1024] = {32767,32766,32764,32761,32757,32752,32746,32739,32731,32722,32712,32701,32689,32677,32663,32648,32632,32615,32597,32578,32558,32537,32516,32493,32469,32444,32419,32392,32365,32336,32307,32276,32245,32213,32179,32145,32110,32074,32037,32000,31961,31921,31881,31839,31797,31754,31710,31665,31619,31572,31525,31476,31427,31377,31326,31274,31222,31168,31114,31059,31003,30947,30889,30831,30772,30713,30652,30591,30529,30466,30403,30339,30274,30208,30142,30075,30007,29939,29870,29800,29730,29659,29587,29514,29442,29368,29294,29219,29143,29067,28991,28914,28836,28758,28679,28599,28519,28439,28358,28276,28194,28112,28029,27945,27861,27777,27692,27606,27521,27434,27348,27261,27173,27085,26997,26908,26819,26730,26640,26550,26459,26368,26277,26185,26094,26001,25909,25816,25723,25630,25536,25442,25348,25254,25159,25065,24970,24874,24779,24683,24587,24491,24395,24298,24202,24105,24008,23911,23814,23717,23619,23522,23424,23326,23228,23130,23032,22934,22836,22738,22640,22541,22443,22344,22246,22147,22049,21950,21852,21753,21655,21556,21458,21359,21261,21162,21064,20966,20867,20769,20671,20573,20475,20377,20279,20181,20084,19986,19889,19791,19694,19597,19500,19403,19306,19210,19113,19017,18921,18825,18729,18633,18538,18442,18347,18252,18157,18063,17968,17874,17780,17686,17592,17499,17406,17313,17220,17128,17035,16943,16851,16760,16668,16577,16486,16395,16305,16215,16125,16035,15946,15857,15768,15679,15591,15503,15415,15328,15240,15153,15067,14980,14894,14809,14723,14638,14553,14468,14384,14300,14216,14133,14050,13967,13884,13802,13720,13639,13558,13477,13396,13316,13236,13156,13077,12998,12919,12840,12762,12685,12607,12530,12453,12377,12301,12225,12150,12074,12000,11925,11851,11777,11704,11631,11558,11485,11413,11341,11270,11199,11128,11057,10987,10917,10848,10779,10710,10641,10573,10505,10438,10371,10304,10238,10171,10106,10040,9975,9910,9846,9781,9718,9654,9591,9528,9465,9403,9341,9280,9219,9158,9097,9037,8977,8917,8858,8799,8741,8682,8624,8567,8509,8452,8395,8339,8283,8227,8172,8116,8062,8007,7953,7899,7845,7792,7739,7686,7634,7582,7530,7479,7427,7377,7326,7276,7226,7176,7127,7077,7029,6980,6932,6884,6836,6789,6742,6695,6649,6602,6556,6511,6465,6420,6375,6331,6286,6242,6199,6155,6112,6069,6026,5984,5942,5900,5858,5817,5776,5735,5695,5654,5614,5574,5535,5496,5456,5418,5379,5341,5303,5265,5227,5190,5153,5116,5080,5043,5007,4971,4936,4900,4865,4830,4795,4761,4726,4692,4659,4625,4592,4558,4526,4493,4460,4428,4396,4364,4332,4301,4270,4239,4208,4177,4147,4117,4087,4057,4028,3998,3969,3940,3911,3883,3854,3826,3798,3770,3743,3715,3688,3661,3634,3607,3581,3555,3528,3502,3477,3451,3426,3400,3375,3350,3326,3301,3277,3253,3229,3205,3181,3158,3134,3111,3088,3065,3042,3020,2997,2975,2953,2931,2909,2888,2866,2845,2824,2803,2782,2761,2741,2720,2700,2680,2660,2640,2620,2601,2581,2562,2543,2524,2505,2486,2467,2449,2431,2412,2394,2376,2359,2341,2323,2306,2289,2271,2254,2237,2221,2204,2187,2171,2155,2138,2122,2106,2090,2075,2059,2043,2028,2013,1998,1983,1968,1953,1938,1923,1909,1894,1880,1866,1852,1838,1824,1810,1796,1783,1769,1756,1743,1729,1716,1703,1690,1678,1665,1652,1640,1627,1615,1603,1590,1578,1566,1554,1543,1531,1519,1508,1496,1485,1474,1462,1451,1440,1429,1418,1408,1397,1386,1376,1365,1355,1344,1334,1324,1314,1304,1294,1284,1274,1264,1255,1245,1236,1226,1217,1208,1198,1189,1180,1171,1162,1153,1144,1136,1127,1118,1110,1101,1093,1085,1076,1068,1060,1052,1044,1036,1028,1020,1012,1004,997,989,981,974,966,959,952,944,937,930,923,916,909,902,895,888,881,874,868,861,854,848,841,835,828,822,816,809,803,797,791,785,779,773,767,761,755,749,743,738,732,726,721,715,710,704,699,693,688,683,678,672,667,662,657,652,647,642,637,632,627,622,617,613,608,603,599,594,589,585,580,576,571,567,563,558,554,550,545,541,537,533,529,525,521,517,513,509,505,501,497,493,489,485,482,478,474,471,467,463,460,456,453,449,446,442,439,435,432,429,425,422,419,416,412,409,406,403,400,397,394,391,388,385,382,379,376,373,370,367,364,361,359,356,353,350,348,345,342,340,337,334,332,329,327,324,322,319,317,314,312,309,307,304,302,300,297,295,293,291,288,286,284,282,279,277,275,273,271,269,267,265,263,261,259,257,255,253,251,249,247,245,243,241,239,237,235,234,232,230,228,226,225,223,221,219,218,216,214,213,211,209,208,206,205,203,201,200,198,197,195,194,192,191,189,188,186,185,183,182,181,179,178,176,175,174,172,171,170,168,167,166,164,163,162,161,159,158,157,156,154,153,152,151,150,148,147,146,145,144,143,142,141,139,138,137,136,135,134,133,132,131,130,129,128,127,126,125,124,123,122,121,120,119,118,117,117,116,115,114,113,112,111,110,109,109,108,107,106,105,104,104,103,102,101,100,100,99,98,97,97,96,95,94,94,93,92,91,91,90,89,89,88,87,86,86,85,84,84,83,83,82,81,81,80,79,79,78,77,77,76,76,75,75,74,73,73,72,72,71,71,70,69,69,68,68,67,67,66,66,65,65,64,64,63,63,62,62,61,61,60,60,59,59,58,58,57,57,57,56,56,55,55,54,54,54,53,53,52,52,51,51,51,50,50,49,49,49,48,48,48,47,47,46,46,46,45,45,45,44,44,44};

const static int16_t k_tanh_yvals[1024] = {0,127,255,383,511,639,767,895,1023,1151,1279,1407,1534,1662,1790,1917,2045,2172,2300,2427,2554,2681,2809,2936,3063,3189,3316,3443,3569,3696,3822,3948,4074,4200,4326,4452,4577,4703,4828,4953,5078,5203,5328,5452,5577,5701,5825,5949,6072,6196,6319,6442,6565,6688,6811,6933,7055,7177,7299,7421,7542,7663,7784,7905,8025,8145,8265,8385,8504,8624,8743,8861,8980,9098,9216,9334,9451,9569,9686,9802,9919,10035,10151,10266,10382,10497,10611,10726,10840,10954,11067,11180,11293,11406,11518,11630,11742,11854,11965,12075,12186,12296,12406,12515,12624,12733,12842,12950,13058,13165,13273,13379,13486,13592,13698,13803,13908,14013,14118,14222,14325,14429,14532,14634,14737,14839,14940,15041,15142,15243,15343,15443,15542,15641,15740,15838,15936,16033,16130,16227,16324,16420,16515,16611,16706,16800,16894,16988,17082,17175,17267,17359,17451,17543,17634,17725,17815,17905,17995,18084,18173,18261,18349,18437,18524,18611,18697,18784,18869,18955,19040,19124,19208,19292,19376,19459,19541,19624,19706,19787,19868,19949,20029,20109,20189,20268,20347,20425,20504,20581,20659,20736,20812,20888,20964,21039,21114,21189,21263,21337,21411,21484,21557,21629,21701,21773,21844,21915,21986,22056,22126,22195,22264,22333,22401,22469,22537,22604,22671,22738,22804,22870,22935,23000,23065,23129,23194,23257,23321,23384,23446,23508,23570,23632,23693,23754,23815,23875,23935,23994,24054,24112,24171,24229,24287,24344,24402,24459,24515,24571,24627,24683,24738,24793,24847,24902,24955,25009,25062,25115,25168,25220,25272,25324,25375,25426,25477,25528,25578,25628,25677,25726,25775,25824,25872,25920,25968,26016,26063,26110,26156,26203,26249,26294,26340,26385,26430,26474,26519,26563,26606,26650,26693,26736,26779,26821,26863,26905,26947,26988,27029,27070,27110,27150,27190,27230,27270,27309,27348,27387,27425,27463,27501,27539,27576,27614,27651,27687,27724,27760,27796,27832,27867,27903,27938,27973,28007,28042,28076,28110,28143,28177,28210,28243,28276,28308,28341,28373,28405,28437,28468,28499,28530,28561,28592,28622,28653,28683,28712,28742,28771,28801,28830,28858,28887,28916,28944,28972,29000,29027,29055,29082,29109,29136,29163,29189,29216,29242,29268,29293,29319,29344,29370,29395,29420,29444,29469,29493,29518,29542,29566,29589,29613,29636,29659,29682,29705,29728,29751,29773,29795,29817,29839,29861,29883,29904,29925,29947,29968,29989,30009,30030,30050,30071,30091,30111,30130,30150,30170,30189,30208,30228,30247,30265,30284,30303,30321,30340,30358,30376,30394,30412,30429,30447,30464,30482,30499,30516,30533,30549,30566,30583,30599,30615,30632,30648,30664,30680,30695,30711,30726,30742,30757,30772,30787,30802,30817,30832,30846,30861,30875,30890,30904,30918,30932,30946,30960,30973,30987,31000,31014,31027,31040,31053,31066,31079,31092,31105,31117,31130,31142,31155,31167,31179,31191,31203,31215,31227,31238,31250,31262,31273,31284,31296,31307,31318,31329,31340,31351,31362,31372,31383,31394,31404,31414,31425,31435,31445,31455,31465,31475,31485,31495,31505,31514,31524,31533,31543,31552,31561,31571,31580,31589,31598,31607,31616,31624,31633,31642,31650,31659,31667,31676,31684,31693,31701,31709,31717,31725,31733,31741,31749,31757,31764,31772,31780,31787,31795,31802,31810,31817,31824,31832,31839,31846,31853,31860,31867,31874,31881,31887,31894,31901,31908,31914,31921,31927,31934,31940,31946,31953,31959,31965,31971,31978,31984,31990,31996,32002,32007,32013,32019,32025,32031,32036,32042,32047,32053,32059,32064,32069,32075,32080,32085,32091,32096,32101,32106,32111,32116,32121,32126,32131,32136,32141,32146,32151,32155,32160,32165,32169,32174,32179,32183,32188,32192,32197,32201,32205,32210,32214,32218,32223,32227,32231,32235,32239,32243,32247,32251,32255,32259,32263,32267,32271,32275,32279,32282,32286,32290,32293,32297,32301,32304,32308,32312,32315,32319,32322,32325,32329,32332,32336,32339,32342,32346,32349,32352,32355,32358,32362,32365,32368,32371,32374,32377,32380,32383,32386,32389,32392,32395,32398,32401,32403,32406,32409,32412,32415,32417,32420,32423,32425,32428,32431,32433,32436,32438,32441,32444,32446,32449,32451,32453,32456,32458,32461,32463,32465,32468,32470,32472,32475,32477,32479,32481,32484,32486,32488,32490,32492,32494,32497,32499,32501,32503,32505,32507,32509,32511,32513,32515,32517,32519,32521,32523,32525,32526,32528,32530,32532,32534,32536,32537,32539,32541,32543,32544,32546,32548,32550,32551,32553,32555,32556,32558,32560,32561,32563,32564,32566,32568,32569,32571,32572,32574,32575,32577,32578,32580,32581,32583,32584,32585,32587,32588,32590,32591,32592,32594,32595,32596,32598,32599,32600,32602,32603,32604,32605,32607,32608,32609,32610,32612,32613,32614,32615,32616,32618,32619,32620,32621,32622,32623,32624,32626,32627,32628,32629,32630,32631,32632,32633,32634,32635,32636,32637,32638,32639,32640,32641,32642,32643,32644,32645,32646,32647,32648,32649,32650,32651,32652,32653,32653,32654,32655,32656,32657,32658,32659,32659,32660,32661,32662,32663,32664,32664,32665,32666,32667,32668,32668,32669,32670,32671,32671,32672,32673,32674,32674,32675,32676,32677,32677,32678,32679,32679,32680,32681,32681,32682,32683,32683,32684,32685,32685,32686,32687,32687,32688,32688,32689,32690,32690,32691,32691,32692,32693,32693,32694,32694,32695,32695,32696,32697,32697,32698,32698,32699,32699,32700,32700,32701,32701,32702,32702,32703,32703,32704,32704,32705,32705,32706,32706,32707,32707,32708,32708,32709,32709,32710,32710,32711,32711,32711,32712,32712,32713,32713,32714,32714,32714,32715,32715,32716,32716,32716,32717,32717,32718,32718,32718,32719,32719,32720,32720,32720,32721,32721,32721,32722,32722,32722,32723,32723,32723,32724,32724,32724,32725,32725,32725,32726,32726,32726,32727,32727,32727,32728,32728,32728,32729,32729,32729,32730,32730,32730,32730,32731,32731,32731,32732,32732,32732,32732,32733,32733,32733,32733,32734,32734,32734,32735,32735,32735,32735,32736,32736,32736,32736,32737,32737,32737,32737,32737,32738,32738,32738,32738,32739,32739,32739,32739,32740,32740,32740,32740,32740,32741,32741,32741,32741,32741,32742,32742,32742,32742,32742,32743,32743,32743,32743,32743,32744,32744,32744,32744,32744,32744,32745,32745,32745,32745,32745};

int32_t tinymath_abs_int8(int8_t x) {
    if (((uint8_t)x) == 0x80) {
        x++;
    }
    
    return x >= 0 ? x : -x;
}

int32_t tinymath_abs_int32(int32_t x) {
    if (((uint32_t)x) == 0x80000000) {
        x++;
    }

    return x >= 0 ? x : -x;
}

void tinytensor_descale(Weight_t * y, int8_t * out_scale, int32_t x, int8_t in_scale) {
    //make it fit in 8 bits
    uint8_t i;
    int32_t ux = tinymath_abs_int32(x);
    
    for (i = 0; i < 24; i++) {
        if (  (ux >> i) <= 127 ) {
            break;
        }
    }
    
    *out_scale = in_scale - i;
    *y = x >> i;
    
}

void tinytensor_tanh(Weight_t * y, int8_t * out_scale, int32_t x,int8_t in_scale) {
    const static uint32_t k_max_len = sizeof(k_tanh_yvals) / sizeof(k_tanh_yvals[0]);
    const uint8_t sign = x < 0;
    Weight_t yy;
    const int8_t shift = 15 - QFIXEDPOINT;
    *out_scale = 0;
    int32_t i;
    int16_t dx;
    
    x = tinymath_abs_int32(x);
    
    if (in_scale > 0) {
        x >>= in_scale;
    }
    
    if (in_scale < 0) {
        x <<= -in_scale;
    }
    
    x <<= shift;
    
    //in Q15, 4.0 is 2^2 * 2^15 = 2^17
    //however we have a 10 bit interval, so right shift by 7
    i = x >> 7;
    
    assert(i >= 0);
    
    if (i > k_max_len) {
        yy = MAX_WEIGHT;
    }
    else {
        dx = x - (i << 7);
        assert(dx >= 0);
        if (dx > 0) {
            int foo = 3;
            foo++;
        }
        yy = k_tanh_yvals[i] + MUL16(dx, k_tanh_slopes[i]);
    }
    
    if (sign) {
        yy = -yy;
    }
    
    yy >>= shift; //go back from Q15
    
    *y = yy;
    
 }



//(tanh + 1) / 2 == sigmoid
//crud, but should work okay
void tinytensor_sigmoid(Weight_t * y, int8_t * out_scale, int32_t x,int8_t in_scale) {
    Weight_t tanh;
    int16_t temp16;
    
    tinytensor_tanh(&tanh,out_scale,x,in_scale);
    temp16 = tanh;
    
    //add one
    temp16 += (1 << QFIXEDPOINT);
    
    //divide by two
    temp16 >>= 1;
    
    if (temp16 > MAX_WEIGHT) {
        temp16 = MAX_WEIGHT;
    }
    
    *y = (Weight_t)temp16;
    *out_scale = 0;
}


void tinytensor_vec_softmax_in_place(Weight_t * xvec, uint32_t len, int8_t in_scale) {
    uint32_t i;
    int32_t temp32;
    int32_t val;
    int32_t expval;
    const int8_t shift = 10 - QFIXEDPOINT;
    temp32 = 0;
    for (i = 0; i < len; i++) {
        val = xvec[i];
        
        if (in_scale > 0) {
            val >>= in_scale;
        }
        
        if (in_scale < 0) {
            val <<= -in_scale;
        }
        
        if (shift > 0) {
            val <<= shift;
        }
        
        if (shift < 0) {
            val >>= -shift;
        }
        
        expval = FixedPointExp2Q10(val);

        if (shift > 0) {
            expval >>= shift;
        }
        
        if (shift < 0) {
            expval <<= -shift;
        }
        
        temp32 += expval;
    }
    
    for (i = 0; i < len; i++) {
        val = xvec[i];
        
        if (in_scale > 0) {
            val >>= in_scale;
        }
        
        if (in_scale < 0) {
            val <<= -in_scale;
        }
        
        if (shift > 0) {
            val <<= shift;
        }
        
        if (shift < 0) {
            val >>= -shift;
        }
        
       
        expval = FixedPointExp2Q10(val);

        if (shift > 0) {
            expval >>= shift;
        }
        
        if (shift < 0) {
            expval <<= -shift;
        }

        
        val = (expval << QFIXEDPOINT) / temp32;
    
    
        if (val > MAX_WEIGHT) {
            val = MAX_WEIGHT;
        }
        
        if (val < -MAX_WEIGHT) {
            val = -MAX_WEIGHT;
        }
        
        xvec[i] = val;
        
    }
    
}


void tinytensor_linear(Weight_t * y, int8_t * out_scale, int32_t x,int8_t in_scale) {
    
    if (x > MAX_WEIGHT) {
        x = MAX_WEIGHT;
    }
    
    if (x < -MAX_WEIGHT) {
        x = -MAX_WEIGHT;
    }
    
    *y = x;
    *out_scale = in_scale;
}


void tinytensor_relu(Weight_t * y, int8_t * out_scale, int32_t x,int8_t in_scale) {
    x =  x < 0 ? 0 : x;
    
    if (x > MAX_WEIGHT) {
        x = MAX_WEIGHT;
    }
    
    *y = x;
    *out_scale = in_scale;

}




int8_t tiny_tensor_get_scaling(int32_t x) {
    int8_t i;
    
    if (x == 0) {
        return 0;
    }

    //find max scaling
    x = tinymath_abs_int32(x);
    
    for (i = 0; i < 8; i++) {
        if (( ((int16_t)x) << i) > MAX_WEIGHT/2) {
            break;
        }
    }
    
    return i;
    
}

inline int8_t tiny_tensor_get_descaling(int32_t x) {
    int8_t i;

    x = tinymath_abs_int32(x);
    
    for (i = 0; i < 31; i++) {
        if ((x >> i) <= MAX_WEIGHT) {
            break;
        }
    }
    
    return i;
    
}

int8_t tiny_tensor_compare_scaled_numbers(const Weight_t x1, const int8_t scale1, const Weight_t x2, const int8_t scale2) {
    int32_t xx1 = x1 << 16;
    int32_t xx2 = x2 << 16;
    
    xx1 = tinymath_abs_int32(xx1);
    xx2 = tinymath_abs_int32(xx2);
    
    if (scale1 > 0) {
        xx1 >>= scale1;
    }
    else {
        xx1 <<= -scale1;
    }
    
    if (scale2 > 0) {
        xx2 >>= scale2;
    }
    else {
        xx2 <<= -scale2;
    }
  
    
    if (xx1 > xx2) {
        return 1;
    }
    
    if (xx2 > xx1) {
        return -1;
    }
    
    return 0;
    
}



