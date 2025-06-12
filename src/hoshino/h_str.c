#include "hoshino/h_str.h"
#include "hoshino/h_cdvd.h"
#include "hoshino/h_game.h"
#include "hoshino/h_menu.h"
#include "hoshino/h_rpc.h"

#ifdef KL2_VER_TRIAL
static BGMTABLE BgmTable[] = {
    { 0x0000, 0x3A9, 2 },
    { 0x0752, 0x42A, 2 },
    { 0x0FA6, 0x480, 4 },
    { 0x21A6, 0x7F5, 2 },
    { 0x3190, 0x6FA, 2 },
    { 0x3F84, 0xB20, 2 },
    { 0x55C4, 0x682, 2 },
    { 0x62C8, 0x682, 2 }
};
static PPTTABLE PptTable[] = {
    { 0, 7 },
    { 7, 31 },
    { 38, 31 },
    { 69, 9 },
    { 78, 19 },
    { 97, 14 },
    { 111, 10 },
    { 121, 6 },
    { 127, 34 },
    { 161, 14 },
    { 175, 20 },
    { 195, 17 },
    { 212, 24 },
    { 236, 19 },
    { 255, 5 },
    { 260, 14 },
    { 274, 7 },
    { 281, 5 },
    { 286, 8 },
    { 294, 7 },
    { 301, 20 },
    { 321, 23 },
    { 344, 16 },
    { 360, 19 },
    { 379, 11 },
    { 390, 12 },
    { 402, 23 },
    { 425, 11 },
    { 436, 8 },
    { 444, 26 },
    { 470, 19 },
    { 489, 9 },
    { 498, 29 },
    { 527, 8 },
    { 535, 18 },
    { 553, 7 },
    { 560, 21 },
    { 581, 43 },
    { 624, 16 },
    { 640, 14 },
    { 654, 25 },
    { 679, 22 },
    { 701, 27 },
    { 728, 8 },
    { 736, 20 },
    { 756, 13 },
    { 769, 11 },
    { 780, 9 },
    { 789, 19 },
    { 808, 23 },
    { 831, 8 },
    { 839, 19 },
    { 858, 17 },
    { 875, 9 },
    { 884, 31 },
    { 915, 25 },
    { 940, 19 },
    { 959, 22 },
    { 981, 30 },
    { 1011, 16 },
    { 1027, 8 },
    { 1035, 25 },
    { 1060, 21 },
    { 1081, 22 },
    { 1103, 31 },
    { 1134, 24 },
    { 1158, 39 },
    { 1197, 24 },
    { 1221, 11 },
    { 1232, 24 },
    { 1256, 15 },
    { 1271, 28 },
    { 1299, 10 },
    { 1309, 25 },
    { 1334, 28 },
    { 1362, 14 },
    { 1376, 33 },
    { 1409, 10 },
    { 1419, 42 },
    { 1461, 33 },
    { 1494, 18 },
    { 1512, 40 },
    { 1552, 66 },
    { 1618, 42 },
    { 1660, 27 },
    { 1687, 55 },
    { 1742, 33 },
    { 1775, 67 },
    { 1842, 17 },
    { 1859, 23 },
    { 1882, 51 },
    { 1933, 12 },
    { 1945, 11 },
    { 1956, 16 },
    { 1972, 68 },
    { 2040, 21 },
    { 2061, 10 },
    { 2071, 8 },
    { 2079, 15 },
    { 2094, 15 },
    { 2109, 21 },
    { 2130, 13 },
    { 2143, 27 },
    { 2170, 23 },
    { 2193, 21 },
    { 2214, 47 },
    { 2261, 9 },
    { 2270, 14 },
    { 2284, 34 },
    { 2318, 11 },
    { 2329, 20 },
    { 2349, 38 },
    { 2387, 9 },
    { 2396, 11 },
    { 2407, 29 },
    { 2436, 31 },
    { 2467, 22 },
    { 2489, 13 },
    { 2502, 23 },
    { 2525, 39 },
    { 2564, 46 },
    { 2610, 12 },
    { 2622, 42 },
    { 2664, 17 },
    { 2681, 26 },
    { 2707, 31 },
    { 2738, 19 },
    { 2757, 8 },
    { 2765, 45 },
    { 2810, 18 },
    { 2828, 41 },
    { 2869, 111 },
    { 2980, 16 },
    { 2996, 6 },
    { 3002, 22 },
    { 3024, 6 },
    { 3030, 14 },
    { 3044, 20 },
    { 3064, 8 },
    { 3072, 33 },
    { 3105, 22 },
    { 3127, 14 },
    { 3141, 13 },
    { 3154, 31 },
    { 3185, 34 },
    { 3219, 25 },
    { 3244, 7 },
    { 3251, 16 },
    { 3267, 16 },
    { 3283, 7 },
    { 3290, 7 },
    { 3297, 8 },
    { 3305, 7 },
    { 3312, 8 },
    { 3320, 8 },
    { 3328, 15 },
    { 3343, 7 },
    { 3350, 19 },
    { 3369, 21 },
    { 3390, 7 },
    { 3397, 16 },
    { 3413, 12 },
    { 3425, 18 },
    { 3443, 15 },
    { 3458, 17 },
    { 3475, 31 },
    { 3506, 10 },
    { 3516, 13 },
    { 3529, 6 },
    { 3535, 21 },
    { 3556, 8 },
    { 3564, 9 },
    { 3573, 19 },
    { 3592, 5 },
    { 3597, 9 },
    { 3606, 64 },
    { 3670, 47 },
    { 3717, 24 },
    { 3741, 84 },
    { 3825, 37 },
    { 3862, 22 },
    { 3884, 37 },
    { 3921, 18 },
    { 3939, 44 },
    { 3983, 16 },
    { 3999, 38 },
    { 4037, 26 },
    { 4063, 18 },
    { 4081, 22 },
    { 4103, 18 },
    { 4121, 12 },
    { 4133, 12 },
    { 4145, 8 },
    { 4153, 23 },
    { 4176, 9 },
    { 4185, 19 },
    { 4204, 9 },
    { 4213, 20 },
    { 4233, 29 },
    { 4262, 32 },
    { 4294, 35 },
    { 4329, 14 },
    { 4343, 8 },
    { 4351, 17 },
    { 4368, 27 },
    { 4395, 12 },
    { 4407, 8 },
    { 4415, 33 },
    { 4448, 16 },
    { 4464, 17 },
    { 4481, 14 },
    { 4495, 8 },
    { 4503, 21 },
    { 4524, 27 },
    { 4551, 24 },
    { 4575, 9 },
    { 4584, 20 },
    { 4604, 17 },
    { 4621, 17 },
    { 4638, 27 },
    { 4665, 41 },
    { 4706, 12 },
    { 4718, 11 },
    { 4729, 30 },
    { 4759, 11 },
    { 4770, 26 },
    { 4796, 19 },
    { 4815, 31 },
    { 4846, 9 },
    { 4855, 14 },
    { 4869, 12 },
    { 4881, 18 },
    { 4899, 36 },
    { 4935, 39 },
    { 4974, 17 },
    { 4991, 19 },
    { 5010, 24 },
    { 5034, 11 },
    { 5045, 24 },
    { 5069, 68 },
    { 5137, 15 },
    { 5152, 15 },
    { 5167, 18 },
    { 5185, 8 },
    { 5193, 12 },
    { 5205, 10 },
    { 5215, 8 },
    { 5223, 16 },
    { 5239, 15 },
    { 5254, 39 },
    { 5293, 9 },
    { 5302, 40 },
    { 5342, 23 },
    { 5365, 15 },
    { 5380, 25 },
    { 5405, 39 },
    { 5444, 12 },
    { 5456, 28 },
    { 5484, 25 },
    { 5509, 9 },
    { 5518, 21 },
    { 5539, 29 },
    { 5568, 30 },
    { 5598, 17 },
    { 5615, 16 },
    { 5631, 15 },
    { 5646, 19 },
    { 5665, 18 },
    { 5683, 20 },
    { 5703, 16 },
    { 5719, 24 },
    { 5743, 24 },
    { 5767, 6 },
    { 5773, 24 },
    { 5797, 13 },
    { 5810, 26 },
    { 5836, 32 },
    { 5868, 28 },
    { 5896, 16 },
    { 5912, 20 },
    { 5932, 21 },
    { 5953, 8 },
    { 5961, 32 },
    { 5993, 6 },
    { 5999, 14 },
    { 6013, 23 },
    { 6036, 13 },
    { 6049, 9 },
    { 6058, 10 },
    { 6068, 10 },
    { 6078, 13 },
    { 6091, 40 },
    { 6131, 23 },
    { 6154, 15 },
    { 6169, 25 },
    { 6194, 39 },
    { 6233, 12 },
    { 6245, 30 },
    { 6275, 20 },
    { 6295, 9 },
    { 6304, 21 },
    { 6325, 29 },
    { 6354, 30 },
    { 6384, 17 },
    { 6401, 16 },
    { 6417, 15 },
    { 6432, 19 },
    { 6451, 18 },
    { 6469, 20 },
    { 6489, 16 },
    { 6505, 14 },
    { 6519, 23 },
    { 6542, 19 },
    { 6561, 8 },
    { 6569, 28 },
    { 6597, 18 },
    { 6615, 29 },
    { 6644, 11 },
    { 6655, 12 },
    { 6667, 11 },
    { 6678, 12 },
    { 6690, 35 },
    { 6725, 21 },
    { 6746, 24 },
    { 6770, 8 },
    { 6778, 31 },
    { 6809, 32 },
    { 6841, 33 },
    { 6874, 10 },
    { 6884, 47 },
    { 6931, 14 },
    { 6945, 10 },
    { 6955, 44 },
    { 6999, 27 },
    { 7026, 23 },
    { 7049, 23 },
    { 7072, 9 },
    { 7081, 28 },
    { 7109, 14 },
    { 7123, 9 },
    { 7132, 21 },
    { 7153, 22 },
    { 7175, 16 },
    { 7191, 14 },
    { 7205, 7 },
    { 7212, 21 },
    { 7233, 22 },
    { 7255, 10 },
    { 7265, 28 },
    { 7293, 14 },
    { 7307, 44 },
    { 7351, 13 },
    { 7364, 6 },
    { 7370, 24 },
    { 7394, 22 },
    { 7416, 8 },
    { 7424, 20 },
    { 7444, 35 },
    { 7479, 45 },
    { 7524, 18 },
    { 7542, 6 },
    { 7548, 15 },
    { 7563, 13 },
    { 7576, 34 },
    { 7610, 26 },
    { 7636, 22 },
    { 7658, 23 },
    { 7681, 19 },
    { 7700, 12 },
    { 7712, 9 },
    { 7721, 16 },
    { 7737, 16 },
    { 7753, 23 },
    { 7776, 9 },
    { 7785, 16 },
    { 7801, 19 },
    { 7820, 24 },
    { 7844, 9 },
    { 7853, 21 },
    { 7874, 16 },
    { 7890, 17 },
    { 7907, 23 },
    { 7930, 9 },
    { 7939, 21 },
    { 7960, 18 },
    { 7978, 18 },
    { 7996, 25 },
    { 8021, 26 },
    { 8047, 24 },
    { 8071, 10 },
    { 8081, 20 },
    { 8101, 12 },
    { 8113, 30 },
    { 8143, 18 },
    { 8161, 22 },
    { 8183, 29 },
    { 8212, 8 },
    { 8220, 13 },
    { 8233, 12 },
    { 8245, 20 },
    { 8265, 21 },
    { 8286, 7 },
    { 8293, 20 },
    { 8313, 19 },
    { 8332, 16 },
    { 8348, 15 },
    { 8363, 10 },
    { 8373, 5 },
    { 8378, 48 },
    { 8426, 30 },
    { 8456, 17 },
    { 8473, 9 },
    { 8482, 8 },
    { 8490, 14 },
    { 8504, 10 },
    { 8514, 23 },
    { 8537, 16 },
    { 8553, 10 },
    { 8563, 37 },
    { 8600, 60 },
    { 8660, 39 },
    { 8699, 30 },
    { 8729, 48 },
    { 8777, 13 },
    { 8790, 22 },
    { 8812, 49 },
    { 8861, 17 },
    { 8878, 12 },
    { 8890, 47 },
    { 8937, 38 },
    { 8975, 32 },
    { 9007, 11 },
    { 9018, 28 },
    { 9046, 76 },
    { 9122, 45 },
    { 9167, 25 },
    { 9192, 18 },
    { 9210, 59 },
    { 9269, 32 },
    { 9301, 26 },
    { 9327, 36 },
    { 9363, 9 },
    { 9372, 26 },
    { 9398, 15 },
    { 9413, 19 },
    { 9432, 28 },
    { 9460, 15 },
    { 9475, 27 },
    { 9502, 24 },
    { 9526, 19 },
    { 9545, 21 },
    { 9566, 13 },
    { 9579, 20 },
    { 9599, 10 },
    { 9609, 18 },
    { 9627, 8 },
    { 9635, 15 },
    { 9650, 16 },
    { 9666, 17 },
    { 9683, 18 },
    { 9701, 24 },
    { 9725, 40 },
    { 9765, 21 },
    { 9786, 22 },
    { 9808, 26 },
    { 9834, 8 },
    { 9842, 25 },
    { 9867, 28 },
    { 9895, 11 },
    { 9906, 13 },
    { 9919, 8 },
    { 9927, 9 },
    { 9936, 12 },
    { 9948, 41 },
    { 9989, 22 },
    { 10011, 22 },
    { 10033, 8 },
    { 10041, 7 },
    { 10048, 18 },
    { 10066, 23 },
    { 10089, 9 },
    { 10098, 23 },
    { 10121, 9 },
    { 10130, 18 },
    { 10148, 26 },
    { 10174, 9 },
    { 10183, 26 },
    { 10209, 9 },
    { 10218, 32 },
    { 10250, 9 },
    { 10259, 40 },
    { 10299, 35 },
    { 10334, 26 },
    { 10360, 8 },
    { 10368, 21 },
    { 10389, 19 },
    { 10408, 25 },
    { 10433, 24 },
    { 10457, 20 },
    { 10477, 12 },
    { 10489, 14 },
    { 10503, 15 },
    { 10518, 29 },
    { 10547, 25 },
    { 10572, 38 },
    { 10610, 19 },
    { 10629, 14 },
    { 10643, 14 },
    { 10657, 15 },
    { 10672, 42 },
    { 10714, 51 },
    { 10765, 47 },
    { 10812, 43 },
    { 10855, 21 },
    { 10876, 40 },
    { 10916, 77 },
    { 10993, 11 },
    { 11004, 44 },
    { 11048, 7 },
    { 11055, 34 },
    { 11089, 13 },
    { 11102, 24 },
    { 11126, 8 },
    { 11134, 14 },
    { 11148, 35 },
    { 11183, 7 },
    { 11190, 65 },
    { 11255, 17 },
    { 11272, 11 },
    { 11283, 18 },
    { 11301, 32 },
    { 11333, 17 },
    { 11350, 28 },
    { 11378, 34 },
    { 11412, 21 },
    { 11433, 31 },
    { 11464, 15 },
    { 11479, 24 },
    { 11503, 22 },
    { 11525, 12 },
    { 11537, 20 },
    { 11557, 32 },
    { 11589, 7 },
    { 11596, 24 },
    { 11620, 15 },
    { 11635, 23 },
    { 11658, 8 },
    { 11666, 12 },
    { 11678, 18 },
    { 11696, 26 },
    { 11722, 26 },
    { 11748, 15 },
    { 11763, 8 },
    { 11771, 8 },
    { 11779, 20 },
    { 11799, 7 },
    { 11806, 8 },
    { 11814, 16 },
    { 11830, 18 },
    { 11848, 25 },
    { 11873, 27 },
    { 11900, 12 },
    { 11912, 8 },
    { 11920, 58 },
    { 11978, 29 },
    { 12007, 9 },
    { 12016, 53 },
    { 12069, 20 },
    { 12089, 26 },
    { 12115, 35 },
    { 12150, 17 },
    { 12167, 9 },
    { 12176, 25 },
    { 12201, 25 },
    { 12226, 21 },
    { 12247, 7 },
    { 12254, 9 },
    { 12263, 14 },
    { 12277, 17 },
    { 12294, 32 },
    { 12326, 47 },
    { 12373, 32 },
    { 12405, 51 },
    { 12456, 50 },
    { 12506, 15 },
    { 12521, 14 },
    { 12535, 29 },
    { 12564, 20 },
    { 12584, 23 },
    { 12607, 11 },
    { 12618, 25 },
    { 12643, 29 },
    { 12672, 6 },
    { 12678, 20 },
    { 12698, 29 },
    { 12727, 16 },
    { 12743, 11 },
    { 12754, 38 },
    { 12792, 18 },
    { 12810, 9 },
    { 12819, 9 },
    { 12828, 10 },
    { 12838, 14 },
    { 12852, 32 },
    { 12884, 42 },
    { 12926, 8 },
    { 12934, 26 },
    { 12960, 28 },
    { 12988, 29 },
    { 13017, 19 },
    { 13036, 13 },
    { 13049, 33 },
    { 13082, 20 },
    { 13102, 37 },
    { 13139, 6 },
    { 13145, 6 },
    { 13151, 7 },
    { 13158, 10 },
    { 13168, 16 },
    { 13184, 12 },
    { 13196, 6 },
    { 13202, 14 },
    { 13216, 13 },
    { 13229, 7 },
    { 13236, 15 },
    { 13251, 14 },
    { 13265, 7 },
    { 13272, 10 },
    { 13282, 16 },
    { 13298, 22 },
    { 13320, 16 },
    { 13336, 9 },
    { 13345, 21 },
    { 13366, 48 },
    { 13414, 14 },
    { 13428, 36 },
    { 13464, 21 },
    { 13485, 47 },
    { 13532, 17 },
    { 13549, 33 },
    { 13582, 35 },
    { 13617, 13 },
    { 13630, 29 },
    { 13659, 8 },
    { 13667, 22 },
    { 13689, 46 },
    { 13735, 16 },
    { 13751, 10 },
    { 13761, 16 },
    { 13777, 5 },
    { 13782, 24 },
    { 13806, 18 },
    { 13824, 7 },
    { 13831, 42 },
    { 13873, 45 },
    { 13918, 5 },
    { 13923, 43 },
    { 13966, 11 },
    { 13977, 42 },
    { 14019, 19 },
    { 14038, 10 },
    { 14048, 9 },
    { 14057, 34 },
    { 14091, 16 },
    { 14107, 30 },
    { 14137, 32 },
    { 14169, 12 },
    { 14181, 22 },
    { 14203, 9 },
    { 14212, 14 },
    { 14226, 19 },
    { 14245, 17 },
    { 14262, 9 },
    { 14271, 9 },
    { 14280, 14 },
    { 14294, 17 },
    { 14311, 8 },
    { 14319, 7 },
    { 14326, 35 },
    { 14361, 12 },
    { 14373, 7 },
    { 14380, 25 },
    { 14405, 13 },
    { 14418, 43 },
    { 14461, 14 },
    { 14475, 31 },
    { 14506, 32 },
    { 14538, 23 },
    { 14561, 15 },
    { 14576, 17 },
    { 14593, 27 },
    { 14620, 11 },
    { 14631, 24 },
    { 14655, 22 },
    { 14677, 19 },
    { 14696, 7 },
    { 14703, 57 },
    { 14760, 33 },
    { 14793, 18 },
    { 14811, 8 },
    { 14819, 17 },
    { 14836, 34 },
    { 14870, 7 },
    { 14877, 27 },
    { 14904, 50 },
    { 14954, 13 },
    { 14967, 23 },
    { 14990, 40 },
    { 15030, 26 },
    { 15056, 29 },
    { 15085, 11 },
    { 15096, 8 },
    { 15104, 41 },
    { 15145, 9 },
    { 15154, 63 },
    { 15217, 10 },
    { 15227, 26 },
    { 15253, 21 },
    { 15274, 10 },
    { 15284, 22 },
    { 15306, 56 },
    { 15362, 12 },
    { 15374, 29 },
    { 15403, 22 },
    { 15425, 24 },
    { 15449, 14 },
    { 15463, 8 },
    { 15471, 26 },
    { 15497, 9 },
    { 15506, 14 },
    { 15520, 19 },
    { 15539, 31 },
    { 15570, 28 },
    { 15598, 17 },
    { 15615, 26 },
    { 15641, 10 },
    { 15651, 19 },
    { 15670, 13 },
    { 15683, 9 },
    { 15692, 7 },
    { 15699, 34 },
    { 15733, 34 },
    { 15767, 16 },
    { 15783, 10 },
    { 15793, 10 },
    { 15803, 15 },
    { 15818, 7 },
    { 15825, 15 },
    { 15840, 17 },
    { 15857, 16 },
    { 15873, 16 },
    { 15889, 24 },
    { 15913, 30 },
    { 15943, 10 },
    { 15953, 11 },
    { 15964, 22 },
    { 15986, 11 },
    { 15997, 17 },
    { 16014, 35 },
    { 16049, 6 },
    { 16055, 34 },
    { 16089, 21 },
    { 16110, 6 },
    { 16116, 8 },
    { 16124, 46 },
    { 16170, 9 },
    { 16179, 44 },
    { 16223, 10 },
    { 16233, 25 },
    { 16258, 6 },
    { 16264, 22 },
    { 16286, 8 },
    { 16294, 21 },
    { 16315, 9 },
    { 16324, 33 },
    { 16357, 11 },
    { 16368, 43 },
    { 16411, 49 },
    { 16460, 39 },
    { 16499, 7 },
    { 16506, 32 },
    { 16538, 85 },
    { 16623, 91 },
    { 16714, 19 },
    { 16733, 26 },
    { 16759, 40 },
    { 16799, 6 },
    { 16805, 12 },
    { 16817, 16 },
    { 16833, 21 },
    { 16854, 22 },
    { 16876, 30 },
    { 16906, 40 },
    { 16946, 31 },
    { 16977, 23 },
    { 17000, 13 },
    { 17013, 8 },
    { 17021, 38 },
    { 17059, 7 },
    { 17066, 12 },
    { 17078, 15 },
    { 17093, 35 },
    { 17128, 24 },
    { 17152, 25 },
    { 17177, 8 },
    { 17185, 19 },
    { 17204, 10 },
    { 17214, 18 },
    { 17232, 49 },
    { 17281, 17 },
    { 17298, 46 },
    { 17344, 8 },
    { 17352, 23 },
    { 17375, 9 },
    { 17384, 44 },
    { 17428, 37 },
    { 17465, 17 },
    { 17482, 32 },
    { 17514, 35 },
    { 17549, 7 },
    { 17556, 50 },
    { 17606, 16 },
    { 17622, 9 },
    { 17631, 9 },
    { 17640, 43 },
    { 17683, 7 },
    { 17690, 39 },
    { 17729, 23 },
    { 17752, 7 },
    { 17759, 45 },
    { 17804, 21 },
    { 17825, 7 },
    { 17832, 31 },
    { 17863, 16 },
    { 17879, 11 },
    { 17890, 36 },
    { 17926, 18 },
    { 17944, 7 },
    { 17951, 27 },
    { 17978, 8 },
    { 17986, 26 },
    { 18012, 44 },
    { 18056, 24 },
    { 18080, 30 },
    { 18110, 16 },
    { 18126, 7 },
    { 18133, 25 },
    { 18158, 26 },
    { 18184, 7 },
    { 18191, 39 },
    { 18230, 49 },
    { 18279, 23 },
    { 18302, 15 },
    { 18317, 9 },
    { 18326, 30 },
    { 18356, 8 },
    { 18364, 91 },
    { 18455, 38 },
    { 18493, 38 },
    { 18531, 47 },
    { 18578, 9 },
    { 18587, 32 },
    { 18619, 29 },
    { 18648, 48 },
    { 18696, 73 },
    { 18769, 31 },
    { 18800, 52 },
    { 18852, 82 },
    { 18934, 36 },
    { 18970, 30 },
    { 19000, 47 },
    { 19047, 86 },
    { 19133, 51 },
    { 19184, 72 },
    { 19256, 51 },
    { 19307, 43 },
    { 19350, 52 },
    { 19402, 67 },
    { 19469, 35 },
    { 19504, 65 },
    { 19569, 90 },
    { 19659, 46 },
    { 19705, 108 },
    { 19813, 70 },
    { 19883, 26 },
    { 19909, 45 },
    { 19954, 77 },
    { 20031, 78 },
    { 20109, 80 },
    { 20189, 60 },
    { 20249, 44 },
    { 20293, 32 },
    { 20325, 18 },
    { 20343, 29 },
    { 20372, 30 },
    { 20402, 36 },
    { 20438, 21 },
    { 20459, 24 },
    { 20483, 5 },
};
#else
KLTABLE *KlTable = NULL; // ?
PPTTABLE *PptTable = NULL;
BGMTABLE *BgmTable = NULL;
#endif
hBGMDATA BgmData = {};
hBGMDATA* bD = NULL;
hPPTDATA PptData = {};
hPPTDATA* pD;
#ifdef KL2_VER_RETAIL
hAC3DATA Ac3Data = {};
hAC3DATA* aD = NULL;
#endif

