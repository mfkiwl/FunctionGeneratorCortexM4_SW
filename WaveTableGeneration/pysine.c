/** 
* @file pysine.c
* @author chris sutton 
* @brief  
* @version 0.1 
* @date 18-Mar-2020 
* @copyright Copyright (c) 2020 
* Generated with Python!
*/ 

#include <pysine.h>

uint32_t sine_data_table_100[SINE_DATA_SIZE] = {
	3050, 3052, 3055, 3058, 3061, 3064, 3067, 3070, 3072, 3075, 
	3078, 3080, 3082, 3085, 3087, 3089, 3091, 3093, 3095, 3096, 
	3098, 3099, 3101, 3102, 3103, 3104, 3104, 3105, 3105, 3105, 
	3106, 3105, 3105, 3105, 3104, 3104, 3103, 3102, 3101, 3099, 
	3098, 3096, 3095, 3093, 3091, 3089, 3087, 3085, 3082, 3080, 
	3078, 3075, 3072, 3070, 3067, 3064, 3061, 3058, 3055, 3052, 
	3050, 3047, 3044, 3041, 3038, 3035, 3032, 3029, 3027, 3024, 
	3022, 3019, 3017, 3014, 3012, 3010, 3008, 3006, 3004, 3003, 
	3001, 3000, 2998, 2997, 2996, 2995, 2995, 2994, 2994, 2994, 
	2994, 2994, 2994, 2994, 2995, 2995, 2996, 2997, 2998, 3000, 
	3001, 3003, 3004, 3006, 3008, 3010, 3012, 3014, 3017, 3019, 
	3022, 3024, 3027, 3029, 3032, 3035, 3038, 3041, 3044, 3047
};

uint32_t sine_data_table_200[SINE_DATA_SIZE] = {
	3050, 3056, 3062, 3068, 3074, 3081, 3087, 3093, 3098, 3104, 
	3110, 3115, 3120, 3125, 3130, 3134, 3139, 3143, 3147, 3150, 
	3153, 3156, 3159, 3162, 3164, 3165, 3167, 3168, 3169, 3169, 
	3170, 3169, 3169, 3168, 3167, 3165, 3164, 3162, 3159, 3156, 
	3153, 3150, 3147, 3143, 3139, 3134, 3130, 3125, 3120, 3115, 
	3110, 3104, 3098, 3093, 3087, 3081, 3074, 3068, 3062, 3056, 
	3050, 3043, 3037, 3031, 3025, 3018, 3012, 3006, 3001, 2995, 
	2990, 2984, 2979, 2974, 2969, 2965, 2960, 2956, 2952, 2949, 
	2946, 2943, 2940, 2937, 2935, 2934, 2932, 2931, 2930, 2930, 
	2930, 2930, 2930, 2931, 2932, 2934, 2935, 2937, 2940, 2943, 
	2946, 2949, 2952, 2956, 2960, 2965, 2969, 2974, 2979, 2984, 
	2990, 2995, 3001, 3006, 3012, 3018, 3025, 3031, 3037, 3043
};

uint32_t sine_data_table_300[SINE_DATA_SIZE] = {
	3050, 3060, 3070, 3080, 3089, 3099, 3109, 3118, 3128, 3137, 
	3146, 3154, 3162, 3170, 3178, 3185, 3192, 3199, 3205, 3211, 
	3216, 3221, 3225, 3229, 3232, 3235, 3237, 3239, 3240, 3241, 
	3242, 3241, 3240, 3239, 3237, 3235, 3232, 3229, 3225, 3221, 
	3216, 3211, 3205, 3199, 3192, 3185, 3178, 3170, 3162, 3154, 
	3146, 3137, 3128, 3118, 3109, 3099, 3089, 3080, 3070, 3060, 
	3050, 3039, 3029, 3019, 3010, 3000, 2990, 2981, 2971, 2962, 
	2954, 2945, 2937, 2929, 2921, 2914, 2907, 2900, 2894, 2888, 
	2883, 2878, 2874, 2870, 2867, 2864, 2862, 2860, 2859, 2858, 
	2858, 2858, 2859, 2860, 2862, 2864, 2867, 2870, 2874, 2878, 
	2883, 2888, 2894, 2900, 2907, 2914, 2921, 2929, 2937, 2945, 
	2954, 2962, 2971, 2981, 2990, 3000, 3010, 3019, 3029, 3039
};