#ifdef KL2_VER_RETAIL
s32 hBgmGetPlaySize() {
    return BgmTable[bD->bgmNo].chsize;
}
#endif

f32 hBgmGetDefVol(BGM no) {
    s32 vol;

#ifdef KL2_VER_TRIAL
    switch (no) {
        case BGM000:
            vol = 110;
            break;
        case BGM001:
            vol = 75;
            break;
        case BGM040:
            vol = 95;
            break;
        case BGM058:
            vol = 120;
            break;
        case BGM060:
            vol = 90;
            break;
        default:
            vol = 100;
            break;
    }
#else
    switch (no) {
        case BGM000:
            vol = 75;
            break;
        case BGM001:
            vol = 75;
            break;
        case BGM003:
            vol = 97;
            break;
        case BGM004:
            vol = 107;
            break;
        case BGM005:
            vol = 90;
            break;
        case BGM006:
            vol = 77;
            break;
        case BGM007:
            vol = 70;
            break;
        case BGM008:
            vol = 80;
            break;
        case BGM009:
            vol = 95;
            break;
        case BGM010:
            vol = 127;
            break;
        case BGM012:
            vol = 100;
            break;
        case BGM013:
            vol = 70;
            break;
        case BGM014:
            vol = 85;
            break;
        case BGM015:
            vol = 85;
            break;
        case BGM016:
            vol = 80;
            break;
        case BGM017:
            vol = 83;
            break;
        case BGM018:
            vol = 75;
            break;
        case BGM019:
            vol = 80;
            break;
        case BGM020:
            vol = 88;
            break;
        case BGM021:
            vol = 88;
            break;
        case BGM022:
            vol = 95;
            break;
        case BGM023:
            vol = 100;
            break;
        case BGM024:
            vol = 80;
            break;
        case BGM025:
            vol = 80;
            break;
        case BGM026:
            vol = 90;
            break;
        case BGM027:
            vol = 100;
            break;
        case BGM028:
            vol = 70;
            break;
        case BGM029:
            vol = 108;
            break;
        case BGM030:
            vol = 97;
            break;
        case BGM031:
            vol = 82;
            break;
        case BGM032:
            vol = 120;
            break;
        case BGM033:
            vol = 50;
            break;
        case BGM034:
            vol = 90;
            break;
        case BGM035:
            vol = 100;
            break;
        case BGM036:
            vol = 73;
            break;
        case BGM037:
            vol = 55;
            break;
        case BGM038:
            vol = 100;
            break;
        case BGM039:
            vol = 90;
            break;
        case BGM040:
            vol = 125;
            break;
        case BGM041:
            vol = 110;
            break;
        case BGM042:
            vol = 90;
            break;
        case BGM043:
            vol = 60;
            break;
        case BGM044:
            vol = 95;
            break;
        case BGM045:
            vol = 80;
            break;
        case BGM046:
            vol = 100;
            break;
        case BGM047:
            vol = 100;
            break;
        case BGM048:
            vol = 90;
            break;
        case BGM049:
            vol = 90;
            break;
        case BGM050:
            vol = 90;
            break;
        case BGM052:
            vol = 80;
            break;
        case BGM053:
            vol = 115;
            break;
        case BGM054:
            vol = 85;
            break;
        case BGM055:
            vol = 110;
            break;
        case BGM056:
            vol = 75;
            break;
        case BGM057:
            vol = 127;
            break;
        case BGM058:
            vol = 90;
            break;
        case BGM059:
            vol = 110;
            break;
        case BGM060:
            vol = 70;
            break;
        case BGM061:
            vol = 75;
            break;
        case BGM062:
            vol = 125;
            break;
        case BGM063:
            vol = 110;
            break;
        case BGM064:
            vol = 85;
            break;
        case BGM065:
            vol = 50;
            break;
        case BGM066:
            vol = 50;
            break;
        case BGM067:
            vol = 70;
            break;
        case BGM068:
            vol = 40;
            break;
        case BGM069:
            vol = 80;
            break;
        case BGM070:
            vol = 55;
            break;
        case BGM072:
            vol = 115;
            break;
        case BGM073:
            vol = 120;
            break;
        case BGM074:
            vol = 120;
            break;
        case BGM075:
            vol = 80;
            break;
        case BGM076:
            vol = 105;
            break;
        case BGM077:
            vol = 100;
            break;
        case BGM078:
            vol = 100;
            break;
        case BGM079:
            vol = 70;
            break;
        case BGM080:
            vol = 75;
            break;
        case BGM081:
            vol = 120;
            break;
        case BGM082:
            vol = 100;
            break;
        case BGM083:
            vol = 90;
            break;
        case BGM084:
            vol = 45;
            break;
        case BGM085:
            vol = 90;
            break;
        case BGM086:
            vol = 85;
            break;
        default:
            vol = 100;
            break;
    }
#endif

    return vol / 127.0f;
}

#ifdef KL2_VER_TRIAL
f32 hBgmGetLoopSecond(BGM no) {
    switch (no) {
        case BGM001:
            return 49.4165f;
        case BGM040:
            return 10.0f;
        case BGM058:
            return 48.185699f;
        default:
            return 0.0f;
    }
}
#else
s32 hBgmGetLoopSize(BGM no) {
    s32 size;

    if (SysGbl.nmode == 2) {
        return hTestBGMskip;
    }

    switch (no) {
        case BGM000:
            size = 3311616;
            break;
        case BGM001:
            size = 2179072;
            break;
        case BGM004:
            size = 330624;
            break;
        case BGM005:
            size = 134848;
            break;
        case BGM006:
            size = 112000;
            break;
        case BGM007:
            size = 190400;
            break;
        case BGM008:
            size = 428736;
            break;
        case BGM009:
            size = 132608;
            break;
        case BGM010:
            size = 1657600;
            break;
        case BGM013:
            size = 3508736;
            break;
        case BGM014:
            size = 3437056;
            break;
        case BGM015:
            size = 2982784;
            break;
        case BGM016:
            size = 440832;
            break;
        case BGM017:
            size = 2538368;
            break;
        case BGM018:
            size = 3809344;
            break;
        case BGM020:
            size = 2694272;
            break;
        case BGM021:
            size = 2694272;
            break;
        case BGM022:
            size = 3293248;
            break;
        case BGM023:
            size = 161280;
            break;
        case BGM026:
            size = 1613696;
            break;
        case BGM027:
            size = 1589056;
            break;
        case BGM028:
            size = 3810240;
            break;
        case BGM031:
            size = 297472;
            break;
        case BGM032:
            size = 66304;
            break;
        case BGM033:
            size = 1436736;
            break;
        case BGM034:
            size = 428736;
            break;
        case BGM036:
            size = 1177792;
            break;
        case BGM037:
            size = 1437184;
            break;
        case BGM039:
            size = 1000384;
            break;
        case BGM040:
            size = 460096;
            break;
        case BGM041:
            size = 9226112;
            break;
        case BGM043:
            size = 2674560;
            break;
        case BGM045:
            size = 1060864;
            break;
        case BGM046:
            size = 771904;
            break;
        case BGM047:
            size = 955136;
            break;
        case BGM048:
            size = 969920;
            break;
        case BGM049:
            size = 756224;
            break;
        case BGM055:
            size = 847168;
            break;
        case BGM056:
            size = 163520;
            break;
        case BGM057:
            size = 2694272;
            break;
        case BGM058:
            size = 879872;
            break;
        case BGM059:
            size = 1000384;
            break;
        case BGM060:
            size = 1444352;
            break;
        case BGM061:
            size = 799232;
            break;
        case BGM064:
            size = 6038144;
            break;
        case BGM066:
            size = 632128;
            break;
        case BGM069:
            size = 662144;
            break;
        case BGM070:
            size = 342720;
            break;
        case BGM076:
            size = 4563328;
            break;
        case BGM077:
            size = 2116800;
            break;
        case BGM078:
            size = 4553472;
            break;
        case BGM079:
            size = 726208;
            break;
        case BGM080:
            size = 1154496;
            break;
        case BGM082:
            size = 22447936;
            break;
        case BGM086:
            size = 6038144;
            break;
        default:
            size = 0;
            break;
    }

    return size / 448 * 256;
}
#endif