uint32_t sine_data_table_400[SINE_DATA_SIZE] = {
	3050, 3063, 3076, 3090, 3103, 3116, 3129, 3142, 3154, 3166, 
	3178, 3189, 3201, 3211, 3221, 3231, 3240, 3249, 3257, 3265, 
	3272, 3278, 3284, 3289, 3294, 3298, 3301, 3303, 3305, 3306, 
	3307, 3306, 3305, 3303, 3301, 3298, 3294, 3289, 3284, 3278, 
	3272, 3265, 3257, 3249, 3240, 3231, 3221, 3211, 3201, 3189, 
	3178, 3166, 3154, 3142, 3129, 3116, 3103, 3090, 3076, 3063, 
	3050, 3036, 3023, 3009, 2996, 2983, 2970, 2957, 2945, 2933, 
	2921, 2910, 2898, 2888, 2878, 2868, 2859, 2850, 2842, 2834, 
	2827, 2821, 2815, 2810, 2805, 2801, 2798, 2796, 2794, 2793, 
	2793, 2793, 2794, 2796, 2798, 2801, 2805, 2810, 2815, 2821, 
	2827, 2834, 2842, 2850, 2859, 2868, 2878, 2888, 2898, 2910, 
	2921, 2933, 2945, 2957, 2970, 2983, 2996, 3009, 3023, 3036
};

uint32_t sine_data_table_500[SINE_DATA_SIZE] = {
	3050, 3067, 3084, 3101, 3117, 3134, 3151, 3167, 3183, 3198, 
	3213, 3228, 3242, 3255, 3268, 3281, 3293, 3304, 3314, 3324, 
	3333, 3341, 3348, 3355, 3360, 3365, 3369, 3372, 3375, 3376, 
	3377, 3376, 3375, 3372, 3369, 3365, 3360, 3355, 3348, 3341, 
	3333, 3324, 3314, 3304, 3293, 3281, 3268, 3255, 3242, 3228, 
	3213, 3198, 3183, 3167, 3151, 3134, 3117, 3101, 3084, 3067, 
	3050, 3032, 3015, 2998, 2982, 2965, 2948, 2932, 2916, 2901, 
	2886, 2871, 2857, 2844, 2831, 2818, 2806, 2795, 2785, 2775, 
	2766, 2758, 2751, 2744, 2739, 2734, 2730, 2727, 2724, 2723, 
	2723, 2723, 2724, 2727, 2730, 2734, 2739, 2744, 2751, 2758, 
	2766, 2775, 2785, 2795, 2806, 2818, 2831, 2844, 2857, 2871, 
	2886, 2901, 2916, 2932, 2948, 2965, 2982, 2998, 3015, 3032
};

uint32_t sine_data_table_600[SINE_DATA_SIZE] = {
	3050, 3070, 3091, 3111, 3132, 3152, 3172, 3191, 3210, 3229, 
	3247, 3265, 3282, 3298, 3314, 3329, 3343, 3356, 3369, 3381, 
	3392, 3401, 3410, 3418, 3425, 3431, 3436, 3440, 3442, 3444, 
	3445, 3444, 3442, 3440, 3436, 3431, 3425, 3418, 3410, 3401, 
	3392, 3381, 3369, 3356, 3343, 3329, 3314, 3298, 3282, 3265, 
	3247, 3229, 3210, 3191, 3172, 3152, 3132, 3111, 3091, 3070, 
	3050, 3029, 3008, 2988, 2967, 2947, 2927, 2908, 2889, 2870, 
	2852, 2834, 2817, 2801, 2785, 2770, 2756, 2743, 2730, 2718, 
	2707, 2698, 2689, 2681, 2674, 2668, 2663, 2659, 2657, 2655, 
	2655, 2655, 2657, 2659, 2663, 2668, 2674, 2681, 2689, 2698, 
	2707, 2718, 2730, 2743, 2756, 2770, 2785, 2801, 2817, 2834, 
	2852, 2870, 2889, 2908, 2927, 2947, 2967, 2988, 3008, 3029
};