s32 hBgmGetLoopLSN() {
    KL2_VER_COND(f32 second, s32 size);
    s32 sector;
    s32 fine;

#ifdef KL2_VER_TRIAL
    second = hBgmGetLoopSecond(bD->bgmNo);
    sector = second * (1575.0f / 128.0f);
    fine = second * 25200.0f - sector * 2048.0f + 0.5f;
    fine = (fine + 128) / 256 * 256;
#else
    size = hBgmGetLoopSize(bD->bgmNo);
    sector = size / 2048;
    fine = (size % 2048 + 128) / 256 * 256;
#endif

    if (fine == 2048) {
        sector++;
        fine = 0;
    }

    if (bD->cdRemain != 0) {
        bD->iopFineTop[bD->iopID] = (0x80000 - bD->cdRemain * 0x800) / bD->bgmChMax / 2;
        bD->iopFine[bD->iopID] = fine;
    } else {
        bD->iopFineTop[bD->iopID] = 0;
        bD->iopFine[bD->iopID] = fine;
    }

    return bD->cdTop + sector * bD->bgmChMax * 2;
}

void hBgmPlay(BGM no, s32 ch) {
#ifdef KL2_VER_RETAIL
    s32 ac3;

    if (no < BGM000) {
        no = BGM002;
        ch = 0;
    }

    if (sD->Stereo == SND_MODE_5P1CH) {
        switch (no) {
            case BGM072:
                ac3 = 0;
                break;
            case BGM073:
                ac3 = 2;
                break;
            case BGM074:
                ac3 = 3;
                break;
            case BGM081:
                ac3 = 1;
                break;
            default:
                ac3 = -1;
                break;
        }

        if (ac3 != -1) {
            hStr_0016f6a8(ac3);
            return;
        }
    }
#endif

    bD->Command |= 1;
    cD->BGMplay = 1;
    hCdCueFlushBGM();
    if (cD->dataFlag == CDREAD_BGM && cD->dataStat != 2) {
        while (!sceCdBreak());
        cD->dataStat = 0;
    }

    bD->iopID = 0;
    bD->iopOK[0] = 0;
    bD->iopOK[1] = 0;
    bD->iopFineTop[0] = 0;
    bD->iopFineTop[1] = 0;
    bD->iopFine[0] = 0;
    bD->iopFine[1] = 0;
    hBgmSetCh(ch);
    bD->bgmNo = no;
    bD->bgmChMax = BgmTable[no].chnum / 2;
    KL2_VER_RETAIL_ONLY(bD->bgmLength = BgmTable[no].chsize);
    KL2_VER_RETAIL_ONLY(bD->bgmSkipSize = hBgmGetLoopSize(no));
    bD->cdCur = bD->cdTop = BgmTable[no].start + bD->Fp.lsn;
#ifdef KL2_VER_TRIAL
    bD->cdSectors = BgmTable[no].chsize * BgmTable[no].chnum;
#else
    bD->cdSectors = ((BgmTable[no].chsize + 0x7FF) / 0x800) * BgmTable[no].chnum;
#endif
    bD->fadeFlag = 0;
    bD->bgmVol = KL2_VER_COND(0.92913383f, 0.78740156f);
    bD->nextNo = -1;
    hCdCuePush(bD->cdCur, 0x100, bD->iopAddr[bD->iopID], 1, cD->eeCnt);
    bD->cdReq = 0;
    bD->cdCur += 0x100;
    bD->cdRemain = bD->cdCur - (bD->cdTop + bD->cdSectors);
}

#ifdef KL2_VER_RETAIL
void hBgmPlayLast10sec(BGM no, s32 ch) {
    bD->Command |= 0x20;
    cD->BGMplay = 1;
    hCdCueFlushBGM();
    if (cD->dataFlag == CDREAD_BGM && cD->dataStat != 2) {
        while (!sceCdBreak());
        cD->dataStat = 0;
    }

    bD->iopID = 0;
    bD->iopOK[0] = 0;
    bD->iopOK[1] = 0;
    bD->iopFineTop[0] = 0;
    bD->iopFineTop[1] = 0;
    bD->iopFine[0] = 0;
    bD->iopFine[1] = 0;
    hBgmSetCh(ch);
    bD->bgmNo = no;
    bD->bgmChMax = BgmTable[no].chnum / 2;
    bD->bgmLength = BgmTable[no].chsize;
    bD->bgmSkipSize = hBgmGetLoopSize(no);
    bD->cdTop = BgmTable[no].start + bD->file.lsn;
    bD->cdSectors = ((BgmTable[no].chsize + 0x7FF) / 0x800) * BgmTable[no].chnum;
    bD->cdCur = bD->cdTop + bD->cdSectors - BgmTable[no].chnum * 64;
    bD->fadeFlag = 0;
    bD->bgmVol = 0.78740156f;
    bD->nextNo = -1;
    hCdCuePush(bD->cdCur, 0x100, bD->iopAddr[bD->iopID], 1, cD->eeCnt);
    bD->cdReq = 0;
    bD->cdCur += 0x100;
    bD->cdRemain = bD->cdCur - (bD->cdTop + bD->cdSectors);
}
#endif