uint32_t sine_data_table_700[SINE_DATA_SIZE] = {
	3050, 3074, 3098, 3121, 3145, 3169, 3192, 3214, 3237, 3258, 
	3280, 3300, 3320, 3339, 3357, 3375, 3391, 3407, 3422, 3435, 
	3448, 3459, 3470, 3479, 3487, 3494, 3499, 3504, 3507, 3509, 
	3510, 3509, 3507, 3504, 3499, 3494, 3487, 3479, 3470, 3459, 
	3448, 3435, 3422, 3407, 3391, 3375, 3357, 3339, 3320, 3300, 
	3280, 3258, 3237, 3214, 3192, 3169, 3145, 3121, 3098, 3074, 
	3050, 3025, 3001, 2978, 2954, 2930, 2907, 2885, 2862, 2841, 
	2820, 2799, 2779, 2760, 2742, 2724, 2708, 2692, 2677, 2664, 
	2651, 2640, 2629, 2620, 2612, 2605, 2600, 2595, 2592, 2590, 
	2590, 2590, 2592, 2595, 2600, 2605, 2612, 2620, 2629, 2640, 
	2651, 2664, 2677, 2692, 2708, 2724, 2742, 2760, 2779, 2799, 
	2820, 2841, 2862, 2885, 2907, 2930, 2954, 2978, 3001, 3025
};

uint32_t sine_data_table_800[SINE_DATA_SIZE] = {
	3050, 3077, 3105, 3132, 3160, 3187, 3213, 3239, 3265, 3290, 
	3315, 3338, 3361, 3383, 3404, 3424, 3443, 3461, 3478, 3494, 
	3508, 3522, 3534, 3544, 3554, 3561, 3568, 3573, 3577, 3579, 
	3580, 3579, 3577, 3573, 3568, 3561, 3554, 3544, 3534, 3522, 
	3508, 3494, 3478, 3461, 3443, 3424, 3404, 3383, 3361, 3338, 
	3315, 3290, 3265, 3239, 3213, 3187, 3160, 3132, 3105, 3077, 
	3050, 3022, 2994, 2967, 2939, 2912, 2886, 2860, 2834, 2809, 
	2785, 2761, 2738, 2716, 2695, 2675, 2656, 2638, 2621, 2605, 
	2591, 2577, 2565, 2555, 2545, 2538, 2531, 2526, 2522, 2520, 
	2520, 2520, 2522, 2526, 2531, 2538, 2545, 2555, 2565, 2577, 
	2591, 2605, 2621, 2638, 2656, 2675, 2695, 2716, 2738, 2761, 
	2785, 2809, 2834, 2860, 2886, 2912, 2939, 2967, 2994, 3022
};

uint32_t sine_data_table_900[SINE_DATA_SIZE] = {
	3050, 3080, 3111, 3142, 3172, 3202, 3232, 3261, 3289, 3317, 
	3345, 3371, 3396, 3421, 3444, 3467, 3488, 3508, 3527, 3544, 
	3560, 3575, 3588, 3600, 3611, 3619, 3627, 3632, 3636, 3639, 
	3640, 3639, 3636, 3632, 3627, 3619, 3611, 3600, 3588, 3575, 
	3560, 3544, 3527, 3508, 3488, 3467, 3444, 3421, 3396, 3371, 
	3345, 3317, 3289, 3261, 3232, 3202, 3172, 3142, 3111, 3080, 
	3050, 3019, 2988, 2957, 2927, 2897, 2867, 2838, 2810, 2782, 
	2755, 2728, 2703, 2678, 2655, 2632, 2611, 2591, 2572, 2555, 
	2539, 2524, 2511, 2499, 2488, 2480, 2472, 2467, 2463, 2460, 
	2460, 2460, 2463, 2467, 2472, 2480, 2488, 2499, 2511, 2524, 
	2539, 2555, 2572, 2591, 2611, 2632, 2655, 2678, 2703, 2728, 
	2755, 2782, 2810, 2838, 2867, 2897, 2927, 2957, 2988, 3019
};

uint32_t sine_data_table_1000[SINE_DATA_SIZE] = {
	3050, 3084, 3117, 3151, 3185, 3218, 3250, 3282, 3314, 3345, 
	3375, 3404, 3432, 3459, 3484, 3509, 3533, 3555, 3575, 3595, 
	3612, 3629, 3643, 3656, 3668, 3677, 3685, 3691, 3696, 3699, 
	3700, 3699, 3696, 3691, 3685, 3677, 3668, 3656, 3643, 3629, 
	3612, 3595, 3575, 3555, 3533, 3509, 3484, 3459, 3432, 3404, 
	3375, 3345, 3314, 3282, 3250, 3218, 3185, 3151, 3117, 3084, 
	3050, 3015, 2982, 2948, 2914, 2881, 2849, 2817, 2785, 2754, 
	2725, 2695, 2667, 2640, 2615, 2590, 2566, 2544, 2524, 2504, 
	2487, 2470, 2456, 2443, 2431, 2422, 2414, 2408, 2403, 2400, 
	2400, 2400, 2403, 2408, 2414, 2422, 2431, 2443, 2456, 2470, 
	2487, 2504, 2524, 2544, 2566, 2590, 2615, 2640, 2667, 2695, 
	2725, 2754, 2785, 2817, 2849, 2881, 2914, 2948, 2982, 3015
};