void hBgmFadeIn(BGM no, s32 ch, s32 frame) {
    hBgmPlay(no, ch);
    if (frame > 0) {
        bD->fadeFlag = 2;
        bD->fadeCnt = 0;
        bD->fadeMax = frame;
    }
}

void hBgmFadeOut(s32 frame) {
#ifdef KL2_VER_RETAIL
    if (sD->Stereo != SND_MODE_5P1CH || aD->field_0x80 == 0) {
#endif
        bD->fadeFlag = 1;
        bD->fadeCnt = 0;
        bD->fadeMax = frame;
#ifdef KL2_VER_RETAIL
    }
#endif
}

void hBgmFadeNext(s32 frame, BGM nextno, s32 nextch, s32 nextframe, f32 nextvol) {
    bD->fadeFlag = 1;
    bD->fadeCnt = 0;
    bD->fadeMax = frame;
    bD->nextNo = nextno;
    bD->nextCh = nextch;
    bD->nextFrame = nextframe;
    bD->nextVol = nextvol;
}

void hBgmPause() {
    bD->Command |= 2;
}

void hBgmSetVol(f32 vol) {
    bD->bgmVol = vol;
}

void hBgmMute() {
    bD->bgmMute = 1 - bD->bgmMute;
}

void hBgmSetCh(s32 ch) {
    bD->Command |= 8;
    bD->bgmCh = ch;
}

void hBgmChangeChX(s32 ch) {
    bD->Command |= 0x10;
    bD->bgmCh = ch;
}

#ifdef KL2_VER_TRIAL
void hBgmRelay(s32 ch) {
    s32 no = bD->bgmNo2;
    bD->Command |= 0x20;
    hCdCueFlushBGM();
    if (cD->dataFlag == 1 && cD->dataStat != 2) {
        while (!sceCdBreak());
        cD->dataStat = 0;
    }

    bD->bgmCh = ch;
    bD->bgmNo = no;
    bD->bgmChMax = BgmTable[no].chnum / 2;
    bD->cdCur = bD->cdTop = BgmTable[no].start + (bD->Fp).lsn;
    bD->cdSectors = BgmTable[no].chsize * BgmTable[no].chnum;
    bD->iopID = 0;
    bD->iopOK[0] = 0;
    bD->iopOK[1] = 0;
    bD->fadeFlag = 0;
    bD->bgmVol = 0.92913383f;
    bD->nextNo = -1;
    hCdCuePush(bD->cdCur, 0x100, bD->iopAddr[0], 1, cD->eeCnt + 0x20);
    bD->cdReq = 0;
    bD->cdCur += 0x100;
    bD->cdRemain = bD->cdCur - (bD->cdTop + bD->cdSectors);
}
#endif

void hBgmStandby(BGM no) {
    bD->bgmNo2 = no;
    hCdCuePush(BgmTable[no].start + bD->Fp.lsn, 0, bD->iopAddr[2], 2, cD->eeCnt);
}

void hBgmWorkClear() {
    bD->nextNo = -1;
    bD->bgmCh = 0;
    bD->bgmChMax = 2;
    bD->iopOK[0] = 0;
    bD->iopOK[1] = 0;
    bD->iopID = 0;
    bD->cdReq = 0;
    bD->fadeFlag = 0;
    bD->bgmVol = 0.0f;
    bD->bgmMute = 0;
    cD->BGMplay = 0;
}

void hBgmReset() {
    if (cD->dataFlag == CDREAD_BGM && cD->dataStat != 2) {
        while (!sceCdBreak());
        cD->dataStat = 0;
    }

    hBgmWorkClear();
    bD->Command |= 0x4;
    hCdCueFlushBGM();
#ifdef KL2_VER_RETAIL
    if (sD->Stereo == SND_MODE_5P1CH && aD->field_0x80 != 0) {
        hStr_0016f6e8();
    }
#endif
}

void hBgmStop() {
    if (cD->dataFlag == CDREAD_BGM && cD->dataStat != 2) {
        while (!sceCdBreak());
        cD->dataStat = 0;
    }

    bD->bgmCh = 0;
    bD->bgmChMax = 2;
    bD->iopOK[0] = 0;
    bD->iopOK[1] = 0;
    bD->iopID = 0;
    bD->cdReq = 0;
    bD->fadeFlag = 0;
    bD->bgmVol = 0.0f;
    bD->bgmMute = 0;
    cD->BGMplay = 0;
    bD->Command |= 4;
    hCdCueFlushBGM();
}

void hBgmFadeNextClear() {
    if (cD->dataFlag == CDREAD_BGM && cD->dataStat != 2) {
        while (!sceCdBreak());
        cD->dataStat = 0;
    }

    bD->iopOK[0] = 0;
    bD->iopOK[1] = 0;
    bD->iopID = 0;
    bD->cdReq = 0;
    bD->bgmVol = 0.0f;
    bD->bgmMute = 0;
    bD->Command |= 4;
    hCdCueFlushBGM();
}