uint32_t sine_data_table_1100[SINE_DATA_SIZE] = {
	3050, 3087, 3124, 3161, 3197, 3233, 3269, 3304, 3338, 3372, 
	3405, 3436, 3467, 3496, 3525, 3552, 3577, 3601, 3624, 3645, 
	3664, 3682, 3698, 3712, 3725, 3735, 3744, 3751, 3756, 3759, 
	3760, 3759, 3756, 3751, 3744, 3735, 3725, 3712, 3698, 3682, 
	3664, 3645, 3624, 3601, 3577, 3552, 3525, 3496, 3467, 3436, 
	3405, 3372, 3338, 3304, 3269, 3233, 3197, 3161, 3124, 3087, 
	3050, 3012, 2975, 2938, 2902, 2866, 2830, 2795, 2761, 2727, 
	2695, 2663, 2632, 2603, 2574, 2547, 2522, 2498, 2475, 2454, 
	2435, 2417, 2401, 2387, 2374, 2364, 2355, 2348, 2343, 2340, 
	2340, 2340, 2343, 2348, 2355, 2364, 2374, 2387, 2401, 2417, 
	2435, 2454, 2475, 2498, 2522, 2547, 2574, 2603, 2632, 2663, 
	2695, 2727, 2761, 2795, 2830, 2866, 2902, 2938, 2975, 3012
};

uint32_t sine_data_table_1200[SINE_DATA_SIZE] = {
	3050, 3090, 3130, 3170, 3210, 3249, 3287, 3325, 3363, 3399, 
	3435, 3469, 3502, 3534, 3565, 3594, 3622, 3648, 3672, 3695, 
	3716, 3736, 3753, 3768, 3782, 3793, 3803, 3810, 3815, 3818, 
	3820, 3818, 3815, 3810, 3803, 3793, 3782, 3768, 3753, 3736, 
	3716, 3695, 3672, 3648, 3622, 3594, 3565, 3534, 3502, 3469, 
	3435, 3399, 3363, 3325, 3287, 3249, 3210, 3170, 3130, 3090, 
	3050, 3009, 2969, 2929, 2889, 2850, 2812, 2774, 2736, 2700, 
	2665, 2630, 2597, 2565, 2534, 2505, 2477, 2451, 2427, 2404, 
	2383, 2363, 2346, 2331, 2317, 2306, 2296, 2289, 2284, 2281, 
	2280, 2281, 2284, 2289, 2296, 2306, 2317, 2331, 2346, 2363, 
	2383, 2404, 2427, 2451, 2477, 2505, 2534, 2565, 2597, 2630, 
	2665, 2700, 2736, 2774, 2812, 2850, 2889, 2929, 2969, 3009
};

uint32_t sine_data_table_1300[SINE_DATA_SIZE] = {
	3050, 3095, 3139, 3184, 3228, 3272, 3315, 3358, 3399, 3440, 
	3480, 3518, 3555, 3591, 3625, 3658, 3689, 3718, 3745, 3771, 
	3794, 3816, 3835, 3852, 3867, 3880, 3891, 3899, 3905, 3908, 
	3910, 3908, 3905, 3899, 3891, 3880, 3867, 3852, 3835, 3816, 
	3794, 3771, 3745, 3718, 3689, 3658, 3625, 3591, 3555, 3518, 
	3480, 3440, 3399, 3358, 3315, 3272, 3228, 3184, 3139, 3095, 
	3050, 3004, 2960, 2915, 2871, 2827, 2784, 2741, 2700, 2659, 
	2620, 2581, 2544, 2508, 2474, 2441, 2410, 2381, 2354, 2328, 
	2305, 2283, 2264, 2247, 2232, 2219, 2208, 2200, 2194, 2191, 
	2190, 2191, 2194, 2200, 2208, 2219, 2232, 2247, 2264, 2283, 
	2305, 2328, 2354, 2381, 2410, 2441, 2474, 2508, 2544, 2581, 
	2620, 2659, 2700, 2741, 2784, 2827, 2871, 2915, 2960, 3004
};