void hBgmRead() {
    s32 nsec;

    nsec = 0x100;
    if (bD->cdRemain == 0) {
        bD->cdCur = hBgmGetLoopLSN();
    } else {
        bD->iopFineTop[bD->iopID] = 0;
        bD->iopFine[bD->iopID] = 0;
    }

    bD->cdRemain = (bD->cdCur + nsec) - (bD->cdTop + bD->cdSectors);
    if (bD->cdRemain > 0)
        nsec -= bD->cdRemain;
    hCdCuePush(bD->cdCur, nsec, bD->iopAddr[bD->iopID], 1, cD->eeCnt);
    bD->cdReq = 0;
    bD->cdCur += nsec;
}

void hBgmRemain() {
    bD->cdCur = hBgmGetLoopLSN();
    hCdCuePush(bD->cdCur, bD->cdRemain, bD->iopAddr[bD->iopID] + 0x80000 - bD->cdRemain * 0x800, 1, cD->eeCnt);
    bD->cdCur += bD->cdRemain;
    bD->cdRemain = bD->cdCur - (bD->cdTop + bD->cdSectors);
    bD->cdReq = 0;
}

void hBgmMain() {
#ifdef KL2_VER_TRIAL
    if (!cD->BGMplay) {
        return;
    }
#endif

    switch (bD->fadeFlag) {
        case 2:
            if (!(bD->Command & 2) && ++bD->fadeCnt >= bD->fadeMax)
                bD->fadeFlag = 0;
            break;
        case 1:
            if (!(bD->Command & 2) && ++bD->fadeCnt >= bD->fadeMax) {
                if (bD->nextNo != -1) {
                    hBgmFadeNextClear();
                    bD->fadeFlag = 3;
                } else {
                    hBgmReset();
                    bD->fadeFlag = 0;
                }
            }
            break;
        case 3:
            if (!(bD->Command & 2)) {
                bD->fadeFlag = 0;
                hBgmFadeIn(bD->nextNo, bD->nextCh, bD->nextFrame);
                hBgmSetVol(bD->nextVol);
                bD->nextNo = -1;
            }
            break;
    }


#ifdef KL2_VER_RETAIL
    if (!cD->BGMplay) {
        return;
    }
#endif

    if (cD->dataFlag == CDREAD_BGM) {
        if (cD->dataStat == 2) {
            if (bD->cdRemain > 0) {
                hBgmRemain();
            } else {
                bD->iopOK[bD->iopID] = 1;
                bD->iopID = 1 - bD->iopID;
                bD->cdReq = 1;
            }
        }
    } else if (bD->iopID == bD->iopNext && bD->cdReq != 0) {
        hBgmRead();
    }
}

s32 hBgmGetMaxCh(BGM no) {
    return BgmTable[no].chnum / 2;
}

s32 hBgmGetStat() {
    if (cD->BGMplay != 0) {
        switch (bD->fadeFlag) {
            case 1:
                return 3;
            case 2:
                return 2;
            case 3:
                return 3;
            default:
                return 1;
        }
    } else {
        return 0;
    }    
}

BGM hBgmGetPlayNo() {
    if (hBgmGetStat()) {
        return bD->bgmNo;
    } else {
        return -1;
    }
}

s32 hBgmGetPlayCh() {
    if (hBgmGetStat()) {
        return bD->bgmCh;
    } else {
        return -1;
    }
}

void hBgmChangeID(s32 id, s32 mode) {
    gD->BGMchgreq = 1;
    gD->BGMchgid = id;
    gD->BGMchgmode = mode;
}

void hPptWorkClear() {
    s32 i;

    bD->Command |= 0x80;
    pD->pptMute = 0;
    pD->eeID = 0;
    pD->iopID = 0;
    pD->reqNum = 0;
    KL2_VER_RETAIL_ONLY(pD->reqID = 0);
    pD->listLoad = 0;
    pD->listPlay = 0;
    pD->listPlayIdx = 0;
    for (i = 0; i < 8; i++) {
        pD->listNum[i] = 0;
        pD->listTbl[i] = 0;
    }
    for (i = 0; i < 4; i++) {
        pD->pptPlay[i] = 0;
        pD->eeStat[i] = 0;
    }
}

void hPptStop(s32 id) {
#ifdef KL2_VER_RETAIL
    s32 num = (id >> 8) & 0xFFFFFF;
    id &= 0xFF;
    if (pD->pptID[id] == num) {
#endif
        pD->pptStop[id] = 1;
        if (pD->eeStat[id] == 3) {
            pD->eeStat[id] = 0;
        }
#ifdef KL2_VER_RETAIL
    }
#endif
}

void hPptReset() {
    if (cD->dataFlag == CDREAD_PPT && cD->dataStat != 2) {
        while (!sceCdBreak());
        cD->dataStat = 0;
    }

    hCdCueFlushPPT();
    hPptWorkClear();
}

#ifdef KL2_VER_TRIAL
void hPptSetVol(f32 vol) {
    sD->pptMVol = vol;
}
#endif

void hPptPause() {
    bD->Command |= 0x40;
}

s32 hPptReq() {
#ifdef KL2_VER_TRIAL
    pD->reqNum++;
    return (pD->eeID + pD->reqNum - 1) % 4;
#else
    s32 var1;
    s32 var2;

    var1 = (pD->iopID + pD->reqNum) % 4;
    var2 = pD->reqID + pD->reqNum;
    pD->reqNum++;
    return var2 << 8 | var1;
#endif
}

void hPptKick() {
    s32 id = pD->iopID;
    if (pD->reqNum != 0 && pD->iopNext[id] == -1 && pD->eeStat[id] == 2) {
        pD->pptPlay[id] = pD->pptSize[id];
        pD->pptVol[id] = pD->reqVol[id];
        KL2_VER_RETAIL_ONLY(pD->pptID[id] = pD->reqID);
        pD->iopNext[id] = 0;
        pD->iopBfID[id] = 0;
        pD->eeStat[id] = 3;
        pD->eeOffset[id] = 0;
        pD->reqNum--;
        KL2_VER_RETAIL_ONLY(pD->reqID++);
        KL2_VER_RETAIL_ONLY(pD->reqID &= 0xFFFFFF);
        pD->iopID++;
        if (pD->iopID == 4) {
            pD->iopID = 0;
        }
    }
}

s32 hPptGetFrame(s32 no) {
    return (PptTable[no & 0xFFFF].nsector * 2048 + 209) / 210;
}

void hPptSetList(s32 *p) {
    s32 ld;

    ld = pD->listLoad;
    pD->listNum[ld] = *p++;
    pD->listTbl[ld] = p;
    pD->listLoad++;
    if (pD->listLoad > 7) {
        pD->listLoad = 0;
    }
}

s32 hPptCheckList() {
    return pD->listNum[pD->listPlay] > pD->listPlayIdx ? 1 : 0;
}

s32 hPptGetListNo() {
    s32 no;

    no = pD->listTbl[pD->listPlay][pD->listPlayIdx];
    pD->listPlayIdx++;
    if (pD->listPlayIdx >= pD->listNum[pD->listPlay]) {
        pD->listNum[pD->listPlay] = 0;
        pD->listPlayIdx = 0;
        pD->listPlay++;
        if (pD->listPlay > 7) {
            pD->listPlay = 0;
        }
    }

    return no;
}

void hPptMain() {
    s32 i;
    s32 no;

    hPptKick();
    for (i = 0; i < 4; i++) {
        if (pD->eeStat[i] == 3 && pD->iopNext[i] == pD->iopBfID[i]) {
            hTrans2IOP(pD->iopAddr[i][pD->iopNext[i]], pD->eeAddr[i] + pD->eeOffset[i], 0x4000);
            pD->eeOffset[i] += 0x4000;
            if (pD->eeOffset[i] >= pD->pptSize[i])
                pD->eeStat[i] = 0;
            else
                pD->iopBfID[i] = 1 - pD->iopBfID[i];
        }
    }

    if (hPptCheckList() && pD->eeStat[pD->eeID] == 0) {
        pD->eeStat[pD->eeID] = 1;
        no = hPptGetListNo();
        if (no >> 0x10 != 0) {
            pD->reqVol[pD->eeID] = 0.7f;
        } else {
            pD->reqVol[pD->eeID] = 1.0f;
        }
        no &= 0xFFFF;
        hCdCuePush(PptTable[no].top + pD->file.lsn, PptTable[no].nsector, pD->eeAddr[pD->eeID], 3, cD->eeCnt);
        pD->pptSize[pD->eeID] = PptTable[no].nsector * 2048;
    }

    if (cD->dataFlag == CDREAD_PPT && cD->dataStat == 2) {
        pD->eeStat[pD->eeID] = 2;
        pD->eeID++;
        if (pD->eeID == 4)
            pD->eeID = 0;
    }
}

void hStrInfo() {
    STRINFO *info;
    s32 i;
    s32 vol;
    f32 volf;

    info = (STRINFO *)RpcArg;

    switch (bD->fadeFlag) {
        case 2:
            volf = (f32)bD->fadeCnt / (f32)bD->fadeMax;
            break;
        case 1:
            volf = (f32)(bD->fadeMax - bD->fadeCnt) / (f32)bD->fadeMax;
            break;
        case 3:
            volf = 0.0f;
            break;
        default:
            volf = 1.0f;
            break;
    }

    switch (sD->pptFade) {
        case 0:
            break;
        case 1:
            volf *= 1.0f - sD->pptFadeCnt * KL2_VER_COND(0.0999999999999999777955, 0.15f) / 60.0f;
            sD->pptFadeCnt++;
            if (sD->pptFadeCnt >= 60.0f) {
                sD->pptFade = 2;
            }
            break;
        case 2:
            volf *= KL2_VER_COND(0.9, 0.85f);
            break;
        case 3:
            volf *= KL2_VER_COND(0.9, 0.85f) + sD->pptFadeCnt * KL2_VER_COND(0.0999999999999999777955, 0.15f) / 60.0f;
            sD->pptFadeCnt++;
            if (sD->pptFadeCnt >= 60.0f) {
                sD->pptFade = 0;
            }
            break;
    }

    if (sD->Stereo == SND_MODE_MONAURAL) {
        volf *= 1.0f KL2_VER_COND(-, +) KL2_VER_COND(3.0f, 6.0f) / sD->dBfader;
    }

    vol = sD->bgmMVol * bD->bgmVol * hSndFader2(volf) * 16367.0f;
    if (vol > 0x3FFF) {
        vol = 0x3FFF;
    } else if (vol < 0) {
        vol = 0;
    }
    if (bD->bgmMute != 0) {
        vol = 0;
    }
    if (hBgmGetStat() == 0) {
        vol = 0;
    }

    info->eeCnt = cD->eeCnt;
    info->Command = bD->Command;
    info->BGMok[0] = bD->iopOK[0];
    info->BGMok[1] = bD->iopOK[1];
    info->BGMfine[0] = bD->iopFine[0];
    info->BGMfine[1] = bD->iopFine[1];
    info->BGMfinetop[0] = bD->iopFineTop[0];
    info->BGMfinetop[1] = bD->iopFineTop[1];
    KL2_VER_RETAIL_ONLY(info->BGMlength = bD->bgmLength);
    KL2_VER_RETAIL_ONLY(info->BGMskipsize = bD->bgmSkipSize);
    KL2_VER_RETAIL_ONLY(info->BGMstereo = sD->Stereo);
    info->BGMvol = vol;
    info->BGMch = bD->bgmCh;
    info->BGMchmax = bD->bgmChMax;
#ifdef KL2_VER_RETAIL
    if (info->Command & 32) {
        info->work0 = (bD->cdSectors / BgmTable[bD->bgmNo].chnum - 64) * 2048;
    }
#endif

    volf = 1.0f;
    if (sD->Stereo == SND_MODE_MONAURAL) {
        volf *= 1.0f - KL2_VER_COND(3.0f, 6.0f) / sD->dBfader;
    }

    for (i = 0; i < 4; i++) {
        vol = sD->pptMVol * hSndFader2(volf * pD->pptVol[i]) * 16367.0f;
        if (vol > 0x3FFF) {
            vol = 0x3FFF;
        } else if (vol < 0) {
            vol = 0;
        }
        if (pD->pptMute != 0) {
            vol = 0;
        }

        info->PPTvol[i] = vol;
        info->PPTsize[i] = pD->pptPlay[i];
        info->PPTstop[i] = pD->pptStop[i];
        pD->pptPlay[i] = 0;
        pD->pptStop[i] = 0;
    }

    KL2_VER_RETAIL_ONLY(info->idk = aD->field_0x94);
    hRpc(IOP_StrInfo);
    bD->Command = 0;
    bD->iopOK[0] = 0;
    bD->iopOK[1] = 0;
}

void hStrInit() {
    s32 i;
    s32 j;
    s32 addr;

    KL2_DEBUG_PRINT(("hStrInit ...\n"));
    bD = &BgmData;
    pD = &PptData;
    KL2_VER_RETAIL_ONLY(aD = &Ac3Data);

    hBgmWorkClear();
    bD->Command = 0;
    bD->bgmVol = 0.92913383f;
    addr = hRpc(IOP_StrInit);
    bD->iopAddr[0] = addr;
    bD->iopAddr[1] = bD->iopAddr[0] + 0x80000;
    bD->iopAddr[2] = bD->iopAddr[1] + 0x80000;

    hPptWorkClear();
    addr = bD->iopAddr[2];
    for (i = 0; i < 4; i++) {
        pD->pptPlay[i] = 0;
        pD->eeStat[i] = 0;
        pD->eeAddr[i] = (s32)(SndTempBuff + i * 0x40000);
        for (j = 0; j < 2; j++) {
            pD->iopAddr[i][j] = addr;
            addr += 0x4000;
        }
    }

    KL2_VER_RETAIL_ONLY(aD->field_0xB4[0] = addr);
    KL2_VER_RETAIL_ONLY(aD->field_0xB4[1] = addr + 0x8000);
    hStrInfo();
    while (hRpcSync());
    hSndRpcRet();
    bD->iopID = bD->iopNext;

    sceCdDiskReady(0);
    while (!sceCdSearchFile(&bD->Fp, KL2_VER_COND("\\KLONOA2\\BGMPACK.BIN;1", "\\BGMPACK.BIN;1")));
    sceCdDiskReady(0);
    while (!sceCdSearchFile(&pD->file, KL2_VER_COND("\\KLONOA2\\PPTPACK.BIN;1", "\\PPTPACK.BIN;1")));
    KL2_VER_RETAIL_ONLY(hStr_0016f4d8());
    KL2_DEBUG_PRINT(("hStrInit ... done\n"));
}